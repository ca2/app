//
// Copyright (c) 2013 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//
#include "framework.h"

#include "aura/graphics/draw2d/_component.h"

//#include <stdlib.h>
//#include <stdio.h>
//#include <math.h>
//#include <memory.h>

#include NANO2D_INCLUDE
#include "context.h"

#define __NANO2D_CONTEXT(ctx) ((::nano2d::context *) (ctx)->p)


::object * get_nano2d_object(NVGcontext * ctx)
{

	auto pcontext = ((::nano2d::context *)(ctx)->p);

	auto pdraw2dcontext = dynamic_cast <::nano2d::draw2d_context *>(pcontext);

	if (pdraw2dcontext)
	{

		return pdraw2dcontext->get_graphics();

	}

	return nullptr;

}

//
//#define FONTSTASH_IMPLEMENTATION
//#include "fontstash.h"
//
//#ifndef NVG_NO_STB
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//#endif 

//#ifdef _MSC_VER
//#pragma warning(disable: 4100)  // unreferenced formal parameter
//#pragma warning(disable: 4127)  // conditional expression is constant
//#pragma warning(disable: 4204)  // nonstandard extension used : non-constant aggregate initializer
//#pragma warning(disable: 4706)  // assignment within conditional expression
//#endif
//
//#define NVG_INIT_FONTIMAGE_SIZE  512
//#define NVG_MAX_FONTIMAGE_SIZE   2048
//#define NVG_MAX_FONTIMAGES       4
//
//#define NVG_INIT_COMMANDS_SIZE 256
//#define NVG_INIT_POINTS_SIZE 128
//#define NVG_INIT_PATHS_SIZE 16
//#define NVG_INIT_VERTS_SIZE 256
//#define NVG_MAX_STATES 32
//
//#define NVG_KAPPA90 0.5522847493f	// Length proportional to radius of a cubic bezier handle for 90deg arcs.
//
//#define NVG_COUNTOF(arr) (sizeof(arr) / sizeof(0[arr]))

//
//enum NVGcommands {
//	NVG_MOVETO = 0,
//	NVG_LINETO = 1,
//	NVG_BEZIERTO = 2,
//	NVG_CLOSE = 3,
//	NVG_WINDING = 4,
//};
//
//enum NVGpointFlags
//{
//	NVG_PT_CORNER = 0x01,
//	NVG_PT_LEFT = 0x02,
//	NVG_PT_BEVEL = 0x04,
//	NVG_PR_INNERBEVEL = 0x08,
//};
//
//struct NVGstate {
//	NVGcompositeOperationState compositeOperation;
//	int shapeAntiAlias;
//	NANO2D_PAINT fill;
//	NANO2D_PAINT stroke;
//	float strokeWidth;
//	float miterLimit;
//	int lineJoin;
//	int lineCap;
//	float alpha;
//	float xform[6];
//	NVGscissor scissor;
//	float fontSize;
//	float letterSpacing;
//	float lineHeight;
//	float fontBlur;
//	int textAlign;
//	int fontId;
//};
//typedef struct NVGstate NVGstate;
//
//struct NVGpoint {
//	float x, y;
//	float dx, dy;
//	float len;
//	float dmx, dmy;
//	unsigned char flags;
//};
//typedef struct NVGpoint NVGpoint;
//
//struct NVGpathCache {
//	NVGpoint * points;
//	int npoints;
//	int cpoints;
//	NVGpath * paths;
//	int npaths;
//	int cpaths;
//	NVGvertex * verts;
//	int nverts;
//	int cverts;
//	float bounds[4];
//};
//typedef struct NVGpathCache NVGpathCache;

//struct NANO2D_CONTEXT {
//	NVGparams params;
//	float * commands;
//	int ccommands;
//	int ncommands;
//	float commandx, commandy;
//	NVGstate states[NVG_MAX_STATES];
//	int nstates;
//	NVGpathCache * cache;
//	float tessTol;
//	float distTol;
//	float fringeWidth;
//	float devicePxRatio;
//	struct FONScontext * fs;
//	int fontImages[NVG_MAX_FONTIMAGES];
//	int fontImageIdx;
//	int drawCallCount;
//	int fillTriCount;
//	int strokeTriCount;
//	int textTriCount;
//};

static float __NANO2D_API(__sqrtf)(float a) { return sqrtf(a); }
//static float __NANO2D_API(__modf)(float a, float b) { return fmodf(a, b); }
static float __NANO2D_API(__sinf)(float a) { return sinf(a); }
static float __NANO2D_API(__cosf)(float a) { return cosf(a); }
static float __NANO2D_API(__tanf)(float a) { return tanf(a); }
static float __NANO2D_API(__atan2f)(float a, float b) { return atan2f(a, b); }
static float __NANO2D_API(__acosf)(float a) { return acosf(a); }

//static int __NANO2D_API(__mini)(int a, int b) { return a < b ? a : b; }
//static int __NANO2D_API(__maxi)(int a, int b) { return a > b ? a : b; }
//static int __NANO2D_API(__clampi)(int a, int mn, int mx) { return a < mn ? mn : (a > mx ? mx : a); }
static float __NANO2D_API(__minf)(float a, float b) { return a < b ? a : b; }
static float __NANO2D_API(__maxf)(float a, float b) { return a > b ? a : b; }
static float __NANO2D_API(__absf)(float a) { return a >= 0.0f ? a : -a; }
static float __NANO2D_API(__signf)(float a) { return a >= 0.0f ? 1.0f : -1.0f; }
//static float __NANO2D_API(__clampf)(float a, float mn, float mx) { return a < mn ? mn : (a > mx ? mx : a); }
static float __NANO2D_API(__cross)(float dx0, float dy0, float dx1, float dy1) { return dx1 * dy0 - dx0 * dy1; }

static float __NANO2D_API(__normalize)(float * x, float * y)
{
	float d = __NANO2D_API(__sqrtf)((*x) * (*x) + (*y) * (*y));
	if (d > 1e-6f) {
		float id = 1.0f / d;
		*x *= id;
		*y *= id;
	}
	return d;
}


//static void __NANO2D_API(__deletePathCache)(NVGpathCache * c)
//{
//	if (c == NULL) return;
//	if (c->points != NULL) free(c->points);
//	if (c->paths != NULL) free(c->paths);
//	if (c->verts != NULL) free(c->verts);
//	free(c);
//}

//static NVGpathCache * __NANO2D_API(__allocPathCache)(void)
//{
//	NVGpathCache * c = (NVGpathCache *)malloc(sizeof(NVGpathCache));
//	if (c == NULL) goto error;
//	memset(c, 0, sizeof(NVGpathCache));
//
//	c->points = (NVGpoint *)malloc(sizeof(NVGpoint) * NVG_INIT_POINTS_SIZE);
//	if (!c->points) goto error;
//	c->npoints = 0;
//	c->cpoints = NVG_INIT_POINTS_SIZE;
//
//	c->paths = (NVGpath *)malloc(sizeof(NVGpath) * NVG_INIT_PATHS_SIZE);
//	if (!c->paths) goto error;
//	c->npaths = 0;
//	c->cpaths = NVG_INIT_PATHS_SIZE;
//
//	c->verts = (NVGvertex *)malloc(sizeof(NVGvertex) * NVG_INIT_VERTS_SIZE);
//	if (!c->verts) goto error;
//	c->nverts = 0;
//	c->cverts = NVG_INIT_VERTS_SIZE;
//
//	return c;
//error:
//	__NANO2D_API(__deletePathCache)(c);
//	return NULL;
//}

//static void __NANO2D_API(__setDevicePixelRatio)(NANO2D_CONTEXT * ctx, float ratio)
//{
//	__NANO2D_CONTEXT(ctx)->tessTol = 0.25f / ratio;
//	__NANO2D_CONTEXT(ctx)->distTol = 0.01f / ratio;
//	__NANO2D_CONTEXT(ctx)->fringeWidth = 1.0f / ratio;
//	__NANO2D_CONTEXT(ctx)->devicePxRatio = ratio;
//}

static NVGcompositeOperationState __NANO2D_API(__compositeOperationState)(int op)
{
	int sfactor, dfactor;

	if (op == NVG_SOURCE_OVER)
	{
		sfactor = NVG_ONE;
		dfactor = NVG_ONE_MINUS_SRC_ALPHA;
	}
	else if (op == NVG_SOURCE_IN)
	{
		sfactor = NVG_DST_ALPHA;
		dfactor = NVG_ZERO;
	}
	else if (op == NVG_SOURCE_OUT)
	{
		sfactor = NVG_ONE_MINUS_DST_ALPHA;
		dfactor = NVG_ZERO;
	}
	else if (op == NVG_ATOP)
	{
		sfactor = NVG_DST_ALPHA;
		dfactor = NVG_ONE_MINUS_SRC_ALPHA;
	}
	else if (op == NVG_DESTINATION_OVER)
	{
		sfactor = NVG_ONE_MINUS_DST_ALPHA;
		dfactor = NVG_ONE;
	}
	else if (op == NVG_DESTINATION_IN)
	{
		sfactor = NVG_ZERO;
		dfactor = NVG_SRC_ALPHA;
	}
	else if (op == NVG_DESTINATION_OUT)
	{
		sfactor = NVG_ZERO;
		dfactor = NVG_ONE_MINUS_SRC_ALPHA;
	}
	else if (op == NVG_DESTINATION_ATOP)
	{
		sfactor = NVG_ONE_MINUS_DST_ALPHA;
		dfactor = NVG_SRC_ALPHA;
	}
	else if (op == NVG_LIGHTER)
	{
		sfactor = NVG_ONE;
		dfactor = NVG_ONE;
	}
	else if (op == NVG_COPY)
	{
		sfactor = NVG_ONE;
		dfactor = NVG_ZERO;
	}
	else if (op == NVG_XOR)
	{
		sfactor = NVG_ONE_MINUS_DST_ALPHA;
		dfactor = NVG_ONE_MINUS_SRC_ALPHA;
	}
	else
	{
		sfactor = NVG_ONE;
		dfactor = NVG_ZERO;
	}

	NVGcompositeOperationState state;
	state.srcRGB = sfactor;
	state.dstRGB = dfactor;
	state.srcAlpha = sfactor;
	state.dstAlpha = dfactor;
	return state;
}

static NVGstate * __NANO2D_API(__getState)(NANO2D_CONTEXT * ctx)
{
	//return &__NANO2D_CONTEXT(ctx)->states[__NANO2D_CONTEXT(ctx)->nstates - 1];
	throw not_implemented();
	return nullptr;

}

//NANO2D_CONTEXT * __NANO2D_API(CreateInternal)(NVGparams * params)
//{
//	FONSparams fontParams;
//	NANO2D_CONTEXT * ctx = (NANO2D_CONTEXT *)malloc(sizeof(NANO2D_CONTEXT));
//	int i;
//	if (ctx == NULL) goto error;
//	memset(ctx, 0, sizeof(NANO2D_CONTEXT));
//
//	__NANO2D_CONTEXT(ctx)->params = *params;
//	for (i = 0; i < NVG_MAX_FONTIMAGES; i++)
//		__NANO2D_CONTEXT(ctx)->fontImages[i] = 0;
//
//	__NANO2D_CONTEXT(ctx)->commands = (float *)malloc(sizeof(float) * NVG_INIT_COMMANDS_SIZE);
//	if (!__NANO2D_CONTEXT(ctx)->commands) goto error;
//	__NANO2D_CONTEXT(ctx)->ncommands = 0;
//	__NANO2D_CONTEXT(ctx)->ccommands = NVG_INIT_COMMANDS_SIZE;
//
//	__NANO2D_CONTEXT(ctx)->cache = __NANO2D_API(__allocPathCache)();
//	if (__NANO2D_CONTEXT(ctx)->cache == NULL) goto error;
//
//	__NANO2D_API(Save)(ctx);
//	__NANO2D_API(Reset)(ctx);
//
//	__NANO2D_API(__setDevicePixelRatio)(ctx, 1.0f);
//
//	if (__NANO2D_CONTEXT(ctx)->params.renderCreate(__NANO2D_CONTEXT(ctx)->params.userPtr) == 0) goto error;
//
//	// Init font rendering
//	memset(&fontParams, 0, sizeof(fontParams));
//	fontParams.width = NVG_INIT_FONTIMAGE_SIZE;
//	fontParams.height = NVG_INIT_FONTIMAGE_SIZE;
//	fontParams.flags = FONS_ZERO_TOPLEFT;
//	fontParams.renderCreate = NULL;
//	fontParams.renderUpdate = NULL;
//	fontParams.renderDraw = NULL;
//	fontParams.renderDelete = NULL;
//	fontParams.userPtr = NULL;
//	__NANO2D_CONTEXT(ctx)->fs = fonsCreateInternal(&fontParams);
//	if (__NANO2D_CONTEXT(ctx)->fs == NULL) goto error;
//
//	// Create font texture
//	__NANO2D_CONTEXT(ctx)->fontImages[0] = __NANO2D_CONTEXT(ctx)->params.renderCreateTexture(__NANO2D_CONTEXT(ctx)->params.userPtr, NVG_TEXTURE_ALPHA, fontParams.width, fontParams.height, 0, NULL);
//	if (__NANO2D_CONTEXT(ctx)->fontImages[0] == 0) goto error;
//	__NANO2D_CONTEXT(ctx)->fontImageIdx = 0;
//
//	return ctx;
//
//error:
//	__NANO2D_API(DeleteInternal)(ctx);
//	return 0;
//}

//NVGparams * __NANO2D_API(InternalParams)(NANO2D_CONTEXT * ctx)
//{
//	return &__NANO2D_CONTEXT(ctx)->params;
//}
//
//void __NANO2D_API(DeleteInternal)(NANO2D_CONTEXT * ctx)
//{
//	int i;
//	if (ctx == NULL) return;
//	if (__NANO2D_CONTEXT(ctx)->commands != NULL) free(__NANO2D_CONTEXT(ctx)->commands);
//	if (__NANO2D_CONTEXT(ctx)->cache != NULL) __NANO2D_API(__deletePathCache)(__NANO2D_CONTEXT(ctx)->cache);
//
//	if (__NANO2D_CONTEXT(ctx)->fs)
//		fonsDeleteInternal(__NANO2D_CONTEXT(ctx)->fs);
//
//	for (i = 0; i < NVG_MAX_FONTIMAGES; i++) {
//		if (__NANO2D_CONTEXT(ctx)->fontImages[i] != 0) {
//			__NANO2D_API(DeleteImage)(ctx, __NANO2D_CONTEXT(ctx)->fontImages[i]);
//			__NANO2D_CONTEXT(ctx)->fontImages[i] = 0;
//		}
//	}
//
//	if (__NANO2D_CONTEXT(ctx)->params.renderDelete != NULL)
//		__NANO2D_CONTEXT(ctx)->params.renderDelete(__NANO2D_CONTEXT(ctx)->params.userPtr);
//
//	free(ctx);
//}
//
//void __NANO2D_API(BeginFrame)(NANO2D_CONTEXT * ctx, float windowWidth, float windowHeight, float devicePixelRatio)
//{
//	/*	printf("Tris: draws:%d  fill:%d  stroke:%d  text:%d  TOT:%d\n",
//			__NANO2D_CONTEXT(ctx)->drawCallCount, __NANO2D_CONTEXT(ctx)->fillTriCount, __NANO2D_CONTEXT(ctx)->strokeTriCount, __NANO2D_CONTEXT(ctx)->textTriCount,
//			__NANO2D_CONTEXT(ctx)->fillTriCount+__NANO2D_CONTEXT(ctx)->strokeTriCount+__NANO2D_CONTEXT(ctx)->textTriCount);*/
//
//	__NANO2D_CONTEXT(ctx)->nstates = 0;
//	__NANO2D_API(Save)(ctx);
//	__NANO2D_API(Reset)(ctx);
//
//	__NANO2D_API(__setDevicePixelRatio)(ctx, devicePixelRatio);
//
//	__NANO2D_CONTEXT(ctx)->params.renderContext(__NANO2D_CONTEXT(ctx)->params.userPtr, windowWidth, windowHeight, devicePixelRatio);
//
//	__NANO2D_CONTEXT(ctx)->drawCallCount = 0;
//	__NANO2D_CONTEXT(ctx)->fillTriCount = 0;
//	__NANO2D_CONTEXT(ctx)->strokeTriCount = 0;
//	__NANO2D_CONTEXT(ctx)->textTriCount = 0;
//}
//
//void __NANO2D_API(CancelFrame)(NANO2D_CONTEXT * ctx)
//{
//	__NANO2D_CONTEXT(ctx)->params.renderCancel(__NANO2D_CONTEXT(ctx)->params.userPtr);
//}
//
//void __NANO2D_API(EndFrame)(NANO2D_CONTEXT * ctx)
//{
//	__NANO2D_CONTEXT(ctx)->params.renderFlush(__NANO2D_CONTEXT(ctx)->params.userPtr);
//	if (__NANO2D_CONTEXT(ctx)->fontImageIdx != 0) {
//		int fontImage = __NANO2D_CONTEXT(ctx)->fontImages[__NANO2D_CONTEXT(ctx)->fontImageIdx];
//		int i, j, iw, ih;
//		// delete images that smaller than current one
//		if (fontImage == 0)
//			return;
//		__NANO2D_API(ImageSize)(ctx, fontImage, &iw, &ih);
//		for (i = j = 0; i < __NANO2D_CONTEXT(ctx)->fontImageIdx; i++) {
//			if (__NANO2D_CONTEXT(ctx)->fontImages[i] != 0) {
//				int nw, nh;
//				__NANO2D_API(ImageSize)(ctx, __NANO2D_CONTEXT(ctx)->fontImages[i], &nw, &nh);
//				if (nw < iw || nh < ih)
//					__NANO2D_API(DeleteImage)(ctx, __NANO2D_CONTEXT(ctx)->fontImages[i]);
//				else
//					__NANO2D_CONTEXT(ctx)->fontImages[j++] = __NANO2D_CONTEXT(ctx)->fontImages[i];
//			}
//		}
//		// make current font image to first
//		__NANO2D_CONTEXT(ctx)->fontImages[j++] = __NANO2D_CONTEXT(ctx)->fontImages[0];
//		__NANO2D_CONTEXT(ctx)->fontImages[0] = fontImage;
//		__NANO2D_CONTEXT(ctx)->fontImageIdx = 0;
//		// clear all images after j
//		for (i = j; i < NVG_MAX_FONTIMAGES; i++)
//			__NANO2D_CONTEXT(ctx)->fontImages[i] = 0;
//	}
//}

