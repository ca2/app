#pragma once


#include "object.h"
#include "aura/graphics/draw2d/path.h"


namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO path :
      virtual public ::draw2d_cairo::object,
      virtual public ::draw2d::path
   {
   public:


      path();
      ~path() override;


      bool create(::draw2d::graphics * pgraphics);
      void destroy() override;

      bool contains(::draw2d::graphics_pointer & pgraphics, const double_point& point) override;


   };









} // namespace draw2d_cairo



