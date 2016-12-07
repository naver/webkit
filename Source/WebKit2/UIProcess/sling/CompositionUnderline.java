package labs.naver.webkit;

import labs.naver.onig.AccessedByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeNamespace;
import labs.naver.view.CompositionClause;

@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class CompositionUnderline {
    @AccessedByNative
    public int mStartOffset = 0;
    @AccessedByNative
    public int mEndOffset = 0;
    @AccessedByNative
    public int mColor = 0;
    @AccessedByNative
    public boolean mFocus = false;

    public CompositionUnderline(CompositionClause clause) {
        mStartOffset = clause.mStartOffset;
        mEndOffset = clause.mEndOffset;
        mColor = clause.mColor;
        mFocus = clause.mFocus;
    }
}
