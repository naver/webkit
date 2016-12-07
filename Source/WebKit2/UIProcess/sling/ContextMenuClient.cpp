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
#include "ContextMenuClient.h"

#include "NativeWebCoreGraphics.h"
#include "SWKWebContentNatives.h"
#include "WebContextMenuItem.h"

#include <NativesVector.h>

using namespace WebCore;

namespace WebKit {

ContextMenuClient::ContextMenuClient(SWKWebContent& webContent, Native::PassLocalRef<Natives::SWKContextMenuDelegate> delegate)
    : m_webContent(webContent)
    , m_delegate(delegate)
{
    ASSERT(m_delegate);
}

void ContextMenuClient::customContextMenuItemSelected(WebPageProxy&, const WebContextMenuItemData& data)
{
    m_delegate->customContextMenuItemSelected(SWKContextMenuItem::create(data));
}

bool ContextMenuClient::showContextMenu(WebPageProxy&, const IntPoint& menuLocation, const Vector<RefPtr<WebContextMenuItem>>& menuItems)
{
    if (!m_delegate->hideContextMenu())
        return false;

    Native::LocalRef<Natives::Vector> menuItemsVector = Natives::Vector::create();
    for (auto& menuItem : menuItems)
        menuItemsVector->add(SWKContextMenuItem::create(menuItem->data()));

    IntPoint userMenuLocation = m_webContent.pageClient().contentsToUserViewport(menuLocation);
    Native::LocalRef<Natives::Point> menuLocationPoint = Natives::Point::create(userMenuLocation.x(), userMenuLocation.y());
    return m_delegate->showContextMenu(menuLocationPoint, menuItemsVector);
}

bool ContextMenuClient::hideContextMenu(WebPageProxy&)
{
    return m_delegate->hideContextMenu();
}

} // namespace WebKit
