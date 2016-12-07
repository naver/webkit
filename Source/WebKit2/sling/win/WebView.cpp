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
#include "WebKitDLLMain.h"
#include "WebView.h"

#include "Assertions.h"
#include "WebFrame.h"
#include <win/GDIUtilities.h>

#include "WebKitTestRunnerSupport.h"
#include "SWKProcessPool.h"
#include "SWKURLRequest.h"
#include "SWKView.h"
#include "SWKWebContent.h"
#include "SWKWebContentConfiguration.h"
#include "WebMutableURLRequest.h"
#include "WebViewContext.h"
#include <util/StringConversion.h>
#include <view/ContentFrame.h>
#include <view/ViewHostWindow.h>

#include <memory>

using namespace view;
using namespace webkit;

class WebMainFrame : public WebFrame
{
public:
    static WebMainFrame* createInstance(WebView&);
protected:
    WebMainFrame(WebView&);
    ~WebMainFrame() { }

    friend class WebView;

public:
    // IWebFrame
    virtual HRESULT STDMETHODCALLTYPE loadRequest(_In_opt_ IWebURLRequest*);
    virtual HRESULT STDMETHODCALLTYPE loadData(_In_opt_ IStream* data, _In_ BSTR mimeType, _In_ BSTR textEncodingName, _In_ BSTR url);
    virtual HRESULT STDMETHODCALLTYPE loadHTMLString(_In_ BSTR, _In_ BSTR baseURL);
    virtual HRESULT STDMETHODCALLTYPE loadAlternateHTMLString(_In_ BSTR, _In_ BSTR baseURL, _In_ BSTR unreachableURL);
    virtual HRESULT STDMETHODCALLTYPE loadArchive(_In_opt_ IWebArchive*);
    virtual HRESULT STDMETHODCALLTYPE dataSource(_COM_Outptr_opt_ IWebDataSource**);
    virtual HRESULT STDMETHODCALLTYPE provisionalDataSource(_COM_Outptr_opt_ IWebDataSource**);
    virtual HRESULT STDMETHODCALLTYPE stopLoading();
    virtual HRESULT STDMETHODCALLTYPE reload();

    // IWebFramePrivate
    virtual HRESULT STDMETHODCALLTYPE reloadFromOrigin();
    virtual HRESULT STDMETHODCALLTYPE loadPlainTextString(_In_ BSTR, _In_ BSTR url);
    virtual HRESULT STDMETHODCALLTYPE stringByEvaluatingJavaScriptInScriptWorld(IWebScriptWorld*, JSObjectRef, BSTR script, BSTR* evaluationResult);
    virtual JSGlobalContextRef STDMETHODCALLTYPE globalContextForScriptWorld(IWebScriptWorld*);
    virtual HRESULT STDMETHODCALLTYPE clearOpener();

    // IWebFrame2:
    virtual HRESULT STDMETHODCALLTYPE isMainFrame(_Out_ BOOL*);

    // WebMainFrame
    HRESULT initWithFrame(RECT frame, _In_ BSTR frameName, _In_ BSTR groupName);

private:
    WebView& m_webView;
    std::unique_ptr<ViewHostWindow> m_window;
    std::shared_ptr<ContentFrame> m_contentFrame;
    std::shared_ptr<SWKWebContentConfiguration> m_webContentConfiguration;
    std::shared_ptr<SWKWebContent> m_webContent;
    std::shared_ptr<SWKView> m_view;
};

WebMainFrame::WebMainFrame(WebView& webView)
    : m_webView(webView)
{
}

WebMainFrame* WebMainFrame::createInstance(WebView& webView)
{
    WebMainFrame* instance = new WebMainFrame(webView);
    instance->AddRef();
    return instance;
}

static std::string injectedBundlePath()
{
    static const DWORD maxInjectedBundlePathLength = 2048;
    static const char injectedBundlePathVariableKey[] = "BUNDLE_PATH";

    char injectedBundlePathVariableValue[maxInjectedBundlePathLength] = { 0, };
    if (!GetEnvironmentVariableA(injectedBundlePathVariableKey, injectedBundlePathVariableValue, maxInjectedBundlePathLength))
        return "";

    return std::string(injectedBundlePathVariableValue);
}

static std::shared_ptr<SWKWebContentConfiguration> createConfiguration(std::shared_ptr<SWKProcessPool> processPool)
{
    std::shared_ptr<SWKWebContentConfiguration> configuration = SWKWebContentConfiguration::create();
    configuration->setProcessPool(processPool);
    return configuration;
}

static std::shared_ptr<SWKWebContentConfiguration> defaultConfiguration()
{
    static std::shared_ptr<SWKProcessPool> processPool = SWKProcessPool::create(injectedBundlePath());
    static std::shared_ptr<SWKWebContentConfiguration> configuration = createConfiguration(processPool);
    return configuration;
}

HRESULT WebMainFrame::initWithFrame(RECT frame, _In_ BSTR frameName, _In_ BSTR groupName)
{
    m_window = ViewHostWindow::create(m_webView.m_hostWindow, frame);
    m_contentFrame = ContentFrame::create();
    m_window->setContentView(m_contentFrame);

    WKPageConfiguration* pageConfiguration = m_webView.m_pageConfigurationLeakedPtr;
    if (pageConfiguration)
        m_webContentConfiguration = std::static_pointer_cast<SWKWebContentConfiguration>(WebKitTestRunnerSupport::createConfiguration(reinterpret_cast<int64_t>(pageConfiguration)));

    if (!m_webContentConfiguration)
        m_webContentConfiguration = defaultConfiguration();

    std::shared_ptr<WebKit::Managed::Rect> frameRect = WebKit::Managed::Rect::create(frame.left, frame.top, frame.right, frame.bottom);
    m_webContent = SWKWebContent::create<SWKWebContent>(frameRect, m_webContentConfiguration);
    m_view = std::static_pointer_cast<SWKView>(m_webContent->createView());
    
    std::shared_ptr<ViewContext> webViewContext = WebViewContext::create(m_view);
    m_contentFrame->contentView().addView(webViewContext);
    webViewContext->setVisible(true);

    m_view->setMotionDetectionDisabled(true);

    return S_OK;
}

//IWebFrame
HRESULT WebMainFrame::loadRequest(_In_opt_ IWebURLRequest* request)
{
    if (!request)
        return E_INVALIDARG;

    if (!m_webContent)
        return E_FAIL;

    HRESULT hr;
    COMPtr<WebMutableURLRequest> mutableRequest;
    hr = request->QueryInterface(CLSID_WebMutableURLRequest, (void**)&mutableRequest.GetInterfacePtr());
    if (FAILED(hr))
        return hr;

    std::shared_ptr<SWKURLRequest> urlRequest = std::static_pointer_cast<SWKURLRequest>(mutableRequest->kit());
    if (!urlRequest)
        return E_FAIL;

    m_webContent->loadRequest(urlRequest);
    return S_OK;
}

HRESULT WebMainFrame::loadData(_In_opt_ IStream* data, _In_ BSTR mimeType, _In_ BSTR textEncodingName, _In_ BSTR url)
{
    return E_NOTIMPL;
}

HRESULT WebMainFrame::loadHTMLString(_In_ BSTR htmlString, _In_ BSTR baseURL)
{
    if (!m_webContent)
        return E_FAIL;

    std::wstring html((!htmlString) ? L"" : htmlString);
    std::wstring url((!baseURL) ? L"" : baseURL);
    m_webContent->loadHTMLString(std::ws2s(html), std::ws2s(url));
    return S_OK;
}

