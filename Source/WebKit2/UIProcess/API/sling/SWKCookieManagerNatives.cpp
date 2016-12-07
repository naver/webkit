/*
 * Copyright (C) 2014-2016 Naver Corp. All rights reserved.
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
#include "SWKCookieManagerNatives.h"

#include "WebCookieManagerProxy.h"
#include "WKAPICast.h"
#include "WKCookieManager.h"
#include <wtf/text/CString.h>

using namespace WebCore;

namespace WebKit {

Native::PassLocalRef<SWKCookieManager> SWKCookieManager::create(WebCookieManagerProxy* cookieManager)
{
    Native::LocalRef<SWKCookieManager> manager = Natives::SWKCookieManager::create().as<SWKCookieManager>();
    manager->m_cookieManager = cookieManager;
    return manager;
}

SWKCookieManager::SWKCookieManager()
{
}

SWKCookieManager::~SWKCookieManager()
{
    if (m_changesObserverCallback)
        m_cookieManager->stopObservingCookieChanges();

    WKCookieManagerSetClient(toAPI(m_cookieManager), nullptr);
}

static void cookiesDidChangeCallback(WKCookieManagerRef, const void* clientInfo)
{
    SWKCookieManager* cookieManager = static_cast<SWKCookieManager*>(const_cast<void*>(clientInfo));
    cookieManager->cookiesDidChange();
}

void SWKCookieManager::initialize()
{
    WKCookieManagerClientV0 cookieManagerClient;
    memset(&cookieManagerClient, 0, sizeof(cookieManagerClient));
    cookieManagerClient.base.version = 0;
    cookieManagerClient.base.clientInfo = this;
    cookieManagerClient.cookiesDidChange = cookiesDidChangeCallback;

    WKCookieManagerSetClient(toAPI(m_cookieManager), &cookieManagerClient.base);
}

void SWKCookieManager::cookiesDidChange()
{
    m_changesObserverCallback->onReceiveBoolean(true);
}

void SWKCookieManager::getHTTPAcceptPolicy(Native::PassLocalRef<Natives::ValueCallback> callback)
{
    m_cookieManager->getHTTPCookieAcceptPolicy([callback](HTTPCookieAcceptPolicy policy, CallbackBase::Error) {
        callback->onReceiveInt(policy);
    });
}

void SWKCookieManager::setHTTPAcceptPolicy(int32_t policy)
{
    m_cookieManager->setHTTPCookieAcceptPolicy(static_cast<HTTPCookieAcceptPolicy>(policy));
}

void SWKCookieManager::setCookie(const std::string& url, const std::string& value)
{
    notImplemented();
}

std::string SWKCookieManager::getCookie(const std::string& url)
{
    notImplemented();
    return "";
}

void SWKCookieManager::clearHostnameCookies(const std::string& hostName)
{
    m_cookieManager->deleteCookiesForHostname(String::fromUTF8(hostName.c_str()));
}

void SWKCookieManager::clearAllCookies()
{
    m_cookieManager->deleteAllCookies();
}

void SWKCookieManager::clearAllExpiredCookies()
{
    notImplemented();
}

void SWKCookieManager::clearAllSessionCookies()
{
    notImplemented();
}

void SWKCookieManager::getHostNamesWithCookies(Native::PassLocalRef<Natives::ValueCallback> callback)
{
    // FIXME: It should be refactored to use Natives::Vector when Natives::Vector supports string.
    m_cookieManager->getHostnamesWithCookies([callback](API::Array* hostNames, CallbackBase::Error) {
        for (auto& it : hostNames->toStringVector()) {
            if (it.isEmpty())
                continue;

            callback->onReceiveString(it.latin1().data());
        }
    });
}

void SWKCookieManager::startObservingChanges(Native::PassLocalRef<Natives::ValueCallback> callback)
{
    m_changesObserverCallback = std::move(callback);

    m_cookieManager->startObservingCookieChanges();
}

void SWKCookieManager::stopObservingChanges()
{
    m_changesObserverCallback.reset();

    m_cookieManager->stopObservingCookieChanges();
}

namespace Natives {

SWKCookieManager* SWKCookieManager::nativeCreate()
{
	return new ::WebKit::SWKCookieManager;
}

}
}
