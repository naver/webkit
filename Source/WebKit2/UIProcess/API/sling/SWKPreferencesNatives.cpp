/*
 * Copyright (C) 2014-2015 Naver Corp. All rights reserved.
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
#include "SWKPreferencesNatives.h"

#include <wtf/text/CString.h>

namespace WebKit {

class SWKPreferencesPrivate : public Natives::SWKPreferences::Private {
public:
    RefPtr<WebPreferences> m_preferences;
};

static SWKPreferencesPrivate* ptr(const std::unique_ptr<Natives::SWKPreferences::Private>& p)
{
    return static_cast<SWKPreferencesPrivate*>(p.get());
}

Native::PassLocalRef<SWKPreferences> SWKPreferences::create(WebPreferences* preferences)
{
    Native::LocalRef<SWKPreferences> webPreferences = Natives::SWKPreferences::create().as<SWKPreferences>();
    ptr(webPreferences->m_private)->m_preferences = preferences;
    return webPreferences;
}

RefPtr<WebPreferences> SWKPreferences::webPreferences()
{
    return ptr(m_private)->m_preferences;
}

namespace Natives {

SWKPreferences* SWKPreferences::nativeCreate()
{
    auto nativeObject = new ::WebKit::SWKPreferences;
    nativeObject->m_private.reset(new SWKPreferencesPrivate);
    return nativeObject;
}

void SWKPreferences::setFullScreenEnabled(bool enable)
{
    ptr(m_private)->m_preferences->setFullScreenEnabled(enable);
}

bool SWKPreferences::getFullScreenEnabled()
{
    return ptr(m_private)->m_preferences->fullScreenEnabled();
}

void SWKPreferences::setJavascriptEnabled(bool enable)
{
    ptr(m_private)->m_preferences->setJavaScriptEnabled(enable);
}

bool SWKPreferences::getJavascriptEnabled()
{
    return ptr(m_private)->m_preferences->javaScriptEnabled();
}

void SWKPreferences::setMinimumFontSize(int32_t size)
{
    ptr(m_private)->m_preferences->setMinimumFontSize(size);
}

int32_t SWKPreferences::getMinimumFontSize()
{
    return ptr(m_private)->m_preferences->minimumFontSize();
}

void SWKPreferences::setJavaScriptCanOpenWindowsAutomatically(bool enable)
{
    ptr(m_private)->m_preferences->setJavaScriptCanOpenWindowsAutomatically(enable);
}

bool SWKPreferences::getJavaScriptCanOpenWindowsAutomatically()
{
    return ptr(m_private)->m_preferences->javaScriptCanOpenWindowsAutomatically();
}

void SWKPreferences::setLoadsImagesAutomatically(bool automatic)
{
    ptr(m_private)->m_preferences->setLoadsImagesAutomatically(automatic);
}

bool SWKPreferences::getLoadsImagesAutomatically()
{
    return ptr(m_private)->m_preferences->loadsImagesAutomatically();
}

void SWKPreferences::setDeveloperExtrasEnabled(bool enable)
{
    ptr(m_private)->m_preferences->setDeveloperExtrasEnabled(enable);
}

bool SWKPreferences::getDeveloperExtrasEnabled()
{
    return ptr(m_private)->m_preferences->developerExtrasEnabled();
}

void SWKPreferences::setFileAccessFromFileUrlsAllowed(bool enable)
{
    ptr(m_private)->m_preferences->setAllowFileAccessFromFileURLs(enable);
}

bool SWKPreferences::getFileAccessFromFileUrlsAllowed()
{
    return ptr(m_private)->m_preferences->allowFileAccessFromFileURLs();
}

void SWKPreferences::setFrameFlatteningEnabled(bool enable)
{
    ptr(m_private)->m_preferences->setFrameFlatteningEnabled(enable);
}

bool SWKPreferences::getFrameFlatteningEnabled()
{
    return ptr(m_private)->m_preferences->frameFlatteningEnabled();
}

void SWKPreferences::setDNSPrefetchingEnabled(bool enable)
{
    ptr(m_private)->m_preferences->setDNSPrefetchingEnabled(enable);
}

bool SWKPreferences::getDNSPrefetchingEnabled()
{
    return ptr(m_private)->m_preferences->dnsPrefetchingEnabled();
}

void SWKPreferences::setEncodingDetectorEnabled(bool enable)
{
    ptr(m_private)->m_preferences->setUsesEncodingDetector(enable);
}

bool SWKPreferences::getEncodingDetectorEnabled()
{
    return ptr(m_private)->m_preferences->usesEncodingDetector();
}

void SWKPreferences::setDefaultTextEncodingName(const std::string& encodingName)
{
    ptr(m_private)->m_preferences->setDefaultTextEncodingName(String(encodingName.c_str(), encodingName.size()));
}

std::string SWKPreferences::getDefaultTextEncodingName()
{
    return ptr(m_private)->m_preferences->defaultTextEncodingName().utf8().data();
}

void SWKPreferences::setPreferredMinimumContentsWidth(int32_t width)
{
    ptr(m_private)->m_preferences->setLayoutFallbackWidth(width);
}

int32_t SWKPreferences::getPreferredMinimumContentsWidth()
{
    return ptr(m_private)->m_preferences->layoutFallbackWidth();
}

void SWKPreferences::setOfflineWebApplicationCacheEnabled(bool enable)
{
    ptr(m_private)->m_preferences->setOfflineWebApplicationCacheEnabled(enable);
}

bool SWKPreferences::getOfflineWebApplicationCacheEnabled()
{
    return ptr(m_private)->m_preferences->offlineWebApplicationCacheEnabled();
}

void SWKPreferences::setScriptsCanOpenWindows(bool enable)
{
    ptr(m_private)->m_preferences->setJavaScriptCanOpenWindowsAutomatically(enable);
}

bool SWKPreferences::getScriptsCanOpenWindows()
{
    return ptr(m_private)->m_preferences->javaScriptCanOpenWindowsAutomatically();
}

void SWKPreferences::setLocalStorageEnabled(bool enable)
{
    ptr(m_private)->m_preferences->setLocalStorageEnabled(enable);
}

bool SWKPreferences::getLocalStorageEnabled()
{
    return ptr(m_private)->m_preferences->localStorageEnabled();
}

void SWKPreferences::setPluginsEnabled(bool enable)
{
    ptr(m_private)->m_preferences->setPluginsEnabled(enable);
}

bool SWKPreferences::getPluginsEnabled()
{
    return ptr(m_private)->m_preferences->pluginsEnabled();
}

void SWKPreferences::setDefaultFontSize(int32_t size)
{
    ptr(m_private)->m_preferences->setDefaultFontSize(size);
}

int32_t SWKPreferences::getDefaultFontSize()
{
    return ptr(m_private)->m_preferences->defaultFontSize();
}

void SWKPreferences::setPrivateBrowsingEnabled(bool enable)
{
    ptr(m_private)->m_preferences->setPrivateBrowsingEnabled(enable);
}

bool SWKPreferences::getPrivateBrowsingEnabled()
{
    return ptr(m_private)->m_preferences->privateBrowsingEnabled();
}

void SWKPreferences::setTextAutosizingEnabled(bool enable)
{
    ptr(m_private)->m_preferences->setTextAutosizingEnabled(enable);
}

bool SWKPreferences::getTextAutosizingEnabled()
{
    return ptr(m_private)->m_preferences->textAutosizingEnabled();
}

void SWKPreferences::setSpatialNavigationEnabled(bool enable)
{
    ptr(m_private)->m_preferences->setSpatialNavigationEnabled(enable);
}

bool SWKPreferences::getSpatialNavigationEnabled()
{
    return ptr(m_private)->m_preferences->spatialNavigationEnabled();
}

void SWKPreferences::setDatabasesEnabled(bool enable)
{
    ptr(m_private)->m_preferences->setDatabasesEnabled(enable);
}

bool SWKPreferences::getDatabasesEnabled()
{
    return ptr(m_private)->m_preferences->databasesEnabled();
}

bool SWKPreferences::getSuppressesIncrementalRendering()
{
    return ptr(m_private)->m_preferences->suppressesIncrementalRendering();
}

void SWKPreferences::setSuppressesIncrementalRendering(bool enable)
{
    ptr(m_private)->m_preferences->setSuppressesIncrementalRendering(enable);
}

bool SWKPreferences::getSmartInsertDeleteEnabled()
{
    return ptr(m_private)->m_preferences->smartInsertDeleteEnabled();
}

void SWKPreferences::setSmartInsertDeleteEnabled(bool enable)
{
    ptr(m_private)->m_preferences->setSmartInsertDeleteEnabled(enable);
}

void SWKPreferences::setHiddenPageDOMTimerThrottlingEnabled(bool enable)
{
    ptr(m_private)->m_preferences->setHiddenPageDOMTimerThrottlingEnabled(enable);
}

void SWKPreferences::setHiddenPageCSSAnimationSuspensionEnabled(bool enable)
{
    ptr(m_private)->m_preferences->setHiddenPageCSSAnimationSuspensionEnabled(enable);
}

void SWKPreferences::setJavaScriptCanAccessClipboard(bool enable)
{
    ptr(m_private)->m_preferences->setJavaScriptCanAccessClipboard(enable);
}

void SWKPreferences::setScrollAnimatorEnabled(bool enable)
{
    ptr(m_private)->m_preferences->setScrollAnimatorEnabled(enable);
}

bool SWKPreferences::getScrollAnimatorEnabled()
{
    return ptr(m_private)->m_preferences->scrollAnimatorEnabled();
}

void SWKPreferences::setUsesPageCache(bool enable)
{
    ptr(m_private)->m_preferences->setUsesPageCache(enable);
}

bool SWKPreferences::getUsesPageCache()
{
    return ptr(m_private)->m_preferences->usesPageCache();
}

void SWKPreferences::setPageCacheSupportsPlugins(bool enable)
{
    ptr(m_private)->m_preferences->setPageCacheSupportsPlugins(enable);
}

bool SWKPreferences::getPageCacheSupportsPlugins()
{
    return ptr(m_private)->m_preferences->pageCacheSupportsPlugins();
}

}
}
