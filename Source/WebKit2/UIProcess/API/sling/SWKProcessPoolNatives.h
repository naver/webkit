/*
 * Copyright (C) 2014 Naver Corp. All rights reserved.
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

#ifndef SWKProcessPool_h
#define SWKProcessPool_h

#include "SWKProcessPoolNativesBase.h"
#include "WKBase.h"
#include <onig/GlobalRef.h>
#include <wtf/Ref.h>
#include <wtf/RefPtr.h>

namespace WebKit {

class GeolocationManager;
class NotificationManager;
class SWKApplicationCacheManager;
class SWKCookieManager;
class SWKDownloadClient;
class SWKIconDatabase;
class SWKKeyValueStorageManager;
class SWKProcessPoolConfiguration;
class SWKResourceCacheManager;
class SWKVisitedLinkStore;
class WebProcessPool;

class SWKProcessPool : public Natives::SWKProcessPool {
    friend class Natives::SWKProcessPool;
public:
    static Native::PassLocalRef<SWKProcessPool> create(Ref<WebProcessPool>);
    ~SWKProcessPool();

    WebProcessPool& processPool() { return *m_processPool; }

protected:
    void setCacheModel(int32_t) override;
    void setMaximumNumberOfProcesses(int32_t) override;

    void setDownloadDelegate(Native::PassLocalRef<Natives::SWKDownloadDelegate>) override;
    void setGeolocationProvider(Native::PassLocalRef<Natives::SWKGeolocationProvider>) override;
    void setNotificationProvider(Native::PassLocalRef<Natives::SWKNotificationProvider>) override;

    Native::PassLocalRef<Natives::SWKApplicationCacheManager> getApplicationCacheManager() override;
    Native::PassLocalRef<Natives::SWKCookieManager> getCookieManager() override;
    Native::PassLocalRef<Natives::SWKIconDatabase> getIconDatabase() override;
    void setIconDatabaseEnabled(bool) override;
    Native::PassLocalRef<Natives::SWKKeyValueStorageManager> getKeyValueStorageManager() override;
    Native::PassLocalRef<Natives::SWKResourceCacheManager> getResourceCacheManager() override;
    Native::PassLocalRef<Natives::SWKVisitedLinkStore> getVisitedLinkStore() override;
    void warmInitialProcess() override;

private:
    SWKProcessPool();
    SWKProcessPool(const std::string&);
    SWKProcessPool(Native::PassLocalRef<SWKProcessPoolConfiguration>);

    void setProcessPool(Ref<WebProcessPool>);

    WKTypeRef initializeInjectedBundleClient();

    static WKTypeRef getInjectedBundleInitializationUserData(WKContextRef, const void* clientInfo);
    WKTypeRef getInjectedBundleInitializationUserData();

    RefPtr<WebProcessPool> m_processPool;
    void* m_platformBundle;

    RefPtr<GeolocationManager> m_geolocationManager;
    RefPtr<NotificationManager> m_notificationManager;

    Native::GlobalRef<SWKApplicationCacheManager> m_applicationCacheManager;
    Native::GlobalRef<SWKCookieManager> m_cookieManager;
    Native::GlobalRef<SWKIconDatabase> m_iconDatabase;
    Native::GlobalRef<SWKKeyValueStorageManager> m_storageManager;
    Native::GlobalRef<SWKResourceCacheManager> m_cacheManager;
    Native::GlobalRef<SWKVisitedLinkStore> m_visitedLinkStore;
};

}

#endif // SWKProcessPool_h
