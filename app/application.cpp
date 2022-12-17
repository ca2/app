#include "framework.h"
#include "application.h"
#include "main_window.h"


//IMPLEMENT_APPLICATION(app_app);


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

      auto pmainwindow = __create_new < ::app_app::main_window >();

      pmainwindow->display(e_display_restored);

      pmainwindow->create_main_window();

      pmainwindow->set_need_layout();

      pmainwindow->set_need_redraw();

      pmainwindow->post_redraw();

   }


#ifdef _DEBUG


   int64_t application::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   int64_t application::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif

  
} // namespace app_app



