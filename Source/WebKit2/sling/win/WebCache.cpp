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
#include "WebCache.h"

#include "Assertions.h"

// WebCache ---------------------------------------------------------------------------

WebCache::WebCache()
{
    gClassCount++;
}

WebCache::~WebCache()
{
    gClassCount--;
}

WebCache* WebCache::createInstance()
{
    WebCache* instance = new WebCache();
    instance->AddRef();
    return instance;
}

// IUnknown -------------------------------------------------------------------

HRESULT WebCache::QueryInterface(_In_ REFIID riid, _COM_Outptr_ void** ppvObject)
{
    if (!ppvObject)
        return E_POINTER;
    *ppvObject = nullptr;
    if (IsEqualGUID(riid, IID_IUnknown))
        *ppvObject = static_cast<WebCache*>(this);
    else if (IsEqualGUID(riid, IID_IWebCache))
        *ppvObject = static_cast<WebCache*>(this);
    else
        return E_NOINTERFACE;

    AddRef();
    return S_OK;
}

ULONG WebCache::AddRef()
{
    return ++m_refCount;
}

ULONG WebCache::Release()
{
    ULONG newRef = --m_refCount;
    if (!newRef)
        delete(this);

    return newRef;
}

// IWebCache ------------------------------------------------------------------------------

HRESULT WebCache::statistics(_Inout_ int* count, _Inout_opt_ IPropertyBag** s)
{
    return E_NOTIMPL;
}

HRESULT WebCache::empty()
{
    return E_NOTIMPL;
}

HRESULT WebCache::setDisabled(BOOL disabled)
{
    return E_NOTIMPL;
}

HRESULT WebCache::disabled(_Out_ BOOL* disabled)
{
    if (!disabled)
        return E_POINTER;
    *disabled = FALSE;
    return S_OK;
}

HRESULT WebCache::cacheFolder(__deref_out_opt BSTR* location)
{
    return E_NOTIMPL;
}

HRESULT WebCache::setCacheFolder(_In_ BSTR location)
{
    return E_NOTIMPL;
}
