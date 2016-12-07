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

#ifndef SWKView_h
#define SWKView_h

#include "SWKViewNativesBase.h"

#include "PageViewportController.h"
#include "PageViewportControllerClientSling.h"
#include <WebCore/Cursor.h>
#include <WebCore/Editor.h>

#include <onig/GlobalRef.h>

namespace WebKit {

class ContextMenuContextData;
class CoordinatedGraphicsScene;
class NativeWebKeyboardEvent;
class PageClientSling;
class ShareableBitmap;
class SWKWebContent;
class UserData;
class WebPopupMenuProxy;

#if ENABLE(CONTEXT_MENUS)
class WebContextMenuProxy;
#endif

class SWKView final : public Natives::SWKView {
    friend class Natives::SWKView;
public:
    ~SWKView();

    PageViewportController& pageViewportController() { return m_pageViewportController; }

    SWKWebContent& webContent() const { return m_webContent; }

    bool useFixedLayout();

    void didChangeViewportAttributes();
    void setViewportPosition(const WebCore::FloatPoint&);
    WebCore::FloatRect mapToViewport(const WebCore::FloatRect&) const;

    void setViewNeedsDisplay(const WebCore::IntRect&);

    bool paintToCurrentGLContext();
    void contextLostGL();
    void teardownGL();
    void setViewResumePainting();

    void editorStateChanged();

    void setCursor(const WebCore::Cursor&);

    RefPtr<WebPopupMenuProxy> createPopupMenuProxy(WebPageProxy&);
#if ENABLE(CONTEXT_MENUS)
    std::unique_ptr<WebContextMenuProxy> createContextMenuProxy(WebPageProxy&, const ContextMenuContextData&, const UserData&);
#endif

#if ENABLE(DRAG_SUPPORT)
    void dragEntered(Native::PassLocalRef<Natives::WebDragData>);
    void dragUpdated(Native::PassLocalRef<Natives::WebDragData>);
    void dragExited(Native::PassLocalRef<Natives::WebDragData>);

    void performDragOperation(Native::PassLocalRef<Natives::WebDragData>);
    void dragEnded(Native::PassLocalRef<Natives::Point>, Native::PassLocalRef<Natives::Point>, int32_t);
    void setDragImage(const WebCore::IntPoint&, PassRefPtr<ShareableBitmap>, bool);
    void setPromisedData(const String&, PassRefPtr<WebCore::SharedBuffer>, const String&, const String&, const String&, const String&, const String&, PassRefPtr<WebCore::SharedBuffer>);
#endif

    bool isSpeaking();
    void speak(const String&);
    void stopSpeaking();

    void doneWithKeyEvent(const NativeWebKeyboardEvent&, bool);

    void webProcessCrashed(const String&);
    void webProcessDidRelaunch();

    void setPageScaleFactor(float, int32_t, int32_t) override;
    float getPageScaleFactor() override;
    void setIntrinsicDeviceScaleFactor(float) override;
    float getIntrinsicDeviceScaleFactor() override;
    void setOverrideDeviceScaleFactor(float overrideDeviceScaleFactor) override;
    float getOverrideDeviceScaleFactor() override;

    void setActive(bool) override;

    void sendSingleTap(float, float) override;
    void sendSingleTapUnconfirmed(float, float) override;
    void sendDoubleTap(float, float) override;
    void sendLongTap(float, float) override;

    void sendShowPressState(float, float) override;
    void sendShowPressCancel(float, float) override;
    void sendLongPress(float, float) override;

    void sendTouchEvent(int64_t, int32_t, int32_t, float, float, float, float, int32_t) override;
    void sendMouseEvent(int64_t, int32_t, int32_t, float, float, float, float, int32_t) override;
    void sendWheelEvent(int64_t, int32_t, int32_t, float, float, float, float, float, float) override;
    void sendKeyEvent(int64_t, int32_t, int32_t, int32_t, int32_t, const std::string&, const std::string&, bool, bool, bool, int32_t) override;

    void setBackgroundColor(int32_t) override;
    int32_t getBackgroundColor() override;

    void setUseFixedLayout(bool) override;
    bool getUseFixedLayout() override;

    void scrollBegin(float, float) override;
    bool scrollBy(float, float, bool) override;
    bool scrollTo(float, float) override;
    void scrollEnd(float, float) override;

    void pinchBegin(float, float) override;
    void adjustTransientZoom(float, float, float) override;
    void commitTransientZoom() override;

    bool requestExitFullScreen() override;

    bool isVisible() override;
    bool isFocused() override;
    bool isActive() override;

private:
    void dispatchOnMainThread(std::function<void ()>);

    void nativeSetInWindow(bool) override;
    void nativeSetVisible(bool) override;
    void nativeSetFocus(bool) override;
    void nativeLayoutChanged(int32_t, int32_t) override;
    void nativeDisplayLocationChanged(int32_t, int32_t) override;

    void onPause() override;
    void onResume() override;

    void enqueuePaintingThreadTask(std::function<void ()>);
    void performPaintingThreadTasks();

private:
    SWKView(SWKWebContent&);

    WebPageProxy& webPage() const;
    PageClientSling& pageClient();
    const PageClientSling& pageClient() const;

    SWKWebContent& m_webContent;

    PageViewportControllerClientSling m_pageViewportControllerClient;
    PageViewportController m_pageViewportController;

    WebCore::Image* m_lastCursorImage;
    bool m_hasInputMethod;
    bool m_waitingForKeyEventHandled;
    Vector<NativeWebKeyboardEvent> m_pendingKeyEvents;

    WebCore::FloatPoint m_transientZoomOrigin;
    float m_transientZoomMagnification;

    std::atomic<bool> m_paintingDisabled;
    Vector<RefPtr<CoordinatedGraphicsScene>> m_detachedScenes;
    Vector<std::function<void ()>> m_paintingThreadTasks;
    bool m_hasPaintingThreadTasks;
    Mutex m_paintingThreadMutex;
    float m_overrideDeviceScaleFactor;
};

}

#endif // SWKView_h
