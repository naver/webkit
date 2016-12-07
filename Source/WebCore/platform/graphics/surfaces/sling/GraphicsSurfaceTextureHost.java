package labs.naver.webkit.clutter;

import labs.naver.onig.AbstractNativeMethod;
import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeNamespace;

@NativeNamespace("WebKit")
@NativeClassExport("WEBCORE_EXPORT")
public class GraphicsSurfaceTextureHost {
    @CalledByNative
    public GraphicsSurfaceTextureHost(long eglConfig, int shareIdentifier) {
    }

    @CalledByNative
    @AbstractNativeMethod
    public void swapBuffers() {
    }

    @CalledByNative
    @AbstractNativeMethod
    public long getGLTexture() {
        return 0;
    }
}
