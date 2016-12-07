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

#ifndef AudioDestinationSling_h
#define AudioDestinationSling_h

#include "AudioBus.h"
#include "AudioDestination.h"
#include "AudioIOCallback.h"
#include "AudioPullFIFO.h"
#include "AudioSourceProvider.h"
#include "WebAudioDestination.h"

#include <wtf/RefPtr.h>
#include <wtf/Vector.h>

#include <onig/GlobalRef.h>

namespace WebCore {

class AudioDestinationSling : public AudioDestination, public AudioSourceProvider, public WebKit::WebAudioDestination::Client {
public:
    AudioDestinationSling(AudioIOCallback&, const String& inputDeviceId, unsigned numberOfInputChannels, unsigned numberOfOutputChannels, float sampleRate);
    virtual ~AudioDestinationSling();

private:
    void render(size_t numberOfFrames, const Vector<float*>& ioData);
    void setIsPlaying(bool);

    // AudioDestination
    void start() override;
    void stop() override;

    bool isPlaying() override { return m_isPlaying; }
    float sampleRate() const override { return m_sampleRate; }

    // AudioSourceProvider
    void provideInput(AudioBus* bus, size_t framesToProcess) override;

    // WebKit::WebAudioDestination::Client
    void audioDestinationRender(int64_t numberOfFrames) override;

private:
    unsigned long m_numberOfOutputChannels;

    AudioIOCallback& m_callback;
    RefPtr<AudioBus> m_renderBus;
    std::unique_ptr<AudioPullFIFO> m_fifo;

    float m_sampleRate;
    bool m_isPlaying;

    Native::GlobalRef<WebKit::WebAudioDestination> m_backend;
};

} // namespace WebCore

#endif // AudioDestinationSling_h
