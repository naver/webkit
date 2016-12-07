// Copied from gfx/thebes/gfxDWriteCommon.cpp and modified.
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

#include "config.h"
#include "DWriteFontLoader.h"

#include <cairo-win32.h>

IDWriteFontFileLoader* DWriteFontFileLoader::m_instance = nullptr;

static IDWriteFactory* GetDWriteFactory()
{
    return static_cast<IDWriteFactory*>(cairo_dwrite_get_factory());
}

IDWriteFontFileLoader* DWriteFontFileLoader::Instance()
{
    if (!m_instance) {
        m_instance = new DWriteFontFileLoader();
        GetDWriteFactory()->RegisterFontFileLoader(m_instance);
    }
    return m_instance;
}

IDWriteFontFile* DWriteFontFileLoader::CreateDWriteFontFile(WTF::Vector<char>* aData, const char* guid)
{
    DWriteFontKey key { 0 };
    key.m_array = aData;
    strcpy(key.m_guid, guid);
    IDWriteFontFile* fontFile;
    if (FAILED(GetDWriteFactory()->CreateCustomFontFileReference(&key, sizeof(DWriteFontKey), DWriteFontFileLoader::Instance(), &fontFile)))
        return nullptr;

    return fontFile;
}

DWriteFontFileLoader::DWriteFontFileLoader()
{
}

HRESULT STDMETHODCALLTYPE
DWriteFontFileLoader::CreateStreamFromKey(const void *fontFileReferenceKey, UINT32 fontFileReferenceKeySize, IDWriteFontFileStream **fontFileStream)
{
    if (!fontFileReferenceKey || !fontFileStream)
        return E_POINTER;

    *fontFileStream = new DWriteFontFileStream(static_cast<const DWriteFontKey*>(fontFileReferenceKey)->m_array);

    if (!*fontFileStream)
        return E_OUTOFMEMORY;

    (*fontFileStream)->AddRef();
    return S_OK;
}

DWriteFontFileStream::DWriteFontFileStream(WTF::Vector<char> *aData)
    : m_refCnt(0)
{
    m_data.swap(*aData);
}

DWriteFontFileStream::~DWriteFontFileStream()
{
}

HRESULT STDMETHODCALLTYPE
DWriteFontFileStream::GetFileSize(UINT64 *fileSize)
{
    *fileSize = m_data.size();
    return S_OK;
}

HRESULT STDMETHODCALLTYPE
DWriteFontFileStream::GetLastWriteTime(UINT64 *lastWriteTime)
{
    return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE
DWriteFontFileStream::ReadFileFragment(const void **fragmentStart, UINT64 fileOffset, UINT64 fragmentSize, void **fragmentContext)
{
    // We are required to do bounds checking.
    if (fileOffset + fragmentSize > (UINT64)m_data.size())
        return E_FAIL;

    // We should be alive for the duration of this.
    *fragmentStart = &m_data[fileOffset];
    *fragmentContext = nullptr;
    return S_OK;
}

void STDMETHODCALLTYPE
DWriteFontFileStream::ReleaseFileFragment(void *fragmentContext)
{
}
