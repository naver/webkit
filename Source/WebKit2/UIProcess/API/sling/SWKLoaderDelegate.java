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

package labs.naver.webkit.api;

import android.util.Pair;

import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeNamespace;
import labs.naver.webkit.SWKCredential;
import labs.naver.webkit.SWKData;
import labs.naver.webkit.SWKNavigationData;
import labs.naver.webkit.SWKProtectionSpace;
import labs.naver.webkit.api.SWKError;

@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class SWKLoaderDelegate {
    // Constants passed by session or task delegates to the provided
    // continuation block in response to an authentication challenge.
    // Use the specified credential, which may be nil.
    public static final int SESSION_AUTH_CHALLENGE_USE_CREDENTIAL = 0;
    // Use the default handling for the challenge as though this delegate method
    // were not implemented. The provided credential parameter is ignored.
    public static final int SESSION_AUTH_CHALLENGE_PERFORM_DEFAULT_HANDLING = 1;
    // Cancel the entire request. The provided credential parameter is ignored.
    public static final int SESSION_AUTH_CHALLENGE_CANCEL_AUTHENTICATION_CHALLENGE = 2;
    // Reject this challenge, and call the authentication delegate method again
    // with the next authentication protection space. The provided credential
    // parameter is ignored.
    public static final int SESSION_AUTH_CHALLENGE_REJECT_PROTECTION_SPACE = 3;

    // @SWKPrivate
    public static final int SAME_DOCUMENT_NAVIGATION_TYPE_ANCHOR_NAVIGATION = 0;
    // @SWKPrivate
    public static final int SAME_DOCUMENT_NAVIGATION_TYPE_SESSION_STATE_PUSH = 1;
    // @SWKPrivate
    public static final int SAME_DOCUMENT_NAVIGATION_TYPE_SESSION_STATE_REPLACE = 2;
    // @SWKPrivate
    public static final int SAME_DOCUMENT_NAVIGATION_TYPE_SESSION_STATE_POP = 3;

    /**
     * Invoked when a main frame navigation starts.
     *
     * @param webContent The web view invoking the delegate method.
     * @param navigation The navigation.
     */
    @CalledByNative
    public void didStartProvisionalNavigation(SWKWebContent webContent,
            SWKNavigation navigation) {
    }

    /**
     * Invoked when a server redirect is received for the main frame.
     *
     * @param webContent The web view invoking the delegate method.
     * @param navigation The navigation.
     */
    @CalledByNative
    public void didReceiveServerRedirectForProvisionalNavigation(
            SWKWebContent webContent, SWKNavigation navigation) {
    }

    /**
     * Invoked when an error occurs while starting to load data for the main
     * frame.
     *
     * @param webContent The web view invoking the delegate method.
     * @param navigation The navigation.
     * @param error The error that occurred.
     */
    @CalledByNative
    public void didFailProvisionalNavigation(SWKWebContent webContent,
            SWKNavigation navigation, SWKError error) {
    }

    /**
     * Invoked when content starts arriving for the main frame.
     *
     * @param webContent The web view invoking the delegate method.
     * @param navigation The navigation.
     */
    @CalledByNative
    public void didCommitNavigation(SWKWebContent webContent,
            SWKNavigation navigation) {
    }

    /**
     * Invoked when a main frame navigation completes.
     *
     * @param webContent The web view invoking the delegate method.
     * @param navigation The navigation.
     */
    @CalledByNative
    public void didFinishNavigation(SWKWebContent webContent,
            SWKNavigation navigation) {
    }

    /**
     * Invoked when an error occurs during a committed main frame navigation.
     *
     * @param webContent The web view invoking the delegate method.
     * @param navigation The navigation.
     * @param error The error that occurred.
     */
    @CalledByNative
    public void didFailNavigation(SWKWebContent webContent,
            SWKNavigation navigation, SWKError error) {
    }

    /**
     * Invoked when the web view needs to respond to an authentication
     * challenge.
     *
     * @param webContent The web view that received the authentication challenge.
     * @param challenge The authentication challenge.
     * @param completionHandler The completion handler you must invoke to
     *            respond to the challenge.
     */
    @CalledByNative
    public void didReceiveAuthenticationChallenge(SWKWebContent webContent,
            SWKAuthenticationChallenge challenge,
            CompletionHandler<Pair<Integer, SWKCredential>> completionHandler) {
    }

    @CalledByNative
    public void didNavigateWithNavigationData(SWKWebContent webContent,
            SWKNavigationData navigationData) {
    }

    @CalledByNative
    public void didPerformClientRedirectFromURL(SWKWebContent webContent,
            SWKURL sourceURL, SWKURL destinationURL) {
    }

    @CalledByNative
    public void didPerformServerRedirectFromURL(SWKWebContent webContent,
            SWKURL sourceURL, SWKURL destinationURL) {
    }

    @CalledByNative
    public void didUpdateHistoryTitle(SWKWebContent webContent, String title,
            SWKURL URL) {
    }

    // @SWKPrivate
    @CalledByNative
    public void didFailProvisionalLoadInSubframe(SWKWebContent webContent,
            SWKNavigation navigation, SWKFrameInfo subframe, SWKError error) {
    }

    // @SWKPrivate
    @CalledByNative
    public void navigationDidFinishDocumentLoad(SWKWebContent webContent,
            SWKNavigation navigation) {
    }

    /**
     * @param navigationType one of the SameDocumentNavigationTypeXXX values.
     */
    // @SWKPrivate
    @CalledByNative
    public void didSameDocumentNavigation(SWKWebContent webContent,
            SWKNavigation navigation, int navigationType) {
    }

    /**
     * @param progressEvents one of the SWKWebContent.RenderingProgressEventXXX
     *            values.
     */
    // @SWKPrivate
    @CalledByNative
    public void renderingProgressDidChange(SWKWebContent webContent,
            int progressEvents) {
    }

    // @SWKPrivate
    @CalledByNative
    public boolean canAuthenticateAgainstProtectionSpace(
            SWKWebContent webContent, SWKProtectionSpace protectionSpace) {
        return false;
    }

    // @SWKPrivate
    @CalledByNative
    public void didReceiveAuthenticationChallenge(SWKWebContent webContent,
            SWKAuthenticationChallenge challenge) {
    }

    // @SWKPrivate
    @CalledByNative
    public void webViewWebContentProcessDidTerminate(SWKWebContent webContent) {
    }

    // @SWKPrivate
    @CalledByNative
    public SWKData webCryptoMasterKeyForWebView(SWKWebContent webContent) {
        return null;
    }

    // @SWKPrivate
    @CalledByNative
    public void willSnapshotBackForwardListItem(SWKWebContent webContent,
            SWKBackForwardListItem item) {
    }

    // @SWKPrivate
    @CalledByNative
    public void didStartLoadForQuickLookDocumentInMainFrameWithFileName(
            SWKWebContent webContent, String fileName, String uti) {
    }

    // @SWKPrivate
    @CalledByNative
    public void didFinishLoadForQuickLookDocumentInMainFrame(
            SWKWebContent webContent, SWKData documentData) {
    }

    @Deprecated
    @CalledByNative
    public void didReceiveTitle(String title) {
    }

    @Deprecated
    @CalledByNative
    public void didChangeProgress(double progress) {
    }

    @Deprecated
    @CalledByNative
    public void didFinishLoad() {
    }

    @Deprecated
    @CalledByNative
    public void didFailLoadWithError(SWKError error) {
    }

    @Deprecated
    @CalledByNative
    public void didStartProvisionalLoad() {
    }

    @Deprecated
    @CalledByNative
    public void didCommitLoad() {
    }

    @Deprecated
    @CalledByNative
    public void didReceiveAuthenticationChallengeInFrame(
            SWKAuthenticationChallenge challenge) {
    }

    @Deprecated
    @CalledByNative
    public void didReceiveServerRedirectForProvisionalLoad() {
    }

    @Deprecated
    @CalledByNative
    public void didFailProvisionalLoadWithError(SWKError error) {
    }

    @Deprecated
    @CalledByNative
    public void didChangeBackForwardList() {
    }

    @Deprecated
    @CalledByNative
    public void processDidBecomeUnresponsive() {
    }

    @Deprecated
    @CalledByNative
    public void processDidBecomeResponsive() {
    }

    @Deprecated
    @CalledByNative
    public void processDidCrash() {
    }
}
