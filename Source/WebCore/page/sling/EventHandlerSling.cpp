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
#include "EventHandler.h"

#include "DataTransfer.h"
#include "FocusController.h"
#include "Frame.h"
#include "FrameView.h"
#include "KeyboardEvent.h"
#include "MouseEventWithHitTestResults.h"
#include "NotImplemented.h"
#include "Page.h"
#include "Pasteboard.h"
#include "PlatformKeyboardEvent.h"
#include "PlatformWheelEvent.h"
#include "RenderWidget.h"

namespace WebCore {

bool EventHandler::tabsToAllFormControls(KeyboardEvent*) const
{
    return true;
}

void EventHandler::focusDocumentView()
{
    Page* page = m_frame.page();
    if (!page)
        return;

    page->focusController().setFocusedFrame(&m_frame);
}

bool EventHandler::passWidgetMouseDownEventToWidget(const MouseEventWithHitTestResults& event)
{
    // Figure out which view to send the event to.
    RenderObject* target = event.targetNode() ? event.targetNode()->renderer() : 0;
    if (!target || !target->isWidget())
        return false;
    return passMouseDownEventToWidget(downcast<RenderWidget>(target)->widget());
}

bool EventHandler::passWidgetMouseDownEventToWidget(RenderWidget* renderWidget)
{
    return passMouseDownEventToWidget(renderWidget->widget());
}

// This function is used to route the mouse down event to the native widgets, it seems like a
// work around for the Mac platform which does not support double clicks, but browsers do.
bool EventHandler::passMouseDownEventToWidget(Widget*)
{
    // return false so the normal propogation handles the event
    return false;
}

bool EventHandler::widgetDidHandleWheelEvent(const PlatformWheelEvent& wheelEvent, Widget& widget)
{
    if (!widget.isFrameView())
        return false;

    return downcast<FrameView>(widget).frame().eventHandler().handleWheelEvent(wheelEvent);
}

bool EventHandler::eventActivatedView(const PlatformMouseEvent&) const
{
    notImplemented();
    return false;
}

bool EventHandler::passMousePressEventToSubframe(MouseEventWithHitTestResults& mev, Frame* subframe)
{
    subframe->eventHandler().handleMousePressEvent(mev.event());
    return true;
}

bool EventHandler::passMouseMoveEventToSubframe(MouseEventWithHitTestResults& mev, 
    Frame* subframe, HitTestResult* hoveredNode)
{
    subframe->eventHandler().handleMouseMoveEvent(mev.event(), hoveredNode);
    return true;
}

bool EventHandler::passMouseReleaseEventToSubframe(MouseEventWithHitTestResults& mev, Frame* subframe)
{
    subframe->eventHandler().handleMouseReleaseEvent(mev.event());
    return true;
}

unsigned EventHandler::accessKeyModifiers()
{
    return PlatformKeyboardEvent::AltKey;
}

}  // namespace WebCore
