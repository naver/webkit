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
#include "ChildProcessLauncher.h"

#include <os/Looper.h>
#include <os/ProcessLauncher.h>
#include <os/Thread.h>
#include <util/StringConversion.h>

#include <string>
#include <sys/socket.h>

namespace webkit {

ChildProcessLauncher::ChildProcessLauncher()
{
}

ChildProcessLauncher::~ChildProcessLauncher()
{
}

// On Windows, our plugin processes need to have the platform message loop because they call the Windows APIs directly.
// LooperRunner is intended to be used for this purpose.
//
// FIXME: We should come up with a better way to do this.
class LooperRunner final {
public:
    LooperRunner(const std::string& processType)
        : m_run(false)
    {
        if (processType == "pluginprocess")
            m_run = true;

        if (m_run)
            os::Looper::prepare();
    }

    void run()
    {
        if (m_run)
            os::Looper::loop();
    }

private:
    bool m_run;
};

void ChildProcessLauncher::threadRunWebKitMain(const std::string& processType, const std::string& clientIdentifier, const std::string& extraInfo)
{
    LooperRunner runner(processType);
    nativeRunWebKitMain(processType, clientIdentifier, extraInfo);
    runner.run();
}

} // namespace webkit

using namespace webkit;

namespace WebKit {
namespace Managed {

static int32_t defaultProcessStrategy()
{
    char* processStrategy;
    if ((processStrategy = getenv("PROCESS_STRATEGY_THREAD")) && processStrategy[0] == '1')
        return ChildProcessLauncher::PROCESS_STRATEGY_ID_THREAD;
    return ChildProcessLauncher::PROCESS_STRATEGY_ID_DEFAULT;
}

void ChildProcessLauncher::INIT()
{
}

bool ChildProcessLauncher::start(int32_t nativeHandle, const std::string& commandLine)
{
    std::vector<std::string> commandLineArguments = std::split(commandLine, '|');

    std::string processType(commandLineArguments[0]);
    std::string clientIdentifier(commandLineArguments[1]);
    std::string executablePath(commandLineArguments[2]);
    std::string extraInfo(commandLineArguments[3]);

    int32_t processStrategy = 0;

    if (!executablePath.compare(PROCESS_STRATEGY_DEFAULT)) {
        processStrategy = defaultProcessStrategy();
    } else if (!executablePath.compare(PROCESS_STRATEGY_THREAD)) {
        processStrategy = PROCESS_STRATEGY_ID_THREAD;
    } else if (!executablePath.compare(PROCESS_STRATEGY_SERVICE)) {
        processStrategy = PROCESS_STRATEGY_ID_SERVICE;
    }

    // Both WebProcess and NetworkProcess cannot be threads at the same time.
    // They share WebCore, and overwrite each other's data and so on.
    // We could allow only one of them to be threads.  But, for now, do not
    // support NetworkProcess as a thread.  Always force the use of
    // a separate process.
    if (!processType.compare("networkprocess"))
        processStrategy = PROCESS_STRATEGY_ID_SERVICE;

    switch (processStrategy) {
    case PROCESS_STRATEGY_ID_THREAD: {
        std::unique_ptr<std::thread> thread = std::unique_ptr<std::thread>(new std::thread([=] {
            webkit::ChildProcessLauncher::threadRunWebKitMain(processType, clientIdentifier, extraInfo);
        }));
        thread->detach();

        nativeDidLaunchChildProcess(nativeHandle, os::Thread::getThreadId(thread->native_handle()));
        break;
    }
    case PROCESS_STRATEGY_ID_SERVICE: {
        // FIXME: It would be nice if we could just create a CommandLine object and output a command line vector from it.
        std::string arguments;
        arguments.append("-type ");
        arguments.append(processType.c_str());
        arguments.append(" -clientIdentifier ");
        arguments.append(clientIdentifier);
        arguments.append(" -extraInfo ");
        arguments.append(extraInfo);

        std::vector<int32_t> fileDescriptors;
        fileDescriptors.push_back(std::stoi(clientIdentifier));

        if (!os::ProcessLauncher::connect("WebKit", "WebKitMain", arguments, fileDescriptors, [=] (uint64_t pid) {
                nativeDidLaunchChildProcess(nativeHandle, pid);
            }))
            return false;

        break;
    }
    default:
        ASSERT(false);
        return false;
    }

    return true;
}

}
} // namespace WebKit
