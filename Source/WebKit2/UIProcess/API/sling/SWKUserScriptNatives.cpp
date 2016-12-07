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
#include "SWKUserScriptNatives.h"

#include <WebCore/NotImplemented.h>

namespace WebKit {

Native::PassLocalRef<SWKUserScript> SWKUserScript::create(const std::string& source, int32_t injectionTime, bool forMainFrameOnly)
{
    return Natives::SWKUserScript::create(source, injectionTime, forMainFrameOnly).as<SWKUserScript>();
}

std::string SWKUserScript::getSource()
{
    notImplemented();
    return "";
}

int32_t SWKUserScript::getInjectionTime()
{
    notImplemented();
    return 0;
}

bool SWKUserScript::isForMainFrameOnly()
{
    notImplemented();
    return false;
}

namespace Natives {

SWKUserScript* SWKUserScript::nativeCreate()
{
    return new ::WebKit::SWKUserScript();
}

} // namespace Natives
} // namespace WebKit

