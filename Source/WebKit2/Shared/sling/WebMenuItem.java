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

package labs.naver.webkit.clutter;

import labs.naver.onig.AccessedByNative;
import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeNamespace;

@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
@SuppressWarnings("unused")
public class WebMenuItem {
    // WebKit2/shared/WebPopupItem.h: enum Type
    @AccessedByNative
    public static final int ITEM_TYPE_SEPARATOR = 0;
    @AccessedByNative
    public static final int ITEM_TYPE_ITEM = 1;

    // WebKit2/Shared/WebPopupItem.h : enum TextDirection
    @AccessedByNative
    public static final int ITEM_TEXT_DIRECTION_RTL = 0;
    @AccessedByNative
    public static final int ITEM_TEXT_DIRECTION_LTR = 1;

    private final int mType;
    private final String mText;
    private final int mTextDirection;
    private final boolean mHasTextDirectionOverride;
    private final String mToolTip;
    private final String mAccessibilityText;
    private final boolean mIsEnabled;
    private final boolean mIsLabel;
    private final boolean mIsSelected;

    @CalledByNative
    private WebMenuItem(int type, String text, int direction,
            boolean hasTextDirectionOverride, String toolTip,
            String accessibilityText, boolean isEnabled, boolean isLabel,
            boolean isSelected) {
        mType = type;
        mText = text;
        mTextDirection = direction;
        mHasTextDirectionOverride = hasTextDirectionOverride;
        mToolTip = toolTip;
        mAccessibilityText = accessibilityText;
        mIsEnabled = isEnabled;
        mIsLabel = isLabel;
        mIsSelected = isSelected;
    }
}
