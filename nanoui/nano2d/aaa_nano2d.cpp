//
// Copyright (c) 2013 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no happening will the authors be held liable for any damages
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
#include "acme/exception/not_implemented.h"
#include "nano2d/draw2d_context.h"
//#include "aura/graphics/draw2d/_component.h"

//#include <stdlib.h>
//#include <stdio.h>
//#include <math.h>
//#include <memory.h>

#include NANO2D_INCLUDE
#include "context.h"

#define __NANO2D_CONTEXT(ctx) ((::nano2d::context  *) (ctx)->p)


namespace nano2d
{


	::object * get_nano2d_object(::nano2d::context  * pcontext)
	{

		auto pnano2dcontext = ((::nano2d::context  *)(pcontext)->p);

		::pointer < ::nano2d::draw2d_context > pdraw2dcontext = pnano2dcontext;

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
	//#define NANO2D_KAPPA90 0.5522847493f	// Length proportional to radius of a cubic bezier handle for 90deg arcs.
	//
	//#define NANO2D_COUNTOF(arr) (sizeof(arr) / sizeof(0[arr]))

	//
	//enum NVGcommands {
	//	::nano2d::e_command_move_to = 0,
	//	::nano2d::e_command_line_to = 1,
	//	::nano2d::e_command_bezier_to = 2,
	//	::nano2d::e_command_close = 3,
	//	::nano2d::e_command_winding = 4,
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
	//struct ::nano2d::state {
	//	NVGcompositeOperationState compositeOperation;
	//	int shapeAntiAlias;
	//	::nano2d::paint fill;
	//	::nano2d::paint stroke;
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
	//typedef struct ::nano2d::state ::nano2d::state;
	//
	//struct NVGpoint {
	//	float x, y;
	//	float Δx, Δy;
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
	//	::nano2d::path * paths;
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
	//	::nano2d::state states[NVG_MAX_STATES];
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

	static float __sqrtf(float a) { return sqrtf(a); }
	//static float __modf(float a, float b) { return fmodf(a, b); }
	static float __sinf(float a) { return sinf(a); }
	static float __cosf(float a) { return cosf(a); }
	static float __tanf(float a) { return tanf(a); }
	static float __atan2f(float a, float b) { return atan2f(a, b); }
	static float __acosf(float a) { return acosf(a); }

	//static int __mini(int a, int b) { return a < b ? a : b; }
	//static int __maxi(int a, int b) { return a > b ? a : b; }
	//static int __clampi(int a, int mn, int mx) { return a < mn ? mn : (a > mx ? mx : a); }
	static float __minf(float a, float b) { return a < b ? a : b; }
	static float __maxf(float a, float b) { return a > b ? a : b; }
	static float __absf(float a) { return a >= 0.0f ? a : -a; }
	static float __signf(float a) { return a >= 0.0f ? 1.0f : -1.0f; }
	//static float __clampf(float a, float mn, float mx) { return a < mn ? mn : (a > mx ? mx : a); }
	static float __cross(float dx0, float dy0, float dx1, float dy1) { return dx1 * dy0 - dx0 * dy1; }

	static float __normalize(float * x, float * y)
	{
		float d = __sqrtf((*x) * (*x) + (*y) * (*y));
		if (d > 1e-6f) {
			float id = 1.0f / d;
			*x *= id;
			*y *= id;
		}
		return d;
	}


	//static void CONTEXT::__deletePathCache)(NVGpathCache * c)
	//{
	//	if (c == NULL) return;
	//	if (c->points != NULL) free(c->points);
	//	if (c->paths != NULL) free(c->paths);
	//	if (c->verts != NULL) free(c->verts);
	//	free(c);
	//}

	//static NVGpathCache * CONTEXT::__allocPathCache)(void)
	//{
	//	NVGpathCache * c = (NVGpathCache *)malloc(sizeof(NVGpathCache));
	//	if (c == NULL) goto error;
	//	::memory_set(c, 0, sizeof(NVGpathCache));
	//
	//	c->points = (NVGpoint *)malloc(sizeof(NVGpoint) * NVG_INIT_POINTS_SIZE);
	//	if (!c->points) goto error;
	//	c->npoints = 0;
	//	c->cpoints = NVG_INIT_POINTS_SIZE;
	//
	//	c->paths = (::nano2d::path *)malloc(sizeof(::nano2d::path) * NVG_INIT_PATHS_SIZE);
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
	//	CONTEXT::__deletePathCache)(c);
	//	return NULL;
	//}

	//static void CONTEXT::__setDevicePixelRatio(float ratio)
	//{
	//	tessTol = 0.25f / ratio;
	//	distTol = 0.01f / ratio;
	//	fringeWidth = 1.0f / ratio;
	//	devicePxRatio = ratio;
	//}

	static ::nano2d::compositeOperationState __compositeOperationState(int op)
	{
		int sfactor, dfactor;

		if (op == ::nano2d::e_composite_operation_source_over)
		{
			sfactor = ::nano2d::e_blend_factor_zero;
			dfactor = ::nano2d::e_blend_factor_one_minus_src_alpha;
		}
		else if (op == ::nano2d::e_composite_operation_source_in)
		{
			sfactor = ::nano2d::e_blend_factor_dst_alpha;
			dfactor = ::nano2d::e_blend_factor_zero;
		}
		else if (op == ::nano2d::e_composite_operation_source_out)
		{
			sfactor = ::nano2d::e_blend_factor_one_minus_dst_alpha;
			dfactor = ::nano2d::e_blend_factor_zero;
		}
		else if (op == ::nano2d::e_composite_operation_atop)
		{
			sfactor = ::nano2d::e_blend_factor_dst_alpha;
			dfactor = ::nano2d::e_blend_factor_one_minus_src_alpha;
		}
		else if (op == ::nano2d::e_composite_operation_destination_over)
		{
			sfactor = ::nano2d::e_blend_factor_one_minus_dst_alpha;
			dfactor = ::nano2d::e_blend_factor_one;
		}
		else if (op == ::nano2d::e_composite_operation_destination_in)
		{
			sfactor = ::nano2d::e_blend_factor_zero;
			dfactor = ::nano2d::e_blend_factor_src_alpha;
		}
		else if (op == ::nano2d::e_composite_operation_destination_out)
		{
			sfactor = ::nano2d::e_blend_factor_zero;
			dfactor = ::nano2d::e_blend_factor_one_minus_src_alpha;
		}
		else if (op == ::nano2d::e_composite_operation_destination_atop)
		{
			sfactor = ::nano2d::e_blend_factor_one_minus_dst_alpha;
			dfactor = ::nano2d::e_blend_factor_src_alpha;
		}
		else if (op == ::nano2d::e_composite_operation_lighter)
		{
			sfactor = ::nano2d::e_blend_factor_one;
			dfactor = ::nano2d::e_blend_factor_one;
		}
		else if (op == ::nano2d::e_composite_operation_copy)
		{
			sfactor = ::nano2d::e_blend_factor_one;
			dfactor = ::nano2d::e_blend_factor_zero;
		}
		else if (op == ::nano2d::e_composite_operation_xor)
		{
			sfactor = ::nano2d::e_blend_factor_one_minus_dst_alpha;
			dfactor = ::nano2d::e_blend_factor_one_minus_src_alpha;
		}
		else
		{
			sfactor = ::nano2d::e_blend_factor_one;
			dfactor = ::nano2d::e_blend_factor_zero;
		}

		::nano2d::compositeOperationState state;
		state.srcRGB = sfactor;
		state.dstRGB = dfactor;
		state.srcAlpha = sfactor;
		state.dstAlpha = dfactor;
		return state;
	}

	
	::nano2d::state * CONTEXT::__getState()
	{

		return &this->states[this->nstates - 1];

		//return &states[nstates - 1];
		//throw not_implemented();
		//return nullptr;

	}

	//NANO2D_CONTEXT * CONTEXT::CreateInternal)(NVGparams * params)
	//{
	//	FONSparams fontParams;
	//	NANO2D_CONTEXT * ctx = (NANO2D_CONTEXT *)malloc(sizeof(NANO2D_CONTEXT));
	//	int i;
	//	if (ctx == NULL) goto error;
	//	::memory_set(ctx, 0, sizeof(NANO2D_CONTEXT));
	//
	//	params = *params;
	//	for (i = 0; i < NVG_MAX_FONTIMAGES; i++)
	//		fontImages[i] = 0;
	//
	//	commands = (float *)malloc(sizeof(float) * NVG_INIT_COMMANDS_SIZE);
	//	if (!commands) goto error;
	//	ncommands = 0;
	//	ccommands = NVG_INIT_COMMANDS_SIZE;
	//
	//	cache = CONTEXT::__allocPathCache)();
	//	if (cache == NULL) goto error;
	//
	//	CONTEXT::Save)(ctx);
	//	CONTEXT::Reset)(ctx);
	//
	//	CONTEXT::__setDevicePixelRatio)(ctx, 1.0f);
	//
	//	if (params.renderCreate(params.userPtr) == 0) goto error;
	//
	//	// Init font rendering
	//	::memory_set(&fontParams, 0, sizeof(fontParams));
	//	fontParams.width = NVG_INIT_FONTIMAGE_SIZE;
	//	fontParams.height = NVG_INIT_FONTIMAGE_SIZE;
	//	fontParams.flags = FONS_ZERO_TOPLEFT;
	//	fontParams.renderCreate = NULL;
	//	fontParams.renderUpdate = NULL;
	//	fontParams.renderDraw = NULL;
	//	fontParams.renderDelete = NULL;
	//	fontParams.userPtr = NULL;
	//	fs = fonsCreateInternal(&fontParams);
	//	if (fs == NULL) goto error;
	//
	//	// Create font texture
	//	fontImages[0] = params.renderCreateTexture(params.userPtr, NVG_TEXTURE_ALPHA, fontParams.width, fontParams.height, 0, NULL);
	//	if (fontImages[0] == 0) goto error;
	//	fontImageIdx = 0;
	//
	//	return ctx;
	//
	//error:
	//	CONTEXT::DeleteInternal)(ctx);
	//	return 0;
	//}

	//NVGparams * CONTEXT::InternalParams()
	//{
	//	return &params;
	//}
	//
	//void CONTEXT::DeleteInternal()
	//{
	//	int i;
	//	if (ctx == NULL) return;
	//	if (commands != NULL) free(commands);
	//	if (cache != NULL) CONTEXT::__deletePathCache)(cache);
	//
	//	if (fs)
	//		fonsDeleteInternal(fs);
	//
	//	for (i = 0; i < NVG_MAX_FONTIMAGES; i++) {
	//		if (fontImages[i] != 0) {
	//			CONTEXT::DeleteImage)(ctx, fontImages[i]);
	//			fontImages[i] = 0;
	//		}
	//	}
	//
	//	if (params.renderDelete != NULL)
	//		params.renderDelete(params.userPtr);
	//
	//	free(ctx);
	//}
	//
	//void CONTEXT::BeginFrame(float windowWidth, float windowHeight, float devicePixelRatio)
	//{
	//	/*	printf("Tris: draws:%d  fill:%d  stroke:%d  text:%d  TOT:%d\n",
	//			drawCallCount, fillTriCount, strokeTriCount, textTriCount,
	//			fillTriCount+strokeTriCount+textTriCount);*/
	//
	//	nstates = 0;
	//	CONTEXT::Save)(ctx);
	//	CONTEXT::Reset)(ctx);
	//
	//	CONTEXT::__setDevicePixelRatio)(ctx, devicePixelRatio);
	//
	//	params.renderContext(params.userPtr, windowWidth, windowHeight, devicePixelRatio);
	//
	//	drawCallCount = 0;
	//	fillTriCount = 0;
	//	strokeTriCount = 0;
	//	textTriCount = 0;
	//}
	//
	//void CONTEXT::CancelFrame()
	//{
	//	params.renderCancel(params.userPtr);
	//}
	//
	//void CONTEXT::EndFrame()
	//{
	//	params.renderFlush(params.userPtr);
	//	if (fontImageIdx != 0) {
	//		int fontImage = fontImages[fontImageIdx];
	//		int i, j, iw, ih;
	//		// delete images that smaller than current one
	//		if (fontImage == 0)
	//			return;
	//		CONTEXT::ImageSize)(ctx, fontImage, &iw, &ih);
	//		for (i = j = 0; i < fontImageIdx; i++) {
	//			if (fontImages[i] != 0) {
	//				int nw, nh;
	//				CONTEXT::ImageSize)(ctx, fontImages[i], &nw, &nh);
	//				if (nw < iw || nh < ih)
	//					CONTEXT::DeleteImage)(ctx, fontImages[i]);
	//				else
	//					fontImages[j++] = fontImages[i];
	//			}
	//		}
	//		// make current font image to first
	//		fontImages[j++] = fontImages[0];
	//		fontImages[0] = fontImage;
	//		fontImageIdx = 0;
	//		// clear all images after j
	//		for (i = j; i < NVG_MAX_FONTIMAGES; i++)
	//			fontImages[i] = 0;
	//	}
	//}

	//::nano2d::color CONTEXT::RGB(unsigned char r, unsigned char g, unsigned char b)
::nano2d::color RGB(unsigned char r, unsigned char g, unsigned char b)
	{
		///return CONTEXT::RGBA)(r, g, b, 255);
		return { r / 255.f, g / 255.f, b / 255.f, 1.0f };
	}

	//::nano2d::color CONTEXT::RGBf)(float r, float g, float b)
::nano2d::color RGBf(float r, float g, float b)
	{
		//return CONTEXT::RGBAf)(r, g, b, 1.0f);
		return { r , g, b, 1.0f };
	}

	//::nano2d::color CONTEXT::RGBA)(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
::nano2d::color RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		::nano2d::color color;
		// Use longer initialization to suppress warning.
		color.r = r / 255.0f;
		color.g = g / 255.0f;
		color.b = b / 255.0f;
		color.a = a / 255.0f;
		return color;
	}

