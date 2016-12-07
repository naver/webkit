/*
 * Copyright (C) 2014-2015 Naver Corp. All rights reserved.
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
#include "VibrationProvider.h"

#if ENABLE(VIBRATION)
#include "SWKWebContentNatives.h"
#include "WebVibrationProxy.h"

namespace WebKit {

static inline VibrationProvider* toVibrationProvider(const void* clientInfo)
{
    return static_cast<VibrationProvider*>(const_cast<void*>(clientInfo));
}

VibrationProvider::VibrationProvider(const SWKWebContent& webContent)
    : m_vibrationProxy(webContent.webPage().vibration())
{
    WKVibrationProviderV0 vibrationProvider = {
        {
            0,       // version
            this,    // clientInfo
        },
        vibrateCallback,
        cancelVibrationCallback
    };

    m_vibrationProxy->initializeProvider(&vibrationProvider.base);
}

VibrationProvider::~VibrationProvider()
{
    m_vibrationProxy->initializeProvider(nullptr);
}

void VibrationProvider::vibrateCallback(WKVibrationRef, uint32_t duration, const void* clientInfo)
{
    VibrationProvider* provider = toVibrationProvider(clientInfo);
    if (provider->m_vibrationProvider)
        provider->m_vibrationProvider->vibrate(duration);
}

void VibrationProvider::cancelVibrationCallback(WKVibrationRef, const void* clientInfo)
{
    VibrationProvider* provider = toVibrationProvider(clientInfo);
    if (provider->m_vibrationProvider)
        provider->m_vibrationProvider->cancelVibration();
}

} // namespace WebKit

#endif // ENABLE(VIBRATION)
