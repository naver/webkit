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

#ifndef UIClient_h
#define UIClient_h

#include "APIUIClient.h"
#include "SWKUIDelegateNatives.h"
#include <onig/GlobalRef.h>

namespace API {
class OpenPanelParameters;
class SecurityOrigin;
class Array;
}

namespace WebKit {

class SWKWebContent;

class UIClient final : public API::UIClient {
public:
    UIClient(SWKWebContent&, Native::PassLocalRef<Natives::SWKUIDelegate>);

    Native::PassLocalRef<Natives::SWKUIDelegate> delegate() { return m_delegate; }

private:
    virtual PassRefPtr<WebPageProxy> createNewPage(WebPageProxy*, WebFrameProxy*, const WebCore::SecurityOriginData&, const WebCore::ResourceRequest&, const WebCore::WindowFeatures&, const NavigationActionData&) override;
    virtual void close(WebKit::WebPageProxy*) override;

    virtual void runJavaScriptAlert(WebPageProxy*, const String&, WebFrameProxy*, const WebCore::SecurityOriginData&, std::function<void ()>) override;
    virtual void runJavaScriptConfirm(WebPageProxy*, const String&, WebFrameProxy*, const WebCore::SecurityOriginData&, std::function<void (bool)>) override;
    virtual void runJavaScriptPrompt(WebPageProxy*, const String&, const String&, WebFrameProxy*, const WebCore::SecurityOriginData&, std::function<void (const String&)>) override;

    virtual void mouseDidMoveOverElement(WebPageProxy*, const WebHitTestResultData&, WebEvent::Modifiers, API::Object*) override;

#if ENABLE(TOUCH_EVENTS)
    virtual void hasTouchEventHandlers(WebPageProxy*, bool hasTouchHandlers) override;
#endif

    virtual bool canRunBeforeUnloadConfirmPanel() const { return true; }
    virtual void runBeforeUnloadConfirmPanel(WebPageProxy*, const String&, WebFrameProxy*, std::function<void (bool)> completionHandler) override;

    virtual bool runOpenPanel(WebPageProxy*, WebFrameProxy*, const WebCore::SecurityOriginData&, API::OpenPanelParameters*, WebOpenPanelResultListenerProxy*) override;

    virtual bool decidePolicyForNotificationPermissionRequest(WebPageProxy*, API::SecurityOrigin*, NotificationPermissionRequest*) override;

#if ENABLE(GEOLOCATION)
    virtual bool decidePolicyForGeolocationPermissionRequest(WebPageProxy*, WebFrameProxy*, API::SecurityOrigin*, GeolocationPermissionRequestProxy*) override;
#endif

    virtual void exceededDatabaseQuota(WebKit::WebPageProxy*, WebKit::WebFrameProxy*, API::SecurityOrigin*, const WTF::String&, const WTF::String&, unsigned long long currentQuota, unsigned long long, unsigned long long, unsigned long long, std::function<void (unsigned long long)> completionHandler) override;

    virtual void setWindowFrame(WebKit::WebPageProxy*, const WebCore::FloatRect&) override;
    virtual WebCore::FloatRect windowFrame(WebKit::WebPageProxy*) override;

#if ENABLE(NETSCAPE_PLUGIN_API)
    virtual void unavailablePluginButtonClicked(WebKit::WebPageProxy*, WKPluginUnavailabilityReason, API::Dictionary*) override;
#endif // ENABLE(NETSCAPE_PLUGIN_API)

private:
    SWKWebContent& m_webContent;
    Native::GlobalRef<SWKUIDelegate> m_delegate;
};

} // namespace WebKit

#endif // UIClient_h
