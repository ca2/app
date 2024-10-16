#include "framework.h"
#include "application.h"
#include "document.h"
#include "frame.h"
#include "impact.h"
#include "main_frame.h"
#include "main_impact.h"
#include "pane_impact.h"
#include "acme/handler/request.h"
#include "apex/database/stream.h"
#include "acme/filesystem/filesystem/dir_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aura/platform/session.h"
#include "base/user/user/single_document_template.h"
#include "core/user/simple/pane_document.h"
#include "core/user/user/user.h"
#ifdef WINDOWS_DESKTOP
#include "build_windows.h"
#endif

#define TEST_DATA_LOCAL 1

void hellomultiverse_debugging();

namespace app_build
{

   __IMPLEMENT_APPLICATION_RELEASE_TIME();


   application::application()
   {

      m_bInterprocessCommunication = true;

      m_ptemplateHelloMultiverseMain = nullptr;
      m_ptemplateHelloMultiverseImpact = nullptr;

      m_strAppId = "app/build";
      m_strAppName = "app/build";
      m_strBaseSupportId = "app/build";
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

      factory()->add_factory_item < linux_build, build >();

#elif defined(WINDOWS_DESKTOP)

      factory()->add_factory_item < ::windows::build, build >();

#endif

      if (is_true("hellomultiverse_debugging"))
      {

         hellomultiverse_debugging();

      }

      //set_local_data();

      auto psession = session()->m_paurasession;

      auto puser = psession->user()->m_pcoreuser;

      puser->will_use_impact_hint(FONTSEL_IMPACT);

      factory()->add_factory_item <::app_build::document >();
      factory()->add_factory_item <::app_build::frame >();
      factory()->add_factory_item <::app_build::main_frame >();
      factory()->add_factory_item <::user::button_impact >();
      factory()->add_factory_item <::app_build::impact >();
      factory()->add_factory_item <::app_build::main_impact >();
      factory()->add_factory_item <::app_build::pane_impact >();

      ::core::application::init_instance();

      string str = payload("hellomultiverse");

      if (str.has_char())
      {

         m_strHelloMultiverse = str;

      }

      auto ptemplate = __initialize_new ::user::single_document_template(
                            "main",
                            ::type < simple_pane_document >(),
                            ::type < main_frame >(),
                            ::type < pane_impact >()));

      m_ptemplateHelloMultiverseMain = ptemplate;

      add_document_template(ptemplate);

      ptemplate = __initialize_new ::user::single_document_template(
                       "main",
                       ::type < document >(),
                       ::type < frame >(),
                       ::type < main_impact >()));

      m_ptemplateHelloMultiverseImpact = ptemplate;

      add_document_template(ptemplate);

      //return true;

   }


   void application::term_application()
   {

      ::core::application::term_application();

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

      m_bMultiverseChat = !is_true("no_hello_edit");

      if (m_ptemplateHelloMultiverseMain->get_document_count() == 0)
      {

         if (prequest->m_payloadFile.is_empty())
         {

            ::file::path path;

            datastream()->get("last_opened_file", path);

            if (!file()->exists(path))
            {

               path = dir()->document2() / "default.hellomultiverse";

            }

            prequest->m_payloadFile = path;

            prequest->m_ecommand = ::e_command_file_open;

         }

         m_ptemplateHelloMultiverseMain->request(prequest);

         return;

      }

      if (prequest->has_file())
      {

         m_ptemplateHelloMultiverseImpact->request(prequest);

      }

      informationf("\nfinished hellomultiverse::on_request");

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

   //   return ::object::increment_reference_count();

   //}

   //i64 application::decrement_reference_count()
   //{

   //   return ::object::decrement_reference_count();

   //}


} // namespace app_build



void hellomultiverse_debugging()
{

   const char * pszFree;

   {

      string strOh = "Oh!! Life!!";

      pszFree = strOh;

      string strXX;

      strXX = strOh + "123" + as_string(15.59) + "%";

      information(strXX);

   }

   information(pszFree);

}




