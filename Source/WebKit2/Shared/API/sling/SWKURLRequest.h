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

#ifndef SWKURLRequest_h
#define SWKURLRequest_h

#include "SWKURLRequestManagedBase.h"

namespace webkit {
    
namespace Managed = WebKit::Managed;

class WEBKIT_EXPORT SWKURLRequest : public Managed::SWKURLRequest {
    friend class Managed::SWKURLRequest;
public:    
    static std::shared_ptr<SWKURLRequest> createWithURL(std::shared_ptr<Managed::SWKURL>);

    virtual std::shared_ptr<Managed::SWKURL> getUrl() const { return m_url; }
    virtual const std::string& getFirstParty() const { return m_firstParty; }
    virtual const std::string& getHttpMethod() const { return m_httpMethod; }

private:
    void INIT(std::shared_ptr<Managed::SWKURL>, const std::string&, const std::string&) override;

    std::shared_ptr<Managed::SWKURL> m_url;
    std::string m_firstParty;
    std::string m_httpMethod;
};

}

#endif // SWKURLRequest
