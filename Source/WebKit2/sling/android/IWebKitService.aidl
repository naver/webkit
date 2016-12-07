/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package labs.naver.webkit.clutter;

/**
 * Example of defining an interface for calling on to a remote service
 * (running in another process).
 */
interface IWebKitService {
    /**
     * Run WebKitMain with client provided options.
     */
    boolean setRunOptions(in Bundle bundle);
    /**
     * Get process type of the service. e.g. "WebProcess"
     */
    String getProcessType();
    /**
     * Request the PID of this service, to do evil things with it.
     */
    int getPid();
}
