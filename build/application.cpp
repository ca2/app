#include "framework.h"


#define TEST_DATA_LOCAL 1

void hellomultiverse_debugging();

namespace app_core_build
{

   application::application()
   {

      m_bInterprocessIntercommunication = true;

      m_ptemplateHelloMultiverseMain = nullptr;
      m_ptemplateHelloMultiverseView = nullptr;

      m_strAppId = "app-core/build";
      m_strAppName = "app-core/build";
      m_strBaseSupportId = "app-core/build";
      m_bLicense = false;

      m_etype = type_normal;

      m_strHelloMultiverseDefault = "Hello Multiverse!!";
      m_strAlternateHelloMultiverseDefault = "Hello!!";

      m_strHelloMultiverse = m_strHelloMultiverseDefault;
      m_strAlternateHelloMultiverse = m_strAlternateHelloMultiverseDefault;

      m_bMultiverseChat = true;

   }


   application::~application()
   {

   }


   void application::init_instance()
   {


#if defined(LINUX)

      ::factory::get_factory()->add_factory_item < linux_build, build >();

#else

      #error "not implemented"

#endif

      if (is_true("hellomultiverse_debugging"))
      {

         hellomultiverse_debugging();

      }

      set_local_data();

      auto psession = get_session();

      auto puser = psession->user()->m_pcoreuser;

      puser->will_use_impact_hint(FONTSEL_IMPACT);

      ::factory::add_factory_item <::app_core_build::document >();
      ::factory::add_factory_item <::app_core_build::frame >();
      ::factory::add_factory_item <::app_core_build::main_frame >();
      ::factory::add_factory_item <::user::button_impact >();
      ::factory::add_factory_item <::app_core_build::impact >();
      ::factory::add_factory_item <::app_core_build::main_impact >();
      ::factory::add_factory_item <::app_core_build::pane_impact >();

      if (!::core::application::init_instance())
      {

         return false;

      }

      string str = payload("hellomultiverse");

      if (str.has_char())
      {

         m_strHelloMultiverse = str;

      }

      auto ptemplate = __new(::user::single_document_template(
                            "main",
                            __type(simple_pane_document),
                            __type(main_frame),
                            __type(pane_impact)));

      m_ptemplateHelloMultiverseMain = ptemplate;

      add_document_template(ptemplate);

      ptemplate = __new(::user::single_document_template(
                       "main",
                       __type(document),
                       __type(frame),
                       __type(main_impact)));

      m_ptemplateHelloMultiverseView = ptemplate;

      add_document_template(ptemplate);

      return true;

   }


   void application::term_application()
   {

      ::core::application::term_application();

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

      m_bMultiverseChat = !is_true("no_hello_edit");

      if (m_ptemplateHelloMultiverseMain->get_document_count() == 0)
      {

         if (pcreate->m_payloadFile.is_empty())
         {

            ::file::path path;

            data_get("last_opened_file", path);

            if (!file().exists(path))
            {

               path = dir().document2() / "default.hellomultiverse";

            }

            pcreate->m_payloadFile = path;

            pcreate->m_ecommand = ::command_line::command_file_open;

         }

         m_ptemplateHelloMultiverseMain->do_request(pcreate);

         return;

      }

      if (pcreate->has_file())
      {

         m_ptemplateHelloMultiverseView->do_request(pcreate);

      }

      output_debug_string("\nfinished hellomultiverse::on_request");

   }


   void application::set_finish()
   {

      return ::thread::set_finish();

   }


   string application::preferred_experience()
   {

      string strExperience = payload("experience");

      if (strExperience.has_char())
      {

         return strExperience;

      }

      return "core";

   }


   //i64 application::increment_reference_count()
   //{

   //   return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   //}

   //i64 application::decrement_reference_count()
   //{

   //   return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   //}


} // namespace app_core_build



void hellomultiverse_debugging()
{

   const char * pszFree;

   {

      string strOh = "Oh!! Life!!";

      pszFree = strOh;

      string strXX;

      strXX = strOh + "123" + __string(15.59) + "%";

      output_debug_string(strXX);

   }

   output_debug_string(pszFree);

}




