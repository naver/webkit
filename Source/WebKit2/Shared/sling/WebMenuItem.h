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

#ifndef WebMenuItem_h
#define WebMenuItem_h

#include "WebMenuItemManagedBase.h"

namespace webkit {

class WebMenuItem : public WebKit::Managed::WebMenuItem {
public:
    void INIT(int32_t type, const std::string& text, int32_t direction, bool hasTextDirectionOverride, const std::string& toolTip,
        const std::string& accessibilityText, bool isEnabled, bool isLabel, bool isSelected) override;

    int32_t getType() const
    {
        return m_type;
    }

    const std::string& getText() const
    {
        return m_text;
    }

private:
    int32_t m_type;
    std::string m_text;
    int32_t m_direction;
    bool m_hasTextDirectionOverride;
    std::string m_toop_tip;
    std::string m_accessibilityText;
    bool m_isEnabled;
    bool m_isLabel;
    bool m_isSelected;
};

}

#endif
