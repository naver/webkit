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

#ifndef SWKUserContentController_h
#define SWKUserContentController_h

#include "SWKUserContentControllerNativesBase.h"
#include "SWKScriptMessageHandlerNatives.h"
#include "SWKUserScriptNatives.h"
#include "SWKUserStyleSheetNatives.h"

#include "NativesVector.h"
#include "WebUserContentControllerProxy.h"

namespace WebKit {

class WebUserContentControllerProxy;

class SWKUserContentController final : public Natives::SWKUserContentController {
    friend class Natives::SWKUserContentController;
public:
    ~SWKUserContentController();

    Native::PassLocalRef<Natives::Vector> getUserScripts() override;
    void addUserScript(Native::PassLocalRef<Natives::SWKUserScript>) override;
    void removeAllUserScripts() override;

    void addUserStyleSheet(Native::PassLocalRef<Natives::SWKUserStyleSheet>) override;
    void removeAllUserStyleSheets() override;

    void addScriptMessageHandler(Native::PassLocalRef<Natives::SWKScriptMessageHandler>, const std::string&) override;
    void removeScriptMessageHandlerForName(const std::string&) override;

    void removeAllUserContent() override;

    RefPtr<WebUserContentControllerProxy> webUserContentController() { return m_userContentController; }

private:
    SWKUserContentController();

    RefPtr<WebUserContentControllerProxy> m_userContentController;
};

}

#endif // SWKUserContentController_h
