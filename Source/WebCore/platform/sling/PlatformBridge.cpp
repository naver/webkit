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
#include "PlatformBridge.h"

#include <ManagedPoint.h>
#include <ManagedString.h>
#include <ManagedVector.h>

#include <windows.h>

#include <codecvt>
#include <locale>
#include <vector>

namespace webkit {

void PlatformBridge::INIT()
{
}

} // namespace webkit

namespace WebKit {
namespace Managed {

static std::string ws2s(const std::wstring& wstr)
{
    typedef std::codecvt_utf8<wchar_t> convert_typeX;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(wstr);
}

std::string PlatformBridge::getPackageName()
{
    return std::string();
}

std::string PlatformBridge::getVersionName()
{
    return "0.0.2";
}

std::shared_ptr<Managed::Point> PlatformBridge::screenSize()
{
    RECT screenSize;
    ::GetWindowRect(GetDesktopWindow(), &screenSize);

    return Managed::Point::create(static_cast<unsigned int>(screenSize.right - screenSize.left),
        static_cast<unsigned int>(screenSize.bottom - screenSize.top));
}

std::shared_ptr<Managed::Point> PlatformBridge::availableScreenSize()
{
    RECT availableScreenSize;
    ::SystemParametersInfo(SPI_GETWORKAREA, 0, &availableScreenSize, 0);

    return Managed::Point::create(static_cast<unsigned int>(availableScreenSize.right - availableScreenSize.left),
        static_cast<unsigned int>(availableScreenSize.bottom - availableScreenSize.top));
}

static DEVMODE deviceMonitorInfo()
{
    // FIXME: We need to get this information from current window handle. Other ports have gotten
    // the information from window.
    HMONITOR monitor = MonitorFromWindow(GetDesktopWindow(), MONITOR_DEFAULTTOPRIMARY);

    MONITORINFOEX monitorInfo;
    monitorInfo.cbSize = sizeof(MONITORINFOEX);
    GetMonitorInfo(monitor, &monitorInfo);

    DEVMODE deviceInfo;
    deviceInfo.dmSize = sizeof(DEVMODE);
    deviceInfo.dmDriverExtra = 0;
    EnumDisplaySettings(monitorInfo.szDevice, ENUM_CURRENT_SETTINGS, &deviceInfo);

    return deviceInfo;
}

int32_t PlatformBridge::screenDepth()
{
    DEVMODE deviceInfo = deviceMonitorInfo();
    if (deviceInfo.dmBitsPerPel == 32) {
        // Some video drivers return 32, but this function is supposed to ignore the alpha
        // component. See <http://webkit.org/b/42972>.
        return 24;
    }
    return deviceInfo.dmBitsPerPel;
}

bool PlatformBridge::screenIsMonochrome()
{
    DEVMODE deviceInfo = deviceMonitorInfo();
    return deviceInfo.dmColor == DMCOLOR_MONOCHROME;
}

std::string PlatformBridge::getApplicationDirectoryPath()
{
    wchar_t buffer[MAX_PATH] = { 0, };
    int length = ::GetModuleFileName(NULL, buffer, MAX_PATH);
    if (!length)
        return "";

    std::string currentExePath(ws2s(buffer));
    std::string::size_type fileName = currentExePath.find_last_of("\\/");
    return currentExePath.substr(0, fileName);
}

static std::string getApplicationName()
{
    // FIXME: Need to implement
    return "NaverBrowser";
}

static std::string getCompanyName()
{
    // FIXME: Need to implement
    return "Naver";
}

std::string PlatformBridge::getWebsiteDataDirectory()
{
    int bufferSize = GetEnvironmentVariableW(L"LOCALAPPDATA", nullptr, 0);
    if (!bufferSize)
        return "";

    std::vector<wchar_t> buffer;
    buffer.reserve(bufferSize);
    bufferSize = GetEnvironmentVariableW(L"LOCALAPPDATA", buffer.data(), bufferSize);
    if (!bufferSize)
        return "";

    return ws2s(buffer.data()) + "\\" + getCompanyName() + "\\" + getApplicationName();
}

std::string PlatformBridge::resolveFilePathForContentUri(const std::string& contentUri)
{
    return "";
}

std::string PlatformBridge::getInspectorServerAddress()
{
    static const char WEBKIT_INSPECTOR_SERVER[] = "127.0.0.1:2999";
    return WEBKIT_INSPECTOR_SERVER;
}

/* platformLanguage and localeInfo are almost verbatim from
 * LanguageWin.cpp.  Slightly modified to use std::string instead of WTFString.
 * On Korean versions of Windows, we typically see "ko-KR".
 */
static std::string localeInfo(LCTYPE localeType, const std::string& fallback)
{
    LANGID langID = GetUserDefaultUILanguage();
    int localeChars = GetLocaleInfoW(langID, localeType, 0, 0);
    if (!localeChars)
        return fallback;
    std::vector<wchar_t> buffer;
    buffer.reserve(localeChars);
    localeChars = GetLocaleInfoW(langID, localeType, buffer.data(), localeChars);
    if (!localeChars)
        return fallback;
    return ws2s(buffer.data());
}

static std::string platformLanguage()
{
    static std::string computedDefaultLanguage;
    if (!computedDefaultLanguage.empty())
        return computedDefaultLanguage;

    std::string languageName = localeInfo(LOCALE_SISO639LANGNAME, "en");
    std::string countryName = localeInfo(LOCALE_SISO3166CTRYNAME, std::string());

    if (countryName.empty())
        computedDefaultLanguage = languageName;
    else
        computedDefaultLanguage = languageName + '-' + countryName;

    return computedDefaultLanguage;
}

std::string PlatformBridge::computeDefaultLanguage()
{
    return platformLanguage();
}

std::shared_ptr<Managed::Vector> PlatformBridge::getSupportedKeyStrengthList()
{
    return Managed::Vector::create();
}

std::string PlatformBridge::getSignedPublicKeyAndChallengeString(int32_t index, const std::string& challenge, const std::string& url)
{
    return "";
}

std::string PlatformBridge::getDefaultInjectedBundlePath()
{
    return getApplicationDirectoryPath() + "\\InjectedBundleSling.dll";
}

std::string PlatformBridge::getDefaultWebInspectorPath()
{
    return getApplicationDirectoryPath() + "\\WebKit.resources\\WebInspectorUI";
}

static bool isWOW64()
{
    static bool initialized = false;
    static bool wow64 = false;

    if (!initialized) {
        initialized = true;
        HMODULE kernel32Module = GetModuleHandleA("kernel32.dll");
        if (!kernel32Module)
            return wow64;
        typedef BOOL(WINAPI* IsWow64ProcessFunc)(HANDLE, PBOOL);
        IsWow64ProcessFunc isWOW64Process = reinterpret_cast<IsWow64ProcessFunc>(GetProcAddress(kernel32Module, "IsWow64Process"));
        if (isWOW64Process) {
            BOOL result = FALSE;
            wow64 = isWOW64Process(GetCurrentProcess(), &result) && result;
        }
    }

    return wow64;
}

static WORD processorArchitecture()
{
    static bool initialized = false;
    static WORD architecture = PROCESSOR_ARCHITECTURE_INTEL;

    if (!initialized) {
        initialized = true;
        HMODULE kernel32Module = GetModuleHandleA("kernel32.dll");
        if (!kernel32Module)
            return architecture;
        typedef VOID(WINAPI* GetNativeSystemInfoFunc)(LPSYSTEM_INFO);
        GetNativeSystemInfoFunc getNativeSystemInfo = reinterpret_cast<GetNativeSystemInfoFunc>(GetProcAddress(kernel32Module, "GetNativeSystemInfo"));
        if (getNativeSystemInfo) {
            SYSTEM_INFO systemInfo;
            ZeroMemory(&systemInfo, sizeof(systemInfo));
            getNativeSystemInfo(&systemInfo);
            architecture = systemInfo.wProcessorArchitecture;
        }
    }

    return architecture;
}

static std::string getCPUArchitecture()
{
    if (isWOW64())
        return "; WOW64";
    if (processorArchitecture() == PROCESSOR_ARCHITECTURE_AMD64)
        return "; Win64; x64";
    if (processorArchitecture() == PROCESSOR_ARCHITECTURE_IA64)
        return "; Win64; IA64";
    return std::string();
}

std::string PlatformBridge::getPlatformVersionForUserAgent()
{
    static bool initialized = false;
    static int majorVersion, minorVersion;

    if (!initialized) {
        initialized = true;
        OSVERSIONINFOEX versionInfo;
        ZeroMemory(&versionInfo, sizeof(versionInfo));
        versionInfo.dwOSVersionInfoSize = sizeof(versionInfo);
        GetVersionEx(reinterpret_cast<OSVERSIONINFO*>(&versionInfo));
        majorVersion = versionInfo.dwMajorVersion;
        minorVersion = versionInfo.dwMinorVersion;
    }

    return "Windows NT " + std::to_string(majorVersion) + "." + std::to_string(minorVersion) + getCPUArchitecture();
}

std::shared_ptr<Managed::Vector> PlatformBridge::getSupportedMediaMimeTypeList()
{
    const char* mimeTypes[] = {
        "audio/flac",
        "audio/mp1",
        "audio/mp2",
        "audio/mp3",
        "audio/mp4",
        "audio/mpeg",
        "audio/ogg",
        "audio/wav",
        "audio/x-flac",
        "audio/x-mp3",
        "audio/x-mpeg",
        "audio/x-wav",
        "audio/x-ms-wma",
        "video/flv",
        "video/mp4",
        "video/mpeg",
        "video/mpegts",
        "video/ogg",
        "video/quicktime",
        "video/x-m4v",
        "video/x-ms-asf",
        "video/x-msvideo",
    };

    std::shared_ptr<Managed::Vector> cache = Managed::Vector::create();
    for (unsigned i = 0; i < (sizeof(mimeTypes) / sizeof(*mimeTypes)); ++i)
        cache->add(::Managed::createString(mimeTypes[i]));

    return cache;
}
}
} // namespace WebKit
