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
#include "acme/exception/not_implemented.h"
#include "nano2d/draw2d_context.h"
#include "aura/graphics/draw2d/graphics.h"
#include "_function.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include <math.h>
//#include <memory.h>

//#include NANO2D_INCLUDE
#include "context.h"

#define __NANO2D_CONTEXT(ctx) ((::nano2d::context *) (ctx)->p)


namespace nano2d
{




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
	//	float * m_faCommands;
	//	int m_ccommands;
	//	int m_ncommands;
	//	float m_fCommandX, m_fCommandY;
	//	::nano2d::state states[NVG_MAX_STATES];
	//	int m_nStates;
	//	NVGpathCache * m_ppathcache;
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

	
	::nano2d::state * context::__getState()
	{

		return &m_statea[this->m_nStates - 1];

		//return &states[m_nStates - 1];
		//throw not_implemented();
		//return nullptr;

	}

	//NANO2D_CONTEXT * context::CreateInternal)(NVGparams * params)
	//{
	//	FONSparams fontParams;
	//	NANO2D_CONTEXT * ctx = (NANO2D_CONTEXT *)malloc(sizeof(NANO2D_CONTEXT));
	//	int i;
	//	if (ctx == NULL) goto error;
	//	memory_set(ctx, 0, sizeof(NANO2D_CONTEXT));
	//
	//	params = *params;
	//	for (i = 0; i < NVG_MAX_FONTIMAGES; i++)
	//		fontImages[i] = 0;
	//
	//	m_faCommands = (float *)malloc(sizeof(float) * NVG_INIT_COMMANDS_SIZE);
	//	if (!m_faCommands) goto error;
	//	m_ncommands = 0;
	//	m_ccommands = NVG_INIT_COMMANDS_SIZE;
	//
	//	m_ppathcache = context::__allocPathCache)();
	//	if (m_ppathcache == NULL) goto error;
	//
	//	context::Save)(ctx);
	//	context::Reset)(ctx);
	//
	//	context::__setDevicePixelRatio)(ctx, 1.0f);
	//
	//	if (params.renderCreate(params.userPtr) == 0) goto error;
	//
	//	// Init font rendering
	//	memory_set(&fontParams, 0, sizeof(fontParams));
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
	//	context::DeleteInternal)(ctx);
	//	return 0;
	//}

	params * context::internal_params()
	{
		return &m_params;
	}

	//
	//void context::DeleteInternal()
	//{
	//	int i;
	//	if (ctx == NULL) return;
	//	if (m_faCommands != NULL) free(m_faCommands);
	//	if (m_ppathcache != NULL) context::__deletePathCache)(m_ppathcache);
	//
	//	if (fs)
	//		fonsDeleteInternal(fs);
	//
	//	for (i = 0; i < NVG_MAX_FONTIMAGES; i++) {
	//		if (fontImages[i] != 0) {
	//			context::DeleteImage)(ctx, fontImages[i]);
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
	void context::begin_frame(float windowWidth, float windowHeight, float devicePixelRatio)
	{
	//	/*	printf("Tris: draws:%d  fill:%d  stroke:%d  text:%d  TOT:%d\n",
	//			drawCallCount, fillTriCount, strokeTriCount, textTriCount,
	//			fillTriCount+strokeTriCount+textTriCount);*/
	//
	//	m_nStates = 0;
	//	context::Save)(ctx);
	//	context::Reset)(ctx);
	//
	//	context::__setDevicePixelRatio)(ctx, devicePixelRatio);
	//
	//	params.renderContext(params.userPtr, windowWidth, windowHeight, devicePixelRatio);
	//
	//	drawCallCount = 0;
	//	fillTriCount = 0;
	//	strokeTriCount = 0;
	//	textTriCount = 0;
	}
	//
	void context::cancel_frame()
	{
	//	params.renderCancel(params.userPtr);
	}
	//
	void context::end_frame()
	{
	//	params.renderFlush(params.userPtr);
	//	if (fontImageIdx != 0) {
	//		int fontImage = fontImages[fontImageIdx];
	//		int i, j, iw, ih;
	//		// delete images that smaller than current one
	//		if (fontImage == 0)
	//			return;
	//		context::ImageSize)(ctx, fontImage, &iw, &ih);
	//		for (i = j = 0; i < fontImageIdx; i++) {
	//			if (fontImages[i] != 0) {
	//				int nw, nh;
	//				context::ImageSize)(ctx, fontImages[i], &nw, &nh);
	//				if (nw < iw || nh < ih)
	//					context::DeleteImage)(ctx, fontImages[i]);
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
	}


	//void context::TransformIdentity)(float * t)
void TransformIdentity(float* t)
	{
		t[0] = 1.0f; t[1] = 0.0f;
		t[2] = 0.0f; t[3] = 1.0f;
		t[4] = 0.0f; t[5] = 0.0f;
	}

	//void context::TransformTranslate)(float * t, float tx, float ty)
void TransformTranslate(float* t, float tx, float ty)
	{
		t[0] = 1.0f; t[1] = 0.0f;
		t[2] = 0.0f; t[3] = 1.0f;
		t[4] = tx; t[5] = ty;
	}

	//void context::TransformScale)(float * t, float sx, float sy)
void TransformScale(float* t, float sx, float sy)
	{
		t[0] = sx; t[1] = 0.0f;
		t[2] = 0.0f; t[3] = sy;
		t[4] = 0.0f; t[5] = 0.0f;
	}

	//void context::TransformRotate)(float * t, float a)
void TransformRotate(float* t, float a)
	{
		float cs = __cosf(a);
		float sn = __sinf(a);
		t[0] = cs; t[1] = sn;
		t[2] = -sn; t[3] = cs;
		t[4] = 0.0f; t[5] = 0.0f;
	}

	//void context::TransformSkewX)(float * t, float a)
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

	//void context::TransformMultiply)(float * t, const float * s)
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

	//void context::TransformPremultiply)(float * t, const float * s)
	void TransformPremultiply(float* t, const float* s)
	{
		float s2[6];
		memory_copy(s2, s, sizeof(float) * 6);
		TransformMultiply(s2, t);
		memory_copy(t, s2, sizeof(float) * 6);
	}

	//int context::TransformInverse)(float * inv, const float * t)
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

	//float context::DegToRad)(float deg)
		float DegToRad(float deg)
	{
		return deg / 180.0f * ::nano2d::f_pi;
	}

	//float context::RadToDeg)(float rad)
		float RadToDeg(float rad)
	{
		return rad / ::nano2d::f_pi * 180.0f;
	}

	//static void context::__setPaintColor)(::nano2d::paint * p, ::color::color color)
	void __setPaintColor(::nano2d::paint* p, ::color::color color)
	{
		memory_set(p, 0, sizeof(*p));
		TransformIdentity(p->xform);
		p->radius = 0.0f;
		p->feather = 1.0f;
		p->innerColor = color;
		p->outerColor = color;
	}


	// State handling
	void context::save1()
	{
		//if (m_nStates >= NVG_MAX_STATES)
		//	return;
		//if (m_nStates > 0)
		//	memory_copy(&states[m_nStates], &states[m_nStates - 1], sizeof(::nano2d::state));
		//m_nStates++;

		//save();

	}

	
	void context::restore1()
	{
		
		//restore();
		//if (m_nStates <= 1)
		//	return;
		//m_nStates--;

	}


	void context::reset1()
	{

		::nano2d::state * state = __getState();

		memory_set(state, 0, sizeof(*state));

		__setPaintColor(&state->fill, argb(255, 255, 255, 255));
		__setPaintColor(&state->stroke, rgba(0, 0, 0, 255));
		state->compositeOperation = __compositeOperationState(::nano2d::e_composite_operation_source_over);
		state->shapeAntiAlias = 1;
		state->strokeWidth = 1.0f;
		state->miterLimit = 10.0f;
		state->lineCap = ::nano2d::e_line_cap_butt;
		state->lineJoin = ::nano2d::e_line_join_miter;
		state->alpha = 1.0f;
		TransformIdentity(state->xform);

		state->m_scissor.extent[0] = -1.0f;
		state->m_scissor.extent[1] = -1.0f;

		state->fontSize = 16.0f;
		state->letterSpacing = 0.0f;
		state->lineHeight = 1.0f;
		state->fontBlur = 0.0f;
		state->textAlign = ::nano2d::e_align_left | ::nano2d::e_align_baseline;
		state->fontId = 0;
	}

	// State setting
	void context::shape_anti_alias(int enabled)
	{
		::nano2d::state * state = __getState();
		state->shapeAntiAlias = enabled;
	}

	void context::stroke_width(float width)
	{
		//::nano2d::state * state = __getState();
		//state->strokeWidth = width;
		//return stroke_width(width);
	}


	void context::miter_limit(float limit)
	{

		::nano2d::state * state = __getState();

		state->miterLimit = limit;

	}


	void context::line_cap(int cap)
	{

		::nano2d::state * state = __getState();

		state->lineCap = cap;

	}


	void context::line_join(int join)
	{

		::nano2d::state * state = __getState();

		state->lineJoin = join;

	}


	void context::global_alpha(float alpha)
	{

		//::nano2d::state * state = __getState();
		//state->alpha = alpha;
		//global_alpha(alpha);

	}


