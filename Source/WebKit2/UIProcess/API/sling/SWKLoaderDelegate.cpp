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

#include "config.h"
#include "SWKLoaderDelegate.h"

#include "SWKAuthenticationChallenge.h"
#include "SWKDataManagedBase.h"
#include "SWKError.h"

namespace WebKit {
namespace Managed {

void SWKLoaderDelegate::INIT()
{
}

void SWKLoaderDelegate::didStartProvisionalNavigation(std::shared_ptr<Managed::SWKWebContent> webContent,
    std::shared_ptr<Managed::SWKNavigation> navigation)
{
}

void SWKLoaderDelegate::didReceiveServerRedirectForProvisionalNavigation(std::shared_ptr<Managed::SWKWebContent> webContent,
    std::shared_ptr<Managed::SWKNavigation> navigation)
{
}

void SWKLoaderDelegate::didFailProvisionalNavigation(std::shared_ptr<Managed::SWKWebContent> webContent,
    std::shared_ptr<Managed::SWKNavigation> navigation,
    std::shared_ptr<Managed::SWKError> error)
{
}

void SWKLoaderDelegate::didCommitNavigation(std::shared_ptr<Managed::SWKWebContent> webContent,
    std::shared_ptr<Managed::SWKNavigation> navigation)
{
}

void SWKLoaderDelegate::didFinishNavigation(std::shared_ptr<Managed::SWKWebContent> webContent,
    std::shared_ptr<Managed::SWKNavigation> navigation)
{
}

void SWKLoaderDelegate::didFailNavigation(std::shared_ptr<Managed::SWKWebContent> webContent,
    std::shared_ptr<Managed::SWKNavigation> navigation,
    std::shared_ptr<Managed::SWKError> error)
{
}

void SWKLoaderDelegate::didReceiveAuthenticationChallenge(std::shared_ptr<Managed::SWKWebContent> webContent,
    std::shared_ptr<Managed::SWKAuthenticationChallenge> challenge,
    std::shared_ptr<Managed::CompletionHandler> completionHandler)
{
}

void SWKLoaderDelegate::didFailProvisionalLoadInSubframe(std::shared_ptr<Managed::SWKWebContent> webContent,
    std::shared_ptr<Managed::SWKNavigation> navigation,
    std::shared_ptr<Managed::SWKFrameInfo> subframe,
    std::shared_ptr<Managed::SWKError> error)
{
}

void SWKLoaderDelegate::navigationDidFinishDocumentLoad(std::shared_ptr<Managed::SWKWebContent> webContent,
    std::shared_ptr<Managed::SWKNavigation> navigation)
{
}

void SWKLoaderDelegate::didSameDocumentNavigation(std::shared_ptr<Managed::SWKWebContent> webContent,
    std::shared_ptr<Managed::SWKNavigation> navigation,
    int32_t navigationType)
{
}

void SWKLoaderDelegate::renderingProgressDidChange(std::shared_ptr<Managed::SWKWebContent> webContent,
    int32_t progressEvents)
{
}

bool SWKLoaderDelegate::canAuthenticateAgainstProtectionSpace(std::shared_ptr<Managed::SWKWebContent> webContent,
    std::shared_ptr<Managed::SWKProtectionSpace> protectionSpace)
{
    return false;
}

void SWKLoaderDelegate::didReceiveAuthenticationChallenge(std::shared_ptr<Managed::SWKWebContent> webContent,
    std::shared_ptr<Managed::SWKAuthenticationChallenge> challenge)
{
}

void SWKLoaderDelegate::webViewWebContentProcessDidTerminate(std::shared_ptr<Managed::SWKWebContent> webContent)
{
}

std::shared_ptr<Managed::SWKData> SWKLoaderDelegate::webCryptoMasterKeyForWebView(std::shared_ptr<Managed::SWKWebContent> webContent)
{
    return Managed::SWKData::create(std::vector<int8_t>());
}

void SWKLoaderDelegate::willSnapshotBackForwardListItem(std::shared_ptr<Managed::SWKWebContent> webContent,
    std::shared_ptr<Managed::SWKBackForwardListItem> item)
{
}

void SWKLoaderDelegate::didStartLoadForQuickLookDocumentInMainFrameWithFileName(std::shared_ptr<Managed::SWKWebContent> webContent,
    const std::string& fileName,
    const std::string& uti)
{
}

void SWKLoaderDelegate::didFinishLoadForQuickLookDocumentInMainFrame(std::shared_ptr<Managed::SWKWebContent> webContent,
    std::shared_ptr<Managed::SWKData> documentData)
{
}

void SWKLoaderDelegate::didReceiveTitle(const std::string& title)
{
}

void SWKLoaderDelegate::didChangeProgress(double /*progress*/)
{
}

void SWKLoaderDelegate::didFinishLoad()
{
}

void SWKLoaderDelegate::didFailLoadWithError(std::shared_ptr<SWKError> error)
{
}

void SWKLoaderDelegate::didStartProvisionalLoad()
{
}

void SWKLoaderDelegate::didCommitLoad()
{

}

void SWKLoaderDelegate::didReceiveAuthenticationChallengeInFrame(std::shared_ptr<Managed::SWKAuthenticationChallenge> challenge)
{
}

void SWKLoaderDelegate::didNavigateWithNavigationData(std::shared_ptr<Managed::SWKWebContent> webContent,
    std::shared_ptr<Managed::SWKNavigationData> navigationData)
{
}

void SWKLoaderDelegate::didPerformClientRedirectFromURL(std::shared_ptr<Managed::SWKWebContent> webContent,
    std::shared_ptr<Managed::SWKURL> sourceURL,
    std::shared_ptr<Managed::SWKURL> destinationURL)
{
}

void SWKLoaderDelegate::didPerformServerRedirectFromURL(std::shared_ptr<Managed::SWKWebContent> webContent,
    std::shared_ptr<Managed::SWKURL> sourceURL,
    std::shared_ptr<Managed::SWKURL> destinationURL)
{
}

void SWKLoaderDelegate::didUpdateHistoryTitle(std::shared_ptr<Managed::SWKWebContent> webContent,
    const std::string& title,
    std::shared_ptr<Managed::SWKURL> URL)
{
}

void SWKLoaderDelegate::didReceiveServerRedirectForProvisionalLoad()
{
}

void SWKLoaderDelegate::didFailProvisionalLoadWithError(std::shared_ptr<SWKError> error)
{
}

void SWKLoaderDelegate::didChangeBackForwardList()
{
}

void SWKLoaderDelegate::processDidBecomeUnresponsive()
{
}

void SWKLoaderDelegate::processDidBecomeResponsive()
{
}

void SWKLoaderDelegate::processDidCrash()
{
}

}
} // namespace WebKit
