package labs.naver.webkit.wtf;

import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeNamespace;

@NativeNamespace("WTF")
@NativeClassExport("WTF_EXPORT_PRIVATE")
public class WTFMainThread {
    public static native void initializeUIThread();

    public static native void initializeUIWorkerThread();

    public static native boolean isMainThread();

    public static native boolean isWebThread();

    public static native boolean isUIThread();

    private WTFMainThread() {
        // Static class, do not instantiate.
    }
}
