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

import java.util.Date;
import java.util.Vector;

public class SWKWebsiteDataStore {
    public static final int WEBSITE_DATA_TYPE_COOKIES = 1 << 0;
    public static final int WEBSITE_DATA_TYPE_DISK_CACHE = 1 << 1;
    public static final int WEBSITE_DATA_TYPE_MEMORY_CACHE = 1 << 2;
    public static final int WEBSITE_DATA_TYPE_LOCAL_STORAGE = 1 << 3;
    public static final int WEBSITE_DATA_TYPE_ALL = Integer.MAX_VALUE;
    
    // Returns the shared default data store.
    public static SWKWebsiteDataStore getDefaultDataStore() {   
        return null;
    }

    // Returns a new non-persistent data store.
    public static SWKWebsiteDataStore getNonPersistentDataStore() {
        return null;
    }

    public boolean isNonPersistent() {
        return false;
    }

    /**
     * @param websiteDataTypes one of the WebsiteDataTypeXXX values.
     */
    public void fetchDataRecordsOfTypes(int websiteDataTypes,
            labs.naver.webkit.api.ValueCallback<Vector<?>> completionHandler) {
    }

    /**
     * @param websiteDataTypes one of the WebsiteDataTypeXXX values.
     */
    public void removeDataOfTypes(int websiteDataTypes, Vector<?> dataRecords,
            labs.naver.webkit.api.ValueCallback<Void> completionHandler) {
    }

    /**
     * @param websiteDataTypes one of the WebsiteDataTypeXXX values.
     */
    public void removeDataOfTypes(int websiteDataTypes, Date date,
            labs.naver.webkit.api.ValueCallback<Void> completionHandler) {
    }

}
