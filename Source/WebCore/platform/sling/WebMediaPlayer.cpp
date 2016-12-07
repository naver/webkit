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
#include "WebMediaPlayer.h"

#include <media/MediaPlayer.h>
#include <opengl/EGLPbufferSurface.h>
#include <opengl/GLTextureStreamChannel.h>

#include <assert.h>

namespace webkit {

WebMediaPlayer::WebMediaPlayer()
    : m_frames(0)
    , m_initialized(false)
    , m_seeking(false)
    , m_error(0)
{
}

WebMediaPlayer::~WebMediaPlayer()
{
    reset();
}

void WebMediaPlayer::load(const std::string& url)
{
    if (m_error)
        return;

    reset();

    m_mediaPlayer->setDataSource(url);
    m_initialized = true;
    m_mediaPlayer->prepareAsync();
}

void WebMediaPlayer::cancelLoad()
{
    if (!m_initialized || m_error)
        return;

    reset();
    m_initialized = false;
}

void WebMediaPlayer::prepareToPlay()
{
}

void WebMediaPlayer::play()
{
    if (!m_initialized || m_error || m_mediaPlayer->isPlaying())
        return;

    m_mediaPlayer->start();
}

bool WebMediaPlayer::isPlaying()
{
    return m_mediaPlayer->isPlaying();
}

void WebMediaPlayer::pause()
{
    if (!m_initialized || m_error || !m_mediaPlayer->isPlaying())
        return;

    m_mediaPlayer->pause();
}

bool WebMediaPlayer::paused()
{
    return !m_initialized || m_error || !m_mediaPlayer->isPlaying();
}

float WebMediaPlayer::duration()
{
    float durationMsec = m_mediaPlayer->getDuration();
    return durationMsec * 0.001f;
}

float WebMediaPlayer::currentTime()
{
    float currentTimeMsec = m_mediaPlayer->getCurrentPosition();
    return currentTimeMsec * 0.001f;
}

void WebMediaPlayer::seek(float position)
{
    if (!m_initialized || m_error)
        return;

    m_seeking = true;

    m_mediaPlayer->seekTo(position * 1000.0f);
}

bool WebMediaPlayer::seeking()
{
    return m_seeking;
}

void WebMediaPlayer::setRate(float rate)
{
}

double WebMediaPlayer::rate()
{
    if (!m_initialized || m_error || !m_mediaPlayer->isPlaying())
        return 0.0;

    return 1.0;
}

void WebMediaPlayer::setVolume(float volume)
{
    m_mediaPlayer->setVolume(volume, volume);
}

bool WebMediaPlayer::supportsMuting()
{
    return false;
}

void WebMediaPlayer::setMuted(bool mute)
{
}

bool WebMediaPlayer::supportsScanning()
{
    return false;
}

bool WebMediaPlayer::requiresImmediateCompositing()
{
    return false;
}

bool WebMediaPlayer::canSaveMediaData()
{
    return false;
}

float WebMediaPlayer::naturalWidth()
{
    return m_mediaPlayer->getVideoWidth();
}

float WebMediaPlayer::naturalHeight()
{
    return m_mediaPlayer->getVideoHeight();
}

bool WebMediaPlayer::hasVideo()
{
    return m_mediaPlayer->getVideoHeight() > 0;
}

bool WebMediaPlayer::hasAudio()
{
    return true;
}

void WebMediaPlayer::setVisible(bool visible)
{
}

void WebMediaPlayer::setPreservesPitch(bool pitch)
{
}

bool WebMediaPlayer::hasClosedCaptions()
{
    return false;
}

void WebMediaPlayer::setClosedCaptionsVisible(bool visible)
{
}

int64_t WebMediaPlayer::totalBytes()
{
    return 0;
}

bool WebMediaPlayer::didLoadingProgress()
{
    return true;
}

bool WebMediaPlayer::supportsFullscreen()
{
    return true;
}

void WebMediaPlayer::enterFullscreen()
{
}

void WebMediaPlayer::exitFullscreen()
{
}

bool WebMediaPlayer::canEnterFullscreen()
{
    return false;
}

double WebMediaPlayer::maximumDurationToCacheMediaTime()
{
    return 0;
}

std::string WebMediaPlayer::engineDescription()
{
    return std::string("sling.WebMediaPlayer");
}

bool WebMediaPlayer::shouldMaintainAspectRatio()
{
    return false;
}

void WebMediaPlayer::setShouldMaintainAspectRatio(bool maintainable)
{
}

bool WebMediaPlayer::hasSingleSecurityOrigin()
{
    return true;
}

bool WebMediaPlayer::didPassCORSAccessCheck()
{
    return false;
}

int32_t WebMediaPlayer::decodedFrameCount()
{
    return 0;
}

int32_t WebMediaPlayer::droppedFrameCount()
{
    return 0;
}

int32_t WebMediaPlayer::audioDecodedByteCount()
{
    return 0;
}

int32_t WebMediaPlayer::videoDecodedByteCount()
{
    return 0;
}

void WebMediaPlayer::getSitesInMediaCache(std::shared_ptr<WebKit::Managed::Vector> sites)
{
}

void WebMediaPlayer::clearMediaCache()
{
}

void WebMediaPlayer::clearMediaCacheForSite(const std::string& site)
{
}

void WebMediaPlayer::setPrivateBrowsingMode(bool mode)
{
}

void WebMediaPlayer::resetTexture(int64_t shareContext, int32_t width, int32_t height)
{
    m_frontbufferSurface->reset(reinterpret_cast<EGLContext>(shareContext), width, height);
}

int32_t WebMediaPlayer::swapTextureBackbuffers()
{
    m_frontbufferSurface->publish();
    m_frontbufferSurface->swapBuffers();
    if (!m_frontbufferSurface->isValid())
        mediaPlayerContextLost();

    return ++m_frames;
}

int32_t WebMediaPlayer::getTextureShareToken()
{
    return m_frontbufferSurface->channel()->shareIdentifier();
}

void WebMediaPlayer::destroyFrontbufferSurface()
{
    m_frontbufferSurface.reset();
    m_mediaSurface->setOutputSurface(nullptr);
}

void WebMediaPlayer::restoreFrontbufferSurface(int64_t shareContext, int32_t width, int32_t height)
{
    auto newSurface = opengl::EGLPbufferSurface::create(EGL_NO_DISPLAY, EGL_NO_CONFIG);
    newSurface->reset(reinterpret_cast<EGLContext>(shareContext), width, height);
    m_frontbufferSurface = newSurface;
    m_mediaSurface->setOutputSurface(m_frontbufferSurface);
}

void WebMediaPlayer::INIT(int32_t playerDisposition)
{
    nativeCreate();

    switch (playerDisposition) {
    case PLAYER_DISPOSITION_DEFAULT:
    case PLAYER_DISPOSITION_EMBED:
        initializeEmbeddedMediaPlayer();
        break;
    case PLAYER_DISPOSITION_REMOTE:
        break;
    default:
        assert(false);
        return;
    }
}

void WebMediaPlayer::initializeEmbeddedMediaPlayer()
{
    m_mediaPlayer = std::shared_ptr<media::MediaPlayer>(media::MediaPlayer::create());

    m_mediaPlayer->setOnBufferingUpdateListener([=](int32_t percent) { onBufferingUpdate(percent); });
    m_mediaPlayer->setOnCompletionListener([=] { onCompletion(); });
    m_mediaPlayer->setOnErrorListener([=](int32_t type) { onError(type); });
    m_mediaPlayer->setOnInfoListener([=] { onInfo(); });
    m_mediaPlayer->setOnPreparedListener([=]() { onPrepared(); });
    m_mediaPlayer->setOnSeekCompleteListener([=] { onSeekComplete(); });
    m_mediaPlayer->setOnTimedTextListener([=] { onTimedText(); });
    m_mediaPlayer->setOnVideoSizeChangedListener([=](int32_t width, int32_t height) { onVideoSizeChanged(width, height); });

    m_mediaSurface = media::MediaSurface::create();
    m_frontbufferSurface = opengl::EGLPbufferSurface::create(EGL_NO_DISPLAY, EGL_NO_CONFIG);

    reset();
}

void WebMediaPlayer::reset()
{
    m_frames = 0;
    m_initialized = false;
    m_seeking = false;
    m_error = 0;

    m_mediaPlayer->reset();
    m_mediaSurface->reset();

    m_mediaSurface->setSourceMedia(m_mediaPlayer);
    m_mediaSurface->setOutputSurface(m_frontbufferSurface);
    m_mediaSurface->setOnFrameAvailableListener([=](media::MediaSurface&) { onFrameAvailable(); });
}

void WebMediaPlayer::onBufferingUpdate(int32_t percent)
{
    mediaPlayerBufferingUpdate(percent);
}

void WebMediaPlayer::onCompletion()
{
    mediaPlayerCompletion();
}

void WebMediaPlayer::onError(int32_t type)
{
    mediaPlayerError(type);
}

void WebMediaPlayer::onInfo()
{
}

void WebMediaPlayer::onPrepared()
{
    mediaPlayerPrepared(duration());
}

void WebMediaPlayer::onSeekComplete()
{
    m_seeking = false;

    mediaPlayerSeekComplete();
}

void WebMediaPlayer::onTimedText()
{
}

void WebMediaPlayer::onVideoSizeChanged(int32_t width, int32_t height)
{
    mediaPlayerVideoSizeChanged(width, height);
}

void WebMediaPlayer::onFrameAvailable()
{
    mediaPlayerFrameAvailable();
}

} // namespace webkit

using namespace webkit;

namespace WebKit {
namespace Managed {

void WebMediaPlayer::INIT(int32_t)
{
}

}
} // namespace WebKit
