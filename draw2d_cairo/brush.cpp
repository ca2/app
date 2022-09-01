#include "framework.h"
#include "brush.h"


namespace draw2d_cairo
{


   brush::brush()
   {

      m_pthis = this;

   }


   brush::~brush()
   {

   }


   void brush::dump(dump_context & dumpcontext) const
   {

      object::dump(dumpcontext);

   }


   bool brush::create(::draw2d::graphics * pgraphics)
   {

      m_osdata[0] = this;

      return true;

   }


   void brush::destroy()
   {

      //auto estatus = 
      
      ::draw2d::brush::destroy();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


} // namespace draw2d_cairo



