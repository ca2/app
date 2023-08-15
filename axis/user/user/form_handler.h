// Created by camilo on 2023-07-14 14:48 <3ThomasBorregaardSorensen!!
#pragma once


#include "aura/user/user/form_handler.h"


namespace axis
{


   class CLASS_DECL_AXIS form_handler :
      virtual public ::user::form_handler
   {
   public:


      form_handler();
      ~form_handler() override;


      ::pointer < ::user::line_layout > create_line_layout(::user::interaction * puserinteractionParent, enum_orientation eorientation);




   };


} // namespace axis



