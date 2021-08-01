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


} // namespace draw2d_cairo





