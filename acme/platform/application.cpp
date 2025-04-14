//
// Created by camilo on 22/02/2022.
//
// app to application and back to acme namespace by camilo on 2022-09-17 18:54 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "application.h"
#include "acme.h"
#include "application_menu.h"
#include "acme/exception/exit.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/filesystem/filesystem/file_system_options.h"
#include "acme/handler/request.h"
#include "acme/operating_system/a_system_menu.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/platform/platform.h"
//#include "acme/handler/sequence.h"
#include "acme/platform/system.h"
#include "acme/platform/session.h"
#include "acme/prototype/string/_str.h"
#include "acme/prototype/text/context.h"
#include "acme/nano/nano.h"
#include "acme/user/micro/user.h"
#include "acme/user/user/activation_token.h"
#include "acme/nano/graphics/icon.h"
#include "acme/windowing/windowing.h"


#ifdef WINDOWS_DESKTOP


#include "acme/_operating_system.h"


CLASS_DECL_ACME::file::path get_module_path(HMODULE hmodule);


#else


CLASS_DECL_ACME::file::path get_module_path();


#endif


namespace platform
{


   application::application()
   {

      //m_bTransferToContainer = true;
      //m_bTransferredToContainer = false;

      m_pfilesystemoptions = __allocate::filesystem::file_system_options();

      m_bApplicationFirstRequest = true;

      //if (!::platform::platform::s_pplatform->m_papplication)
      //{

      //   ::platform::platform::s_pplatform->m_papplication = this;

      //}

      //m_acme.m_papplication = this;
      //m_acme.m_papplication = this;

      m_papplication = this;
      // m_papexapplication = nullptr;
      // m_paquaapplication = nullptr;
      // m_pauraapplication = nullptr;
      // m_paxisapplication = nullptr;
      // m_pbaseapplication = nullptr;
      // m_pbredapplication = nullptr;
      // m_pcoreapplication = nullptr;
      
      //set_platform();


   }


   application::~application()
   {

      // m_papexapplication = nullptr;
      // m_paquaapplication = nullptr;
      // m_pauraapplication = nullptr;
      // m_paxisapplication = nullptr;
      // m_pbaseapplication = nullptr;
      // m_pbredapplication = nullptr;
      // m_pcoreapplication = nullptr;

      if (session() && session()->m_papplication == this)
      {

         session()->m_papplication = nullptr;

      }

      if (system() && system()->m_papplication == this)
      {

         system()->m_papplication = nullptr;

      }

      // if (m_pplatform && m_papplication == this)
      // {
      //
      //    m_papplication = nullptr;
      //
      // }

      /*   if (g_p == this)
       {

       m_pmain.release();

       ::acme::del(m_pmain);

       g_p = nullptr;



       }*/
       //   ::acme::finalize_system();

      printf_line("platform::application destroyed");
      
   }


   void application::on_set_platform()
   {

      ::platform::context::on_set_platform();

      if (::is_null(system()->m_papplication))
      {

         system()->m_papplication = this;

      }

      __check_refdbg

      factory()->add_factory_item < ::platform::system >();

      __check_refdbg

      factory()->add_factory_item < ::platform::session >();

   }


   void application::on_initialize_particle()
   {

      ::platform::context::on_initialize_particle();

      {

#include "deployment/build.h"

         m_strBuild = pszBuild;

      }

      if (m_strBuild.is_empty())
      {

         m_strBuild = "(unknown build version)";

      }


   }


   ::user::user * application::user()
   {

      return nullptr;

   }

   //int application::application_main()
   //{

   //   implement_application();

   //   return m_iExitCode;

   //}


   //void application::initialize(::particle* pparticle)
   //{

   //   ::task::initialize(pparticle);

   //}


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


   ::application_menu * application::application_menu()
   {

      if (__defer_construct_new(m_papplicationmenu))
      {

         m_papplicationmenu->m_strName = application_title();

         m_papplicationmenu->m_bPopup = true;

      }

      return m_papplicationmenu;

   }


   //void application::on_initialize_application()
   //{

   //}

   //::factory::factory_pointer& application::factory()
   //{

   //   return this->::system()->factory();

   //}


   void application::initialize_application()
   {

      set_platform();

      // if (m_papplication == nullptr)
      // {
      //
      //    m_papplication = this;
      //
      //    defer_initialize_platform();
      //
      // }
      //
      // if (!m_psystem)
      // {
      //
      //    m_psystem = m_psystem;
      //
      // }

   }


#if REFERENCING_DEBUGGING


