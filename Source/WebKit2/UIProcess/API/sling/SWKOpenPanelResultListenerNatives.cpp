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

#include "config.h"
#include "SWKOpenPanelResultListenerNatives.h"

#include "APIArray.h"
#include "APIOpenPanelParameters.h"
#include "APIString.h"
#include "APIURL.h"
#include "WebOpenPanelResultListenerProxy.h"
#include <wtf/text/CString.h>

#include <NativesString.h>
#include <NativesVector.h>

namespace WebKit {

Native::PassLocalRef<SWKOpenPanelResultListener> SWKOpenPanelResultListener::create(API::OpenPanelParameters* parameters, WebOpenPanelResultListenerProxy* listener)
{
    Native::LocalRef<SWKOpenPanelResultListener> request = Natives::SWKOpenPanelResultListener::create(parameters->allowMultipleFiles()).as<SWKOpenPanelResultListener>();
    request->m_parameters = parameters;
    request->m_listener = listener;
    request->m_valid = true;
    return request;
}

void SWKOpenPanelResultListener::chooseFiles(Native::PassLocalRef<Natives::Vector> files)
{
    if (UNLIKELY(!m_valid))
        return;

    int32_t size = files->size();
    if (size <= 0)
        return;

    WTF::Vector<String> chosenFiles;
    for (int32_t i = 0; i < size; ++i) {
        auto stringBytes = files->elementAt(i).as<Native::Natives::String>()->getBytes();
        const char* filePath = reinterpret_cast<const char*>(stringBytes.data());
        chosenFiles.append(WTF::String::fromUTF8(filePath, stringBytes.count()));
    }

    m_listener->chooseFiles(chosenFiles);
    m_valid = false;
}

void SWKOpenPanelResultListener::chooseDirectories(Native::PassLocalRef<Natives::Vector> directories)
{
#if ENABLE(DIRECTORY_UPLOAD)
    if (UNLIKELY(!m_valid))
        return;

    int32_t size = directories->size();
    if (size <= 0)
        return;

    WTF::Vector<RefPtr<API::Object>> chosenDirectories;
    for (int32_t i = 0; i < size; ++i) {
        auto stringBytes = directories->elementAt(i).as<Native::Natives::String>()->getBytes();
        const char* directoryPath = reinterpret_cast<const char*>(stringBytes.data());
        chosenDirectories.append(API::URL::create(WTF::String::fromUTF8(directoryPath, stringBytes.count())));
    }

    m_listener->chooseDirectories(API::Array::create(WTFMove(chosenDirectories)).ptr());
    m_valid = false;
#endif
}

void SWKOpenPanelResultListener::cancel()
{
    if (UNLIKELY(!m_valid))
        return;

    m_listener->cancel();
    m_valid = false;
}

static Native::PassLocalRef<Natives::Vector> toStringVector(PassRefPtr<API::Array> array)
{
    size_t size = array->size();
    if (!size)
        return Natives::Vector::create();

    Native::LocalRef<Natives::Vector> result = Natives::Vector::create(size);
    for (const auto& entry : array->elementsOfType<API::String>()) {
        std::string value = entry->string().utf8().data();
        result->add(::Natives::createString(value));
    }

    return result;
}

Native::PassLocalRef<Natives::Vector> SWKOpenPanelResultListener::getAcceptMIMETypes()
{
    return toStringVector(m_parameters->acceptMIMETypes());
}

Native::PassLocalRef<Natives::Vector> SWKOpenPanelResultListener::getSelectedFileNames()
{
    return toStringVector(m_parameters->selectedFileNames());
}

bool SWKOpenPanelResultListener::allowsDirectoryUpload()
{
#if ENABLE(DIRECTORY_UPLOAD)
    return m_parameters->allowsDirectoryUpload();
#else
    return false;
#endif
}

namespace Natives {

SWKOpenPanelResultListener* SWKOpenPanelResultListener::nativeCreate()
{
    return new ::WebKit::SWKOpenPanelResultListener();
}

} // namespace Natives
} // namespace WebKit

