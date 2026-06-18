//
// Created by camilo on 2022-09-08 22:16 <3ThomasBorregaardSorensen!!
//

//**
//* \brief Determine whether an icon ID is a texture loaded via ``::nano2d::_image_icon``.
//*
//* \rst
//* The implementation defines all ``value < 1024`` as image icons, and
//   * everything ``> = 1024`` as an Entypo icon(see :ref:`file_nanoui_entypo.h`).
//      * The value ``1024`` exists to provide a generous buffer on how many images
//      * may have been loaded by NanoVG.
//      * \endrst
//      *
//      *\param value
//      * The integral value of the icon.
//      *
//      *\return
//      *Whether or not this is an image icon.
//      * /
inline bool nano2d_is_image_icon(::i32 value) { return value < 1024; }

/**
 * \brief Determine whether an icon ID is a font-based icon (e.g. from ``entypo.ttf``).
 *
 * \rst
 * See :func:`nanoui::nano2d::_is_image_icon` for details.
 * \endrst
 *
 * \param value
 *     The integral value of the icon.
 *
 * \return
 *     Whether or not this is a font icon (from ``entypo.ttf``).
 */
inline bool nano2d_is_font_icon(::i32 value) { return value >= 1024; }



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
//#define NANO2D_KAPPA90 0.5522847493f   // Length proportional to radius of a cubic bezier handle for 90deg arcs.
//
//#define NANO2D_COUNTOF(arr) (sizeof(arr) / sizeof(0[arr]))

//
//enum NVGcommands {
//   ::nano2d::e_command_move_to = 0,
//   ::nano2d::e_command_line_to = 1,
//   ::nano2d::e_command_bezier_to = 2,
//   ::nano2d::e_command_close = 3,
//   ::nano2d::e_command_winding = 4,
//};
//
//enum NVGpointFlags
//{
//   NVG_PT_CORNER = 0x01,
//   NVG_PT_LEFT = 0x02,
//   NVG_PT_BEVEL = 0x04,
//   NVG_PR_INNERBEVEL = 0x08,
//};
//
//struct ::nano2d::state {
//   NVGcompositeOperationState compositeOperation;
//   ::i32 shapeAntiAlias;
//   ::nano2d::paint fill;
//   ::nano2d::paint stroke;
//   ::f32 strokeWidth;
//   ::f32 miterLimit;
//   ::i32 lineJoin;
//   ::i32 lineCap;
//   ::f32 alpha;
//   ::f32 xform[6];
//   NVGscissor scissor;
//   ::f32 fontSize;
//   ::f32 letterSpacing;
//   ::f32 lineHeight;
//   ::f32 fontBlur;
//   ::i32 textAlign;
//   ::i32 fontId;
//};
//typedef struct ::nano2d::state ::nano2d::state;
//
//struct NVGpoint {
//   ::f32 x, y;
//   ::f32 Δx, Δy;
//   ::f32 len;
//   ::f32 dmx, dmy;
//   ::u8 flags;
//};
//typedef struct NVGpoint NVGpoint;
//
//struct NVGpathCache {
//   NVGpoint * points;
//   ::i32 npoints;
//   ::i32 cpoints;
//   ::nano2d::path * paths;
//   ::i32 npaths;
//   ::i32 cpaths;
//   NVGvertex * verts;
//   ::i32 nverts;
//   ::i32 cverts;
//   ::f32 bounds[4];
//};
//typedef struct NVGpathCache NVGpathCache;

//struct NANO2D_CONTEXT {
//   NVGparams params;
//   ::f32 * m_faCommands;
//   ::i32 m_ccommands;
//   ::i32 m_ncommands;
//   ::f32 m_fCommandX, m_fCommandY;
//   ::nano2d::state states[NVG_MAX_STATES];
//   ::i32 m_nStates;
//   NVGpathCache * m_ppathcache;
//   ::f32 tessTol;
//   ::f32 distTol;
//   ::f32 fringeWidth;
//   ::f32 devicePxRatio;
//   struct FONScontext * fs;
//   ::i32 fontImages[NVG_MAX_FONTIMAGES];
//   ::i32 fontImageIdx;
//   ::i32 drawCallCount;
//   ::i32 fillTriCount;
//   ::i32 strokeTriCount;
//   ::i32 textTriCount;
//};

