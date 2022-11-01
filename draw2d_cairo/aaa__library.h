// Created by camilo on 2022-07-30 01:27 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/operating_system/ansi/_pthread.h"


#define TOY_FONT_SELECTION 0


#if defined(LINUX)

#define USE_PANGO

#endif





::particle * cairo_mutex();
void init_cairo_mutex();
void destroy_cairo_mutex();


void destroy_pointer(cairo_surface_t* p);
void destroy_pointer(cairo_pattern_t* p);


using cairo_surface_holder = ::holder < cairo_surface_t* >;
using cairo_pattern_holder = ::holder < cairo_pattern_t* >;



void copy(RECTANGLE_I32 * prectTarget, const cairo_rectangle_int_t * prectSource);
void copy(cairo_rectangle_int_t * prectTarget, const RECTANGLE_I32 * prectSource);


namespace draw2d_cairo
{




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



