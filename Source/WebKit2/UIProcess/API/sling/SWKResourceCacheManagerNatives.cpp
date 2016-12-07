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
#include "SWKResourceCacheManagerNatives.h"

#include "ValueCallbackNatives.h"
#include "WKAPICast.h"
#include "WKArray.h"
#include "WKResourceCacheManager.h"
#include "WKRetainPtr.h"
#include "WKString.h"
#include <wtf/text/CString.h>

#include <onig/GlobalRef.h>

using namespace WebCore;

namespace WebKit {

Native::PassLocalRef<SWKResourceCacheManager> SWKResourceCacheManager::create(WKContextRef context)
{
    Native::LocalRef<SWKResourceCacheManager> manager = Natives::SWKResourceCacheManager::create().as<SWKResourceCacheManager>();
    manager->m_resourceCacheManager = WKContextGetResourceCacheManager(context);
    return manager;
}

typedef std::pair<Native::GlobalRef<SWKResourceCacheManager>, Native::GlobalRef<ValueCallback>> ResourceCacheManagerFunctionContext;

static void getCacheOriginsCallback(WKArrayRef cacheOrigins, WKErrorRef, void* context)
{
    auto functionContext = std::unique_ptr<ResourceCacheManagerFunctionContext>(static_cast<ResourceCacheManagerFunctionContext*>(context));
    const size_t length = WKArrayGetSize(cacheOrigins);
    for (size_t i = 0; i < length; ++i) {
        WKStringRef cacheOrigin = static_cast<WKStringRef>(WKArrayGetItemAtIndex(cacheOrigins, i));
        if (WKStringIsEmpty(cacheOrigin))
            continue;

        functionContext->second->onReceiveString(toWTFString(cacheOrigin).latin1().data());
    }
}

void SWKResourceCacheManager::getCacheOrigins(Native::PassLocalRef<Natives::ValueCallback> callback)
{
    WKResourceCacheManagerGetCacheOrigins(m_resourceCacheManager.get(), new ResourceCacheManagerFunctionContext(this, callback), getCacheOriginsCallback);
}

void SWKResourceCacheManager::clearCacheForOrigin(const std::string& protocol, const std::string& host, int32_t port, int32_t resourceCachesToClear)
{
    RefPtr<API::SecurityOrigin> securityOrigin = API::SecurityOrigin::create(String(protocol.data()), String(host.data()), port);
    WKResourceCacheManagerClearCacheForOrigin(m_resourceCacheManager.get(), toAPI(securityOrigin.get()), toAPI(resourceCachesToClear));
}

void SWKResourceCacheManager::clearCacheForAllOrigins(int32_t resourceCachesToClear)
{
    WKResourceCacheManagerClearCacheForAllOrigins(m_resourceCacheManager.get(), toAPI(resourceCachesToClear));
}

void SWKResourceCacheManager::setCachePolicy(int32_t resourceCachePolicy)
{
}

int32_t SWKResourceCacheManager::getCachePolicy()
{
    return 0;
}

namespace Natives {

SWKResourceCacheManager* SWKResourceCacheManager::nativeCreate()
{
    return new ::WebKit::SWKResourceCacheManager;
}

}
}
