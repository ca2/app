// form_maker.h turn into form_handler.h from axis/form_handler by
// camilo on 2023-08-22 02:10 <3ThomasBorregaardSorensen!!
#pragma once


#include "axis/user/user/form_handler.h"


namespace base
{


   class CLASS_DECL_BASE form_handler :
      virtual public ::axis::form_handler
   {
   public:


      form_handler();
      ~form_handler() override;


      //::pointer < ::user::line_layout > create_line_layout(::user::interaction * puserinteractionParent, enum_orientation eorientation);




   };


} // namespace axis




//// Created by camilo <3ThomasBorregaardSorensen!!
//#pragma once
//
//
//namespace user
//{
//
//   class CLASS_DECL_AURA form_maker :
//      public ::axis::form_designer
//   {
//   public:
//
//      
//      virtual void make_form(::user::interaction * puserinteraction) = 0;
//
//
//   };
//
//
//} // namespace user
//
//
//
//
