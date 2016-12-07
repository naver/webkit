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
#include "WebKitTestRunnerSupportNatives.h"

#include "SWKWebContentNatives.h"

namespace WebKit {
namespace Natives {

Native::PassLocalRef<Natives::SWKWebContentConfiguration> WebKitTestRunnerSupport::createConfiguration(int64_t pageConfigurationRef)
{
    WKPageConfigurationRef pageConfiguration = reinterpret_cast<WKPageConfigurationRef>(pageConfigurationRef);
    return ::WebKit::SWKWebContentConfiguration::create(pageConfiguration);
}

int64_t WebKitTestRunnerSupport::getWKPageRefFromWebContent(Native::PassLocalRef<Natives::SWKWebContent> webContent)
{
    Native::LocalRef<::WebKit::SWKWebContent> content = webContent.as<::WebKit::SWKWebContent>();
    WKPageRef pageRef = toAPI(&content->webPage());
    return reinterpret_cast<int64_t>(pageRef);
}

WebKitTestRunnerSupport* WebKitTestRunnerSupport::CTOR()
{
    return new ::WebKit::WebKitTestRunnerSupport();
}

}
}
