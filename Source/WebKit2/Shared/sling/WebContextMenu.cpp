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
#include "WebContextMenu.h"

#include <ManagedVector.h>
#include <view/ContentView.h>
#include <view/GeometryConversion.h>
#include <view/Menu.h>

namespace webkit {

void WebContextMenu::setSelectionHandler(std::function<void (const std::shared_ptr<SWKContextMenuItem>&)> handler)
{
    m_selectionHandler = handler;
}

void WebContextMenu::populate(view::Menu& menu, const std::shared_ptr<SWKContextMenuItem>& item)
{
    switch (item->getType()) {
    case SWKContextMenuItem::ACTION_TYPE:
    case SWKContextMenuItem::CHECKABLE_ACTION_TYPE:
        menu.addItem(toViewMenuItem(item));
        m_itemMap[item->getAction()] = item;
        break;
    case SWKContextMenuItem::SEPARATOR_TYPE:
        menu.addSeparator();
        break;
    case SWKContextMenuItem::SUBMENU_TYPE:
        populate(*menu.addSubmenu(toViewMenuItem(item)), item->getSubmenu());
        break;
    }
}

void WebContextMenu::populate(view::Menu& menu, const std::shared_ptr<WebKit::Managed::Vector>& items)
{
    auto& menuItems = ::Managed::vectorData(*items);
    for (auto& menuItem : menuItems)
        populate(menu, std::static_pointer_cast<SWKContextMenuItem>(menuItem));
}

std::shared_ptr<view::MenuItem> WebContextMenu::toViewMenuItem(const std::shared_ptr<SWKContextMenuItem>& item)
{
    return std::make_shared<view::MenuItem>(item->getTitle(), item->isEnabled(), item->isChecked(), item->getAction());
}

void WebContextMenu::showContextMenu(std::shared_ptr<WebKit::Managed::SWKView> view, std::shared_ptr<WebKit::Managed::Point> location, std::shared_ptr<WebKit::Managed::Vector> items)
{
    auto anchor = std::static_pointer_cast<SWKView>(view);
    if (!anchor->getContentView() || items->isEmpty())
        return;

    m_contextMenu = view::Menu::create(*anchor->getContentView());
    m_contextMenu->setOnMenuItemClickListener([&](int32_t action) {
        const std::shared_ptr<SWKContextMenuItem>& item = m_itemMap.at(action);
        if (m_selectionHandler)
            m_selectionHandler(item);
        else
            contextMenuItemSelected(item);
    });

    populate(*m_contextMenu, items);
    m_contextMenu->show(view::geometry_cast<view::Point>(*location));
}

void WebContextMenu::hideContextMenu()
{
    if (m_contextMenu)
        m_contextMenu->dismiss();

    m_itemMap.clear();
}

} // namespace webkit

namespace WebKit {
namespace Managed {

void WebContextMenu::INIT()
{
    nativeCreate();
}

} // namespace Managed
} // namespace WebKit
