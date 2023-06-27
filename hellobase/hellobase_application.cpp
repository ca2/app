#include "framework.h"


namespace hellobase
{


   application::application(::particle * pparticle) :
      ::object(this),
      ::thread(this),
      ::aura::application(pparticle),
      ::axis::application(pparticle),
      ::base::application(pparticle),
      ::aura::application(pparticle),
      ::sphere::application(pparticle)
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


   void application::init_instance()
   {

      add_factory_item <::hellobase::document >();
      add_factory_item <::hellobase::main_frame >();
      add_factory_item <::user::button_impact >();
      add_factory_item <::hellobase::impact >();

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
                             __type(impact)));
      m_ptemplateHelloBaseMain = pDocTemplate;


      return true;

   }


   i32 application::exit_application()
   {

      ::helloaxis::application::exit_application();

      return ::base::application::exit_application();

   }


   void application::on_request(::request * prequest)
   {

#if 0

#ifdef _DEBUG

      information("_DEBUG build? (basis)");

      ASSERT(false);

#else

      information("RELEASE build? (stage)");

      ASSERT(false);

#endif

#endif

      if (m_ptemplateHelloBaseMain->get_document_count() == 0)
      {

         m_ptemplateHelloBaseMain->do_request(pcreate);

      }


      information("\nfinished hellobase::on_request");

   }


   string application::preferred_experience()
   {

      return "core";

   }


   string application::get_helloaura()
   {

      return "Hello Base!!";

   }


} // namespace hellobase




extern "C"
::acme::library * app_hellobase_get_new_library(::particle * pparticle)
{

   return memory_new ::apex::single_application_library < ::hellobase::application > (pparticle, "app/hellobase");

}




