/*
 * Copyright (C) 2014-2015 Naver Corp. All rights reserved.
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

#ifndef ContextMenuClient_h
#define ContextMenuClient_h

#include "APIContextMenuClient.h"
#include "SWKContextMenuDelegateNatives.h"
#include <WebKit/WKArray.h>
#include <WebKit/WKPage.h>
#include <onig/GlobalRef.h>

namespace WebKit {

class SWKWebContent;

class ContextMenuClient final : public API::ContextMenuClient {
public:
    ContextMenuClient(SWKWebContent&, Native::PassLocalRef<Natives::SWKContextMenuDelegate>);
    ~ContextMenuClient() = default;

    Native::PassLocalRef<Natives::SWKContextMenuDelegate> delegate() const { return m_delegate; }

private:
    void customContextMenuItemSelected(WebPageProxy&, const WebContextMenuItemData&) override;
    bool showContextMenu(WebPageProxy&, const WebCore::IntPoint&, const Vector<RefPtr<WebContextMenuItem>>&) override;
    bool hideContextMenu(WebPageProxy&) override;

    SWKWebContent& m_webContent;
    Native::GlobalRef<SWKContextMenuDelegate> m_delegate;
};

} // namespace WebKit

#endif // ContextMenuClient_h
