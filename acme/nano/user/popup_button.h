//
// Created by camilo on 2022-02-16 22:38 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "interaction.h"


namespace nano
{


   namespace user
   {


      class popup_button :
         virtual public ::nano::user::interaction
      {
      public:

         ::pointer < ::nano::user::interaction >      m_puserinteractionbaseOwner;

         popup_button();
         ~popup_button() override;



         void calculate_size_and_position(int x = INT_MIN, int y = INT_MIN);


         virtual void initialize_popup_button(const ::string & strText, int x, int y, ::nano::windowing::window * pnanowindowingwindowOwner);

         void on_click(const ::payload & payload, ::user::mouse * pmouse) override;

         void on_draw(::nano::graphics::device * pnanodevice) override;


         ::pointer < ::operating_system::a_system_menu > create_system_menu(bool bContextual = true) override;

      };


   } // namespace user


} // namespace nano



