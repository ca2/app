//
// Created by camilo on 22/02/2022.
//
// app to application and back to acme namespace by camilo on 2022-09-17 18:54 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "application.h"
#include "acme.h"
#include "acme/exception/exit.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/platform/session.h"
#include "acme/primitive/string/_str.h"
#include "acme/primitive/text/context.h"


#ifdef WINDOWS_DESKTOP


#include "acme/_operating_system.h"


CLASS_DECL_ACME::file::path get_module_path(HMODULE hmodule);


#else


CLASS_DECL_ACME::file::path get_module_path();


#endif


namespace acme
{


   application::application()
   {

      m_acme.m_pacmeapplication = this;

      m_pacmeapplication = this;
      m_papexapplication = nullptr;
      m_paquaapplication = nullptr;
      m_pauraapplication = nullptr;
      m_paxisapplication = nullptr;
      m_pbaseapplication = nullptr;
      m_pbredapplication = nullptr;
      m_pcoreapplication = nullptr;

      factory()->add_factory_item < ::acme::system >();
      factory()->add_factory_item < ::acme::session >();

   }


   application::~application()
   {

      /*   if (g_p == this)
         {

            m_pmain->m_psubsystem.release();

            ::acme::del(m_pmain);

            g_p = nullptr;



         }*/
         //   ::acme::finalize_system();

   }


   void application::initialize(::particle* pparticle)
   {

      ::task::initialize(pparticle);

      {

#include "deployment/build.h"

         m_strBuild = pszBuild;

      }

      if (m_strBuild.is_empty())
      {

         m_strBuild = "(unknown build version)";

      }

#ifdef WINDOWS

      m_strCommandLine = ::GetCommandLineW();

#endif

   }


   void application::start_application(::request* prequest)
   {


      //bool application::start_application(::request * prequest)
      //{

      branch();

      if (::is_set(prequest))
      {

         post_request(prequest);

      }

      //return true;

   //   ;;;
   //}

   }


   //void application::on_initialize_application()
   //{

   //}

   ::factory::factory_pointer& application::factory()
   {

      return ::acme::acme::g_pacme->m_psubsystem->factory();

   }


   void application::implement_application()
   {

      output_debug_string("acme::application implement_application\n");

      set_main_user_thread();

      task_guard taskguard;

      ::e_status estatus = error_failed;

      ::e_status estatusEnd = error_failed;

      string strAppId;

      if (!m_bConsole)
      {

         strAppId = m_strAppId;

      }

      {

         string strPrgName = m_strAppId;

         strPrgName.replace_with(".", "/");

         strPrgName.replace_with("-", "_");

         m_strProgName = "com." + strPrgName;

      }

      //main.m_bAudio = main_hold_base::is_audio_enabled();

      auto pfactoryitem = ::acme::acme::g_pacme->m_psubsystem->m_pfactory->get_factory_item<::acme::system>();

      ::pointer<::acme::system> psystem = pfactoryitem->create_particle();

      ::set_task(psystem);

      psystem->initialize_system();

      information() << "acme implement_application system_construct";

      psystem->system_construct(this);

      information() << "acme implement_application create_os_node";

      psystem->create_os_node();

      auto pnode = psystem->node();

      pnode->implement(pnode, psystem);

      //pnode->start_application(pnode, psystem);

//         if (m_iExitCode == 0 && m_iExitCode != 0)
//         {
//
//            m_iExitCode = m_iExitCode;
//
//         //}
//
//         }

         //auto psystem = platform_create_system(strAppId);

         /*estatus =*/

         //if (!estatus)
         //{

         //   return estatus;

         //}

         /*estatus = */ //psystem->__task_init();

         //if (!estatus)
         //{

         //   return estatus;

         //}


         //return estatus;

      //}


   }


