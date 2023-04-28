#include "framework.h"
#include "application.h"
#include "main_window.h"
#include "acme/platform/system.h"


namespace app_app
{


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

      pmainwindow->display(e_display_restored);

      pmainwindow->create_main_window();

      pmainwindow->set_need_layout();

      pmainwindow->set_need_redraw();

      pmainwindow->post_redraw();

   }


   string application::draw2d_get_default_implementation_name()
   {

      return acmesystem()->implementation_name("draw2d", "opengl");

   }

  
} // namespace app_app



