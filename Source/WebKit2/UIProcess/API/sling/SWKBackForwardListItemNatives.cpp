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
#include "SWKBackForwardListItemNatives.h"

#include "SWKURLNatives.h"
#include <wtf/text/CString.h>

namespace WebKit {

Native::PassLocalRef<SWKBackForwardListItem> SWKBackForwardListItem::create(WebBackForwardListItem* item)
{
    Native::LocalRef<SWKBackForwardListItem> instance = Natives::SWKBackForwardListItem::create().as<SWKBackForwardListItem>();
    instance->m_item = item;
    return instance.release();
}

Native::PassLocalRef<Natives::SWKURL> SWKBackForwardListItem::getURL()
{
    return SWKURL::createWithString(m_item->url());
}

std::string SWKBackForwardListItem::getTitle()
{
    return m_item->title().utf8().data();
}

std::string SWKBackForwardListItem::getOriginalURL()
{
    return m_item->originalURL().utf8().data();
}

} // namespace WebKit

namespace WebKit {
namespace Natives {

SWKBackForwardListItem* SWKBackForwardListItem::nativeCreate()
{
    return new ::WebKit::SWKBackForwardListItem();
}

} // namespace Natives
} // namespace WebKit
