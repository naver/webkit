package labs.naver.webkit.clutter;

import labs.naver.onig.AbstractNativeMethod;
import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeConstructor;
import labs.naver.onig.NativeDestructor;
import labs.naver.onig.NativeNamespace;
import labs.naver.onig.NativeObjectField;

@NativeNamespace("WebKit")
@NativeClassExport("WEBCORE_EXPORT")
public class WebAudioFileReader {
    @CalledByNative
    public WebAudioFileReader() {
    }

    @CalledByNative
    public WebAudioFileReader(String url) {
    }

    @CalledByNative
    @AbstractNativeMethod
    public int getChannelsPerFrame() {
        return 2;
    }

    @CalledByNative
    @AbstractNativeMethod
    public int getSampleRate() {
        return 44100;
    }

    @CalledByNative
    @AbstractNativeMethod
    public long getNumberOfFrames() {
        return getSampleRate() * getChannelsPerFrame() * 2;
    }

    @CalledByNative
    @AbstractNativeMethod
    public long writeInputData(char[] data, long length) {
        return 0;
    }

    @CalledByNative
    @AbstractNativeMethod
    public boolean prepare() {
        return true;
    }

    @CalledByNative
    @AbstractNativeMethod
    public void start() {
    }

    @CalledByNative
    @AbstractNativeMethod
    public void signalEndOfInputStream() {
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

    private native void audioFileRequestInputData(long offset, long length);
    private native void audioFileCompletion();
    private native void audioFileSampleAvailable(float[] data, long length);
}