NANO2D_COLOR __NANO2D_API(RGB)(unsigned char r, unsigned char g, unsigned char b)
{
	///return __NANO2D_API(RGBA)(r, g, b, 255);
	return { r / 255.f, g / 255.f, b / 255.f, 1.0f };
}

NANO2D_COLOR __NANO2D_API(RGBf)(float r, float g, float b)
{
	//return __NANO2D_API(RGBAf)(r, g, b, 1.0f);
	return { r , g, b, 1.0f };
}

NANO2D_COLOR __NANO2D_API(RGBA)(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	NANO2D_COLOR color;
	// Use longer initialization to suppress warning.
	color.r = r / 255.0f;
	color.g = g / 255.0f;
	color.b = b / 255.0f;
	color.a = a / 255.0f;
	return color;
}

NANO2D_COLOR __NANO2D_API(RGBAf)(float r, float g, float b, float a)
{
	NANO2D_COLOR color;
	// Use longer initialization to suppress warning.
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return color;
}

NANO2D_COLOR __NANO2D_API(TransRGBA)(NANO2D_COLOR c, unsigned char a)
{
	c.a = a / 255.0f;
	return c;
}

NANO2D_COLOR __NANO2D_API(TransRGBAf)(NANO2D_COLOR c, float a)
{
	c.a = a;
	return c;
}

//NANO2D_COLOR __NANO2D_API(LerpRGBA)(NANO2D_COLOR c0, NANO2D_COLOR c1, float u)
//{
//	int i;
//	float oneminu;
//	NANO2D_COLOR cint = { {{0}} };
//
//	u = __NANO2D_API(__clampf)(u, 0.0f, 1.0f);
//	oneminu = 1.0f - u;
//	for (i = 0; i < 4; i++)
//	{
//		cint.rgba[i] = c0.rgba[i] * oneminu + c1.rgba[i] * u;
//	}
//
//	return cint;
//}

NANO2D_COLOR __NANO2D_API(HSL)(float h, float s, float l)
{
	//return __NANO2D_API(HSLA)(h, s, l, 255);
	::color::color color;

	color.set_hls(h, l, s);
	return { color.fr(), color.fg(), color.fb(), color.fa() };

}

//static float __NANO2D_API(__hue)(float h, float m1, float m2)
//{
//	if (h < 0) h += 1;
//	if (h > 1) h -= 1;
//	if (h < 1.0f / 6.0f)
//		return m1 + (m2 - m1) * h * 6.0f;
//	else if (h < 3.0f / 6.0f)
//		return m2;
//	else if (h < 4.0f / 6.0f)
//		return m1 + (m2 - m1) * (2.0f / 3.0f - h) * 6.0f;
//	return m1;
//}

NANO2D_COLOR __NANO2D_API(HSLA)(float h, float s, float l, unsigned char a)
{
	//float m1, m2;
	//NANO2D_COLOR col;
	//h = __NANO2D_API(__modf)(h, 1.0f);
	//if (h < 0.0f) h += 1.0f;
	//s = __NANO2D_API(__clampf)(s, 0.0f, 1.0f);
	//l = __NANO2D_API(__clampf)(l, 0.0f, 1.0f);
	//m2 = l <= 0.5f ? (l * (1 + s)) : (l + s - l * s);
	//m1 = 2 * l - m2;
	//col.r = __NANO2D_API(__clampf)(__NANO2D_API(__hue)(h + 1.0f / 3.0f, m1, m2), 0.0f, 1.0f);
	//col.g = __NANO2D_API(__clampf)(__NANO2D_API(__hue)(h, m1, m2), 0.0f, 1.0f);
	//col.b = __NANO2D_API(__clampf)(__NANO2D_API(__hue)(h - 1.0f / 3.0f, m1, m2), 0.0f, 1.0f);
	::color::color color;

	color.set_hls(h, l, s);
	color.alpha = a;
	return { color.fr(), color.fg(), color.fb(), color.fa() };
}

void __NANO2D_API(TransformIdentity)(float * t)
{
	t[0] = 1.0f; t[1] = 0.0f;
	t[2] = 0.0f; t[3] = 1.0f;
	t[4] = 0.0f; t[5] = 0.0f;
}

void __NANO2D_API(TransformTranslate)(float * t, float tx, float ty)
{
	t[0] = 1.0f; t[1] = 0.0f;
	t[2] = 0.0f; t[3] = 1.0f;
	t[4] = tx; t[5] = ty;
}

void __NANO2D_API(TransformScale)(float * t, float sx, float sy)
{
	t[0] = sx; t[1] = 0.0f;
	t[2] = 0.0f; t[3] = sy;
	t[4] = 0.0f; t[5] = 0.0f;
}

void __NANO2D_API(TransformRotate)(float * t, float a)
{
	float cs = __NANO2D_API(__cosf)(a), sn = __NANO2D_API(__sinf)(a);
	t[0] = cs; t[1] = sn;
   t[2] = -sn; t[3] = cs;
	t[4] = 0.0f; t[5] = 0.0f;
}

void __NANO2D_API(TransformSkewX)(float * t, float a)
{
	t[0] = 1.0f; t[1] = 0.0f;
	t[2] = __NANO2D_API(__tanf)(a); t[3] = 1.0f;
	t[4] = 0.0f; t[5] = 0.0f;
}

void __NANO2D_API(TransformSkewY)(float * t, float a)
{
	t[0] = 1.0f; t[1] = __NANO2D_API(__tanf)(a);
	t[2] = 0.0f; t[3] = 1.0f;
	t[4] = 0.0f; t[5] = 0.0f;
}

void __NANO2D_API(TransformMultiply)(float * t, const float * s)
{
	float t0 = t[0] * s[0] + t[1] * s[2];
	float t2 = t[2] * s[0] + t[3] * s[2];
	float t4 = t[4] * s[0] + t[5] * s[2] + s[4];
	t[1] = t[0] * s[1] + t[1] * s[3];
	t[3] = t[2] * s[1] + t[3] * s[3];
	t[5] = t[4] * s[1] + t[5] * s[3] + s[5];
	t[0] = t0;
	t[2] = t2;
	t[4] = t4;
}

void __NANO2D_API(TransformPremultiply)(float * t, const float * s)
{
	float s2[6];
	memcpy(s2, s, sizeof(float) * 6);
	__NANO2D_API(TransformMultiply)(s2, t);
	memcpy(t, s2, sizeof(float) * 6);
}

int __NANO2D_API(TransformInverse)(float * inv, const float * t)
{
	double invdet, det = (double)t[0] * t[3] - (double)t[2] * t[1];
	if (det > -1e-6 && det < 1e-6) {
		__NANO2D_API(TransformIdentity)(inv);
		return 0;
	}
	invdet = 1.0 / det;
	inv[0] = (float)(t[3] * invdet);
	inv[2] = (float)(-t[2] * invdet);
	inv[4] = (float)(((double)t[2] * t[5] - (double)t[3] * t[4]) * invdet);
	inv[1] = (float)(-t[1] * invdet);
	inv[3] = (float)(t[0] * invdet);
	inv[5] = (float)(((double)t[1] * t[4] - (double)t[0] * t[5]) * invdet);
	return 1;
}

void __NANO2D_API(TransformPoint)(float * dx, float * dy, const float * t, float sx, float sy)
{
	*dx = sx * t[0] + sy * t[2] + t[4];
	*dy = sx * t[1] + sy * t[3] + t[5];
}

float __NANO2D_API(DegToRad)(float deg)
{
	return deg / 180.0f * NVG_PI;
}

float __NANO2D_API(RadToDeg)(float rad)
{
	return rad / NVG_PI * 180.0f;
}

static void __NANO2D_API(__setPaintColor)(NANO2D_PAINT * p, NANO2D_COLOR color)
{
	memset(p, 0, sizeof(*p));
	__NANO2D_API(TransformIdentity)(p->xform);
	p->radius = 0.0f;
	p->feather = 1.0f;
	p->innerColor = color;
	p->outerColor = color;
}


// State handling
void __NANO2D_API(Save)(NANO2D_CONTEXT * ctx)
{
	//if (__NANO2D_CONTEXT(ctx)->nstates >= NVG_MAX_STATES)
	//	return;
	//if (__NANO2D_CONTEXT(ctx)->nstates > 0)
	//	memcpy(&__NANO2D_CONTEXT(ctx)->states[__NANO2D_CONTEXT(ctx)->nstates], &__NANO2D_CONTEXT(ctx)->states[__NANO2D_CONTEXT(ctx)->nstates - 1], sizeof(NVGstate));
	//__NANO2D_CONTEXT(ctx)->nstates++;

	__NANO2D_CONTEXT(ctx)->save();

}

void __NANO2D_API(Restore)(NANO2D_CONTEXT * ctx)
{
	__NANO2D_CONTEXT(ctx)->restore();
	//if (__NANO2D_CONTEXT(ctx)->nstates <= 1)
	//	return;
	//__NANO2D_CONTEXT(ctx)->nstates--;
}

void __NANO2D_API(Reset)(NANO2D_CONTEXT * ctx)
{
	NVGstate * state = __NANO2D_API(__getState)(ctx);
	memset(state, 0, sizeof(*state));

	__NANO2D_API(__setPaintColor)(&state->fill, __NANO2D_API(RGBA)(255, 255, 255, 255));
	__NANO2D_API(__setPaintColor)(&state->stroke, __NANO2D_API(RGBA)(0, 0, 0, 255));
	state->compositeOperation = __NANO2D_API(__compositeOperationState)(NVG_SOURCE_OVER);
	state->shapeAntiAlias = 1;
	state->strokeWidth = 1.0f;
	state->miterLimit = 10.0f;
	state->lineCap = NVG_BUTT;
	state->lineJoin = NVG_MITER;
	state->alpha = 1.0f;
	__NANO2D_API(TransformIdentity)(state->xform);

	state->scissor.extent[0] = -1.0f;
	state->scissor.extent[1] = -1.0f;

	state->fontSize = 16.0f;
	state->letterSpacing = 0.0f;
	state->lineHeight = 1.0f;
	state->fontBlur = 0.0f;
	state->textAlign = NVG_ALIGN_LEFT | NVG_ALIGN_BASELINE;
	state->fontId = 0;
}

// State setting
void __NANO2D_API(ShapeAntiAlias)(NANO2D_CONTEXT * ctx, int enabled)
{
	NVGstate * state = __NANO2D_API(__getState)(ctx);
	state->shapeAntiAlias = enabled;
}

void __NANO2D_API(StrokeWidth)(NANO2D_CONTEXT * ctx, float width)
{
	//NVGstate * state = __NANO2D_API(__getState)(ctx);
	//state->strokeWidth = width;
	return __NANO2D_CONTEXT(ctx)->stroke_width(width);
}

void __NANO2D_API(MiterLimit)(NANO2D_CONTEXT * ctx, float limit)
{
	NVGstate * state = __NANO2D_API(__getState)(ctx);
	state->miterLimit = limit;
}

void __NANO2D_API(LineCap)(NANO2D_CONTEXT * ctx, int cap)
{
	NVGstate * state = __NANO2D_API(__getState)(ctx);
	state->lineCap = cap;
}

void __NANO2D_API(LineJoin)(NANO2D_CONTEXT * ctx, int join)
{
	NVGstate * state = __NANO2D_API(__getState)(ctx);
	state->lineJoin = join;
}

void __NANO2D_API(GlobalAlpha)(NANO2D_CONTEXT * ctx, float alpha)
{
	//NVGstate * state = __NANO2D_API(__getState)(ctx);
	//state->alpha = alpha;
   __NANO2D_CONTEXT(ctx)->global_alpha(alpha);

}

void __NANO2D_API(Transform)(NANO2D_CONTEXT * ctx, float a, float b, float c, float d, float e, float f)
{
	NVGstate * state = __NANO2D_API(__getState)(ctx);
	float t[6] = { a, b, c, d, e, f };
	__NANO2D_API(TransformPremultiply)(state->xform, t);
}

void __NANO2D_API(ResetTransform)(NANO2D_CONTEXT * ctx)
{
	NVGstate * state = __NANO2D_API(__getState)(ctx);
	__NANO2D_API(TransformIdentity)(state->xform);
}

void __NANO2D_API(Translate)(NANO2D_CONTEXT * ctx, float x, float y)
{
	//NVGstate * state = __NANO2D_API(__getState)(ctx);
	//float t[6];
	//__NANO2D_API(TransformTranslate)(t, x, y);
	//__NANO2D_API(TransformPremultiply)(state->xform, t);

	__NANO2D_CONTEXT(ctx)->translate(x, y);

}

void __NANO2D_API(Rotate)(NANO2D_CONTEXT * ctx, float angle)
{
	//NVGstate * state = __NANO2D_API(__getState)(ctx);
	//float t[6];
	//__NANO2D_API(TransformRotate)(t, angle);
	//__NANO2D_API(TransformPremultiply)(state->xform, t);
	__NANO2D_CONTEXT(ctx)->rotate(angle);
}

void __NANO2D_API(SkewX)(NANO2D_CONTEXT * ctx, float angle)
{
	NVGstate * state = __NANO2D_API(__getState)(ctx);
	float t[6];
	__NANO2D_API(TransformSkewX)(t, angle);
	__NANO2D_API(TransformPremultiply)(state->xform, t);
}

void __NANO2D_API(SkewY)(NANO2D_CONTEXT * ctx, float angle)
{
	NVGstate * state = __NANO2D_API(__getState)(ctx);
	float t[6];
	__NANO2D_API(TransformSkewY)(t, angle);
	__NANO2D_API(TransformPremultiply)(state->xform, t);
}

void __NANO2D_API(Scale)(NANO2D_CONTEXT * ctx, float x, float y)
{
	NVGstate * state = __NANO2D_API(__getState)(ctx);
	float t[6];
	__NANO2D_API(TransformScale)(t, x, y);
	__NANO2D_API(TransformPremultiply)(state->xform, t);
}

void __NANO2D_API(CurrentTransform)(NANO2D_CONTEXT * ctx, float * xform)
{
	NVGstate * state = __NANO2D_API(__getState)(ctx);
	if (xform == NULL) return;
	memcpy(xform, state->xform, sizeof(float) * 6);
}

void __NANO2D_API(StrokeColor)(NANO2D_CONTEXT * ctx, NANO2D_COLOR color)
{
	//NVGstate * state = __NANO2D_API(__getState)(ctx);
	//__NANO2D_API(__setPaintColor)(&state->stroke, color);

	__NANO2D_CONTEXT(ctx)->stroke_color(color);

}

void __NANO2D_API(StrokePaint)(NANO2D_CONTEXT * ctx, NANO2D_PAINT paint)
{
	//NVGstate * state = __NANO2D_API(__getState)(ctx);
	//state->stroke = paint;
	//__NANO2D_API(TransformMultiply)(state->stroke.xform, state->xform);

	__NANO2D_CONTEXT(ctx)->stroke_paint(paint);
}

void __NANO2D_API(FillColor)(NANO2D_CONTEXT * ctx, NANO2D_COLOR color)
{
	//NVGstate * state = __NANO2D_API(__getState)(ctx);
	//__NANO2D_API(__setPaintColor)(&state->fill, color);

	__NANO2D_CONTEXT(ctx)->fill_color(color);

}

void __NANO2D_API(FillPaint)(NANO2D_CONTEXT * ctx, NANO2D_PAINT paint)
{
	//NVGstate * state = __NANO2D_API(__getState)(ctx);
	//state->fill = paint;
	//__NANO2D_API(TransformMultiply)(state->fill.xform, state->xform);

	__NANO2D_CONTEXT(ctx)->fill_paint(paint);

}

#ifndef NVG_NO_STB
int __NANO2D_API(CreateImage)(NANO2D_CONTEXT * ctx, const char * filename, int imageFlags)
{
	//int w, h, n, image;
	//unsigned char * img;
	//stbi_set_unpremultiply_on_load(1);
	//stbi_convert_iphone_png_to_rgb(1);
	//img = stbi_load(filename, &w, &h, &n, 4);
	//if (img == NULL) {
	//	//		printf("Failed to load %s - %s\n", filename, stbi_failure_reason());
	//	return 0;
	//}
	//image = __NANO2D_API(CreateImageRGBA)(ctx, w, h, imageFlags, img);
	//stbi_image_free(img);
	//return image;
	return __NANO2D_CONTEXT(ctx)->create_image(filename, imageFlags);
}

int __NANO2D_API(CreateImageMem)(NANO2D_CONTEXT * ctx, int imageFlags, unsigned char * data, int ndata)
{
	//int w, h, n, image;
	//unsigned char * img = stbi_load_from_memory(data, ndata, &w, &h, &n, 4);
	//if (img == NULL) {
	//	//		printf("Failed to load %s - %s\n", filename, stbi_failure_reason());
	//	return 0;
	//}
	//image = __NANO2D_API(CreateImageRGBA)(ctx, w, h, imageFlags, img);
	//stbi_image_free(img);
	//return image;
	return -1;
}
#endif

