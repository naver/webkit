package labs.naver.webkit;

import java.util.Vector;

import android.graphics.Rect;
import labs.naver.onig.AbstractNativeMethod;
import labs.naver.onig.AccessedByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeConstructor;
import labs.naver.onig.NativeDestructor;
import labs.naver.onig.NativeNamespace;
import labs.naver.onig.NativeObjectField;
import labs.naver.webkit.api.SWKView;

@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class WebEditable {

    @AccessedByNative
    public static final int EDITOR_ACTION_UNSPECIFIED = 0;
    @AccessedByNative
    public static final int EDITOR_ACTION_NONE = 1;
    @AccessedByNative
    public static final int EDITOR_ACTION_GO = 2;
    @AccessedByNative
    public static final int EDITOR_ACTION_SEARCH = 3;
    @AccessedByNative
    public static final int EDITOR_ACTION_SEND = 4;
    @AccessedByNative
    public static final int EDITOR_ACTION_NEXT = 5;
    @AccessedByNative
    public static final int EDITOR_ACTION_DONE = 6;
    @AccessedByNative
    public static final int EDITOR_ACTION_PREVIOUS = 7;

    @AbstractNativeMethod
    public native Rect editableCaretRectAtStart();
    @AbstractNativeMethod
    public native Rect editableCaretRectAtEnd();
    @AbstractNativeMethod
    public native String editableSelectionText();
    @AbstractNativeMethod
    public native String editableTextBeforeCaret(int length);
    @AbstractNativeMethod
    public native String editableTextAfterCaret(int length);

    @AbstractNativeMethod
    public native boolean setComposition(String text,
            Vector<CompositionUnderline> underlines, int selectionStart,
            int selectionEnd, int replacementStart, int replacementEnd);
    @AbstractNativeMethod
    public native boolean confirmComposition(String text);
    @AbstractNativeMethod
    public native boolean finishComposition();
    @AbstractNativeMethod
    public native void cancelComposition();

    @AbstractNativeMethod
    public native boolean performEditorAction(int editorAction);

    @AbstractNativeMethod
    public native boolean sendKeyEvent(long timestamp, int action,
            int modifiers, int virtualKeyCode, int nativeKeyCode, String text,
            String unmodifiedText, boolean isAutoRepeat, boolean isSystemKey,
            boolean isKeypadKey, int strokeHash);

    @NativeObjectField
    private int mNativePtr;

    public WebEditable(SWKView view) {
        nativeCreate(view);
    }

    @Override
    protected void finalize() {
        nativeDestroy();
    }

    @NativeConstructor
    private native void nativeCreate(SWKView view);
    @NativeDestructor
    private native void nativeDestroy();
}
