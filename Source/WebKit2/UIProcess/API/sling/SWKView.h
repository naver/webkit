/*
 * Copyright (C) 2015 Naver Corp. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    virtual notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    virtual notice, this list of conditions and the following disclaimer in the
 *    virtual documentation and/or other materials provided with the distribution.
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

#ifndef SWKView_h
#define SWKView_h

#include "SWKViewManagedBase.h"

#include "CompletionHandler.h"
#include <view/ContentFrame.h>
#include <view/ViewContext.h>

namespace webkit {

namespace Managed = WebKit::Managed;

class SWKWebContent;
class WebEditable;
class WebRenderer;

class WEBKIT_EXPORT SWKView : public WebKit::Managed::SWKView {
    friend class WebKit::Managed::SWKView;
public:
    static std::shared_ptr<SWKView> create(std::shared_ptr<SWKWebContent>);
    virtual ~SWKView();

    view::ContentView* getContentView() { return m_view; }
    std::shared_ptr<view::ContentFrame> displayInPopupWindow(const view::Rect&);
    void closePopupWindow();
    void setOnCloseListener(std::shared_ptr<Managed::CompletionHandler>);

    virtual void onAttachedToView(view::ContentView&);
    virtual void onDetachedFromView();

    virtual void onVisibilityChanged(bool);
    virtual void onFocusChanged(bool);

    virtual void onLayout(int32_t, int32_t);
    virtual void onDisplayLocation(int32_t, int32_t);

    virtual void onConfigurationChanged(const view::Configuration&);

    virtual void setMotionDetectionDisabled(bool);
    virtual bool getMotionDetectionDisabled() const;

    virtual void setMouseTouchEventsEnabled(bool);
    virtual bool getMouseTouchEventsEnabled() const;

    virtual view::MotionDetector::Settings getMotionSettings() const;

    virtual bool sendGenericEvent(const view::UIEvent&);

    virtual int32_t getWidth() override;
    virtual int32_t getHeight() override;

    virtual int32_t getContentWidth() const;
    virtual int32_t getContentHeight() const;

    virtual float getScale();
    virtual float getMinimumScale() const;
    virtual float getMaximumScale() const;
	
    virtual void pinchTo(const view::RectF&);
    virtual void pinchBy(float, float, float);
    virtual void pinchEnd();

    virtual view::RectF getViewport();

    virtual void invalidate();
    virtual void invalidate(const view::Rect&);

    virtual int64_t nativeWindowHandle() override;

protected:
    SWKView();

    inline float contentsToScreen(float value) { return value * getEffectiveScale(); }
    inline float screenToContents(float value) { return value / getEffectiveScale(); }

    virtual void didChangeContentsPosition(int32_t, int32_t) override;
    virtual void didChangeContentsSize(int32_t, int32_t) override;
    virtual void didChangeViewportAttributes(float, float, float) override;

    virtual void setViewNeedsDisplay(int32_t, int32_t, int32_t, int32_t) override;

    virtual void hasTouchEventHandlers(bool) override;
    virtual void doneWithTouchEvent(bool) override;

    virtual void didChangeCursor(int32_t) override;
    virtual void didChangeCursor(int32_t hotSpotX, int32_t hotSpotY, std::shared_ptr<Managed::WebBitmap> dragImage) override;
    virtual void didChangeTooltip(const std::string&) override;

    virtual void startInputMethod(bool) override;
    virtual void endInputMethod() override;
    virtual void editorStateChanged(const std::string&, int32_t, int32_t, int32_t, int32_t) override;

    virtual void enterFullScreen() override;
    virtual void exitFullScreen() override;

    virtual void didPerformDragControllerAction(int64_t, bool, int32_t) override;
    virtual void setDragImage(int32_t, int32_t, std::shared_ptr<Managed::WebBitmap>, bool) override;
    virtual void setPromisedData(const std::string&, const std::vector<int8_t>&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&) override;

    virtual bool isSpeaking() override;
    virtual void speak(const std::string&) override;
    virtual void stopSpeaking() override;

    virtual void webProcessCrashed(const std::string&) override;

    virtual float getEffectiveScale();

private:
    std::shared_ptr<SWKWebContent> m_webContent;
    std::shared_ptr<Managed::CompletionHandler> m_closeListener;
    view::ContentView* m_view;

    int32_t m_width;
    int32_t m_height;
    int32_t m_contentWidth;
    int32_t m_contentHeight;

    float m_minimumScale;
    float m_maximumScale;
    float m_viewportX;
    float m_viewportY;

    bool m_disableMotionDetection;
    bool m_enableMouseTouchEvents;

    bool m_hasInputMethod;
};

}

#endif
