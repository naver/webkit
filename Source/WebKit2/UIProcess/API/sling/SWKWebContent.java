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

package labs.naver.webkit.api;

import android.graphics.Rect;
import android.util.Pair;
import labs.naver.onig.AbstractNativeMethod;
import labs.naver.onig.AccessedByNative;
import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeConstructor;
import labs.naver.onig.NativeDestructor;
import labs.naver.onig.NativeNamespace;
import labs.naver.onig.NativeObjectField;
import labs.naver.webkit.SWKContextMenuDelegate;
import labs.naver.webkit.SWKContextMenuItem;
import labs.naver.webkit.SWKData;
import labs.naver.webkit.SWKFindDelegate;
import labs.naver.webkit.SWKFormDelegate;
import labs.naver.webkit.SWKSessionState;
import labs.naver.webkit.SWKURLRequest;
import labs.naver.webkit.WebPrintInfo;
import labs.naver.webkit.clutter.WebBitmap;

import java.util.Vector;

/**
 * A SWKWebContent object displays interactive Web content.
 */
@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class SWKWebContent {
    @AccessedByNative
    public static final int FIND_OPTIONS_CASE_INSENSITIVE = 0x00000001;
    @AccessedByNative
    public static final int FIND_OPTIONS_AT_WORD_STARTS = 0x00000002;
    @AccessedByNative
    public static final int FIND_OPTIONS_TREAT_MEDIAL_CAPITAL_AS_WORD_START = 0x00000004;
    @AccessedByNative
    public static final int FIND_OPTIONS_BACKWARDS = 0x00000008;
    @AccessedByNative
    public static final int FIND_OPTIONS_WRAP_AROUND = 0x00000010;
    @AccessedByNative
    public static final int FIND_OPTIONS_SHOW_OVERLAY = 0x00000020;
    @AccessedByNative
    public static final int FIND_OPTIONS_SHOW_FIND_INDICATOR = 0x00000040;
    @AccessedByNative
    public static final int FIND_OPTIONS_SHOW_HIGHLIGHT = 0x00000080;
    @AccessedByNative
    public static final int FIND_OPTIONS_DETERMINE_MATCH_INDEX = 0x00000100;

    // @SWKPrivate
    @AccessedByNative
    public static final int RENDERING_PROGRESS_EVENT_FIRST_LAYOUT = 0x00000001;
    // @SWKPrivate
    @AccessedByNative
    public static final int RENDERING_PROGRESS_EVENT_FIRST_VISUALLY_NON_EMPTY_LAYOUT = 0x00000002;
    // @SWKPrivate
    @AccessedByNative
    public static final int RENDERING_PROGRESS_EVENT_FIRST_PAINT_WITH_SIGNIFICANT_AREA = 0x00000004;
    // @SWKPrivate
    @AccessedByNative
    public static final int RENDERING_PROGRESS_EVENT_REACHED_SESSION_RESTORATION_RENDER_TREE_SIZE_THRESHOLD = 0x00000008;

    public SWKWebContent() {
        this(null, null);
    }

    /**
     * Returns a web view initialized with a specified frame and configuration.
     * <p>
     * The initializer copies the specified configuration, so mutating the
     * configuration after invoking the initializer has no effect on the web
     * view.
     *
     * @param frame The frame for the new web view.
     * @param configuration The configuration for the new web view.
     * @result An initialized web view, or null if the object could not be
     *         initialized.
     */
    @CalledByNative
    public SWKWebContent(Rect frame, SWKWebContentConfiguration configuration) {
        nativeCreate(frame, configuration);
    }

    /**
     * A copy of the configuration with which the web view was initialized.
     */
    @AbstractNativeMethod
    public native SWKWebContentConfiguration getConfiguration();

    /**
     * Set the web view's user interface delegate.
     */
    @AbstractNativeMethod
    public native void setUIDelegate(SWKUIDelegate uiDelegate);

    /**
     * Get the web view's user interface delegate.
     */
    @AbstractNativeMethod
    public native SWKUIDelegate getUIDelegate();

    /**
     * Set the web view's loader delegate.
     */
    @AbstractNativeMethod
    public native void setLoaderDelegate(SWKLoaderDelegate loaderDelegate);

    /**
     * Set the web view's policy delegate.
     */
    @AbstractNativeMethod
    public native void setPolicyDelegate(SWKPolicyDelegate policyDelegate);

    /**
     * Get the web view's back-forward list.
     */
    @AbstractNativeMethod
    public native SWKBackForwardList getBackForwardList();

    /**
     * Navigates to a requested URL.
     *
     * @param request The request specifying the URL to which to navigate.
     * @result A new navigation for the given request.
     */
    @AbstractNativeMethod
    public native SWKNavigation loadRequest(SWKURLRequest request);

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
    public SWKNavigation loadFileURL(String Url, String readAccessUrl) {
        return null;
    }

    /**
     * Sets the webpage contents and base URL.
     *
     * @param string The string to use as the contents of the webpage.
     * @param baseURL A URL that is used to resolve relative URLs within the
     *            document.
     * @result A new navigation.
     */
    @AbstractNativeMethod
    public native SWKNavigation loadHTMLString(String htmlString, String baseURL);

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
    @AbstractNativeMethod
    public native SWKNavigation loadData(String data, String MimeType, String characterEncodingName,
            String baseUrl);

    /**
     * Navigates to an item from the back-forward list and sets it as the
     * current item.
     *
     * @param item The item to which to navigate. Must be one of the items in
     *            the web view's back-forward list.
     * @result A new navigation to the requested item, or null if it is already
     *         the current item or is not part of the web view's back-forward
     *         list.
     * @see backForwardList
     */
    @AbstractNativeMethod
    public native SWKNavigation goToBackForwardListItem(SWKBackForwardListItem item);

    /**
     * Get the page title.
     */
    @AbstractNativeMethod
    public native String getTitle();

    /**
     * Get the active URL. This is the URL that should be reflected in the user
     * interface.
     */
    @AbstractNativeMethod
    public native SWKURL getURL();

    /**
     * Get a boolean value indicating whether the view is currently loading
     * content.
     */
    public boolean isLoading() {
        return false;
    }

    /**
     * Get an estimate of what fraction of the current navigation has been
     * completed.
     * <p>
     * This value ranges from 0.0 to 1.0 based on the total number of bytes
     * expected to be received, including the main document and all of its
     * potential subresources. After a navigation completes, the value remains
     * at 1.0 until a new navigation starts, at which point it is reset to 0.0.
     */
    public double getEstimatedProgress() {
        return 0;
    }

    /**
     * Get a boolean value indicating whether all resources on the page have
     * been loaded over securely encrypted connections.
     */
    public boolean hasOnlySecureContent() {
        return false;
    }

    /**
     * Get a boolean value indicating whether there is a back item in the
     * back-forward list that can be navigated to.
     *
     * @see backForwardList.
     */
    @AbstractNativeMethod
    public native boolean canGoBack();

    /**
     * Get a boolean value indicating whether there is a forward item in the
     * back-forward list that can be navigated to.
     *
     * @see backForwardList.
     */
    @AbstractNativeMethod
    public native boolean canGoForward();

    /**
     * Navigates to the back item in the back-forward list.
     *
     * @result A new navigation to the requested item, or null if there is no
     *         back item in the back-forward list.
     */
    @AbstractNativeMethod
    public native SWKNavigation goBack();

    /**
     * Navigates to the forward item in the back-forward list.
     *
     * @result A new navigation to the requested item, or null if there is no
     *         forward item in the back-forward list.
     */
    @AbstractNativeMethod
    public native SWKNavigation goForward();

    /**
     * Reloads the current page.
     *
     * @result A new navigation representing the reload.
     */
    @AbstractNativeMethod
    public native SWKNavigation reload();

    /**
     * Reloads the current page, performing end-to-end revalidation using
     * cache-validating conditionals if possible.
     *
     * @result A new navigation representing the reload.
     */
    @AbstractNativeMethod
    public native SWKNavigation reloadFromOrigin();

    /**
     * Stops loading all resources on the current page.
     */
    @AbstractNativeMethod
    public native void stopLoading();

    /**
     * Evaluates the given JavaScript string.
     *
     * @param javaScriptString The JavaScript string to evaluate.
     * @param valueCallback A callback to invoke when script evaluation
     *            completes or fails. The valueCallback is passed the result
     *            of the script evaluation or an error.
     */
    @AbstractNativeMethod
    public native void evaluateJavaScript(String javaScriptString, ValueCallback<?> valueCallback);

    /**
     * Get the custom user agent string or null if no custom user agent string
     * has been set.
     */
    @AbstractNativeMethod
    public native String getCustomUserAgent();

    /**
     * Set the custom user agent string.
     */
    @AbstractNativeMethod
    public native void setCustomUserAgent(String customUserAgent);

    /**
     * Get the custom text encoding name string or null.
     */
    @AbstractNativeMethod
    public native String getCustomTextEncodingName();

    /**
     * Set the custom text encoding name. Current contents will be reloaded if encoding is changed.
     */
    @AbstractNativeMethod
    public native void setCustomTextEncodingName(String customTextEncodingName);

    /**
     * Create the UI view associated with the web view.
     */
    @AbstractNativeMethod
    public native SWKView createView();

    /**
     * The UI view associated with the web view. Can be null.
     */
    @AbstractNativeMethod
    public native SWKView peekView();

    @AbstractNativeMethod
    public native int getContentWidth();

    @AbstractNativeMethod
    public native int getContentHeight();

    /**
     * Request to close to webcontent.
     *
     * WebContent will try to close and show beforeUnloadConfirmPanel if needed.
     * If WebContent is ready to close, webViewClose of UIDelegate will be called.
     */
    @AbstractNativeMethod
    public native void tryClose();

    // @SWKPrivate
    public void loadAlternateHTMLString(String string, SWKURL baseURL, SWKURL unreachableURL) {

    }

    // @SWKPrivate
    @AbstractNativeMethod
    public native void restoreFromSessionState(SWKSessionState sessionState, boolean navigate);

    // @SWKPrivate
    @AbstractNativeMethod
    public native void snapshotRect(Rect rectInViewCoordinates, float imageWidth,
            ValueCallback<WebBitmap> completionHandler);

    // @SWKPrivate
    public void killWebContentProcess() {
    }

    // @SWKPrivate
    public void getMainResourceDataWithCompletionHandler(
            ValueCallback<Pair<SWKData, SWKError>> completionHandler) {
    }

    // @SWKPrivate
    public void getWebArchiveDataWithCompletionHandler(
            ValueCallback<Pair<SWKData, SWKError>> completionHandler) {
    }

    /**
     * @param options one of the FindOptionsXXX values.
     */
    // @SWKPrivate
    @AbstractNativeMethod
    public native void findString(String string, int options, int maxCount);

    /**
     * @param options one of the FindOptionsXXX values.
     */
    // @SWKPrivate
    @AbstractNativeMethod
    public native void countStringMatches(String string, int options, int maxCount);

    @Deprecated
    @AbstractNativeMethod
    public native void selectFindMatch(int matchIndex);

    // @SWKPrivate
    @AbstractNativeMethod
    public native void hideFindUI();

    // @SWKPrivate
    @AbstractNativeMethod
    public native SWKURL getUnreachableURL();

    // @SWKPrivate
    public Vector<?> getCertificateChain() {
        return null;
    }

    // @SWKPrivate
    public String getCommittedURL() {
        return null;
    }

    // @SWKPrivate
    public String getMIMEType() {
        return null;
    }

    // @SWKPrivate
    @AbstractNativeMethod
    public native String getUserAgent();

    // @SWKPrivate
    public int getWebProcessIdentifier() {
        return 0;
    }

    // @SWKPrivate
    @AbstractNativeMethod
    public native SWKSessionState getSessionState();

    // @SWKPrivate
    public boolean isNetworkRequestsInProgress() {
        return false;
    }

    // @SWKPrivate
    public boolean isSupportingTextZoom() {
        return false;
    }

    /**
     * @param observedRenderingProgressEvents one of the
     *            RenderingProgressEventXXX values.
     */
    // @SWKPrivate
    public void setObservedRenderingProgressEvents(
            int observedRenderingProgressEvents) {
    }

    /**
     * @return one of the RenderingProgressEventXXX values.
     */
    // @SWKPrivate
    public int getObservedRenderingProgressEvents() {
        return 0;
    }

    // @SWKPrivate
    public boolean isEditable() {
        return false;
    }

    // @SWKPrivate
    public void setEditable(boolean editable) {
    }

    // @SWKPrivate
    public void setAllowsRemoteInspection(boolean allowsRemoteInspection) {
    }

    // @SWKPrivate
    public boolean getAllowsRemoteInspection() {
        return false;
    }

    // @SWKPrivate
    public void setAddsVisitedLinks(boolean addsVisitedLinks) {
    }

    // @SWKPrivate
    public boolean getAddsVisitedLinks() {
        return false;
    }

    @AbstractNativeMethod
    public native void setTextZoomFactor(double textZoomFactor);

    @AbstractNativeMethod
    public native double getTextZoomFactor();

    @AbstractNativeMethod
    public native void setPageZoomFactor(double pageZoomFactor);

    @AbstractNativeMethod
    public native double getPageZoomFactor();

    // @SWKPrivate
    @AbstractNativeMethod
    public native void setFindDelegate(SWKFindDelegate findDelegate);

    // @SWKPrivate
    @AbstractNativeMethod
    public native SWKFindDelegate getFindDelegate();

    // @SWKPrivate
    @AbstractNativeMethod
    public native void setFormDelegate(SWKFormDelegate formDelegate);

    // @SWKPrivate
    @AbstractNativeMethod
    public native void setContextMenuDelegate(SWKContextMenuDelegate contextMenuDelegate);

    // @SWKPrivate
    @AbstractNativeMethod
    public native SWKContextMenuDelegate getContextMenuDelegate();

    // @SWKPrivate
    @AbstractNativeMethod
    public native void setSelectedContextMenuItem(SWKContextMenuItem item);

    // @SWKPrivate
    @AbstractNativeMethod
    public native void showWebInspector(boolean show);

    // @SWKPrivate
    @AbstractNativeMethod
    public native void getContentsAsString(ValueCallback<String> callback);

    // @SWKPrivate
    @AbstractNativeMethod
    public native void getContentsAsMHTMLData(ValueCallback<SWKData> callback);

    @AbstractNativeMethod
    public native void getResourceDataFromFocusedFrame(SWKURL resourceURL, ValueCallback<SWKData> callback);

    // @SWKPrivate
    @AbstractNativeMethod
    public native void computePagesForPrinting(WebPrintInfo printInfo, ValueCallback<Integer> callback);

    // @SWKPrivate
    @AbstractNativeMethod
    public native void drawPagesToPDF(WebPrintInfo printInfo, int first, int count, ValueCallback<SWKData> callback);

    @NativeObjectField
    private int mNativeClass;

    @Override
    protected void finalize() throws Throwable {
        try {
            nativeDestroy();
        } finally {
            super.finalize();
        }
    }

    @NativeConstructor
    private native void nativeCreate(Rect frame, SWKWebContentConfiguration configuration);
    @NativeDestructor
    private native void nativeDestroy();

    static {
        System.loadLibrary("WebKit2");
    }
}
