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
#include "SWKWebContent.h"

#include "SWKBackForwardList.h"
#include "SWKProcessPool.h"
#include "SWKView.h"
#include "SWKURL.h"
#include "SWKURLRequest.h"
#include "SWKWebContentConfiguration.h"
#include "WebPrintInfo.h"

namespace webkit {

void SWKWebContent::INIT()
{
    INIT(nullptr, nullptr);
}

void SWKWebContent::INIT(std::shared_ptr<Managed::Rect> frame, std::shared_ptr<Managed::SWKWebContentConfiguration> configuration)
{
    nativeCreate(frame, configuration);
}

std::shared_ptr<SWKBackForwardList> SWKWebContent::getBackForwardList()
{
    return std::static_pointer_cast<SWKBackForwardList>(Managed::SWKWebContent::getBackForwardList());
}

std::shared_ptr<SWKNavigation> SWKWebContent::loadRequest(std::shared_ptr<SWKURLRequest> request)
{
    return std::static_pointer_cast<SWKNavigation>(Managed::SWKWebContent::loadRequest(request));
}

std::shared_ptr<SWKNavigation> SWKWebContent::loadFileURL(const std::string& Url, const std::string& readAccessUrl)
{
    return nullptr;
}

std::shared_ptr<SWKNavigation> SWKWebContent::loadHTMLString(const std::string& htmlString, const std::string& baseURL)
{
    return std::static_pointer_cast<SWKNavigation>(Managed::SWKWebContent::loadHTMLString(htmlString, baseURL));
}

std::shared_ptr<SWKNavigation> SWKWebContent::loadData(const std::string& data, const std::string& MimeType, const std::string& characterEncodingName,
    const std::string& baseUrl)
{
    return std::static_pointer_cast<SWKNavigation>(Managed::SWKWebContent::loadData(data, MimeType, characterEncodingName, baseUrl));
}

std::string SWKWebContent::getTitle()
{
    return Managed::SWKWebContent::getTitle();
}

std::shared_ptr<SWKURL> SWKWebContent::getURL()
{
    return std::static_pointer_cast<SWKURL>(Managed::SWKWebContent::getURL());
}

bool SWKWebContent::isLoading()
{
    return false;
}

double SWKWebContent::getEstimatedProgress()
{
    return 0;
}

bool SWKWebContent::hasOnlySecureContent()
{
    return false;
}

bool SWKWebContent::canGoBack()
{
    return Managed::SWKWebContent::canGoBack();
}

bool SWKWebContent::canGoForward()
{
    return Managed::SWKWebContent::canGoForward();
}

std::shared_ptr<SWKNavigation> SWKWebContent::goBack()
{
    return std::static_pointer_cast<SWKNavigation>(Managed::SWKWebContent::goBack());
}

std::shared_ptr<SWKNavigation> SWKWebContent::goForward()
{
    return std::static_pointer_cast<SWKNavigation>(Managed::SWKWebContent::goForward());
}

std::shared_ptr<SWKNavigation> SWKWebContent::reload()
{
    return std::static_pointer_cast<SWKNavigation>(Managed::SWKWebContent::reload());
}

std::shared_ptr<SWKNavigation> SWKWebContent::reloadFromOrigin()
{
    return std::static_pointer_cast<SWKNavigation>(Managed::SWKWebContent::reloadFromOrigin());
}

void SWKWebContent::stopLoading()
{
    Managed::SWKWebContent::stopLoading();
}

std::string SWKWebContent::getCustomUserAgent()
{
    return Managed::SWKWebContent::getCustomUserAgent();
}

void SWKWebContent::setCustomUserAgent(const std::string& customUserAgent)
{
    return Managed::SWKWebContent::setCustomUserAgent(customUserAgent);
}


std::shared_ptr<SWKView> SWKWebContent::createView()
{
    return std::static_pointer_cast<SWKView>(Managed::SWKWebContent::createView());
}

std::shared_ptr<SWKView> SWKWebContent::peekView()
{
    return std::static_pointer_cast<SWKView>(Managed::SWKWebContent::peekView());
}

int32_t SWKWebContent::getContentWidth()
{
    return Managed::SWKWebContent::getContentWidth();
}

int32_t SWKWebContent::getContentHeight()
{
    return Managed::SWKWebContent::getContentHeight();
}

void SWKWebContent::loadAlternateHTMLString(const std::string& string, std::shared_ptr<SWKURL> baseURL, std::shared_ptr<SWKURL> unreachableURL)
{
}

void SWKWebContent::snapshotRect(std::shared_ptr<Native::Managed::Rect> rectInViewCoordinates, float imageWidth,
    std::shared_ptr<ValueCallback<WebBitmap>> completionHandler)
{
    Managed::SWKWebContent::snapshotRect(rectInViewCoordinates, imageWidth, completionHandler);
}

void SWKWebContent::killWebContentProcess()
{
}

void SWKWebContent::getMainResourceDataWithCompletionHandle(
    std::shared_ptr<ValueCallback<std::pair<std::shared_ptr<SWKData>, std::shared_ptr<SWKError>>>> completionHandler)
{
}

void SWKWebContent::getWebArchiveDataWithCompletionHandle(
    std::shared_ptr<ValueCallback<std::pair<std::shared_ptr<SWKData>, std::shared_ptr<SWKError>>>> completionHandler)
{
}

void SWKWebContent::findString(const std::string& string, int32_t options, int32_t maxCount)
{
    Managed::SWKWebContent::findString(string, options, maxCount);
}

void SWKWebContent::countStringMatches(const std::string& string, int32_t options, int32_t maxCount)
{
    Managed::SWKWebContent::countStringMatches(string, options, maxCount);
}

void SWKWebContent::selectFindMatch(int32_t matchIndex)
{
    Managed::SWKWebContent::selectFindMatch(matchIndex);
}

void SWKWebContent::hideFindUI()
{
    Managed::SWKWebContent::hideFindUI();
}

std::shared_ptr<SWKURL> SWKWebContent::getUnreachableURL()
{
    return std::static_pointer_cast<SWKURL>(Managed::SWKWebContent::getUnreachableURL());
}

std::shared_ptr<Vector> getCertificateChain()
{
    return nullptr;
}

std::string SWKWebContent::getCommittedURL()
{
    return nullptr;
}

std::string SWKWebContent::getMIMEType()
{
    return nullptr;
}

std::string SWKWebContent::getUserAgent()
{
    return Managed::SWKWebContent::getUserAgent();
}

int32_t SWKWebContent::getWebProcessIdentifier()
{
    return 0;
}

bool SWKWebContent::isNetworkRequestsInProgress()
{
    return false;
}

bool SWKWebContent::isSupportingTextZoom()
{
    return false;
}

void SWKWebContent::setObservedRenderingProgressEvent(int32_t observedRenderingProgressEvents)
{
}

int32_t SWKWebContent::getObservedRenderingProgressEvents()
{
    return 0;
}

bool SWKWebContent::isEditable()
{
    return false;
}

void SWKWebContent::setEditable(bool editable)
{
}

void SWKWebContent::setAllowsRemoteInspection(bool allowsRemoteInspection)
{
}

bool SWKWebContent::getAllowsRemoteInspection()
{
    return false;
}

void SWKWebContent::setAddsVisitedLinks(bool addsVisitedLinks)
{
}

bool SWKWebContent::getAddsVisitedLinks()
{
    return false;
}


} // namespace webkit

namespace WebKit {
namespace Managed {

void SWKWebContent::INIT(std::shared_ptr<Managed::Rect> frame, std::shared_ptr<Managed::SWKWebContentConfiguration> configuration)
{
}

} // namespace Managed
} // namespace WebKit
