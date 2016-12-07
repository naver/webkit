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
#include "GeolocationManager.h"

#include "WKAPICast.h"
#include "WKGeolocationManager.h"
#include "WebGeolocationManagerProxy.h"
#include "WebGeolocationPosition.h"

namespace WebKit {

static inline GeolocationManager* toGeolocationManager(const void* clientInfo)
{
    return static_cast<GeolocationManager*>(const_cast<void*>(clientInfo));
}

static void startUpdatingCallback(WKGeolocationManagerRef, const void* clientInfo)
{
    toGeolocationManager(clientInfo)->startUpdating();
}

static void stopUpdatingCallback(WKGeolocationManagerRef, const void* clientInfo)
{
    toGeolocationManager(clientInfo)->stopUpdating();
}

PassRefPtr<GeolocationManager> GeolocationManager::create(WebGeolocationManagerProxy* geolocationManager)
{
    return adoptRef(new GeolocationManager(geolocationManager));
}

void GeolocationManager::setGeolocationProvider(Native::PassLocalRef<Natives::SWKGeolocationProvider> provider)
{
    m_geolocationProvider = provider;
}

void GeolocationManager::startUpdating()
{
    if (!m_geolocationProvider)
        return;

    m_geolocationProvider->startUpdating(m_geolocationManager);
}

void GeolocationManager::stopUpdating()
{
    if (!m_geolocationProvider)
        return;

    m_geolocationProvider->stopUpdating(m_geolocationManager);
}

GeolocationManager::GeolocationManager(WebGeolocationManagerProxy* geolocationManager)
    : m_geolocationManager(SWKGeolocationManager::create(*geolocationManager))
{
    WKGeolocationProviderV1 provider = {
        {
            1, // version
            this, // clientInfo
        },
        startUpdatingCallback,
        stopUpdatingCallback,
        0 // setEnableHighAccuracy
    };

    geolocationManager->initializeProvider(&provider.base);
}

GeolocationManager::~GeolocationManager()
{
    m_geolocationManager->webGeolocationManager().initializeProvider(nullptr);
}

} // namespace WebKit
