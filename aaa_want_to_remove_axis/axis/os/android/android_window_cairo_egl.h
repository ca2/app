#pragma once


class CLASS_DECL_AXIS window_cairo_egl :
   public window_graphics
{
public:


   cairo_t *                           m_cairo;
   cairo_surface_t *                   m_cairosurface;
   memory                 m_mem;
   size                                m_size;


   window_cairo_egl();
   virtual ~window_cairo_egl();


   virtual void create_window_graphics(oswindow interaction_impl, i64 cx, i64 cy, int iStride = -1);
   virtual void destroy_window_graphics();

   virtual void update_window(oswindow interaction_impl, COLORREF * pOsBitmapData, const ::rect & rect, int iStride = -1);

};
