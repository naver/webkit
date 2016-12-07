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
#include "MainThread.h"

#include "RunLoop.h"

#include <WTFMainThreadNativesBase.h>
#include <mutex>
#include <pthread.h>

namespace WTF {

static pthread_main_np_t applicationUIThreadIdentifer;

struct ThreadFlags {
    enum {
        Main = 1 << 0,
        Web = 1 << 1,
        UI = 1 << 2,
    };
};
static thread_local uint32_t threadFlags;

static void dispatchFunctionOnMainThreadCallback(void* function)
{
    ASSERT(function);

    RunLoop::main().dispatch([=] {
        ((void(*)())function)();
    });
}

void initializeMainThreadPlatform()
{
    if (isMainThread())
        return;

    if (pthread_init_main_np() == 0) {
        pthread_setusercallback_np(dispatchFunctionOnMainThreadCallback);
        threadFlags |= ThreadFlags::Main;

        if (isApplicationUIThread()) {
            ASSERT(!applicationUIThreadIdentifer);
            applicationUIThreadIdentifer = pthread_get_main_np();
        }

        initializeGCThreads();
    }

    ASSERT(isMainThread());
}

void initializeWebThread()
{
    ASSERT(!isApplicationUIThread());
    threadFlags |= ThreadFlags::Web;
}

void initializeUIThread()
{
    static std::once_flag onceFlag;
    std::call_once(onceFlag, []{
        threadFlags |= ThreadFlags::UI;
    });

    ASSERT(isApplicationUIThread());
}

static void invokeDispatchFunctionsFromMainThread()
{
    dispatchFunctionsFromMainThread();
}

void scheduleDispatchFunctionsOnMainThread()
{
    pthread_callusercallback_np((void*)invokeDispatchFunctionsFromMainThread);
}

bool isMainThread()
{
    return Natives::WTFMainThread::isMainThread();
}

bool isWebThread()
{
    return Natives::WTFMainThread::isWebThread();
}

bool isUIThread()
{
    return Natives::WTFMainThread::isMainThread();
}

bool isApplicationUIThread()
{
    return Natives::WTFMainThread::isUIThread();
}

namespace Natives {

void WTFMainThread::initializeUIThread()
{
    WTF::initializeUIThread();
}

void WTFMainThread::initializeUIWorkerThread()
{
    ASSERT(applicationUIThreadIdentifer);
    pthread_init_current_np(applicationUIThreadIdentifer);
}

bool WTFMainThread::isMainThread()
{
    return (threadFlags & ThreadFlags::Main) != 0;
}

bool WTFMainThread::isWebThread()
{
    return (threadFlags & ThreadFlags::Web) != 0;
}

bool WTFMainThread::isUIThread()
{
    return (threadFlags & ThreadFlags::UI) != 0;
}

WTFMainThread* WTFMainThread::CTOR()
{
    ASSERT_NOT_REACHED();
    return new WTFMainThread;
}

}
} // namespace WTF
