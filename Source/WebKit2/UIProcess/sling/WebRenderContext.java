package labs.naver.webkit.view;

import javax.microedition.khronos.opengles.GL10;

import labs.naver.view.RenderContext;
import labs.naver.webkit.WebRenderer;
import labs.naver.webkit.api.SWKView;
import labs.naver.webkit.wtf.WTFMainThread;

public class WebRenderContext implements RenderContext {

    @Override
    public void beginPaint(GL10 gl) {
        WTFMainThread.initializeUIWorkerThread();
        mRenderer.beginPaint();
    }

    @Override
    public void paint(GL10 gl) {
        mRenderer.paint();
    }

    @Override
    public void endPaint(GL10 gl) {
        mRenderer.endPaint();
    }

    @Override
    public void contextLost(GL10 gl) {
        mRenderer.contextLost();
    }

    private WebRenderer mRenderer;

    public WebRenderContext(SWKView view) {
        mRenderer = new WebRenderer(view);
    }
}
