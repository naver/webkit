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
#include "WebProcess.h"

#include "NotImplemented.h"
#include "WKBase.h"
#include "WebFrameNetworkingContext.h"
#include "WebProcessCreationParameters.h"
#include <WebCore/AuthenticationChallenge.h>
#include <WebCore/Language.h>
#include <WebCore/MemoryCache.h>
#include <WebCore/PageCache.h>
#include <WebCore/NetworkingContext.h>
#include <WebCore/ResourceHandle.h>
#include <wtf/MainThread.h>
#include <wtf/RunLoop.h>
#include <wtf/text/CString.h>

#if USE(GRAPHICS_SURFACE)
#include <WebCore/GraphicsSurfacePbufferPrivate.h>
#endif

using namespace WebCore;

namespace WebKit {

static uint64_t getMemorySize()
{
    static uint64_t kDefaultMemorySize = 512;
#if !OS(WINDOWS)
    // Copied from WebProcessSoup.cpp
    long pageSize = sysconf(_SC_PAGESIZE);
    if (pageSize == -1)
        return kDefaultMemorySize;

    long physPages = sysconf(_SC_PHYS_PAGES);
    if (physPages == -1)
        return kDefaultMemorySize;

    return ((pageSize / 1024LL) * physPages) / 1024LL;
#else
    // Based on chromium: base/sys_info_win.cc: AmountOfPhysicalMemory()
    MEMORYSTATUSEX memory_info;
    memory_info.dwLength = sizeof(memory_info);
    if (!GlobalMemoryStatusEx(&memory_info))
        return kDefaultMemorySize;
    return static_cast<uint64_t>(memory_info.ullTotalPhys) / 1048576LL;
#endif
}

void WebProcess::platformSetCacheModel(CacheModel cacheModel)
{
    notImplemented();
}

void WebProcess::platformClearResourceCaches(ResourceCachesToClear)
{
    notImplemented();
}

void WebProcess::platformInitializeWebProcess(WebProcessCreationParameters&& parameters)
{
    notImplemented();
}

void WebProcess::platformTerminate()
{
    notImplemented();
}

} // namespace WebKit
