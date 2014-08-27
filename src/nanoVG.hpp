#pragma once

#define NANOVG_GL2_IMPLEMENTATION 1
#include "nanovg.h"
#include "nanovg_gl.h"

#include "ofMain.h"
#include <memory>
#include <string>

namespace ofx { namespace nvg {
    
    class Context {
    public:
        Context( bool antiAlias = true, bool stencilStrokes = false )
        {
            int flags = (antiAlias ? NVG_ANTIALIAS : 0 ) |
                        (stencilStrokes ? NVG_STENCIL_STROKES : 0 );
        
            mCtx = std::shared_ptr<NVGcontext>( nvgCreateGL2( flags ) );
            
        }
        
        ~Context()
        {
                //nvgDeleteInternal( get() );
        }
        
        inline NVGcontext* get() { return mCtx.get(); }
        
        // Frame //
        
        inline void beginFrame(int windowWidth, int windowHeight, float devicePixelRatio) {
            nvgBeginFrame(get(), windowWidth, windowHeight, devicePixelRatio);
        }
        inline void beginFrame(const ofVec2f& windowSize, float devicePixelRatio) {
            beginFrame(windowSize.x, windowSize.y, devicePixelRatio);
        }
        inline void endFrame() {
            nvgEndFrame(get());
        }
        
        // State Handling //
        
        inline void save() { nvgSave(get()); }
        inline void restore() { nvgRestore(get()); }
        inline void reset() { nvgReset(get()); }
        
        // Render Styles //
        
        inline void strokeColor(const NVGcolor& color) {
            nvgStrokeColor(get(), color);
        }
        inline void strokeColor(const ofFloatColor& color) {
            strokeColor(reinterpret_cast<const NVGcolor&>(color));
        }
        inline void strokePaint(const NVGpaint& paint) {
            nvgStrokePaint(get(), paint);
        }
        inline void fillColor(const NVGcolor& color) {
            nvgFillColor(get(), color);
        }
        inline void fillColor(const ofFloatColor& color) {
            fillColor(reinterpret_cast<const NVGcolor&>(color));
        }
        inline void fillPaint(const NVGpaint& paint) {
            nvgFillPaint(get(), paint);
        }
        
        inline void miterLimit(float limit) { nvgMiterLimit(get(), limit); }
        inline void strokeWidth(float size) { nvgStrokeWidth(get(), size); }
        inline void lineCap(int cap) { nvgLineCap(get(), cap); }
        inline void lineJoin(int join) { nvgLineJoin(get(), join); }
        
        // Transform //
        
        inline void resetTransform() {
            nvgResetTransform(get());
        }
        inline void transform(const ofMatrix3x3& mtx) {
            nvgTransform(get(), mtx.a, mtx.b, mtx.c, mtx.d, mtx.e, mtx.f);
        }
        inline void setTransform(const ofMatrix3x3& mtx) {
            resetTransform();
            transform(mtx);
        }
        inline void translate(float x, float y) {
            nvgTranslate(get(), x, y);
        }
        inline void translate(const ofVec2f& translation) {
            translate(translation.x, translation.y);
        }
        inline void rotate(float angle) { nvgRotate(get(), angle); }
        inline void skewX(float angle) { nvgSkewX(get(), angle); }
        inline void skewY(float angle) { nvgSkewY(get(), angle); }
        inline void scale(float x, float y) { nvgScale(get(), x, y); }
        inline void scale(const ofVec2f& s) { scale(s.x, s.y); }
        
        ofMatrix3x3 currentTransform() {
            ofMatrix3x3 xform;
            nvgCurrentTransform(mCtx.get(), &xform[0]);
            return xform;
        }
        
        // Paints //
        
