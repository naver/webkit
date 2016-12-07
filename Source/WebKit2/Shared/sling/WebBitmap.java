/*
 * Copyright (C) 2016 Naver Corp. All rights reserved.
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
package labs.naver.webkit.clutter;

import android.graphics.Bitmap.Config;

import labs.naver.onig.AbstractNativeMethod;
import labs.naver.onig.AccessedByNative;
import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeNamespace;

@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class WebBitmap {
    @AccessedByNative
    public static final int CONFIG_ALPHA_8 = 1;
    @AccessedByNative
    public static final int CONFIG_RGB_565 = 3;
    @AccessedByNative
    public static final int CONFIG_ARGB_8888 = 5;

    private android.graphics.Bitmap mBitmap;
    private int mWidth;
    private int mHeight;

    @CalledByNative
    public WebBitmap(int[] colors, int width, int height, int config) {
        mWidth = width;
        mHeight = height;

        this.mBitmap = android.graphics.Bitmap.createBitmap(width, height,
                integerToConfig(config));
    }

    private static Config integerToConfig(int config) {
        switch (config) {
        case CONFIG_ALPHA_8:
            return Config.ALPHA_8;
        case CONFIG_RGB_565:
            return Config.RGB_565;
        case CONFIG_ARGB_8888:
            return Config.ARGB_8888;
        default:
            break;
        }
        throw new IllegalArgumentException("Bitmap config value is not proper");
    }

    @CalledByNative
    @AbstractNativeMethod
    public void setPixels(int[] pixels, int offset, int stride, int x, int y,
            int width, int height) {
    }

    @CalledByNative
    @AbstractNativeMethod
    public void getPixels(int[] pixels, int offset, int stride, int x, int y,
            int width, int height) {
    }

    @CalledByNative
    @AbstractNativeMethod
    public int getWidth() {
        return mWidth;
    }

    @CalledByNative
    @AbstractNativeMethod
    public int getHeight() {
        return mHeight;
    }

    @CalledByNative
    @AbstractNativeMethod
    public int getRowBytes() {
        return 0;
    }

    @CalledByNative
    @AbstractNativeMethod
    public int getByteCount() {
        return 0;
    }

    public android.graphics.Bitmap getBitmap() {
        return mBitmap;
    }
}
