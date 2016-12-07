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

import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeNamespace;

@NativeNamespace("WebKit")
@NativeClassExport("WEBKIT_EXPORT")
public class SWKNotification {
    private final String mTitle;
    private final String mBody;
    private final String mIconURL;
    private final String mTag;
    private final String mLanguage;
    private final String mDirection;
    private final SWKSecurityOrigin mOrigin;

    @CalledByNative
    SWKNotification(String title, String body, String iconURL, String tag, String language,
            String direction, SWKSecurityOrigin origin) {
        mTitle = title;
        mBody = body;
        mIconURL = iconURL;
        mTag = tag;
        mLanguage = language;
        mDirection = direction;
        mOrigin = origin;
    }

    public String getTitle() {
        return mTitle;
    }

    public String getBody() {
        return mBody;
    }

    public String getIconURL() {
        return mIconURL;
    }

    public String getTag() {
        return mTag;
    }

    public String getLanguage() {
        return mLanguage;
    }

    public String getDirection() {
        return mDirection;
    }

    public SWKSecurityOrigin getOrigin() {
        return mOrigin;
    }
}