HRESULT WebMainFrame::loadAlternateHTMLString(_In_ BSTR, _In_ BSTR baseURL, _In_ BSTR unreachableURL)
{
    return E_NOTIMPL;
}

HRESULT WebMainFrame::loadArchive(_In_opt_ IWebArchive*)
{
    return E_NOTIMPL;
}

HRESULT WebMainFrame::dataSource(_COM_Outptr_opt_ IWebDataSource**)
{
    return E_NOTIMPL;
}

HRESULT WebMainFrame::provisionalDataSource(_COM_Outptr_opt_ IWebDataSource**)
{
    return E_NOTIMPL;
}

HRESULT WebMainFrame::stopLoading()
{
    return E_NOTIMPL;
}

HRESULT WebMainFrame::reload()
{
    return E_NOTIMPL;
}

// IWebFramePrivate
HRESULT WebMainFrame::reloadFromOrigin()
{
    return E_NOTIMPL;
}

HRESULT WebMainFrame::loadPlainTextString(_In_ BSTR, _In_ BSTR url)
{
    return E_NOTIMPL;
}

HRESULT WebMainFrame::stringByEvaluatingJavaScriptInScriptWorld(IWebScriptWorld*, JSObjectRef, BSTR script, BSTR* evaluationResult)
{
    return E_NOTIMPL;
}

JSGlobalContextRef WebMainFrame::globalContextForScriptWorld(IWebScriptWorld*)
{
    return nullptr;
}

HRESULT WebMainFrame::clearOpener()
{
    return E_NOTIMPL;
}

// IWebFrame2:
HRESULT WebMainFrame::isMainFrame(_Out_ BOOL*)
{
    return E_NOTIMPL;
}

// WebView ----------------------------------------------------------------

WebView::WebView()
{
    gClassCount++;
}

WebView::~WebView()
{
    gClassCount--;
}

WebView* WebView::createInstance()
{
    WebView* instance = new WebView();
    instance->AddRef();
    return instance;
}

HRESULT WebView::close()
{
    return E_NOTIMPL;
}

// IUnknown -------------------------------------------------------------------

HRESULT WebView::QueryInterface(_In_ REFIID riid, _COM_Outptr_ void** ppvObject)
{
    if (!ppvObject)
        return E_POINTER;
    *ppvObject = nullptr;
    if (IsEqualGUID(riid, CLSID_WebView))
        *ppvObject = this;
    else if (IsEqualGUID(riid, IID_IUnknown))
        *ppvObject = static_cast<IWebView*>(this);
    else if (IsEqualGUID(riid, IID_IWebView))
        *ppvObject = static_cast<IWebView*>(this);
    else if (IsEqualGUID(riid, IID_IWebViewPrivate))
        *ppvObject = static_cast<IWebViewPrivate*>(this);
    else if (IsEqualGUID(riid, IID_IWebViewPrivate2))
        *ppvObject = static_cast<IWebViewPrivate2*>(this);
    else if (IsEqualGUID(riid, IID_IWebViewPrivate3))
        *ppvObject = static_cast<IWebViewPrivate3*>(this);
    else if (IsEqualGUID(riid, IID_IWebIBActions))
        *ppvObject = static_cast<IWebIBActions*>(this);
    else if (IsEqualGUID(riid, IID_IWebViewCSS))
        *ppvObject = static_cast<IWebViewCSS*>(this);
    else if (IsEqualGUID(riid, IID_IWebViewEditing))
        *ppvObject = static_cast<IWebViewEditing*>(this);
    else if (IsEqualGUID(riid, IID_IWebViewUndoableEditing))
        *ppvObject = static_cast<IWebViewUndoableEditing*>(this);
    else if (IsEqualGUID(riid, IID_IWebViewEditingActions))
        *ppvObject = static_cast<IWebViewEditingActions*>(this);
    else if (IsEqualGUID(riid, IID_IWebNotificationObserver))
        *ppvObject = static_cast<IWebNotificationObserver*>(this);
    else if (IsEqualGUID(riid, IID_IDropTarget))
        *ppvObject = static_cast<IDropTarget*>(this);
    else if (IsEqualGUID(riid, IID_ITestRunnerWebView))
        *ppvObject = static_cast<ITestRunnerWebView*>(this);
    else
        return E_NOINTERFACE;

    AddRef();
    return S_OK;
}

ULONG WebView::AddRef()
{
    return ++m_refCount;
}

ULONG WebView::Release()
{
    if (m_refCount == 1) {
        // Call close() now so that clients don't have to. (It's harmless to call close() multiple
        // times.) We do this here instead of in our destructor because close() can cause AddRef()
        // and Release() to be called, and if that happened in our destructor we would be destroyed
        // more than once.
        close();
    }

    ULONG newRef = --m_refCount;
    if (!newRef) {
        delete(this);
    }

    return newRef;
}

// IWebView --------------------------------------------------------------------

HRESULT WebView::canShowMIMEType(_In_ BSTR mimeType, _Out_ BOOL* canShow)
{
    if (!canShow)
        return E_POINTER;

    *canShow = true;

    return E_NOTIMPL;
}

HRESULT WebView::canShowMIMETypeAsHTML(_In_ BSTR mimeType, _Out_ BOOL* canShow)
{
    if (!canShow)
        return E_POINTER;

    *canShow = false;

    return E_NOTIMPL;
}

HRESULT WebView::MIMETypesShownAsHTML(_COM_Outptr_opt_ IEnumVARIANT** enumVariant)
{
    ASSERT_NOT_REACHED();
    if (!enumVariant)
        return E_POINTER;
    *enumVariant = nullptr;
    return E_NOTIMPL;
}

HRESULT WebView::setMIMETypesShownAsHTML(__inout_ecount_full(cMimeTypes) BSTR* mimeTypes, int cMimeTypes)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

