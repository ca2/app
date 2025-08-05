// From options_impact.h by camilo 2023-08-22 05:57 <3ThomasBorregaardSorensen!!
#pragma once


#include "form_handler.h"


namespace user
{


   class CLASS_DECL_BERG options_impact_handler :
      virtual public ::base::form_handler
   {
   public:


      virtual void create_options_impact(::user::interaction * puserinteractionParent) = 0;


   };



} // namespace user


