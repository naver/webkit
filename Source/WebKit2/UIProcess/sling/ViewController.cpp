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
#include "ViewController.h"

#include "SWKWebContentNatives.h"
#include "WebEditableNatives.h"
#include "WebViewportAttributes.h"

#if ENABLE(CONTEXT_MENUS)
#include "WebContextMenuProxySling.h"
#endif

#include <NativesPoint.h>
#include <NativesRect.h>

using namespace WebCore;

namespace WebKit {

void ViewController::hasTouchEventHandlers(bool hasTouchHandlers)
{
    Native::LocalRef<WebKit::SWKView> view = m_view.tryPromote();
    if (!view)
        return;
    view->hasTouchEventHandlers(hasTouchHandlers);
}

void ViewController::enterFullScreen()
{
    Native::LocalRef<WebKit::SWKView> view = m_view.tryPromote();
    if (!view)
        return;
    return view->enterFullScreen();
}

void ViewController::exitFullScreen()
{
    Native::LocalRef<WebKit::SWKView> view = m_view.tryPromote();
    if (!view)
        return;
    return view->exitFullScreen();
}

void ViewController::setViewNeedsDisplay(const WebCore::IntRect& area)
{
    Native::LocalRef<WebKit::SWKView> view = m_view.tryPromote();
    if (!view)
        return;
    return view->setViewNeedsDisplay(area);
}

void ViewController::setViewResumePainting()
{
    Native::LocalRef<WebKit::SWKView> view = m_view.tryPromote();
    if (!view)
        return;
    return view->setViewResumePainting();
}

void ViewController::editorStateChanged()
{
    Native::LocalRef<WebKit::SWKView> view = m_view.tryPromote();
    if (!view)
        return;
    return view->editorStateChanged();
}

void ViewController::setCursor(const WebCore::Cursor& cursor)
{
    Native::LocalRef<WebKit::SWKView> view = m_view.tryPromote();
    if (!view)
        return;
    return view->setCursor(cursor);
}

RefPtr<WebPopupMenuProxy> ViewController::createPopupMenuProxy(WebPageProxy& page)
{
    Native::LocalRef<WebKit::SWKView> view = m_view.tryPromote();
    if (!view)
        return nullptr;
    return view->createPopupMenuProxy(page);
}

#if ENABLE(CONTEXT_MENUS)
std::unique_ptr<WebContextMenuProxy> ViewController::createContextMenuProxy(WebPageProxy& page, const ContextMenuContextData& contextMenuContextData, const UserData& userData)
{
    Native::LocalRef<WebKit::SWKView> view = m_view.tryPromote();
    if (!view)
        return nullptr;
    return view->createContextMenuProxy(page, contextMenuContextData, userData);
}
#endif

bool ViewController::isSpeaking()
{
    Native::LocalRef<WebKit::SWKView> view = m_view.tryPromote();
    if (!view)
        return false;
    return view->isSpeaking();
}

void ViewController::speak(const String& string)
{
    Native::LocalRef<WebKit::SWKView> view = m_view.tryPromote();
    if (!view)
        return;
    view->speak(string);
}

void ViewController::stopSpeaking()
{
    Native::LocalRef<WebKit::SWKView> view = m_view.tryPromote();
    if (!view)
        return;
    view->stopSpeaking();
}

void ViewController::doneWithKeyEvent(const NativeWebKeyboardEvent& event, bool wasEventHandled)
{
    Native::LocalRef<WebKit::SWKView> view = m_view.tryPromote();
    if (!view)
        return;
    return view->doneWithKeyEvent(event, wasEventHandled);
}

#if ENABLE(TOUCH_EVENTS)
void ViewController::doneWithTouchEvent(bool wasEventHandled)
{
    Native::LocalRef<WebKit::SWKView> view = m_view.tryPromote();
    if (!view)
        return;
    return view->doneWithTouchEvent(wasEventHandled);
}
#endif

void ViewController::didCommitLoad()
{
    Native::LocalRef<WebKit::SWKView> view = m_view.tryPromote();
    if (!view)
        return;
    return view->pageViewportController().didCommitLoad();
}

void ViewController::didChangeContentsSize(const WebCore::IntSize& size)
{
    if (m_contentSize != size)
        m_contentSize = size;

    Native::LocalRef<WebKit::SWKView> view = m_view.tryPromote();
    if (!view)
        return;

    if (view->useFixedLayout())
        view->pageViewportController().didChangeContentsSize(size);
    view->didChangeContentsSize(size.width(), size.height());
}

void ViewController::didChangeContentsPosition(const WebCore::IntPoint& position)
{
    Native::LocalRef<WebKit::SWKView> view = m_view.tryPromote();
    if (!view)
        return;

    if (view->useFixedLayout())
        view->pageViewportController().pageDidRequestScroll(position);
}

void ViewController::didChangeViewportAttributes(const WebCore::ViewportAttributes& attributes)
{
    Native::LocalRef<WebKit::SWKView> view = m_view.tryPromote();
    if (!view)
        return;

    ASSERT(view->useFixedLayout());
    view->pageViewportController().didChangeViewportAttributes(attributes);
}

void ViewController::didChangeTooltip(const String& tooltip)
{
    Native::LocalRef<WebKit::SWKView> view = m_view.tryPromote();
    if (!view)
        return;
    view->didChangeTooltip(tooltip.utf8().data());
}

void ViewController::didRenderFrame(const WebCore::IntSize& contentsSize, const WebCore::IntRect& coveredRect)
{
    Native::LocalRef<WebKit::SWKView> view = m_view.tryPromote();
    if (!view)
        return;

    if (view->useFixedLayout())
        view->pageViewportController().didRenderFrame(contentsSize, coveredRect);
}

void ViewController::didCompletePageTransition()
{
    Native::LocalRef<WebKit::SWKView> view = m_view.tryPromote();
    if (!view)
        return;

    if (view->useFixedLayout())
        view->pageViewportController().pageTransitionViewportReady();
}

void ViewController::webProcessCrashed(const String& url)
{
    Native::LocalRef<WebKit::SWKView> view = m_view.tryPromote();
    if (!view)
        return;
    return view->webProcessCrashed(url);
}

void ViewController::webProcessDidRelaunch()
{
    Native::LocalRef<WebKit::SWKView> view = m_view.tryPromote();
    if (!view)
        return;
    return view->webProcessDidRelaunch();
}

#if OS(WINDOWS)
int64_t ViewController::nativeWindowHandle()
{
    Native::LocalRef<WebKit::SWKView> view = m_view.tryPromote();
    if (!view)
        return 0;
    return view->nativeWindowHandle();
}
#endif

Native::PassLocalRef<SWKView> ViewController::createView(SWKWebContent* webContent)
{
    ASSERT(!m_view);
    Native::LocalRef<SWKView> view = SWKView::create(webContent).as<SWKView>();
    m_view = view;
    return view.release();
}

Native::PassLocalRef<SWKView> ViewController::view()
{
    return m_view.tryPromote();
}

ViewController::ViewController(SWKWebContent& content)
    : m_content(content)
{
}

ViewController::~ViewController()
{
}

} // namespace WebKit
