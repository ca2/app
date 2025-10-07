#include "framework.h"
#include "application.h"
#include "main_window.h"
#include "acme/platform/system.h"


__IMPLEMENT_APPLICATION_RELEASE_TIME(app_app);
IMPLEMENT_APPLICATION_FACTORY(app_app);


namespace app_app
{


   // __IMPLEMENT_APPLICATION_RELEASE_TIME1(app_app));


   application::application()
   {
      
      m_strAppId = "app/app";

      m_strAppName = "app/app";

      m_strBaseSupportId = "app_app";

      m_bNetworking = false;

      m_bLicense = false;

      m_bImaging = false; // showing application icon may use innate_ui icon?

      m_bWriteText = false;

      m_bInterprocessCommunication = false;

   }


   application::~application()
   {

   }


   void application::on_request(::request * prequest)
   {

      if (!m_pmainwindow)
      {

         m_pmainwindow = øcreate_new<::app_app::main_window>();

         m_pmainwindow->create_main_window(prequest);

         m_pmainwindow->display(e_display_normal);

      }

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

      //pmainwindow->create_main_window(prequest);

      //pmainwindow->m_pthreadUserInteraction->m_procedurea.add([this]() {});

      //pmainwindow->m_pthreadUserInteraction->run_posted_procedures();

   }


   string application::draw2d_get_default_implementation_name()
   {

      //return system()->implementation_name("draw2d", "opengl");
      //return system()->implementation_name("draw2d", "gdiplus");
      return ::aura::application::draw2d_get_default_implementation_name();

   }

  
} // namespace app_app



