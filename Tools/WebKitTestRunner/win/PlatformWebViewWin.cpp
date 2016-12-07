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
#include "PlatformWebView.h"

#include "COMPtr.h"
#include "NotImplemented.h"

using namespace WebKit;

namespace WTR {

static LPCWSTR hostWindowClassName = L"WTRWebViewHostWindow";

static void registerWindowClass()
{
    static bool initialized;
    if (initialized)
        return;
    initialized = true;

    WNDCLASSEXW wndClass = {0};
    wndClass.cbSize = sizeof(wndClass);
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = DefWindowProcW;
    wndClass.hCursor = LoadCursor(0, IDC_ARROW);
    wndClass.hInstance = GetModuleHandle(0);
    wndClass.lpszClassName = hostWindowClassName;

    RegisterClassExW(&wndClass);
}

PlatformWebView::PlatformWebView(WKPageConfigurationRef configuration, const TestOptions& options)
    : m_view(nullptr)
    , m_window(NULL)
    , m_windowIsKey(true)
    , m_options(options)
#if OS(WINDOWS)
    , m_viewWindow(NULL)
#endif
{
    registerWindowClass();

    RECT viewRect = {0, 0, 800, 600};
    m_window = CreateWindowExW(0, hostWindowClassName, L"WebKitTestRunner", WS_OVERLAPPEDWINDOW, 0 /*XOFFSET*/, 0 /*YOFFSET*/, viewRect.right, viewRect.bottom, 0, 0, GetModuleHandle(0), 0);

    HRESULT hr = WebKitCreateInstance(CLSID_WebView, 0, IID_IWebView, reinterpret_cast<void**>(&m_view));
    if (FAILED(hr)) {
        ASSERT_NOT_REACHED();
        return;
    }

    m_view->setHostWindow(m_window);

    COMPtr<ITestRunnerWebView> testRunnerWebView;
    hr = m_view->QueryInterface(IID_ITestRunnerWebView, reinterpret_cast<void**>(&testRunnerWebView.GetInterfacePtr()));
    if (FAILED(hr)) {
        ASSERT_NOT_REACHED();
        return;
    }

    testRunnerWebView->setPageConfiguration((long*)configuration);

    hr = m_view->initWithFrame(viewRect, L"PlatformWebViewFrame", L"WebKitTestRunner");
    if (FAILED(hr)) {
        ASSERT_NOT_REACHED();
        return;
    }

    COMPtr<IWebViewPrivate> webViewPrivate;
    hr = m_view->QueryInterface(IID_IWebViewPrivate, reinterpret_cast<void**>(&webViewPrivate.GetInterfacePtr()));
    if (FAILED(hr)) {
        ASSERT_NOT_REACHED();
        return;
    }

    webViewPrivate->viewWindow(&m_viewWindow);
}

PlatformWebView::~PlatformWebView()
{
    if (::IsWindow(m_window))
        ::DestroyWindow(m_window);
    m_view->Release();
}

void PlatformWebView::setWindowIsKey(bool isKey)
{
    m_windowIsKey = isKey;
}

void PlatformWebView::resizeTo(unsigned width, unsigned height)
{
    ::SetWindowPos(m_viewWindow, 0, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS);
}

WKPageRef PlatformWebView::page()
{
    COMPtr<ITestRunnerWebView> testRunnerWebView;
    HRESULT hr = m_view->QueryInterface(IID_ITestRunnerWebView, reinterpret_cast<void**>(&testRunnerWebView.GetInterfacePtr()));
    if (FAILED(hr)) {
        ASSERT_NOT_REACHED();
        return nullptr;
    }

    long* pageRef = nullptr;
    testRunnerWebView->pageRef(&pageRef);

    return reinterpret_cast<WKPageRef>(pageRef);
}

void PlatformWebView::focus()
{
    ::SetFocus(m_viewWindow);
}

WKRect PlatformWebView::windowFrame()
{
    notImplemented();
    return WKRect();
}

void PlatformWebView::setWindowFrame(WKRect frame)
{
    notImplemented();
}

void PlatformWebView::addChromeInputField()
{
    notImplemented();
}

void PlatformWebView::removeChromeInputField()
{
    notImplemented();
}

void PlatformWebView::makeWebViewFirstResponder()
{
    notImplemented();
}

void PlatformWebView::changeWindowScaleIfNeeded(float)
{
    notImplemented();
}

WKRetainPtr<WKImageRef> PlatformWebView::windowSnapshotImage()
{
    notImplemented();
    return nullptr;
}

bool PlatformWebView::viewSupportsOptions(const TestOptions& options) const
{
    notImplemented();
    return false;
}

void PlatformWebView::didInitializeClients()
{
    notImplemented();
}

void PlatformWebView::setNavigationGesturesEnabled(bool)
{
    notImplemented();
}

} // namespace WTR

