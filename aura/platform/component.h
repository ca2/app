// Created by camilo on 2025-03-09 02:03 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/platform/component.h"
#include "aura/user/user/form_handler.h"


namespace aura
{


   class CLASS_DECL_AURA component :
      virtual public ::apex::component,
      virtual public ::user::form_handler
   {
   public:


      void _001CreateForm(user::interaction* puserinteractionParent) override;


   };


} // namespace aura