   void application::initialize_application_flags()
   {

      if (m_bVerbose.undefined())
      {

         m_bVerbose = true;

      }

      if (m_bConsole.undefined())
      {

         m_bConsole = false;

      }

      if (m_bDraw2d.undefined())
      {

         m_bDraw2d = !m_bConsole;

      }

      if (m_bWriteText.undefined())
      {

         m_bWriteText = m_bDraw2d;

      }

      if (m_bUser.undefined())
      {

         m_bUser = !m_bConsole;

      }

      if (m_bUserEx.undefined())
      {

         m_bUserEx = !m_bConsole;

      }

      if (m_bImaging.undefined())
      {

         m_bImaging = !m_bConsole;

      }

      if (m_bCrypto.undefined())
      {

         m_bCrypto = !m_bConsole;

      }

      if (m_bResource.undefined())
      {

         //m_bResource = !m_bConsole;

         m_bResource = true;

      }

#ifdef WINDOWS_DESKTOP

      if (m_bGdiplus.undefined())
      {

         m_bGdiplus = !m_bConsole;

      }

#endif

#if defined(LINUX)

      if (m_bGtkApp.undefined())
      {

         m_bGtkApp = !m_bConsole;

      }

#endif

      if (m_bShowApplicationInformation.undefined())
      {

         m_bShowApplicationInformation = false;

      }

      if (m_bConsole)
      {

         if (m_bSession.undefined())
         {

            m_bSession = false;

         }

      }
      else // !m_bConsole
      {

         if (m_bSession.undefined())
         {

            m_bSession = true;

         }

      }

      //string strAppId = acmeapplication()->m_strAppId;

   }



   bool application::is_application() const
   {

      return true;

   }


   bool application::is_system() const
   {

      return false;

   }


   bool application::is_session() const
   {

      return true;

   }


   bool application::is_service() const
   {

      return false;

   }


   bool application::is_user_service() const
   {

      return false;

   }


   bool application::can_exit_application()
   {

      return true;

   }


   ::file::path application::get_module_path()
   {

      synchronous_lock synchronizationlock(synchronization());

      if (!m_bModulePath)
      {

#ifdef WINDOWS_DESKTOP

         m_pathModule = ::get_module_path((HMODULE)::acme::acme::g_pacme->m_psubsystem->m_hinstanceThis);

#elif defined(ANDROID)

         m_pathModule.empty();

#else

         //throw ::exception(todo);
         //m_pathModule = acmefile()->module();
         m_pathModule = ::get_module_path();

#endif

         m_bModulePath = true;

      }

      return m_pathModule;

   }


   ::file::path application::get_module_folder()
   {

      synchronous_lock synchronizationlock(synchronization());

      if (!m_bModuleFolder)
      {

         m_pathModuleFolder = get_module_path().folder();

         m_bModuleFolder = true;

      }

      return m_pathModuleFolder;

   }


   ::string application::app_name()
   {

      ::string strAppName;

      if (m_strAppName.has_char())
      {

         strAppName = m_strAppName;

      }
      else
      {

         string strAppIdUnderscore = m_strAppId;

         strAppIdUnderscore.find_replace("/", "_");

         strAppIdUnderscore.find_replace("-", "_");

         strAppName = strAppIdUnderscore;

      }

      return strAppName;

   }


   //::string node::app_name()
   //{




   //}


   ::string application::app_root()
   {

      auto iFind = m_strAppId.find_index('/');

      if (iFind < 0)
      {

         return{};

      }

      return m_strAppId.left(iFind);

   }


   ::string application::application_title()
   {

      auto textAppTitle = m_textAppTitle;

      string strAppTitle;

      if (textAppTitle.get_text().has_char())
      {

         strAppTitle = textAppTitle.get_text();

      }
      else
      {

         string_array stra;

         stra.explode("/", m_strAppId);

         strAppTitle = stra.slice(1).implode(" ");

         strAppTitle.replace_with(" ", "_");

         strAppTitle.replace_with(" ", "-");

         strAppTitle.replace_with(" ", ".");

      }

      return strAppTitle;

   }



