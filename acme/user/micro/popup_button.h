//
// Created by camilo on 2022-02-16 22:38 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/user/micro/main_window.h"


namespace micro
{

      class popup_button :
         virtual public ::micro::main_window
      {
      public:

         
         ::payload m_payloadPopupButtonResult;


         popup_button();
         ~popup_button() override;

         
         void create_window() override;


         void calculate_size_and_position(int x = INT_MIN, int y = INT_MIN);


         virtual void initialize_popup_button(const ::string & strText, int x, int y, ::acme::windowing::window * pacmewindowingwindowOwner);

         void on_click(const ::payload & payload, ::user::mouse * pmouse) override;

         void on_draw(::nano::graphics::device * pnanodevice) override;


         ::pointer < ::operating_system::a_system_menu > create_system_menu(bool bContextual = true) override;

      };


} // namespace micro



