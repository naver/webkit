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
#include "PolicyClient.h"

#include "APIPolicyClient.h"
#include "APIURLRequest.h"
#include "NavigationActionData.h"
#include "SWKNavigationActionNatives.h"
#include "SWKFramePolicyListenerNatives.h"
#include "SWKURLNatives.h"
#include "SWKWebContentNatives.h"
#include "WKAPICast.h"
#include "WebFrameProxy.h"
#include <WebCore/HTTPStatusCodes.h>
#include <WebCore/NotImplemented.h>
#include <WebKit/WKFramePolicyListener.h>

namespace WebKit {

PolicyClient::PolicyClient(SWKWebContent& webContent, Native::PassLocalRef<Natives::SWKPolicyDelegate> delegate)
    : m_webContent(webContent)
    , m_delegate(delegate)
{
    ASSERT(m_delegate);
}

void PolicyClient::decidePolicyForNavigationAction(WebPageProxy&, WebFrameProxy*, const NavigationActionData& navigationActionData, WebFrameProxy* sourceFrame,
    const WebCore::ResourceRequest& /*originalRequest*/, const WebCore::ResourceRequest& resourceRequest, Ref<WebFramePolicyListenerProxy>&& listener, API::Object*)
{
    Native::LocalRef<SWKURLRequest> request = SWKURLRequest::create(SWKURL::create(resourceRequest.url()),
        resourceRequest.firstPartyForCookies().string().utf8().data(), resourceRequest.httpMethod().utf8().data());
    Native::LocalRef<SWKNavigationAction> navigationAction = SWKNavigationAction::create(navigationActionData, request.release());
    Native::LocalRef<SWKFramePolicyListener> policyListener = SWKFramePolicyListener::create(WTFMove(listener));
    m_delegate->decidePolicyForNavigationAction(&m_webContent, navigationAction, policyListener);
}

void PolicyClient::decidePolicyForNewWindowAction(WebPageProxy& webPageProxy, WebFrameProxy&, const NavigationActionData& navigationActionData, const WebCore::ResourceRequest& resourceRequest, const WTF::String&, Ref<WebFramePolicyListenerProxy>&& listener, API::Object*)
{
    decidePolicyForNavigationAction(webPageProxy, nullptr, navigationActionData, nullptr, resourceRequest, resourceRequest, WTFMove(listener), nullptr);
}

void PolicyClient::decidePolicyForResponse(WebPageProxy&, WebFrameProxy& frame, const WebCore::ResourceResponse& resourceResponse, const WebCore::ResourceRequest& resourceRequest, bool canShowMIMEType, Ref<WebFramePolicyListenerProxy>&& listener, API::Object*)
{
    notImplemented();
}

}
