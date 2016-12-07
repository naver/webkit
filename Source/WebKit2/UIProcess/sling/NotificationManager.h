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

#ifndef NotificationManager_h
#define NotificationManager_h

#include "SWKNotificationNatives.h"
#include "SWKNotificationProviderNatives.h"
#include "WKBase.h"
#include <onig/GlobalRef.h>
#include <wtf/HashMap.h>
#include <wtf/RefCounted.h>
#include <wtf/PassRefPtr.h>

namespace API {
class Array;
}

namespace WebKit {

class WebNotification;
class WebNotificationManagerProxy;
class WebPageProxy;

class NotificationManager : public RefCounted<NotificationManager> {
public:
    static PassRefPtr<NotificationManager> create(WebNotificationManagerProxy*);

    virtual ~NotificationManager() = default;

    void setNotificationProvider(Native::PassLocalRef<Natives::SWKNotificationProvider>);
    void show(WebPageProxy*, WebNotification*);
    void cancel(WebNotification*);
    void clearNotifications(API::Array*);

private:
    static void showCallback(WKPageRef, WKNotificationRef, const void*);
    static void cancelCallback(WKNotificationRef, const void*);
    static void clearNotificationsCallback(WKArrayRef, const void*);

    explicit NotificationManager(WebNotificationManagerProxy*);

    void cancelNotificationById(uint64_t);

    RefPtr<WebNotificationManagerProxy> m_notificationManager;
    HashMap<uint64_t, Native::GlobalRef<SWKNotification>> m_notifications;
    Native::GlobalRef<SWKNotificationProvider> m_notificationProvider;
};

} // namespace WebKit

#endif // NotificationManager_h