int __NANO2D_API(CreateImageRGBA)(NANO2D_CONTEXT * ctx, int w, int h, int imageFlags, const void * data, int iScan)
{
	//return __NANO2D_CONTEXT(ctx)->params.renderCreateTexture(__NANO2D_CONTEXT(ctx)->params.userPtr, NVG_TEXTURE_RGBA, w, h, imageFlags, data);
	return __NANO2D_CONTEXT(ctx)->create_image_rgba(w, h, imageFlags, data, iScan);
}

void __NANO2D_API(UpdateImage)(NANO2D_CONTEXT * ctx, int image, const void * data)
{
	//int w h;
	//__NANO2D_CONTEXT(ctx)->params.renderGetTextureSize(__NANO2D_CONTEXT(ctx)->params.userPtr, image, &w, &h);
	//__NANO2D_CONTEXT(ctx)->params.renderUpdateTexture(__NANO2D_CONTEXT(ctx)->params.userPtr, image, 0, 0, w, h, data);
	return __NANO2D_CONTEXT(ctx)->update_image(image, data);
}

void __NANO2D_API(ImageSize)(NANO2D_CONTEXT * ctx, int image, int * w, int * h)
{
	//__NANO2D_CONTEXT(ctx)->params.renderGetTextureSize(__NANO2D_CONTEXT(ctx)->params.userPtr, image, w, h);

	__NANO2D_CONTEXT(ctx)->image_size(image, w, h);
}

void __NANO2D_API(DeleteImage)(NANO2D_CONTEXT * ctx, int image)
{
	__NANO2D_CONTEXT(ctx)->params.renderDeleteTexture(__NANO2D_CONTEXT(ctx)->params.userPtr, image);
}

NANO2D_PAINT __NANO2D_API(LinearGradient)(NANO2D_CONTEXT * ctx,
	float sx, float sy, float ex, float ey,
	NANO2D_COLOR icol, NANO2D_COLOR ocol)
{

	return __NANO2D_CONTEXT(ctx)->linear_gradient(sx, sy, ex, ey, icol, ocol);
	//NANO2D_PAINT p;
	//float dx, dy, d;
	//const float large = 1e5;
	//NVG_NOTUSED(ctx);
	//memset(&p, 0, sizeof(p));

	//// Calculate transform aligned to the line
	//dx = ex - sx;
	//dy = ey - sy;
	//d = sqrtf(dx * dx + dy * dy);
	//if (d > 0.0001f) {
	//	dx /= d;
	//	dy /= d;
	//}
	//else {
	//	dx = 0;
	//	dy = 1;
	//}

	//p.xform[0] = dy; p.xform[1] = -dx;
	//p.xform[2] = dx; p.xform[3] = dy;
	//p.xform[4] = sx - dx * large; p.xform[5] = sy - dy * large;

	//p.extent[0] = large;
	//p.extent[1] = large + d * 0.5f;

	//p.radius = 0.0f;

	//p.feather = __NANO2D_API(__maxf)(1.0f, d);

	//p.innerColor = icol;
	//p.outerColor = ocol;

	//return p;
}

NANO2D_PAINT __NANO2D_API(RadialGradient)(NANO2D_CONTEXT * ctx,
	float cx, float cy, float inr, float outr,
	NANO2D_COLOR icol, NANO2D_COLOR ocol)
{
	return __NANO2D_CONTEXT(ctx)->radial_gradient(cx, cy, inr, outr, icol, ocol);
	//NANO2D_PAINT p;
	//float r = (inr + outr) * 0.5f;
	//float f = (outr - inr);
	//NVG_NOTUSED(ctx);
	//memset(&p, 0, sizeof(p));

	//__NANO2D_API(TransformIdentity)(p.xform);
	//p.xform[4] = cx;
	//p.xform[5] = cy;

	//p.extent[0] = r;
	//p.extent[1] = r;

	//p.radius = r;

	//p.feather = __NANO2D_API(__maxf)(1.0f, f);

	//p.innerColor = icol;
	//p.outerColor = ocol;

	//return p;
}

NANO2D_PAINT __NANO2D_API(BoxGradient)(NANO2D_CONTEXT * ctx,
	float x, float y, float w, float h, float r, float f,
	NANO2D_COLOR icol, NANO2D_COLOR ocol)
{
	return __NANO2D_CONTEXT(ctx)->box_gradient(x, y, w, h, r, f, icol, ocol);
	//NANO2D_PAINT p;
	//NVG_NOTUSED(ctx);
	//memset(&p, 0, sizeof(p));

	//__NANO2D_API(TransformIdentity)(p.xform);
	//p.xform[4] = x + w * 0.5f;
	//p.xform[5] = y + h * 0.5f;

	//p.extent[0] = w * 0.5f;
	//p.extent[1] = h * 0.5f;

	//p.radius = r;

	//p.feather = __NANO2D_API(__maxf)(1.0f, f);

	//p.innerColor = icol;
	//p.outerColor = ocol;

	//return p;
}


NANO2D_PAINT __NANO2D_API(ImagePattern)(NANO2D_CONTEXT * ctx,
	float cx, float cy, float w, float h, float angle,
	int image, float alpha)
{

	return __NANO2D_CONTEXT(ctx)->image_pattern(cx, cy, w, h, angle, image, alpha);
	//NANO2D_PAINT p;
	//NVG_NOTUSED(ctx);
	//memset(&p, 0, sizeof(p));

	//__NANO2D_API(TransformRotate)(p.xform, angle);
	//p.xform[4] = cx;
	//p.xform[5] = cy;

	//p.extent[0] = w;
	//p.extent[1] = h;

	//p.image = image;

	//p.innerColor = p.outerColor = __NANO2D_API(RGBAf)(1, 1, 1, alpha);

	//return p;
}

// Scissoring
void __NANO2D_API(Scissor)(NANO2D_CONTEXT * ctx, float x, float y, float w, float h)
{
	NVGstate * state = __NANO2D_API(__getState)(ctx);

	w = __NANO2D_API(__maxf)(0.0f, w);
	h = __NANO2D_API(__maxf)(0.0f, h);

	__NANO2D_API(TransformIdentity)(state->scissor.xform);
	state->scissor.xform[4] = x + w * 0.5f;
	state->scissor.xform[5] = y + h * 0.5f;
	__NANO2D_API(TransformMultiply)(state->scissor.xform, state->xform);

	state->scissor.extent[0] = w * 0.5f;
	state->scissor.extent[1] = h * 0.5f;
}

//static void __NANO2D_API(__isectRects)(float * dst,
//	float ax, float ay, float aw, float ah,
//	float bx, float by, float bw, float bh)
//{
//	float minx = __NANO2D_API(__maxf)(ax, bx);
//	float miny = __NANO2D_API(__maxf)(ay, by);
//	float maxx = __NANO2D_API(__minf)(ax + aw, bx + bw);
//	float maxy = __NANO2D_API(__minf)(ay + ah, by + bh);
//	dst[0] = minx;
//	dst[1] = miny;
//	dst[2] = __NANO2D_API(__maxf)(0.0f, maxx - minx);
//	dst[3] = __NANO2D_API(__maxf)(0.0f, maxy - miny);
//}

void __NANO2D_API(IntersectScissor)(NANO2D_CONTEXT * ctx, float x, float y, float w, float h)
{

	__NANO2D_CONTEXT(ctx)->intersect_scissor(x, y, w, h);
	//NVGstate * state = __NANO2D_API(__getState)(ctx);
	//float pxform[6], invxorm[6];
	//float rect[4];
	//float ex, ey, tex, tey;

	//// If no previous scissor has been set, set the scissor as current scissor.
	//if (state->scissor.extent[0] < 0) {
	//	__NANO2D_API(Scissor)(ctx, x, y, w, h);
	//	return;
	//}

	//// Transform the current scissor rect into current transform space.
	//// If there is difference in rotation, this will be approximation.
	//memcpy(pxform, state->scissor.xform, sizeof(float) * 6);
	//ex = state->scissor.extent[0];
	//ey = state->scissor.extent[1];
	//__NANO2D_API(TransformInverse)(invxorm, state->xform);
	//__NANO2D_API(TransformMultiply)(pxform, invxorm);
	//tex = ex * __NANO2D_API(__absf)(pxform[0]) + ey * __NANO2D_API(__absf)(pxform[2]);
	//tey = ex * __NANO2D_API(__absf)(pxform[1]) + ey * __NANO2D_API(__absf)(pxform[3]);

	//// Intersect rects.
	//__NANO2D_API(__isectRects)(rect, pxform[4] - tex, pxform[5] - tey, tex * 2, tey * 2, x, y, w, h);

	//__NANO2D_API(Scissor)(ctx, rect[0], rect[1], rect[2], rect[3]);
}

void __NANO2D_API(ResetScissor)(NANO2D_CONTEXT * ctx)
{
	//NVGstate * state = __NANO2D_API(__getState)(ctx);
	//memset(state->scissor.xform, 0, sizeof(state->scissor.xform));
	//state->scissor.extent[0] = -1.0f;
	//state->scissor.extent[1] = -1.0f;
	__NANO2D_CONTEXT(ctx)->reset_scissor();
}

// Global composite operation.
void __NANO2D_API(GlobalCompositeOperation)(NANO2D_CONTEXT * ctx, int op)
{
	NVGstate * state = __NANO2D_API(__getState)(ctx);
	state->compositeOperation = __NANO2D_API(__compositeOperationState)(op);
}

void __NANO2D_API(GlobalCompositeBlendFunc)(NANO2D_CONTEXT * ctx, int sfactor, int dfactor)
{
	__NANO2D_API(GlobalCompositeBlendFuncSeparate)(ctx, sfactor, dfactor, sfactor, dfactor);
}

void __NANO2D_API(GlobalCompositeBlendFuncSeparate)(NANO2D_CONTEXT * ctx, int srcRGB, int dstRGB, int srcAlpha, int dstAlpha)
{
	NVGcompositeOperationState op;
	op.srcRGB = srcRGB;
	op.dstRGB = dstRGB;
	op.srcAlpha = srcAlpha;
	op.dstAlpha = dstAlpha;

	NVGstate * state = __NANO2D_API(__getState)(ctx);
	state->compositeOperation = op;
}

static int __NANO2D_API(__ptEquals)(float x1, float y1, float x2, float y2, float tol)
{
	float dx = x2 - x1;
	float dy = y2 - y1;
	return dx * dx + dy * dy < tol * tol;
}

static float __NANO2D_API(__distPtSeg)(float x, float y, float px, float py, float qx, float qy)
{
	float pqx, pqy, dx, dy, d, t;
	pqx = qx - px;
	pqy = qy - py;
	dx = x - px;
	dy = y - py;
	d = pqx * pqx + pqy * pqy;
	t = pqx * dx + pqy * dy;
	if (d > 0) t /= d;
	if (t < 0) t = 0;
	else if (t > 1) t = 1;
	dx = px + t * pqx - x;
	dy = py + t * pqy - y;
	return dx * dx + dy * dy;
}

static void __NANO2D_API(__appendCommands)(NANO2D_CONTEXT * ctx, float * vals, int nvals)
{
	NVGstate * state = __NANO2D_API(__getState)(ctx);
	int i;

	if (__NANO2D_CONTEXT(ctx)->ncommands + nvals > __NANO2D_CONTEXT(ctx)->ccommands) {
		float * commands;
		int ccommands = __NANO2D_CONTEXT(ctx)->ncommands + nvals + __NANO2D_CONTEXT(ctx)->ccommands / 2;
		commands = (float *)realloc(__NANO2D_CONTEXT(ctx)->commands, sizeof(float) * ccommands);
		if (commands == NULL) return;
		__NANO2D_CONTEXT(ctx)->commands = commands;
		__NANO2D_CONTEXT(ctx)->ccommands = ccommands;
	}

	if ((int)vals[0] != NVG_CLOSE && (int)vals[0] != NVG_WINDING) {
		__NANO2D_CONTEXT(ctx)->commandx = vals[nvals - 2];
		__NANO2D_CONTEXT(ctx)->commandy = vals[nvals - 1];
	}

	// transform commands
	i = 0;
	while (i < nvals) {
		int cmd = (int)vals[i];
		switch (cmd) {
		case NVG_MOVETO:
			__NANO2D_API(TransformPoint)(&vals[i + 1], &vals[i + 2], state->xform, vals[i + 1], vals[i + 2]);
			i += 3;
			break;
		case NVG_LINETO:
			__NANO2D_API(TransformPoint)(&vals[i + 1], &vals[i + 2], state->xform, vals[i + 1], vals[i + 2]);
			i += 3;
			break;
		case NVG_BEZIERTO:
			__NANO2D_API(TransformPoint)(&vals[i + 1], &vals[i + 2], state->xform, vals[i + 1], vals[i + 2]);
			__NANO2D_API(TransformPoint)(&vals[i + 3], &vals[i + 4], state->xform, vals[i + 3], vals[i + 4]);
			__NANO2D_API(TransformPoint)(&vals[i + 5], &vals[i + 6], state->xform, vals[i + 5], vals[i + 6]);
			i += 7;
			break;
		case NVG_CLOSE:
			i++;
			break;
		case NVG_WINDING:
			i += 2;
			break;
		default:
			i++;
		}
	}

	memcpy(&__NANO2D_CONTEXT(ctx)->commands[__NANO2D_CONTEXT(ctx)->ncommands], vals, nvals * sizeof(float));

	__NANO2D_CONTEXT(ctx)->ncommands += nvals;
}


//static void __NANO2D_API(__clearPathCache)(NANO2D_CONTEXT * ctx)
//{
//	__NANO2D_CONTEXT(ctx)->cache->npoints = 0;
//	__NANO2D_CONTEXT(ctx)->cache->npaths = 0;
//}

//static NVGpath * __NANO2D_API(__lastPath)(NANO2D_CONTEXT * ctx)
//{
//	if (__NANO2D_CONTEXT(ctx)->cache->npaths > 0)
//		return &__NANO2D_CONTEXT(ctx)->cache->paths[__NANO2D_CONTEXT(ctx)->cache->npaths - 1];
//	return NULL;
//}

//static void __NANO2D_API(__addPath)(NANO2D_CONTEXT * ctx)
//{
//	NVGpath * path;
//	if (__NANO2D_CONTEXT(ctx)->cache->npaths + 1 > __NANO2D_CONTEXT(ctx)->cache->cpaths) {
//		NVGpath * paths;
//		int cpaths = __NANO2D_CONTEXT(ctx)->cache->npaths + 1 + __NANO2D_CONTEXT(ctx)->cache->cpaths / 2;
//		paths = (NVGpath *)realloc(__NANO2D_CONTEXT(ctx)->cache->paths, sizeof(NVGpath) * cpaths);
//		if (paths == NULL) return;
//		__NANO2D_CONTEXT(ctx)->cache->paths = paths;
//		__NANO2D_CONTEXT(ctx)->cache->cpaths = cpaths;
//	}
//	path = &__NANO2D_CONTEXT(ctx)->cache->paths[__NANO2D_CONTEXT(ctx)->cache->npaths];
//	memset(path, 0, sizeof(*path));
//	path->first = __NANO2D_CONTEXT(ctx)->cache->npoints;
//	path->winding = NVG_CCW;
//
//	__NANO2D_CONTEXT(ctx)->cache->npaths++;
//}
//
//static NVGpoint * __NANO2D_API(__lastPoint)(NANO2D_CONTEXT * ctx)
//{
//	if (__NANO2D_CONTEXT(ctx)->cache->npoints > 0)
//		return &__NANO2D_CONTEXT(ctx)->cache->points[__NANO2D_CONTEXT(ctx)->cache->npoints - 1];
//	return NULL;
//}

//static void __NANO2D_API(__addPoint)(NANO2D_CONTEXT * ctx, float x, float y, int flags)
//{
//	NVGpath * path = __NANO2D_API(__lastPath)(ctx);
//	NVGpoint * pt;
//	if (path == NULL) return;
//
//	if (path->count > 0 && __NANO2D_CONTEXT(ctx)->cache->npoints > 0) {
//		pt = __NANO2D_API(__lastPoint)(ctx);
//		if (__NANO2D_API(__ptEquals)(pt->x, pt->y, x, y, __NANO2D_CONTEXT(ctx)->distTol)) {
//			pt->flags |= flags;
//			return;
//		}
//	}
//
//	if (__NANO2D_CONTEXT(ctx)->cache->npoints + 1 > __NANO2D_CONTEXT(ctx)->cache->cpoints) {
//		NVGpoint * points;
//		int cpoints = __NANO2D_CONTEXT(ctx)->cache->npoints + 1 + __NANO2D_CONTEXT(ctx)->cache->cpoints / 2;
//		points = (NVGpoint *)realloc(__NANO2D_CONTEXT(ctx)->cache->points, sizeof(NVGpoint) * cpoints);
//		if (points == NULL) return;
//		__NANO2D_CONTEXT(ctx)->cache->points = points;
//		__NANO2D_CONTEXT(ctx)->cache->cpoints = cpoints;
//	}
//
//	pt = &__NANO2D_CONTEXT(ctx)->cache->points[__NANO2D_CONTEXT(ctx)->cache->npoints];
//	memset(pt, 0, sizeof(*pt));
//	pt->x = x;
//	pt->y = y;
//	pt->flags = (unsigned char)flags;
//
//	__NANO2D_CONTEXT(ctx)->cache->npoints++;
//	path->count++;
//}

//static void __NANO2D_API(__closePath)(NANO2D_CONTEXT * ctx)
//{
//	NVGpath * path = __NANO2D_API(__lastPath)(ctx);
//	if (path == NULL) return;
//	path->closed = 1;
//}

