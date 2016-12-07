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
#include "SWKNotification.h"

#include "SWKSecurityOrigin.h"

namespace webkit {

void SWKNotification::INIT(const std::string& title, const std::string& body,
    const std::string& iconURL, const std::string& tag, const std::string& language,
    const std::string& direction, std::shared_ptr<Managed::SWKSecurityOrigin> origin)
{
    m_title = title;
    m_body = body;
    m_iconURL = iconURL;
    m_tag = tag;
    m_language = language;
    m_direction = direction;
    m_origin = std::static_pointer_cast<SWKSecurityOrigin>(origin);
}

} // namespace webkit

namespace WebKit {
namespace Managed {

void SWKNotification::INIT(const std::string& title, const std::string& body,
    const std::string& iconURL, const std::string& tag, const std::string& language,
    const std::string& direction, std::shared_ptr<Managed::SWKSecurityOrigin> origin)
{
}

} // namespace Managed
} // namespace WebKit
