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
#include "SWKNavigationActionNatives.h"

#include "NavigationActionData.h"

namespace WebKit {

static int32_t toInt32(WebCore::NavigationType navigationType)
{
    switch (navigationType) {
    case WebCore::NavigationType::LinkClicked:
        return Natives::SWKNavigationAction::NAVIGATION_TYPE_LINK_CLICKED;
    case WebCore::NavigationType::FormSubmitted:
        return Natives::SWKNavigationAction::NAVIGATION_TYPE_FORM_SUBMITTED;
    case WebCore::NavigationType::BackForward:
        return Natives::SWKNavigationAction::NAVIGATION_TYPE_BACK_FORWARD;
    case WebCore::NavigationType::Reload:
        return Natives::SWKNavigationAction::NAVIGATION_TYPE_RELOAD;
    case WebCore::NavigationType::FormResubmitted:
        return Natives::SWKNavigationAction::NAVIGATION_TYPE_FORM_RESUBMITTED;
    case WebCore::NavigationType::Other:
        return Natives::SWKNavigationAction::NAVIGATION_TYPE_OTHER;
    }

    ASSERT_NOT_REACHED();
}

static int32_t toInt32(WebMouseEvent::Button buttonType)
{
    int32_t type = Natives::SWKNavigationAction::EVENT_MOUSE_BUTTON_NONE;

    switch (buttonType) {
    case WebMouseEvent::Button::NoButton:
        return Natives::SWKNavigationAction::EVENT_MOUSE_BUTTON_NONE;
        break;
    case WebMouseEvent::Button::LeftButton:
        return Natives::SWKNavigationAction::EVENT_MOUSE_BUTTON_LEFT;
        break;
    case WebMouseEvent::Button::MiddleButton:
        return Natives::SWKNavigationAction::EVENT_MOUSE_BUTTON_MIDDLE;
        break;
    case WebMouseEvent::Button::RightButton:
        return Natives::SWKNavigationAction::EVENT_MOUSE_BUTTON_RIGHT;
    }

    ASSERT_NOT_REACHED();
}

Native::PassLocalRef<SWKNavigationAction> SWKNavigationAction::create(const NavigationActionData& navigationActionData,
    Native::PassLocalRef<SWKURLRequest> request)
{
    Native::LocalRef<SWKNavigationAction> instance = Natives::SWKNavigationAction::create(
        toInt32(navigationActionData.navigationType),
        toInt32(navigationActionData.mouseButton),
        static_cast<int32_t>(navigationActionData.modifiers),
        request).as<SWKNavigationAction>();

    return instance.release();
}

} // namespace WebKit

namespace WebKit {
namespace Natives {

SWKNavigationAction* SWKNavigationAction::nativeCreate()
{
    return new ::WebKit::SWKNavigationAction();
}

} // namespace Natives
} // namespace WebKit
