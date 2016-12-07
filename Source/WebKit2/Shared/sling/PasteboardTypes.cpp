/*
 * Copyright (C) 2014-2015 Naver Corp. All rights reserved.
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
#include "PasteboardTypes.h"

#include <wtf/RetainPtr.h>

namespace WebKit {

const char* const PasteboardTypes::WebTextPboardType = "TEXT";
const char* const PasteboardTypes::WebImagePboardType = "IMAGE";
const char* const PasteboardTypes::WebFilenamePboardType = "FILENAMES";
const char* const PasteboardTypes::WebMarkupPboardType = "HTML";
const char* const PasteboardTypes::WebURLPboardType = "URL";
const char* const PasteboardTypes::WebURLNamePboardType = "URLName";
const char* const PasteboardTypes::WebURLsWithTitlesPboardType = "URLWithTitle";

static inline char** retain(char** array)
{
    return array;
}
    
char** PasteboardTypes::forEditing()
{
    static char** types;
    return types;
}

char** PasteboardTypes::forURL()
{
    static char** types;
    return types;
}

char** PasteboardTypes::forImages()
{
    static char** types;
    return types;
}

char** PasteboardTypes::forImagesWithArchive()
{
    static char** types;
    return types;
}

char** PasteboardTypes::forSelection()
{
    static char** types;
    return types;
}
    
} // namespace WebKit
