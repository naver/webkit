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

#ifndef WebViewContext_h
#define WebViewContext_h

#include <view/MotionDetector.h>
#include <view/ViewContext.h>

namespace webkit {

class SWKView;

class WEBKIT_EXPORT WebViewContext : public view::ViewContext {
public:
    static std::shared_ptr<WebViewContext> create(std::shared_ptr<SWKView>);
    ~WebViewContext();

private:
    void attached(view::ContentView&) override;
    void detached() override;

    void setVisible(bool) override;
    void setFocus(bool) override;
    void setActive(bool) override;
    bool isVisible() override;
    bool isFocused() override;
    bool isActive() override;

    void layout(int32_t, int32_t) override;
    void displayLocation(int32_t, int32_t) override;
    void onConfigurationChanged(const view::Configuration&) override;

    void pause() override;
    void resume() override;

    view::MotionDetector::Settings motionSettings() const override;

    void sendSingleTap(float x, float y) override;
    void sendDoubleTap(float x, float y) override;

    bool sendGenericEvent(const view::UIEvent&) override;

    std::shared_ptr<view::EditableContext> editable() override;

    int32_t width() const override;
    int32_t height() const override;

    int32_t contentWidth() const override;
    int32_t contentHeight() const override;

    float currentScale() const override;
    float minimumScale() const override;
    float maximumScale() const override;
    
    void scrollBegin(float x, float y) override;
    bool scrollBy(float deltaX, float deltaY) override;
    bool scrollTo(float x, float y) override;
    void scrollEnd(float x, float y) override;

    void pinchBegin(float x, float y) override;
    void pinchTo(const view::RectF& rect) override;
    void pinchBy(float x, float y, float deltaScale) override;
    void pinchEnd() override;

    view::RectF viewport() const override;

    void invalidate() override;
    void invalidate(const view::Rect&) override;

    std::shared_ptr<view::RenderContext> renderer() override;

private:
    WebViewContext(std::shared_ptr<SWKView>);

    std::shared_ptr<SWKView> m_view;
    std::shared_ptr<view::RenderContext> m_renderer;
};

}

#endif
