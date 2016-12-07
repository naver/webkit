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

import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeNamespace;

@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class SWKURLResponse {
    public static final long URL_RESPONSE_UNKNOWN_LENGTH = -1;

    private final SWKURL mURL;
    private final String mMimeType;
    private final String mEncodingName;
    private final long mExpectedLength;
    private final String mContentDisposition;

    @CalledByNative
    private SWKURLResponse(SWKURL url, String mimeType, long expectedLength, String encodingName,
                           String contentDisposition) {
        mURL = url;
        mMimeType = mimeType;
        mEncodingName = encodingName;
        mExpectedLength = expectedLength;
        mContentDisposition = contentDisposition;
    }

    public long getExpectedContentLength() {
        return mExpectedLength;
    }

    public String getSuggestedFilename() {
        // FIXME: Need to implement
        return null;
    }

    public String getMIMEType() {
        return mMimeType;
    }

    public String getTextEncodingName() {
        return mEncodingName;
    }

    public SWKURL getURL() {
        return mURL;
    }

    public String getContentDisposition() {
        return mContentDisposition;
    }
}
