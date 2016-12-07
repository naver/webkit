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

/**
 * A SWKUserScript object represents a script that can be injected into webpages.
 */
@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class SWKUserScript {
    /**
     * Inject the script after the document element has been created, but before
     * any other content has been loaded.
     */
    @AccessedByNative
    public static final int INJECTION_TIME_AT_DOCUMENT_START = 0;
    /**
     * Inject the script after the document has finished loading, but before any
     * subresources may have finished loading.
     */
    @AccessedByNative
    public static final int INJECTION_TIME_AT_DOCUMENT_END = 1;

    /**
     * Returns an initialized user script that can be added to a
     * SWKUserContentController.
     *
     * @param source The script source.
     * @param injectionTime When the script should be injected. Possible values
     *            are InjectionTimeAtDocumentStart and
     *            InjectionTimeAtDocumentEnd.
     * @param forMainFrameOnly Whether the script should be injected into all
     *            frames or just the main frame.
     */
    @CalledByNative
    public SWKUserScript(String source, int injectionTime,
            boolean forMainFrameOnly) {
        nativeCreate();
    }

    /**
     * Get the script source code.
     */
    @AbstractNativeMethod
    public native String getSource();

    /**
     * Get when the script should be injected.
     *
     * @return InjectionTimeAtDocumentStart or InjectionTimeAtDocumentEnd.
     */
    @AbstractNativeMethod
    public native int getInjectionTime();

    /**
     * Get whether the script should be injected into all frames or just the
     * main frame.
     */
    @AbstractNativeMethod
    public native boolean isForMainFrameOnly();

    @NativeObjectField
    private int mNativeClass;

    @NativeConstructor
    private native void nativeCreate();
    @NativeDestructor
    private native void nativeDestroy();
}
