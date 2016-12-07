/*
 * Copyright (C) 2014 Naver Corp. All rights reserved.
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

#ifndef SWKWebContentConfiguration_h
#define SWKWebContentConfiguration_h

#include "APIPageConfiguration.h"
#include "SWKPreferencesNatives.h"
#include "SWKProcessPoolNatives.h"
#include "SWKUserContentControllerNatives.h"
#include "SWKWebContentConfigurationNativesBase.h"
#include "WebPageGroup.h"

#include <onig/GlobalRef.h>

namespace WebKit {

class SWKWebContentConfiguration final : public Natives::SWKWebContentConfiguration {
    friend class Natives::SWKWebContentConfiguration;
public:
    static Native::PassLocalRef<Natives::SWKWebContentConfiguration> create();
    static Native::PassLocalRef<Natives::SWKWebContentConfiguration> create(WKPageConfigurationRef);

    PassRefPtr<WebPageGroup> getOrCreatePageGroup();
    void setPageGroup(PassRefPtr<WebPageGroup> pageGroup);

    Native::PassLocalRef<Natives::SWKProcessPool> getProcessPool() override;
    void setProcessPool(Native::PassLocalRef<Natives::SWKProcessPool>) override;

    Native::PassLocalRef<Natives::SWKPreferences> getPreferences() override;
    void setPreferences(Native::PassLocalRef<Natives::SWKPreferences>) override;

    Native::PassLocalRef<Natives::SWKUserContentController> getUserContentController() override;
    void setUserContentController(Native::PassLocalRef<Natives::SWKUserContentController>) override;

    bool isSuppressesIncrementalRendering() override;
    void setSuppressesIncrementalRendering(bool) override;

    std::string getApplicationNameForUserAgent() override;
    void setApplicationNameForUserAgent(const std::string&) override;

    bool isAllowsInlineMediaPlayback() override;
    void setAllowsInlineMediaPlayback(bool) override;

    bool isMediaPlaybackRequiresUserAction() override;
    void setMediaPlaybackRequiresUserAction(bool) override;

    void setGroupIdentifier(const std::string& groupIdentifier) override { m_groupIdentifier = groupIdentifier; }
    std::string getGroupIdentifier() override { return m_groupIdentifier; }

    void setRelatedPage(WebPageProxy* relatedPage) { m_configuration->setRelatedPage(relatedPage); }
    WebPageProxy* relatedPage() { return m_configuration->relatedPage(); }

    Ref<API::PageConfiguration> pageConfiguration();

private:
    SWKWebContentConfiguration();

    std::string m_groupIdentifier;
    std::string m_applicationNameForUserAgent;

    RefPtr<API::PageConfiguration> m_configuration;

    RefPtr<WebPageGroup> m_pageGroup;
    Native::GlobalRef<SWKProcessPool> m_processPool;
    Native::GlobalRef<SWKPreferences> m_preferences;
    Native::GlobalRef<SWKUserContentController> m_userContentController;
};

}

#endif // SWKWebContentConfiguration_h
