#pragma once


#include "object.h"
#include "aura/graphics/draw2d/pen.h"


namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO pen :
      virtual public ::draw2d_cairo::object,
      virtual public ::draw2d::pen
   {
   public:


      pen();
      ~pen() override;


      void update(::draw2d::graphics * pdraw2dgraphics) override;
      void destroy() override;


      // void dump(dump_context & dumpcontext) const override;


   };


} // namespace draw2d_cairo





