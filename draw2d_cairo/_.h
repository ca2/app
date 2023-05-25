#pragma once


#include "aura/_.h" // psystem->ftlibrary()


#include "acme/primitive/primitive/holder.h"
////#include "aura/graphics/draw2d/_component.h"
//#include "acme/primitive/geometry2d/_impl.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"


// apt install libcairo2-dev
// dnf install cairo-devel pango
#include <cairo/cairo-features.h>
#include <cairo/cairo.h>
#include <cairo/cairo-ft.h>
#ifdef WINDOWS_DESKTOP
#include "cairo/cairo-win32.h"
#endif


#if defined(_draw2d_cairo_project)
#define CLASS_DECL_DRAW2D_CAIRO  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_DRAW2D_CAIRO  CLASS_DECL_IMPORT
#endif


#include "acme/operating_system/ansi/_pthread.h"


#define TOY_FONT_SELECTION 0


#if defined(LINUX)

#define USE_PANGO

#include <pango/pango.h>

#endif


::particle * cairo_mutex();
void init_cairo_mutex();
void destroy_cairo_mutex();


void destroy_pointer(cairo_surface_t* p);
void destroy_pointer(cairo_pattern_t* p);


using cairo_surface_holder = ::holder < cairo_surface_t* >;
using cairo_pattern_holder = ::holder < cairo_pattern_t* >;


void copy(::rectangle_i32 * prectTarget, const cairo_rectangle_int_t * prectSource);
void copy(cairo_rectangle_int_t * prectTarget, const ::rectangle_i32 * prectSource);


namespace draw2d_cairo
{




} // namespace draw2d_cairo


#define __graphics(pgraphics) ((::draw2d_cairo::graphics *) pgraphics->m_pthis)
#define __pen(ppen) ((::draw2d_cairo::pen *) ppen->m_pthis)
#define __brush(pbrush) ((::draw2d_cairo::brush *) pbrush->m_pthis)
#define __font(pfont) ((::draw2d_cairo::font *) pfont->m_pthis)
#define __graphics_path(ppath) ((::draw2d_cairo::path *) ppath->m_pthis)

FT_Library __ftlibrary();

//void copy(::draw2d::matrix * pmatrix, const cairo_matrix_t * pcairomatrix);

//void copy(cairo_matrix_t* pcairomatrix,  const ::draw2d::matrix* pmatrix);



#define TOY_FONT_SELECTION 0


#if defined(LINUX)

#define USE_PANGO

#endif





::particle * cairo_mutex();
void init_cairo_mutex();
void destroy_cairo_mutex();


void destroy_pointer(cairo_surface_t * p);
void destroy_pointer(cairo_pattern_t * p);


using cairo_surface_holder = ::holder < cairo_surface_t * >;
using cairo_pattern_holder = ::holder < cairo_pattern_t * >;



void copy(::rectangle_i32 * prectTarget, const cairo_rectangle_int_t * prectSource);
void copy(cairo_rectangle_int_t * prectTarget, const ::rectangle_i32 * prectSource);


namespace draw2d_cairo
{




} // namespace draw2d_cairo


#define __graphics(pgraphics) ((::draw2d_cairo::graphics *) pgraphics->m_pthis)
#define __pen(ppen) ((::draw2d_cairo::pen *) ppen->m_pthis)
#define __brush(pbrush) ((::draw2d_cairo::brush *) pbrush->m_pthis)
#define __font(pfont) ((::draw2d_cairo::font *) pfont->m_pthis)
#define __graphics_path(ppath) ((::draw2d_cairo::path *) ppath->m_pthis)

FT_Library __ftlibrary();

CLASS_DECL_DRAW2D_CAIRO void copy(::draw2d::matrix * pmatrix, const cairo_matrix_t * pcairomatrix);


CLASS_DECL_DRAW2D_CAIRO void copy(cairo_matrix_t * pcairomatrix, const ::draw2d::matrix * pmatrix);

