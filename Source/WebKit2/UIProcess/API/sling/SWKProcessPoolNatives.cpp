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

#include "config.h"
#include "SWKProcessPoolNatives.h"

#include "DownloadClient.h"
#include "GeolocationManager.h"
#include "NotificationManager.h"
#include "SWKApplicationCacheManagerNatives.h"
#include "SWKCookieManagerNatives.h"
#include "SWKGeolocationManagerNatives.h"
#include "SWKGeolocationProviderNatives.h"
#include "SWKIconDatabaseNatives.h"
#include "SWKKeyValueStorageManagerNatives.h"
#include "SWKNotificationProviderNatives.h"
#include "SWKProcessPoolConfigurationNatives.h"
#include "SWKResourceCacheManagerNatives.h"
#include "SWKVisitedLinkStoreNatives.h"
#include "WKAPICast.h"
#include "WebCookieManagerProxy.h"
#include "WebIconDatabase.h"
#include "WebGeolocationManagerProxy.h"
#include "WebNotificationManagerProxy.h"
#include "WebProcessPool.h"
#include <WebCore/FileSystem.h>
#include <WebCore/IconDatabase.h>
#include <cutils/log.h>
#include <dlfcn.h>

namespace WebKit {

Native::PassLocalRef<SWKProcessPool> SWKProcessPool::create(Ref<WebProcessPool> webProcessPool)
{
    Native::LocalRef<SWKProcessPool> processPool = Natives::SWKProcessPool::create();
    processPool->setProcessPool(WTFMove(webProcessPool));
    return processPool;
}

SWKProcessPool::SWKProcessPool()
    : m_platformBundle(nullptr)
{
    WTF::initializeUIThread();
}

SWKProcessPool::SWKProcessPool(const std::string& injectedBundlePath)
    : m_platformBundle(nullptr)
{
    WTF::initializeUIThread();
    auto configuration = API::ProcessPoolConfiguration::create();
    configuration->setInjectedBundlePath(String::fromUTF8(injectedBundlePath.c_str()));
    setProcessPool(WebProcessPool::create(configuration));
}

SWKProcessPool::SWKProcessPool(Native::PassLocalRef<SWKProcessPoolConfiguration> configuration)
    : m_platformBundle(nullptr)
{
    WTF::initializeUIThread();
    setProcessPool(WebProcessPool::create(configuration->configuration()));
}

SWKProcessPool::~SWKProcessPool()
{
}

void SWKProcessPool::setProcessPool(Ref<WebProcessPool> context)
{
    m_processPool = WTFMove(context);

    m_geolocationManager = GeolocationManager::create(processPool().supplement<WebGeolocationManagerProxy>());
    m_notificationManager = NotificationManager::create(processPool().supplement<WebNotificationManagerProxy>());

    WKContextInjectedBundleClientV1 injectedBundleClient = {
        { 1, this },
        0, // didReceiveMessageFromInjectedBundle,
        0, // didReceiveSynchronousMessageFromInjectedBundle,
        getInjectedBundleInitializationUserData
    };
    m_processPool->initializeInjectedBundleClient(&injectedBundleClient.base);
}

// NOTE: Must be implemented by InjectedBundle's as a function named "WKContextInitializeInjectedBundleClient".
extern "C" typedef WKTypeRef (*WKContextInitializeInjectedBundleClientFunctionPtr)(WKContextRef);

WKTypeRef SWKProcessPool::initializeInjectedBundleClient()
{
    if (m_platformBundle || processPool().injectedBundlePath().length() == 0)
        return nullptr;

    const char *error;

    m_platformBundle = dlopen(WebCore::fileSystemRepresentation(processPool().injectedBundlePath()).data(), RTLD_LOCAL);
    if (!m_platformBundle) {
        ALOGE("InjectedBundle dlopen error [%s]", dlerror());
        return nullptr;
    }

    WKContextInitializeInjectedBundleClientFunctionPtr initializeFunction = 0;
    initializeFunction = reinterpret_cast<WKContextInitializeInjectedBundleClientFunctionPtr>(dlsym(m_platformBundle, "WKContextInitializeInjectedBundleClient"));

    if (!initializeFunction && (error = dlerror()) != NULL)  {
        ALOGE("InjectedBundle dlsym error [%s]", error);
        return nullptr;
    }

    processPool().configuration().setFullySynchronousModeIsAllowedForTesting(true);

    return initializeFunction(toAPI(&processPool()));
}

WKTypeRef SWKProcessPool::getInjectedBundleInitializationUserData(WKContextRef context, const void* clientInfo)
{
    return static_cast<SWKProcessPool*>(const_cast<void*>(clientInfo))->getInjectedBundleInitializationUserData();
}

WKTypeRef SWKProcessPool::getInjectedBundleInitializationUserData()
{
    return initializeInjectedBundleClient();
}

static CacheModel toCacheModel(int32_t cacheModel)
{
    switch (cacheModel) {
    case SWKProcessPool::CACHE_MODEL_DOCUMENT_VIEWER:
        return CacheModelDocumentViewer;
    case SWKProcessPool::CACHE_MODEL_DOCUMENT_BROWSER:
        return CacheModelDocumentBrowser;
    case SWKProcessPool::CACHE_MODEL_PRIMARY_WEBBROWSER:
        return CacheModelPrimaryWebBrowser;
    }
    ASSERT_NOT_REACHED();
    return CacheModelDocumentViewer;
}

void SWKProcessPool::setCacheModel(int32_t cacheModel)
{
    processPool().setCacheModel(toCacheModel(cacheModel));
}

void SWKProcessPool::setMaximumNumberOfProcesses(int32_t maximumNumberOfProcesses)
{
    processPool().setMaximumNumberOfProcesses(maximumNumberOfProcesses);
}

void SWKProcessPool::warmInitialProcess()
{
    processPool().warmInitialProcess();
}

void SWKProcessPool::setDownloadDelegate(Native::PassLocalRef<Natives::SWKDownloadDelegate> downloadDelegate)
{
    if (!downloadDelegate) {
        processPool().setDownloadClient(nullptr);
        return;
    }

    processPool().setDownloadClient(std::make_unique<DownloadClient>(*this, downloadDelegate));
}

void SWKProcessPool::setGeolocationProvider(Native::PassLocalRef<Natives::SWKGeolocationProvider> provider)
{
    m_geolocationManager->setGeolocationProvider(provider);
}

void SWKProcessPool::setNotificationProvider(Native::PassLocalRef<Natives::SWKNotificationProvider> provider)
{
    m_notificationManager->setNotificationProvider(provider);
}

Native::PassLocalRef<Natives::SWKApplicationCacheManager> SWKProcessPool::getApplicationCacheManager()
{
    if (!m_applicationCacheManager)
        m_applicationCacheManager = SWKApplicationCacheManager::create(toAPI(&processPool()));

    return m_applicationCacheManager;
}

Native::PassLocalRef<Natives::SWKCookieManager> SWKProcessPool::getCookieManager()
{
    if (!m_cookieManager)
        m_cookieManager = SWKCookieManager::create(processPool().supplement<WebCookieManagerProxy>());

    return m_cookieManager;
}

Native::PassLocalRef<Natives::SWKIconDatabase> SWKProcessPool::getIconDatabase()
{
    if (!m_iconDatabase)
        m_iconDatabase = SWKIconDatabase::create(processPool().iconDatabase());

    return m_iconDatabase;
}

void SWKProcessPool::setIconDatabaseEnabled(bool enable)
{
    getIconDatabase();
    WebIconDatabase* iconDatabase = processPool().iconDatabase();
    if (iconDatabase->isOpen() == enable)
        return;

    if (enable) {
        // This implicitly enables the database on UI process side.
        processPool().setIconDatabasePath(processPool().iconDatabasePath());
    } else
        iconDatabase->close();
}

Native::PassLocalRef<Natives::SWKKeyValueStorageManager> SWKProcessPool::getKeyValueStorageManager()
{
    if (!m_storageManager)
        m_storageManager = SWKKeyValueStorageManager::create(toAPI(&processPool()));

    return m_storageManager;
}

Native::PassLocalRef<Natives::SWKResourceCacheManager> SWKProcessPool::getResourceCacheManager()
{
    if (!m_cacheManager)
        m_cacheManager = SWKResourceCacheManager::create(toAPI(&processPool()));

    return m_cacheManager;
}

Native::PassLocalRef<Natives::SWKVisitedLinkStore> SWKProcessPool::getVisitedLinkStore()
{
    if (!m_visitedLinkStore)
        m_visitedLinkStore = SWKVisitedLinkStore::create(processPool().visitedLinkStore());

    return m_visitedLinkStore;
}

namespace Natives {

SWKProcessPool* SWKProcessPool::nativeCreate()
{
    return new ::WebKit::SWKProcessPool();
}

SWKProcessPool* SWKProcessPool::nativeCreateWithInjectedBundlePath(std::string injectedBundlePath)
{
    return new ::WebKit::SWKProcessPool(injectedBundlePath);
}

SWKProcessPool* SWKProcessPool::nativeCreateWithConfiguration(Native::PassLocalRef<Natives::SWKProcessPoolConfiguration> configuration)
{
    return new ::WebKit::SWKProcessPool(configuration.as<::WebKit::SWKProcessPoolConfiguration>());
}

}

}
