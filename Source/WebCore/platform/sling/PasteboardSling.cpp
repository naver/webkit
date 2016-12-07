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

#include "config.h"
#include "Pasteboard.h"

#include "CachedImage.h"
#include "Document.h"
#include "DocumentFragment.h"
#include "DocumentLoader.h"
#include "DragData.h"
#include "Editor.h"
#include "EditorClient.h"
#include "ExceptionCodePlaceholder.h"
#include "Frame.h"
#include "FrameView.h"
#include "FrameLoaderClient.h"
#include "HitTestResult.h"
#include "HTMLAnchorElement.h"
#include "htmlediting.h"
#include "HTMLNames.h"
#include "Image.h"
#include "URL.h"
#include "MIMETypeRegistry.h"
#include "Page.h"
#include "PasteboardStrategy.h"
#include "PlatformStrategies.h"
#include "RenderImage.h"
#include "Text.h"
#include "markup.h"
#include <wtf/StdLibExtras.h>
#include <wtf/RetainPtr.h>
#include <wtf/text/StringBuilder.h>
#include <wtf/unicode/CharacterNames.h>

namespace WebCore {

Pasteboard::Pasteboard()
{
}

void Pasteboard::writePlainText(const String&, SmartReplaceOption)
{
    notImplemented();
}

void Pasteboard::clear()
{
    notImplemented();
}

bool Pasteboard::canSmartReplace()
{
    notImplemented();
    return false;
}

std::unique_ptr<Pasteboard> Pasteboard::createForCopyAndPaste()
{
    return std::make_unique<Pasteboard>();
}

std::unique_ptr<Pasteboard> Pasteboard::createPrivate()
{
    return std::make_unique<Pasteboard>();
}

bool Pasteboard::hasData()
{
    notImplemented();
    return false;
}

void Pasteboard::clear(const String&)
{
    notImplemented();
}

void Pasteboard::read(PasteboardPlainText&)
{
    notImplemented();
}

String Pasteboard::readString(const String&)
{
    notImplemented();
    return String();
}

void Pasteboard::write(const PasteboardURL&)
{
    notImplemented();
}

void Pasteboard::writeString(const String&, const String&)
{
    notImplemented();
}

Vector<String> Pasteboard::types()
{
    notImplemented();
    return Vector<String>();
}

Vector<String> Pasteboard::readFilenames()
{
    notImplemented();
    return Vector<String>();
}

void Pasteboard::writePasteboard(const Pasteboard&)
{
    notImplemented();
}

}
