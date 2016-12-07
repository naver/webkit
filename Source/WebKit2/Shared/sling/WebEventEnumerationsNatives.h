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

#ifndef WebEventEnumerations_h
#define WebEventEnumerations_h

#include "WebEventEnumerationsNativesBase.h"

#include "WebEvent.h"

namespace WebKit {

class WebEventEnumerations final : public Natives::WebEventEnumerations {
    friend class Natives::WebEventEnumerations;
public:
    static WebEvent::Type toMouseAction(int32_t);
    static WebEvent::Type toKeyAction(int32_t);
    static WebEvent::Type toTouchAction(int32_t);

    static WebEvent::Modifiers toModifiers(int32_t);
    static WebMouseEvent::Button toButton(int32_t);

#if ENABLE(TOUCH_EVENTS)
    static WebPlatformTouchPoint::TouchPointState toTouchPointState(int32_t);
#endif

private:
    WebEventEnumerations() = default; // Static class, do not instantiate.
};

}

#endif // WebEventEnumerations_h
