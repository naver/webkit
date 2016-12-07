/*
 * Copyright (C) 2015 Naver Corp. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "SWKViewNatives.h"

#include "CoordinatedDrawingAreaProxy.h"
#include "CoordinatedGraphicsScene.h"
#include "CoordinatedLayerTreeHostProxy.h"
#include "NativeWebEvent.h"
#include "WebBitmapNativesBase.h"
#include "SWKWebContentNatives.h"
#include "WebEditableNatives.h"
#include "WebPopupMenuProxySling.h"
#include "WebView.h"
#include <WebCore/CairoUtilities.h>
#include <WebCore/DragData.h>

#if ENABLE(CONTEXT_MENUS)
#include "WebContextMenuProxySling.h"
#endif

#include <NativesPoint.h>
#include <onig/WeakGlobalRef.h>

using namespace WebCore;

namespace WebKit {

static const float ALMOST_INTEGER_THRESHOLD = 0.1f;

static float snapAlmostIntegerDeviceScaleFactorToInteger(float deviceScaleFactor)
{
    float rounded = round(deviceScaleFactor);
    float diff = abs(rounded - deviceScaleFactor);
    if (diff < ALMOST_INTEGER_THRESHOLD)
        return rounded;
    return deviceScaleFactor;
}

SWKView::SWKView(SWKWebContent& webContent)
    : m_webContent(webContent)
    , m_pageViewportControllerClient(*this)
    , m_pageViewportController(&webContent.webPage(), m_pageViewportControllerClient)
    , m_lastCursorImage(nullptr)
    , m_hasInputMethod(false)
    , m_waitingForKeyEventHandled(false)
    , m_transientZoomMagnification(0.0f)
    , m_paintingDisabled(false)
    , m_overrideDeviceScaleFactor(0.0f)
{
}

SWKView::~SWKView()
{
}

bool SWKView::useFixedLayout()
{
    return webPage().useFixedLayout();
}

void SWKView::didChangeViewportAttributes()
{
    Natives::SWKView::didChangeViewportAttributes(m_pageViewportController.minimumScale(), m_pageViewportController.maximumScale(), m_pageViewportController.currentScale());
}

void SWKView::setViewportPosition(const FloatPoint& contentsPosition)
{
    pageClient().setContentPosition(contentsPosition);
    m_pageViewportController.didChangeContentsVisibility(contentsPosition, m_pageViewportController.currentScale());
    Natives::SWKView::didChangeContentsPosition(contentsPosition.x(), contentsPosition.y());
}

FloatRect SWKView::mapToViewport(const FloatRect& rect) const
{
    FloatRect mappedRect(rect);
    mappedRect.scale(const_cast<SWKView*>(this)->getIntrinsicDeviceScaleFactor());
    mappedRect.moveBy(-pageClient().contentPosition());
    return mappedRect;
}

void SWKView::setViewNeedsDisplay(const IntRect& dirtyRect)
{
    Natives::SWKView::setViewNeedsDisplay(dirtyRect.x(), dirtyRect.y(), dirtyRect.width(), dirtyRect.height());
}

bool SWKView::paintToCurrentGLContext()
{
    if (UNLIKELY(m_hasPaintingThreadTasks))
        performPaintingThreadTasks();

    if (m_paintingDisabled)
        return false;

    pageClient().paintToCurrentGLContext();
    return true;
}

void SWKView::contextLostGL()
{
    if (m_paintingDisabled)
        return;

    m_paintingDisabled = true;

    CoordinatedGraphicsScene* scene = pageClient().coordinatedGraphicsScene();
    scene->setGraphicsContextWasDestroyedElsewhere();
    scene->purgeGLResources();

    dispatchOnMainThread([=] {
        CoordinatedDrawingAreaProxy* drawingArea = static_cast<CoordinatedDrawingAreaProxy*>(webPage().drawingArea());
        drawingArea->resetCoordinatedGraphicsState();
        drawingArea->requestCoordinatedGraphicsStateAfterReset();
    });
}

void SWKView::teardownGL()
{
    ASSERT(m_paintingDisabled);

    Vector<RefPtr<CoordinatedGraphicsScene>> detachedScenes;

    {
        MutexLocker lock(m_paintingThreadMutex);
        WTF::swap(detachedScenes, m_detachedScenes);
    }

    for (auto& detachedScene : detachedScenes)
        detachedScene->deleteGLResourcesThenDestroyOnMainThread();
}

void SWKView::setViewResumePainting()
{
    m_paintingDisabled = false;
    setActive(true);
}

void SWKView::editorStateChanged()
{
    const EditorState& editorState = webPage().editorState();

    if (m_hasInputMethod) {
        if (editorState.selectionIsNone) {
            endInputMethod();
            m_hasInputMethod = false;
        }
    } else {
        if (editorState.isContentEditable) {
            startInputMethod(editorState.isInPasswordField);
            m_hasInputMethod = true;
        }
    }

    Natives::SWKView::editorStateChanged(editorState.editableText.utf8().data(), editorState.selectionRangeStart, editorState.selectionRangeEnd,
        editorState.compositionRangeStart, editorState.compositionRangeEnd);
}

void SWKView::setCursor(const Cursor& cursor)
{
    if (Image* cursorImage = cursor.image()) {
        if (cursorImage == m_lastCursorImage)
            return;

        m_lastCursorImage = cursorImage;
        RefPtr<cairo_surface_t> surface = cursorImage->nativeImageForCurrentFrame();
        if (!surface)
            return;

        flipImageSurfaceVertically(surface.get());
        cairo_surface_flush(surface.get());

        void* data = cairo_image_surface_get_data(surface.get());
        if (!data)
            return;

        FloatSize imageSize = cursorImage->size();
        Native::ImmutableArray<int32_t> imageData(reinterpret_cast<int32_t*>(data), imageSize.width() * imageSize.height());
        Native::LocalRef<Natives::WebBitmap> bitmap = Natives::WebBitmap::create(imageData, imageSize.width(), imageSize.height(), Natives::WebBitmap::CONFIG_ARGB_8888);

        Optional<IntPoint> hotspot = cursorImage->hotSpot();
        Natives::SWKView::didChangeCursor(hotspot->x(), hotspot->y(), bitmap);
        return;
    }

    m_lastCursorImage = nullptr;
    Natives::SWKView::didChangeCursor(static_cast<int32_t>(cursor.type()));
}

RefPtr<WebPopupMenuProxy> SWKView::createPopupMenuProxy(WebPageProxy& page)
{
    return WebPopupMenuProxySling::create(this, page);
}

#if ENABLE(CONTEXT_MENUS)
std::unique_ptr<WebContextMenuProxy> SWKView::createContextMenuProxy(WebPageProxy& page, const ContextMenuContextData& contextMenuContextData, const UserData& userData)
{
    return WebContextMenuProxySling::create(this, page, contextMenuContextData, userData);
}
#endif

bool SWKView::isSpeaking()
{
    return Natives::SWKView::isSpeaking();
}

void SWKView::speak(const String& string)
{
    Natives::SWKView::speak(string.utf8().data());
}

void SWKView::stopSpeaking()
{
    Natives::SWKView::stopSpeaking();
}

bool SWKView::isVisible()
{
    return pageClient().isVisible();
}

bool SWKView::isFocused()
{
    return pageClient().isFocused();
}

bool SWKView::isActive()
{
    return pageClient().isActive();
}

void SWKView::doneWithKeyEvent(const NativeWebKeyboardEvent& event, bool wasEventHandled)
{
    m_waitingForKeyEventHandled = false;

    if (m_pendingKeyEvents.isEmpty())
        return;

    if (wasEventHandled) {
        m_pendingKeyEvents.removeFirstMatching([&](const NativeWebKeyboardEvent& pendingEvent) {
            if (event.hash() == pendingEvent.hash())
                return true;
            return false;
        });

        if (m_pendingKeyEvents.isEmpty())
            return;
    }

    webPage().handleKeyboardEvent(m_pendingKeyEvents.at(0));
    m_pendingKeyEvents.remove(0);

    m_waitingForKeyEventHandled = true;
}

void SWKView::webProcessCrashed(const String& url)
{
    RefPtr<CoordinatedGraphicsScene> scene(pageClient().coordinatedGraphicsScene());
    if (!scene)
        return;

    enqueuePaintingThreadTask([=] {
        scene->deleteGLResourcesThenDestroyOnMainThread();
    });

    Natives::SWKView::webProcessCrashed(url.utf8().data());
}

void SWKView::webProcessDidRelaunch()
{
    // CoordinatedGraphics WebView has been deactivated automatically when
    // the web process is crashed.
    // So the WebView should be activated in order to be able to receive any
    // scene state from the newly created web process.
    setActive(true);
}

void SWKView::setPageScaleFactor(float scale, int32_t x, int32_t y)
{
    webPage().scalePage(scale, IntPoint(x, y));
}

float SWKView::getPageScaleFactor()
{
    return webPage().pageScaleFactor();
}

void SWKView::setIntrinsicDeviceScaleFactor(float scale)
{
    webPage().setIntrinsicDeviceScaleFactor(snapAlmostIntegerDeviceScaleFactorToInteger(scale));
}

float SWKView::getIntrinsicDeviceScaleFactor()
{
    if (m_overrideDeviceScaleFactor != 0.0f)
        return m_overrideDeviceScaleFactor;

    return webPage().deviceScaleFactor();
}

void SWKView::setOverrideDeviceScaleFactor(float overrideDeviceScaleFactor)
{
    // Default value is 0. A value of 0 means the window's backing scale factor
    // will be used and automatically update when the window moves screens.
    m_overrideDeviceScaleFactor = overrideDeviceScaleFactor;
}

float SWKView::getOverrideDeviceScaleFactor()
{
    return m_overrideDeviceScaleFactor;
}

void SWKView::setActive(bool active)
{
    pageClient().setActive(active);
    webPage().updateActivityState(active);
    webPage().viewStateDidChange(ViewState::IsVisible);
}

void SWKView::sendSingleTap(float x, float y)
{
    NativeWebMouseEvent fakeMouseDown = NativeWebEvent::createMouseEvent(currentTimeMS(),
        WebEventEnumerations::toMouseAction(WebEventEnumerations::ACTION_DOWN),
        WebEventEnumerations::toButton(WebEventEnumerations::MODIFIER_LEFT_BUTTON),
        WebEventEnumerations::toModifiers(0),
        x, y, x, y, 1, pageClient().transformFromScene());
    webPage().handleMouseEvent(fakeMouseDown);

    NativeWebMouseEvent fakeMouseMove = NativeWebEvent::createMouseEvent(currentTimeMS(),
        WebEventEnumerations::toMouseAction(WebEventEnumerations::ACTION_MOVE),
        WebEventEnumerations::toButton(0),
        WebEventEnumerations::toModifiers(0),
        x, y, x, y, 1, pageClient().transformFromScene());
    webPage().handleMouseEvent(fakeMouseMove);

    NativeWebMouseEvent fakeMouseUp = NativeWebEvent::createMouseEvent(currentTimeMS(),
        WebEventEnumerations::toMouseAction(WebEventEnumerations::ACTION_UP),
        WebEventEnumerations::toButton(WebEventEnumerations::MODIFIER_LEFT_BUTTON),
        WebEventEnumerations::toModifiers(0),
        x, y, x, y, 1, pageClient().transformFromScene());
    webPage().handleMouseEvent(fakeMouseUp);
}

void SWKView::sendSingleTapUnconfirmed(float x, float y)
{
    notImplemented();
}

void SWKView::sendDoubleTap(float x, float y)
{
    notImplemented();
}

void SWKView::sendLongTap(float x, float y)
{
    notImplemented();
}

void SWKView::sendShowPressState(float x, float y)
{
    notImplemented();
}

void SWKView::sendShowPressCancel(float x, float y)
{
    notImplemented();
}

void SWKView::sendLongPress(float x, float y)
{
    NativeWebMouseEvent fakeMouseDown = NativeWebEvent::createMouseEvent(currentTimeMS(),
        WebEventEnumerations::toMouseAction(WebEventEnumerations::ACTION_DOWN),
        WebEventEnumerations::toButton(WebEventEnumerations::MODIFIER_RIGHT_BUTTON),
        WebEventEnumerations::toModifiers(0),
        x, y, x, y, 1, pageClient().transformFromScene());
    webPage().handleMouseEvent(fakeMouseDown);

    NativeWebMouseEvent fakeMouseMove = NativeWebEvent::createMouseEvent(currentTimeMS(),
        WebEventEnumerations::toMouseAction(WebEventEnumerations::ACTION_MOVE),
        WebEventEnumerations::toButton(0),
        WebEventEnumerations::toModifiers(0),
        x, y, x, y, 1, pageClient().transformFromScene());
    webPage().handleMouseEvent(fakeMouseMove);

    NativeWebMouseEvent fakeMouseUp = NativeWebEvent::createMouseEvent(currentTimeMS(),
        WebEventEnumerations::toMouseAction(WebEventEnumerations::ACTION_UP),
        WebEventEnumerations::toButton(WebEventEnumerations::MODIFIER_RIGHT_BUTTON),
        WebEventEnumerations::toModifiers(0),
        x, y, x, y, 1, pageClient().transformFromScene());
    webPage().handleMouseEvent(fakeMouseUp);
}

void SWKView::sendTouchEvent(int64_t timestamp, int32_t action, int32_t modifiers, float x, float y, float globalX, float globalY, int32_t id)
{
#if ENABLE(TOUCH_EVENTS)
    NativeWebTouchEvent touchEvent = NativeWebEvent::createTouchEvent(timestamp,
        WebEventEnumerations::toTouchAction(action),
        WebEventEnumerations::toModifiers(modifiers),
        x, y, globalX, globalY, id,
        WebEventEnumerations::toTouchPointState(action), pageClient().transformFromScene());
    webPage().handleTouchEvent(touchEvent);
#endif
}

void SWKView::sendMouseEvent(int64_t timestamp, int32_t action, int32_t modifiers, float x, float y, float globalX, float globalY, int32_t clickCount)
{
    NativeWebMouseEvent mouseEvent = NativeWebEvent::createMouseEvent(timestamp,
        WebEventEnumerations::toMouseAction(action),
        WebEventEnumerations::toButton(modifiers),
        WebEventEnumerations::toModifiers(modifiers),
        x, y, globalX, globalY, clickCount, pageClient().transformFromScene());
    webPage().handleMouseEvent(mouseEvent);
}

void SWKView::sendWheelEvent(int64_t timestamp, int32_t action, int32_t modifiers, float deltaX, float deltaY, float x, float y, float globalX, float globalY)
{
    NativeWebWheelEvent wheelEvent = NativeWebEvent::createWheelEvent(timestamp, modifiers,
        deltaX, deltaY, x, y, globalX, globalY,
        pageClient().transformFromScene(), getIntrinsicDeviceScaleFactor());
    webPage().handleWheelEvent(wheelEvent);
}

void SWKView::sendKeyEvent(int64_t timestamp, int32_t action, int32_t modifiers, int32_t windowsVirtualKeyCode, int32_t nativeVirtualKeyCode,
    const std::string& text, const std::string& unmodifiedText, bool isAutoRepeat, bool isSystemKey, bool isKeypadKey, int32_t strokeHash)
{
    NativeWebKeyboardEvent keyEvent = NativeWebEvent::createKeyboardEvent(timestamp,
        WebEventEnumerations::toKeyAction(action),
        WebEventEnumerations::toModifiers(modifiers),
        windowsVirtualKeyCode, nativeVirtualKeyCode, String::fromUTF8(text.c_str()), String::fromUTF8(unmodifiedText.c_str()),
        isAutoRepeat, isSystemKey, isKeypadKey, strokeHash);
    if (m_waitingForKeyEventHandled) {
        m_pendingKeyEvents.append(keyEvent);
        return;
    }

    ASSERT(m_pendingKeyEvents.isEmpty());

    webPage().handleKeyboardEvent(keyEvent);
    m_waitingForKeyEventHandled = true;
}

void SWKView::setBackgroundColor(int32_t color)
{
    RefPtr<CoordinatedGraphicsScene> scene(pageClient().coordinatedGraphicsScene());
    if (!scene)
        return;

    scene->setViewBackgroundColor(color);
}

int32_t SWKView::getBackgroundColor()
{
    RefPtr<CoordinatedGraphicsScene> scene(pageClient().coordinatedGraphicsScene());
    if (!scene)
        return Color::white;

    return scene->viewBackgroundColor().rgb();
}

void SWKView::setUseFixedLayout(bool use)
{
    webPage().setUseFixedLayout(use);
}

bool SWKView::getUseFixedLayout()
{
    return useFixedLayout();
}

void SWKView::scrollBegin(float left, float top)
{
    pageClient().scrollBegin(FloatPoint(left, top));
}

bool SWKView::scrollBy(float deltaX, float deltaY, bool isOverScrollAllowed)
{
    if (pageClient().scrollBy(FloatSize(deltaX, deltaY), isOverScrollAllowed)) {
        const FloatPoint& position = pageClient().contentPosition();
        m_pageViewportController.didChangeContentsVisibility(position, pageClient().contentScaleFactor());
        Natives::SWKView::didChangeContentsPosition(position.x(), position.y());
        return true;
    }

    return false;
}

bool SWKView::scrollTo(float left, float top)
{
    notImplemented();
    return false;
}

void SWKView::scrollEnd(float, float)
{
    pageClient().scrollEnd();
}

void SWKView::pinchBegin(float x, float y)
{
    notImplemented();
}

void SWKView::adjustTransientZoom(float x, float y, float magnification)
{
    if (useFixedLayout()) {
        pageClient().setContentScaleFactor(magnification);
        pageClient().setContentPosition(FloatPoint(x, y));
        Natives::SWKView::setViewNeedsDisplay(0, 0, 0, 0);
        return;
    }

    if (CoordinatedDrawingAreaProxy* drawingArea = static_cast<CoordinatedDrawingAreaProxy*>(webPage().drawingArea())) {
        drawingArea->adjustTransientZoom(magnification, FloatPoint(x, y));
    }

    m_transientZoomOrigin = FloatPoint(x, y);
    m_transientZoomMagnification = magnification;
}

void SWKView::commitTransientZoom()
{
    if (useFixedLayout()) {
        pageClient().setContentScaleFactor(m_transientZoomMagnification);
        pageClient().setContentPosition(m_transientZoomOrigin);
        m_pageViewportController.didChangeContentsVisibility(m_transientZoomOrigin, m_transientZoomMagnification);
        return;
    }

    if (CoordinatedDrawingAreaProxy* drawingArea = static_cast<CoordinatedDrawingAreaProxy*>(webPage().drawingArea())) {
        drawingArea->commitTransientZoom(m_transientZoomMagnification, m_transientZoomOrigin);
    }
}

bool SWKView::requestExitFullScreen()
{
#if ENABLE(FULLSCREEN_API)
    return pageClient().requestExitFullScreen();
#else
    return false;
#endif
}

void SWKView::dispatchOnMainThread(std::function<void ()> function)
{
    if (isMainThread())
        function();
    else
        callOnMainThread(WTFMove(function));
}

void SWKView::nativeSetInWindow(bool inWindow)
{
    if (!inWindow) {
        RefPtr<CoordinatedGraphicsScene> scene(pageClient().coordinatedGraphicsScene());
        MutexLocker lock(m_paintingThreadMutex);
        m_detachedScenes.append(scene);

        CoordinatedDrawingAreaProxy* drawingArea = static_cast<CoordinatedDrawingAreaProxy*>(webPage().drawingArea());
        drawingArea->resetCoordinatedGraphicsState();
    } else if (!pageClient().coordinatedGraphicsScene()) {
        CoordinatedDrawingAreaProxy* drawingArea = static_cast<CoordinatedDrawingAreaProxy*>(webPage().drawingArea());
        drawingArea->requestCoordinatedGraphicsStateAfterReset();
        return;
    }

    setActive(inWindow);
    m_paintingDisabled = !inWindow;
}

void SWKView::nativeSetVisible(bool visible)
{
    pageClient().setVisible(visible);
}

void SWKView::nativeSetFocus(bool focus)
{
    pageClient().setFocused(focus);
}

void SWKView::nativeLayoutChanged(int32_t width, int32_t height)
{
    IntRect layoutRect(0, 0, width, height);
    pageClient().windowAndViewFramesChanged(layoutRect, FloatPoint());
    pageClient().setSize(layoutRect.size());
    FloatSize viewportSize = layoutRect.size();
    viewportSize.scale(1 / getIntrinsicDeviceScaleFactor());

    m_pageViewportController.didChangeViewportSize(roundedIntSize(viewportSize));
}

void SWKView::nativeDisplayLocationChanged(int32_t, int32_t)
{
    pageClient().windowAndViewFramesChanged(IntRect(IntPoint(), pageClient().size()), FloatPoint());
}

void SWKView::onPause()
{
    setActive(false);
}

void SWKView::onResume()
{
    setActive(true);
}

void SWKView::enqueuePaintingThreadTask(std::function<void ()> task)
{
    MutexLocker lock(m_paintingThreadMutex);

    m_paintingThreadTasks.append(WTFMove(task));
    m_hasPaintingThreadTasks = true;
}

void SWKView::performPaintingThreadTasks()
{
    Vector<std::function<void ()>> paintingThreadTasks;

    {
        MutexLocker lock(m_paintingThreadMutex);
        WTF::swap(paintingThreadTasks, m_paintingThreadTasks);
        m_hasPaintingThreadTasks = false;
    }

    for (auto& paintingThreadTask : paintingThreadTasks)
        paintingThreadTask();
}

inline WebPageProxy& SWKView::webPage() const
{
    return m_webContent.webPage();
}

inline PageClientSling& SWKView::pageClient()
{
    return m_webContent.pageClient();
}

const PageClientSling& SWKView::pageClient() const
{
    return m_webContent.pageClient();
}

namespace Natives {

SWKView* SWKView::nativeCreate(Native::PassLocalRef<Natives::SWKWebContent> webContent)
{
    return new ::WebKit::SWKView(*webContent.as<::WebKit::SWKWebContent>());
}

} // namespace Natives
} // namespace WebKit
