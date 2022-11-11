#pragma once


#include "aura/graphics/draw2d/brush.h"


namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO brush :
      virtual public ::draw2d::brush
   {
   public:


      brush();
      ~brush() override;


      bool create(::draw2d::graphics * pgraphics);
      void destroy() override;


      // void dump(dump_context & dumpcontext) const override;


   };


} // namespace draw2d_cairo



