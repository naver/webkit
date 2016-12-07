/*
 * Copyright (C) 2010 The SWK Open Source Project
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

package labs.naver.webkit;

import java.util.Vector;

import android.content.Context;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.res.Resources;
import android.graphics.Point;
import android.util.DisplayMetrics;
import android.util.Log;

import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeNamespace;
import labs.naver.webkit.clutter.WebKitResourcesManager;

@NativeNamespace("WebKit")
@NativeClassExport("WEBCORE_EXPORT")
public class PlatformBridge {
    private PlatformBridge() {} // Utility class, do not instantiate.

    public static void LOG(String message) {
        Log.d("WEBKIT_DEBUG",
                Thread.currentThread().getStackTrace()[3].getMethodName()
                        + ": " + message);
    }

    public static void LOGE(String message) {
        Log.e("WEBKIT_DEBUG",
                Thread.currentThread().getStackTrace()[3].getMethodName()
                        + ": " + message);
    }

    private static String sFilesDirectory;
    private static String sVersionName;
    private static Context sContext;

    private static void checkInitialized() {
        if (sContext == null)
            throw new IllegalStateException(
                    "Call CookieSyncManager::createInstance() or create a webview before using this class");
    }

    private static void initialize() {
        if (!WebKitResourcesManager.copyAssets(sContext.getAssets(),
                "inspector", getApplicationDirectoryPath() + "/WebKit.resources/WebInspectorUI"))
            LOGE("Error while try copying assets to application files directory");

        if (!WebKitResourcesManager.copyAssets(sContext.getAssets(),
                "fonts", getApplicationDirectoryPath() + "/fonts"))
            LOGE("Error while try copying font assets to application files directory");
    }

    public static synchronized void setContext(Context context) {
        if (sContext != null)
            return;
        sContext = context.getApplicationContext();
        initialize();
    }

    public static synchronized Context getContext() {
        return sContext;
    }

    @CalledByNative
    private static synchronized String getPackageName() {
        checkInitialized();
        return sContext.getPackageName();
    }

    @SuppressWarnings("unused")
    @CalledByNative
    private static synchronized String getVersionName() {
        checkInitialized();
        if (sVersionName == null) {
            try {
                sVersionName = sContext.getPackageManager().getPackageInfo(getPackageName(), 0).versionName;
            } catch (NameNotFoundException e) {
                e.printStackTrace();
            }
        }
        return sVersionName;
    }

    // Device
    @SuppressWarnings("unused")
    @CalledByNative
    private static Point screenSize() {
        // FIXME: it should return physical size.
        return availableScreenSize();
    }

    @CalledByNative
    private static Point availableScreenSize() {
        DisplayMetrics metrics = Resources.getSystem().getDisplayMetrics();
        return new Point(metrics.widthPixels, metrics.heightPixels);
    }

    @SuppressWarnings("unused")
    @CalledByNative
    private static int screenDepth() {
        return 32;
    }

    @SuppressWarnings("unused")
    @CalledByNative
    private static boolean screenIsMonochrome() {
        return false;
    }

    @CalledByNative
    private static synchronized String getApplicationDirectoryPath() {
        checkInitialized();
        if (sFilesDirectory == null)
            sFilesDirectory = sContext.getFilesDir().getPath();
        return sFilesDirectory;
    }

    @SuppressWarnings("unused")
    @CalledByNative
    private static String getWebsiteDataDirectory() {
        // FIXME: Need to implement
        return getApplicationDirectoryPath();
    }

    @SuppressWarnings("unused")
    @CalledByNative
    private static String resolveFilePathForContentUri(String contentUri) {
        return "";
    }

    // Inspector
    private static final String WEBKIT_INSPECTOR_SERVER = "127.0.0.1:2999";

    @SuppressWarnings("unused")
    @CalledByNative
    private static synchronized String getInspectorServerAddress() {
        checkInitialized();
        return WEBKIT_INSPECTOR_SERVER;
    }

    // Language
    @SuppressWarnings("unused")
    @CalledByNative
    private static String computeDefaultLanguage() {
        return "en";
    }

    // KeyGenerator
    @SuppressWarnings("unused")
    @CalledByNative
    private static Vector<String> getSupportedKeyStrengthList() {
        return new Vector<String>();
    }

    @SuppressWarnings("unused")
    @CalledByNative
    private static String getSignedPublicKeyAndChallengeString(int index, String challenge, String url) {
        return "";
    }

    // Injected Bundle
    @SuppressWarnings("unused")
    @CalledByNative
    private static String getDefaultInjectedBundlePath() {
        return "";
    }

    // Web Inspector
    @SuppressWarnings("unused")
    @CalledByNative
    private static String getDefaultWebInspectorPath() {
        return "";
    }

    @SuppressWarnings("unused")
    @CalledByNative
    private static String getPlatformVersionForUserAgent() {
        // FIXME: Need to implement
        return "Android 5.0; SM-G900P Build/LRX21T";
    }

    @SuppressWarnings("unused")
    @CalledByNative
    private static Vector<String> getSupportedMediaMimeTypeList() {
        return new Vector<String>();
    }
}