        inline NVGpaint linearGradient(float sx, float sy, float ex, float ey,
                                       NVGcolor icol, NVGcolor ocol) {
            return nvgLinearGradient(get(), sx, sy, ex, ey, icol, ocol);
        }
        inline NVGpaint boxGradient(float x, float y, float w, float h, float r, float f,
                                    NVGcolor icol, NVGcolor ocol) {
            return nvgBoxGradient(get(), x, y, w, h, r, f, icol, ocol);
        }
        inline NVGpaint radialGradient(float cx, float cy, float inr, float outr,
                                       NVGcolor icol, NVGcolor ocol) {
            return nvgRadialGradient(get(), cx, cy, inr, outr, icol, ocol);
        }
        inline NVGpaint imagePattern(float ox, float oy, float ex, float ey,
                                     float angle, int image, int repeat, float alpha) {
            return nvgImagePattern(get(), ox, oy, ex, ey, angle, image, repeat, alpha);
        }
        
        // Scissoring //
        
        inline void scissor(float x, float y, float w, float h) {
            nvgScissor(get(), x, y, w, h);
        }
        inline void resetScissor() {
            nvgResetScissor(get());
        }
        
        // Paths //
        
        inline void beginPath() { nvgBeginPath(get()); }
        inline void moveTo(float x, float y) { nvgMoveTo(get(), x, y); }
        inline void moveTo(const ofVec2f& p) { moveTo(p.x, p.y); }
        inline void lineTo(float x, float y) { nvgLineTo(get(), x, y); }
        inline void lineTo(const ofVec2f& p) { lineTo(p.x, p.y); }
        inline void quadTo(float cx, float cy, float x, float y) {
            nvgQuadTo(get(), cx, cy, x, y);
        }
        inline void quadTo(const ofVec2f& p1, const ofVec2f& p2) {
            quadTo(p1.x, p1.y, p2.x, p2.y);
        }
        inline void bezierTo(float c1x, float c1y, float c2x, float c2y, float x, float y) {
            nvgBezierTo(get(), c1x, c1y, c2x, c2y, x, y);
        }
        inline void bezierTo(const ofVec2f& p1, const ofVec2f& p2, const ofVec2f& p3) {
            bezierTo(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
        }
        inline void arcTo(float x1, float y1, float x2, float y2, float radius) {
            nvgArcTo(get(), x1, y1, x2, y2, radius);
        }
        inline void arcTo(const ofVec2f& p1, const ofVec2f& p2, float radius) {
            arcTo(p1.x, p1.y, p2.x, p2.y, radius);
        }
        inline void closePath() { nvgClosePath(get()); }
        inline void pathWinding(int dir) { nvgPathWinding(get(), dir); }
        inline void arc(float cx, float cy, float r, float a0, float a1, int dir) {
            nvgArc(get(), cx, cy, r, a0, a1, dir);
        }
        inline void arc(const ofVec2f &center, float r, float a0, float a1, int dir) {
            arc(center.x, center.y, r, a0, a1, dir);
        }
        inline void rect(float x, float y, float w, float h) {
            nvgRect(get(), x, y, w, h);
        }
        inline void rect(const ofVec4f& r) {
            rect(r[0], r[2], r[3], r[4]);
        }
        inline void roundedRect(float x, float y, float w, float h, float r) {
            nvgRoundedRect(get(), x, y, w, h, r);
        }
        inline void roundedRect(const ofVec4f& rect, float r) {
            roundedRect(rect[0], rect[1], rect[2], rect[3], r);
        }
        inline void ellipse(float cx, float cy, float rx, float ry) {
            nvgEllipse(get(), cx, cy, rx, ry);
        }
        inline void ellipse(const ofVec2f& center, float rx, float ry) {
            ellipse(center.x, center.y, rx, ry);
        }
        inline void circle(float cx, float cy, float r) {
            nvgCircle(get(), cx, cy, r);
        }
        inline void circle(const ofVec2f& center, float radius) {
            circle(center.x, center.x, radius);
        }
        
        inline void fill() { nvgFill(get()); }
        inline void stroke() { nvgStroke(get()); }
        
        // openFrameworks Types //
        
        void polyLine(const ofPolyline& polyline);
        //void shape2d(const Shape2d& shape);
        
    private:
        std::shared_ptr<NVGcontext> mCtx;
    };
    
}} // cinder::nvg