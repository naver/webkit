/*
 * Copyright (C) 2015 Naver Corp. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef WebEditable_h
#define WebEditable_h

#include "WebEditableNativesBase.h"

#include <WebCore/IntRect.h>
#include <wtf/text/WTFString.h>

#include <onig/GlobalRef.h>

namespace WebKit {

class EditorState;
class SWKView;
class WebPageProxy;

class WebEditable final : public Natives::WebEditable {
    friend class Natives::WebEditable;
public:
    ~WebEditable();

    Native::PassLocalRef<Natives::Rect> editableCaretRectAtStart() override;
    Native::PassLocalRef<Natives::Rect> editableCaretRectAtEnd() override;

    std::string editableSelectionText() override;
    std::string editableTextBeforeCaret(int32_t length) override;
    std::string editableTextAfterCaret(int32_t length) override;

    bool setComposition(const std::string& text, Native::PassLocalRef<Natives::Vector> underlines, int32_t selectionStart, int32_t selectionEnd, int32_t replacementStart, int32_t replacementEnd) override;
    bool confirmComposition(const std::string& text) override;
    bool finishComposition() override;
    void cancelComposition() override;

    bool performEditorAction(int32_t editorAction) override;
    bool sendKeyEvent(int64_t timestamp, int32_t action, int32_t modifiers, int32_t virtualKeyCode, int32_t nativeKeyCode,
        const std::string& text, const std::string& unmodifiedText, bool isAutoRepeat, bool isSystemKey, bool isKeypadKey, int32_t strokeHash) override;

private:
    WebEditable(Native::PassLocalRef<Natives::SWKView>);

    WebPageProxy& webPage();
    const EditorState& editorState();

    Native::GlobalRef<SWKView> m_view;
};

}

#endif // WebEditable_h
