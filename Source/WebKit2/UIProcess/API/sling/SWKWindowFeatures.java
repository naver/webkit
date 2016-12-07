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
import labs.naver.onig.NativeNamespace;

/**
 * SWKWindowFeatures specifies optional attributes for the containing window
 * when a new SWKWebContent is requested.
 */
@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class SWKWindowFeatures {
    /**
     * Whether the menu bar should be visible. null if menu bar visibility was
     * not specified.
     */
    @AbstractNativeMethod
    public boolean getMenuBarVisibility() {
        return mMenuBarVisible;
    }

    /**
     * Whether the status bar should be visible. null if status bar visibility
     * was not specified.
     */
    @AbstractNativeMethod
    public boolean getStatusBarVisibility() {
        return mStatusBarVisible;
    }

    /**
     * Whether toolbars should be visible. null if toolbar visibility was not
     * specified.
     */
    @AbstractNativeMethod
    public boolean getToolBarsVisibility() {
        return mToolBarsVisible;
    }

    /**
     * Whether the containing window should be resizable. null if resizability
     * was not specified.
     */
    @AbstractNativeMethod
    public boolean getAllowsResizing() {
        return mAllowResizing;
    }

    /**
     * The x coordinate of the containing window. null if the x coordinate was
     * not specified.
     */
    @AbstractNativeMethod
    public int getX() {
        return mX;
    }

    /**
     * The y coordinate of the containing window. null if the y coordinate was
     * not specified.
     */
    @AbstractNativeMethod
    public int getY() {
        return mY;
    }

    /**
     * The width coordinate of the containing window. null if the width was not
     * specified.
     */
    @AbstractNativeMethod
    public int getWidth() {
        return mWidth;
    }

    /**
     * The height coordinate of the containing window. null if the height was
     * not specified.
     */
    @AbstractNativeMethod
    public int getHeight() {
        return mHeight;
    }

    @CalledByNative
    private SWKWindowFeatures(int x, int y, int width, int height, boolean allowResizing,
            boolean menuBarVisible, boolean statusBarVisible, boolean toolBarsVisible) {
        mX = x;
        mY = y;
        mWidth = width;
        mHeight = height;
        mAllowResizing = allowResizing;
        mMenuBarVisible = menuBarVisible;
        mStatusBarVisible = statusBarVisible;
        mToolBarsVisible = toolBarsVisible;
    }

    private final int mX;
    private final int mY;
    private final int mWidth;
    private final int mHeight;
    private final boolean mAllowResizing;
    private final boolean mMenuBarVisible;
    private final boolean mStatusBarVisible;
    private final boolean mToolBarsVisible;
}
