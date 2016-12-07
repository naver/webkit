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

#ifndef SWKCookieManager_h
#define SWKCookieManager_h

#include "SWKCookieManagerNativesBase.h"
#include "ValueCallbackNatives.h"

#include <onig/GlobalRef.h>

namespace WebKit {

class WebCookieManagerProxy;

class SWKCookieManager : public Natives::SWKCookieManager {
    friend class Natives::SWKCookieManager;
public:
    static Native::PassLocalRef<SWKCookieManager> create(WebCookieManagerProxy*);

    void cookiesDidChange();

protected:
    void getHTTPAcceptPolicy(Native::PassLocalRef<Natives::ValueCallback>) override;
    void setHTTPAcceptPolicy(int32_t) override;
    void setCookie(const std::string&, const std::string&) override;
    std::string getCookie(const std::string&) override;
    void clearHostnameCookies(const std::string&) override;
    void clearAllCookies() override;
    void clearAllExpiredCookies() override;
    void clearAllSessionCookies() override;
    void getHostNamesWithCookies(Native::PassLocalRef<Natives::ValueCallback>) override;
    void startObservingChanges(Native::PassLocalRef<Natives::ValueCallback>) override;
    void stopObservingChanges() override;

private:
    SWKCookieManager();
    ~SWKCookieManager();

    void initialize();

    WebCookieManagerProxy* m_cookieManager;
    Native::GlobalRef<ValueCallback> m_changesObserverCallback;
};

}

#endif // SWKCookieManager_h
