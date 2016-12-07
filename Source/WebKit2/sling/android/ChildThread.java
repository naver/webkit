package labs.naver.sling;

import android.os.Looper;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ChildThread extends Thread {
    private final Lock mChildThreadMutex = new ReentrantLock();
    private final Condition mChildThreadWaitCondition = mChildThreadMutex.newCondition();
    private final boolean mRunMessageLoop;
    private final Runnable mThreadEntry;

    public ChildThread(Runnable threadEntry, String name, int priority, boolean runMessageLoop) {
        super(name);
        mThreadEntry = threadEntry;
        setPriority(priority);
        mRunMessageLoop = runMessageLoop;
    }

    @Override
    public synchronized void start() {
        mChildThreadMutex.lock();
        super.start();
        try {
            mChildThreadWaitCondition.await();
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } finally {
            mChildThreadMutex.unlock();
        }
    }

    @Override
    public void run() {
        if (mRunMessageLoop)
            Looper.prepare();
        
        mChildThreadMutex.lock();
        mThreadEntry.run();
        mChildThreadWaitCondition.signal();
        mChildThreadMutex.unlock();
        
        if (mRunMessageLoop)
            Looper.loop();
    }
}