HRESULT WebView::URLFromPasteboard(_In_opt_ IDataObject* /*pasteboard*/, _Deref_opt_out_ BSTR* /*url*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

HRESULT WebView::URLTitleFromPasteboard(_In_opt_ IDataObject* /*pasteboard*/, _Deref_opt_out_ BSTR* /*urlTitle*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

HRESULT WebView::initWithFrame(RECT frame, _In_ BSTR frameName, _In_ BSTR groupName)
{
    ASSERT(!m_mainFrame);
    WebMainFrame* webFrame = WebMainFrame::createInstance(*this);
    m_mainFrame = webFrame;
    webFrame->initWithFrame(frame, frameName, groupName);
    webFrame->Release();
    return S_OK;
}

HRESULT WebView::setAccessibilityDelegate(_In_opt_ IAccessibilityDelegate* d)
{
    m_accessibilityDelegate = d;
    return S_OK;
}

HRESULT WebView::accessibilityDelegate(_COM_Outptr_opt_ IAccessibilityDelegate** d)
{
    if (!d)
        return E_POINTER;
    *d = m_accessibilityDelegate;
    return S_OK;
}

HRESULT WebView::setUIDelegate(_In_opt_ IWebUIDelegate* d)
{
    m_uiDelegate = d;
    return S_OK;
}

HRESULT WebView::uiDelegate(_COM_Outptr_opt_ IWebUIDelegate** d)
{
    if (!d)
        return E_POINTER;
    *d = m_uiDelegate;
    return S_OK;
}

HRESULT WebView::setResourceLoadDelegate(_In_opt_ IWebResourceLoadDelegate* d)
{
    m_resourceLoadDelegate = d;
    return S_OK;
}

HRESULT WebView::resourceLoadDelegate(_COM_Outptr_opt_ IWebResourceLoadDelegate** d)
{
    if (!d)
        return E_POINTER;
    *d = m_resourceLoadDelegate;
    return S_OK;
}

HRESULT WebView::setDownloadDelegate(_In_opt_ IWebDownloadDelegate* d)
{
    m_downloadDelegate = d;
    return S_OK;
}

HRESULT WebView::downloadDelegate(_COM_Outptr_opt_ IWebDownloadDelegate** d)
{
    if (!d)
        return E_POINTER;
    *d = m_downloadDelegate;
    return S_OK;
}

HRESULT WebView::setFrameLoadDelegate(_In_opt_ IWebFrameLoadDelegate* d)
{
    m_frameLoadDelegate = d;
    return S_OK;
}

HRESULT WebView::frameLoadDelegate(_COM_Outptr_opt_ IWebFrameLoadDelegate** d)
{
    if (!d)
        return E_POINTER;
    *d = m_frameLoadDelegate;
    return S_OK;
}

HRESULT WebView::setPolicyDelegate(_In_opt_ IWebPolicyDelegate* d)
{
    return E_NOTIMPL;
}

HRESULT WebView::policyDelegate(_COM_Outptr_opt_ IWebPolicyDelegate** d)
{
    if (!d)
        return E_POINTER;
    *d = nullptr;
    return E_NOTIMPL;
}

HRESULT WebView::mainFrame(_COM_Outptr_opt_ IWebFrame** frame)
{
    if (!frame) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *frame = m_mainFrame;
    if (!m_mainFrame)
        return E_UNEXPECTED;

    m_mainFrame->AddRef();
    return S_OK;
}

HRESULT WebView::focusedFrame(_COM_Outptr_opt_ IWebFrame** frame)
{
    return E_NOTIMPL;
}

HRESULT WebView::backForwardList(_COM_Outptr_opt_ IWebBackForwardList** list)
{
    if (!list) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }
    *list = nullptr;
    return E_NOTIMPL;
}

HRESULT WebView::setMaintainsBackForwardList(BOOL flag)
{
    return E_NOTIMPL;
}

HRESULT WebView::goBack(_Out_ BOOL* succeeded)
{
    if (!succeeded)
        return E_POINTER;

    *succeeded = FALSE;
    return E_NOTIMPL;
}

HRESULT WebView::goForward(_Out_ BOOL* succeeded)
{
    if (!succeeded)
        return E_POINTER;

    *succeeded = FALSE;
    return E_NOTIMPL;
}

HRESULT WebView::goToBackForwardItem(_In_opt_ IWebHistoryItem* item, _Out_ BOOL* succeeded)
{
    if (!item)
        return E_FAIL;

    if (!succeeded)
        return E_POINTER;

    *succeeded = FALSE;

    return E_NOTIMPL;
}

HRESULT WebView::setTextSizeMultiplier(float multiplier)
{
    return E_NOTIMPL;
}

HRESULT WebView::setPageSizeMultiplier(float multiplier)
{
    return E_NOTIMPL;
}

HRESULT WebView::textSizeMultiplier(_Out_ float* multiplier)
{
    if (!multiplier)
        return E_POINTER;

    *multiplier = 1.0f;
    return E_NOTIMPL;
}

HRESULT WebView::pageSizeMultiplier(_Out_ float* multiplier)
{
    if (!multiplier)
        return E_POINTER;

    *multiplier = 1.0f;
    return E_NOTIMPL;
}

HRESULT WebView::setApplicationNameForUserAgent(_In_ BSTR applicationName)
{
    return E_NOTIMPL;
}

HRESULT WebView::applicationNameForUserAgent(_Deref_opt_out_ BSTR* applicationName)
{
    if (!applicationName)
        return E_POINTER;

    return E_NOTIMPL;
}

HRESULT WebView::setCustomUserAgent(_In_ BSTR userAgentString)
{
    return E_NOTIMPL;
}

HRESULT WebView::customUserAgent(_Deref_opt_out_ BSTR* userAgentString)
{
    if (!userAgentString)
        return E_POINTER;

    return E_NOTIMPL;
}

HRESULT WebView::userAgentForURL(_In_ BSTR url, _Deref_opt_out_ BSTR* userAgent)
{
    if (!userAgent)
        return E_POINTER;

    return E_NOTIMPL;
}

HRESULT WebView::supportsTextEncoding(_Out_ BOOL* supports)
{
    if (!supports)
        return E_POINTER;

    *supports = TRUE;
    return E_NOTIMPL;
}

HRESULT WebView::setCustomTextEncodingName(_In_ BSTR encodingName)
{
    return E_NOTIMPL;
}

HRESULT WebView::customTextEncodingName(_Deref_opt_out_ BSTR* encodingName)
{
    if (!encodingName)
        return E_POINTER;

    return E_NOTIMPL;
}

HRESULT WebView::setMediaStyle(_In_ BSTR /*media*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

HRESULT WebView::mediaStyle(_Deref_opt_out_ BSTR* /*media*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

HRESULT WebView::stringByEvaluatingJavaScriptFromString(_In_ BSTR script, // assumes input does not have "JavaScript" at the begining.
    _Deref_opt_out_ BSTR* result)
{
    if (!result) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *result = nullptr;

    return E_NOTIMPL;
}

HRESULT WebView::windowScriptObject(_COM_Outptr_opt_ IWebScriptObject** webScriptObject)
{
    ASSERT_NOT_REACHED();
    if (!webScriptObject)
        return E_POINTER;
    *webScriptObject = nullptr;
    return E_NOTIMPL;
}

HRESULT WebView::setPreferences(_In_opt_ IWebPreferences* prefs)
{
    return E_NOTIMPL;
}

HRESULT WebView::preferences(_COM_Outptr_opt_ IWebPreferences** prefs)
{
    if (!prefs)
        return E_POINTER;
    return E_NOTIMPL;
}

HRESULT WebView::setPreferencesIdentifier(_In_ BSTR /*anIdentifier*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

HRESULT WebView::preferencesIdentifier(_Deref_opt_out_ BSTR* /*anIdentifier*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

HRESULT WebView::setHostWindow(_In_ HWND window)
{
    ASSERT(!m_mainFrame);
    m_hostWindow = window;
    return S_OK;
}

HRESULT WebView::hostWindow(_Deref_opt_out_ HWND* window)
{
    if (!window)
        return E_POINTER;

    *window = m_hostWindow;
    return E_NOTIMPL;
}

HRESULT WebView::searchFor(_In_ BSTR str, BOOL forward, BOOL caseFlag, BOOL wrapFlag, _Out_ BOOL* found)
{
    if (!found)
        return E_INVALIDARG;
    
    if (!str || !SysStringLen(str))
        return E_INVALIDARG;

    *found = FALSE;
    return E_NOTIMPL;
}

HRESULT WebView::updateFocusedAndActiveState()
{
    return E_NOTIMPL;
}

HRESULT WebView::executeCoreCommandByName(_In_ BSTR name, _In_ BSTR value)
{
    return E_NOTIMPL;
}

HRESULT WebView::clearMainFrameName()
{
    return E_NOTIMPL;
}

HRESULT WebView::markAllMatchesForText(_In_ BSTR str, BOOL caseSensitive, BOOL highlight, UINT limit, _Out_ UINT* matches)
{
    if (!matches)
        return E_INVALIDARG;

    if (!str || !SysStringLen(str))
        return E_INVALIDARG;

    *matches = 0;
    return E_NOTIMPL;
}

HRESULT WebView::unmarkAllTextMatches()
{
    return E_NOTIMPL;
}

HRESULT WebView::rectsForTextMatches(_COM_Outptr_opt_ IEnumTextMatches** pmatches)
{
    if (!pmatches)
        return E_POINTER;
    *pmatches = nullptr;
    return E_NOTIMPL;
}

HRESULT WebView::generateSelectionImage(BOOL forceWhiteText, _Deref_opt_out_ HBITMAP* hBitmap)
{
    if (!hBitmap)
        return E_POINTER;

    *hBitmap = nullptr;
    return E_NOTIMPL;
}

HRESULT WebView::selectionRect(_Inout_ RECT* rc)
{
    if (!rc)
        return E_POINTER;

    return E_NOTIMPL;
}

HRESULT WebView::registerViewClass(_In_opt_ IWebDocumentView*, _In_opt_ IWebDocumentRepresentation*, _In_ BSTR /*forMIMEType*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

HRESULT WebView::setGroupName(_In_ BSTR groupName)
{
    return E_NOTIMPL;
}
    
HRESULT WebView::groupName(_Deref_opt_out_ BSTR* groupName)
{
    if (!groupName)
        return E_POINTER;

    *groupName = nullptr;
    return E_NOTIMPL;
}
    
HRESULT WebView::estimatedProgress(_Out_ double* estimatedProgress)
{
    if (!estimatedProgress)
        return E_POINTER;
    *estimatedProgress = 1.0;
    return E_NOTIMPL;
}
    
HRESULT WebView::isLoading(_Out_ BOOL* isLoading)
{
    if (!isLoading)
        return E_POINTER;

    *isLoading = FALSE;

    return E_NOTIMPL;
}
    
HRESULT WebView::elementAtPoint(_In_ LPPOINT point, _COM_Outptr_opt_ IPropertyBag** elementDictionary)
{
    if (!elementDictionary || !point) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *elementDictionary = nullptr;

    return E_NOTIMPL;
}
    
HRESULT WebView::pasteboardTypesForSelection(_COM_Outptr_opt_ IEnumVARIANT** enumVariant)
{
    ASSERT_NOT_REACHED();
    if (!enumVariant)
        return E_POINTER;
    *enumVariant = nullptr;
    return E_NOTIMPL;
}
    
HRESULT WebView::writeSelectionWithPasteboardTypes(__inout_ecount_full(cTypes) BSTR* types, int cTypes, _In_opt_ IDataObject* /*pasteboard*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::pasteboardTypesForElement(_In_opt_ IPropertyBag* /*elementDictionary*/, _COM_Outptr_opt_ IEnumVARIANT** enumVariant)
{
    ASSERT_NOT_REACHED();
    if (!enumVariant)
        return E_POINTER;
    *enumVariant = nullptr;
    return E_NOTIMPL;
}
    
