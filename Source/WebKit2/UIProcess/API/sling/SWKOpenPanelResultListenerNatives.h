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

#ifndef SWKOpenPanelResultListener_h
#define SWKOpenPanelResultListener_h

#include "SWKOpenPanelResultListenerNativesBase.h"

namespace API {
class OpenPanelParameters;
}

namespace WebKit {

class WebOpenPanelParameters;
class WebOpenPanelResultListenerProxy;

class SWKOpenPanelResultListener final : public Natives::SWKOpenPanelResultListener {
    friend class Natives::SWKOpenPanelResultListener;
public:
    static Native::PassLocalRef<SWKOpenPanelResultListener> create(API::OpenPanelParameters*, WebOpenPanelResultListenerProxy*);
    virtual ~SWKOpenPanelResultListener() = default;

protected:
    void chooseFiles(Native::PassLocalRef<Natives::Vector>) override;
    void chooseDirectories(Native::PassLocalRef<Natives::Vector>) override;
    void cancel() override;

    Native::PassLocalRef<Natives::Vector> getAcceptMIMETypes() override;
    Native::PassLocalRef<Natives::Vector> getSelectedFileNames() override;

    bool allowsDirectoryUpload() override;

private:
    SWKOpenPanelResultListener() = default;

    API::OpenPanelParameters* m_parameters;
    WebOpenPanelResultListenerProxy* m_listener;
    bool m_valid;
};

} // namespace WebKit

#endif // SWKOpenPanelResultListener_h

