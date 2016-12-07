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

#include "WebMediaPlayerNativesBase.h"

namespace WebKit {

class WebMediaPlayer final : public Natives::WebMediaPlayer {
    friend class Natives::WebMediaPlayer;
public:
    class Client {
    public:
        virtual void mediaPlayerBufferingUpdate(int32_t percent) = 0;
        virtual void mediaPlayerCompletion() = 0;
        virtual void mediaPlayerError(int32_t type) = 0;
        virtual void mediaPlayerFrameAvailable() = 0;
        virtual void mediaPlayerPrepared(int32_t duration) = 0;
        virtual void mediaPlayerSeekComplete() = 0;
        virtual void mediaPlayerVideoSizeChanged(int32_t width, int32_t height) = 0;
        virtual void mediaPlayerContextLost() = 0;
    };

    static Native::PassLocalRef<WebMediaPlayer> create(Client&, int32_t playerDisposition);
    static Native::PassLocalRef<WebMediaPlayer> create(int32_t playerDisposition) = delete;
    ~WebMediaPlayer() = default;

private:
    WebMediaPlayer();

    Client* m_client;
};

}

#endif // WebMediaPlayer_h
