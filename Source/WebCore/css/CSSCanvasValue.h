/*
 * Copyright (C) 2008 Apple Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "CSSImageGeneratorValue.h"
#include "HTMLCanvasElement.h"

namespace WebCore {

class Document;
class HTMLCanvasElement;

class CSSCanvasValue : public CSSImageGeneratorValue {
public:
    static Ref<CSSCanvasValue> create(const String& name) { return adoptRef(*new CSSCanvasValue(name)); }
    ~CSSCanvasValue();

    String customCSSText() const;

    RefPtr<Image> image(RenderElement*, const FloatSize&);
    bool isFixedSize() const { return true; }
    FloatSize fixedSize(const RenderElement*);

    bool isPending() const { return false; }
    void loadSubimages(CachedResourceLoader&, const ResourceLoaderOptions&) { }

    bool equals(const CSSCanvasValue&) const;

private:
    explicit CSSCanvasValue(const String& name)
        : CSSImageGeneratorValue(CanvasClass)
        , m_canvasObserver(*this)
        , m_name(name)
    {
    }

    // NOTE: We put the CanvasObserver in a member instead of inheriting from it
    // to avoid adding a vptr to CSSCanvasValue.
    class CanvasObserverProxy final : public CanvasObserver {
    public:
        explicit CanvasObserverProxy(CSSCanvasValue& ownerValue)
            : m_ownerValue(ownerValue)
        {
        }

        virtual ~CanvasObserverProxy()
        {
        }

    private:
        void canvasChanged(HTMLCanvasElement& canvas, const FloatRect& changedRect) override
        {
            m_ownerValue.canvasChanged(canvas, changedRect);
        }
        void canvasResized(HTMLCanvasElement& canvas) override
        {
            m_ownerValue.canvasResized(canvas);
        }
        void canvasDestroyed(HTMLCanvasElement& canvas) override
        {
            m_ownerValue.canvasDestroyed(canvas);
        }

        CSSCanvasValue& m_ownerValue;
    };

    void canvasChanged(HTMLCanvasElement&, const FloatRect& changedRect);
    void canvasResized(HTMLCanvasElement&);
    void canvasDestroyed(HTMLCanvasElement&);

    HTMLCanvasElement* element(Document&);

    CanvasObserverProxy m_canvasObserver;

    // The name of the canvas.
    String m_name;
    // The document supplies the element and owns it.
    HTMLCanvasElement* m_element { nullptr };
};

} // namespace WebCore

SPECIALIZE_TYPE_TRAITS_CSS_VALUE(CSSCanvasValue, isCanvasValue())

