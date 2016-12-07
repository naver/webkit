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
#include "SWKDownloadNatives.h"

#include "DownloadProxy.h"
#include "SWKURLNatives.h"

namespace WebKit {

class SWKDownloadPrivate : public Natives::SWKDownload::Private {
public:
    RefPtr<DownloadProxy> m_downloadProxy;
    Native::WeakGlobalRef<SWKWebContent> m_webContent;
};

static SWKDownloadPrivate* ptr(const std::unique_ptr<Natives::SWKDownload::Private>& p)
{
    return static_cast<SWKDownloadPrivate*>(p.get());
}

Native::PassLocalRef<SWKDownload> SWKDownload::create(Native::PassLocalRef<SWKWebContent> content, DownloadProxy* downloadProxy)
{
    Native::LocalRef<SWKDownload> download = Natives::SWKDownload::create().as<SWKDownload>();
    ptr(download->m_private)->m_downloadProxy = downloadProxy;
    ptr(download->m_private)->m_webContent = content;
    return download;
}

Native::PassLocalRef<Natives::SWKURLRequest> SWKDownload::getRequest()
{
    const auto& downloadRequest = ptr(m_private)->m_downloadProxy->request();
    Native::LocalRef<SWKURLRequest> request = SWKURLRequest::create(
        SWKURL::create(downloadRequest.url()),
        downloadRequest.firstPartyForCookies().string().utf8().data(),
        downloadRequest.httpMethod().utf8().data());

    return request;
}

void SWKDownload::cancel()
{
    ptr(m_private)->m_downloadProxy->cancel();
}

Native::PassLocalRef<Natives::SWKWebContent> SWKDownload::getOriginatingWebContent()
{
    Native::LocalRef<WebKit::SWKWebContent> content = ptr(m_private)->m_webContent.tryPromote();
    if (!content)
        return nullptr;

    return content.release();
}

namespace Natives {

SWKDownload* SWKDownload::nativeCreate()
{
    auto nativeObject = new ::WebKit::SWKDownload();
    nativeObject->m_private.reset(new SWKDownloadPrivate);
    return nativeObject;
}

} // namespace Natives
} // namespace WebKit
