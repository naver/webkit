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
#include "EventSenderProxy.h"

#include "NotImplemented.h"
#include "PlatformWebView.h"
#include "TestController.h"

namespace WTR {

EventSenderProxy::EventSenderProxy(TestController* testController)
    : m_testController(testController)
    , m_time(0)
    , m_leftMouseButtonDown(false)
    , m_clickCount(0)
    , m_clickTime(0)
    , m_clickButton(kWKEventMouseButtonNoButton)
{
}

EventSenderProxy::~EventSenderProxy()
{
#if ENABLE(TOUCH_EVENTS)
    clearTouchPoints();
#endif
}

void EventSenderProxy::updateClickCountForButton(int button)
{
}

void EventSenderProxy::dispatchEvent(const MSG& event)
{
    notImplemented();
}

void EventSenderProxy::sendOrQueueEvent(const MSG& event)
{
    notImplemented();
}

void EventSenderProxy::mouseDown(unsigned button, WKEventModifiers wkModifiers)
{
    notImplemented();
}

void EventSenderProxy::mouseUp(unsigned button, WKEventModifiers wkModifiers)
{
    notImplemented();
}

void EventSenderProxy::mouseMoveTo(double x, double y)
{
}

void EventSenderProxy::mouseScrollBy(int horizontal, int vertical)
{
    notImplemented();
}

void EventSenderProxy::continuousMouseScrollBy(int horizontal, int vertical, bool paged)
{
    notImplemented();
}

void EventSenderProxy::mouseScrollByWithWheelAndMomentumPhases(int x, int y, int /*phase*/, int /*momentum*/)
{
}

void EventSenderProxy::swipeGestureWithWheelAndMomentumPhases(int, int, int, int)
{
    notImplemented();
}

void EventSenderProxy::leapForward(int milliseconds)
{
    notImplemented();
}

void EventSenderProxy::keyDown(WKStringRef keyRef, WKEventModifiers wkModifiers, unsigned location)
{
    notImplemented();
}

#if ENABLE(TOUCH_EVENTS)
void EventSenderProxy::addTouchPoint(int x, int y)
{
    notImplemented();
}

void EventSenderProxy::updateTouchPoint(int index, int x, int y)
{
    notImplemented();
}

void EventSenderProxy::setTouchModifier(WKEventModifiers modifier, bool enable)
{
    notImplemented();
}

void EventSenderProxy::touchStart()
{
    notImplemented();
}

void EventSenderProxy::touchMove()
{
    notImplemented();
}

void EventSenderProxy::touchEnd()
{
    notImplemented();
}

void EventSenderProxy::touchCancel()
{
    notImplemented();
}

void EventSenderProxy::clearTouchPoints()
{
    notImplemented();
}

void EventSenderProxy::releaseTouchPoint(int index)
{
    notImplemented();
}

void EventSenderProxy::cancelTouchPoint(int index)
{
    notImplemented();
}

void EventSenderProxy::setTouchPointRadius(int radiusX, int radiusY)
{
    notImplemented();
}
#endif

}
