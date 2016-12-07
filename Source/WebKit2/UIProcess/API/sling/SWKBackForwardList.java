package labs.naver.webkit.api;

import java.util.Vector;

import labs.naver.onig.AbstractNativeMethod;
import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeConstructor;
import labs.naver.onig.NativeDestructor;
import labs.naver.onig.NativeNamespace;
import labs.naver.onig.NativeObjectField;

@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class SWKBackForwardList {

    /**
     * The current item.
     */
    @AbstractNativeMethod
    public native SWKBackForwardListItem getCurrentItem();

    /**
     * The item immediately preceding the current item, or nil
     * if there isn't one.
     */
    @AbstractNativeMethod
    public native SWKBackForwardListItem getBackItem();

    /**
     * The item immediately following the current item, or nil if
     * there isn't one.
     */
    @AbstractNativeMethod
    public native SWKBackForwardListItem getForwardItem();

    /**
     * Returns the item at a specified distance from the current
     * item.
     *
     * @param index Index of the desired list item relative to the current item:
     * 0 for the current item, -1 for the immediately preceding item, 1 for the
     * immediately following item, and so on.
     *
     * @result The item at the specified distance from the current item, or nil
     * if the index parameter exceeds the limits of the list.
     */
    @AbstractNativeMethod
    public native SWKBackForwardListItem getItemAtIndex(int index);

    /**
     * The portion of the list preceding the current item.
     *
     * @discussion The items are in the order in which they were originally
     * visited.
     */
    public Vector<SWKBackForwardListItem> getBackList() {
        return null;
    }

    @Deprecated
    @AbstractNativeMethod
    public native int getBackListCount();

    /**
     * The portion of the list following the current item.
     *
     * @discussion The items are in the order in which they were originally
     * visited.
     */
    public Vector<SWKBackForwardListItem> getForwardList() {
        return null;
    }

    @Deprecated
    @AbstractNativeMethod
    public native int getForwardListCount();

    // @SWKPrivate
    public void removeAllItems() {
    }

    // Removes all items except the current one.
    // @SWKPrivate
    @AbstractNativeMethod
    public native void clear();

    @NativeObjectField
    private int mNativeInstance;

    @CalledByNative
    SWKBackForwardList() {
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
