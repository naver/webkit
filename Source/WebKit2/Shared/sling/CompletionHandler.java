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
import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeConstructor;
import labs.naver.onig.NativeDestructor;
import labs.naver.onig.NativeNamespace;
import labs.naver.onig.NativeObjectField;

/**
 * A callback class to be invoked by Java side.
 */
@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public final class CompletionHandler<T extends Object> {
    /**
     * Invoke when the value is available.
     * @param value The value.
     */
    @AbstractNativeMethod
    public void invoke() {
        nativeInvoke(null);
    }

    /**
     * Invoke when the value is available.
     * @param value The value.
     */
    @AbstractNativeMethod
    public void invoke(boolean value) {
        nativeInvoke(Boolean.valueOf(value));
    }

    /**
     * Invoke when the value is available.
     * @param value The value.
     */
    @AbstractNativeMethod
    public void invoke(int value) {
        nativeInvoke(Integer.valueOf(value));
    }

    /**
     * Invoke when the value is available.
     * @param value The value.
     */
    @AbstractNativeMethod
    public void invoke(long value) {
        nativeInvoke(Long.valueOf(value));
    }

    /**
     * Invoke when the value is available.
     * @param value The value.
     */
    @AbstractNativeMethod
    private void invoke(String value) {
        nativeInvoke(value);
    }

    /**
     * Invoke when the value is available.
     * @param value The value.
     */
    @AbstractNativeMethod
    public void invoke(T value) {
        nativeInvoke(value);
    }

    /**
     * Invoke when the value is available.
     * @param value The value.
     */
    @AbstractNativeMethod
    private native void nativeInvoke(Object value);

    @NativeObjectField
    private int mNativePtr;

    @CalledByNative
    private CompletionHandler(String typeName) {
        nativeCreate(typeName);
    }

    @Override
    protected void finalize() {
        nativeDestroy();
    }

    @NativeConstructor
    private native void nativeCreate(String typeName);
    @NativeDestructor
    private native void nativeDestroy();
}
