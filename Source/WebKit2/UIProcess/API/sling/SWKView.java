package labs.naver.webkit.api;

import android.content.res.Configuration;
import android.graphics.Point;
import android.graphics.Rect;
import android.graphics.RectF;
import android.util.Log;

import labs.naver.onig.AbstractNativeMethod;
import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeConstructor;
import labs.naver.onig.NativeDestructor;
import labs.naver.onig.NativeNamespace;
import labs.naver.onig.NativeObjectField;
import labs.naver.view.ContentView;
import labs.naver.view.MotionDetector.Settings;
import labs.naver.view.UIEvent;
import labs.naver.webkit.clutter.WebBitmap;

@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class SWKView {
    public static final String TAG = "SWKView";

    private SWKWebContent mWebContent;
    private ContentView mView;

    public void onAttachedToView(ContentView view) {
        mView = view;

        setIntrinsicDeviceScaleFactor(view.deviceScaleFactor());
        nativeSetInWindow(true);
    }

    public void onDetachedFromView() {
        mView = null;

        nativeSetInWindow(false);
    }

    public void onVisibilityChanged(boolean visible) {
        nativeSetVisible(visible);
    }

    public void onFocusChanged(boolean focus) {
        nativeSetFocus(focus);
    }

    private int mWidth;
    private int mHeight;

    public void onLayout(int width, int height) {
        if (width == mWidth && height == mHeight)
            return;

        mWidth = width;
        mHeight = height;

        nativeLayoutChanged(mWidth, mHeight);
    }

    public void onConfigurationChanged(Configuration config) {
    }

    @AbstractNativeMethod
    public native void onPause();

    @AbstractNativeMethod
    public native void onResume();

    private boolean mDisableMotionDetection;
    private boolean mEnableMouseTouchEvents;

    public void setMotionDetectionDisabled(boolean disable) {
        if (disable == mDisableMotionDetection)
            return;

        mDisableMotionDetection = disable;

        mView.motionSettingsChanged();
    }

    public boolean getMotionDetectionDisabled() {
        return mDisableMotionDetection;
    }

    public void setMouseTouchEventsEnabled(boolean enable) {
        if (enable == mEnableMouseTouchEvents)
            return;

        mEnableMouseTouchEvents = enable;

        mView.motionSettingsChanged();
    }

    public boolean getMouseTouchEventsEnabled() {
        return mEnableMouseTouchEvents;
    }

    public Settings getMotionSettings() {
        // TODO Auto-generated method stub
        Settings settings = new Settings();
        settings.disableDetection = getMotionDetectionDisabled();
        settings.canHandlePinchBy = true;
        settings.mouseTouchEvents = getMouseTouchEventsEnabled();
        return settings;
    }

    @AbstractNativeMethod
    public native void setActive(boolean active);

    @AbstractNativeMethod
    public native void sendSingleTap(float x, float y);

    @AbstractNativeMethod
    public native void sendSingleTapUnconfirmed(float x, float y);

    @AbstractNativeMethod
    public native void sendDoubleTap(float x, float y);

    @AbstractNativeMethod
    public native void sendLongTap(float x, float y);

    @AbstractNativeMethod
    public native void sendShowPressState(float x, float y);

    @AbstractNativeMethod
    public native void sendShowPressCancel(float x, float y);

    @AbstractNativeMethod
    public native void sendLongPress(float x, float y);

    @AbstractNativeMethod
    public native void sendTouchEvent(long timestamp, int action,
            int modifiers, float x, float y, float globalX, float globalY,
            int id);

    @AbstractNativeMethod
    public native void sendMouseEvent(long timestamp, int action,
            int modifiers, float x, float y, float globalX, float globalY,
            int clickCount);

    @AbstractNativeMethod
    public native void sendWheelEvent(long timestamp, int action,
            int modifiers, float deltaX, float deltaY, float x, float y,
            float globalX, float globalY);

    @AbstractNativeMethod
    public native void sendKeyEvent(long timestamp, int action, int modifiers,
            int windowsVirtualKeyCode, int nativeVirtualKeyCode, String text,
            String unmodifiedText, boolean isAutoRepeat, boolean isSystemKey,
            boolean isKeypadKey, int strokeHash);

    public boolean sendGenericEvent(UIEvent event) {
        return false;
    }

    @CalledByNative
    @AbstractNativeMethod
    public int getWidth() {
        return mWidth;
    }

    @CalledByNative
    @AbstractNativeMethod
    public int getHeight() {
        return mHeight;
    }

    private int mContentWidth;
    private int mContentHeight;

    public int getContentWidth() {
        return mContentWidth;
    }

    public int getContentHeight() {
        return mContentHeight;
    }

    private float mMinimumScale = 0.5f;
    private float mMaximumScale = 4.0f;

    public float getScale() {
        return getPageScaleFactor();
    }

    public float getMinimumScale() {
        return mMinimumScale;
    }

    public float getMaximumScale() {
        return mMaximumScale;
    }

    // @SWKPrivate
    @AbstractNativeMethod
    public native void setOverrideDeviceScaleFactor(float overrideDeviceScaleFactor);

    // @SWKPrivate
    @AbstractNativeMethod
    public native float getOverrideDeviceScaleFactor();

    private float contentsToScreen(float value) {
        return value * getEffectiveScale();
    }

    private float screenToContents(float value) {
        return value / getEffectiveScale();
    }

    @AbstractNativeMethod
    public native void setBackgroundColor(int color);

    @AbstractNativeMethod
    public native int getBackgroundColor();

    @AbstractNativeMethod
    public native void setUseFixedLayout(boolean use);

    @AbstractNativeMethod
    public native boolean getUseFixedLayout();

    public void awakenScrollbars() {

    }

    @AbstractNativeMethod
    public native void scrollBegin(float x, float y);

    @AbstractNativeMethod
    public native boolean scrollBy(float deltaX, float deltaY, boolean isOverScrollAllowed);

    @AbstractNativeMethod
    public native boolean scrollTo(float x, float y);

    @AbstractNativeMethod
    public native void scrollEnd(float x, float y);

    public boolean canPinchBy() {
        return true;
    }

    @AbstractNativeMethod
    public native void pinchBegin(float x, float y);

    public void pinchTo(RectF rect) {
        // TODO: Pinch to zoom using new viewport coordinates(Not used).
    }

    public void pinchBy(float x, float y, float deltaScale) {
        adjustTransientZoom(x, y, deltaScale);
    }

    public void pinchEnd() {
        commitTransientZoom();
    }

    @AbstractNativeMethod
    private native void adjustTransientZoom(float x, float y, float deltaScale);

    @AbstractNativeMethod
    private native void commitTransientZoom();

    private float mViewportX;
    private float mViewportY;

    public RectF getViewport() {
        float viewportWidth = screenToContents(mWidth);
        float viewportHeight = screenToContents(mHeight);
        return new RectF(mViewportX, mViewportX + viewportWidth, mViewportY,
                mViewportY + viewportHeight);
    }

    private void scrollPositionChanged(float x, float y) {
    }

    public void invalidate() {
    }

    public void invalidate(Rect rect) {
    }

    @AbstractNativeMethod
    public native boolean requestExitFullScreen();

    @AbstractNativeMethod
    public native boolean isVisible();

    @AbstractNativeMethod
    public native boolean isFocused();

    @AbstractNativeMethod
    public native boolean isActive();

    @CalledByNative
    @AbstractNativeMethod
    private void didChangeContentsPosition(int cssX, int cssY) {
        mViewportX = contentsToScreen(cssX);
        mViewportY = contentsToScreen(cssY);

        awakenScrollbars();
    }

    @CalledByNative
    @AbstractNativeMethod
    private void didChangeContentsSize(int width, int height) {
        mContentWidth = width;
        mContentHeight = height;
    }

    @CalledByNative
    @AbstractNativeMethod
    private void didChangeViewportAttributes(float minimumScale, float maximumScale,
            float scale) {
        mMinimumScale = minimumScale;
        mMaximumScale = maximumScale;

        // FIXME : x, y arguments should be calculated correctly. Refer to ViewGestureController.mm endMagnificationGesture().
        setPageScaleFactor(scale, 0, 0);
    }

    @CalledByNative
    @AbstractNativeMethod
    private void setViewNeedsDisplay(int x, int y, int width, int height) {
        mView.contentInvalidated();
    }

    @CalledByNative
    @AbstractNativeMethod
    private void hasTouchEventHandlers(boolean hasTouchHandlers) {
    }

    @CalledByNative
    @AbstractNativeMethod
    private void doneWithTouchEvent(boolean wasEventHandled) {
    }

    @CalledByNative
    @AbstractNativeMethod
    private void didChangeCursor(int cursorType) {
    }

    @CalledByNative
    @AbstractNativeMethod
    private void didChangeCursor(int hotSpotX, int hotSpotY, WebBitmap dragImage) {
    }

    @CalledByNative
    @AbstractNativeMethod
    private void didChangeTooltip(String tooltip) {
    }

    private boolean mHasInputMethod = false;

    @CalledByNative
    @AbstractNativeMethod
    private void startInputMethod(boolean isInPasswordField) {
        if (mHasInputMethod)
            return;

        mHasInputMethod = mView.startInputMethod();
    }

    @CalledByNative
    @AbstractNativeMethod
    private void endInputMethod() {
        if (!mHasInputMethod)
            return;

        mHasInputMethod = false;

        mView.endInputMethod();
    }

    @CalledByNative
    @AbstractNativeMethod
    private void editorStateChanged(String text, int selectionStart,
            int selectionEnd, int compositionStart, int compositionEnd) {
        if (!mHasInputMethod)
            return;

        mView.editableStateChanged(text, selectionStart, selectionEnd,
                compositionStart, compositionEnd);
    }

    @CalledByNative
    @AbstractNativeMethod
    private void enterFullScreen() {
        Log.d(TAG, "enterFullScreen");
    }

    @CalledByNative
    @AbstractNativeMethod
    private void exitFullScreen() {
        Log.d(TAG, "exitFullScreen");
    }

    @CalledByNative
    @AbstractNativeMethod
    void didPerformDragControllerAction(long dragOperation, boolean mouseIsOverFileInput, int numberOfItemsToBeAccepted) {
    }

    @CalledByNative
    @AbstractNativeMethod
    private void setDragImage(int x, int y, WebBitmap dragImage, boolean isLinkDrag) {
    }

    @CalledByNative
    @AbstractNativeMethod
    private void setPromisedData(String pasteboardName, byte[] imageBuffer, String filename, String extension,
        String title, String url, String visibleUrl) {
    }

    @CalledByNative
    @AbstractNativeMethod
    private boolean isSpeaking() {
        return false;
    }

    @CalledByNative
    @AbstractNativeMethod
    private void speak(String string) {
    }

    @CalledByNative
    @AbstractNativeMethod
    private void stopSpeaking() {
    }

    @CalledByNative
    @AbstractNativeMethod
    private void webProcessCrashed(String url) {
        setViewNeedsDisplay(0, 0, mWidth, mHeight);
    }

    @AbstractNativeMethod
    private native void setPageScaleFactor(float scale, int x, int y);

    @AbstractNativeMethod
    private native float getPageScaleFactor();

    @AbstractNativeMethod
    private native void setIntrinsicDeviceScaleFactor(float scale);
    
    @AbstractNativeMethod
    private native float getIntrinsicDeviceScaleFactor();

    private float getEffectiveScale() {
        return getPageScaleFactor() * getIntrinsicDeviceScaleFactor();     
    }

    @CalledByNative
    @AbstractNativeMethod
    private long nativeWindowHandle() {
        return 0;
    }

    @NativeObjectField
    private int mNativePtr;

    @CalledByNative
    public SWKView(SWKWebContent webContent) {
        nativeCreate(webContent);
    }

    @Override
    protected void finalize() {
        nativeDestroy();
    }

    @NativeConstructor
    private native void nativeCreate(SWKWebContent webContent);
    @NativeDestructor
    private native void nativeDestroy();

    @AbstractNativeMethod
    private native void nativeSetInWindow(boolean inWindow);
    @AbstractNativeMethod
    private native void nativeSetVisible(boolean visible);
    @AbstractNativeMethod
    private native void nativeSetFocus(boolean focus);
    @AbstractNativeMethod
    private native void nativeLayoutChanged(int width, int height);
    @AbstractNativeMethod
    private native void nativeDisplayLocationChanged(int x, int y);
}
