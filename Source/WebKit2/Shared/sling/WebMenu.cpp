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
#include "WebMenu.h"

#include "WebMenuItem.h"
#include <ManagedRect.h>
#include <ManagedVector.h>
#include <view/ContentView.h>
#include <view/GeometryConversion.h>

namespace webkit {

void WebMenu::showPopupMenu(std::shared_ptr<Managed::SWKView> view, std::shared_ptr<Managed::Rect> rect, int32_t direction,
    double pageScaleFactor, std::shared_ptr<Managed::Vector> items, int32_t selectedIndex)
{
    std::shared_ptr<SWKView> anchor = std::static_pointer_cast<SWKView>(view);
    if (!anchor->getContentView())
        return;

    m_popupMenu = view::PopupMenu::create(*anchor->getContentView());

    m_popupMenu->setOnMenuItemClickListener([=] (int32_t index) {
        valueChangedForPopupMenu(index);
    });
    m_popupMenu->setOnDismissListener([=] (view::PopupMenu&) {
        valueChangedForPopupMenu(selectedIndex);
    });
    m_popupMenu->setOnMenuItemFocusListener([=] (int32_t index) {
        valueFocusedForPopupMenu(index);
    });

    auto& menuItems = ::Managed::vectorData(*items);

    for (auto& menuItem : menuItems) {
        std::shared_ptr<WebMenuItem> item = std::static_pointer_cast<WebMenuItem>(menuItem);
        switch (item->getType()) {
        case WebMenuItem::ITEM_TYPE_SEPARATOR:
            break;
        case WebMenuItem::ITEM_TYPE_ITEM:
            m_popupMenu->add(item->getText());
            break;
        }
    }

    // FIXME: pageScaleFactor is not applied yet. Need to check it.
    view::Rect popupRect = view::geometry_cast<view::Rect>(*rect);
    m_popupMenu->setSelected(selectedIndex);
    m_popupMenu->show(popupRect);
}

void WebMenu::hidePopupMenu(std::shared_ptr<Managed::SWKView> view)
{
    m_popupMenu->dismiss();
}

}

namespace WebKit {
namespace Managed {

void WebMenu::INIT()
{
    nativeCreate();
}

}
}
