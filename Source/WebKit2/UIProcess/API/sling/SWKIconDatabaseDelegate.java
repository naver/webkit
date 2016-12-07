package labs.naver.webkit;

import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeNamespace;

@Deprecated
@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class SWKIconDatabaseDelegate {

    @CalledByNative
    public void didChangeIconForPageURL(SWKIconDatabase iconDatabase, String pageURL) {
    }
    
    @CalledByNative
    public void didRemoveAllIcons(SWKIconDatabase iconDatabase) {
    }
    
    @CalledByNative
    public void iconDataReadyForPageURL(SWKIconDatabase iconDatabase, String pageURL) {
    }
}
