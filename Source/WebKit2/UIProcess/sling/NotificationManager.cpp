/*
 * Copyright (C) 2015 Naver Corp. All rights reserved.
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
#include "NotificationManager.h"

#include "APIArray.h"
#include "SWKNotificationNatives.h"
#include "WKAPICast.h"
#include "WKNotificationManager.h"
#include "WebNotification.h"
#include "WebNotificationManagerProxy.h"
#include "WebPageProxy.h"

namespace WebKit {

static inline NotificationManager* toNotificationManager(const void* clientInfo)
{
    return static_cast<NotificationManager*>(const_cast<void*>(clientInfo));
}

PassRefPtr<NotificationManager> NotificationManager::create(WebNotificationManagerProxy* manager)
{
    return adoptRef(new NotificationManager(manager));
}

void NotificationManager::setNotificationProvider(Native::PassLocalRef<Natives::SWKNotificationProvider> delegate)
{
    m_notificationProvider = delegate;
}

void NotificationManager::show(WebPageProxy*, WebNotification* webNotification)
{
    if (!m_notificationProvider)
        return;

    const uint64_t notificationID = webNotification->notificationID();
    Native::LocalRef<SWKNotification> notification = m_notifications.get(notificationID);
    if (!notification) {
        notification = SWKNotification::create(*webNotification);
        m_notifications.set(notificationID, notification);
    }

    if (m_notificationProvider->show(notification))
        m_notificationManager->providerDidShowNotification(notificationID);
}

void NotificationManager::cancel(WebNotification* notification)
{
    cancelNotificationById(notification->notificationID());
}

void NotificationManager::clearNotifications(API::Array* ids)
{
    for (const auto& id : ids->elementsOfType<API::UInt64>())
        cancelNotificationById(id->value());
}

void NotificationManager::cancelNotificationById(uint64_t id)
{
    Native::LocalRef<SWKNotification> notification = m_notifications.get(id);
    if (notification) {
        Vector<RefPtr<API::Object>> ids;
        ids.append(API::UInt64::create(id));
        m_notificationManager->providerDidCloseNotifications(API::Array::create(WTFMove(ids)).ptr());
        m_notifications.remove(id);
    }
}

void NotificationManager::showCallback(WKPageRef page, WKNotificationRef notification, const void* clientInfo)
{
    toNotificationManager(clientInfo)->show(toImpl(page), toImpl(notification));
}

void NotificationManager::cancelCallback(WKNotificationRef notification, const void* clientInfo)
{
    toNotificationManager(clientInfo)->cancel(toImpl(notification));
}

void NotificationManager::clearNotificationsCallback(WKArrayRef notificationIDs, const void* clientInfo)
{
    toNotificationManager(clientInfo)->clearNotifications(toImpl(notificationIDs));
}

NotificationManager::NotificationManager(WebNotificationManagerProxy* manager)
    : m_notificationManager(manager)
{
    WKNotificationProviderV0 provider = {
        { 0, this },
        showCallback,
        cancelCallback,
        0,    // didDestroyNotificationCallback,
        0,    // addNotificationManagerCallback,
        0,    // removeNotificationManagerCallback,
        0,    // notificationPermissionsCallback,
        clearNotificationsCallback,
    };
    WKNotificationManagerSetProvider(toAPI(manager), reinterpret_cast<WKNotificationProviderBase*>(&provider));
}

} // namespace WebKit
