#include "framework.h"
#define NO_IMAGING
#include "aura/application.h"
#include "aura/update.h"


namespace app_app
{


   application::application()
   {

      m_strAppId = "app/app";

      m_strAppName = "app/app";

      m_strBaseSupportId = "app_app";

      m_bLicense = false;

   }


   application::~application()
   {

   }


   ::e_status application::init_instance()
   {

      if (!::aura::application::init_instance())
      {

         return false;

      }

      return true;

   }


   void application::term_application()
   {

      ::aura::application::term_application();

   }


   void application::on_request(::create * pcreate)
   {

      //return;

      //sleep(0.5_s);

      __compose_new(m_pwindow);

      //::rect rectWindow;

      //bool bOk = m_pwindow->_001InitialFramePosition(rectWindow, );

      m_pwindow->create_main_window();


//      if (bOk)
  //    {

         m_pwindow->start_layout();

         m_pwindow->display(e_display_normal);

    //     m_pwindow->place(rectWindow);

         m_pwindow->set_need_layout();

         m_pwindow->set_need_redraw();

         m_pwindow->set_layout_ready();

         m_pwindow->post_redraw();

      //}



   }


#ifdef _DEBUG


   int64_t application::add_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::object::add_ref(OBJ_REF_DBG_ARGS);

   }


   int64_t application::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::object::dec_ref(OBJ_REF_DBG_ARGS);

   }


#endif


   __namespace_application_factory("app/app");


} // namespace app_app



