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
#include "GraphicsSurfacePbuffer.h"

#include <opengl/EGLOffscreenContext.h>
#include <opengl/GLTextureHandle.h>
#include <opengl/GLTextureStreamChannel.h>

using namespace opengl;

namespace webkit {

GraphicsSurfacePbuffer::GraphicsSurfacePbuffer()
{
}

GraphicsSurfacePbuffer::~GraphicsSurfacePbuffer()
{
}

void GraphicsSurfacePbuffer::INIT(int64_t eglDisplay, int64_t eglConfig, int64_t eglShareContext, int32_t surfaceWidth, int32_t surfaceHeight)
{
    m_surface = EGLPbufferSurface::create(reinterpret_cast<EGLDisplay>(eglDisplay), reinterpret_cast<EGLConfig>(eglConfig), reinterpret_cast<EGLContext>(eglShareContext), surfaceWidth, surfaceHeight);
}

bool GraphicsSurfacePbuffer::makeCurrent()
{
    return m_surface->getContext()->makeCurrent();
}

bool GraphicsSurfacePbuffer::doneCurrent()
{
    return m_surface->getContext()->doneCurrent();
}

int32_t GraphicsSurfacePbuffer::getShareIdentifier()
{
    return (m_surface->channel()) ? m_surface->channel()->shareIdentifier() : 0;
}

void GraphicsSurfacePbuffer::publishSurface()
{
    m_surface->publish();
}

bool GraphicsSurfacePbuffer::copyFromTexture(int32_t texture, bool flip)
{
    return m_surface->copyFromTexture(*GLTextureHandle::create(texture), flip);
}

void GraphicsSurfacePbuffer::reset(int64_t eglShareContext, int32_t surfaceWidth, int32_t surfaceHeight)
{
    m_surface->reset(reinterpret_cast<EGLContext>(eglShareContext), surfaceWidth, surfaceHeight);
}

} // namespace WebKit

namespace WebKit {
namespace Managed {

void GraphicsSurfacePbuffer::INIT(int64_t, int64_t, int64_t, int32_t, int32_t)
{
}

} // namespace Managed
} // namespace WebKit
