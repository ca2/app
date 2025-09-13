#include "framework.h"
#include "keep.h"
#include "draw2d.h"
#include "acme/parallelization/synchronous_lock.h"


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

   _synchronous_lock synchronouslock(::draw2d_cairo::mutex(), ::system(), SYNCHRONOUS_LOCK_SUFFIX);

   cairo_save(m_pdc);

   m_bSave = true;

}


void cairo_keep::restore()
{

   _synchronous_lock ml(::draw2d_cairo::mutex(), ::system(), SYNCHRONOUS_LOCK_SUFFIX);

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

   _synchronous_lock ml(::draw2d_cairo::mutex(), ::system(), SYNCHRONOUS_LOCK_SUFFIX);

   restore();

   save();

}

