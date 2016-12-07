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

#ifndef WebMediaPlayer_h
#define WebMediaPlayer_h

#include "WebMediaPlayerManagedBase.h"

#include <media/MediaPlayer.h>
#include <media/MediaSurface.h>

namespace webkit {

namespace Managed = WebKit::Managed;

class WebMediaPlayerChannel;

class WebMediaPlayer final : public WebKit::Managed::WebMediaPlayer {
    friend class WebKit::Managed::WebMediaPlayer;
public:
    WEBKIT_EXPORT ~WebMediaPlayer();
    
    WEBKIT_EXPORT void load(const std::string& url) override;
    WEBKIT_EXPORT void cancelLoad() override;

    WEBKIT_EXPORT void prepareToPlay() override;
    WEBKIT_EXPORT void play() override;
    WEBKIT_EXPORT bool isPlaying() override;

    WEBKIT_EXPORT void pause() override;
    WEBKIT_EXPORT bool paused() override;

    WEBKIT_EXPORT float duration() override;

    WEBKIT_EXPORT float currentTime() override;

    WEBKIT_EXPORT void seek(float position) override;
    WEBKIT_EXPORT bool seeking() override;

    WEBKIT_EXPORT void setRate(float rate) override;
    WEBKIT_EXPORT double rate() override;

    WEBKIT_EXPORT void setVolume(float volume) override;
    WEBKIT_EXPORT bool supportsMuting() override;
    WEBKIT_EXPORT void setMuted(bool mute) override;

    WEBKIT_EXPORT bool supportsScanning() override;
    WEBKIT_EXPORT bool requiresImmediateCompositing() override;
    WEBKIT_EXPORT bool canSaveMediaData() override;

    WEBKIT_EXPORT float naturalWidth() override;
    WEBKIT_EXPORT float naturalHeight() override;

    WEBKIT_EXPORT bool hasVideo() override;
    WEBKIT_EXPORT bool hasAudio() override;

    WEBKIT_EXPORT void setVisible(bool visible) override;

    WEBKIT_EXPORT void setPreservesPitch(bool pitch) override;

    WEBKIT_EXPORT bool hasClosedCaptions() override;
    WEBKIT_EXPORT void setClosedCaptionsVisible(bool visible) override;

    WEBKIT_EXPORT int64_t totalBytes() override;

    WEBKIT_EXPORT bool didLoadingProgress() override;

    WEBKIT_EXPORT bool supportsFullscreen() override;
    WEBKIT_EXPORT void enterFullscreen() override;
    WEBKIT_EXPORT void exitFullscreen() override;
    WEBKIT_EXPORT bool canEnterFullscreen() override;

    WEBKIT_EXPORT double maximumDurationToCacheMediaTime() override;

    WEBKIT_EXPORT std::string engineDescription() override;

    WEBKIT_EXPORT bool shouldMaintainAspectRatio() override;
    WEBKIT_EXPORT void setShouldMaintainAspectRatio(bool maintainable) override;

    WEBKIT_EXPORT bool hasSingleSecurityOrigin() override;

    WEBKIT_EXPORT bool didPassCORSAccessCheck() override;

    WEBKIT_EXPORT int32_t decodedFrameCount() override;
    WEBKIT_EXPORT int32_t droppedFrameCount() override;
    WEBKIT_EXPORT int32_t audioDecodedByteCount() override;
    WEBKIT_EXPORT int32_t videoDecodedByteCount() override;

    WEBKIT_EXPORT void getSitesInMediaCache(std::shared_ptr<WebKit::Managed::Vector> sites) override;
    WEBKIT_EXPORT void clearMediaCache() override;
    WEBKIT_EXPORT void clearMediaCacheForSite(const std::string& site) override;
    WEBKIT_EXPORT void setPrivateBrowsingMode(bool mode) override;

    WEBKIT_EXPORT void resetTexture(int64_t shareContext, int32_t width, int32_t height) override;
    WEBKIT_EXPORT int32_t swapTextureBackbuffers() override;
    WEBKIT_EXPORT int32_t getTextureShareToken() override;
    WEBKIT_EXPORT void destroyFrontbufferSurface() override;
    WEBKIT_EXPORT void restoreFrontbufferSurface(int64_t shareContext, int32_t width, int32_t height) override;

private:
    WebMediaPlayer();

    void INIT(int32_t) override;

    void initializeEmbeddedMediaPlayer();
    void reset();

    void onBufferingUpdate(int32_t percent);
    void onCompletion();
    void onError(int32_t type);
    void onInfo();
    void onPrepared();
    void onSeekComplete();
    void onTimedText();
    void onVideoSizeChanged(int32_t width, int32_t height);

    void onFrameAvailable();

    std::shared_ptr<WebMediaPlayerChannel> m_mediaPlayerChannel;
    std::shared_ptr<opengl::GLTransportSurface> m_frontbufferSurface;

    std::shared_ptr<media::MediaPlayer> m_mediaPlayer;
    std::shared_ptr<media::MediaSurface> m_mediaSurface;
    std::shared_ptr<opengl::GLTransportSurface> m_surfaceTexture;
    int32_t m_frames;
    bool m_initialized;
    bool m_seeking;
    int32_t m_error;
};

} // namespace webkit

#endif // WebMediaPlayer_h
