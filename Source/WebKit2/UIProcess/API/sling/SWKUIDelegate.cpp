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
#include "SWKUIDelegate.h"

#include "SWKURLRequest.h"
#include "SWKWebHitTestResult.h"
#include "SWKOpenPanelResultListener.h"
#include <ManagedVector.h>
#include <ManagedRect.h>

namespace WebKit {
namespace Managed {

void SWKUIDelegate::INIT()
{
}

std::shared_ptr<Managed::SWKWebContent> SWKUIDelegate::createWebViewWithConfiguration(
    std::shared_ptr<Managed::SWKWebContentConfiguration> configuration,
    std::shared_ptr<Managed::SWKNavigationAction> navigationAction,
    std::shared_ptr<Managed::SWKWindowFeatures> windowFeatures)
{
    return nullptr;
}

bool SWKUIDelegate::runJavaScriptAlertPanelWithMessage(std::shared_ptr<Managed::SWKWebContent> webContent,
    const std::string& message, std::shared_ptr<Managed::SWKFrameInfo> frame, std::shared_ptr<Managed::CompletionHandler> completionHandler)
{
    return false;
}

bool SWKUIDelegate::runJavaScriptConfirmPanelWithMessage(std::shared_ptr<Managed::SWKWebContent> webContent,
    const std::string& message, std::shared_ptr<Managed::SWKFrameInfo> frame, std::shared_ptr<Managed::CompletionHandler> completionHandler)
{
    return false;
}

bool SWKUIDelegate::runBeforeUnloadConfirmPanelWithMessage(std::shared_ptr<Managed::SWKWebContent> webContent,
    const std::string& message, std::shared_ptr<Managed::SWKFrameInfo> frame, std::shared_ptr<Managed::CompletionHandler> completionHandler)
{
    return false;
}

bool SWKUIDelegate::runJavaScriptTextInputPanelWithPrompt(std::shared_ptr<Managed::SWKWebContent> webContent,
    const std::string& prompt, const std::string& defaultText, std::shared_ptr<Managed::SWKFrameInfo> frame, std::shared_ptr<Managed::CompletionHandler> completionHandler)
{
    return false;
}

void SWKUIDelegate::decideDatabaseQuotaForSecurityOrigin(std::shared_ptr<Managed::SWKWebContent> webContent,
    std::shared_ptr<Managed::SWKSecurityOrigin> securityOrigin, int64_t currentQuota, int64_t currentOriginUsage,
    int64_t currentUsage, int64_t expectedUsage, std::shared_ptr<Managed::CompletionHandler> decisionHandler)
{
}

void SWKUIDelegate::decideWebApplicationCacheQuotaForSecurityOrigin(std::shared_ptr<Managed::SWKWebContent> webContent,
    std::shared_ptr<Managed::SWKSecurityOrigin> securityOrigin, int64_t currentQuota, int64_t totalBytesNeeded,
    std::shared_ptr<Managed::CompletionHandler> decisionHandler)
{
}

bool SWKUIDelegate::decidePolicyForGeolocationPermissionRequest(std::shared_ptr<Managed::SWKSecurityOrigin> origin,
    std::shared_ptr<Managed::SWKGeolocationPermissionRequest> request)
{
    return false;
}

bool SWKUIDelegate::decidePolicyForNotificationPermissionRequest(std::shared_ptr<Managed::SWKSecurityOrigin> origin,
    std::shared_ptr<Managed::SWKNotificationPermissionRequest> request)
{
    return false;
}

void SWKUIDelegate::printFrame(std::shared_ptr<Managed::SWKWebContent> webContent,
    std::shared_ptr<Managed::SWKFrameHandle> frame)
{
}

void SWKUIDelegate::webViewClose(std::shared_ptr<Managed::SWKWebContent> webContent)
{
}

std::shared_ptr<Native::Managed::Vector> SWKUIDelegate::actionsForElement(std::shared_ptr<Managed::SWKWebContent> webContent,
    std::shared_ptr<Managed::SWKActivatedElementInfo> element,
    std::shared_ptr<Native::Managed::Vector> defaultActions)
{
    return Managed::Vector::create();
}

void SWKUIDelegate::didNotHandleTapAsClickAtPoint(std::shared_ptr<Managed::SWKWebContent> webContent,
    std::shared_ptr<Managed::Point> point)
{
}

bool SWKUIDelegate::shouldRequestGeolocationAuthorizationForURL(std::shared_ptr<Managed::SWKWebContent> webContent,
    std::shared_ptr<Managed::SWKURL> url,
    bool isMainFrame,
    std::shared_ptr<Managed::SWKURL> mainFrameURL)
{
    return false;
}

void SWKUIDelegate::mouseDidMoveOverElement(std::shared_ptr<SWKWebHitTestResult> hitTestResult, int32_t modifiers)
{
}

bool SWKUIDelegate::runOpenPanel(std::shared_ptr<Managed::SWKOpenPanelResultListener> request)
{
    return false;
}

bool SWKUIDelegate::exceededDatabaseQuota(std::shared_ptr<Managed::SWKWebContent> webContent, std::shared_ptr<Managed::SWKSecurityOrigin> securityOrigin, int64_t currentQuota,
     int64_t currentOriginUsage, int64_t currentDatabaseUsage, int64_t expectedUsage, std::shared_ptr<Managed::CompletionHandler> completionHandler)
{
    return false;
}

std::shared_ptr<Managed::Rect> SWKUIDelegate::getWindowRect(std::shared_ptr<Managed::SWKWebContent>)
{
    return Managed::Rect::create();
}

void SWKUIDelegate::setWindowRect(std::shared_ptr<Managed::SWKWebContent>, std::shared_ptr<Managed::Rect>)
{
}

void SWKUIDelegate::receiveMessageFromJavaScript(std::shared_ptr<Managed::SWKWebContent>, std::shared_ptr<Managed::Vector>)
{
}

void SWKUIDelegate::didPressMissingPluginButton(const std::string&)
{
}

} // namespace Managed
} // namespace WebKit
