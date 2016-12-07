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
#include "SWKContextMenuItemNatives.h"

#include <wtf/text/CString.h>

namespace WebKit {

static Native::PassLocalRef<Native::Natives::Vector> createSubmenu(const Vector<WebContextMenuItemData>& dataVector)
{
    Native::LocalRef<Native::Natives::Vector> items = Native::Natives::Vector::create();
    for (const auto& data : dataVector)
        items->add(SWKContextMenuItem::create(data));
    return items;
}

Native::PassLocalRef<SWKContextMenuItem> SWKContextMenuItem::create(const WebContextMenuItemData& data)
{
    Native::LocalRef<SWKContextMenuItem> item = Natives::SWKContextMenuItem::create().as<SWKContextMenuItem>();
    item->m_type = data.type();
    item->m_action = data.action();
    item->m_title = data.title().utf8().data();
    item->m_enabled = data.enabled();
    item->m_checked = data.checked();
    item->m_submenu = createSubmenu(data.submenu());

    return item;
}

WebContextMenuItemData SWKContextMenuItem::kitItem() const
{
    return WebContextMenuItemData(static_cast<WebCore::ContextMenuItemType>(m_type),
        static_cast<WebCore::ContextMenuAction>(m_action), String(m_title.c_str()), m_enabled, m_checked);
}

namespace Natives {

SWKContextMenuItem* SWKContextMenuItem::nativeCreate()
{
	return new ::WebKit::SWKContextMenuItem();
}

SWKContextMenuItem* SWKContextMenuItem::nativeCreateWithArgs(int32_t type, int32_t action, std::string title, bool enabled, bool checked)
{
    auto item = new ::WebKit::SWKContextMenuItem();
    item->m_type = type;
    item->m_action = action;
    item->m_title = std::move(title);
    item->m_enabled = enabled;
    item->m_checked = checked;
    item->m_submenu = Native::Natives::Vector::create();

    return item;
}

} // namespace Natives
} // namespace WebKit