   void application::on_after_construct(::reference_referer* preferer)
   {


      m_prefererCreation = preferer;


      ::subparticle::on_after_construct(preferer);


   }


#endif


   void application::_001TryCloseApplication()
   {

      if (!::system()->is_console())
      {

         //system()->acme_windowing()->windowing_system_post_quit();

//         main_post([this]()
            {

  //             post([this]()
                  {

                     set_finish();

               }
                     //);

         }
               //);

      }

   }


   void application::application_on_status(::e_status estatus, ::particle* pparticle, long long hi, void* p)
   {

      if (estatus == error_icloud_not_available)
      {

         if (!m_bGUIReady)
         {

            auto pusermessage = __create_new < user_message >();

            pusermessage->m_estatus = estatus;

            pusermessage->m_pparticle = pparticle;

            pusermessage->m_hi = hi;

            pusermessage->m_p = p;

            m_usermessagea.add_unique(pusermessage);

         }
         else
         {

            on_error_icloud_not_available(pparticle, hi, p);

         }

      }

   }


   void application::on_error_icloud_not_available(::particle* pparticle, long long hi, void* p)
   {

      ::function < void(const ::atom& atom) > function;

      auto pmessagebox = __initialize_new::message_box(
         "Application needs iCloud and it is not Available",
         "iCloud is not Available.",
         e_message_box_ok | e_message_box_icon_exclamation);

      pmessagebox->sync();

   }


   int application::application_main()
   {

      __check_refdbg

      initialize_application();

      __check_refdbg

      //output_debug_string("platform::application implement_application\n");

      ::e_status estatus = error_failed;

      ::e_status estatusEnd = error_failed;

      string strAppId;

      if (!::system()->is_console())
      {

         strAppId = m_strAppId;

      }

      if(m_strAppId.has_character())
      {

         string strPrgName = m_strAppId;

         strPrgName.replace_with(".", "/");

         strPrgName.replace_with("-", "_");

         m_strProgName = "com." + strPrgName;

      }

      //main.m_bAudio = main_hold_base::is_audio_enabled();

      //auto pfactoryitem = this->::system()->m_pfactory->get_factory_item<::platform::system>();

      //::pointer<::platform::system> psystem = pfactoryitem->create_particle();

      // ::set_task(m_psystem);

      //information() << "acme implement_application system_construct";

      //information() << "acme implement_application create_os_node";

      //m_psystem->create_os_node();

      //auto pnode = m_psystem->node();

      system()->application_main(this);

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

      return m_iExitCode;

   }


   void application::initialize_application_flags()
   {

      if (m_bVerbose.undefined())
      {

         m_bVerbose = true;

      }

      if (m_bDraw2d.undefined())
      {

         m_bDraw2d = !::system()->is_console();

      }

      if (m_bWriteText.undefined())
      {

         m_bWriteText = m_bDraw2d;

      }

      if (m_bUser.undefined())
      {

         m_bUser = !::system()->is_console();

      }

      if (m_bUserEx.undefined())
      {

         m_bUserEx = !::system()->is_console();

      }

      if (m_bImaging.undefined())
      {

         m_bImaging = !::system()->is_console();

      }

//      if (m_bCrypto.undefined())
//      {
//
//         m_bCrypto = !::system()->is_console();
//
//      }

      if (m_bResource.undefined())
      {

         m_bResource = !system()->m_bConsole;

         //m_bResource = true;

      }

#ifdef WINDOWS_DESKTOP

      if (m_bGdiplus.undefined())
      {

         m_bGdiplus = !::system()->is_console();

      }

#endif

#if defined(LINUX)

      if (m_bGtkApp.undefined())
      {

         m_bGtkApp = !::system()->is_console();

      }

#endif

      if (m_bShowApplicationInformation.undefined())
      {

         m_bShowApplicationInformation = false;

      }

      if (::system()->is_console())
      {

         if (m_bSession.undefined())
         {

            m_bSession = false;

         }

      }
      else // !is_console()
      {

         if (m_bSession.undefined())
         {

            m_bSession = true;

         }

      }

      //string strAppId = application()->m_strAppId;

   }



   //bool application::is_application() const
   //{

   //   return true;

   //}


   //bool application::is_system() const
   //{

