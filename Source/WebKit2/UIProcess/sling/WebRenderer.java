package labs.naver.webkit;

import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeConstructor;
import labs.naver.onig.NativeDestructor;
import labs.naver.onig.NativeNamespace;
import labs.naver.onig.NativeObjectField;
import labs.naver.webkit.api.SWKView;

@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class WebRenderer {

    public native void beginPaint();
    public native void paint();
    public native void endPaint();

    public native void contextLost();
    public native void teardown();

    @NativeObjectField
    private int mNativePtr;

    public WebRenderer(SWKView view) {
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
