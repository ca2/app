#include "framework.h"
#include "application.h"
#include "main_window.h"


__IMPLEMENT_APPLICATION_RELEASE_TIME(app_message_box);
IMPLEMENT_APPLICATION_FACTORY(app_message_box);


namespace app_message_box
{


   // __IMPLEMENT_APPLICATION_RELEASE_TIME1(app_message_box));


   application::application()
   {

      m_strAppId = "app/message_box";

      m_strAppName = "Message Box";

      m_strBaseSupportId = "app/message_box";

      m_bLicense = false;

      m_bImaging = false; // showing application icon may use innate_ui icon?

      m_bNetworking = false;

   }


   application::~application()
   {

   }


   void application::init_instance()
   {

      ::aura::application::init_instance();

   }


   void application::term_application()
   {

      ::aura::application::term_application();

   }


   void application::on_request(::request * prequest)
   {

      if (!m_pmainwindow)
      {

         __construct_new(m_pmainwindow);

         m_pmainwindow->display(e_display_normal);

         //m_pmainwindow->create_main_window_asynchronously();

         m_pmainwindow->create_main_window(prequest);

         //      m_pmainwindow->set_need_layout();
         //
         //      m_pmainwindow->set_need_redraw();
         //
         //      m_pmainwindow->post_redraw();

      }

   }


#ifdef _DEBUG


   long long application::increment_reference_count()
   {

      return ::object::increment_reference_count();

   }


   long long application::decrement_reference_count()
   {

      return ::object::decrement_reference_count();

   }


#endif

  
} // namespace app_message_box



