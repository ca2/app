#include "framework.h"
#include "path.h"
#include "graphics.h"


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


   void path::destroy()
   {

      //auto estatus = 
      
      ::draw2d::path::destroy();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   bool path::contains(::draw2d::graphics_pointer & pgraphics, const point_f64& point)
   {

      auto pcairographics = pgraphics.cast < graphics >();

      if(::is_null(pcairographics))
      {

         return ::draw2d::path::contains(pgraphics, point);

      }

      pcairographics->_set(this);

      if(pgraphics->fill_contains(point))
      {

         information("cairo in fill");

         return true;

      }
      else
      {

         information("cairo NOT in fill");

         return false;

      }

   }


} // namespace draw2d_cairo



