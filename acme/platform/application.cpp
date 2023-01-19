﻿//
// Created by camilo on 22/02/2022.
//
// app to application and back to acme namespace by camilo on 2022-09-17 18:54 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "application.h"
#include "acme.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/platform/session.h"


#ifdef WINDOWS


#include "acme/_operating_system.h"


CLASS_DECL_ACME::file::path get_module_path(HMODULE hmodule);


#else


CLASS_DECL_ACME ::file::path get_module_path();


#endif


CLASS_DECL_ACME void set_main_user_thread();

//#if defined(LINUX) || defined(FREEBSD) || defined(RASPBIAN) || defined(ANDROID)
//static const char * g_p1;
//static const char * g_p2;
//void set_res(const char * p1, const char * p2)
//{
//
//   g_p1 = p1;
//   g_p2 = p2;
//}
//#endif
//#ifdef WINDOWS
//static HINSTANCE g_hinstanceThis;
//static HINSTANCE g_hinstancePrev;
//static int g_nCmdShow;
//CLASS_DECL_ACME void set_winmain(HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, int nCmdShow)
//{
//   g_hinstanceThis = hinstanceThis;
//   g_hinstancePrev = hinstancePrev;
//   g_nCmdShow = nCmdShow;
//}
//#endif


namespace acme
{


   application::application()
   {

      m_papexapplication = nullptr;
      m_paquaapplication = nullptr;
      m_pauraapplication = nullptr;
      m_paxisapplication = nullptr;
      m_pbaseapplication = nullptr;
      m_pbredapplication = nullptr;
      m_pcoreapplication = nullptr;

      if (m_pacme && !m_pacme->m_pacmeapplication)
      {

         m_pacme->m_pacmeapplication = this;

      }

//      if (g_p == nullptr)
//      {
//
//         g_p = this;
//         
//#ifdef WINDOWS
//
//         defer_initialize_system_heap();
//
//#endif
//
//         g_p->m_pmain = memory_new ::main();
//
//      }
//      else
//      {
//
//         m_pmain = g_p->m_pmain;
//
//      }

       factory()->add_factory_item < ::acme::system >();
       factory()->add_factory_item < ::acme::session >();

      //if (!g_p)
      //{

      //   g_p = this;

      //}

      m_pacmeapplication = this;

      //acmeapplication() = this;

      //acmeapplication() = this;

      //::acme::initialize();

//#if defined(WINDOWS)
//
//      m_hinstanceThis = g_hinstanceThis;
//      m_hinstancePrev = g_hinstancePrev;
//      m_nCmdShow = g_nCmdShow;
//
//#elif defined(LINUX) || defined(FREEBSD) || defined(RASPBIAN) || defined(ANDROID)
//
//      m_pchar_binary__matter_zip_start = g_p1;
//      m_pchar_binary__matter_zip_end = g_p2;
//
//#endif

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


   void application::initialize(::particle * pparticle)
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

      return ::acme::acme::g_p->m_psubsystem->factory();

   }


   void application::implement_application()
   {

      //on_initialize_application(pmain);


      //



      //void __main(::acme::application * pacmeapplication)
      //{



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

         auto pfactoryitem = ::acme::acme::g_p->m_psubsystem->m_pfactory->get_factory_item<::acme::system>();

         ::pointer<::acme::system> psystem = pfactoryitem->create_particle();

         ::set_task(psystem);

         psystem->initialize_system();

         //psystem->acmeapplication() = pacmeapplication;

         //psystem->m_psubsystem = psubsystem;

         psystem->system_construct(this);

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

         ::task_release();

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

      if(m_bVerbose.undefined())
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

         m_bResource = !m_bConsole;

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

#ifdef WINDOWS

         m_pathModule = ::get_module_path((HMODULE)::acme::acme::g_p->m_psubsystem->m_hinstanceThis);

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


   bool application::handle_call(::payload & payload, const ::string & strObject, const ::string & strMember, ::property_set & propertyset)
   {

      if (strObject == "application")
      {

         return handle_application_call(payload, strMember, propertyset);

      }

      return false;
      
   }


   bool application::handle_application_call(::payload & payload, const ::string & strMember, ::property_set & propertyset)
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




} // namespace acme


void * application_system(void * pApplication)
{

   auto papp = (::acme::application *)pApplication;

   return papp->acmesystem();

}

bool application_get_bool(void * pApplication, const char * pszItem)
{
   
   auto papp = (::acme::application *)pApplication;
   
   return papp->payload(pszItem).as_bool();
   
}
