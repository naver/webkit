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

package labs.naver.webkit;

import labs.naver.onig.AbstractNativeMethod;
import labs.naver.onig.AccessedByNative;
import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeConstructor;
import labs.naver.onig.NativeDestructor;
import labs.naver.onig.NativeNamespace;
import labs.naver.onig.NativeObjectField;

import java.util.Vector;

@Deprecated
@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class SWKContextMenuItem {

    // WebCore/platform/ContextMenuItem.h: enum ContextMenuItemType
    @AccessedByNative
    public static final int ACTION_TYPE = 0;
    @AccessedByNative
    public static final int CHECKABLE_ACTION_TYPE = 1;
    @AccessedByNative
    public static final int SEPARATOR_TYPE = 2;
    @AccessedByNative
    public static final int SUBMENU_TYPE = 3;

    // WebCore/platform/ContextMenuItem.h: enum ContextMenuAction
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_NO_ACTION = 0;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_OPEN_LINK_IN_NEW_WINDOW = 1;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_DOWNLOAD_LINK_TO_DISK = 2;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_COPY_LINK_TO_CLIPBOARD = 3;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_OPEN_IMAGE_IN_NEW_WINDOW = 4;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_DOWNLOAD_IMAGE_TO_DISK = 5;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_COPY_IMAGE_TO_CLIPBOARD = 6;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_COPY_IMAGE_URL_TO_CLIPBOARD = 7;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_OPEN_FRAME_IN_NEW_WINDOW = 8;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_COPY = 9;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_GO_BACK = 10;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_GO_FORWARD = 11;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_STOP = 12;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_RELOAD = 13;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_CUT = 14;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_PASTE = 15;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_SPELLING_GUESS = 16;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_NO_GUESSES_FOUND = 17;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_IGNORE_SPELLING = 18;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_LEARN_SPELLING = 19;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_OTHER = 20;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_SEARCH_IN_SPOTLIGHT = 21;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_SEARCH_WEB = 22;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_LOOK_UP_IN_DICTIONARY = 23;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_OPEN_WITH_DEFAULT_APPLICATION = 24;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_PDF_ACTUAL_SIZE = 25;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_PDF_ZOOM_IN = 26;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_PDF_ZOOM_OUT = 27;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_PDF_AUTO_SIZE = 28;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_PDF_SINGLE_PAGE = 29;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_PDF_FACING_PAGES = 30;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_PDF_CONTINUOUS = 31;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_PDF_NEXT_PAGE = 32;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_PDF_PREVIOUS_PAGE = 33;
    // These are new tags! Not a part of API!!!!
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_OPEN_LINK = 2000;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_IGNORE_GRAMMAR = 2001;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_SPELLING_MENU = 2002; // Spelling or Spelling/Grammar sub-menu
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_SHOW_SPELLING_PANEL = 2003;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_CHECK_SPELLING = 2004;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_CHECK_SPELLING_WHILE_TYPING = 2005;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_CHECK_GRAMMAR_WITH_SPELLING = 2006;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_FONT_MENU = 2007; // Font sub-menu
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_SHOW_FONTS = 2008;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_BOLD = 2009;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_ITALIC = 2010;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_UNDERLINE = 2011;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_OUTLINE = 2012;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_STYLES = 2013;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_SHOW_COLORS = 2014;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_SPEECH_MENU = 2015; // Speech sub-menu
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_START_SPEAKING = 2016;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_STOP_SPEAKING = 2017;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_WRITING_DIRECTION_MENU = 2018; // Writing Direction sub-menu
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_DEFAULT_DIRECTION = 2019;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_LEFT_TO_RIGHT = 2020;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_RIGHT_TO_LEFT = 2021;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_PDF_SINGLE_PAGE_SCROLLING = 2022;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_PDF_FACING_PAGES_SCROLLING = 2023;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_INSPECT_ELEMENT = 2024; // if ENABLE(INSPECTOR)
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_TEXT_DIRECTION_MENU = 2025; // Text Direction sub-menu
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_TEXT_DIRECTION_DEFAULT = 2026;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_TEXT_DIRECTION_LEFT_TO_RIGHT = 2027;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_TEXT_DIRECTION_RIGHT_TO_LEFT = 2028;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_OPEN_MEDIA_IN_NEW_WINDOW = 2029;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_DOWNLOAD_MEDIA_TO_DISK = 2030;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_COPY_MEDIA_LINK_TO_CLIPBOARD = 2031;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_TOGGLE_MEDIA_CONTROLS = 2032;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_TOGGLE_MEDIA_LOOP = 2033;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_ENTER_VIDEO_FULLSCREEN = 2034;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_MEDIA_PLAY_PAUSE = 2035;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_MEDIA_MUTE = 2036;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_DICTATION_ALTERNATIVE = 2037;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_OPEN_LINK_IN_THIS_WINDOW = 2038;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_TAG_TOGGLE_VIDEO_FULLSCREEN = 2039;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_BASE_CUSTOM_TAG = 5000;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_CUSTOM_TAG_NO_ACTION = 5998;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_LAST_CUSTOM_TAG = 5999;
    @AccessedByNative
    public static final int CONTEXT_MENU_ITEM_BASE_APPLICATION_TAG = 10000;

    @NativeObjectField
    private int mNativeInstance;

    @CalledByNative
    public SWKContextMenuItem() {
        nativeCreate();
    }

    @CalledByNative
    public SWKContextMenuItem(int type, int action, String title, boolean enabled, boolean checked) {
        nativeCreateWithArgs(type, action, title, enabled, checked);
    }

    @Override
    protected void finalize() {
        nativeDestroy();
    }

    @NativeConstructor
    private native void nativeCreate();
    @NativeConstructor
    private native void nativeCreateWithArgs(int type, int action, String title, boolean enabled, boolean checked);
    @NativeDestructor
    private native void nativeDestroy();

    @AbstractNativeMethod
    public native int getType();
    @AbstractNativeMethod
    public native int getAction();
    @AbstractNativeMethod
    public native String getTitle();
    @AbstractNativeMethod
    public native boolean isEnabled();
    @AbstractNativeMethod
    public native boolean isChecked();
    @AbstractNativeMethod
    public native Vector<SWKContextMenuItem> getSubmenu();
}
