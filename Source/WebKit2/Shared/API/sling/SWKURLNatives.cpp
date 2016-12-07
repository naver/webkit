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
#include "SWKURLNatives.h"

#include <wtf/text/CString.h>

using namespace WebCore;

namespace WebKit {

Native::PassLocalRef<SWKURL> SWKURL::create(const URL& url)
{
    Native::LocalRef<SWKURL> newUrl = Natives::SWKURL::create();
    newUrl->m_url = url;
    return newUrl.release();
}

Native::PassLocalRef<SWKURL> SWKURL::createWithString(const String& absoluteString)
{
    Native::LocalRef<SWKURL> newUrl = Natives::SWKURL::create();
    newUrl->m_url = URL(URL(), absoluteString);
    return newUrl.release();
}

std::string SWKURL::getAbsoluteString()
{
    return m_url.string().utf8().data();
}

std::string SWKURL::getProtocol()
{
    return m_url.protocol().utf8().data();
}

std::string SWKURL::getHost()
{
    return m_url.host().utf8().data();
}

namespace Natives {

SWKURL* SWKURL::nativeCreateWithString(std::string absoluteString)
{
    ::WebKit::SWKURL* nativeURL = new ::WebKit::SWKURL;
    nativeURL->m_url = URL(URL(), String::fromUTF8(absoluteString.c_str()));
    return nativeURL;
}

SWKURL* SWKURL::nativeCreate()
{
    return new ::WebKit::SWKURL;
}

}
}
