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
#include "WebHistory.h"

#include "Assertions.h"

// WebHistory -----------------------------------------------------------------

WebHistory::WebHistory()
{
    gClassCount++;
}

WebHistory::~WebHistory()
{
    gClassCount--;
}

WebHistory* WebHistory::createInstance()
{
    WebHistory* instance = new WebHistory();
    instance->AddRef();
    return instance;
}

// IUnknown -------------------------------------------------------------------

HRESULT WebHistory::QueryInterface(_In_ REFIID riid, _COM_Outptr_ void** ppvObject)
{
    if (!ppvObject)
        return E_POINTER;
    *ppvObject = nullptr;
    if (IsEqualGUID(riid, CLSID_WebHistory))
        *ppvObject = this;
    else if (IsEqualGUID(riid, IID_IUnknown))
        *ppvObject = static_cast<IWebHistory*>(this);
    else if (IsEqualGUID(riid, IID_IWebHistory))
        *ppvObject = static_cast<IWebHistory*>(this);
    else if (IsEqualGUID(riid, IID_IWebHistoryPrivate))
        *ppvObject = static_cast<IWebHistoryPrivate*>(this);
    else
        return E_NOINTERFACE;

    AddRef();
    return S_OK;
}

ULONG WebHistory::AddRef()
{
    return ++m_refCount;
}

ULONG WebHistory::Release()
{
    ULONG newRef = --m_refCount;
    if (!newRef)
        delete(this);

    return newRef;
}

// IWebHistory ----------------------------------------------------------------

HRESULT WebHistory::optionalSharedHistory(_COM_Outptr_opt_ IWebHistory** history)
{
    if (!history)
        return E_POINTER;
    *history = NULL;
    return E_NOTIMPL;
}

HRESULT WebHistory::setOptionalSharedHistory(_In_opt_ IWebHistory* history)
{
    return E_NOTIMPL;
}

HRESULT WebHistory::unused1()
{
    ASSERT_NOT_REACHED();
    return E_FAIL;
}

HRESULT WebHistory::unused2()
{
    ASSERT_NOT_REACHED();
    return E_FAIL;
}

HRESULT WebHistory::addItems(int itemCount, __deref_in_ecount_opt(itemCount) IWebHistoryItem** items)
{
    return E_NOTIMPL;
}

HRESULT WebHistory::removeItems(int itemCount, __deref_in_ecount_opt(itemCount) IWebHistoryItem** items)
{
    return E_NOTIMPL;
}

HRESULT WebHistory::removeAllItems()
{
    return E_NOTIMPL;
}

// FIXME: This function should be removed from the IWebHistory interface.
HRESULT WebHistory::orderedLastVisitedDays(_Inout_ int* count, _In_ DATE* calendarDates)
{
    return E_NOTIMPL;
}

// FIXME: This function should be removed from the IWebHistory interface.
HRESULT WebHistory::orderedItemsLastVisitedOnDay(_Inout_ int* count, __deref_in_opt IWebHistoryItem** items, DATE calendarDate)
{
    return E_NOTIMPL;
}

HRESULT WebHistory::allItems(_Inout_ int* count, __deref_opt_out IWebHistoryItem** items)
{
    return E_NOTIMPL;
}

HRESULT WebHistory::setVisitedLinkTrackingEnabled(BOOL visitedLinkTrackingEnabled)
{
    return E_NOTIMPL;
}

HRESULT WebHistory::removeAllVisitedLinks()
{
    return E_NOTIMPL;
}

HRESULT WebHistory::setHistoryItemLimit(int limit)
{
    return E_NOTIMPL;
}

HRESULT WebHistory::historyItemLimit(_Out_ int* limit)
{
    if (!limit)
        return E_POINTER;
    *limit = 0;
    return E_NOTIMPL;
}

HRESULT WebHistory::setHistoryAgeInDaysLimit(int limit)
{
    return E_NOTIMPL;
}

HRESULT WebHistory::historyAgeInDaysLimit(_Out_ int* limit)
{
    if (!limit)
        return E_POINTER;
    *limit = 0;
    return E_NOTIMPL;
}

HRESULT WebHistory::itemForURL(_In_ BSTR urlBStr, _COM_Outptr_opt_ IWebHistoryItem** item)
{
    if (!item)
        return E_POINTER;
    *item = nullptr;
    return E_NOTIMPL;
}
