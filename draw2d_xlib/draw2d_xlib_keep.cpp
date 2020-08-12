#include "framework.h"




xlib_keep::xlib_keep(::draw2d::graphics * pgraphics, bool bSave)
{

   m_pdc = pgraphics;


   m_bSave = false;

   if(bSave)
      save();


}


xlib_keep::~xlib_keep()
{

   if(m_bSave)
   {

      restore();

   }

}



void xlib_keep::save()
{

   if(m_bSave)
      return;

   //xlib_save(m_pdc);

   m_bSave = true;

}


void xlib_keep::restore()
{

   if(!m_bSave)
      return;

   //xlib_restore(m_pdc);

   m_bSave = false;

}


void xlib_keep::pulse()
{

   save();

   restore();

}