//static void __NANO2D_API(__pathWinding)(NANO2D_CONTEXT * ctx, int winding)
//{
//	NVGpath * path = __NANO2D_API(__lastPath)(ctx);
//	if (path == NULL) return;
//	path->winding = winding;
//}
//
//static float __NANO2D_API(__getAverageScale)(float * t)
//{
//	float sx = sqrtf(t[0] * t[0] + t[2] * t[2]);
//	float sy = sqrtf(t[1] * t[1] + t[3] * t[3]);
//	return (sx + sy) * 0.5f;
//}

//static NVGvertex * __NANO2D_API(__allocTempVerts)(NANO2D_CONTEXT * ctx, int nverts)
//{
//	if (nverts > __NANO2D_CONTEXT(ctx)->cache->cverts) {
//		NVGvertex * verts;
//		int cverts = (nverts + 0xff) & ~0xff; // Round up to prevent allocations when things change just slightly.
//		verts = (NVGvertex *)realloc(__NANO2D_CONTEXT(ctx)->cache->verts, sizeof(NVGvertex) * cverts);
//		if (verts == NULL) return NULL;
//		__NANO2D_CONTEXT(ctx)->cache->verts = verts;
//		__NANO2D_CONTEXT(ctx)->cache->cverts = cverts;
//	}
//
//	return __NANO2D_CONTEXT(ctx)->cache->verts;
//}
//
//static float __NANO2D_API(__triarea2)(float ax, float ay, float bx, float by, float cx, float cy)
//{
//	float abx = bx - ax;
//	float aby = by - ay;
//	float acx = cx - ax;
//	float acy = cy - ay;
//	return acx * aby - abx * acy;
//}

//static float __NANO2D_API(__polyArea)(NVGpoint * pts, int npts)
//{
//	int i;
//	float area = 0;
//	for (i = 2; i < npts; i++) {
//		NVGpoint * a = &pts[0];
//		NVGpoint * b = &pts[i - 1];
//		NVGpoint * c = &pts[i];
//		area += __NANO2D_API(__triarea2)(a->x, a->y, b->x, b->y, c->x, c->y);
//	}
//	return area * 0.5f;
//}

//static void __NANO2D_API(__polyReverse)(NVGpoint * pts, int npts)
//{
//	NVGpoint tmp;
//	int i = 0, j = npts - 1;
//	while (i < j) {
//		tmp = pts[i];
//		pts[i] = pts[j];
//		pts[j] = tmp;
//		i++;
//		j--;
//	}
//}


//static void __NANO2D_API(__vset)(NVGvertex * vtx, float x, float y, float u, float v)
//{
//	vtx->x = x;
//	vtx->y = y;
//	vtx->u = u;
//	vtx->v = v;
//}

//static void __NANO2D_API(__tesselateBezier)(NANO2D_CONTEXT * ctx,
//	float x1, float y1, float x2, float y2,
//	float x3, float y3, float x4, float y4,
//	int level, int type)
//{
//	float x12, y12, x23, y23, x34, y34, x123, y123, x234, y234, x1234, y1234;
//	float dx, dy, d2, d3;
//
//	if (level > 10) return;
//
//	x12 = (x1 + x2) * 0.5f;
//	y12 = (y1 + y2) * 0.5f;
//	x23 = (x2 + x3) * 0.5f;
//	y23 = (y2 + y3) * 0.5f;
//	x34 = (x3 + x4) * 0.5f;
//	y34 = (y3 + y4) * 0.5f;
//	x123 = (x12 + x23) * 0.5f;
//	y123 = (y12 + y23) * 0.5f;
//
//	dx = x4 - x1;
//	dy = y4 - y1;
//	d2 = __NANO2D_API(__absf)(((x2 - x4) * dy - (y2 - y4) * dx));
//	d3 = __NANO2D_API(__absf)(((x3 - x4) * dy - (y3 - y4) * dx));
//
//	if ((d2 + d3) * (d2 + d3) < __NANO2D_CONTEXT(ctx)->tessTol * (dx * dx + dy * dy)) {
//		__NANO2D_API(__addPoint)(ctx, x4, y4, type);
//		return;
//	}
//
//	/*	if (__NANO2D_API(__absf)(x1+x3-x2-x2) + __NANO2D_API(__absf)(y1+y3-y2-y2) + __NANO2D_API(__absf)(x2+x4-x3-x3) + __NANO2D_API(__absf)(y2+y4-y3-y3) < __NANO2D_CONTEXT(ctx)->tessTol) {
//			__NANO2D_API(__addPoint)(ctx, x4, y4, type);
//			return;
//		}*/
//
//	x234 = (x23 + x34) * 0.5f;
//	y234 = (y23 + y34) * 0.5f;
//	x1234 = (x123 + x234) * 0.5f;
//	y1234 = (y123 + y234) * 0.5f;
//
//	__NANO2D_API(__tesselateBezier)(ctx, x1, y1, x12, y12, x123, y123, x1234, y1234, level + 1, 0);
//	__NANO2D_API(__tesselateBezier)(ctx, x1234, y1234, x234, y234, x34, y34, x4, y4, level + 1, type);
//}

//static void __NANO2D_API(__flattenPaths)(NANO2D_CONTEXT * ctx)
//{
//	NVGpathCache * cache = __NANO2D_CONTEXT(ctx)->cache;
//	//	NVGstate* state = __NANO2D_API(__getState)(ctx);
//	NVGpoint * last;
//	NVGpoint * p0;
//	NVGpoint * p1;
//	NVGpoint * pts;
//	NVGpath * path;
//	int i, j;
//	float * cp1;
//	float * cp2;
//	float * p;
//	float area;
//
//	if (cache->npaths > 0)
//		return;
//
//	// Flatten
//	i = 0;
//	while (i < __NANO2D_CONTEXT(ctx)->ncommands) {
//		int cmd = (int)__NANO2D_CONTEXT(ctx)->commands[i];
//		switch (cmd) {
//		case NVG_MOVETO:
//			__NANO2D_API(__addPath)(ctx);
//			p = &__NANO2D_CONTEXT(ctx)->commands[i + 1];
//			__NANO2D_API(__addPoint)(ctx, p[0], p[1], NVG_PT_CORNER);
//			i += 3;
//			break;
//		case NVG_LINETO:
//			p = &__NANO2D_CONTEXT(ctx)->commands[i + 1];
//			__NANO2D_API(__addPoint)(ctx, p[0], p[1], NVG_PT_CORNER);
//			i += 3;
//			break;
//		case NVG_BEZIERTO:
//			last = __NANO2D_API(__lastPoint)(ctx);
//			if (last != NULL) {
//				cp1 = &__NANO2D_CONTEXT(ctx)->commands[i + 1];
//				cp2 = &__NANO2D_CONTEXT(ctx)->commands[i + 3];
//				p = &__NANO2D_CONTEXT(ctx)->commands[i + 5];
//				__NANO2D_API(__tesselateBezier)(ctx, last->x, last->y, cp1[0], cp1[1], cp2[0], cp2[1], p[0], p[1], 0, NVG_PT_CORNER);
//			}
//			i += 7;
//			break;
//		case NVG_CLOSE:
//			__NANO2D_API(__closePath)(ctx);
//			i++;
//			break;
//		case NVG_WINDING:
//			__NANO2D_API(__pathWinding)(ctx, (int)__NANO2D_CONTEXT(ctx)->commands[i + 1]);
//			i += 2;
//			break;
//		default:
//			i++;
//		}
//	}
//
//	cache->bounds[0] = cache->bounds[1] = 1e6f;
//	cache->bounds[2] = cache->bounds[3] = -1e6f;
//
//	// Calculate the direction and length of line segments.
//	for (j = 0; j < cache->npaths; j++) {
//		path = &cache->paths[j];
//		pts = &cache->points[path->first];
//
//		// If the first and last points are the same, remove the last, mark as closed path.
//		p0 = &pts[path->count - 1];
//		p1 = &pts[0];
//		if (__NANO2D_API(__ptEquals)(p0->x, p0->y, p1->x, p1->y, __NANO2D_CONTEXT(ctx)->distTol)) {
//			path->count--;
//			p0 = &pts[path->count - 1];
//			path->closed = 1;
//		}
//
//		// Enforce winding.
//		if (path->count > 2) {
//			area = __NANO2D_API(__polyArea)(pts, path->count);
//			if (path->winding == NVG_CCW && area < 0.0f)
//				__NANO2D_API(__polyReverse)(pts, path->count);
//			if (path->winding == NVG_CW && area > 0.0f)
//				__NANO2D_API(__polyReverse)(pts, path->count);
//		}
//
//		for (i = 0; i < path->count; i++) {
//			// Calculate segment direction and length
//			p0->dx = p1->x - p0->x;
//			p0->dy = p1->y - p0->y;
//			p0->len = __NANO2D_API(__normalize)(&p0->dx, &p0->dy);
//			// Update bounds
//			cache->bounds[0] = __NANO2D_API(__minf)(cache->bounds[0], p0->x);
//			cache->bounds[1] = __NANO2D_API(__minf)(cache->bounds[1], p0->y);
//			cache->bounds[2] = __NANO2D_API(__maxf)(cache->bounds[2], p0->x);
//			cache->bounds[3] = __NANO2D_API(__maxf)(cache->bounds[3], p0->y);
//			// Advance
//			p0 = p1++;
//		}
//	}
//}

//static int __NANO2D_API(__curveDivs)(float r, float arc, float tol)
//{
//	float da = acosf(r / (r + tol)) * 2.0f;
//	return __NANO2D_API(__maxi)(2, (int)ceilf(arc / da));
//}

//static void __NANO2D_API(__chooseBevel)(int bevel, NVGpoint * p0, NVGpoint * p1, float w,
//	float * x0, float * y0, float * x1, float * y1)
//{
//	if (bevel) {
//		*x0 = p1->x + p0->dy * w;
//		*y0 = p1->y - p0->dx * w;
//		*x1 = p1->x + p1->dy * w;
//		*y1 = p1->y - p1->dx * w;
//	}
//	else {
//		*x0 = p1->x + p1->dmx * w;
//		*y0 = p1->y + p1->dmy * w;
//		*x1 = p1->x + p1->dmx * w;
//		*y1 = p1->y + p1->dmy * w;
//	}
//}

//static NVGvertex * __NANO2D_API(__roundJoin)(NVGvertex * dst, NVGpoint * p0, NVGpoint * p1,
//	float lw, float rw, float lu, float ru, int ncap,
//	float fringe)
//{
//	int i, n;
//	float dlx0 = p0->dy;
//	float dly0 = -p0->dx;
//	float dlx1 = p1->dy;
//	float dly1 = -p1->dx;
//	NVG_NOTUSED(fringe);
//
//	if (p1->flags & NVG_PT_LEFT) {
//		float lx0, ly0, lx1, ly1, a0, a1;
//		__NANO2D_API(__chooseBevel)(p1->flags & NVG_PR_INNERBEVEL, p0, p1, lw, &lx0, &ly0, &lx1, &ly1);
//		a0 = atan2f(-dly0, -dlx0);
//		a1 = atan2f(-dly1, -dlx1);
//		if (a1 > a0) a1 -= NVG_PI * 2;
//
//		__NANO2D_API(__vset)(dst, lx0, ly0, lu, 1); dst++;
//		__NANO2D_API(__vset)(dst, p1->x - dlx0 * rw, p1->y - dly0 * rw, ru, 1); dst++;
//
//		n = __NANO2D_API(__clampi)((int)ceilf(((a0 - a1) / NVG_PI) * ncap), 2, ncap);
//		for (i = 0; i < n; i++) {
//			float u = i / (float)(n - 1);
//			float a = a0 + u * (a1 - a0);
//			float rx = p1->x + cosf(a) * rw;
//			float ry = p1->y + sinf(a) * rw;
//			__NANO2D_API(__vset)(dst, p1->x, p1->y, 0.5f, 1); dst++;
//			__NANO2D_API(__vset)(dst, rx, ry, ru, 1); dst++;
//		}
//
//		__NANO2D_API(__vset)(dst, lx1, ly1, lu, 1); dst++;
//		__NANO2D_API(__vset)(dst, p1->x - dlx1 * rw, p1->y - dly1 * rw, ru, 1); dst++;
//
//	}
//	else {
//		float rx0, ry0, rx1, ry1, a0, a1;
//		__NANO2D_API(__chooseBevel)(p1->flags & NVG_PR_INNERBEVEL, p0, p1, -rw, &rx0, &ry0, &rx1, &ry1);
//		a0 = atan2f(dly0, dlx0);
//		a1 = atan2f(dly1, dlx1);
//		if (a1 < a0) a1 += NVG_PI * 2;
//
//		__NANO2D_API(__vset)(dst, p1->x + dlx0 * rw, p1->y + dly0 * rw, lu, 1); dst++;
//		__NANO2D_API(__vset)(dst, rx0, ry0, ru, 1); dst++;
//
//		n = __NANO2D_API(__clampi)((int)ceilf(((a1 - a0) / NVG_PI) * ncap), 2, ncap);
//		for (i = 0; i < n; i++) {
//			float u = i / (float)(n - 1);
//			float a = a0 + u * (a1 - a0);
//			float lx = p1->x + cosf(a) * lw;
//			float ly = p1->y + sinf(a) * lw;
//			__NANO2D_API(__vset)(dst, lx, ly, lu, 1); dst++;
//			__NANO2D_API(__vset)(dst, p1->x, p1->y, 0.5f, 1); dst++;
//		}
//
//		__NANO2D_API(__vset)(dst, p1->x + dlx1 * rw, p1->y + dly1 * rw, lu, 1); dst++;
//		__NANO2D_API(__vset)(dst, rx1, ry1, ru, 1); dst++;
//
//	}
//	return dst;
//}

//static NVGvertex * __NANO2D_API(__bevelJoin)(NVGvertex * dst, NVGpoint * p0, NVGpoint * p1,
//	float lw, float rw, float lu, float ru, float fringe)
//{
//	float rx0, ry0, rx1, ry1;
//	float lx0, ly0, lx1, ly1;
//	float dlx0 = p0->dy;
//	float dly0 = -p0->dx;
//	float dlx1 = p1->dy;
//	float dly1 = -p1->dx;
//	NVG_NOTUSED(fringe);
//
//	if (p1->flags & NVG_PT_LEFT) {
//		__NANO2D_API(__chooseBevel)(p1->flags & NVG_PR_INNERBEVEL, p0, p1, lw, &lx0, &ly0, &lx1, &ly1);
//
//		__NANO2D_API(__vset)(dst, lx0, ly0, lu, 1); dst++;
//		__NANO2D_API(__vset)(dst, p1->x - dlx0 * rw, p1->y - dly0 * rw, ru, 1); dst++;
//
//		if (p1->flags & NVG_PT_BEVEL) {
//			__NANO2D_API(__vset)(dst, lx0, ly0, lu, 1); dst++;
//			__NANO2D_API(__vset)(dst, p1->x - dlx0 * rw, p1->y - dly0 * rw, ru, 1); dst++;
//
//			__NANO2D_API(__vset)(dst, lx1, ly1, lu, 1); dst++;
//			__NANO2D_API(__vset)(dst, p1->x - dlx1 * rw, p1->y - dly1 * rw, ru, 1); dst++;
//		}
//		else {
//			rx0 = p1->x - p1->dmx * rw;
//			ry0 = p1->y - p1->dmy * rw;
//
//			__NANO2D_API(__vset)(dst, p1->x, p1->y, 0.5f, 1); dst++;
//			__NANO2D_API(__vset)(dst, p1->x - dlx0 * rw, p1->y - dly0 * rw, ru, 1); dst++;
//
//			__NANO2D_API(__vset)(dst, rx0, ry0, ru, 1); dst++;
//			__NANO2D_API(__vset)(dst, rx0, ry0, ru, 1); dst++;
//
//			__NANO2D_API(__vset)(dst, p1->x, p1->y, 0.5f, 1); dst++;
//			__NANO2D_API(__vset)(dst, p1->x - dlx1 * rw, p1->y - dly1 * rw, ru, 1); dst++;
//		}
//
//		__NANO2D_API(__vset)(dst, lx1, ly1, lu, 1); dst++;
//		__NANO2D_API(__vset)(dst, p1->x - dlx1 * rw, p1->y - dly1 * rw, ru, 1); dst++;
//
//	}
//	else {
//		__NANO2D_API(__chooseBevel)(p1->flags & NVG_PR_INNERBEVEL, p0, p1, -rw, &rx0, &ry0, &rx1, &ry1);
//
//		__NANO2D_API(__vset)(dst, p1->x + dlx0 * lw, p1->y + dly0 * lw, lu, 1); dst++;
//		__NANO2D_API(__vset)(dst, rx0, ry0, ru, 1); dst++;
//
//		if (p1->flags & NVG_PT_BEVEL) {
//			__NANO2D_API(__vset)(dst, p1->x + dlx0 * lw, p1->y + dly0 * lw, lu, 1); dst++;
//			__NANO2D_API(__vset)(dst, rx0, ry0, ru, 1); dst++;
//
//			__NANO2D_API(__vset)(dst, p1->x + dlx1 * lw, p1->y + dly1 * lw, lu, 1); dst++;
//			__NANO2D_API(__vset)(dst, rx1, ry1, ru, 1); dst++;
//		}
//		else {
//			lx0 = p1->x + p1->dmx * lw;
//			ly0 = p1->y + p1->dmy * lw;
//
//			__NANO2D_API(__vset)(dst, p1->x + dlx0 * lw, p1->y + dly0 * lw, lu, 1); dst++;
//			__NANO2D_API(__vset)(dst, p1->x, p1->y, 0.5f, 1); dst++;
//
//			__NANO2D_API(__vset)(dst, lx0, ly0, lu, 1); dst++;
//			__NANO2D_API(__vset)(dst, lx0, ly0, lu, 1); dst++;
//
//			__NANO2D_API(__vset)(dst, p1->x + dlx1 * lw, p1->y + dly1 * lw, lu, 1); dst++;
//			__NANO2D_API(__vset)(dst, p1->x, p1->y, 0.5f, 1); dst++;
//		}
//
//		__NANO2D_API(__vset)(dst, p1->x + dlx1 * lw, p1->y + dly1 * lw, lu, 1); dst++;
//		__NANO2D_API(__vset)(dst, rx1, ry1, ru, 1); dst++;
//	}
//
//	return dst;
//}