   //   return false;

   //}


   //bool application::is_session() const
   //{

   //   return true;

   //}


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

      _synchronous_lock synchronizationlock(synchronization());

      if (!m_bModulePath)
      {

#ifdef WINDOWS_DESKTOP

         m_pathModule = ::get_module_path((HMODULE)system()->m_hinstanceThis);

#elif defined(ANDROID)

         m_pathModule.empty();

#else

         //throw ::exception(todo);
         //m_pathModule = file_system()->module();
         m_pathModule = ::get_module_path();

#endif

         m_bModulePath = true;

      }

      return m_pathModule;

   }


   ::file::path application::get_module_folder()
   {

      _synchronous_lock synchronizationlock(synchronization());

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

      if (m_strAppName.has_character())
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

      if (textAppTitle.get_text().has_character())
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

      if (textAppName.get_text().has_character())
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


   //int application::__implement()
   //{

   //   return main_loop();

   //}


   //int application::main_loop()
   //{

   //   //__main(this);

   //   return m_iExitCode;

   //}
   void application::main()
   {

      ::task::main();

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

      if (!system()->m_bConsole)
      {
         auto papplicationmenu = application_menu();

         papplicationmenu->erase_all();

         using namespace ::apex;

         {

            auto ppopupApp = papplicationmenu->popup(application_title());

            //pmenuMain->add(pmenuApp);

            ppopupApp->item("About " + application_title(), "show_about_box", "", "");

            ppopupApp->separator();

            ppopupApp->item("Quit " + application_title(), "try_close_application", "", "");

         }

         //      {
         //
         //         auto ppopupView = papplicationmenu->popup("View");
         //
         //         //ppopupView->add(pmenuView);
         //
         //         ppopupView->item("Transparent Frame", "transparent_frame", "", "");
         //
         //      }
         //
         //      //applicationmenu().add_item(i++, _("Transparent Frame"), "transparent_frame");
         //
         ////      applicationmenu()->add_item(i++, "About " + m_strAppName, "show_about", "", "Show About");
         ////
         ////      applicationmenu()->add_item(i++, "Transparent Frame", "transparent_frame", "Ctrl+Shift+T", "Toggle Transparent Frame");

         application_menu_update();
      }

   }


   void application::application_menu_update()
   {

   //#ifdef LINUX
   //
   //      auto psystem = system();
   //
   //      if (application()->m_bGtkApp)
   //      {
   //
   //         auto pnode = psystem->node();
   //
   //         if (pnode)
   //         {
   //
   //            pnode->set_application_menu(m_pappmenu, this);
   //
   //         }
   //
   //      }
   //
   //#else
   //
      system()->acme_windowing()->application_handle(id_application_menu_update, nullptr);
   //
   //#endif

   }


   void application::init_instance()
   {

      node()->add_application_capability(m_eapplicationcapabilitya);

   }


   //void application::init_task()
   //{

   //   ::task::init_task();

   //   //try
   //   //{

   //   //   pre_run();
   //   //   //{

   //   //   //   return false;

   //   //   //}

   //   //}
   //   //catch (const ::exception& e)
   //   //{

   //   //   informationf("application::init_task exception!!");

   //   //   handle_exception(e);

   //   //   session()->set_finish();

   //   //   throw e;

   //   //}
   //   //catch (...)
   //   //{

   //   //   //      return false;

   //   //   throw ::exception(error_exception);

   //   //}

   //   //return true;

   //}


   //void application::term_task()
   //{

   //   debug() << "::platform::applicationterm_task";

   //   ping();

   //   //try
   //   //{

   //   //   pos_run();

   //   //}
   //   //catch (...)
   //   //{

   //   //}

   //   ::task::term_task();

   //}


   void application::user_confirm_close_application()
   {

      auto pmessagebox = __initialize_new::message_box("Are you sure you want to close application?", nullptr, e_message_box_yes_no);

      pmessagebox->async()
         << [this, pmessagebox]()
         {

            if (pmessagebox->m_payloadResult.as_int() == e_dialog_result_yes)
            {

               auto papp = get_app();

               papp->_001TryCloseApplication();

            }
            else if (pmessagebox->m_payloadResult.as_int() == e_dialog_result_cancel)
            {

            }

         };

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

      ::file::path pathFolder = directory_system()->roaming() / m_strAppId;

      return pathFolder;

   }


   //::pointer<::handle::ini>application::get_ini()
   //{

   //   auto pathFolder = get_app_localconfig_folder();

   //   auto pathIni = pathFolder / "this.ini";

   //   auto pini = file_system()->get_ini(pathIni);

   //   return pini;

   //}


#ifdef _DEBUG


   long long application::increment_reference_count()
   {

      return ::platform::context::increment_reference_count();

   }
   
   
   long long application::decrement_reference_count()
   {

      return ::platform::context::decrement_reference_count();

   }

#endif

   ::release_time_for_project application::release_time()
   {

      return ::system()->as_release_time_for_project("(not set)");

   }


   string application::get_visual_studio_build()
   {

      ::file::path path = directory_system()->config() / "programming/vs_build.txt";

      string strBuild = file_system()->as_string(path);

      strBuild.trim();

      return strBuild;

   }


   ::string application::get_application_name()
   {

      return m_strAppName;

   }



   void application::set_locale(const scoped_string& scopedstrLocale, const ::action_context& context)
   {

      string strLocale(scopedstrLocale);


      strLocale.trim();

      m_strLocale = strLocale;

      on_set_locale(m_strLocale, context);

   }


   void application::set_schema(const ::scoped_string& scopedstrSchema, const ::action_context& context)
   {

      string strSchema(scopedstrSchema);

      strSchema.trim();

      m_strSchema = strSchema;

      on_set_schema(m_strSchema, context);

   }


   void application::on_set_locale(const ::scoped_string& scopedstrLocale, const ::action_context& context)
   {

      __UNREFERENCED_PARAMETER(scopedstrLocale);
      __UNREFERENCED_PARAMETER(context);

      //psystem->appa_load_string_table();
   }


   void application::on_set_schema(const ::scoped_string& scopedstrSchema, const ::action_context& context)
   {

      __UNREFERENCED_PARAMETER(scopedstrSchema);
      __UNREFERENCED_PARAMETER(context);

      //psystem->appa_load_string_table();
   }


   string application::get_locale_schema_dir()
   {

      return _001Concatenate(get_locale(), "/", get_schema());

   }


   string application::get_locale_schema_dir(const ::scoped_string& scopedstrLocale)
   {

      return _001Concatenate(scopedstrLocale.is_empty() ? get_locale() : ::string(scopedstrLocale), "/", get_schema());

   }


   void application::matter_locator_locale_schema_matter(string_array& stra, const string_array& straMatterLocator, const ::scoped_string& scopedstrLocale, const ::scoped_string& scopedstrSchema)
   {

      if (scopedstrLocale.is_empty() || scopedstrSchema.is_empty())
      {

         return;

      }

      for (auto& strMatterLocator : straMatterLocator)
      {

         string strLs = get_locale_schema_dir(scopedstrLocale, scopedstrSchema);

         stra.add_unique(::file::path(strMatterLocator) / strLs);

      }

   }


   void application::locale_schema_matter(string_array& stra, const string_array& straMatterLocator, const ::scoped_string& scopedstrLocale, const ::scoped_string& scopedstrSchema)
   {

      if (straMatterLocator.has_elements())
      {

         stra.add_unique(::file::path(straMatterLocator.first()) / get_locale_schema_dir("map", "map"));

      }

      matter_locator_locale_schema_matter(stra, straMatterLocator, scopedstrLocale, scopedstrSchema);

      if (m_bSession)
      {

         auto psession = session();

         auto ptextcontext = psession->text_context();

         for (int i = 0; i < ptextcontext->localeschema().m_straLocale.get_count(); i++)
         {

            auto strLocale = ptextcontext->localeschema().m_straLocale[i];

            auto strSchema = ptextcontext->localeschema().m_straSchema[i];

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


   string application::get_locale_schema_dir(const ::scoped_string& scopedstrLocale, const ::scoped_string& scopedstrSchema)
   {

      return _001Concatenate(scopedstrLocale, "/", scopedstrSchema);

   }


   void application::fill_locale_schema(::text::international::locale_schema& localeschema, const ::scoped_string& scopedstrLocale, const ::scoped_string& scopedstrSchema)
   {

      localeschema.m_straLocale.erase_all();
      localeschema.m_straSchema.erase_all();


      string strLocale(scopedstrLocale);
      string strSchema(scopedstrSchema);


      localeschema.m_strLocale = scopedstrLocale;
      localeschema.m_strSchema = scopedstrSchema;


      localeschema.add_locale_variant(strLocale, strSchema);
      localeschema.add_locale_variant(get_locale(), strSchema);
      localeschema.add_locale_variant("std", strSchema);
      localeschema.add_locale_variant("en", strSchema);

      localeschema.destroy();

   }


   void application::fill_locale_schema(::text::international::locale_schema& localeschema)
   {


      localeschema.m_straLocale.erase_all();
      localeschema.m_straSchema.erase_all();


      //localeschema.m_bAddAlternateStyle = true;


      string_array straLocale;
      string_array straSchema;

      straLocale.add(get_locale());
      straSchema.add(get_schema());


      string_array stra;

      stra = payload("locale").as_string_array();

      stra.case_insensitive_erase("_std");

      straLocale.append_unique(payload("locale").as_string_array());

      stra.empty();

      stra = payload("schema").as_string_array();

      stra.case_insensitive_erase("_std");

      straSchema.append_unique(payload("schema").as_string_array());

      localeschema.m_strLocale = straLocale[0];
      localeschema.m_strSchema = straSchema[0];

      for (::collection::index iLocale = 0; iLocale < straLocale.get_count(); iLocale++)
      {

         for (::collection::index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
         {

            localeschema.add_locale_variant(straLocale[iLocale], straSchema[iSchema]);

         }

      }

      for (::collection::index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      {

         localeschema.add_locale_variant(get_locale(), straSchema[iSchema]);

      }

      for (::collection::index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      {

         localeschema.add_locale_variant("std", straSchema[iSchema]);

      }


      for (::collection::index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      {

         localeschema.add_locale_variant("en", straSchema[iSchema]);

      }

      localeschema.destroy();

   }


   ::enum_id application::key_command(::user::enum_key ekey, ::user::key_state* pkeystate)
   {

      return node()->key_command(ekey, pkeystate);

   }


   void application::on_before_launching()
   {


   }


   //void application::os_native_bergedge_start()
   //{


   //}


   void application::process_init()
   {

      initialize_context();

      if (m_strAppId.has_character())
      {

         string_array stra;

         stra.explode("/", m_strAppId);

         m_strRoot = stra[0];

         m_strDomain = stra.slice(1).implode("/");

         add_matter_locator(this);

      }

   }


   void application::init_task()
   {

      ::task::init_task();
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
      //auto psystem = system();
      //
      //if (!is_system() && is_true("SessionSynchronizedInput"))
      //{
      //
      //::AttachThreadInput(GetCurrentThreadId(), (unsigned int)psystem->get_itask(), true);
      //
      //}
      //
      //#endif

      ping();

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

      ping();

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
      catch (::exit_exception* pe)
      {

         throw pe;

      }
      catch (const ::exception* pe)
      {

         ::acme::del(pe);

         //return false;

      }
      catch (...)
      {

         //return false;

      }

      //auto psystem = system();

      //      auto psystem = system();
      //
      //      psystem->install_progress_add_up();

      ping();

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
      catch (const ::exception& e)
      {

         handle_exception(e);

         auto pmessagebox = __initialize_new::message_box(
            "Application failed to initialize (1).\n\n" + e.m_strMessage,
            m_strAppName,
            e_message_box_ok,
            e.m_strMessage + "\n" + e.m_strDetails);

         pmessagebox->sync();

         throw e;

      }
      catch (...)
      {

         auto pmessagebox = __initialize_new::message_box(
            "Application failed to initialize (2). Unknown exception",
            m_strAppName);

         pmessagebox->sync();

         throw "Unknown exception";

      }

      ping();

      try
      {

         auto psystem = system();

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

      }
      catch (const ::exit_exception& exception)
      {

         throw exception;

      }
      catch (const ::exception& exception)
      {

         auto pmessagebox = __initialize_new::message_box(
            "Application failed to initialize (4). Unknown exception",
            m_strAppName,
            e_message_box_ok,
            exception.m_strMessage + "\n\n" + exception.get_consolidated_details(this));

         pmessagebox->sync();

         throw exception;

      }
      catch (...)
      {

         auto pmessagebox = __initialize_new::message_box(
            "Application failed to initialize (4). Unknown exception",
            m_strAppName);

         pmessagebox->sync();

         throw "Unknown exception";

      }

      //return true;

   }


   //void application::pre_run()
   //{

   //   //information() << "apex::application::pre_run";

   //   try
   //   {

   //      ping();

   //      application_pre_run();

   //      //{

   //      //   m_bReady = true;

   //      //   return false;

   //      //}

   //      //    if(!check_install())
   //      //    {

   //      //       m_bReady = true;

   //      //       return false;

   //      //    }

   //      //         if(!is_system() && !is_session())
   //      //         {
   //      //
   //      //            if(!is_installed())
   //      //            {
   //      //
   //      //
   //      //            }
   //      //
   //      //         }

   //      //xxdebug_box("pre_run 1 ok", "pre_run 1 ok", e_message_box_icon_information);

   //      //auto estatus =
   //      on_before_launching();

   //      //if(!estatus)
   //      //{

   //      //   m_bReady = true;

   //      //   return estatus;

   //      //}

   //      ping();

   //      os_native_bergedge_start();
   //      //{

   //      //   m_bReady = true;

   //      //   return false;

   //      //}

   //      //information() << "apex::application::pre_run success";

   //      //return true;

   //   }
   //   catch (const ::exception& e)
   //   {

   //      informationf("application::pre_run exception!!");

   //      handle_exception(e);

   //      throw e;

   //   }
   //   catch (...)
   //   {

   //      information() << "apex::application::pre_run exception.4";

   //      throw ::exception(error_exception);

   //   }

   //   //return false;

   //}


   void application::init_application()
   {

      auto psystem = system();

      //information() << "apex::application::init_application";

      ping();

      init1();

      //if (!init1())
      //{
      //
      ////dappy(::type(this).name() + " : init1 failure : " + as_string(m_iErrorCode));
      //
      //return false;
      //
      //}

      psystem->install_progress_add_up(); // 2

      //xxdebug_box("init1 ok", "init1 ok", e_message_box_icon_information);

      ping();

      init2();

      //if (!init2())
      //{
      //
      ////dappy(::type(this).name() + " : init2 failure : " + as_string(m_iErrorCode));
      //
      //return false;
      //
      //}

      psystem->install_progress_add_up(); // 3

      //xxdebug_box("init2 ok", "init2 ok", e_message_box_icon_information);

      ping();

      init3();

      //if (!init3())
      //{
      //
      ////dappy(::type(this).name() + " : init3 failure : " + as_string(m_iErrorCode));
      //
      //return false;
      //
      //}

      psystem->install_progress_add_up(); // 4

      //xxdebug_box("init3 ok", "init3 ok", e_message_box_icon_information);

      ping();

      //dappy(::type(this).name() + " : init3 ok : " + as_string(m_iErrorCode));

      //try
      //{

      init();
      //{
      //
      ////dappy(::type(this).name() + " : initialize failure : " + as_string(m_iErrorCode));
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


   //void application::pos_run()
   //{

   //   debug() << "::platform::applicationpos_run";

   //   try
   //   {

   //      ping();

   //      application_pos_run();

   //      //xxdebug_box("pre_run 1 ok", "pre_run 1 ok", e_message_box_icon_information);

   //   }
   //   catch (...)
   //   {

   //      information() << "::platform::applicationpos_run exception.4";

   //   }

   //}


   void application::term_task()
   {

      try
      {

         //if (!is_installing() && !is_unstalling())
         {

            term_instance();

         }

      }
      catch (...)
      {

      }

      try
      {

         term_application();

      }
      catch (...)
      {

      }

      ping();

      try
      {

         process_term();

      }
      catch (...)
      {

      }

      //try
      //{
      //
      //TermApplication();
      //
      //}
      //catch (...)
      //{
      //
      //}

      ::task::term_task();

   }


   void application::term_instance()
   {


   }


   void application::term3()
   {


   }


   void application::term2()
   {


   }


   void application::term1()
   {


   }


   void application::term()
   {


   }




   void application::term_application()
   {

      //try
      //{

      //   close(::apex::e_end_app);

      //}
      //catch (...)
      //{

      //}

      //release_exclusive();

      try
      {

         //try
         //{

         //   m_pinterprocesscommunication.release();

         //}
         //catch (...)
         //{

         //}

         try
         {

            term();

         }
         catch (...)
         {


         }

         try
         {

            term3();

         }
         catch (...)
         {


         }

         try
         {

            term2();

         }
         catch (...)
         {


         }

         try
         {

            term1();

         }
         catch (...)
         {


         }


      }
      catch (...)
      {

      }

   }


   void application::process_term()
   {

      auto psession = session();

      if (::is_set(psession))
      {

         psession->post([this]()
            {

               session()->erase_application(this);

            });

      }

      finalize_context();

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


   ::string_array application::get_about_box_lines()
   {

      auto releasetimeforproject = release_time();

      ::string_array stra;

      stra.add(m_strAppName);

      stra.add("Application ID: " + m_strAppId);

      stra.add("Release Time: " + ::as_string(releasetimeforproject));

      return ::transfer(stra);

   }


   void application::show_about_box(::user::activation_token * puseractivationtoken)
   {

      auto lines = get_about_box_lines();

      ::string strMessage;

      strMessage = lines.implode("\n");

      auto picon = __øcreate < ::nano::graphics::icon>();

      auto pfile = file()->get("matter://main/icon.png");

      picon->load_image_from_file(pfile);

      auto paboutbox = __initialize_new_with(system()->acme_windowing()) ::message_box("About\n\n" + strMessage, nullptr, e_message_box_ok, "", picon);

      //psequencer->then([this, strPath](auto pconversation)
      //      {

      //   if (pconversation->m_payloadResult == e_dialog_result_yes)
      //   {

      //      save_document(strPath);

      //   }
      //   else
      //   {

      //      cancel_save_document();

      //   }


      //      });

      paboutbox->m_puseractivationtoken = puseractivationtoken;

      paboutbox->async();




   }


   bool application::handle_command(const ::atom& atom, ::user::activation_token * puseractivationtoken)
   {

      if (::command_handler::handle_command(atom, puseractivationtoken))
      {

         return true;

      }

      return false;

   }


   bool application::on_command_final(const ::atom& atom, ::user::activation_token * puseractivationtoken)
   {
      
      if(atom == "show_about_box")
      {
       
         show_about_box(puseractivationtoken);

         return true;
         
      }
      else if(atom == "try_close_application")
      {
       
         _001TryCloseApplication();

         return true;
         
      }

      return false;

   }


   void application::add_impact_system(const ::atom& atom, const ::pointer<::user::impact_system>& pimpactsystem)
   {

      throw interface_only();

   }


   ::pointer<::user::impact_system> application::impact_system(const ::atom& atom)
   {

      throw interface_only();

      return {};

   }


   get_file_extension_mime_type* application::get_get_file_extension_mime_type()
   {

      return nullptr;

   }


   void application::pick_browse(const ::function < void(const ::file::path&) >& callback)
   {


   }


   void application::pick_media(const char* pszMediaType)
   {

      __UNREFERENCED_PARAMETER(pszMediaType);

   }


   void application::did_pick_document_at_url(const char* pszUrl)
   {

      auto prequest = __create_new <::request>();

      prequest->m_payloadFile = pszUrl;

      prequest->m_ecommand = ::e_command_file_open;

      this->request(prequest);

   }


   void application::did_pick_document_at_urls(const ::string_array& straUrl)
   {

      auto prequest = __create_new <::request>();

      prequest->m_payloadFile = straUrl;

      prequest->m_ecommand = ::e_command_file_open;

      this->request(prequest);

   }


   void application::on_prompt_write_file(::user::controller* pusercontroller)
   {

      file_manager_save_as(pusercontroller);

   }


   void application::file_manager_save_as(::user::controller* pusercontroller)
   {


   }


   bool application::fill_system_menu(::operating_system::a_system_menu* psystemmenu)
   {

      psystemmenu->add_item("About...", "about_box");

      return true;

   }


   void application::on_system_main()
   {

      information() << "platform::application::on_system_main";

      system()->acme_windowing()->windowing_application_main_loop();


   }


} // namespace platform


::platform::system * application_system(::platform::application * papplication)
{

   return papplication->system();

}


bool application_get_bool(::platform::application * papplication, const char* pszItem)
{

   return papplication->payload(pszItem).as_bool();

}


CLASS_DECL_ACME void application_send_status(::enum_status estatus, ::particle* pparticle, long long hi, void* p)
{

   system()->application()->application_on_status(estatus, pparticle, hi, p);

}


void application_handle_command(::platform::application * papplication, const char * pszCommand, ::user::activation_token * puseractivationtoken)
{
   
   papplication->on_command_final(pszCommand, puseractivationtoken);
   
}



