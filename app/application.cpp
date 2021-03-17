#include "framework.h"
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

      __compose_new(m_pmainwindow);

      //rectangle_i32 rectWindow;

      //bool bOk = m_pmainwindow->_001InitialFramePosition(rectWindow, );
      m_pmainwindow->display(e_display_normal);

      m_pmainwindow->create_main_window();


//      if (bOk)
  //    {

         m_pmainwindow->start_layout();


    //     m_pmainwindow->place(rectWindow);

         m_pmainwindow->set_need_layout();

         m_pmainwindow->set_need_redraw();

         m_pmainwindow->set_layout_ready();

         m_pmainwindow->post_redraw();

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

  
} // namespace app_app



