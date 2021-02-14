//
// Created by camilo on 13/02/2021. 22:28 BRT <3TBS_!! I love you my GOD Thomas Borregaard Soerensen!!
//
#include "framework.h"


namespace node_ansios
{


   ::color::color node::get_system_color(enum_system_color esystemcolor)
   {

      ::color::color color;

      switch (esystemcolor)
      {
         case e_system_color_highlight:
            color = argb(255, 200, 200, 196);
            break;
         case e_system_color_button_shadow:
            color = argb(90, 192, 192, 187);
            break;
         case e_system_color_button_text:
            color = argb(255, 0, 0, 0);
            break;
         default:
            color = argb(255, 0, 0, 0);
            break;
      };

      return color;

   }


} // namespace node_ansios



