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
package labs.naver.webkit.api;

import labs.naver.onig.AbstractNativeMethod;
import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeConstructor;
import labs.naver.onig.NativeDestructor;
import labs.naver.onig.NativeNamespace;
import labs.naver.onig.NativeObjectField;

import java.util.Vector;

/**
 * A SWKUserContentController object provides a way for JavaScript to post
 * messages to a web view. The user content controller associated with a web
 * view is specified by its web view configuration.
 */
@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class SWKUserContentController {

    @CalledByNative
    public SWKUserContentController() {
        nativeCreate();
    }

    /**
     * Get the user scripts associated with this user content controller.
     */
    @AbstractNativeMethod
    public native Vector<SWKUserScript> getUserScripts();

    /**
     * Adds a user script.
     *
     * @param userScript The user script to add.
     */
    @AbstractNativeMethod
    public native void addUserScript(SWKUserScript userScript);

    /**
     * Removes all associated user scripts.
     */
    @AbstractNativeMethod
    public native void removeAllUserScripts();

    /**
     * Adds a user style sheet.
     *
     * @param userStyleSheet The user style sheet to add.
     */
    // @SWKPrivate
    @AbstractNativeMethod
    public native void addUserStyleSheet(SWKUserStyleSheet userStyleSheet);

    /**
     * Removes all associated user style sheets.
     */
    // @SWKPrivate
    @AbstractNativeMethod
    public native void removeAllUserStyleSheets();

    /**
     * Adds a script message handler.
     * <p>
     * Adding a scriptMessageHandler adds a function
     * window.webkit.messageHandlers.<name>.postMessage(<messageBody>) for all
     * frames.
     *
     * @param scriptMessageHandler The message handler to add.
     * @param name The name of the message handler.
     */
    @AbstractNativeMethod
    public native void addScriptMessageHandler(
            SWKScriptMessageHandler scriptMessageHandler, String name);

    /**
     * Removes a script message handler.
     *
     * @param name The name of the message handler to remove.
     */
    @AbstractNativeMethod
    public native void removeScriptMessageHandlerForName(String name);

    /**
     * Removes all associated user script and style sheets.
     */
    // @SWKPrivate
    @AbstractNativeMethod
    public native void removeAllUserContent();

    @NativeObjectField
    private int mNativeClass;

    @NativeConstructor
    private native void nativeCreate();
    @NativeDestructor
    private native void nativeDestroy();
}
