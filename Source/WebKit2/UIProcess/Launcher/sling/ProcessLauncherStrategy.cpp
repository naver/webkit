/*
 * Copyright (C) 2014 Naver Corp. All rights reserved.
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
#include "ProcessLauncherStrategy.h"

#include <wtf/text/WTFString.h>

namespace WebKit {

std::unique_ptr<ProcessLauncherStrategy> ProcessLauncherStrategy::create()
{
    return std::unique_ptr<ProcessLauncherStrategy>(new ProcessLauncherStrategy);
}

IPC::Connection::SocketPair ProcessLauncherStrategy::createPlatformConnection(unsigned options)
{
    return IPC::Connection::createPlatformConnection(options);
}

bool ProcessLauncherStrategy::launchPlatformProcess(int connector, String commandLine, DidFinishLaunchingProcessCallbackFunction didFinishLaunchingProcess)
{
    Native::LocalRef<ChildProcessLauncher> platformProcessLauncher = ChildProcessLauncher::create(WTFMove(didFinishLaunchingProcess));
    bool processLaunched = platformProcessLauncher->requestStart(connector, commandLine.latin1().data());
    if (!processLaunched) {
        LOG_ERROR("Failed to start process with arguments: %s", commandLine.latin1().data());
        ASSERT_NOT_REACHED();
    }

    return processLaunched;
}

}  // namespace WebKit
