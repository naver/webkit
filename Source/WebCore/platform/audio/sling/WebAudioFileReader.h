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

#include "WebAudioFileReaderManagedBase.h"

#include <media/AudioFile.h>

namespace webkit {

namespace Managed = WebKit::Managed;

class WebAudioFileReader final : public WebKit::Managed::WebAudioFileReader {
    friend class WebKit::Managed::WebAudioFileReader;
public:
    WEBKIT_EXPORT ~WebAudioFileReader();
    
    WEBKIT_EXPORT int32_t getChannelsPerFrame() override;    
    WEBKIT_EXPORT int32_t getSampleRate() override;
    WEBKIT_EXPORT int64_t getNumberOfFrames() override;

    WEBKIT_EXPORT int64_t writeInputData(const std::vector<char>& data, int64_t length) override;

    WEBKIT_EXPORT bool prepare() override;

    WEBKIT_EXPORT void start() override;
    WEBKIT_EXPORT void signalEndOfInputStream() override;

private:
    WebAudioFileReader();

    void INIT() override;
    void INIT(const std::string& url) override;

    std::shared_ptr<media::AudioFile> m_audioFile;
    int32_t m_channelsPerFrame;
    int32_t m_sampleRate;
    int32_t m_bitsPerSample;
    int64_t m_numberOfFrames;
    int32_t m_errorCode;
};

} // namespace webkit

#endif // WebAudioFileReader_h
