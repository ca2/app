//
// Created by camilo on 2022-01-21 14:57 <3ThomasBorregaardSorensen
// Generalized by camilo on 31/01/2022 14:28 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/user/micro/message_box.h"


namespace micro
{


   class CLASS_DECL_ACME details_window :
      virtual public ::micro::message_box
   {
   public:



      details_window();
      ~details_window() override;


      void calculate_size() override;



      void on_click(const ::payload & payload, ::user::mouse * pmouse) override;


   };


} // namespace nano



