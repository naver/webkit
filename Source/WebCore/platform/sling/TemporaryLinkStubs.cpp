/*
 * Copyright 2009, The Android Open Source Project
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
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"

#include "AXObjectCache.h"
#include "CookieStorage.h"
#include "File.h"
#include "GraphicsContext.h"
#include "Icon.h"
#include "NotImplemented.h"
#include "ResourceError.h"
#include "SynchronousLoaderClient.h"

using namespace WebCore;

namespace WebCore {

// This class is used in conjunction with the File Upload form element, and
// therefore relates to the above. When a file has been selected, an icon
// representing the file type can be rendered next to the filename on the
// web page. The icon for the file is encapsulated within this class.
Icon::~Icon() { }
void Icon::paint(GraphicsContext&, const FloatRect&) { }

Vector<String> supportedKeySizes()
{
    notImplemented();
    return Vector<String>();
}

ResourceError SynchronousLoaderClient::platformBadResponseError()
{
    notImplemented();
    return ResourceError();
}

int MakeDataExecutable;

RefPtr<Icon> Icon::createIconForFiles(const Vector<String>&)
{
    notImplemented();
    return 0;
}

void startObservingCookieChanges(CookieChangeCallbackPtr)
{
    notImplemented();
}

void stopObservingCookieChanges()
{
    notImplemented();
}

AccessibilityReplacedText::AccessibilityReplacedText(const VisibleSelection&)
{
}

void AccessibilityReplacedText::postTextStateChangeNotification(AXObjectCache*, AXTextEditType, const String&, const VisibleSelection&)
{
}

} // namespace WebCore
