#pragma once

#include "nanovg.hpp"
#define NANOVG_GL2_IMPLEMENTATION
#include "nanovg_gl.h"

namespace ofx { namespace nvg {
    
    Context createContextGL2(bool antiAlias = true, bool stencilStrokes = false) {
        int flags = (antiAlias      ? NVG_ANTIALIAS       : 0) |
        (stencilStrokes ? NVG_STENCIL_STROKES : 0);
        
        return { Context::BackingCtx{ nvgCreateGL2(flags), nvgDeleteGL2 } };
    }
    
}} // ofx::nvg