HRESULT WebView::writeElement(_In_opt_ IPropertyBag* /*elementDictionary*/, __inout_ecount_full(cWithPasteboardTypes) BSTR* withPasteboardTypes, int cWithPasteboardTypes, _In_opt_ IDataObject* /*pasteboard*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::selectedText(_Deref_opt_out_ BSTR* text)
{
    if (!text) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *text = nullptr;

    return E_NOTIMPL;
}

HRESULT WebView::centerSelectionInVisibleArea(_In_opt_ IUnknown* /* sender */)
{
    return E_NOTIMPL;
}

HRESULT WebView::moveDragCaretToPoint(_In_ LPPOINT /*point*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::removeDragCaret()
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::setDrawsBackground(BOOL /*drawsBackground*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::drawsBackground(_Out_ BOOL* /*drawsBackground*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::setMainFrameURL(_In_ BSTR /*urlString*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::mainFrameURL(_Deref_opt_out_ BSTR* urlString)
{
    if (!urlString)
        return E_POINTER;

    return E_NOTIMPL;
}
    
HRESULT WebView::mainFrameDocument(_COM_Outptr_opt_ IDOMDocument** document)
{
    if (!document)
        return E_POINTER;

    *document = nullptr;

    return E_NOTIMPL;
}
    
HRESULT WebView::mainFrameTitle(_Deref_opt_out_ BSTR* /*title*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::mainFrameIcon(_Deref_opt_out_ HBITMAP* /*hBitmap*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

HRESULT WebView::registerURLSchemeAsLocal(_In_ BSTR scheme)
{
    if (!scheme)
        return E_POINTER;

    return E_NOTIMPL;
}

// IWebIBActions ---------------------------------------------------------------

HRESULT WebView::takeStringURLFrom(_In_opt_ IUnknown* /*sender*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::stopLoading(_In_opt_ IUnknown* /*sender*/)
{
    return E_NOTIMPL;
}
    
HRESULT WebView::reload(_In_opt_ IUnknown* /*sender*/)
{
    return E_NOTIMPL;
}
    
HRESULT WebView::canGoBack(_In_opt_ IUnknown* /*sender*/, _Out_ BOOL* result)
{
    if (!result)
        return E_POINTER;

    *result = FALSE;
    return E_NOTIMPL;
}
    
HRESULT WebView::goBack(_In_opt_ IUnknown* /*sender*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::canGoForward(_In_opt_ IUnknown* /*sender*/, _Out_ BOOL* result)
{
    if (!result)
        return E_POINTER;
    
    *result = FALSE;
    return E_NOTIMPL;
}
    
HRESULT WebView::goForward(_In_opt_ IUnknown* /*sender*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

HRESULT WebView::canMakeTextLarger(_In_opt_ IUnknown* /*sender*/, _Out_ BOOL* result)
{
    if (!result)
        return E_POINTER;

    *result = FALSE;
    return E_NOTIMPL;
}

HRESULT WebView::canZoomPageIn(_In_opt_ IUnknown* /*sender*/, _Out_ BOOL* result)
{
    if (!result)
        return E_POINTER;

    *result = FALSE;
    return E_NOTIMPL;
}

HRESULT WebView::makeTextLarger(_In_opt_ IUnknown* /*sender*/)
{
    return E_NOTIMPL;
}

HRESULT WebView::zoomPageIn(_In_opt_ IUnknown* /*sender*/)
{
    return E_NOTIMPL;
}

HRESULT WebView::canMakeTextSmaller(_In_opt_ IUnknown* /*sender*/, _Out_ BOOL* result)
{
    if (!result)
        return E_POINTER;

    *result = FALSE;
    return E_NOTIMPL;
}

HRESULT WebView::canZoomPageOut(_In_opt_ IUnknown* /*sender*/, _Out_ BOOL* result)
{
    if (!result)
        return E_POINTER;

    *result = FALSE;
    return E_NOTIMPL;
}

HRESULT WebView::makeTextSmaller(_In_opt_ IUnknown* /*sender*/)
{
    return E_NOTIMPL;
}

