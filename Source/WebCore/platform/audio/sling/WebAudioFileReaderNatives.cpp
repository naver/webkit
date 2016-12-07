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
#include "WebAudioFileReaderNatives.h"

namespace WebKit {

Native::PassLocalRef<WebAudioFileReader> WebAudioFileReader::create(Client& client)
{
    Native::LocalRef<WebAudioFileReader> audio = Natives::WebAudioFileReader::create().as<WebAudioFileReader>();
    audio->m_client = &client;
    return audio.release();
}

Native::PassLocalRef<WebAudioFileReader> WebAudioFileReader::create(Client& client, const std::string& url)
{
    Native::LocalRef<WebAudioFileReader> audio = Natives::WebAudioFileReader::create(url).as<WebAudioFileReader>();
    audio->m_client = &client;
    return audio.release();
}

WebAudioFileReader::WebAudioFileReader()
    : m_client(nullptr)
{
}

WebAudioFileReader& reader(Natives::WebAudioFileReader* audio)
{
    return *static_cast<WebAudioFileReader*>(audio);
}

} // namespace WebKit

namespace WebKit {
namespace Natives {

WebAudioFileReader* WebAudioFileReader::nativeCreate()
{
    return new ::WebKit::WebAudioFileReader();
}

void WebAudioFileReader::audioFileRequestInputData(int64_t offset, int64_t length)
{
    reader(this).m_client->audioFileRequestInputData(offset, length);
}

void WebAudioFileReader::audioFileCompletion()
{
    reader(this).m_client->audioFileCompletion();
}

void WebAudioFileReader::audioFileSampleAvailable(const Native::ImmutableArray<float>& data, int64_t length)
{
    reader(this).m_client->audioFileSampleAvailable(data, length);
}

} // namespace Natives
} // namespace WebKit

