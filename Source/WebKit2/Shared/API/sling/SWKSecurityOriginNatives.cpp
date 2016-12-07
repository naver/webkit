/*
 * Copyright (C) 2014-2016 Naver Corp. All rights reserved.
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
#include "SWKSecurityOriginNatives.h"

#include "APISecurityOrigin.h"

namespace WebKit {

static std::string safeCast(const String& string)
{
    CString cstring = string.utf8();
    if (cstring.buffer())
        return std::string(cstring.buffer()->data(), cstring.buffer()->length());
    return std::string();
}

class SWKSecurityOriginPrivate : public Natives::SWKSecurityOrigin::Private {
public:
    RefPtr<API::SecurityOrigin> m_securityOrigin;
};

static SWKSecurityOriginPrivate* ptr(const std::unique_ptr<Natives::SWKSecurityOrigin::Private>& p)
{
    return static_cast<SWKSecurityOriginPrivate*>(p.get());
}

API::SecurityOrigin* SWKSecurityOrigin::origin() const
{
    return ptr(m_private)->m_securityOrigin.get();
}

Native::PassLocalRef<SWKSecurityOrigin> SWKSecurityOrigin::create(API::SecurityOrigin* origin)
{
    WebCore::SecurityOrigin& core = origin->securityOrigin();
    Native::LocalRef<SWKSecurityOrigin> securityOrigin = Natives::SWKSecurityOrigin::create(safeCast(core.protocol()), safeCast(core.host()), core.port());
    ptr(securityOrigin->m_private)->m_securityOrigin = origin;
    return securityOrigin.release();
}

namespace Natives {

SWKSecurityOrigin* SWKSecurityOrigin::nativeCreate()
{
    auto nativeObject = new::WebKit::SWKSecurityOrigin();
    nativeObject->m_private.reset(new SWKSecurityOriginPrivate);
    return nativeObject;
}

} // namespace Natives
} // namespace WebKit
