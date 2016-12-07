/*
 * Copyright (C) 2014-2015 Naver Corp. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
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
#include "Screen.h"

#include "FrameView.h"
#include "HostWindow.h"
#include "NotImplemented.h"
#include "PlatformBridgeNatives.h"
#include "Widget.h"
#include <NativesPoint.h>

using namespace WebKit;

namespace WebCore {

int screenDepth(Widget*)
{
    return PlatformBridge::screenDepth();
}

int screenDepthPerComponent(Widget*)
{
    int depth = PlatformBridge::screenDepth();

    switch (depth) {
    case 24:
    case 32:
        return 8;
    case 8:
        return 2;
    default:
        // Assumes RGB.
        return depth / 3;
    }
}

bool screenIsMonochrome(Widget*)
{
    return PlatformBridge::screenIsMonochrome();
}

// This is used by JavaScript Screen object and media query for device info. We
// should return the value in the device pixel.
FloatRect screenRect(Widget* widget)
{
    if (!widget)
        return FloatRect();

    Native::LocalRef<Native::Natives::Point> size = PlatformBridge::screenSize().as<Native::Natives::Point>();
    return FloatRect(FloatPoint(), FloatSize(size->x.get(), size->y.get()));
}

// Similar as screenRect, this is used by JavaScript Screen object. This is also
// used by JavaScript Window to position and resize (usually to full screen).
FloatRect screenAvailableRect(Widget* widget)
{
    if (!widget)
        return FloatRect();

    Native::LocalRef<Native::Natives::Point> size = PlatformBridge::availableScreenSize().as<Native::Natives::Point>();
    return FloatRect(FloatPoint(),FloatSize(size->x.get(), size->y.get()));
}

bool screenHasInvertedColors()
{
    notImplemented();
    return false;
}

bool screenSupportsExtendedColor(Widget*)
{
    notImplemented();
    return true;
}

} // namespace WebCore
