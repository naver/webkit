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

#ifndef PolicyClient_h
#define PolicyClient_h

#include "APIPolicyClient.h"
#include "SWKPolicyDelegateNatives.h"
#include <onig/GlobalRef.h>

namespace WebKit {

class SWKWebContent;

class PolicyClient final : public API::PolicyClient {
public:
    PolicyClient(SWKWebContent&, Native::PassLocalRef<Natives::SWKPolicyDelegate>);
    ~PolicyClient() = default;

private:
    void decidePolicyForNavigationAction(WebPageProxy&, WebFrameProxy* destinationFrame, const NavigationActionData&, WebFrameProxy* sourceFrame, const WebCore::ResourceRequest& originalRequest, const WebCore::ResourceRequest&, Ref<WebFramePolicyListenerProxy>&&, API::Object* userData) override;
    void decidePolicyForNewWindowAction(WebPageProxy&, WebFrameProxy& sourceFrame, const NavigationActionData&, const WebCore::ResourceRequest&, const WTF::String& frameName, Ref<WebFramePolicyListenerProxy>&&, API::Object* userData) override;
    void decidePolicyForResponse(WebPageProxy&, WebFrameProxy&, const WebCore::ResourceResponse&, const WebCore::ResourceRequest&, bool canShowMIMEType, Ref<WebFramePolicyListenerProxy>&&, API::Object* userData) override;

    SWKWebContent& m_webContent;
    Native::GlobalRef<SWKPolicyDelegate> m_delegate;
};

}

#endif // PolicyClient_h
