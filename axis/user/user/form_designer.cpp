// Created by camilo on 2023-07-14 14:52 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "form_designer.h"
#include "line_layout.h"


namespace axis
{


   form_designer::form_designer()
   {


   }


   form_designer::~form_designer()
   {


   }



   ::pointer < ::user::line_layout > form_designer::create_line_layout(::user::interaction * puserinteractionParent, enum_orientation eorientation)
   {

      auto plinelayout = __create_new < ::user::line_layout >();

      plinelayout->m_eorientation = eorientation;

      plinelayout->create_child(puserinteractionParent);

      plinelayout->display();

      plinelayout->set_need_layout();

      return plinelayout;

   }


} // namespace axis




