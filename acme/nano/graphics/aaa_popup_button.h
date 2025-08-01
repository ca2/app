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
   virtual public ::micro::elemental
{
public:



   popup_button();
   ~popup_button() override;



   void calculate_size_and_position(int x = INT_MIN, int y = INT_MIN);


   virtual void initialize_popup_button(const ::scoped_string & scopedstrText, int x, int y);

   void on_click(const ::payload& payload, ::user::mouse * pmouse) override;

   void on_draw(::nano::graphics::device * pnanodevice) override;


};


   } // namespace user


} // namespace nano



