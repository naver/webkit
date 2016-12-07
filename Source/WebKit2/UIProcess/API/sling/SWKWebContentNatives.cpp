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
#include "SWKWebContentNatives.h"

#include "APIData.h"
#include "CairoUtilities.h"
#include "ContextMenuClient.h"
#include "DownloadClient.h"
#include "FindClient.h"
#include "FormClient.h"
#include "LoaderClient.h"
#include "NativeWebCoreGraphics.h"
#include "PolicyClient.h"
#include "PrintInfo.h"
#include "SWKBackForwardListItemNatives.h"
#include "SWKDataNatives.h"
#include "SWKFormDelegateNatives.h"
#include "SWKNavigationNatives.h"
#include "SWKSessionStateNatives.h"
#include "SWKURLNatives.h"
#include "SWKURLRequestNatives.h"
#include "SWKWebContentConfigurationNatives.h"
#include "WKData.h"
#include "WebBackForwardList.h"
#include "WebBitmapNativesBase.h"
#include "WebCertificateInfo.h"
#include "WebInspectorProxy.h"
#include "WebKitServiceRunnerNativesBase.h"
#include "WebPrintInfoNatives.h"
#include <JavaScriptCore/JSRetainPtr.h>
#include <JavaScriptCore/JSStringRef.h>
#include <NativesRect.h>

#if ENABLE(VIBRATION)
#include "VibrationProvider.h"
#endif

using namespace WebCore;

