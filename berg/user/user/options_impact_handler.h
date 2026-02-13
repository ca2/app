// From options_impact.h by camilo 2023-08-22 05:57 <3ThomasBorregaardSorensen!!
#pragma once


#include "form_handler.h"


namespace user
{


   class CLASS_DECL_BERG options_impact_handler :
      virtual public ::berg::form_handler
   {
   public:


      options_impact_handler();
      ~options_impact_handler() override;


      virtual void create_options_impact(const ::atom & atom, ::user::interaction * puserinteractionParent);


   };



} // namespace user