   ::string application::application_name()
   {

      auto textAppName = m_textAppName;

      string strAppName;

      if (textAppName.get_text().has_char())
      {

         strAppName = textAppName.get_text();

      }
      else
      {

         string_array stra;

         stra.explode("/", m_strAppId);

         strAppName = stra.slice(1).implode(" ");

         strAppName.replace_with(" ", "_");

         strAppName.replace_with(" ", "-");

         strAppName.replace_with(" ", ".");

      }

      return strAppName;

   }


   //#ifdef WINDOWS
   //
   //
   //   void application::get_arguments_from_command_line()
   //   {
   //
   //      m_argc = __argc;
   //
   //      m_argv = __argv;
   //
   //      m_envp = *__p__environ();
   //
   //      m_wargv = __wargv;
   //
   //      m_wenvp = *__p__wenviron();
   //
   //      m_strCommandLine = ::GetCommandLineW();
   //
   //   }
   //
   //
   //#else
   //
   //
   //   void application::set_args(int argc, char * argv[], char * envp[])
   //   {
   //
   //      m_argc = argc;
   //
   //      m_argv = argv;
   //
   //      m_envp = envp;
   //
   //   }
   //
   //
   //#endif


   int application::__implement()
   {

      return main_loop();

   }


   int application::main_loop()
   {

      //__main(this);

      return m_iExitCode;

   }


   void application::init1()
   {


      initialize_context_1();


   }


   void application::init2()
   {


   }


   void application::init3()
   {


   }


   void application::init()
   {


   }



   void application::init_instance()
   {

      acmenode()->add_application_capability(m_eapplicationcapabilitya);

   }


   bool application::has_capability(enum_application_capability ecapability) const
   {

      return m_eapplicationcapabilitya.contains(ecapability);

   }


   void application::add_capability(enum_application_capability ecapability)
   {

      m_eapplicationcapabilitya.add_unique(ecapability);

   }


   //
   //class ::main main(argc, argv, envp);
   //
   //__main(main);
   //
   //class ::main main(argc, argv, envp);
   //
   //__main(main);


   bool application::handle_call(::payload& payload, const ::string& strObject, const ::string& strMember, ::property_set& propertyset)
   {

      if (strObject == "application")
      {

         return handle_application_call(payload, strMember, propertyset);

      }

      return false;

   }


   bool application::handle_application_call(::payload& payload, const ::string& strMember, ::property_set& propertyset)
   {

      return false;

   }


   ::file::path application::get_app_localconfig_folder()
   {

      ::file::path pathFolder = acmedirectory()->roaming() / m_strAppId;

      return pathFolder;

   }


   ::pointer<::handle::ini>application::get_ini()
   {

      auto pathFolder = get_app_localconfig_folder();

      auto pathIni = pathFolder / "this.ini";

      auto pini = acmefile()->get_ini(pathIni);

      return pini;

   }


   string application::get_visual_studio_build()
   {

      ::file::path path = acmedirectory()->config() / "programming/vs_build.txt";

      string strBuild = acmefile()->as_string(path);

      strBuild.trim();

      return strBuild;

   }


   ::string application::get_application_name()
   {

      return m_strAppName;

   }



   void application::set_locale(const string& pcsz, const ::action_context& context)
   {

      string strLocale(pcsz);


      strLocale.trim();

      m_strLocale = strLocale;

      on_set_locale(m_strLocale, context);

   }


   void application::set_schema(const string& pcsz, const ::action_context& context)

   {

      string strSchema(pcsz);


      strSchema.trim();

      m_strSchema = strSchema;

      on_set_schema(m_strSchema, context);

   }


   void application::on_set_locale(const string& pcsz, const ::action_context& context)

   {
      UNREFERENCED_PARAMETER(context);
      UNREFERENCED_PARAMETER(pcsz);

      //psystem->appa_load_string_table();
   }


