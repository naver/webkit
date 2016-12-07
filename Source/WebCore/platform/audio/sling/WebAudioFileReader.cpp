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
#include "WebAudioFileReader.h"

#include <media/MediaFormat.h>

#include <assert.h>

namespace webkit {

WebAudioFileReader::WebAudioFileReader()
    : m_audioFile(media::AudioFile::create())
    , m_channelsPerFrame(0)
    , m_sampleRate(0)
    , m_bitsPerSample(0)
    , m_numberOfFrames(0)
    , m_errorCode(0)
{
}

WebAudioFileReader::~WebAudioFileReader()
{
    m_audioFile->reset();
}

int32_t WebAudioFileReader::getChannelsPerFrame()
{
    return m_channelsPerFrame;
}

int32_t WebAudioFileReader::getSampleRate()
{
    return m_sampleRate;
}

int64_t WebAudioFileReader::getNumberOfFrames()
{
    return m_numberOfFrames;
}

int64_t WebAudioFileReader::writeInputData(const std::vector<char>& data, int64_t length)
{
    return m_audioFile->writeInputData(reinterpret_cast<const int8_t*>(data.data()), length);
}

bool WebAudioFileReader::prepare()
{
    m_audioFile->setOnCompletionListener([=] (media::AudioFile&) {
        Managed::WebAudioFileReader::audioFileCompletion();
    });

    m_audioFile->setOnErrorListener([=] (media::AudioFile&, int32_t errorCode) {
        m_errorCode = errorCode;
    });

    m_audioFile->setOnSampleAvailableListener([=] (media::AudioFile&, const float samples[], int64_t samplesCount) {
        assert(samplesCount % m_channelsPerFrame == 0);
        m_numberOfFrames += samplesCount / m_channelsPerFrame;

        std::vector<float> samplesCopy(samplesCount);
        memcpy(samplesCopy.data(), samples, sizeof(float) * samplesCount);
        Managed::WebAudioFileReader::audioFileSampleAvailable(samplesCopy, samplesCount);
    });

    m_audioFile->prepare();
    if (m_errorCode)
        return false;

    std::shared_ptr<media::MediaFormat> audioFormat = m_audioFile->getOutputFormat();
    if (!audioFormat)
        return false;

    m_channelsPerFrame = audioFormat->getInteger(media::MediaFormat::KEY_CHANNEL_COUNT);
    m_sampleRate = audioFormat->getInteger(media::MediaFormat::KEY_SAMPLE_RATE);

    return true;
}

void WebAudioFileReader::start()
{
    m_audioFile->start();
}

void WebAudioFileReader::signalEndOfInputStream()
{
    m_audioFile->signalEndOfInputStream();
}

void WebAudioFileReader::INIT()
{
    nativeCreate();

    m_audioFile->setDataSource([=] (int64_t offset, int64_t length) {
        Managed::WebAudioFileReader::audioFileRequestInputData(offset, length);
    });
}

void WebAudioFileReader::INIT(const std::string& url)
{
    nativeCreate();

    m_audioFile->setDataSource(url);
}

} // namespace webkit

using namespace webkit;

namespace WebKit {
namespace Managed {

void WebAudioFileReader::INIT()
{
}

void WebAudioFileReader::INIT(const std::string&)
{
}

}
} // namespace WebKit
