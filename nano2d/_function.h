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
inline bool nano2d_is_image_icon(int value) { return value < 1024; }

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
inline bool nano2d_is_font_icon(int value) { return value >= 1024; }



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
//   int shapeAntiAlias;
//   ::nano2d::paint fill;
//   ::nano2d::paint stroke;
//   float strokeWidth;
//   float miterLimit;
//   int lineJoin;
//   int lineCap;
//   float alpha;
//   float xform[6];
//   NVGscissor scissor;
//   float fontSize;
//   float letterSpacing;
//   float lineHeight;
//   float fontBlur;
//   int textAlign;
//   int fontId;
//};
//typedef struct ::nano2d::state ::nano2d::state;
//
//struct NVGpoint {
//   float x, y;
//   float Δx, Δy;
//   float len;
//   float dmx, dmy;
//   unsigned char flags;
//};
//typedef struct NVGpoint NVGpoint;
//
//struct NVGpathCache {
//   NVGpoint * points;
//   int npoints;
//   int cpoints;
//   ::nano2d::path * paths;
//   int npaths;
//   int cpaths;
//   NVGvertex * verts;
//   int nverts;
//   int cverts;
//   float bounds[4];
//};
//typedef struct NVGpathCache NVGpathCache;

//struct NANO2D_CONTEXT {
//   NVGparams params;
//   float * m_faCommands;
//   int m_ccommands;
//   int m_ncommands;
//   float m_fCommandX, m_fCommandY;
//   ::nano2d::state states[NVG_MAX_STATES];
//   int m_nStates;
//   NVGpathCache * m_ppathcache;
//   float tessTol;
//   float distTol;
//   float fringeWidth;
//   float devicePxRatio;
//   struct FONScontext * fs;
//   int fontImages[NVG_MAX_FONTIMAGES];
//   int fontImageIdx;
//   int drawCallCount;
//   int fillTriCount;
//   int strokeTriCount;
//   int textTriCount;
//};

inline float __sqrtf(float a) { return sqrtf(a); }
//static float __modf(float a, float b) { return fmodf(a, b); }
inline float __sinf(float a) { return sinf(a); }
inline float __cosf(float a) { return cosf(a); }
inline float __tanf(float a) { return tanf(a); }
inline float __atan2f(float a, float b) { return atan2f(a, b); }
inline float __acosf(float a) { return acosf(a); }

//inline int __mini(int a, int b) { return a < b ? a : b; }
//inline int __maxi(int a, int b) { return a > b ? a : b; }
//inline int __clampi(int a, int mn, int mx) { return a < mn ? mn : (a > mx ? mx : a); }
inline float __minf(float a, float b) { return a < b ? a : b; }
inline float __maxf(float a, float b) { return a > b ? a : b; }
inline float __absf(float a) { return a >= 0.0f ? a : -a; }
inline float __signf(float a) { return a >= 0.0f ? 1.0f : -1.0f; }
//static float __clampf(float a, float mn, float mx) { return a < mn ? mn : (a > mx ? mx : a); }
inline float __cross(float dx0, float dy0, float dx1, float dy1) { return dx1 * dy0 - dx0 * dy1; }

inline float __normalize(float * x, float * y)
{
   float d = __sqrtf((*x) * (*x) + (*y) * (*y));
   if (d > 1e-6f) {
      float id = 1.0f / d;
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
//   memset(c, 0, sizeof(NVGpathCache));
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

//static void context::__setDevicePixelRatio(float ratio)
//{
//   tessTol = 0.25f / ratio;
//   distTol = 0.01f / ratio;
//   fringeWidth = 1.0f / ratio;
//   devicePxRatio = ratio;
//}

inline ::nano2d::compositeOperationState __compositeOperationState(int op)
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



} // namespace nano2d




