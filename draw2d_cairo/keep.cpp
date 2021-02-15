#include "framework.h"


cairo_keep::cairo_keep(cairo_t * pgraphics, bool bSave)
{

   m_bSave = false;

   if (pgraphics == nullptr)
   {

      m_pdc = nullptr;

      return;

   }

   m_pdc = pgraphics;

   if (bSave)
   {

      save();

   }

}


cairo_keep::~cairo_keep()
{

   if(m_bSave)
   {

      restore();

   }

}



void cairo_keep::save()
{

   if(m_pdc == nullptr)
      return;

   if(m_bSave)
      return;

   synchronization_lock synchronizationlock(cairo_mutex());

   cairo_save(m_pdc);

   m_bSave = true;

}


void cairo_keep::restore()
{

   synchronization_lock ml(cairo_mutex());

   if(m_pdc == nullptr)
   {

      return;

   }

   if(!m_bSave)
   {

      return;

   }

   cairo_restore(m_pdc);

   m_bSave = false;

}


void cairo_keep::pulse()
{

   synchronization_lock ml(cairo_mutex());

   restore();

   save();

}

