#pragma once


#include "aura/platform/application.h"


namespace app_app
{


   class CLASS_DECL_APP_APP application :
      virtual public ::aura::application
   {
   public:
      ::pointer<::app_app::main_window> m_pmainwindow;

      application();
      ~application() override;
      
      __DECLARE_APPLICATION_RELEASE_TIME();



      virtual void on_request(::request * prequest) override;


      string draw2d_get_default_implementation_name() override;


   };


} // namespace app_app



