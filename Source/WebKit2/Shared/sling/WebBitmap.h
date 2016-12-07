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

#ifndef WebBitmap_h
#define WebBitmap_h

#include "WebBitmapManagedBase.h"

namespace view {
class Bitmap;
}

namespace webkit {

class NATIVE_EXPORT WebBitmap : public WebKit::Managed::WebBitmap {
    friend class WebKit::Managed::WebBitmap;
public:
    WebBitmap();
    ~WebBitmap();

    void setPixels(const std::vector<int32_t>&, int32_t offset, int32_t stride, int32_t x, int32_t y, int32_t width, int32_t height) override;
    void getPixels(const std::vector<int32_t>&, int32_t offset, int32_t stride, int32_t x, int32_t y, int32_t width, int32_t height) override;

    int32_t getWidth() override;
    int32_t getHeight() override;

    int32_t getRowBytes() override;
    int32_t getByteCount() override;

    std::shared_ptr<view::Bitmap> getBitmap() { return m_bitmap; }

private:
    void INIT(const std::vector<int32_t>& colors, int32_t width, int32_t height, int32_t config) override;

    std::shared_ptr<view::Bitmap> m_bitmap;
};

} // namespace webkit

#endif
