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

#if ENABLE(VIDEO)

#include "BitmapImage.h"
#include "GLContext.h"
#include "GraphicsContext.h"
#include "GraphicsSurfacePrivate.h"
#include "MediaPlayerPrivateSling.h"
#include "Logging.h"
#include "NotImplemented.h"
#include "PlatformBridgeNatives.h"
#include "PlatformDisplay.h"
#include "SharedBuffer.h"
#include "URL.h"

#include <wtf/HashMap.h>
#include <wtf/MainThread.h>
#include <wtf/NeverDestroyed.h>
#include <wtf/text/CString.h>
#include <NativesString.h>
#include <NativesVector.h>

using namespace WebKit;

namespace WebCore {

void MediaPlayerPrivateSling::registerMediaEngine(MediaEngineRegistrar registrar)
{
    registrar([](MediaPlayer* player) { return std::make_unique<MediaPlayerPrivateSling>(player); },
        getSupportedTypes, supportsType, 0, 0, 0, 0);
}

static HashSet<String, ASCIICaseInsensitiveHash> mimeTypeCache()
{
    static NeverDestroyed<HashSet<String, ASCIICaseInsensitiveHash>> cache;
    static bool typeListInitialized = false;

    if (typeListInitialized)
        return cache;

    Native::LocalRef<Native::Natives::Vector> mimeTypes = PlatformBridge::getSupportedMediaMimeTypeList();

    for (int32_t index = 0; index < mimeTypes->size(); ++index) {
        Native::LocalRef<Native::Natives::String> value = mimeTypes->elementAt(index).as<Native::Natives::String>();
        String type = String::fromUTF8((char*)(value->getBytes().data()), value->getBytes().count());
        cache.get().add(type);
    }

    typeListInitialized = true;
    return cache;
}

void MediaPlayerPrivateSling::getSupportedTypes(HashSet<String, ASCIICaseInsensitiveHash>& supportedTypes)
{
    supportedTypes = mimeTypeCache();
}

MediaPlayer::SupportsType MediaPlayerPrivateSling::supportsType(const MediaEngineSupportParameters& parameters)
{
    if (parameters.type.isNull() || parameters.type.isEmpty())
        return MediaPlayer::IsNotSupported;

    if (mimeTypeCache().contains(parameters.type))
        return parameters.codecs.isEmpty() ? MediaPlayer::MayBeSupported : MediaPlayer::IsSupported;

    return MediaPlayer::IsNotSupported;
}

MediaPlayerPrivateSling::MediaPlayerPrivateSling(MediaPlayer* player)
    : m_context(ThreadCallbackContext::create(mainThreadCallback, this))
    , m_player(player)
    , m_networkState(MediaPlayer::Empty)
    , m_readyState(MediaPlayer::HaveNothing)
    , m_preload(MediaPlayer::Auto)
    , m_isAllowedToRender(false)
    , m_hasSizeInfo(false)
    , m_queuedNotifications()
    , m_queueMutex()
    , m_mainThreadCallPending(false)
    , m_delayCallbacks(0)
    , m_ignoreLoadStateChanges(false)
    , m_delayCharacteristicsChangedNotification(0)
    , m_inbandTrackConfigurationPending(false)
    , m_cachedDuration(MediaTime::invalidTime())
    , m_reportedDuration(MediaTime::invalidTime())
    , m_loadingMetadata(false)
    , m_seeking(false)
    , m_backend(WebMediaPlayer::create(*this, WebMediaPlayer::PLAYER_DISPOSITION_DEFAULT))
{
}

MediaPlayerPrivateSling::~MediaPlayerPrivateSling()
{
    LOG(Media, "MediaPlayerPrivateSling::~MediaPlayerPrivateSling(%p)", this);
    setIgnoreLoadStateChanges(true);
    m_context->finishCallOnThread();
    if (client())
        client()->platformLayerWillBeDestroyed();
}

void MediaPlayerPrivateSling::load(const String& url)
{
    if (m_networkState != MediaPlayer::Loading) {
        m_networkState = MediaPlayer::Loading;
        m_player->networkStateChanged();
    }

    if (m_readyState != MediaPlayer::HaveNothing) {
        m_readyState = MediaPlayer::HaveNothing;
        m_player->readyStateChanged();
    }

    m_assetURL = url;

    if (!url.length())
        return;

    m_backend->load(url.utf8().data());

    setPreload(m_preload);
}

#if ENABLE(MEDIA_SOURCE)
void MediaPlayerPrivateSling::load(const String& url, MediaSourcePrivateClient*)
{
    m_networkState = MediaPlayer::FormatError;
    m_player->networkStateChanged();
}
#endif

#if ENABLE(MEDIA_STREAM)
void MediaPlayerPrivateSling::load(MediaStreamPrivate*)
{
}
#endif

void MediaPlayerPrivateSling::playabilityKnown()
{
}

void MediaPlayerPrivateSling::cancelLoad()
{
    m_backend->cancelLoad();
}

void MediaPlayerPrivateSling::prepareToPlay()
{
    m_backend->prepareToPlay();
}

PlatformMedia MediaPlayerPrivateSling::platformMedia() const
{
    return NoPlatformMedia;
}

PlatformLayer* MediaPlayerPrivateSling::platformLayer() const
{
    return (hasAvailableVideoFrame()) ? const_cast<MediaPlayerPrivateSling*>(this) : nullptr;
}

long MediaPlayerPrivateSling::platformErrorCode() const
{
    return 0;
}

void MediaPlayerPrivateSling::play()
{
    m_backend->play();
}

void MediaPlayerPrivateSling::pause()
{
    m_backend->pause();
}

bool MediaPlayerPrivateSling::supportsFullscreen() const
{
    return m_backend->supportsFullscreen();
}

bool MediaPlayerPrivateSling::supportsScanning() const
{
    return m_backend->supportsScanning();
}

bool MediaPlayerPrivateSling::requiresImmediateCompositing() const
{
    return m_backend->requiresImmediateCompositing();
}

URL MediaPlayerPrivateSling::resolvedURL() const
{
    if (!m_assetURL.length())
        return URL();

    return URL(ParsedURLString, m_assetURL);
}

bool MediaPlayerPrivateSling::canSaveMediaData() const
{
    URL url = resolvedURL();

    if (url.isLocalFile())
        return true;

    if (!url.protocolIsInHTTPFamily())
        return false;

    if (isLiveStream())
        return false;

    return true;
}

FloatSize MediaPlayerPrivateSling::naturalSize() const
{
    return m_naturalSize;
}

bool MediaPlayerPrivateSling::hasVideo() const
{
    if (m_hasSizeInfo)
        return !m_naturalSize.isEmpty();

    return false;
}

bool MediaPlayerPrivateSling::hasAudio() const
{
    return m_backend->hasAudio();
}

void MediaPlayerPrivateSling::setVisible(bool visible)
{
    m_backend->setVisible(visible);
}

float MediaPlayerPrivateSling::duration() const
{
    return m_backend->duration();
}

MediaTime MediaPlayerPrivateSling::durationMediaTime() const
{
    if (m_cachedDuration.isValid())
        return m_cachedDuration;

    MediaTime cachedDuration = MediaTime::createWithFloat(duration());
    if (!cachedDuration || cachedDuration.isInvalid())
        return MediaTime::zeroTime();

    m_cachedDuration = cachedDuration;
    return m_cachedDuration;
}

float MediaPlayerPrivateSling::currentTime() const
{
    return m_backend->currentTime();
}

MediaTime MediaPlayerPrivateSling::currentMediaTime() const
{
    return MediaTime::createWithFloat(currentTime());
}

void MediaPlayerPrivateSling::seek(float time)
{
    m_backend->seek(time);
}

bool MediaPlayerPrivateSling::seeking() const
{
    return m_backend->seeking();
}

void MediaPlayerPrivateSling::setRate(float rate)
{
    m_backend->setRate(rate);
}

double MediaPlayerPrivateSling::rate() const
{
    return m_backend->rate();
}

void MediaPlayerPrivateSling::setPreservesPitch(bool pitch)
{
    m_backend->setPreservesPitch(pitch);
}

bool MediaPlayerPrivateSling::paused() const
{
    return m_backend->paused();
}

void MediaPlayerPrivateSling::setVolume(float volume)
{
    m_backend->setVolume(volume);
}

bool MediaPlayerPrivateSling::supportsMuting() const
{
    return m_backend->supportsMuting();
}

void MediaPlayerPrivateSling::setMuted(bool mute)
{
    m_backend->setMuted(mute);
}

bool MediaPlayerPrivateSling::hasClosedCaptions() const
{
    return m_backend->hasClosedCaptions();
}

void MediaPlayerPrivateSling::setClosedCaptionsVisible(bool visible)
{
    m_backend->setClosedCaptionsVisible(visible);
}

double MediaPlayerPrivateSling::maxFastForwardRate() const
{
    return std::numeric_limits<double>::infinity();
}

double MediaPlayerPrivateSling::minFastReverseRate() const
{
    return -std::numeric_limits<double>::infinity();
}

MediaPlayer::NetworkState MediaPlayerPrivateSling::networkState() const
{
    return m_networkState;
}

MediaPlayer::ReadyState MediaPlayerPrivateSling::readyState() const
{
    return m_readyState;
}

float MediaPlayerPrivateSling::maxTimeSeekable() const
{
    if (std::isinf(duration()))
        return 0.0f;

    return duration();
}

std::unique_ptr<PlatformTimeRanges> MediaPlayerPrivateSling::buffered() const
{
    notImplemented();
    return std::make_unique<PlatformTimeRanges>();
}

unsigned long long MediaPlayerPrivateSling::totalBytes() const
{
    return m_backend->totalBytes();
}

bool MediaPlayerPrivateSling::didLoadingProgress() const
{
    return m_backend->didLoadingProgress();
}

void MediaPlayerPrivateSling::setSize(const IntSize&)
{
    notImplemented();
}

void MediaPlayerPrivateSling::paint(GraphicsContext&, const FloatRect&)
{
}

void MediaPlayerPrivateSling::paintCurrentFrameInContext(GraphicsContext&, const FloatRect&)
{
}

void MediaPlayerPrivateSling::setPreload(MediaPlayer::Preload preload)
{
    m_preload = preload;
}

bool MediaPlayerPrivateSling::hasAvailableVideoFrame() const
{
    return readyState() >= MediaPlayer::HaveCurrentData && m_hasSizeInfo;
}

bool MediaPlayerPrivateSling::canLoadPoster() const
{
    return false;
}

void MediaPlayerPrivateSling::setPoster(const String&)
{
}

#if USE(NATIVE_FULLSCREEN_VIDEO)
void MediaPlayerPrivateSling::enterFullscreen()
{
    m_backend->enterFullscreen();
}

void MediaPlayerPrivateSling::exitFullscreen()
{
    m_backend->exitFullscreen();
}
#endif

bool MediaPlayerPrivateSling::supportsAcceleratedRendering() const
{
    return true;
}

void MediaPlayerPrivateSling::acceleratedRenderingStateChanged()
{
    notImplemented();
}

bool MediaPlayerPrivateSling::shouldMaintainAspectRatio() const
{
    return m_backend->shouldMaintainAspectRatio();
}

void MediaPlayerPrivateSling::setShouldMaintainAspectRatio(bool maintainable)
{
    m_backend->setShouldMaintainAspectRatio(maintainable);
}

bool MediaPlayerPrivateSling::hasSingleSecurityOrigin() const
{
    return m_backend->hasSingleSecurityOrigin();
}

bool MediaPlayerPrivateSling::didPassCORSAccessCheck() const
{
    return m_backend->didPassCORSAccessCheck();
}

MediaPlayer::MovieLoadType MediaPlayerPrivateSling::movieLoadType() const
{
    if (isLiveStream())
        return MediaPlayer::LiveStream;

    return MediaPlayer::Download;
}

void MediaPlayerPrivateSling::prepareForRendering()
{
    if (m_isAllowedToRender)
        return;
    m_isAllowedToRender = true;

    notImplemented();
}

MediaTime MediaPlayerPrivateSling::mediaTimeForTimeValue(const MediaTime& timeValue) const
{
    notImplemented();
    return timeValue;
}

double MediaPlayerPrivateSling::maximumDurationToCacheMediaTime() const
{
    return m_backend->maximumDurationToCacheMediaTime();
}

unsigned MediaPlayerPrivateSling::decodedFrameCount() const
{
    return m_backend->decodedFrameCount();
}

unsigned MediaPlayerPrivateSling::droppedFrameCount() const
{
    return m_backend->droppedFrameCount();
}

unsigned MediaPlayerPrivateSling::audioDecodedByteCount() const
{
    return m_backend->audioDecodedByteCount();
}

unsigned MediaPlayerPrivateSling::videoDecodedByteCount() const
{
    return m_backend->videoDecodedByteCount();
}

void MediaPlayerPrivateSling::setPrivateBrowsingMode(bool mode)
{
    m_backend->setPrivateBrowsingMode(mode);
}

String MediaPlayerPrivateSling::engineDescription() const
{
    return String(m_backend->engineDescription().data());
}

void MediaPlayerPrivateSling::setDelayCallbacks(bool delay) const
{
    MutexLocker lock(m_queueMutex);
    if (delay)
        ++m_delayCallbacks;
    else {
        ASSERT(m_delayCallbacks);
        --m_delayCallbacks;
    }
}

void MediaPlayerPrivateSling::scheduleMainThreadNotification(Notification::Type type, const MediaTime& time)
{
    scheduleMainThreadNotification(Notification(type, time));
}

void MediaPlayerPrivateSling::scheduleMainThreadNotification(Notification::Type type, bool finished)
{
    scheduleMainThreadNotification(Notification(type, finished));
}

void MediaPlayerPrivateSling::scheduleMainThreadNotification(Notification::Type type, int32_t value)
{
    scheduleMainThreadNotification(Notification(type, value));
}

void MediaPlayerPrivateSling::scheduleMainThreadNotification(Notification::Type type, IntSize size)
{
    scheduleMainThreadNotification(Notification(type, size));
}

void MediaPlayerPrivateSling::mediaPlayerBufferingUpdate(int32_t percent)
{
    setDelayCallbacks(true);
    scheduleMainThreadNotification(Notification::BufferingUpdate, percent);
    setDelayCallbacks(false);
}

void MediaPlayerPrivateSling::mediaPlayerCompletion()
{
    setDelayCallbacks(true);
    scheduleMainThreadNotification(Notification::Completion);
    setDelayCallbacks(false);
}

void MediaPlayerPrivateSling::mediaPlayerError(int32_t type)
{
    setDelayCallbacks(true);
    scheduleMainThreadNotification(Notification::Error, type);
    setDelayCallbacks(false);
}

void MediaPlayerPrivateSling::mediaPlayerFrameAvailable()
{
    setDelayCallbacks(true);
    scheduleMainThreadNotification(Notification::FrameAvailable, 0);
    setDelayCallbacks(false);
}

void MediaPlayerPrivateSling::mediaPlayerPrepared(int32_t duration)
{
    setDelayCallbacks(true);
    scheduleMainThreadNotification(Notification::Prepared, duration);
    setDelayCallbacks(false);
}

void MediaPlayerPrivateSling::mediaPlayerSeekComplete()
{
    setDelayCallbacks(true);
    scheduleMainThreadNotification(Notification::SeekCompleted);
    setDelayCallbacks(false);
}

void MediaPlayerPrivateSling::mediaPlayerVideoSizeChanged(int32_t width, int32_t height)
{
    setDelayCallbacks(true);
    scheduleMainThreadNotification(Notification::VideoSizeChanged, IntSize(width, height));
    setDelayCallbacks(false);
}

void MediaPlayerPrivateSling::mediaPlayerContextLost()
{
    setDelayCallbacks(true);
    scheduleMainThreadNotification(Notification::ContextLost);
    setDelayCallbacks(false);
}

void MediaPlayerPrivateSling::bufferingUpdate(int32_t percent)
{
    if (percent >= 100) {
        m_readyState = MediaPlayer::HaveEnoughData;
        m_player->readyStateChanged();
    } else if (m_readyState < MediaPlayer::HaveCurrentData) {
        m_readyState = MediaPlayer::HaveCurrentData;
        m_player->readyStateChanged();
    }
}

void MediaPlayerPrivateSling::completion()
{
    if (m_cachedDuration == MediaTime::zeroTime())
        m_cachedDuration = currentMediaTime();

    m_player->timeChanged();
}

void MediaPlayerPrivateSling::error(int32_t type)
{
    UNUSED_PARAM(type);
    m_networkState = MediaPlayer::NetworkError;
    m_player->networkStateChanged();

    if (m_readyState != MediaPlayer::HaveNothing) {
        m_readyState = MediaPlayer::HaveNothing;
        m_player->readyStateChanged();
    }
}

void MediaPlayerPrivateSling::frameAvailable()
{
    if (client())
        client()->setPlatformLayerNeedsDisplay();
}

void MediaPlayerPrivateSling::prepared(int32_t duration)
{
    m_readyState = MediaPlayer::HaveMetadata;
    m_player->readyStateChanged();

    MediaTime cachedDuration = MediaTime::createWithFloat(duration);
    if (m_cachedDuration != cachedDuration) {
        m_cachedDuration = cachedDuration;
        m_player->durationChanged();
    }

    m_networkState = MediaPlayer::Idle;
    m_player->networkStateChanged();
}

void MediaPlayerPrivateSling::seekCompleted(bool finished)
{
    LOG(Media, "MediaPlayerPrivateSling::seekCompleted(%p) - finished = %d", this, finished);
    UNUSED_PARAM(finished);

    m_readyState = MediaPlayer::HaveEnoughData;
    m_player->readyStateChanged();
    m_player->timeChanged();
}

void MediaPlayerPrivateSling::videoSizeChanged(const IntSize& size)
{
    if (size == m_naturalSize)
        return;

    m_naturalSize = size;

    m_backend->resetTexture(reinterpret_cast<int64_t>(GLContext::sharingContext()->platformContext()), size.width(), size.height());

    m_player->sizeChanged();
    m_hasSizeInfo = true;
}

void MediaPlayerPrivateSling::contextLost()
{
    if (GLContext::destroySharingContextIfLost()) {
        m_backend->destroyFrontbufferSurface();
        PlatformDisplay::destroySharedDisplay();
    }

    m_backend->restoreFrontbufferSurface(reinterpret_cast<int64_t>(GLContext::sharingContext()->platformContext()), m_naturalSize.width(), m_naturalSize.height());
}

void MediaPlayerPrivateSling::updateStates()
{
}

void MediaPlayerPrivateSling::metadataLoaded()
{
    m_loadingMetadata = false;
    tracksChanged();
}

void MediaPlayerPrivateSling::rateChanged()
{
    m_player->rateChanged();
}

void MediaPlayerPrivateSling::loadedTimeRangesChanged()
{
    m_cachedLoadedTimeRanges = nullptr;
    m_cachedMaxTimeLoaded = MediaTime::zeroTime();
    invalidateCachedDuration();
}

void MediaPlayerPrivateSling::seekableTimeRangesChanged()
{
    m_cachedMaxTimeSeekable = MediaTime::zeroTime();
    m_cachedMinTimeSeekable = MediaTime::zeroTime();
}

void MediaPlayerPrivateSling::timeChanged(const MediaTime& time)
{
    LOG(Media, "MediaPlayerPrivateSling::timeChanged(%p) - time = %s", this, String::number(time.timeValue()).utf8().data());
    UNUSED_PARAM(time);
}

void MediaPlayerPrivateSling::tracksChanged()
{
    LOG(Media, "MediaPlayerPrivateSling::tracksChanged(%p)", this);
}

void MediaPlayerPrivateSling::didEnd()
{
    MediaTime now = currentMediaTime();
    if (now > MediaTime::zeroTime())
        m_cachedDuration = now;

    updateStates();
    m_player->timeChanged();
}

void MediaPlayerPrivateSling::invalidateCachedDuration()
{
    LOG(Media, "MediaPlayerPrivateSling::invalidateCachedDuration(%p)", this);

    m_cachedDuration = MediaTime::invalidTime();

    MediaTime duration = this->durationMediaTime();
    if (duration != m_reportedDuration) {
        if (m_reportedDuration.isValid())
            m_player->durationChanged();
        m_reportedDuration = duration;
    }
}

void MediaPlayerPrivateSling::clearMainThreadPendingFlag()
{
    MutexLocker lock(m_queueMutex);
    m_mainThreadCallPending = false;
}

#if !LOG_DISABLED
static const char* notificationName(MediaPlayerPrivateSling::Notification& notification)
{
#define DEFINE_TYPE_STRING_CASE(type) case MediaPlayerPrivateSling::Notification::type: return #type;
    switch (notification.type()) {
    FOR_EACH_MEDIAPLAYERPRIVATESLING_NOTIFICATION_TYPE(DEFINE_TYPE_STRING_CASE)
    case MediaPlayerPrivateSling::Notification::FunctionType: return "FunctionType";
    default: ASSERT_NOT_REACHED(); return "";
    }
#undef DEFINE_TYPE_STRING_CASE
}
#endif // !LOG_DISABLED

void MediaPlayerPrivateSling::mainThreadCallback(void* context)
{
    LOG(Media, "MediaPlayerPrivateSling::mainThreadCallback(%p)", context);
    MediaPlayerPrivateSling* player = static_cast<MediaPlayerPrivateSling*>(context);

    player->clearMainThreadPendingFlag();
    player->dispatchNotification();
}

void MediaPlayerPrivateSling::scheduleMainThreadNotification(Notification notification)
{
    if (notification.type() != Notification::FunctionType)
        LOG(Media, "MediaPlayerPrivateSling::scheduleMainThreadNotification(%p) - notification %s", this, notificationName(notification));

    m_queueMutex.lock();

    m_queuedNotifications.append(notification);

#if OS(WINDOWS)
    bool delayDispatch = true;
#else
    bool delayDispatch = m_delayCallbacks || !isMainThread();
#endif
    if (delayDispatch && !m_mainThreadCallPending) {
        m_mainThreadCallPending = true;
        m_context->callOnThread();
    }

    m_queueMutex.unlock();

    if (delayDispatch) {
        if (notification.type() != Notification::FunctionType)
            LOG(Media, "MediaPlayerPrivateSling::scheduleMainThreadNotification(%p) - early return", this);
        return;
    }

    dispatchNotification();
}

void MediaPlayerPrivateSling::dispatchNotification()
{
    ASSERT(isMainThread());

    Notification notification = Notification();
    {
        MutexLocker lock(m_queueMutex);

        if (m_queuedNotifications.isEmpty())
            return;

        if (!m_delayCallbacks) {
            // Only dispatch one notification callback per invocation because they can cause recursion.
            notification = m_queuedNotifications.first();
            m_queuedNotifications.remove(0);
        }

        if (!m_queuedNotifications.isEmpty() && !m_mainThreadCallPending)
            m_context->callOnThread();

        if (!notification.isValid())
            return;
    }

    if (notification.type() != Notification::FunctionType)
        LOG(Media, "MediaPlayerPrivateSling::dispatchNotification(%p) - dispatching %s", this, notificationName(notification));

    switch (notification.type()) {
    case Notification::BufferingUpdate:
        bufferingUpdate(notification.value());
        break;
    case Notification::Completion:
        completion();
        break;
    case Notification::Error:
        error(notification.value());
        break;
    case Notification::FrameAvailable:
        frameAvailable();
        break;
    case Notification::Prepared:
        prepared(notification.value());
        break;
    case Notification::SeekCompleted:
        seekCompleted(notification.finished());
        break;
    case Notification::VideoSizeChanged:
        videoSizeChanged(notification.size());
        break;
    case Notification::ContextLost:
        contextLost();
        break;
    case Notification::FunctionType:
        notification.function()();
        break;
    case Notification::None:
        ASSERT_NOT_REACHED();
        break;
    }
}

#if ENABLE(WEB_AUDIO)
AudioSourceProvider* MediaPlayerPrivateSling::audioSourceProvider()
{
    return nullptr;
}
#endif

#if ENABLE(VIDEO_TRACK)
bool MediaPlayerPrivateSling::requiresTextTrackRepresentation() const
{
    return false;
}

void MediaPlayerPrivateSling::setTextTrackRepresentation(TextTrackRepresentation*)
{
}

void MediaPlayerPrivateSling::syncTextTrackBounds()
{
}
#endif

#if ENABLE(MEDIA_SOURCE)
unsigned long MediaPlayerPrivateSling::droppedVideoFrames()
{
    return 0;
}

unsigned long MediaPlayerPrivateSling::droppedVideoFrames()
{
    return 0;
}

unsigned long MediaPlayerPrivateSling::corruptedVideoFrames()
{
    return 0;
}

MediaTime MediaPlayerPrivateSling::totalFrameDelay()
{
    return nullptr;
}
#endif

void MediaPlayerPrivateSling::paintToTextureMapper(TextureMapper&, const FloatRect&, const TransformationMatrix&, float)
{
}

#if USE(GRAPHICS_SURFACE)
IntSize MediaPlayerPrivateSling::platformLayerSize() const
{
    return IntSize(naturalSize());
}

uint32_t MediaPlayerPrivateSling::copyToGraphicsSurface()
{
    return m_backend->swapTextureBackbuffers();
}

GraphicsSurfaceToken MediaPlayerPrivateSling::graphicsSurfaceToken() const
{
    return m_backend->getTextureShareToken();
}

GraphicsSurface::Flags MediaPlayerPrivateSling::graphicsSurfaceFlags() const
{
    return GraphicsSurface::SupportsAlpha | GraphicsSurfacePrivate::SupportsTextureStreaming;
}
#endif

} // namespace WebCore

#endif
