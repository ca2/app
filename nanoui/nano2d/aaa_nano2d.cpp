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
	//	::i32 shapeAntiAlias;
	//	::nano2d::paint fill;
	//	::nano2d::paint stroke;
	//	::f32 strokeWidth;
	//	::f32 miterLimit;
	//	::i32 lineJoin;
	//	::i32 lineCap;
	//	::f32 alpha;
	//	::f32 xform[6];
	//	NVGscissor scissor;
	//	::f32 fontSize;
	//	::f32 letterSpacing;
	//	::f32 lineHeight;
	//	::f32 fontBlur;
	//	::i32 textAlign;
	//	::i32 fontId;
	//};
	//typedef struct ::nano2d::state ::nano2d::state;
	//
	//struct NVGpoint {
	//	::f32 x, y;
	//	::f32 Δx, Δy;
	//	::f32 len;
	//	::f32 dmx, dmy;
	//	::u8 flags;
	//};
	//typedef struct NVGpoint NVGpoint;
	//
	//struct NVGpathCache {
	//	NVGpoint * points;
	//	::i32 npoints;
	//	::i32 cpoints;
	//	::nano2d::path * paths;
	//	::i32 npaths;
	//	::i32 cpaths;
	//	NVGvertex * verts;
	//	::i32 nverts;
	//	::i32 cverts;
	//	::f32 bounds[4];
	//};
	//typedef struct NVGpathCache NVGpathCache;

	//struct NANO2D_CONTEXT {
	//	NVGparams params;
	//	::f32 * commands;
	//	::i32 ccommands;
	//	::i32 ncommands;
	//	::f32 commandx, commandy;
	//	::nano2d::state states[NVG_MAX_STATES];
	//	::i32 nstates;
	//	NVGpathCache * cache;
	//	::f32 tessTol;
	//	::f32 distTol;
	//	::f32 fringeWidth;
	//	::f32 devicePxRatio;
	//	struct FONScontext * fs;
	//	::i32 fontImages[NVG_MAX_FONTIMAGES];
	//	::i32 fontImageIdx;
	//	::i32 drawCallCount;
	//	::i32 fillTriCount;
	//	::i32 strokeTriCount;
	//	::i32 textTriCount;
	//};

	static ::f32 __sqrtf(::f32 a) { return sqrtf(a); }
	//static ::f32 __modf(::f32 a, ::f32 b) { return fmodf(a, b); }
	static ::f32 __sinf(::f32 a) { return sinf(a); }
	static ::f32 __cosf(::f32 a) { return cosf(a); }
	static ::f32 __tanf(::f32 a) { return tanf(a); }
	static ::f32 __atan2f(::f32 a, ::f32 b) { return atan2f(a, b); }
	static ::f32 __acosf(::f32 a) { return acosf(a); }

	//static ::i32 __mini(::i32 a, ::i32 b) { return a < b ? a : b; }
	//static ::i32 __maxi(::i32 a, ::i32 b) { return a > b ? a : b; }
	//static ::i32 __clampi(::i32 a, ::i32 mn, ::i32 mx) { return a < mn ? mn : (a > mx ? mx : a); }
	static ::f32 __minf(::f32 a, ::f32 b) { return a < b ? a : b; }
	static ::f32 __maxf(::f32 a, ::f32 b) { return a > b ? a : b; }
	static ::f32 __absf(::f32 a) { return a >= 0.0f ? a : -a; }
	static ::f32 __signf(::f32 a) { return a >= 0.0f ? 1.0f : -1.0f; }
	//static ::f32 __clampf(::f32 a, ::f32 mn, ::f32 mx) { return a < mn ? mn : (a > mx ? mx : a); }
	static ::f32 __cross(::f32 dx0, ::f32 dy0, ::f32 dx1, ::f32 dy1) { return dx1 * dy0 - dx0 * dy1; }

	static ::f32 __normalize(::f32 * x, ::f32 * y)
	{
		::f32 d = __sqrtf((*x) * (*x) + (*y) * (*y));
		if (d > 1e-6f) {
			::f32 id = 1.0f / d;
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

	//static void CONTEXT::__setDevicePixelRatio(::f32 ratio)
	//{
	//	tessTol = 0.25f / ratio;
	//	distTol = 0.01f / ratio;
	//	fringeWidth = 1.0f / ratio;
	//	devicePxRatio = ratio;
	//}

	static ::nano2d::compositeOperationState __compositeOperationState(::i32 op)
	{
		::i32 sfactor, dfactor;

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
	//	::i32 i;
	//	if (ctx == NULL) goto error;
	//	::memory_set(ctx, 0, sizeof(NANO2D_CONTEXT));
	//
	//	params = *params;
	//	for (i = 0; i < NVG_MAX_FONTIMAGES; i++)
	//		fontImages[i] = 0;
	//
	//	commands = (::f32 *)malloc(sizeof(::f32) * NVG_INIT_COMMANDS_SIZE);
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
	//	::i32 i;
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
	//void CONTEXT::BeginFrame(::f32 windowWidth, ::f32 windowHeight, ::f32 devicePixelRatio)
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
	//		::i32 fontImage = fontImages[fontImageIdx];
	//		::i32 i, j, iw, ih;
	//		// delete images that smaller than current one
	//		if (fontImage == 0)
	//			return;
	//		CONTEXT::ImageSize)(ctx, fontImage, &iw, &ih);
	//		for (i = j = 0; i < fontImageIdx; i++) {
	//			if (fontImages[i] != 0) {
	//				::i32 nw, nh;
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

	//::nano2d::color CONTEXT::RGB(::u8 r, ::u8 g, ::u8 b)
::nano2d::color RGB(::u8 r, ::u8 g, ::u8 b)
	{
		///return CONTEXT::RGBA)(r, g, b, 255);
		return { r / 255.f, g / 255.f, b / 255.f, 1.0f };
	}

	//::nano2d::color CONTEXT::RGBf)(::f32 r, ::f32 g, ::f32 b)
::nano2d::color RGBf(::f32 r, ::f32 g, ::f32 b)
	{
		//return CONTEXT::RGBAf)(r, g, b, 1.0f);
		return { r , g, b, 1.0f };
	}

	//::nano2d::color CONTEXT::RGBA)(::u8 r, ::u8 g, ::u8 b, ::u8 a)
::nano2d::color RGBA(::u8 r, ::u8 g, ::u8 b, ::u8 a)
	{
		::nano2d::color color;
		// Use longer initialization to suppress warning.
		color.r = r / 255.0f;
		color.g = g / 255.0f;
		color.b = b / 255.0f;
		color.a = a / 255.0f;
		return color;
	}

	//::nano2d::color CONTEXT::RGBAf)(::f32 r, ::f32 g, ::f32 b, ::f32 a)
::nano2d::color RGBAf(::f32 r, ::f32 g, ::f32 b, ::f32 a)
	{
		::nano2d::color color;
		// Use longer initialization to suppress warning.
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
		return color;
	}

	//::nano2d::color CONTEXT::TransRGBA)(::nano2d::color c, ::u8 a)
::nano2d::color TransRGBA(::nano2d::color c, ::u8 a)
	{
		c.a = a / 255.0f;
		return c;
	}

	//::nano2d::color CONTEXT::TransRGBAf)(::nano2d::color c, ::f32 a)
::nano2d::color TransRGBAf(::nano2d::color c, ::f32 a)
	{
		c.a = a;
		return c;
	}

	//::nano2d::color CONTEXT::LerpRGBA)(::nano2d::color c0, ::nano2d::color c1, ::f32 u)
	//{
	//	::i32 i;
	//	::f32 oneminu;
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

	//::nano2d::color CONTEXT::HSL)(::f32 h, ::f32 s, ::f32 l)
::nano2d::color HSL(::f32 h, ::f32 s, ::f32 l)
	{
		//return CONTEXT::HSLA)(h, s, l, 255);
		::color::color color;

		color.set_hls(h, l, s);
		return { color.fr(), color.fg(), color.fb(), color.fa() };

	}

	//static ::f32 CONTEXT::__hue)(::f32 h, ::f32 m1, ::f32 m2)
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

	//::nano2d::color CONTEXT::HSLA)(::f32 h, ::f32 s, ::f32 l, ::u8 a)
::nano2d::color HSLA(::f32 h, ::f32 s, ::f32 l, ::u8 a)
	{
		//::f32 m1, m2;
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

	//void CONTEXT::TransformIdentity)(::f32 * t)
void TransformIdentity(::f32* t)
	{
		t[0] = 1.0f; t[1] = 0.0f;
		t[2] = 0.0f; t[3] = 1.0f;
		t[4] = 0.0f; t[5] = 0.0f;
	}

	//void CONTEXT::TransformTranslate)(::f32 * t, ::f32 tx, ::f32 ty)
void TransformTranslate(::f32* t, ::f32 tx, ::f32 ty)
	{
		t[0] = 1.0f; t[1] = 0.0f;
		t[2] = 0.0f; t[3] = 1.0f;
		t[4] = tx; t[5] = ty;
	}

	//void CONTEXT::TransformScale)(::f32 * t, ::f32 sx, ::f32 sy)
void TransformScale(::f32* t, ::f32 sx, ::f32 sy)
	{
		t[0] = sx; t[1] = 0.0f;
		t[2] = 0.0f; t[3] = sy;
		t[4] = 0.0f; t[5] = 0.0f;
	}

	//void CONTEXT::TransformRotate)(::f32 * t, ::f32 a)
void TransformRotate(::f32* t, ::f32 a)
	{
		::f32 cs = __cosf(a);
		::f32 sn = __sinf(a);
		t[0] = cs; t[1] = sn;
		t[2] = -sn; t[3] = cs;
		t[4] = 0.0f; t[5] = 0.0f;
	}

	//void CONTEXT::TransformSkewX)(::f32 * t, ::f32 a)
void TransformSkewX(::f32* t, ::f32 a)
	{
		t[0] = 1.0f; t[1] = 0.0f;
		t[2] = __tanf(a); t[3] = 1.0f;
		t[4] = 0.0f; t[5] = 0.0f;
	}

	void TransformSkewY(::f32 * t, ::f32 a)
	{
		t[0] = 1.0f; t[1] = __tanf(a);
		t[2] = 0.0f; t[3] = 1.0f;
		t[4] = 0.0f; t[5] = 0.0f;
	}

	//void CONTEXT::TransformMultiply)(::f32 * t, const ::f32 * s)
	void TransformMultiply(::f32* t, const ::f32* s)
	{
		::f32 t0 = t[0] * s[0] + t[1] * s[2];
		::f32 t2 = t[2] * s[0] + t[3] * s[2];
		::f32 t4 = t[4] * s[0] + t[5] * s[2] + s[4];
		t[1] = t[0] * s[1] + t[1] * s[3];
		t[3] = t[2] * s[1] + t[3] * s[3];
		t[5] = t[4] * s[1] + t[5] * s[3] + s[5];
		t[0] = t0;
		t[2] = t2;
		t[4] = t4;
	}

	//void CONTEXT::TransformPremultiply)(::f32 * t, const ::f32 * s)
	void TransformPremultiply(::f32* t, const ::f32* s)
	{
		::f32 s2[6];
		::memory_copy(s2, s, sizeof(::f32) * 6);
		TransformMultiply(s2, t);
		::memory_copy(t, s2, sizeof(::f32) * 6);
	}

	//::i32 CONTEXT::TransformInverse)(::f32 * inv, const ::f32 * t)
		::i32 TransformInverse(::f32* inv, const ::f32* t)
	{
		::f64 invdet, det = (::f64)t[0] * t[3] - (::f64)t[2] * t[1];
		if (det > -1e-6 && det < 1e-6) {
			TransformIdentity(inv);
			return 0;
		}
		invdet = 1.0 / det;
		inv[0] = (::f32)(t[3] * invdet);
		inv[2] = (::f32)(-t[2] * invdet);
		inv[4] = (::f32)(((::f64)t[2] * t[5] - (::f64)t[3] * t[4]) * invdet);
		inv[1] = (::f32)(-t[1] * invdet);
		inv[3] = (::f32)(t[0] * invdet);
		inv[5] = (::f32)(((::f64)t[1] * t[4] - (::f64)t[0] * t[5]) * invdet);
		return 1;
	}

	//void transform_point(::f32 * Δx, ::f32 * Δy, const ::f32 * t, ::f32 sx, ::f32 sy)
		void transform_point(::f32* Δx, ::f32* Δy, const ::f32* t, ::f32 sx, ::f32 sy)
	{
		*Δx = sx * t[0] + sy * t[2] + t[4];
		*Δy = sx * t[1] + sy * t[3] + t[5];
	}

	//::f32 CONTEXT::DegToRad)(::f32 deg)
		::f32 DegToRad(::f32 deg)
	{
		return deg / 180.0f * ::nano2d::f_pi;
	}

	//::f32 CONTEXT::RadToDeg)(::f32 rad)
		::f32 RadToDeg(::f32 rad)
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
	void CONTEXT::shape_anti_alias(::i32 enabled)
	{
		::nano2d::state * state = __getState();
		state->shapeAntiAlias = enabled;
	}

	void CONTEXT::stroke_width(::f32 width)
	{
		//::nano2d::state * state = __getState();
		//state->strokeWidth = width;
		//return stroke_width(width);
	}


	void CONTEXT::miter_limit(::f32 limit)
	{

		::nano2d::state * state = __getState();

		state->miterLimit = limit;

	}


	void CONTEXT::line_cap(::i32 cap)
	{

		::nano2d::state * state = __getState();

		state->lineCap = cap;

	}


	void CONTEXT::line_join(::i32 join)
	{

		::nano2d::state * state = __getState();

		state->lineJoin = join;

	}


	void CONTEXT::global_alpha(::f32 alpha)
	{

		//::nano2d::state * state = __getState();
		//state->alpha = alpha;
		//global_alpha(alpha);

	}


	void CONTEXT::transform(::f32 a, ::f32 b, ::f32 c, ::f32 d, ::f32 e, ::f32 f)
	{
		
		::nano2d::state * state = __getState();

		::f32 t[6] = { a, b, c, d, e, f };

		TransformPremultiply(state->xform, t);

	}


	void CONTEXT::reset_transform()
	{

		::nano2d::state * state = __getState();

		TransformIdentity(state->xform);

	}


	void CONTEXT::translate(::f32 x, ::f32 y)
	{
		//::nano2d::state * state = __getState();
		//::f32 t[6];
		//CONTEXT::TransformTranslate)(t, x, y);
		//CONTEXT::TransformPremultiply)(state->xform, t);

		//translate(x, y);

	}

	
	void CONTEXT::rotate(::f32 angle)
	{
		
		//::nano2d::state * state = __getState();
		//::f32 t[6];
		//CONTEXT::TransformRotate)(t, angle);
		//CONTEXT::TransformPremultiply)(state->xform, t);
		//rotate(angle);

	}


	void CONTEXT::skew_x(::f32 angle)
	{
		::nano2d::state * state = __getState();
		::f32 t[6];
		TransformSkewX(t, angle);
		TransformPremultiply(state->xform, t);
	}

	void CONTEXT::skew_y(::f32 angle)
	{
		::nano2d::state * state = __getState();
		::f32 t[6];
		TransformSkewY(t, angle);
		TransformPremultiply(state->xform, t);
	}

	void CONTEXT::scale(::f32 x, ::f32 y)
	{
		::nano2d::state * state = __getState();
		::f32 t[6];
		TransformScale(t, x, y);
		TransformPremultiply(state->xform, t);
	}


	void CONTEXT::current_transform(::f32 * xform)
	{
		::nano2d::state * state = __getState();
		if (xform == NULL) return;
		::memory_copy(xform, state->xform, sizeof(::f32) * 6);
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
	::i32 CONTEXT::create_image(const ::scoped_string& scopedstrFilename, ::i32 imageFlags)
	{
		//::i32 w, h, n, image;
		//::u8 * img;
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


	::i32 CONTEXT::create_image_mem(::i32 imageFlags, ::u8 * data, ::i32 ndata)
	{
		//::i32 w, h, n, image;
		//::u8 * img = stbi_load_from_memory(data, ndata, &w, &h, &n, 4);
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

	
	::i32 CONTEXT::create_image_rgba(::i32 w, ::i32 h, ::i32 imageFlags, const void * data, ::i32 iScan)
	{
		//return params.renderCreateTexture(params.userPtr, NVG_TEXTURE_RGBA, w, h, imageFlags, data);
		//return create_image_rgba(w, h, imageFlags, data, iScan);

		return -1;

	}


	void CONTEXT::update_image(::i32 image, const void * data)
	{
		//::i32 w h;
		//params.renderGetTextureSize(params.userPtr, image, &w, &h);
		//params.renderUpdateTexture(params.userPtr, image, 0, 0, w, h, data);
		//return update_image(image, data);

		//re

	}


	void CONTEXT::image_size(::i32 image, ::i32 * w, ::i32 * h)
	{
		//params.renderGetTextureSize(params.userPtr, image, w, h);

		//image_size(image, w, h);

	}


	void CONTEXT::delete_image(::i32 image)
	{
	
		//params.renderDeleteTexture(params.userPtr, image);

	}

	
	::nano2d::paint CONTEXT::linear_gradient(
		::f32 sx, ::f32 sy, ::f32 ex, ::f32 ey,
		::nano2d::color icol, ::nano2d::color ocol)
	{

		//return linear_gradient(sx, sy, ex, ey, icol, ocol);
		//::nano2d::paint p;
		//::f32 Δx, Δy, d;
		//const ::f32 large = 1e5;
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
		::f32 cx, ::f32 cy, ::f32 inr, ::f32 outr,
		::nano2d::color icol, ::nano2d::color ocol)
	{

		return {};


		//return radial_gradient(cx, cy, inr, outr, icol, ocol);
		//::nano2d::paint p;
		//::f32 r = (inr + outr) * 0.5f;
		//::f32 f = (outr - inr);
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
		::f32 x, ::f32 y, ::f32 w, ::f32 h, ::f32 r, ::f32 f,
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


	::nano2d::paint CONTEXT::image_pattern(::f32 cx, ::f32 cy, ::f32 w, ::f32 h, ::f32 angle,
		::i32 image, ::f32 alpha)
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
	void CONTEXT::scissor(::f32 x, ::f32 y, ::f32 w, ::f32 h)
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

	//static void CONTEXT::__isectRects)(::f32 * dst,
	//	::f32 ax, ::f32 ay, ::f32 aw, ::f32 ah,
	//	::f32 bx, ::f32 by, ::f32 bw, ::f32 bh)
	//{
	//	::f32 minx = CONTEXT::__maxf)(ax, bx);
	//	::f32 miny = CONTEXT::__maxf)(ay, by);
	//	::f32 maxx = CONTEXT::__minf)(ax + aw, bx + bw);
	//	::f32 maxy = CONTEXT::__minf)(ay + ah, by + bh);
	//	dst[0] = minx;
	//	dst[1] = miny;
	//	dst[2] = CONTEXT::__maxf)(0.0f, maxx - minx);
	//	dst[3] = CONTEXT::__maxf)(0.0f, maxy - miny);
	//}

	void CONTEXT::intersect_scissor(::f32 x, ::f32 y, ::f32 w, ::f32 h)
	{

		// intersect_scissor(x, y, w, h);
		//::nano2d::state * state = __getState();
		//::f32 pxform[6], invxorm[6];
		//::f32 rect[4];
		//::f32 ex, ey, tex, tey;

		//// If no previous scissor has been set, set the scissor as current scissor.
		//if (state->scissor.extent[0] < 0) {
		//	CONTEXT::Scissor)(ctx, x, y, w, h);
		//	return;
		//}

		//// Transform the current scissor rect into current transform space.
		//// If there is difference in rotation, this will be approximation.
		//::memory_copy(pxform, state->scissor.xform, sizeof(::f32) * 6);
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
	void CONTEXT::global_composite_operation(::i32 op)
	{
		
		::nano2d::state * state = __getState();
		state->compositeOperation = __compositeOperationState(op);

	}


	void CONTEXT::global_composite_blend_func(::i32 sfactor, ::i32 dfactor)
	{
		
		global_composite_blend_func_separate(sfactor, dfactor, sfactor, dfactor);

	}


	void CONTEXT::global_composite_blend_func_separate(::i32 srcRGB, ::i32 dstRGB, ::i32 srcAlpha, ::i32 dstAlpha)
	{
		compositeOperationState op;
		op.srcRGB = srcRGB;
		op.dstRGB = dstRGB;
		op.srcAlpha = srcAlpha;
		op.dstAlpha = dstAlpha;

		::nano2d::state * state = __getState();
		state->compositeOperation = op;

	}


	::i32 point_equals(::f32 x1, ::f32 y1, ::f32 x2, ::f32 y2, ::f32 tol)
	{
		
		::f32 Δx = x2 - x1;
		::f32 Δy = y2 - y1;
		return Δx * Δx + Δy * Δy < tol * tol;

	}


	::f32 point_distance_seg(::f32 x, ::f32 y, ::f32 px, ::f32 py, ::f32 qx, ::f32 qy)
	{
		::f32 pqx, pqy, Δx, Δy, d, t;
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


	void CONTEXT::__append_commands(::f32 * vals, ::i32 nvals)
	{
		::nano2d::state * state = __getState();
		::i32 i;

		if (ncommands + nvals > ccommands) {
			::f32 * commands;
			::i32 ccommands = ncommands + nvals + ccommands / 2;
			commands = (::f32 *)realloc(commands, sizeof(::f32) * ccommands);
			if (commands == NULL) return;
			commands = commands;
			ccommands = ccommands;
		}

		if ((::i32)vals[0] != ::nano2d::e_command_close && (::i32)vals[0] != ::nano2d::e_command_winding) {
			commandx = vals[nvals - 2];
			commandy = vals[nvals - 1];
		}

		// transform commands
		i = 0;
		while (i < nvals) {
			::i32 cmd = (::i32)vals[i];
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

		::memory_copy(&commands[ncommands], vals, nvals * sizeof(::f32));

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
	//		::i32 cpaths = cache->npaths + 1 + cache->cpaths / 2;
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

	//static void CONTEXT::__addPoint(::f32 x, ::f32 y, ::i32 flags)
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
	//		::i32 cpoints = cache->npoints + 1 + cache->cpoints / 2;
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
	//	pt->flags = (::u8)flags;
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

	//static void CONTEXT::__pathWinding(::i32 winding)
	//{
	//	::nano2d::path * path = CONTEXT::__lastPath)(ctx);
	//	if (path == NULL) return;
	//	path->winding = winding;
	//}
	//
	//static ::f32 CONTEXT::__getAverageScale)(::f32 * t)
	//{
	//	::f32 sx = sqrtf(t[0] * t[0] + t[2] * t[2]);
	//	::f32 sy = sqrtf(t[1] * t[1] + t[3] * t[3]);
	//	return (sx + sy) * 0.5f;
	//}

	//static NVGvertex * CONTEXT::__allocTempVerts(::i32 nverts)
	//{
	//	if (nverts > cache->cverts) {
	//		NVGvertex * verts;
	//		::i32 cverts = (nverts + 0xff) & ~0xff; // Round up to prevent allocations when things change just slightly.
	//		verts = (NVGvertex *)realloc(cache->verts, sizeof(NVGvertex) * cverts);
	//		if (verts == NULL) return NULL;
	//		cache->verts = verts;
	//		cache->cverts = cverts;
	//	}
	//
	//	return cache->verts;
	//}
	//
	//static ::f32 CONTEXT::__triarea2)(::f32 ax, ::f32 ay, ::f32 bx, ::f32 by, ::f32 cx, ::f32 cy)
	//{
	//	::f32 abx = bx - ax;
	//	::f32 aby = by - ay;
	//	::f32 acx = cx - ax;
	//	::f32 acy = cy - ay;
	//	return acx * aby - abx * acy;
	//}

	//static ::f32 CONTEXT::__polyArea)(NVGpoint * pts, ::i32 npts)
	//{
	//	::i32 i;
	//	::f32 area = 0;
	//	for (i = 2; i < npts; i++) {
	//		NVGpoint * a = &pts[0];
	//		NVGpoint * b = &pts[i - 1];
	//		NVGpoint * c = &pts[i];
	//		area += CONTEXT::__triarea2)(a->x, a->y, b->x, b->y, c->x, c->y);
	//	}
	//	return area * 0.5f;
	//}

	//static void CONTEXT::__polyReverse)(NVGpoint * pts, ::i32 npts)
	//{
	//	NVGpoint tmp;
	//	::i32 i = 0, j = npts - 1;
	//	while (i < j) {
	//		tmp = pts[i];
	//		pts[i] = pts[j];
	//		pts[j] = tmp;
	//		i++;
	//		j--;
	//	}
	//}


	//static void CONTEXT::__vset)(NVGvertex * vtx, ::f32 x, ::f32 y, ::f32 u, ::f32 v)
	//{
	//	vtx->x = x;
	//	vtx->y = y;
	//	vtx->u = u;
	//	vtx->v = v;
	//}

	//static void CONTEXT::__tesselateBezier)(NANO2D_CONTEXT * ctx,
	//	::f32 x1, ::f32 y1, ::f32 x2, ::f32 y2,
	//	::f32 x3, ::f32 y3, ::f32 x4, ::f32 y4,
	//	::i32 level, ::i32 type)
	//{
	//	::f32 x12, y12, x23, y23, x34, y34, x123, y123, x234, y234, x1234, y1234;
	//	::f32 Δx, Δy, d2, d3;
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
	//	::i32 i, j;
	//	::f32 * cp1;
	//	::f32 * cp2;
	//	::f32 * p;
	//	::f32 area;
	//
	//	if (cache->npaths > 0)
	//		return;
	//
	//	// Flatten
	//	i = 0;
	//	while (i < ncommands) {
	//		::i32 cmd = (::i32)commands[i];
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
	//			CONTEXT::__pathWinding)(ctx, (::i32)commands[i + 1]);
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

	//static ::i32 CONTEXT::__curveDivs)(::f32 r, ::f32 arc, ::f32 tol)
	//{
	//	::f32 da = acosf(r / (r + tol)) * 2.0f;
	//	return CONTEXT::__maxi)(2, (::i32)ceilf(arc / da));
	//}

	//static void CONTEXT::__chooseBevel)(::i32 bevel, NVGpoint * p0, NVGpoint * p1, ::f32 w,
	//	::f32 * x0, ::f32 * y0, ::f32 * x1, ::f32 * y1)
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
	//	::f32 lw, ::f32 rw, ::f32 lu, ::f32 ru, ::i32 ncap,
	//	::f32 fringe)
	//{
	//	::i32 i, n;
	//	::f32 dlx0 = p0->Δy;
	//	::f32 dly0 = -p0->Δx;
	//	::f32 dlx1 = p1->Δy;
	//	::f32 dly1 = -p1->Δx;
	//	NVG_NOTUSED(fringe);
	//
	//	if (p1->flags & NVG_PT_LEFT) {
	//		::f32 lx0, ly0, lx1, ly1, a0, a1;
	//		CONTEXT::__chooseBevel)(p1->flags & NVG_PR_INNERBEVEL, p0, p1, lw, &lx0, &ly0, &lx1, &ly1);
	//		a0 = atan2f(-dly0, -dlx0);
	//		a1 = atan2f(-dly1, -dlx1);
	//		if (a1 > a0) a1 -= ::nano2d::f_pi * 2;
	//
	//		CONTEXT::__vset)(dst, lx0, ly0, lu, 1); dst++;
	//		CONTEXT::__vset)(dst, p1->x - dlx0 * rw, p1->y - dly0 * rw, ru, 1); dst++;
	//
	//		n = CONTEXT::__clampi)((::i32)ceilf(((a0 - a1) / ::nano2d::f_pi) * ncap), 2, ncap);
	//		for (i = 0; i < n; i++) {
	//			::f32 u = i / (::f32)(n - 1);
	//			::f32 a = a0 + u * (a1 - a0);
	//			::f32 rx = p1->x + cosf(a) * rw;
	//			::f32 ry = p1->y + sinf(a) * rw;
	//			CONTEXT::__vset)(dst, p1->x, p1->y, 0.5f, 1); dst++;
	//			CONTEXT::__vset)(dst, rx, ry, ru, 1); dst++;
	//		}
	//
	//		CONTEXT::__vset)(dst, lx1, ly1, lu, 1); dst++;
	//		CONTEXT::__vset)(dst, p1->x - dlx1 * rw, p1->y - dly1 * rw, ru, 1); dst++;
	//
	//	}
	//	else {
	//		::f32 rx0, ry0, rx1, ry1, a0, a1;
	//		CONTEXT::__chooseBevel)(p1->flags & NVG_PR_INNERBEVEL, p0, p1, -rw, &rx0, &ry0, &rx1, &ry1);
	//		a0 = atan2f(dly0, dlx0);
	//		a1 = atan2f(dly1, dlx1);
	//		if (a1 < a0) a1 += ::nano2d::f_pi * 2;
	//
	//		CONTEXT::__vset)(dst, p1->x + dlx0 * rw, p1->y + dly0 * rw, lu, 1); dst++;
	//		CONTEXT::__vset)(dst, rx0, ry0, ru, 1); dst++;
	//
	//		n = CONTEXT::__clampi)((::i32)ceilf(((a1 - a0) / ::nano2d::f_pi) * ncap), 2, ncap);
	//		for (i = 0; i < n; i++) {
	//			::f32 u = i / (::f32)(n - 1);
	//			::f32 a = a0 + u * (a1 - a0);
	//			::f32 lx = p1->x + cosf(a) * lw;
	//			::f32 ly = p1->y + sinf(a) * lw;
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
	//	::f32 lw, ::f32 rw, ::f32 lu, ::f32 ru, ::f32 fringe)
	//{
	//	::f32 rx0, ry0, rx1, ry1;
	//	::f32 lx0, ly0, lx1, ly1;
	//	::f32 dlx0 = p0->Δy;
	//	::f32 dly0 = -p0->Δx;
	//	::f32 dlx1 = p1->Δy;
	//	::f32 dly1 = -p1->Δx;
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
	//	::f32 Δx, ::f32 Δy, ::f32 w, ::f32 d,
	//	::f32 aa, ::f32 u0, ::f32 u1)
	//{
	//	::f32 px = p->x - Δx * d;
	//	::f32 py = p->y - Δy * d;
	//	::f32 dlx = Δy;
	//	::f32 dly = -Δx;
	//	CONTEXT::__vset)(dst, px + dlx * w - Δx * aa, py + dly * w - Δy * aa, u0, 0); dst++;
	//	CONTEXT::__vset)(dst, px - dlx * w - Δx * aa, py - dly * w - Δy * aa, u1, 0); dst++;
	//	CONTEXT::__vset)(dst, px + dlx * w, py + dly * w, u0, 1); dst++;
	//	CONTEXT::__vset)(dst, px - dlx * w, py - dly * w, u1, 1); dst++;
	//	return dst;
	//}

	//static NVGvertex * CONTEXT::__buttCapEnd)(NVGvertex * dst, NVGpoint * p,
	//	::f32 Δx, ::f32 Δy, ::f32 w, ::f32 d,
	//	::f32 aa, ::f32 u0, ::f32 u1)
	//{
	//	::f32 px = p->x + Δx * d;
	//	::f32 py = p->y + Δy * d;
	//	::f32 dlx = Δy;
	//	::f32 dly = -Δx;
	//	CONTEXT::__vset)(dst, px + dlx * w, py + dly * w, u0, 1); dst++;
	//	CONTEXT::__vset)(dst, px - dlx * w, py - dly * w, u1, 1); dst++;
	//	CONTEXT::__vset)(dst, px + dlx * w + Δx * aa, py + dly * w + Δy * aa, u0, 0); dst++;
	//	CONTEXT::__vset)(dst, px - dlx * w + Δx * aa, py - dly * w + Δy * aa, u1, 0); dst++;
	//	return dst;
	//}
	//

	//static NVGvertex * CONTEXT::__roundCapStart)(NVGvertex * dst, NVGpoint * p,
	//	::f32 Δx, ::f32 Δy, ::f32 w, ::i32 ncap,
	//	::f32 aa, ::f32 u0, ::f32 u1)
	//{
	//	::i32 i;
	//	::f32 px = p->x;
	//	::f32 py = p->y;
	//	::f32 dlx = Δy;
	//	::f32 dly = -Δx;
	//	NVG_NOTUSED(aa);
	//	for (i = 0; i < ncap; i++) {
	//		::f32 a = i / (::f32)(ncap - 1) * ::nano2d::f_pi;
	//		::f32 ax = cosf(a) * w, ay = sinf(a) * w;
	//		CONTEXT::__vset)(dst, px - dlx * ax - Δx * ay, py - dly * ax - Δy * ay, u0, 1); dst++;
	//		CONTEXT::__vset)(dst, px, py, 0.5f, 1); dst++;
	//	}
	//	CONTEXT::__vset)(dst, px + dlx * w, py + dly * w, u0, 1); dst++;
	//	CONTEXT::__vset)(dst, px - dlx * w, py - dly * w, u1, 1); dst++;
	//	return dst;
	//}

	//static NVGvertex * CONTEXT::__roundCapEnd)(NVGvertex * dst, NVGpoint * p,
	//	::f32 Δx, ::f32 Δy, ::f32 w, ::i32 ncap,
	//	::f32 aa, ::f32 u0, ::f32 u1)
	//{
	//	::i32 i;
	//	::f32 px = p->x;
	//	::f32 py = p->y;
	//	::f32 dlx = Δy;
	//	::f32 dly = -Δx;
	//	NVG_NOTUSED(aa);
	//	CONTEXT::__vset)(dst, px + dlx * w, py + dly * w, u0, 1); dst++;
	//	CONTEXT::__vset)(dst, px - dlx * w, py - dly * w, u1, 1); dst++;
	//	for (i = 0; i < ncap; i++) {
	//		::f32 a = i / (::f32)(ncap - 1) * ::nano2d::f_pi;
	//		::f32 ax = cosf(a) * w, ay = sinf(a) * w;
	//		CONTEXT::__vset)(dst, px, py, 0.5f, 1); dst++;
	//		CONTEXT::__vset)(dst, px - dlx * ax + Δx * ay, py - dly * ax + Δy * ay, u0, 1); dst++;
	//	}
	//	return dst;
	//}


	//static void CONTEXT::__calculateJoins(::f32 w, ::i32 lineJoin, ::f32 miterLimit)
	//{
	//	NVGpathCache * cache = cache;
	//	::i32 i, j;
	//	::f32 iw = 0.0f;
	//
	//	if (w > 0.0f) iw = 1.0f / w;
	//
	//	// Calculate which joins needs extra vertices to append, and gather vertex count.
	//	for (i = 0; i < cache->npaths; i++) {
	//		::nano2d::path * path = &cache->paths[i];
	//		NVGpoint * pts = &cache->points[path->first];
	//		NVGpoint * p0 = &pts[path->count - 1];
	//		NVGpoint * p1 = &pts[0];
	//		::i32 nleft = 0;
	//
	//		path->nbevel = 0;
	//
	//		for (j = 0; j < path->count; j++) {
	//			::f32 dlx0, dly0, dlx1, dly1, dmr2, cross, limit;
	//			dlx0 = p0->Δy;
	//			dly0 = -p0->Δx;
	//			dlx1 = p1->Δy;
	//			dly1 = -p1->Δx;
	//			// Calculate extrusions
	//			p1->dmx = (dlx0 + dlx1) * 0.5f;
	//			p1->dmy = (dly0 + dly1) * 0.5f;
	//			dmr2 = p1->dmx * p1->dmx + p1->dmy * p1->dmy;
	//			if (dmr2 > 0.000001f) {
	//				::f32 scale = 1.0f / dmr2;
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


	//static ::i32 CONTEXT::__expandStroke(::f32 w, ::f32 fringe, ::i32 lineCap, ::i32 lineJoin, ::f32 miterLimit)
	//{
	//	NVGpathCache * cache = cache;
	//	NVGvertex * verts;
	//	NVGvertex * dst;
	//	::i32 cverts, i, j;
	//	::f32 aa = fringe;//fringeWidth;
	//	::f32 u0 = 0.0f, u1 = 1.0f;
	//	::i32 ncap = CONTEXT::__curveDivs)(w, ::nano2d::f_pi, tessTol);	// Calculate divisions per half circle.
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
	//		::i32 loop = (path->closed == 0) ? 0 : 1;
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
	//		::i32 s, e, loop;
	//		::f32 Δx, Δy;
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
	//			CONTEXT::__vset)(dst, verts[0].x, verts[0].y, u0, 1); dst++;
	//			CONTEXT::__vset)(dst, verts[1].x, verts[1].y, u1, 1); dst++;
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
	//		path->nstroke = (::i32)(dst - verts);
	//
	//		verts = dst;
	//	}
	//
	//	return 1;
	//}

	//static ::i32 CONTEXT::__expandFill(::f32 w, ::i32 lineJoin, ::f32 miterLimit)
	//{
	//	NVGpathCache * cache = cache;
	//	NVGvertex * verts;
	//	NVGvertex * dst;
	//	::i32 cverts, convex, i, j;
	//	::f32 aa = fringeWidth;
	//	::i32 fringe = w > 0.0f;
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
	//		::f32 rw, lw, woff;
	//		::f32 ru, lu;
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
	//					::f32 dlx0 = p0->Δy;
	//					::f32 dly0 = -p0->Δx;
	//					::f32 dlx1 = p1->Δy;
	//					::f32 dly1 = -p1->Δx;
	//					if (p1->flags & NVG_PT_LEFT) {
	//						::f32 lx = p1->x + p1->dmx * woff;
	//						::f32 ly = p1->y + p1->dmy * woff;
	//						CONTEXT::__vset)(dst, lx, ly, 0.5f, 1); dst++;
	//					}
	//					else {
	//						::f32 lx0 = p1->x + dlx0 * woff;
	//						::f32 ly0 = p1->y + dly0 * woff;
	//						::f32 lx1 = p1->x + dlx1 * woff;
	//						::f32 ly1 = p1->y + dly1 * woff;
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
	//				CONTEXT::__vset)(dst, pts[j].x, pts[j].y, 0.5f, 1);
	//				dst++;
	//			}
	//		}
	//
	//		path->nfill = (::i32)(dst - verts);
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
	//			CONTEXT::__vset)(dst, verts[0].x, verts[0].y, lu, 1); dst++;
	//			CONTEXT::__vset)(dst, verts[1].x, verts[1].y, ru, 1); dst++;
	//
	//			path->nstroke = (::i32)(dst - verts);
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

	void CONTEXT::move_to(::f32 x, ::f32 y)
	{
		//::f32 vals[] = { ::nano2d::e_command_move_to, x, y };
		//CONTEXT::__appendCommands)(ctx, vals, NANO2D_COUNTOF(vals));
		//move_to(x, y);
	}

	void CONTEXT::line_to(::f32 x, ::f32 y)
	{
		/*::f32 vals[] = { ::nano2d::e_command_line_to, x, y };
		CONTEXT::__appendCommands)(ctx, vals, NANO2D_COUNTOF(vals));*/

		//line_to(x, y);
	}

	void CONTEXT::bezier_to(::f32 c1x, ::f32 c1y, ::f32 c2x, ::f32 c2y, ::f32 x, ::f32 y)
	{
		//::f32 vals[] = { ::nano2d::e_command_bezier_to, c1x, c1y, c2x, c2y, x, y };
		//CONTEXT::__appendCommands)(ctx, vals, NANO2D_COUNTOF(vals));
	}

	void CONTEXT::quad_to(::f32 cx, ::f32 cy, ::f32 x, ::f32 y)
	{
		//::f32 x0 = commandx;
		//::f32 y0 = commandy;
		//::f32 vals[] = { ::nano2d::e_command_bezier_to,
		//	 x0 + 2.0f / 3.0f * (cx - x0), y0 + 2.0f / 3.0f * (cy - y0),
		//	 x + 2.0f / 3.0f * (cx - x), y + 2.0f / 3.0f * (cy - y),
		//	 x, y };
		//CONTEXT::__appendCommands)(ctx, vals, NANO2D_COUNTOF(vals));
	}

	void CONTEXT::arc_to(::f32 x1, ::f32 y1, ::f32 x2, ::f32 y2, ::f32 radius)
	{
		//::f32 x0 = commandx;
		//::f32 y0 = commandy;
		//::f32 dx0, dy0, dx1, dy1, a, d, cx, cy, a0, a1;
		//::i32 dir;

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
		//::f32 vals[] = { ::nano2d::e_command_close };
		//CONTEXT::__appendCommands)(ctx, vals, NANO2D_COUNTOF(vals));
		//close_path();
	}


	void CONTEXT::path_winding(::i32 dir)
	{
		//::f32 vals[] = { ::nano2d::e_command_winding, (::f32)dir };
		//CONTEXT::__appendCommands)(ctx, vals, NANO2D_COUNTOF(vals));

		//path_winding(dir);

	}

	void CONTEXT::arc(::f32 cx, ::f32 cy, ::f32 r, ::f32 a0, ::f32 a1, ::i32 dir)
	{
		//arc(cx, cy, r, a0, a1, dir);
		//::f32 a = 0, da = 0, hda = 0, kappa = 0;
		//::f32 Δx = 0, Δy = 0, x = 0, y = 0, tanx = 0, tany = 0;
		//::f32 px = 0, py = 0, ptanx = 0, ptany = 0;
		//::f32 vals[3 + 5 * 7 + 100];
		//::i32 i, ndivs, nvals;
		//::i32 transfer = ncommands > 0 ? ::nano2d::e_command_line_to : ::nano2d::e_command_move_to;

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
		//ndivs = CONTEXT::__maxi)(1, CONTEXT::__mini)((::i32)(CONTEXT::__absf)(da) / (::nano2d::f_pi * 0.5f) + 0.5f), 5));
		//hda = (da / (::f32)ndivs) / 2.0f;
		//kappa = CONTEXT::__absf)(4.0f / 3.0f * (1.0f - CONTEXT::__cosf)(hda)) / CONTEXT::__sinf)(hda));

		//if (dir == ::nano2d::e_winding_ccw)
		//	kappa = -kappa;

		//nvals = 0;
		//for (i = 0; i <= ndivs; i++) {
		//	a = a0 + da * (i / (::f32)ndivs);
		//	Δx = CONTEXT::__cosf)(a);
		//	Δy = CONTEXT::__sinf)(a);
		//	x = cx + Δx * r;
		//	y = cy + Δy * r;
		//	tanx = -Δy * r * kappa;
		//	tany = Δx * r * kappa;

		//	if (i == 0) {
		//		vals[nvals++] = (::f32)transfer;
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


	void CONTEXT::f64_rectangle(::f32 x, ::f32 y, ::f32 w, ::f32 h)
	{
		//::f32 vals[] = {
		//	::nano2d::e_command_move_to, x,y,
		//	::nano2d::e_command_line_to, x,y + h,
		//	::nano2d::e_command_line_to, x + w,y + h,
		//	::nano2d::e_command_line_to, x + w,y,
		//	::nano2d::e_command_close
		//};
		//CONTEXT::__appendCommands)(ctx, vals, NANO2D_COUNTOF(vals));
		//rect(x, y, w, h);
	}


	void CONTEXT::rounded_rectangle(::f32 x, ::f32 y, ::f32 w, ::f32 h, ::f32 r)
	{
	//	CONTEXT::RoundedRectVarying)(ctx, x, y, w, h, r, r, r, r);

		//rounded_rect(x, y, w, h, r);

	}


	void CONTEXT::rounded_rectangle_varying(::f32 x, ::f32 y, ::f32 w, ::f32 h, ::f32 radTopLeft, ::f32 radTopRight, ::f32 radBottomRight, ::f32 radBottomLeft)
	{
		//if (radTopLeft < 0.1f && radTopRight < 0.1f && radBottomRight < 0.1f && radBottomLeft < 0.1f) {
		//	CONTEXT::Rect)(ctx, x, y, w, h);
		//	return;
		//}
		//else {
		//	::f32 halfw = CONTEXT::__absf)(w) * 0.5f;
		//	::f32 halfh = CONTEXT::__absf)(h) * 0.5f;
		//	::f32 rxBL = CONTEXT::__minf)(radBottomLeft, halfw) * CONTEXT::__signf)(w), ryBL = CONTEXT::__minf)(radBottomLeft, halfh) * CONTEXT::__signf)(h);
		//	::f32 rxBR = CONTEXT::__minf)(radBottomRight, halfw) * CONTEXT::__signf)(w), ryBR = CONTEXT::__minf)(radBottomRight, halfh) * CONTEXT::__signf)(h);
		//	::f32 rxTR = CONTEXT::__minf)(radTopRight, halfw) * CONTEXT::__signf)(w), ryTR = CONTEXT::__minf)(radTopRight, halfh) * CONTEXT::__signf)(h);
		//	::f32 rxTL = CONTEXT::__minf)(radTopLeft, halfw) * CONTEXT::__signf)(w), ryTL = CONTEXT::__minf)(radTopLeft, halfh) * CONTEXT::__signf)(h);
		//	::f32 vals[] = {
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

	void CONTEXT::f64_ellipse(::f32 cx, ::f32 cy, ::f32 rx, ::f32 ry)
	{
		//::f32 vals[] = {
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


	void CONTEXT::circle(::f32 cx, ::f32 cy, ::f32 r)
	{
		
		//CONTEXT::Ellipse)(ctx, cx, cy, r, r);

	}


	void CONTEXT::debug_dump_path_cache()
	{
		const ::nano2d::path * path;
		::i32 i, j;

		printf("Dumping %d cached paths\n", cache->npaths);
		for (i = 0; i < cache->npaths; i++) {
			path = &cache->paths[i];
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


	void CONTEXT::fill()
	{

		//::nano2d::state * state = __getState();
		//const ::nano2d::path * path;
		//::nano2d::paint fillPaint = state->fill;
		//::i32 i;

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
		//::f32 scale = CONTEXT::__getAverageScale)(state->xform);
		//::f32 strokeWidth = CONTEXT::__clampf)(state->strokeWidth * scale, 0.0f, 200.0f);
		//::nano2d::paint strokePaint = state->stroke;
		//const ::nano2d::path * path;
		//::i32 i;


		//if (strokeWidth < fringeWidth) {
		//	// If the stroke width is less than pixel size, use alpha to emulate coverage.
		//	// Since coverage is area, scale by alpha*alpha.
		//	::f32 alpha = CONTEXT::__clampf)(strokeWidth / fringeWidth, 0.0f, 1.0f);
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
	//::i32 CONTEXT::CreateFont(const_char_pointer pszName, const_char_pointer pszFilename)
	//{
	//	//return fonsAddFont(fs, name, filename, 0);
	//	return -1;
	//}

	::i32 CONTEXT::CreateFontAtIndex(const_char_pointer pszName, const_char_pointer pszFilename, const ::i32 fontIndex)
	{
		//return fonsAddFont(fs, name, filename, fontIndex);
		return -1;
	}


	::i32 CONTEXT::create_font_mem(const_char_pointer pszName, ::u8 * data, ::i32 ndata, ::i32 freeData)
	{
	
		//return fonsAddFontMem(fs, name, data, ndata, freeData, 0);
		return -1;

	}


	::i32 CONTEXT::create_font_mem_at_index(const_char_pointer pszName, ::u8 * data, ::i32 ndata, ::i32 freeData, const ::i32 fontIndex)
	{
	
		//return fonsAddFontMem(fs, name, data, ndata, freeData, fontIndex);
		return -1;

	}


	::i32 CONTEXT::find_font(const_char_pointer pszName)
	{

		//if (name == NULL) return -1;
		//return fonsGetFontByName(fs, name);
		return -1;

	}


	::i32 CONTEXT::add_fallback_font_id(::i32 baseFont, ::i32 fallbackFont)
	{
		//if (baseFont == -1 || fallbackFont == -1) return 0;
		//return fonsAddFallbackFont(fs, baseFont, fallbackFont);
		return -1;
	}

	
	::i32 CONTEXT::add_fallback_font(const_char_pointer baseFont, const_char_pointer fallbackFont)
	{
		//return CONTEXT::AddFallbackFontId)(ctx, CONTEXT::FindFont)(ctx, baseFont), CONTEXT::FindFont)(ctx, fallbackFont));
		return -1;
	}


	void CONTEXT::reset_fallback_fonts_id(::i32 baseFont)
	{
		//fonsResetFallbackFont(fs, baseFont);
		return;
	}


	void CONTEXT::reset_fallback_fonts(const_char_pointer baseFont)
	{
		//CONTEXT::ResetFallbackFontsId)(ctx, CONTEXT::FindFont)(ctx, baseFont));
		return;
	}


	// State setting
	void CONTEXT::font_size(::f32 size)
	{
		//::nano2d::state * state = __getState();
		//state->fontSize = size;
		//font_size(size);

	}

	
	void CONTEXT::font_blur(::f32 blur)
	{
		
		//::nano2d::state * state = __getState();
		//state->fontBlur = blur;
		//throw_todo();
		//font_blur(blur);

	}


	//::write_text::font_pointer CONTEXT::CreateFont(const_char_pointer face, ::f32 size)
	//{
	//   
	//   return create_font(face, size);
	//   
	//}


	void CONTEXT::text_letter_spacing(::f32 spacing)
	{
		
		//::nano2d::state * state = __getState();
		//state->letterSpacing = spacing;
		throw_todo();

	}

	
	void CONTEXT::text_line_height(::f32 lineHeight)
	{
		//::nano2d::state * state = __getState();
		//state->lineHeight = lineHeight;
		//text_line_height(lineHeight);

	}

	
	void CONTEXT::text_align(::i32 align)
	{

		//::nano2d::state * state = __getState();
		//state->textAlign = align;

		//text_align(align);

	}


	void CONTEXT::font_face_id(::i32 font)
	{
	
		//::nano2d::state * state = __getState();
		//state->fontId = font;
		throw_todo();

	}


	void CONTEXT::font_face(const_char_pointer font)
	{
		//::nano2d::state * state = __getState();
		//state->fontId = fonsGetFontByName(fs, font);

		//font_face(font);

	}


	//static ::f32 CONTEXT::__quantize)(::f32 a, ::f32 d)
	//{
	//	return ((::i32)(a / d + 0.5f)) * d;
	//}

	//static ::f32 CONTEXT::__getFontScale)(::nano2d::state * state)
	//{
	//	return CONTEXT::__minf)(CONTEXT::__quantize)(CONTEXT::__getAverageScale)(state->xform), 0.01f), 4.0f);
	//}

	//static void CONTEXT::__flushTextTexture()
	//{
	//	//::i32 dirty[4];
	//
	//	//if (fonsValidateTexture(fs, dirty)) {
	//	//	::i32 fontImage = fontImages[fontImageIdx];
	//	//	// Update texture
	//	//	if (fontImage != 0) {
	//	//		::i32 iw, ih;
	//	//		const ::u8 * data = fonsGetTextureData(fs, &iw, &ih);
	//	//		::i32 x = dirty[0];
	//	//		::i32 y = dirty[1];
	//	//		::i32 w = dirty[2] - dirty[0];
	//	//		::i32 h = dirty[3] - dirty[1];
	//	//		params.renderUpdateTexture(params.userPtr, fontImage, x, y, w, h, data);
	//	//	}
	//	//}
	//}

	//static ::i32 CONTEXT::__allocTextAtlas()
	//{
	//	//::i32 iw, ih;
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
	//static void CONTEXT::__renderText(NVGvertex * verts, ::i32 nverts)
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
	//static ::i32 CONTEXT::__isTransformFlipped)(const ::f32 * xform)
	//{
	//	/*::f32 det = xform[0] * xform[3] - xform[2] * xform[1];
	//	return(det < 0);*/
	//	throw_todo();
	//	return -1;
	//}
	//
	::f32 CONTEXT::Text(::f32 x, ::f32 y, const_char_pointer string, const_char_pointer end)
	{

		//::nano2d::state * state = __getState();
		//FONStextIter iter, prevIter;
		//FONSquad q;
		//NVGvertex * verts;
		//::f32 scale = CONTEXT::__getFontScale)(state) * devicePxRatio;
		//::f32 invscale = 1.0f / scale;
		//::i32 cverts = 0;
		//::i32 nverts = 0;
		//::i32 isFlipped = CONTEXT::__isTransformFlipped)(state->xform);

		//if (end == NULL)
		//	end = string + strlen(string);

		//if (state->fontId == FONS_INVALID) return x;

		//fonsSetSize(fs, state->fontSize * scale);
		//fonsSetSpacing(fs, state->letterSpacing * scale);
		//fonsSetBlur(fs, state->fontBlur * scale);
		//fonsSetAlign(fs, state->textAlign);
		//fonsSetFont(fs, state->fontId);

		//cverts = CONTEXT::__maxi)(2, (::i32)(end - string)) * 6; // conservative estimate.
		//verts = CONTEXT::__allocTempVerts)(ctx, cverts);
		//if (verts == NULL) return x;

		//fonsTextIterInit(fs, &iter, x * scale, y * scale, string, end, FONS_GLYPH_BITMAP_REQUIRED);
		//prevIter = iter;
		//while (fonsTextIterNext(fs, &iter, &q)) {
		//	::f32 c[4 * 2];
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
		//		::f32 tmp;

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


	void CONTEXT::text_box(::f32 x, ::f32 y, ::f32 breakRowWidth, const_char_pointer string, const_char_pointer end)
	{

		//text(x, y, string, end);
		// throw_todo();
		//::nano2d::state * state = __getState();
		//::nano2d::text_row rows[2];
		//::i32 nrows = 0, i;
		//::i32 oldAlign = state->textAlign;
		//::i32 haling = state->textAlign & (::nano2d::e_align_left | ::nano2d::e_align_center | ::nano2d::e_align_right);
		//::i32 valign = state->textAlign & (::nano2d::e_align_top | ::nano2d::e_align_middle | ::nano2d::e_align_bottom | ::nano2d::e_align_baseline);
		//::f32 lineh = 0;

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


	::i32 CONTEXT::text_glyph_positions(::f32 x, ::f32 y, const_char_pointer string, const_char_pointer end, ::nano2d::glyphPosition * positions, ::i32 maxPositions)
	{

		return text_glyph_positions(x, y, string, end, positions, maxPositions);

		//throw_todo();
		//return -1;
		//::nano2d::state * state = __getState();
		//::f32 scale = CONTEXT::__getFontScale)(state) * devicePxRatio;
		//::f32 invscale = 1.0f / scale;
		//FONStextIter iter, prevIter;
		//FONSquad q;
		//::i32 npos = 0;

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
		//	positions[npos].x = iter.x * invscale;
		//	positions[npos].minx = CONTEXT::__minf)(iter.x, q.x0) * invscale;
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


	::i32 CONTEXT::text_break_lines(const_char_pointer string, const_char_pointer end, ::f32 breakRowWidth, ::nano2d::text_row * rows, ::i32 maxRows)
	{

		throw_todo();
		return -1;
		//::nano2d::state * state = __getState();
		//::f32 scale = CONTEXT::__getFontScale)(state) * devicePxRatio;
		//::f32 invscale = 1.0f / scale;
		//FONStextIter iter, prevIter;
		//FONSquad q;
		//::i32 nrows = 0;
		//::f32 rowStartX = 0;
		//::f32 rowWidth = 0;
		//::f32 rowMinX = 0;
		//::f32 rowMaxX = 0;
		//const_char_pointer rowStart = NULL;
		//const_char_pointer rowEnd = NULL;
		//const_char_pointer wordStart = NULL;
		//::f32 wordStartX = 0;
		//::f32 wordMinX = 0;
		//const_char_pointer breakEnd = NULL;
		//::f32 breakWidth = 0;
		//::f32 breakMaxX = 0;
		//::i32 type = NVG_SPACE, ptype = NVG_SPACE;
		//::u32 pcodepoint = 0;

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
		//				// The current ::i8 is the row so far
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
		//			::f32 nextWidth = iter.nextx - rowStartX;

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


	::f32 CONTEXT::text_bounds(::f32 x, ::f32 y, const_char_pointer string, const_char_pointer end, ::f32 * bounds)
	{

		//return text_bounds(x, y, string, end, bounds);
		//::nano2d::state * state = __getState();
		//::f32 scale = CONTEXT::__getFontScale)(state) * devicePxRatio;
		//::f32 invscale = 1.0f / scale;
		//::f32 width;

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

	void CONTEXT::text_box_bounds(::f32 x, ::f32 y, ::f32 breakRowWidth, const_char_pointer string, const_char_pointer end, ::f32 * bounds)
	{

		//text_bounds(x, y, string, end, bounds);

	//
	//	//::nano2d::state * state = __getState();
	//	::nano2d::text_row rows[2];
	//	::f32 scale = CONTEXT::__getFontScale)(state) * devicePxRatio;
	//	::f32 invscale = 1.0f / scale;
	//	::i32 nrows = 0, i;
	//	::i32 oldAlign = state->textAlign;
	//	::i32 haling = state->textAlign & (::nano2d::e_align_left | ::nano2d::e_align_center | ::nano2d::e_align_right);
	//	::i32 valign = state->textAlign & (::nano2d::e_align_top | ::nano2d::e_align_middle | ::nano2d::e_align_bottom | ::nano2d::e_align_baseline);
	//	::f32 lineh = 0, rminy = 0, rmaxy = 0;
	//	::f32 minx, miny, maxx, maxy;
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
	//			::f32 rminx, rmaxx, Δx = 0;
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

	void CONTEXT::text_metrics(::f32 * ascender, ::f32 * descender, ::f32 * lineh)
	{
		//::nano2d::state * state = __getState();
		//::f32 scale = CONTEXT::__getFontScale)(state) * devicePxRatio;
		//::f32 invscale = 1.0f / scale;

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