namespace WebKit {

SWKWebContent::SWKWebContent(Native::PassLocalRef<Natives::Rect> frame, Native::PassLocalRef<SWKWebContentConfiguration> configuration)
    : m_configuration(configuration)
    , m_processPool(m_configuration->getProcessPool().as<SWKProcessPool>())
    , m_pageGroup(m_configuration->getOrCreatePageGroup())
    , m_pageClient(*this)
    , m_page(m_pageClient.page())
    , m_backForwardList(SWKBackForwardList::create(webPage().backForwardList()))
    , m_viewController(*this)
    , m_processDidBecomeUnresponsive(false)
    , m_unresponsiveProcessWatchdogTimer(*this, &SWKWebContent::unresponsiveProcessWatchdogTimerFired)
    , m_unresponsiveProcessWatchdogCounter(0)
    , m_jsGlobalContext(nullptr)
{
    if (!m_configuration->getApplicationNameForUserAgent().empty())
        m_page->setApplicationNameForUserAgent(m_configuration->getApplicationNameForUserAgent().c_str());

    if (frame && frame->width() > 0 && frame->height() > 0)
        m_pageClient.setSize(IntSize(frame->width(), frame->height()));

    // FIXME: Need to check if here is correct place to enable default preferences.
    // However default feature is not enabled when we set it at SWKPreferences::create().
    m_page->preferences().setDeveloperExtrasEnabled(true);
    m_page->preferences().setFullScreenEnabled(true);
    m_page->preferences().setOfflineWebApplicationCacheEnabled(true);
    m_page->preferences().setHiddenPageDOMTimerThrottlingEnabled(true);
    m_page->preferences().setHiddenPageCSSAnimationSuspensionEnabled(true);
    m_page->preferences().setUsesPageCache(false);
    m_page->preferences().setPageCacheSupportsPlugins(false);
}

SWKWebContent::~SWKWebContent()
{
    if (m_jsGlobalContext)
        JSGlobalContextRelease(m_jsGlobalContext);
}

void SWKWebContent::unresponsiveProcessWatchdogTimerFired()
{
    ASSERT(m_processDidBecomeUnresponsive);

    const pid_t processIdentifier = webPage().process().processIdentifier();
    if (!WebKit::Natives::WebKitServiceRunner::isProcessDisconnected(processIdentifier)) {
        static const int32_t maxUnresponsiveProcessWatchdogCounter = 20;
        if (++m_unresponsiveProcessWatchdogCounter < maxUnresponsiveProcessWatchdogCounter)
            return;

        WebKit::Natives::WebKitServiceRunner::unbindProcess(processIdentifier);
    }

    m_processDidBecomeUnresponsive = false;
    m_unresponsiveProcessWatchdogCounter = 0;

    m_unresponsiveProcessWatchdogTimer.stop();

    webPage().process().connection()->postConnectionDidCloseOnConnectionWorkQueue();
}

JSGlobalContextRef SWKWebContent::jsGlobalContext()
{
    if (!m_jsGlobalContext)
        m_jsGlobalContext = JSGlobalContextCreate(0);

    return m_jsGlobalContext;
}

void SWKWebContent::processDidBecomeUnresponsive()
{
    ASSERT(!m_processDidBecomeUnresponsive);
    ASSERT(!m_unresponsiveProcessWatchdogTimer.isActive());

    if (webPage().process().state() != ChildProcessProxy::State::Running)
        return;

    m_processDidBecomeUnresponsive = true;

    static const int32_t unresponsiveProcessWatchdogTimerIntervalInMilliseconds = 100;
    m_unresponsiveProcessWatchdogTimer.startRepeating(std::chrono::milliseconds(unresponsiveProcessWatchdogTimerIntervalInMilliseconds));
}

void SWKWebContent::processDidBecomeResponsive()
{
    ASSERT(m_processDidBecomeUnresponsive);

    m_processDidBecomeUnresponsive = false;
    m_unresponsiveProcessWatchdogCounter = 0;

    m_unresponsiveProcessWatchdogTimer.stop();
}

void SWKWebContent::handleDownloadRequest(DownloadProxy* download)
{
    notImplemented();
}

Native::PassLocalRef<Natives::SWKWebContentConfiguration> SWKWebContent::getConfiguration()
{
    return m_configuration;
}

void SWKWebContent::setUIDelegate(Native::PassLocalRef<Natives::SWKUIDelegate> uiDelegate)
{
    if (!uiDelegate) {
        webPage().setUIClient(nullptr);
        return;
    }

    webPage().setUIClient(std::make_unique<UIClient>(*this, uiDelegate));
}

Native::PassLocalRef<Natives::SWKUIDelegate> SWKWebContent::getUIDelegate()
{
    return static_cast<UIClient&>(webPage().uiClient()).delegate();
}

void SWKWebContent::setFormDelegate(Native::PassLocalRef<Natives::SWKFormDelegate> formDelegate)
{
    if (!formDelegate) {
        webPage().setFormClient(nullptr);
        return;
    }

    webPage().setFormClient(std::make_unique<FormClient>(*this, formDelegate));
}

void SWKWebContent::setLoaderDelegate(Native::PassLocalRef<Natives::SWKLoaderDelegate> loaderDelegate)
{
    if (!loaderDelegate) {
        webPage().setLoaderClient(nullptr);
        return;
    }

    webPage().setLoaderClient(std::make_unique<LoaderClient>(*this, loaderDelegate));
}

void SWKWebContent::setPolicyDelegate(Native::PassLocalRef<Natives::SWKPolicyDelegate> policyDelegate)
{
    if (!policyDelegate) {
        webPage().setPolicyClient(nullptr);
        return;
    }

    webPage().setPolicyClient(std::make_unique<PolicyClient>(*this, policyDelegate));
}

Native::PassLocalRef<Natives::SWKBackForwardList> SWKWebContent::getBackForwardList()
{
    return m_backForwardList;
}

Native::PassLocalRef<Natives::SWKNavigation> SWKWebContent::loadRequest(Native::PassLocalRef<Natives::SWKURLRequest> request)
{
    Native::LocalRef<SWKURL> url = request->getUrl();
    RefPtr<API::Navigation> navigation = webPage().loadRequest(ResourceRequest(String::fromUTF8(url->getAbsoluteString().c_str())));
    return SWKNavigation::create();
}

Native::PassLocalRef<Natives::SWKNavigation> SWKWebContent::loadHTMLString(const std::string& htmlString, const std::string& baseURL)
{
    RefPtr<API::Navigation> navigation = webPage().loadHTMLString(String::fromUTF8(htmlString.c_str()), String::fromUTF8(baseURL.c_str()));
    return SWKNavigation::create();
}

Native::PassLocalRef<Natives::SWKNavigation> SWKWebContent::loadData(const std::string& data, const std::string& MimeType, const std::string& characterEncodingName, const std::string& baseUrl)
{
    RefPtr<API::Data> htmlData = API::Data::create(reinterpret_cast<const unsigned char *>(data.c_str()), data.length());
    RefPtr<API::Navigation> navigation = webPage().loadData(htmlData.get(), String::fromUTF8(MimeType.c_str()), String::fromUTF8(characterEncodingName.c_str()), String::fromUTF8(baseUrl.c_str()));
    return SWKNavigation::create();
}

Native::PassLocalRef<Natives::SWKNavigation> SWKWebContent::goToBackForwardListItem(Native::PassLocalRef<Natives::SWKBackForwardListItem> item)
{
    RefPtr<API::Navigation> navigation = webPage().goToBackForwardItem(item.as<SWKBackForwardListItem>()->item());
    return SWKNavigation::create();
}

std::string SWKWebContent::getTitle()
{
    return webPage().pageLoadState().title().utf8().data();
}

Native::PassLocalRef<Natives::SWKURL> SWKWebContent::getURL()
{
    return SWKURL::createWithString(webPage().pageLoadState().activeURL());
}

Native::PassLocalRef<Natives::SWKURL> SWKWebContent::getUnreachableURL()
{
    return SWKURL::createWithString(webPage().pageLoadState().unreachableURL());
}

bool SWKWebContent::canGoBack()
{
    return webPage().backForwardList().backItem();
}

bool SWKWebContent::canGoForward()
{
    return webPage().backForwardList().forwardItem();
}

Native::PassLocalRef<Natives::SWKNavigation> SWKWebContent::goBack()
{
    RefPtr<API::Navigation> navigation = webPage().goBack();
    return SWKNavigation::create();
}

Native::PassLocalRef<Natives::SWKNavigation> SWKWebContent::goForward()
{
    RefPtr<API::Navigation> navigation = webPage().goForward();
    return SWKNavigation::create();
}

Native::PassLocalRef<Natives::SWKNavigation> SWKWebContent::reload()
{
    RefPtr<API::Navigation> navigation = webPage().reload(false, false);
    return SWKNavigation::create();
}

Native::PassLocalRef<Natives::SWKNavigation> SWKWebContent::reloadFromOrigin()
{
    RefPtr<API::Navigation> navigation = webPage().reload(true, false);
    return SWKNavigation::create();
}

void SWKWebContent::stopLoading()
{
    webPage().stopLoading();
}

void SWKWebContent::evaluateJavaScript(const std::string& javaScriptString, Native::PassLocalRef<Natives::ValueCallback> valueCallback)
{
    if (javaScriptString.empty())
        return;

    webPage().runJavaScriptInMainFrame(String::fromUTF8(javaScriptString.c_str()),
        [=] (API::SerializedScriptValue* scriptValue, bool hadException, const ExceptionDetails&, CallbackBase::Error error) {
            if (!valueCallback)
                return;

            // FIXME: Handle CallbackBase::Error and send it to valueCallback
            if (error != CallbackBase::Error::None || !scriptValue) {
                valueCallback->onReceiveString("");
                return;
            }

            JSValueRef value = scriptValue->deserialize(jsGlobalContext(), 0);
            JSRetainPtr<JSStringRef> stringValue(Adopt, JSValueToStringCopy(jsGlobalContext(), value, 0));
            size_t size = JSStringGetMaximumUTF8CStringSize(stringValue.get());
            auto cstring = std::make_unique<char[]>(size);
            JSStringGetUTF8CString(stringValue.get(), cstring.get(), size);
            valueCallback->onReceiveString(cstring.get());
        });
}

std::string SWKWebContent::getCustomUserAgent()
{
    return webPage().customUserAgent().utf8().data();
}

void SWKWebContent::setCustomUserAgent(const std::string& customUserAgent)
{
    webPage().setCustomUserAgent(String::fromUTF8(customUserAgent.c_str()));
}

std::string SWKWebContent::getCustomTextEncodingName()
{
    return webPage().customTextEncodingName().utf8().data();
}

void SWKWebContent::setCustomTextEncodingName(const std::string& customUserAgent)
{
    webPage().setCustomTextEncodingName(String::fromUTF8(customUserAgent.c_str(), customUserAgent.length()));
}

Native::PassLocalRef<Natives::SWKView> SWKWebContent::createView()
{
    return m_viewController.createView(this);
}

Native::PassLocalRef<Natives::SWKView> SWKWebContent::peekView()
{
    return m_viewController.view();
}

int32_t SWKWebContent::getContentWidth()
{
    return m_viewController.getContentSize().width();
}

int32_t SWKWebContent::getContentHeight()
{
    return m_viewController.getContentSize().height();
}

void SWKWebContent::tryClose()
{
    webPage().tryClose();
}

void SWKWebContent::restoreFromSessionState(Native::PassLocalRef<Natives::SWKSessionState> swkSessionState, bool navigate)
{
    WebKit::SessionState sessionState = swkSessionState.as<SWKSessionState>()->sessionState();
    webPage().restoreFromSessionState(WTFMove(sessionState), navigate);
}

void SWKWebContent::snapshotRect(Native::PassLocalRef<Natives::Rect> rectInViewCoordinates, float imageWidth, Native::PassLocalRef<Natives::ValueCallback> completionHandler)
{
    notImplemented();
}

static PrintInfo printInfoFromWebPrintInfo(Native::PassLocalRef<Natives::WebPrintInfo> printInfo)
{
    PrintInfo result;
    result.pageSetupScaleFactor = printInfo->mPageSetupScaleFactor.get();
    result.availablePaperWidth = printInfo->mAvailablePaperWidth.get();
    result.availablePaperHeight = printInfo->mAvailablePaperHeight.get();
    return result;
}

void SWKWebContent::computePagesForPrinting(Native::PassLocalRef<Natives::WebPrintInfo> printInfo, Native::PassLocalRef<Natives::ValueCallback> callback)
{
    webPage().computePagesForPrinting(webPage().mainFrame(), printInfoFromWebPrintInfo(printInfo), ComputedPagesCallback::create([callback](const Vector<WebCore::IntRect>& rects, double, CallbackBase::Error) {
        Vector<WKRect> wkRects(rects.size());
        for (size_t i = 0; i < rects.size(); ++i)
            wkRects[i] = toAPI(rects[i]);
        callback->onReceiveInt(wkRects.size());
    }));
}

void SWKWebContent::drawPagesToPDF(Native::PassLocalRef<Natives::WebPrintInfo> printInfo, int first, int count, Native::PassLocalRef<Natives::ValueCallback> callback)
{
    webPage().drawPagesToPDF(webPage().mainFrame(), printInfoFromWebPrintInfo(printInfo), first, count, DataCallback::create([callback](API::Data* data, CallbackBase::Error) {
        if (!data || !data->size())
            return;
        Native::ImmutableArray<int8_t> byteArray((int8_t*)(data->bytes()), data->size(), true);
        callback->onReceiveObject(Natives::SWKData::create(byteArray));
    }));
}

void SWKWebContent::findString(const std::string& string, int32_t options, int32_t maxCount)
{
    FindOptions findOption = static_cast<FindOptions>(options);
    webPage().findString(String::fromUTF8(string.c_str()), findOption, maxCount);
}

void SWKWebContent::countStringMatches(const std::string& string, int32_t options, int32_t maxCount)
{
    webPage().findStringMatches(String::fromUTF8(string.c_str()), static_cast<FindOptions>(options), maxCount);
}

void SWKWebContent::selectFindMatch(int32_t matchIndex)
{
    webPage().selectFindMatch(matchIndex);
}

void SWKWebContent::hideFindUI()
{
    webPage().hideFindUI();
}

std::string SWKWebContent::getUserAgent()
{
    return webPage().userAgent().utf8().data();
}

Native::PassLocalRef<Natives::SWKSessionState> SWKWebContent::getSessionState()
{
    return SWKSessionState::create(webPage().sessionState(nullptr));
}

void SWKWebContent::setTextZoomFactor(double textZoomFactor)
{
    webPage().setTextZoomFactor(textZoomFactor);
}

double SWKWebContent::getTextZoomFactor()
{
    return webPage().textZoomFactor();
}

void SWKWebContent::setPageZoomFactor(double pageZoomFactor)
{
    webPage().setPageZoomFactor(pageZoomFactor);
}

double SWKWebContent::getPageZoomFactor()
{
    return webPage().pageZoomFactor();
}

void SWKWebContent::setFindDelegate(Native::PassLocalRef<Natives::SWKFindDelegate> findDelegate)
{
    if (!findDelegate) {
        webPage().setFindClient(nullptr);
        return;
    }

    webPage().setFindClient(std::make_unique<FindClient>(*this, findDelegate));
}

Native::PassLocalRef<Natives::SWKFindDelegate> SWKWebContent::getFindDelegate()
{
    return static_cast<FindClient&>(webPage().findClient()).delegate();
}

void SWKWebContent::setContextMenuDelegate(Native::PassLocalRef<Natives::SWKContextMenuDelegate> contextMenuDelegate)
{
    if (!contextMenuDelegate) {
        webPage().setContextMenuClient(nullptr);
        return;
    }

    webPage().setContextMenuClient(std::make_unique<ContextMenuClient>(*this, contextMenuDelegate));
}

Native::PassLocalRef<Natives::SWKContextMenuDelegate> SWKWebContent::getContextMenuDelegate()
{
    return static_cast<ContextMenuClient&>(webPage().contextMenuClient()).delegate();
}

void SWKWebContent::setSelectedContextMenuItem(Native::PassLocalRef<Natives::SWKContextMenuItem> item)
{
    webPage().contextMenuItemSelected(item.as<::WebKit::SWKContextMenuItem>()->kitItem());
}

void SWKWebContent::showWebInspector(bool show)
{
    WebInspectorProxy* inspector = webPage().inspector();
    if (!inspector)
        return;

    if (show)
        inspector->show();
    else
        inspector->close();
}

static int32_t toError(CallbackBase::Error error)
{
    switch (error) {
    case CallbackBase::Error::Unknown:
        return Natives::ValueCallback::ERROR_UNKNOWN;
    case CallbackBase::Error::ProcessExited:
        return Natives::ValueCallback::ERROR_PROCESS_EXITED;
    case CallbackBase::Error::OwnerWasInvalidated:
        return Natives::ValueCallback::ERROR_OWNER_WAS_INVALIDATED;
    }

    return Natives::ValueCallback::ERROR_UNKNOWN;
}

void SWKWebContent::getContentsAsString(Native::PassLocalRef<Natives::ValueCallback> callback)
{
    webPage().getContentsAsString([callback](const String& content, CallbackBase::Error error) {
        if (error != CallbackBase::Error::None) {
            callback->onReceiveError(toError(error));
            return;
        }

        CString utf8Content = content.utf8();
        callback->onReceiveString(std::string(utf8Content.data(), utf8Content.length()));
    });
}

void SWKWebContent::getContentsAsMHTMLData(Native::PassLocalRef<Natives::ValueCallback> callback)
{
#if ENABLE(MHTML)
    webPage().getContentsAsMHTMLData([callback](API::Data* data, CallbackBase::Error) {
        if (!data || !data->size())
            return;
        Native::ImmutableArray<int8_t> byteArray((int8_t*)(data->bytes()), data->size(), true);
        callback->onReceiveObject(Natives::SWKData::create(byteArray));
    });
#endif
}

void SWKWebContent::getResourceDataFromFocusedFrame(Native::PassLocalRef<Natives::SWKURL> resourceURL, Native::PassLocalRef<Natives::ValueCallback> callback)
{
    std::string absoulteURLString = resourceURL->getAbsoluteString();
    webPage().getResourceDataFromFrame(
        webPage().focusedFrame(),
        API::URL::create(String::fromUTF8(absoulteURLString.c_str())).ptr(),
        [callback](API::Data* data, CallbackBase::Error) {
            if (!data || !data->size())
                return;
            Native::ImmutableArray<int8_t> byteArray((int8_t*)(data->bytes()), data->size(), true);
            callback->onReceiveObject(Natives::SWKData::create(byteArray));
        });
}

namespace Natives {

SWKWebContent* SWKWebContent::nativeCreate(Native::PassLocalRef<Natives::Rect> frame, Native::PassLocalRef<Natives::SWKWebContentConfiguration> configuration)
{
    // FIXME: Consider to copy configuration
    return new ::WebKit::SWKWebContent(frame, configuration.as<::WebKit::SWKWebContentConfiguration>());
}

} // namespace Natives
} // namespace WebKit
