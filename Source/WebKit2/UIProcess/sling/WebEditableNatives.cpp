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
#include "WebEditableNatives.h"

#include "NativeWebCoreGraphics.h"
#include "SWKViewNatives.h"
#include "SWKWebContentNatives.h"
#include <wtf/Vector.h>
#include <wtf/text/CString.h>

#include <NativesRect.h>
#include <NativesVector.h>

using namespace WebCore;

namespace WebKit {

WebEditable::WebEditable(Native::PassLocalRef<Natives::SWKView> view)
    : m_view(view.as<SWKView>())
{
}

WebEditable::~WebEditable()
{
}

Native::PassLocalRef<Natives::Rect> WebEditable::editableCaretRectAtStart()
{
    return toRect(editorState().caretRectAtStart);
}

Native::PassLocalRef<Natives::Rect> WebEditable::editableCaretRectAtEnd()
{
    return toRect(editorState().caretRectAtEnd);
}

std::string WebEditable::editableSelectionText()
{
    return editorState().selectedText.utf8().data();
}

std::string WebEditable::editableTextBeforeCaret(int32_t length)
{
    int32_t beginOffset = std::max(editorState().selectionRangeStart - length, 0);
    String text = editorState().editableText.substring(beginOffset, editorState().selectionRangeStart - beginOffset);
    return text.utf8().data();
}

std::string WebEditable::editableTextAfterCaret(int32_t length)
{
    int32_t endOffset = std::min(editorState().selectionRangeEnd + length, int32_t(editorState().editableText.length()));
    String text = editorState().editableText.substring(editorState().selectionRangeEnd, endOffset - editorState().selectionRangeEnd);
    return text.utf8().data();
}

bool WebEditable::setComposition(const std::string& text, Native::PassLocalRef<Natives::Vector> nativeUnderlines, int32_t selectionStart, int32_t selectionEnd, int32_t replacementStart, int32_t replacementEnd)
{
    // FIXME: Should pass nativeUnderlines.
    Vector<CompositionUnderline> underlines;
    webPage().setComposition(String::fromUTF8(text.c_str()), underlines, selectionStart, selectionEnd, replacementStart, replacementEnd);
    return true;
}

bool WebEditable::confirmComposition(const std::string& text)
{
    webPage().confirmComposition(String::fromUTF8(text.c_str()));
    return true;
}

bool WebEditable::finishComposition()
{
    webPage().finishComposition();
    return true;
}

void WebEditable::cancelComposition()
{
    webPage().cancelComposition();
}

bool WebEditable::performEditorAction(int32_t editorAction)
{
    return false;
}

bool WebEditable::sendKeyEvent(int64_t timestamp, int32_t action, int32_t modifiers, int32_t virtualKeyCode, int32_t nativeKeyCode,
    const std::string& text, const std::string& unmodifiedText, bool isAutoRepeat, bool isSystemKey, bool isKeypadKey, int32_t strokeHash)
{
    m_view->sendKeyEvent(timestamp, action, modifiers, virtualKeyCode, nativeKeyCode, text, unmodifiedText, isAutoRepeat, isSystemKey, isKeypadKey, strokeHash);
    return true;
}

WebPageProxy& WebEditable::webPage()
{
    return m_view->webContent().webPage();
}

const EditorState& WebEditable::editorState()
{
    return webPage().editorState();
}

namespace Natives {

WebEditable* WebEditable::nativeCreate(Native::PassLocalRef<Natives::SWKView> view)
{
    return new ::WebKit::WebEditable(view);
}

} // namespace Natives
} // namespace WebKit
