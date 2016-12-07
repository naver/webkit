/*
 * Copyright (C) 2013-2015 Naver Corp. All rights reserved.
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
#include "PageClientSling.h"

#include "APIPageConfiguration.h"
#include "CoordinatedDrawingAreaProxy.h"
#include "CoordinatedGraphicsScene.h"
#include "SWKWebContentNatives.h"
#include "CoordinatedLayerTreeHostProxy.h"
#include "NotImplemented.h"
#include "ViewState.h"
#include "WebBackForwardList.h"
#include "WebBackForwardListItem.h"
#include "WebContextMenuProxy.h"
#include "WebPageProxy.h"
#include "WebProcessPool.h"

#if ENABLE(CONTEXT_MENUS)
#include "WebContextMenuProxySling.h"
#endif

using namespace WebCore;

namespace WebKit {

PageClientSling::PageClientSling(SWKWebContent& webContent)
    : m_webContent(webContent)
    , m_scrollableLayer(nullptr)
    , m_focused(false)
    , m_visible(false)
#if ENABLE(FULLSCREEN_API)
    , m_hasRequestedFullScreen(false)
#endif
    , m_opacity(1.0)
{
    Ref<API::PageConfiguration> pageConfiguration = webContent.getConfiguration().as<WebKit::SWKWebContentConfiguration>()->pageConfiguration();
    WebProcessPool* context = pageConfiguration->processPool();
    m_page = context->createWebPage(*this, WTFMove(pageConfiguration));

    m_page->pageGroup().preferences().setAcceleratedCompositingEnabled(true);
    m_page->pageGroup().preferences().setForceCompositingMode(true);
    m_page->initializeWebPage(); // FIXME: initialization should be done before setting preferences.

    char* debugVisualsEnvironment = getenv("WEBKIT_SHOW_COMPOSITING_DEBUG_VISUALS");
    bool showDebugVisuals = debugVisualsEnvironment && !strcmp(debugVisualsEnvironment, "1");
    m_page->pageGroup().preferences().setCompositingBordersVisible(showDebugVisuals);
    m_page->pageGroup().preferences().setCompositingRepaintCountersVisible(showDebugVisuals);
}

PageClientSling::~PageClientSling()
{
    if (m_page->isClosed())
        return;

    m_page->close();
}

CoordinatedGraphicsScene* PageClientSling::coordinatedGraphicsScene()
{
    if (CoordinatedDrawingAreaProxy* drawingArea = static_cast<CoordinatedDrawingAreaProxy*>(page()->drawingArea()))
        return drawingArea->coordinatedLayerTreeHostProxy().coordinatedGraphicsScene();

    return nullptr;
}

void PageClientSling::setSize(const WebCore::IntSize& size)
{
    if (m_size == size)
        return;

    m_size = size;

    updateViewportSize();
}

bool PageClientSling::isActive()
{
    // FIXME: WebPageProxy() update status.
    if (!m_page)
        return nullptr;

    CoordinatedGraphicsScene* scene = coordinatedGraphicsScene();
    if (!scene)
        return false;

    return scene->isActive();
}

void PageClientSling::setActive(bool active)
{
    CoordinatedGraphicsScene* scene = coordinatedGraphicsScene();
    if (!scene || scene->isActive() == active)
        return;

    scene->setActive(active);
    m_page->viewStateDidChange(ViewState::WindowIsActive);
}

void PageClientSling::setFocused(bool focused)
{
    if (m_focused == focused)
        return;

    m_focused = focused;
    m_page->viewStateDidChange(ViewState::IsFocused | ViewState::WindowIsActive);
}

void PageClientSling::setVisible(bool visible)
{
    if (m_visible == visible)
        return;

    m_visible = visible;
    m_page->viewStateDidChange(ViewState::IsVisible);

    if (CoordinatedDrawingAreaProxy* drawingArea = static_cast<CoordinatedDrawingAreaProxy*>(page()->drawingArea()))
        drawingArea->visibilityDidChange();
}

void PageClientSling::setContentScaleFactor(float scaleFactor)
{
    m_page->scalePage(scaleFactor, roundedIntPoint(contentPosition()));
    updateViewportSize();
}

void PageClientSling::setUserViewportTranslation(double tx, double ty)
{
    m_userViewportTransform = TransformationMatrix().translate(tx, ty);
}

IntPoint PageClientSling::userViewportToContents(const IntPoint& point) const
{
    return transformFromScene().mapPoint(point);
}

IntPoint PageClientSling::userViewportToScene(const WebCore::IntPoint& point) const
{
    return m_userViewportTransform.mapPoint(point);
}

IntPoint PageClientSling::contentsToUserViewport(const IntPoint& point) const
{
    return transformToScene().mapPoint(point);
}

void PageClientSling::paintToCurrentGLContext()
{
    CoordinatedGraphicsScene* scene = coordinatedGraphicsScene();
    if (!scene)
        return;

    const FloatRect& viewport = m_userViewportTransform.mapRect(IntRect(IntPoint(), m_size));

    scene->paintToCurrentGLContext(transformToScene().toTransformationMatrix(), m_opacity, viewport, m_page->pageExtendedBackgroundColor(), m_page->drawsBackground(), m_contentPosition);
}

void PageClientSling::setDrawsBackground(bool drawsBackground)
{
    m_page->setDrawsBackground(drawsBackground);
}

bool PageClientSling::drawsBackground() const
{
    return m_page->drawsBackground();
}

void PageClientSling::suspendActiveDOMObjectsAndAnimations()
{
    m_page->suspendActiveDOMObjectsAndAnimations();
}

void PageClientSling::resumeActiveDOMObjectsAndAnimations()
{
    m_page->resumeActiveDOMObjectsAndAnimations();
}

#if ENABLE(FULLSCREEN_API)
bool PageClientSling::requestExitFullScreen()
{
    if (!isFullScreen())
        return false;

    m_page->fullScreenManager()->requestExitFullScreen();
    return true;
}
#endif

#if USE(COORDINATED_GRAPHICS_MULTIPROCESS)
void PageClientSling::findZoomableAreaForPoint(const IntPoint& point, const IntSize& size)
{
    m_page->findZoomableAreaForPoint(transformFromScene().mapPoint(point), transformFromScene().mapSize(size));
}
#endif

WebCore::FloatSize PageClientSling::visibleContentsSize() const
{
    FloatSize visibleContentsSize(dipSize());
    if (m_page->useFixedLayout())
        visibleContentsSize.scale(1 / contentScaleFactor());

    return visibleContentsSize;
}

AffineTransform PageClientSling::transformFromScene() const
{
    Optional<AffineTransform> transform = transformToScene().inverse();
    return transform ? *transform : AffineTransform();
}

AffineTransform PageClientSling::transformToScene() const
{
    FloatPoint position = -m_contentPosition;
    float effectiveScale = m_page->deviceScaleFactor();
    if (m_page->useFixedLayout())
        effectiveScale *= contentScaleFactor();
    position.scale(effectiveScale, effectiveScale);

    TransformationMatrix transform = m_userViewportTransform;
    transform.translate(position.x(), position.y());
    transform.scale(effectiveScale);

    return transform.toAffineTransform();
}

void PageClientSling::scrollBegin(const FloatPoint& devicePoint)
{
    CoordinatedGraphicsScene* scene = coordinatedGraphicsScene();
    if (!scene)
        return;

    m_remainedScrollDelta = FloatSize();
    m_scrollableLayer = scene->findScrollableContentsLayerAt(devicePoint);
}

// FIXME: It's required until we fixed wrong position of fixed element.
IntSize PageClientSling::adjustDelta(const FloatSize& deviceDelta)
{
    FloatSize scrollDelta = deviceDelta + m_remainedScrollDelta;
    IntSize flooredDelta = flooredIntSize(scrollDelta);

    m_remainedScrollDelta = scrollDelta - flooredDelta;

    return flooredDelta;
}

bool PageClientSling::scrollBy(const FloatSize& deviceDelta, bool isOverScrollAllowed)
{
    if (m_scrollableLayer) {
        m_scrollableLayer->scrollBy(deviceDelta);
        if (!isOverScrollAllowed)
            return false;
    }

    float effectiveScale = m_page->deviceScaleFactor();
    effectiveScale *= contentScaleFactor();

    FloatSize cssDelta = deviceDelta;
    cssDelta.scale(1 / effectiveScale);
    cssDelta = adjustDelta(cssDelta);

    // bound content position
    FloatPoint newContentPosition;
    newContentPosition.setX(clampTo(m_contentPosition.x() + cssDelta.width(), 0.f, m_contentsSize.width() - floorf(m_size.width() / effectiveScale)));
    newContentPosition.setY(clampTo(m_contentPosition.y() + cssDelta.height(), 0.f, m_contentsSize.height() - floorf(m_size.height() / effectiveScale)));

    if (newContentPosition == m_contentPosition)
        return false;

    setContentPosition(newContentPosition);
    return true;
}

void PageClientSling::scrollEnd()
{
    m_scrollableLayer = nullptr;
}

void PageClientSling::windowAndViewFramesChanged(const FloatRect& viewFrameInWindowCoordinates, const FloatPoint& accessibilityViewCoordinates)
{
    notImplemented();
}

inline ViewController& PageClientSling::view()
{
    return m_webContent.view();
}

void PageClientSling::updateViewportSize()
{
    if (CoordinatedDrawingAreaProxy* drawingArea = static_cast<CoordinatedDrawingAreaProxy*>(page()->drawingArea())) {
        // Web Process expects sizes in UI units, and not raw device units.
        drawingArea->setSize(roundedIntSize(dipSize()), IntSize(), IntSize());
        FloatRect visibleContentsRect(contentPosition(), visibleContentsSize());
        visibleContentsRect.intersect(FloatRect(FloatPoint(), contentsSize()));
        drawingArea->setVisibleContentsRect(visibleContentsRect, FloatPoint());
    }
}

inline WebCore::FloatSize PageClientSling::dipSize() const
{
    FloatSize dipSize(size());
    dipSize.scale(1 / m_page->deviceScaleFactor());

    return dipSize;
}

std::unique_ptr<DrawingAreaProxy> PageClientSling::createDrawingAreaProxy()
{
    return std::make_unique<CoordinatedDrawingAreaProxy>(*m_page);
}

void PageClientSling::setViewResumePainting()
{
    view().setViewResumePainting();
}

void PageClientSling::setViewNeedsDisplay(const WebCore::Region& area)
{
    m_webContent.view().setViewNeedsDisplay(area.bounds());
}

void PageClientSling::requestScroll(const WebCore::FloatPoint&, const WebCore::IntPoint&, bool)
{
    notImplemented();
}

WebCore::IntSize PageClientSling::viewSize()
{
    return roundedIntSize(dipSize());
}

bool PageClientSling::isViewWindowActive()
{
    return isActive();
}

bool PageClientSling::isViewFocused()
{
    return isFocused();
}

bool PageClientSling::isViewVisible()
{
    return isActive() && isVisible();
}

bool PageClientSling::isViewInWindow()
{
    notImplemented();
    return true;
}

void PageClientSling::processDidExit()
{
    m_webContent.view().webProcessCrashed(m_page->backForwardList().currentItem() ? m_page->backForwardList().currentItem()->url() : "");
}

void PageClientSling::didRelaunchProcess()
{
    m_webContent.view().webProcessDidRelaunch();
}

void PageClientSling::pageClosed()
{
    notImplemented();
}

void PageClientSling::preferencesDidChange()
{
    notImplemented();
}

void PageClientSling::toolTipChanged(const String&, const String& newToolTip)
{
    m_webContent.view().didChangeTooltip(newToolTip);
}

void PageClientSling::didCommitLoadForMainFrame(const String&, bool)
{
    setContentPosition(WebCore::FloatPoint());
    m_contentsSize = IntSize();
    view().didCommitLoad();
}

#if USE(COORDINATED_GRAPHICS_MULTIPROCESS)
void PageClientSling::pageDidRequestScroll(const IntPoint& position)
{
    FloatPoint uiPosition(position);
    setContentPosition(uiPosition);

    m_webContent.view().didChangeContentsPosition(position);
}

void PageClientSling::didRenderFrame(const WebCore::IntSize& contentsSize, const WebCore::IntRect& coveredRect)
{
    m_webContent.view().didRenderFrame(contentsSize, coveredRect);
}

void PageClientSling::pageTransitionViewportReady()
{
    m_webContent.view().didCompletePageTransition();
}
#endif

void PageClientSling::updateTextInputState()
{
    view().editorStateChanged();
}

void PageClientSling::handleDownloadRequest(DownloadProxy* download)
{
    m_webContent.handleDownloadRequest(download);
}

void PageClientSling::didChangeContentSize(const WebCore::IntSize& size)
{
    if (m_contentsSize == size)
        return;

    m_contentsSize = size;
    m_webContent.view().didChangeContentsSize(size);

    updateViewportSize();
}

void PageClientSling::setCursor(const Cursor& cursor)
{
    view().setCursor(cursor);
}

void PageClientSling::setCursorHiddenUntilMouseMoves(bool)
{
    notImplemented();
}

void PageClientSling::didChangeViewportProperties(const WebCore::ViewportAttributes& attr)
{
    m_webContent.view().didChangeViewportAttributes(attr);
}

void PageClientSling::registerEditCommand(PassRefPtr<WebEditCommandProxy> command, WebPageProxy::UndoOrRedo undoOrRedo)
{
    m_undoController.registerEditCommand(command, undoOrRedo);
}

void PageClientSling::clearAllEditCommands()
{
    m_undoController.clearAllEditCommands();
}

bool PageClientSling::canUndoRedo(WebPageProxy::UndoOrRedo undoOrRedo)
{
    return m_undoController.canUndoRedo(undoOrRedo);
}

void PageClientSling::executeUndoRedo(WebPageProxy::UndoOrRedo undoOrRedo)
{
    m_undoController.executeUndoRedo(undoOrRedo);
}

void PageClientSling::wheelEventWasNotHandledByWebCore(const NativeWebWheelEvent&)
{
}

bool PageClientSling::isSpeaking()
{
    return view().isSpeaking();
}

void PageClientSling::speak(const String& string)
{
    view().speak(string);
}

void PageClientSling::stopSpeaking()
{
    view().stopSpeaking();
}

FloatRect PageClientSling::convertToDeviceSpace(const FloatRect& userRect)
{
    if (m_page->useFixedLayout()) {
        FloatRect result = userRect;
        result.scale(m_page->deviceScaleFactor());
        return result;
    }
    // Legacy mode.
    notImplemented();
    return userRect;
}

FloatRect PageClientSling::convertToUserSpace(const FloatRect& deviceRect)
{
    if (m_page->useFixedLayout()) {
        FloatRect result = deviceRect;
        result.scale(1 / m_page->deviceScaleFactor());
        return result;
    }
    // Legacy mode.
    notImplemented();
    return deviceRect;
}

IntPoint PageClientSling::screenToRootView(const IntPoint& point)
{
    notImplemented();
    return point;
}

IntRect PageClientSling::rootViewToScreen(const IntRect&)
{
    notImplemented();
    return IntRect();
}

void PageClientSling::doneWithKeyEvent(const NativeWebKeyboardEvent& event, bool wasEventHandled)
{
    view().doneWithKeyEvent(event, wasEventHandled);
}

#if ENABLE(TOUCH_EVENTS)
void PageClientSling::doneWithTouchEvent(const NativeWebTouchEvent& event, bool wasEventHandled)
{
    m_webContent.view().doneWithTouchEvent(wasEventHandled);
}
#endif

RefPtr<WebPopupMenuProxy> PageClientSling::createPopupMenuProxy(WebPageProxy& page)
{
    return view().createPopupMenuProxy(page);
}

#if ENABLE(CONTEXT_MENUS)
std::unique_ptr<WebContextMenuProxy> PageClientSling::createContextMenuProxy(WebPageProxy& page, const ContextMenuContextData& contextMenuContextData, const UserData& userData)
{
    return view().createContextMenuProxy(page, contextMenuContextData, userData);
}
#endif

#if ENABLE(INPUT_TYPE_COLOR)
RefPtr<WebColorPicker> PageClientSling::createColorPicker(WebPageProxy*, const WebCore::Color&, const WebCore::IntRect&)
{
    notImplemented();
    return nullptr;
}
#endif

void PageClientSling::enterAcceleratedCompositingMode(const LayerTreeContext&)
{
    setActive(true);
}

void PageClientSling::exitAcceleratedCompositingMode()
{
    setActive(false);
}

void PageClientSling::updateAcceleratedCompositingMode(const LayerTreeContext&)
{
    notImplemented();
}

#if ENABLE(FULLSCREEN_API)
WebFullScreenManagerProxyClient& PageClientSling::fullScreenManagerProxyClient()
{
    return *this;
}

void PageClientSling::closeFullScreenManager()
{
}

bool PageClientSling::isFullScreen()
{
    return m_hasRequestedFullScreen;
}

void PageClientSling::enterFullScreen()
{
    if (m_hasRequestedFullScreen)
        return;

    WebFullScreenManagerProxy* manager = m_page->fullScreenManager();
    if (!manager)
        return;

    m_hasRequestedFullScreen = true;

    manager->willEnterFullScreen();
    view().enterFullScreen();
    manager->didEnterFullScreen();
}

void PageClientSling::exitFullScreen()
{
    if (!m_hasRequestedFullScreen)
        return;

    WebFullScreenManagerProxy* manager = m_page->fullScreenManager();
    if (!manager)
        return;

    m_hasRequestedFullScreen = false;

    manager->willExitFullScreen();
    view().exitFullScreen();
    manager->didExitFullScreen();
}

void PageClientSling::beganEnterFullScreen(const IntRect&, const IntRect&)
{
    notImplemented();
}

void PageClientSling::beganExitFullScreen(const IntRect&, const IntRect&)
{
    notImplemented();
}
#endif

void PageClientSling::didFinishLoadingDataForCustomContentProvider(const String& suggestedFilename, const IPC::DataReference&)
{
    notImplemented();
}

void PageClientSling::didFirstVisuallyNonEmptyLayoutForMainFrame()
{
    notImplemented();
}

void PageClientSling::didFinishLoadForMainFrame()
{
    notImplemented();
}

void PageClientSling::didSameDocumentNavigationForMainFrame(SameDocumentNavigationType)
{
    notImplemented();
}

void PageClientSling::didRestoreScrollPosition()
{
    notImplemented();
}

WebCore::UserInterfaceLayoutDirection PageClientSling::userInterfaceLayoutDirection()
{
    notImplemented();
    return WebCore::UserInterfaceLayoutDirection::LTR;
}

void PageClientSling::refView()
{
    notImplemented();
}

void PageClientSling::derefView()
{
    notImplemented();
}

}
