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

#include "config.h"
#include "SWKIconDatabaseNatives.h"

#include "APIData.h"
#include "DataReference.h"
#include "WebBitmapNativesBase.h"
#include "WKAPICast.h"
#include "WKArray.h"
#include "WKIconDatabase.h"
#include "WKSecurityOriginRef.h"
#include "WKString.h"

#include <onig/GlobalRef.h>

using namespace WebCore;

namespace WebKit {

Native::PassLocalRef<SWKIconDatabase> SWKIconDatabase::create(WebIconDatabase* iconDatabase)
{
    Native::LocalRef<SWKIconDatabase> swkIconDatabase = Natives::SWKIconDatabase::create().as<SWKIconDatabase>();
    swkIconDatabase->m_iconDatabase = iconDatabase;
    return swkIconDatabase.release();
}

SWKIconDatabase::~SWKIconDatabase()
{
    iconDatabase().close();
}

void SWKIconDatabase::retainIconForPageURL(const std::string& pageURL)
{
    iconDatabase().retainIconForPageURL(String(pageURL.data()));
}

void SWKIconDatabase::releaseIconForPageURL(const std::string& pageURL)
{
    iconDatabase().releaseIconForPageURL(String(pageURL.data()));
}

void SWKIconDatabase::setIconURLForPageURL(const std::string& iconURL, const std::string& pageURL)
{
    iconDatabase().setIconURLForPageURL(String(iconURL.data()), String(pageURL.data()));
}

void SWKIconDatabase::setIconDataForIconURL(Native::PassLocalRef<Natives::WebBitmap> iconData, const std::string& iconURL)
{
    // TODO : should pass the iconData to setIconDataForIconURL after implementing the WebBitmap class
    iconDatabase().setIconDataForIconURL(IPC::DataReference(0, 0), String(iconURL.data()));
}

static void didChangeIconForPageURL(WKIconDatabaseRef, WKURLRef url, const void* clientInfo)
{
    SWKIconDatabase* iconDatabase = static_cast<SWKIconDatabase*>(const_cast<void*>(clientInfo));
    iconDatabase->delegate()->didChangeIconForPageURL(iconDatabase, toWTFString(url).utf8().data());
}

static void didRemoveAllIcons(WKIconDatabaseRef, const void* clientInfo)
{
    SWKIconDatabase* iconDatabase = static_cast<SWKIconDatabase*>(const_cast<void*>(clientInfo));
    iconDatabase->delegate()->didRemoveAllIcons(iconDatabase);
}

static void iconDataReadyForPageURL(WKIconDatabaseRef, WKURLRef url, const void* clientInfo)
{
    SWKIconDatabase* iconDatabase = static_cast<SWKIconDatabase*>(const_cast<void*>(clientInfo));
    iconDatabase->delegate()->iconDataReadyForPageURL(iconDatabase, toWTFString(url).utf8().data());
}

void SWKIconDatabase::setIconDatabaseDelegate(Native::PassLocalRef<Natives::SWKIconDatabaseDelegate> delegate)
{
    m_delegate = delegate;

    WKIconDatabaseClientV1 iconDatabaseClient;
    memset(&iconDatabaseClient, 0, sizeof(WKIconDatabaseClientV1));
    iconDatabaseClient.base.version = 1;
    iconDatabaseClient.base.clientInfo = this;
    iconDatabaseClient.didChangeIconForPageURL = didChangeIconForPageURL;
    iconDatabaseClient.didRemoveAllIcons = didRemoveAllIcons;
    iconDatabaseClient.iconDataReadyForPageURL = iconDataReadyForPageURL;

    iconDatabase().initializeIconDatabaseClient(&iconDatabaseClient.base);
}

Native::ImmutableArray<int8_t> SWKIconDatabase::getIconDataForPageURL(const std::string& pageURL)
{
    RefPtr<API::Data> data = iconDatabase().iconDataForPageURL(String(pageURL.data()));
    if (!data || !data.get()->size()) {
        std::vector<int8_t> emptyVector;
        return Native::ImmutableArray<int8_t>(emptyVector);
    }

    Native::ImmutableArray<int8_t> iconData((int8_t*)(data.get()->bytes()), data.get()->size(), true);
    return iconData;
}

void SWKIconDatabase::removeAllIcons()
{
    iconDatabase().removeAllIcons();
}

namespace Natives {

SWKIconDatabase* SWKIconDatabase::nativeCreate()
{
    return new ::WebKit::SWKIconDatabase;
}

}
}
