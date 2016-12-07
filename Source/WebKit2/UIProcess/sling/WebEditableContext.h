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

#ifndef WebEditableContext_h
#define WebEditableContext_h

#include <view/EditableContext.h>

namespace webkit {

class SWKView;
class WebEditable;

class WEBKIT_EXPORT WebEditableContext : public view::EditableContext {
public:
    static std::shared_ptr<WebEditableContext> create(std::shared_ptr<SWKView>&);
    ~WebEditableContext();

private:
    virtual view::Rect editableCaretRectAtStart() override;
    virtual view::Rect editableCaretRectAtEnd() override;
    virtual std::wstring editableSelectionText() override;
    virtual std::wstring editableTextBeforeCaret(int32_t) override;
    virtual std::wstring editableTextAfterCaret(int32_t) override;

    bool setComposition(const std::wstring&, const std::vector<view::CompositionClause>&, int32_t, int32_t, int32_t, int32_t) override;
    bool confirmComposition(const std::wstring&) override;
    bool finishComposition() override;
    void cancelComposition() override;

    bool performEditorAction(EditorAction) override;
    bool sendKeyEvent(const view::UIEvent&) override;

private:
    WebEditableContext(std::shared_ptr<SWKView>&);

    std::shared_ptr<WebEditable> m_editable;
};

}

#endif
