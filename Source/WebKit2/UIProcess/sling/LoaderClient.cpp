/*
 * Copyright (C) 2014-2015 Naver Corp. All rights reserved.
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
#include "LoaderClient.h"

#include "AuthenticationChallengeProxy.h"
#include "AuthenticationDecisionListener.h"
#include "WebBackForwardListItem.h"
#include "SWKAuthenticationChallengeNatives.h"
#include "SWKNavigationNatives.h"
#include "SWKWebContentNatives.h"
#include "SWKErrorNatives.h"
#include <WebCore/NotImplemented.h>

using namespace WebCore;

namespace WebKit {

LoaderClient::LoaderClient(SWKWebContent& webContent, Native::PassLocalRef<Natives::SWKLoaderDelegate> delegate)
    : m_webContent(webContent)
    , m_delegate(delegate)
{
    ASSERT(m_delegate);
}

void LoaderClient::didStartProvisionalLoadForFrame(WebPageProxy& page, WebFrameProxy& frame, API::Navigation*, API::Object* userData)
{
    if (!frame.isMainFrame())
        return;

    m_delegate->didStartProvisionalLoad();
}

void LoaderClient::didReceiveServerRedirectForProvisionalLoadForFrame(WebPageProxy& page, WebFrameProxy& frame, API::Navigation*, API::Object* userData)
{
    if (!frame.isMainFrame())
        return;

    m_delegate->didReceiveServerRedirectForProvisionalLoad();
}

void LoaderClient::didFailProvisionalLoadWithErrorForFrame(WebPageProxy& page, WebFrameProxy& frame, API::Navigation*, const ResourceError& error, API::Object* userData)
{
    if (!frame.isMainFrame())
        return;

    m_delegate->didFailProvisionalLoadWithError(SWKError::create(error));
}

void LoaderClient::didCommitLoadForFrame(WebPageProxy& page, WebFrameProxy& frame, API::Navigation*, API::Object* userData)
{
    if (!frame.isMainFrame())
        return;

    m_delegate->didCommitLoad();
}

void LoaderClient::didFinishLoadForFrame(WebPageProxy& page, WebFrameProxy& frame, API::Navigation*, API::Object* userData)
{
    if (!frame.isMainFrame())
        return;

    m_delegate->didFinishLoad();
}

void LoaderClient::didFailLoadWithErrorForFrame(WebPageProxy& page, WebFrameProxy& frame, API::Navigation*, const ResourceError& error, API::Object* userData)
{
    if (!frame.isMainFrame())
        return;

    m_delegate->didFailProvisionalLoadWithError(SWKError::create(error));
}

void LoaderClient::didSameDocumentNavigationForFrame(WebPageProxy& page, WebFrameProxy& frame, API::Navigation*, SameDocumentNavigationType type, API::Object* userData)
{
    if (!frame.isMainFrame())
        return;

    m_delegate->didSameDocumentNavigation(&m_webContent, SWKNavigation::create(), type);
}

void LoaderClient::didReceiveTitleForFrame(WebPageProxy& page, const String& title, WebFrameProxy& frame, API::Object* userData)
{
    if (!frame.isMainFrame())
        return;

    m_delegate->didReceiveTitle(title.utf8().data());
}

void LoaderClient::didStartProgress(WebPageProxy& page)
{
    m_delegate->didChangeProgress(page.estimatedProgress());
}

void LoaderClient::didChangeProgress(WebPageProxy& page)
{
    m_delegate->didChangeProgress(page.estimatedProgress());
}

void LoaderClient::didFinishProgress(WebPageProxy& page)
{
    m_delegate->didChangeProgress(page.estimatedProgress());
}

void LoaderClient::didReceiveAuthenticationChallengeInFrame(WebPageProxy&, WebFrameProxy&, AuthenticationChallengeProxy* authenticationChallenge)
{
    notImplemented();
}

void LoaderClient::didChangeBackForwardList(WebKit::WebPageProxy&, WebKit::WebBackForwardListItem*, Vector<RefPtr<WebKit::WebBackForwardListItem>>)
{
    m_delegate->didChangeBackForwardList();
}

void LoaderClient::processDidBecomeUnresponsive(WebPageProxy& page)
{
    m_delegate->processDidBecomeUnresponsive();
}

void LoaderClient::processDidBecomeResponsive(WebPageProxy& page)
{
    m_delegate->processDidBecomeResponsive();
}

void LoaderClient::processDidCrash(WebPageProxy& page)
{
    m_delegate->webViewWebContentProcessDidTerminate(&m_webContent);
}

} // namespace WebKit
