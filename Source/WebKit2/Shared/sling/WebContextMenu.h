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

#ifndef WebContextMenu_h
#define WebContextMenu_h

#include "WebContextMenuManagedBase.h"
#include "SWKContextMenuItem.h"
#include "SWKView.h"
#include <map>
#include <view/Menu.h>
#include <view/MenuItem.h>

namespace webkit {

class WEBKIT_EXPORT WebContextMenu final : public WebKit::Managed::WebContextMenu {
    friend class WebKit::Managed::WebContextMenu;
public:
    ~WebContextMenu() = default;

    void setSelectionHandler(std::function<void (const std::shared_ptr<SWKContextMenuItem>&)>);
    void showContextMenu(std::shared_ptr<WebKit::Managed::SWKView>, std::shared_ptr<WebKit::Managed::Point>, std::shared_ptr<WebKit::Managed::Vector>) override;
    void hideContextMenu() override;

private:
    WebContextMenu() = default;

    void populate(view::Menu&, const std::shared_ptr<SWKContextMenuItem>&);
    void populate(view::Menu&, const std::shared_ptr<WebKit::Managed::Vector>&);
    std::shared_ptr<view::MenuItem> toViewMenuItem(const std::shared_ptr<SWKContextMenuItem>&);

    std::unique_ptr<view::Menu> m_contextMenu;
    std::map<int32_t, std::shared_ptr<SWKContextMenuItem>> m_itemMap;
    std::function<void (const std::shared_ptr<SWKContextMenuItem>&)> m_selectionHandler;
};

} // namespace webkit

#endif // WebContextMenu_h