inline ::f32 __sqrtf(::f32 a) { return sqrtf(a); }
//static ::f32 __modf(::f32 a, ::f32 b) { return fmodf(a, b); }
inline ::f32 __sinf(::f32 a) { return sinf(a); }
inline ::f32 __cosf(::f32 a) { return cosf(a); }
inline ::f32 __tanf(::f32 a) { return tanf(a); }
inline ::f32 __atan2f(::f32 a, ::f32 b) { return atan2f(a, b); }
inline ::f32 __acosf(::f32 a) { return acosf(a); }

//inline ::i32 __mini(::i32 a, ::i32 b) { return a < b ? a : b; }
//inline ::i32 __maxi(::i32 a, ::i32 b) { return a > b ? a : b; }
//inline ::i32 __clampi(::i32 a, ::i32 mn, ::i32 mx) { return a < mn ? mn : (a > mx ? mx : a); }
inline ::f32 __minf(::f32 a, ::f32 b) { return a < b ? a : b; }
inline ::f32 __maxf(::f32 a, ::f32 b) { return a > b ? a : b; }
inline ::f32 __absf(::f32 a) { return a >= 0.0f ? a : -a; }
inline ::f32 __signf(::f32 a) { return a >= 0.0f ? 1.0f : -1.0f; }
//static ::f32 __clampf(::f32 a, ::f32 mn, ::f32 mx) { return a < mn ? mn : (a > mx ? mx : a); }
inline ::f32 __cross(::f32 dx0, ::f32 dy0, ::f32 dx1, ::f32 dy1) { return dx1 * dy0 - dx0 * dy1; }

inline ::f32 __normalize(::f32 * x, ::f32 * y)
{
   ::f32 d = __sqrtf((*x) * (*x) + (*y) * (*y));
   if (d > 1e-6f) {
      ::f32 id = 1.0f / d;
      *x *= id;
      *y *= id;
   }
   return d;
}


//static void context::__deletePathCache)(NVGpathCache * c)
//{
//   if (c == NULL) return;
//   if (c->points != NULL) free(c->points);
//   if (c->paths != NULL) free(c->paths);
//   if (c->verts != NULL) free(c->verts);
//   free(c);
//}

//static NVGpathCache * context::__allocPathCache)(void)
//{
//   NVGpathCache * c = (NVGpathCache *)malloc(sizeof(NVGpathCache));
//   if (c == NULL) goto error;
//   ::memory_set(c, 0, sizeof(NVGpathCache));
//
//   c->points = (NVGpoint *)malloc(sizeof(NVGpoint) * NVG_INIT_POINTS_SIZE);
//   if (!c->points) goto error;
//   c->npoints = 0;
//   c->cpoints = NVG_INIT_POINTS_SIZE;
//
//   c->paths = (::nano2d::path *)malloc(sizeof(::nano2d::path) * NVG_INIT_PATHS_SIZE);
//   if (!c->paths) goto error;
//   c->npaths = 0;
//   c->cpaths = NVG_INIT_PATHS_SIZE;
//
//   c->verts = (NVGvertex *)malloc(sizeof(NVGvertex) * NVG_INIT_VERTS_SIZE);
//   if (!c->verts) goto error;
//   c->nverts = 0;
//   c->cverts = NVG_INIT_VERTS_SIZE;
//
//   return c;
//error:
//   context::__deletePathCache)(c);
//   return NULL;
//}

//static void context::__setDevicePixelRatio(::f32 ratio)
//{
//   tessTol = 0.25f / ratio;
//   distTol = 0.01f / ratio;
//   fringeWidth = 1.0f / ratio;
//   devicePxRatio = ratio;
//}

inline ::nano2d::compositeOperationState __compositeOperationState(::i32 op)
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



} // namespace nano2d




