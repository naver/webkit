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

#include "AudioFileReader.h"
#include "AudioBus.h"
#include "WebAudioFileReader.h"

#include <wtf/text/CString.h>

#include <condition_variable>
#include <mutex>

#include <onig/GlobalRef.h>
#include <safeint/safeint.h>

namespace WebCore {

class AudioFileReader final : public WebKit::WebAudioFileReader::Client {
public:
    AudioFileReader(const void* data, size_t dataSize, bool mixToMono, float sampleRate);
    AudioFileReader(const char* filePath, bool mixToMono, float sampleRate);
    ~AudioFileReader();

    PassRefPtr<AudioBus> createBus(bool mixToMono, float sampleRate);

private:
    void audioFileRequestInputData(int64_t offset, int64_t length) override;
    void audioFileCompletion() override;
    void audioFileSampleAvailable(const Native::ImmutableArray<float>& data, int64_t length) override;

    void waitForCompletion();

private:
    bool m_mixToMono;
    float m_sampleRate;
    std::pair<const char*, size_t> m_data;
    std::vector<float> m_samples;
    bool m_complete;
    Native::GlobalRef<WebKit::WebAudioFileReader> m_backend;
};

AudioFileReader::AudioFileReader(const void* data, size_t dataSize, bool mixToMono, float sampleRate)
    : m_mixToMono(mixToMono)
    , m_sampleRate(sampleRate)
    , m_data(reinterpret_cast<const char*>(data), dataSize)
    , m_complete(false)
    , m_backend(WebKit::WebAudioFileReader::create(*this))
{
}

AudioFileReader::AudioFileReader(const char* filePath, bool mixToMono, float sampleRate)
    : m_mixToMono(mixToMono)
    , m_sampleRate(sampleRate)
    , m_complete(false)
    , m_backend(WebKit::WebAudioFileReader::create(*this, filePath))
{
}

AudioFileReader::~AudioFileReader()
{
    m_backend.reset();
}

PassRefPtr<AudioBus> AudioFileReader::createBus(bool mixToMono, float sampleRate)
{
    if (!m_backend->prepare())
        return nullptr;

    m_backend->start();

    if (!m_complete)
        return nullptr;

    int32_t numberOfChannels = m_backend->getChannelsPerFrame();
    int64_t numberOfFrames64 = m_backend->getNumberOfFrames();
    size_t numberOfFrames = safeint::integral_cast<size_t>(numberOfFrames64);

    RefPtr<AudioBus> audioBus = AudioBus::create(numberOfChannels, numberOfFrames);
    // FIXME: Get resampled output from file reader backend if possible.
    int32_t outputSampleRate = m_backend->getSampleRate();
    audioBus->setSampleRate(outputSampleRate);

    for (size_t i = 0; i < numberOfChannels; ++i) {
        audioBus->channel(i)->zero();
        float* busChannelData = audioBus->channel(i)->mutableData();
        for (size_t src = i, dest = 0; dest < numberOfFrames; src += numberOfChannels, ++dest)
            busChannelData[dest] = m_samples[src];
    }

    // If the bus needs no conversion then return as is.
    if ((!mixToMono || audioBus->numberOfChannels() == 1) && audioBus->sampleRate() == sampleRate)
        return audioBus.release();

    return AudioBus::createBySampleRateConverting(audioBus.get(), mixToMono, sampleRate);
}

void AudioFileReader::audioFileRequestInputData(int64_t offset, int64_t length)
{
    ASSERT(offset <= m_data.second);

    int64_t bytesToWrite = std::min<int64_t>(length, m_data.second - offset);
    int64_t writtenBytes = m_backend->writeInputData(Native::ImmutableArray<char>(m_data.first + offset, bytesToWrite), bytesToWrite);
    if (offset + length >= m_data.second)
        m_backend->signalEndOfInputStream();

    UNUSED_PARAM(writtenBytes);
}

void AudioFileReader::audioFileCompletion()
{
    m_complete = true;
}

void AudioFileReader::audioFileSampleAvailable(const Native::ImmutableArray<float>& data, int64_t length)
{
    m_samples.insert(m_samples.end(), data.data(), data.data() + length);
}

PassRefPtr<AudioBus> createBusFromInMemoryAudioFile(const void* data, size_t dataSize, bool mixToMono, float sampleRate)
{
    AudioFileReader reader(data, dataSize, mixToMono, sampleRate);
    return reader.createBus(mixToMono, sampleRate);
}

PassRefPtr<AudioBus> createBusFromAudioFile(const char* filePath, bool mixToMono, float sampleRate)
{
    AudioFileReader reader(filePath, mixToMono, sampleRate);
    return reader.createBus(mixToMono, sampleRate);
}
                                
void writeBusToAudioFile(AudioBus* bus, const char* filePath, double fileSampleRate)
{
}

} // namespace WebCore

#endif // ENABLE(WEB_AUDIO)
