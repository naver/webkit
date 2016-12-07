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

#ifndef WebMediaPlayerHost_h
#define WebMediaPlayerHost_h

#include "Messages.h"
#include <os/MessageHost.h>

namespace webkit {

class WebMediaPlayer;

class WebMediaPlayerHost : public os::MessageHost {
public:
    WEBKIT_EXPORT virtual ~WebMediaPlayerHost();

    WEBKIT_EXPORT static void initializeOnce();

protected:
    WEBKIT_EXPORT WebMediaPlayerHost(std::shared_ptr<os::Messenger>&&);

    // os::MessageHost
    WEBKIT_EXPORT void receive(const os::Message&) override;

private:
    static void setReceiveMessages(bool& onceFlag, Messages);
    static bool receiveMessage(os::Messenger&, const os::Message&);

    std::shared_ptr<WebMediaPlayer> m_mediaPlayer;
};

}

#endif
