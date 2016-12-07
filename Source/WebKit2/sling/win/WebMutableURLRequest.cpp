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
#include "WebMutableURLRequest.h"

#include "SWKURL.h"
#include "SWKURLRequest.h"

#include "Assertions.h"
#include <util/StringConversion.h>

using namespace webkit;

// IWebURLRequest ----------------------------------------------------------------

WebMutableURLRequest::WebMutableURLRequest(bool isMutable)
    : m_isMutable(isMutable)
{
    gClassCount++;
}

WebMutableURLRequest* WebMutableURLRequest::createInstance()
{
    WebMutableURLRequest* instance = new WebMutableURLRequest(true);
    instance->AddRef();
    return instance;
}

WebMutableURLRequest* WebMutableURLRequest::createInstance(IWebMutableURLRequest* req)
{
    WebMutableURLRequest* instance = new WebMutableURLRequest(true);
    instance->AddRef();
    return instance;
}

WebMutableURLRequest* WebMutableURLRequest::createImmutableInstance()
{
    WebMutableURLRequest* instance = new WebMutableURLRequest(false);
    instance->AddRef();
    return instance;
}

WebMutableURLRequest::~WebMutableURLRequest()
{
    gClassCount--;
}

// IUnknown -------------------------------------------------------------------

HRESULT WebMutableURLRequest::QueryInterface(_In_ REFIID riid, _COM_Outptr_ void** ppvObject)
{
    if (!ppvObject)
        return E_POINTER;
    *ppvObject = nullptr;
    if (IsEqualGUID(riid, CLSID_WebMutableURLRequest))
        *ppvObject = this;
    else if (IsEqualGUID(riid, IID_IUnknown))
        *ppvObject = static_cast<IWebURLRequest*>(this);
    else if (IsEqualGUID(riid, IID_IWebMutableURLRequest) && m_isMutable)
        *ppvObject = static_cast<IWebMutableURLRequest*>(this);
    else if (IsEqualGUID(riid, __uuidof(IWebMutableURLRequestPrivate)) && m_isMutable)
        *ppvObject = static_cast<IWebMutableURLRequestPrivate*>(this);
    else if (IsEqualGUID(riid, IID_IWebURLRequest))
        *ppvObject = static_cast<IWebURLRequest*>(this);
    else
        return E_NOINTERFACE;

    AddRef();
    return S_OK;
}

ULONG WebMutableURLRequest::AddRef()
{
    return ++m_refCount;
}

ULONG WebMutableURLRequest::Release()
{
    ULONG newRef = --m_refCount;
    if (!newRef)
        delete(this);

    return newRef;
}

// IWebURLRequest --------------------------------------------------------------------

