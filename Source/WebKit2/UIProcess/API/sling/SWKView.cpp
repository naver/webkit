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
#include "SWKView.h"

#include "SWKWebContent.h"
#include "WebBitmap.h"
#include "WebEditable.h"
#include "WebRenderer.h"

#include <util/CompilerMacros.h>
#include <util/StringConversion.h>
#include <view/Configuration.h>
#include <view/ContentView.h>
#include <view/Cursor.h>
#include <view/DisplayMetrics.h>
#include <view/UIEvent.h>
#include <view/ViewHostWindow.h>

namespace webkit {

std::shared_ptr<SWKView> SWKView::create(std::shared_ptr<SWKWebContent> webContent)
{
    return WebKit::Managed::SWKView::create<SWKView>(webContent);
}

SWKView::SWKView()
    : m_view(nullptr)
    , m_width(0)
    , m_height(0)
    , m_contentWidth(0)
    , m_contentHeight(0)
    , m_minimumScale(0.5f)
    , m_maximumScale(4.0f)
    , m_viewportX(0.0f)
    , m_viewportY(0.0f)
    , m_disableMotionDetection(false)
    , m_enableMouseTouchEvents(false)
    , m_hasInputMethod(false)
{
}

SWKView::~SWKView()
{
}

std::shared_ptr<view::ContentFrame> SWKView::displayInPopupWindow(const view::Rect& clientRect)
{
    return view::ContentFrame::createPopup(clientRect);
}

void SWKView::closePopupWindow()
{
    m_view->hostWindow()->closePopupWindow();
}

void SWKView::setOnCloseListener(std::shared_ptr<Managed::CompletionHandler> listener)
{
    m_closeListener = listener;
}

void SWKView::onAttachedToView(view::ContentView& view)
{
    assert(!m_view);

    m_view = &view;

    setIntrinsicDeviceScaleFactor(view.deviceScaleFactor());
    nativeSetInWindow(true);
}

void SWKView::onDetachedFromView()
{
    assert(m_view);

    m_view = nullptr;

    nativeSetInWindow(false);

    if (m_closeListener)
        m_closeListener->invoke();
}

void SWKView::onVisibilityChanged(bool visible)
{
    nativeSetVisible(visible);
}

void SWKView::onFocusChanged(bool focus)
{
    nativeSetFocus(focus);
}

void SWKView::onLayout(int32_t width, int32_t height)
{
    if (width == m_width && height == m_height)
        return;

    m_width = width;
    m_height = height;

    nativeLayoutChanged(m_width, m_height);
}

void SWKView::onDisplayLocation(int32_t x, int32_t y)
{
    nativeDisplayLocationChanged(x, y);
}

void SWKView::onConfigurationChanged(const view::Configuration& config)
{
    if (config.densityDpi != view::Configuration::DENSITY_DPI_UNDEFINED)
        setIntrinsicDeviceScaleFactor(1.0f * config.densityDpi / view::DisplayMetrics::DENSITY_DEFAULT);
}

void SWKView::setMotionDetectionDisabled(bool disable)
{
    if (disable == m_disableMotionDetection || !m_view)
        return;

    m_disableMotionDetection = disable;

    m_view->motionSettingsChanged();
}

bool SWKView::getMotionDetectionDisabled() const
{
    return m_disableMotionDetection;
}

void SWKView::setMouseTouchEventsEnabled(bool enable)
{
    if (enable == m_enableMouseTouchEvents || !m_view)
        return;

    m_enableMouseTouchEvents = enable;

    m_view->motionSettingsChanged();
}

bool SWKView::getMouseTouchEventsEnabled() const
{
    return m_enableMouseTouchEvents;
}

view::MotionDetector::Settings SWKView::getMotionSettings() const
{
    view::MotionDetector::Settings settings;
    settings.flags.disableDetection = getMotionDetectionDisabled();
    settings.flags.canHandlePinchBy = true;
    settings.flags.mouseTouchEvents = getMouseTouchEventsEnabled();
    return settings;
}

bool SWKView::sendGenericEvent(const view::UIEvent& event)
{
    switch (event.source()) {
    case view::UIEvent::Source::Mouse: {
        if (event.action() == view::UIEvent::Action::Enter)
            return false;
        const view::UIEvent::Pointer& pointer = event.pointers()[0];
        sendMouseEvent(event.timestamp().count(), static_cast<int32_t>(event.action()), event.modifiers().value,
            pointer.coord.x, pointer.coord.y, pointer.globalCoord.x, pointer.globalCoord.y, event.repeatCount());
        return true;
    }
    case view::UIEvent::Source::Wheel: {
        const view::UIEvent::Pointer& pointer = event.pointers()[0];
        sendWheelEvent(event.timestamp().count(), static_cast<int32_t>(event.action()), event.modifiers().value, 0.0f, pointer.magnitude,
            pointer.coord.x, pointer.coord.y, pointer.globalCoord.x, pointer.globalCoord.y);
        return true;
    }
    case view::UIEvent::Source::Touch: {
        const view::UIEvent::Pointer& pointer = event.pointers()[0];
        sendTouchEvent(event.timestamp().count(), static_cast<int32_t>(event.action()), event.modifiers().value,
            pointer.coord.x, pointer.coord.y, pointer.globalCoord.x, pointer.globalCoord.y, pointer.id);
        return true;
    }
    case view::UIEvent::Source::Key: {
        const view::UIEvent::KeyState& keyState = event.keyState();
        std::string text = std::ws2s(std::wstring(&keyState.unicodeCharacter, 1));
        sendKeyEvent(event.timestamp().count(), static_cast<int32_t>(event.action()), event.modifiers().value,
            keyState.virtualKeyCode, keyState.nativeKeyCode, text, text,
            keyState.isAutoRepeat, keyState.isSystemKey, keyState.isKeypadKey,
            keyState.strokeHash);
        return true;
    }
    default:
        break;
    }
    return false;
}

int32_t SWKView::getWidth()
{
    return m_width;
}

int32_t SWKView::getHeight()
{
    return m_height;
}

int32_t SWKView::getContentWidth() const
{
    return m_contentWidth;
}

int32_t SWKView::getContentHeight() const
{
    return m_contentHeight;
}

float SWKView::getScale()
{
    return getPageScaleFactor();
}

float SWKView::getMinimumScale() const
{
    return m_minimumScale;
}

float SWKView::getMaximumScale() const
{
    return m_maximumScale;
}

void SWKView::pinchTo(const view::RectF& rect)
{
    // TODO: Pinch to zoom using new viewport coordinates(Not used).
}

void SWKView::pinchBy(float x, float y, float deltaScale)
{
    adjustTransientZoom(x, y, deltaScale);
}

void SWKView::pinchEnd()
{
    commitTransientZoom();
}

view::RectF SWKView::getViewport()
{
    float viewportWidth = screenToContents(m_width);
    float viewportHeight = screenToContents(m_height);
    return view::RectF(m_viewportX, m_viewportX + viewportWidth, m_viewportY,
            m_viewportY + viewportHeight);
}

void SWKView::invalidate()
{
}

void SWKView::invalidate(const view::Rect& rect)
{
}

void SWKView::didChangeContentsPosition(int32_t cssX, int32_t cssY)
{
}

void SWKView::didChangeContentsSize(int32_t width, int32_t height)
{
    m_contentWidth = width;
    m_contentHeight = height;
}

void SWKView::didChangeViewportAttributes(float minimumScale, float maximumScale, float scale)
{
    m_minimumScale = minimumScale;
    m_maximumScale = maximumScale;

    // FIXME : x, y arguments should be calculated correctly. Refer to ViewGestureController.mm endMagnificationGesture().
    setPageScaleFactor(scale, 0, 0);
}

void SWKView::setViewNeedsDisplay(int32_t x, int32_t y, int32_t width, int32_t height)
{
    if (UNLIKELY(!m_view))
        return;

    m_view->contentInvalidated();
}

void SWKView::hasTouchEventHandlers(bool hasTouchHandlers)
{
}

void SWKView::doneWithTouchEvent(bool wasEventHandled)
{
}

void SWKView::didChangeCursor(int32_t cursorType)
{
    if (!m_view)
        return;

    m_view->setCursor(view::Cursor::systemCursor(static_cast<view::Cursor::Type>(cursorType)));
}

void SWKView::didChangeCursor(int32_t hotSpotX, int32_t hotSpotY, std::shared_ptr<Managed::WebBitmap> cursorImage)
{
    if (!m_view)
        return;

    m_view->setCursor(view::Cursor::create(view::Point(hotSpotX, hotSpotY), std::static_pointer_cast<webkit::WebBitmap>(cursorImage)->getBitmap()));
}

void SWKView::didChangeTooltip(const std::string& tooltip)
{
}

void SWKView::startInputMethod(bool isInPasswordField)
{
    if (m_hasInputMethod || !m_view)
        return;

    m_hasInputMethod = m_view->startInputMethod(!isInPasswordField);
}

void SWKView::endInputMethod()
{
    if (!m_hasInputMethod || !m_view)
        return;

    m_hasInputMethod = false;

    m_view->endInputMethod();
}

void SWKView::editorStateChanged(const std::string&, int32_t, int32_t, int32_t, int32_t)
{
}

void SWKView::enterFullScreen()
{
}

void SWKView::exitFullScreen()
{
}

void SWKView::didPerformDragControllerAction(int64_t dragOperation, bool mouseIsOverFileInput, int32_t numberOfItemsToBeAccepted)
{
}

void SWKView::setDragImage(int32_t x, int32_t y, std::shared_ptr<Managed::WebBitmap> dragImage, bool isLinkDrag)
{
}

void SWKView::setPromisedData(const std::string& pasteboardName, const std::vector<int8_t>& imageBuffer, const std::string& filename,
    const std::string& extension, const std::string& title, const std::string& url, const std::string& visibleUrl)
{
}

bool SWKView::isSpeaking()
{
    return false;
}

void SWKView::speak(const std::string& string)
{
}

void SWKView::stopSpeaking()
{
}

void SWKView::webProcessCrashed(const std::string& url)
{
    setViewNeedsDisplay(0, 0, m_width, m_height);
}

float SWKView::getEffectiveScale()
{
    return getPageScaleFactor() * getIntrinsicDeviceScaleFactor(); 
}

int64_t SWKView::nativeWindowHandle()
{
    if (!m_view)
        return 0;

    // FIXME: This doesn't seem good.
    return reinterpret_cast<int64_t>(m_view->hostWindow()->windowHandle());
}

} // namespace webkit

namespace WebKit {
namespace Managed {

static webkit::SWKView& view(SWKView* v)
{
    return *static_cast<webkit::SWKView*>(v);
}

void SWKView::INIT(std::shared_ptr<Managed::SWKWebContent> webContent)
{
    view(this).m_webContent = std::static_pointer_cast<webkit::SWKWebContent>(webContent);
    view(this).nativeCreate(webContent);
}

}
} // namespace WebKit
