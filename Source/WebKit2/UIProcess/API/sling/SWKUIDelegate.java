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

package labs.naver.webkit.api;

import android.graphics.Point;
import android.graphics.Rect;

import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeNamespace;
import labs.naver.webkit.SWKActivatedElementInfo;
import labs.naver.webkit.SWKFrameHandle;
import labs.naver.webkit.SWKGeolocationPermissionRequest;
import labs.naver.webkit.SWKNotificationPermissionRequest;
import labs.naver.webkit.SWKOpenPanelResultListener;
import labs.naver.webkit.SWKSecurityOrigin;
import labs.naver.webkit.SWKWebHitTestResult;
import java.util.Vector;

@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public abstract class SWKUIDelegate {
    /**
     * Creates a new web view.
     * <p>
     * The web view returned must be created with the specified configuration. WebKit will load the request in the returned web view.
     * If you do not implement this method, the web view will cancel the navigation.
     *
     * @param webContent The web view invoking the delegate method.
     * @param configuration The configuration to use when creating the new web view.
     * @param navigationAction The navigation action causing the new web view to
     * be created.
     * @param windowFeatures Window features requested by the webpage.
     * @result A new web view or null.
     */
    @CalledByNative
    public SWKWebContent createWebViewWithConfiguration(SWKWebContentConfiguration configuration,
            SWKNavigationAction navigationAction, SWKWindowFeatures windowFeatures) {
        return null;
    }

    /**
     * Displays a JavaScript alert panel.
     * <p>
     * For user security, your app should call attention to the fact
     * that a specific website controls the content in this panel. A simple forumla
     * for identifying the controlling website is frame.request.URL.host.
     * The panel should have a single OK button.
     * If you do not implement this method, the web view will behave as if the user selected the OK button.
     *
     * @param webContent The web view invoking the delegate method.
     * @param message The message to display.
     * @param frame Information about the frame whose JavaScript initiated this
     * call.
     * @param completionHandler The completion handler to call after the alert
     * panel has been dismissed.
     */
    @CalledByNative
    public boolean runJavaScriptAlertPanelWithMessage(SWKWebContent webContent, String message,
            SWKFrameInfo frame, final CompletionHandler<Void> completionHandler) {
        return false;
    }

    /**
     * Displays a JavaScript confirm panel.
     * <p>
     * For user security, your app should call attention to the fact
     * that a specific website controls the content in this panel. A simple forumla
     * for identifying the controlling website is frame.request.URL.host.
     * The panel should have two buttons, such as OK and Cancel.
     * If you do not implement this method, the web view will behave as if the user selected the Cancel button.
     *
     * @param webContent The web view invoking the delegate method.
     * @param message The message to display.
     * @param frame Information about the frame whose JavaScript initiated this call.
     * @param completionHandler The completion handler to call after the confirm
     * panel has been dismissed. Pass YES if the user chose OK, NO if the user
     * chose Cancel.
     */
    @CalledByNative
    public boolean runJavaScriptConfirmPanelWithMessage(SWKWebContent webContent, String message,
            SWKFrameInfo frame, final CompletionHandler<Boolean> completionHandler) {
        return false;
    }

    /**
     * Displays a JavaScript beforeunload confirm panel.
     *
     * @param webContent The web view invoking the delegate method.
     * @param message The message to display.
     * @param frame Information about the frame whose JavaScript initiated this call.
     * @param completionHandler The completion handler to call after the confirm
     * panel has been dismissed. Pass YES if the user chose OK, NO if the user
     * chose Cancel.
     */
    @CalledByNative
    public boolean runBeforeUnloadConfirmPanelWithMessage(SWKWebContent webContent, String message,
            SWKFrameInfo frame, final CompletionHandler<Boolean> completionHandler) {
        return false;
    }

    /**
     * Displays a JavaScript text input panel.
     * <p>
     * For user security, your app should call attention to the fact
     * that a specific website controls the content in this panel. A simple forumla
     * for identifying the controlling website is frame.request.URL.host.
     * The panel should have two buttons, such as OK and Cancel, and a field in
     * which to enter text.
     * If you do not implement this method, the web view will behave as if the user selected the Cancel button.
     *
     * @param webContent The web view invoking the delegate method.
     * @param message The message to display.
     * @param defaultText The initial text to display in the text entry field.
     * @param frame Information about the frame whose JavaScript initiated this call.
     * @param completionHandler The completion handler to call after the text
     * input panel has been dismissed. Pass the entered text if the user chose
     * OK, otherwise null.
     */
    @CalledByNative
    public boolean runJavaScriptTextInputPanelWithPrompt(SWKWebContent webContent, String prompt,
            String defaultText, SWKFrameInfo frame, final CompletionHandler<String> completionHandler) {
        return false;
    }

    // FIXME: This should be handled by the SWKWebsiteDataStore delegate.
    // @SWKPrivate
    @CalledByNative
    public void decideDatabaseQuotaForSecurityOrigin(SWKWebContent webContent,
            SWKSecurityOrigin securityOrigin, long currentQuota,
            long currentOriginUsage, long currentUsage, long expectedUsage,
            final CompletionHandler<Long> decisionHandler) {
    }

    // FIXME: This should be handled by the SWKWebsiteDataStore delegate.
    // @SWKPrivate
    @CalledByNative
    public void decideWebApplicationCacheQuotaForSecurityOrigin(SWKWebContent webContent,
            SWKSecurityOrigin securityOrigin, long currentQuota, long totalBytesNeeded,
            final CompletionHandler<Long> decisionHandler) {
    }

    // @SWKPrivate
    @CalledByNative
    public boolean decidePolicyForGeolocationPermissionRequest(SWKSecurityOrigin origin,
             SWKGeolocationPermissionRequest request) {
        return false;
    }

    // @SWKPrivate
    @CalledByNative
    public boolean decidePolicyForNotificationPermissionRequest(SWKSecurityOrigin origin,
             SWKNotificationPermissionRequest request) {
        return false;
    }

    @CalledByNative
    // @SWKPrivate
    public void printFrame(SWKWebContent webContent, SWKFrameHandle frame) {
    }

    @CalledByNative
    // @SWKPrivate
    public void webViewClose(SWKWebContent webContent) {

    }

    @CalledByNative
    // @SWKPrivate
    public Vector<?> actionsForElement(SWKWebContent webContent, SWKActivatedElementInfo element,
            Vector<?> defaultActions) {
        return null;
    }

    @CalledByNative
    // @SWKPrivate
    public void didNotHandleTapAsClickAtPoint(SWKWebContent webContent, Point point) {

    }

    @CalledByNative
    // @SWKPrivate
    public boolean shouldRequestGeolocationAuthorizationForURL(SWKWebContent webContent, SWKURL url,
            boolean isMainFrame, SWKURL mainFrameURL) {
        return false;
    }

    @Deprecated
    @CalledByNative
    public void mouseDidMoveOverElement(SWKWebHitTestResult hitTestResult, int modifiers) {
    }

    @CalledByNative
    public boolean runOpenPanel(SWKOpenPanelResultListener request) {
        return false;
    }

    // @SWKPrivate
    @CalledByNative
    public boolean exceededDatabaseQuota(SWKWebContent webContent, SWKSecurityOrigin securityOrigin,
            long currentQuota, long currentOriginUsage, long currentDatabaseUsage, long expectedUsage,
            final CompletionHandler<Long> decisionHandler) {
        return false;
    }

    @CalledByNative
    public Rect getWindowRect(SWKWebContent webContent) {
        return new Rect();
    }

    @CalledByNative
    public void setWindowRect(SWKWebContent webContent, Rect rect) {
    }

    // @SWKPrivate
    @CalledByNative
    public void receiveMessageFromJavaScript(SWKWebContent webContent, Vector<String> messages) {
    }

    // @SWKPrivate
    @CalledByNative
    public void didPressMissingPluginButton(String url) {
    }
}
