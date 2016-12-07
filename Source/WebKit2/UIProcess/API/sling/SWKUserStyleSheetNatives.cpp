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
#include "SWKUserStyleSheetNatives.h"

#include <NativesString.h>
#include <NativesVector.h>

namespace WebKit {

Native::PassLocalRef<SWKUserStyleSheet> SWKUserStyleSheet::create(const std::string& source, Native::PassLocalRef<Natives::Vector> whitelist, Native::PassLocalRef<Natives::Vector> blacklist, int32_t injectedFrames, int32_t level)
{
    Native::LocalRef<SWKUserStyleSheet> userStyleSheet = Natives::SWKUserStyleSheet::create(source, whitelist, blacklist, injectedFrames, level).as<SWKUserStyleSheet>();
    userStyleSheet->m_source = source;
    userStyleSheet->m_injectedFrames = injectedFrames;
    userStyleSheet->m_level = level;
    return userStyleSheet;
}

namespace Natives {

SWKUserStyleSheet* SWKUserStyleSheet::nativeCreate()
{
    return new ::WebKit::SWKUserStyleSheet();
}

SWKUserStyleSheet* SWKUserStyleSheet::nativeCreateWithSource(std::string source, Native::PassLocalRef<Natives::Vector> whitelist, Native::PassLocalRef<Natives::Vector> blacklist, int32_t injectedFrames, int32_t level)
{
    auto userStyleSheet = new ::WebKit::SWKUserStyleSheet();
    userStyleSheet->m_source = source;
    userStyleSheet->m_injectedFrames = injectedFrames;
    userStyleSheet->m_level = level;
    return userStyleSheet;
}

} // namespace Natives
} // namespace WebKit

