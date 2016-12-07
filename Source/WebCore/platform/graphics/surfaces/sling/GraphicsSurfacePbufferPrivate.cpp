/*

 Copyright (C) 2012 Zeno Albisser <zeno@webkit.org>
 Copyright (C) 2015 Naver Corp. All rights reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Library General Public
 License as published by the Free Software Foundation; either
 version 2 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Library General Public License for more details.

 You should have received a copy of the GNU Library General Public License
 along with this library; see the file COPYING.LIB.  If not, write to
 the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 Boston, MA 02110-1301, USA.
 */

#include "config.h"
#include "GraphicsSurfacePbufferPrivate.h"

#include <GLES2/gl2.h>
#include <utility>

#if USE(CAIRO)
#include <cairo-gl.h>
#endif

#if USE(GRAPHICS_SURFACE)

namespace WebCore {

enum class MakeCurrentResult {
    Success,
    Failure,
    NoOp
};

class AutoMakeCurrent {
    WTF_MAKE_NONCOPYABLE(AutoMakeCurrent);
public:
    explicit AutoMakeCurrent(GraphicsSurfacePbufferPrivate& instance)
        : m_instance(instance)
    {
        m_state = m_instance.makeCurrent();
    }
    ~AutoMakeCurrent()
    {
        if (MakeCurrentResult::Success == m_state)
            m_instance.doneCurrent();
    }
    bool operator!() const { return m_state == MakeCurrentResult::Failure; }
private:
    MakeCurrentResult m_state;
    GraphicsSurfacePbufferPrivate& m_instance;
};

GraphicsSurfacePbufferPrivate::GraphicsSurfacePbufferPrivate(uint32_t frontBufferHandle, const IntSize& size, GraphicsSurface::Flags flags, const PlatformGraphicsContext3D shareContext)
    : GraphicsSurfacePrivate(frontBufferHandle, size, flags, shareContext)
    , m_frontBufferShareHandle(frontBufferHandle)
    , m_frontBufferTexture(0)
    , m_published(false)
#if USE(CAIRO)
    , m_cairoDevice(0)
#endif
{
    if (!frontBufferHandle)
        createPbufferSurface(shareContext);
}

void GraphicsSurfacePbufferPrivate::createPbufferSurface(PlatformGraphicsContext3D shareContext)
{
    m_pbuffer = WebKit::GraphicsSurfacePbuffer::create(0, 0, reinterpret_cast<int64_t>(shareContext), m_size.width(), m_size.height());
    if (!m_pbuffer)
        return;

    m_frontBufferShareHandle = m_pbuffer->getShareIdentifier();
    m_frontBuffer = m_frontBufferShareHandle;
}

void GraphicsSurfacePbufferPrivate::importFrontBufferTexture()
{
    if (!m_texture) {
        m_texture = WebKit::GraphicsSurfaceTextureHost::create(0, m_frontBufferShareHandle);
        if (m_texture)
            m_frontBufferTexture = static_cast<GLuint>(m_texture->getGLTexture());
    }
}

GraphicsSurfacePbufferPrivate::~GraphicsSurfacePbufferPrivate()
{
    AutoMakeCurrent autoMakeCurrent(*this);
    if (!autoMakeCurrent)
        return;

#if USE(CAIRO)
    if (m_cairoSurface)
        m_cairoSurface.release();

    if (m_cairoDevice)
        cairo_device_destroy(m_cairoDevice);
#endif

    releaseFrontBufferTexture();
}

uint32_t GraphicsSurfacePbufferPrivate::swapBuffers()
{
    importFrontBufferTexture();

    if (m_texture)
        m_texture->swapBuffers();

    return m_frontBufferTexture;
}

GLuint GraphicsSurfacePbufferPrivate::textureId() const
{
    return const_cast<GraphicsSurfacePbufferPrivate*>(this)->frontBufferTextureID();
}

void GraphicsSurfacePbufferPrivate::copyFromTexture(uint32_t texture, DrawOption drawOption)
{
    AutoMakeCurrent autoMakeCurrent(*this);
    if (!autoMakeCurrent)
        return;

    if (!m_published) {
        m_pbuffer->publishSurface();
        m_published = true;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    m_pbuffer->copyFromTexture(texture, drawOption == DrawOption::Flip ? true : false);
}

void GraphicsSurfacePbufferPrivate::paintToTextureMapper(TextureMapper& textureMapper, const FloatRect& targetRect, const TransformationMatrix& transform, float opacity)
{
    FloatRect rectOnContents(FloatPoint::zero(), m_size);
    TransformationMatrix adjustedTransform = transform;
    adjustedTransform.multiply(TransformationMatrix::rectToRect(rectOnContents, targetRect));

    TextureMapperGL::Flags flags = m_flags & GraphicsSurface::SupportsAlpha ? TextureMapperGL::ShouldBlend : 0;
    static_cast<TextureMapperGL&>(textureMapper).drawTexture(textureId(), flags, m_size, rectOnContents, adjustedTransform, opacity);
}

#if USE(CAIRO)
static PassRefPtr<cairo_surface_t> createCairoGLSurface(const FloatSize& size, GraphicsSurfacePbufferPrivate* graphicsSurfacePrivate)
{
    cairo_device_t* device = graphicsSurfacePrivate->cairoDevice();
    AutoMakeCurrent autoMakeCurrent(*graphicsSurfacePrivate);
    return adoptRef(cairo_gl_surface_create_for_egl(device, eglGetCurrentSurface(EGL_DRAW), size.width(), size.height()));
}
#endif

bool GraphicsSurfacePbufferPrivate::lock(const IntRect& rect, GraphicsSurface::LockOptions)
{
    m_graphicsContext = createGraphicsContext();
    if (!m_graphicsContext)
        return false;

    m_graphicsContext->clip(rect);
    m_graphicsContext->translate(rect.x(), rect.y());
    return true;
}

std::unique_ptr<GraphicsContext> GraphicsSurfacePbufferPrivate::beginPaint()
{
    return WTFMove(m_graphicsContext);
}

std::unique_ptr<GraphicsContext> GraphicsSurfacePbufferPrivate::createGraphicsContext()
{
#if USE(CAIRO)
    if (!m_cairoSurface)
        m_cairoSurface = createCairoGLSurface(m_size, this);

    RefPtr<cairo_t> cairoContext = adoptRef(cairo_create(m_cairoSurface.get()));
    return std::make_unique<GraphicsContext>(cairoContext.get());
#endif
    return nullptr;
}

MakeCurrentResult GraphicsSurfacePbufferPrivate::makeCurrent()
{
    if (m_texture)
        return MakeCurrentResult::NoOp;

    return m_pbuffer->makeCurrent() ? MakeCurrentResult::Success : MakeCurrentResult::Failure;
}

bool GraphicsSurfacePbufferPrivate::doneCurrent()
{
    return m_pbuffer->doneCurrent();
}

uint32_t GraphicsSurfacePbufferPrivate::frontBufferTextureID()
{
    importFrontBufferTexture();

    return m_frontBufferTexture;
}

void GraphicsSurfacePbufferPrivate::releaseFrontBufferTexture()
{
    m_frontBufferTexture = 0;

    m_texture.reset();
}

#if USE(CAIRO)
cairo_device_t* GraphicsSurfacePbufferPrivate::cairoDevice()
{
    if (!m_cairoDevice) {
        AutoMakeCurrent autoMakeCurrent(*this);
        if (!autoMakeCurrent)
            return nullptr;

        m_cairoDevice = cairo_egl_device_create(eglGetCurrentDisplay(), eglGetCurrentContext());
        // Thread-awareness is a huge performance hit on non-Intel drivers.
        cairo_gl_device_set_thread_aware(m_cairoDevice, FALSE);
    }

    return m_cairoDevice;
}
#endif

void GraphicsSurfacePbufferPrivate::flush()
{
    if (m_cairoSurface)
        cairo_surface_flush(m_cairoSurface.get());

    AutoMakeCurrent autoMakeCurrent(*this);
    if (!autoMakeCurrent)
        return;

    glFinish();
}

void GraphicsSurfacePbufferPrivate::reset(const IntSize& size, GraphicsSurface::Flags, const PlatformGraphicsContext3D shareContext)
{
    if (!m_pbuffer || size == m_size)
        return;

    m_size = size;

    m_pbuffer->reset(reinterpret_cast<int64_t>(shareContext), m_size.width(), m_size.height());

    m_frontBufferShareHandle = m_pbuffer->getShareIdentifier();
    m_frontBuffer = m_frontBufferShareHandle;
    m_published = false;
}

} // namespace WebCore

#endif // USE(GRAPHICS_SURFACE)
