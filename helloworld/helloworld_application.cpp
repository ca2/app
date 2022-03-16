#include "framework.h"


namespace helloworld
{


   application::application(::object * pobject) :
      ::object(this),
      ::thread(this),
      ::aura::application(pobject),
      ::axis::application(pobject),
      ::base::application(pobject),
      ::aura::application(pobject),
      ::sphere::application(pobject) :
      m_mutexAiFont(this)
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
      add_factory_item <::user::button_view >();
      add_factory_item <::helloworld::impact >();
      add_factory_item <::helloworld::main_impact >();
      add_factory_item <::helloworld::switcher_view >();
      add_factory_item <::helloworld::pane_impact >();

      if (!::aura::application::init_instance())
      {

         return false;

      }

      string str = m_varTopicQuery["helloworld"];

      if (str.has_char())
      {

         m_strHelloWorld = str;

      }

      set_local_data_key_modifier();

      ::user::single_document_template* pDocTemplate;


      pDocTemplate = __new(::user::single_document_template(
                             this,
                             "main",
                             __type(document),
                             __type(main_frame),
                             __type(pane_impact)));
      m_ptemplateHelloWorldMain = pDocTemplate;
      add_document_template(pDocTemplate);


      pDocTemplate = __new(::user::single_document_template(
                             this,
                             "main",
                             __type(document),
                             __type(frame),
                             __type(main_impact)));
      m_ptemplateHelloWorldView = pDocTemplate;
      add_document_template(pDocTemplate);


      pDocTemplate = __new(::user::single_document_template(
                             this,
                             "switcher",
                             __type(document),
                             __type(frame),
                             __type(switcher_view)));
      m_ptemplateHelloWorldSwitcher = pDocTemplate;
      add_document_template(pDocTemplate);


      return true;

   }


   i32 application::exit_application()
   {

      return ::aura::application::exit_application();

   }


   void application::on_request(::create * pcreate)
   {

#if 0

#ifdef _DEBUG

      output_debug_string("_DEBUG build? (basis)");

      ASSERT(false);

#else

      output_debug_string("RELEASE build? (stage)");

      ASSERT(false);

#endif

#endif

      m_bWorldChat = !m_varTopicQuery["no_hello_edit"].is_set();

      if (m_ptemplateHelloWorldMain->get_document_count() == 0)
      {

         m_ptemplateHelloWorldMain->do_request(pcreate);

      }

      if (pcreate->m_pcommandline->m_payloadFile.has_char())
      {

         m_ptemplateHelloWorldView->do_request(pcreate);

      }

      if (m_varTopicQuery["wfi_maximize"].is_set())
      {

         pcreate->m_pcommandline->payload("document").cast < document >()->get_type_impact < ::userex::pane_tab_impact >()->top_level_frame()->_001WindowMaximize();

      }

      output_debug_string("\nfinished helloworld::on_request");

   }


   string application::preferred_experience()
   {

      return "core";

   }


   i64 application::increment_reference_count()
   {

      return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }

   i64 application::decrement_reference_count()
   {

      return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


} // namespace helloworld




extern "C"
::acme::library * app_helloworld_get_new_library(::object * pobject)
{

   return new ::apex::single_application_library < ::helloworld::application > (pobject, "app/helloworld");

}




