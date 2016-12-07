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

#ifndef SWKResourceCacheManager_h
#define SWKResourceCacheManager_h

#include "SWKResourceCacheManagerNativesBase.h"
#include "WKBase.h"
#include "WKRetainPtr.h"

namespace WebKit {

class SWKResourceCacheManager : public Natives::SWKResourceCacheManager {
    friend class Natives::SWKResourceCacheManager;
public:
    static Native::PassLocalRef<SWKResourceCacheManager> create(WKContextRef);

protected:
    void getCacheOrigins(Native::PassLocalRef<Natives::ValueCallback>) override;
    void clearCacheForOrigin(const std::string&, const std::string&, int32_t, int32_t) override;
    void clearCacheForAllOrigins(int32_t) override;
    void setCachePolicy(int32_t) override;
    int32_t getCachePolicy() override;

private:
    WKRetainPtr<WKResourceCacheManagerRef> m_resourceCacheManager;
};

}

#endif // SWKResourceCacheManager_h
