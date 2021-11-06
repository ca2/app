#include "framework.h"


cairo_surface_t *  ca_cairo_keep::g_cairosurface = nullptr;
cairo_t *  ca_cairo_keep::g_cairo = nullptr;


ca_cairo_keep::ca_cairo_keep(cairo_t * pgraphics, bool bSave)
{

   m_pdc = pgraphics;

   m_bSave = false;

   if(bSave)
      save();


}


ca_cairo_keep::~ca_cairo_keep()
{

   if(m_bSave)
   {

      restore();

   }

}



void ca_cairo_keep::save()
{

   if(m_bSave)
      return;

   cairo_save(m_pdc);

   m_bSave = true;

}


void ca_cairo_keep::restore()
{

   if(!m_bSave)
      return;

   cairo_restore(m_pdc);

   m_bSave = false;

}


void ca_cairo_keep::pulse()
{

   save();

   restore();

}



