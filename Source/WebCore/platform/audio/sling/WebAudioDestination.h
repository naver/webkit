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

#ifndef WebAudioDestination_h
#define WebAudioDestination_h

#include "WebAudioDestinationManagedBase.h"

#include <media/AudioTrack.h>

namespace webkit {

namespace Managed = WebKit::Managed;

class WebAudioDestination final : public WebKit::Managed::WebAudioDestination {
    friend class WebKit::Managed::WebAudioDestination;
public:
    WEBKIT_EXPORT ~WebAudioDestination();
    
    WEBKIT_EXPORT bool start() override;    
    WEBKIT_EXPORT bool stop() override;
    WEBKIT_EXPORT void setSampleRate(float) override;

    WEBKIT_EXPORT void render(const std::vector<float>& audioData, int64_t sizeInFloats) override;

private:
    WebAudioDestination();

    void reset();

    void onMarkerReached();
    void onPeriodicNotification();

    void INIT(int32_t) override;

    float m_sampleRate;
    int32_t m_audioBufferSize;
    int32_t m_renderNumberOfFrames;
    std::shared_ptr<media::AudioTrack> m_track;
};

} // namespace webkit

#endif // WebAudioDestination_h
