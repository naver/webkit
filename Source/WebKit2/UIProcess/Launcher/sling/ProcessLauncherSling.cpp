/*
 * Copyright (C) 2013 Naver Corp. All rights reserved.
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
#include "ProcessLauncher.h"

#include "NotImplemented.h"
#include "ProcessExecutablePath.h"
#include "ProcessLauncherStrategy.h"
#include "WebKitServiceRunnerNativesBase.h"
#include <wtf/RunLoop.h>

namespace WebKit {

static const char* processTypeAsString(ProcessLauncher::ProcessType processType)
{
    switch (processType) {
    case ProcessLauncher::ProcessType::Web:
        return "webprocess";
#if ENABLE(NETSCAPE_PLUGIN_API)
    case ProcessLauncher::ProcessType::Plugin32:
    case ProcessLauncher::ProcessType::Plugin64:
        return "pluginprocess";
#endif
    case ProcessLauncher::ProcessType::Network:
        return "networkprocess";
#if ENABLE(DATABASE_PROCESS)
    case ProcessLauncher::ProcessType::Database:
        return "databaseprocess";
#endif
    }

    ASSERT_NOT_REACHED();
    return 0;
}

void ProcessLauncher::launchProcess()
{
    std::unique_ptr<ProcessLauncherStrategy> strategy = ProcessLauncherStrategy::create();

    IPC::Connection::SocketPair sockets = strategy->createPlatformConnection();
    if (sockets.client == -1 || sockets.server == -1) {
        LOG_ERROR("Creation of socket failed with errno: %d", errno);
        ASSERT_NOT_REACHED();
        return;
    }

    String executablePath;
    String extraInfo = ASCIILiteral("none");
    switch (m_launchOptions.processType) {
    case ProcessType::Web:
        executablePath = executablePathOfWebProcess();
        break;
#if ENABLE(NETSCAPE_PLUGIN_API)
    case ProcessType::Plugin32:
    case ProcessType::Plugin64:
        executablePath = executablePathOfPluginProcess();
        extraInfo = m_launchOptions.extraInitializationData.get("plugin-path");
        break;
#endif
    case ProcessType::Network:
        executablePath = executablePathOfNetworkProcess();
        break;
#if ENABLE(DATABASE_PROCESS)
    case ProcessType::Database:
        executablePath = executablePathOfDatabaseProcess();
        break;
#endif
    default:
        ASSERT_NOT_REACHED();
        return;
    }

    String processType = processTypeAsString(m_launchOptions.processType);
    int connector = sockets.server;
    String commandLine;
    commandLine.append(processType);
    commandLine.append('|');
    commandLine.append(String::number(sockets.client));
    commandLine.append('|');
    commandLine.append(executablePath);
    commandLine.append('|');
    commandLine.append(extraInfo);

    RefPtr<ProcessLauncher> protect(this);
    bool processLaunched = strategy->launchPlatformProcess(connector, commandLine, [protect] (pid_t pid, IPC::Connection::Identifier connector) {
        RunLoop::main().dispatch([=] { protect->didFinishLaunchingProcess(pid, connector); });
    });

    if (!processLaunched) {
        LOG_ERROR("Failed to start: %s", processType.utf8().data());
        ASSERT_NOT_REACHED();
    }
}

void ProcessLauncher::terminateProcess()
{
    if (m_isLaunching) {
        invalidate();
        return;
    }

    if (!m_processIdentifier)
        return;

    WebKit::Natives::WebKitServiceRunner::unbindProcess(m_processIdentifier);

    m_processIdentifier = 0;
}

void ProcessLauncher::platformInvalidate()
{
}

} // namespace WebKit