   void application::on_set_schema(const string& pcsz, const ::action_context& context)

   {
      UNREFERENCED_PARAMETER(context);
      UNREFERENCED_PARAMETER(pcsz);

      //psystem->appa_load_string_table();
   }





   string application::get_locale_schema_dir()
   {

      return _001Concatenate(get_locale(), "/", get_schema());

   }


   string application::get_locale_schema_dir(const ::string& strLocale)
   {

      return _001Concatenate(strLocale.is_empty() ? get_locale() : strLocale, "/", get_schema());

   }


   void application::matter_locator_locale_schema_matter(string_array& stra, const string_array& straMatterLocator, const ::string& strLocale, const ::string& strSchema)
   {

      if (strLocale.is_empty() || strSchema.is_empty())
      {

         return;

      }

      for (auto& strMatterLocator : straMatterLocator)
      {

         string strLs = get_locale_schema_dir(strLocale, strSchema);

         stra.add_unique(::file::path(strMatterLocator) / strLs);

      }

   }


   void application::locale_schema_matter(string_array& stra, const string_array& straMatterLocator, const ::string& strLocale, const ::string& strSchema)
   {

      if (straMatterLocator.has_elements())
      {

         stra.add_unique(::file::path(straMatterLocator.first()) / get_locale_schema_dir("map", "map"));

      }

      matter_locator_locale_schema_matter(stra, straMatterLocator, strLocale, strSchema);

      if (acmeapplication()->m_bSession)
      {

         auto psession = acmesession();

         auto ptextcontext = psession->text_context();

         for (i32 i = 0; i < ptextcontext->localeschema().m_idaLocale.get_count(); i++)
         {

            string strLocale = ptextcontext->localeschema().m_idaLocale[i];

            string strSchema = ptextcontext->localeschema().m_idaSchema[i];

            matter_locator_locale_schema_matter(stra, straMatterLocator, strLocale, strSchema);

         }

      }

      matter_locator_locale_schema_matter(stra, straMatterLocator, "en", "en");

      matter_locator_locale_schema_matter(stra, straMatterLocator, "_std", "_std");

      if (straMatterLocator.has_elements())
      {

         stra.add_unique(::file::path(straMatterLocator.first()) / get_locale_schema_dir("404", "404"));

      }

   }


   string application::get_locale_schema_dir(const ::string& strLocale, const ::string& strSchema)
   {

      return _001Concatenate(strLocale, "/", strSchema);

   }


   void application::fill_locale_schema(::text::international::locale_schema& localeschema, const string& pszLocale, const string& pszSchema)
   {

      localeschema.m_idaLocale.erase_all();
      localeschema.m_idaSchema.erase_all();


      string strLocale(pszLocale);
      string strSchema(pszSchema);


      localeschema.m_atomLocale = pszLocale;
      localeschema.m_atomSchema = pszSchema;


      localeschema.add_locale_variant(strLocale, strSchema);
      localeschema.add_locale_variant(get_locale(), strSchema);
      localeschema.add_locale_variant("std", strSchema);
      localeschema.add_locale_variant("en", strSchema);

      localeschema.destroy();

   }


   void application::fill_locale_schema(::text::international::locale_schema& localeschema)
   {


      localeschema.m_idaLocale.erase_all();
      localeschema.m_idaSchema.erase_all();


      //localeschema.m_bAddAlternateStyle = true;


      string_array straLocale;
      string_array straSchema;

      straLocale.add(get_locale());
      straSchema.add(get_schema());


      string_array stra;

      stra = payload("locale").stra();

      stra.erase_ci("_std");

      straLocale.append_unique(payload("locale").stra());

      stra.empty();

      stra = payload("schema").stra();

      stra.erase_ci("_std");

      straSchema.append_unique(payload("schema").stra());

      localeschema.m_atomLocale = straLocale[0];
      localeschema.m_atomSchema = straSchema[0];

      for (index iLocale = 0; iLocale < straLocale.get_count(); iLocale++)
      {

         for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
         {

            localeschema.add_locale_variant(straLocale[iLocale], straSchema[iSchema]);

         }

      }

      for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      {

         localeschema.add_locale_variant(get_locale(), straSchema[iSchema]);

      }

      for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      {

         localeschema.add_locale_variant("std", straSchema[iSchema]);

      }


      for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      {

         localeschema.add_locale_variant("en", straSchema[iSchema]);

      }

      localeschema.destroy();

   }


