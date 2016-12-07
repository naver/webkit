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
#include "WebAudioDestinationNatives.h"

namespace WebKit {

Native::PassLocalRef<WebAudioDestination> WebAudioDestination::create(Client& client, int32_t destinationDisposition)
{
    Native::LocalRef<WebAudioDestination> audio = Natives::WebAudioDestination::create(destinationDisposition).as<WebAudioDestination>();
    audio->m_client = &client;
    return audio.release();
}

WebAudioDestination::WebAudioDestination()
    : m_client(nullptr)
{
}

WebAudioDestination& destination(Natives::WebAudioDestination* audio)
{
    return *static_cast<WebAudioDestination*>(audio);
}

} // namespace WebKit

namespace WebKit {
namespace Natives {

WebAudioDestination* WebAudioDestination::nativeCreate()
{
    return new ::WebKit::WebAudioDestination();
}

void WebAudioDestination::audioDestinationRender(int64_t numberOfFrames)
{
    destination(this).m_client->audioDestinationRender(numberOfFrames);
}

} // namespace Natives
} // namespace WebKit

