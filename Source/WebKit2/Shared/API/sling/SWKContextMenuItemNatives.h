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

#ifndef SWKContextMenuItem_h
#define SWKContextMenuItem_h

#include "SWKContextMenuItemNativesBase.h"

#include "WebContextMenuItem.h"
#include <NativesVector.h>
#include <onig/GlobalRef.h>

namespace WebKit {

class SWKContextMenuItem : public Natives::SWKContextMenuItem {
    friend class Natives::SWKContextMenuItem;
public:
    static Native::PassLocalRef<SWKContextMenuItem> create(const WebContextMenuItemData&);

    WebContextMenuItemData kitItem() const;

protected:
    int32_t getType() override { return m_type; }
    int32_t getAction() override { return m_action; }
    std::string getTitle() override { return m_title; }
    bool isEnabled() override { return m_enabled; }
    bool isChecked() override { return m_checked; }
    Native::PassLocalRef<Natives::Vector> getSubmenu() override { return m_submenu; }

private:
    int32_t m_type;
    int32_t m_action;
    std::string m_title;
    bool m_enabled;
    bool m_checked;
    Native::GlobalRef<Natives::Vector> m_submenu;
};

} // namespace WebKit

#endif // SWKContextMenuItem_h
