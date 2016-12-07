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
#include "EGLPbufferSurface.h"

#if USE(EGL) && USE(GRAPHICS_SURFACE)

#include "EGLConfigSelector.h"
#include "EGLHelper.h"
#include "GLPlatformContext.h"

namespace WebCore {

EGLPbufferSurface::EGLPbufferSurface(GLPlatformSurface::SurfaceAttributes surfaceAttributes)
    : EGLOffScreenSurface(surfaceAttributes)
{
    if (!m_configSelector)
        return;

    EGLConfig config = configuration();

    if (!config) {
        destroy();
        return;
    }

    const EGLint contextAttributes[] = {
#if USE(OPENGL_ES_2)
        EGL_CONTEXT_CLIENT_VERSION, 2,
#endif
        EGL_NONE
    };

    EGLContext context = eglCreateContext(EGLHelper::eglDisplay(), config, 0, contextAttributes);
    if (context == EGL_NO_CONTEXT) {
        destroy();
        return;
    }
    m_bufferHandle = reinterpret_cast<PlatformBufferHandle>(context);

    static const int pbufferAttributes[] = { EGL_WIDTH, 1, EGL_HEIGHT, 1, EGL_NONE };
    m_drawable = eglCreatePbufferSurface(EGLHelper::eglDisplay(), config, pbufferAttributes);
    if (m_drawable == EGL_NO_SURFACE) {
        LOG_ERROR("Failed to create EGL surface(%d).", eglGetError());
        destroy();
    }
}

EGLPbufferSurface::~EGLPbufferSurface()
{
}

void EGLPbufferSurface::destroy()
{
    EGLOffScreenSurface::destroy();

    if (m_bufferHandle) {
        eglDestroyContext(EGLHelper::eglDisplay(), reinterpret_cast<EGLContext>(m_bufferHandle));
        m_bufferHandle = 0;
    }
}

}

#endif
