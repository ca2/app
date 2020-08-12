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


   void path::destroy()
   {

      ::draw2d::path::destroy();

   }


} // namespace draw2d_cairo





