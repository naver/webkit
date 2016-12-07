package labs.naver.webkit.clutter;

import labs.naver.onig.AbstractNativeMethod;
import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeNamespace;
import labs.naver.webkit.PlatformBridge;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.ParcelFileDescriptor;
import android.os.RemoteException;
import android.util.SparseArray;

@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class WebKitServiceRunner {
    private static SparseArray<String> mRunningServices = new SparseArray<String>();
    private static SparseArray<Connection> mServiceConnections = new SparseArray<Connection>();

    public class Connection implements ServiceConnection {
        @Override
        public void onServiceConnected(ComponentName className, IBinder service) {
            // This is called when the connection with the service has been
            // established, giving us the service object we can use to
            // interact with the service. We are communicating with our
            // service through an IDL interface, so get a client-side
            // representation of that from the raw service object.
            mService = IWebKitService.Stub.asInterface(service);

            // We want to monitor the service for as long as we are
            // connected to it.
            try {
                Bundle bundle = new Bundle();
                bundle.putString("processType", mProcessType);
                bundle.putParcelable("clientIdentifier", ParcelFileDescriptor
                        .adoptFd(Integer.parseInt(mClientIdentifier)));
                if (mService.setRunOptions(bundle)) {
                    int servicePid = mService.getPid();
                    PlatformBridge.getContext().startService(mServiceIntent);
                    mRunningServices.put(servicePid, className.getClassName());
                    mServiceConnections.put(servicePid, this);
                    mConnectionCallback.onConnected(className, servicePid);
                } else {
                    mConnectionCallback.onConnectFailed(className);
                }
            } catch (RemoteException e) {
                // In this case the service has crashed before we could even
                // do anything with it; we can count on soon being
                // disconnected (and then reconnected if it can be
                // restarted)
                // so there is no need to do anything here.
            }
        }

        @Override
        public void onServiceDisconnected(ComponentName className) {
            PlatformBridge.LOG("Service " + className.getClassName() + " crashed!");

            // This is called when the connection with the service has been
            // unexpectedly disconnected -- that is, its process crashed.
            mService = null;
            // We have to restart the service manually.
            unbindService();

            int indexOfService = mRunningServices.indexOfValue(className
                    .getClassName());
            int servicePid = mRunningServices.keyAt(indexOfService);
            mRunningServices.removeAt(indexOfService);
            mServiceConnections.remove(servicePid);
            mConnectionCallback.onDisconnected(className);
        }

        /** The primary interface we will be calling on the service. */
        private IWebKitService mService;

        private Intent mServiceIntent;
        private String mProcessType;
        private String mClientIdentifier;

        private ConnectionCallback mConnectionCallback;

        private Connection(Intent intent, String processType,
                String clientIdentifier, ConnectionCallback connectionCallback) {
            mServiceIntent = intent;
            mProcessType = processType;
            mClientIdentifier = clientIdentifier;
            mConnectionCallback = connectionCallback;
        }

        boolean bindService() {
            return PlatformBridge.getContext().bindService(mServiceIntent, this,
                    Context.BIND_AUTO_CREATE);
        }

        public boolean unbindService() {
            PlatformBridge.getContext().unbindService(this);
            return PlatformBridge.getContext().stopService(mServiceIntent);
        }
    };

    public interface ConnectionCallback {
        void onConnected(ComponentName className, int pid);

        void onConnectFailed(ComponentName className);

        void onDisconnected(ComponentName className);
    }

    private static Intent createServiceIntent(String processType) {
        Intent intent = new Intent();
        intent.setAction(IWebKitService.class.getName());
        // FIXME: Provide multiple service classes which can be used for WebProcess.
        intent.setClassName(PlatformBridge.getContext(), processType
                .equals("webprocess") ? WebKitServiceWebProcess.class.getName()
                : WebKitServiceNetworkProcess.class.getName());
        intent.setPackage(PlatformBridge.getContext().getPackageName());
        return intent;
    }

    private Connection mServiceConnection;

    boolean connect(String processType, String clientIdentifier,
            ConnectionCallback connectionCallback) {
        // Establish a couple connections with the service, binding
        // by interface names. This allows other applications to be
        // installed that replace the remote service by implementing
        // the same interface.
        mServiceConnection = (new Connection(createServiceIntent(processType), processType,
                clientIdentifier, connectionCallback));
        return mServiceConnection.bindService();
    }

    public static boolean isConnectedToService(int servicePid) {
        return mServiceConnections.get(servicePid) != null;
    }

    public static Connection getConnection(int servicePid) {
        return mServiceConnections.get(servicePid);
    }

    @CalledByNative
    @AbstractNativeMethod
    @SuppressWarnings("unused")
    private static boolean isProcessDisconnected(int pid) {
        return !isConnectedToService(pid);
    }

    @CalledByNative
    @AbstractNativeMethod
    @SuppressWarnings("unused")
    private static void unbindProcess(int pid) {
        getConnection(pid).unbindService();
    }
}
