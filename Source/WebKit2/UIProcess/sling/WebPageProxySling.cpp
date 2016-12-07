/*
 * Copyright (C) 2013-2015 Naver Corp. All rights reserved.
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
#include "WebPageProxy.h"

#include "APIUIClient.h"
#include "DataReference.h"
#include "DictionaryPopupInfo.h"
#include "EditingRange.h"
#include "EditorState.h"
#include "NativeWebKeyboardEvent.h"
#include "NotImplemented.h"
#include "PageClient.h"
#include "TextChecker.h"
#include "WebPageMessages.h"
#include "WebProcessProxy.h"

#include <WebCore/GraphicsLayer.h>
#include <WebCore/RuntimeApplicationChecks.h>
#include <WebCore/SharedBuffer.h>
#include <WebCore/UserAgentSling.h>
#include <wtf/text/StringConcatenate.h>

namespace WebKit {

void WebPageProxy::platformInitialize(void)
{
#if OS(ANDROID)
    m_useFixedLayout = true;
#endif
}

String WebPageProxy::standardUserAgent(const String& applicationNameForUserAgent)
{
    return WebCore::standardUserAgent(applicationNameForUserAgent);
}

void WebPageProxy::saveRecentSearches(const String&, const Vector<WebCore::RecentSearch>&)
{
    notImplemented();
}

void WebPageProxy::loadRecentSearches(const String&, Vector<WebCore::RecentSearch>&)
{
    notImplemented();
}

void WebPageProxy::setComposition(const String& text, Vector<WebCore::CompositionUnderline>& underlines, int32_t selectionStart, int32_t selectionEnd, int32_t replacementStart, int32_t replacementEnd)
{
    if (!isValid())
        return;

    process().send(Messages::WebPage::SetComposition(text, underlines, selectionStart, selectionEnd, replacementStart, replacementEnd), m_pageID, 0);
}

void WebPageProxy::confirmComposition(const String& text)
{
    if (!isValid())
        return;

    process().send(Messages::WebPage::ConfirmComposition(text), m_pageID, 0);
}

void WebPageProxy::finishComposition()
{
    if (!isValid())
        return;

    process().send(Messages::WebPage::FinishComposition(), m_pageID, 0);
}

void WebPageProxy::cancelComposition()
{
    if (!isValid())
        return;

    process().send(Messages::WebPage::CancelComposition(), m_pageID, 0);
}

void WebPageProxy::editorStateChanged(const EditorState& state)
{
    m_editorState = state;

    m_pageClient.updateTextInputState();
}

void WebPageProxy::setViewResumePainting()
{
    m_pageClient.setViewResumePainting();
}

void WebPageProxy::updateActivityState(bool isForeground)
{
    if (!isForeground) {
        if (!m_backgroundActivityToken) {
            m_backgroundActivityToken = m_process->throttler().backgroundActivityToken();
            m_foregroundActivityToken = nullptr;
        }
    } else {
        if (!m_foregroundActivityToken) {
            m_foregroundActivityToken = m_process->throttler().foregroundActivityToken();
            m_backgroundActivityToken = nullptr;
        }
    }
}

void WebPageProxy::getIsSpeaking(bool& isSpeaking)
{
    isSpeaking = m_pageClient.isSpeaking();
}

void WebPageProxy::speak(const String& string)
{
    m_pageClient.speak(string);
}

void WebPageProxy::stopSpeaking()
{
    m_pageClient.stopSpeaking();
}

} // namespace WebKit
