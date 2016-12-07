package labs.naver.webkit.api;

import labs.naver.onig.AccessedByNative;
import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeNamespace;

@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class ValueCallback<T extends Object> {

    // Followed from CallbackBase::Error.
    @AccessedByNative
    public static final int ERROR_NONE = 0;
    @AccessedByNative
    public static final int ERROR_UNKNOWN = 1;
    @AccessedByNative
    public static final int ERROR_PROCESS_EXITED = 2;
    @AccessedByNative
    public static final int ERROR_OWNER_WAS_INVALIDATED = 3;

    public void onReceiveValue(T value) {
        assert false;
    }

    @CalledByNative
    private void onReceiveError(int error) {
    }

    @SuppressWarnings("unused")
    @CalledByNative
    private void onReceiveBoolean(boolean value) {
        onReceiveObject(Boolean.valueOf(value));
    }

    @SuppressWarnings("unused")
    @CalledByNative
    private void onReceiveByte(byte value) {
        onReceiveObject(Byte.valueOf(value));
    }

    @SuppressWarnings("unused")
    @CalledByNative
    private void onReceiveShort(short value) {
        onReceiveObject(Short.valueOf(value));
    }

    @SuppressWarnings("unused")
    @CalledByNative
    private void onReceiveInt(int value) {
        onReceiveObject(Integer.valueOf(value));
    }

    @SuppressWarnings("unused")
    @CalledByNative
    private void onReceiveLong(long value) {
        onReceiveObject(Long.valueOf(value));
    }

    @SuppressWarnings("unused")
    @CalledByNative
    private void onReceiveFloat(float value) {
        onReceiveObject(Float.valueOf(value));
    }

    @SuppressWarnings("unused")
    @CalledByNative
    private void onReceiveDouble(double value) {
        onReceiveObject(Double.valueOf(value));
    }

    @SuppressWarnings("unchecked")
    @CalledByNative
    private void onReceiveObject(Object value) {
        onReceiveValue((T) value);
    }

    @SuppressWarnings("unused")
    @CalledByNative
    private void onReceiveString(String value) {
        onReceiveObject(value);
    }
}
