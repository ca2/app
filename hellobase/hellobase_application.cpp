#include "framework.h"


namespace hellobase
{


   application::application(::layered * pobjectContext) :
      ::object(this),
      ::thread(this),
      ::aura::application(pobject),
      ::axis::application(pobject),
      ::base::application(pobject),
      ::aura::application(pobject),
      ::sphere::application(pobject)
   {

      m_ptemplateHelloBaseMain = nullptr;

      m_strAppName = "app/hellobase";
      m_strLibraryName = "app/hellobase";
      m_strBaseSupportId = "ca2_flag";
      m_bLicense = false;

      m_etype = type_normal;

      m_strHelloBaseDefault = "Hello Base!!";
      m_strAlternateHelloBaseDefault = "Hi Base!!";


   }


   application::~application()
   {
   }


   ::estatus application::init_instance()
   {

      create_factory <::hellobase::document >();
      create_factory <::hellobase::main_frame >();
      create_factory <::user::button_view >();
      create_factory <::hellobase::view >();

      if (!::base::application::init_instance())
      {

         return false;

      }

      if (!::helloaxis::application::init_instance())
      {

         return false;

      }

      string str = m_varTopicQuery["hellobase"];

      if (str.has_char())
      {

         m_strHelloBase = str;

      }

      set_local_data_key_modifier();

      ::user::single_document_template* pDocTemplate;


      pDocTemplate = __new(::user::single_document_template(
                             this,
                             "main",
                             __type(document),
                             __type(main_frame),
                             __type(view)));
      m_ptemplateHelloBaseMain = pDocTemplate;


      return true;

   }


   i32 application::exit_application()
   {

      ::helloaxis::application::exit_application();

      return ::base::application::exit_application();

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

      if (m_ptemplateHelloBaseMain->get_document_count() == 0)
      {

         m_ptemplateHelloBaseMain->do_request(pcreate);

      }


      output_debug_string("\nfinished hellobase::on_request");

   }


   string application::preferred_experience()
   {

      return "aura";

   }


   string application::get_helloaura()
   {

      return "Hello Base!!";

   }


} // namespace hellobase




extern "C"
::apex::library * app_hellobase_get_new_library(::layered * pobjectContext)
{

   return new ::aura::single_application_library < ::hellobase::application > (pobject, "app/hellobase");

}




