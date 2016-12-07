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

import labs.naver.onig.AbstractNativeMethod;
import labs.naver.onig.AccessedByNative;
import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeConstructor;
import labs.naver.onig.NativeDestructor;
import labs.naver.onig.NativeNamespace;
import labs.naver.onig.NativeObjectField;
import labs.naver.webkit.SWKApplicationCacheManager;
import labs.naver.webkit.SWKCookieManager;
import labs.naver.webkit.SWKDownloadDelegate;
import labs.naver.webkit.SWKGeolocationProvider;
import labs.naver.webkit.SWKIconDatabase;
import labs.naver.webkit.SWKKeyValueStorageManager;
import labs.naver.webkit.SWKNotificationProvider;
import labs.naver.webkit.SWKProcessPoolConfiguration;
import labs.naver.webkit.SWKResourceCacheManager;
import labs.naver.webkit.SWKVisitedLinkStore;

import java.util.Vector;

@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public final class SWKProcessPool {

    // WebKit2/Shared/android/CacheModel.h
    @Deprecated
    @AccessedByNative
    public static final int CACHE_MODEL_DOCUMENT_VIEWER = 0;
    @Deprecated
    @AccessedByNative
    public static final int CACHE_MODEL_DOCUMENT_BROWSER = 1;
    @Deprecated
    @AccessedByNative
    public static final int CACHE_MODEL_PRIMARY_WEBBROWSER = 2;

    @AccessedByNative
    public static final int PROCESS_MODEL_SHARED_SECONDARY_PROCESS = 0;
    @AccessedByNative
    public static final int PROCESS_MODEL_MULTIPLE_SECONDARY_PROCESSES = 1;

    @CalledByNative
    // @SWKPrivate
    public SWKProcessPool() {
        nativeCreate();
    }

    @CalledByNative
    // @SWKPrivate
    public SWKProcessPool(String injectedBundlePath) {
        nativeCreateWithInjectedBundlePath(injectedBundlePath);
    }

    @CalledByNative
    // @SWKPrivate
    public SWKProcessPool(SWKProcessPoolConfiguration configuration) {
        nativeCreateWithConfiguration(configuration);
    }

    @AbstractNativeMethod
    public native void setCacheModel(int cacheModel);

    /**
     * Set the maximum number of web processes.
     *
     * As a default, there is no limitation to launch web processes.
     *
     * @note Can only be called when there are no processes running.
     */
    @AbstractNativeMethod
    public native void setMaximumNumberOfProcesses(int maximumNumberOfProcesses);

    @AbstractNativeMethod
    // @SWKPrivate
    public native void warmInitialProcess();

    @AbstractNativeMethod
    public native void setDownloadDelegate(SWKDownloadDelegate downloadDelegate);

    @AbstractNativeMethod
    public native void setGeolocationProvider(
            SWKGeolocationProvider geolocationProvider);

    @AbstractNativeMethod
    public native void setNotificationProvider(
            SWKNotificationProvider notificationProvider);

    @AbstractNativeMethod
    @Deprecated
    public native SWKApplicationCacheManager getApplicationCacheManager();

    @AbstractNativeMethod
    @Deprecated
    public native SWKCookieManager getCookieManager();

    @AbstractNativeMethod
    @Deprecated
    public native SWKIconDatabase getIconDatabase();

    @AbstractNativeMethod
    @Deprecated
    public native void setIconDatabaseEnabled(boolean enable);

    @AbstractNativeMethod
    @Deprecated
    public native SWKKeyValueStorageManager getKeyValueStorageManager();

    @AbstractNativeMethod
    @Deprecated
    public native SWKResourceCacheManager getResourceCacheManager();

    @AbstractNativeMethod
    @Deprecated
    public native SWKVisitedLinkStore getVisitedLinkStore();

    @NativeObjectField
    private int mNativeClass;

    @Override
    protected void finalize() {
        nativeDestroy();
    }

    @NativeConstructor
    private native void nativeCreate();
    @NativeConstructor
    private native void nativeCreateWithInjectedBundlePath(String injectedBundlePath);
    @NativeConstructor
    private native void nativeCreateWithConfiguration(SWKProcessPoolConfiguration configuration);
    @NativeDestructor
    private native void nativeDestroy();
}
