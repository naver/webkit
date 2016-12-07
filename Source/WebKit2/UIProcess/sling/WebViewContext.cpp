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
#include "WebViewContext.h"

#include "SWKView.h"
#include "WebEditableContext.h"
#include "WebRenderContext.h"

namespace webkit {

std::shared_ptr<WebViewContext> WebViewContext::create(std::shared_ptr<SWKView> view)
{
    return std::shared_ptr<WebViewContext>(new WebViewContext(view));
}

WebViewContext::WebViewContext(std::shared_ptr<SWKView> view)
    : m_view(view)
{
}

WebViewContext::~WebViewContext()
{
}

void WebViewContext::attached(view::ContentView& view)
{
    m_view->onAttachedToView(view);
}

void WebViewContext::detached()
{
    m_view->onDetachedFromView();
}

void WebViewContext::setVisible(bool visible)
{
    m_view->onVisibilityChanged(visible);
}

void WebViewContext::setFocus(bool focus)
{
    m_view->onFocusChanged(focus);
}

void WebViewContext::setActive(bool active)
{
    m_view->setActive(active);
}

bool WebViewContext::isVisible()
{
    return m_view->isVisible();
}

bool WebViewContext::isFocused()
{
    return m_view->isFocused();
}

bool WebViewContext::isActive()
{
    return m_view->isActive();
}

void WebViewContext::layout(int32_t width, int32_t height)
{
    m_view->onLayout(width, height);
}

void WebViewContext::displayLocation(int32_t x, int32_t y)
{
    m_view->onDisplayLocation(x, y);
}

void WebViewContext::onConfigurationChanged(const view::Configuration& config)
{
    m_view->onConfigurationChanged(config);
}

void WebViewContext::pause()
{
    m_view->onPause();
}

void WebViewContext::resume()
{
    m_view->onResume();
}

view::MotionDetector::Settings WebViewContext::motionSettings() const
{
    return m_view->getMotionSettings();
}

void WebViewContext::sendSingleTap(float x, float y)
{
    m_view->sendSingleTap(x, y);
}

void WebViewContext::sendDoubleTap(float x, float y)
{
    m_view->sendDoubleTap(x, y);
}

bool WebViewContext::sendGenericEvent(const view::UIEvent& event)
{
    return m_view->sendGenericEvent(event);
}

std::shared_ptr<view::EditableContext> WebViewContext::editable()
{
    return WebEditableContext::create(m_view);
}

int32_t WebViewContext::width() const
{
    return m_view->getWidth();
}

int32_t WebViewContext::height() const
{
    return m_view->getHeight();
}

int32_t WebViewContext::contentWidth() const
{
    return m_view->getContentWidth();
}

int32_t WebViewContext::contentHeight() const
{
    return m_view->getContentHeight();
}

float WebViewContext::currentScale() const
{
    return m_view->getScale();
}

float WebViewContext::minimumScale() const
{
    return m_view->getMinimumScale();
}

float WebViewContext::maximumScale() const
{
    return m_view->getMaximumScale();
}

void WebViewContext::scrollBegin(float x, float y)
{
    return m_view->scrollBegin(x, y);
}

bool WebViewContext::scrollBy(float deltaX, float deltaY)
{
    return m_view->scrollBy(deltaX, deltaY, true);
}

bool WebViewContext::scrollTo(float x, float y)
{
    return false;
}

void WebViewContext::scrollEnd(float x, float y)
{
    return m_view->scrollEnd(x, y);
}

void WebViewContext::pinchBegin(float x, float y)
{
    m_view->pinchBegin(x, y);
}

void WebViewContext::pinchTo(const view::RectF& rect)
{
    m_view->pinchTo(rect);
}

void WebViewContext::pinchBy(float x, float y, float deltaScale)
{
    m_view->pinchBy(x, y, deltaScale);
}

void WebViewContext::pinchEnd()
{
    m_view->pinchEnd();
}

view::RectF WebViewContext::viewport() const
{
    return m_view->getViewport();
}

void WebViewContext::invalidate()
{
    m_view->invalidate();
}

void WebViewContext::invalidate(const view::Rect& rect)
{
    m_view->invalidate(rect);
}

std::shared_ptr<view::RenderContext> WebViewContext::renderer()
{
    if (!m_renderer)
        m_renderer = WebRenderContext::create(m_view);

    return m_renderer;
}

} // namespace webkit
