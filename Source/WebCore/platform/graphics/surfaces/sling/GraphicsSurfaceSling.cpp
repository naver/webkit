/*
 * Copyright (C) 2014 Naver Corp. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "GraphicsSurface.h"

#if USE(GRAPHICS_SURFACE)

#include "GraphicsSurfacePbufferPrivate.h"
#include "NotImplemented.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

namespace WebCore {

GraphicsSurfacePrivate* GraphicsSurfacePrivate::create(uint32_t fb, const IntSize& size, GraphicsSurface::Flags flags, const PlatformGraphicsContext3D shareContext)
{
    return new GraphicsSurfacePbufferPrivate(fb, size, flags, shareContext);
}

PassRefPtr<GraphicsSurface> GraphicsSurface::platformCreate(const IntSize& size, GraphicsSurface::Flags flags, const PlatformGraphicsContext3D shareContext)
{
    RefPtr<GraphicsSurface> surface = adoptRef(new GraphicsSurface(size, flags));
    surface->m_private = GraphicsSurfacePrivate::create(0, size, flags, shareContext);
    surface->m_private->m_owner = surface.get();
    return surface;
}

PassRefPtr<GraphicsSurface> GraphicsSurface::platformImport(const IntSize& size, Flags flags, const GraphicsSurfaceToken& token)
{
    RefPtr<GraphicsSurface> surface = adoptRef(new GraphicsSurface(size, flags));
    surface->m_private = GraphicsSurfacePrivate::create(token.frontBufferHandle, size, flags);
    surface->m_private->m_owner = surface.get();
    return surface;
}

GraphicsSurfaceToken GraphicsSurface::platformExport()
{
    if (!m_private)
        return GraphicsSurfaceToken();

    return GraphicsSurfaceToken(m_private->frontBuffer());
}

void GraphicsSurface::platformDestroy()
{
    if (m_fbo) {
        glDeleteFramebuffers(1, &m_fbo);
        m_fbo = 0;
    }

    if (m_private) {
        m_private->destroy();
        delete m_private;
        m_private = 0;
    }
}

uint32_t GraphicsSurface::platformGetTextureID()
{
    if (!m_private)
        return 0;

    return m_private->textureId();
}

char* GraphicsSurface::platformLock(const IntRect& rect, int* /*outputStride*/, LockOptions lockOptions)
{
    if (!m_private)
        return nullptr;

    m_private->lock(rect, lockOptions);
    return 0;
}

void GraphicsSurface::platformUnlock()
{
}

void GraphicsSurface::platformCopyToGLTexture(uint32_t target, uint32_t texture, const IntRect& targetRect, const IntPoint& offset)
{
    if (!m_fbo)
        glGenFramebuffers(1, &m_fbo);

    uint32_t sourceTexture = m_private->textureId();

    glBindTexture(target, texture);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, sourceTexture, 0);
    glCopyTexSubImage2D(target, 0, targetRect.x(), targetRect.y(), offset.x(), offset.y(), targetRect.width(), targetRect.height());
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // If the web process starts rendering and unlocks the surface before this happens, we might copy contents
    // of the currently rendering frame on our texture instead of the previously completed frame.
    // Flush the command buffer to reduce the odds of this happening, this would not be necessary with double buffering.
    glFlush();
}

void GraphicsSurface::platformCopyFromTexture(uint32_t texture, const IntRect&)
{
    if (!m_private)
        return;

    m_private->copyFromTexture(texture);
}

void GraphicsSurface::platformPaintToTextureMapper(TextureMapper& textureMapper, const FloatRect& targetRect, const TransformationMatrix& transform, float opacity)
{
    if (!m_private)
        return;

    m_private->paintToTextureMapper(textureMapper, targetRect, transform, opacity);
}

uint32_t GraphicsSurface::platformFrontBuffer() const
{
    if (!m_private)
        return 0;

    return m_private->frontBuffer();
}

uint32_t GraphicsSurface::platformSwapBuffers()
{
    if (!m_private)
        return 0;

    return m_private->swapBuffers();
}

IntSize GraphicsSurface::platformSize() const
{
    if (!m_private)
        return IntSize();

    return m_private->size();
}

std::unique_ptr<GraphicsContext> GraphicsSurface::platformBeginPaint(const IntSize&, char*, int)
{
    if (!m_private)
        return nullptr;

    return m_private->beginPaint();
}

PassRefPtr<Image> GraphicsSurface::createReadOnlyImage(const IntRect& rect)
{
    if (!m_private)
        return nullptr;

    return m_private->createReadOnlyImage(rect);
}

}

#endif // USE(GRAPHICS_SURFACE)