//static NVGvertex * __NANO2D_API(__buttCapStart)(NVGvertex * dst, NVGpoint * p,
//	float dx, float dy, float w, float d,
//	float aa, float u0, float u1)
//{
//	float px = p->x - dx * d;
//	float py = p->y - dy * d;
//	float dlx = dy;
//	float dly = -dx;
//	__NANO2D_API(__vset)(dst, px + dlx * w - dx * aa, py + dly * w - dy * aa, u0, 0); dst++;
//	__NANO2D_API(__vset)(dst, px - dlx * w - dx * aa, py - dly * w - dy * aa, u1, 0); dst++;
//	__NANO2D_API(__vset)(dst, px + dlx * w, py + dly * w, u0, 1); dst++;
//	__NANO2D_API(__vset)(dst, px - dlx * w, py - dly * w, u1, 1); dst++;
//	return dst;
//}

//static NVGvertex * __NANO2D_API(__buttCapEnd)(NVGvertex * dst, NVGpoint * p,
//	float dx, float dy, float w, float d,
//	float aa, float u0, float u1)
//{
//	float px = p->x + dx * d;
//	float py = p->y + dy * d;
//	float dlx = dy;
//	float dly = -dx;
//	__NANO2D_API(__vset)(dst, px + dlx * w, py + dly * w, u0, 1); dst++;
//	__NANO2D_API(__vset)(dst, px - dlx * w, py - dly * w, u1, 1); dst++;
//	__NANO2D_API(__vset)(dst, px + dlx * w + dx * aa, py + dly * w + dy * aa, u0, 0); dst++;
//	__NANO2D_API(__vset)(dst, px - dlx * w + dx * aa, py - dly * w + dy * aa, u1, 0); dst++;
//	return dst;
//}
//

//static NVGvertex * __NANO2D_API(__roundCapStart)(NVGvertex * dst, NVGpoint * p,
//	float dx, float dy, float w, int ncap,
//	float aa, float u0, float u1)
//{
//	int i;
//	float px = p->x;
//	float py = p->y;
//	float dlx = dy;
//	float dly = -dx;
//	NVG_NOTUSED(aa);
//	for (i = 0; i < ncap; i++) {
//		float a = i / (float)(ncap - 1) * NVG_PI;
//		float ax = cosf(a) * w, ay = sinf(a) * w;
//		__NANO2D_API(__vset)(dst, px - dlx * ax - dx * ay, py - dly * ax - dy * ay, u0, 1); dst++;
//		__NANO2D_API(__vset)(dst, px, py, 0.5f, 1); dst++;
//	}
//	__NANO2D_API(__vset)(dst, px + dlx * w, py + dly * w, u0, 1); dst++;
//	__NANO2D_API(__vset)(dst, px - dlx * w, py - dly * w, u1, 1); dst++;
//	return dst;
//}

//static NVGvertex * __NANO2D_API(__roundCapEnd)(NVGvertex * dst, NVGpoint * p,
//	float dx, float dy, float w, int ncap,
//	float aa, float u0, float u1)
//{
//	int i;
//	float px = p->x;
//	float py = p->y;
//	float dlx = dy;
//	float dly = -dx;
//	NVG_NOTUSED(aa);
//	__NANO2D_API(__vset)(dst, px + dlx * w, py + dly * w, u0, 1); dst++;
//	__NANO2D_API(__vset)(dst, px - dlx * w, py - dly * w, u1, 1); dst++;
//	for (i = 0; i < ncap; i++) {
//		float a = i / (float)(ncap - 1) * NVG_PI;
//		float ax = cosf(a) * w, ay = sinf(a) * w;
//		__NANO2D_API(__vset)(dst, px, py, 0.5f, 1); dst++;
//		__NANO2D_API(__vset)(dst, px - dlx * ax + dx * ay, py - dly * ax + dy * ay, u0, 1); dst++;
//	}
//	return dst;
//}


//static void __NANO2D_API(__calculateJoins)(NANO2D_CONTEXT * ctx, float w, int lineJoin, float miterLimit)
//{
//	NVGpathCache * cache = __NANO2D_CONTEXT(ctx)->cache;
//	int i, j;
//	float iw = 0.0f;
//
//	if (w > 0.0f) iw = 1.0f / w;
//
//	// Calculate which joins needs extra vertices to append, and gather vertex count.
//	for (i = 0; i < cache->npaths; i++) {
//		NVGpath * path = &cache->paths[i];
//		NVGpoint * pts = &cache->points[path->first];
//		NVGpoint * p0 = &pts[path->count - 1];
//		NVGpoint * p1 = &pts[0];
//		int nleft = 0;
//
//		path->nbevel = 0;
//
//		for (j = 0; j < path->count; j++) {
//			float dlx0, dly0, dlx1, dly1, dmr2, cross, limit;
//			dlx0 = p0->dy;
//			dly0 = -p0->dx;
//			dlx1 = p1->dy;
//			dly1 = -p1->dx;
//			// Calculate extrusions
//			p1->dmx = (dlx0 + dlx1) * 0.5f;
//			p1->dmy = (dly0 + dly1) * 0.5f;
//			dmr2 = p1->dmx * p1->dmx + p1->dmy * p1->dmy;
//			if (dmr2 > 0.000001f) {
//				float scale = 1.0f / dmr2;
//				if (scale > 600.0f) {
//					scale = 600.0f;
//				}
//				p1->dmx *= scale;
//				p1->dmy *= scale;
//			}
//
//			// Clear flags, but keep the corner.
//			p1->flags = (p1->flags & NVG_PT_CORNER) ? NVG_PT_CORNER : 0;
//
//			// Keep track of left turns.
//			cross = p1->dx * p0->dy - p0->dx * p1->dy;
//			if (cross > 0.0f) {
//				nleft++;
//				p1->flags |= NVG_PT_LEFT;
//			}
//
//			// Calculate if we should use bevel or miter for inner join.
//			limit = __NANO2D_API(__maxf)(1.01f, __NANO2D_API(__minf)(p0->len, p1->len) * iw);
//			if ((dmr2 * limit * limit) < 1.0f)
//				p1->flags |= NVG_PR_INNERBEVEL;
//
//			// Check to see if the corner needs to be beveled.
//			if (p1->flags & NVG_PT_CORNER) {
//				if ((dmr2 * miterLimit * miterLimit) < 1.0f || lineJoin == NVG_BEVEL || lineJoin == NVG_ROUND) {
//					p1->flags |= NVG_PT_BEVEL;
//				}
//			}
//
//			if ((p1->flags & (NVG_PT_BEVEL | NVG_PR_INNERBEVEL)) != 0)
//				path->nbevel++;
//
//			p0 = p1++;
//		}
//
//		path->convex = (nleft == path->count) ? 1 : 0;
//	}
//}


//static int __NANO2D_API(__expandStroke)(NANO2D_CONTEXT * ctx, float w, float fringe, int lineCap, int lineJoin, float miterLimit)
//{
//	NVGpathCache * cache = __NANO2D_CONTEXT(ctx)->cache;
//	NVGvertex * verts;
//	NVGvertex * dst;
//	int cverts, i, j;
//	float aa = fringe;//__NANO2D_CONTEXT(ctx)->fringeWidth;
//	float u0 = 0.0f, u1 = 1.0f;
//	int ncap = __NANO2D_API(__curveDivs)(w, NVG_PI, __NANO2D_CONTEXT(ctx)->tessTol);	// Calculate divisions per half circle.
//
//	w += aa * 0.5f;
//
//	// Disable the gradient used for antialiasing when antialiasing is not used.
//	if (aa == 0.0f) {
//		u0 = 0.5f;
//		u1 = 0.5f;
//	}
//
//	__NANO2D_API(__calculateJoins)(ctx, w, lineJoin, miterLimit);
//
//	// Calculate max vertex usage.
//	cverts = 0;
//	for (i = 0; i < cache->npaths; i++) {
//		NVGpath * path = &cache->paths[i];
//		int loop = (path->closed == 0) ? 0 : 1;
//		if (lineJoin == NVG_ROUND)
//			cverts += (path->count + path->nbevel * (ncap + 2) + 1) * 2; // plus one for loop
//		else
//			cverts += (path->count + path->nbevel * 5 + 1) * 2; // plus one for loop
//		if (loop == 0) {
//			// space for caps
//			if (lineCap == NVG_ROUND) {
//				cverts += (ncap * 2 + 2) * 2;
//			}
//			else {
//				cverts += (3 + 3) * 2;
//			}
//		}
//	}
//
//	verts = __NANO2D_API(__allocTempVerts)(ctx, cverts);
//	if (verts == NULL) return 0;
//
//	for (i = 0; i < cache->npaths; i++) {
//		NVGpath * path = &cache->paths[i];
//		NVGpoint * pts = &cache->points[path->first];
//		NVGpoint * p0;
//		NVGpoint * p1;
//		int s, e, loop;
//		float dx, dy;
//
//		path->fill = 0;
//		path->nfill = 0;
//
//		// Calculate fringe or stroke
//		loop = (path->closed == 0) ? 0 : 1;
//		dst = verts;
//		path->stroke = dst;
//
//		if (loop) {
//			// Looping
//			p0 = &pts[path->count - 1];
//			p1 = &pts[0];
//			s = 0;
//			e = path->count;
//		}
//		else {
//			// Add cap
//			p0 = &pts[0];
//			p1 = &pts[1];
//			s = 1;
//			e = path->count - 1;
//		}
//
//		if (loop == 0) {
//			// Add cap
//			dx = p1->x - p0->x;
//			dy = p1->y - p0->y;
//			__NANO2D_API(__normalize)(&dx, &dy);
//			if (lineCap == NVG_BUTT)
//				dst = __NANO2D_API(__buttCapStart)(dst, p0, dx, dy, w, -aa * 0.5f, aa, u0, u1);
//			else if (lineCap == NVG_BUTT || lineCap == NVG_SQUARE)
//				dst = __NANO2D_API(__buttCapStart)(dst, p0, dx, dy, w, w - aa, aa, u0, u1);
//			else if (lineCap == NVG_ROUND)
//				dst = __NANO2D_API(__roundCapStart)(dst, p0, dx, dy, w, ncap, aa, u0, u1);
//		}
//
//		for (j = s; j < e; ++j) {
//			if ((p1->flags & (NVG_PT_BEVEL | NVG_PR_INNERBEVEL)) != 0) {
//				if (lineJoin == NVG_ROUND) {
//					dst = __NANO2D_API(__roundJoin)(dst, p0, p1, w, w, u0, u1, ncap, aa);
//				}
//				else {
//					dst = __NANO2D_API(__bevelJoin)(dst, p0, p1, w, w, u0, u1, aa);
//				}
//			}
//			else {
//				__NANO2D_API(__vset)(dst, p1->x + (p1->dmx * w), p1->y + (p1->dmy * w), u0, 1); dst++;
//				__NANO2D_API(__vset)(dst, p1->x - (p1->dmx * w), p1->y - (p1->dmy * w), u1, 1); dst++;
//			}
//			p0 = p1++;
//		}
//
//		if (loop) {
//			// Loop it
//			__NANO2D_API(__vset)(dst, verts[0].x, verts[0].y, u0, 1); dst++;
//			__NANO2D_API(__vset)(dst, verts[1].x, verts[1].y, u1, 1); dst++;
//		}
//		else {
//			// Add cap
//			dx = p1->x - p0->x;
//			dy = p1->y - p0->y;
//			__NANO2D_API(__normalize)(&dx, &dy);
//			if (lineCap == NVG_BUTT)
//				dst = __NANO2D_API(__buttCapEnd)(dst, p1, dx, dy, w, -aa * 0.5f, aa, u0, u1);
//			else if (lineCap == NVG_BUTT || lineCap == NVG_SQUARE)
//				dst = __NANO2D_API(__buttCapEnd)(dst, p1, dx, dy, w, w - aa, aa, u0, u1);
//			else if (lineCap == NVG_ROUND)
//				dst = __NANO2D_API(__roundCapEnd)(dst, p1, dx, dy, w, ncap, aa, u0, u1);
//		}
//
//		path->nstroke = (int)(dst - verts);
//
//		verts = dst;
//	}
//
//	return 1;
//}

//static int __NANO2D_API(__expandFill)(NANO2D_CONTEXT * ctx, float w, int lineJoin, float miterLimit)
//{
//	NVGpathCache * cache = __NANO2D_CONTEXT(ctx)->cache;
//	NVGvertex * verts;
//	NVGvertex * dst;
//	int cverts, convex, i, j;
//	float aa = __NANO2D_CONTEXT(ctx)->fringeWidth;
//	int fringe = w > 0.0f;
//
//	__NANO2D_API(__calculateJoins)(ctx, w, lineJoin, miterLimit);
//
//	// Calculate max vertex usage.
//	cverts = 0;
//	for (i = 0; i < cache->npaths; i++) {
//		NVGpath * path = &cache->paths[i];
//		cverts += path->count + path->nbevel + 1;
//		if (fringe)
//			cverts += (path->count + path->nbevel * 5 + 1) * 2; // plus one for loop
//	}
//
//	verts = __NANO2D_API(__allocTempVerts)(ctx, cverts);
//	if (verts == NULL) return 0;
//
//	convex = cache->npaths == 1 && cache->paths[0].convex;
//
//	for (i = 0; i < cache->npaths; i++) {
//		NVGpath * path = &cache->paths[i];
//		NVGpoint * pts = &cache->points[path->first];
//		NVGpoint * p0;
//		NVGpoint * p1;
//		float rw, lw, woff;
//		float ru, lu;
//
//		// Calculate shape vertices.
//		woff = 0.5f * aa;
//		dst = verts;
//		path->fill = dst;
//
//		if (fringe) {
//			// Looping
//			p0 = &pts[path->count - 1];
//			p1 = &pts[0];
//			for (j = 0; j < path->count; ++j) {
//				if (p1->flags & NVG_PT_BEVEL) {
//					float dlx0 = p0->dy;
//					float dly0 = -p0->dx;
//					float dlx1 = p1->dy;
//					float dly1 = -p1->dx;
//					if (p1->flags & NVG_PT_LEFT) {
//						float lx = p1->x + p1->dmx * woff;
//						float ly = p1->y + p1->dmy * woff;
//						__NANO2D_API(__vset)(dst, lx, ly, 0.5f, 1); dst++;
//					}
//					else {
//						float lx0 = p1->x + dlx0 * woff;
//						float ly0 = p1->y + dly0 * woff;
//						float lx1 = p1->x + dlx1 * woff;
//						float ly1 = p1->y + dly1 * woff;
//						__NANO2D_API(__vset)(dst, lx0, ly0, 0.5f, 1); dst++;
//						__NANO2D_API(__vset)(dst, lx1, ly1, 0.5f, 1); dst++;
//					}
//				}
//				else {
//					__NANO2D_API(__vset)(dst, p1->x + (p1->dmx * woff), p1->y + (p1->dmy * woff), 0.5f, 1); dst++;
//				}
//				p0 = p1++;
//			}
//		}
//		else {
//			for (j = 0; j < path->count; ++j) {
//				__NANO2D_API(__vset)(dst, pts[j].x, pts[j].y, 0.5f, 1);
//				dst++;
//			}
//		}
//
//		path->nfill = (int)(dst - verts);
//		verts = dst;
//
//		// Calculate fringe
//		if (fringe) {
//			lw = w + woff;
//			rw = w - woff;
//			lu = 0;
//			ru = 1;
//			dst = verts;
//			path->stroke = dst;
//
//			// Create only half a fringe for convex shapes so that
//			// the shape can be rendered without stenciling.
//			if (convex) {
//				lw = woff;	// This should generate the same vertex as fill inset above.
//				lu = 0.5f;	// Set outline fade at middle.
//			}
//
//			// Looping
//			p0 = &pts[path->count - 1];
//			p1 = &pts[0];
//
//			for (j = 0; j < path->count; ++j) {
//				if ((p1->flags & (NVG_PT_BEVEL | NVG_PR_INNERBEVEL)) != 0) {
//					dst = __NANO2D_API(__bevelJoin)(dst, p0, p1, lw, rw, lu, ru, __NANO2D_CONTEXT(ctx)->fringeWidth);
//				}
//				else {
//					__NANO2D_API(__vset)(dst, p1->x + (p1->dmx * lw), p1->y + (p1->dmy * lw), lu, 1); dst++;
//					__NANO2D_API(__vset)(dst, p1->x - (p1->dmx * rw), p1->y - (p1->dmy * rw), ru, 1); dst++;
//				}
//				p0 = p1++;
//			}
//
//			// Loop it
//			__NANO2D_API(__vset)(dst, verts[0].x, verts[0].y, lu, 1); dst++;
//			__NANO2D_API(__vset)(dst, verts[1].x, verts[1].y, ru, 1); dst++;
//
//			path->nstroke = (int)(dst - verts);
//			verts = dst;
//		}
//		else {
//			path->stroke = NULL;
//			path->nstroke = 0;
//		}
//	}
//
//	return 1;
//}


