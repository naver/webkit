/*
 * Copyright (C) 2013 Naver Corp. All rights reserved.
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
#include "WebCoreArgumentCoders.h"

#if USE(CURL)

#include "NotImplemented.h"
#include <WebCore/CertificateInfo.h>
#include <WebCore/ResourceError.h>
#include <WebCore/ResourceRequest.h>
#include <WebCore/ResourceResponse.h>
#include <wtf/text/CString.h>

using namespace WebCore;

namespace IPC {

void ArgumentCoder<ResourceRequest>::encodePlatformData(ArgumentEncoder& encoder, const ResourceRequest& resourceRequest)
{
    encoder << resourceRequest.url().string();
    encoder << resourceRequest.httpMethod();
    encoder << resourceRequest.httpHeaderFields();

    // FIXME: Do not encode HTTP message body.
    // 1. It can be large and thus costly to send across.
    // 2. It is misleading to provide a body with some requests, while others use body streams, which cannot be serialized at all.
    FormData* httpBody = resourceRequest.httpBody();
    encoder << static_cast<bool>(httpBody);
    if (httpBody)
        encoder << httpBody->flattenToString();

    encoder << resourceRequest.firstPartyForCookies().string();
}

bool ArgumentCoder<ResourceRequest>::decodePlatformData(ArgumentDecoder& decoder, ResourceRequest& resourceRequest)
{
    String url;
    if (!decoder.decode(url))
        return false;
    resourceRequest.setURL(URL(URL(), url));

    String httpMethod;
    if (!decoder.decode(httpMethod))
        return false;
    resourceRequest.setHTTPMethod(httpMethod);

    HTTPHeaderMap headers;
    if (!decoder.decode(headers))
        return false;
    resourceRequest.setHTTPHeaderFields(WTFMove(headers));

    bool hasHTTPBody;
    if (!decoder.decode(hasHTTPBody))
        return false;
    if (hasHTTPBody) {
        String httpBody;
        if (!decoder.decode(httpBody))
            return false;
        resourceRequest.setHTTPBody(FormData::create(httpBody.utf8()));
    }

    String firstPartyForCookies;
    if (!decoder.decode(firstPartyForCookies))
        return false;
    resourceRequest.setFirstPartyForCookies(URL(URL(), firstPartyForCookies));

    return true;
}

void ArgumentCoder<CertificateInfo>::encode(ArgumentEncoder& encoder, const CertificateInfo& certificateInfo)
{
    notImplemented();
}

bool ArgumentCoder<CertificateInfo>::decode(ArgumentDecoder& decoder, CertificateInfo& certificateInfo)
{
    notImplemented();
    return true;
}

void ArgumentCoder<ResourceError>::encodePlatformData(ArgumentEncoder& encoder, const ResourceError& resourceError)
{
    bool errorIsNull = resourceError.isNull();
    encoder << errorIsNull;
    if (errorIsNull)
        return;

    encoder << resourceError.domain();
    encoder << resourceError.errorCode();
    encoder << resourceError.failingURL();
    encoder << resourceError.localizedDescription();
    encoder << resourceError.isCancellation();
    encoder << resourceError.isTimeout();

    encoder << CertificateInfo(resourceError);
}

bool ArgumentCoder<ResourceError>::decodePlatformData(ArgumentDecoder& decoder, ResourceError& resourceError)
{
    bool errorIsNull;
    if (!decoder.decode(errorIsNull))
        return false;
    if (errorIsNull) {
        resourceError = ResourceError();
        return true;
    }

    String domain;
    if (!decoder.decode(domain))
        return false;

    int errorCode;
    if (!decoder.decode(errorCode))
        return false;

    WebCore::URL failingURL;
    if (!decoder.decode(failingURL))
        return false;

    String localizedDescription;
    if (!decoder.decode(localizedDescription))
        return false;

    bool isCancellation;
    if (!decoder.decode(isCancellation))
        return false;

    bool isTimeout;
    if (!decoder.decode(isTimeout))
        return false;

    resourceError = ResourceError(domain, errorCode, failingURL, localizedDescription);
    resourceError.setType(ResourceErrorBase::Type::Cancellation);
    resourceError.setType(ResourceErrorBase::Type::Timeout);

    CertificateInfo certificateInfo;
    if (!decoder.decode(certificateInfo))
        return false;

    return true;
}

void ArgumentCoder<ProtectionSpace>::encodePlatformData(ArgumentEncoder&, const WebCore::ProtectionSpace&)
{
    notImplemented();
}

bool ArgumentCoder<ProtectionSpace>::decodePlatformData(ArgumentDecoder&, WebCore::ProtectionSpace&)
{
    notImplemented();
    return true;
}

void ArgumentCoder<Credential>::encodePlatformData(ArgumentEncoder&, const WebCore::Credential&)
{
    notImplemented();
}

bool ArgumentCoder<Credential>::decodePlatformData(ArgumentDecoder&, WebCore::Credential&)
{
    notImplemented();
    return true;
}

}

#endif // USE(CURL)
