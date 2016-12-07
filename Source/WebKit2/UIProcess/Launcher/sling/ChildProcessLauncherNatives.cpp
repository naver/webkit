/*
 * Copyright (C) 2013-2015 Naver Corp. All rights reserved.
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
#include "ChildProcessLauncherNatives.h"

#include "NetworkProcessMainUnix.h"
#include "ProcessLauncher.h"
#include "WebProcessMainUnix.h"

#if ENABLE(DATABASE_PROCESS)
#include "DatabaseProcessMainUnix.h"
#endif

#if ENABLE(PLUGIN_PROCESS)
#if PLUGIN_ARCHITECTURE(WIN)
#include "PluginProcessMainWin.h"
#endif
#endif

namespace WebKit {

Native::PassLocalRef<ChildProcessLauncher> ChildProcessLauncher::create(DidFinishLaunchingProcessCallbackFunction didFinishLaunchingProcessCallback)
{
    Native::LocalRef<ChildProcessLauncher> launcher = static_pointer_cast<ChildProcessLauncher>(Natives::ChildProcessLauncher::create());
    launcher->m_didFinishLaunchingProcessCallback = WTFMove(didFinishLaunchingProcessCallback);
    return launcher;
}

ChildProcessLauncher::ChildProcessLauncher()
    : m_pid(0)
    , m_connector(0)
{
}

ChildProcessLauncher::~ChildProcessLauncher()
{
}

bool ChildProcessLauncher::requestStart(IPC::Connection::Identifier connector, const std::string& commandLine)
{
    m_protector = this;

    m_connector = connector;

    if (!start(reinterpret_cast<int32_t>(this), commandLine))
        return false;
    return true;
}

pid_t ChildProcessLauncher::pid() const
{
    return m_pid;
}

void ChildProcessLauncher::didFinishLaunchingProcess(pid_t pid)
{
    m_didFinishLaunchingProcessCallback(pid, m_connector);
    m_pid = pid;
    m_connector = 0;

    m_protector.reset();
}

static bool getProcessTypeFromString(const char* string, ProcessLauncher::ProcessType& processType)
{
    if (!strcmp(string, "webprocess")) {
        processType = ProcessLauncher::ProcessType::Web;
        return true;
    }

#if ENABLE(NETSCAPE_PLUGIN_API)
    if (!strcmp(string, "pluginprocess")) {
        processType = ProcessLauncher::ProcessType::Plugin32;
        return true;
    }
#endif

    if (!strcmp(string, "networkprocess")) {
        processType = ProcessLauncher::ProcessType::Network;
        return true;
    }

#if ENABLE(DATABASE_PROCESS)
    if (!strcmp(string, "databaseprocess")) {
        processType = ProcessLauncher::ProcessType::Database;
        return true;
    }
#endif
    return false;
}

static int WebKitMain(const std::string& processTypeString, const std::string& clientIdentifierString, const std::string& extraInfo)
{
    ProcessLauncher::ProcessType processType;
    if (!getProcessTypeFromString(processTypeString.data(), processType))
        return -1;

    const int argc = 3;
    char* argv[argc] = {
        const_cast<char*>(processTypeString.data()),
        const_cast<char*>(clientIdentifierString.data()),
        const_cast<char*>(extraInfo.data())
    };

    switch (processType) {
    case ProcessLauncher::ProcessType::Web:
        return WebKit::WebProcessMainUnix(argc, argv);
#if ENABLE(DATABASE_PROCESS)
    case ProcessLauncher::ProcessType::Database:
        return WebKit::DatabaseProcessMainUnix(argc, argv);
#endif
    case ProcessLauncher::ProcessType::Network:
        return WebKit::NetworkProcessMainUnix(argc, argv);
#if ENABLE(PLUGIN_PROCESS)
#if PLUGIN_ARCHITECTURE(WIN)
    case ProcessLauncher::ProcessType::Plugin32:
    case ProcessLauncher::ProcessType::Plugin64:
        return WebKit::PluginProcessMainWin(argc, argv);
#endif
#endif
    default:
        ASSERT_NOT_REACHED();
        break;
    }

    return -1;
}

namespace Natives {

ChildProcessLauncher* ChildProcessLauncher::CTOR()
{
    return new ::WebKit::ChildProcessLauncher();
}

void ChildProcessLauncher::nativeDidLaunchChildProcess(int32_t nativeHandle, int32_t pid)
{
    ::WebKit::ChildProcessLauncher* launcher = reinterpret_cast<::WebKit::ChildProcessLauncher*>(nativeHandle);
    launcher->didFinishLaunchingProcess(pid);
}

int32_t ChildProcessLauncher::nativeRunWebKitMain(const std::string& processTypeString, const std::string& clientIdentifierString, const std::string& extraInfo)
{
    return WebKitMain(processTypeString, clientIdentifierString, extraInfo);
}

} // namespace Natives

} // namespace WebKit
