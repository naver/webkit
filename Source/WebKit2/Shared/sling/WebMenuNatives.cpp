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
#include "WebMenuNatives.h"

namespace WebKit {

class WebMenuPrivate : public Natives::WebMenu::Private {
public :
    std::function<void (int32_t)> m_valueChangedCallback;
    std::function<void (int32_t)> m_valueFocusedCallback;
};

static WebMenuPrivate* ptr(const std::unique_ptr<Natives::WebMenu::Private>& p)
{
    return static_cast<WebMenuPrivate*>(p.get());
}

Native::PassLocalRef<WebMenu> WebMenu::create(std::function<void (int32_t)> valueChangedCallback, std::function<void (int32_t)> valueFocusedCallback)
{
    Native::LocalRef<WebMenu> popupMenu = Natives::WebMenu::create().as<WebMenu>();
    ptr(popupMenu->m_private)->m_valueChangedCallback = std::move(valueChangedCallback);
    ptr(popupMenu->m_private)->m_valueFocusedCallback = std::move(valueFocusedCallback);
    return popupMenu.release();
}

void WebMenu::valueChangedForPopupMenu(int32_t index)
{
    ptr(m_private)->m_valueChangedCallback(index);
}

void WebMenu::valueFocusedForPopupMenu(int32_t index)
{
    ptr(m_private)->m_valueFocusedCallback(index);
}

namespace Natives {

WebMenu* WebMenu::nativeCreate()
{
    auto nativeObject = new ::WebKit::WebMenu();
    nativeObject->m_private.reset(new WebMenuPrivate);
    return nativeObject;
}

}
}
