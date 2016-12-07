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

#ifndef GraphicsSurfacePbuffer_h
#define GraphicsSurfacePbuffer_h

#include "GraphicsSurfacePbufferManagedBase.h"

#include <opengl/EGLPbufferSurface.h>

namespace webkit {

class WEBKIT_EXPORT GraphicsSurfacePbuffer final : public WebKit::Managed::GraphicsSurfacePbuffer {
    friend class WebKit::Managed::GraphicsSurfacePbuffer;
public:
    ~GraphicsSurfacePbuffer();

    bool makeCurrent() override;

    bool doneCurrent() override;

    int32_t getShareIdentifier() override;

    void publishSurface() override;

    bool copyFromTexture(int32_t texture, bool flip) override;

    void reset(int64_t eglShareContext, int32_t surfaceWidth, int32_t surfaceHeight) override;

private:
    GraphicsSurfacePbuffer();

    void INIT(int64_t eglDisplay, int64_t eglConfig, int64_t eglShareContext, int32_t surfaceWidth, int32_t surfaceHeight) override;

    std::shared_ptr<opengl::EGLPbufferSurface> m_surface;
};

} // namespace webkit

#endif
