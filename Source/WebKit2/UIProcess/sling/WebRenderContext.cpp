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
#include "WebRenderContext.h"

#include "WTFMainThread.h"
#include "WebRenderer.h"

using namespace webkit::wtf;

namespace webkit {

std::shared_ptr<WebRenderContext> WebRenderContext::create(std::shared_ptr<SWKView>& view)
{
    return std::shared_ptr<WebRenderContext>(new WebRenderContext(view));
}

WebRenderContext::WebRenderContext(std::shared_ptr<SWKView>& view)
    : m_renderer(WebRenderer::create(view))
{
}

WebRenderContext::~WebRenderContext()
{
}

void WebRenderContext::beginPaint()
{
    WTFMainThread::initializeUIWorkerThread();
    m_renderer->beginPaint();
}

void WebRenderContext::paint()
{
    m_renderer->paint();
}

void WebRenderContext::endPaint()
{
    m_renderer->endPaint();
}

void WebRenderContext::contextLost()
{
    m_renderer->contextLost();
}

void WebRenderContext::teardown()
{
    m_renderer->teardown();
}

} // namespace webkit
