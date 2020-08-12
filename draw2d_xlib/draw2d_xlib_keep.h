#pragma once


class CLASS_DECL_DRAW2D_XLIB xlib_keep
{
public:


   ::draw2d::graphics *         m_pdc;
   bool              m_bSave;

   //static xlib_surface_t * g_xlibsurface;
   //static xlib_t *  g_xlib;


   xlib_keep(::draw2d::graphics * pgraphics, bool bSave = true);
   ~xlib_keep();


   void save();
   void restore();
   void pulse();


};


