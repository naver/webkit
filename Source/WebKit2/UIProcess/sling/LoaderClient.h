/*
 * Copyright (C) 2014 Naver Corp. All rights reserved.
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

#ifndef LoaderClient_h
#define LoaderClient_h

#include "APILoaderClient.h"
#include "SWKLoaderDelegateNatives.h"
#include <WebKit/WKPageLoadTypes.h>
#include <WebKit/WKBase.h>
#include <onig/GlobalRef.h>

namespace WebKit {

class SWKWebContent;

class LoaderClient final : public API::LoaderClient {
public:
    LoaderClient(SWKWebContent&, Native::PassLocalRef<Natives::SWKLoaderDelegate>);
    ~LoaderClient() = default;

private:
    void didStartProvisionalLoadForFrame(WebPageProxy& page, WebFrameProxy& frame, API::Navigation*, API::Object* userData) override;
    void didReceiveServerRedirectForProvisionalLoadForFrame(WebPageProxy& page, WebFrameProxy& frame, API::Navigation*, API::Object* userData) override;
    void didFailProvisionalLoadWithErrorForFrame(WebPageProxy& page, WebFrameProxy& frame, API::Navigation*, const WebCore::ResourceError& error, API::Object* userData) override;
    void didCommitLoadForFrame(WebPageProxy& page, WebFrameProxy& frame, API::Navigation*, API::Object* userData) override;
    void didFinishLoadForFrame(WebPageProxy& page, WebFrameProxy& frame, API::Navigation*, API::Object* userData) override;
    void didFailLoadWithErrorForFrame(WebPageProxy& page, WebFrameProxy& frame, API::Navigation*, const WebCore::ResourceError& error, API::Object* userData) override;
    void didSameDocumentNavigationForFrame(WebPageProxy& page, WebFrameProxy& frame, API::Navigation*, SameDocumentNavigationType type, API::Object* userData) override;
    void didReceiveTitleForFrame(WebPageProxy& page, const String& title, WebFrameProxy& frame, API::Object* userData) override;
    void didStartProgress(WebPageProxy& page) override;
    void didChangeProgress(WebPageProxy& page) override;
    void didFinishProgress(WebPageProxy& page) override;
    void didReceiveAuthenticationChallengeInFrame(WebPageProxy& page, WebFrameProxy& frame, AuthenticationChallengeProxy* authenticationChallenge) override;    
    void didChangeBackForwardList(WebKit::WebPageProxy&, WebKit::WebBackForwardListItem*, Vector<RefPtr<WebKit::WebBackForwardListItem>>) override;

    void processDidBecomeUnresponsive(WebPageProxy& page) override;
    void processDidBecomeResponsive(WebPageProxy& page) override;
    void processDidCrash(WebPageProxy& page) override;

    SWKWebContent& m_webContent;
    Native::GlobalRef<SWKLoaderDelegate> m_delegate;
};

} // namespace WebKit

#endif // LoaderClient_h
