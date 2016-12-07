package labs.naver.webkit.view;

import java.util.Vector;

import android.graphics.Rect;
import labs.naver.view.CompositionClause;
import labs.naver.view.EditableContext;
import labs.naver.view.UIEvent;
import labs.naver.webkit.CompositionUnderline;
import labs.naver.webkit.WebEditable;
import labs.naver.webkit.api.SWKView;

public class WebEditableContext implements EditableContext {

    @Override
    public Rect editableCaretRectAtStart() {
        return mEditable.editableCaretRectAtStart();
    }

    @Override
    public Rect editableCaretRectAtEnd() {
        return mEditable.editableCaretRectAtEnd();
    }

    @Override
    public String editableSelectionText() {
        return mEditable.editableSelectionText();
    }

    @Override
    public String editableTextBeforeCaret(int length) {
        return mEditable.editableTextBeforeCaret(length);
    }

    @Override
    public String editableTextAfterCaret(int length) {
        return mEditable.editableTextAfterCaret(length);
    }

    @Override
    public boolean setComposition(String text,
            Vector<CompositionClause> clauses, int selectionStart,
            int selectionEnd, int replacementStart, int replacementEnd) {
        if (clauses == null)
            return mEditable.setComposition(text, null, selectionStart,
                    selectionEnd, replacementStart, replacementEnd);

        Vector<CompositionUnderline> underlines = new Vector<CompositionUnderline>(
                clauses.size());
        for (CompositionClause clause : clauses)
            underlines.add(new CompositionUnderline(clause));
        return mEditable.setComposition(text, underlines, selectionStart,
                selectionEnd, replacementStart, replacementEnd);
    }

    @Override
    public boolean confirmComposition(String text) {
        return mEditable.confirmComposition(text);
    }

    @Override
    public boolean finishComposition() {
        return mEditable.finishComposition();
    }

    @Override
    public void cancelComposition() {
        mEditable.cancelComposition();
    }

    @Override
    public boolean performEditorAction(int editorAction) {
        return mEditable.performEditorAction(editorAction);
    }

    @Override
    public boolean sendKeyEvent(UIEvent event) {
        return mEditable.sendKeyEvent(event.timestamp(), event.action(),
                event.modifiers(), event.keyState().mVirtualKeyCode,
                event.keyState().mNativeKeyCode,
                Character.toString(event.keyState().mUnicodeCharacter),
                Character.toString(event.keyState().mUnicodeCharacter),
                event.keyState().mIsAutoRepeat, event.keyState().mIsSystemKey,
                event.keyState().mIsKeypadKey, event.keyState().mStrokeHash);
    }

    private WebEditable mEditable;

    public WebEditableContext(SWKView view) {
        mEditable = new WebEditable(view);
    }
}
