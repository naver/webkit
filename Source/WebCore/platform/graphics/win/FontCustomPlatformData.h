/*
 * Copyright (C) 2007, 2008 Apple Inc. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifndef FontCustomPlatformData_h
#define FontCustomPlatformData_h

#include "TextFlags.h"
#include <windows.h>
#include <wtf/Forward.h>
#include <wtf/Noncopyable.h>
#include <wtf/text/WTFString.h>

#if USE(CAIRO_DWRITEFONT)
#include "COMPtr.h"
#include <dwrite.h>
#endif

typedef struct CGFont* CGFontRef;

namespace WebCore {

class FontDescription;
class FontPlatformData;
class SharedBuffer;

struct FontCustomPlatformData {
    WTF_MAKE_NONCOPYABLE(FontCustomPlatformData);
public:
#if !USE(CAIRO_DWRITEFONT)
    FontCustomPlatformData(HANDLE fontReference, const String& name)
        : m_fontReference(fontReference)
        , m_name(name)
    {
    }
#else
    FontCustomPlatformData(HANDLE fontReference, const String& name, IDWriteFontFile* fontFile, DWRITE_FONT_FACE_TYPE faceType)
        : m_fontReference(fontReference)
        , m_name(name)
        , m_fontFile(AdoptCOM, fontFile)
        , m_faceType(faceType)
    {
    }
#endif

    ~FontCustomPlatformData();

    FontPlatformData fontPlatformData(const FontDescription&, bool bold, bool italic);

    static bool supportsFormat(const String&);

    HANDLE m_fontReference;
    String m_name;
#if USE(CAIRO_DWRITEFONT)
    COMPtr<IDWriteFontFile> m_fontFile;
    DWRITE_FONT_FACE_TYPE m_faceType;
#endif
};

std::unique_ptr<FontCustomPlatformData> createFontCustomPlatformData(SharedBuffer&);

}

#endif
