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
#include "WebDataSource.h"

#include "Assertions.h"

// WebDataSource ----------------------------------------------------------------

WebDataSource::WebDataSource(WebDocumentLoader*)
{
    gClassCount++;
}

WebDataSource::~WebDataSource()
{
    gClassCount--;
}

WebDataSource* WebDataSource::createInstance(WebDocumentLoader* loader)
{
    WebDataSource* instance = new WebDataSource(loader);
    instance->AddRef();
    return instance;
}

// IWebDataSourcePrivate ------------------------------------------------------

HRESULT WebDataSource::overrideEncoding(_Deref_opt_out_ BSTR* /*encoding*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

HRESULT WebDataSource::setOverrideEncoding(_In_ BSTR /*encoding*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

HRESULT WebDataSource::mainDocumentError(_COM_Outptr_opt_ IWebError** error)
{
    if (!error) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *error = nullptr;
    return E_NOTIMPL;
}

HRESULT WebDataSource::setDeferMainResourceDataLoad(BOOL flag)
{
    return E_NOTIMPL;
}

// IUnknown -------------------------------------------------------------------

HRESULT WebDataSource::QueryInterface(_In_ REFIID riid, _COM_Outptr_ void** ppvObject)
{
    if (!ppvObject)
        return E_POINTER;
    *ppvObject = nullptr;
if (IsEqualGUID(riid, IID_IUnknown))
        *ppvObject = static_cast<IWebDataSource*>(this);
    else if (IsEqualGUID(riid, IID_IWebDataSource))
        *ppvObject = static_cast<IWebDataSource*>(this);
    else if (IsEqualGUID(riid, IID_IWebDataSourcePrivate))
        *ppvObject = static_cast<IWebDataSourcePrivate*>(this);
    else
        return E_NOINTERFACE;

    AddRef();
    return S_OK;
}

ULONG WebDataSource::AddRef()
{
    return ++m_refCount;
}

ULONG WebDataSource::Release()
{
    ULONG newRef = --m_refCount;
    if (!newRef)
        delete(this);

    return newRef;
}

// IWebDataSource --------------------------------------------------------------

HRESULT WebDataSource::initWithRequest(_In_opt_ IWebURLRequest* /*request*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}

HRESULT WebDataSource::data(_COM_Outptr_opt_ IStream** stream)
{
    if (!stream)
        return E_POINTER;
    *stream = nullptr;
    return E_NOTIMPL;
}

HRESULT WebDataSource::representation(_COM_Outptr_opt_ IWebDocumentRepresentation** rep)
{
    if (!rep)
        return E_POINTER;
    *rep = nullptr;
    return E_NOTIMPL;
}

HRESULT WebDataSource::webFrame(_COM_Outptr_opt_ IWebFrame** frame)
{
    if (!frame)
        return E_POINTER;
    *frame = nullptr;
    return E_NOTIMPL;
}

HRESULT WebDataSource::initialRequest(_COM_Outptr_opt_ IWebURLRequest** request)
{
    if (!request)
        return E_POINTER;
    *request = nullptr;
    return E_NOTIMPL;
}

HRESULT WebDataSource::request(_COM_Outptr_opt_ IWebMutableURLRequest** request)
{
    if (!request)
        return E_POINTER;
    *request = nullptr;
    return E_NOTIMPL;
}

HRESULT WebDataSource::response(_COM_Outptr_opt_ IWebURLResponse** response)
{
    if (!response)
        return E_POINTER;
    *response = nullptr;
    return E_NOTIMPL;
}

HRESULT WebDataSource::textEncodingName(_Deref_opt_out_ BSTR* name)
{
    if (!name)
        return E_POINTER;

    *name = nullptr;
    return E_NOTIMPL;
}

HRESULT WebDataSource::isLoading(_Out_ BOOL* loading)
{
    if (!loading)
        return E_POINTER;

    *loading = FALSE;
    return E_NOTIMPL;
}

HRESULT WebDataSource::pageTitle(_Deref_opt_out_ BSTR* title)
{
    if (!title)
        return E_POINTER;

    *title = nullptr;
    return E_NOTIMPL;
}

HRESULT WebDataSource::unreachableURL(_Deref_opt_out_ BSTR* url)
{
    if (!url)
        return E_POINTER;

    *url = nullptr;
    return E_NOTIMPL;
}

HRESULT WebDataSource::webArchive(_COM_Outptr_opt_ IWebArchive** archive)
{
    ASSERT_NOT_REACHED();
    if (!archive)
        return E_POINTER;
    *archive = nullptr;
    return E_NOTIMPL;
}

HRESULT WebDataSource::mainResource(_COM_Outptr_opt_ IWebResource** resource)
{
    ASSERT_NOT_REACHED();
    if (!resource)
        return E_POINTER;
    *resource = nullptr;
    return E_NOTIMPL;
}

HRESULT WebDataSource::subresources(_COM_Outptr_opt_ IEnumVARIANT** result)
{
    ASSERT_NOT_REACHED();
    if (!result)
        return E_POINTER;
    *result = nullptr;
    return E_NOTIMPL;
}

HRESULT WebDataSource::subresourceForURL(_In_ BSTR url, _COM_Outptr_opt_ IWebResource** resource)
{
    if (!resource) {
        ASSERT_NOT_REACHED();
        return E_POINTER;
    }

    *resource = nullptr;
    return E_NOTIMPL;
}

HRESULT WebDataSource::addSubresource(_In_opt_ IWebResource* /*subresource*/)
{
    ASSERT_NOT_REACHED();
    return E_NOTIMPL;
}
