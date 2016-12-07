package labs.naver.webkit;

import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeNamespace;

@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class SWKVibrationProvider {
    @CalledByNative
    public void vibrate(long durationInMs) {
    }

    @CalledByNative
    public void cancelVibration() {
    }
}
