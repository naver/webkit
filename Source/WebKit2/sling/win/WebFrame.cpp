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
#include "WebFrame.h"

#include "Assertions.h"

// WebFrame ----------------------------------------------------------------

WebFrame::WebFrame()
{
    gClassCount++;
}

WebFrame::~WebFrame()
{
    gClassCount--;
}

WebFrame* WebFrame::createInstance()
{
    WebFrame* instance = new WebFrame();
    instance->AddRef();
    return instance;
}

HRESULT WebFrame::setAllowsScrolling(BOOL flag)
{
    return E_NOTIMPL;
}

HRESULT WebFrame::allowsScrolling(_Out_ BOOL* flag)
{
    if (!flag)
        return E_POINTER;

    *flag = FALSE;
    return E_NOTIMPL;
}

HRESULT WebFrame::setIsDisconnected(BOOL flag)
{
    ASSERT_NOT_REACHED();
    return E_FAIL;
}

HRESULT WebFrame::setExcludeFromTextSearch(BOOL flag)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

HRESULT WebFrame::reloadFromOrigin()
{
    return E_NOTIMPL;
}

HRESULT WebFrame::paintDocumentRectToContext(RECT rect, _In_ HDC deviceContext)
{
    return E_NOTIMPL;
}

HRESULT WebFrame::paintScrollViewRectToContextAtPoint(RECT rect, POINT pt, _In_ HDC deviceContext)
{
    return E_NOTIMPL;
}

// IUnknown -------------------------------------------------------------------

HRESULT WebFrame::QueryInterface(_In_ REFIID riid, _COM_Outptr_ void** ppvObject)
{
    if (!ppvObject)
        return E_POINTER;
    *ppvObject = nullptr;
    if (IsEqualGUID(riid, IID_IUnknown))
        *ppvObject = static_cast<IWebFrame2*>(this);
    else if (IsEqualGUID(riid, IID_IWebFrame))
        *ppvObject = static_cast<IWebFrame2*>(this);
    else if (IsEqualGUID(riid, IID_IWebFrame2))
        *ppvObject = static_cast<IWebFrame2*>(this);
    else if (IsEqualGUID(riid, IID_IWebFramePrivate))
        *ppvObject = static_cast<IWebFramePrivate*>(this);
    else if (IsEqualGUID(riid, IID_IWebDocumentText))
        *ppvObject = static_cast<IWebDocumentText*>(this);
    else
        return E_NOINTERFACE;

    AddRef();
    return S_OK;
}

ULONG WebFrame::AddRef()
{
    return ++m_refCount;
}

ULONG WebFrame::Release()
{
    ULONG newRef = --m_refCount;
    if (!newRef)
        delete(this);

    return newRef;
}

// IWebFrame -------------------------------------------------------------------

HRESULT WebFrame::name(_Deref_opt_out_ BSTR* frameName)
{
    if (!frameName) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *frameName = nullptr;
    return E_NOTIMPL;
}

HRESULT WebFrame::webView(_COM_Outptr_opt_ IWebView** view)
{
    if (!view)
        return E_POINTER;
    *view = nullptr;
    return E_NOTIMPL;
}

HRESULT WebFrame::frameView(_COM_Outptr_opt_ IWebFrameView** view)
{
    ASSERT_NOT_REACHED();
    if (!view)
        return E_POINTER;
    *view = nullptr;
    return E_NOTIMPL;
}

HRESULT WebFrame::DOMDocument(_COM_Outptr_opt_ IDOMDocument** result)
{
    if (!result) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *result = nullptr;
    return *result ? S_OK : E_FAIL;
}


HRESULT WebFrame::DOMWindow(_COM_Outptr_opt_ IDOMWindow** window)
{
    if (!window) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *window = nullptr;
    return *window ? S_OK : E_FAIL;
}

HRESULT WebFrame::frameElement(_COM_Outptr_opt_ IDOMHTMLElement** frameElement)
{
    if (!frameElement)
        return E_POINTER;

    *frameElement = nullptr;
    return *frameElement ? S_OK : E_FAIL;
}

HRESULT WebFrame::currentForm(_COM_Outptr_opt_ IDOMElement** currentForm)
{
    if (!currentForm) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *currentForm = nullptr;
    return *currentForm ? S_OK : E_FAIL;
}

JSGlobalContextRef WebFrame::globalContext()
{
    return nullptr;
}

JSGlobalContextRef WebFrame::globalContextForScriptWorld(IWebScriptWorld* iWorld)
{
    return nullptr;
}

