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
#include "WebCoreStatistics.h"

#include "Assertions.h"

// WebCoreStatistics ---------------------------------------------------------------------------

WebCoreStatistics::WebCoreStatistics()
{
    gClassCount++;
}

WebCoreStatistics::~WebCoreStatistics()
{
    gClassCount--;
}

WebCoreStatistics* WebCoreStatistics::createInstance()
{
    WebCoreStatistics* instance = new WebCoreStatistics();
    instance->AddRef();
    return instance;
}

// IUnknown -------------------------------------------------------------------

HRESULT WebCoreStatistics::QueryInterface(_In_ REFIID riid, _COM_Outptr_ void** ppvObject)
{
    if (!ppvObject)
        return E_POINTER;
    *ppvObject = nullptr;
    if (IsEqualGUID(riid, IID_IUnknown))
        *ppvObject = static_cast<WebCoreStatistics*>(this);
    else if (IsEqualGUID(riid, IID_IWebCoreStatistics))
        *ppvObject = static_cast<WebCoreStatistics*>(this);
    else
        return E_NOINTERFACE;

    AddRef();
    return S_OK;
}

ULONG WebCoreStatistics::AddRef()
{
    return ++m_refCount;
}

ULONG WebCoreStatistics::Release()
{
    ULONG newRef = --m_refCount;
    if (!newRef)
        delete(this);

    return newRef;
}

// IWebCoreStatistics ------------------------------------------------------------------------------

HRESULT WebCoreStatistics::javaScriptObjectsCount(_Out_ UINT* count)
{
    if (!count)
        return E_POINTER;

    *count = 0;
    return E_NOTIMPL;
}

HRESULT WebCoreStatistics::javaScriptGlobalObjectsCount(_Out_ UINT* count)
{
    if (!count)
        return E_POINTER;

    *count = 0;
    return E_NOTIMPL;
}

HRESULT WebCoreStatistics::javaScriptProtectedObjectsCount(_Out_ UINT* count)
{
    if (!count)
        return E_POINTER;

    *count = 0;
    return E_NOTIMPL;
}

HRESULT WebCoreStatistics::javaScriptProtectedGlobalObjectsCount(_Out_ UINT* count)
{
    if (!count)
        return E_POINTER;

    *count = 0;
    return E_NOTIMPL;
}

HRESULT WebCoreStatistics::javaScriptProtectedObjectTypeCounts(_COM_Outptr_opt_ IPropertyBag2** typeNamesAndCounts)
{
    if (!typeNamesAndCounts)
        return E_POINTER;

    return E_NOTIMPL;
}

HRESULT WebCoreStatistics::javaScriptObjectTypeCounts(_COM_Outptr_opt_ IPropertyBag2** typeNamesAndCounts)
{
    if (!typeNamesAndCounts)
        return E_POINTER;

    *typeNamesAndCounts = 0;
    return E_NOTIMPL;
}

HRESULT WebCoreStatistics::iconPageURLMappingCount(_Out_ UINT* count)
{
    if (!count)
        return E_POINTER;
    *count = 0;
    return E_NOTIMPL;
}

HRESULT WebCoreStatistics::iconRetainedPageURLCount(_Out_ UINT *count)
{
    if (!count)
        return E_POINTER;
    *count = 0;
    return E_NOTIMPL;
}

HRESULT WebCoreStatistics::iconRecordCount(_Out_ UINT *count)
{
    if (!count)
        return E_POINTER;
    *count = 0;
    return E_NOTIMPL;
}

HRESULT WebCoreStatistics::iconsWithDataCount(_Out_ UINT *count)
{
    if (!count)
        return E_POINTER;
    *count = 0;
    return E_NOTIMPL;
}

HRESULT WebCoreStatistics::cachedFontDataCount(_Out_ UINT *count)
{
    if (!count)
        return E_POINTER;
    *count = 0;
    return E_NOTIMPL;
}

HRESULT WebCoreStatistics::cachedFontDataInactiveCount(_Out_ UINT *count)
{
    if (!count)
        return E_POINTER;
    *count = 0;
    return E_NOTIMPL;
}

HRESULT WebCoreStatistics::purgeInactiveFontData(void)
{
    return E_NOTIMPL;
}

HRESULT WebCoreStatistics::glyphPageCount(_Out_ UINT *count)
{
    if (!count)
        return E_POINTER;
    *count = 0;
    return E_NOTIMPL;
}

HRESULT WebCoreStatistics::garbageCollectJavaScriptObjects()
{
    return E_NOTIMPL;
}

HRESULT WebCoreStatistics::garbageCollectJavaScriptObjectsOnAlternateThreadForDebugging(BOOL waitUntilDone)
{
    return E_NOTIMPL;
}

HRESULT WebCoreStatistics::setJavaScriptGarbageCollectorTimerEnabled(BOOL enable)
{
    return E_NOTIMPL;
}

HRESULT WebCoreStatistics::shouldPrintExceptions(_Out_ BOOL* shouldPrint)
{
    if (!shouldPrint)
        return E_POINTER;

    *shouldPrint = FALSE;
    return E_NOTIMPL;
}

HRESULT WebCoreStatistics::setShouldPrintExceptions(BOOL print)
{
    return E_NOTIMPL;
}

HRESULT WebCoreStatistics::startIgnoringWebCoreNodeLeaks()
{
    return E_NOTIMPL;
}

HRESULT WebCoreStatistics::stopIgnoringWebCoreNodeLeaks()
{
    return E_NOTIMPL;
}

HRESULT WebCoreStatistics::memoryStatistics(_COM_Outptr_opt_ IPropertyBag** statistics)
{
    if (!statistics)
        return E_POINTER;

    *statistics = NULL;
    return E_NOTIMPL;
}

HRESULT WebCoreStatistics::returnFreeMemoryToSystem()
{
    return E_NOTIMPL;
}

HRESULT WebCoreStatistics::cachedPageCount(_Out_ INT* count)
{
    if (!count)
        return E_POINTER;

    *count = 0;
    return E_NOTIMPL;
}

HRESULT WebCoreStatistics::cachedFrameCount(_Out_ INT* count)
{
    if (!count)
        return E_POINTER;

    *count = 0;
    return E_NOTIMPL;
}
