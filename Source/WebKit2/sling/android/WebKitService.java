/*
 * Copyright (C) 2007 The SWK Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package labs.naver.webkit.clutter;

import android.app.Service;
import android.content.Intent;
import android.content.res.Configuration;
import android.os.Bundle;
import android.os.IBinder;
import android.os.ParcelFileDescriptor;
import android.os.Process;
import android.os.RemoteException;
import labs.naver.sling.ChildThread;
import labs.naver.webkit.PlatformBridge;

public class WebKitService extends Service {
    static {
        System.loadLibrary("WebKit2");
    }

    @Override
    public void onCreate() {
        PlatformBridge.LOG("WebKitService.onCreate");
        PlatformBridge.setContext(this);
    }

    @Override
    public void onDestroy() {
        PlatformBridge.LOG("WebKitService.onDestroy");

        Process.killProcess(android.os.Process.myPid());
    }

    private String mProcessType;
    private String mClientIdentifier;

    @Override
    public IBinder onBind(Intent intent) {
        if (IWebKitService.class.getName().equals(intent.getAction())) {
            PlatformBridge.LOG("WebKitService.onBind : IWebKitService");
            return mBinder;
        }
        PlatformBridge.LOG("null");
        return null;
    }

    @Override
    public boolean onUnbind(Intent intent) {
        PlatformBridge.LOG("WebKitService.onUnbind");
        this.stopSelf();
        return false;
    }

    @Override
    public void onRebind(Intent intent) {
        PlatformBridge.LOG("WebKitService.onRebind");
        super.onRebind(intent);
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        PlatformBridge.LOG("WebKitService.onConfigurationChanged");
        super.onConfigurationChanged(newConfig);
    }

    @Override
    public void onLowMemory() {
        PlatformBridge.LOG("WebKitService.onLowMemory");
        super.onLowMemory();
    }

    @Override
    public void onTrimMemory(int level) {
        PlatformBridge.LOG("WebKitService.onTrimMemory");
        super.onTrimMemory(level);
    }

    @Override
    public void onTaskRemoved(Intent rootIntent) {
        PlatformBridge.LOG("WebKitService.onTaskRemoved");
    }

    private Thread mProcessMainThread;

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        PlatformBridge.LOG("WebKitService.onStartCommand : processType=" + mProcessType
                + ", clientIdentifier=" + mClientIdentifier);

        if (mProcessType == null) {
            PlatformBridge.LOG("WebKitService.onStartCommand : this service is relaunched by system unintentionally. So stop it.");
            stopSelf();
            return START_NOT_STICKY;
        }

        mProcessMainThread = new ChildThread(new Runnable() {
            @Override
            public void run() {
                ChildProcessLauncher.threadRunWebKitMain(mProcessType,
                        mClientIdentifier);
            }
        }, mProcessType, Thread.NORM_PRIORITY, true);
        mProcessMainThread.start();
        return START_NOT_STICKY;
    }

    /**
     * The IRemoteInterface is defined through IDL
     */
    private final IWebKitService.Stub mBinder = new IWebKitService.Stub() {
        @Override
        public boolean setRunOptions(Bundle bundle) throws RemoteException {
            // TODO Auto-generated method stub
            String processType = bundle.getString("processType");
            if (processType == null)
                return false;

            ParcelFileDescriptor clientIdentifier = bundle
                    .getParcelable("clientIdentifier");
            if (clientIdentifier == null)
                return false;

            mProcessType = processType;
            mClientIdentifier = Integer.toString(clientIdentifier.detachFd());
            return true;
        }

        @Override
        public String getProcessType() {
            return mProcessType;
        }

        @Override
        public int getPid() {
            return Process.myPid();
        }
    };
}
