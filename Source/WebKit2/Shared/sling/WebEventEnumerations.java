package labs.naver.webkit.api;

import labs.naver.onig.AccessedByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeNamespace;

@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class WebEventEnumerations {
    // These constants should be matched with those in UIEvent.java.
    @AccessedByNative
    public static final int SOURCE_UNKNOWN = 0;
    @AccessedByNative
    public static final int SOURCE_MOUSE = 1;
    @AccessedByNative
    public static final int SOURCE_WHEEL = 2;
    @AccessedByNative
    public static final int SOURCE_TOUCH = 3;
    @AccessedByNative
    public static final int SOURCE_KEY = 4;

    @AccessedByNative
    public static final int ACTION_NONE = 0;
    @AccessedByNative
    public static final int ACTION_CANCEL = 1;
    @AccessedByNative
    public static final int ACTION_DOWN = 2;
    @AccessedByNative
    public static final int ACTION_UP = 3;
    @AccessedByNative
    public static final int ACTION_PRESS = 4;
    @AccessedByNative
    public static final int ACTION_MOVE = 5;
    @AccessedByNative
    public static final int ACTION_ENTER = 6;
    @AccessedByNative
    public static final int ACTION_LEAVE = 7;
    @AccessedByNative
    public static final int ACTION_AWAY = 8;

    @AccessedByNative
    public static final int MODIFIER_ALT_KEY = 1; // 1 << 0
    @AccessedByNative
    public static final int MODIFIER_CTRL_KEY = 2; // 1 << 1
    @AccessedByNative
    public static final int MODIFIER_SHIFT_KEY = 4; // 1 << 2;
    @AccessedByNative
    public static final int MODIFIER_LEFT_BUTTON = 8; // 1 << 3;
    @AccessedByNative
    public static final int MODIFIER_RIGHT_BUTTON = 16; // 1 << 4;
    @AccessedByNative
    public static final int MODIFIER_MIDDLE_BUTTON = 32; // 1 << 5;

}
