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

#include "config.h"
#include "WebEditableContext.h"

#include "CompositionUnderline.h"
#include "WebEditable.h"
#include <ManagedVector.h>
#include <util/StringConversion.h>
#include <view/GeometryConversion.h>
#include <view/UIEvent.h>

namespace webkit {

std::shared_ptr<WebEditableContext> WebEditableContext::create(std::shared_ptr<SWKView>& view)
{
    return std::shared_ptr<WebEditableContext>(new WebEditableContext(view));
}

WebEditableContext::WebEditableContext(std::shared_ptr<SWKView>& view)
    : m_editable(WebEditable::create(view))
{
}

WebEditableContext::~WebEditableContext()
{
}

view::Rect WebEditableContext::editableCaretRectAtStart()
{
    return view::geometry_cast<view::Rect>(*m_editable->editableCaretRectAtStart());
}

view::Rect WebEditableContext::editableCaretRectAtEnd()
{
    return view::geometry_cast<view::Rect>(*m_editable->editableCaretRectAtEnd());
}

std::wstring WebEditableContext::editableSelectionText()
{
    return std::s2ws(m_editable->editableSelectionText());
}

std::wstring WebEditableContext::editableTextBeforeCaret(int32_t length)
{
    return std::s2ws(m_editable->editableTextBeforeCaret(length));
}

std::wstring WebEditableContext::editableTextAfterCaret(int32_t length)
{
    return std::s2ws(m_editable->editableTextAfterCaret(length));
}

bool WebEditableContext::setComposition(const std::wstring& text, const std::vector<view::CompositionClause>& clauses, int32_t selectionStart, int32_t selectionEnd, int32_t replacementStart, int32_t replacementEnd)
{
    if (clauses.empty())
        return m_editable->setComposition(std::ws2s(text), nullptr, selectionStart, selectionEnd,
            replacementStart, replacementEnd);

    std::shared_ptr<Managed::Vector> underlines = Managed::Vector::create(clauses.size());
    for (auto& clause : clauses)
        underlines->add(CompositionUnderline::create(clause));
    return m_editable->setComposition(std::ws2s(text), underlines, selectionStart, selectionEnd,
        replacementStart, replacementEnd);
}

bool WebEditableContext::confirmComposition(const std::wstring& text)
{
    return m_editable->confirmComposition(std::ws2s(text));
}

bool WebEditableContext::finishComposition()
{
    return m_editable->finishComposition();
}

void WebEditableContext::cancelComposition()
{
    m_editable->cancelComposition();
}

bool WebEditableContext::performEditorAction(EditorAction editorAction)
{
    return m_editable->performEditorAction(static_cast<int32_t>(editorAction));
}

bool WebEditableContext::sendKeyEvent(const view::UIEvent& event)
{
    if (event.source() != view::UIEvent::Source::Key)
        return false;

    std::string text = std::ws2s(std::wstring(&event.keyState().unicodeCharacter, 1));
    return m_editable->sendKeyEvent(event.timestamp().count(), static_cast<int32_t>(event.action()), event.modifiers().value,
        event.keyState().virtualKeyCode, event.keyState().nativeKeyCode, text, text,
        event.keyState().isAutoRepeat, event.keyState().isSystemKey, event.keyState().isKeypadKey,
        event.keyState().strokeHash);
}

} // namespace webkit
