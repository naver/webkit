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

#ifndef SWKWindowFeatures_h
#define SWKWindowFeatures_h

#include "SWKWindowFeaturesManagedBase.h"

namespace webkit {

namespace Managed = WebKit::Managed;

class WEBKIT_EXPORT SWKWindowFeatures final : public WebKit::Managed::SWKWindowFeatures {
    friend class WebKit::Managed::SWKWindowFeatures;
public:
    virtual int32_t getX() override { return m_x; }
    virtual int32_t getY() override { return m_y; }
    virtual int32_t getWidth() override { return m_width; }
    virtual int32_t getHeight() override { return m_height; }
    virtual bool getAllowsResizing() override { return m_allowResizing; }
    virtual bool getMenuBarVisibility() override { return m_menuBarVisible; }
    virtual bool getStatusBarVisibility() override { return m_statusBarVisible; }
    virtual bool getToolBarsVisibility() override { return m_toolBarsVisible; }

private:
    virtual void INIT(int32_t, int32_t, int32_t, int32_t, bool, bool, bool, bool) override;

    int32_t m_x;
    int32_t m_y;
    int32_t m_width;
    int32_t m_height;
    bool m_allowResizing : 1;
    bool m_menuBarVisible : 1;
    bool m_statusBarVisible : 1;
    bool m_toolBarsVisible : 1;
};

}
#endif