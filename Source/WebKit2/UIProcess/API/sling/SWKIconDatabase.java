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

package labs.naver.webkit;

import labs.naver.onig.AbstractNativeMethod;
import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeConstructor;
import labs.naver.onig.NativeDestructor;
import labs.naver.onig.NativeNamespace;
import labs.naver.onig.NativeObjectField;
import labs.naver.webkit.clutter.WebBitmap;

@Deprecated
@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class SWKIconDatabase {

    @NativeObjectField
    private int mNativeClass;

    @CalledByNative
    private SWKIconDatabase() {
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
    
    @AbstractNativeMethod
    public native void retainIconForPageURL(String pageURL);
    @AbstractNativeMethod
    public native void releaseIconForPageURL(String pageURL);
    @AbstractNativeMethod
    public native void setIconURLForPageURL(String iconURL, String pageURL);
    @AbstractNativeMethod
    public native void setIconDataForIconURL(WebBitmap iconData, String iconURL);
    @AbstractNativeMethod
    public native void setIconDatabaseDelegate(SWKIconDatabaseDelegate delegate);
    @AbstractNativeMethod
    public native byte[] getIconDataForPageURL(String pageURL);
    @AbstractNativeMethod
    public native void removeAllIcons();
}
