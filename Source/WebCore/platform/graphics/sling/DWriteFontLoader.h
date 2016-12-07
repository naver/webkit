// Copied from gfx/thebes/gfxDWriteCommon.h and modified
/* -*- Mode: C++; tab-width: 20; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

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

#ifndef DWriteFontLoader_h
#define DWriteFontLoader_h

#include <dwrite.h>
#include <wtf/Vector.h>

struct DWriteFontKey {
    WTF::Vector<char> *m_array;
    char m_guid[LF_FACESIZE]; // Max size of LOGFONT's lfFaceName
};

class DWriteFontFileLoader : public IDWriteFontFileLoader {
public:
    DWriteFontFileLoader();

    static IDWriteFontFileLoader* Instance();
    static IDWriteFontFile* CreateDWriteFontFile(WTF::Vector<char>* aData, const char* guid);

    // IUnknown interface
    IFACEMETHOD(QueryInterface)(IID const& iid, OUT void** ppObject)
    {
        if (iid == __uuidof(IDWriteFontFileLoader)) {
            *ppObject = static_cast<IDWriteFontFileLoader*>(this);
            return S_OK;
        }
        if (iid == __uuidof(IUnknown)) {
            *ppObject = static_cast<IUnknown*>(this);
            return S_OK;
        }
        return E_NOINTERFACE;
    }

    IFACEMETHOD_(ULONG, AddRef)()
    {
        return 1;
    }

    IFACEMETHOD_(ULONG, Release)()
    {
        return 1;
    }

    virtual HRESULT STDMETHODCALLTYPE CreateStreamFromKey(void const* fontFileReferenceKey, UINT32 fontFileReferenceKeySize, OUT IDWriteFontFileStream**);

private:
    static IDWriteFontFileLoader* m_instance;
}; 

class DWriteFontFileStream final : public IDWriteFontFileStream {
public:
    /**
     * Used by the FontFileLoader to create a new font stream,
     * this font stream is created from data in memory. The memory
     * passed may be released after object creation, it will be
     * copied internally.
     *
     * @param aData Font data
     */
    DWriteFontFileStream(WTF::Vector<char> *aData);
    ~DWriteFontFileStream();

    // IUnknown interface
    IFACEMETHOD(QueryInterface)(IID const& iid, OUT void** ppObject)
    {
        if (iid == __uuidof(IDWriteFontFileStream)) {
            *ppObject = static_cast<IDWriteFontFileStream*>(this);
            return S_OK;
        }
        if (iid == __uuidof(IUnknown)) {
            *ppObject = static_cast<IUnknown*>(this);
            return S_OK;
        }
        return E_NOINTERFACE;
    }

    IFACEMETHOD_(ULONG, AddRef)()
    {
        ++m_refCnt;
        return m_refCnt;
    }

    IFACEMETHOD_(ULONG, Release)()
    {
        --m_refCnt;
        if (!m_refCnt) {
            delete this;
            return 0;
        }
        return m_refCnt;
    }

    // IDWriteFontFileStream methods
    virtual HRESULT STDMETHODCALLTYPE ReadFileFragment(void const** fragmentStart, UINT64 fileOffset, UINT64 fragmentSize, OUT void** fragmentContext);

    virtual void STDMETHODCALLTYPE ReleaseFileFragment(void* fragmentContext);

    virtual HRESULT STDMETHODCALLTYPE GetFileSize(OUT UINT64* fileSize);

    virtual HRESULT STDMETHODCALLTYPE GetLastWriteTime(OUT UINT64* lastWriteTime);

private:
    WTF::Vector<char> m_data;
    int m_refCnt;
}; 

#endif
