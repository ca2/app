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


      virtual void handle(::topic * ptopic, ::context * pcontext) override;


   };



} // namespace filemanager



















