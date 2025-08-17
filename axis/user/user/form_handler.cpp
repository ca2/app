// Created by camilo on 2023-07-14 14:52 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "form_handler.h"
#include "line_layout.h"


namespace axis
{


   form_handler::form_handler()
   {


   }


   form_handler::~form_handler()
   {


   }


   ::pointer < ::user::line_layout > form_handler::create_line_layout(::user::interaction * puserinteractionParent, enum_orientation eorientation)
   {

      auto plinelayout = øcreate_new < ::user::line_layout >();

      plinelayout->create_line_layout(puserinteractionParent, eorientation);

      return plinelayout;

   }


} // namespace axis




