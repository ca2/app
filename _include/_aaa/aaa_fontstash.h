//
// Copyright (c) 2009-2013 Mikko Mononen memon@inside.org
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

#ifndef FONS_H
#define FONS_H

#define FONS_INVALID -1

enum FONSflags {
	FONS_ZERO_TOPLEFT = 1,
	FONS_ZERO_BOTTOMLEFT = 2,
};

enum FONSalign {
	// Horizontal align
	FONS_ALIGN_LEFT = 1 << 0,	// Default
	FONS_ALIGN_CENTER = 1 << 1,
	FONS_ALIGN_RIGHT = 1 << 2,
	// Vertical align
	FONS_ALIGN_TOP = 1 << 3,
	FONS_ALIGN_MIDDLE = 1 << 4,
	FONS_ALIGN_BOTTOM = 1 << 5,
	FONS_ALIGN_BASELINE = 1 << 6, // Default
};

enum FONSglyphBitmap {
	FONS_GLYPH_BITMAP_OPTIONAL = 1,
	FONS_GLYPH_BITMAP_REQUIRED = 2,
};

enum FONSerrorCode {
	// Font atlas is full.
	FONS_ATLAS_FULL = 1,
	// Scratch memory used to render glyphs is full, requested size reported in 'val', you may need to bump up FONS_SCRATCH_BUF_SIZE.
	FONS_SCRATCH_FULL = 2,
	// Calls to fonsPushState has created too large stack, if you need deep state stack bump up FONS_MAX_STATES.
	FONS_STATES_OVERFLOW = 3,
	// Trying to pop too many states fonsPopState().
	FONS_STATES_UNDERFLOW = 4,
};

struct FONSparams {
	::i32 width, height;
	::u8 flags;
	void * userPtr;
	::i32 (*renderCreate)(void * uptr, ::i32 width, ::i32 height);
	::i32 (*renderResize)(void * uptr, ::i32 width, ::i32 height);
	void (*renderUpdate)(void * uptr, ::i32 * rect, const ::u8 * data);
	void (*renderDraw)(void * uptr, const ::f32 * verts, const ::f32 * tcoords, const ::u32 * colors, ::i32 nverts);
	void (*renderDelete)(void * uptr);
};
typedef struct FONSparams FONSparams;

struct FONSquad
{
	::f32 x0, y0, s0, t0;
	::f32 x1, y1, s1, t1;
};
typedef struct FONSquad FONSquad;

struct FONStextIter {
	::f32 x, y, nextx, nexty, scale, spacing;
	::u32 codepoint;
	::i16 isize, iblur;
	struct FONSfont * font;
	::i32 prevGlyphIndex;
	const_char_pointer str;
	const_char_pointer next;
	const_char_pointer end;
	::u32 utf8state;
	::i32 bitmapOption;
};
typedef struct FONStextIter FONStextIter;

typedef struct FONScontext FONScontext;

// Constructor and destructor.
FONScontext * fonsCreateInternal(FONSparams * params);
void fonsDeleteInternal(FONScontext * s);

void fonsSetErrorCallback(FONScontext * s, void (*callback)(void * uptr, ::i32 error, ::i32 val), void * uptr);
// Returns current atlas size.
void fonsGetAtlasSize(FONScontext * s, ::i32 * width, ::i32 * height);
// Expands the atlas size.
::i32 fonsExpandAtlas(FONScontext * s, ::i32 width, ::i32 height);
// Resets the whole stash.
::i32 fonsResetAtlas(FONScontext * stash, ::i32 width, ::i32 height);

// Add fonts
::i32 fonsAddFont(FONScontext * s, const_char_pointer pszName, const ::file::path & path, ::i32 fontIndex);
::i32 fonsAddFontMem(FONScontext * s, const_char_pointer pszName, ::u8 * data, ::i32 ndata, ::i32 freeData, ::i32 fontIndex);
::i32 fonsGetFontByName(FONScontext * s, const_char_pointer pszName);

// State handling
void fonsPushState(FONScontext * s);
void fonsPopState(FONScontext * s);
void fonsClearState(FONScontext * s);

// State setting
void fonsSetSize(FONScontext * s, ::f32 size);
void fonsSetColor(FONScontext * s, ::u32 color);
void fonsSetSpacing(FONScontext * s, ::f32 spacing);
void fonsSetBlur(FONScontext * s, ::f32 blur);
void fonsSetAlign(FONScontext * s, ::i32 align);
void fonsSetFont(FONScontext * s, ::i32 font);

// Draw text
::f32 fonsDrawText(FONScontext * s, ::f32 x, ::f32 y, const_char_pointer string, const_char_pointer end);

// Measure text
::f32 fonsTextBounds(FONScontext * s, ::f32 x, ::f32 y, const_char_pointer string, const_char_pointer end, ::f32 * bounds);
void fonsLineBounds(FONScontext * s, ::f32 y, ::f32 * miny, ::f32 * maxy);
void fonsVertMetrics(FONScontext * s, ::f32 * ascender, ::f32 * descender, ::f32 * lineh);

// Text iterator
::i32 fonsTextIterInit(FONScontext * stash, FONStextIter * iter, ::f32 x, ::f32 y, const_char_pointer str, const_char_pointer end, ::i32 bitmapOption);
::i32 fonsTextIterNext(FONScontext * stash, FONStextIter * iter, struct FONSquad * quad);

// Pull texture changes
const ::u8 * fonsGetTextureData(FONScontext * stash, ::i32 * width, ::i32 * height);
::i32 fonsValidateTexture(FONScontext * s, ::i32 * dirty);

// Draws the stash texture for debugging
void fonsDrawDebug(FONScontext * s, ::f32 x, ::f32 y);

#endif // FONTSTASH_H


#ifdef FONTSTASH_IMPLEMENTATION

#define FONS_NOTUSED(v)  (void)sizeof(v)

#ifdef FONS_USE_FREETYPE

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_ADVANCES_H
#include <math.h>

struct FONSttFontImpl {
	FT_Face font;
};
typedef struct FONSttFontImpl FONSttFontImpl;

#else

#define STB_TRUETYPE_IMPLEMENTATION

static void * fons__tmpalloc(size_t size, void * up);
static void fons__tmpfree(void * ptr, void * up);
#define STBTT_malloc(x,u)    fons__tmpalloc(x,u)
#define STBTT_free(x,u)      fons__tmpfree(x,u)
#include "stb_truetype.h"

struct FONSttFontImpl {
	stbtt_fontinfo font;
};
typedef struct FONSttFontImpl FONSttFontImpl;

#endif

#ifndef FONS_SCRATCH_BUF_SIZE
#	define FONS_SCRATCH_BUF_SIZE 96000
#endif
#ifndef FONS_HASH_LUT_SIZE
#	define FONS_HASH_LUT_SIZE 256
#endif
#ifndef FONS_INIT_FONTS
#	define FONS_INIT_FONTS 4
#endif
#ifndef FONS_INIT_GLYPHS
#	define FONS_INIT_GLYPHS 256
#endif
#ifndef FONS_INIT_ATLAS_NODES
#	define FONS_INIT_ATLAS_NODES 256
#endif
#ifndef FONS_VERTEX_COUNT
#	define FONS_VERTEX_COUNT 1024
#endif
#ifndef FONS_MAX_STATES
#	define FONS_MAX_STATES 20
#endif
#ifndef FONS_MAX_FALLBACKS
#	define FONS_MAX_FALLBACKS 20
#endif

static ::u32 fons__hashint(::u32 a)
{
	a += ~(a << 15);
	a ^= (a >> 10);
	a += (a << 3);
	a ^= (a >> 6);
	a += ~(a << 11);
	a ^= (a >> 16);
	return a;
}

static ::i32 fons__mini(::i32 a, ::i32 b)
{
	return a < b ? a : b;
}

static ::i32 fons__maxi(::i32 a, ::i32 b)
{
	return a > b ? a : b;
}

struct FONSglyph
{
	::u32 codepoint;
	::i32 index;
	::i32 next;
	::i16 size, blur;
	::i16 x0, y0, x1, y1;
	::i16 xadv, xoff, yoff;
};
typedef struct FONSglyph FONSglyph;

