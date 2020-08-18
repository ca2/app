#include "framework.h"
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


   ::estatus application::init_instance()
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

      __refer(m_pwindow, __create_new < window >());

      ::rect rectWindow;

      m_pwindow->_001InitialFramePosition(rectWindow, {0.05, 0.05, 0.4, 0.4});

      ::user::create_struct cs(0, nullptr, "app_app", WS_VISIBLE, rectWindow);

      m_pwindow->create_window_ex(cs);

      m_pwindow->display(display_normal);

      m_pwindow->place(rectWindow);

      m_pwindow->set_need_layout();

      m_pwindow->set_need_redraw();

      m_pwindow->post_redraw();

   }


   int64_t application::add_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::object::add_ref(OBJ_REF_DBG_ARGS);

   }


   int64_t application::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return ::object::dec_ref(OBJ_REF_DBG_ARGS);

   }


   __namespace_application_factory("app/app");


} // namespace app_app







//
//extern "C"
//::aura::library * app_simple_drawing_get_new_library()
//{
//
//   return new ::aura::single_application_library < ::app_app::application >("app-simple/drawing");
//
//}
//
//
//aura_app aura_app_simple_drawing("app-simple/drawing", &app_simple_drawing_get_new_library);
//
//
//app_app::application application;


