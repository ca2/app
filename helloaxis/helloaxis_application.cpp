#include "framework.h"


namespace helloaxis
{


   application::application(::object * pobject) :
      ::object(this),
      ::thread(this),
      ::aura::application(pobject),
      ::axis::application(pobject),
      ::base::application(pobject),
      ::aura::application(pobject),
      ::sphere::application(pobject)
   {

      m_strAppName = "app/helloaxis";
      m_strLibraryName = "app/helloaxis";
      m_strBaseSupportId = "ca2_flag";
      m_bLicense = false;

      //m_etype = type_normal;

      m_strHelloAxisDefault = "Hello Axis!!";
      m_strAlternateHelloAxisDefault = "Hi Axis!!";

      m_strHelloAxis = m_strHelloAxisDefault;
      m_strAlternateHelloAxis = m_strAlternateHelloAxisDefault;

      //m_iErrorAiFont = -1;

      //m_bLoadAiFont = false;

      //m_faceAi = nullptr; // FT_Face m_faceAi;

      //m_bAxisChat = true;



   }


   application::~application()
   {
   }


   ::estatus application::init_instance()
   {

      if (!::axis::application::init_instance())
      {

         return false;

      }

      if (!::helloaura::application::init_instance())
      {

         return false;

      }

      set_local_data_key_modifier();

      return true;

   }


   i32 application::exit_application()
   {

      ::helloaura::application::exit_application();

      return ::axis::application::exit_application();

   }


   void application::on_request(::create * pcreate)
   {

#if 0

#ifdef _DEBUG

      output_debug_string("_DEBUG build? (basis)");

      ASSERT(FALSE);

#else

      output_debug_string("RELEASE build? (stage)");

      ASSERT(FALSE);

#endif

#endif

//      m_bAxisChat = !m_varTopicQuery["no_hello_edit"].is_set();

      output_debug_string("\nfinished helloaxis::on_request");

      m_prender = new ::helloaxis::render(this);

      ::helloaura::main_window(m_prender);

      System.set_finish();

   }




   string application::get_helloaura()
   {

      return "Hello Axis!!";

   }

} // namespace helloaxis




extern "C"
::aura::library * app_helloaxis_get_new_library(::object * pobject)
{

   return new ::aura::single_application_library < ::helloaxis::application > (pobject, "app/helloaxis");

}




