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

#ifndef WebAudioFileReader_h
#define WebAudioFileReader_h

#include "WebAudioFileReaderNativesBase.h"

namespace WebKit {

class WebAudioFileReader final : public Natives::WebAudioFileReader {
    friend class Natives::WebAudioFileReader;
public:
    class Client {
    public:
        virtual void audioFileRequestInputData(int64_t offset, int64_t length) = 0;
        virtual void audioFileCompletion() = 0;
        virtual void audioFileSampleAvailable(const Native::ImmutableArray<float>& data, int64_t length) = 0;
    };

    static Native::PassLocalRef<WebAudioFileReader> create(Client&);
    static Native::PassLocalRef<WebAudioFileReader> create(Client&, const std::string& url);
    static Native::PassLocalRef<WebAudioFileReader> create() = delete;
    static Native::PassLocalRef<WebAudioFileReader> create(const std::string& url) = delete;
    ~WebAudioFileReader() = default;

private:
    WebAudioFileReader();

    Client* m_client;
};

}

#endif // WebAudioFileReader_h