   void application::on_before_launching()
   {


   }


   void application::os_native_bergedge_start()
   {


   }


   void application::process_init()
   {


      initialize_context();

   }


   void application::application_pre_run()
   {
      //
      //information() << "apex::application::application_pre_run";
      //
      //#ifdef WINDOWS_DESKTOP
      //
      //MSG msg;
      //
      //// Create Windows Message Queue
      //::PeekMessageA(&msg, nullptr, 0, 0xffff, 0);
      //
      //MESSAGE message;
      //
      //copy(message, msg);
      //
      //auto psystem = acmesystem()->m_papexsystem;
      //
      //if (!is_system() && is_true("SessionSynchronizedInput"))
      //{
      //
      //::AttachThreadInput(GetCurrentThreadId(), (u32)psystem->get_itask(), true);
      //
      //}
      //
      //#endif

      m_timeHeartBeat.Now();

      //try
      //{
      //
      //if (!InitApplication())
      //{
      //
      //return false;
      //
      //}
      //
      //}
      //catch (::exit_exception * pe)
      //{
      //
      //throw pe;
      //
      //}
      //catch (const ::exception * pe)
      //{
      //
      ////thisexc << 1 << m_iErrorCode;
      //
      //::acme::del(pe);
      //
      //return false;
      //
      //}
      //catch (...)
      //{
      //
      ////thisexcall << 1 << m_iErrorCode;
      //
      //return false;
      //
      //}

      m_timeHeartBeat.Now();

      //::e_status estatus = ::success;

      try
      {

         //estatus = 

         process_init();

         //if(!estatus)
         //{
         //
         //return false;
         //
         //}

      }
      catch (::exit_exception * pe)
      {

         throw pe;

      }
      catch (const ::exception * pe)
      {

         ::acme::del(pe);

         //return false;

      }
      catch (...)
      {

         //return false;

      }

      //auto psystem = acmesystem()->m_papexsystem;

      //      auto psystem = acmesystem();
      //
      //      psystem->install_progress_add_up();

      m_timeHeartBeat.Now();

      try
      {

         //if (!init_application())
         init_application();
         //{
         //
         //return false;
         //
         //}

      }
      catch (const ::exception & e)
      {

         handle_exception(e);

         message_box_synchronous(this, "Application failed to initialize (1).\n\n" + e.m_strMessage, m_strAppName, e_message_box_ok, e.m_strMessage + "\n" + e.m_strDetails);

         throw e;

      }
      catch (...)
      {

         message_box_synchronous(this, "Application failed to initialize (2). Unknown exception", m_strAppName);

         throw "Unknown exception";

      }

      m_timeHeartBeat.Now();

      try
      {

         auto psystem = acmesystem();

         //if (!is_system() && !is_session())
         {

            if (psystem->is_true("uninstall"))
            {

               do_uninstall();

               //return false;

            }
            else if (psystem->is_true("install"))
            {

               do_install();

               //return false;

            }

         }

         init_instance();

         //if (!init_instance())
         //{
         //
         ////return false;
         //
         //}

         //on_update_matter_locator();

      }
      catch (const ::exit_exception & exception)
      {

         throw exception;

      }
      catch (const ::exception & exception)
      {

         message_box_synchronous(this, "Application failed to initialize (4). Unknown exception", m_strAppName, e_message_box_ok,
            exception.m_strMessage + "\n\n" + exception.m_strDetails + "\n\n" + exception.m_strCallstack);

         throw exception;

      }
      catch (...)
      {

         message_box_synchronous(this, "Application failed to initialize (4). Unknown exception", m_strAppName);

         throw "Unknown exception";

      }

      //return true;

   }


