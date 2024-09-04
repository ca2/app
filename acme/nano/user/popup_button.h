//
// Created by camilo on 2022-02-16 22:38 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "window.h"

namespace nano
{

namespace user
{

class popup_button :
   virtual public ::nano::user::window
{
public:



   popup_button();
   ~popup_button() override;



   void calculate_size_and_position(int x = INT_MIN, int y = INT_MIN);


   virtual void initialize_popup_button(const ::string & strText, int x, int y);

   void on_click(const ::payload& payload, ::user::mouse * pmouse) override;

   void on_draw(::nano::user::device * pnanodevice) override;


};


   } // namespace user


} // namespace nano



