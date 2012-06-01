/*
 * Copyright (C) 2011 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CCSharedQuadState_h
#define CCSharedQuadState_h

#include "FloatQuad.h"
#include "IntRect.h"
#include <public/WebTransformationMatrix.h>
#include <wtf/PassOwnPtr.h>

namespace WebCore {

class CCSharedQuadState {
    WTF_MAKE_NONCOPYABLE(CCSharedQuadState);
public:
    static PassOwnPtr<CCSharedQuadState> create(const WebKit::WebTransformationMatrix& quadTransform, const WebKit::WebTransformationMatrix& layerTransform, const IntRect& layerRect, const IntRect& clipRect, float opacity, bool opaque);

    // The transform that quads in a CCDrawQuad should be transformed with.
    const WebKit::WebTransformationMatrix& quadTransform() const { return m_quadTransform; }
    // The transform that layerRect() should be transformed with.
    const WebKit::WebTransformationMatrix& layerTransform() const { return m_layerTransform; }
    const IntRect& layerRect() const { return m_layerRect; }
    // Usage: if clipRect is empty, this clipRect should not be used.
    const IntRect& clipRect() const { return m_clipRect; }

    float opacity() const { return m_opacity; }
    bool isOpaque() const { return m_opaque; }
    bool isLayerAxisAlignedIntRect() const;

private:
    CCSharedQuadState(const WebKit::WebTransformationMatrix& quadTransform, const WebKit::WebTransformationMatrix& layerTransform, const IntRect& layerRect, const IntRect& clipRect, float opacity, bool opaque);

    WebKit::WebTransformationMatrix m_quadTransform;
    WebKit::WebTransformationMatrix m_layerTransform;
    IntRect m_layerRect;
    IntRect m_clipRect;
    float m_opacity;
    bool m_opaque;
};

}

#endif
