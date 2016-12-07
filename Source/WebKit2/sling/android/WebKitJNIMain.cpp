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

#if defined(ANDROID)

#include <WebCore/Logging.h>

#include <string>

#include <cutils/log.h>
#include <sys/system_properties.h>

#include <onig/androidjni/JavaVM.h>

#if !LOG_DISABLED
#include <wtf/text/WTFString.h>
#define LOG_NAMESPACE "log.nw."
static void enableLogChannels();
#endif

extern void initializeWebKitJNIBindings();


JNI_EXPORT jint JNI_OnLoad(JavaVM* vm, void* /*reserved*/)
{
#if !LOG_DISABLED
    enableLogChannels();
#endif

    // Save the JavaVM pointer for use globally.
    Native::setVM(vm);

    JNIEnv* env = NULL;
    jint result = -1;

    if (vm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK) {
        ALOGE("GetEnv failed!");
        return result;
    }
    ALOG_ASSERT(env, "Could not retrieve the env!");

    initializeWebKitJNIBindings();

    return JNI_VERSION_1_4;
}

#if !LOG_DISABLED
static void checkAndEnableLogChannel(const char* channel)
{
    std::string key(LOG_NAMESPACE);
    key.append(channel);

    char value[PROP_VALUE_MAX];
    if (__system_property_get(key.c_str(), value) <= 0) {
        return;
    }

    WebCore::enableLogChannel(String(channel), !strcmp(value, "1"));
}

static void enableLogChannels()
{
    // WebCore/platform/Logging.h
    checkAndEnableLogChannel("Animations");
    checkAndEnableLogChannel("Archives");
    checkAndEnableLogChannel("BackForward");
    checkAndEnableLogChannel("Compositing");
    checkAndEnableLogChannel("DiskImageCache");
    checkAndEnableLogChannel("Editing");
    checkAndEnableLogChannel("Events");
    checkAndEnableLogChannel("FTP");
    checkAndEnableLogChannel("FileAPI");
    checkAndEnableLogChannel("Frames");
    checkAndEnableLogChannel("Gamepad");
    checkAndEnableLogChannel("History");
    checkAndEnableLogChannel("IconDatabase");
    checkAndEnableLogChannel("LiveConnect");
    checkAndEnableLogChannel("Loading");
    checkAndEnableLogChannel("Media");
    checkAndEnableLogChannel("MediaSource");
    checkAndEnableLogChannel("MediaSourceSamples");
    checkAndEnableLogChannel("MemoryPressure");
    checkAndEnableLogChannel("Network");
    checkAndEnableLogChannel("NotYetImplemented");
    checkAndEnableLogChannel("PageCache");
    checkAndEnableLogChannel("PlatformLeaks");
    checkAndEnableLogChannel("Plugins");
    checkAndEnableLogChannel("PopupBlocking");
    checkAndEnableLogChannel("Progress");
    checkAndEnableLogChannel("RemoteInspector");
    checkAndEnableLogChannel("ResourceLoading");
    checkAndEnableLogChannel("SQLDatabase");
    checkAndEnableLogChannel("SpellingAndGrammar");
    checkAndEnableLogChannel("StorageAPI");
    checkAndEnableLogChannel("Threading");
    checkAndEnableLogChannel("WebAudio");
    checkAndEnableLogChannel("WebGL");
    checkAndEnableLogChannel("WebReplay");

    // WebKit2/Platform/Logging.h
    checkAndEnableLogChannel("ContextMenu");
    checkAndEnableLogChannel("IconDatabase");
    checkAndEnableLogChannel("InspectorServer");
    checkAndEnableLogChannel("KeyHandling");
    checkAndEnableLogChannel("Network");
    checkAndEnableLogChannel("NetworkScheduling");
    checkAndEnableLogChannel("Plugins");
    checkAndEnableLogChannel("RemoteLayerTree");
    checkAndEnableLogChannel("SessionState");
    checkAndEnableLogChannel("StorageAPI");
    checkAndEnableLogChannel("TextInput");
    checkAndEnableLogChannel("View");
    checkAndEnableLogChannel("IDB");
    checkAndEnableLogChannel("Services");
}
#endif // !LOG_DISABLED

#endif // defined(ANDROID)