// Draw
void __NANO2D_API(BeginPath)(NANO2D_CONTEXT * ctx)
{
	//__NANO2D_CONTEXT(ctx)->ncommands = 0;
	//__NANO2D_API(__clearPathCache)(ctx);

	__NANO2D_CONTEXT(ctx)->begin_path();

}

void __NANO2D_API(MoveTo)(NANO2D_CONTEXT * ctx, float x, float y)
{
	//float vals[] = { NVG_MOVETO, x, y };
	//__NANO2D_API(__appendCommands)(ctx, vals, NVG_COUNTOF(vals));
	__NANO2D_CONTEXT(ctx)->move_to(x, y);
}

void __NANO2D_API(LineTo)(NANO2D_CONTEXT * ctx, float x, float y)
{
	/*float vals[] = { NVG_LINETO, x, y };
	__NANO2D_API(__appendCommands)(ctx, vals, NVG_COUNTOF(vals));*/

	__NANO2D_CONTEXT(ctx)->line_to(x, y);
}

void __NANO2D_API(BezierTo)(NANO2D_CONTEXT * ctx, float c1x, float c1y, float c2x, float c2y, float x, float y)
{
	float vals[] = { NVG_BEZIERTO, c1x, c1y, c2x, c2y, x, y };
	__NANO2D_API(__appendCommands)(ctx, vals, NVG_COUNTOF(vals));
}

void __NANO2D_API(QuadTo)(NANO2D_CONTEXT * ctx, float cx, float cy, float x, float y)
{
	float x0 = __NANO2D_CONTEXT(ctx)->commandx;
	float y0 = __NANO2D_CONTEXT(ctx)->commandy;
	float vals[] = { NVG_BEZIERTO,
		 x0 + 2.0f / 3.0f * (cx - x0), y0 + 2.0f / 3.0f * (cy - y0),
		 x + 2.0f / 3.0f * (cx - x), y + 2.0f / 3.0f * (cy - y),
		 x, y };
	__NANO2D_API(__appendCommands)(ctx, vals, NVG_COUNTOF(vals));
}

void __NANO2D_API(ArcTo)(NANO2D_CONTEXT * ctx, float x1, float y1, float x2, float y2, float radius)
{
	float x0 = __NANO2D_CONTEXT(ctx)->commandx;
	float y0 = __NANO2D_CONTEXT(ctx)->commandy;
	float dx0, dy0, dx1, dy1, a, d, cx, cy, a0, a1;
	int dir;

	if (__NANO2D_CONTEXT(ctx)->ncommands == 0) {
		return;
	}

	// Handle degenerate cases.
	if (__NANO2D_API(__ptEquals)(x0, y0, x1, y1, __NANO2D_CONTEXT(ctx)->distTol) ||
		__NANO2D_API(__ptEquals)(x1, y1, x2, y2, __NANO2D_CONTEXT(ctx)->distTol) ||
		__NANO2D_API(__distPtSeg)(x1, y1, x0, y0, x2, y2) < __NANO2D_CONTEXT(ctx)->distTol * __NANO2D_CONTEXT(ctx)->distTol ||
		radius < __NANO2D_CONTEXT(ctx)->distTol) {
		__NANO2D_API(LineTo)(ctx, x1, y1);
		return;
	}

	// Calculate tangential circle to lines (x0,y0)-(x1,y1) and (x1,y1)-(x2,y2).
	dx0 = x0 - x1;
	dy0 = y0 - y1;
	dx1 = x2 - x1;
	dy1 = y2 - y1;
	__NANO2D_API(__normalize)(&dx0, &dy0);
	__NANO2D_API(__normalize)(&dx1, &dy1);
	a = __NANO2D_API(__acosf)(dx0 * dx1 + dy0 * dy1);
	d = radius / __NANO2D_API(__tanf)(a / 2.0f);

	//	printf("a=%f� d=%f\n", a/NVG_PI*180.0f, d);

	if (d > 10000.0f) {
		__NANO2D_API(LineTo)(ctx, x1, y1);
		return;
	}

	if (__NANO2D_API(__cross)(dx0, dy0, dx1, dy1) > 0.0f) {
		cx = x1 + dx0 * d + dy0 * radius;
		cy = y1 + dy0 * d + -dx0 * radius;
		a0 = __NANO2D_API(__atan2f)(dx0, -dy0);
		a1 = __NANO2D_API(__atan2f)(-dx1, dy1);
		dir = NVG_CW;
		//		printf("CW c=(%f, %f) a0=%f� a1=%f�\n", cx, cy, a0/NVG_PI*180.0f, a1/NVG_PI*180.0f);
	}
	else {
		cx = x1 + dx0 * d + -dy0 * radius;
		cy = y1 + dy0 * d + dx0 * radius;
		a0 = __NANO2D_API(__atan2f)(-dx0, dy0);
		a1 = __NANO2D_API(__atan2f)(dx1, -dy1);
		dir = NVG_CCW;
		//		printf("CCW c=(%f, %f) a0=%f� a1=%f�\n", cx, cy, a0/NVG_PI*180.0f, a1/NVG_PI*180.0f);
	}

	__NANO2D_API(Arc)(ctx, cx, cy, radius, a0, a1, dir);
}

void __NANO2D_API(ClosePath)(NANO2D_CONTEXT * ctx)
{
	//float vals[] = { NVG_CLOSE };
	//__NANO2D_API(__appendCommands)(ctx, vals, NVG_COUNTOF(vals));
	__NANO2D_CONTEXT(ctx)->close_path();
}

void __NANO2D_API(PathWinding)(NANO2D_CONTEXT * ctx, int dir)
{
	//float vals[] = { NVG_WINDING, (float)dir };
	//__NANO2D_API(__appendCommands)(ctx, vals, NVG_COUNTOF(vals));

	__NANO2D_CONTEXT(ctx)->path_winding(dir);

}

void __NANO2D_API(Arc)(NANO2D_CONTEXT * ctx, float cx, float cy, float r, float a0, float a1, int dir)
{
	__NANO2D_CONTEXT(ctx)->arc(cx, cy, r, a0, a1, dir);
	//float a = 0, da = 0, hda = 0, kappa = 0;
	//float dx = 0, dy = 0, x = 0, y = 0, tanx = 0, tany = 0;
	//float px = 0, py = 0, ptanx = 0, ptany = 0;
	//float vals[3 + 5 * 7 + 100];
	//int i, ndivs, nvals;
	//int move = __NANO2D_CONTEXT(ctx)->ncommands > 0 ? NVG_LINETO : NVG_MOVETO;

	//// Clamp angles
	//da = a1 - a0;
	//if (dir == NVG_CW) {
	//	if (__NANO2D_API(__absf)(da) >= NVG_PI * 2) {
	//		da = NVG_PI * 2;
	//	}
	//	else {
	//		while (da < 0.0f) da += NVG_PI * 2;
	//	}
	//}
	//else {
	//	if (__NANO2D_API(__absf)(da) >= NVG_PI * 2) {
	//		da = -NVG_PI * 2;
	//	}
	//	else {
	//		while (da > 0.0f) da -= NVG_PI * 2;
	//	}
	//}

	//// Split arc into max 90 degree segments.
	//ndivs = __NANO2D_API(__maxi)(1, __NANO2D_API(__mini)((int)(__NANO2D_API(__absf)(da) / (NVG_PI * 0.5f) + 0.5f), 5));
	//hda = (da / (float)ndivs) / 2.0f;
	//kappa = __NANO2D_API(__absf)(4.0f / 3.0f * (1.0f - __NANO2D_API(__cosf)(hda)) / __NANO2D_API(__sinf)(hda));

	//if (dir == NVG_CCW)
	//	kappa = -kappa;

	//nvals = 0;
	//for (i = 0; i <= ndivs; i++) {
	//	a = a0 + da * (i / (float)ndivs);
	//	dx = __NANO2D_API(__cosf)(a);
	//	dy = __NANO2D_API(__sinf)(a);
	//	x = cx + dx * r;
	//	y = cy + dy * r;
	//	tanx = -dy * r * kappa;
	//	tany = dx * r * kappa;

	//	if (i == 0) {
	//		vals[nvals++] = (float)move;
	//		vals[nvals++] = x;
	//		vals[nvals++] = y;
	//	}
	//	else {
	//		vals[nvals++] = NVG_BEZIERTO;
	//		vals[nvals++] = px + ptanx;
	//		vals[nvals++] = py + ptany;
	//		vals[nvals++] = x - tanx;
	//		vals[nvals++] = y - tany;
	//		vals[nvals++] = x;
	//		vals[nvals++] = y;
	//	}
	//	px = x;
	//	py = y;
	//	ptanx = tanx;
	//	ptany = tany;
	//}

	//__NANO2D_API(__appendCommands)(ctx, vals, nvals);
}

void __NANO2D_API(Rect)(NANO2D_CONTEXT * ctx, float x, float y, float w, float h)
{
	//float vals[] = {
	//	NVG_MOVETO, x,y,
	//	NVG_LINETO, x,y + h,
	//	NVG_LINETO, x + w,y + h,
	//	NVG_LINETO, x + w,y,
	//	NVG_CLOSE
	//};
	//__NANO2D_API(__appendCommands)(ctx, vals, NVG_COUNTOF(vals));
	__NANO2D_CONTEXT(ctx)->rect(x, y, w, h);
}

void __NANO2D_API(RoundedRect)(NANO2D_CONTEXT * ctx, float x, float y, float w, float h, float r)
{
//	__NANO2D_API(RoundedRectVarying)(ctx, x, y, w, h, r, r, r, r);

	__NANO2D_CONTEXT(ctx)->rounded_rect(x, y, w, h, r);

}

void __NANO2D_API(RoundedRectVarying)(NANO2D_CONTEXT * ctx, float x, float y, float w, float h, float radTopLeft, float radTopRight, float radBottomRight, float radBottomLeft)
{
	if (radTopLeft < 0.1f && radTopRight < 0.1f && radBottomRight < 0.1f && radBottomLeft < 0.1f) {
		__NANO2D_API(Rect)(ctx, x, y, w, h);
		return;
	}
	else {
		float halfw = __NANO2D_API(__absf)(w) * 0.5f;
		float halfh = __NANO2D_API(__absf)(h) * 0.5f;
		float rxBL = __NANO2D_API(__minf)(radBottomLeft, halfw) * __NANO2D_API(__signf)(w), ryBL = __NANO2D_API(__minf)(radBottomLeft, halfh) * __NANO2D_API(__signf)(h);
		float rxBR = __NANO2D_API(__minf)(radBottomRight, halfw) * __NANO2D_API(__signf)(w), ryBR = __NANO2D_API(__minf)(radBottomRight, halfh) * __NANO2D_API(__signf)(h);
		float rxTR = __NANO2D_API(__minf)(radTopRight, halfw) * __NANO2D_API(__signf)(w), ryTR = __NANO2D_API(__minf)(radTopRight, halfh) * __NANO2D_API(__signf)(h);
		float rxTL = __NANO2D_API(__minf)(radTopLeft, halfw) * __NANO2D_API(__signf)(w), ryTL = __NANO2D_API(__minf)(radTopLeft, halfh) * __NANO2D_API(__signf)(h);
		float vals[] = {
			NVG_MOVETO, x, y + ryTL,
			NVG_LINETO, x, y + h - ryBL,
			NVG_BEZIERTO, x, y + h - ryBL * (1 - NVG_KAPPA90), x + rxBL * (1 - NVG_KAPPA90), y + h, x + rxBL, y + h,
			NVG_LINETO, x + w - rxBR, y + h,
			NVG_BEZIERTO, x + w - rxBR * (1 - NVG_KAPPA90), y + h, x + w, y + h - ryBR * (1 - NVG_KAPPA90), x + w, y + h - ryBR,
			NVG_LINETO, x + w, y + ryTR,
			NVG_BEZIERTO, x + w, y + ryTR * (1 - NVG_KAPPA90), x + w - rxTR * (1 - NVG_KAPPA90), y, x + w - rxTR, y,
			NVG_LINETO, x + rxTL, y,
			NVG_BEZIERTO, x + rxTL * (1 - NVG_KAPPA90), y, x, y + ryTL * (1 - NVG_KAPPA90), x, y + ryTL,
			NVG_CLOSE
		};
		__NANO2D_API(__appendCommands)(ctx, vals, NVG_COUNTOF(vals));
	}
}

void __NANO2D_API(Ellipse)(NANO2D_CONTEXT * ctx, float cx, float cy, float rx, float ry)
{
	//float vals[] = {
	//	NVG_MOVETO, cx - rx, cy,
	//	NVG_BEZIERTO, cx - rx, cy + ry * NVG_KAPPA90, cx - rx * NVG_KAPPA90, cy + ry, cx, cy + ry,
	//	NVG_BEZIERTO, cx + rx * NVG_KAPPA90, cy + ry, cx + rx, cy + ry * NVG_KAPPA90, cx + rx, cy,
	//	NVG_BEZIERTO, cx + rx, cy - ry * NVG_KAPPA90, cx + rx * NVG_KAPPA90, cy - ry, cx, cy - ry,
	//	NVG_BEZIERTO, cx - rx * NVG_KAPPA90, cy - ry, cx - rx, cy - ry * NVG_KAPPA90, cx - rx, cy,
	//	NVG_CLOSE
	//};
	//__NANO2D_API(__appendCommands)(ctx, vals, NVG_COUNTOF(vals));

	__NANO2D_CONTEXT(ctx)->ellipse(cx, cy, rx, ry);

}

void __NANO2D_API(Circle)(NANO2D_CONTEXT * ctx, float cx, float cy, float r)
{
	__NANO2D_API(Ellipse)(ctx, cx, cy, r, r);
}

void __NANO2D_API(DebugDumpPathCache)(NANO2D_CONTEXT * ctx)
{
	const NVGpath * path;
	int i, j;

	printf("Dumping %d cached paths\n", __NANO2D_CONTEXT(ctx)->cache->npaths);
	for (i = 0; i < __NANO2D_CONTEXT(ctx)->cache->npaths; i++) {
		path = &__NANO2D_CONTEXT(ctx)->cache->paths[i];
		printf(" - Path %d\n", i);
		if (path->nfill) {
			printf("   - fill: %d\n", path->nfill);
			for (j = 0; j < path->nfill; j++)
				printf("%f\t%f\n", path->fill[j].x, path->fill[j].y);
		}
		if (path->nstroke) {
			printf("   - stroke: %d\n", path->nstroke);
			for (j = 0; j < path->nstroke; j++)
				printf("%f\t%f\n", path->stroke[j].x, path->stroke[j].y);
		}
	}
}

void __NANO2D_API(Fill)(NANO2D_CONTEXT * ctx)
{

	//NVGstate * state = __NANO2D_API(__getState)(ctx);
	//const NVGpath * path;
	//NANO2D_PAINT fillPaint = state->fill;
	//int i;

	//__NANO2D_API(__flattenPaths)(ctx);
	//if (__NANO2D_CONTEXT(ctx)->params.edgeAntiAlias && state->shapeAntiAlias)
	//	__NANO2D_API(__expandFill)(ctx, __NANO2D_CONTEXT(ctx)->fringeWidth, NVG_MITER, 2.4f);
	//else
	//	__NANO2D_API(__expandFill)(ctx, 0.0f, NVG_MITER, 2.4f);

	//// Apply global alpha
	//fillPaint.innerColor.a *= state->alpha;
	//fillPaint.outerColor.a *= state->alpha;

	//__NANO2D_CONTEXT(ctx)->params.renderFill(__NANO2D_CONTEXT(ctx)->params.userPtr, &fillPaint, state->compositeOperation, &state->scissor, __NANO2D_CONTEXT(ctx)->fringeWidth,
	//	__NANO2D_CONTEXT(ctx)->cache->bounds, __NANO2D_CONTEXT(ctx)->cache->paths, __NANO2D_CONTEXT(ctx)->cache->npaths);

	//// Count triangles
	//for (i = 0; i < __NANO2D_CONTEXT(ctx)->cache->npaths; i++) {
	//	path = &__NANO2D_CONTEXT(ctx)->cache->paths[i];
	//	__NANO2D_CONTEXT(ctx)->fillTriCount += path->nfill - 2;
	//	__NANO2D_CONTEXT(ctx)->fillTriCount += path->nstroke - 2;
	//	__NANO2D_CONTEXT(ctx)->drawCallCount += 2;
	//}

	__NANO2D_CONTEXT(ctx)->fill();

}

