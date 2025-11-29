#include "framework.h"


namespace helloworld
{


   application::application(::particle * pparticle) :
      ::object(this),
      ::thread(this),
      ::aura::application(pparticle),
      ::axis::application(pparticle),
      ::berg::application(pparticle),
      ::aura::application(pparticle),
      ::sphere::application(pparticle) :
      m_pmutexAiFont(this)
   {

      m_ptemplateHelloWorldMain = nullptr;
      m_ptemplateHelloWorldView = nullptr;
      m_ptemplateHelloWorldSwitcher = nullptr;

      m_strAppName = "app/helloworld";
      m_strLibraryName = "app/helloworld";
      m_strBaseSupportId = "ca2_flag";
      m_bLicense = false;

      m_etype = type_normal;

      m_strHelloWorldDefault = "Hello World!!";
      m_strAlternateHelloWorldDefault = "Hello!!";

      m_strHelloWorld = m_strHelloWorldDefault;
      m_strAlternateHelloWorld = m_strAlternateHelloWorldDefault;

      m_iErrorAiFont = -1;

      m_bLoadAiFont = false;

      m_faceAi = nullptr; // FT_Face m_faceAi;

      m_bWorldChat = true;



   }


   application::~application()
   {
   }


   void application::init_instance()
   {

      ::aura::session * pcoression = get_app()->m_psession;

      pcoression->use_font_sel();

      add_factory_item <::helloworld::document >();
      add_factory_item <::helloworld::frame >();
      add_factory_item <::helloworld::main_frame >();
      add_factory_item <::user::button_impact >();
      add_factory_item <::helloworld::impact >();
      add_factory_item <::helloworld::main_impact >();
      add_factory_item <::helloworld::switcher_impact >();
      add_factory_item <::helloworld::pane_impact >();

      if (!::aura::application::init_instance())
      {

         return false;

      }

      string str = m_varTopicQuery["helloworld"];

      if (str.has_character())
      {

         m_strHelloWorld = str;

      }

      set_local_data_key_modifier();

      ::user::single_document_template* pDocTemplate;


      pDocTemplate = __initialize_new ::user::single_document_template(
                             this,
                             "main",
                             typeid(document ),
                             typeid(main_frame ),
                             typeid(pane_impact )));
      m_ptemplateHelloWorldMain = pDocTemplate;
      add_document_template(pDocTemplate);


      pDocTemplate = __initialize_new ::user::single_document_template(
                             this,
                             "main",
                             typeid(document ),
                             typeid(frame ),
                             typeid(main_impact )));
      m_ptemplateHelloWorldView = pDocTemplate;
      add_document_template(pDocTemplate);


      pDocTemplate = __initialize_new ::user::single_document_template(
                             this,
                             "switcher",
                             typeid(document ),
                             typeid(frame ),
                             typeid(switcher_impact )));
      m_ptemplateHelloWorldSwitcher = pDocTemplate;
      add_document_template(pDocTemplate);


      return true;

   }


   int application::exit_application()
   {

      return ::aura::application::exit_application();

   }


   void application::on_request(::request * prequest)
   {

#if 0

#ifdef _DEBUG

      informationf("_DEBUG build? (basis)");

      ASSERT(false);

#else

      informationf("RELEASE build? (stage)");

      ASSERT(false);

#endif

#endif

      m_bWorldChat = !m_varTopicQuery["no_hello_edit"].is_set();

      if (m_ptemplateHelloWorldMain->get_document_count() == 0)
      {

         m_ptemplateHelloWorldMain->do_request(pcreate);

      }

      if (pcreate->m_payloadFile.has_character())
      {

         m_ptemplateHelloWorldView->do_request(pcreate);

      }

      if (m_varTopicQuery["wfi_maximize"].is_set())
      {

         pcreate->payload("document").cast < document >()->get_typed_impact < ::userex::pane_tab_impact >()->top_level_frame()->_001WindowMaximize();

      }

      informationf("----> finished helloworld::on_request");

   }


   string application::preferred_experience()
   {

      return "core";

   }


   long long application::increment_reference_count()
   {

      return ::object::increment_reference_count();

   }

   long long application::decrement_reference_count()
   {

      return ::object::decrement_reference_count();

   }


} // namespace helloworld




extern "C"
::acme::library * app_helloworld_get_new_library(::particle * pparticle)
{

   return ___new ::apex::single_application_library < ::helloworld::application >  (pparticle, "app/helloworld");

}




