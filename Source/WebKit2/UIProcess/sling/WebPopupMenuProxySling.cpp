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
#include "WebPopupMenuProxySling.h"

#include "NativeWebCoreGraphics.h"
#include "WebMenuNatives.h"
#include "WebMenuItemNatives.h"
#include "SWKViewNatives.h"
#include "WebPopupItem.h"

#include <NativesVector.h>

using namespace WebCore;

namespace WebKit {

static int32_t toItemType(WebPopupItem::Type type)
{
    switch (type) {
    case WebPopupItem::Type::Separator:
        return Natives::WebMenuItem::ITEM_TYPE_SEPARATOR;
    case WebPopupItem::Type::Item:
        return Natives::WebMenuItem::ITEM_TYPE_ITEM;
    default:
        ASSERT_NOT_REACHED();
        break;
    }
    return Natives::WebMenuItem::ITEM_TYPE_ITEM;
}

static int32_t toItemTextDirection(TextDirection direction)
{
    switch (direction) {
    case TextDirection::RTL:
        return Natives::WebMenuItem::ITEM_TEXT_DIRECTION_RTL;
    case TextDirection::LTR:
        return Natives::WebMenuItem::ITEM_TEXT_DIRECTION_LTR;
    default:
        ASSERT_NOT_REACHED();
        break;
    }
    return Natives::WebMenuItem::ITEM_TEXT_DIRECTION_LTR;
}

WebPopupMenuProxySling::WebPopupMenuProxySling(SWKView* view, WebPopupMenuProxy::Client& client)
    : WebPopupMenuProxy(client)
    , m_view(view)
{
}

WebPopupMenuProxySling::~WebPopupMenuProxySling()
{
}

void WebPopupMenuProxySling::showPopupMenu(const WebCore::IntRect& rect, WebCore::TextDirection direction, double pageScaleFactor, const Vector<WebPopupItem>& items, const PlatformPopupMenuData& data, int32_t selectedIndex)
{
    Native::LocalRef<Natives::Vector> menuItems = Native::Natives::Vector::create();
    for (const WebPopupItem& item : items) {
        Native::LocalRef<WebMenuItem> menuItem = Natives::WebMenuItem::create(toItemType(item.m_type), item.m_text.utf8().data(),
            toItemTextDirection(item.m_textDirection), item.m_hasTextDirectionOverride, item.m_toolTip.utf8().data(), item.m_accessibilityText.utf8().data(),
            item.m_isEnabled, item.m_isLabel, item.m_isSelected);
        menuItems->add(menuItem);
    }

    if (m_popupMenu)
        m_popupMenu.reset();

    m_popupMenu = WebMenu::create(
        [=] (int newSelectedIndex) {
            m_client->valueChangedForPopupMenu(this, newSelectedIndex);
        },
        [=] (int newSelectedIndex) {
            m_client->setTextFromItemForPopupMenu(this, newSelectedIndex);
        });

    RefPtr<WebPopupMenuProxySling> protect(this);
    m_popupMenu->showPopupMenu(m_view, toRect(IntRect(m_view->mapToViewport(rect))), toItemTextDirection(direction), pageScaleFactor, menuItems, selectedIndex);
}

void WebPopupMenuProxySling::hidePopupMenu()
{
    m_popupMenu->hidePopupMenu(m_view);
}

}
