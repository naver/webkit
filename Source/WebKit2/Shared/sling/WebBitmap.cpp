/*
 * Copyright (C) 2016 Naver Corp. All rights reserved.
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
#include "WebBitmap.h"

#include <view/Bitmap.h>

namespace webkit {

WebBitmap::WebBitmap()
{
}

WebBitmap::~WebBitmap()
{
}

static view::Bitmap::Config integerToConfig(int config)
{
    switch (config) {
    case WebBitmap::CONFIG_ALPHA_8:
        return view::Bitmap::Config::ALPHA_8;
    case WebBitmap::CONFIG_RGB_565:
        return view::Bitmap::Config::RGB_565;
    case WebBitmap::CONFIG_ARGB_8888:
        return view::Bitmap::Config::ARGB_8888;
    default:
        return view::Bitmap::Config::INVALID;
    }
}
void WebBitmap::INIT(const std::vector<int32_t>& colors, int32_t width, int32_t height, int32_t config)
{
    m_bitmap = view::Bitmap::createBitmap(colors, width, height, integerToConfig(config));
}

void WebBitmap::setPixels(const std::vector<int32_t>& pixels, int32_t offset, int32_t stride, int32_t x, int32_t y, int32_t width, int32_t height)
{
    m_bitmap->setPixels(pixels, offset, stride, x, y, width, height);
}

void WebBitmap::getPixels(const std::vector<int32_t>& pixels, int32_t offset, int32_t stride, int32_t x, int32_t y, int32_t width, int32_t height)
{
    m_bitmap->getPixels(const_cast<std::vector<int32_t>&>(pixels), offset, stride, x, y, width, height);
}

int32_t WebBitmap::getWidth()
{
    return m_bitmap->getWidth();
}

int32_t WebBitmap::getHeight()
{
    return m_bitmap->getHeight();
}

int32_t WebBitmap::getRowBytes()
{
    return m_bitmap->getRowBytes();
}

int32_t WebBitmap::getByteCount()
{
    return m_bitmap->getByteCount();
}

} // namespace webkit

namespace WebKit {
namespace Managed {

void WebBitmap::INIT(const std::vector<int32_t>&, int32_t, int32_t, int32_t)
{
}

}
} // namespace WebKit

