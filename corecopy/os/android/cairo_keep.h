#pragma once


class CLASS_DECL_CORE ca_cairo_keep
{
public:


   cairo_t *         m_pdc;
   bool              m_bSave;

   static cairo_surface_t * g_cairosurface;
   static cairo_t *  g_cairo;


   ca_cairo_keep(cairo_t * pdc, bool bSave = true);
   ~ca_cairo_keep();


   void save();
   void restore();
   void pulse();


};



