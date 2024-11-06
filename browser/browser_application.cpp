#include "framework.h"


namespace browser
{


   application::application(::particle * pparticle) :
      ::object(this),
      ::thread(this),
      ::aura::application(pparticle),
      ::axis::application(pparticle),
      ::base::application(pparticle),
      ::aura::application(pparticle)
   {

      m_ptemplateHelloBrowserMain = nullptr;
      m_ptemplateHelloBrowserView = nullptr;
      m_ptemplateHelloBrowserSwitcher = nullptr;

      m_strAppId = "app/browser";
      m_strAppName = "app/browser";
      m_strBaseSupportId = "ca2_flag";
      m_bLicense = false;

      m_etype = type_normal;

      m_strHelloBrowserDefault = "Hello Browser!!";
      m_strAlternateHelloBrowserDefault = "Hello!!";

      m_strHelloBrowser = m_strHelloBrowserDefault;
      m_strAlternateHelloBrowser = m_strAlternateHelloBrowserDefault;

      m_bBrowserChat = true;

   }


   application::~application()
   {
   }


   void application::init_instance()
   {


      {

         // SimpleApp implements application-level callbacks for the browser process.
// It will create the first browser instance in OnContextInitialized() after
// CEF has initialized.
         CefMainArgs mainargs(psystem->m_hinstance);

         CefSettings settings;
         settings.multi_threaded_message_loop = true;
         get_app() = ___new SimpleApp();

         WCHAR szTempPath[MAX_PATH] = L"";
         GetTempPathW(_countof(szTempPath), szTempPath);

         // get an unique item name in temp dir
         WCHAR szRelative[MAX_PATH] = L"";
         GetTempFileNameW(szTempPath, L"CCD", 0, szRelative);

         ::DeleteFileW(szRelative);

                  auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->create(szRelative);  // or SHCreateDirectory(NULL, szCacheDir); - needs include shlobj.h

         CefString(&settings.cache_path) = szRelative;

         CefInitialize(mainargs, settings, get_app(), nullptr);

      }



      set_local_data();

      ::aura::session * pcoression = &Session;

      pcoression->will_use_impact_hint(FONTSEL_IMPACT);

      add_factory_item <::browser::document >();
      add_factory_item <::browser::frame >();
      add_factory_item <::browser::main_frame >();
      add_factory_item <::user::button_impact >();
      add_factory_item <::browser::impact >();
      add_factory_item <::browser::main_impact >();
      add_factory_item <::browser::switcher_impact >();
      add_factory_item <::browser::pane_impact >();
      add_factory_item <::browser::gcom >();
      add_matter_locator("app-core/hellomultiverse");


      if (!::aura::application::init_instance())
      {

         return false;

      }

      string str = m_varTopicQuery["browser"];

      if (str.has_char())
      {

         m_strHelloBrowser = str;

      }




      auto
      pDocTemplate = __initialize_new ::user::single_document_template(
                          this,
                          "main",
                          ::type < document >(),
                          ::type < main_frame >(),
                          ::type < pane_impact >()));
      m_ptemplateHelloBrowserMain = pDocTemplate;
      add_document_template(pDocTemplate);


      pDocTemplate = __initialize_new ::user::single_document_template(
                          this,
                          "main",
                          ::type < document >(),
                          ::type < frame >(),
                          ::type < main_impact >()));
      m_ptemplateHelloBrowserView = pDocTemplate;
      add_document_template(pDocTemplate);


      pDocTemplate = __initialize_new ::user::single_document_template(
                          this,
                          "switcher",
                          ::type < document >(),
                          ::type < frame >(),
                          ::type < switcher_impact >()));
      m_ptemplateHelloBrowserSwitcher = pDocTemplate;
      add_document_template(pDocTemplate);


      return true;

   }


   void application::term_application()
   {

      ::aura::application::term_application();

      CefShutdown();

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

      m_bBrowserChat = !m_varTopicQuery["no_hello_edit"].is_set();

      if (m_ptemplateHelloBrowserMain->get_document_count() == 0)
      {

         m_ptemplateHelloBrowserMain->do_request(pcreate);

      }

      if (pcreate->m_payloadFile.has_char())
      {

         m_ptemplateHelloBrowserView->do_request(pcreate);

      }

      informationf("\nfinished browser::on_request");

   }


   string application::preferred_experience()
   {

      return "core";

   }


   i64 application::increment_reference_count()
   {

      return ::object::increment_reference_count();

   }

   i64 application::decrement_reference_count()
   {

      return ::object::decrement_reference_count();

   }


} // namespace browser


extern "C"
::acme::library * app_browser_get_new_library(::particle * pparticle)
{

   return ___new ::apex::single_application_library < ::browser::application >  (pparticle, "app/browser");

}


::aura::application * get_acid_app(::particle * pparticle)
{

   return ___new ::browser::application (pparticle);

}


aura_app aura_app_browser("app/browser", &app_browser_get_new_library);



