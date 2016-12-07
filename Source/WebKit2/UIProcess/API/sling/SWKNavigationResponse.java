/*
 * Copyright (C) 2014 Naver Corp. All rights reserved.
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

import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeNamespace;
import labs.naver.webkit.SWKURLRequest;

/**
 * Contains information about a navigation response, used for making policy
 * decisions.
 */
@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class SWKNavigationResponse {
    /**
     * Get a boolean value indicating whether the frame being navigated is the
     * main frame.
     */
    public boolean isForMainFrame() {
        return false;
    }

    /**
     * Get The frame's response.
     */
    public SWKURLResponse getResponse() {
        return null;
    }

    /**
     * Get a boolean value indicating whether WebKit can display the response's
     * MIME type natively.
     * <p>
     * Allowing a navigation response with a MIME type that can't be shown will
     * cause the navigation to fail.
     */
    public boolean canShowMIMEType() {
        return false;
    }

    // @SWKPrivate
    public SWKFrameInfo getFrame() {
        return null;
    }

    // @SWKPrivate
    public SWKURLRequest getRequest() {
        return null;
    }
}