	//::nano2d::color CONTEXT::RGBAf)(float r, float g, float b, float a)
::nano2d::color RGBAf(float r, float g, float b, float a)
	{
		::nano2d::color color;
		// Use longer initialization to suppress warning.
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
		return color;
	}

	//::nano2d::color CONTEXT::TransRGBA)(::nano2d::color c, unsigned char a)
::nano2d::color TransRGBA(::nano2d::color c, unsigned char a)
	{
		c.a = a / 255.0f;
		return c;
	}

	//::nano2d::color CONTEXT::TransRGBAf)(::nano2d::color c, float a)
::nano2d::color TransRGBAf(::nano2d::color c, float a)
	{
		c.a = a;
		return c;
	}

	//::nano2d::color CONTEXT::LerpRGBA)(::nano2d::color c0, ::nano2d::color c1, float u)
	//{
	//	int i;
	//	float oneminu;
	//	::nano2d::color cint = { {{0}} };
	//
	//	u = CONTEXT::__clampf)(u, 0.0f, 1.0f);
	//	oneminu = 1.0f - u;
	//	for (i = 0; i < 4; i++)
	//	{
	//		cint.rgba[i] = c0.rgba[i] * oneminu + c1.rgba[i] * u;
	//	}
	//
	//	return cint;
	//}

	//::nano2d::color CONTEXT::HSL)(float h, float s, float l)
::nano2d::color HSL(float h, float s, float l)
	{
		//return CONTEXT::HSLA)(h, s, l, 255);
		::color::color color;

		color.set_hls(h, l, s);
		return { color.fr(), color.fg(), color.fb(), color.fa() };

	}

	//static float CONTEXT::__hue)(float h, float m1, float m2)
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

	//::nano2d::color CONTEXT::HSLA)(float h, float s, float l, unsigned char a)
::nano2d::color HSLA(float h, float s, float l, unsigned char a)
	{
		//float m1, m2;
		//::nano2d::color col;
		//h = CONTEXT::__modf)(h, 1.0f);
		//if (h < 0.0f) h += 1.0f;
		//s = CONTEXT::__clampf)(s, 0.0f, 1.0f);
		//l = CONTEXT::__clampf)(l, 0.0f, 1.0f);
		//m2 = l <= 0.5f ? (l * (1 + s)) : (l + s - l * s);
		//m1 = 2 * l - m2;
		//col.r = CONTEXT::__clampf)(CONTEXT::__hue)(h + 1.0f / 3.0f, m1, m2), 0.0f, 1.0f);
		//col.g = CONTEXT::__clampf)(CONTEXT::__hue)(h, m1, m2), 0.0f, 1.0f);
		//col.b = CONTEXT::__clampf)(CONTEXT::__hue)(h - 1.0f / 3.0f, m1, m2), 0.0f, 1.0f);
		::color::color color;

		color.set_hls(h, l, s);
		color.alpha = a;
		return { color.fr(), color.fg(), color.fb(), color.fa() };
	}

	//void CONTEXT::TransformIdentity)(float * t)
void TransformIdentity(float* t)
	{
		t[0] = 1.0f; t[1] = 0.0f;
		t[2] = 0.0f; t[3] = 1.0f;
		t[4] = 0.0f; t[5] = 0.0f;
	}

	//void CONTEXT::TransformTranslate)(float * t, float tx, float ty)
void TransformTranslate(float* t, float tx, float ty)
	{
		t[0] = 1.0f; t[1] = 0.0f;
		t[2] = 0.0f; t[3] = 1.0f;
		t[4] = tx; t[5] = ty;
	}

	//void CONTEXT::TransformScale)(float * t, float sx, float sy)
void TransformScale(float* t, float sx, float sy)
	{
		t[0] = sx; t[1] = 0.0f;
		t[2] = 0.0f; t[3] = sy;
		t[4] = 0.0f; t[5] = 0.0f;
	}

	//void CONTEXT::TransformRotate)(float * t, float a)
void TransformRotate(float* t, float a)
	{
		float cs = __cosf(a);
		float sn = __sinf(a);
		t[0] = cs; t[1] = sn;
		t[2] = -sn; t[3] = cs;
		t[4] = 0.0f; t[5] = 0.0f;
	}

	//void CONTEXT::TransformSkewX)(float * t, float a)
void TransformSkewX(float* t, float a)
	{
		t[0] = 1.0f; t[1] = 0.0f;
		t[2] = __tanf(a); t[3] = 1.0f;
		t[4] = 0.0f; t[5] = 0.0f;
	}

	void TransformSkewY(float * t, float a)
	{
		t[0] = 1.0f; t[1] = __tanf(a);
		t[2] = 0.0f; t[3] = 1.0f;
		t[4] = 0.0f; t[5] = 0.0f;
	}

	//void CONTEXT::TransformMultiply)(float * t, const float * s)
	void TransformMultiply(float* t, const float* s)
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

	//void CONTEXT::TransformPremultiply)(float * t, const float * s)
	void TransformPremultiply(float* t, const float* s)
	{
		float s2[6];
		::memory_copy(s2, s, sizeof(float) * 6);
		TransformMultiply(s2, t);
		::memory_copy(t, s2, sizeof(float) * 6);
	}