HRESULT WebView::zoomPageOut(_In_opt_ IUnknown* /*sender*/)
{
    return E_NOTIMPL;
}

HRESULT WebView::canMakeTextStandardSize(_In_opt_ IUnknown* /*sender*/, _Out_ BOOL* result)
{
    if (!result)
        return E_POINTER;

    *result = FALSE;
    return E_NOTIMPL;
}

HRESULT WebView::canResetPageZoom(_In_opt_ IUnknown* /*sender*/, _Out_ BOOL* result)
{
    if (!result)
        return E_POINTER;

    *result = FALSE;
    return E_NOTIMPL;
}

HRESULT WebView::makeTextStandardSize(_In_opt_ IUnknown* /*sender*/)
{
    return E_NOTIMPL;
}

HRESULT WebView::resetPageZoom(_In_opt_ IUnknown* /*sender*/)
{
    return E_NOTIMPL;
}

HRESULT WebView::toggleContinuousSpellChecking(_In_opt_ IUnknown* /*sender*/)
{
    return E_NOTIMPL;
}

HRESULT WebView::toggleSmartInsertDelete(_In_opt_ IUnknown* /*sender*/)
{
    return E_NOTIMPL;
}

HRESULT WebView::toggleGrammarChecking(_In_opt_ IUnknown* /*sender*/)
{
    return E_NOTIMPL;
}

HRESULT WebView::reloadFromOrigin(_In_opt_ IUnknown* /*sender*/)
{
    return E_NOTIMPL;
}

// IWebViewCSS -----------------------------------------------------------------

HRESULT WebView::computedStyleForElement(_In_opt_ IDOMElement* /*element*/, _In_ BSTR /*pseudoElement*/, _COM_Outptr_opt_ IDOMCSSStyleDeclaration** style)
{
    ASSERT_NOT_REACHED();
    if (!style)
        return E_POINTER;
    *style = nullptr;
    return E_NOTIMPL;
}

// IWebViewEditing -------------------------------------------------------------

HRESULT WebView::editableDOMRangeForPoint(_In_ LPPOINT /*point*/, _COM_Outptr_opt_ IDOMRange** range)
{
    ASSERT_NOT_REACHED();
    if (!range)
        return E_POINTER;
    *range = nullptr;
    return E_NOTIMPL;
}
    
HRESULT WebView::setSelectedDOMRange(_In_opt_ IDOMRange* /*range*/,  WebSelectionAffinity /*affinity*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::selectedDOMRange(_COM_Outptr_opt_ IDOMRange** range)
{
    ASSERT_NOT_REACHED();
    if (!range)
        return E_POINTER;
    *range = nullptr;
    return E_NOTIMPL;
}
    
HRESULT WebView::selectionAffinity(_Out_ WebSelectionAffinity*)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::setEditable(BOOL flag)
{
    return E_NOTIMPL;
}
    
HRESULT WebView::isEditable(_Out_ BOOL* isEditable)
{
    if (!isEditable)
        return E_POINTER;

    *isEditable = FALSE;

    return E_NOTIMPL;
}
    
HRESULT WebView::setTypingStyle(_In_opt_ IDOMCSSStyleDeclaration* /*style*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::typingStyle(_COM_Outptr_opt_ IDOMCSSStyleDeclaration** style)
{
    ASSERT_NOT_REACHED();
    if (!style)
        return E_POINTER;
    *style = nullptr;
    return E_NOTIMPL;
}
    
HRESULT WebView::setSmartInsertDeleteEnabled(BOOL flag)
{
    return E_NOTIMPL;
}
    
HRESULT WebView::smartInsertDeleteEnabled(_Out_ BOOL* enabled)
{
    if (!enabled)
        return E_POINTER;

    *enabled = FALSE;
    return E_NOTIMPL;
}
 
HRESULT WebView::setSelectTrailingWhitespaceEnabled(BOOL flag)
{
    return E_NOTIMPL;
}
    
HRESULT WebView::isSelectTrailingWhitespaceEnabled(_Out_ BOOL* enabled)
{
    if (!enabled)
        return E_POINTER;

    *enabled = FALSE;
    return E_NOTIMPL;
}

HRESULT WebView::setContinuousSpellCheckingEnabled(BOOL flag)
{
    return E_NOTIMPL;
}
    
HRESULT WebView::isContinuousSpellCheckingEnabled(_Out_ BOOL* enabled)
{
    if (!enabled)
        return E_POINTER;

    *enabled = FALSE;
    return E_NOTIMPL;
}
    
HRESULT WebView::spellCheckerDocumentTag(_Out_ int* tag)
{
    if (!tag)
        return E_POINTER;

    // we just use this as a flag to indicate that we've spell checked the document
    // and need to close the spell checker out when the view closes.
    *tag = 0;
    return E_NOTIMPL;
}

HRESULT WebView::undoManager(_COM_Outptr_opt_ IWebUndoManager** manager)
{
    ASSERT_NOT_REACHED();
    if (!manager)
        return E_POINTER;
    *manager = nullptr;
    return E_NOTIMPL;
}
    
HRESULT WebView::setEditingDelegate(_In_opt_ IWebEditingDelegate* d)
{
    return E_NOTIMPL;
}
    
HRESULT WebView::editingDelegate(_COM_Outptr_opt_ IWebEditingDelegate** d)
{
    return E_NOTIMPL;
}
    
HRESULT WebView::styleDeclarationWithText(_In_ BSTR /*text*/, _COM_Outptr_opt_ IDOMCSSStyleDeclaration** style)
{
    ASSERT_NOT_REACHED();
    if (!style)
        return E_POINTER;
    *style = nullptr;
    return E_NOTIMPL;
}
    
HRESULT WebView::hasSelectedRange(_Out_ BOOL* hasSelectedRange)
{
    if (!hasSelectedRange)
        return E_POINTER;

    *hasSelectedRange = FALSE;
    return E_NOTIMPL;
}
    
HRESULT WebView::cutEnabled(_Out_ BOOL* enabled)
{
    if (!enabled)
        return E_POINTER;

    *enabled = FALSE;
    return E_NOTIMPL;
}
    
HRESULT WebView::copyEnabled(_Out_ BOOL* enabled)
{
    if (!enabled)
        return E_POINTER;

    *enabled = FALSE;
    return E_NOTIMPL;
}
    
HRESULT WebView::pasteEnabled(_Out_ BOOL* enabled)
{
    if (!enabled)
        return E_POINTER;

    *enabled = FALSE;
    return E_NOTIMPL;
}
    
HRESULT WebView::deleteEnabled(_Out_ BOOL* enabled)
{
    if (!enabled)
        return E_POINTER;

    *enabled = FALSE;
    return E_NOTIMPL;
}
    
HRESULT WebView::editingEnabled(_Out_ BOOL* enabled)
{
    if (!enabled)
        return E_POINTER;

    *enabled = FALSE;
    return E_NOTIMPL;
}

HRESULT WebView::isGrammarCheckingEnabled(_Out_ BOOL* enabled)
{
    if (!enabled)
        return E_POINTER;

    *enabled = FALSE;
    return E_NOTIMPL;
}

HRESULT WebView::setGrammarCheckingEnabled(BOOL enabled)
{
    return E_NOTIMPL;
}

// IWebViewUndoableEditing -----------------------------------------------------

