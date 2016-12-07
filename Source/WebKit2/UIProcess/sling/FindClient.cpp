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
#include "FindClient.h"

#include "SWKWebContentNatives.h"
#include "WKPage.h"
#include "WKSharedAPICast.h"
#include "WKString.h"

namespace WebKit {

FindClient::FindClient(SWKWebContent& webContent, Native::PassLocalRef<Natives::SWKFindDelegate> delegate)
    : m_webContent(webContent)
    , m_delegate(delegate)
{
    ASSERT(m_delegate);
}

void FindClient::didCountStringMatches(WebPageProxy*, const String& string, uint32_t matchCount)
{
    m_delegate->didCountMatches(&m_webContent, matchCount, string.utf8().data());
}

void FindClient::didFindString(WebPageProxy*, const String& string, const Vector<WebCore::IntRect>&, uint32_t matchCount, int32_t matchIndex)
{
    m_delegate->didFindMatches(&m_webContent, matchCount, string.utf8().data(), matchIndex);
}

void FindClient::didFailToFindString(WebPageProxy*, const String& string)
{
    m_delegate->didFailToFindString(&m_webContent, string.utf8().data());
}

} // namespace WebKit
