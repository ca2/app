#include "framework.h"
#define WITH_GPU
#define NO_IMAGING
#include "aura/application.h"
#include "aura/update.h"


namespace app_shader
{


   application::application() 
   {

      m_strAppId = "app/shader";

      m_strAppName = "app/shader";

      m_strBaseSupportId = "app/shader";

      m_bLicense = false;


   }


   application::~application()
   {

   }


   ::e_status application::init_instance()
   {

      set_local_data();

      create_factory <::app_shader::window >();

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

      __compose(m_pwindow, __create_new < window >());

      ::rectangle_i32 rectWindow;

      m_pwindow->_001InitialFramePosition(rectWindow, { 0.05, 0.05, 0.4, 0.4 });

      //auto pusersystem = __new(::user::system(0, nullptr, "app_app", WS_VISIBLE, rectWindow));

      //m_pwindow->create_window_ex(pusersystem);

      m_pwindow->create_host();

      m_pwindow->display(e_display_normal);

      m_pwindow->place(rectWindow);

      m_pwindow->set_need_layout();

      m_pwindow->set_need_redraw();

      m_pwindow->post_redraw();

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


   __namespace_application_factory("app/shader");


} // namespace app_shader



