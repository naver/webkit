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

#ifndef MediaPlayerPrivateSling_h
#define MediaPlayerPrivateSling_h

#if ENABLE(VIDEO)

#include "MediaPlayerPrivate.h"
#include "TextureMapperPlatformLayer.h"
#include "ThreadCallbackContext.h"
#include "WebMediaPlayerNatives.h"

#if USE(GRAPHICS_SURFACE)
#include "GraphicsSurface.h"
#endif

#include <onig/GlobalRef.h>

namespace WebCore {

typedef void MediaEngineRegisterSelf(MediaEngineRegistrar);
typedef void MediaPlayerFunction(void*);

class MediaPlayerPrivateSling : public MediaPlayerPrivateInterface, public WebKit::WebMediaPlayer::Client
    , public TextureMapperPlatformLayer {
public:
    class Notification {
    public:
#define FOR_EACH_MEDIAPLAYERPRIVATESLING_NOTIFICATION_TYPE(macro) \
    macro(None) \
    macro(BufferingUpdate) \
    macro(Completion) \
    macro(Error) \
    macro(FrameAvailable) \
    macro(Prepared) \
    macro(SeekCompleted) \
    macro(VideoSizeChanged) \
    macro(ContextLost) \

        enum Type {
#define DEFINE_TYPE_ENUM(type) type,
            FOR_EACH_MEDIAPLAYERPRIVATESLING_NOTIFICATION_TYPE(DEFINE_TYPE_ENUM)
#undef DEFINE_TYPE_ENUM
            FunctionType,
        };

        Notification()
            : m_type(None)
            , m_finished(false)
        {
        }

        Notification(Type type, const MediaTime& time)
            : m_type(type)
            , m_time(time)
            , m_finished(false)
        {
        }

        Notification(Type type, bool finished)
            : m_type(type)
            , m_finished(finished)
        {
        }

        Notification(std::function<void ()> function)
            : m_type(FunctionType)
            , m_finished(false)
            , m_function(function)
        {
        }

        Notification(Type type, const int32_t value)
            : m_type(type)
            , m_finished(false)
            , m_value(value)
        {
        }

        Notification(Type type, const IntSize& size)
            : m_type(type)
            , m_finished(false)
            , m_size(size)
        {
        }

        Type type() { return m_type; }
        bool isValid() { return m_type != None; }
        MediaTime time() { return m_time; }
        bool finished() { return m_finished; }
        int32_t value() { return m_value; }
        IntSize size() { return m_size; }
        std::function<void ()>& function() { return m_function; }

    private:
        Type m_type;
        MediaTime m_time;
        bool m_finished;
        int32_t m_value;
        IntSize m_size;
        std::function<void ()> m_function;
    };

    explicit MediaPlayerPrivateSling(MediaPlayer*);
    ~MediaPlayerPrivateSling();

    static void registerMediaEngine(MediaEngineRegistrar);

    static void getSupportedTypes(HashSet<String, ASCIICaseInsensitiveHash>&);
    static MediaPlayer::SupportsType supportsType(const MediaEngineSupportParameters&);

    void load(const String& url) override;
#if ENABLE(MEDIA_SOURCE)
    void load(const String& url, MediaSourcePrivateClient*) override;
#endif
#if ENABLE(MEDIA_STREAM)
    void load(MediaStreamPrivate*) override;
#endif
    void cancelLoad() override;
    
    void prepareToPlay() override;

    PlatformMedia platformMedia() const override;
    PlatformLayer* platformLayer() const override;

    long platformErrorCode() const override;

    void play() override;
    void pause() override;    

    bool supportsFullscreen() const override;
    bool supportsScanning() const override;
    bool requiresImmediateCompositing() const override;

    bool canSaveMediaData() const override;

    FloatSize naturalSize() const override;

    bool hasVideo() const override;
    bool hasAudio() const override;

    void setVisible(bool) override;

    float duration() const override;
    MediaTime durationMediaTime() const override;

    float currentTime() const override;
    MediaTime currentMediaTime() const override;

    void seek(float) override;

    bool seeking() const override;

    void setRate(float) override;
    double rate() const override;

    void setPreservesPitch(bool) override;

    bool paused() const override;

    void setVolume(float) override;

    bool supportsMuting() const override;
    void setMuted(bool) override;

    bool hasClosedCaptions() const override;  
    void setClosedCaptionsVisible(bool) override;

    double maxFastForwardRate() const override;
    double minFastReverseRate() const override;

    MediaPlayer::NetworkState networkState() const override;
    MediaPlayer::ReadyState readyState() const override;

    float maxTimeSeekable() const override;

    std::unique_ptr<PlatformTimeRanges> buffered() const override;

    unsigned long long totalBytes() const override;
    bool didLoadingProgress() const override;

    void setSize(const IntSize&) override;

    void paint(GraphicsContext&, const FloatRect&) override;
    void paintCurrentFrameInContext(GraphicsContext& c, const FloatRect& r) override;

    void setPreload(MediaPlayer::Preload) override;

    bool hasAvailableVideoFrame() const override;

    bool canLoadPoster() const override;
    void setPoster(const String&) override;

#if USE(NATIVE_FULLSCREEN_VIDEO)
    void enterFullscreen() override;
    void exitFullscreen() override;
#endif

    bool supportsAcceleratedRendering() const override;
    void acceleratedRenderingStateChanged() override;

    bool shouldMaintainAspectRatio() const override;
    void setShouldMaintainAspectRatio(bool) override;

    bool hasSingleSecurityOrigin() const override;

    bool didPassCORSAccessCheck() const override;

    MediaPlayer::MovieLoadType movieLoadType() const override;

    void prepareForRendering() override;

    MediaTime mediaTimeForTimeValue(const MediaTime& timeValue) const override;

    double maximumDurationToCacheMediaTime() const override;

    unsigned decodedFrameCount() const override;
    unsigned droppedFrameCount() const override;
    unsigned audioDecodedByteCount() const override;
    unsigned videoDecodedByteCount() const override;

    void setPrivateBrowsingMode(bool) override;

    String engineDescription() const override;

#if ENABLE(WEB_AUDIO)
    AudioSourceProvider* audioSourceProvider() override;
#endif

#if ENABLE(VIDEO_TRACK)
    bool requiresTextTrackRepresentation() const override;
    void setTextTrackRepresentation(TextTrackRepresentation*) override;
    void syncTextTrackBounds() override;;
#endif

#if ENABLE(MEDIA_SOURCE)
    unsigned long totalVideoFrames() override;
    unsigned long droppedVideoFrames() override;
    unsigned long corruptedVideoFrames() override;
    MediaTime totalFrameDelay() override;
#endif

    // TextureMapperPlatformLayer
    void paintToTextureMapper(TextureMapper&, const FloatRect&, const TransformationMatrix&, float) override;

#if USE(GRAPHICS_SURFACE)
    IntSize platformLayerSize() const override;
    uint32_t copyToGraphicsSurface() override;
    GraphicsSurfaceToken graphicsSurfaceToken() const override;
    GraphicsSurface::Flags graphicsSurfaceFlags() const override;
#endif

protected:
    URL resolvedURL() const;
    bool isLiveStream() const { return std::isinf(duration()); }

private:
    void bufferingUpdate(int32_t percent);
    void completion();
    void error(int32_t type);
    void frameAvailable();
    void prepared(int32_t duration);
    void seekCompleted(bool);
    void videoSizeChanged(const IntSize&);
    void contextLost();

    void updateStates();

    static void mainThreadCallback(void*);

    void metadataLoaded();
    void playabilityKnown();
    void rateChanged();
    void loadedTimeRangesChanged();
    void seekableTimeRangesChanged();
    void timeChanged(const MediaTime&);
    void tracksChanged();
    void didEnd();
    void contentsNeedsDisplay() { }

    void invalidateCachedDuration();
    void setDelayCallbacks(bool) const;
    void setIgnoreLoadStateChanges(bool delay) { m_ignoreLoadStateChanges = delay; }
    void scheduleMainThreadNotification(Notification);
    void scheduleMainThreadNotification(Notification::Type, const MediaTime& = MediaTime::zeroTime());
    void scheduleMainThreadNotification(Notification::Type, bool completed);
    void scheduleMainThreadNotification(Notification::Type, int32_t value);
    void scheduleMainThreadNotification(Notification::Type, IntSize size);
    void dispatchNotification();
    void clearMainThreadPendingFlag();
	
    // WebKit::WebMediaPlayer::Client
    void mediaPlayerBufferingUpdate(int32_t percent) override;
    void mediaPlayerCompletion() override;
    void mediaPlayerError(int32_t type) override;
    void mediaPlayerFrameAvailable() override;
    void mediaPlayerPrepared(int32_t duration) override;
    void mediaPlayerSeekComplete() override;
    void mediaPlayerVideoSizeChanged(int32_t width, int32_t height) override;
    void mediaPlayerContextLost() override;

private:
    RefPtr<ThreadCallbackContext> m_context;
    MediaPlayer* m_player;

    MediaPlayer::NetworkState m_networkState;
    MediaPlayer::ReadyState m_readyState;

    String m_assetURL;
    MediaPlayer::Preload m_preload;

    FloatSize m_naturalSize;
    bool m_isAllowedToRender;
    bool m_hasSizeInfo;

    Vector<Notification> m_queuedNotifications;
    mutable Mutex m_queueMutex;
    bool m_mainThreadCallPending;
    mutable int m_delayCallbacks;

    bool m_ignoreLoadStateChanges;
    int m_delayCharacteristicsChangedNotification;
    bool m_inbandTrackConfigurationPending;

    mutable std::unique_ptr<PlatformTimeRanges> m_cachedLoadedTimeRanges;
    FloatSize m_cachedNaturalSize;
    mutable MediaTime m_cachedMaxTimeLoaded;
    mutable MediaTime m_cachedMaxTimeSeekable;
    mutable MediaTime m_cachedMinTimeSeekable;
    mutable MediaTime m_cachedDuration;
    MediaTime m_reportedDuration;

    bool m_loadingMetadata;
    bool m_seeking;

    Native::GlobalRef<WebKit::WebMediaPlayer> m_backend;
};

} // namespace WebCore
#endif

#endif // MediaPlayerPrivateSling_h
