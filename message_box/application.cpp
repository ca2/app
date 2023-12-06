#include "framework.h"
#include "application.h"
#include "main_window.h"


__DECLARE_RELEASE_TIME(app_message_box);


namespace app_message_box
{


   __IMPLEMENT_APPLICATION_RELEASE_TIME(app_message_box);


   application::application()
   {

      m_strAppId = "app/message_box";

      m_strAppName = "Message Box";

      m_strBaseSupportId = "app/message_box";

      m_bLicense = false;

      m_bImaging = false;

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


#ifdef _DEBUG


   int64_t application::increment_reference_count()
   {

      return ::object::increment_reference_count();

   }


   int64_t application::decrement_reference_count()
   {

      return ::object::decrement_reference_count();

   }


#endif

  
} // namespace app_message_box



