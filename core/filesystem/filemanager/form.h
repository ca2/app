#pragma once


#include "impact_base.h"
#include "base/user/form/impact.h"


namespace filemanager
{


   class CLASS_DECL_CORE form :
      virtual public ::filemanager_show < ::user::form_impact >
   {
   public:

      form();
      form(form&&)=delete;


      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


   };



} // namespace filemanager



