HRESULT WebFrame::loadRequest(_In_opt_ IWebURLRequest* request)
{
    if (!request)
        return S_OK;

    return E_NOTIMPL;
}

HRESULT WebFrame::loadData(_In_opt_ IStream* data, _In_ BSTR mimeType, _In_ BSTR textEncodingName, _In_ BSTR url)
{
    return E_NOTIMPL;
}

HRESULT WebFrame::loadPlainTextString(_In_ BSTR plainText, _In_ BSTR url)
{
    return E_NOTIMPL;
}

HRESULT WebFrame::loadHTMLString(_In_ BSTR htmlString, _In_ BSTR baseURL)
{
    return S_OK;
}

HRESULT WebFrame::loadAlternateHTMLString(_In_ BSTR str, _In_ BSTR baseURL, _In_ BSTR unreachableURL)
{
    return E_NOTIMPL;
}

HRESULT WebFrame::loadArchive(_In_opt_ IWebArchive* /*archive*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

HRESULT WebFrame::dataSource(_COM_Outptr_opt_ IWebDataSource** source)
{
    if (!source) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *source = nullptr;
    return *source ? S_OK : E_FAIL;
}

HRESULT WebFrame::provisionalDataSource(_COM_Outptr_opt_ IWebDataSource** source)
{
    if (!source) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *source = nullptr;
    return *source ? S_OK : E_FAIL;
}

HRESULT WebFrame::stopLoading()
{
    return E_NOTIMPL;
}

HRESULT WebFrame::reload()
{
    return E_NOTIMPL;
}

HRESULT WebFrame::findFrameNamed(_In_ BSTR name, _COM_Outptr_opt_ IWebFrame** frame)
{
    if (!frame) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *frame = nullptr;
    return E_NOTIMPL;
}

HRESULT WebFrame::parentFrame(_COM_Outptr_opt_ IWebFrame** frame)
{
    if (!frame)
        return E_POINTER;

    *frame = nullptr;
    return E_NOTIMPL;
}

HRESULT WebFrame::childFrames(_COM_Outptr_opt_ IEnumVARIANT** enumFrames)
{
    if (!enumFrames)
        return E_POINTER;

    *enumFrames = nullptr;
    return E_NOTIMPL;
}

// IWebFramePrivate ------------------------------------------------------

HRESULT WebFrame::renderTreeAsExternalRepresentation(BOOL forPrinting, _Deref_opt_out_ BSTR* result)
{
    if (!result)
        return E_POINTER;

    *result = nullptr;
    return E_NOTIMPL;
}

HRESULT WebFrame::pageNumberForElementById(_In_ BSTR id, float pageWidthInPixels, float pageHeightInPixels, _Out_ int* pageNumber)
{
    // TODO: Please remove this function if not needed as this is LTC specific function
    // and has been moved to Internals.
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

HRESULT WebFrame::numberOfPages(float pageWidthInPixels, float pageHeightInPixels, _Out_ int* pageCount)
{
    // TODO: Please remove this function if not needed as this is LTC specific function
    // and has been moved to Internals.
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

HRESULT WebFrame::scrollOffset(_Out_ SIZE* offset)
{
    if (!offset) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *offset = SIZE();
    return E_NOTIMPL;
}

HRESULT WebFrame::layout()
{
    return E_NOTIMPL;
}

HRESULT WebFrame::firstLayoutDone(_Out_ BOOL* result)
{
    if (!result) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *result = FALSE;
    return E_NOTIMPL;
}

HRESULT WebFrame::pendingFrameUnloadEventCount(_Out_ UINT* result)
{
    if (!result) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *result = 0;
    return E_NOTIMPL;
}

HRESULT WebFrame::hasSpellingMarker(UINT from, UINT length, BOOL* result)
{
    *result = FALSE;
    return E_NOTIMPL;
}

HRESULT WebFrame::clearOpener()
{
    return E_NOTIMPL;
}

HRESULT WebFrame::setTextDirection(_In_ BSTR direction)
{
    return E_NOTIMPL;
}

// IWebDocumentText -----------------------------------------------------------

HRESULT WebFrame::supportsTextEncoding(_Out_ BOOL* result)
{
    *result = FALSE;
    return E_NOTIMPL;
}

HRESULT WebFrame::selectedString(_Deref_opt_out_ BSTR* result)
{
    if (!result)
        return E_POINTER;
    *result = nullptr;
    return E_NOTIMPL;
}

HRESULT WebFrame::selectAll()
{
    return E_NOTIMPL;
}

HRESULT WebFrame::deselectAll()
{
    return E_NOTIMPL;
}

// WebFrame ---------------------------------------------------------------

HRESULT WebFrame::elementDoesAutoComplete(_In_opt_ IDOMElement *element, _Out_ BOOL* result)
{
    if (!element)
        return E_INVALIDARG;

    *result = false;
    return E_NOTIMPL;
}

HRESULT WebFrame::resumeAnimations()
{
    return E_NOTIMPL;
}

HRESULT WebFrame::suspendAnimations()
{
    return E_NOTIMPL;
}

HRESULT WebFrame::pauseAnimation(_In_ BSTR animationName, _In_opt_ IDOMNode* node, double secondsFromNow, _Out_ BOOL* animationWasRunning)
{
    if (!node || !animationWasRunning)
        return E_POINTER;

    *animationWasRunning = FALSE;
    return E_NOTIMPL;
}

HRESULT WebFrame::pauseTransition(_In_ BSTR propertyName, _In_opt_ IDOMNode* node, double secondsFromNow, _Out_ BOOL* transitionWasRunning)
{
    if (!node || !transitionWasRunning)
        return E_POINTER;

    *transitionWasRunning = FALSE;
    return E_NOTIMPL;
}

HRESULT WebFrame::visibleContentRect(_Out_ RECT* rect)
{
    if (!rect)
        return E_POINTER;
    *rect = RECT();
    return E_NOTIMPL;
}

HRESULT WebFrame::numberOfActiveAnimations(_Out_ UINT* number)
{
    if (!number)
        return E_POINTER;

    *number = 0;
    return E_NOTIMPL;
}

HRESULT WebFrame::isDisplayingStandaloneImage(_Out_ BOOL* result)
{
    if (!result)
        return E_POINTER;

    *result = FALSE;
    return E_NOTIMPL;
}

HRESULT WebFrame::allowsFollowingLink(_In_ BSTR url, _Out_ BOOL* result)
{
    if (!result)
        return E_POINTER;

    *result = TRUE;
    return E_NOTIMPL;
}

HRESULT WebFrame::layerTreeAsText(_Deref_out_opt_ BSTR* result)
{
    if (!result)
        return E_POINTER;
    *result = nullptr;
    return E_NOTIMPL;
}

HRESULT WebFrame::setInPrintingMode(BOOL value, _In_ HDC printDC)
{
    return E_NOTIMPL;
}

HRESULT WebFrame::getPrintedPageCount(_In_ HDC printDC, _Out_ UINT *pageCount)
{
    if (!pageCount || !printDC) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *pageCount = 0;
    return E_NOTIMPL;
}

HRESULT WebFrame::spoolPages(HDC printDC, UINT startPage, UINT endPage, void* ctx)
{
    return E_NOTIMPL;
}

HRESULT WebFrame::isFrameSet(_Out_ BOOL* result)
{
    if (!result)
        return E_POINTER;

    *result = FALSE;
    return E_NOTIMPL;
}

HRESULT WebFrame::string(_Deref_opt_out_ BSTR* result)
{
    if (!result)
        return E_POINTER;

    *result = nullptr;
    return E_NOTIMPL;
}

HRESULT WebFrame::size(_Out_ SIZE* size)
{
    if (!size)
        return E_POINTER;
    return E_NOTIMPL;
}

HRESULT WebFrame::hasScrollBars(_Out_ BOOL* result)
{
    if (!result)
        return E_POINTER;
    *result = FALSE;
    return E_NOTIMPL;
}

HRESULT WebFrame::contentBounds(_Out_ RECT* result)
{
    if (!result)
        return E_POINTER;
    return E_NOTIMPL;
}

HRESULT WebFrame::frameBounds(_Out_ RECT* result)
{
    if (!result)
        return E_POINTER;
    return E_NOTIMPL;
}

HRESULT WebFrame::isDescendantOfFrame(_In_opt_ IWebFrame* ancestor, _Out_ BOOL* result)
{
    if (!result)
        return E_POINTER;
    *result = FALSE;
    return E_NOTIMPL;
}

HRESULT WebFrame::stringByEvaluatingJavaScriptInScriptWorld(IWebScriptWorld* iWorld, JSObjectRef globalObjectRef, BSTR script, BSTR* evaluationResult)
{
    if (!evaluationResult)
        return E_POINTER;
    *evaluationResult = 0;
    return E_NOTIMPL;
}

// IWebFrame2
HRESULT WebFrame::isMainFrame(_Out_ BOOL* value)
{
    if (!value)
        return E_POINTER;
    *value = FALSE;
    return E_NOTIMPL;
}
