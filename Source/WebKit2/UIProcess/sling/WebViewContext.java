package labs.naver.webkit.view;

import android.annotation.SuppressLint;
import android.content.res.Configuration;
import android.graphics.Rect;
import android.graphics.RectF;
import android.view.View;

import labs.naver.view.ContentView;
import labs.naver.view.EditableContext;
import labs.naver.view.MotionDetector.Settings;
import labs.naver.view.RenderContext;
import labs.naver.view.UIEvent;
import labs.naver.view.ViewContext;
import labs.naver.webkit.api.SWKView;

public class WebViewContext implements ViewContext {

    @Override
    public void attached(ContentView contentView) {
        mView.onAttachedToView(contentView);
    }

    @Override
    public void detached() {
        mView.onDetachedFromView();
    }

    @Override
    public void setVisible(int visibility) {
        mView.onVisibilityChanged(visibility == View.VISIBLE);
    }

    @Override
    public void setFocus(boolean focus) {
        mView.onFocusChanged(focus);
    }

    @Override
    public void setActive(boolean active) {
        mView.setActive(active);
    }

    @Override
    public boolean isVisible() {
        return mView.isVisible();
    }

    @Override
    public boolean isFocused() {
        return mView.isFocused();
    }

    @Override
    public boolean isActive() {
        return mView.isActive();
    }

    @SuppressLint("WrongCall")
    @Override
    public void layout(int width, int height) {
        mView.onLayout(width, height);
    }

    @Override
    public void onConfigurationChanged(Configuration config) {
        mView.onConfigurationChanged(config);
    }

    @Override
    public void pause() {
        mView.onPause();
    }

    @Override
    public void resume() {
        mView.onResume();
    }

    @Override
    public Settings motionSettings() {
        return mView.getMotionSettings();
    }

    @Override
    public void sendSingleTap(float x, float y) {
        mView.sendSingleTap(x, y);
    }

    @Override
    public void sendDoubleTap(float x, float y) {
        mView.sendDoubleTap(x, y);
    }

    @Override
    public boolean sendGenericEvent(UIEvent event) {
        return mView.sendGenericEvent(event);
    }

    @Override
    public EditableContext editable() {
        return new WebEditableContext(mView);
    }

    @Override
    public int width() {
        return mView.getWidth();
    }

    @Override
    public int height() {
        return mView.getHeight();
    }

    @Override
    public int contentWidth() {
        return mView.getContentWidth();
    }

    @Override
    public int contentHeight() {
        return mView.getContentHeight();
    }

    @Override
    public float currentScale() {
        return mView.getScale();
    }

    @Override
    public float minimumScale() {
        return mView.getMinimumScale();
    }

    @Override
    public float maximumScale() {
        return mView.getMaximumScale();
    }

    @Override
    public void scrollBegin(float x, float y) {
        mView.scrollBegin(x, y);
    }

    @Override
    public boolean scrollBy(float deltaX, float deltaY) {
        return mView.scrollBy(deltaX, deltaY, true);
    }

    @Override
    public boolean scrollTo(float x, float y) {
        return mView.scrollTo(x, y);
    }

    @Override
    public void scrollEnd(float x, float y) {
        mView.scrollEnd(x, y);
    }

    @Override
    public void pinchBegin(float x, float y) {
        mView.pinchBegin(x, y);
    }

    @Override
    public void pinchTo(RectF rect) {
        mView.pinchTo(rect);
    }

    @Override
    public void pinchBy(float x, float y, float deltaScale) {
        mView.pinchBy(x, y, deltaScale);
    }

    @Override
    public void pinchEnd() {
        mView.pinchEnd();
    }

    @Override
    public RectF viewport() {
        return mView.getViewport();
    }

    @Override
    public void invalidate() {
        mView.invalidate();
    }

    @Override
    public void invalidate(Rect rect) {
        mView.invalidate(rect);
    }

    @Override
    public RenderContext renderer() {
        if (mRenderer == null)
            mRenderer = new WebRenderContext(mView);

        return mRenderer;
    }

    private final SWKView mView;
    private RenderContext mRenderer;

    public WebViewContext(SWKView view) {
        mView = view;
    }
}