HRESULT WebView::replaceSelectionWithNode(_In_opt_ IDOMNode* /*node*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::replaceSelectionWithText(_In_ BSTR text)
{
    return E_NOTIMPL;
}
    
HRESULT WebView::replaceSelectionWithMarkupString(_In_ BSTR /*markupString*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::replaceSelectionWithArchive(_In_opt_ IWebArchive* /*archive*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::deleteSelection()
{
    return E_NOTIMPL;
}

HRESULT WebView::clearSelection()
{
    return E_NOTIMPL;
}
    
HRESULT WebView::applyStyle(_In_opt_ IDOMCSSStyleDeclaration* /*style*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

// IWebViewEditingActions ------------------------------------------------------

HRESULT WebView::copy(_In_opt_ IUnknown* /*sender*/)
{
    return E_NOTIMPL;
}

HRESULT WebView::cut(_In_opt_ IUnknown* /*sender*/)
{
    return E_NOTIMPL;
}

HRESULT WebView::paste(_In_opt_ IUnknown* /*sender*/)
{
    return E_NOTIMPL;
}

HRESULT WebView::copyURL(_In_ BSTR url)
{
    return E_NOTIMPL;
}

HRESULT WebView::copyFont(_In_opt_ IUnknown* /*sender*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::pasteFont(_In_opt_ IUnknown* /*sender*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::delete_(_In_opt_ IUnknown* /*sender*/)
{
    return E_NOTIMPL;
}
    
HRESULT WebView::pasteAsPlainText(_In_opt_ IUnknown* /*sender*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::pasteAsRichText(_In_opt_ IUnknown* /*sender*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::changeFont(_In_opt_ IUnknown* /*sender*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::changeAttributes(_In_opt_ IUnknown* /*sender*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::changeDocumentBackgroundColor(_In_opt_ IUnknown* /*sender*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::changeColor(_In_opt_ IUnknown* /*sender*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::alignCenter(_In_opt_ IUnknown* /*sender*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::alignJustified(_In_opt_ IUnknown* /*sender*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::alignLeft(_In_opt_ IUnknown* /*sender*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::alignRight(_In_opt_ IUnknown* /*sender*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::checkSpelling(_In_opt_ IUnknown* /*sender*/)
{
    return E_NOTIMPL;
}
    
HRESULT WebView::showGuessPanel(_In_opt_ IUnknown* /*sender*/)
{
    return E_NOTIMPL;
}
    
