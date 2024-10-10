// Created by camilo on 2023-10-09 11:54 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "color_selector_popup.h"
#include "acme/prototype/geometry2d/_text_stream.h"


namespace user
{


   color_selector_popup::color_selector_popup()
   {


   }


   color_selector_popup::~color_selector_popup()
   {


   }


   void color_selector_popup::install_message_routing(channel * pchannel)
   {

      ::user::color_selector_control::install_message_routing(pchannel);

      ::user::popup::install_message_routing(pchannel);

   }


   void color_selector_popup::show_popup(const ::point_i32 & point)
   {

      information() << "show_popup : " << point;

      popup::show_popup(point);

   }


} // namespace user



