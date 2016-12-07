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

#ifndef SWKWebHitTestResult_h
#define SWKWebHitTestResult_h

#include "SWKWebHitTestResultManagedBase.h"

#include <ManagedRect.h>

namespace webkit {

class SWKWebHitTestResult : public WebKit::Managed::SWKWebHitTestResult {
public:
    SWKWebHitTestResult() = default;
    virtual ~SWKWebHitTestResult() = default;

    virtual void INIT(const std::string& absoluteImageURL, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, bool, std::shared_ptr<Native::Managed::Rect>, bool) override;

    virtual const std::string& absoluteImageURL() const { return m_absoluteImageURL; }
    virtual const std::string& absolutePDFURL() const { return m_absolutePDFURL; }
    virtual const std::string& absoluteLinkURL() const { return m_absoluteLinkURL; }
    virtual const std::string& absoluteMediaURL() const { return m_absoluteMediaURL; }
    virtual const std::string& linkLabel() const { return m_linkLabel; }
    virtual const std::string& linkTitle() const { return m_linkTitle; }
    virtual bool isContentEditable() const { return m_isContentEditable; }
    virtual std::shared_ptr<Native::Managed::Rect> elementBoundingBox() const { return m_elementBoundingBox; }
    virtual bool isScrollbar() const { return m_isScrollbar; }

private:
    std::string m_absoluteImageURL;
    std::string m_absolutePDFURL;
    std::string m_absoluteLinkURL;
    std::string m_absoluteMediaURL;
    std::string m_linkLabel;
    std::string m_linkTitle;
    bool m_isContentEditable;
    std::shared_ptr<Native::Managed::Rect> m_elementBoundingBox;
    bool m_isScrollbar;
};

} // namespace webkit

#endif // SWKWebHitTestResult_h
