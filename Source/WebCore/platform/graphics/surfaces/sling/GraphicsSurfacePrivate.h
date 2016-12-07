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

#ifndef GraphicsSurfacePrivate_h
#define GraphicsSurfacePrivate_h

#if USE(GRAPHICS_SURFACE)

#include "GraphicsSurface.h"
#include "TextureMapperGL.h"

namespace WebCore {

class GraphicsSurface;

class GraphicsSurfacePrivate {
    friend class GraphicsSurface;
public:
    enum Flag {
        SupportsTextureStreaming = 0x1000
    };

    enum class DrawOption {
        Normal = 0,
        Flip = 1
    };

    static GraphicsSurfacePrivate* create(uint32_t, const IntSize&, GraphicsSurface::Flags, const PlatformGraphicsContext3D shareContext = 0);
    virtual ~GraphicsSurfacePrivate()
    {
    }

    GraphicsSurface::Flags flags() const { return m_flags; }
    const FloatRect& rect() const { return m_rect; }
    const IntSize& size() const { return m_size; }
    virtual uint32_t frontBuffer() const { return m_frontBuffer; }

    virtual void destroy() { }
    virtual uint32_t swapBuffers() { return 0; }

    virtual GLuint textureId() const { return 0; }

    virtual void copyToGLTexture(uint32_t, uint32_t, const IntRect&, const IntPoint&) { }
    virtual void copyFromTexture(uint32_t, DrawOption = DrawOption::Normal) { }
    virtual bool copyToBitmapTexture(BitmapTexture*, const IntRect&, const IntPoint&) { return false; }
    virtual void paintToTextureMapper(TextureMapper&, const FloatRect&, const TransformationMatrix&, float) { }

    virtual bool lock(const IntRect&, GraphicsSurface::LockOptions) { return false; }
    virtual std::unique_ptr<GraphicsContext> beginPaint() { return nullptr; }
    virtual PassRefPtr<Image> createReadOnlyImage(const IntRect&) { return nullptr; }
    virtual void flush() { }
    virtual void reset(const IntSize&, GraphicsSurface::Flags, const PlatformGraphicsContext3D) { }

protected:
    GraphicsSurfacePrivate() { }
    GraphicsSurfacePrivate(uint32_t fb, const IntSize& size, GraphicsSurface::Flags flags, const PlatformGraphicsContext3D)
        : m_flags(flags)
        , m_rect(FloatPoint::zero(), size)
        , m_size(size)
        , m_frontBuffer(fb)
        , m_owner(0)
    {
    }

    GraphicsSurface::Flags m_flags;
    FloatRect m_rect;
    IntSize m_size;
    uint32_t m_frontBuffer;
    GraphicsSurface* m_owner;
};

}
#endif // USE(GRAPHICS_SURFACE)

#endif // GraphicsSurfacePrivate_h
