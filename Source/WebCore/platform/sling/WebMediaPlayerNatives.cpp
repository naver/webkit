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
#include "WebMediaPlayerNatives.h"

namespace WebKit {

Native::PassLocalRef<WebMediaPlayer> WebMediaPlayer::create(Client& client, int32_t playerDisposition)
{
    Native::LocalRef<WebMediaPlayer> mp = Natives::WebMediaPlayer::create(playerDisposition).as<WebMediaPlayer>();
    mp->m_client = &client;
    return mp.release();
}

WebMediaPlayer::WebMediaPlayer()
    : m_client(nullptr)
{
}

WebMediaPlayer& mediaPlayer(Natives::WebMediaPlayer* mp)
{
    return *static_cast<WebMediaPlayer*>(mp);
}

} // namespace WebKit

namespace WebKit {
namespace Natives {

WebMediaPlayer* WebMediaPlayer::nativeCreate()
{
    return new ::WebKit::WebMediaPlayer();
}

void WebMediaPlayer::mediaPlayerBufferingUpdate(int32_t percent)
{
    mediaPlayer(this).m_client->mediaPlayerBufferingUpdate(percent);
}

void WebMediaPlayer::mediaPlayerCompletion()
{
    mediaPlayer(this).m_client->mediaPlayerCompletion();
}

void WebMediaPlayer::mediaPlayerError(int32_t type)
{
    mediaPlayer(this).m_client->mediaPlayerError(type);
}

void WebMediaPlayer::mediaPlayerFrameAvailable()
{
    mediaPlayer(this).m_client->mediaPlayerFrameAvailable();
}

void WebMediaPlayer::mediaPlayerPrepared(int32_t duration)
{
    mediaPlayer(this).m_client->mediaPlayerPrepared(duration);
}

void WebMediaPlayer::mediaPlayerSeekComplete()
{
    mediaPlayer(this).m_client->mediaPlayerSeekComplete();
}

void WebMediaPlayer::mediaPlayerVideoSizeChanged(int32_t width, int32_t height)
{
    mediaPlayer(this).m_client->mediaPlayerVideoSizeChanged(width, height);
}

void WebMediaPlayer::mediaPlayerContextLost()
{
    mediaPlayer(this).m_client->mediaPlayerContextLost();
}

} // namespace Natives
} // namespace WebKit

