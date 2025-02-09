#include "framework.h"


namespace app_net
{


   __IMPLEMENT_APPLICATION_RELEASE_TIME();


   application::application()
   {

      m_strAppId = "app/app";

      m_strAppName = "app/app";

      m_strBaseSupportId = "app_app";

      m_bLicense = false;

      m_bImaging = false;

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

      __construct_new(m_pwindow);

      m_pwindow->create_main_window();

      //m_pwindow->start_layout();

      m_pwindow->display(e_display_normal);

      m_pwindow->set_need_layout();

      m_pwindow->set_need_redraw();

      //m_pwindow->set_layout_ready();

      m_pwindow->post_redraw();

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




} // namespace app_net



