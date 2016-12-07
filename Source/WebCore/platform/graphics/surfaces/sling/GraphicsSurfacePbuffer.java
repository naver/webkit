package labs.naver.webkit.clutter;

import labs.naver.onig.AbstractNativeMethod;
import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeNamespace;

@NativeNamespace("WebKit")
@NativeClassExport("WEBCORE_EXPORT")
public class GraphicsSurfacePbuffer {
    @CalledByNative
    public GraphicsSurfacePbuffer(long eglDisplay, long eglConfig,
            long eglShareContext, int surfaceWidth, int surfaceHeight) {
    }

    @CalledByNative
    @AbstractNativeMethod
    public boolean makeCurrent() {
        return false;
    }

    @CalledByNative
    @AbstractNativeMethod
    public boolean doneCurrent() {
        return false;
    }

    @CalledByNative
    @AbstractNativeMethod
    public int getShareIdentifier() {
        return 0;
    }

    @CalledByNative
    @AbstractNativeMethod
    public void publishSurface() {
    }

    @CalledByNative
    @AbstractNativeMethod
    public boolean copyFromTexture(int texture, boolean flip) {
        return false;
    }

    @CalledByNative
    @AbstractNativeMethod
    public void reset(long eglShareContext, int surfaceWidth, int surfaceHeight) {
    }
}
