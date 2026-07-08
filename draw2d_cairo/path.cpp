#include "framework.h"
#include "draw2d.h"
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


   //bool path::contains(::draw2d::graphics_pointer & pgraphics, const ::f64_point& point)
   bool path::path_contains_point(const ::f64_point& point)
   {

      ::cast < ::draw2d_cairo::draw2d > pdraw2d = draw2d();

      ::cast < ::draw2d_cairo::graphics > pgraphics = pdraw2d->get_thread_graphics();
//      auto pcairographics = pgraphics.cast < graphics >();

      if(::is_null(pgraphics))
      {

         return ::draw2d::path::path_contains_point(point);

      }

      pgraphics->_set(this);

      if(pgraphics->fill_contains(point))
      {

         informationf("cairo in fill");

         return true;

      }
      else
      {

         informationf("cairo NOT in fill");

         return false;

      }

   }


} // namespace draw2d_cairo