struct FONSfont
{
	FONSttFontImpl font;
	::i8 name[64];
	::u8 * data;
	::i32 dataSize;
	::u8 freeData;
	::f32 ascender;
	::f32 descender;
	::f32 lineh;
	FONSglyph * glyphs;
	::i32 cglyphs;
	::i32 nglyphs;
	::i32 lut[FONS_HASH_LUT_SIZE];
	::i32 fallbacks[FONS_MAX_FALLBACKS];
	::i32 nfallbacks;
};
typedef struct FONSfont FONSfont;

struct FONSstate
{
	::i32 font;
	::i32 align;
	::f32 size;
	::u32 color;
	::f32 blur;
	::f32 spacing;
};
typedef struct FONSstate FONSstate;

struct FONSatlasNode {
	::i16 x, y, width;
};
typedef struct FONSatlasNode FONSatlasNode;

struct FONSatlas
{
	::i32 width, height;
	FONSatlasNode * nodes;
	::i32 nnodes;
	::i32 cnodes;
};
typedef struct FONSatlas FONSatlas;

struct FONScontext
{
	FONSparams params;
	::f32 itw, ith;
	::u8 * texData;
	::i32 dirtyRect[4];
	FONSfont ** fonts;
	FONSatlas * atlas;
	::i32 cfonts;
	::i32 nfonts;
	::f32 verts[FONS_VERTEX_COUNT * 2];
	::f32 tcoords[FONS_VERTEX_COUNT * 2];
	::u32 colors[FONS_VERTEX_COUNT];
	::i32 nverts;
	::u8 * scratch;
	::i32 nscratch;
	FONSstate states[FONS_MAX_STATES];
	::i32 nstates;
	void (*handleError)(void * uptr, ::i32 error, ::i32 val);
	void * errorUptr;
#ifdef FONS_USE_FREETYPE
	FT_Library ftLibrary;
#endif
};

#ifdef FONS_USE_FREETYPE

::i32 fons__tt_init(FONScontext * context)
{
	FT_Error ftError;
	FONS_NOTUSED(context);
	ftError = FT_Init_FreeType(&context->ftLibrary);
	return ftError == 0;
}

::i32 fons__tt_done(FONScontext * context)
{
	FT_Error ftError;
	FONS_NOTUSED(context);
	ftError = FT_Done_FreeType(context->ftLibrary);
	return ftError == 0;
}

::i32 fons__tt_loadFont(FONScontext * context, FONSttFontImpl * font, ::u8 * data, ::i32 dataSize, ::i32 fontIndex)
{
	FT_Error ftError;
	FONS_NOTUSED(context);

	ftError = FT_New_Memory_Face(context->ftLibrary, (const FT_Byte *)data, dataSize, fontIndex, &font->font);
	return ftError == 0;
}

void fons__tt_getFontVMetrics(FONSttFontImpl * font, ::i32 * ascent, ::i32 * descent, ::i32 * lineGap)
{
	*ascent = font->font->ascender;
	*descent = font->font->descender;
	*lineGap = font->font->height - (*ascent - *descent);
}

::f32 fons__tt_getPixelHeightScale(FONSttFontImpl * font, ::f32 size)
{
	return size / font->font->units_per_EM;
}

::i32 fons__tt_getGlyphIndex(FONSttFontImpl * font, ::i32 codepoint)
{
	return FT_Get_Char_Index(font->font, codepoint);
}

::i32 fons__tt_buildGlyphBitmap(FONSttFontImpl * font, ::i32 glyph, ::f32 size, ::f32 scale,
	::i32 * advance, ::i32 * lsb, ::i32 * x0, ::i32 * y0, ::i32 * x1, ::i32 * y1)
{
	FT_Error ftError;
	FT_GlyphSlot ftGlyph;
	FT_Fixed advFixed;
	FONS_NOTUSED(scale);

	ftError = FT_Set_Pixel_Sizes(font->font, 0, size);
	if (ftError) return 0;
	ftError = FT_Load_Glyph(font->font, glyph, FT_LOAD_RENDER | FT_LOAD_FORCE_AUTOHINT | FT_LOAD_TARGET_LIGHT);
	if (ftError) return 0;
	ftError = FT_Get_Advance(font->font, glyph, FT_LOAD_NO_SCALE, &advFixed);
	if (ftError) return 0;
	ftGlyph = font->font->glyph;
	*advance = (::i32)advFixed;
	*lsb = (::i32)ftGlyph->metrics.horiBearingX;
	*x0 = ftGlyph->bitmap_left;
	*x1 = *x0 + ftGlyph->bitmap.width;
	*y0 = -ftGlyph->bitmap_top;
	*y1 = *y0 + ftGlyph->bitmap.rows;
	return 1;
}

void fons__tt_renderGlyphBitmap(FONSttFontImpl * font, ::u8 * output, ::i32 outWidth, ::i32 outHeight, ::i32 outStride,
	::f32 scaleX, ::f32 scaleY, ::i32 glyph)
{
	FT_GlyphSlot ftGlyph = font->font->glyph;
	::i32 ftGlyphOffset = 0;
	::u32 x, y;
	FONS_NOTUSED(outWidth);
	FONS_NOTUSED(outHeight);
	FONS_NOTUSED(scaleX);
	FONS_NOTUSED(scaleY);
	FONS_NOTUSED(glyph);	// glyph has already been loaded by fons__tt_buildGlyphBitmap

	for (y = 0; y < ftGlyph->bitmap.rows; y++) {
		for (x = 0; x < ftGlyph->bitmap.width; x++) {
			output[(y * outStride) + x] = ftGlyph->bitmap.buffer[ftGlyphOffset++];
		}
	}
}

::i32 fons__tt_getGlyphKernAdvance(FONSttFontImpl * font, ::i32 glyph1, ::i32 glyph2)
{
	FT_Vector ftKerning;
	FT_Get_Kerning(font->font, glyph1, glyph2, FT_KERNING_DEFAULT, &ftKerning);
	return (::i32)((ftKerning.x + 32) >> 6);  // Round up and convert to integer
}

#else

::i32 fons__tt_init(FONScontext * context)
{
	FONS_NOTUSED(context);
	return 1;
}

::i32 fons__tt_done(FONScontext * context)
{
	FONS_NOTUSED(context);
	return 1;
}

::i32 fons__tt_loadFont(FONScontext * context, FONSttFontImpl * font, ::u8 * data, ::i32 dataSize, ::i32 fontIndex)
{
	::i32 offset, stbError;
	FONS_NOTUSED(dataSize);

	font->font.userdata = context;
	offset = stbtt_GetFontOffsetForIndex(data, fontIndex);
	if (offset == -1) {
		stbError = 0;
	}
	else {
		stbError = stbtt_InitFont(&font->font, data, offset);
	}
	return stbError;
}

void fons__tt_getFontVMetrics(FONSttFontImpl * font, ::i32 * ascent, ::i32 * descent, ::i32 * lineGap)
{
	stbtt_GetFontVMetrics(&font->font, ascent, descent, lineGap);
}

::f32 fons__tt_getPixelHeightScale(FONSttFontImpl * font, ::f32 size)
{
	return stbtt_ScaleForMappingEmToPixels(&font->font, size);
}

::i32 fons__tt_getGlyphIndex(FONSttFontImpl * font, ::i32 codepoint)
{
	return stbtt_FindGlyphIndex(&font->font, codepoint);
}

::i32 fons__tt_buildGlyphBitmap(FONSttFontImpl * font, ::i32 glyph, ::f32 size, ::f32 scale,
	::i32 * advance, ::i32 * lsb, ::i32 * x0, ::i32 * y0, ::i32 * x1, ::i32 * y1)
{
	FONS_NOTUSED(size);
	stbtt_GetGlyphHMetrics(&font->font, glyph, advance, lsb);
	stbtt_GetGlyphBitmapBox(&font->font, glyph, scale, scale, x0, y0, x1, y1);
	return 1;
}

void fons__tt_renderGlyphBitmap(FONSttFontImpl * font, ::u8 * output, ::i32 outWidth, ::i32 outHeight, ::i32 outStride,
	::f32 scaleX, ::f32 scaleY, ::i32 glyph)
{
	stbtt_MakeGlyphBitmap(&font->font, output, outWidth, outHeight, outStride, scaleX, scaleY, glyph);
}

