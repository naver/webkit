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

#ifndef SWKUserStyleSheet_h
#define SWKUserStyleSheet_h

#include "SWKUserStyleSheetNativesBase.h"

namespace WebKit {

class SWKUserStyleSheet final : public Natives::SWKUserStyleSheet {
    friend class Natives::SWKUserStyleSheet;
public:
    static Native::PassLocalRef<SWKUserStyleSheet> create(const std::string&, Native::PassLocalRef<Natives::Vector>, Native::PassLocalRef<Natives::Vector>, int32_t, int32_t);
    virtual ~SWKUserStyleSheet() = default;

protected:
    virtual std::string getSource() override { return m_source; }
    virtual std::string getUrl() override { return m_url; }
    virtual Native::PassLocalRef<Natives::Vector> getBlacklist() override { return nullptr; }
    virtual Native::PassLocalRef<Natives::Vector> getWhitelist() override { return nullptr; }
    virtual int32_t getInjectedFrames() override { return m_injectedFrames; }
    virtual int32_t getLevel() override { return m_level; }

private:
    SWKUserStyleSheet() = default;

    std::string m_source;
    std::string m_url;
    int32_t m_injectedFrames;
    int32_t m_level;
};

} // namespace WebKit

#endif // SWKUserStyleSheet_h

