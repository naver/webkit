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

#ifndef NativeTypeTraits_h
#define NativeTypeTraits_h

#include <wtf/text/CString.h>

namespace WebKit {

template<typename T>
struct NativeTypeTraits;

template<> struct NativeTypeTraits<void> {
    static CString name() { return "void"; }
};

template<> struct NativeTypeTraits<bool> {
    static CString name() { return "bool"; }
};

template<> struct NativeTypeTraits<int32_t> {
    static CString name() { return "int32_t"; }
};

template<> struct NativeTypeTraits<int64_t> {
    static CString name() { return "int64_t"; }
};

template<> struct NativeTypeTraits<String> {
    static CString name() { return "WTF::String"; }
};

template<> struct NativeTypeTraits<WebCore::IntPoint> {
    static CString name() { return "WebCore::Point"; }
};

template<> struct NativeTypeTraits<WebCore::IntRect> {
    static CString name() { return "WebCore::Rect"; }
};

} // namespace WebKit

#endif // NativeTypeTraits_h
