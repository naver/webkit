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
#include "WebAudioDestination.h"

#include <media/AudioFormat.h>
#include <util/LogHelper.h>

#include <assert.h>

using namespace media;

namespace webkit {

WebAudioDestination::WebAudioDestination()
    : m_sampleRate(AudioTrack::getNativeOutputSampleRate(AudioFormat::STREAM_MUSIC))
    , m_audioBufferSize(0)
    , m_renderNumberOfFrames(0)
{
}

WebAudioDestination::~WebAudioDestination()
{
}

bool WebAudioDestination::start()
{
    if (!m_track)
        reset();

    m_track->play();

    if (m_track->getPlayState() != AudioTrack::PLAYSTATE_PLAYING)
        return false;

    m_track->setPositionNotificationPeriod(m_renderNumberOfFrames);

    return true;
}
    
bool WebAudioDestination::stop()
{
    if (!m_track)
        return false;

    m_track->stop();

    if (m_track->getPlayState() != AudioTrack::PLAYSTATE_STOPPED)
        return false;

    m_track->setPositionNotificationPeriod(0);

    return true;
}

void WebAudioDestination::setSampleRate(float sampleRate)
{
    if (sampleRate == m_sampleRate)
        return;

    m_sampleRate = sampleRate;

    reset();
}

void WebAudioDestination::render(const std::vector<float>& audioData, int64_t sizeInFloats)
{
    int32_t result = m_track->write((float*)audioData.data(), 0, sizeInFloats, AudioTrack::WRITE_NON_BLOCKING);
    if (result == AudioTrack::ERROR_BAD_VALUE) {
        LOGE("WebAudioDestination.render(): ERROR_BAD_VALUE");
        return;
    } else if (result == AudioTrack::ERROR_INVALID_OPERATION) {
        LOGE("WebAudioDestination.render(): ERROR_INVALID_OPERATION");
        return;
    }
}

void WebAudioDestination::reset()
{
    if (m_track)
        m_track->release();

    const int32_t bufferSize = AudioTrack::getMinBufferSize(m_sampleRate, AudioFormat::CHANNEL_OUT_STEREO, AudioFormat::ENCODING_PCM_FLOAT) * 8;
    const int32_t bufferSizeInNumberOfFrames = bufferSize / 8;

    m_track = AudioTrack::create(AudioFormat::STREAM_MUSIC, m_sampleRate, AudioFormat::CHANNEL_OUT_STEREO,
        AudioFormat::ENCODING_PCM_FLOAT, bufferSize, AudioTrack::MODE_STREAM);

    m_track->setPlaybackPositionUpdateListener({
        [=] (AudioTrack&) {
            onMarkerReached();
        },
        [=] (AudioTrack&) {
            onPeriodicNotification();
        }
    });

    m_audioBufferSize = bufferSize;
    m_renderNumberOfFrames = bufferSizeInNumberOfFrames / 2;
    audioDestinationRender(bufferSizeInNumberOfFrames);
}

void WebAudioDestination::onMarkerReached()
{
}

void WebAudioDestination::onPeriodicNotification()
{
    audioDestinationRender(m_renderNumberOfFrames);
}

void WebAudioDestination::INIT(int32_t destinationDisposition)
{
    nativeCreate();
}

} // namespace webkit

using namespace webkit;

namespace WebKit {
namespace Managed {

void WebAudioDestination::INIT(int32_t)
{
}

float WebAudioDestination::audioHardwareSampleRate()
{
    return AudioTrack::getNativeOutputSampleRate(AudioFormat::STREAM_MUSIC);
}

int32_t WebAudioDestination::audioHardwareOutputChannels()
{
    return 2;
}

}
} // namespace WebKit
