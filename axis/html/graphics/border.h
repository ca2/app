#pragma once


#include "acme/primitive/geometry2d/_geometry2d.h"


namespace html
{


   class CLASS_DECL_AXIS border :
      public ::rectangle_f32
   {
   public:

      enum e_style
      {

         style_solid,

      };


      ::color::color    crLeft;
      ::color::color    crTop;
      ::color::color    crRight;
      ::color::color    crBottom;
      
      e_style     styleLeft;
      e_style     styleTop;
      e_style     styleRight;
      e_style     styleBottom;

      
   };


} // namespace html