HRESULT WebMutableURLRequest::requestWithURL(_In_ BSTR /*theURL*/, WebURLRequestCachePolicy /*cachePolicy*/, double /*timeoutInterval*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

HRESULT WebMutableURLRequest::allHTTPHeaderFields(_COM_Outptr_opt_ IPropertyBag** result)
{
    ASSERT_NOT_REACHED();
    if (!result)
        return E_POINTER;
    *result = nullptr;
    return E_NOTIMPL;
}

HRESULT WebMutableURLRequest::cachePolicy(_Out_ WebURLRequestCachePolicy* result)
{
    if (!result)
        return E_POINTER;
    *result = WebURLRequestUseProtocolCachePolicy;
    return S_OK;
}

HRESULT WebMutableURLRequest::HTTPBody(_COM_Outptr_opt_ IStream** result)
{
    ASSERT_NOT_REACHED();
    if (!result)
        return E_POINTER;
    *result = nullptr;
    return E_NOTIMPL;
}

HRESULT WebMutableURLRequest::HTTPBodyStream(_COM_Outptr_opt_ IStream** result)
{
    ASSERT_NOT_REACHED();
    if (!result)
        return E_POINTER;
    *result = nullptr;
    return E_NOTIMPL;
}

HRESULT WebMutableURLRequest::HTTPMethod(__deref_opt_out BSTR* result)
{
    if (!result)
        return E_POINTER;
    *result = NULL;
    return E_NOTIMPL;
}

HRESULT WebMutableURLRequest::HTTPShouldHandleCookies(_Out_ BOOL* result)
{
    if (!result)
        return E_POINTER;
    *result = FALSE;
    return E_NOTIMPL;
}

HRESULT WebMutableURLRequest::initWithURL(_In_ BSTR urlBStr, WebURLRequestCachePolicy cachePolicy, double timeoutInterval)
{
    std::wstring url((!urlBStr) ? L"" : urlBStr);
    m_request = SWKURLRequest::createWithURL(SWKURL::createWithString(std::ws2s(url)));
    return S_OK;
}

HRESULT WebMutableURLRequest::mainDocumentURL(__deref_opt_out BSTR* result)
{
    if (!result)
        return E_POINTER;
    *result = NULL;
    return E_NOTIMPL;
}

HRESULT WebMutableURLRequest::timeoutInterval(_Out_ double* result)
{
    if (!result)
        return E_POINTER;
    *result = 0.0;
    return E_NOTIMPL;
}

HRESULT WebMutableURLRequest::URL(__deref_opt_out BSTR* result)
{
    if (!result)
        return E_POINTER;
    *result = NULL;
    return E_NOTIMPL;
}

HRESULT WebMutableURLRequest::valueForHTTPHeaderField(_In_ BSTR field, __deref_opt_out BSTR* result)
{
    if (!result) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *result = NULL;
    return E_NOTIMPL;
}

HRESULT WebMutableURLRequest::isEmpty(_Out_ BOOL* result)
{
    if (!result)
        return E_POINTER;
    *result = FALSE;
    return E_NOTIMPL;
}

HRESULT WebMutableURLRequest::isEqual(_In_opt_ IWebURLRequest* other, _Out_ BOOL* result)
{
    if (!result)
        return E_POINTER;

    *result = FALSE;
    return E_NOTIMPL;
}

// IWebMutableURLRequest --------------------------------------------------------

HRESULT WebMutableURLRequest::addValue(_In_ BSTR value, _In_ BSTR field)
{
    return E_NOTIMPL;
}

HRESULT WebMutableURLRequest::setAllHTTPHeaderFields(_In_opt_ IPropertyBag* /*headerFields*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

HRESULT WebMutableURLRequest::setCachePolicy(WebURLRequestCachePolicy policy)
{
    return E_NOTIMPL;
}

HRESULT WebMutableURLRequest::setHTTPBody(_In_opt_ IStream* data)
{
    if (!data)
        return E_POINTER;

    return E_NOTIMPL;
}

HRESULT WebMutableURLRequest::setHTTPBodyStream(_In_opt_ IStream* data)
{
    return E_NOTIMPL;
}

HRESULT WebMutableURLRequest::setHTTPMethod(_In_ BSTR method)
{
    m_httpMethod = method;
    return S_OK;
}

HRESULT WebMutableURLRequest::setHTTPShouldHandleCookies(BOOL handleCookies)
{
    return E_NOTIMPL;
}

HRESULT WebMutableURLRequest::setMainDocumentURL(_In_ BSTR theURL)
{
    return E_NOTIMPL;
}

HRESULT WebMutableURLRequest::setTimeoutInterval(double timeoutInterval)
{
    return E_NOTIMPL;
}

HRESULT WebMutableURLRequest::setURL(_In_ BSTR url)
{
    return E_NOTIMPL;
}

HRESULT WebMutableURLRequest::setValue(_In_ BSTR value, _In_ BSTR field)
{
    return E_NOTIMPL;
}

HRESULT WebMutableURLRequest::setAllowsAnyHTTPSCertificate()
{
    return E_NOTIMPL;
}

HRESULT WebMutableURLRequest::setClientCertificate(ULONG_PTR cert)
{
    if (!cert)
        return E_POINTER;

    return E_NOTIMPL;
}

CFURLRequestRef WebMutableURLRequest::cfRequest()
{
    return nullptr;
}

HRESULT WebMutableURLRequest::mutableCopy(_COM_Outptr_opt_ IWebMutableURLRequest** result)
{
    if (!result)
        return E_POINTER;

    *result = NULL;
    return E_NOTIMPL;
}
