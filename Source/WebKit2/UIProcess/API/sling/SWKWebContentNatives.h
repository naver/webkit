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

#ifndef SWKWebContent_h
#define SWKWebContent_h

#include "SWKWebContentNativesBase.h"

#include "PageClientSling.h"
#include "SWKBackForwardListNatives.h"
#include "SWKContextMenuItemNatives.h"
#include "SWKLoaderDelegateNatives.h"
#include "SWKPolicyDelegateNatives.h"
#include "SWKProcessPoolNatives.h"
#include "SWKUIDelegateNatives.h"
#include "SWKViewNatives.h"
#include "SWKWebContentConfigurationNatives.h"
#include "SharedBuffer.h"
#include "UIClient.h"
#include "ValueCallbackNatives.h"
#include "ViewController.h"
#include "WebContextMenuNatives.h"
#include "WebPrintInfoNatives.h"
#include <JavaScriptCore/JSContextRef.h>

namespace WebKit {

class ContextMenuClient;
class FindClient;
class LoaderClient;
class PolicyClient;
#if ENABLE(VIBRATION)
class VibrationProvider;
#endif

class SWKWebContent final : public Natives::SWKWebContent {
    friend class Natives::SWKWebContent;
public:
    ~SWKWebContent();

    WebPageProxy& webPage() const { return *m_page; }
    PageClientSling& pageClient() { return m_pageClient; }
    ViewController& view() { return m_viewController; }

    void processDidBecomeUnresponsive();
    void processDidBecomeResponsive();

    void handleDownloadRequest(DownloadProxy*);

    Native::PassLocalRef<Natives::SWKWebContentConfiguration> getConfiguration() override;

    void setUIDelegate(Native::PassLocalRef<Natives::SWKUIDelegate>) override;
    Native::PassLocalRef<Natives::SWKUIDelegate> getUIDelegate() override;
    void setLoaderDelegate(Native::PassLocalRef<Natives::SWKLoaderDelegate>) override;
    void setPolicyDelegate(Native::PassLocalRef<Natives::SWKPolicyDelegate>) override;

    Native::PassLocalRef<Natives::SWKBackForwardList> getBackForwardList() override;

    Native::PassLocalRef<Natives::SWKNavigation> loadRequest(Native::PassLocalRef<Natives::SWKURLRequest>) override;
    Native::PassLocalRef<Natives::SWKNavigation> loadHTMLString(const std::string&, const std::string&) override;
    Native::PassLocalRef<Natives::SWKNavigation> loadData(const std::string&, const std::string&, const std::string&, const std::string&) override;

    Native::PassLocalRef<Natives::SWKNavigation> goToBackForwardListItem(Native::PassLocalRef<Natives::SWKBackForwardListItem>) override;

    std::string getTitle() override;
    Native::PassLocalRef<Natives::SWKURL> getURL() override;
    Native::PassLocalRef<Natives::SWKURL> getUnreachableURL() override;

    bool canGoBack() override;
    bool canGoForward() override;
    Native::PassLocalRef<Natives::SWKNavigation> goBack() override;
    Native::PassLocalRef<Natives::SWKNavigation> goForward() override;
    Native::PassLocalRef<Natives::SWKNavigation> reload() override;
    Native::PassLocalRef<Natives::SWKNavigation> reloadFromOrigin() override;
    void stopLoading() override;

    void evaluateJavaScript(const std::string&, Native::PassLocalRef<Natives::ValueCallback>) override;

    std::string getCustomUserAgent() override;
    void setCustomUserAgent(const std::string&) override;
    std::string getCustomTextEncodingName() override;
    void setCustomTextEncodingName(const std::string&) override;

    Native::PassLocalRef<Natives::SWKView> createView() override;
    Native::PassLocalRef<Natives::SWKView> peekView() override;

    int32_t getContentWidth() override;
    int32_t getContentHeight() override;

    void tryClose() override;

    void restoreFromSessionState(Native::PassLocalRef<Natives::SWKSessionState> sessionState, bool navigate) override;
    void snapshotRect(Native::PassLocalRef<Natives::Rect>, float, Native::PassLocalRef<Natives::ValueCallback>) override;
    void computePagesForPrinting(Native::PassLocalRef<Natives::WebPrintInfo>, Native::PassLocalRef<Natives::ValueCallback>) override;
    void drawPagesToPDF(Native::PassLocalRef<Natives::WebPrintInfo>, int, int, Native::PassLocalRef<Natives::ValueCallback>) override;

    void findString(const std::string&, int32_t, int32_t) override;
    void countStringMatches(const std::string&, int32_t, int32_t) override;
    void selectFindMatch(int32_t) override;
    void hideFindUI() override;

    std::string getUserAgent() override;

    Native::PassLocalRef<Natives::SWKSessionState> getSessionState() override;

    void setTextZoomFactor(double textZoomFactor) override;
    double getTextZoomFactor() override;
    void setPageZoomFactor(double pageZoomFactor) override;
    double getPageZoomFactor() override;

    void setFindDelegate(Native::PassLocalRef<Natives::SWKFindDelegate>) override;
    Native::PassLocalRef<Natives::SWKFindDelegate> getFindDelegate() override;
    void setFormDelegate(Native::PassLocalRef<Natives::SWKFormDelegate>) override;

    void setContextMenuDelegate(Native::PassLocalRef<Natives::SWKContextMenuDelegate>) override;
    Native::PassLocalRef<Natives::SWKContextMenuDelegate> getContextMenuDelegate() override;
    void setSelectedContextMenuItem(Native::PassLocalRef<Natives::SWKContextMenuItem>) override;

    void showWebInspector(bool) override;
    void getContentsAsString(Native::PassLocalRef<Natives::ValueCallback>) override;
    void getContentsAsMHTMLData(Native::PassLocalRef<Natives::ValueCallback>) override;
    void getResourceDataFromFocusedFrame(Native::PassLocalRef<Natives::SWKURL> resourceURL, Native::PassLocalRef<Natives::ValueCallback>) override;

private:
    SWKWebContent(Native::PassLocalRef<Natives::Rect>, Native::PassLocalRef<SWKWebContentConfiguration>);

    void unresponsiveProcessWatchdogTimerFired();

    JSGlobalContextRef jsGlobalContext();

    Native::GlobalRef<SWKWebContentConfiguration> m_configuration;
    Native::GlobalRef<SWKProcessPool> m_processPool;
    RefPtr<WebPageGroup> m_pageGroup;
    PageClientSling m_pageClient;
    WebPageProxy* m_page;

    Native::GlobalRef<SWKBackForwardList> m_backForwardList;

    ViewController m_viewController;

    bool m_processDidBecomeUnresponsive;
    WebCore::Timer m_unresponsiveProcessWatchdogTimer;
    int32_t m_unresponsiveProcessWatchdogCounter;

    JSGlobalContextRef m_jsGlobalContext;
};

}

#endif // SWKWebContent_h