HRESULT WebView::performFindPanelAction(_In_opt_ IUnknown* /*sender*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::startSpeaking(_In_opt_ IUnknown* /*sender*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
    
HRESULT WebView::stopSpeaking(_In_opt_ IUnknown* /*sender*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

// IWebNotificationObserver -----------------------------------------------------------------

HRESULT WebView::onNotify(_In_opt_ IWebNotification* notification)
{
    if (!notification)
        return E_POINTER;

    return E_NOTIMPL;
}

HRESULT updateSharedSettingsFromPreferencesIfNeeded(IWebPreferences* preferences)
{
    return E_NOTIMPL;
}

// IWebViewPrivate ------------------------------------------------------------

HRESULT WebView::MIMETypeForExtension(_In_ BSTR extension, _Deref_opt_out_ BSTR* mimeType)
{
    if (!mimeType)
        return E_POINTER;

    *mimeType = FALSE;
    return E_NOTIMPL;
}

HRESULT WebView::setCustomDropTarget(_In_opt_ IDropTarget* dt)
{
    if (!dt)
        return E_POINTER;
    return E_NOTIMPL;
}

HRESULT WebView::removeCustomDropTarget()
{
    return E_NOTIMPL;
}

HRESULT WebView::setInViewSourceMode(BOOL)
{
    return E_NOTIMPL;
}
    
HRESULT WebView::inViewSourceMode(_Out_ BOOL*)
{
    return E_NOTIMPL;
}

HRESULT WebView::viewWindow(_Deref_opt_out_ HWND* window)
{
    if (!window)
        return E_POINTER;

    WebMainFrame& mainFrame = *static_cast<WebMainFrame*>(m_mainFrame.GetInterfacePtr());
    *window = (HWND)mainFrame.m_window->windowHandle();
    return S_OK;
}

HRESULT WebView::setFormDelegate(_In_opt_ IWebFormDelegate* formDelegate)
{
    return E_NOTIMPL;
}

HRESULT WebView::formDelegate(_COM_Outptr_opt_ IWebFormDelegate** formDelegate)
{
    if (!formDelegate)
        return E_POINTER;
    *formDelegate = nullptr;
    return E_NOTIMPL;
}

HRESULT WebView::setFrameLoadDelegatePrivate(_In_opt_ IWebFrameLoadDelegatePrivate* d)
{
    m_frameLoadDelegatePrivate = d;
    return S_OK;
}

HRESULT WebView::frameLoadDelegatePrivate(_COM_Outptr_opt_ IWebFrameLoadDelegatePrivate** d)
{
    if (!d)
        return E_POINTER;
    *d = m_frameLoadDelegatePrivate;
    return S_OK;
}

HRESULT WebView::scrollOffset(_Out_ LPPOINT offset)
{
    if (!offset)
        return E_POINTER;
    return E_NOTIMPL;
}

HRESULT WebView::scrollBy(_In_ LPPOINT offset)
{
    if (!offset)
        return E_POINTER;

    return E_NOTIMPL;
}

HRESULT WebView::visibleContentRect(_Out_ LPRECT rect)
{
    if (!rect)
        return E_POINTER;

    return E_NOTIMPL;
}

HRESULT WebView::DragEnter(IDataObject* pDataObject, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
{
    return E_NOTIMPL;
}

HRESULT WebView::DragOver(DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
{
    return E_NOTIMPL;
}

HRESULT WebView::DragLeave()
{
    return E_NOTIMPL;
}

HRESULT WebView::Drop(IDataObject* pDataObject, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
{
    return E_NOTIMPL;
}

HRESULT WebView::canHandleRequest(_In_opt_ IWebURLRequest* request, _Out_ BOOL* result)
{
    if (!result)
        return E_POINTER;

    *result = FALSE;

    if (!request)
        return E_NOTIMPL;

    *result = FALSE;
    return E_NOTIMPL;
}

HRESULT WebView::standardUserAgentWithApplicationName(_In_ BSTR applicationName, _Deref_opt_out_ BSTR* groupName)
{
    if (!groupName) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    if (!applicationName) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *groupName = 0;
    return E_NOTIMPL;
}

HRESULT WebView::clearFocusNode()
{
    return E_NOTIMPL;
}

HRESULT WebView::setInitialFocus(BOOL forward)
{
    return E_NOTIMPL;
}

HRESULT WebView::setTabKeyCyclesThroughElements(BOOL cycles)
{
    return E_NOTIMPL;
}

HRESULT WebView::tabKeyCyclesThroughElements(_Out_ BOOL* result)
{
    if (!result) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *result = FALSE;
    return E_NOTIMPL;
}

HRESULT WebView::setAllowSiteSpecificHacks(BOOL allow)
{
    return E_NOTIMPL;
}

HRESULT WebView::addAdditionalPluginDirectory(_In_ BSTR directory)
{
    return E_NOTIMPL;
}

HRESULT WebView::loadBackForwardListFromOtherView(_In_opt_ IWebView* otherView)
{
    if (!otherView)
        return E_NOTIMPL;

    return E_NOTIMPL;
}

HRESULT WebView::clearUndoRedoOperations()
{
    return E_NOTIMPL;
}

HRESULT WebView::shouldClose(_Out_ BOOL* result)
{
    if (!result) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *result = FALSE;

    return E_NOTIMPL;
}

HRESULT WebView::setProhibitsMainFrameScrolling(BOOL b)
{
    return E_NOTIMPL;
}

HRESULT WebView::setShouldApplyMacFontAscentHack(BOOL b)
{
    return E_NOTIMPL;
}

HRESULT WebView::inspector(_COM_Outptr_opt_ IWebInspector** inspector)
{
    if (!inspector)
        return E_POINTER;
    *inspector = nullptr;
    return E_NOTIMPL;
}

HRESULT WebView::windowAncestryDidChange()
{
    return E_NOTIMPL;
}

HRESULT WebView::paintDocumentRectToContext(RECT rect, _In_ HDC deviceContext)
{
    if (!deviceContext)
        return E_POINTER;

    return E_NOTIMPL;
}

HRESULT WebView::paintScrollViewRectToContextAtPoint(RECT rect, POINT pt, _In_ HDC deviceContext)
{
    if (!deviceContext)
        return E_POINTER;

    return E_NOTIMPL;
}

HRESULT WebView::reportException(_In_ JSContextRef context, _In_ JSValueRef exception)
{
    if (!context || !exception)
        return E_INVALIDARG;

    return E_NOTIMPL;
}

HRESULT WebView::elementFromJS(_In_ JSContextRef context, _In_ JSValueRef nodeObject, _COM_Outptr_opt_ IDOMElement** element)
{
    if (!element)
        return E_POINTER;

    *element = nullptr;

    if (!context || !nodeObject)
        return E_INVALIDARG;

    *element = 0;
    return E_NOTIMPL;
}

HRESULT WebView::setCustomHTMLTokenizerTimeDelay(double timeDelay)
{
    ASSERT_NOT_REACHED();
    return E_FAIL;
}

HRESULT WebView::setCustomHTMLTokenizerChunkSize(int chunkSize)
{
    ASSERT_NOT_REACHED();
    return E_FAIL;
}

HRESULT WebView::backingStore(_Deref_opt_out_ HBITMAP* hBitmap)
{
    if (!hBitmap)
        return E_POINTER;
    *hBitmap = 0;
    return E_NOTIMPL;
}

HRESULT WebView::setTransparent(BOOL transparent)
{
    return S_OK;
}

HRESULT WebView::transparent(_Out_ BOOL* transparent)
{
    if (!transparent)
        return E_POINTER;

    *transparent = FALSE;
    return S_OK;
}

HRESULT WebView::setUsesLayeredWindow(BOOL usesLayeredWindow)
{
    return S_OK;
}

HRESULT WebView::usesLayeredWindow(_Out_ BOOL* usesLayeredWindow)
{
    if (!usesLayeredWindow)
        return E_POINTER;

    *usesLayeredWindow = FALSE;
    return S_OK;
}

HRESULT WebView::setCookieEnabled(BOOL enable)
{
    return E_NOTIMPL;
}

HRESULT WebView::cookieEnabled(_Out_ BOOL* enabled)
{
    if (!enabled)
        return E_POINTER;

    *enabled = FALSE;
    return E_NOTIMPL;
}

HRESULT WebView::setMediaVolume(float volume)
{
    return E_NOTIMPL;
}

HRESULT WebView::mediaVolume(_Out_ float* volume)
{
    if (!volume)
        return E_POINTER;

    *volume = 1.0f;
    return E_NOTIMPL;
}

HRESULT WebView::setDefersCallbacks(BOOL defersCallbacks)
{
    return E_NOTIMPL;
}

HRESULT WebView::defersCallbacks(_Out_ BOOL* defersCallbacks)
{
    if (!defersCallbacks)
        return E_POINTER;

    *defersCallbacks = FALSE;
    return E_NOTIMPL;
}

HRESULT WebView::globalHistoryItem(_COM_Outptr_opt_ IWebHistoryItem** item)
{
    if (!item)
        return E_POINTER;
    *item = nullptr;
    return E_NOTIMPL;
}

HRESULT WebView::setAlwaysUsesComplexTextCodePath(BOOL complex)
{
    return E_NOTIMPL;
}

HRESULT WebView::alwaysUsesComplexTextCodePath(_Out_ BOOL* complex)
{
    if (!complex)
        return E_POINTER;

    *complex = FALSE;
    return E_NOTIMPL;
}

HRESULT WebView::registerEmbeddedViewMIMEType(_In_ BSTR mimeType)
{
    if (!mimeType)
        return E_POINTER;

    return E_NOTIMPL;
}

HRESULT WebView::setMemoryCacheDelegateCallsEnabled(BOOL enabled)
{
    return E_NOTIMPL;
}

HRESULT WebView::setJavaScriptURLsAreAllowed(BOOL)
{
    return E_NOTIMPL;
}

HRESULT WebView::setCanStartPlugins(BOOL canStartPlugins)
{
    return E_NOTIMPL;
}

HRESULT WebView::addUserScriptToGroup(_In_ BSTR groupName, _In_opt_ IWebScriptWorld* iWorld, _In_ BSTR source, _In_ BSTR url,
    unsigned whitelistCount, __inout_ecount_full(whitelistCount) BSTR* whitelist,
    unsigned blacklistCount, __inout_ecount_full(blacklistCount) BSTR* blacklist,
    WebUserScriptInjectionTime injectionTime)
{
    return E_NOTIMPL;
}

HRESULT WebView::addUserScriptToGroup(_In_ BSTR groupName, _In_opt_ IWebScriptWorld* iWorld, _In_ BSTR source, _In_ BSTR url,
    unsigned whitelistCount, __inout_ecount_full(whitelistCount) BSTR* whitelist,
    unsigned blacklistCount, __inout_ecount_full(blacklistCount) BSTR* blacklist,
    WebUserScriptInjectionTime injectionTime, WebUserContentInjectedFrames injectedFrames)
{
    return E_NOTIMPL;
}

HRESULT WebView::addUserStyleSheetToGroup(_In_ BSTR groupName, _In_opt_ IWebScriptWorld* iWorld, _In_ BSTR source, _In_ BSTR url,
    unsigned whitelistCount, __inout_ecount_full(whitelistCount) BSTR* whitelist, unsigned blacklistCount, __inout_ecount_full(blacklistCount) BSTR* blacklist)
{
    return E_NOTIMPL;
}

HRESULT WebView::addUserStyleSheetToGroup(_In_ BSTR groupName, _In_opt_ IWebScriptWorld* iWorld, _In_ BSTR source, _In_ BSTR url,
    unsigned whitelistCount, __inout_ecount_full(whitelistCount) BSTR* whitelist, unsigned blacklistCount, __inout_ecount_full(blacklistCount) BSTR* blacklist,
    WebUserContentInjectedFrames injectedFrames)
{
    return E_NOTIMPL;
}

HRESULT WebView::removeUserScriptFromGroup(_In_ BSTR groupName, _In_opt_ IWebScriptWorld* iWorld, _In_ BSTR url)
{
    return E_NOTIMPL;
}

HRESULT WebView::removeUserStyleSheetFromGroup(_In_ BSTR groupName, _In_opt_ IWebScriptWorld* iWorld, _In_ BSTR url)
{
    return E_NOTIMPL;
}

HRESULT WebView::removeUserScriptsFromGroup(_In_ BSTR groupName, _In_opt_ IWebScriptWorld* iWorld)
{
    return E_NOTIMPL;
}

HRESULT WebView::removeUserStyleSheetsFromGroup(_In_ BSTR groupName, _In_opt_ IWebScriptWorld* iWorld)
{
    return E_NOTIMPL;
}

HRESULT WebView::removeAllUserContentFromGroup(_In_ BSTR groupName)
{
    return E_NOTIMPL;
}

HRESULT WebView::invalidateBackingStore(_In_ const RECT* rect)
{
    return E_NOTIMPL;
}

HRESULT WebView::addOriginAccessWhitelistEntry(_In_ BSTR sourceOrigin, _In_ BSTR destinationProtocol, _In_ BSTR destinationHost, BOOL allowDestinationSubdomains)
{
    return E_NOTIMPL;
}

HRESULT WebView::removeOriginAccessWhitelistEntry(_In_ BSTR sourceOrigin, _In_ BSTR destinationProtocol, _In_ BSTR destinationHost, BOOL allowDestinationSubdomains)
{
    return E_NOTIMPL;
}

HRESULT WebView::resetOriginAccessWhitelists()
{
    return E_NOTIMPL;
}
 
HRESULT WebView::setHistoryDelegate(_In_ IWebHistoryDelegate* historyDelegate)
{
    return E_NOTIMPL;
}

HRESULT WebView::historyDelegate(_COM_Outptr_opt_ IWebHistoryDelegate** historyDelegate)
{
    if (!historyDelegate)
        return E_POINTER;
    *historyDelegate = nullptr;
    return E_NOTIMPL;
}

HRESULT WebView::addVisitedLinks(__inout_ecount_full(visitedURLCount) BSTR* visitedURLs, unsigned visitedURLCount)
{
    return E_NOTIMPL;
}

HRESULT WebView::unused1()
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

HRESULT WebView::unused2()
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

HRESULT WebView::unused3()
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

HRESULT WebView::unused4()
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

HRESULT WebView::unused5()
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

HRESULT WebView::setGeolocationProvider(_In_opt_ IWebGeolocationProvider* locationProvider)
{
    return E_NOTIMPL;
}

HRESULT WebView::geolocationProvider(_COM_Outptr_opt_ IWebGeolocationProvider** locationProvider)
{
    if (!locationProvider)
        return E_POINTER;
    *locationProvider = nullptr;
    return E_NOTIMPL;
}

HRESULT WebView::geolocationDidChangePosition(_In_opt_ IWebGeolocationPosition* position)
{
    return E_NOTIMPL;
}

HRESULT WebView::geolocationDidFailWithError(_In_opt_ IWebError* error)
{
    if (!error)
        return E_POINTER;

    return E_NOTIMPL;
}

HRESULT WebView::setDomainRelaxationForbiddenForURLScheme(BOOL forbidden, _In_ BSTR scheme)
{
    return E_NOTIMPL;
}

HRESULT WebView::registerURLSchemeAsSecure(_In_ BSTR scheme)
{
    return E_NOTIMPL;
}

HRESULT WebView::registerURLSchemeAsAllowingLocalStorageAccessInPrivateBrowsing(_In_ BSTR scheme)
{
    return E_NOTIMPL;
}

HRESULT WebView::registerURLSchemeAsAllowingDatabaseAccessInPrivateBrowsing(_In_ BSTR scheme)
{
    return E_NOTIMPL;
}

HRESULT WebView::nextDisplayIsSynchronous()
{
    return E_NOTIMPL;
}

HRESULT WebView::defaultMinimumTimerInterval(_Out_ double* interval)
{
    if (!interval)
        return E_POINTER;
    *interval = 0.0;
    return E_NOTIMPL;
}

HRESULT WebView::setMinimumTimerInterval(double interval)
{
    return E_NOTIMPL;
}

HRESULT WebView::httpPipeliningEnabled(_Out_ BOOL* enabled)
{
    if (!enabled)
        return E_POINTER;
    *enabled = FALSE;
    return E_NOTIMPL;
}

HRESULT WebView::setHTTPPipeliningEnabled(BOOL enabled)
{
    return E_NOTIMPL;
}

// Used by TextInputController in DumpRenderTree

HRESULT WebView::setCompositionForTesting(_In_ BSTR composition, UINT from, UINT length)
{
    return E_NOTIMPL;
}

HRESULT WebView::hasCompositionForTesting(_Out_ BOOL* result)
{
    *result = FALSE;
    return E_NOTIMPL;
}

HRESULT WebView::confirmCompositionForTesting(_In_ BSTR composition)
{
    return E_NOTIMPL;
}

HRESULT WebView::compositionRangeForTesting(_Out_ UINT* startPosition, _Out_ UINT* length)
{
    if (!startPosition || !length)
        return E_POINTER;

    *startPosition = 0;
    *length = 0;

    return E_NOTIMPL;
}


HRESULT WebView::firstRectForCharacterRangeForTesting(UINT location, UINT length, _Out_ RECT* resultRect)
{
    if (!resultRect)
        return E_POINTER;

    return E_NOTIMPL;
}

HRESULT WebView::selectedRangeForTesting(_Out_ UINT* location, _Out_ UINT* length)
{
    if (!location || !length)
        return E_POINTER;

    *location = 0;
    *length = 0;

    return E_NOTIMPL;
}

// IWebViewPrivate2
HRESULT WebView::setLoadResourcesSerially(BOOL serialize)
{
    return E_NOTIMPL;
}

HRESULT WebView::scaleWebView(double scale, POINT origin)
{
    return E_NOTIMPL;
}

HRESULT WebView::dispatchPendingLoadRequests()
{
    return E_NOTIMPL;
}

HRESULT WebView::setCustomBackingScaleFactor(double customScaleFactor)
{
    return E_NOTIMPL;
}

HRESULT WebView::backingScaleFactor(_Out_ double* factor)
{
    if (!factor)
        return E_POINTER;

    *factor = deviceScaleFactor();

    return E_NOTIMPL;
}

HRESULT WebView::layerTreeAsString(_Deref_opt_out_ BSTR* treeBstr)
{
    if (!treeBstr)
        return E_POINTER;

    *treeBstr = nullptr;

    return E_NOTIMPL;
}

HRESULT WebView::findString(BSTR __MIDL__IWebViewPrivate30001, WebFindOptions __MIDL__IWebViewPrivate30002, BOOL *found)
{
    if (!found)
        return E_POINTER;

    *found = FALSE;

    return E_NOTIMPL;
}

// ITestRunnerWebView
HRESULT WebView::setPageConfiguration(long* pageConfiguration)
{
    m_pageConfigurationLeakedPtr = reinterpret_cast<WKPageConfiguration*>(pageConfiguration);

    return S_OK;
}

HRESULT WebView::pageRef(long** pageRef)
{
    if (!pageRef)
        return E_POINTER;

    WebMainFrame& mainFrame = *static_cast<WebMainFrame*>(m_mainFrame.GetInterfacePtr());
    *pageRef = reinterpret_cast<long*>(WebKitTestRunnerSupport::getWKPageRefFromWebContent(mainFrame.m_webContent));

    return S_OK;
}

float WebView::deviceScaleFactor() const
{
    return WebCore::deviceScaleFactorForWindow(nullptr);
}
