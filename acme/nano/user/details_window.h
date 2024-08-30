//
// Created by camilo on 2022-01-21 14:57 <3ThomasBorregaardSorensen
// Generalized by camilo on 31/01/2022 14:28 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "message_box.h"

namespace nano
{

   namespace user
   {
   

class details_window :
   virtual public ::nano::user::message_box
{
public:



   details_window();
   ~details_window() override;


   void calculate_size() override;



   void on_click(const ::payload& payload, ::user::mouse * pmouse) override;


};


   } // namespace user


} // namespace nano



