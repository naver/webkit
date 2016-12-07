package labs.naver.webkit.clutter;

import android.content.ComponentName;
import android.os.Process;

import labs.naver.onig.AccessedByNative;
import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeNamespace;
import labs.naver.sling.ChildThread;
import labs.naver.webkit.PlatformBridge;
import labs.naver.webkit.wtf.WTFMainThread;

@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class ChildProcessLauncher {
    @AccessedByNative
    private static final String PROCESS_STRATEGY_THREAD = "thread-strategy";
    @AccessedByNative
    private static final String PROCESS_STRATEGY_SERVICE = "service-strategy";
    @AccessedByNative
    private static final String PROCESS_STRATEGY_DEFAULT = "default-strategy";

    @AccessedByNative
    private static final String PROCESS_TYPE_WEB_PROCESS = "webprocess";
    @AccessedByNative
    private static final String PROCESS_TYPE_PLUGIN_PROCESS = "pluginprocess";
    @AccessedByNative
    private static final String PROCESS_TYPE_NETWORK_PROCESS = "networkprocess";
    @AccessedByNative
    private static final String PROCESS_TYPE_DATABASE_PROCESS = "databaseprocess";

    @AccessedByNative
    private static final int PROCESS_STRATEGY_ID_THREAD = 1;
    @AccessedByNative
    private static final int PROCESS_STRATEGY_ID_SERVICE = 2;
    @AccessedByNative
    private static final int PROCESS_STRATEGY_ID_DEFAULT = PROCESS_STRATEGY_ID_SERVICE;

    @CalledByNative
    private static boolean start(final int nativeHandle, final String commandLine) {
        String[] commandLineArguments = commandLine.split(new String("\\|"));

        final String processType = commandLineArguments[0];
        final String clientIdentifier = commandLineArguments[1];
        final String executablePath = commandLineArguments[2];

        if (!processType.equals(PROCESS_TYPE_WEB_PROCESS)
                && !processType.equals(PROCESS_TYPE_PLUGIN_PROCESS)
                && !processType.equals(PROCESS_TYPE_NETWORK_PROCESS)
                && !processType.equals(PROCESS_TYPE_DATABASE_PROCESS)) {
            PlatformBridge.LOGE("Error on request nonexistent process-type: "
                    + processType);
            assert false;
        }

        int processStrategy = 0;

        if (executablePath.equals(PROCESS_STRATEGY_DEFAULT)) {
            processStrategy = PROCESS_STRATEGY_ID_DEFAULT;
        } else if (executablePath.equals(PROCESS_STRATEGY_THREAD)) {
            processStrategy = PROCESS_STRATEGY_ID_THREAD;
        } else if (executablePath.equals(PROCESS_STRATEGY_SERVICE)) {
            processStrategy = PROCESS_STRATEGY_ID_SERVICE;
        }

        switch (processStrategy) {
        case PROCESS_STRATEGY_ID_THREAD:
            Runnable threadRunWebKitMainRunner = new Runnable() {
                @Override
                public void run() {
                    threadRunWebKitMain(processType, clientIdentifier);
                }
            };
            ChildThread thread = new ChildThread(threadRunWebKitMainRunner,
                    processType, Thread.NORM_PRIORITY, true);

            thread.start();

            nativeDidLaunchChildProcess(nativeHandle, Process.myPid());
            break;
        case PROCESS_STRATEGY_ID_SERVICE:
            WebKitServiceRunner.ConnectionCallback connectionCallback = new WebKitServiceRunner.ConnectionCallback() {
                @Override
                public void onConnected(ComponentName className, int pid) {
                    PlatformBridge.LOG("ChildProcessLauncher.onConnected: "
                            + className.getClassName() + " pid: " + pid);
                    nativeDidLaunchChildProcess(nativeHandle, pid);
                }

                @Override
                public void onConnectFailed(ComponentName className) {
                    PlatformBridge.LOGE("ChildProcessLauncher.onConnectFailed: "
                            + className.getClassName());
                }

                @Override
                public void onDisconnected(ComponentName className) {
                    PlatformBridge.LOGE("ChildProcessLauncher.onDisconnected: "
                            + className.getClassName());
                }
            };

            WebKitServiceRunner serviceRunner = new WebKitServiceRunner();

            if (!serviceRunner.connect(processType, clientIdentifier,
                    connectionCallback)) {
                PlatformBridge.LOG("failed to connect to WebKit service.");
                return false;
            }
            break;
        default:
            assert false;
            return false;
        }

        return true;
    }

    static void threadRunWebKitMain(String processType, String clientIdentifier) {
        threadRunWebKitMain(processType, clientIdentifier, "");
    }

    static void threadRunWebKitMain(String processType, String clientIdentifier, String extraInfo) {
        WTFMainThread.initializeUIThread(); // TODO: Try using native(non-UI) thread instead.
        nativeRunWebKitMain(processType, clientIdentifier, extraInfo);
    }

    private static native void nativeDidLaunchChildProcess(int nativeHandle, int pid);
    private static native int nativeRunWebKitMain(String processType, String clientIdentifier, String extraInfo);
}