	//int CONTEXT::TransformInverse)(float * inv, const float * t)
		int TransformInverse(float* inv, const float* t)
	{
		double invdet, det = (double)t[0] * t[3] - (double)t[2] * t[1];
		if (det > -1e-6 && det < 1e-6) {
			TransformIdentity(inv);
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

	//void transform_point(float * Δx, float * Δy, const float * t, float sx, float sy)
		void transform_point(float* Δx, float* Δy, const float* t, float sx, float sy)
	{
		*Δx = sx * t[0] + sy * t[2] + t[4];
		*Δy = sx * t[1] + sy * t[3] + t[5];
	}

	//float CONTEXT::DegToRad)(float deg)
		float DegToRad(float deg)
	{
		return deg / 180.0f * ::nano2d::f_pi;
	}

	//float CONTEXT::RadToDeg)(float rad)
		float RadToDeg(float rad)
	{
		return rad / ::nano2d::f_pi * 180.0f;
	}

	//static void CONTEXT::__setPaintColor)(::nano2d::paint * p, ::nano2d::color color)
	void __setPaintColor(::nano2d::paint* p, ::nano2d::color color)
	{
		::memory_set(p, 0, sizeof(*p));
		TransformIdentity(p->xform);
		p->radius = 0.0f;
		p->feather = 1.0f;
		p->innerColor = color;
		p->outerColor = color;
	}


	// State handling
	void CONTEXT::save()
	{
		//if (nstates >= NVG_MAX_STATES)
		//	return;
		//if (nstates > 0)
		//	::memory_copy(&states[nstates], &states[nstates - 1], sizeof(::nano2d::state));
		//nstates++;

		//save();

	}

	
	void CONTEXT::restore()
	{
		
		//restore();
		//if (nstates <= 1)
		//	return;
		//nstates--;

	}


	void CONTEXT::reset()
	{

		::nano2d::state * state = __getState();

		::memory_set(state, 0, sizeof(*state));

		__setPaintColor(&state->fill, RGBA(255, 255, 255, 255));
		__setPaintColor(&state->stroke, RGBA(0, 0, 0, 255));
		state->compositeOperation = __compositeOperationState(::nano2d::e_composite_operation_source_over);
		state->shapeAntiAlias = 1;
		state->strokeWidth = 1.0f;
		state->miterLimit = 10.0f;
		state->lineCap = ::nano2d::e_line_cap_butt;
		state->lineJoin = ::nano2d::e_line_join_miter;
		state->alpha = 1.0f;
		TransformIdentity(state->xform);

		state->scissor.extent[0] = -1.0f;
		state->scissor.extent[1] = -1.0f;

		state->fontSize = 16.0f;
		state->letterSpacing = 0.0f;
		state->lineHeight = 1.0f;
		state->fontBlur = 0.0f;
		state->textAlign = ::nano2d::e_align_left | ::nano2d::e_align_baseline;
		state->fontId = 0;
	}

	// State setting
	void CONTEXT::shape_anti_alias(int enabled)
	{
		::nano2d::state * state = __getState();
		state->shapeAntiAlias = enabled;
	}

	void CONTEXT::stroke_width(float width)
	{
		//::nano2d::state * state = __getState();
		//state->strokeWidth = width;
		//return stroke_width(width);
	}


	void CONTEXT::miter_limit(float limit)
	{

		::nano2d::state * state = __getState();

		state->miterLimit = limit;

	}


	void CONTEXT::line_cap(int cap)
	{

		::nano2d::state * state = __getState();

		state->lineCap = cap;

	}


	void CONTEXT::line_join(int join)
	{

		::nano2d::state * state = __getState();

		state->lineJoin = join;

	}


	void CONTEXT::global_alpha(float alpha)
	{

		//::nano2d::state * state = __getState();
		//state->alpha = alpha;
		//global_alpha(alpha);

	}


	void CONTEXT::transform(float a, float b, float c, float d, float e, float f)
	{
		
		::nano2d::state * state = __getState();

		float t[6] = { a, b, c, d, e, f };

		TransformPremultiply(state->xform, t);

	}


	void CONTEXT::reset_transform()
	{

		::nano2d::state * state = __getState();

		TransformIdentity(state->xform);

	}


	void CONTEXT::translate(float x, float y)
	{
		//::nano2d::state * state = __getState();
		//float t[6];
		//CONTEXT::TransformTranslate)(t, x, y);
		//CONTEXT::TransformPremultiply)(state->xform, t);

		//translate(x, y);

	}

	
	void CONTEXT::rotate(float angle)
	{
		
		//::nano2d::state * state = __getState();
		//float t[6];
		//CONTEXT::TransformRotate)(t, angle);
		//CONTEXT::TransformPremultiply)(state->xform, t);
		//rotate(angle);

	}


	void CONTEXT::skew_x(float angle)
	{
		::nano2d::state * state = __getState();
		float t[6];
		TransformSkewX(t, angle);
		TransformPremultiply(state->xform, t);
	}

	void CONTEXT::skew_y(float angle)
	{
		::nano2d::state * state = __getState();
		float t[6];
		TransformSkewY(t, angle);
		TransformPremultiply(state->xform, t);
	}

	void CONTEXT::scale(float x, float y)
	{
		::nano2d::state * state = __getState();
		float t[6];
		TransformScale(t, x, y);
		TransformPremultiply(state->xform, t);
	}


	void CONTEXT::current_transform(float * xform)
	{
		::nano2d::state * state = __getState();
		if (xform == NULL) return;
		::memory_copy(xform, state->xform, sizeof(float) * 6);
	}

	void CONTEXT::stroke_color(::nano2d::color color)
	{
		//::nano2d::state * state = __getState();
		//CONTEXT::__setPaintColor)(&state->stroke, color);

		//stroke_color(color);

	}

	void CONTEXT::stroke_paint(::nano2d::paint paint)
	{
		//::nano2d::state * state = __getState();
		//state->stroke = paint;
		//CONTEXT::TransformMultiply)(state->stroke.xform, state->xform);

		//stroke_paint(paint);
	}

	void CONTEXT::fill_color(::nano2d::color color)
	{
		//::nano2d::state * state = __getState();
		//CONTEXT::__setPaintColor)(&state->fill, color);

		//fill_color(color);

	}

	void CONTEXT::fill_paint(::nano2d::paint paint)
	{
		//::nano2d::state * state = __getState();
		//state->fill = paint;
		//CONTEXT::TransformMultiply)(state->fill.xform, state->xform);

		//fill_paint(paint);

	}

	#ifndef NVG_NO_STB
	int CONTEXT::create_image(const ::scoped_string& scopedstrFilename, int imageFlags)
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
		//image = CONTEXT::CreateImageRGBA)(ctx, w, h, imageFlags, img);
		//stbi_image_free(img);
		//return image;
		//return create_image(filename, imageFlags);
		return -1;

	}


	int CONTEXT::create_image_mem(int imageFlags, unsigned char * data, int ndata)
	{
		//int w, h, n, image;
		//unsigned char * img = stbi_load_from_memory(data, ndata, &w, &h, &n, 4);
		//if (img == NULL) {
		//	//		printf("Failed to load %s - %s\n", filename, stbi_failure_reason());
		//	return 0;
		//}
		//image = CONTEXT::CreateImageRGBA)(ctx, w, h, imageFlags, img);
		//stbi_image_free(img);
		//return image;
		return -1;
	}
	#endif

	
	int CONTEXT::create_image_rgba(int w, int h, int imageFlags, const void * data, int iScan)
	{
		//return params.renderCreateTexture(params.userPtr, NVG_TEXTURE_RGBA, w, h, imageFlags, data);
		//return create_image_rgba(w, h, imageFlags, data, iScan);

		return -1;

	}


	void CONTEXT::update_image(int image, const void * data)
	{
		//int w h;
		//params.renderGetTextureSize(params.userPtr, image, &w, &h);
		//params.renderUpdateTexture(params.userPtr, image, 0, 0, w, h, data);
		//return update_image(image, data);

		//re

	}


	void CONTEXT::image_size(int image, int * w, int * h)
	{
		//params.renderGetTextureSize(params.userPtr, image, w, h);

		//image_size(image, w, h);

	}


	void CONTEXT::delete_image(int image)
	{
	
		//params.renderDeleteTexture(params.userPtr, image);

	}

	
	::nano2d::paint CONTEXT::linear_gradient(
		float sx, float sy, float ex, float ey,
		::nano2d::color icol, ::nano2d::color ocol)
	{

		//return linear_gradient(sx, sy, ex, ey, icol, ocol);
		//::nano2d::paint p;
		//float Δx, Δy, d;
		//const float large = 1e5;
		//NVG_NOTUSED(ctx);
		//::memory_set(&p, 0, sizeof(p));

		//// Calculate transform aligned to the line
		//Δx = ex - sx;
		//Δy = ey - sy;
		//d = sqrtf(Δx * Δx + Δy * Δy);
		//if (d > 0.0001f) {
		//	Δx /= d;
		//	Δy /= d;
		//}
		//else {
		//	Δx = 0;
		//	Δy = 1;
		//}

		//p.xform[0] = Δy; p.xform[1] = -Δx;
		//p.xform[2] = Δx; p.xform[3] = Δy;
		//p.xform[4] = sx - Δx * large; p.xform[5] = sy - Δy * large;

		//p.extent[0] = large;
		//p.extent[1] = large + d * 0.5f;

		//p.radius = 0.0f;

		//p.feather = CONTEXT::__maxf)(1.0f, d);

		//p.innerColor = icol;
		//p.outerColor = ocol;

		//return p;
	}


	::nano2d::paint CONTEXT::radial_gradient(
		float cx, float cy, float inr, float outr,
		::nano2d::color icol, ::nano2d::color ocol)
	{

		return {};


		//return radial_gradient(cx, cy, inr, outr, icol, ocol);
		//::nano2d::paint p;
		//float r = (inr + outr) * 0.5f;
		//float f = (outr - inr);
		//NVG_NOTUSED(ctx);
		//::memory_set(&p, 0, sizeof(p));

		//CONTEXT::TransformIdentity)(p.xform);
		//p.xform[4] = cx;
		//p.xform[5] = cy;

		//p.extent[0] = r;
		//p.extent[1] = r;

		//p.radius = r;

		//p.feather = CONTEXT::__maxf)(1.0f, f);

		//p.innerColor = icol;
		//p.outerColor = ocol;

		//return p;
	}

	
	::nano2d::paint CONTEXT::box_gradient(
		float x, float y, float w, float h, float r, float f,
		::nano2d::color icol, ::nano2d::color ocol)
	{

		return {};
		//return box_gradient(x, y, w, h, r, f, icol, ocol);
		//::nano2d::paint p;
		//NVG_NOTUSED(ctx);
		//::memory_set(&p, 0, sizeof(p));

		//CONTEXT::TransformIdentity)(p.xform);
		//p.xform[4] = x + w * 0.5f;
		//p.xform[5] = y + h * 0.5f;

		//p.extent[0] = w * 0.5f;
		//p.extent[1] = h * 0.5f;

		//p.radius = r;

		//p.feather = CONTEXT::__maxf)(1.0f, f);

		//p.innerColor = icol;
		//p.outerColor = ocol;

		//return p;
	}


	::nano2d::paint CONTEXT::image_pattern(float cx, float cy, float w, float h, float angle,
		int image, float alpha)
	{

		return {};

		//return image_pattern(cx, cy, w, h, angle, image, alpha);
		//::nano2d::paint p;
		//NVG_NOTUSED(ctx);
		//::memory_set(&p, 0, sizeof(p));

		//CONTEXT::TransformRotate)(p.xform, angle);
		//p.xform[4] = cx;
		//p.xform[5] = cy;

		//p.extent[0] = w;
		//p.extent[1] = h;

		//p.image = image;

		//p.innerColor = p.outerColor = CONTEXT::RGBAf)(1, 1, 1, alpha);

		//return p;
	}

	// Scissoring
	void CONTEXT::scissor(float x, float y, float w, float h)
	{
		//::nano2d::state * state = __getState();

		//w = CONTEXT::__maxf)(0.0f, w);
		//h = CONTEXT::__maxf)(0.0f, h);

		//CONTEXT::TransformIdentity)(state->scissor.xform);
		//state->scissor.xform[4] = x + w * 0.5f;
		//state->scissor.xform[5] = y + h * 0.5f;
		//CONTEXT::TransformMultiply)(state->scissor.xform, state->xform);

		//state->scissor.extent[0] = w * 0.5f;
		//state->scissor.extent[1] = h * 0.5f;
	}

	//static void CONTEXT::__isectRects)(float * dst,
	//	float ax, float ay, float aw, float ah,
	//	float bx, float by, float bw, float bh)
	//{
	//	float minx = CONTEXT::__maxf)(ax, bx);
	//	float miny = CONTEXT::__maxf)(ay, by);
	//	float maxx = CONTEXT::__minf)(ax + aw, bx + bw);
	//	float maxy = CONTEXT::__minf)(ay + ah, by + bh);
	//	dst[0] = minx;
	//	dst[1] = miny;
	//	dst[2] = CONTEXT::__maxf)(0.0f, maxx - minx);
	//	dst[3] = CONTEXT::__maxf)(0.0f, maxy - miny);
	//}

	void CONTEXT::intersect_scissor(float x, float y, float w, float h)
	{

		// intersect_scissor(x, y, w, h);
		//::nano2d::state * state = __getState();
		//float pxform[6], invxorm[6];
		//float rect[4];
		//float ex, ey, tex, tey;

		//// If no previous scissor has been set, set the scissor as current scissor.
		//if (state->scissor.extent[0] < 0) {
		//	CONTEXT::Scissor)(ctx, x, y, w, h);
		//	return;
		//}

		//// Transform the current scissor rect into current transform space.
		//// If there is difference in rotation, this will be approximation.
		//::memory_copy(pxform, state->scissor.xform, sizeof(float) * 6);
		//ex = state->scissor.extent[0];
		//ey = state->scissor.extent[1];
		//CONTEXT::TransformInverse)(invxorm, state->xform);
		//CONTEXT::TransformMultiply)(pxform, invxorm);
		//tex = ex * CONTEXT::__absf)(pxform[0]) + ey * CONTEXT::__absf)(pxform[2]);
		//tey = ex * CONTEXT::__absf)(pxform[1]) + ey * CONTEXT::__absf)(pxform[3]);

		//// Intersect rects.
		//CONTEXT::__isectRects)(rect, pxform[4] - tex, pxform[5] - tey, tex * 2, tey * 2, x, y, w, h);

		//CONTEXT::Scissor)(ctx, rect[0], rect[1], rect[2], rect[3]);
	}

	void CONTEXT::reset_scissor()
	{
		//::nano2d::state * state = __getState();
		//::memory_set(state->scissor.xform, 0, sizeof(state->scissor.xform));
		//state->scissor.extent[0] = -1.0f;
		//state->scissor.extent[1] = -1.0f;
		//reset_scissor();
	}

	
	// Global composite operation.
	void CONTEXT::global_composite_operation(int op)
	{
		
		::nano2d::state * state = __getState();
		state->compositeOperation = __compositeOperationState(op);

	}


	void CONTEXT::global_composite_blend_func(int sfactor, int dfactor)
	{
		
		global_composite_blend_func_separate(sfactor, dfactor, sfactor, dfactor);

	}


	void CONTEXT::global_composite_blend_func_separate(int srcRGB, int dstRGB, int srcAlpha, int dstAlpha)
	{
		compositeOperationState op;
		op.srcRGB = srcRGB;
		op.dstRGB = dstRGB;
		op.srcAlpha = srcAlpha;
		op.dstAlpha = dstAlpha;

		::nano2d::state * state = __getState();
		state->compositeOperation = op;

	}


	int point_equals(float x1, float y1, float x2, float y2, float tol)
	{
		
		float Δx = x2 - x1;
		float Δy = y2 - y1;
		return Δx * Δx + Δy * Δy < tol * tol;

	}


	float point_distance_seg(float x, float y, float px, float py, float qx, float qy)
	{
		float pqx, pqy, Δx, Δy, d, t;
		pqx = qx - px;
		pqy = qy - py;
		Δx = x - px;
		Δy = y - py;
		d = pqx * pqx + pqy * pqy;
		t = pqx * Δx + pqy * Δy;
		if (d > 0) t /= d;
		if (t < 0) t = 0;
		else if (t > 1) t = 1;
		Δx = px + t * pqx - x;
		Δy = py + t * pqy - y;
		return Δx * Δx + Δy * Δy;
	}


	void CONTEXT::__append_commands(float * vals, int nvals)
	{
		::nano2d::state * state = __getState();
		int i;

		if (ncommands + nvals > ccommands) {
			float * commands;
			int ccommands = ncommands + nvals + ccommands / 2;
			commands = (float *)realloc(commands, sizeof(float) * ccommands);
			if (commands == NULL) return;
			commands = commands;
			ccommands = ccommands;
		}

		if ((int)vals[0] != ::nano2d::e_command_close && (int)vals[0] != ::nano2d::e_command_winding) {
			commandx = vals[nvals - 2];
			commandy = vals[nvals - 1];
		}

		// transform commands
		i = 0;
		while (i < nvals) {
			int cmd = (int)vals[i];
			switch (cmd) {
			case ::nano2d::e_command_move_to:
				transform_point(&vals[i + 1], &vals[i + 2], state->xform, vals[i + 1], vals[i + 2]);
				i += 3;
				break;
			case ::nano2d::e_command_line_to:
				transform_point(&vals[i + 1], &vals[i + 2], state->xform, vals[i + 1], vals[i + 2]);
				i += 3;
				break;
			case ::nano2d::e_command_bezier_to:
				transform_point(&vals[i + 1], &vals[i + 2], state->xform, vals[i + 1], vals[i + 2]);
				transform_point(&vals[i + 3], &vals[i + 4], state->xform, vals[i + 3], vals[i + 4]);
				transform_point(&vals[i + 5], &vals[i + 6], state->xform, vals[i + 5], vals[i + 6]);
				i += 7;
				break;
			case ::nano2d::e_command_close:
				i++;
				break;
			case ::nano2d::e_command_winding:
				i += 2;
				break;
			default:
				i++;
			}
		}

		::memory_copy(&commands[ncommands], vals, nvals * sizeof(float));

		ncommands += nvals;
	}


	//static void CONTEXT::__clearPathCache()
	//{
	//	cache->npoints = 0;
	//	cache->npaths = 0;
	//}

	//static ::nano2d::path * CONTEXT::__lastPath()
	//{
	//	if (cache->npaths > 0)
	//		return &cache->paths[cache->npaths - 1];
	//	return NULL;
	//}

	//static void CONTEXT::__addPath()
	//{
	//	::nano2d::path * path;
	//	if (cache->npaths + 1 > cache->cpaths) {
	//		::nano2d::path * paths;
	//		int cpaths = cache->npaths + 1 + cache->cpaths / 2;
	//		paths = (::nano2d::path *)realloc(cache->paths, sizeof(::nano2d::path) * cpaths);
	//		if (paths == NULL) return;
	//		cache->paths = paths;
	//		cache->cpaths = cpaths;
	//	}
	//	path = &cache->paths[cache->npaths];
	//	::memory_set(path, 0, sizeof(*path));
	//	path->first = cache->npoints;
	//	path->winding = ::nano2d::e_winding_ccw;
	//
	//	cache->npaths++;
	//}
	//
	//static NVGpoint * CONTEXT::__lastPoint()
	//{
	//	if (cache->npoints > 0)
	//		return &cache->points[cache->npoints - 1];
	//	return NULL;
	//}

	//static void CONTEXT::__addPoint(float x, float y, int flags)
	//{
	//	::nano2d::path * path = CONTEXT::__lastPath)(ctx);
	//	NVGpoint * pt;
	//	if (path == NULL) return;
	//
	//	if (path->count > 0 && cache->npoints > 0) {
	//		pt = CONTEXT::__lastPoint)(ctx);
	//		if (CONTEXT::__ptEquals)(pt->x, pt->y, x, y, distTol)) {
	//			pt->flags |= flags;
	//			return;
	//		}
	//	}
	//
	//	if (cache->npoints + 1 > cache->cpoints) {
	//		NVGpoint * points;
	//		int cpoints = cache->npoints + 1 + cache->cpoints / 2;
	//		points = (NVGpoint *)realloc(cache->points, sizeof(NVGpoint) * cpoints);
	//		if (points == NULL) return;
	//		cache->points = points;
	//		cache->cpoints = cpoints;
	//	}
	//
	//	pt = &cache->points[cache->npoints];
	//	::memory_set(pt, 0, sizeof(*pt));
	//	pt->x = x;
	//	pt->y = y;
	//	pt->flags = (unsigned char)flags;
	//
	//	cache->npoints++;
	//	path->count++;
	//}

	//static void CONTEXT::__closePath()
	//{
	//	::nano2d::path * path = CONTEXT::__lastPath)(ctx);
	//	if (path == NULL) return;
	//	path->closed = 1;
	//}

	//static void CONTEXT::__pathWinding(int winding)
	//{
	//	::nano2d::path * path = CONTEXT::__lastPath)(ctx);
	//	if (path == NULL) return;
	//	path->winding = winding;
	//}
	//
	//static float CONTEXT::__getAverageScale)(float * t)
	//{
	//	float sx = sqrtf(t[0] * t[0] + t[2] * t[2]);
	//	float sy = sqrtf(t[1] * t[1] + t[3] * t[3]);
	//	return (sx + sy) * 0.5f;
	//}

	//static NVGvertex * CONTEXT::__allocTempVerts(int nverts)
	//{
	//	if (nverts > cache->cverts) {
	//		NVGvertex * verts;
	//		int cverts = (nverts + 0xff) & ~0xff; // Round up to prevent allocations when things change just slightly.
	//		verts = (NVGvertex *)realloc(cache->verts, sizeof(NVGvertex) * cverts);
	//		if (verts == NULL) return NULL;
	//		cache->verts = verts;
	//		cache->cverts = cverts;
	//	}
	//
	//	return cache->verts;
	//}
	//
	//static float CONTEXT::__triarea2)(float ax, float ay, float bx, float by, float cx, float cy)
	//{
	//	float abx = bx - ax;
	//	float aby = by - ay;
	//	float acx = cx - ax;
	//	float acy = cy - ay;
	//	return acx * aby - abx * acy;
	//}

	//static float CONTEXT::__polyArea)(NVGpoint * pts, int npts)
	//{
	//	int i;
	//	float area = 0;
	//	for (i = 2; i < npts; i++) {
	//		NVGpoint * a = &pts[0];
	//		NVGpoint * b = &pts[i - 1];
	//		NVGpoint * c = &pts[i];
	//		area += CONTEXT::__triarea2)(a->x, a->y, b->x, b->y, c->x, c->y);
	//	}
	//	return area * 0.5f;
	//}

	//static void CONTEXT::__polyReverse)(NVGpoint * pts, int npts)
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


	//static void CONTEXT::__vset)(NVGvertex * vtx, float x, float y, float u, float v)
	//{
	//	vtx->x = x;
	//	vtx->y = y;
	//	vtx->u = u;
	//	vtx->v = v;
	//}

	//static void CONTEXT::__tesselateBezier)(NANO2D_CONTEXT * ctx,
	//	float x1, float y1, float x2, float y2,
	//	float x3, float y3, float x4, float y4,
	//	int level, int type)
	//{
	//	float x12, y12, x23, y23, x34, y34, x123, y123, x234, y234, x1234, y1234;
	//	float Δx, Δy, d2, d3;
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
	//	Δx = x4 - x1;
	//	Δy = y4 - y1;
	//	d2 = CONTEXT::__absf)(((x2 - x4) * Δy - (y2 - y4) * Δx));
	//	d3 = CONTEXT::__absf)(((x3 - x4) * Δy - (y3 - y4) * Δx));
	//
	//	if ((d2 + d3) * (d2 + d3) < tessTol * (Δx * Δx + Δy * Δy)) {
	//		CONTEXT::__addPoint)(ctx, x4, y4, type);
	//		return;
	//	}
	//
	//	/*	if (CONTEXT::__absf)(x1+x3-x2-x2) + CONTEXT::__absf)(y1+y3-y2-y2) + CONTEXT::__absf)(x2+x4-x3-x3) + CONTEXT::__absf)(y2+y4-y3-y3) < tessTol) {
	//			CONTEXT::__addPoint)(ctx, x4, y4, type);
	//			return;
	//		}*/
	//
	//	x234 = (x23 + x34) * 0.5f;
	//	y234 = (y23 + y34) * 0.5f;
	//	x1234 = (x123 + x234) * 0.5f;
	//	y1234 = (y123 + y234) * 0.5f;
	//
	//	CONTEXT::__tesselateBezier)(ctx, x1, y1, x12, y12, x123, y123, x1234, y1234, level + 1, 0);
	//	CONTEXT::__tesselateBezier)(ctx, x1234, y1234, x234, y234, x34, y34, x4, y4, level + 1, type);
	//}

	//static void CONTEXT::__flattenPaths()
	//{
	//	NVGpathCache * cache = cache;
	//	//	::nano2d::state* state = __getState();
	//	NVGpoint * last;
	//	NVGpoint * p0;
	//	NVGpoint * p1;
	//	NVGpoint * pts;
	//	::nano2d::path * path;
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
	//	while (i < ncommands) {
	//		int cmd = (int)commands[i];
	//		switch (cmd) {
	//		case ::nano2d::e_command_move_to:
	//			CONTEXT::__addPath)(ctx);
	//			p = &commands[i + 1];
	//			CONTEXT::__addPoint)(ctx, p[0], p[1], NVG_PT_CORNER);
	//			i += 3;
	//			break;
	//		case ::nano2d::e_command_line_to:
	//			p = &commands[i + 1];
	//			CONTEXT::__addPoint)(ctx, p[0], p[1], NVG_PT_CORNER);
	//			i += 3;
	//			break;
	//		case ::nano2d::e_command_bezier_to:
	//			last = CONTEXT::__lastPoint)(ctx);
	//			if (last != NULL) {
	//				cp1 = &commands[i + 1];
	//				cp2 = &commands[i + 3];
	//				p = &commands[i + 5];
	//				CONTEXT::__tesselateBezier)(ctx, last->x, last->y, cp1[0], cp1[1], cp2[0], cp2[1], p[0], p[1], 0, NVG_PT_CORNER);
	//			}
	//			i += 7;
	//			break;
	//		case ::nano2d::e_command_close:
	//			CONTEXT::__closePath)(ctx);
	//			i++;
	//			break;
	//		case ::nano2d::e_command_winding:
	//			CONTEXT::__pathWinding)(ctx, (int)commands[i + 1]);
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
	//		if (CONTEXT::__ptEquals)(p0->x, p0->y, p1->x, p1->y, distTol)) {
	//			path->count--;
	//			p0 = &pts[path->count - 1];
	//			path->closed = 1;
	//		}
	//
	//		// Enforce winding.
	//		if (path->count > 2) {
	//			area = CONTEXT::__polyArea)(pts, path->count);
	//			if (path->winding == ::nano2d::e_winding_ccw && area < 0.0f)
	//				CONTEXT::__polyReverse)(pts, path->count);
	//			if (path->winding == ::nano2d::e_winding_cw && area > 0.0f)
	//				CONTEXT::__polyReverse)(pts, path->count);
	//		}
	//
	//		for (i = 0; i < path->count; i++) {
	//			// Calculate segment direction and length
	//			p0->Δx = p1->x - p0->x;
	//			p0->Δy = p1->y - p0->y;
	//			p0->len = CONTEXT::__normalize)(&p0->Δx, &p0->Δy);
	//			// Update bounds
	//			cache->bounds[0] = CONTEXT::__minf)(cache->bounds[0], p0->x);
	//			cache->bounds[1] = CONTEXT::__minf)(cache->bounds[1], p0->y);
	//			cache->bounds[2] = CONTEXT::__maxf)(cache->bounds[2], p0->x);
	//			cache->bounds[3] = CONTEXT::__maxf)(cache->bounds[3], p0->y);
	//			// Advance
	//			p0 = p1++;
	//		}
	//	}
	//}

	//static int CONTEXT::__curveDivs)(float r, float arc, float tol)
	//{
	//	float da = acosf(r / (r + tol)) * 2.0f;
	//	return CONTEXT::__maxi)(2, (int)ceilf(arc / da));
	//}

	//static void CONTEXT::__chooseBevel)(int bevel, NVGpoint * p0, NVGpoint * p1, float w,
	//	float * x0, float * y0, float * x1, float * y1)
	//{
	//	if (bevel) {
	//		*x0 = p1->x + p0->Δy * w;
	//		*y0 = p1->y - p0->Δx * w;
	//		*x1 = p1->x + p1->Δy * w;
	//		*y1 = p1->y - p1->Δx * w;
	//	}
	//	else {
	//		*x0 = p1->x + p1->dmx * w;
	//		*y0 = p1->y + p1->dmy * w;
	//		*x1 = p1->x + p1->dmx * w;
	//		*y1 = p1->y + p1->dmy * w;
	//	}
	//}

	//static NVGvertex * CONTEXT::__roundJoin)(NVGvertex * dst, NVGpoint * p0, NVGpoint * p1,
	//	float lw, float rw, float lu, float ru, int ncap,
	//	float fringe)
	//{
	//	int i, n;
	//	float dlx0 = p0->Δy;
	//	float dly0 = -p0->Δx;
	//	float dlx1 = p1->Δy;
	//	float dly1 = -p1->Δx;
	//	NVG_NOTUSED(fringe);
	//
	//	if (p1->flags & NVG_PT_LEFT) {
	//		float lx0, ly0, lx1, ly1, a0, a1;
	//		CONTEXT::__chooseBevel)(p1->flags & NVG_PR_INNERBEVEL, p0, p1, lw, &lx0, &ly0, &lx1, &ly1);
	//		a0 = atan2f(-dly0, -dlx0);
	//		a1 = atan2f(-dly1, -dlx1);
	//		if (a1 > a0) a1 -= ::nano2d::f_pi * 2;
	//
	//		CONTEXT::__vset)(dst, lx0, ly0, lu, 1); dst++;
	//		CONTEXT::__vset)(dst, p1->x - dlx0 * rw, p1->y - dly0 * rw, ru, 1); dst++;
	//
	//		n = CONTEXT::__clampi)((int)ceilf(((a0 - a1) / ::nano2d::f_pi) * ncap), 2, ncap);
	//		for (i = 0; i < n; i++) {
	//			float u = i / (float)(n - 1);
	//			float a = a0 + u * (a1 - a0);
	//			float rx = p1->x + cosf(a) * rw;
	//			float ry = p1->y + sinf(a) * rw;
	//			CONTEXT::__vset)(dst, p1->x, p1->y, 0.5f, 1); dst++;
	//			CONTEXT::__vset)(dst, rx, ry, ru, 1); dst++;
	//		}
	//
	//		CONTEXT::__vset)(dst, lx1, ly1, lu, 1); dst++;
	//		CONTEXT::__vset)(dst, p1->x - dlx1 * rw, p1->y - dly1 * rw, ru, 1); dst++;
	//
	//	}
	//	else {
	//		float rx0, ry0, rx1, ry1, a0, a1;
	//		CONTEXT::__chooseBevel)(p1->flags & NVG_PR_INNERBEVEL, p0, p1, -rw, &rx0, &ry0, &rx1, &ry1);
	//		a0 = atan2f(dly0, dlx0);
	//		a1 = atan2f(dly1, dlx1);
	//		if (a1 < a0) a1 += ::nano2d::f_pi * 2;
	//
	//		CONTEXT::__vset)(dst, p1->x + dlx0 * rw, p1->y + dly0 * rw, lu, 1); dst++;
	//		CONTEXT::__vset)(dst, rx0, ry0, ru, 1); dst++;
	//
	//		n = CONTEXT::__clampi)((int)ceilf(((a1 - a0) / ::nano2d::f_pi) * ncap), 2, ncap);
	//		for (i = 0; i < n; i++) {
	//			float u = i / (float)(n - 1);
	//			float a = a0 + u * (a1 - a0);
	//			float lx = p1->x + cosf(a) * lw;
	//			float ly = p1->y + sinf(a) * lw;
	//			CONTEXT::__vset)(dst, lx, ly, lu, 1); dst++;
	//			CONTEXT::__vset)(dst, p1->x, p1->y, 0.5f, 1); dst++;
	//		}
	//
	//		CONTEXT::__vset)(dst, p1->x + dlx1 * rw, p1->y + dly1 * rw, lu, 1); dst++;
	//		CONTEXT::__vset)(dst, rx1, ry1, ru, 1); dst++;
	//
	//	}
	//	return dst;
	//}

	//static NVGvertex * CONTEXT::__bevelJoin)(NVGvertex * dst, NVGpoint * p0, NVGpoint * p1,
	//	float lw, float rw, float lu, float ru, float fringe)
	//{
	//	float rx0, ry0, rx1, ry1;
	//	float lx0, ly0, lx1, ly1;
	//	float dlx0 = p0->Δy;
	//	float dly0 = -p0->Δx;
	//	float dlx1 = p1->Δy;
	//	float dly1 = -p1->Δx;
	//	NVG_NOTUSED(fringe);
	//
	//	if (p1->flags & NVG_PT_LEFT) {
	//		CONTEXT::__chooseBevel)(p1->flags & NVG_PR_INNERBEVEL, p0, p1, lw, &lx0, &ly0, &lx1, &ly1);
	//
	//		CONTEXT::__vset)(dst, lx0, ly0, lu, 1); dst++;
	//		CONTEXT::__vset)(dst, p1->x - dlx0 * rw, p1->y - dly0 * rw, ru, 1); dst++;
	//
	//		if (p1->flags & NVG_PT_BEVEL) {
	//			CONTEXT::__vset)(dst, lx0, ly0, lu, 1); dst++;
	//			CONTEXT::__vset)(dst, p1->x - dlx0 * rw, p1->y - dly0 * rw, ru, 1); dst++;
	//
	//			CONTEXT::__vset)(dst, lx1, ly1, lu, 1); dst++;
	//			CONTEXT::__vset)(dst, p1->x - dlx1 * rw, p1->y - dly1 * rw, ru, 1); dst++;
	//		}
	//		else {
	//			rx0 = p1->x - p1->dmx * rw;
	//			ry0 = p1->y - p1->dmy * rw;
	//
	//			CONTEXT::__vset)(dst, p1->x, p1->y, 0.5f, 1); dst++;
	//			CONTEXT::__vset)(dst, p1->x - dlx0 * rw, p1->y - dly0 * rw, ru, 1); dst++;
	//
	//			CONTEXT::__vset)(dst, rx0, ry0, ru, 1); dst++;
	//			CONTEXT::__vset)(dst, rx0, ry0, ru, 1); dst++;
	//
	//			CONTEXT::__vset)(dst, p1->x, p1->y, 0.5f, 1); dst++;
	//			CONTEXT::__vset)(dst, p1->x - dlx1 * rw, p1->y - dly1 * rw, ru, 1); dst++;
	//		}
	//
	//		CONTEXT::__vset)(dst, lx1, ly1, lu, 1); dst++;
	//		CONTEXT::__vset)(dst, p1->x - dlx1 * rw, p1->y - dly1 * rw, ru, 1); dst++;
	//
	//	}
	//	else {
	//		CONTEXT::__chooseBevel)(p1->flags & NVG_PR_INNERBEVEL, p0, p1, -rw, &rx0, &ry0, &rx1, &ry1);
	//
	//		CONTEXT::__vset)(dst, p1->x + dlx0 * lw, p1->y + dly0 * lw, lu, 1); dst++;
	//		CONTEXT::__vset)(dst, rx0, ry0, ru, 1); dst++;
	//
	//		if (p1->flags & NVG_PT_BEVEL) {
	//			CONTEXT::__vset)(dst, p1->x + dlx0 * lw, p1->y + dly0 * lw, lu, 1); dst++;
	//			CONTEXT::__vset)(dst, rx0, ry0, ru, 1); dst++;
	//
	//			CONTEXT::__vset)(dst, p1->x + dlx1 * lw, p1->y + dly1 * lw, lu, 1); dst++;
	//			CONTEXT::__vset)(dst, rx1, ry1, ru, 1); dst++;
	//		}
	//		else {
	//			lx0 = p1->x + p1->dmx * lw;
	//			ly0 = p1->y + p1->dmy * lw;
	//
	//			CONTEXT::__vset)(dst, p1->x + dlx0 * lw, p1->y + dly0 * lw, lu, 1); dst++;
	//			CONTEXT::__vset)(dst, p1->x, p1->y, 0.5f, 1); dst++;
	//
	//			CONTEXT::__vset)(dst, lx0, ly0, lu, 1); dst++;
	//			CONTEXT::__vset)(dst, lx0, ly0, lu, 1); dst++;
	//
	//			CONTEXT::__vset)(dst, p1->x + dlx1 * lw, p1->y + dly1 * lw, lu, 1); dst++;
	//			CONTEXT::__vset)(dst, p1->x, p1->y, 0.5f, 1); dst++;
	//		}
	//
	//		CONTEXT::__vset)(dst, p1->x + dlx1 * lw, p1->y + dly1 * lw, lu, 1); dst++;
	//		CONTEXT::__vset)(dst, rx1, ry1, ru, 1); dst++;
	//	}
	//
	//	return dst;
	//}

	//static NVGvertex * CONTEXT::__buttCapStart)(NVGvertex * dst, NVGpoint * p,
	//	float Δx, float Δy, float w, float d,
	//	float aa, float u0, float u1)
	//{
	//	float px = p->x - Δx * d;
	//	float py = p->y - Δy * d;
	//	float dlx = Δy;
	//	float dly = -Δx;
	//	CONTEXT::__vset)(dst, px + dlx * w - Δx * aa, py + dly * w - Δy * aa, u0, 0); dst++;
	//	CONTEXT::__vset)(dst, px - dlx * w - Δx * aa, py - dly * w - Δy * aa, u1, 0); dst++;
	//	CONTEXT::__vset)(dst, px + dlx * w, py + dly * w, u0, 1); dst++;
	//	CONTEXT::__vset)(dst, px - dlx * w, py - dly * w, u1, 1); dst++;
	//	return dst;
	//}

	//static NVGvertex * CONTEXT::__buttCapEnd)(NVGvertex * dst, NVGpoint * p,
	//	float Δx, float Δy, float w, float d,
	//	float aa, float u0, float u1)
	//{
	//	float px = p->x + Δx * d;
	//	float py = p->y + Δy * d;
	//	float dlx = Δy;
	//	float dly = -Δx;
	//	CONTEXT::__vset)(dst, px + dlx * w, py + dly * w, u0, 1); dst++;
	//	CONTEXT::__vset)(dst, px - dlx * w, py - dly * w, u1, 1); dst++;
	//	CONTEXT::__vset)(dst, px + dlx * w + Δx * aa, py + dly * w + Δy * aa, u0, 0); dst++;
	//	CONTEXT::__vset)(dst, px - dlx * w + Δx * aa, py - dly * w + Δy * aa, u1, 0); dst++;
	//	return dst;
	//}
	//

	//static NVGvertex * CONTEXT::__roundCapStart)(NVGvertex * dst, NVGpoint * p,
	//	float Δx, float Δy, float w, int ncap,
	//	float aa, float u0, float u1)
	//{
	//	int i;
	//	float px = p->x;
	//	float py = p->y;
	//	float dlx = Δy;
	//	float dly = -Δx;
	//	NVG_NOTUSED(aa);
	//	for (i = 0; i < ncap; i++) {
	//		float a = i / (float)(ncap - 1) * ::nano2d::f_pi;
	//		float ax = cosf(a) * w, ay = sinf(a) * w;
	//		CONTEXT::__vset)(dst, px - dlx * ax - Δx * ay, py - dly * ax - Δy * ay, u0, 1); dst++;
	//		CONTEXT::__vset)(dst, px, py, 0.5f, 1); dst++;
	//	}
	//	CONTEXT::__vset)(dst, px + dlx * w, py + dly * w, u0, 1); dst++;
	//	CONTEXT::__vset)(dst, px - dlx * w, py - dly * w, u1, 1); dst++;
	//	return dst;
	//}

	//static NVGvertex * CONTEXT::__roundCapEnd)(NVGvertex * dst, NVGpoint * p,
	//	float Δx, float Δy, float w, int ncap,
	//	float aa, float u0, float u1)
	//{
	//	int i;
	//	float px = p->x;
	//	float py = p->y;
	//	float dlx = Δy;
	//	float dly = -Δx;
	//	NVG_NOTUSED(aa);
	//	CONTEXT::__vset)(dst, px + dlx * w, py + dly * w, u0, 1); dst++;
	//	CONTEXT::__vset)(dst, px - dlx * w, py - dly * w, u1, 1); dst++;
	//	for (i = 0; i < ncap; i++) {
	//		float a = i / (float)(ncap - 1) * ::nano2d::f_pi;
	//		float ax = cosf(a) * w, ay = sinf(a) * w;
	//		CONTEXT::__vset)(dst, px, py, 0.5f, 1); dst++;
	//		CONTEXT::__vset)(dst, px - dlx * ax + Δx * ay, py - dly * ax + Δy * ay, u0, 1); dst++;
	//	}
	//	return dst;
	//}


	//static void CONTEXT::__calculateJoins(float w, int lineJoin, float miterLimit)
	//{
	//	NVGpathCache * cache = cache;
	//	int i, j;
	//	float iw = 0.0f;
	//
	//	if (w > 0.0f) iw = 1.0f / w;
	//
	//	// Calculate which joins needs extra vertices to append, and gather vertex count.
	//	for (i = 0; i < cache->npaths; i++) {
	//		::nano2d::path * path = &cache->paths[i];
	//		NVGpoint * pts = &cache->points[path->first];
	//		NVGpoint * p0 = &pts[path->count - 1];
	//		NVGpoint * p1 = &pts[0];
	//		int nleft = 0;
	//
	//		path->nbevel = 0;
	//
	//		for (j = 0; j < path->count; j++) {
	//			float dlx0, dly0, dlx1, dly1, dmr2, cross, limit;
	//			dlx0 = p0->Δy;
	//			dly0 = -p0->Δx;
	//			dlx1 = p1->Δy;
	//			dly1 = -p1->Δx;
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
	//			cross = p1->Δx * p0->Δy - p0->Δx * p1->Δy;
	//			if (cross > 0.0f) {
	//				nleft++;
	//				p1->flags |= NVG_PT_LEFT;
	//			}
	//
	//			// Calculate if we should use bevel or miter for inner join.
	//			limit = CONTEXT::__maxf)(1.01f, CONTEXT::__minf)(p0->len, p1->len) * iw);
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


	//static int CONTEXT::__expandStroke(float w, float fringe, int lineCap, int lineJoin, float miterLimit)
	//{
	//	NVGpathCache * cache = cache;
	//	NVGvertex * verts;
	//	NVGvertex * dst;
	//	int cverts, i, j;
	//	float aa = fringe;//fringeWidth;
	//	float u0 = 0.0f, u1 = 1.0f;
	//	int ncap = CONTEXT::__curveDivs)(w, ::nano2d::f_pi, tessTol);	// Calculate divisions per half circle.
	//
	//	w += aa * 0.5f;
	//
	//	// Disable the gradient used for antialiasing when antialiasing is not used.
	//	if (aa == 0.0f) {
	//		u0 = 0.5f;
	//		u1 = 0.5f;
	//	}
	//
	//	CONTEXT::__calculateJoins)(ctx, w, lineJoin, miterLimit);
	//
	//	// Calculate max vertex usage.
	//	cverts = 0;
	//	for (i = 0; i < cache->npaths; i++) {
	//		::nano2d::path * path = &cache->paths[i];
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
	//	verts = CONTEXT::__allocTempVerts)(ctx, cverts);
	//	if (verts == NULL) return 0;
	//
	//	for (i = 0; i < cache->npaths; i++) {
	//		::nano2d::path * path = &cache->paths[i];
	//		NVGpoint * pts = &cache->points[path->first];
	//		NVGpoint * p0;
	//		NVGpoint * p1;
	//		int s, e, loop;
	//		float Δx, Δy;
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
	//			Δx = p1->x - p0->x;
	//			Δy = p1->y - p0->y;
	//			CONTEXT::__normalize)(&Δx, &Δy);
	//			if (lineCap == ::nano2d::e_line_cap_butt)
	//				dst = CONTEXT::__buttCapStart)(dst, p0, Δx, Δy, w, -aa * 0.5f, aa, u0, u1);
	//			else if (lineCap == ::nano2d::e_line_cap_butt || lineCap == NVG_SQUARE)
	//				dst = CONTEXT::__buttCapStart)(dst, p0, Δx, Δy, w, w - aa, aa, u0, u1);
	//			else if (lineCap == NVG_ROUND)
	//				dst = CONTEXT::__roundCapStart)(dst, p0, Δx, Δy, w, ncap, aa, u0, u1);
	//		}
	//
	//		for (j = s; j < e; ++j) {
	//			if ((p1->flags & (NVG_PT_BEVEL | NVG_PR_INNERBEVEL)) != 0) {
	//				if (lineJoin == NVG_ROUND) {
	//					dst = CONTEXT::__roundJoin)(dst, p0, p1, w, w, u0, u1, ncap, aa);
	//				}
	//				else {
	//					dst = CONTEXT::__bevelJoin)(dst, p0, p1, w, w, u0, u1, aa);
	//				}
	//			}
	//			else {
	//				CONTEXT::__vset)(dst, p1->x + (p1->dmx * w), p1->y + (p1->dmy * w), u0, 1); dst++;
	//				CONTEXT::__vset)(dst, p1->x - (p1->dmx * w), p1->y - (p1->dmy * w), u1, 1); dst++;
	//			}
	//			p0 = p1++;
	//		}
	//
	//		if (loop) {
	//			// Loop it
	//			CONTEXT::__vset)(dst, verts[0].x(), verts[0].y(), u0, 1); dst++;
	//			CONTEXT::__vset)(dst, verts[1].x(), verts[1].y(), u1, 1); dst++;
	//		}
	//		else {
	//			// Add cap
	//			Δx = p1->x - p0->x;
	//			Δy = p1->y - p0->y;
	//			CONTEXT::__normalize)(&Δx, &Δy);
	//			if (lineCap == ::nano2d::e_line_cap_butt)
	//				dst = CONTEXT::__buttCapEnd)(dst, p1, Δx, Δy, w, -aa * 0.5f, aa, u0, u1);
	//			else if (lineCap == ::nano2d::e_line_cap_butt || lineCap == NVG_SQUARE)
	//				dst = CONTEXT::__buttCapEnd)(dst, p1, Δx, Δy, w, w - aa, aa, u0, u1);
	//			else if (lineCap == NVG_ROUND)
	//				dst = CONTEXT::__roundCapEnd)(dst, p1, Δx, Δy, w, ncap, aa, u0, u1);
	//		}
	//
	//		path->nstroke = (int)(dst - verts);
	//
	//		verts = dst;
	//	}
	//
	//	return 1;
	//}

	//static int CONTEXT::__expandFill(float w, int lineJoin, float miterLimit)
	//{
	//	NVGpathCache * cache = cache;
	//	NVGvertex * verts;
	//	NVGvertex * dst;
	//	int cverts, convex, i, j;
	//	float aa = fringeWidth;
	//	int fringe = w > 0.0f;
	//
	//	CONTEXT::__calculateJoins)(ctx, w, lineJoin, miterLimit);
	//
	//	// Calculate max vertex usage.
	//	cverts = 0;
	//	for (i = 0; i < cache->npaths; i++) {
	//		::nano2d::path * path = &cache->paths[i];
	//		cverts += path->count + path->nbevel + 1;
	//		if (fringe)
	//			cverts += (path->count + path->nbevel * 5 + 1) * 2; // plus one for loop
	//	}
	//
	//	verts = CONTEXT::__allocTempVerts)(ctx, cverts);
	//	if (verts == NULL) return 0;
	//
	//	convex = cache->npaths == 1 && cache->paths[0].convex;
	//
	//	for (i = 0; i < cache->npaths; i++) {
	//		::nano2d::path * path = &cache->paths[i];
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
	//					float dlx0 = p0->Δy;
	//					float dly0 = -p0->Δx;
	//					float dlx1 = p1->Δy;
	//					float dly1 = -p1->Δx;
	//					if (p1->flags & NVG_PT_LEFT) {
	//						float lx = p1->x + p1->dmx * woff;
	//						float ly = p1->y + p1->dmy * woff;
	//						CONTEXT::__vset)(dst, lx, ly, 0.5f, 1); dst++;
	//					}
	//					else {
	//						float lx0 = p1->x + dlx0 * woff;
	//						float ly0 = p1->y + dly0 * woff;
	//						float lx1 = p1->x + dlx1 * woff;
	//						float ly1 = p1->y + dly1 * woff;
	//						CONTEXT::__vset)(dst, lx0, ly0, 0.5f, 1); dst++;
	//						CONTEXT::__vset)(dst, lx1, ly1, 0.5f, 1); dst++;
	//					}
	//				}
	//				else {
	//					CONTEXT::__vset)(dst, p1->x + (p1->dmx * woff), p1->y + (p1->dmy * woff), 0.5f, 1); dst++;
	//				}
	//				p0 = p1++;
	//			}
	//		}
	//		else {
	//			for (j = 0; j < path->count; ++j) {
	//				CONTEXT::__vset)(dst, pts[j].x(), pts[j].y(), 0.5f, 1);
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
	//					dst = CONTEXT::__bevelJoin)(dst, p0, p1, lw, rw, lu, ru, fringeWidth);
	//				}
	//				else {
	//					CONTEXT::__vset)(dst, p1->x + (p1->dmx * lw), p1->y + (p1->dmy * lw), lu, 1); dst++;
	//					CONTEXT::__vset)(dst, p1->x - (p1->dmx * rw), p1->y - (p1->dmy * rw), ru, 1); dst++;
	//				}
	//				p0 = p1++;
	//			}
	//
	//			// Loop it
	//			CONTEXT::__vset)(dst, verts[0].x(), verts[0].y(), lu, 1); dst++;
	//			CONTEXT::__vset)(dst, verts[1].x(), verts[1].y(), ru, 1); dst++;
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
	void CONTEXT::begin_path()
	{
		//ncommands = 0;
		//CONTEXT::__clearPathCache)(ctx);

		//begin_path();

	}

	void CONTEXT::move_to(float x, float y)
	{
		//float vals[] = { ::nano2d::e_command_move_to, x, y };
		//CONTEXT::__appendCommands)(ctx, vals, NANO2D_COUNTOF(vals));
		//move_to(x, y);
	}

	void CONTEXT::line_to(float x, float y)
	{
		/*float vals[] = { ::nano2d::e_command_line_to, x, y };
		CONTEXT::__appendCommands)(ctx, vals, NANO2D_COUNTOF(vals));*/

		//line_to(x, y);
	}

	void CONTEXT::bezier_to(float c1x, float c1y, float c2x, float c2y, float x, float y)
	{
		//float vals[] = { ::nano2d::e_command_bezier_to, c1x, c1y, c2x, c2y, x, y };
		//CONTEXT::__appendCommands)(ctx, vals, NANO2D_COUNTOF(vals));
	}

	void CONTEXT::quad_to(float cx, float cy, float x, float y)
	{
		//float x0 = commandx;
		//float y0 = commandy;
		//float vals[] = { ::nano2d::e_command_bezier_to,
		//	 x0 + 2.0f / 3.0f * (cx - x0), y0 + 2.0f / 3.0f * (cy - y0),
		//	 x + 2.0f / 3.0f * (cx - x), y + 2.0f / 3.0f * (cy - y),
		//	 x, y };
		//CONTEXT::__appendCommands)(ctx, vals, NANO2D_COUNTOF(vals));
	}

	void CONTEXT::arc_to(float x1, float y1, float x2, float y2, float radius)
	{
		//float x0 = commandx;
		//float y0 = commandy;
		//float dx0, dy0, dx1, dy1, a, d, cx, cy, a0, a1;
		//int dir;

		//if (ncommands == 0) {
		//	return;
		//}

		//// Handle degenerate cases.
		//if (CONTEXT::__ptEquals)(x0, y0, x1, y1, distTol) ||
		//	CONTEXT::__ptEquals)(x1, y1, x2, y2, distTol) ||
		//	CONTEXT::__distPtSeg)(x1, y1, x0, y0, x2, y2) < distTol * distTol ||
		//	radius < distTol) {
		//	CONTEXT::LineTo)(ctx, x1, y1);
		//	return;
		//}

		//// Calculate tangential circle to lines (x0,y0)-(x1,y1) and (x1,y1)-(x2,y2).
		//dx0 = x0 - x1;
		//dy0 = y0 - y1;
		//dx1 = x2 - x1;
		//dy1 = y2 - y1;
		//CONTEXT::__normalize)(&dx0, &dy0);
		//CONTEXT::__normalize)(&dx1, &dy1);
		//a = CONTEXT::__acosf)(dx0 * dx1 + dy0 * dy1);
		//d = radius / CONTEXT::__tanf)(a / 2.0f);

		////	printf("a=%f� d=%f\n", a/::nano2d::f_pi*180.0f, d);

		//if (d > 10000.0f) {
		//	CONTEXT::LineTo)(ctx, x1, y1);
		//	return;
		//}

		//if (CONTEXT::__cross)(dx0, dy0, dx1, dy1) > 0.0f) {
		//	cx = x1 + dx0 * d + dy0 * radius;
		//	cy = y1 + dy0 * d + -dx0 * radius;
		//	a0 = CONTEXT::__atan2f)(dx0, -dy0);
		//	a1 = CONTEXT::__atan2f)(-dx1, dy1);
		//	dir = ::nano2d::e_winding_cw;
		//	//		printf("CW c=(%f, %f) a0=%f� a1=%f�\n", cx, cy, a0/::nano2d::f_pi*180.0f, a1/::nano2d::f_pi*180.0f);
		//}
		//else {
		//	cx = x1 + dx0 * d + -dy0 * radius;
		//	cy = y1 + dy0 * d + dx0 * radius;
		//	a0 = CONTEXT::__atan2f)(-dx0, dy0);
		//	a1 = CONTEXT::__atan2f)(dx1, -dy1);
		//	dir = ::nano2d::e_winding_ccw;
		//	//		printf("CCW c=(%f, %f) a0=%f� a1=%f�\n", cx, cy, a0/::nano2d::f_pi*180.0f, a1/::nano2d::f_pi*180.0f);
		//}

		//CONTEXT::Arc)(ctx, cx, cy, radius, a0, a1, dir);
	}


	void CONTEXT::close_path()
	{
		//float vals[] = { ::nano2d::e_command_close };
		//CONTEXT::__appendCommands)(ctx, vals, NANO2D_COUNTOF(vals));
		//close_path();
	}


	void CONTEXT::path_winding(int dir)
	{
		//float vals[] = { ::nano2d::e_command_winding, (float)dir };
		//CONTEXT::__appendCommands)(ctx, vals, NANO2D_COUNTOF(vals));

		//path_winding(dir);

	}

	void CONTEXT::arc(float cx, float cy, float r, float a0, float a1, int dir)
	{
		//arc(cx, cy, r, a0, a1, dir);
		//float a = 0, da = 0, hda = 0, kappa = 0;
		//float Δx = 0, Δy = 0, x = 0, y = 0, tanx = 0, tany = 0;
		//float px = 0, py = 0, ptanx = 0, ptany = 0;
		//float vals[3 + 5 * 7 + 100];
		//int i, ndivs, nvals;
		//int transfer = ncommands > 0 ? ::nano2d::e_command_line_to : ::nano2d::e_command_move_to;

		//// Clamp angles
		//da = a1 - a0;
		//if (dir == ::nano2d::e_winding_cw) {
		//	if (CONTEXT::__absf)(da) >= ::nano2d::f_pi * 2) {
		//		da = ::nano2d::f_pi * 2;
		//	}
		//	else {
		//		while (da < 0.0f) da += ::nano2d::f_pi * 2;
		//	}
		//}
		//else {
		//	if (CONTEXT::__absf)(da) >= ::nano2d::f_pi * 2) {
		//		da = -::nano2d::f_pi * 2;
		//	}
		//	else {
		//		while (da > 0.0f) da -= ::nano2d::f_pi * 2;
		//	}
		//}

		//// Split arc into max 90 degree segments.
		//ndivs = CONTEXT::__maxi)(1, CONTEXT::__mini)((int)(CONTEXT::__absf)(da) / (::nano2d::f_pi * 0.5f) + 0.5f), 5));
		//hda = (da / (float)ndivs) / 2.0f;
		//kappa = CONTEXT::__absf)(4.0f / 3.0f * (1.0f - CONTEXT::__cosf)(hda)) / CONTEXT::__sinf)(hda));

		//if (dir == ::nano2d::e_winding_ccw)
		//	kappa = -kappa;

		//nvals = 0;
		//for (i = 0; i <= ndivs; i++) {
		//	a = a0 + da * (i / (float)ndivs);
		//	Δx = CONTEXT::__cosf)(a);
		//	Δy = CONTEXT::__sinf)(a);
		//	x = cx + Δx * r;
		//	y = cy + Δy * r;
		//	tanx = -Δy * r * kappa;
		//	tany = Δx * r * kappa;

		//	if (i == 0) {
		//		vals[nvals++] = (float)transfer;
		//		vals[nvals++] = x;
		//		vals[nvals++] = y;
		//	}
		//	else {
		//		vals[nvals++] = ::nano2d::e_command_bezier_to;
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

		//CONTEXT::__appendCommands)(ctx, vals, nvals);
	}


	void CONTEXT::double_rectangle(float x, float y, float w, float h)
	{
		//float vals[] = {
		//	::nano2d::e_command_move_to, x,y,
		//	::nano2d::e_command_line_to, x,y + h,
		//	::nano2d::e_command_line_to, x + w,y + h,
		//	::nano2d::e_command_line_to, x + w,y,
		//	::nano2d::e_command_close
		//};
		//CONTEXT::__appendCommands)(ctx, vals, NANO2D_COUNTOF(vals));
		//rect(x, y, w, h);
	}


	void CONTEXT::rounded_rectangle(float x, float y, float w, float h, float r)
	{
	//	CONTEXT::RoundedRectVarying)(ctx, x, y, w, h, r, r, r, r);

		//rounded_rect(x, y, w, h, r);

	}


	void CONTEXT::rounded_rectangle_varying(float x, float y, float w, float h, float radTopLeft, float radTopRight, float radBottomRight, float radBottomLeft)
	{
		//if (radTopLeft < 0.1f && radTopRight < 0.1f && radBottomRight < 0.1f && radBottomLeft < 0.1f) {
		//	CONTEXT::Rect)(ctx, x, y, w, h);
		//	return;
		//}
		//else {
		//	float halfw = CONTEXT::__absf)(w) * 0.5f;
		//	float halfh = CONTEXT::__absf)(h) * 0.5f;
		//	float rxBL = CONTEXT::__minf)(radBottomLeft, halfw) * CONTEXT::__signf)(w), ryBL = CONTEXT::__minf)(radBottomLeft, halfh) * CONTEXT::__signf)(h);
		//	float rxBR = CONTEXT::__minf)(radBottomRight, halfw) * CONTEXT::__signf)(w), ryBR = CONTEXT::__minf)(radBottomRight, halfh) * CONTEXT::__signf)(h);
		//	float rxTR = CONTEXT::__minf)(radTopRight, halfw) * CONTEXT::__signf)(w), ryTR = CONTEXT::__minf)(radTopRight, halfh) * CONTEXT::__signf)(h);
		//	float rxTL = CONTEXT::__minf)(radTopLeft, halfw) * CONTEXT::__signf)(w), ryTL = CONTEXT::__minf)(radTopLeft, halfh) * CONTEXT::__signf)(h);
		//	float vals[] = {
		//		::nano2d::e_command_move_to, x, y + ryTL,
		//		::nano2d::e_command_line_to, x, y + h - ryBL,
		//		::nano2d::e_command_bezier_to, x, y + h - ryBL * (1 - NANO2D_KAPPA90), x + rxBL * (1 - NANO2D_KAPPA90), y + h, x + rxBL, y + h,
		//		::nano2d::e_command_line_to, x + w - rxBR, y + h,
		//		::nano2d::e_command_bezier_to, x + w - rxBR * (1 - NANO2D_KAPPA90), y + h, x + w, y + h - ryBR * (1 - NANO2D_KAPPA90), x + w, y + h - ryBR,
		//		::nano2d::e_command_line_to, x + w, y + ryTR,
		//		::nano2d::e_command_bezier_to, x + w, y + ryTR * (1 - NANO2D_KAPPA90), x + w - rxTR * (1 - NANO2D_KAPPA90), y, x + w - rxTR, y,
		//		::nano2d::e_command_line_to, x + rxTL, y,
		//		::nano2d::e_command_bezier_to, x + rxTL * (1 - NANO2D_KAPPA90), y, x, y + ryTL * (1 - NANO2D_KAPPA90), x, y + ryTL,
		//		::nano2d::e_command_close
		//	};
		//	CONTEXT::__appendCommands)(ctx, vals, NANO2D_COUNTOF(vals));
		//}
	}

	void CONTEXT::double_ellipse(float cx, float cy, float rx, float ry)
	{
		//float vals[] = {
		//	::nano2d::e_command_move_to, cx - rx, cy,
		//	::nano2d::e_command_bezier_to, cx - rx, cy + ry * NANO2D_KAPPA90, cx - rx * NANO2D_KAPPA90, cy + ry, cx, cy + ry,
		//	::nano2d::e_command_bezier_to, cx + rx * NANO2D_KAPPA90, cy + ry, cx + rx, cy + ry * NANO2D_KAPPA90, cx + rx, cy,
		//	::nano2d::e_command_bezier_to, cx + rx, cy - ry * NANO2D_KAPPA90, cx + rx * NANO2D_KAPPA90, cy - ry, cx, cy - ry,
		//	::nano2d::e_command_bezier_to, cx - rx * NANO2D_KAPPA90, cy - ry, cx - rx, cy - ry * NANO2D_KAPPA90, cx - rx, cy,
		//	::nano2d::e_command_close
		//};
		//CONTEXT::__appendCommands)(ctx, vals, NANO2D_COUNTOF(vals));

		//ellipse(cx, cy, rx, ry);

	}


	void CONTEXT::circle(float cx, float cy, float r)
	{
		
		//CONTEXT::Ellipse)(ctx, cx, cy, r, r);

	}


	void CONTEXT::debug_dump_path_cache()
	{
		const ::nano2d::path * path;
		int i, j;

		printf("Dumping %d cached paths\n", cache->npaths);
		for (i = 0; i < cache->npaths; i++) {
			path = &cache->paths[i];
			printf(" - Path %d\n", i);
			if (path->nfill) {
				printf("   - fill: %d\n", path->nfill);
				for (j = 0; j < path->nfill; j++)
					printf("%f\t%f\n", path->fill[j].x(), path->fill[j].y());
			}
			if (path->nstroke) {
				printf("   - stroke: %d\n", path->nstroke);
				for (j = 0; j < path->nstroke; j++)
					printf("%f\t%f\n", path->stroke[j].x(), path->stroke[j].y());
			}
		}
	}


	void CONTEXT::fill()
	{

		//::nano2d::state * state = __getState();
		//const ::nano2d::path * path;
		//::nano2d::paint fillPaint = state->fill;
		//int i;

		//CONTEXT::__flattenPaths)(ctx);
		//if (params.edgeAntiAlias && state->shapeAntiAlias)
		//	CONTEXT::__expandFill)(ctx, fringeWidth, ::nano2d::e_line_join_miter, 2.4f);
		//else
		//	CONTEXT::__expandFill)(ctx, 0.0f, ::nano2d::e_line_join_miter, 2.4f);

		//// Apply global alpha
		//fillPaint.innerColor.a *= state->alpha;
		//fillPaint.outerColor.a *= state->alpha;

		//params.renderFill(params.userPtr, &fillPaint, state->compositeOperation, &state->scissor, fringeWidth,
		//	cache->bounds, cache->paths, cache->npaths);

		//// Count triangles
		//for (i = 0; i < cache->npaths; i++) {
		//	path = &cache->paths[i];
		//	fillTriCount += path->nfill - 2;
		//	fillTriCount += path->nstroke - 2;
		//	drawCallCount += 2;
		//}

		//fill();

	}


	void CONTEXT::stroke()
	{

		//stroke();


		//::nano2d::state * state = __getState();
		//float scale = CONTEXT::__getAverageScale)(state->xform);
		//float strokeWidth = CONTEXT::__clampf)(state->strokeWidth * scale, 0.0f, 200.0f);
		//::nano2d::paint strokePaint = state->stroke;
		//const ::nano2d::path * path;
		//int i;


		//if (strokeWidth < fringeWidth) {
		//	// If the stroke width is less than pixel size, use alpha to emulate coverage.
		//	// Since coverage is area, scale by alpha*alpha.
		//	float alpha = CONTEXT::__clampf)(strokeWidth / fringeWidth, 0.0f, 1.0f);
		//	strokePaint.innerColor.a *= alpha * alpha;
		//	strokePaint.outerColor.a *= alpha * alpha;
		//	strokeWidth = fringeWidth;
		//}

		//// Apply global alpha
		//strokePaint.innerColor.a *= state->alpha;
		//strokePaint.outerColor.a *= state->alpha;

		//CONTEXT::__flattenPaths)(ctx);

		//if (params.edgeAntiAlias && state->shapeAntiAlias)
		//	CONTEXT::__expandStroke)(ctx, strokeWidth * 0.5f, fringeWidth, state->lineCap, state->lineJoin, state->miterLimit);
		//else
		//	CONTEXT::__expandStroke)(ctx, strokeWidth * 0.5f, 0.0f, state->lineCap, state->lineJoin, state->miterLimit);

		//params.renderStroke(params.userPtr, &strokePaint, state->compositeOperation, &state->scissor, fringeWidth,
		//	strokeWidth, cache->paths, cache->npaths);

		//// Count triangles
		//for (i = 0; i < cache->npaths; i++) {
		//	path = &cache->paths[i];
		//	strokeTriCount += path->nstroke - 2;
		//	drawCallCount++;
		//}
	}

	// Add fonts
	//int CONTEXT::CreateFont(const char * name, const char * filename)
	//{
	//	//return fonsAddFont(fs, name, filename, 0);
	//	return -1;
	//}

	int CONTEXT::CreateFontAtIndex(const char * name, const char * filename, const int fontIndex)
	{
		//return fonsAddFont(fs, name, filename, fontIndex);
		return -1;
	}


	int CONTEXT::create_font_mem(const char * name, unsigned char * data, int ndata, int freeData)
	{
	
		//return fonsAddFontMem(fs, name, data, ndata, freeData, 0);
		return -1;

	}


	int CONTEXT::create_font_mem_at_index(const char * name, unsigned char * data, int ndata, int freeData, const int fontIndex)
	{
	
		//return fonsAddFontMem(fs, name, data, ndata, freeData, fontIndex);
		return -1;

	}


	int CONTEXT::find_font(const char * name)
	{

		//if (name == NULL) return -1;
		//return fonsGetFontByName(fs, name);
		return -1;

	}


	int CONTEXT::add_fallback_font_id(int baseFont, int fallbackFont)
	{
		//if (baseFont == -1 || fallbackFont == -1) return 0;
		//return fonsAddFallbackFont(fs, baseFont, fallbackFont);
		return -1;
	}

	
	int CONTEXT::add_fallback_font(const char * baseFont, const char * fallbackFont)
	{
		//return CONTEXT::AddFallbackFontId)(ctx, CONTEXT::FindFont)(ctx, baseFont), CONTEXT::FindFont)(ctx, fallbackFont));
		return -1;
	}


	void CONTEXT::reset_fallback_fonts_id(int baseFont)
	{
		//fonsResetFallbackFont(fs, baseFont);
		return;
	}


	void CONTEXT::reset_fallback_fonts(const char * baseFont)
	{
		//CONTEXT::ResetFallbackFontsId)(ctx, CONTEXT::FindFont)(ctx, baseFont));
		return;
	}


	// State setting
	void CONTEXT::font_size(float size)
	{
		//::nano2d::state * state = __getState();
		//state->fontSize = size;
		//font_size(size);

	}

	
	void CONTEXT::font_blur(float blur)
	{
		
		//::nano2d::state * state = __getState();
		//state->fontBlur = blur;
		//throw_todo();
		//font_blur(blur);

	}


	//::write_text::font_pointer CONTEXT::CreateFont(const char * face, float size)
	//{
	//   
	//   return create_font(face, size);
	//   
	//}


	void CONTEXT::text_letter_spacing(float spacing)
	{
		
		//::nano2d::state * state = __getState();
		//state->letterSpacing = spacing;
		throw_todo();

	}

	
	void CONTEXT::text_line_height(float lineHeight)
	{
		//::nano2d::state * state = __getState();
		//state->lineHeight = lineHeight;
		//text_line_height(lineHeight);

	}

	
	void CONTEXT::text_align(int align)
	{

		//::nano2d::state * state = __getState();
		//state->textAlign = align;

		//text_align(align);

	}


	void CONTEXT::font_face_id(int font)
	{
	
		//::nano2d::state * state = __getState();
		//state->fontId = font;
		throw_todo();

	}


	void CONTEXT::font_face(const char * font)
	{
		//::nano2d::state * state = __getState();
		//state->fontId = fonsGetFontByName(fs, font);

		//font_face(font);

	}


	//static float CONTEXT::__quantize)(float a, float d)
	//{
	//	return ((int)(a / d + 0.5f)) * d;
	//}

	//static float CONTEXT::__getFontScale)(::nano2d::state * state)
	//{
	//	return CONTEXT::__minf)(CONTEXT::__quantize)(CONTEXT::__getAverageScale)(state->xform), 0.01f), 4.0f);
	//}

	//static void CONTEXT::__flushTextTexture()
	//{
	//	//int dirty[4];
	//
	//	//if (fonsValidateTexture(fs, dirty)) {
	//	//	int fontImage = fontImages[fontImageIdx];
	//	//	// Update texture
	//	//	if (fontImage != 0) {
	//	//		int iw, ih;
	//	//		const unsigned char * data = fonsGetTextureData(fs, &iw, &ih);
	//	//		int x = dirty[0];
	//	//		int y = dirty[1];
	//	//		int w = dirty[2] - dirty[0];
	//	//		int h = dirty[3] - dirty[1];
	//	//		params.renderUpdateTexture(params.userPtr, fontImage, x, y, w, h, data);
	//	//	}
	//	//}
	//}

	//static int CONTEXT::__allocTextAtlas()
	//{
	//	//int iw, ih;
	//	//CONTEXT::__flushTextTexture)(ctx);
	//	//if (fontImageIdx >= NVG_MAX_FONTIMAGES - 1)
	//	//	return 0;
	//	//// if next fontImage already have a texture
	//	//if (fontImages[fontImageIdx + 1] != 0)
	//	//	CONTEXT::ImageSize)(ctx, fontImages[fontImageIdx + 1], &iw, &ih);
	//	//else { // calculate the aaa_primitive_new font image size and create it.
	//	//	CONTEXT::ImageSize)(ctx, fontImages[fontImageIdx], &iw, &ih);
	//	//	if (iw > ih)
	//	//		ih *= 2;
	//	//	else
	//	//		iw *= 2;
	//	//	if (iw > NVG_MAX_FONTIMAGE_SIZE || ih > NVG_MAX_FONTIMAGE_SIZE)
	//	//		iw = ih = NVG_MAX_FONTIMAGE_SIZE;
	//	//	fontImages[fontImageIdx + 1] = params.renderCreateTexture(params.userPtr, NVG_TEXTURE_ALPHA, iw, ih, 0, NULL);
	//	//}
	//	//++fontImageIdx;
	//	//fonsResetAtlas(fs, iw, ih);
	//	throw_todo();
	//	return 1;
	//}
	//
	//static void CONTEXT::__renderText(NVGvertex * verts, int nverts)
	//{
	//	//::nano2d::state * state = __getState();
	//	//::nano2d::paint paint = state->fill;
	//
	//	//// Render triangles.
	//	//paint.image = fontImages[fontImageIdx];
	//
	//	//// Apply global alpha
	//	//paint.innerColor.a *= state->alpha;
	//	//paint.outerColor.a *= state->alpha;
	//
	//	//params.renderTriangles(params.userPtr, &paint, state->compositeOperation, &state->scissor, verts, nverts, fringeWidth);
	//
	//	//drawCallCount++;
	//	//textTriCount += nverts / 3;
	//	throw_todo();
	//}
	//
	//static int CONTEXT::__isTransformFlipped)(const float * xform)
	//{
	//	/*float det = xform[0] * xform[3] - xform[2] * xform[1];
	//	return(det < 0);*/
	//	throw_todo();
	//	return -1;
	//}
	//
	float CONTEXT::Text(float x, float y, const char * string, const char * end)
	{

		//::nano2d::state * state = __getState();
		//FONStextIter iter, prevIter;
		//FONSquad q;
		//NVGvertex * verts;
		//float scale = CONTEXT::__getFontScale)(state) * devicePxRatio;
		//float invscale = 1.0f / scale;
		//int cverts = 0;
		//int nverts = 0;
		//int isFlipped = CONTEXT::__isTransformFlipped)(state->xform);

		//if (end == NULL)
		//	end = string + strlen(string);

		//if (state->fontId == FONS_INVALID) return x;

		//fonsSetSize(fs, state->fontSize * scale);
		//fonsSetSpacing(fs, state->letterSpacing * scale);
		//fonsSetBlur(fs, state->fontBlur * scale);
		//fonsSetAlign(fs, state->textAlign);
		//fonsSetFont(fs, state->fontId);

		//cverts = CONTEXT::__maxi)(2, (int)(end - string)) * 6; // conservative estimate.
		//verts = CONTEXT::__allocTempVerts)(ctx, cverts);
		//if (verts == NULL) return x;

		//fonsTextIterInit(fs, &iter, x * scale, y * scale, string, end, FONS_GLYPH_BITMAP_REQUIRED);
		//prevIter = iter;
		//while (fonsTextIterNext(fs, &iter, &q)) {
		//	float c[4 * 2];
		//	if (iter.prevGlyphIndex == -1) { // can not retrieve glyph?
		//		if (nverts != 0) {
		//			CONTEXT::__renderText)(ctx, verts, nverts);
		//			nverts = 0;
		//		}
		//		if (!CONTEXT::__allocTextAtlas)(ctx))
		//			break; // no memory :(
		//		iter = prevIter;
		//		fonsTextIterNext(fs, &iter, &q); // try again
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
		//	transform_point(&c[0], &c[1], state->xform, q.x0 * invscale, q.y0 * invscale);
		//	transform_point(&c[2], &c[3], state->xform, q.x1 * invscale, q.y0 * invscale);
		//	transform_point(&c[4], &c[5], state->xform, q.x1 * invscale, q.y1 * invscale);
		//	transform_point(&c[6], &c[7], state->xform, q.x0 * invscale, q.y1 * invscale);
		//	// Create triangles
		//	if (nverts + 6 <= cverts) {
		//		CONTEXT::__vset)(&verts[nverts], c[0], c[1], q.s0, q.t0); nverts++;
		//		CONTEXT::__vset)(&verts[nverts], c[4], c[5], q.s1, q.t1); nverts++;
		//		CONTEXT::__vset)(&verts[nverts], c[2], c[3], q.s1, q.t0); nverts++;
		//		CONTEXT::__vset)(&verts[nverts], c[0], c[1], q.s0, q.t0); nverts++;
		//		CONTEXT::__vset)(&verts[nverts], c[6], c[7], q.s0, q.t1); nverts++;
		//		CONTEXT::__vset)(&verts[nverts], c[4], c[5], q.s1, q.t1); nverts++;
		//	}
		//}

		//// TODO: add back-end bit to do this just once per frame.
		//CONTEXT::__flushTextTexture)(ctx);

		//CONTEXT::__renderText)(ctx, verts, nverts);

		//return iter.nextx / scale;

		//return text(x, y, string, end);
		return 0.f;

	}


	void CONTEXT::text_box(float x, float y, float breakRowWidth, const char * string, const char * end)
	{

		//text(x, y, string, end);
		// throw_todo();
		//::nano2d::state * state = __getState();
		//::nano2d::text_row rows[2];
		//int nrows = 0, i;
		//int oldAlign = state->textAlign;
		//int haling = state->textAlign & (::nano2d::e_align_left | ::nano2d::e_align_center | ::nano2d::e_align_right);
		//int valign = state->textAlign & (::nano2d::e_align_top | ::nano2d::e_align_middle | ::nano2d::e_align_bottom | ::nano2d::e_align_baseline);
		//float lineh = 0;

		//if (state->fontId == FONS_INVALID) return;

		//CONTEXT::TextMetrics)(ctx, NULL, NULL, &lineh);

		//state->textAlign = ::nano2d::e_align_left | valign;

		//while ((nrows = CONTEXT::TextBreakLines)(ctx, string, end, breakRowWidth, rows, 2))) {
		//	for (i = 0; i < nrows; i++) {
		//		::nano2d::text_row * row = &rows[i];
		//		if (haling & ::nano2d::e_align_left)
		//			CONTEXT::Text)(ctx, x, y, row->start, row->end);
		//		else if (haling & ::nano2d::e_align_center)
		//			CONTEXT::Text)(ctx, x + breakRowWidth * 0.5f - row->width * 0.5f, y, row->start, row->end);
		//		else if (haling & ::nano2d::e_align_right)
		//			CONTEXT::Text)(ctx, x + breakRowWidth - row->width, y, row->start, row->end);
		//		y += lineh * state->lineHeight;
		//	}
		//	string = rows[nrows - 1].next;
		//}

		//state->textAlign = oldAlign;
	}


	int CONTEXT::text_glyph_positions(float x, float y, const char * string, const char * end, ::nano2d::glyphPosition * positions, int maxPositions)
	{

		return text_glyph_positions(x, y, string, end, positions, maxPositions);

		//throw_todo();
		//return -1;
		//::nano2d::state * state = __getState();
		//float scale = CONTEXT::__getFontScale)(state) * devicePxRatio;
		//float invscale = 1.0f / scale;
		//FONStextIter iter, prevIter;
		//FONSquad q;
		//int npos = 0;

		//if (state->fontId == FONS_INVALID) return 0;

		//if (end == NULL)
		//	end = string + strlen(string);

		//if (string == end)
		//	return 0;

		//fonsSetSize(fs, state->fontSize * scale);
		//fonsSetSpacing(fs, state->letterSpacing * scale);
		//fonsSetBlur(fs, state->fontBlur * scale);
		//fonsSetAlign(fs, state->textAlign);
		//fonsSetFont(fs, state->fontId);

		//fonsTextIterInit(fs, &iter, x * scale, y * scale, string, end, FONS_GLYPH_BITMAP_OPTIONAL);
		//prevIter = iter;
		//while (fonsTextIterNext(fs, &iter, &q)) {
		//	if (iter.prevGlyphIndex < 0 && CONTEXT::__allocTextAtlas)(ctx)) { // can not retrieve glyph?
		//		iter = prevIter;
		//		fonsTextIterNext(fs, &iter, &q); // try again
		//	}
		//	prevIter = iter;
		//	positions[npos].str = iter.str;
		//	positions[npos].x() = iter.x() * invscale;
		//	positions[npos].minx = CONTEXT::__minf)(iter.x(), q.x0) * invscale;
		//	positions[npos].maxx = CONTEXT::__maxf)(iter.nextx, q.x1) * invscale;
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


	int CONTEXT::text_break_lines(const char * string, const char * end, float breakRowWidth, ::nano2d::text_row * rows, int maxRows)
	{

		throw_todo();
		return -1;
		//::nano2d::state * state = __getState();
		//float scale = CONTEXT::__getFontScale)(state) * devicePxRatio;
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

		//fonsSetSize(fs, state->fontSize * scale);
		//fonsSetSpacing(fs, state->letterSpacing * scale);
		//fonsSetBlur(fs, state->fontBlur * scale);
		//fonsSetAlign(fs, state->textAlign);
		//fonsSetFont(fs, state->fontId);

		//breakRowWidth *= scale;

		//fonsTextIterInit(fs, &iter, 0, 0, string, end, FONS_GLYPH_BITMAP_OPTIONAL);
		//prevIter = iter;
		//while (fonsTextIterNext(fs, &iter, &q)) {
		//	if (iter.prevGlyphIndex < 0 && CONTEXT::__allocTextAtlas)(ctx)) { // can not retrieve glyph?
		//		iter = prevIter;
		//		fonsTextIterNext(fs, &iter, &q); // try again
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
		//		// Always handle aaa_primitive_new lines.
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
		//				rowStartX = iter.x();
		//				rowStart = iter.str;
		//				rowEnd = iter.next;
		//				rowWidth = iter.nextx - rowStartX;
		//				rowMinX = q.x0 - rowStartX;
		//				rowMaxX = q.x1 - rowStartX;
		//				wordStart = iter.str;
		//				wordStartX = iter.x();
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
		//				wordStartX = iter.x();
		//				wordMinX = q.x0;
		//			}

		//			// Break to aaa_primitive_new line when a character is beyond break width.
		//			if ((type == NVG_CHAR || type == NVG_CJK_CHAR) && nextWidth > breakRowWidth) {
		//				// The run length is too long, need to break to aaa_primitive_new line.
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
		//					rowStartX = iter.x();
		//					rowStart = iter.str;
		//					rowEnd = iter.next;
		//					rowWidth = iter.nextx - rowStartX;
		//					rowMinX = q.x0 - rowStartX;
		//					rowMaxX = q.x1 - rowStartX;
		//					wordStart = iter.str;
		//					wordStartX = iter.x();
		//					wordMinX = q.x0 - rowStartX;
		//				}
		//				else {
		//					// Break the line from the end of the last word, and start aaa_primitive_new line from the beginning of the aaa_primitive_new.
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

		//// Break the line from the end of the last word, and start aaa_primitive_new line from the beginning of the aaa_primitive_new.
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


	float CONTEXT::text_bounds(float x, float y, const char * string, const char * end, float * bounds)
	{

		//return text_bounds(x, y, string, end, bounds);
		//::nano2d::state * state = __getState();
		//float scale = CONTEXT::__getFontScale)(state) * devicePxRatio;
		//float invscale = 1.0f / scale;
		//float width;

		//if (state->fontId == FONS_INVALID) return 0;

		//fonsSetSize(fs, state->fontSize * scale);
		//fonsSetSpacing(fs, state->letterSpacing * scale);
		//fonsSetBlur(fs, state->fontBlur * scale);
		//fonsSetAlign(fs, state->textAlign);
		//fonsSetFont(fs, state->fontId);

		//width = fonsTextBounds(fs, x * scale, y * scale, string, end, bounds);
		//if (bounds != NULL) {
		//	// Use line bounds for height.
		//	fonsLineBounds(fs, y * scale, &bounds[1], &bounds[3]);
		//	bounds[0] *= invscale;
		//	bounds[1] *= invscale;
		//	bounds[2] *= invscale;
		//	bounds[3] *= invscale;
		//}
		//return width * invscale;
	}

	void CONTEXT::text_box_bounds(float x, float y, float breakRowWidth, const char * string, const char * end, float * bounds)
	{

		//text_bounds(x, y, string, end, bounds);

	//
	//	//::nano2d::state * state = __getState();
	//	::nano2d::text_row rows[2];
	//	float scale = CONTEXT::__getFontScale)(state) * devicePxRatio;
	//	float invscale = 1.0f / scale;
	//	int nrows = 0, i;
	//	int oldAlign = state->textAlign;
	//	int haling = state->textAlign & (::nano2d::e_align_left | ::nano2d::e_align_center | ::nano2d::e_align_right);
	//	int valign = state->textAlign & (::nano2d::e_align_top | ::nano2d::e_align_middle | ::nano2d::e_align_bottom | ::nano2d::e_align_baseline);
	//	float lineh = 0, rminy = 0, rmaxy = 0;
	//	float minx, miny, maxx, maxy;
	//
	//	if (state->fontId == FONS_INVALID) {
	//		if (bounds != NULL)
	//			bounds[0] = bounds[1] = bounds[2] = bounds[3] = 0.0f;
	//		return;
	//	}
	//
	//	CONTEXT::TextMetrics)(ctx, NULL, NULL, &lineh);
	//
	//	state->textAlign = ::nano2d::e_align_left | valign;
	//
	//	minx = maxx = x;
	//	miny = maxy = y;
	//
	//	fonsSetSize(fs, state->fontSize * scale);
	//	fonsSetSpacing(fs, state->letterSpacing * scale);
	//	fonsSetBlur(fs, state->fontBlur * scale);
	//	fonsSetAlign(fs, state->textAlign);
	//	fonsSetFont(fs, state->fontId);
	//	fonsLineBounds(fs, 0, &rminy, &rmaxy);
	//	rminy *= invscale;
	//	rmaxy *= invscale;
	//
	//	while ((nrows = CONTEXT::TextBreakLines)(ctx, string, end, breakRowWidth, rows, 2))) {
	//		for (i = 0; i < nrows; i++) {
	//			::nano2d::text_row * row = &rows[i];
	//			float rminx, rmaxx, Δx = 0;
	//			// Horizontal bounds
	//			if (haling & ::nano2d::e_align_left)
	//				Δx = 0;
	//			else if (haling & ::nano2d::e_align_center)
	//				Δx = breakRowWidth * 0.5f - row->width * 0.5f;
	//			else if (haling & ::nano2d::e_align_right)
	//				Δx = breakRowWidth - row->width;
	//			rminx = x + row->minx + Δx;
	//			rmaxx = x + row->maxx + Δx;
	//			minx = CONTEXT::__minf)(minx, rminx);
	//			maxx = CONTEXT::__maxf)(maxx, rmaxx);
	//			// Vertical bounds.
	//			miny = CONTEXT::__minf)(miny, y + rminy);
	//			maxy = CONTEXT::__maxf)(maxy, y + rmaxy);
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

	void CONTEXT::text_metrics(float * ascender, float * descender, float * lineh)
	{
		//::nano2d::state * state = __getState();
		//float scale = CONTEXT::__getFontScale)(state) * devicePxRatio;
		//float invscale = 1.0f / scale;

		//if (state->fontId == FONS_INVALID) return;

		//fonsSetSize(fs, state->fontSize * scale);
		//fonsSetSpacing(fs, state->letterSpacing * scale);
		//fonsSetBlur(fs, state->fontBlur * scale);
		//fonsSetAlign(fs, state->textAlign);
		//fonsSetFont(fs, state->fontId);

		//fonsVertMetrics(fs, ascender, descender, lineh);
		//if (ascender != NULL)
		//	*ascender *= invscale;
		//if (descender != NULL)
		//	*descender *= invscale;
		//if (lineh != NULL)
		//	*lineh *= invscale;
	}

	// vim: ft=c nu noet ts=4


} // namespace nano2d



