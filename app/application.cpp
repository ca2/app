#include "framework.h"
#include "application.h"
#include "main_window.h"
#include "acme/platform/system.h"


__DECLARE_RELEASE_TIME(app_app);


namespace app_app
{


   __IMPLEMENT_APPLICATION_RELEASE_TIME(app_app);


   application::application()
   {
      
      m_strAppId = "app/app";

      m_strAppName = "app/app";

      m_strBaseSupportId = "app_app";

      m_bNetworking = false;

      m_bLicense = false;

      m_bImaging = false;

      m_bWriteText = false;

      m_bInterprocessCommunication = false;

   }


   application::~application()
   {

   }


   void application::on_request(::request * prequest)
   {

      auto pmainwindow = __create_new < ::app_app::main_window >();

      //pmainwindow->display(e_display_normal);

//      pmainwindow->m_procedureOnAfterCreate = [pmainwindow]()
//      {
//
//         //pmainwindow->set_need_layout();
//
//         pmainwindow->set_need_redraw();
//
//         pmainwindow->post_redraw();
//
//      };

      pmainwindow->create_main_window_asynchronously();

   }


   string application::draw2d_get_default_implementation_name()
   {

      //return acmesystem()->implementation_name("draw2d", "opengl");
      //return acmesystem()->implementation_name("draw2d", "gdiplus");
      return ::aura::application::draw2d_get_default_implementation_name();

   }

  
} // namespace app_app



