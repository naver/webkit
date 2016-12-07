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
#include "WebContextMenuProxySling.h"

#if ENABLE(CONTEXT_MENUS)

#include "APIContextMenuClient.h"
#include "NativeWebCoreGraphics.h"
#include "SWKContextMenuItemNatives.h"
#include "SWKViewNatives.h"
#include "WebPageProxy.h"
#include "WebProcessProxy.h"

namespace WebKit {

WebContextMenuProxySling::WebContextMenuProxySling(SWKView* view, WebPageProxy& page, const ContextMenuContextData& contextMenuContextData, const UserData& userData)
    : WebContextMenuProxy(contextMenuContextData, userData)
    , m_view(view)
    , m_page(page)
{
}

void WebContextMenuProxySling::show()
{
    Ref<WebPageProxy> protect(m_page);

    Vector<RefPtr<WebContextMenuItem>> proposedAPIItems;
    for (auto& item : m_context.menuItems()) {
        if (item.action() != WebCore::ContextMenuItemTagShareMenu)
            proposedAPIItems.append(WebContextMenuItem::create(item));
    }

    Vector<RefPtr<WebContextMenuItem>> clientItems;
    bool useProposedItems = true;
    if (m_page.contextMenuClient().getContextMenuFromProposedMenu(m_page, proposedAPIItems, clientItems, m_context.webHitTestResultData(), m_page.process().transformHandlesToObjects(m_userData.object()).get()))
        useProposedItems = false;

    const Vector<RefPtr<WebContextMenuItem>>& itemsToShow = useProposedItems ? proposedAPIItems : clientItems;
    if (itemsToShow.isEmpty())
        return;

    if (!m_page.contextMenuClient().showContextMenu(m_page, m_context.menuLocation(), itemsToShow)) {
        m_contextMenu = WebContextMenu::create();
        m_contextMenu->setSelectionHandler([&](Native::PassLocalRef<SWKContextMenuItem> item) {
            m_page.contextMenuItemSelected(item->kitItem());
        });

        Native::LocalRef<Native::Natives::Vector> items = Native::Natives::Vector::create();
        for (const auto& menuItem : itemsToShow)
            items->add(SWKContextMenuItem::create(menuItem->data()));

        m_contextMenu->showContextMenu(m_view, toPoint(m_context.menuLocation()), items.release());
    }
}

} // namespace WebKit

#endif // ENABLE(CONTEXT_MENUS)