	void context::transform(float a, float b, float c, float d, float e, float f)
	{
		
		::nano2d::state * state = __getState();

		float t[6] = { a, b, c, d, e, f };

		TransformPremultiply(state->xform, t);

	}


	void context::reset_transform()
	{

		::nano2d::state * state = __getState();

		TransformIdentity(state->xform);

	}


	void context::translate(float x, float y)
	{
		//::nano2d::state * state = __getState();
		//float t[6];
		//context::TransformTranslate)(t, x, y);
		//context::TransformPremultiply)(state->xform, t);

		//translate(x, y);

	}

	
	void context::rotate(float angle)
	{
		
		//::nano2d::state * state = __getState();
		//float t[6];
		//context::TransformRotate)(t, angle);
		//context::TransformPremultiply)(state->xform, t);
		//rotate(angle);

	}


	void context::skew_x(float angle)
	{
		::nano2d::state * state = __getState();
		float t[6];
		TransformSkewX(t, angle);
		TransformPremultiply(state->xform, t);
	}

	void context::skew_y(float angle)
	{
		::nano2d::state * state = __getState();
		float t[6];
		TransformSkewY(t, angle);
		TransformPremultiply(state->xform, t);
	}

	void context::scale(float x, float y)
	{
		::nano2d::state * state = __getState();
		float t[6];
		TransformScale(t, x, y);
		TransformPremultiply(state->xform, t);
	}


	void context::current_transform(float * xform)
	{
		::nano2d::state * state = __getState();
		if (xform == NULL) return;
		memory_copy(xform, state->xform, sizeof(float) * 6);
	}

	void context::stroke_color(::color::color color)
	{
		//::nano2d::state * state = __getState();
		//context::__setPaintColor)(&state->stroke, color);

		//stroke_color(color);

	}

	void context::stroke_paint(::nano2d::paint paint)
	{
		//::nano2d::state * state = __getState();
		//state->stroke = paint;
		//context::TransformMultiply)(state->stroke.xform, state->xform);

		//stroke_paint(paint);
	}

	void context::fill_color(::color::color color)
	{
		//::nano2d::state * state = __getState();
		//context::__setPaintColor)(&state->fill, color);

		//fill_color(color);

	}

	void context::fill_paint(::nano2d::paint paint)
	{
		//::nano2d::state * state = __getState();
		//state->fill = paint;
		//context::TransformMultiply)(state->fill.xform, state->xform);

		//fill_paint(paint);

	}

