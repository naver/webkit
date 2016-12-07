package labs.naver.webkit;

import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeConstructor;
import labs.naver.onig.NativeDestructor;
import labs.naver.onig.NativeNamespace;
import labs.naver.onig.NativeObjectField;

@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class SWKSecurityOrigin {
    private final String mProtocol;
    private final String mHost;
    private final int mPort;

    @NativeObjectField
    private int mNativeClass;

    @CalledByNative
    private SWKSecurityOrigin(String protocol, String host, int port) {
        mProtocol = protocol;
        mHost = host;
        mPort = port;

        nativeCreate();
    }

    @Override
    protected void finalize() {
        nativeDestroy();
    }

    public String getProtocol() {
        return mProtocol;
    }

    public String getHost() {
        return mHost;
    }

    public int getPort() {
        return mPort;
    }

    @NativeConstructor
    private native void nativeCreate();
    @NativeDestructor
    private native void nativeDestroy();
}
