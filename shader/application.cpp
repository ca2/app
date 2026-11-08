#include "platform.h"
#include "application.h"
#include "main_window.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "bred/user/user/gpu_shader_render.h"


__IMPLEMENT_APPLICATION_RELEASE_TIME(app_shader);
IMPLEMENT_APPLICATION_FACTORY(app_shader);


namespace app_shader
{


   // __IMPLEMENT_APPLICATION_RELEASE_TIME1(app_shader));


   application::application() 
   {

      m_bGpu2 = true;

      m_strAppId = "app-graphics3d/shader";

      m_strAppName = "Shader";

      m_strBaseSupportId = "app-graphics3d/shader";

      m_bLicense = false;

      m_bImaging = false; // showing application icon may use innate_ui icon?

      m_bWriteText = false;

   }


   application::~application()
   {

   }


   void application::init_instance()
   {

      //set_local_data();

      //factory()->add_factory_item <::app_shader::main_window >();

      ::aura::application::init_instance();

      //if (!)
      //{

      //   return false;

      //}

      //return true;

   }


   void application::term_application()
   {

      ::aura::application::term_application();

   }


   void application::on_request(::request * prequest)
   {

      m_pmainwindow = create_newø < ::app_shader::main_window > ();

      m_pmainwindow->display(e_display_normal);

      m_pmainwindow->create_main_window(prequest);

//      m_pmainwindow->set_need_layout();
//
//      m_pmainwindow->set_need_redraw();
//
//      m_pmainwindow->post_redraw();

   }



#ifdef _DEBUG


   ::i64 application::increment_reference_count()
   {

      return ::object::increment_reference_count();

   }


   ::i64 application::decrement_reference_count()
   {

      return ::object::decrement_reference_count();

   }


#endif




} // namespace app_shader



