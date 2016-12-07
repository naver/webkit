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

#include "ChildProcessLauncherNatives.h"
#include "CompletionHandlerNatives.h"
#include "NativesString.h"
#include "SWKApplicationCacheManagerNatives.h"
#include "SWKAuthenticationChallengeNatives.h"
#include "SWKBackForwardListNatives.h"
#include "SWKBackForwardListItemNatives.h"
#include "SWKContextMenuItemNatives.h"
#include "SWKCookieManagerNatives.h"
#include "SWKDownloadNatives.h"
#include "SWKErrorNatives.h"
#include "SWKFormDelegateNatives.h"
#include "SWKGeolocationManagerNatives.h"
#include "SWKGeolocationProviderNatives.h"
#include "SWKIconDatabaseNatives.h"
#include "SWKKeyValueStorageManagerNatives.h"
#include "SWKNavigationActionNatives.h"
#include "SWKNotificationNatives.h"
#include "SWKOpenPanelResultListenerNatives.h"
#include "SWKPreferencesNatives.h"
#include "SWKProcessPoolNatives.h"
#include "SWKResourceCacheManagerNatives.h"
#include "SWKSecurityOriginNatives.h"
#include "SWKURLNatives.h"
#include "SWKURLRequestNatives.h"
#include "SWKURLResponseNatives.h"
#include "SWKViewNatives.h"
#include "SWKVisitedLinkStoreNatives.h"
#include "SWKWebContentNatives.h"
#include "SWKWebContentConfigurationNatives.h"
#include "SWKWebHitTestResultNatives.h"
#include "ThreadLoopBackendNativesBase.h"
#include "ValueCallbackNatives.h"
#include "WTFMainThreadNativesBase.h"
#include "WebBitmapNatives.h"
#include "WebContextMenuNatives.h"
#include "WebMenuNatives.h"
#include "WebMenuItemNatives.h"
#include "WebEditableNatives.h"
#include "WebMediaPlayerNatives.h"
#include "WebRendererNatives.h"

void initializeWebKitJNIBindings()
{
    WTF::Natives::ThreadLoopBackend::registerClass();
    WTF::Natives::WTFMainThread::registerClass();
    WebKit::Natives::ChildProcessLauncher::registerClass();
    WebKit::Natives::CompletionHandler::registerClass();
    Native::Natives::String::registerClass();
    WebKit::Natives::SWKApplicationCacheManager::registerClass();
    WebKit::Natives::SWKAuthenticationChallenge::registerClass();
    WebKit::Natives::SWKBackForwardList::registerClass();
    WebKit::Natives::SWKBackForwardListItem::registerClass();
    WebKit::Natives::SWKContextMenuItem::registerClass();
    WebKit::Natives::SWKCookieManager::registerClass();
    WebKit::Natives::SWKDownload::registerClass();
    WebKit::Natives::SWKError::registerClass();
    WebKit::Natives::SWKFormDelegate::registerClass();
    WebKit::Natives::SWKGeolocationManager::registerClass();
    WebKit::Natives::SWKGeolocationProvider::registerClass();
    WebKit::Natives::SWKIconDatabase::registerClass();
    WebKit::Natives::SWKKeyValueStorageManager::registerClass();
    WebKit::Natives::SWKNavigationAction::registerClass();
    WebKit::Natives::SWKOpenPanelResultListener::registerClass();
    WebKit::Natives::SWKPreferences::registerClass();
    WebKit::Natives::SWKProcessPool::registerClass();
    WebKit::Natives::SWKResourceCacheManager::registerClass();
    WebKit::Natives::SWKSecurityOrigin::registerClass();
    WebKit::Natives::SWKURL::registerClass();
    WebKit::Natives::SWKURLRequest::registerClass();
    WebKit::Natives::SWKURLResponse::registerClass();
    WebKit::Natives::SWKView::registerClass();
    WebKit::Natives::SWKVisitedLinkStore::registerClass();
    WebKit::Natives::SWKWebContent::registerClass();
    WebKit::Natives::SWKWebContentConfiguration::registerClass();
    WebKit::Natives::SWKWebHitTestResult::registerClass();
    WebKit::Natives::SWKError::registerClass();
    WebKit::Natives::ValueCallback::registerClass();
    WebKit::Natives::WebBitmap::registerClass();
    WebKit::Natives::WebContextMenu::registerClass();
    WebKit::Natives::WebMenu::registerClass();
    WebKit::Natives::WebMenuItem::registerClass();
    WebKit::Natives::WebEditable::registerClass();
    WebKit::Natives::WebRenderer::registerClass();
    WebKit::Natives::WebMediaPlayer::registerClass();
}

#endif // defined(ANDROID)
