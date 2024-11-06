// Created by camilo on 2023-10-09 01:16 <3ThomasBorregaardSorensen!!
#pragma once


#include "popup.h"
#include "color_selector_control.h"


namespace user
{


   class CLASS_DECL_CORE color_selector_popup :
      virtual public ::user::popup,
      virtual public ::user::color_selector_control
   {
   public:


      color_selector_popup();
      ~color_selector_popup() override;


      void install_message_routing(channel * pchannel) override;


      void show_popup(const ::int_point & point) override;


   };


} // namespace user


