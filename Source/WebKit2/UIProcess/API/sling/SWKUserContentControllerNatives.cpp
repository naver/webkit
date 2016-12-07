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

#include "config.h"
#include "SWKUserContentControllerNatives.h"

#include <WebCore/NotImplemented.h>

namespace WebKit {

SWKUserContentController::SWKUserContentController()
    : m_userContentController(WebUserContentControllerProxy::create())
{
}

SWKUserContentController::~SWKUserContentController()
{
}

Native::PassLocalRef<Natives::Vector> SWKUserContentController::getUserScripts()
{
    notImplemented();
    return nullptr;
}

void SWKUserContentController::addUserScript(Native::PassLocalRef<Natives::SWKUserScript>)
{
    notImplemented();
}

void SWKUserContentController::removeAllUserScripts()
{
    m_userContentController->removeAllUserScripts();
}

void SWKUserContentController::addUserStyleSheet(Native::PassLocalRef<Natives::SWKUserStyleSheet> userStyleSheet)
{
    notImplemented();
}

void SWKUserContentController::removeAllUserStyleSheets()
{
    m_userContentController->removeAllUserStyleSheets();
}

void SWKUserContentController::addScriptMessageHandler(Native::PassLocalRef<Natives::SWKScriptMessageHandler>, const std::string&)
{
    notImplemented();
}

void SWKUserContentController::removeScriptMessageHandlerForName(const std::string&)
{
    notImplemented();
}

void SWKUserContentController::removeAllUserContent()
{
    removeAllUserStyleSheets();
    removeAllUserScripts();
}

namespace Natives {

SWKUserContentController* SWKUserContentController::nativeCreate()
{
    return new ::WebKit::SWKUserContentController();
}

} // namespace Natives
} // namespace WebKit