void __NANO2D_API(Stroke)(NANO2D_CONTEXT * ctx)
{

	__NANO2D_CONTEXT(ctx)->stroke();


	//NVGstate * state = __NANO2D_API(__getState)(ctx);
	//float scale = __NANO2D_API(__getAverageScale)(state->xform);
	//float strokeWidth = __NANO2D_API(__clampf)(state->strokeWidth * scale, 0.0f, 200.0f);
	//NANO2D_PAINT strokePaint = state->stroke;
	//const NVGpath * path;
	//int i;


	//if (strokeWidth < __NANO2D_CONTEXT(ctx)->fringeWidth) {
	//	// If the stroke width is less than pixel size, use alpha to emulate coverage.
	//	// Since coverage is area, scale by alpha*alpha.
	//	float alpha = __NANO2D_API(__clampf)(strokeWidth / __NANO2D_CONTEXT(ctx)->fringeWidth, 0.0f, 1.0f);
	//	strokePaint.innerColor.a *= alpha * alpha;
	//	strokePaint.outerColor.a *= alpha * alpha;
	//	strokeWidth = __NANO2D_CONTEXT(ctx)->fringeWidth;
	//}

	//// Apply global alpha
	//strokePaint.innerColor.a *= state->alpha;
	//strokePaint.outerColor.a *= state->alpha;

	//__NANO2D_API(__flattenPaths)(ctx);

	//if (__NANO2D_CONTEXT(ctx)->params.edgeAntiAlias && state->shapeAntiAlias)
	//	__NANO2D_API(__expandStroke)(ctx, strokeWidth * 0.5f, __NANO2D_CONTEXT(ctx)->fringeWidth, state->lineCap, state->lineJoin, state->miterLimit);
	//else
	//	__NANO2D_API(__expandStroke)(ctx, strokeWidth * 0.5f, 0.0f, state->lineCap, state->lineJoin, state->miterLimit);

	//__NANO2D_CONTEXT(ctx)->params.renderStroke(__NANO2D_CONTEXT(ctx)->params.userPtr, &strokePaint, state->compositeOperation, &state->scissor, __NANO2D_CONTEXT(ctx)->fringeWidth,
	//	strokeWidth, __NANO2D_CONTEXT(ctx)->cache->paths, __NANO2D_CONTEXT(ctx)->cache->npaths);

	//// Count triangles
	//for (i = 0; i < __NANO2D_CONTEXT(ctx)->cache->npaths; i++) {
	//	path = &__NANO2D_CONTEXT(ctx)->cache->paths[i];
	//	__NANO2D_CONTEXT(ctx)->strokeTriCount += path->nstroke - 2;
	//	__NANO2D_CONTEXT(ctx)->drawCallCount++;
	//}
}

// Add fonts
//int __NANO2D_API(CreateFont)(NANO2D_CONTEXT * ctx, const char * name, const char * filename)
//{
//	//return fonsAddFont(__NANO2D_CONTEXT(ctx)->fs, name, filename, 0);
//	return -1;
//}

int __NANO2D_API(CreateFontAtIndex)(NANO2D_CONTEXT * ctx, const char * name, const char * filename, const int fontIndex)
{
	//return fonsAddFont(__NANO2D_CONTEXT(ctx)->fs, name, filename, fontIndex);
	return -1;
}

int __NANO2D_API(CreateFontMem)(NANO2D_CONTEXT * ctx, const char * name, unsigned char * data, int ndata, int freeData)
{
	//return fonsAddFontMem(__NANO2D_CONTEXT(ctx)->fs, name, data, ndata, freeData, 0);
	return -1;
}

int __NANO2D_API(CreateFontMemAtIndex)(NANO2D_CONTEXT * ctx, const char * name, unsigned char * data, int ndata, int freeData, const int fontIndex)
{
	//return fonsAddFontMem(__NANO2D_CONTEXT(ctx)->fs, name, data, ndata, freeData, fontIndex);
	return -1;
}

int __NANO2D_API(FindFont)(NANO2D_CONTEXT * ctx, const char * name)
{
	//if (name == NULL) return -1;
	//return fonsGetFontByName(__NANO2D_CONTEXT(ctx)->fs, name);
	return -1;
}


int __NANO2D_API(AddFallbackFontId)(NANO2D_CONTEXT * ctx, int baseFont, int fallbackFont)
{
	//if (baseFont == -1 || fallbackFont == -1) return 0;
	//return fonsAddFallbackFont(__NANO2D_CONTEXT(ctx)->fs, baseFont, fallbackFont);
	return -1;
}

int __NANO2D_API(AddFallbackFont)(NANO2D_CONTEXT * ctx, const char * baseFont, const char * fallbackFont)
{
	//return __NANO2D_API(AddFallbackFontId)(ctx, __NANO2D_API(FindFont)(ctx, baseFont), __NANO2D_API(FindFont)(ctx, fallbackFont));
	return -1;
}

void __NANO2D_API(ResetFallbackFontsId)(NANO2D_CONTEXT * ctx, int baseFont)
{
	//fonsResetFallbackFont(__NANO2D_CONTEXT(ctx)->fs, baseFont);
	return;
}

void __NANO2D_API(ResetFallbackFonts)(NANO2D_CONTEXT * ctx, const char * baseFont)
{
	//__NANO2D_API(ResetFallbackFontsId)(ctx, __NANO2D_API(FindFont)(ctx, baseFont));
	return;
}

// State setting
void __NANO2D_API(FontSize)(NANO2D_CONTEXT * ctx, float size)
{
	//NVGstate * state = __NANO2D_API(__getState)(ctx);
	//state->fontSize = size;
	__NANO2D_CONTEXT(ctx)->font_size(size);
}

void __NANO2D_API(FontBlur)(NANO2D_CONTEXT * ctx, float blur)
{
	//NVGstate * state = __NANO2D_API(__getState)(ctx);
	//state->fontBlur = blur;
	//throw_todo();
   __NANO2D_CONTEXT(ctx)->font_blur(blur);
}


//::write_text::font_pointer __NANO2D_API(CreateFont)(NANO2D_CONTEXT * ctx, const char * face, float size)
//{
//   
//   return __NANO2D_CONTEXT(ctx)->create_font(face, size);
//   
//}


void __NANO2D_API(TextLetterSpacing)(NANO2D_CONTEXT * ctx, float spacing)
{
	//NVGstate * state = __NANO2D_API(__getState)(ctx);
	//state->letterSpacing = spacing;
	throw_todo();
}

void __NANO2D_API(TextLineHeight)(NANO2D_CONTEXT * ctx, float lineHeight)
{
	//NVGstate * state = __NANO2D_API(__getState)(ctx);
	//state->lineHeight = lineHeight;
   __NANO2D_CONTEXT(ctx)->text_line_height(lineHeight);
}

void __NANO2D_API(TextAlign)(NANO2D_CONTEXT * ctx, int align)
{
	//NVGstate * state = __NANO2D_API(__getState)(ctx);
	//state->textAlign = align;

	__NANO2D_CONTEXT(ctx)->text_align(align);
}

void __NANO2D_API(FontFaceId)(NANO2D_CONTEXT * ctx, int font)
{
	//NVGstate * state = __NANO2D_API(__getState)(ctx);
	//state->fontId = font;
	throw_todo();
}

void __NANO2D_API(FontFace)(NANO2D_CONTEXT * ctx, const char * font)
{
	//NVGstate * state = __NANO2D_API(__getState)(ctx);
	//state->fontId = fonsGetFontByName(__NANO2D_CONTEXT(ctx)->fs, font);

	__NANO2D_CONTEXT(ctx)->font_face(font);

}

//static float __NANO2D_API(__quantize)(float a, float d)
//{
//	return ((int)(a / d + 0.5f)) * d;
//}

//static float __NANO2D_API(__getFontScale)(NVGstate * state)
//{
//	return __NANO2D_API(__minf)(__NANO2D_API(__quantize)(__NANO2D_API(__getAverageScale)(state->xform), 0.01f), 4.0f);
//}

//static void __NANO2D_API(__flushTextTexture)(NANO2D_CONTEXT * ctx)
//{
//	//int dirty[4];
//
//	//if (fonsValidateTexture(__NANO2D_CONTEXT(ctx)->fs, dirty)) {
//	//	int fontImage = __NANO2D_CONTEXT(ctx)->fontImages[__NANO2D_CONTEXT(ctx)->fontImageIdx];
//	//	// Update texture
//	//	if (fontImage != 0) {
//	//		int iw, ih;
//	//		const unsigned char * data = fonsGetTextureData(__NANO2D_CONTEXT(ctx)->fs, &iw, &ih);
//	//		int x = dirty[0];
//	//		int y = dirty[1];
//	//		int w = dirty[2] - dirty[0];
//	//		int h = dirty[3] - dirty[1];
//	//		__NANO2D_CONTEXT(ctx)->params.renderUpdateTexture(__NANO2D_CONTEXT(ctx)->params.userPtr, fontImage, x, y, w, h, data);
//	//	}
//	//}
//}

//static int __NANO2D_API(__allocTextAtlas)(NANO2D_CONTEXT * ctx)
//{
//	//int iw, ih;
//	//__NANO2D_API(__flushTextTexture)(ctx);
//	//if (__NANO2D_CONTEXT(ctx)->fontImageIdx >= NVG_MAX_FONTIMAGES - 1)
//	//	return 0;
//	//// if next fontImage already have a texture
//	//if (__NANO2D_CONTEXT(ctx)->fontImages[__NANO2D_CONTEXT(ctx)->fontImageIdx + 1] != 0)
//	//	__NANO2D_API(ImageSize)(ctx, __NANO2D_CONTEXT(ctx)->fontImages[__NANO2D_CONTEXT(ctx)->fontImageIdx + 1], &iw, &ih);
//	//else { // calculate the new font image size and create it.
//	//	__NANO2D_API(ImageSize)(ctx, __NANO2D_CONTEXT(ctx)->fontImages[__NANO2D_CONTEXT(ctx)->fontImageIdx], &iw, &ih);
//	//	if (iw > ih)
//	//		ih *= 2;
//	//	else
//	//		iw *= 2;
//	//	if (iw > NVG_MAX_FONTIMAGE_SIZE || ih > NVG_MAX_FONTIMAGE_SIZE)
//	//		iw = ih = NVG_MAX_FONTIMAGE_SIZE;
//	//	__NANO2D_CONTEXT(ctx)->fontImages[__NANO2D_CONTEXT(ctx)->fontImageIdx + 1] = __NANO2D_CONTEXT(ctx)->params.renderCreateTexture(__NANO2D_CONTEXT(ctx)->params.userPtr, NVG_TEXTURE_ALPHA, iw, ih, 0, NULL);
//	//}
//	//++__NANO2D_CONTEXT(ctx)->fontImageIdx;
//	//fonsResetAtlas(__NANO2D_CONTEXT(ctx)->fs, iw, ih);
//	throw_todo();
//	return 1;
//}
//
//static void __NANO2D_API(__renderText)(NANO2D_CONTEXT * ctx, NVGvertex * verts, int nverts)
//{
//	//NVGstate * state = __NANO2D_API(__getState)(ctx);
//	//NANO2D_PAINT paint = state->fill;
//
//	//// Render triangles.
//	//paint.image = __NANO2D_CONTEXT(ctx)->fontImages[__NANO2D_CONTEXT(ctx)->fontImageIdx];
//
//	//// Apply global alpha
//	//paint.innerColor.a *= state->alpha;
//	//paint.outerColor.a *= state->alpha;
//
//	//__NANO2D_CONTEXT(ctx)->params.renderTriangles(__NANO2D_CONTEXT(ctx)->params.userPtr, &paint, state->compositeOperation, &state->scissor, verts, nverts, __NANO2D_CONTEXT(ctx)->fringeWidth);
//
//	//__NANO2D_CONTEXT(ctx)->drawCallCount++;
//	//__NANO2D_CONTEXT(ctx)->textTriCount += nverts / 3;
//	throw_todo();
//}
//
//static int __NANO2D_API(__isTransformFlipped)(const float * xform)
//{
//	/*float det = xform[0] * xform[3] - xform[2] * xform[1];
//	return(det < 0);*/
//	throw_todo();
//	return -1;
//}
//
float __NANO2D_API(Text)(NANO2D_CONTEXT * ctx, float x, float y, const char * string, const char * end)
{

	//NVGstate * state = __NANO2D_API(__getState)(ctx);
	//FONStextIter iter, prevIter;
	//FONSquad q;
	//NVGvertex * verts;
	//float scale = __NANO2D_API(__getFontScale)(state) * __NANO2D_CONTEXT(ctx)->devicePxRatio;
	//float invscale = 1.0f / scale;
	//int cverts = 0;
	//int nverts = 0;
	//int isFlipped = __NANO2D_API(__isTransformFlipped)(state->xform);

	//if (end == NULL)
	//	end = string + strlen(string);

	//if (state->fontId == FONS_INVALID) return x;

	//fonsSetSize(__NANO2D_CONTEXT(ctx)->fs, state->fontSize * scale);
	//fonsSetSpacing(__NANO2D_CONTEXT(ctx)->fs, state->letterSpacing * scale);
	//fonsSetBlur(__NANO2D_CONTEXT(ctx)->fs, state->fontBlur * scale);
	//fonsSetAlign(__NANO2D_CONTEXT(ctx)->fs, state->textAlign);
	//fonsSetFont(__NANO2D_CONTEXT(ctx)->fs, state->fontId);

	//cverts = __NANO2D_API(__maxi)(2, (int)(end - string)) * 6; // conservative estimate.
	//verts = __NANO2D_API(__allocTempVerts)(ctx, cverts);
	//if (verts == NULL) return x;

	//fonsTextIterInit(__NANO2D_CONTEXT(ctx)->fs, &iter, x * scale, y * scale, string, end, FONS_GLYPH_BITMAP_REQUIRED);
	//prevIter = iter;
	//while (fonsTextIterNext(__NANO2D_CONTEXT(ctx)->fs, &iter, &q)) {
	//	float c[4 * 2];
	//	if (iter.prevGlyphIndex == -1) { // can not retrieve glyph?
	//		if (nverts != 0) {
	//			__NANO2D_API(__renderText)(ctx, verts, nverts);
	//			nverts = 0;
	//		}
	//		if (!__NANO2D_API(__allocTextAtlas)(ctx))
	//			break; // no memory :(
	//		iter = prevIter;
	//		fonsTextIterNext(__NANO2D_CONTEXT(ctx)->fs, &iter, &q); // try again
	//		if (iter.prevGlyphIndex == -1) // still can not find glyph?
	//			break;
	//	}
	//	prevIter = iter;
	//	if (isFlipped) {
	//		float tmp;

	//		tmp = q.y0; q.y0 = q.y1; q.y1 = tmp;
	//		tmp = q.t0; q.t0 = q.t1; q.t1 = tmp;
	//	}
	//	// Transform corners.
	//	__NANO2D_API(TransformPoint)(&c[0], &c[1], state->xform, q.x0 * invscale, q.y0 * invscale);
	//	__NANO2D_API(TransformPoint)(&c[2], &c[3], state->xform, q.x1 * invscale, q.y0 * invscale);
	//	__NANO2D_API(TransformPoint)(&c[4], &c[5], state->xform, q.x1 * invscale, q.y1 * invscale);
	//	__NANO2D_API(TransformPoint)(&c[6], &c[7], state->xform, q.x0 * invscale, q.y1 * invscale);
	//	// Create triangles
	//	if (nverts + 6 <= cverts) {
	//		__NANO2D_API(__vset)(&verts[nverts], c[0], c[1], q.s0, q.t0); nverts++;
	//		__NANO2D_API(__vset)(&verts[nverts], c[4], c[5], q.s1, q.t1); nverts++;
	//		__NANO2D_API(__vset)(&verts[nverts], c[2], c[3], q.s1, q.t0); nverts++;
	//		__NANO2D_API(__vset)(&verts[nverts], c[0], c[1], q.s0, q.t0); nverts++;
	//		__NANO2D_API(__vset)(&verts[nverts], c[6], c[7], q.s0, q.t1); nverts++;
	//		__NANO2D_API(__vset)(&verts[nverts], c[4], c[5], q.s1, q.t1); nverts++;
	//	}
	//}

	//// TODO: add back-end bit to do this just once per frame.
	//__NANO2D_API(__flushTextTexture)(ctx);

	//__NANO2D_API(__renderText)(ctx, verts, nverts);

	//return iter.nextx / scale;

	return __NANO2D_CONTEXT(ctx)->text(x, y, string, end);


}

void __NANO2D_API(TextBox)(NANO2D_CONTEXT * ctx, float x, float y, float breakRowWidth, const char * string, const char * end)
{

	__NANO2D_CONTEXT(ctx)->text(x, y, string, end);
	// throw_todo();
	//NVGstate * state = __NANO2D_API(__getState)(ctx);
	//NVGtextRow rows[2];
	//int nrows = 0, i;
	//int oldAlign = state->textAlign;
	//int haling = state->textAlign & (NVG_ALIGN_LEFT | NVG_ALIGN_CENTER | NVG_ALIGN_RIGHT);
	//int valign = state->textAlign & (NVG_ALIGN_TOP | NVG_ALIGN_MIDDLE | NVG_ALIGN_BOTTOM | NVG_ALIGN_BASELINE);
	//float lineh = 0;

	//if (state->fontId == FONS_INVALID) return;

	//__NANO2D_API(TextMetrics)(ctx, NULL, NULL, &lineh);

	//state->textAlign = NVG_ALIGN_LEFT | valign;

	//while ((nrows = __NANO2D_API(TextBreakLines)(ctx, string, end, breakRowWidth, rows, 2))) {
	//	for (i = 0; i < nrows; i++) {
	//		NVGtextRow * row = &rows[i];
	//		if (haling & NVG_ALIGN_LEFT)
	//			__NANO2D_API(Text)(ctx, x, y, row->start, row->end);
	//		else if (haling & NVG_ALIGN_CENTER)
	//			__NANO2D_API(Text)(ctx, x + breakRowWidth * 0.5f - row->width * 0.5f, y, row->start, row->end);
	//		else if (haling & NVG_ALIGN_RIGHT)
	//			__NANO2D_API(Text)(ctx, x + breakRowWidth - row->width, y, row->start, row->end);
	//		y += lineh * state->lineHeight;
	//	}
	//	string = rows[nrows - 1].next;
	//}

	//state->textAlign = oldAlign;
}

