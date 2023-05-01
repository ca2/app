#pragma once


#include "aura/platform/application.h"


namespace app_app
{


   class CLASS_DECL_APP_APP application :
      virtual public ::aura::application
   {
   public:


      application();
      ~application() override;


      virtual void on_request(::request * prequest) override;


      string draw2d_get_default_implementation_name() override;


   };


} // namespace app_app