::i32 fons__tt_getGlyphKernAdvance(FONSttFontImpl * font, ::i32 glyph1, ::i32 glyph2)
{
	return stbtt_GetGlyphKernAdvance(&font->font, glyph1, glyph2);
}

#endif

#ifdef STB_TRUETYPE_IMPLEMENTATION

static void * fons__tmpalloc(size_t size, void * up)
{
	::u8 * ptr;
	FONScontext * stash = (FONScontext *)up;

	// 16-::u8 align the returned pointer
	size = (size + 0xf) & ~0xf;

	if (stash->nscratch + (::i32)size > FONS_SCRATCH_BUF_SIZE) {
		if (stash->handleError)
			stash->handleError(stash->errorUptr, FONS_SCRATCH_FULL, stash->nscratch + (::i32)size);
		return NULL;
	}
	ptr = stash->scratch + stash->nscratch;
	stash->nscratch += (::i32)size;
	return ptr;
}

static void fons__tmpfree(void * ptr, void * up)
{
	(void)ptr;
	(void)up;
	// empty
}

#endif // STB_TRUETYPE_IMPLEMENTATION

// Copyright (c) 2008-2010 Bjoern Hoehrmann <bjoern@hoehrmann.de>
// See http://bjoern.hoehrmann.de/utf-8/decoder/dfa/ for details.

#define FONS_UTF8_ACCEPT 0
#define FONS_UTF8_REJECT 12

static ::u32 fons__decutf8(::u32 * state, ::u32 * codep, ::u32 ::u8)
{
	static const ::u8 utf8d[] = {
		// The first part of the table maps bytes to character classes that
		// to reduce the size of the transition table and create bitmasks.
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
		7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
		8,8,2,2,2,2,2,2,2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		10,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3, 11,6,6,6,5,8,8,8,8,8,8,8,8,8,8,8,

		// The second part is a transition table that maps a combination
		// of a state of the automaton and a character class to a state.
		0,12,24,36,60,96,84,12,12,12,48,72, 12,12,12,12,12,12,12,12,12,12,12,12,
		12, 0,12,12,12,12,12, 0,12, 0,12,12, 12,24,12,12,12,12,12,24,12,24,12,12,
		12,12,12,12,12,12,12,24,12,12,12,12, 12,24,12,12,12,12,12,12,12,24,12,12,
		12,12,12,12,12,12,12,36,12,36,12,12, 12,36,12,12,12,12,12,36,12,36,12,12,
		12,36,12,12,12,12,12,12,12,12,12,12,
	};

	::u32 type = utf8d[::u8];

	*codep = (*state != FONS_UTF8_ACCEPT) ?
		(::u8 & 0x3fu) | (*codep << 6) :
		(0xff >> type) & (::u8);

	*state = utf8d[256 + *state + type];
	return *state;
}

// Atlas based on Skyline Bin Packer by Jukka Jylohnki

static void fons__deleteAtlas(FONSatlas * atlas)
{
	if (atlas == NULL) return;
	if (atlas->nodes != NULL) free(atlas->nodes);
	free(atlas);
}

static FONSatlas * fons__allocAtlas(::i32 w, ::i32 h, ::i32 nnodes)
{
	FONSatlas * atlas = NULL;

	// Allocate memory for the font stash.
	atlas = (FONSatlas *)malloc(sizeof(FONSatlas));
	if (atlas == NULL) goto error;
	::memory_set(atlas, 0, sizeof(FONSatlas));

	atlas->width = w;
	atlas->height = h;

	// Allocate space for skyline nodes
	atlas->nodes = (FONSatlasNode *)malloc(sizeof(FONSatlasNode) * nnodes);
	if (atlas->nodes == NULL) goto error;
	::memory_set(atlas->nodes, 0, sizeof(FONSatlasNode) * nnodes);
	atlas->nnodes = 0;
	atlas->cnodes = nnodes;

	// Init root node.
	atlas->nodes[0].x = 0;
	atlas->nodes[0].y = 0;
	atlas->nodes[0].width = (::i16)w;
	atlas->nnodes++;

	return atlas;

error:
	if (atlas) fons__deleteAtlas(atlas);
	return NULL;
}

static ::i32 fons__atlasInsertNode(FONSatlas * atlas, ::i32 idx, ::i32 x, ::i32 y, ::i32 w)
{
	::i32 i;
	// Insert node
	if (atlas->nnodes + 1 > atlas->cnodes) {
		atlas->cnodes = atlas->cnodes == 0 ? 8 : atlas->cnodes * 2;
		atlas->nodes = (FONSatlasNode *)realloc(atlas->nodes, sizeof(FONSatlasNode) * atlas->cnodes);
		if (atlas->nodes == NULL)
			return 0;
	}
	for (i = atlas->nnodes; i > idx; i--)
		atlas->nodes[i] = atlas->nodes[i - 1];
	atlas->nodes[idx].x = (::i16)x;
	atlas->nodes[idx].y = (::i16)y;
	atlas->nodes[idx].width = (::i16)w;
	atlas->nnodes++;

	return 1;
}

static void fons__atlasRemoveNode(FONSatlas * atlas, ::i32 idx)
{
	::i32 i;
	if (atlas->nnodes == 0) return;
	for (i = idx; i < atlas->nnodes - 1; i++)
		atlas->nodes[i] = atlas->nodes[i + 1];
	atlas->nnodes--;
}

static void fons__atlasExpand(FONSatlas * atlas, ::i32 w, ::i32 h)
{
	// Insert node for empty space
	if (w > atlas->width)
		fons__atlasInsertNode(atlas, atlas->nnodes, atlas->width, 0, w - atlas->width);
	atlas->width = w;
	atlas->height = h;
}

static void fons__atlasReset(FONSatlas * atlas, ::i32 w, ::i32 h)
{
	atlas->width = w;
	atlas->height = h;
	atlas->nnodes = 0;

	// Init root node.
	atlas->nodes[0].x = 0;
	atlas->nodes[0].y = 0;
	atlas->nodes[0].width = (::i16)w;
	atlas->nnodes++;
}

