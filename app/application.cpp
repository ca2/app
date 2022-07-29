#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_library.h"
#endif
#include "aura/update.h"


namespace app_app
{


   application::application()
   {
      
      m_strAppId = "app/app";

      m_strAppName = "app/app";

      m_strBaseSupportId = "app_app";

      m_bLicense = false;

      m_bImaging = false;

      m_bWriteText = false;

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

  
} // namespace app_app



