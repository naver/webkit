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

#ifndef NativeObjectCast_h
#define NativeObjectCast_h

#include "NativeWebCoreGraphics.h"
#include <wtf/Vector.h>
#include <wtf/text/WTFString.h>

#include <NativesBoolean.h>
#include <NativesInteger.h>
#include <NativesLong.h>
#include <NativesString.h>

namespace WebKit {

template<typename T>
struct NativeObjectCast;

template<> struct NativeObjectCast<bool> {
    static Native::PassLocalRef<Native::Natives::Boolean> toObject(bool value);
    static bool fromObject(Native::PassLocalRef<Native::AnyObject> value);
};

template<> struct NativeObjectCast<int32_t> {
    static Native::PassLocalRef<Native::Natives::Integer> toObject(int32_t value);
    static int32_t fromObject(Native::PassLocalRef<Native::AnyObject> value);
};

template<> struct NativeObjectCast<int64_t> {
    static Native::PassLocalRef<Native::Natives::Long> toObject(int64_t value);
    static int64_t fromObject(Native::PassLocalRef<Native::AnyObject> value);
};

template<> struct NativeObjectCast<String> {
    static Native::PassLocalRef<Native::Natives::String> toObject(const String& value);
    static String fromObject(Native::PassLocalRef<Native::AnyObject> value);
};

template<> struct NativeObjectCast<WebCore::IntPoint> {
    static Native::PassLocalRef<Native::Natives::Point> toObject(const WebCore::IntPoint& value);
    static WebCore::IntPoint fromObject(Native::PassLocalRef<Native::AnyObject> value);
};

template<> struct NativeObjectCast<WebCore::IntRect> {
    static Native::PassLocalRef<Native::Natives::Rect> toObject(const WebCore::IntRect& value);
    static WebCore::IntRect fromObject(Native::PassLocalRef<Native::AnyObject> value);
};

} // namespace WebKit

#endif // NativeObjectCast_h
