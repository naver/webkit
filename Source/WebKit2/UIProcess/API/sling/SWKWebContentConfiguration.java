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

import labs.naver.onig.AbstractNativeMethod;
import labs.naver.onig.AccessedByNative;
import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeConstructor;
import labs.naver.onig.NativeDestructor;
import labs.naver.onig.NativeNamespace;
import labs.naver.onig.NativeObjectField;
import labs.naver.webkit.SWKVisitedLinkStore;
import labs.naver.webkit.SWKWebsiteDataStore;
import labs.naver.webkit.wtf.WTFMainThread;

/**
 * A SWKWebContentConfiguration object is a collection of properties with which to
 * initialize a web view.
 */
@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class SWKWebContentConfiguration {

    /**
     * Selection granularity varies automatically based on the selection. Use
     * with {@link #setSelectionGranularity}.
     */
    @AccessedByNative
    public static final int SELECTION_GRANULARITY_DYNAMIC = 0;
    /**
     * SelectionGranularityCharacter Selection endpoints can be placed at any
     * character boundary. Use with {@link #setSelectionGranularity}.
     */
    @AccessedByNative
    public static final int SELECTION_GRANULARITY_CHARACTER = 1;

    /**
     * The user content controller to associate with the web view.
     */
    private SWKUserContentController mUserContentController;

    /**
     * The level of granularity with which the user can interactively select
     * content in the web view. *
     * <p>
     * An example of how granularity may vary when
     * SWKSelectionGranularityDynamic is used is that when the selection is
     * within a single block, the granularity may be single character, and when
     * the selection is not confined to a single block, the selection
     * granularity may be single block.
     * <p>
     * The default value is SelectionGranularityDynamic.
     */
    private int mSelectionGranularity = SELECTION_GRANULARITY_DYNAMIC;

    @CalledByNative
    public SWKWebContentConfiguration() {
        nativeCreate();
    }

    /**
     * The process pool from which to obtain the view's web content process.
     * <p>
     * When a web view is initialized, a new web content process will be created
     * for it from the specified pool, or an existing process in that pool will
     * be used.
     */
    @AbstractNativeMethod
    public native SWKProcessPool getProcessPool();

    @AbstractNativeMethod
    public native void setProcessPool(SWKProcessPool processPool);

    /**
     * The preference settings to be used by the web view.
     */
    @AbstractNativeMethod
    public native SWKPreferences getPreferences();

    @AbstractNativeMethod
    public native void setPreferences(SWKPreferences preferences);

    @AbstractNativeMethod
    public native SWKUserContentController getUserContentController();

    @AbstractNativeMethod
    public native void setUserContentController(SWKUserContentController userContentController);

    /**
     * A boolean value indicating whether the web view suppresses content
     * rendering until it is fully loaded into memory.
     * <p>
     * The default value is false.
     */
    @AbstractNativeMethod
    public native boolean isSuppressesIncrementalRendering();

    @AbstractNativeMethod
    public native void setSuppressesIncrementalRendering(boolean suppressesIncrementalRendering);

    /**
     * The name of the application as used in the user agent string.
     */
    @AbstractNativeMethod
    public native String getApplicationNameForUserAgent();

    @AbstractNativeMethod
    public native void setApplicationNameForUserAgent(String applicationNameForUserAgent);

    /**
     * A boolean value indicating whether HTML5 videos play inline (true) or use
     * the native full-screen controller (false).
     * <p>
     * The default value is false.
     */
    @AbstractNativeMethod
    public native boolean isAllowsInlineMediaPlayback();

    @AbstractNativeMethod
    public native void setAllowsInlineMediaPlayback(boolean allowsInlineMediaPlayback);

    /**
     * A boolean value indicating whether HTML5 videos require the user to start
     * playing them (true) or can play automatically (false).
     * <p>
     * The default value is true.
     */
    @AbstractNativeMethod
    public native boolean isMediaPlaybackRequiresUserAction();

    @AbstractNativeMethod
    public native void setMediaPlaybackRequiresUserAction(boolean mediaPlaybackRequiresUserAction);

    public int getSelectionGranularity() {
        return mSelectionGranularity;
    }

    public void setSelectionGranularity(int selectionGranularity) {
        mSelectionGranularity = selectionGranularity;
    }

    // @SWKPrivate
    @AbstractNativeMethod
    public native void setGroupIdentifier(String groupIdentifier);

    // @SWKPrivate
    @AbstractNativeMethod
    public native String getGroupIdentifier();

    // @SWKPrivate
    public void setVisitedLinkProvider(SWKVisitedLinkStore visitedLinkProvider) {
    }

    // @SWKPrivate
    public SWKVisitedLinkStore getVisitedLinkProvider() {
        return null;
    }

    // @SWKPrivate
    public void setWebsiteDataStore(SWKWebsiteDataStore websiteDataStore) {
    }

    // @SWKPrivate
    public SWKWebsiteDataStore getWebsiteDataStore() {
        return null;
    }

    // @SWKPrivate
    public void setTreatsSHA1SignedCertificatesAsInsecure(
            boolean treatsSHA1SignedCertificatesAsInsecure) {
    }

    // @SWKPrivate
    public boolean getTreatsSHA1SignedCertificatesAsInsecure() {
        return false;
    }

    // @SWKPrivate
    public void setAllowsAlternateFullscreen(boolean allowsAlternateFullscreen) {
    }

    // @SWKPrivate
    public boolean getAllowsAlternateFullscreen() {
        return false;
    }

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
    private native void nativeCreate();
    @NativeDestructor
    private native void nativeDestroy();

    static {
        System.loadLibrary("WebKit2");
        WTFMainThread.initializeUIThread(); // FIXME: Remove.
    }
}
