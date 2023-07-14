// Created by camilo on 2023-07-14 14:48 <3ThomasBorregaardSorensen!!
#pragma once


#include "aura/user/user/form_designer.h"


namespace axis
{


   class CLASS_DECL_AXIS form_designer :
      virtual public ::user::form_designer
   {
   public:


      form_designer();
      ~form_designer() override;


      ::pointer < ::user::line_layout > create_line_layout(::user::interaction * puserinteractionParent, enum_orientation eorientation);




   };


} // namespace axis



