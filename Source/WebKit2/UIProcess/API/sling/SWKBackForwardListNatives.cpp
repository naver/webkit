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
#include "SWKBackForwardListNatives.h"

#include "SWKBackForwardListItemNatives.h"
#include "WebBackForwardList.h"

namespace WebKit {

Native::PassLocalRef<SWKBackForwardList> SWKBackForwardList::create(WebBackForwardList& backForwardList)
{
    Native::LocalRef<SWKBackForwardList> list = Natives::SWKBackForwardList::create().as<SWKBackForwardList>();
    list->m_backForwardList = &backForwardList;    
    return list;
}

Native::PassLocalRef<Natives::SWKBackForwardListItem> SWKBackForwardList::getBackItem()
{
    if (!m_backForwardList->backItem())
        return nullptr;

    return SWKBackForwardListItem::create(m_backForwardList->backItem()).as<Natives::SWKBackForwardListItem>();
}

Native::PassLocalRef<Natives::SWKBackForwardListItem> SWKBackForwardList::getCurrentItem()
{
    return SWKBackForwardListItem::create(m_backForwardList->currentItem()).as<Natives::SWKBackForwardListItem>();
}

Native::PassLocalRef<Natives::SWKBackForwardListItem> SWKBackForwardList::getForwardItem()
{
    if (!m_backForwardList->forwardItem())
        return nullptr;

    return SWKBackForwardListItem::create(m_backForwardList->forwardItem()).as<Natives::SWKBackForwardListItem>();
}

Native::PassLocalRef<Natives::SWKBackForwardListItem> SWKBackForwardList::getItemAtIndex(int32_t index)
{
    return SWKBackForwardListItem::create(m_backForwardList->itemAtIndex(index)).as<Natives::SWKBackForwardListItem>();
}

int32_t SWKBackForwardList::getBackListCount()
{
    return m_backForwardList->backListCount();
}

int32_t SWKBackForwardList::getForwardListCount()
{
    return m_backForwardList->forwardListCount();
}

void SWKBackForwardList::clear()
{
    m_backForwardList->clear();
}

} // namespace WebKit

namespace WebKit {
namespace Natives {

SWKBackForwardList* SWKBackForwardList::nativeCreate()
{
    return new ::WebKit::SWKBackForwardList();
}

} // namespace Natives
} // namespace WebKit

