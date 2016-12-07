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

import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeConstructor;
import labs.naver.onig.NativeDestructor;
import labs.naver.onig.NativeNamespace;
import labs.naver.onig.NativeObjectField;

/**
 * A SWKPreferences object encapsulates the preference settings for a web view.
 * The preferences object associated with a web view is specified by its web
 * view configuration.
 */
@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class SWKPreferences {
    // @SWKPrivate
    public static final int STORAGE_BLOCKING_POLICY_ALLOW_ALL = 0;
    // @SWKPrivate
    public static final int STORAGE_BLOCKING_POLICY_BLOCK_THIRD_PARTY = 0;
    // @SWKPrivate
    public static final int STORAGE_BLOCKING_POLICY_BLOCK_ALL = 0;

    // @SWKPrivate
    public static final int DEBUG_OVERLAY_REGION_NON_FAST_SCROLLABLE_REGION = 1 << 0;
    // @SWKPrivate
    public static final int DEBUG_OVERLAY_REGION_WHEEL_EVENT_HANDLER_REGION = 1 << 1;

    // @SWKPrivate
    public static final int JAVA_SCRIPT_RUNTIME_FLAGS_SYMBOL_ENABLED = 1 << 0;
    // @SWKPrivate
    public static final int JAVA_SCRIPT_RUNTIME_FLAGS_PROMISE_DISABLED = 1 << 1;
    // @SWKPrivate
    public static final int JAVA_SCRIPT_RUNTIME_FLAGS_ALL_ENABLED = JAVA_SCRIPT_RUNTIME_FLAGS_SYMBOL_ENABLED;

    public native void setMinimumFontSize(int size);
    public native int getMinimumFontSize();

    public native void setJavaScriptCanOpenWindowsAutomatically(boolean enable);
    public native boolean getJavaScriptCanOpenWindowsAutomatically();

    public native void setJavascriptEnabled(boolean enable);
    public native boolean getJavascriptEnabled();

    // @SWKPrivate
    public void setTelephoneNumberDetectionIsEnabled(boolean telephoneNumberDetectionIsEnabled) {
    }

    // @SWKPrivate
    public boolean getTelephoneNumberDetectionIsEnabled() {
        return false;
    }

    // @SWKPrivate
    public void setStorageBlockingPolicy(int storageBlockingPolicy) {
    }

    // @SWKPrivate
    public int getStorageBlockingPolicy() {
        return STORAGE_BLOCKING_POLICY_ALLOW_ALL;
    }

    // @SWKPrivate
    public void setCompositingBordersVisible(boolean compositingBordersVisible) {
    }

    // @SWKPrivate
    public boolean getCompositingBordersVisible() {
        return false;
    }

    // @SWKPrivate
    public void setCompositingRepaintCountersVisible(boolean compositingRepaintCountersVisible) {
    }

    // @SWKPrivate
    public boolean getCompositingRepaintCountersVisible() {
        return false;
    }

    // @SWKPrivate
    public void setTiledScrollingIndicatorVisible(boolean tiledScrollingIndicatorVisible) {
    }

    // @SWKPrivate
    public boolean getTiledScrollingIndicatorVisible() {
        return false;
    }

    // @SWKPrivate
    public void setVisibleDebugOverlayRegions(int visibleDebugOverlayRegions) {
    }

    // @SWKPrivate
    public int getVisibleDebugOverlayRegions() {
        return 0;
    }

    // @SWKPrivate
    public void setSimpleLineLayoutDebugBordersEnabled(boolean simpleLineLayoutDebugBordersEnabled) {
    }

    // @SWKPrivate
    public boolean getSimpleLineLayoutDebugBordersEnabled() {
        return false;
    }

    // @SWKPrivate
    public void setLogsPageMessagesToSystemConsoleEnabled(
            boolean logsPageMessagesToSystemConsoleEnabled) {
    }

    // @SWKPrivate
    public boolean getLogsPageMessagesToSystemConsoleEnabled() {
        return false;
    }

    // @SWKPrivate
    public void setAllowFileAccessFromFileURLs(boolean allowFileAccessFromFileURLs) {
    }

    // @SWKPrivate
    public boolean getAllowFileAccessFromFileURLs() {
        return false;
    }

    // @SWKPrivate
    public void setJavaScriptRuntimeFlags(int javaScriptRuntimeFlags) {
    }

    // @SWKPrivate
    public int getJavaScriptRuntimeFlags() {
        return 0;
    }

    // @SWKPrivate
    public void setStandalone(boolean standalone) {
    }

    // @SWKPrivate
    public boolean isStandalone() {
        return false;
    }

    // @SWKPrivate
    public void setDiagnosticLoggingEnabled(boolean diagnosticLoggingEnabled) {
    }

    // @SWKPrivate
    public boolean getDiagnosticLoggingEnabled() {
        return false;
    }

    // FIXME: This should be configured on the SWKWebsiteDataStore.
    // FIXME: This property should not have the verb "is" in it.
    // @SWKPrivate
    public void setOfflineApplicationCacheIsEnabled(boolean offlineApplicationCacheIsEnabled) {
    }

    // @SWKPrivate
    public boolean getOfflineApplicationCacheIsEnabled() {
        return false;
    }

    @NativeObjectField
    private int mNativeInstance;

    @CalledByNative
    private SWKPreferences() {
        nativeCreate();
    }

    @Override
    protected void finalize() {
        nativeDestroy();
    }

    @NativeConstructor
    private native void nativeCreate();
    @NativeDestructor
    private native void nativeDestroy();

    // @SWKPrivate
    public native void setFullScreenEnabled(boolean enable);

    // @SWKPrivate
    public native boolean getFullScreenEnabled();

    // @SWKPrivate
    public native void setLoadsImagesAutomatically(boolean automatic);

    // @SWKPrivate
    public native boolean getLoadsImagesAutomatically();

    // @SWKPrivate
    public native void setDeveloperExtrasEnabled(boolean enable);

    // @SWKPrivate
    public native boolean getDeveloperExtrasEnabled();

    // @SWKPrivate
    public native void setFileAccessFromFileUrlsAllowed(boolean enable);

    // @SWKPrivate
    public native boolean getFileAccessFromFileUrlsAllowed();

    // @SWKPrivate
    public native void setFrameFlatteningEnabled(boolean enable);

    // @SWKPrivate
    public native boolean getFrameFlatteningEnabled();

    // @SWKPrivate
    public native void setDNSPrefetchingEnabled(boolean enable);

    // @SWKPrivate
    public native boolean getDNSPrefetchingEnabled();

    // @SWKPrivate
    public native void setEncodingDetectorEnabled(boolean enable);

    // @SWKPrivate
    public native boolean getEncodingDetectorEnabled();

    // @SWKPrivate
    public native void setDefaultTextEncodingName(String encodingName);

    // @SWKPrivate
    public native String getDefaultTextEncodingName();

    // @SWKPrivate
    public native void setPreferredMinimumContentsWidth(int width);

    // @SWKPrivate
    public native int getPreferredMinimumContentsWidth();

    // @SWKPrivate
    public native void setOfflineWebApplicationCacheEnabled(boolean enable);

    // @SWKPrivate
    public native boolean getOfflineWebApplicationCacheEnabled();

    // @SWKPrivate
    public native void setScriptsCanOpenWindows(boolean enable);

    // @SWKPrivate
    public native boolean getScriptsCanOpenWindows();

    // @SWKPrivate
    public native void setLocalStorageEnabled(boolean enable);

    // @SWKPrivate
    public native boolean getLocalStorageEnabled();

    // @SWKPrivate
    public native void setPluginsEnabled(boolean enable);

    // @SWKPrivate
    public native boolean getPluginsEnabled();

    // @SWKPrivate
    public native void setDefaultFontSize(int size);

    // @SWKPrivate
    public native int getDefaultFontSize();

    // @SWKPrivate
    public native void setPrivateBrowsingEnabled(boolean enable);

    // @SWKPrivate
    public native boolean getPrivateBrowsingEnabled();

    // @SWKPrivate
    public native void setTextAutosizingEnabled(boolean enable);

    // @SWKPrivate
    public native boolean getTextAutosizingEnabled();

    // @SWKPrivate
    public native void setSpatialNavigationEnabled(boolean enable);

    // @SWKPrivate
    public native boolean getSpatialNavigationEnabled();

    // @SWKPrivate
    public native void setDatabasesEnabled(boolean enable);

    // @SWKPrivate
    public native boolean getDatabasesEnabled();

    // @SWKPrivate
    public native boolean getSuppressesIncrementalRendering();

    // @SWKPrivate
    public native void setSuppressesIncrementalRendering(boolean enable);

    // @SWKPrivate
    public native boolean getSmartInsertDeleteEnabled();

    // @SWKPrivate
    public native void setSmartInsertDeleteEnabled(boolean enable);

    // @SWKPrivate
    public native void setHiddenPageDOMTimerThrottlingEnabled(boolean enable);

    // @SWKPrivate
    public native void setHiddenPageCSSAnimationSuspensionEnabled(boolean enable);

    // @SWKPrivate
    public native void setJavaScriptCanAccessClipboard(boolean enable);

    // @SWKPrivate
    public native void setScrollAnimatorEnabled(boolean enable);

    // @SWKPrivate
    public native boolean getScrollAnimatorEnabled();

    // @SWKPrivate
    public native void setUsesPageCache(boolean enable);

    // @SWKPrivate
    public native boolean getUsesPageCache();

    // @SWKPrivate
    public native void setPageCacheSupportsPlugins(boolean enable);

    // @SWKPrivate
    public native boolean getPageCacheSupportsPlugins();
}
