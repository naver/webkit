/*
 * Copyright (C) 2010 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "TestRunner.h"

#include "InjectedBundle.h"
#include <wtf/text/StringBuilder.h>

namespace WTR {

using namespace std;

void TestRunner::platformInitialize()
{
    m_waitToDumpWatchdogTimer = 0;
}

void TestRunner::invalidateWaitToDumpWatchdogTimer()
{
    if (!m_waitToDumpWatchdogTimer)
        return;

    ::KillTimer(0, m_waitToDumpWatchdogTimer);
    m_waitToDumpWatchdogTimer = 0;
}

static void CALLBACK waitToDumpWatchdogTimerFired(HWND, UINT, UINT_PTR, DWORD)
{
    InjectedBundle::singleton().testRunner()->waitToDumpWatchdogTimerFired();
}

static const UINT_PTR waitToDumpWatchdogTimerIdentifier = 1;

void TestRunner::initializeWaitToDumpWatchdogTimerIfNeeded()
{
    if (m_waitToDumpWatchdogTimer)
        return;

    m_waitToDumpWatchdogTimer = ::SetTimer(0, waitToDumpWatchdogTimerIdentifier, m_timeout / 1000, WTR::waitToDumpWatchdogTimerFired);
}

static const wstring& exePath()
{
    static wstring path;
    static bool initialized;

    if (initialized)
        return path;
    initialized = true;

    TCHAR buffer[MAX_PATH];
    GetModuleFileName(GetModuleHandle(0), buffer, ARRAYSIZE(buffer));
    path = buffer;
    int lastSlash = path.rfind('\\');
    if (lastSlash != -1 && lastSlash + 1 < path.length())
        path = path.substr(0, lastSlash + 1);

    return path;
}

JSRetainPtr<JSStringRef> TestRunner::pathToLocalResource(JSStringRef url)
{
    return JSStringRetain(url); // TODO.
}

JSRetainPtr<JSStringRef> TestRunner::inspectorTestStubURL()
{
    String basePath = exePath().c_str();
    basePath.replace('\\', '/');

    StringBuilder builder;
    builder.append("file:///");
    builder.append(basePath);
    builder.appendLiteral("WebInspectorUI/UserInterface/TestStub.html");

    return JSStringCreateWithUTF8CString(builder.toString().utf8().data());
}

} // namespace WTR