int __NANO2D_API(TextGlyphPositions)(NANO2D_CONTEXT * ctx, float x, float y, const char * string, const char * end, NVGglyphPosition * positions, int maxPositions)
{

	return __NANO2D_CONTEXT(ctx)->text_glyph_positions(x, y, string, end, positions, maxPositions);

	//throw_todo();
	//return -1;
	//NVGstate * state = __NANO2D_API(__getState)(ctx);
	//float scale = __NANO2D_API(__getFontScale)(state) * __NANO2D_CONTEXT(ctx)->devicePxRatio;
	//float invscale = 1.0f / scale;
	//FONStextIter iter, prevIter;
	//FONSquad q;
	//int npos = 0;

	//if (state->fontId == FONS_INVALID) return 0;

	//if (end == NULL)
	//	end = string + strlen(string);

	//if (string == end)
	//	return 0;

	//fonsSetSize(__NANO2D_CONTEXT(ctx)->fs, state->fontSize * scale);
	//fonsSetSpacing(__NANO2D_CONTEXT(ctx)->fs, state->letterSpacing * scale);
	//fonsSetBlur(__NANO2D_CONTEXT(ctx)->fs, state->fontBlur * scale);
	//fonsSetAlign(__NANO2D_CONTEXT(ctx)->fs, state->textAlign);
	//fonsSetFont(__NANO2D_CONTEXT(ctx)->fs, state->fontId);

	//fonsTextIterInit(__NANO2D_CONTEXT(ctx)->fs, &iter, x * scale, y * scale, string, end, FONS_GLYPH_BITMAP_OPTIONAL);
	//prevIter = iter;
	//while (fonsTextIterNext(__NANO2D_CONTEXT(ctx)->fs, &iter, &q)) {
	//	if (iter.prevGlyphIndex < 0 && __NANO2D_API(__allocTextAtlas)(ctx)) { // can not retrieve glyph?
	//		iter = prevIter;
	//		fonsTextIterNext(__NANO2D_CONTEXT(ctx)->fs, &iter, &q); // try again
	//	}
	//	prevIter = iter;
	//	positions[npos].str = iter.str;
	//	positions[npos].x = iter.x * invscale;
	//	positions[npos].minx = __NANO2D_API(__minf)(iter.x, q.x0) * invscale;
	//	positions[npos].maxx = __NANO2D_API(__maxf)(iter.nextx, q.x1) * invscale;
	//	npos++;
	//	if (npos >= maxPositions)
	//		break;
	//}

	//return npos;
}

enum NVGcodepointType {
	NVG_SPACE,
	NVG_NEWLINE,
	NVG_CHAR,
	NVG_CJK_CHAR,
};

int __NANO2D_API(TextBreakLines)(NANO2D_CONTEXT * ctx, const char * string, const char * end, float breakRowWidth, NVGtextRow * rows, int maxRows)
{
	throw_todo();
	return -1;
	//NVGstate * state = __NANO2D_API(__getState)(ctx);
	//float scale = __NANO2D_API(__getFontScale)(state) * __NANO2D_CONTEXT(ctx)->devicePxRatio;
	//float invscale = 1.0f / scale;
	//FONStextIter iter, prevIter;
	//FONSquad q;
	//int nrows = 0;
	//float rowStartX = 0;
	//float rowWidth = 0;
	//float rowMinX = 0;
	//float rowMaxX = 0;
	//const char * rowStart = NULL;
	//const char * rowEnd = NULL;
	//const char * wordStart = NULL;
	//float wordStartX = 0;
	//float wordMinX = 0;
	//const char * breakEnd = NULL;
	//float breakWidth = 0;
	//float breakMaxX = 0;
	//int type = NVG_SPACE, ptype = NVG_SPACE;
	//unsigned int pcodepoint = 0;

	//if (maxRows == 0) return 0;
	//if (state->fontId == FONS_INVALID) return 0;

	//if (end == NULL)
	//	end = string + strlen(string);

	//if (string == end) return 0;

	//fonsSetSize(__NANO2D_CONTEXT(ctx)->fs, state->fontSize * scale);
	//fonsSetSpacing(__NANO2D_CONTEXT(ctx)->fs, state->letterSpacing * scale);
	//fonsSetBlur(__NANO2D_CONTEXT(ctx)->fs, state->fontBlur * scale);
	//fonsSetAlign(__NANO2D_CONTEXT(ctx)->fs, state->textAlign);
	//fonsSetFont(__NANO2D_CONTEXT(ctx)->fs, state->fontId);

	//breakRowWidth *= scale;

	//fonsTextIterInit(__NANO2D_CONTEXT(ctx)->fs, &iter, 0, 0, string, end, FONS_GLYPH_BITMAP_OPTIONAL);
	//prevIter = iter;
	//while (fonsTextIterNext(__NANO2D_CONTEXT(ctx)->fs, &iter, &q)) {
	//	if (iter.prevGlyphIndex < 0 && __NANO2D_API(__allocTextAtlas)(ctx)) { // can not retrieve glyph?
	//		iter = prevIter;
	//		fonsTextIterNext(__NANO2D_CONTEXT(ctx)->fs, &iter, &q); // try again
	//	}
	//	prevIter = iter;
	//	switch (iter.codepoint) {
	//	case 9:			// \t
	//	case 11:		// \v
	//	case 12:		// \f
	//	case 32:		// space
	//	case 0x00a0:	// NBSP
	//		type = NVG_SPACE;
	//		break;
	//	case 10:		// \n
	//		type = pcodepoint == 13 ? NVG_SPACE : NVG_NEWLINE;
	//		break;
	//	case 13:		// \r
	//		type = pcodepoint == 10 ? NVG_SPACE : NVG_NEWLINE;
	//		break;
	//	case 0x0085:	// NEL
	//		type = NVG_NEWLINE;
	//		break;
	//	default:
	//		if ((iter.codepoint >= 0x4E00 && iter.codepoint <= 0x9FFF) ||
	//			(iter.codepoint >= 0x3000 && iter.codepoint <= 0x30FF) ||
	//			(iter.codepoint >= 0xFF00 && iter.codepoint <= 0xFFEF) ||
	//			(iter.codepoint >= 0x1100 && iter.codepoint <= 0x11FF) ||
	//			(iter.codepoint >= 0x3130 && iter.codepoint <= 0x318F) ||
	//			(iter.codepoint >= 0xAC00 && iter.codepoint <= 0xD7AF))
	//			type = NVG_CJK_CHAR;
	//		else
	//			type = NVG_CHAR;
	//		break;
	//	}

	//	if (type == NVG_NEWLINE) {
	//		// Always handle new lines.
	//		rows[nrows].start = rowStart != NULL ? rowStart : iter.str;
	//		rows[nrows].end = rowEnd != NULL ? rowEnd : iter.str;
	//		rows[nrows].width = rowWidth * invscale;
	//		rows[nrows].minx = rowMinX * invscale;
	//		rows[nrows].maxx = rowMaxX * invscale;
	//		rows[nrows].next = iter.next;
	//		nrows++;
	//		if (nrows >= maxRows)
	//			return nrows;
	//		// Set null break point
	//		breakEnd = rowStart;
	//		breakWidth = 0.0;
	//		breakMaxX = 0.0;
	//		// Indicate to skip the white space at the beginning of the row.
	//		rowStart = NULL;
	//		rowEnd = NULL;
	//		rowWidth = 0;
	//		rowMinX = rowMaxX = 0;
	//	}
	//	else {
	//		if (rowStart == NULL) {
	//			// Skip white space until the beginning of the line
	//			if (type == NVG_CHAR || type == NVG_CJK_CHAR) {
	//				// The current char is the row so far
	//				rowStartX = iter.x;
	//				rowStart = iter.str;
	//				rowEnd = iter.next;
	//				rowWidth = iter.nextx - rowStartX;
	//				rowMinX = q.x0 - rowStartX;
	//				rowMaxX = q.x1 - rowStartX;
	//				wordStart = iter.str;
	//				wordStartX = iter.x;
	//				wordMinX = q.x0 - rowStartX;
	//				// Set null break point
	//				breakEnd = rowStart;
	//				breakWidth = 0.0;
	//				breakMaxX = 0.0;
	//			}
	//		}
	//		else {
	//			float nextWidth = iter.nextx - rowStartX;

	//			// track last non-white space character
	//			if (type == NVG_CHAR || type == NVG_CJK_CHAR) {
	//				rowEnd = iter.next;
	//				rowWidth = iter.nextx - rowStartX;
	//				rowMaxX = q.x1 - rowStartX;
	//			}
	//			// track last end of a word
	//			if (((ptype == NVG_CHAR || ptype == NVG_CJK_CHAR) && type == NVG_SPACE) || type == NVG_CJK_CHAR) {
	//				breakEnd = iter.str;
	//				breakWidth = rowWidth;
	//				breakMaxX = rowMaxX;
	//			}
	//			// track last beginning of a word
	//			if ((ptype == NVG_SPACE && (type == NVG_CHAR || type == NVG_CJK_CHAR)) || type == NVG_CJK_CHAR) {
	//				wordStart = iter.str;
	//				wordStartX = iter.x;
	//				wordMinX = q.x0;
	//			}

	//			// Break to new line when a character is beyond break width.
	//			if ((type == NVG_CHAR || type == NVG_CJK_CHAR) && nextWidth > breakRowWidth) {
	//				// The run length is too long, need to break to new line.
	//				if (breakEnd == rowStart) {
	//					// The current word is longer than the row length, just break it from here.
	//					rows[nrows].start = rowStart;
	//					rows[nrows].end = iter.str;
	//					rows[nrows].width = rowWidth * invscale;
	//					rows[nrows].minx = rowMinX * invscale;
	//					rows[nrows].maxx = rowMaxX * invscale;
	//					rows[nrows].next = iter.str;
	//					nrows++;
	//					if (nrows >= maxRows)
	//						return nrows;
	//					rowStartX = iter.x;
	//					rowStart = iter.str;
	//					rowEnd = iter.next;
	//					rowWidth = iter.nextx - rowStartX;
	//					rowMinX = q.x0 - rowStartX;
	//					rowMaxX = q.x1 - rowStartX;
	//					wordStart = iter.str;
	//					wordStartX = iter.x;
	//					wordMinX = q.x0 - rowStartX;
	//				}
	//				else {
	//					// Break the line from the end of the last word, and start new line from the beginning of the new.
	//					rows[nrows].start = rowStart;
	//					rows[nrows].end = breakEnd;
	//					rows[nrows].width = breakWidth * invscale;
	//					rows[nrows].minx = rowMinX * invscale;
	//					rows[nrows].maxx = breakMaxX * invscale;
	//					rows[nrows].next = wordStart;
	//					nrows++;
	//					if (nrows >= maxRows)
	//						return nrows;
	//					// Update row
	//					rowStartX = wordStartX;
	//					rowStart = wordStart;
	//					rowEnd = iter.next;
	//					rowWidth = iter.nextx - rowStartX;
	//					rowMinX = wordMinX - rowStartX;
	//					rowMaxX = q.x1 - rowStartX;
	//				}
	//				// Set null break point
	//				breakEnd = rowStart;
	//				breakWidth = 0.0;
	//				breakMaxX = 0.0;
	//			}
	//		}
	//	}

	//	pcodepoint = iter.codepoint;
	//	ptype = type;
	//}

	//// Break the line from the end of the last word, and start new line from the beginning of the new.
	//if (rowStart != NULL) {
	//	rows[nrows].start = rowStart;
	//	rows[nrows].end = rowEnd;
	//	rows[nrows].width = rowWidth * invscale;
	//	rows[nrows].minx = rowMinX * invscale;
	//	rows[nrows].maxx = rowMaxX * invscale;
	//	rows[nrows].next = end;
	//	nrows++;
	//}

	//return nrows;
}

float __NANO2D_API(TextBounds)(NANO2D_CONTEXT * ctx, float x, float y, const char * string, const char * end, float * bounds)
{

	return __NANO2D_CONTEXT(ctx)->text_bounds(x, y, string, end, bounds);
	//NVGstate * state = __NANO2D_API(__getState)(ctx);
	//float scale = __NANO2D_API(__getFontScale)(state) * __NANO2D_CONTEXT(ctx)->devicePxRatio;
	//float invscale = 1.0f / scale;
	//float width;

	//if (state->fontId == FONS_INVALID) return 0;

	//fonsSetSize(__NANO2D_CONTEXT(ctx)->fs, state->fontSize * scale);
	//fonsSetSpacing(__NANO2D_CONTEXT(ctx)->fs, state->letterSpacing * scale);
	//fonsSetBlur(__NANO2D_CONTEXT(ctx)->fs, state->fontBlur * scale);
	//fonsSetAlign(__NANO2D_CONTEXT(ctx)->fs, state->textAlign);
	//fonsSetFont(__NANO2D_CONTEXT(ctx)->fs, state->fontId);

	//width = fonsTextBounds(__NANO2D_CONTEXT(ctx)->fs, x * scale, y * scale, string, end, bounds);
	//if (bounds != NULL) {
	//	// Use line bounds for height.
	//	fonsLineBounds(__NANO2D_CONTEXT(ctx)->fs, y * scale, &bounds[1], &bounds[3]);
	//	bounds[0] *= invscale;
	//	bounds[1] *= invscale;
	//	bounds[2] *= invscale;
	//	bounds[3] *= invscale;
	//}
	//return width * invscale;
}

void __NANO2D_API(TextBoxBounds)(NANO2D_CONTEXT * ctx, float x, float y, float breakRowWidth, const char * string, const char * end, float * bounds)
{

	__NANO2D_CONTEXT(ctx)->text_bounds(x, y, string, end, bounds);

//
//	//NVGstate * state = __NANO2D_API(__getState)(ctx);
//	NVGtextRow rows[2];
//	float scale = __NANO2D_API(__getFontScale)(state) * __NANO2D_CONTEXT(ctx)->devicePxRatio;
//	float invscale = 1.0f / scale;
//	int nrows = 0, i;
//	int oldAlign = state->textAlign;
//	int haling = state->textAlign & (NVG_ALIGN_LEFT | NVG_ALIGN_CENTER | NVG_ALIGN_RIGHT);
//	int valign = state->textAlign & (NVG_ALIGN_TOP | NVG_ALIGN_MIDDLE | NVG_ALIGN_BOTTOM | NVG_ALIGN_BASELINE);
//	float lineh = 0, rminy = 0, rmaxy = 0;
//	float minx, miny, maxx, maxy;
//
//	if (state->fontId == FONS_INVALID) {
//		if (bounds != NULL)
//			bounds[0] = bounds[1] = bounds[2] = bounds[3] = 0.0f;
//		return;
//	}
//
//	__NANO2D_API(TextMetrics)(ctx, NULL, NULL, &lineh);
//
//	state->textAlign = NVG_ALIGN_LEFT | valign;
//
//	minx = maxx = x;
//	miny = maxy = y;
//
//	fonsSetSize(__NANO2D_CONTEXT(ctx)->fs, state->fontSize * scale);
//	fonsSetSpacing(__NANO2D_CONTEXT(ctx)->fs, state->letterSpacing * scale);
//	fonsSetBlur(__NANO2D_CONTEXT(ctx)->fs, state->fontBlur * scale);
//	fonsSetAlign(__NANO2D_CONTEXT(ctx)->fs, state->textAlign);
//	fonsSetFont(__NANO2D_CONTEXT(ctx)->fs, state->fontId);
//	fonsLineBounds(__NANO2D_CONTEXT(ctx)->fs, 0, &rminy, &rmaxy);
//	rminy *= invscale;
//	rmaxy *= invscale;
//
//	while ((nrows = __NANO2D_API(TextBreakLines)(ctx, string, end, breakRowWidth, rows, 2))) {
//		for (i = 0; i < nrows; i++) {
//			NVGtextRow * row = &rows[i];
//			float rminx, rmaxx, dx = 0;
//			// Horizontal bounds
//			if (haling & NVG_ALIGN_LEFT)
//				dx = 0;
//			else if (haling & NVG_ALIGN_CENTER)
//				dx = breakRowWidth * 0.5f - row->width * 0.5f;
//			else if (haling & NVG_ALIGN_RIGHT)
//				dx = breakRowWidth - row->width;
//			rminx = x + row->minx + dx;
//			rmaxx = x + row->maxx + dx;
//			minx = __NANO2D_API(__minf)(minx, rminx);
//			maxx = __NANO2D_API(__maxf)(maxx, rmaxx);
//			// Vertical bounds.
//			miny = __NANO2D_API(__minf)(miny, y + rminy);
//			maxy = __NANO2D_API(__maxf)(maxy, y + rmaxy);
//
//			y += lineh * state->lineHeight;
//		}
//		string = rows[nrows - 1].next;
//	}
//
//	state->textAlign = oldAlign;
//
//	if (bounds != NULL) {
//		bounds[0] = minx;
//		bounds[1] = miny;
//		bounds[2] = maxx;
//		bounds[3] = maxy;
//	}
////	throw_todo();
}

void __NANO2D_API(TextMetrics)(NANO2D_CONTEXT * ctx, float * ascender, float * descender, float * lineh)
{
	//NVGstate * state = __NANO2D_API(__getState)(ctx);
	//float scale = __NANO2D_API(__getFontScale)(state) * __NANO2D_CONTEXT(ctx)->devicePxRatio;
	//float invscale = 1.0f / scale;

	//if (state->fontId == FONS_INVALID) return;

	//fonsSetSize(__NANO2D_CONTEXT(ctx)->fs, state->fontSize * scale);
	//fonsSetSpacing(__NANO2D_CONTEXT(ctx)->fs, state->letterSpacing * scale);
	//fonsSetBlur(__NANO2D_CONTEXT(ctx)->fs, state->fontBlur * scale);
	//fonsSetAlign(__NANO2D_CONTEXT(ctx)->fs, state->textAlign);
	//fonsSetFont(__NANO2D_CONTEXT(ctx)->fs, state->fontId);

	//fonsVertMetrics(__NANO2D_CONTEXT(ctx)->fs, ascender, descender, lineh);
	//if (ascender != NULL)
	//	*ascender *= invscale;
	//if (descender != NULL)
	//	*descender *= invscale;
	//if (lineh != NULL)
	//	*lineh *= invscale;
}

// vim: ft=c nu noet ts=4



