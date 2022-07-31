#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_library.h"
#endif


namespace draw2d_cairo
{


   pen::pen()
   {

      m_pthis = this;

   }


   pen::~pen()
   {

   }


   void pen::dump(dump_context & dumpcontext) const
   {

      object::dump(dumpcontext);

   }


   bool pen::create(::draw2d::graphics * pgraphics)
   {

      m_osdata[0] = this;

      return true;

   }


   void pen::destroy()
   {

      //auto estatus = 
      
      ::draw2d::pen::destroy();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


} // namespace draw2d_cairo



