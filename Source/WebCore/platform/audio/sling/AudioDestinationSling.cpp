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

#if ENABLE(WEB_AUDIO)

#include "AudioDestinationSling.h"

#include "AudioChannel.h"
#include "AudioSourceProvider.h"
#include "Logging.h"

namespace WebCore {

const int renderBufferSize = 128;
const size_t fifoSize = 8192;

std::unique_ptr<AudioDestination> AudioDestination::create(AudioIOCallback& callback, const String& inputDeviceId, unsigned numberOfInputChannels, unsigned numberOfOutputChannels, float sampleRate)
{
    return std::make_unique<AudioDestinationSling>(callback, inputDeviceId, numberOfInputChannels, numberOfOutputChannels, sampleRate);
}

float AudioDestination::hardwareSampleRate()
{
    return WebKit::WebAudioDestination::audioHardwareSampleRate();
}

unsigned long AudioDestination::maxChannelCount()
{
    return WebKit::WebAudioDestination::audioHardwareOutputChannels();
}

AudioDestinationSling::AudioDestinationSling(AudioIOCallback& callback, const String& inputDeviceId, unsigned numberOfInputChannels, unsigned numberOfOutputChannels, float sampleRate)
    : m_numberOfOutputChannels(maxChannelCount())
    , m_callback(callback)
    , m_renderBus(AudioBus::create(m_numberOfOutputChannels, renderBufferSize, false))
    , m_fifo(new AudioPullFIFO(*this, numberOfOutputChannels, fifoSize, renderBufferSize))
    , m_sampleRate(sampleRate)
    , m_isPlaying(false)
    , m_backend(WebKit::WebAudioDestination::create(*this, WebKit::WebAudioDestination::DESTINATION_DISPOSITION_DEFAULT))
{
    m_backend->setSampleRate(m_sampleRate);
}

AudioDestinationSling::~AudioDestinationSling()
{
    stop();
}

void AudioDestinationSling::render(size_t numberOfFrames, const Vector<float*>& ioData)
{
    for (unsigned i = 0; i < m_numberOfOutputChannels; ++i)
        m_renderBus->setChannelMemory(i, ioData[i], numberOfFrames);

    m_fifo->consume(m_renderBus.get(), numberOfFrames);
}

void AudioDestinationSling::setIsPlaying(bool isPlaying)
{
    if (m_isPlaying == isPlaying)
        return;

    m_isPlaying = isPlaying;
    m_callback.isPlayingDidChange();
}

void AudioDestinationSling::start()
{
    bool result = m_backend->start();

    if (!result)
        setIsPlaying(true);
}

void AudioDestinationSling::stop()
{
    bool result = m_backend->stop();

    if (!result)
        setIsPlaying(false);
}

void AudioDestinationSling::provideInput(AudioBus* bus, size_t framesToProcess)
{
    // FIXME: Add support for local/live audio input.
    m_callback.render(0, bus, framesToProcess);
}

void AudioDestinationSling::audioDestinationRender(int64_t numberOfFrames)
{
    ASSERT(numberOfFrames + renderBufferSize <= fifoSize);

    std::vector<std::vector<float>> floatArrays(m_numberOfOutputChannels);
    Vector<float*> ioData;

    for (auto& floatArray : floatArrays) {
        floatArray.reserve(numberOfFrames);
        ioData.append(floatArray.data());
    }

    render(numberOfFrames, ioData);

    std::vector<float> interleavedFloatArray;
    size_t dest = 0;
    interleavedFloatArray.reserve(numberOfFrames * m_numberOfOutputChannels);

    for (size_t i = 0; i < numberOfFrames; ++i)
        for (unsigned long channel = 0; channel < m_numberOfOutputChannels; ++channel)
            interleavedFloatArray[dest++] = floatArrays[channel][i];

    m_backend->render(Native::ImmutableArray<float>(interleavedFloatArray.data(), interleavedFloatArray.capacity()), interleavedFloatArray.capacity());
}

} // namespace WebCore

#endif // ENABLE(WEB_AUDIO)
