package labs.naver.webkit;

import labs.naver.onig.AbstractNativeMethod;
import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeConstructor;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeDestructor;
import labs.naver.onig.NativeNamespace;
import labs.naver.onig.NativeObjectField;

import java.util.Vector;

@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class SWKOpenPanelResultListener {
    /**
     * Sets the files chosen by the user.
     */
    @AbstractNativeMethod
    public native void chooseFiles(Vector<String> files);

    /**
     * Cancels the file chooser request.
     */
    @AbstractNativeMethod
    public native void cancel();

    /**
     * Sets the directory chosen by the user.
     */
    @AbstractNativeMethod
    public native void chooseDirectories(Vector<String> directories);

    /**
     * Queries the list of accepted MIME types.
     *
     * Possible MIME types are:
     * - "audio\/\*": All sound files are accepted
     * - "video\/\*": All video files are accepted
     * - "image\/\*": All image files are accepted
     * - standard IANA MIME type (see http://www.iana.org/assignments/media-types/ for a complete list)
     *
     * @return The list of accepted MIME types. The list items are guaranteed to be stringshared.
     * The caller needs to free the list and its items after use
     */
    @AbstractNativeMethod
    public native Vector<String> getAcceptMIMETypes();

    @AbstractNativeMethod
    public native Vector<String> getSelectedFileNames();

    @AbstractNativeMethod
    public native boolean allowsDirectoryUpload();

    private boolean mAllowMultipleFiles;

    public boolean isAllowedMultipleFiles() {
        return mAllowMultipleFiles;
    }

    @NativeObjectField
    private int mNativeInstance;

    @CalledByNative
    SWKOpenPanelResultListener(boolean allowMultipleFiles) {
        mAllowMultipleFiles = allowMultipleFiles;
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
