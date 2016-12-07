package labs.naver.webkit.wtf;

import java.util.concurrent.atomic.AtomicBoolean;

import android.os.Handler;
import android.os.Message;

import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeConstructor;
import labs.naver.onig.NativeDestructor;
import labs.naver.onig.NativeNamespace;
import labs.naver.onig.NativeObjectField;

@NativeNamespace("WTF")
@NativeClassExport("WTF_EXPORT_PRIVATE")
class ThreadLoopBackend {
    private static final boolean DEBUG = false;

    private AtomicBoolean mMessageFired = new AtomicBoolean(true);

    @CalledByNative
    private void dispatch() {
        if (!mMessageFired.getAndSet(false)) {
            // mMessageFired was already false.
            return;
        }
        mHandler.sendEmptyMessage(0);
    }

    @CalledByNative
    private void dispatchTimer(int timerID, double nextFireIntervalInMillis) {
        long nextFireInterval = (long) nextFireIntervalInMillis;
        mHandler.sendEmptyMessageDelayed(timerID, nextFireInterval);
    }

    @CalledByNative
    private void removeTimer(int timerID) {
        mHandler.removeMessages(timerID);
    }

    @CalledByNative
    private void stop() {
        mHandler.getLooper().quit();
    }

    private Handler mHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            if (msg.what == 0) {
                mMessageFired.set(true);
                nativePerformMessage();
            } else {
                nativePerformTimer(msg.what);
            }
        }
    };

    @NativeObjectField
    private int mNativePtr;

    @CalledByNative
    private ThreadLoopBackend() {
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

    private native void nativePerformMessage();
    private native void nativePerformTimer(int timerID);
}
