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
#include "NativeObjectCast.h"

#include <wtf/text/CString.h>

namespace WebKit {

Native::PassLocalRef<Native::Natives::Boolean> NativeObjectCast<bool>::toObject(bool value)
{
    return Native::Natives::Boolean::create(value);
}

bool NativeObjectCast<bool>::fromObject(Native::PassLocalRef<Native::AnyObject> value)
{
    return value.as<Native::Natives::Boolean>()->value.get();
}

Native::PassLocalRef<Native::Natives::Integer> NativeObjectCast<int32_t>::toObject(int32_t value)
{
    return Native::Natives::Integer::create(value);
}

int32_t NativeObjectCast<int32_t>::fromObject(Native::PassLocalRef<Native::AnyObject> value)
{
    return value.as<Native::Natives::Integer>()->value.get();
}

Native::PassLocalRef<Native::Natives::Long> NativeObjectCast<int64_t>::toObject(int64_t value)
{
    return Native::Natives::Long::create(value);
}

int64_t NativeObjectCast<int64_t>::fromObject(Native::PassLocalRef<Native::AnyObject> value)
{
    return value.as<Native::Natives::Long>()->value.get();
}

Native::PassLocalRef<Native::Natives::String> NativeObjectCast<String>::toObject(const String& value)
{
    return Native::Natives::String::create(Native::ImmutableArray<int8_t>(reinterpret_cast<const int8_t*>(value.utf8().data()), value.length()));
}

String NativeObjectCast<String>::fromObject(Native::PassLocalRef<Native::AnyObject> value)
{
    Native::ImmutableArray<int8_t> bytes = value.as<Native::Natives::String>()->getBytes();
    return String::fromUTF8(reinterpret_cast<const char*>(bytes.data()), bytes.count());
}

Native::PassLocalRef<Native::Natives::Point> NativeObjectCast<WebCore::IntPoint>::toObject(const WebCore::IntPoint& value)
{
    return toPoint(value);
}

WebCore::IntPoint NativeObjectCast<WebCore::IntPoint>::fromObject(Native::PassLocalRef<Native::AnyObject> value)
{
    return fromPoint(value.as<Native::Natives::Point>());
}

Native::PassLocalRef<Native::Natives::Rect> NativeObjectCast<WebCore::IntRect>::toObject(const WebCore::IntRect& value)
{
    return toRect(value);
}

WebCore::IntRect NativeObjectCast<WebCore::IntRect>::fromObject(Native::PassLocalRef<Native::AnyObject> value)
{
    return fromRect(value.as<Native::Natives::Rect>());
}

}
