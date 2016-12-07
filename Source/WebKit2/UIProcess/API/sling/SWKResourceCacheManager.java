package labs.naver.webkit;

import labs.naver.onig.AbstractNativeMethod;
import labs.naver.onig.AccessedByNative;
import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeConstructor;
import labs.naver.onig.NativeDestructor;
import labs.naver.onig.NativeNamespace;
import labs.naver.onig.NativeObjectField;
import labs.naver.webkit.api.ValueCallback;

@Deprecated
@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class SWKResourceCacheManager {

    // WebKit2/Shared/ResourceCachesToClear.h
    @AccessedByNative
    public static final int ALL_RESOURCE_CACHES = 0;
    @AccessedByNative
    public static final int IN_MEMORY_RESOURCE_CACHES_ONLY = 1;

    // WebKit2/Shared/android/ResourceCachePolicy.h
    @AccessedByNative
    public static final int DEFAULT_CACHE = 0;
    @AccessedByNative
    public static final int DO_NOT_VERIFY_CACHE = 1;
    @AccessedByNative
    public static final int DISABLE_CACHE = 2;
    @AccessedByNative
    public static final int USE_CACHE_ONLY = 3;

    @AbstractNativeMethod
    public native void getCacheOrigins(ValueCallback<String> callback);
    @AbstractNativeMethod
    public native void clearCacheForOrigin(String protocol, String host, int port, int resourceCachesToClear);
    @AbstractNativeMethod
    public native void clearCacheForAllOrigins(int resourceCachesToClear);
    @AbstractNativeMethod
    public native void setCachePolicy(int resourceCachePolicy);
    @AbstractNativeMethod
    public native int getCachePolicy();
    
    @NativeObjectField
    private int mNativeClass;

    @CalledByNative
    public SWKResourceCacheManager() {
        nativeCreate();
    }
    
    @Override
    protected void finalize() {
        nativeDestroy();
    }
    
    @NativeConstructor
    private native void nativeCreate();
    @NativeDestructor
    private native void nativeDestroy();
}
