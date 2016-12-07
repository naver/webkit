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
#include "SWKWebContentConfigurationNatives.h"

#include "APIProcessPoolConfiguration.h"
#include "APIWebsiteDataStore.h"
#include "WKPageGroup.h"
#include "WebProcessPool.h"
#include <wtf/NeverDestroyed.h>

namespace WebKit {

Native::PassLocalRef<Natives::SWKWebContentConfiguration> SWKWebContentConfiguration::create()
{
    return Natives::SWKWebContentConfiguration::create().as<SWKWebContentConfiguration>();
}

Native::PassLocalRef<Natives::SWKWebContentConfiguration> SWKWebContentConfiguration::create(WKPageConfigurationRef webPageConfiguration)
{
    Native::LocalRef<SWKWebContentConfiguration> configuration = Natives::SWKWebContentConfiguration::create();
    configuration->m_configuration = toImpl(webPageConfiguration);
    configuration->m_pageGroup = configuration->m_configuration->pageGroup();
    configuration->m_processPool = SWKProcessPool::create(*configuration->m_configuration->processPool());
    if (!configuration->m_configuration->websiteDataStore())
        configuration->m_configuration->setWebsiteDataStore(API::WebsiteDataStore::defaultDataStore().get());
    return configuration.release();
}

SWKWebContentConfiguration::SWKWebContentConfiguration()
    : m_groupIdentifier("")
    , m_applicationNameForUserAgent("")
    , m_configuration(nullptr)
{
}

Ref<API::PageConfiguration> SWKWebContentConfiguration::pageConfiguration()
{
    if (!m_configuration) {
        m_configuration = API::PageConfiguration::create();
        m_configuration->setWebsiteDataStore(API::WebsiteDataStore::defaultDataStore().get());
    }
    return *m_configuration;
}

PassRefPtr<WebPageGroup> SWKWebContentConfiguration::getOrCreatePageGroup()
{
    if (!m_pageGroup) {
        m_pageGroup = WebPageGroup::create(getGroupIdentifier().c_str());
        pageConfiguration()->setPageGroup(m_pageGroup.get());
    }
    return m_pageGroup;
}

void SWKWebContentConfiguration::setPageGroup(PassRefPtr<WebPageGroup> pageGroup)
{
    m_pageGroup = pageGroup;
    pageConfiguration()->setPageGroup(m_pageGroup.get());
}

Native::PassLocalRef<Natives::SWKProcessPool> SWKWebContentConfiguration::getProcessPool()
{
    if (!m_processPool) {
        m_processPool = SWKProcessPool::create(WebProcessPool::create(API::ProcessPoolConfiguration::create()));
        setProcessPool(m_processPool);
    }
    return m_processPool;
}

void SWKWebContentConfiguration::setProcessPool(Native::PassLocalRef<Natives::SWKProcessPool> processPool)
{
    m_processPool = processPool;
    pageConfiguration()->setProcessPool(&m_processPool.getPtr<SWKProcessPool>()->processPool());
}

Native::PassLocalRef<Natives::SWKPreferences> SWKWebContentConfiguration::getPreferences()
{
    // FIXME : need to move m_preferences allocation to setPreferences.
    if (!m_preferences) {
        m_preferences = SWKPreferences::create(&getOrCreatePageGroup()->preferences());
        setPreferences(m_preferences);
    }
    return m_preferences;
}

void SWKWebContentConfiguration::setPreferences(Native::PassLocalRef<Natives::SWKPreferences> preferences)
{
    m_preferences = preferences;
    pageConfiguration()->setPreferences(m_preferences.getPtr<SWKPreferences>()->webPreferences().get());
}

Native::PassLocalRef<Natives::SWKUserContentController> SWKWebContentConfiguration::getUserContentController()
{
    // FIXME : need to move m_userContentController allocation to setUserContentController.
    if (!m_userContentController) {
        m_userContentController = SWKUserContentController::create();
        setUserContentController(m_userContentController);
    }
    return m_userContentController;
}

void SWKWebContentConfiguration::setUserContentController(Native::PassLocalRef<Natives::SWKUserContentController> userContentController)
{
    m_userContentController = userContentController;
    pageConfiguration()->setUserContentController(m_userContentController.getPtr<SWKUserContentController>()->webUserContentController().get());
}

bool SWKWebContentConfiguration::isSuppressesIncrementalRendering()
{
    notImplemented();
    return false;
}

void SWKWebContentConfiguration::setSuppressesIncrementalRendering(bool suppressesIncrementalRendering)
{
    notImplemented();
}

std::string SWKWebContentConfiguration::getApplicationNameForUserAgent()
{
    return m_applicationNameForUserAgent;
}

void SWKWebContentConfiguration::setApplicationNameForUserAgent(const std::string& applicationNameForUserAgent)
{
    m_applicationNameForUserAgent = applicationNameForUserAgent;
}

bool SWKWebContentConfiguration::isAllowsInlineMediaPlayback()
{
    notImplemented();
    return false;
}

void SWKWebContentConfiguration::setAllowsInlineMediaPlayback(bool allowsInlineMediaPlayback)
{
    notImplemented();
}

bool SWKWebContentConfiguration::isMediaPlaybackRequiresUserAction()
{
    notImplemented();
    return false;
}

void SWKWebContentConfiguration::setMediaPlaybackRequiresUserAction(bool mediaPlaybackRequiresUserAction)
{
    notImplemented();
}

namespace Natives {

SWKWebContentConfiguration* SWKWebContentConfiguration::nativeCreate()
{
    return new ::WebKit::SWKWebContentConfiguration();
}

}
}
