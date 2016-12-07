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

#ifndef GraphicsSurfacePbufferPrivate_h
#define GraphicsSurfacePbufferPrivate_h

#if USE(GRAPHICS_SURFACE)

#include "GraphicsSurface.h"
#include "GraphicsSurfacePbufferNatives.h"
#include "GraphicsSurfacePrivate.h"
#include "GraphicsSurfaceTextureHostNatives.h"
#include "IntRect.h"

#include <onig/GlobalRef.h>

namespace WebCore {

enum class MakeCurrentResult;

class GraphicsSurfacePbufferPrivate : public GraphicsSurfacePrivate {
    friend class AutoMakeCurrent;
public:
    GraphicsSurfacePbufferPrivate(uint32_t frontBufferHandle, const IntSize&, GraphicsSurface::Flags, const PlatformGraphicsContext3D);
    ~GraphicsSurfacePbufferPrivate();

    uint32_t swapBuffers() override;

    GLuint textureId() const override;

    void copyFromTexture(uint32_t, DrawOption) override;
    void paintToTextureMapper(TextureMapper&, const FloatRect&, const TransformationMatrix&, float) override;

    bool lock(const IntRect&, GraphicsSurface::LockOptions) override;
    std::unique_ptr<GraphicsContext> beginPaint() override;
    void flush() override;
    void reset(const IntSize&, GraphicsSurface::Flags, const PlatformGraphicsContext3D) override;

#if USE(CAIRO)
    virtual cairo_device_t* cairoDevice();
#endif

private:
    void createPbufferSurface(PlatformGraphicsContext3D);
    void importFrontBufferTexture();
    void releaseFrontBufferTexture();
    uint32_t frontBufferTextureID();
    MakeCurrentResult makeCurrent();
    bool doneCurrent();
    std::unique_ptr<GraphicsContext> createGraphicsContext();

private:
    int32_t m_frontBufferShareHandle;
    GLuint m_frontBufferTexture;
    bool m_published;

#if USE(CAIRO)
    cairo_device_t* m_cairoDevice;
    RefPtr<cairo_surface_t> m_cairoSurface;
#endif
    std::unique_ptr<GraphicsContext> m_graphicsContext;

    Native::GlobalRef<WebKit::GraphicsSurfacePbuffer> m_pbuffer;
    Native::GlobalRef<WebKit::GraphicsSurfaceTextureHost> m_texture;
};


} // namespace WebCore
#endif

#endif // GraphicsSurfacePbufferPrivate_h
