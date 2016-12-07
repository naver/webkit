package labs.naver.webkit.clutter;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.math.BigInteger;
import java.security.DigestInputStream;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

import labs.naver.webkit.PlatformBridge;


import android.content.res.AssetManager;

public class WebKitResourcesManager {
    public static String fileHash(InputStream in, String algorithm)
            throws IOException {
        try {
            MessageDigest digest = MessageDigest.getInstance(algorithm);
            digest.reset();

            DigestInputStream digestInputStream = new DigestInputStream(in,
                    digest);

            byte[] buffer = new byte[8192];
            while ((digestInputStream.read(buffer)) != -1) {
            }

            byte[] hash = digest.digest();
            return new BigInteger(1, hash).toString(16);
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }

    private static int sAssetsCopied;
    private static int sAssetsSkippedCopying;

    public static boolean copyAssets(AssetManager assetManager,
            String fromAssetPath, String toPath) {
        sAssetsCopied = 0;
        sAssetsSkippedCopying = 0;
        boolean ok = copyAsset(assetManager, fromAssetPath, toPath);
        PlatformBridge.LOG("Copied " + sAssetsCopied + " asset file(s), skipped "
                + sAssetsSkippedCopying + " asset file(s).");
        return ok;
    }

    private static boolean copyAssetFolder(AssetManager assetManager,
            String fromAssetPath, String toPath) {
        try {
            String[] files = assetManager.list(fromAssetPath);
            new File(toPath).mkdirs();
            boolean res = true;
            for (String file : files) {
                String sourcePath = fromAssetPath + "/" + file;
                res &= copyAsset(assetManager, sourcePath, toPath + "/"
                        + file);
            }
            return res;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    private static boolean copyAsset(AssetManager assetManager,
            String fromAssetPath, String toPath) {
        InputStream in = null;
        OutputStream out = null;
        try {
            in = assetManager.open(fromAssetPath);
        } catch (IOException e) {
            return copyAssetFolder(assetManager, fromAssetPath, toPath);
        }

        try {
            File outFile = new File(toPath);
            if (outFile.exists()) {
                InputStream exist = new FileInputStream(toPath);
                if (fileHash(in, "MD5").equals(fileHash(exist, "MD5"))) {
                    sAssetsSkippedCopying++;
                    exist.close();
                    return true;
                }
                exist.close();
            }
            outFile.createNewFile();
            out = new FileOutputStream(toPath);
            copyFile(in, out);
            in.close();
            in = null;
            out.flush();
            out.close();
            out = null;
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    private static void copyFile(InputStream in, OutputStream out)
            throws IOException {
        sAssetsCopied++;
        byte[] buffer = new byte[1024];
        int read;
        while ((read = in.read(buffer)) != -1) {
            out.write(buffer, 0, read);
        }
    }
}
