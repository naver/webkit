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
#include "UIClient.h"

#include "CompletionHandlerNatives.h"
#include "NativeWebCoreGraphics.h"
#include "PluginInformation.h"
#include "SWKOpenPanelResultListenerNatives.h"
#include "SWKFrameInfoNatives.h"
#include "SWKGeolocationPermissionRequestNatives.h"
#include "SWKNotificationPermissionRequestNatives.h"
#include "SWKSecurityOriginNatives.h"
#include "SWKWebContentNatives.h"
#include "SWKWebHitTestResultNatives.h"
#include <WebCore/NotImplemented.h>

#include <NativesString.h>
#include <NativesVector.h>

using namespace WebCore;

namespace WebKit {

UIClient::UIClient(SWKWebContent& webContent, Native::PassLocalRef<Natives::SWKUIDelegate> delegate)
    : m_webContent(webContent)
    , m_delegate(delegate)
{
    ASSERT(m_delegate);
}

PassRefPtr<WebPageProxy> UIClient::createNewPage(WebPageProxy*, WebFrameProxy*, const SecurityOriginData&, const ResourceRequest& resourceRequest, const WindowFeatures& windowFeatures, const NavigationActionData& navigationActionData)
{
    notImplemented();
    return nullptr;
}

void UIClient::close(WebPageProxy*)
{
    m_delegate->webViewClose(&m_webContent);
}

void UIClient::runJavaScriptAlert(WebPageProxy*, const String& message, WebFrameProxy*, const SecurityOriginData&, std::function<void ()> completionHandler)
{
    Native::LocalRef<CompletionHandler<void>> handlerObject = CompletionHandler<void>::create(completionHandler);
    if (!m_delegate->runJavaScriptAlertPanelWithMessage(&m_webContent, message.utf8().data(), SWKFrameInfo::create(), handlerObject))
        completionHandler();
}

void UIClient::runJavaScriptConfirm(WebPageProxy*, const String& message, WebFrameProxy*, const SecurityOriginData&, std::function<void (bool)> completionHandler)
{
    Native::LocalRef<CompletionHandler<bool>> handlerObject = CompletionHandler<bool>::create(completionHandler);
    if (!m_delegate->runJavaScriptConfirmPanelWithMessage(&m_webContent, message.utf8().data(), SWKFrameInfo::create(), handlerObject))
        completionHandler(false);
}

void UIClient::runJavaScriptPrompt(WebPageProxy*, const String& message, const String& defaultValue, WebFrameProxy*, const SecurityOriginData&, std::function<void (const String&)> completionHandler)
{
    Native::LocalRef<CompletionHandler<String>> handlerObject = CompletionHandler<String>::create(completionHandler);
    if (!m_delegate->runJavaScriptTextInputPanelWithPrompt(&m_webContent, message.utf8().data(), defaultValue.utf8().data(), SWKFrameInfo::create(), handlerObject))
        completionHandler(String());
}

void UIClient::runBeforeUnloadConfirmPanel(WebPageProxy*, const String& message, WebFrameProxy*, std::function<void (bool)> completionHandler)
{
    Native::LocalRef<CompletionHandler<bool>> handlerObject = CompletionHandler<bool>::create(completionHandler);
    if (!m_delegate->runBeforeUnloadConfirmPanelWithMessage(&m_webContent, message.utf8().data(), SWKFrameInfo::create(), handlerObject))
        completionHandler(false);
}

void UIClient::mouseDidMoveOverElement(WebPageProxy*, const WebHitTestResultData& data, WebEvent::Modifiers modifiers, API::Object*)
{
    RefPtr<API::HitTestResult> hitTestResult = API::HitTestResult::create(data);
    Native::LocalRef<SWKWebHitTestResult> webHitTestResult = SWKWebHitTestResult::create(*hitTestResult);
    m_delegate->mouseDidMoveOverElement(webHitTestResult, modifiers);
}

#if ENABLE(TOUCH_EVENTS)
void UIClient::hasTouchEventHandlers(WebPageProxy*, bool hasTouchHandlers)
{
    m_webContent.view().hasTouchEventHandlers(hasTouchHandlers);
}
#endif

bool UIClient::runOpenPanel(WebPageProxy*, WebFrameProxy*, const WebCore::SecurityOriginData&, API::OpenPanelParameters* parameters, WebOpenPanelResultListenerProxy* listener)
{
    Native::LocalRef<SWKOpenPanelResultListener> resultListener = SWKOpenPanelResultListener::create(parameters, listener);
    return m_delegate->runOpenPanel(resultListener);
}

bool UIClient::decidePolicyForNotificationPermissionRequest(WebPageProxy*, API::SecurityOrigin* origin, NotificationPermissionRequest* request)
{
    Native::LocalRef<SWKSecurityOrigin> securityOrigin = SWKSecurityOrigin::create(origin);
    Native::LocalRef<SWKNotificationPermissionRequest> permissionRequest = SWKNotificationPermissionRequest::create(request);
    return m_delegate->decidePolicyForNotificationPermissionRequest(securityOrigin, permissionRequest);
}

#if ENABLE(GEOLOCATION)
bool UIClient::decidePolicyForGeolocationPermissionRequest(WebPageProxy*, WebFrameProxy*, API::SecurityOrigin* origin, GeolocationPermissionRequestProxy* request)
{
    Native::LocalRef<SWKSecurityOrigin> securityOrigin = SWKSecurityOrigin::create(origin);
    Native::LocalRef<SWKGeolocationPermissionRequest> permissionRequest = SWKGeolocationPermissionRequest::create(request);
    return m_delegate->decidePolicyForGeolocationPermissionRequest(securityOrigin, permissionRequest);
}
#endif

void UIClient::exceededDatabaseQuota(WebKit::WebPageProxy*, WebKit::WebFrameProxy*, API::SecurityOrigin* origin,
    const WTF::String&, const WTF::String&, unsigned long long currentQuota, unsigned long long currentOriginUsage,
    unsigned long long currentDatabaseUsage, unsigned long long expectedUsage, std::function<void (unsigned long long)> completionHandler)
{
    Native::LocalRef<SWKSecurityOrigin> securityOrigin = SWKSecurityOrigin::create(origin);
    Native::LocalRef<CompletionHandler<int64_t>> handlerObject = CompletionHandler<int64_t>::create(completionHandler);
    if (!m_delegate->exceededDatabaseQuota(&m_webContent, securityOrigin, currentQuota, currentOriginUsage, currentDatabaseUsage, expectedUsage, handlerObject))
        completionHandler(currentQuota);
}

void UIClient::setWindowFrame(WebKit::WebPageProxy*, const FloatRect& rect)
{
    m_delegate->setWindowRect(&m_webContent, toRect(enclosingIntRect(rect)));
}

FloatRect UIClient::windowFrame(WebPageProxy* page)
{
    // FIXME: We need to re-implement this function based on a page.
    // Current implementation might not be able to support multiple windows.
    return FloatRect(fromRect(m_delegate->getWindowRect(&m_webContent)));
}

#if ENABLE(NETSCAPE_PLUGIN_API)
void UIClient::unavailablePluginButtonClicked(WebKit::WebPageProxy*, WKPluginUnavailabilityReason pluginUnavailabilityReason, API::Dictionary* pluginInformation)
{
    if (!pluginInformation || !pluginInformation->size())
        return;

    if (pluginUnavailabilityReason != kWKPluginUnavailabilityReasonPluginMissing)
        return;

    if (API::URL* url = pluginInformation->get<API::URL>(pluginInformationPluginspageAttributeURLKey()))
        m_delegate->didPressMissingPluginButton(url->string().utf8().data());
}
#endif // ENABLE(NETSCAPE_PLUGIN_API)

} // namespace WebKit
