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

#ifndef SWKURLResponse_h
#define SWKURLResponse_h

#include "SWKURL.h"
#include "SWKURLResponseManagedBase.h"

namespace webkit {

namespace Managed = WebKit::Managed;

class SWKURLResponse final : public Managed::SWKURLResponse {
    friend class Managed::SWKURLResponse;
public:
    std::shared_ptr<SWKURL> getURL() { return m_url; }
    std::string getMimeType() { return m_mimeType; }
    int64_t getExpectedContentLength() { return m_expectedLength; }
    std::string getTextEncodingName() { return m_encodingName; }
    std::string getContentDisposition() { return m_contentDisposition; }

private:
    void INIT(std::shared_ptr<Managed::SWKURL>, const std::string&, int64_t, const std::string&, const std::string&) override;

    std::shared_ptr<SWKURL> m_url;
    std::string m_mimeType;
    int64_t m_expectedLength;
    std::string m_encodingName;
    std::string m_contentDisposition;
};

}

#endif
