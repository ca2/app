//
// Created by camilo on 2022-02-16 22:38 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "interchange.h"

namespace nano
{

namespace user
{

class popup_button :
   virtual public ::nano::user::interchange
{
public:



   popup_button();
   ~popup_button() override;



   void calculate_size_and_position(int x = INT_MIN, int y = INT_MIN);


   virtual void initialize_popup_button(const ::string & strText, int x, int y, ::nano::user::interchange * pinterchangeParent);

   void on_click(const ::payload& payload, ::user::mouse * pmouse) override;

   void on_draw(::nano::graphics::device * pnanodevice) override;


   virtual ::pointer < ::operating_system::a_system_menu > create_system_menu(bool bContextual = true);

};


   } // namespace user


} // namespace nano



