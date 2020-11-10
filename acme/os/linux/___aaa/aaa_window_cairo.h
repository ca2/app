#pragma once


#include "cairo/cairo.h"


class CLASS_DECL_ACME window_cairo :
   virtual public ::graphics::graphics
{
public:


   cairo_t *                     m_cairo;
   cairo_surface_t *             m_cairosurface;
   cairo_t *                     m_cairoSource;
   cairo_surface_t *             m_cairosurfaceSource;
   memory                 m_mem;


   window_cairo();
   virtual ~window_cairo();

   virtual void create_window_graphics(oswindow window, i64 cx, i64 cy, int iStride = -1);
   virtual void destroy_window_graphics();

   virtual void update_window(oswindow window, color32_t * pOsBitmapData, const ::rect & rect, int iStride = -1);


};
