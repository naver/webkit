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

import java.util.Vector;

/**
 * A SWKUserStyleSheet object represents a script that can be injected into
 * webpages.
 */
@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class SWKUserStyleSheet {
    @AccessedByNative
    public static final int INJECTION_IN_ALL_FRAMES = 0;
    @AccessedByNative
    public static final int INJECTION_IN_TOP_FRAME_ONLY = 1;

    @AccessedByNative
    public static final int USER_STYLE_USER_LEVEL = 0;
    @AccessedByNative
    public static final int USER_STYLE_AUTHOR_LEVEL = 1;

    @CalledByNative
    public SWKUserStyleSheet() {
        nativeCreate();
    }

    @CalledByNative
    public SWKUserStyleSheet(String source, Vector<?> whitelist, Vector<?> blacklist,
            int injectedFrames, int level) {
        nativeCreateWithSource(source, whitelist, blacklist, injectedFrames,
                level);
    }

    @AbstractNativeMethod
    public native String getSource();

    @AbstractNativeMethod
    public native String getUrl();

    @AbstractNativeMethod
    public native Vector<?> getBlacklist();

    @AbstractNativeMethod
    public native Vector<?> getWhitelist();

    @AbstractNativeMethod
    public native int getInjectedFrames();

    @AbstractNativeMethod
    public native int getLevel();

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
    @NativeConstructor
    private native void nativeCreateWithSource(String source, Vector<?> whitelist,
            Vector<?> blacklist, int injectedFrames, int level);
    @NativeDestructor
    private native void nativeDestroy();
}
