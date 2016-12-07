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
#include "SWKApplicationCacheManagerNatives.h"

#include "SWKSecurityOriginNatives.h"
#include "ValueCallbackNatives.h"
#include "WKAPICast.h"
#include "WKApplicationCacheManager.h"
#include "WKArray.h"
#include "WKSecurityOriginRef.h"
#include "WKString.h"

#include <NativesVector.h>

#include <onig/GlobalRef.h>

using namespace WebCore;

namespace WebKit {

Native::PassLocalRef<SWKApplicationCacheManager> SWKApplicationCacheManager::create(WKContextRef context)
{
    Native::LocalRef<SWKApplicationCacheManager> manager = Natives::SWKApplicationCacheManager::create().as<SWKApplicationCacheManager>();
    manager->m_applicationCacheManager = WKContextGetApplicationCacheManager(context);
    return manager;
}

typedef std::pair<Native::GlobalRef<SWKApplicationCacheManager>, Native::GlobalRef<ValueCallback>> ApplicationCacheManagerFunctionContext;

static void getApplicationCacheOriginsCallback(WKArrayRef wkOrigins, WKErrorRef, void* context)
{
    auto functionContext = std::unique_ptr<ApplicationCacheManagerFunctionContext>(reinterpret_cast<ApplicationCacheManagerFunctionContext*>(context));
    Native::LocalRef<Native::Natives::Vector> origins = Native::Natives::Vector::create();
    const size_t originsCount = WKArrayGetSize(wkOrigins);
    for (size_t i = 0; i < originsCount; ++i) {
        WKSecurityOriginRef securityOriginRef = static_cast<WKSecurityOriginRef>(WKArrayGetItemAtIndex(wkOrigins, i));
        Native::LocalRef<SWKSecurityOrigin> origin = SWKSecurityOrigin::create(toImpl(securityOriginRef));
        origins->add(origin);
    }

    functionContext->second->onReceiveObject(origins);
}

void SWKApplicationCacheManager::getApplicationCacheOrigins(Native::PassLocalRef<Natives::ValueCallback> callback)
{
    WKApplicationCacheManagerGetApplicationCacheOrigins(m_applicationCacheManager.get(), new ApplicationCacheManagerFunctionContext(this, callback), getApplicationCacheOriginsCallback);
}

void SWKApplicationCacheManager::deleteEntriesForOrigin(Native::PassLocalRef<Natives::SWKSecurityOrigin> origin)
{
    WKApplicationCacheManagerDeleteEntriesForOrigin(m_applicationCacheManager.get(), toAPI(origin.as<SWKSecurityOrigin>()->origin()));
}

void SWKApplicationCacheManager::deleteAllEntries()
{
    WKApplicationCacheManagerDeleteAllEntries(m_applicationCacheManager.get());
}

namespace Natives {

SWKApplicationCacheManager* SWKApplicationCacheManager::nativeCreate()
{
    return new ::WebKit::SWKApplicationCacheManager;
}

}
}