   void application::pre_run()
   {

      information() << "apex::application::pre_run";

      try
      {

         m_timeHeartBeat.Now();

         application_pre_run();

         //{

         //   m_bReady = true;

         //   return false;

         //}

         //    if(!check_install())
         //    {

         //       m_bReady = true;

         //       return false;

         //    }

         //         if(!is_system() && !is_session())
         //         {
         //
         //            if(!is_installed())
         //            {
         //
         //
         //            }
         //
         //         }

         //xxdebug_box("pre_run 1 ok", "pre_run 1 ok", e_message_box_icon_information);

         //auto estatus = 
         on_before_launching();

         //if(!estatus)
         //{

         //   m_bReady = true;

         //   return estatus;

         //}

         m_timeHeartBeat.Now();

         os_native_bergedge_start();
         //{

         //   m_bReady = true;

         //   return false;

         //}

         information() << "apex::application::pre_run success";

         //return true;

      }
      catch (const ::exception& e)
      {

         handle_exception(e);

         throw e;

      }
      catch (...)
      {

         information() << "apex::application::pre_run exception.4";

         throw ::exception(error_exception);

      }

      //return false;

   }


   void application::init_application()
   {

      auto psystem = acmesystem();

      information() << "apex::application::init_application";

      m_timeHeartBeat.Now();

      init1();

      //if (!init1())
      //{
      //
      ////dappy(__type_name(this) + " : init1 failure : " + as_string(m_iErrorCode));
      //
      //return false;
      //
      //}

      psystem->install_progress_add_up(); // 2

      //xxdebug_box("init1 ok", "init1 ok", e_message_box_icon_information);

      m_timeHeartBeat.Now();

      init2();

      //if (!init2())
      //{
      //
      ////dappy(__type_name(this) + " : init2 failure : " + as_string(m_iErrorCode));
      //
      //return false;
      //
      //}

      psystem->install_progress_add_up(); // 3

      //xxdebug_box("init2 ok", "init2 ok", e_message_box_icon_information);

      m_timeHeartBeat.Now();

      init3();

      //if (!init3())
      //{
      //
      ////dappy(__type_name(this) + " : init3 failure : " + as_string(m_iErrorCode));
      //
      //return false;
      //
      //}

      psystem->install_progress_add_up(); // 4

      //xxdebug_box("init3 ok", "init3 ok", e_message_box_icon_information);

      m_timeHeartBeat.Now();

      //dappy(__type_name(this) + " : init3 ok : " + as_string(m_iErrorCode));

      //try
      //{

      init();
      //{
      //
      ////dappy(__type_name(this) + " : initialize failure : " + as_string(m_iErrorCode));
      //
      //return false;
      //
      //}
      //
      //}
      //catch (const ::string & psz)
      //{
      //
      //if (!strcmp(psz, "You have not logged in! Exiting!"))
      //{
      //
      //return false;
      //
      //}
      //
      //return false;

      //}

      psystem->install_progress_add_up(); // 5

      //      m_bAuraInitializeInstanceResult = true;

      //return true;

   }


   void application::do_install()
   {


   }


   void application::do_uninstall()
   {



   }


   void application::on_install()
   {


   }


   void application::on_uninstall()
   {


   }


} // namespace acme


void* application_system(void* pApplication)
{

   auto papp = (::acme::application*)pApplication;

   return papp->acmesystem();

}

bool application_get_bool(void* pApplication, const char* pszItem)
{

   auto papp = (::acme::application*)pApplication;

   return papp->payload(pszItem).as_bool();

}
