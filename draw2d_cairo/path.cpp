#include "framework.h"


namespace draw2d_cairo
{


   path::path()
   {

      m_pthis = this;

   }

   path::~path()
   {

   }


   bool path::create(::draw2d::graphics * pgraphics)
   {

      m_osdata[0] = this;

      return true;

   }


   ::e_status path::destroy()
   {

      auto estatus = ::draw2d::path::destroy();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   bool path::contains(::draw2d::graphics_pointer & pgraphics, const point_f64& point)
   {

      if(!pgraphics)
      {

         auto psystem = m_psystem->m_paurasystem;

         auto pdraw2d = psystem->draw2d();

         pgraphics = pdraw2d->create_memory_graphics();

      }

      pgraphics.cast < graphics >()->_set(this);

      return pgraphics->fill_contains(point);


   }



} // namespace draw2d_cairo





