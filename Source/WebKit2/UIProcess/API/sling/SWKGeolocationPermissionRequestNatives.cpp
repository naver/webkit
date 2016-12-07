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
#include "SWKGeolocationPermissionRequestNatives.h"

#include "GeolocationPermissionRequestProxy.h"

namespace WebKit {

Native::PassLocalRef<SWKGeolocationPermissionRequest> SWKGeolocationPermissionRequest::create(
    GeolocationPermissionRequestProxy* request)
{
    Native::LocalRef<SWKGeolocationPermissionRequest> newRequest
        = Natives::SWKGeolocationPermissionRequest::create().as<SWKGeolocationPermissionRequest>();
    newRequest->m_request = request;
    return newRequest;
}

void SWKGeolocationPermissionRequest::allow()
{
    m_request->allow();
}

void SWKGeolocationPermissionRequest::deny()
{
    m_request->deny();
}

void SWKGeolocationPermissionRequest::invalidate()
{
    m_request->invalidate();
}

namespace Natives {

SWKGeolocationPermissionRequest* SWKGeolocationPermissionRequest::nativeCreate()
{
    return new ::WebKit::SWKGeolocationPermissionRequest();
}

} // namespace Natives
} // namespace WebKit
