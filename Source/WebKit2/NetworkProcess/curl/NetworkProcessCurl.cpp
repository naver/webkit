/*
 * Copyright (C) 2013 Naver Corp. All rights reserved.
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
#include "NetworkProcess.h"

#include "NetworkProcessCreationParameters.h"
#include "WebCookieManager.h"
#include <WebCore/NotImplemented.h>

using namespace WebCore;

namespace WebKit {

void NetworkProcess::platformInitializeNetworkProcess(const NetworkProcessCreationParameters& parameters)
{
    notImplemented();
}

void NetworkProcess::platformTerminate()
{
    notImplemented();
}

void NetworkProcess::allowSpecificHTTPSCertificateForHost(const WebCore::CertificateInfo&, const String& host)
{
    notImplemented();
}

void NetworkProcess::clearCacheForAllOrigins(uint32_t cachesToClear)
{
    notImplemented();
}

// FIXME: This should take a session ID so we can identify which disk cache to delete.
void NetworkProcess::clearDiskCache(std::chrono::system_clock::time_point, std::function<void ()>)
{
    notImplemented();
}

void NetworkProcess::platformSetCacheModel(CacheModel cacheModel)
{
}

} // namespace WebKit
