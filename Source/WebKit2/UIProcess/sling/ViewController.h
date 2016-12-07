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

#ifndef ViewController_h
#define ViewController_h

#include "SWKViewNatives.h"

#include <onig/WeakGlobalRef.h>

namespace WebKit {

class WebEditable;

#if ENABLE(CONTEXT_MENUS)
class WebContextMenuProxy;
#endif

class ViewController {
    friend class SWKWebContent;
public:
    ~ViewController();

    void hasTouchEventHandlers(bool hasTouchHandlers);

    void enterFullScreen();
    void exitFullScreen();

    void setViewNeedsDisplay(const WebCore::IntRect&);
    void setViewResumePainting();

    void editorStateChanged();

    void setCursor(const WebCore::Cursor&);

    RefPtr<WebPopupMenuProxy> createPopupMenuProxy(WebPageProxy&);
#if ENABLE(CONTEXT_MENUS)
    std::unique_ptr<WebContextMenuProxy> createContextMenuProxy(WebPageProxy&, const ContextMenuContextData&, const UserData&);
#endif

    bool isSpeaking();
    void speak(const String& string);
    void stopSpeaking();

    void doneWithKeyEvent(const NativeWebKeyboardEvent&, bool wasEventHandled);
#if ENABLE(TOUCH_EVENTS)
    void doneWithTouchEvent(bool wasEventHandled);
#endif

    void didCommitLoad();
    void didChangeContentsSize(const WebCore::IntSize&);
    void didChangeContentsPosition(const WebCore::IntPoint&);
    void didChangeViewportAttributes(const WebCore::ViewportAttributes&);
    void didChangeTooltip(const String&);
    void didRenderFrame(const WebCore::IntSize&, const WebCore::IntRect&);
    void didCompletePageTransition();

    void webProcessCrashed(const String&);
    void webProcessDidRelaunch();

    const WebCore::IntSize& getContentSize() const { return m_contentSize; }

    // FIXME: Remove all nativeWindowHandle()s from WebKit.
#if OS(WINDOWS)
    int64_t nativeWindowHandle();
#endif

private:

private:
    ViewController(SWKWebContent&);

    Native::PassLocalRef<SWKView> createView(SWKWebContent*);
    Native::PassLocalRef<SWKView> view();

    Native::WeakGlobalRef<SWKView> m_view;
    SWKWebContent& m_content;

    WebCore::IntSize m_contentSize;
};

} // namespace WebKit

#endif // ViewController_h
