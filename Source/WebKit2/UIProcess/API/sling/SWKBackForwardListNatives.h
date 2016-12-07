/*
 * Copyright (C) 2014 Naver Corp. All rights reserved override.
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

#ifndef SWKBackForwardList_h
#define SWKBackForwardList_h

#include "SWKBackForwardListNativesBase.h"

#include <onig/GlobalRef.h>

namespace WebKit {

class SWKBackForwardListItem;
class WebBackForwardList;

class SWKBackForwardList : public Natives::SWKBackForwardList {
public:
    static Native::PassLocalRef<SWKBackForwardList> create(WebBackForwardList&);
    ~SWKBackForwardList() { }

protected:
    Native::PassLocalRef<Natives::SWKBackForwardListItem> getCurrentItem() override;
    Native::PassLocalRef<Natives::SWKBackForwardListItem> getBackItem() override;
    Native::PassLocalRef<Natives::SWKBackForwardListItem> getForwardItem() override;
    Native::PassLocalRef<Natives::SWKBackForwardListItem> getItemAtIndex(int32_t) override;
    int32_t getBackListCount() override;
    int32_t getForwardListCount() override;
    void clear() override;

private: 
    WebBackForwardList* m_backForwardList;
};

}

#endif // SWKBackForwardList_h

