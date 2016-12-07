/*
 * Copyright (C) 2006, 2007, 2014-2015 Apple Inc.  All rights reserved.
 * Copyright (C) 2015 Naver Corp. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#include "config.h"
#include "WebKitDLLMain.h"

#include "ForEachCoClass.h"
#include "RuntimeLink.h"
#include "WebKitClassFactory.h"
#include <wtf/StdLibExtras.h>

#include <sstream>

ULONG gLockCount;
ULONG gClassCount;
HINSTANCE gInstance;

#define CLSID_FOR_CLASS(cls) CLSID_##cls,
CLSID gRegCLSIDs[] = {
    FOR_EACH_COCLASS(CLSID_FOR_CLASS)
};
#undef CLSID_FOR_CLASS

STDAPI_(BOOL) DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID /*lpReserved*/)
{
    wchar_t dllPath[MAX_PATH];
    HRESULT hRes;

    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            gInstance = hModule;

            if (GetModuleFileNameW(hModule, dllPath, MAX_PATH) != 0) {
                wchar_t* filename = wcsrchr(dllPath, L'\\');
                if (filename)
                    *filename = 0;
                SetCurrentDirectoryW(dllPath);
            }

            runtimeLink();
            return TRUE;

        case DLL_PROCESS_DETACH:
            break;

        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
            break;
    }

    return FALSE;
}

_Check_return_
STDAPI DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID* ppv)
{
    bool found = false;
    for (size_t i = 0; i < WTF_ARRAY_LENGTH(gRegCLSIDs); ++i) {
        if (IsEqualGUID(rclsid, gRegCLSIDs[i])) {
            found = true;
            break;
        }
    }
    if (!found)
        return E_FAIL;

    if (!IsEqualGUID(riid, IID_IUnknown) && !IsEqualGUID(riid, IID_IClassFactory))
        return E_NOINTERFACE;

    WebKitClassFactory* factory = new WebKitClassFactory(rclsid);
    *ppv = reinterpret_cast<LPVOID>(factory);
    if (!factory)
        return E_OUTOFMEMORY;

    factory->AddRef();
    return S_OK;
}

STDAPI DllCanUnloadNow(void)
{
    if (!gClassCount && !gLockCount)
        return S_OK;
    
    return S_FALSE;
}

// deprecated - do not use
STDAPI DllUnregisterServer(void)
{
    return 0;
}

// deprecated - do not use
STDAPI DllRegisterServer(void)
{
    return 0;
}

// deprecated - do not use
STDAPI RunAsLocalServer()
{
    return 0;
}

// deprecated - do not use
STDAPI LocalServerDidDie()
{
    return 0;
}

void shutDownWebKit()
{
}

HRESULT APIResultHook(HRESULT res, const char* tag, const char* function)
{
    std::stringstream ss;
    ss << tag << ": " << function << std::endl;
    OutputDebugStringA(ss.str().c_str());
    return res;
}
