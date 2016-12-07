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

#include "WebMediaPlayerHost.h"

#include "WebMediaPlayerHostMessages.h"
#include <os/Process.h>
#include <os/Thread.h>

#include <assert.h>

namespace webkit {

WebMediaPlayerHost::WebMediaPlayerHost(std::shared_ptr<os::Messenger>&& messageSender)
    : os::MessageHost(std::move(messageSender))
{
}

WebMediaPlayerHost::~WebMediaPlayerHost()
{
}

void WebMediaPlayerHost::initializeOnce()
{
    static bool onceFlag = false;

    setReceiveMessages(onceFlag, Messages::WebMediaPlayerHostMessages);
}

void WebMediaPlayerHost::receive(const os::Message& message)
{
    MessageHost::receive(message);
}

void WebMediaPlayerHost::setReceiveMessages(bool& onceFlag, Messages messages)
{
    if (onceFlag)
        return;

    onceFlag = true;

    os::Thread::runOnMainThread([=] {
        os::Process::current().setMessageReceiver(WebMediaPlayerHost::receiveMessage, static_cast<os::Messages>(messages));
    });
}

bool WebMediaPlayerHost::receiveMessage(os::Messenger& replySender, const os::Message& message)
{
    if (message.what == WebMediaPlayerHostMessages::Connect) {
        new WebMediaPlayerHost(os::Messenger::create(message.replyTo));
        return true;
    }

    return false;
}

}
