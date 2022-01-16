#pragma once


#include "aura/_.h" // psystem->ftlibrary()

#include "aura/operating_system.h"
#include "aura/graphics/draw2d/_draw2d.h"
#include "acme/primitive/geometry2d/_impl.h"


#define TOY_FONT_SELECTION 0


#if defined(LINUX)

#define USE_PANGO

#endif


#include "acme/node/operating_system/ansi/_pthread.h"


// apt install libcairo2-dev
// dnf install cairo-devel pango
#include <cairo/cairo-features.h>
#include <cairo/cairo.h>
#include <cairo/cairo-ft.h>
#ifdef WINDOWS_DESKTOP
#include "cairo/cairo-win32.h"
#endif


::mutex * cairo_mutex();
void init_cairo_mutex();
void destroy_cairo_mutex();


void destroy_pointer(cairo_surface_t* p);
void destroy_pointer(cairo_pattern_t* p);


using cairo_surface_holder = ::holder < cairo_surface_t* >;
using cairo_pattern_holder = ::holder < cairo_pattern_t* >;


#ifdef _DRAW2D_CAIRO_LIBRARY
#define CLASS_DECL_DRAW2D_CAIRO  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_DRAW2D_CAIRO  CLASS_DECL_IMPORT
#endif


void copy(RECTANGLE_I32 * prectTarget, const cairo_rectangle_int_t * prectSource);
void copy(cairo_rectangle_int_t * prectTarget, const RECTANGLE_I32 * prectSource);


namespace draw2d_cairo
{


   enum enum_mask
   {

      e_mask_fill,
      e_mask_paint,
      e_mask_paint_with_alpha,

   };


} // namespace draw2d_cairo


#define __graphics(pgraphics) ((::draw2d_cairo::graphics *) pgraphics->m_pthis)
#define __pen(ppen) ((::draw2d_cairo::pen *) ppen->m_pthis)
#define __brush(pbrush) ((::draw2d_cairo::brush *) pbrush->m_pthis)
#define __font(pfont) ((::draw2d_cairo::font *) pfont->m_pthis)
#define __graphics_path(ppath) ((::draw2d_cairo::path *) ppath->m_pthis)

FT_Library __ftlibrary();

inline void copy(::draw2d::matrix * pmatrix, const cairo_matrix_t * pcairomatrix)
{

   pmatrix->a1 = pcairomatrix->xx;
   pmatrix->a2 = pcairomatrix->yx;
   pmatrix->b1 = pcairomatrix->xy;
   pmatrix->b2 = pcairomatrix->yy;
   pmatrix->c1 = pcairomatrix->x0;
   pmatrix->c2 = pcairomatrix->y0;

}


inline void copy(cairo_matrix_t* pcairomatrix,  const ::draw2d::matrix* pmatrix)
{

   pcairomatrix->xx = pmatrix->a1;
   pcairomatrix->yx = pmatrix->a2;
   pcairomatrix->xy = pmatrix->b1;
   pcairomatrix->yy = pmatrix->b2;
   pcairomatrix->x0 = pmatrix->c1;
   pcairomatrix->y0 = pmatrix->c2;

}


#include "factory_exchange.h"
#include "keep.h"


#include "object.h"
#include "pen.h"
#include "bitmap.h"
#include "brush.h"
#include "font.h"
#include "palette.h"
#include "region.h"
#include "image.h"
#include "path.h"


#include "graphics.h"



#include "draw2d.h"


#include "_impl.h"



