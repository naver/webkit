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

#ifndef ChildProcessLauncher_h
#define ChildProcessLauncher_h

#include "ChildProcessLauncherNativesBase.h"
#include "Connection.h"

#include <onig/GlobalRef.h>

namespace WebKit {

typedef std::function<void (pid_t, IPC::Connection::Identifier)> DidFinishLaunchingProcessCallbackFunction;

class ChildProcessLauncher : public Natives::ChildProcessLauncher {
public:
    static Native::PassLocalRef<ChildProcessLauncher> create(DidFinishLaunchingProcessCallbackFunction);
    ~ChildProcessLauncher();

    bool requestStart(IPC::Connection::Identifier, const std::string&);

    pid_t pid() const;

private:
    friend class Natives::ChildProcessLauncher;

    ChildProcessLauncher();

    void didFinishLaunchingProcess(pid_t);

    DidFinishLaunchingProcessCallbackFunction m_didFinishLaunchingProcessCallback;

    pid_t m_pid;
    int m_connector;
    Native::GlobalRef<ChildProcessLauncher> m_protector;
};

} // namespace WebKit

#endif
