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

#ifndef SWKNotification_h
#define SWKNotification_h

#include "SWKNotificationManagedBase.h"

namespace webkit {

namespace Managed = WebKit::Managed;

class SWKSecurityOrigin;

class SWKNotification : public Managed::SWKNotification {
public:
    SWKNotification() = default;
    virtual ~SWKNotification() = default;

    virtual void INIT(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, std::shared_ptr<Managed::SWKSecurityOrigin>) override;

    const std::string& getTitle() const { return m_title; }
    const std::string& getBody() const { return m_body; }
    const std::string& getIconURL() const { return m_iconURL; }
    const std::string& getTag() const { return m_tag; }
    const std::string& getLanguage() const { return m_language; }
    const std::string& getDirection() const { return m_direction; }
    const std::shared_ptr<SWKSecurityOrigin> getOrigin() const { return m_origin; }

private:
    std::string m_title;
    std::string m_body;
    std::string m_iconURL;
    std::string m_tag;
    std::string m_language;
    std::string m_direction;
    std::shared_ptr<SWKSecurityOrigin> m_origin;
};

} // namespace webkit

#endif // SWKNotification_h
