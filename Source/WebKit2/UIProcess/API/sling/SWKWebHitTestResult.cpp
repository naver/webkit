/*
 * Copyright (C) 2014 Naver Corp. All rights reserved.
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
#include "SWKWebHitTestResult.h"

namespace webkit {

void SWKWebHitTestResult::INIT(const std::string& absoluteImageURL,
    const std::string& absolutePDFURL,
    const std::string& absoluteLinkURL,
    const std::string& absoluteMediaURL,
    const std::string& linkLabel,
    const std::string& linkTitle,
    bool isContentEditable,
    std::shared_ptr<Native::Managed::Rect> elementBoundingBox,
    bool isScrollbar)
{
    m_absoluteImageURL = absoluteImageURL;
    m_absolutePDFURL = absolutePDFURL;
    m_absoluteLinkURL = absoluteLinkURL;
    m_absoluteMediaURL = absoluteMediaURL;
    m_linkLabel = linkLabel;
    m_linkTitle = linkTitle;
    m_isContentEditable = isContentEditable;
    m_elementBoundingBox = std::static_pointer_cast<Native::Managed::Rect>(elementBoundingBox);
    m_isScrollbar = isScrollbar;
}

} // namespace webkit

namespace WebKit {
namespace Managed {

void SWKWebHitTestResult::INIT(const std::string& absoluteImageURL,
    const std::string& absolutePDFURL,
    const std::string& absoluteLinkURL,
    const std::string& absoluteMediaURL,
    const std::string& linkLabel,
    const std::string& linkTitle,
    bool isContentEditable,
    std::shared_ptr<Native::Managed::Rect> elementBoundingBox,
    bool isScrollbar)
{
}

} // namespace Managed
} // namespace WebKit