	#ifndef NVG_NO_STB
	int context::create_image(const ::scoped_string& scopedstrFilename, int imageFlags)
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
		//image = context::CreateImageRGBA)(ctx, w, h, imageFlags, img);
		//stbi_image_free(img);
		//return image;
		//return create_image(filename, imageFlags);
		return -1;

	}


	int context::create_image_mem(int imageFlags, unsigned char * data, int ndata)
	{
		//int w, h, n, image;
		//unsigned char * img = stbi_load_from_memory(data, ndata, &w, &h, &n, 4);
		//if (img == NULL) {
		//	//		printf("Failed to load %s - %s\n", filename, stbi_failure_reason());
		//	return 0;
		//}
		//image = context::CreateImageRGBA)(ctx, w, h, imageFlags, img);
		//stbi_image_free(img);
		//return image;
		return -1;
	}
	#endif

	
	int context::create_image_rgba(int w, int h, int imageFlags, const void * data, int iScan)
	{
		//return params.renderCreateTexture(params.userPtr, NVG_TEXTURE_RGBA, w, h, imageFlags, data);
		//return create_image_rgba(w, h, imageFlags, data, iScan);

		return -1;

	}


	void context::update_image(int image, const void * data)
	{
		//int w h;
		//params.renderGetTextureSize(params.userPtr, image, &w, &h);
		//params.renderUpdateTexture(params.userPtr, image, 0, 0, w, h, data);
		//return update_image(image, data);

		//re

	}


	void context::image_size(int image, int * w, int * h)
	{
		//params.renderGetTextureSize(params.userPtr, image, w, h);

		//image_size(image, w, h);

	}


	void context::delete_image(int image)
	{
	
		//params.renderDeleteTexture(params.userPtr, image);

	}

	
	::nano2d::paint context::linear_gradient(
		float sx, float sy, float ex, float ey,
		::color::color icol, ::color::color ocol)
	{

		//return linear_gradient(sx, sy, ex, ey, icol, ocol);
		//::nano2d::paint p;
		//float Δx, Δy, d;
		//const float large = 1e5;
		//NVG_NOTUSED(ctx);
		//memory_set(&p, 0, sizeof(p));

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

		//p.feather = context::__maxf)(1.0f, d);

		//p.innerColor = icol;
		//p.outerColor = ocol;

		//return p;
		return {};

	}


	::nano2d::paint context::radial_gradient(float cx, float cy, float inr, float outr, ::color::color icol, ::color::color ocol)
	{

		return {};


		//return radial_gradient(cx, cy, inr, outr, icol, ocol);
		//::nano2d::paint p;
		//float r = (inr + outr) * 0.5f;
		//float f = (outr - inr);
		//NVG_NOTUSED(ctx);
		//memory_set(&p, 0, sizeof(p));

		//context::TransformIdentity)(p.xform);
		//p.xform[4] = cx;
		//p.xform[5] = cy;

		//p.extent[0] = r;
		//p.extent[1] = r;

		//p.radius = r;

		//p.feather = context::__maxf)(1.0f, f);

		//p.innerColor = icol;
		//p.outerColor = ocol;

		//return p;
	}

	
	::nano2d::paint context::box_gradient(
		float x, float y, float w, float h, float r, float f,
		::color::color icol, ::color::color ocol)
	{

		return {};
		//return box_gradient(x, y, w, h, r, f, icol, ocol);
		//::nano2d::paint p;
		//NVG_NOTUSED(ctx);
		//memory_set(&p, 0, sizeof(p));

		//context::TransformIdentity)(p.xform);
		//p.xform[4] = x + w * 0.5f;
		//p.xform[5] = y + h * 0.5f;

		//p.extent[0] = w * 0.5f;
		//p.extent[1] = h * 0.5f;

		//p.radius = r;

		//p.feather = context::__maxf)(1.0f, f);

		//p.innerColor = icol;
		//p.outerColor = ocol;

		//return p;
	}


	::nano2d::paint context::image_pattern_from_index(float cx, float cy, float w, float h, float angle,
		float alpha, int image)
	{

		return {};

		//return image_pattern(cx, cy, w, h, angle, image, alpha);
		//::nano2d::paint p;
		//NVG_NOTUSED(ctx);
		//memory_set(&p, 0, sizeof(p));

		//context::TransformRotate)(p.xform, angle);
		//p.xform[4] = cx;
		//p.xform[5] = cy;

		//p.extent[0] = w;
		//p.extent[1] = h;

		//p.image = image;

		//p.innerColor = p.outerColor = context::RGBAf)(1, 1, 1, alpha);

		//return p;
	}


	::nano2d::paint context::image_pattern_from_image(float cx, float cy, float w, float h, float angle,
		float alpha, ::image * pimage)
	{

		return {};

	}

	// Scissoring
	void context::scissor(float x, float y, float w, float h)
	{
		//::nano2d::state * state = __getState();

		//w = context::__maxf)(0.0f, w);
		//h = context::__maxf)(0.0f, h);

		//context::TransformIdentity)(state->scissor.xform);
		//state->scissor.xform[4] = x + w * 0.5f;
		//state->scissor.xform[5] = y + h * 0.5f;
		//context::TransformMultiply)(state->scissor.xform, state->xform);

		//state->scissor.extent[0] = w * 0.5f;
		//state->scissor.extent[1] = h * 0.5f;
	}

	//static void context::__isectRects)(float * dst,
	//	float ax, float ay, float aw, float ah,
	//	float bx, float by, float bw, float bh)
	//{
	//	float minx = context::__maxf)(ax, bx);
	//	float miny = context::__maxf)(ay, by);
	//	float maxx = context::__minf)(ax + aw, bx + bw);
	//	float maxy = context::__minf)(ay + ah, by + bh);
	//	dst[0] = minx;
	//	dst[1] = miny;
	//	dst[2] = context::__maxf)(0.0f, maxx - minx);
	//	dst[3] = context::__maxf)(0.0f, maxy - miny);
	//}

	void context::intersect_scissor(float x, float y, float w, float h)
	{

		// intersect_scissor(x, y, w, h);
		//::nano2d::state * state = __getState();
		//float pxform[6], invxorm[6];
		//float rect[4];
		//float ex, ey, tex, tey;

		//// If no previous scissor has been set, set the scissor as current scissor.
		//if (state->scissor.extent[0] < 0) {
		//	context::Scissor)(ctx, x, y, w, h);
		//	return;
		//}

		//// Transform the current scissor rect into current transform space.
		//// If there is difference in rotation, this will be approximation.
		//memory_copy(pxform, state->scissor.xform, sizeof(float) * 6);
		//ex = state->scissor.extent[0];
		//ey = state->scissor.extent[1];
		//context::TransformInverse)(invxorm, state->xform);
		//context::TransformMultiply)(pxform, invxorm);
		//tex = ex * context::__absf)(pxform[0]) + ey * context::__absf)(pxform[2]);
		//tey = ex * context::__absf)(pxform[1]) + ey * context::__absf)(pxform[3]);

		//// Intersect rects.
		//context::__isectRects)(rect, pxform[4] - tex, pxform[5] - tey, tex * 2, tey * 2, x, y, w, h);

		//context::Scissor)(ctx, rect[0], rect[1], rect[2], rect[3]);
	}

	void context::reset_scissor()
	{
		//::nano2d::state * state = __getState();
		//memory_set(state->scissor.xform, 0, sizeof(state->scissor.xform));
		//state->scissor.extent[0] = -1.0f;
		//state->scissor.extent[1] = -1.0f;
		//reset_scissor();
	}

	
	// Global composite operation.
	void context::global_composite_operation(int op)
	{
		
		::nano2d::state * state = __getState();
		state->compositeOperation = __compositeOperationState(op);

	}


	void context::global_composite_blend_func(int sfactor, int dfactor)
	{
		
		global_composite_blend_func_separate(sfactor, dfactor, sfactor, dfactor);

	}


	void context::global_composite_blend_func_separate(int srcRGB, int dstRGB, int srcAlpha, int dstAlpha)
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


	void context::__append_commands(float * vals, int nvals)
	{

		::nano2d::state * state = __getState();

		int i;

		if (m_ncommands + nvals > m_ccommands) {
			float * faCommands;
			int ccommands = m_ncommands + nvals + m_ccommands / 2;
			faCommands = (float *)realloc(m_faCommands, sizeof(float) * ccommands);
			if (faCommands == NULL) return;
			m_faCommands = faCommands;
			m_ccommands = ccommands;
		}

		if ((int)vals[0] != ::nano2d::e_command_close && (int)vals[0] != ::nano2d::e_command_winding) {
			m_fCommandX = vals[nvals - 2];
			m_fCommandY = vals[nvals - 1];
		}

		// transform m_faCommands
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

		memory_copy(&m_faCommands[m_ncommands], vals, nvals * sizeof(float));

		m_ncommands += nvals;
	}


	//static void context::__clearPathCache()
	//{
	//	m_ppathcache->npoints = 0;
	//	m_ppathcache->npaths = 0;
	//}

	//static ::nano2d::path * context::__lastPath()
	//{
	//	if (m_ppathcache->npaths > 0)
	//		return &m_ppathcache->paths[m_ppathcache->npaths - 1];
	//	return NULL;
	//}

	//static void context::__addPath()
	//{
	//	::nano2d::path * path;
	//	if (m_ppathcache->npaths + 1 > m_ppathcache->cpaths) {
	//		::nano2d::path * paths;
	//		int cpaths = m_ppathcache->npaths + 1 + m_ppathcache->cpaths / 2;
	//		paths = (::nano2d::path *)realloc(m_ppathcache->paths, sizeof(::nano2d::path) * cpaths);
	//		if (paths == NULL) return;
	//		m_ppathcache->paths = paths;
	//		m_ppathcache->cpaths = cpaths;
	//	}
	//	path = &m_ppathcache->paths[m_ppathcache->npaths];
	//	memory_set(path, 0, sizeof(*path));
	//	path->first = m_ppathcache->npoints;
	//	path->winding = ::nano2d::e_winding_ccw;
	//
	//	m_ppathcache->npaths++;
	//}
	//
	//static NVGpoint * context::__lastPoint()
	//{
	//	if (m_ppathcache->npoints > 0)
	//		return &m_ppathcache->points[m_ppathcache->npoints - 1];
	//	return NULL;
	//}

	//static void context::__addPoint(float x, float y, int flags)
	//{
	//	::nano2d::path * path = context::__lastPath)(ctx);
	//	NVGpoint * pt;
	//	if (path == NULL) return;
	//
	//	if (path->count > 0 && m_ppathcache->npoints > 0) {
	//		pt = context::__lastPoint)(ctx);
	//		if (context::__ptEquals)(pt->x, pt->y, x, y, distTol)) {
	//			pt->flags |= flags;
	//			return;
	//		}
	//	}
	//
	//	if (m_ppathcache->npoints + 1 > m_ppathcache->cpoints) {
	//		NVGpoint * points;
	//		int cpoints = m_ppathcache->npoints + 1 + m_ppathcache->cpoints / 2;
	//		points = (NVGpoint *)realloc(m_ppathcache->points, sizeof(NVGpoint) * cpoints);
	//		if (points == NULL) return;
	//		m_ppathcache->points = points;
	//		m_ppathcache->cpoints = cpoints;
	//	}
	//
	//	pt = &m_ppathcache->points[m_ppathcache->npoints];
	//	memory_set(pt, 0, sizeof(*pt));
	//	pt->x = x;
	//	pt->y = y;
	//	pt->flags = (unsigned char)flags;
	//
	//	m_ppathcache->npoints++;
	//	path->count++;
	//}

	//static void context::__closePath()
	//{
	//	::nano2d::path * path = context::__lastPath)(ctx);
	//	if (path == NULL) return;
	//	path->closed = 1;
	//}

	//static void context::__pathWinding(int winding)
	//{
	//	::nano2d::path * path = context::__lastPath)(ctx);
	//	if (path == NULL) return;
	//	path->winding = winding;
	//}
	//
	//static float context::__getAverageScale)(float * t)
	//{
	//	float sx = sqrtf(t[0] * t[0] + t[2] * t[2]);
	//	float sy = sqrtf(t[1] * t[1] + t[3] * t[3]);
	//	return (sx + sy) * 0.5f;
	//}

	//static NVGvertex * context::__allocTempVerts(int nverts)
	//{
	//	if (nverts > m_ppathcache->cverts) {
	//		NVGvertex * verts;
	//		int cverts = (nverts + 0xff) & ~0xff; // Round up to prevent allocations when things change just slightly.
	//		verts = (NVGvertex *)realloc(m_ppathcache->verts, sizeof(NVGvertex) * cverts);
	//		if (verts == NULL) return NULL;
	//		m_ppathcache->verts = verts;
	//		m_ppathcache->cverts = cverts;
	//	}
	//
	//	return m_ppathcache->verts;
	//}
	//
	//static float context::__triarea2)(float ax, float ay, float bx, float by, float cx, float cy)
	//{
	//	float abx = bx - ax;
	//	float aby = by - ay;
	//	float acx = cx - ax;
	//	float acy = cy - ay;
	//	return acx * aby - abx * acy;
	//}

	//static float context::__polyArea)(NVGpoint * pts, int npts)
	//{
	//	int i;
	//	float area = 0;
	//	for (i = 2; i < npts; i++) {
	//		NVGpoint * a = &pts[0];
	//		NVGpoint * b = &pts[i - 1];
	//		NVGpoint * c = &pts[i];
	//		area += context::__triarea2)(a->x, a->y, b->x, b->y, c->x, c->y);
	//	}
	//	return area * 0.5f;
	//}

	//static void context::__polyReverse)(NVGpoint * pts, int npts)
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


	//static void context::__vset)(NVGvertex * vtx, float x, float y, float u, float v)
	//{
	//	vtx->x = x;
	//	vtx->y = y;
	//	vtx->u = u;
	//	vtx->v = v;
	//}

	//static void context::__tesselateBezier)(NANO2D_CONTEXT * ctx,
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
	//	d2 = context::__absf)(((x2 - x4) * Δy - (y2 - y4) * Δx));
	//	d3 = context::__absf)(((x3 - x4) * Δy - (y3 - y4) * Δx));
	//
	//	if ((d2 + d3) * (d2 + d3) < tessTol * (Δx * Δx + Δy * Δy)) {
	//		context::__addPoint)(ctx, x4, y4, type);
	//		return;
	//	}
	//
	//	/*	if (context::__absf)(x1+x3-x2-x2) + context::__absf)(y1+y3-y2-y2) + context::__absf)(x2+x4-x3-x3) + context::__absf)(y2+y4-y3-y3) < tessTol) {
	//			context::__addPoint)(ctx, x4, y4, type);
	//			return;
	//		}*/
	//
	//	x234 = (x23 + x34) * 0.5f;
	//	y234 = (y23 + y34) * 0.5f;
	//	x1234 = (x123 + x234) * 0.5f;
	//	y1234 = (y123 + y234) * 0.5f;
	//
	//	context::__tesselateBezier)(ctx, x1, y1, x12, y12, x123, y123, x1234, y1234, level + 1, 0);
	//	context::__tesselateBezier)(ctx, x1234, y1234, x234, y234, x34, y34, x4, y4, level + 1, type);
	//}

	//static void context::__flattenPaths()
	//{
	//	NVGpathCache * m_ppathcache = m_ppathcache;
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
	//	if (m_ppathcache->npaths > 0)
	//		return;
	//
	//	// Flatten
	//	i = 0;
	//	while (i < m_ncommands) {
	//		int cmd = (int)m_faCommands[i];
	//		switch (cmd) {
	//		case ::nano2d::e_command_move_to:
	//			context::__addPath)(ctx);
	//			p = &m_faCommands[i + 1];
	//			context::__addPoint)(ctx, p[0], p[1], NVG_PT_CORNER);
	//			i += 3;
	//			break;
	//		case ::nano2d::e_command_line_to:
	//			p = &m_faCommands[i + 1];
	//			context::__addPoint)(ctx, p[0], p[1], NVG_PT_CORNER);
	//			i += 3;
	//			break;
	//		case ::nano2d::e_command_bezier_to:
	//			last = context::__lastPoint)(ctx);
	//			if (last != NULL) {
	//				cp1 = &m_faCommands[i + 1];
	//				cp2 = &m_faCommands[i + 3];
	//				p = &m_faCommands[i + 5];
	//				context::__tesselateBezier)(ctx, last->x, last->y, cp1[0], cp1[1], cp2[0], cp2[1], p[0], p[1], 0, NVG_PT_CORNER);
	//			}
	//			i += 7;
	//			break;
	//		case ::nano2d::e_command_close:
	//			context::__closePath)(ctx);
	//			i++;
	//			break;
	//		case ::nano2d::e_command_winding:
	//			context::__pathWinding)(ctx, (int)m_faCommands[i + 1]);
	//			i += 2;
	//			break;
	//		default:
	//			i++;
	//		}
	//	}
	//
	//	m_ppathcache->bounds[0] = m_ppathcache->bounds[1] = 1e6f;
	//	m_ppathcache->bounds[2] = m_ppathcache->bounds[3] = -1e6f;
	//
	//	// Calculate the direction and length of line segments.
	//	for (j = 0; j < m_ppathcache->npaths; j++) {
	//		path = &m_ppathcache->paths[j];
	//		pts = &m_ppathcache->points[path->first];
	//
	//		// If the first and last points are the same, remove the last, mark as closed path.
	//		p0 = &pts[path->count - 1];
	//		p1 = &pts[0];
	//		if (context::__ptEquals)(p0->x, p0->y, p1->x, p1->y, distTol)) {
	//			path->count--;
	//			p0 = &pts[path->count - 1];
	//			path->closed = 1;
	//		}
	//
	//		// Enforce winding.
	//		if (path->count > 2) {
	//			area = context::__polyArea)(pts, path->count);
	//			if (path->winding == ::nano2d::e_winding_ccw && area < 0.0f)
	//				context::__polyReverse)(pts, path->count);
	//			if (path->winding == ::nano2d::e_winding_cw && area > 0.0f)
	//				context::__polyReverse)(pts, path->count);
	//		}
	//
	//		for (i = 0; i < path->count; i++) {
	//			// Calculate segment direction and length
	//			p0->Δx = p1->x - p0->x;
	//			p0->Δy = p1->y - p0->y;
	//			p0->len = context::__normalize)(&p0->Δx, &p0->Δy);
	//			// Update bounds
	//			m_ppathcache->bounds[0] = context::__minf)(m_ppathcache->bounds[0], p0->x);
	//			m_ppathcache->bounds[1] = context::__minf)(m_ppathcache->bounds[1], p0->y);
	//			m_ppathcache->bounds[2] = context::__maxf)(m_ppathcache->bounds[2], p0->x);
	//			m_ppathcache->bounds[3] = context::__maxf)(m_ppathcache->bounds[3], p0->y);
	//			// Advance
	//			p0 = p1++;
	//		}
	//	}
	//}

	//static int context::__curveDivs)(float r, float arc, float tol)
	//{
	//	float da = acosf(r / (r + tol)) * 2.0f;
	//	return context::__maxi)(2, (int)ceilf(arc / da));
	//}

	//static void context::__chooseBevel)(int bevel, NVGpoint * p0, NVGpoint * p1, float w,
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

	//static NVGvertex * context::__roundJoin)(NVGvertex * dst, NVGpoint * p0, NVGpoint * p1,
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
	//		context::__chooseBevel)(p1->flags & NVG_PR_INNERBEVEL, p0, p1, lw, &lx0, &ly0, &lx1, &ly1);
	//		a0 = atan2f(-dly0, -dlx0);
	//		a1 = atan2f(-dly1, -dlx1);
	//		if (a1 > a0) a1 -= ::nano2d::f_pi * 2;
	//
	//		context::__vset)(dst, lx0, ly0, lu, 1); dst++;
	//		context::__vset)(dst, p1->x - dlx0 * rw, p1->y - dly0 * rw, ru, 1); dst++;
	//
	//		n = context::__clampi)((int)ceilf(((a0 - a1) / ::nano2d::f_pi) * ncap), 2, ncap);
	//		for (i = 0; i < n; i++) {
	//			float u = i / (float)(n - 1);
	//			float a = a0 + u * (a1 - a0);
	//			float rx = p1->x + cosf(a) * rw;
	//			float ry = p1->y + sinf(a) * rw;
	//			context::__vset)(dst, p1->x, p1->y, 0.5f, 1); dst++;
	//			context::__vset)(dst, rx, ry, ru, 1); dst++;
	//		}
	//
	//		context::__vset)(dst, lx1, ly1, lu, 1); dst++;
	//		context::__vset)(dst, p1->x - dlx1 * rw, p1->y - dly1 * rw, ru, 1); dst++;
	//
	//	}
	//	else {
	//		float rx0, ry0, rx1, ry1, a0, a1;
	//		context::__chooseBevel)(p1->flags & NVG_PR_INNERBEVEL, p0, p1, -rw, &rx0, &ry0, &rx1, &ry1);
	//		a0 = atan2f(dly0, dlx0);
	//		a1 = atan2f(dly1, dlx1);
	//		if (a1 < a0) a1 += ::nano2d::f_pi * 2;
	//
	//		context::__vset)(dst, p1->x + dlx0 * rw, p1->y + dly0 * rw, lu, 1); dst++;
	//		context::__vset)(dst, rx0, ry0, ru, 1); dst++;
	//
	//		n = context::__clampi)((int)ceilf(((a1 - a0) / ::nano2d::f_pi) * ncap), 2, ncap);
	//		for (i = 0; i < n; i++) {
	//			float u = i / (float)(n - 1);
	//			float a = a0 + u * (a1 - a0);
	//			float lx = p1->x + cosf(a) * lw;
	//			float ly = p1->y + sinf(a) * lw;
	//			context::__vset)(dst, lx, ly, lu, 1); dst++;
	//			context::__vset)(dst, p1->x, p1->y, 0.5f, 1); dst++;
	//		}
	//
	//		context::__vset)(dst, p1->x + dlx1 * rw, p1->y + dly1 * rw, lu, 1); dst++;
	//		context::__vset)(dst, rx1, ry1, ru, 1); dst++;
	//
	//	}
	//	return dst;
	//}

	//static NVGvertex * context::__bevelJoin)(NVGvertex * dst, NVGpoint * p0, NVGpoint * p1,
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
	//		context::__chooseBevel)(p1->flags & NVG_PR_INNERBEVEL, p0, p1, lw, &lx0, &ly0, &lx1, &ly1);
	//
	//		context::__vset)(dst, lx0, ly0, lu, 1); dst++;
	//		context::__vset)(dst, p1->x - dlx0 * rw, p1->y - dly0 * rw, ru, 1); dst++;
	//
	//		if (p1->flags & NVG_PT_BEVEL) {
	//			context::__vset)(dst, lx0, ly0, lu, 1); dst++;
	//			context::__vset)(dst, p1->x - dlx0 * rw, p1->y - dly0 * rw, ru, 1); dst++;
	//
	//			context::__vset)(dst, lx1, ly1, lu, 1); dst++;
	//			context::__vset)(dst, p1->x - dlx1 * rw, p1->y - dly1 * rw, ru, 1); dst++;
	//		}
	//		else {
	//			rx0 = p1->x - p1->dmx * rw;
	//			ry0 = p1->y - p1->dmy * rw;
	//
	//			context::__vset)(dst, p1->x, p1->y, 0.5f, 1); dst++;
	//			context::__vset)(dst, p1->x - dlx0 * rw, p1->y - dly0 * rw, ru, 1); dst++;
	//
	//			context::__vset)(dst, rx0, ry0, ru, 1); dst++;
	//			context::__vset)(dst, rx0, ry0, ru, 1); dst++;
	//
	//			context::__vset)(dst, p1->x, p1->y, 0.5f, 1); dst++;
	//			context::__vset)(dst, p1->x - dlx1 * rw, p1->y - dly1 * rw, ru, 1); dst++;
	//		}
	//
	//		context::__vset)(dst, lx1, ly1, lu, 1); dst++;
	//		context::__vset)(dst, p1->x - dlx1 * rw, p1->y - dly1 * rw, ru, 1); dst++;
	//
	//	}
	//	else {
	//		context::__chooseBevel)(p1->flags & NVG_PR_INNERBEVEL, p0, p1, -rw, &rx0, &ry0, &rx1, &ry1);
	//
	//		context::__vset)(dst, p1->x + dlx0 * lw, p1->y + dly0 * lw, lu, 1); dst++;
	//		context::__vset)(dst, rx0, ry0, ru, 1); dst++;
	//
	//		if (p1->flags & NVG_PT_BEVEL) {
	//			context::__vset)(dst, p1->x + dlx0 * lw, p1->y + dly0 * lw, lu, 1); dst++;
	//			context::__vset)(dst, rx0, ry0, ru, 1); dst++;
	//
	//			context::__vset)(dst, p1->x + dlx1 * lw, p1->y + dly1 * lw, lu, 1); dst++;
	//			context::__vset)(dst, rx1, ry1, ru, 1); dst++;
	//		}
	//		else {
	//			lx0 = p1->x + p1->dmx * lw;
	//			ly0 = p1->y + p1->dmy * lw;
	//
	//			context::__vset)(dst, p1->x + dlx0 * lw, p1->y + dly0 * lw, lu, 1); dst++;
	//			context::__vset)(dst, p1->x, p1->y, 0.5f, 1); dst++;
	//
	//			context::__vset)(dst, lx0, ly0, lu, 1); dst++;
	//			context::__vset)(dst, lx0, ly0, lu, 1); dst++;
	//
	//			context::__vset)(dst, p1->x + dlx1 * lw, p1->y + dly1 * lw, lu, 1); dst++;
	//			context::__vset)(dst, p1->x, p1->y, 0.5f, 1); dst++;
	//		}
	//
	//		context::__vset)(dst, p1->x + dlx1 * lw, p1->y + dly1 * lw, lu, 1); dst++;
	//		context::__vset)(dst, rx1, ry1, ru, 1); dst++;
	//	}
	//
	//	return dst;
	//}

	//static NVGvertex * context::__buttCapStart)(NVGvertex * dst, NVGpoint * p,
	//	float Δx, float Δy, float w, float d,
	//	float aa, float u0, float u1)
	//{
	//	float px = p->x - Δx * d;
	//	float py = p->y - Δy * d;
	//	float dlx = Δy;
	//	float dly = -Δx;
	//	context::__vset)(dst, px + dlx * w - Δx * aa, py + dly * w - Δy * aa, u0, 0); dst++;
	//	context::__vset)(dst, px - dlx * w - Δx * aa, py - dly * w - Δy * aa, u1, 0); dst++;
	//	context::__vset)(dst, px + dlx * w, py + dly * w, u0, 1); dst++;
	//	context::__vset)(dst, px - dlx * w, py - dly * w, u1, 1); dst++;
	//	return dst;
	//}

	//static NVGvertex * context::__buttCapEnd)(NVGvertex * dst, NVGpoint * p,
	//	float Δx, float Δy, float w, float d,
	//	float aa, float u0, float u1)
	//{
	//	float px = p->x + Δx * d;
	//	float py = p->y + Δy * d;
	//	float dlx = Δy;
	//	float dly = -Δx;
	//	context::__vset)(dst, px + dlx * w, py + dly * w, u0, 1); dst++;
	//	context::__vset)(dst, px - dlx * w, py - dly * w, u1, 1); dst++;
	//	context::__vset)(dst, px + dlx * w + Δx * aa, py + dly * w + Δy * aa, u0, 0); dst++;
	//	context::__vset)(dst, px - dlx * w + Δx * aa, py - dly * w + Δy * aa, u1, 0); dst++;
	//	return dst;
	//}
	//

	//static NVGvertex * context::__roundCapStart)(NVGvertex * dst, NVGpoint * p,
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
	//		context::__vset)(dst, px - dlx * ax - Δx * ay, py - dly * ax - Δy * ay, u0, 1); dst++;
	//		context::__vset)(dst, px, py, 0.5f, 1); dst++;
	//	}
	//	context::__vset)(dst, px + dlx * w, py + dly * w, u0, 1); dst++;
	//	context::__vset)(dst, px - dlx * w, py - dly * w, u1, 1); dst++;
	//	return dst;
	//}

	//static NVGvertex * context::__roundCapEnd)(NVGvertex * dst, NVGpoint * p,
	//	float Δx, float Δy, float w, int ncap,
	//	float aa, float u0, float u1)
	//{
	//	int i;
	//	float px = p->x;
	//	float py = p->y;
	//	float dlx = Δy;
	//	float dly = -Δx;
	//	NVG_NOTUSED(aa);
	//	context::__vset)(dst, px + dlx * w, py + dly * w, u0, 1); dst++;
	//	context::__vset)(dst, px - dlx * w, py - dly * w, u1, 1); dst++;
	//	for (i = 0; i < ncap; i++) {
	//		float a = i / (float)(ncap - 1) * ::nano2d::f_pi;
	//		float ax = cosf(a) * w, ay = sinf(a) * w;
	//		context::__vset)(dst, px, py, 0.5f, 1); dst++;
	//		context::__vset)(dst, px - dlx * ax + Δx * ay, py - dly * ax + Δy * ay, u0, 1); dst++;
	//	}
	//	return dst;
	//}


	//static void context::__calculateJoins(float w, int lineJoin, float miterLimit)
	//{
	//	NVGpathCache * m_ppathcache = m_ppathcache;
	//	int i, j;
	//	float iw = 0.0f;
	//
	//	if (w > 0.0f) iw = 1.0f / w;
	//
	//	// Calculate which joins needs extra vertices to append, and gather vertex count.
	//	for (i = 0; i < m_ppathcache->npaths; i++) {
	//		::nano2d::path * path = &m_ppathcache->paths[i];
	//		NVGpoint * pts = &m_ppathcache->points[path->first];
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
	//			limit = context::__maxf)(1.01f, context::__minf)(p0->len, p1->len) * iw);
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


	//static int context::__expandStroke(float w, float fringe, int lineCap, int lineJoin, float miterLimit)
	//{
	//	NVGpathCache * m_ppathcache = m_ppathcache;
	//	NVGvertex * verts;
	//	NVGvertex * dst;
	//	int cverts, i, j;
	//	float aa = fringe;//fringeWidth;
	//	float u0 = 0.0f, u1 = 1.0f;
	//	int ncap = context::__curveDivs)(w, ::nano2d::f_pi, tessTol);	// Calculate divisions per half circle.
	//
	//	w += aa * 0.5f;
	//
	//	// Disable the gradient used for antialiasing when antialiasing is not used.
	//	if (aa == 0.0f) {
	//		u0 = 0.5f;
	//		u1 = 0.5f;
	//	}
	//
	//	context::__calculateJoins)(ctx, w, lineJoin, miterLimit);
	//
	//	// Calculate max vertex usage.
	//	cverts = 0;
	//	for (i = 0; i < m_ppathcache->npaths; i++) {
	//		::nano2d::path * path = &m_ppathcache->paths[i];
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
	//	verts = context::__allocTempVerts)(ctx, cverts);
	//	if (verts == NULL) return 0;
	//
	//	for (i = 0; i < m_ppathcache->npaths; i++) {
	//		::nano2d::path * path = &m_ppathcache->paths[i];
	//		NVGpoint * pts = &m_ppathcache->points[path->first];
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
	//			context::__normalize)(&Δx, &Δy);
	//			if (lineCap == ::nano2d::e_line_cap_butt)
	//				dst = context::__buttCapStart)(dst, p0, Δx, Δy, w, -aa * 0.5f, aa, u0, u1);
	//			else if (lineCap == ::nano2d::e_line_cap_butt || lineCap == NVG_SQUARE)
	//				dst = context::__buttCapStart)(dst, p0, Δx, Δy, w, w - aa, aa, u0, u1);
	//			else if (lineCap == NVG_ROUND)
	//				dst = context::__roundCapStart)(dst, p0, Δx, Δy, w, ncap, aa, u0, u1);
	//		}
	//
	//		for (j = s; j < e; ++j) {
	//			if ((p1->flags & (NVG_PT_BEVEL | NVG_PR_INNERBEVEL)) != 0) {
	//				if (lineJoin == NVG_ROUND) {
	//					dst = context::__roundJoin)(dst, p0, p1, w, w, u0, u1, ncap, aa);
	//				}
	//				else {
	//					dst = context::__bevelJoin)(dst, p0, p1, w, w, u0, u1, aa);
	//				}
	//			}
	//			else {
	//				context::__vset)(dst, p1->x + (p1->dmx * w), p1->y + (p1->dmy * w), u0, 1); dst++;
	//				context::__vset)(dst, p1->x - (p1->dmx * w), p1->y - (p1->dmy * w), u1, 1); dst++;
	//			}
	//			p0 = p1++;
	//		}
	//
	//		if (loop) {
	//			// Loop it
	//			context::__vset)(dst, verts[0].x(), verts[0].y(), u0, 1); dst++;
	//			context::__vset)(dst, verts[1].x(), verts[1].y(), u1, 1); dst++;
	//		}
	//		else {
	//			// Add cap
	//			Δx = p1->x - p0->x;
	//			Δy = p1->y - p0->y;
	//			context::__normalize)(&Δx, &Δy);
	//			if (lineCap == ::nano2d::e_line_cap_butt)
	//				dst = context::__buttCapEnd)(dst, p1, Δx, Δy, w, -aa * 0.5f, aa, u0, u1);
	//			else if (lineCap == ::nano2d::e_line_cap_butt || lineCap == NVG_SQUARE)
	//				dst = context::__buttCapEnd)(dst, p1, Δx, Δy, w, w - aa, aa, u0, u1);
	//			else if (lineCap == NVG_ROUND)
	//				dst = context::__roundCapEnd)(dst, p1, Δx, Δy, w, ncap, aa, u0, u1);
	//		}
	//
	//		path->nstroke = (int)(dst - verts);
	//
	//		verts = dst;
	//	}
	//
	//	return 1;
	//}

	//static int context::__expandFill(float w, int lineJoin, float miterLimit)
	//{
	//	NVGpathCache * m_ppathcache = m_ppathcache;
	//	NVGvertex * verts;
	//	NVGvertex * dst;
	//	int cverts, convex, i, j;
	//	float aa = fringeWidth;
	//	int fringe = w > 0.0f;
	//
	//	context::__calculateJoins)(ctx, w, lineJoin, miterLimit);
	//
	//	// Calculate max vertex usage.
	//	cverts = 0;
	//	for (i = 0; i < m_ppathcache->npaths; i++) {
	//		::nano2d::path * path = &m_ppathcache->paths[i];
	//		cverts += path->count + path->nbevel + 1;
	//		if (fringe)
	//			cverts += (path->count + path->nbevel * 5 + 1) * 2; // plus one for loop
	//	}
	//
	//	verts = context::__allocTempVerts)(ctx, cverts);
	//	if (verts == NULL) return 0;
	//
	//	convex = m_ppathcache->npaths == 1 && m_ppathcache->paths[0].convex;
	//
	//	for (i = 0; i < m_ppathcache->npaths; i++) {
	//		::nano2d::path * path = &m_ppathcache->paths[i];
	//		NVGpoint * pts = &m_ppathcache->points[path->first];
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
	//						context::__vset)(dst, lx, ly, 0.5f, 1); dst++;
	//					}
	//					else {
	//						float lx0 = p1->x + dlx0 * woff;
	//						float ly0 = p1->y + dly0 * woff;
	//						float lx1 = p1->x + dlx1 * woff;
	//						float ly1 = p1->y + dly1 * woff;
	//						context::__vset)(dst, lx0, ly0, 0.5f, 1); dst++;
	//						context::__vset)(dst, lx1, ly1, 0.5f, 1); dst++;
	//					}
	//				}
	//				else {
	//					context::__vset)(dst, p1->x + (p1->dmx * woff), p1->y + (p1->dmy * woff), 0.5f, 1); dst++;
	//				}
	//				p0 = p1++;
	//			}
	//		}
	//		else {
	//			for (j = 0; j < path->count; ++j) {
	//				context::__vset)(dst, pts[j].x(), pts[j].y(), 0.5f, 1);
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
	//					dst = context::__bevelJoin)(dst, p0, p1, lw, rw, lu, ru, fringeWidth);
	//				}
	//				else {
	//					context::__vset)(dst, p1->x + (p1->dmx * lw), p1->y + (p1->dmy * lw), lu, 1); dst++;
	//					context::__vset)(dst, p1->x - (p1->dmx * rw), p1->y - (p1->dmy * rw), ru, 1); dst++;
	//				}
	//				p0 = p1++;
	//			}
	//
	//			// Loop it
	//			context::__vset)(dst, verts[0].x(), verts[0].y(), lu, 1); dst++;
	//			context::__vset)(dst, verts[1].x(), verts[1].y(), ru, 1); dst++;
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
	void context::begin_path()
	{
		//m_ncommands = 0;
		//context::__clearPathCache)(ctx);

		//begin_path();

	}

	void context::move_to(float x, float y)
	{
		//float vals[] = { ::nano2d::e_command_move_to, x, y };
		//context::__appendCommands)(ctx, vals, NANO2D_COUNTOF(vals));
		//move_to(x, y);
	}

	void context::line_to(float x, float y)
	{
		/*float vals[] = { ::nano2d::e_command_line_to, x, y };
		context::__appendCommands)(ctx, vals, NANO2D_COUNTOF(vals));*/

		//line_to(x, y);
	}

	void context::bezier_to(float c1x, float c1y, float c2x, float c2y, float x, float y)
	{
		//float vals[] = { ::nano2d::e_command_bezier_to, c1x, c1y, c2x, c2y, x, y };
		//context::__appendCommands)(ctx, vals, NANO2D_COUNTOF(vals));
	}

	void context::quad_to(float cx, float cy, float x, float y)
	{
		//float x0 = m_fCommandX;
		//float y0 = m_fCommandY;
		//float vals[] = { ::nano2d::e_command_bezier_to,
		//	 x0 + 2.0f / 3.0f * (cx - x0), y0 + 2.0f / 3.0f * (cy - y0),
		//	 x + 2.0f / 3.0f * (cx - x), y + 2.0f / 3.0f * (cy - y),
		//	 x, y };
		//context::__appendCommands)(ctx, vals, NANO2D_COUNTOF(vals));
	}

	void context::arc_to(float x1, float y1, float x2, float y2, float radius)
	{
		//float x0 = m_fCommandX;
		//float y0 = m_fCommandY;
		//float dx0, dy0, dx1, dy1, a, d, cx, cy, a0, a1;
		//int dir;

		//if (m_ncommands == 0) {
		//	return;
		//}

		//// Handle degenerate cases.
		//if (context::__ptEquals)(x0, y0, x1, y1, distTol) ||
		//	context::__ptEquals)(x1, y1, x2, y2, distTol) ||
		//	context::__distPtSeg)(x1, y1, x0, y0, x2, y2) < distTol * distTol ||
		//	radius < distTol) {
		//	context::LineTo)(ctx, x1, y1);
		//	return;
		//}

		//// Calculate tangential circle to lines (x0,y0)-(x1,y1) and (x1,y1)-(x2,y2).
		//dx0 = x0 - x1;
		//dy0 = y0 - y1;
		//dx1 = x2 - x1;
		//dy1 = y2 - y1;
		//context::__normalize)(&dx0, &dy0);
		//context::__normalize)(&dx1, &dy1);
		//a = context::__acosf)(dx0 * dx1 + dy0 * dy1);
		//d = radius / context::__tanf)(a / 2.0f);

		////	printf("a=%fMATH_PI d=%f\n", a/::nano2d::f_pi*180.0f, d);

		//if (d > 10000.0f) {
		//	context::LineTo)(ctx, x1, y1);
		//	return;
		//}

		//if (context::__cross)(dx0, dy0, dx1, dy1) > 0.0f) {
		//	cx = x1 + dx0 * d + dy0 * radius;
		//	cy = y1 + dy0 * d + -dx0 * radius;
		//	a0 = context::__atan2f)(dx0, -dy0);
		//	a1 = context::__atan2f)(-dx1, dy1);
		//	dir = ::nano2d::e_winding_cw;
		//	//		printf("CW c=(%f, %f) a0=%fMATH_PI a1=%fMATH_PI\n", cx, cy, a0/::nano2d::f_pi*180.0f, a1/::nano2d::f_pi*180.0f);
		//}
		//else {
		//	cx = x1 + dx0 * d + -dy0 * radius;
		//	cy = y1 + dy0 * d + dx0 * radius;
		//	a0 = context::__atan2f)(-dx0, dy0);
		//	a1 = context::__atan2f)(dx1, -dy1);
		//	dir = ::nano2d::e_winding_ccw;
		//	//		printf("CCW c=(%f, %f) a0=%fMATH_PI a1=%fMATH_PI\n", cx, cy, a0/::nano2d::f_pi*180.0f, a1/::nano2d::f_pi*180.0f);
		//}

		//context::Arc)(ctx, cx, cy, radius, a0, a1, dir);
	}


	void context::close_path()
	{
		//float vals[] = { ::nano2d::e_command_close };
		//context::__appendCommands)(ctx, vals, NANO2D_COUNTOF(vals));
		//close_path();
	}


	void context::path_winding(int dir)
	{
		//float vals[] = { ::nano2d::e_command_winding, (float)dir };
		//context::__appendCommands)(ctx, vals, NANO2D_COUNTOF(vals));

		//path_winding(dir);

	}

	void context::arc(float cx, float cy, float r, ::angle_f32 a0, ::angle_f32 a1, int dir)
	{
		//arc(cx, cy, r, a0, a1, dir);
		//float a = 0, da = 0, hda = 0, kappa = 0;
		//float Δx = 0, Δy = 0, x = 0, y = 0, tanx = 0, tany = 0;
		//float px = 0, py = 0, ptanx = 0, ptany = 0;
		//float vals[3 + 5 * 7 + 100];
		//int i, ndivs, nvals;
		//int transfer = m_ncommands > 0 ? ::nano2d::e_command_line_to : ::nano2d::e_command_move_to;

		//// Clamp angles
		//da = a1 - a0;
		//if (dir == ::nano2d::e_winding_cw) {
		//	if (context::__absf)(da) >= ::nano2d::f_pi * 2) {
		//		da = ::nano2d::f_pi * 2;
		//	}
		//	else {
		//		while (da < 0.0f) da += ::nano2d::f_pi * 2;
		//	}
		//}
		//else {
		//	if (context::__absf)(da) >= ::nano2d::f_pi * 2) {
		//		da = -::nano2d::f_pi * 2;
		//	}
		//	else {
		//		while (da > 0.0f) da -= ::nano2d::f_pi * 2;
		//	}
		//}

		//// Split arc into max 90 degree segments.
		//ndivs = context::__maxi)(1, context::__mini)((int)(context::__absf)(da) / (::nano2d::f_pi * 0.5f) + 0.5f), 5));
		//hda = (da / (float)ndivs) / 2.0f;
		//kappa = context::__absf)(4.0f / 3.0f * (1.0f - context::__cosf)(hda)) / context::__sinf)(hda));

		//if (dir == ::nano2d::e_winding_ccw)
		//	kappa = -kappa;

		//nvals = 0;
		//for (i = 0; i <= ndivs; i++) {
		//	a = a0 + da * (i / (float)ndivs);
		//	Δx = context::__cosf)(a);
		//	Δy = context::__sinf)(a);
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

		//context::__appendCommands)(ctx, vals, nvals);
	}


	void context::rectangle(float x, float y, float w, float h)
	{
		//float vals[] = {
		//	::nano2d::e_command_move_to, x,y,
		//	::nano2d::e_command_line_to, x,y + h,
		//	::nano2d::e_command_line_to, x + w,y + h,
		//	::nano2d::e_command_line_to, x + w,y,
		//	::nano2d::e_command_close
		//};
		//context::__appendCommands)(ctx, vals, NANO2D_COUNTOF(vals));
		//rect(x, y, w, h);
	}


	void context::frame_pixel_perfect_rectangle(int x, int y, int w, int h, const ::color::color& color, int width)
	{


	}

	void context::rounded_rectangle(float x, float y, float w, float h, float r)
	{
	//	context::RoundedRectVarying)(ctx, x, y, w, h, r, r, r, r);

		//rounded_rect(x, y, w, h, r);

	}


	void context::rounded_rectangle_varying(float x, float y, float w, float h, float radTopLeft, float radTopRight, float radBottomRight, float radBottomLeft)
	{
		//if (radTopLeft < 0.1f && radTopRight < 0.1f && radBottomRight < 0.1f && radBottomLeft < 0.1f) {
		//	context::Rect)(ctx, x, y, w, h);
		//	return;
		//}
		//else {
		//	float halfw = context::__absf)(w) * 0.5f;
		//	float halfh = context::__absf)(h) * 0.5f;
		//	float rxBL = context::__minf)(radBottomLeft, halfw) * context::__signf)(w), ryBL = context::__minf)(radBottomLeft, halfh) * context::__signf)(h);
		//	float rxBR = context::__minf)(radBottomRight, halfw) * context::__signf)(w), ryBR = context::__minf)(radBottomRight, halfh) * context::__signf)(h);
		//	float rxTR = context::__minf)(radTopRight, halfw) * context::__signf)(w), ryTR = context::__minf)(radTopRight, halfh) * context::__signf)(h);
		//	float rxTL = context::__minf)(radTopLeft, halfw) * context::__signf)(w), ryTL = context::__minf)(radTopLeft, halfh) * context::__signf)(h);
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
		//	context::__appendCommands)(ctx, vals, NANO2D_COUNTOF(vals));
		//}
	}


	void context::ellipse(float cx, float cy, float rx, float ry)
	{
		//float vals[] = {
		//	::nano2d::e_command_move_to, cx - rx, cy,
		//	::nano2d::e_command_bezier_to, cx - rx, cy + ry * NANO2D_KAPPA90, cx - rx * NANO2D_KAPPA90, cy + ry, cx, cy + ry,
		//	::nano2d::e_command_bezier_to, cx + rx * NANO2D_KAPPA90, cy + ry, cx + rx, cy + ry * NANO2D_KAPPA90, cx + rx, cy,
		//	::nano2d::e_command_bezier_to, cx + rx, cy - ry * NANO2D_KAPPA90, cx + rx * NANO2D_KAPPA90, cy - ry, cx, cy - ry,
		//	::nano2d::e_command_bezier_to, cx - rx * NANO2D_KAPPA90, cy - ry, cx - rx, cy - ry * NANO2D_KAPPA90, cx - rx, cy,
		//	::nano2d::e_command_close
		//};
		//context::__appendCommands)(ctx, vals, NANO2D_COUNTOF(vals));

		//ellipse(cx, cy, rx, ry);

	}


	void context::circle(float cx, float cy, float r)
	{
		
		ellipse(cx, cy, r, r);

	}


	void context::debug_dump_path_cache()
	{
		const ::nano2d::path * path;
		int i, j;

		printf("Dumping %d cached paths\n", m_ppathcache->npaths);
		for (i = 0; i < m_ppathcache->npaths; i++) {
			path = &m_ppathcache->paths[i];
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


	void context::fill()
	{

		//::nano2d::state * state = __getState();
		//const ::nano2d::path * path;
		//::nano2d::paint fillPaint = state->fill;
		//int i;

		//context::__flattenPaths)(ctx);
		//if (params.edgeAntiAlias && state->shapeAntiAlias)
		//	context::__expandFill)(ctx, fringeWidth, ::nano2d::e_line_join_miter, 2.4f);
		//else
		//	context::__expandFill)(ctx, 0.0f, ::nano2d::e_line_join_miter, 2.4f);

		//// Apply global alpha
		//fillPaint.innerColor.a *= state->alpha;
		//fillPaint.outerColor.a *= state->alpha;

		//params.renderFill(params.userPtr, &fillPaint, state->compositeOperation, &state->scissor, fringeWidth,
		//	m_ppathcache->bounds, m_ppathcache->paths, m_ppathcache->npaths);

		//// Count triangles
		//for (i = 0; i < m_ppathcache->npaths; i++) {
		//	path = &m_ppathcache->paths[i];
		//	fillTriCount += path->nfill - 2;
		//	fillTriCount += path->nstroke - 2;
		//	drawCallCount += 2;
		//}

		//fill();

	}


	void context::stroke()
	{

		//stroke();


		//::nano2d::state * state = __getState();
		//float scale = context::__getAverageScale)(state->xform);
		//float strokeWidth = context::__clampf)(state->strokeWidth * scale, 0.0f, 200.0f);
		//::nano2d::paint strokePaint = state->stroke;
		//const ::nano2d::path * path;
		//int i;


		//if (strokeWidth < fringeWidth) {
		//	// If the stroke width is less than pixel size, use alpha to emulate coverage.
		//	// Since coverage is area, scale by alpha*alpha.
		//	float alpha = context::__clampf)(strokeWidth / fringeWidth, 0.0f, 1.0f);
		//	strokePaint.innerColor.a *= alpha * alpha;
		//	strokePaint.outerColor.a *= alpha * alpha;
		//	strokeWidth = fringeWidth;
		//}

		//// Apply global alpha
		//strokePaint.innerColor.a *= state->alpha;
		//strokePaint.outerColor.a *= state->alpha;

		//context::__flattenPaths)(ctx);

		//if (params.edgeAntiAlias && state->shapeAntiAlias)
		//	context::__expandStroke)(ctx, strokeWidth * 0.5f, fringeWidth, state->lineCap, state->lineJoin, state->miterLimit);
		//else
		//	context::__expandStroke)(ctx, strokeWidth * 0.5f, 0.0f, state->lineCap, state->lineJoin, state->miterLimit);

		//params.renderStroke(params.userPtr, &strokePaint, state->compositeOperation, &state->scissor, fringeWidth,
		//	strokeWidth, m_ppathcache->paths, m_ppathcache->npaths);

		//// Count triangles
		//for (i = 0; i < m_ppathcache->npaths; i++) {
		//	path = &m_ppathcache->paths[i];
		//	strokeTriCount += path->nstroke - 2;
		//	drawCallCount++;
		//}
	}

	// Add fonts
	//int context::CreateFont(const char * name, const char * filename)
	//{
	//	//return fonsAddFont(fs, name, filename, 0);
	//	return -1;
	//}

	int context::create_font_at_index(const ::scoped_string& name, const ::scoped_string& filename, const int fontIndex)
	{
		//return fonsAddFont(fs, name, filename, fontIndex);
		return -1;
	}


	int context::create_font_mem(const ::scoped_string& name, unsigned char * data, int ndata, int freeData)
	{
	
		//return fonsAddFontMem(fs, name, data, ndata, freeData, 0);
		return -1;

	}


	int context::create_font_mem_at_index(const ::scoped_string& name, unsigned char * data, int ndata, int freeData, const int fontIndex)
	{
	
		//return fonsAddFontMem(fs, name, data, ndata, freeData, fontIndex);
		return -1;

	}


	int context::find_font(const ::scoped_string& name)
	{

		//if (name == NULL) return -1;
		//return fonsGetFontByName(fs, name);
		return -1;

	}


	int context::add_fallback_font_id(int baseFont, int fallbackFont)
	{
		//if (baseFont == -1 || fallbackFont == -1) return 0;
		//return fonsAddFallbackFont(fs, baseFont, fallbackFont);
		return -1;
	}

	
	int context::add_fallback_font(const ::scoped_string& baseFont, const ::scoped_string& fallbackFont)
	{
		//return context::AddFallbackFontId)(ctx, context::FindFont)(ctx, baseFont), context::FindFont)(ctx, fallbackFont));
		return -1;
	}


	void context::reset_fallback_fonts_id(int baseFont)
	{
		//fonsResetFallbackFont(fs, baseFont);
		return;
	}


	void context::reset_fallback_fonts(const ::scoped_string& baseFont)
	{
		//context::ResetFallbackFontsId)(ctx, context::FindFont)(ctx, baseFont));
		return;
	}


	// State setting
	void context::font_size(float size)
	{
		//::nano2d::state * state = __getState();
		//state->fontSize = size;
		//font_size(size);

	}

	
	void context::font_blur(float blur)
	{
		
		//::nano2d::state * state = __getState();
		//state->fontBlur = blur;
		//throw_todo();
		//font_blur(blur);

	}


	//::write_text::font_pointer context::CreateFont(const char * face, float size)
	//{
	//   
	//   return create_font(face, size);
	//   
	//}


	void context::text_letter_spacing(float spacing)
	{
		
		//::nano2d::state * state = __getState();
		//state->letterSpacing = spacing;
		throw_todo();

	}

	
	void context::text_line_height(float lineHeight)
	{
		//::nano2d::state * state = __getState();
		//state->lineHeight = lineHeight;
		//text_line_height(lineHeight);

	}

	
	void context::text_align(int align)
	{

		//::nano2d::state * state = __getState();
		//state->textAlign = align;

		//text_align(align);

	}


	void context::font_face_id(int font)
	{
	
		//::nano2d::state * state = __getState();
		//state->fontId = font;
		throw_todo();

	}


	void context::font_face(const ::scoped_string& font)
	{
		//::nano2d::state * state = __getState();
		//state->fontId = fonsGetFontByName(fs, font);

		//font_face(font);

	}


	//static float context::__quantize)(float a, float d)
	//{
	//	return ((int)(a / d + 0.5f)) * d;
	//}

	//static float context::__getFontScale)(::nano2d::state * state)
	//{
	//	return context::__minf)(context::__quantize)(context::__getAverageScale)(state->xform), 0.01f), 4.0f);
	//}

	//static void context::__flushTextTexture()
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

	//static int context::__allocTextAtlas()
	//{
	//	//int iw, ih;
	//	//context::__flushTextTexture)(ctx);
	//	//if (fontImageIdx >= NVG_MAX_FONTIMAGES - 1)
	//	//	return 0;
	//	//// if next fontImage already have a texture
	//	//if (fontImages[fontImageIdx + 1] != 0)
	//	//	context::ImageSize)(ctx, fontImages[fontImageIdx + 1], &iw, &ih);
	//	//else { // calculate the memory_new font image size and create it.
	//	//	context::ImageSize)(ctx, fontImages[fontImageIdx], &iw, &ih);
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
	//static void context::__renderText(NVGvertex * verts, int nverts)
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
	//static int context::__isTransformFlipped)(const float * xform)
	//{
	//	/*float det = xform[0] * xform[3] - xform[2] * xform[1];
	//	return(det < 0);*/
	//	throw_todo();
	//	return -1;
	//}
	//
	float context::text(float x, float y, const ::scoped_string& scopedstr)
	{

		//::nano2d::state * state = __getState();
		//FONStextIter iter, prevIter;
		//FONSquad q;
		//NVGvertex * verts;
		//float scale = context::__getFontScale)(state) * devicePxRatio;
		//float invscale = 1.0f / scale;
		//int cverts = 0;
		//int nverts = 0;
		//int isFlipped = context::__isTransformFlipped)(state->xform);

		//if (end == NULL)
		//	end = string + strlen(string);

		//if (state->fontId == FONS_INVALID) return x;

		//fonsSetSize(fs, state->fontSize * scale);
		//fonsSetSpacing(fs, state->letterSpacing * scale);
		//fonsSetBlur(fs, state->fontBlur * scale);
		//fonsSetAlign(fs, state->textAlign);
		//fonsSetFont(fs, state->fontId);

		//cverts = context::__maxi)(2, (int)(end - string)) * 6; // conservative estimate.
		//verts = context::__allocTempVerts)(ctx, cverts);
		//if (verts == NULL) return x;

		//fonsTextIterInit(fs, &iter, x * scale, y * scale, string, end, FONS_GLYPH_BITMAP_REQUIRED);
		//prevIter = iter;
		//while (fonsTextIterNext(fs, &iter, &q)) {
		//	float c[4 * 2];
		//	if (iter.prevGlyphIndex == -1) { // can not retrieve glyph?
		//		if (nverts != 0) {
		//			context::__renderText)(ctx, verts, nverts);
		//			nverts = 0;
		//		}
		//		if (!context::__allocTextAtlas)(ctx))
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
		//		context::__vset)(&verts[nverts], c[0], c[1], q.s0, q.t0); nverts++;
		//		context::__vset)(&verts[nverts], c[4], c[5], q.s1, q.t1); nverts++;
		//		context::__vset)(&verts[nverts], c[2], c[3], q.s1, q.t0); nverts++;
		//		context::__vset)(&verts[nverts], c[0], c[1], q.s0, q.t0); nverts++;
		//		context::__vset)(&verts[nverts], c[6], c[7], q.s0, q.t1); nverts++;
		//		context::__vset)(&verts[nverts], c[4], c[5], q.s1, q.t1); nverts++;
		//	}
		//}

		//// TODO: add back-end bit to do this just once per frame.
		//context::__flushTextTexture)(ctx);

		//context::__renderText)(ctx, verts, nverts);

		//return iter.nextx / scale;

		//return text(x, y, string, end);
		return 0.f;

	}


	void context::text_box(float x, float y, float breakRowWidth, const ::scoped_string& scopedstr)
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

		//context::TextMetrics)(ctx, NULL, NULL, &lineh);

		//state->textAlign = ::nano2d::e_align_left | valign;

		//while ((nrows = context::TextBreakLines)(ctx, string, end, breakRowWidth, rows, 2))) {
		//	for (i = 0; i < nrows; i++) {
		//		::nano2d::text_row * row = &rows[i];
		//		if (haling & ::nano2d::e_align_left)
		//			context::Text)(ctx, x, y, row->start, row->end);
		//		else if (haling & ::nano2d::e_align_center)
		//			context::Text)(ctx, x + breakRowWidth * 0.5f - row->width * 0.5f, y, row->start, row->end);
		//		else if (haling & ::nano2d::e_align_right)
		//			context::Text)(ctx, x + breakRowWidth - row->width, y, row->start, row->end);
		//		y += lineh * state->lineHeight;
		//	}
		//	string = rows[nrows - 1].next;
		//}

		//state->textAlign = oldAlign;
	}


	int context::text_glyph_positions(float x, float y, const ::scoped_string& scopedstr, ::nano2d::glyphPosition * positions, int maxPositions)
	{

		//return text_glyph_positions(x, y, scopedstr, positions, maxPositions);

		//throw_todo();
		//return -1;
		//::nano2d::state * state = __getState();
		//float scale = context::__getFontScale)(state) * devicePxRatio;
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
		//	if (iter.prevGlyphIndex < 0 && context::__allocTextAtlas)(ctx)) { // can not retrieve glyph?
		//		iter = prevIter;
		//		fonsTextIterNext(fs, &iter, &q); // try again
		//	}
		//	prevIter = iter;
		//	positions[npos].str = iter.str;
		//	positions[npos].x() = iter.x() * invscale;
		//	positions[npos].minx = context::__minf)(iter.x(), q.x0) * invscale;
		//	positions[npos].maxx = context::__maxf)(iter.nextx, q.x1) * invscale;
		//	npos++;
		//	if (npos >= maxPositions)
		//		break;
		//}

		//return npos;
      return 0;
	}



	int context::text_break_lines(const ::scoped_string& scopedstr, float breakRowWidth, ::nano2d::text_row * rows, int maxRows)
	{

		throw_todo();
		return -1;
		//::nano2d::state * state = __getState();
		//float scale = context::__getFontScale)(state) * devicePxRatio;
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
		//	if (iter.prevGlyphIndex < 0 && context::__allocTextAtlas)(ctx)) { // can not retrieve glyph?
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
		//		// Always handle memory_new lines.
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

		//			// Break to memory_new line when a character is beyond break width.
		//			if ((type == NVG_CHAR || type == NVG_CJK_CHAR) && nextWidth > breakRowWidth) {
		//				// The run length is too long, need to break to memory_new line.
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
		//					// Break the line from the end of the last word, and start memory_new line from the beginning of the memory_new.
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

		//// Break the line from the end of the last word, and start memory_new line from the beginning of the memory_new.
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


	float context::text_bounds(float x, float y, const ::scoped_string& string, float * bounds)
	{

		//return text_bounds(x, y, string, end, bounds);
		//::nano2d::state * state = __getState();
		//float scale = context::__getFontScale)(state) * devicePxRatio;
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

		return 0.f;

	}


	void context::text_box_bounds(float x, float y, float breakRowWidth, const ::scoped_string& string, float * bounds)
	{

		//text_bounds(x, y, string, end, bounds);

	//
	//	//::nano2d::state * state = __getState();
	//	::nano2d::text_row rows[2];
	//	float scale = context::__getFontScale)(state) * devicePxRatio;
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
	//	context::TextMetrics)(ctx, NULL, NULL, &lineh);
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
	//	while ((nrows = context::TextBreakLines)(ctx, string, end, breakRowWidth, rows, 2))) {
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
	//			minx = context::__minf)(minx, rminx);
	//			maxx = context::__maxf)(maxx, rmaxx);
	//			// Vertical bounds.
	//			miny = context::__minf)(miny, y + rminy);
	//			maxy = context::__maxf)(maxy, y + rmaxy);
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

	void context::text_metrics(float * ascender, float * descender, float * lineh)
	{
		//::nano2d::state * state = __getState();
		//float scale = context::__getFontScale)(state) * devicePxRatio;
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

	void context::_draw_image(float x, float y, float w, float h, ::image* pimage)
	{


	}


} // namespace nano2d





CLASS_DECL_NANO2D ::object* get_nano2d_object(::nano2d::context* pcontext)
{

	::pointer < ::nano2d::draw2d_context > pdraw2dcontext = pcontext;

	if (pdraw2dcontext)
	{

		return pdraw2dcontext->get_graphics();

	}

	return nullptr;

}
