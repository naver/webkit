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

#ifndef SWKWebContent_h
#define SWKWebContent_h

#include "SWKBackForwardList.h"
#include "SWKNavigation.h"
#include "SWKNotificationProvider.h"
#include "SWKWebContentManagedBase.h"
#include "ValueCallback.h"
#include "WebPrintInfo.h"

#include <ManagedRect.h>

namespace webkit {

namespace Managed = WebKit::Managed;

class SWKData;
class SWKError;
class SWKEvaluateJavaScriptError;
class SWKURLRequest;
class SWKView;
class SWKWebContentConfiguration;
class Vector;
class WebBitmap;

class WEBKIT_EXPORT SWKWebContent : public Managed::SWKWebContent {
    friend class Managed::SWKWebContent;
public:
    void INIT();

    /**
     * Returns a web view initialized with a specified frame and configuration.
     * <p>
     * The initializer copies the specified configuration, so mutating the
     * configuration after invoking the initializer has no effect on the web
     * view.
     *
     * @param frame The frame for the new web view.
     * @param configuration The configuration for the new web view.
     * @result An initialized web view, or nullptr if the object could not be
     *         initialized.
     */
    void INIT(std::shared_ptr<Managed::Rect>, std::shared_ptr<Managed::SWKWebContentConfiguration>);

    /**
     * Get the web view's back-forward list.
     */
    std::shared_ptr<SWKBackForwardList> getBackForwardList();

    /**
     * Navigates to a requested URL.
     *
     * @param request The request specifying the URL to which to navigate.
     * @result A new navigation for the given request.
     */
    std::shared_ptr<SWKNavigation> loadRequest(std::shared_ptr<SWKURLRequest>);

    /**
     * Navigates to the requested file URL on the filesystem.
     *
     * @param URL The file URL to which to navigate.
     * @param readAccessURL The URL to allow read access to.
     * @discussion If readAccessURL references a single file, only that file may
     *             be loaded by WebKit. If readAccessURL references a directory,
     *             files inside that file may be loaded by WebKit.
     * @result A new navigation for the given file URL.
     */
    std::shared_ptr<SWKNavigation> loadFileURL(const std::string&, const std::string&);

    /**
     * Sets the webpage contents and base URL.
     *
     * @param string The string to use as the contents of the webpage.
     * @param baseURL A URL that is used to resolve relative URLs within the
     *            document.
     * @result A new navigation.
     */
    std::shared_ptr<SWKNavigation> loadHTMLString(const std::string&, const std::string&);

    /**
     * Sets the webpage contents and base URL.
     *
     * @param data The data to use as the contents of the webpage.
     * @param MIMEType The MIME type of the data.
     * @param encodingName The data's character encoding name.
     * @param baseURL A URL that is used to resolve relative URLs within the
     *            document.
     * @result A new navigation.
     */
    std::shared_ptr<SWKNavigation> loadData(const std::string&, const std::string&, const std::string&, const std::string&);

    /**
     * Get the page title.
     */
    std::string getTitle();

    /**
     * Get the active URL. This is the URL that should be reflected in the user
     * interface.
     */
    std::shared_ptr<Managed::SWKURL> getURL();

    /**
     * Get a bool value indicating whether the view is currently loading
     * content.
     */
    bool isLoading();

    /**
     * Get an estimate of what fraction of the current navigation has been
     * completed.
     * <p>
     * This value ranges from 0.0 to 1.0 based on the total number of bytes
     * expected to be received, including the main document and all of its
     * potential subresources. After a navigation completes, the value remains
     * at 1.0 until a new navigation starts, at which point it is reset to 0.0.
     */
    double getEstimatedProgress();

    /**
     * Get a bool value indicating whether all resources on the page have
     * been loaded over securely encrypted connections.
     */
    bool hasOnlySecureContent();

    /**
     * Get a bool value indicating whether there is a back item in the
     * back-forward list that can be navigated to.
     *
     * @see backForwardList.
     */
    bool canGoBack();

    /**
     * Get a bool value indicating whether there is a forward item in the
     * back-forward list that can be navigated to.
     *
     * @see backForwardList.
     */
    bool canGoForward();

    /**
     * Navigates to the back item in the back-forward list.
     *
     * @result A new navigation to the requested item, or nullptr if there is no
     *         back item in the back-forward list.
     */
    std::shared_ptr<SWKNavigation> goBack();

    /**
     * Navigates to the forward item in the back-forward list.
     *
     * @result A new navigation to the requested item, or nullptr if there is no
     *         forward item in the back-forward list.
     */
    std::shared_ptr<SWKNavigation> goForward();

    /**
     * Reloads the current page.
     *
     * @result A new navigation representing the reload.
     */
    std::shared_ptr<SWKNavigation> reload();

    /**
     * Reloads the current page, performing end-to-end revalidation using
     * cache-validating conditionals if possible.
     *
     * @result A new navigation representing the reload.
     */
    std::shared_ptr<SWKNavigation> reloadFromOrigin();

    /**
     * Stops loading all resources on the current page.
     */
    void stopLoading();

    /**
     * Get the custom user agent string or nullptr if no custom user agent string
     * has been set.
     */
    std::string getCustomUserAgent();

    /**
     * Set the custom user agent string.
     */
    void setCustomUserAgent(const std::string&);

    /**
     * Create the UI view associated with the web view.
     */
    std::shared_ptr<SWKView> createView();

    /**
     * The UI view associated with the web view. Can be null.
     */
    std::shared_ptr<SWKView> peekView();

    /**
     * Get the content width.
     */
    int32_t getContentWidth();

    /**
     * Get the content height.
     */
    int32_t getContentHeight();
        
    void loadAlternateHTMLString(const std::string&, std::shared_ptr<Managed::SWKURL>, std::shared_ptr<Managed::SWKURL>);

    void snapshotRect(std::shared_ptr<Native::Managed::Rect>, float, std::shared_ptr<ValueCallback<WebBitmap>>);

    void killWebContentProcess();

    void getMainResourceDataWithCompletionHandle(
        std::shared_ptr<ValueCallback<std::pair<std::shared_ptr<SWKData>, std::shared_ptr<SWKError>>>>);

    void getWebArchiveDataWithCompletionHandle(
        std::shared_ptr<ValueCallback<std::pair<std::shared_ptr<SWKData>, std::shared_ptr<SWKError>>>>);

    /**
     * @param options one of the FindOptionsXXX values.
     */
    void findString(const std::string&, int32_t, int32_t);

    /**
     * @param options one of the FindOptionsXXX values.
     */
    void countStringMatches(const std::string&, int32_t, int32_t);

    void selectFindMatch(int32_t);

    void hideFindUI();

    std::shared_ptr<Managed::SWKURL> getUnreachableURL();

    std::shared_ptr<Vector> getCertificateChain();

    std::string getCommittedURL();

    std::string getMIMEType();

    std::string getUserAgent();

    int32_t getWebProcessIdentifier();

    bool isNetworkRequestsInProgress();

    bool isSupportingTextZoom();

    /**
     * @param observedRenderingProgressEvents one of the
     *            RenderingProgressEventXXX values.
     */
    void setObservedRenderingProgressEvent(int32_t);

    /**
     * @return one of the RenderingProgressEventXXX values.
     */
    int32_t getObservedRenderingProgressEvents();

    bool isEditable();

    void setEditable(bool);

    void setAllowsRemoteInspection(bool);

    bool getAllowsRemoteInspection();

    void setAddsVisitedLinks(bool);

    bool getAddsVisitedLinks();

};

}

#endif // SWKWebContent_h
