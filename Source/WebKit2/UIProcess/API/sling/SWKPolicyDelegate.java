/*
 * Copyright (C) 2014-2015 Naver Corp. All rights reserved.
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
public class SWKPolicyDelegate {
    
    // The policy to pass back to the decision handler from the decidePolicyForNavigationAction method.
    // Cancel the navigation.
    public static final int NavigationActionPolicyCancel = 0;
    // Allow the navigation to continue.
    public static final int NavigationActionPolicyAllow = 1;

    // The policy to pass back to the decision handler from the
    // decidePolicyForNavigationResponse method.
    // Cancel the navigation.
    public static final int NavigationResponsePolicyCancel = 0;
    // Allow the navigation to continue.
    public static final int NavigationResponsePolicyAllow = 1;



    /**
     * Decides whether to allow or cancel a navigation.
     * <p>
     * If you do not implement this method, the web view will load the request
     * or, if appropriate, forward it to another application. *
     * 
     * @param webContent The web view invoking the delegate method.
     * @param navigationAction Descriptive information about the action
     *            triggering the navigation request.
     * @param decisionHandler The decision handler to call to allow or cancel
     *            the navigation. The argument is one of the constants of the
     *            NavigationActionPolicyXXX.
     */
    @CalledByNative
    public void decidePolicyForNavigationAction(SWKWebContent webContent,
            SWKNavigationAction navigationAction,
            SWKFramePolicyListener listener) {
    }

    /**
     * Decides whether to allow or cancel a navigation after its response is
     * known.
     * <p>
     * If you do not implement this method, the web view will allow the
     * response, if the web view can show it.
     * 
     * @param webContent The web view invoking the delegate method.
     * @param navigationResponse Descriptive information about the navigation
     *            response.
     * @param decisionHandler The decision handler to call to allow or cancel
     *            the navigation. The argument is one of the constants of the
     *            NavigationResponsePolicyXXX.
     */
    @CalledByNative
    public void decidePolicyForNavigationResponse(SWKWebContent webContent,
            SWKNavigationResponse navigationResponse,
            SWKFramePolicyListener listener) {
    }
}
