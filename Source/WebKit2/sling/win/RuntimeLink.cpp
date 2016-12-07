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
#include "RuntimeLink.h"

#include "CompletionHandler.h"
#include "GraphicsSurfacePbuffer.h"
#include "GraphicsSurfaceTextureHost.h"
#include "SWKApplicationCacheManager.h"
#include "SWKAuthenticationChallenge.h"
#include "SWKBackForwardList.h"
#include "SWKBackForwardListItem.h"
#include "SWKContextMenuItem.h"
#include "SWKData.h"
#include "SWKError.h"
#include "SWKIconDatabase.h"
#include "SWKKeyValueStorageManager.h"
#include "SWKNavigationAction.h"
#include "SWKNotification.h"
#include "SWKOpenPanelResultListener.h"
#include "SWKPreferences.h"
#include "SWKProcessPool.h"
#include "SWKSecurityOrigin.h"
#include "SWKURLRequest.h"
#include "SWKURLResponse.h"
#include "SWKUserScript.h"
#include "SWKUserStyleSheet.h"
#include "SWKView.h"
#include "SWKVisitedLinkStore.h"
#include "SWKWebContent.h"
#include "SWKWebContentConfiguration.h"
#include "SWKWebHitTestResult.h"
#include "SWKWindowFeatures.h"
#include "WebAudioDestination.h"
#include "WebAudioFileReader.h"
#include "WebContextMenu.h"
#include "WebEditable.h"
#include "WebMediaPlayer.h"
#include "WebMenu.h"
#include "WebMenuItem.h"
#include <os/Process.h>

using namespace webkit;

#define RUNTIME_LINK(name) name::runtimeLink<name>()

void runtimeLink()
{
    static bool linked = false;
    if (linked)
        return;

    os::Process::initialize();

    RUNTIME_LINK(CompletionHandler);
    RUNTIME_LINK(GraphicsSurfacePbuffer);
    RUNTIME_LINK(GraphicsSurfaceTextureHost);
    RUNTIME_LINK(SWKApplicationCacheManager);
    RUNTIME_LINK(SWKAuthenticationChallenge);
    RUNTIME_LINK(SWKBackForwardList);
    RUNTIME_LINK(SWKBackForwardListItem);
    RUNTIME_LINK(SWKContextMenuItem);
    RUNTIME_LINK(SWKData);
    RUNTIME_LINK(SWKError);
    RUNTIME_LINK(SWKIconDatabase);
    RUNTIME_LINK(SWKKeyValueStorageManager);
    RUNTIME_LINK(SWKNavigationAction);
    RUNTIME_LINK(SWKNotification);
    RUNTIME_LINK(SWKOpenPanelResultListener);
    RUNTIME_LINK(SWKPreferences);
    RUNTIME_LINK(SWKProcessPool);
    RUNTIME_LINK(SWKSecurityOrigin);
    RUNTIME_LINK(SWKURLRequest);
    RUNTIME_LINK(SWKURLResponse);
    RUNTIME_LINK(SWKUserScript);
    RUNTIME_LINK(SWKUserStyleSheet);
    RUNTIME_LINK(SWKView);
    RUNTIME_LINK(SWKVisitedLinkStore);
    RUNTIME_LINK(SWKWebContent);
    RUNTIME_LINK(SWKWebContentConfiguration);
    RUNTIME_LINK(SWKWebHitTestResult);
    RUNTIME_LINK(SWKWindowFeatures);
    RUNTIME_LINK(WebAudioDestination);
    RUNTIME_LINK(WebAudioFileReader);
    RUNTIME_LINK(WebContextMenu);
    RUNTIME_LINK(WebEditable);
    RUNTIME_LINK(WebMediaPlayer);
    RUNTIME_LINK(WebMenu);
    RUNTIME_LINK(WebMenuItem);

    linked = true;
}
