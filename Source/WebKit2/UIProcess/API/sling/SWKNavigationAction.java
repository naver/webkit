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

package labs.naver.webkit.api;

import labs.naver.onig.AccessedByNative;
import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeConstructor;
import labs.naver.onig.NativeDestructor;
import labs.naver.onig.NativeNamespace;
import labs.naver.onig.NativeObjectField;
import labs.naver.webkit.SWKURLRequest;

@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class SWKNavigationAction {

    @AccessedByNative
    public static final int NAVIGATION_TYPE_LINK_NONE = -1;
    @AccessedByNative
    // A link with an href attribute was activated by the user.
    public static final int NAVIGATION_TYPE_LINK_CLICKED = 0;
    @AccessedByNative
    // A form was submitted.
    public static final int NAVIGATION_TYPE_FORM_SUBMITTED = 1;
    @AccessedByNative
    // An item from the back-forward list was requested.
    public static final int NAVIGATION_TYPE_BACK_FORWARD = 2;
    @AccessedByNative
    // The webpage was reloaded.
    public static final int NAVIGATION_TYPE_RELOAD = 3;
    @AccessedByNative
    // A form was resubmitted (for example by going back, going forward, or
    // reloading).
    public static final int NAVIGATION_TYPE_FORM_RESUBMITTED = 4;
    @AccessedByNative
    // Navigation is taking place for some other reason.
    public static final int NAVIGATION_TYPE_OTHER = 5;

    @AccessedByNative
    public static final int EVENT_MOUSE_BUTTON_NONE = -1;
    @AccessedByNative
    public static final int EVENT_MOUSE_BUTTON_LEFT = 0;
    @AccessedByNative
    public static final int EVENT_MOUSE_BUTTON_RIGHT = 1;
    @AccessedByNative
    public static final int EVENT_MOUSE_BUTTON_MIDDLE = 2;

    @AccessedByNative
    public static final int EVENT_MODIFIER_KEY_NONE = 0;
    @AccessedByNative
    public static final int EVENT_MODIFIER_KEY_SHIFT = 1; //(1 << 0)
    @AccessedByNative
    public static final int EVENT_MODIFIER_KEY_CTRL = 2; //(1 << 1)
    @AccessedByNative
    public static final int EVENT_MODIFIER_KEY_ALT = 4; //(1 << 2)
    @AccessedByNative
    public static final int EVENT_MODIFIER_KEY_META = 8; //(1 << 3)

    private int mNavigationType;
    private int mMouseButton;
    private int mModifiers;
    private SWKURLRequest mRequest;
    @Deprecated
    private String mFrameName;

    /**
     * Get the frame requesting the navigation.
     */
    public SWKFrameInfo getSourceFrame() {
        return null;
    }

    /**
     * Get the target frame, or nil if this is a new window navigation.
     */
    public SWKFrameInfo getTargetFrame() {
        return null;
    }

    /**
     * Get the type of action that triggered the navigation.
     *
     * @discussion The value is one of the constants of NAVIGATION_TYPE_XXX.
     */
    public int getNavigationType() {
        return mNavigationType;
    }

    /**
     * Get the navigation's request.
     */
    public SWKURLRequest getRequest() {
        return mRequest;
    }

    /**
     * Get the modifier keys that were in effect when the navigation was
     * requested.
     */
    public int getModifierFlags() {
        return mModifiers;
    }

    /**
     * Get the number of the mouse button causing the navigation to be
     * requested.
     *
     * @discussion The return value is one of constants of EVENT_MOUSE_BUTTON_XXX
     */
    public int getMouseButton() {
        return mMouseButton;
    }

    // @SWKPrivate
    public SWKURL getOriginalURL() {
        return null;
    }

    // @SWKPrivate
    public boolean isUserInitiated() {
        return false;
    }

    // @SWKPrivate
    public boolean canHandleRequest() {
        return false;
    }

    @Deprecated
    public int getModifiers() {
        return mModifiers;
    }

    @Deprecated
    public String getFrameName() {
        return mFrameName;
    }

    @NativeObjectField
    private int mNativeInstance;

    @CalledByNative
    private SWKNavigationAction(int navigationType, int mouseButton,
            int modifiers, SWKURLRequest request) {
        mNavigationType = navigationType;
        mMouseButton = mouseButton;
        mModifiers = modifiers;
        mRequest = request;

        nativeCreate();
    }

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
}
