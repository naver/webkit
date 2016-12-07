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
package labs.naver.webkit;

import android.graphics.Rect;

import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeNamespace;
import labs.naver.webkit.api.CompletionHandler;
import labs.naver.webkit.api.SWKWebContent;
import java.util.Vector;

@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public abstract class SWKFormDelegate {
    @CalledByNative
    public void didStartInputSession(SWKWebContent webContent, SWKFormInputSession inputSession) {
    }

    @CalledByNative
    public void willSubmitFormValues(Vector<String> values, CompletionHandler<Void> submissionHandler) {
        submissionHandler.invoke();
    }

    @CalledByNative
    public void accessoryViewCustomButtonTappedInFormInputSession(SWKWebContent webContent,
            SWKFormInputSession inputSession) {
    }

    @CalledByNative
    public boolean hasSuggestionsForCurrentStringInInputSession(SWKWebContent webContent,
            SWKFormInputSession inputSession) {
        return false;
    }

    @CalledByNative
    public Vector<?> suggestionsForString(SWKWebContent webContent, String string,
            SWKFormInputSession inputSession) {
        return null;
    }

    @CalledByNative
    public void textDidChangeInTextField(String name, String value, boolean autocomplete, Rect rect, final CompletionHandler<String> replyHandler) {
        // replyHandler call is not mandatory.
    }

    @CalledByNative
    public void textFieldDidEndEditing() {
    }
}
