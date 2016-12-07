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
#include "WebEventEnumerationsNatives.h"

namespace WebKit {

WebEvent::Type WebEventEnumerations::toMouseAction(int32_t value)
{
    switch (value) {
    case ACTION_DOWN:
        return WebEvent::MouseDown;
    case ACTION_UP:
        return WebEvent::MouseUp;
    case ACTION_MOVE:
    case ACTION_LEAVE:
        return WebEvent::MouseMove;
    default:
        return WebEvent::NoType;
    }
}

WebEvent::Type WebEventEnumerations::toKeyAction(int32_t value)
{
    switch (value) {
    case ACTION_DOWN:
        return WebEvent::RawKeyDown;
    case ACTION_UP:
        return WebEvent::KeyUp;
    case ACTION_PRESS:
        return WebEvent::Char;
    default:
        return WebEvent::NoType;
    }
}

#if ENABLE(TOUCH_EVENTS)
WebEvent::Type WebEventEnumerations::toTouchAction(int32_t value)
{
    switch (value) {
    case ACTION_CANCEL:
        return WebEvent::TouchCancel;
    case ACTION_DOWN:
        return WebEvent::TouchStart;
    case ACTION_UP:
        return WebEvent::TouchEnd;
    case ACTION_MOVE:
        return WebEvent::TouchMove;
    default:
        return WebEvent::NoType;
    }
}
#endif

WebEvent::Modifiers WebEventEnumerations::toModifiers(int32_t value)
{
    uint32_t modifiers = 0;

    if (value & MODIFIER_ALT_KEY)
        modifiers |= WebEvent::AltKey;
    if (value & MODIFIER_CTRL_KEY)
        modifiers |= WebEvent::ControlKey;
    if (value & MODIFIER_SHIFT_KEY)
        modifiers |= WebEvent::ShiftKey;

    return static_cast<WebEvent::Modifiers>(modifiers);
}

WebMouseEvent::Button WebEventEnumerations::toButton(int32_t value)
{
    static const int32_t buttonsMask = MODIFIER_LEFT_BUTTON | MODIFIER_RIGHT_BUTTON | MODIFIER_MIDDLE_BUTTON;

    value &= buttonsMask;

    switch (value) {
    case MODIFIER_LEFT_BUTTON:
        return WebMouseEvent::LeftButton;
    case MODIFIER_RIGHT_BUTTON:
        return WebMouseEvent::RightButton;
    case MODIFIER_MIDDLE_BUTTON:
        return WebMouseEvent::MiddleButton;
    default:
        return WebMouseEvent::NoButton;
    }
}

#if ENABLE(TOUCH_EVENTS)
WebPlatformTouchPoint::TouchPointState WebEventEnumerations::toTouchPointState(int32_t value)
{
    switch (value) {
    case ACTION_CANCEL:
        return WebPlatformTouchPoint::TouchCancelled;
    case ACTION_DOWN:
        return WebPlatformTouchPoint::TouchPressed;
    case ACTION_UP:
        return WebPlatformTouchPoint::TouchReleased;
    case ACTION_MOVE:
        return WebPlatformTouchPoint::TouchMoved;
    default:
        return WebPlatformTouchPoint::TouchStationary;
    }
}
#endif

namespace Natives {

WebEventEnumerations* WebEventEnumerations::CTOR()
{
    return new ::WebKit::WebEventEnumerations();
}

}
}