static ::i32 fons__atlasAddSkylineLevel(FONSatlas * atlas, ::i32 idx, ::i32 x, ::i32 y, ::i32 w, ::i32 h)
{
	::i32 i;

	// Insert aaa_primitive_new node
	if (fons__atlasInsertNode(atlas, idx, x, y + h, w) == 0)
		return 0;

	// Delete skyline segments that fall under the shadow of the aaa_primitive_new segment.
	for (i = idx + 1; i < atlas->nnodes; i++) {
		if (atlas->nodes[i].x < atlas->nodes[i - 1].x + atlas->nodes[i - 1].width) {
			::i32 shrink = atlas->nodes[i - 1].x + atlas->nodes[i - 1].width - atlas->nodes[i].x;
			atlas->nodes[i].x += (::i16)shrink;
			atlas->nodes[i].width -= (::i16)shrink;
			if (atlas->nodes[i].width <= 0) {
				fons__atlasRemoveNode(atlas, i);
				i--;
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}

	// Merge same height skyline segments that are next to each other.
	for (i = 0; i < atlas->nnodes - 1; i++) {
		if (atlas->nodes[i].y == atlas->nodes[i + 1].y) {
			atlas->nodes[i].width += atlas->nodes[i + 1].width;
			fons__atlasRemoveNode(atlas, i + 1);
			i--;
		}
	}

	return 1;
}

static ::i32 fons__atlasRectFits(FONSatlas * atlas, ::i32 i, ::i32 w, ::i32 h)
{
	// Checks if there is enough space at the location of skyline span 'i',
	// and return the max height of all skyline spans under that at that location,
	// (think tetris block being dropped at that position). Or -1 if no space found.
	::i32 x = atlas->nodes[i].x;
	::i32 y = atlas->nodes[i].y;
	::i32 spaceLeft;
	if (x + w > atlas->width)
		return -1;
	spaceLeft = w;
	while (spaceLeft > 0) {
		if (i == atlas->nnodes) return -1;
		y = fons__maxi(y, atlas->nodes[i].y);
		if (y + h > atlas->height) return -1;
		spaceLeft -= atlas->nodes[i].width;
		++i;
	}
	return y;
}

static ::i32 fons__atlasAddRect(FONSatlas * atlas, ::i32 rw, ::i32 rh, ::i32 * rx, ::i32 * ry)
{
	::i32 besth = atlas->height, bestw = atlas->width, besti = -1;
	::i32 bestx = -1, besty = -1, i;

	// Bottom left fit heuristic.
	for (i = 0; i < atlas->nnodes; i++) {
		::i32 y = fons__atlasRectFits(atlas, i, rw, rh);
		if (y != -1) {
			if (y + rh < besth || (y + rh == besth && atlas->nodes[i].width < bestw)) {
				besti = i;
				bestw = atlas->nodes[i].width;
				besth = y + rh;
				bestx = atlas->nodes[i].x;
				besty = y;
			}
		}
	}

	if (besti == -1)
		return 0;

	// Perform the actual packing.
	if (fons__atlasAddSkylineLevel(atlas, besti, bestx, besty, rw, rh) == 0)
		return 0;

	*rx = bestx;
	*ry = besty;

	return 1;
}

static void fons__addWhiteRect(FONScontext * stash, ::i32 w, ::i32 h)
{
	::i32 x, y, gx, gy;
	::u8 * dst;
	if (fons__atlasAddRect(stash->atlas, w, h, &gx, &gy) == 0)
		return;

	// Rasterize
	dst = &stash->texData[gx + gy * stash->params.width];
	for (y = 0; y < h; y++) {
		for (x = 0; x < w; x++)
			dst[x] = 0xff;
		dst += stash->params.width;
	}

	stash->dirtyRect[0] = fons__mini(stash->dirtyRect[0], gx);
	stash->dirtyRect[1] = fons__mini(stash->dirtyRect[1], gy);
	stash->dirtyRect[2] = fons__maxi(stash->dirtyRect[2], gx + w);
	stash->dirtyRect[3] = fons__maxi(stash->dirtyRect[3], gy + h);
}

FONScontext * fonsCreateInternal(FONSparams * params)
{
	FONScontext * stash = NULL;

	// Allocate memory for the font stash.
	stash = (FONScontext *)malloc(sizeof(FONScontext));
	if (stash == NULL) goto error;
	::memory_set(stash, 0, sizeof(FONScontext));

	stash->params = *params;

	// Allocate scratch buffer.
	stash->scratch = (::u8 *)malloc(FONS_SCRATCH_BUF_SIZE);
	if (stash->scratch == NULL) goto error;

	// Initialize implementation library
	if (!fons__tt_init(stash)) goto error;

	if (stash->params.renderCreate != NULL) {
		if (stash->params.renderCreate(stash->params.userPtr, stash->params.width, stash->params.height) == 0)
			goto error;
	}

	stash->atlas = fons__allocAtlas(stash->params.width, stash->params.height, FONS_INIT_ATLAS_NODES);
	if (stash->atlas == NULL) goto error;

	// Allocate space for fonts.
	stash->fonts = (FONSfont **)malloc(sizeof(FONSfont *) * FONS_INIT_FONTS);
	if (stash->fonts == NULL) goto error;
	::memory_set(stash->fonts, 0, sizeof(FONSfont *) * FONS_INIT_FONTS);
	stash->cfonts = FONS_INIT_FONTS;
	stash->nfonts = 0;

	// Create texture for the cache.
	stash->itw = 1.0f / stash->params.width;
	stash->ith = 1.0f / stash->params.height;
	stash->texData = (::u8 *)malloc(stash->params.width * stash->params.height);
	if (stash->texData == NULL) goto error;
	::memory_set(stash->texData, 0, stash->params.width * stash->params.height);

	stash->dirtyRect[0] = stash->params.width;
	stash->dirtyRect[1] = stash->params.height;
	stash->dirtyRect[2] = 0;
	stash->dirtyRect[3] = 0;

	// Add white rect at 0,0 for debug drawing.
	fons__addWhiteRect(stash, 2, 2);

	fonsPushState(stash);
	fonsClearState(stash);

	return stash;

error:
	fonsDeleteInternal(stash);
	return NULL;
}

static FONSstate * fons__getState(FONScontext * stash)
{
	return &stash->states[stash->nstates - 1];
}

::i32 fonsAddFallbackFont(FONScontext * stash, ::i32 base, ::i32 fallback)
{
	FONSfont * baseFont = stash->fonts[base];
	if (baseFont->nfallbacks < FONS_MAX_FALLBACKS) {
		baseFont->fallbacks[baseFont->nfallbacks++] = fallback;
		return 1;
	}
	return 0;
}

void fonsResetFallbackFont(FONScontext * stash, ::i32 base)
{
	::i32 i;

	FONSfont * baseFont = stash->fonts[base];
	baseFont->nfallbacks = 0;
	baseFont->nglyphs = 0;
	for (i = 0; i < FONS_HASH_LUT_SIZE; i++)
		baseFont->lut[i] = -1;
}

void fonsSetSize(FONScontext * stash, ::f32 size)
{
	fons__getState(stash)->size = size;
}

void fonsSetColor(FONScontext * stash, ::u32 color)
{
	fons__getState(stash)->color = color;
}

void fonsSetSpacing(FONScontext * stash, ::f32 spacing)
{
	fons__getState(stash)->spacing = spacing;
}

void fonsSetBlur(FONScontext * stash, ::f32 blur)
{
	fons__getState(stash)->blur = blur;
}

void fonsSetAlign(FONScontext * stash, ::i32 align)
{
	fons__getState(stash)->align = align;
}

void fonsSetFont(FONScontext * stash, ::i32 font)
{
	fons__getState(stash)->font = font;
}

void fonsPushState(FONScontext * stash)
{
	if (stash->nstates >= FONS_MAX_STATES) {
		if (stash->handleError)
			stash->handleError(stash->errorUptr, FONS_STATES_OVERFLOW, 0);
		return;
	}
	if (stash->nstates > 0)
		::memory_copy(&stash->states[stash->nstates], &stash->states[stash->nstates - 1], sizeof(FONSstate));
	stash->nstates++;
}

void fonsPopState(FONScontext * stash)
{
	if (stash->nstates <= 1) {
		if (stash->handleError)
			stash->handleError(stash->errorUptr, FONS_STATES_UNDERFLOW, 0);
		return;
	}
	stash->nstates--;
}

void fonsClearState(FONScontext * stash)
{
	FONSstate * state = fons__getState(stash);
	state->size = 12.0f;
	state->color = 0xffffffff;
	state->font = 0;
	state->blur = 0;
	state->spacing = 0;
	state->align = FONS_ALIGN_LEFT | FONS_ALIGN_BASELINE;
}

static void fons__freeFont(FONSfont * font)
{
	if (font == NULL) return;
	if (font->glyphs) free(font->glyphs);
	if (font->freeData && font->data) free(font->data);
	free(font);
}

static ::i32 fons__allocFont(FONScontext * stash)
{
	FONSfont * font = NULL;
	if (stash->nfonts + 1 > stash->cfonts) {
		stash->cfonts = stash->cfonts == 0 ? 8 : stash->cfonts * 2;
		stash->fonts = (FONSfont **)realloc(stash->fonts, sizeof(FONSfont *) * stash->cfonts);
		if (stash->fonts == NULL)
			return -1;
	}
	font = (FONSfont *)malloc(sizeof(FONSfont));
	if (font == NULL) goto error;
	::memory_set(font, 0, sizeof(FONSfont));

	font->glyphs = (FONSglyph *)malloc(sizeof(FONSglyph) * FONS_INIT_GLYPHS);
	if (font->glyphs == NULL) goto error;
	font->cglyphs = FONS_INIT_GLYPHS;
	font->nglyphs = 0;

	stash->fonts[stash->nfonts++] = font;
	return stash->nfonts - 1;

error:
	fons__freeFont(font);

	return FONS_INVALID;
}

::i32 fonsAddFont(FONScontext * stash, const_char_pointer pszName, const ::file::path & path, ::i32 fontIndex)
{
	FILE * fp = 0;
	::i32 dataSize = 0;
	size_t readed;
	::u8 * data = NULL;

	// Read in the font data.
	fp = fopen(path, "rb");
	if (fp == NULL) goto error;
	fseek(fp, 0, SEEK_END);
	dataSize = (::i32)ftell(fp);
	fseek(fp, 0, SEEK_SET);
	data = (::u8 *)malloc(dataSize);
	if (data == NULL) goto error;
	readed = fread(data, 1, dataSize, fp);
	fclose(fp);
	fp = 0;
	if (readed != (size_t)dataSize) goto error;

	return fonsAddFontMem(stash, name, data, dataSize, 1, fontIndex);

error:
	if (data) free(data);
	if (fp) fclose(fp);
	return FONS_INVALID;
}

::i32 fonsAddFontMem(FONScontext * stash, const_char_pointer pszName, ::u8 * data, ::i32 dataSize, ::i32 freeData, ::i32 fontIndex)
{
	::i32 i, ascent, descent, fh, lineGap;
	FONSfont * font;

	::i32 idx = fons__allocFont(stash);
	if (idx == FONS_INVALID)
		return FONS_INVALID;

	font = stash->fonts[idx];

	strncpy(font->name, name, sizeof(font->name));
	font->name[sizeof(font->name) - 1] = '\0';

	// Init hash lookup.
	for (i = 0; i < FONS_HASH_LUT_SIZE; ++i)
		font->lut[i] = -1;

	// Read in the font data.
	font->dataSize = dataSize;
	font->data = data;
	font->freeData = (::u8)freeData;

	// Init font
	stash->nscratch = 0;
	if (!fons__tt_loadFont(stash, &font->font, data, dataSize, fontIndex)) goto error;

	// Store normalized line height. The real line height is got
	// by multiplying the lineh by font size.
	fons__tt_getFontVMetrics(&font->font, &ascent, &descent, &lineGap);
	ascent += lineGap;
	fh = ascent - descent;
	font->ascender = (::f32)ascent / (::f32)fh;
	font->descender = (::f32)descent / (::f32)fh;
	font->lineh = font->ascender - font->descender;

	return idx;

error:
	fons__freeFont(font);
	stash->nfonts--;
	return FONS_INVALID;
}

::i32 fonsGetFontByName(FONScontext * s, const_char_pointer pszName)
{
	::i32 i;
	for (i = 0; i < s->nfonts; i++) {
		if (strcmp(s->fonts[i]->name, name) == 0)
			return i;
	}
	return FONS_INVALID;
}


static FONSglyph * fons__allocGlyph(FONSfont * font)
{
	if (font->nglyphs + 1 > font->cglyphs) {
		font->cglyphs = font->cglyphs == 0 ? 8 : font->cglyphs * 2;
		font->glyphs = (FONSglyph *)realloc(font->glyphs, sizeof(FONSglyph) * font->cglyphs);
		if (font->glyphs == NULL) return NULL;
	}
	font->nglyphs++;
	return &font->glyphs[font->nglyphs - 1];
}


// Based on Exponential blur, Jani Huhtanen, 2006

#define APREC 16
#define ZPREC 7

static void fons__blurCols(::u8 * dst, ::i32 w, ::i32 h, ::i32 dstStride, ::i32 alpha)
{
	::i32 x, y;
	for (y = 0; y < h; y++) {
		::i32 z = 0; // force zero border
		for (x = 1; x < w; x++) {
			z += (alpha * (((::i32)(dst[x]) << ZPREC) - z)) >> APREC;
			dst[x] = (::u8)(z >> ZPREC);
		}
		dst[w - 1] = 0; // force zero border
		z = 0;
		for (x = w - 2; x >= 0; x--) {
			z += (alpha * (((::i32)(dst[x]) << ZPREC) - z)) >> APREC;
			dst[x] = (::u8)(z >> ZPREC);
		}
		dst[0] = 0; // force zero border
		dst += dstStride;
	}
}

static void fons__blurRows(::u8 * dst, ::i32 w, ::i32 h, ::i32 dstStride, ::i32 alpha)
{
	::i32 x, y;
	for (x = 0; x < w; x++) {
		::i32 z = 0; // force zero border
		for (y = dstStride; y < h * dstStride; y += dstStride) {
			z += (alpha * (((::i32)(dst[y]) << ZPREC) - z)) >> APREC;
			dst[y] = (::u8)(z >> ZPREC);
		}
		dst[(h - 1) * dstStride] = 0; // force zero border
		z = 0;
		for (y = (h - 2) * dstStride; y >= 0; y -= dstStride) {
			z += (alpha * (((::i32)(dst[y]) << ZPREC) - z)) >> APREC;
			dst[y] = (::u8)(z >> ZPREC);
		}
		dst[0] = 0; // force zero border
		dst++;
	}
}


static void fons__blur(FONScontext * stash, ::u8 * dst, ::i32 w, ::i32 h, ::i32 dstStride, ::i32 blur)
{
	::i32 alpha;
	::f32 sigma;
	(void)stash;

	if (blur < 1)
		return;
	// Calculate the alpha such that 90% of the kernel is within the radius. (Kernel extends to infinity)
	sigma = (::f32)blur * 0.57735f; // 1 / sqrt(3)
	alpha = (::i32)((1 << APREC) * (1.0f - expf(-2.3f / (sigma + 1.0f))));
	fons__blurRows(dst, w, h, dstStride, alpha);
	fons__blurCols(dst, w, h, dstStride, alpha);
	fons__blurRows(dst, w, h, dstStride, alpha);
	fons__blurCols(dst, w, h, dstStride, alpha);
	//	fons__blurrows(dst, w, h, dstStride, alpha);
	//	fons__blurcols(dst, w, h, dstStride, alpha);
}

static FONSglyph * fons__getGlyph(FONScontext * stash, FONSfont * font, ::u32 codepoint,
	::i16 isize, ::i16 iblur, ::i32 bitmapOption)
{
	::i32 i, g, advance, lsb, x0, y0, x1, y1, gw, gh, gx, gy, x, y;
	::f32 scale;
	FONSglyph * glyph = NULL;
	::u32 h;
	::f32 size = isize / 10.0f;
	::i32 pad, added;
	::u8 * bdst;
	::u8 * dst;
	FONSfont * renderFont = font;

	if (isize < 2) return NULL;
	if (iblur > 20) iblur = 20;
	pad = iblur + 2;

	// Reset allocator.
	stash->nscratch = 0;

	// Find code point and size.
	h = fons__hashint(codepoint) & (FONS_HASH_LUT_SIZE - 1);
	i = font->lut[h];
	while (i != -1) {
		if (font->glyphs[i].codepoint == codepoint && font->glyphs[i].size == isize && font->glyphs[i].blur == iblur) {
			glyph = &font->glyphs[i];
			if (bitmapOption == FONS_GLYPH_BITMAP_OPTIONAL || (glyph->x0 >= 0 && glyph->y0 >= 0)) {
				return glyph;
			}
			// At this point, glyph exists but the bitmap data is not yet created.
			break;
		}
		i = font->glyphs[i].next;
	}

	// Create a aaa_primitive_new glyph or rasterize bitmap data for a cached glyph.
	g = fons__tt_getGlyphIndex(&font->font, codepoint);
	// Try to find the glyph in fallback fonts.
	if (g == 0) {
		for (i = 0; i < font->nfallbacks; ++i) {
			FONSfont * fallbackFont = stash->fonts[font->fallbacks[i]];
			::i32 fallbackIndex = fons__tt_getGlyphIndex(&fallbackFont->font, codepoint);
			if (fallbackIndex != 0) {
				g = fallbackIndex;
				renderFont = fallbackFont;
				break;
			}
		}
		// It is possible that we did not find a fallback glyph.
		// In that case the glyph index 'g' is 0, and we'hi proceed below and cache empty glyph.
	}
	scale = fons__tt_getPixelHeightScale(&renderFont->font, size);
	fons__tt_buildGlyphBitmap(&renderFont->font, g, size, scale, &advance, &lsb, &x0, &y0, &x1, &y1);
	gw = x1 - x0 + pad * 2;
	gh = y1 - y0 + pad * 2;

	// Determines the spot to draw glyph in the atlas.
	if (bitmapOption == FONS_GLYPH_BITMAP_REQUIRED) {
		// Find free spot for the rect in the atlas
		added = fons__atlasAddRect(stash->atlas, gw, gh, &gx, &gy);
		if (added == 0 && stash->handleError != NULL) {
			// Atlas is full, let the user to resize the atlas (or not), and try again.
			stash->handleError(stash->errorUptr, FONS_ATLAS_FULL, 0);
			added = fons__atlasAddRect(stash->atlas, gw, gh, &gx, &gy);
		}
		if (added == 0) return NULL;
	}
	else {
		// Negative coordinate indicates there is no bitmap data created.
		gx = -1;
		gy = -1;
	}

	// Init glyph.
	if (glyph == NULL) {
		glyph = fons__allocGlyph(font);
		glyph->codepoint = codepoint;
		glyph->size = isize;
		glyph->blur = iblur;
		glyph->next = 0;

		// Insert ::i8 to hash lookup.
		glyph->next = font->lut[h];
		font->lut[h] = font->nglyphs - 1;
	}
	glyph->index = g;
	glyph->x0 = (::i16)gx;
	glyph->y0 = (::i16)gy;
	glyph->x1 = (::i16)(glyph->x0 + gw);
	glyph->y1 = (::i16)(glyph->y0 + gh);
	glyph->xadv = (::i16)(scale * advance * 10.0f);
	glyph->xoff = (::i16)(x0 - pad);
	glyph->yoff = (::i16)(y0 - pad);

	if (bitmapOption == FONS_GLYPH_BITMAP_OPTIONAL) {
		return glyph;
	}

	// Rasterize
	dst = &stash->texData[(glyph->x0 + pad) + (glyph->y0 + pad) * stash->params.width];
	fons__tt_renderGlyphBitmap(&renderFont->font, dst, gw - pad * 2, gh - pad * 2, stash->params.width, scale, scale, g);

	// Make sure there is one pixel empty border.
	dst = &stash->texData[glyph->x0 + glyph->y0 * stash->params.width];
	for (y = 0; y < gh; y++) {
		dst[y * stash->params.width] = 0;
		dst[gw - 1 + y * stash->params.width] = 0;
	}
	for (x = 0; x < gw; x++) {
		dst[x] = 0;
		dst[x + (gh - 1) * stash->params.width] = 0;
	}

	// Debug code to color the glyph background
/*	::u8* fdst = &stash->texData[glyph->x0 + glyph->y0 * stash->params.width];
	for (y = 0; y < gh; y++) {
		for (x = 0; x < gw; x++) {
			::i32 a = (::i32)fdst[x+y*stash->params.width] + 20;
			if (a > 255) a = 255;
			fdst[x+y*stash->params.width] = a;
		}
	}*/

	// Blur
	if (iblur > 0) {
		stash->nscratch = 0;
		bdst = &stash->texData[glyph->x0 + glyph->y0 * stash->params.width];
		fons__blur(stash, bdst, gw, gh, stash->params.width, iblur);
	}

	stash->dirtyRect[0] = fons__mini(stash->dirtyRect[0], glyph->x0);
	stash->dirtyRect[1] = fons__mini(stash->dirtyRect[1], glyph->y0);
	stash->dirtyRect[2] = fons__maxi(stash->dirtyRect[2], glyph->x1);
	stash->dirtyRect[3] = fons__maxi(stash->dirtyRect[3], glyph->y1);

	return glyph;
}

static void fons__getQuad(FONScontext * stash, FONSfont * font,
	::i32 prevGlyphIndex, FONSglyph * glyph,
	::f32 scale, ::f32 spacing, ::f32 * x, ::f32 * y, FONSquad * q)
{
	::f32 rx, ry, xoff, yoff, x0, y0, x1, y1;

	if (prevGlyphIndex != -1) {
		::f32 adv = fons__tt_getGlyphKernAdvance(&font->font, prevGlyphIndex, glyph->index) * scale;
		*x += (::i32)(adv + spacing + 0.5f);
	}

	// Each glyph has 2px border to allow good interpolation,
	// one pixel to prevent leaking, and one to allow good interpolation for rendering.
	// Inset the texture region by one pixel for correct interpolation.
	xoff = (::i16)(glyph->xoff + 1);
	yoff = (::i16)(glyph->yoff + 1);
	x0 = (::f32)(glyph->x0 + 1);
	y0 = (::f32)(glyph->y0 + 1);
	x1 = (::f32)(glyph->x1 - 1);
	y1 = (::f32)(glyph->y1 - 1);

	if (stash->params.flags & FONS_ZERO_TOPLEFT) {
		rx = floorf(*x + xoff);
		ry = floorf(*y + yoff);

		q->x0 = rx;
		q->y0 = ry;
		q->x1 = rx + x1 - x0;
		q->y1 = ry + y1 - y0;

		q->s0 = x0 * stash->itw;
		q->t0 = y0 * stash->ith;
		q->s1 = x1 * stash->itw;
		q->t1 = y1 * stash->ith;
	}
	else {
		rx = floorf(*x + xoff);
		ry = floorf(*y - yoff);

		q->x0 = rx;
		q->y0 = ry;
		q->x1 = rx + x1 - x0;
		q->y1 = ry - y1 + y0;

		q->s0 = x0 * stash->itw;
		q->t0 = y0 * stash->ith;
		q->s1 = x1 * stash->itw;
		q->t1 = y1 * stash->ith;
	}

	*x += (::i32)(glyph->xadv / 10.0f + 0.5f);
}

static void fons__flush(FONScontext * stash)
{
	// Flush texture
	if (stash->dirtyRect[0] < stash->dirtyRect[2] && stash->dirtyRect[1] < stash->dirtyRect[3]) {
		if (stash->params.renderUpdate != NULL)
			stash->params.renderUpdate(stash->params.userPtr, stash->dirtyRect, stash->texData);
		// Reset dirty rect
		stash->dirtyRect[0] = stash->params.width;
		stash->dirtyRect[1] = stash->params.height;
		stash->dirtyRect[2] = 0;
		stash->dirtyRect[3] = 0;
	}

	// Flush triangles
	if (stash->nverts > 0) {
		if (stash->params.renderDraw != NULL)
			stash->params.renderDraw(stash->params.userPtr, stash->verts, stash->tcoords, stash->colors, stash->nverts);
		stash->nverts = 0;
	}
}

static __inline void fons__vertex(FONScontext * stash, ::f32 x, ::f32 y, ::f32 s, ::f32 t, ::u32 c)
{
	stash->verts[stash->nverts * 2 + 0] = x;
	stash->verts[stash->nverts * 2 + 1] = y;
	stash->tcoords[stash->nverts * 2 + 0] = s;
	stash->tcoords[stash->nverts * 2 + 1] = t;
	stash->colors[stash->nverts] = c;
	stash->nverts++;
}

static ::f32 fons__getVertAlign(FONScontext * stash, FONSfont * font, ::i32 align, ::i16 isize)
{
	if (stash->params.flags & FONS_ZERO_TOPLEFT) {
		if (align & FONS_ALIGN_TOP) {
			return font->ascender * (::f32)isize / 10.0f;
		}
		else if (align & FONS_ALIGN_MIDDLE) {
			return (font->ascender + font->descender) / 2.0f * (::f32)isize / 10.0f;
		}
		else if (align & FONS_ALIGN_BASELINE) {
			return 0.0f;
		}
		else if (align & FONS_ALIGN_BOTTOM) {
			return font->descender * (::f32)isize / 10.0f;
		}
	}
	else {
		if (align & FONS_ALIGN_TOP) {
			return -font->ascender * (::f32)isize / 10.0f;
		}
		else if (align & FONS_ALIGN_MIDDLE) {
			return -(font->ascender + font->descender) / 2.0f * (::f32)isize / 10.0f;
		}
		else if (align & FONS_ALIGN_BASELINE) {
			return 0.0f;
		}
		else if (align & FONS_ALIGN_BOTTOM) {
			return -font->descender * (::f32)isize / 10.0f;
		}
	}
	return 0.0;
}

::f32 fonsDrawText(FONScontext * stash,
	::f32 x, ::f32 y,
	const_char_pointer str, const_char_pointer end)
{
	FONSstate * state = fons__getState(stash);
	::u32 codepoint;
	::u32 utf8state = 0;
	FONSglyph * glyph = NULL;
	FONSquad q;
	::i32 prevGlyphIndex = -1;
	::i16 isize = (::i16)(state->size * 10.0f);
	::i16 iblur = (::i16)state->blur;
	::f32 scale;
	FONSfont * font;
	::f32 width;

	if (stash == NULL) return x;
	if (state->font < 0 || state->font >= stash->nfonts) return x;
	font = stash->fonts[state->font];
	if (font->data == NULL) return x;

	scale = fons__tt_getPixelHeightScale(&font->font, (::f32)isize / 10.0f);

	if (end == NULL)
		end = str + strlen(str);

	// Align horizontally
	if (state->align & FONS_ALIGN_LEFT) {
		// empty
	}
	else if (state->align & FONS_ALIGN_RIGHT) {
		width = fonsTextBounds(stash, x, y, str, end, NULL);
		x -= width;
	}
	else if (state->align & FONS_ALIGN_CENTER) {
		width = fonsTextBounds(stash, x, y, str, end, NULL);
		x -= width * 0.5f;
	}
	// Align vertically.
	y += fons__getVertAlign(stash, font, state->align, isize);

	for (; str != end; ++str) {
		if (fons__decutf8(&utf8state, &codepoint, *(const ::u8 *)str))
			continue;
		glyph = fons__getGlyph(stash, font, codepoint, isize, iblur, FONS_GLYPH_BITMAP_REQUIRED);
		if (glyph != NULL) {
			fons__getQuad(stash, font, prevGlyphIndex, glyph, scale, state->spacing, &x, &y, &q);

			if (stash->nverts + 6 > FONS_VERTEX_COUNT)
				fons__flush(stash);

			fons__vertex(stash, q.x0, q.y0, q.s0, q.t0, state->color);
			fons__vertex(stash, q.x1, q.y1, q.s1, q.t1, state->color);
			fons__vertex(stash, q.x1, q.y0, q.s1, q.t0, state->color);

			fons__vertex(stash, q.x0, q.y0, q.s0, q.t0, state->color);
			fons__vertex(stash, q.x0, q.y1, q.s0, q.t1, state->color);
			fons__vertex(stash, q.x1, q.y1, q.s1, q.t1, state->color);
		}
		prevGlyphIndex = glyph != NULL ? glyph->index : -1;
	}
	fons__flush(stash);

	return x;
}

::i32 fonsTextIterInit(FONScontext * stash, FONStextIter * iter,
	::f32 x, ::f32 y, const_char_pointer str, const_char_pointer end, ::i32 bitmapOption)
{
	FONSstate * state = fons__getState(stash);
	::f32 width;

	::memory_set(iter, 0, sizeof(*iter));

	if (stash == NULL) return 0;
	if (state->font < 0 || state->font >= stash->nfonts) return 0;
	iter->font = stash->fonts[state->font];
	if (iter->font->data == NULL) return 0;

	iter->isize = (::i16)(state->size * 10.0f);
	iter->iblur = (::i16)state->blur;
	iter->scale = fons__tt_getPixelHeightScale(&iter->font->font, (::f32)iter->isize / 10.0f);

	// Align horizontally
	if (state->align & FONS_ALIGN_LEFT) {
		// empty
	}
	else if (state->align & FONS_ALIGN_RIGHT) {
		width = fonsTextBounds(stash, x, y, str, end, NULL);
		x -= width;
	}
	else if (state->align & FONS_ALIGN_CENTER) {
		width = fonsTextBounds(stash, x, y, str, end, NULL);
		x -= width * 0.5f;
	}
	// Align vertically.
	y += fons__getVertAlign(stash, iter->font, state->align, iter->isize);

	if (end == NULL)
		end = str + strlen(str);

	iter->x = iter->nextx = x;
	iter->y = iter->nexty = y;
	iter->spacing = state->spacing;
	iter->str = str;
	iter->next = str;
	iter->end = end;
	iter->codepoint = 0;
	iter->prevGlyphIndex = -1;
	iter->bitmapOption = bitmapOption;

	return 1;
}

::i32 fonsTextIterNext(FONScontext * stash, FONStextIter * iter, FONSquad * quad)
{
	FONSglyph * glyph = NULL;
	const_char_pointer str = iter->next;
	iter->str = iter->next;

	if (str == iter->end)
		return 0;

	for (; str != iter->end; str++) {
		if (fons__decutf8(&iter->utf8state, &iter->codepoint, *(const ::u8 *)str))
			continue;
		str++;
		// Get glyph and quad
		iter->x = iter->nextx;
		iter->y = iter->nexty;
		glyph = fons__getGlyph(stash, iter->font, iter->codepoint, iter->isize, iter->iblur, iter->bitmapOption);
		// If the iterator was initialized with FONS_GLYPH_BITMAP_OPTIONAL, then the UV coordinates of the quad will be invalid.
		if (glyph != NULL)
			fons__getQuad(stash, iter->font, iter->prevGlyphIndex, glyph, iter->scale, iter->spacing, &iter->nextx, &iter->nexty, quad);
		iter->prevGlyphIndex = glyph != NULL ? glyph->index : -1;
		break;
	}
	iter->next = str;

	return 1;
}

void fonsDrawDebug(FONScontext * stash, ::f32 x, ::f32 y)
{
	::i32 i;
	::i32 w = stash->params.width;
	::i32 h = stash->params.height;
	::f32 u = w == 0 ? 0 : (1.0f / w);
	::f32 v = h == 0 ? 0 : (1.0f / h);

	if (stash->nverts + 6 + 6 > FONS_VERTEX_COUNT)
		fons__flush(stash);

	// Draw background
	fons__vertex(stash, x + 0, y + 0, u, v, 0x0fffffff);
	fons__vertex(stash, x + w, y + h, u, v, 0x0fffffff);
	fons__vertex(stash, x + w, y + 0, u, v, 0x0fffffff);

	fons__vertex(stash, x + 0, y + 0, u, v, 0x0fffffff);
	fons__vertex(stash, x + 0, y + h, u, v, 0x0fffffff);
	fons__vertex(stash, x + w, y + h, u, v, 0x0fffffff);

	// Draw texture
	fons__vertex(stash, x + 0, y + 0, 0, 0, 0xffffffff);
	fons__vertex(stash, x + w, y + h, 1, 1, 0xffffffff);
	fons__vertex(stash, x + w, y + 0, 1, 0, 0xffffffff);

	fons__vertex(stash, x + 0, y + 0, 0, 0, 0xffffffff);
	fons__vertex(stash, x + 0, y + h, 0, 1, 0xffffffff);
	fons__vertex(stash, x + w, y + h, 1, 1, 0xffffffff);

	// Drawbug draw atlas
	for (i = 0; i < stash->atlas->nnodes; i++) {
		FONSatlasNode * n = &stash->atlas->nodes[i];

		if (stash->nverts + 6 > FONS_VERTEX_COUNT)
			fons__flush(stash);

		fons__vertex(stash, x + n->x + 0, y + n->y + 0, u, v, 0xc00000ff);
		fons__vertex(stash, x + n->x + n->width, y + n->y + 1, u, v, 0xc00000ff);
		fons__vertex(stash, x + n->x + n->width, y + n->y + 0, u, v, 0xc00000ff);

		fons__vertex(stash, x + n->x + 0, y + n->y + 0, u, v, 0xc00000ff);
		fons__vertex(stash, x + n->x + 0, y + n->y + 1, u, v, 0xc00000ff);
		fons__vertex(stash, x + n->x + n->width, y + n->y + 1, u, v, 0xc00000ff);
	}

	fons__flush(stash);
}

::f32 fonsTextBounds(FONScontext * stash,
	::f32 x, ::f32 y,
	const_char_pointer str, const_char_pointer end,
	::f32 * bounds)
{
	FONSstate * state = fons__getState(stash);
	::u32 codepoint;
	::u32 utf8state = 0;
	FONSquad q;
	FONSglyph * glyph = NULL;
	::i32 prevGlyphIndex = -1;
	::i16 isize = (::i16)(state->size * 10.0f);
	::i16 iblur = (::i16)state->blur;
	::f32 scale;
	FONSfont * font;
	::f32 startx, advance;
	::f32 minx, miny, maxx, maxy;

	if (stash == NULL) return 0;
	if (state->font < 0 || state->font >= stash->nfonts) return 0;
	font = stash->fonts[state->font];
	if (font->data == NULL) return 0;

	scale = fons__tt_getPixelHeightScale(&font->font, (::f32)isize / 10.0f);

	// Align vertically.
	y += fons__getVertAlign(stash, font, state->align, isize);

	minx = maxx = x;
	miny = maxy = y;
	startx = x;

	if (end == NULL)
		end = str + strlen(str);

	for (; str != end; ++str) {
		if (fons__decutf8(&utf8state, &codepoint, *(const ::u8 *)str))
			continue;
		glyph = fons__getGlyph(stash, font, codepoint, isize, iblur, FONS_GLYPH_BITMAP_OPTIONAL);
		if (glyph != NULL) {
			fons__getQuad(stash, font, prevGlyphIndex, glyph, scale, state->spacing, &x, &y, &q);
			if (q.x0 < minx) minx = q.x0;
			if (q.x1 > maxx) maxx = q.x1;
			if (stash->params.flags & FONS_ZERO_TOPLEFT) {
				if (q.y0 < miny) miny = q.y0;
				if (q.y1 > maxy) maxy = q.y1;
			}
			else {
				if (q.y1 < miny) miny = q.y1;
				if (q.y0 > maxy) maxy = q.y0;
			}
		}
		prevGlyphIndex = glyph != NULL ? glyph->index : -1;
	}

	advance = x - startx;

	// Align horizontally
	if (state->align & FONS_ALIGN_LEFT) {
		// empty
	}
	else if (state->align & FONS_ALIGN_RIGHT) {
		minx -= advance;
		maxx -= advance;
	}
	else if (state->align & FONS_ALIGN_CENTER) {
		minx -= advance * 0.5f;
		maxx -= advance * 0.5f;
	}

	if (bounds) {
		bounds[0] = minx;
		bounds[1] = miny;
		bounds[2] = maxx;
		bounds[3] = maxy;
	}

	return advance;
}

void fonsVertMetrics(FONScontext * stash,
	::f32 * ascender, ::f32 * descender, ::f32 * lineh)
{
	FONSfont * font;
	FONSstate * state = fons__getState(stash);
	::i16 isize;

	if (stash == NULL) return;
	if (state->font < 0 || state->font >= stash->nfonts) return;
	font = stash->fonts[state->font];
	isize = (::i16)(state->size * 10.0f);
	if (font->data == NULL) return;

	if (ascender)
		*ascender = font->ascender * isize / 10.0f;
	if (descender)
		*descender = font->descender * isize / 10.0f;
	if (lineh)
		*lineh = font->lineh * isize / 10.0f;
}

void fonsLineBounds(FONScontext * stash, ::f32 y, ::f32 * miny, ::f32 * maxy)
{
	FONSfont * font;
	FONSstate * state = fons__getState(stash);
	::i16 isize;

	if (stash == NULL) return;
	if (state->font < 0 || state->font >= stash->nfonts) return;
	font = stash->fonts[state->font];
	isize = (::i16)(state->size * 10.0f);
	if (font->data == NULL) return;

	y += fons__getVertAlign(stash, font, state->align, isize);

	if (stash->params.flags & FONS_ZERO_TOPLEFT) {
		*miny = y - font->ascender * (::f32)isize / 10.0f;
		*maxy = *miny + font->lineh * isize / 10.0f;
	}
	else {
		*maxy = y + font->descender * (::f32)isize / 10.0f;
		*miny = *maxy - font->lineh * isize / 10.0f;
	}
}

const ::u8 * fonsGetTextureData(FONScontext * stash, ::i32 * width, ::i32 * height)
{
	if (width != NULL)
		*width = stash->params.width;
	if (height != NULL)
		*height = stash->params.height;
	return stash->texData;
}

::i32 fonsValidateTexture(FONScontext * stash, ::i32 * dirty)
{
	if (stash->dirtyRect[0] < stash->dirtyRect[2] && stash->dirtyRect[1] < stash->dirtyRect[3]) {
		dirty[0] = stash->dirtyRect[0];
		dirty[1] = stash->dirtyRect[1];
		dirty[2] = stash->dirtyRect[2];
		dirty[3] = stash->dirtyRect[3];
		// Reset dirty rect
		stash->dirtyRect[0] = stash->params.width;
		stash->dirtyRect[1] = stash->params.height;
		stash->dirtyRect[2] = 0;
		stash->dirtyRect[3] = 0;
		return 1;
	}
	return 0;
}

void fonsDeleteInternal(FONScontext * stash)
{
	::i32 i;
	if (stash == NULL) return;

	if (stash->params.renderDelete)
		stash->params.renderDelete(stash->params.userPtr);

	for (i = 0; i < stash->nfonts; ++i)
		fons__freeFont(stash->fonts[i]);

	if (stash->atlas) fons__deleteAtlas(stash->atlas);
	if (stash->fonts) free(stash->fonts);
	if (stash->texData) free(stash->texData);
	if (stash->scratch) free(stash->scratch);
	fons__tt_done(stash);
	free(stash);
}

void fonsSetErrorCallback(FONScontext * stash, void (*callback)(void * uptr, ::i32 error, ::i32 val), void * uptr)
{
	if (stash == NULL) return;
	stash->handleError = callback;
	stash->errorUptr = uptr;
}

void fonsGetAtlasSize(FONScontext * stash, ::i32 * width, ::i32 * height)
{
	if (stash == NULL) return;
	*width = stash->params.width;
	*height = stash->params.height;
}

::i32 fonsExpandAtlas(FONScontext * stash, ::i32 width, ::i32 height)
{
	::i32 i, maxy = 0;
	::u8 * data = NULL;
	if (stash == NULL) return 0;

	width = fons__maxi(width, stash->params.width);
	height = fons__maxi(height, stash->params.height);

	if (width == stash->params.width && height == stash->params.height)
		return 1;

	// Flush pending glyphs.
	fons__flush(stash);

	// Create aaa_primitive_new texture
	if (stash->params.renderResize != NULL) {
		if (stash->params.renderResize(stash->params.userPtr, width, height) == 0)
			return 0;
	}
	// Copy old texture data over.
	data = (::u8 *)malloc(width * height);
	if (data == NULL)
		return 0;
	for (i = 0; i < stash->params.height; i++) {
		::u8 * dst = &data[i * width];
		::u8 * src = &stash->texData[i * stash->params.width];
		::memory_copy(dst, src, stash->params.width);
		if (width > stash->params.width)
			::memory_set(dst + stash->params.width, 0, width - stash->params.width);
	}
	if (height > stash->params.height)
		::memory_set(&data[stash->params.height * width], 0, (height - stash->params.height) * width);

	free(stash->texData);
	stash->texData = data;

	// Increase atlas size
	fons__atlasExpand(stash->atlas, width, height);

	// Add existing data as dirty.
	for (i = 0; i < stash->atlas->nnodes; i++)
		maxy = fons__maxi(maxy, stash->atlas->nodes[i].y);
	stash->dirtyRect[0] = 0;
	stash->dirtyRect[1] = 0;
	stash->dirtyRect[2] = stash->params.width;
	stash->dirtyRect[3] = maxy;

	stash->params.width = width;
	stash->params.height = height;
	stash->itw = 1.0f / stash->params.width;
	stash->ith = 1.0f / stash->params.height;

	return 1;
}

::i32 fonsResetAtlas(FONScontext * stash, ::i32 width, ::i32 height)
{
	::i32 i, j;
	if (stash == NULL) return 0;

	// Flush pending glyphs.
	fons__flush(stash);

	// Create aaa_primitive_new texture
	if (stash->params.renderResize != NULL) {
		if (stash->params.renderResize(stash->params.userPtr, width, height) == 0)
			return 0;
	}

	// Reset atlas
	fons__atlasReset(stash->atlas, width, height);

	// Clear texture data.
	stash->texData = (::u8 *)realloc(stash->texData, width * height);
	if (stash->texData == NULL) return 0;
	::memory_set(stash->texData, 0, width * height);

	// Reset dirty rect
	stash->dirtyRect[0] = width;
	stash->dirtyRect[1] = height;
	stash->dirtyRect[2] = 0;
	stash->dirtyRect[3] = 0;

	// Reset cached glyphs
	for (i = 0; i < stash->nfonts; i++) {
		FONSfont * font = stash->fonts[i];
		font->nglyphs = 0;
		for (j = 0; j < FONS_HASH_LUT_SIZE; j++)
			font->lut[j] = -1;
	}

	stash->params.width = width;
	stash->params.height = height;
	stash->itw = 1.0f / stash->params.width;
	stash->ith = 1.0f / stash->params.height;

	// Add white rect at 0,0 for debug drawing.
	fons__addWhiteRect(stash, 2, 2);

	return 1;
}


#endif
