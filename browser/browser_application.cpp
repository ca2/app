#include "framework.h"


namespace browser
{


   application::application(::object * pobject) :
      ::object(this),
      ::thread(this),
      ::aura::application(pobject),
      ::axis::application(pobject),
      ::base::application(pobject),
      ::aura::application(pobject)
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


   ::e_status application::init_instance()
   {


      {

         // SimpleApp implements application-level callbacks for the browser process.
// It will create the first browser instance in OnContextInitialized() after
// CEF has initialized.
         CefMainArgs mainargs(psystem->m_hinstance);

         CefSettings settings;
         settings.multi_threaded_message_loop = true;
         get_application() = new SimpleApp();

         WCHAR szTempPath[MAX_PATH] = L"";
         GetTempPathW(_countof(szTempPath), szTempPath);

         // get an unique item name in temp dir
         WCHAR szRelative[MAX_PATH] = L"";
         GetTempFileNameW(szTempPath, L"CCD", 0, szRelative);

         ::DeleteFileW(szRelative);

                  auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;

pacmedir->create(szRelative);  // or SHCreateDirectory(NULL, szCacheDir); - needs include shlobj.h

         CefString(&settings.cache_path) = szRelative;

         CefInitialize(mainargs, settings, get_application(), nullptr);

      }



      set_local_data();

      ::aura::session * pcoression = &Session;

      pcoression->will_use_view_hint(FONTSEL_IMPACT);

      create_factory <::browser::document >();
      create_factory <::browser::frame >();
      create_factory <::browser::main_frame >();
      create_factory <::user::button_view >();
      create_factory <::browser::impact >();
      create_factory <::browser::main_impact >();
      create_factory <::browser::switcher_view >();
      create_factory <::browser::pane_view >();
      create_factory <::browser::gcom >();
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
      pDocTemplate = __new(::user::single_document_template(
                          this,
                          "main",
                          __type(document),
                          __type(main_frame),
                          __type(pane_view)));
      m_ptemplateHelloBrowserMain = pDocTemplate;
      add_document_template(pDocTemplate);


      pDocTemplate = __new(::user::single_document_template(
                          this,
                          "main",
                          __type(document),
                          __type(frame),
                          __type(main_impact)));
      m_ptemplateHelloBrowserView = pDocTemplate;
      add_document_template(pDocTemplate);


      pDocTemplate = __new(::user::single_document_template(
                          this,
                          "switcher",
                          __type(document),
                          __type(frame),
                          __type(switcher_view)));
      m_ptemplateHelloBrowserSwitcher = pDocTemplate;
      add_document_template(pDocTemplate);


      return true;

   }


   void application::term_application()
   {

      ::aura::application::term_application();

      CefShutdown();

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

      m_bBrowserChat = !m_varTopicQuery["no_hello_edit"].is_set();

      if (m_ptemplateHelloBrowserMain->get_document_count() == 0)
      {

         m_ptemplateHelloBrowserMain->do_request(pcreate);

      }

      if (pcreate->m_pcommandline->m_varFile.has_char())
      {

         m_ptemplateHelloBrowserView->do_request(pcreate);

      }

      output_debug_string("\nfinished browser::on_request");

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


} // namespace browser


extern "C"
::acme::library * app_browser_get_new_library(::object * pobject)
{

   return new ::apex::single_application_library < ::browser::application > (pobject, "app/browser");

}


::aura::application * get_acid_app(::object * pobject)
{

   return new ::browser::application(pobject);

}


aura_app aura_app_browser("app/browser", &app_browser_get_new_library);



