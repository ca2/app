#include "framework.h"

#include "application.h"
#include "main_window.h"


IMPLEMENT_APPLICATION(app_message_box);


namespace app_message_box
{


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

      //if (!::aura::application::init_instance())
      //{

      //   return false;

      //}

      //return true;

   }


   void application::term_application()
   {

      ::aura::application::term_application();

   }


   void application::on_request(::create * pcreate)
   {

      __compose_new(m_pmainwindow);

      m_pmainwindow->display(e_display_restored);

      m_pmainwindow->create_main_window();

      m_pmainwindow->set_need_layout();

      m_pmainwindow->set_need_redraw();

      m_pmainwindow->post_redraw();

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

  
} // namespace app_message_box



