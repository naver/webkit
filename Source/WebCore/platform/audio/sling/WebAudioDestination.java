package labs.naver.webkit.clutter;

import labs.naver.onig.AbstractNativeMethod;
import labs.naver.onig.AccessedByNative;
import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeConstructor;
import labs.naver.onig.NativeDestructor;
import labs.naver.onig.NativeNamespace;
import labs.naver.onig.NativeObjectField;

@NativeNamespace("WebKit")
@NativeClassExport("WEBCORE_EXPORT")
public class WebAudioDestination {
    @AccessedByNative
    public static final int DESTINATION_DISPOSITION_DEFAULT = 0;
    @AccessedByNative
    public static final int DESTINATION_DISPOSITION_EMBED = 1;
    @AccessedByNative
    public static final int DESTINATION_DISPOSITION_REMOTE = 2;

    @CalledByNative
    public WebAudioDestination(int destinationDisposition) {
    }

    @CalledByNative
    @AbstractNativeMethod
    public boolean start() {
        return false;
    }

    @CalledByNative
    @AbstractNativeMethod
    public boolean stop() {
        return false;
    }

    @CalledByNative
    @AbstractNativeMethod
    public void setSampleRate(float sampleRate) {
    }

    @CalledByNative
    @AbstractNativeMethod
    public void render(float[] audioData, long sizeInFloats) {
    }

    @CalledByNative
    @AbstractNativeMethod
    static public float audioHardwareSampleRate() {
        return 44100;
    }

    @CalledByNative
    @AbstractNativeMethod
    static public int audioHardwareOutputChannels() {
        return 2;
    }

    @NativeObjectField
    private int mNativeClass;

    @Override
    protected void finalize() {
        nativeDestroy();
    }

    @NativeConstructor
    private native void nativeCreate();
    @NativeDestructor
    private native void nativeDestroy();

    private native void audioDestinationRender(long numberOfFrames);
}
