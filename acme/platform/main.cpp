//
// Created by camilo on 30/10/2021 ~ 00:00 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#ifdef LINUX
#include "acme/operating_system/ansi/binreloc.h"
#endif
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/platform/acme.h"
#include "acme/platform/set_app_id.h"
#include "acme/platform/system_setup.h"
#include "_main_hold_base.h"


static int g_argc;


#ifdef WINDOWS
static wchar_t ** g_argv;
static wchar_t ** g_envp;
#else
static char ** g_argv;
static char ** g_envp;
#endif

#ifdef WINDOWS
CLASS_DECL_ACME void set_argc_argv_envp(int argc, wchar_t ** argv, wchar_t ** envp)
#else
CLASS_DECL_ACME void set_argc_argv_envp(int argc, char ** argv, char ** envp)
#endif
{

   g_argc = argc;
   g_argv = argv;
   g_envp = envp;

}


namespace acme
{

   
   void initialize();


} // namespace acme


MAIN::MAIN()
{

   __zero(this);

   ::acme::initialize();

}



main::main()
{



#ifndef WINDOWS

      ::unsetenv("LD_LIBRARY_PATH");

#endif

      //m_pfnDeferTerm = nullptr;

      //m_iStatusCount = 0;

      //m_iTotalStatusCount = 0;




}


main::~main()
{


}





//const char * br_init_get_symbol();
//
//
//const char * g_pszAppId = nullptr;
//
//
//void executable_set_app_id(const char * pszAppId)
//{
//
//	g_pszAppId = pszAppId;
//
//}
//
//
//const char * executable_get_app_id()
//{
//
//
//   return g_pszAppId;
//
//}
//
//
//set_app_id::set_app_id(const char * pszAppId)
//{
//
//#ifdef LINUX
//
//   br_init_set_symbol(pszAppId);
//
//#endif
//
//   executable_set_app_id(pszAppId);
//
//}




string main::_get_argv(int iArgument) const
{

   if (iArgument < 0 || iArgument >= _get_argc())
   {

      return "";

   }

   if (m_wargv && m_wargv[iArgument])
   {

      return m_wargv[iArgument];

   }
   else if (m_argv && m_argv[iArgument])
   {

      return m_argv[iArgument];

   }

   return "";

}


string main::get_executable() const
{

   return _get_argv(0);

}


string_array main::get_arguments()
{

   string_array stra;

   for (::index i = 0; i < m_argc; i++)
   {

      string strArgument;

      if (m_wargv && m_wargv[i])
      {

      strArgument = m_wargv[i];

      }
      else if (m_argv && m_argv[i])
      {

         strArgument = m_argv[i];

      }
      else
      {

         break;

      }

      stra.add(strArgument);

   }

   return ::move(stra);

}


string main::get_argument1(int iArgument) const
{

   return _get_argv(iArgument + 1);

}


CLASS_DECL_ACME void set_main_user_thread();


//void __main()
//{
//
//
//
//
//}


void __main(::acme::application * pacmeapplication)
{

   #ifdef WINDOWS_DESKTOP
   //{

   //   auto papp = ::app_factory::new_app();

   pacmeapplication->m_argc = __argc;

   pacmeapplication->m_argv = __argv;

   pacmeapplication->m_wargv = __wargv;

   pacmeapplication->m_envp = *__p__environ();

   pacmeapplication->m_wenvp = *__p__wenviron();

      //pacmeapplication->m_hinstanceThis = hinstanceThis;

      //pacmeapplication->m_hinstancePrev = hinstancePrev;

   pacmeapplication->m_strCommandLine = ::GetCommandLineW();

      //pacmeapplication->m_nCmdShow = nCmdShow;

      //pacmeapplication->m_bConsole = false;

      //int iExitCode = pacmeapplication->main_loop();

      //return iExitCode;

#elif !defined(_UWP)

   pacmeapplication->set_args(g_argc, g_argv, g_envp);

#endif


   set_main_user_thread();

   ::e_status estatus = error_failed;

   ::e_status estatusEnd = error_failed;

   string strAppId;

   if (!pacmeapplication->m_bConsole)
   {

      strAppId = pacmeapplication->m_strAppId;

   }

   //main.m_bAudio = main_hold_base::is_audio_enabled();

   auto pfactoryitem = ::factory::get_factory()->get_factory_item<::acme::system>();

   ::pointer<::acme::system>psystem = pfactoryitem->create_element();

#ifdef WINDOWS_DESKTOP
   ::set_task(psystem);
#endif
   //psystem->m_pacmeapplicationStartup = pacmeapplication;

   //psystem->m_psubsystem = psubsystem;

   psystem->system_construct(pacmeapplication);

   psystem->create_os_node();

   auto pnode = psystem->node();

   pnode->implement(pnode, psystem);

   if(pacmeapplication->m_iExitCode == 0 && psystem->m_iExitCode != 0)
   {

      pacmeapplication->m_iExitCode = psystem->m_iExitCode;

   }

   //}

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

}


app_flag::app_flag(::main & main, const char * pszFlag)
{

   if(!::is_empty(pszFlag))
   {

      if(!strcmp(pszFlag, "no_audio"))
      {

         main.m_bAudio = false;

      }
      else if(!strcmp(pszFlag, "no_imaging"))
      {

         main.m_bImaging = false;

      }

   }

}



static char * g_pchar_binary__matter_zip_start = nullptr;


static char * g_pchar_binary__matter_zip_end = nullptr;


embed_resource::embed_resource(char * start, char * end)
{

   g_pchar_binary__matter_zip_start = start;

   g_pchar_binary__matter_zip_end = end;

}


char * embed_resource::get_start()
{

   return g_pchar_binary__matter_zip_start;

}


char * embed_resource::get_end()
{

   return g_pchar_binary__matter_zip_end;

}






#include "acme/operating_system.h"


//#ifdef ANDROID
//
//#include "acme/operating_system/android/_os_local.h"
//
//#endif


#ifdef ANDROID


#endif


//#if defined(WINDOWS_DESKTOP)

//CLASS_DECL_ACME bool windows_register_class(HINSTANCE hinstance);

//CLASS_DECL_ACME ATOM MyRegisterClass(HINSTANCE hInstance);

//#endif




void main::system_construct(const ::main * pmain)
{

   //auto estatus = 
   
   MAIN::copy_main(*pmain);


      //*((MAIN *)this) = *pmain;

      m_strCommandLine = pmain->m_strCommandLine;

      m_strAppId = pmain->m_strAppId;

      m_pfnImplement = pmain->m_pfnImplement;

#if defined(LINUX) || defined(ANDROID) || defined(FREEBSD)

      if (!m_pchar_binary__matter_zip_start && !m_pchar_binary__matter_zip_end
         && pmain->m_pchar_binary__matter_zip_start && pmain->m_pchar_binary__matter_zip_end)
      {

         m_pchar_binary__matter_zip_start = pmain->m_pchar_binary__matter_zip_start;

         m_pchar_binary__matter_zip_end = pmain->m_pchar_binary__matter_zip_end;

      }

#endif

      if (!m_pacmeapplicationStartup && pmain->m_pacmeapplicationStartup)
      {

         m_pacmeapplicationStartup = pmain->m_pacmeapplicationStartup;

      }



   //if (!estatus)
   //{

   //   return estatus;

   //}

   //m_iPathInstallFolderExeArg = -1;

#ifdef WINDOWS_DESKTOP

   if (!m_hinstanceThis)
   {

      m_hinstanceThis = ::GetModuleHandle(nullptr);

   }

   //m_hPrevInstance = nullptr;

   if (m_nCmdShow == -1000)
   {

      m_nCmdShow = SW_SHOWDEFAULT;

   }

#elif defined(LINUX)

   m_bGtkApp = false;

#endif

   //estatus = 
   on_system_construct();

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


//void apex_main_data::system_construct(int argc, char** argv, char ** envp)
//{
//
//   auto estatus = acme_main_data::system_construct(argc, argv, envp);
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   m_iPathInstallFolderExeArg = -1;
//
//#ifdef WINDOWS_DESKTOP
//
//   m_hinstance = ::GetModuleHandle(nullptr);
//
//   m_hPrevInstance = nullptr;
//
//   m_nCmdShow = SW_SHOWDEFAULT;
//
//#elif defined(LINUX)
//
//   m_bGtkApp = false;
//
//#endif
//
//   estatus = on_system_construct();
//
//   if(!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   return estatus;
//
//}
//
//
//void apex_main_data::system_construct(int argc, wchar_t** argv, wchar_t ** envp)
//{
//
//   auto estatus = acme_main_data::system_construct(argc, argv, envp);
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   m_iPathInstallFolderExeArg = -1;
//
//#ifdef WINDOWS_DESKTOP
//
//   m_hinstance = ::GetModuleHandle(nullptr);
//
//   m_hPrevInstance = nullptr;
//
//   m_nCmdShow = SW_SHOWDEFAULT;
//
//#elif defined(LINUX)
//
//   m_bGtkApp = false;
//
//#endif
//
//   estatus = on_system_construct();
//
//   if(!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   return estatus;
//
//}


void main::on_system_construct()
{

   //return success;

}


#ifdef WINDOWS_DESKTOP


//void apex_main_data::system_construct(hinstance hinstanceThis, hinstance hPrevInstance, char * pCmdLine, i32 nCmdShow)
//{
//
//   auto estatus = acme_main_data::system_construct(pCmdLine);
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   m_hinstance = hinstanceThis;
//
//   m_hPrevInstance = hPrevInstance;
//
//   m_nCmdShow = nCmdShow;
//
//   //__zero(m_mainrunnera);
//
//   estatus = on_system_construct();
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   return estatus;
//
//
//}


#elif defined(_UWP)


void main::system_construct(const ::string_array & straParam)
{

   //m_poslocal = nullptr;

   auto stra = straParam;

   m_argc = __argc;

   m_argv = __argv;

   m_wargv = __wargv;

   //m_pfnNewAuraApplication = nullptr;

   //m_pfnNewAuraLibrary = nullptr;

   //m_poslocal = nullptr;

   m_edisplay = e_display_default;

   //__zero(m_mainrunnera);

   //return ::success;

}


#else


void main::system_construct(const char * pszCommandLine, const ::e_display & edisplay)
{

   m_strCommandLine = pszCommandLine;

   //m_edisplay = windows_show_window_to_edisplay(edisplay, m_eactivation);

   //m_poslocal = nullptr;

   //__zero(m_mainrunnera);

   //auto estatus =
   //
   on_system_construct();

//   if(!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   return estatus;

}


#endif


//void apex_main_data::set_main_struct(const apex_main_struct & mainstruct)
//{
//
//   *((::apex_main_struct*)(this)) = mainstruct;
//
//}


string main::get_arg(int i) const
{

   if (m_wargv)
   {

      return string(m_wargv[i]);

   }
   else if (m_argv)
   {

      return string(m_argv[i]);

   }

   return "";


}


string main::get_env(const char * pszVariableName) const
{

   if (m_wenvp)
   {

      wstring wstrPrefix(pszVariableName);

      wstrPrefix += "=";

      for(auto p = m_wenvp; p != nullptr; p++)
      {

         wstring wstr(*p);

         if(wstr.begins_eat_ci(wstrPrefix))
         {

            return wstr;

         }

      }

      return "";

   }
   else if (m_envp)
   {

      string strPrefix(pszVariableName);

      strPrefix += "=";

      for(auto p = m_envp; p != nullptr; p++)
      {

         string str(*p);

         if(str.begins_eat_ci(strPrefix))
         {

            return str;

         }

      }

      return "";

   }

   return "";

}


bool main::is_console_app() const
{

   return m_bConsole;

}


//
//
//
//// Offloading apex(TBS) from deep stack stuff 2022-02-22 by camilo at 07:18 <3ThomasBorregaardSørensen!!
//#include "framework.h"
//#include "acme/operating_system.h"
//#include "app_core.h"
//#include "acme/platform/system_setup.h"
////#include "apex/platform/static_start.h"
//#include "acme/filesystem/filesystem/acme_directory.h"
//#include "acme/filesystem/filesystem/acme_file.h"
//#include <stdio.h>
//#include <time.h>



CLASS_DECL_ACME bool is_verbose();

CLASS_DECL_ACME int_bool os_init_windowing();
CLASS_DECL_ACME void os_term_windowing();

#ifdef RASPBIAN


#include <sys/types.h>
#include <unistd.h>


#endif


#ifdef LINUX


   #ifndef RASPBIAN


   void sn_start_context();


   #endif


#endif

//
//#ifdef _DEBUG
//
//
//   static bool g_bVerbose = true;
//
//
//#else
//
//
//   static bool g_bVerbose = false;
//
//
//#endif
//

//bool is_verbose()
//{
//
//   return g_bVerbose;
//
//}
//

//void set_verbose(bool bVerbose)
//{
//
//   g_bVerbose = bVerbose;
//
//}


typedef int_bool DEFER_INIT();


typedef DEFER_INIT * PFN_DEFER_INIT;


//void debug_context_object(::object * pobject);


#ifdef __APPLE__


char * ns_get_bundle_identifier();


string apple_get_bundle_identifier();


//string ca2_command_line2();


#endif


#ifdef WINDOWS


#define APP_CORE_BASE_DIR "C:\\ca2\\config\\system"


#else


#undef USE_MISC


#define APP_CORE_BASE_DIR "/::payload/tmp/ca2/config/system"


#endif




//app_core::~app_core()
//{
//
//}


bool main::on_result(const ::e_status & estatus)
{

   if (estatus == ::success)
   {

      return true;

   }

   //if (m_iStatusCount >= APP_CORE_MAXIMUM_STATUS_COUNT)
   //{

   //   m_iTotalStatusCount++;

   //   return false;

   //}

   m_estatusa.add(estatus);

   return false;

}


void main::system_prep()
{

// prelude::defer_call_construct(this);

//#ifdef __APPLE__
//
// if(m_lpCmdLine == nullptr)
// {
//
//    string str = apple_get_bundle_identifier();
//
//    ::str().begins_eat_ci(str, "com.ca2.");
//
//    str.replace(".", "/");
//
//    m_lpCmdLine = ::str().dup("app : app=" + str);
//
// }
//
//#endif

   m_durationStart.Now();

   m_durationAfterApplicationFirstRequest = m_durationStart;

   if (m_psystem->m_pacmefile->exists(::file::path(APP_CORE_BASE_DIR) / "wait_on_beg.txt"))
   {

      sleep(10_s);

   }

   if (m_psystem->m_pacmefile->exists(::file::path(APP_CORE_BASE_DIR) / "beg_debug_box.txt"))
   {

      //debug_box("zzzAPPzzz app", "zzzAPPzzz app", e_message_box_icon_information);

   }

   //os_init_imaging();

//#ifdef

  // os_init_windowing();

   //return true;

}


//extern "C"
//::apex::system * apex_create_apex_system();


//CLASS_DECL_ACME void set_path_install_folder(const char * pszPath);

CLASS_DECL_ACME void set_debug_pointer(void * p);


void main::system_init()
{

   ///// string test (NEW STRING 2019-11-26)
   //{

   //   //string str1 = "\"teste\\\"teste2\"";

   //   //const char * psz = str1;

   //   //string str = ::str().consume_quoted_value(psz);

   //   //output_debug_string(str);

   //}

   //if (m_iPathInstallFolderExeArg >= 0 && m_iPathInstallFolderExeArg < m_argc)
   //{

   //   ::file::path pathModule = get_arg(m_iPathInstallFolderExeArg);

   //   m_psystem->m_pacmedirectory->set_path_install_folder(pathModule.folder(4));

   //}

   //on_command_line();

//   string strAppId;
//
//   string_array stra1;
//
//#ifdef WINDOWS
//
//   {
//
//      auto pwsz = ;
//
//      string strCommandLine(pwsz);
//
//      set_command_line(strCommandLine);
//
//      //stra1 = get_c_args_from_string(strCommandLine);
//
//      /// <summary>
//      /// This no_escape_get_c_args_from_string
//      /// considers the string literally,
//      /// that is, it doesn't parse escape sequences.
//      /// </summary>
//      stra1 = no_escape_get_c_args_from_string(strCommandLine);
//
//   }
//
//#elif defined(ANDROID)
//
//   {
//
//      string strCommandLine(m_strCommandLine);
//
//      stra1 = get_c_args_from_string(strCommandLine);
//
//   }
//
//#else
//
//
//   stra1 = get_c_args(m_argc, m_argv);
//
//#endif
//
//   string_array stra2;
//
//   stra2 = get_c_args_from_string(m_strCommandLine);
//
//   string_array stra3;
//
////#ifdef WINDOWS_DESKTOP
////
////   stra3 = get_c_args_from_string(ca2_command_line((hinstance) m_hinstance));
////
//////#elif defined(__APPLE__)
//////
//////   stra3 =  get_c_args_for_c(ca2_command_line2());
//////
//////#else
//////
//////   stra3 = get_c_args_from_c(ca2_command_line());
////
////#endif
//
//   //string_array stra5;
//
//   //if(m_pszMain)
//   //{
//
//   //   stra5 = get_c_args_from_string(m_pszMain);
//
//   //}
//
//   //string_array stra4;
//
//   //string strCommandLine = merge_colon_args(
//   //   {
//
//   //      stra1, stra2, stra3, stra5
//
//
//   //   });
//
//   set_command_line(strCommandLine);
//
//#if !defined(WINDOWS)
//
//   string strUid;
//
//   get_command_line_param(strUid, strCommandLine, "uid");
//
//   if (strUid.has_char())
//   {
//
//      uid_t uid = atoi(strUid);
//
//      output_error_message("going to seteuid to: " + __string(uid), "going to seteuid", e_message_box_ok);
//
//      if (seteuid(uid) == 0)
//      {
//
//         output_error_message("uid=" + __string(uid), "seteuid success", e_message_box_ok);
//
//      }
//      else
//      {
//
//         int iErr = errno;
//
//         string strError;
//
//         strError.format("errno=%d uid=%d", iErr);
//
//         //message_box(strError, "seteuid failed", e_message_box_icon_exclamation);
//
//      }
//
//   }
//
//#endif
//

   if (!m_bShowApplicationInformation)
   {

      string strShowApplicationInformation;

      if (is_command_line_param_true(strShowApplicationInformation, m_strCommandLine, "show_application_information"))
      {

         m_bShowApplicationInformation = true;

      }

   }

   //string strNoDock;

   //get_command_line_param(strAppId, strCommandLine, "app");

   //if (strAppId.has_char())
   //{

   //   m_strAppId = strAppId;

   //}
   //else if(m_strAppId.has_char())
   //{

   //   strCommandLine += " app=" +m_strAppId;

   //}

   {

      string strPrgName = m_strAppId;

      strPrgName.replace_with(".", "/");

      strPrgName.replace_with("-", "_");

      m_strProgName = "com." + strPrgName;

   }

   //string strDerivedApplication;

   //get_command_line_param(strDerivedApplication, strCommandLine, "derived_application");

   //g_iDerivedApplication = atoi(strDerivedApplication);

//#ifndef CUBE
//
//   defer_load_backbone_libraries(strAppId);
//
//#endif

   //os_init_application();

//   {
//
//   const char * psz = nullptr;
//   const char * psz2 = nullptr;
//
//   int iRef1 = -1;
//   int iRef2 = -1;
//   int iRef3 = -1;
//
//   string strX;
//
//   auto pmetadata = strX.metadata();
//
//   // string test
//   {
//
//      string str("Test");
//
//      psz = str;
//
//      pmetadata = str.metadata();
//
//      set_debug_pointer(pmetadata);
//
//      ASSERT(string::NATURAL_META_DATA::to_data(str.metadata()) == psz);
//
//      string str1;
//
//      str1 = str;
//
//      string str2;
//
//      str2 = str;
//
//      iRef1 = str.metadata()->m_countReference;
//
//      {
//
//         string str3;
//
//         str3 = str2;
//
//         string strA;
//
//         strA = str3;
//
//         iRef2 = str.metadata()->m_countReference;
//
//      }
//
//      iRef3 = str.metadata()->m_countReference;
//
//   }
//
//}

   // psystem = __move_transfer(g_pfn_create_system());

   //psystem = __move_transfer(apex_create_apex_system());

   //auto psystem = get_system()->m_papexsystem;
   auto psystem = get_system();

   if (!psystem)
   {

      return;

      //on_result(error_failed);

      //return false;

   }

//   psystem->common_construct();

   ::set_task(psystem);

   //debug_context_object(psystem);

   psystem->initialize(psystem);

   //set_object(psystem);


   // what could influence time before Main?
   // cold start (never previously called program and its Dlls...)?
   psystem->m_durationMainStart = m_durationStart;

   //xxdebug_box("box1", "box1", e_message_box_icon_information);
//
  // ::file::path pathOutputDebugString = m_psystem->m_pacmedirectory->system() / strAppId / "output_debug_string.txt" ;

   //::file::path pathGlobalOutputDebugString = m_psystem->m_pacmedirectory->config() / "output_debug_string.txt" ;

   //::apex::g_bOutputDebugString = m_psystem->m_pacmefile->exists(pathOutputDebugString)||  m_psystem->m_pacmefile->exists(pathGlobalOutputDebugString);

   //return true;

}




string main::get_command_line()
{

   return m_strCommandLine;

}




//void app_core::defer_load_backbone_libraries(string strAppId)
//{
//
//   if (strAppId.has_char())
//   {
//
//      void * hmodule = nullptr;
//
//      bool bInApp = strAppId.compare_ci("acid") == 0;
//
//      if (!bInApp)
//      {
//
//         bInApp = m_pfnNewAuraApplication != nullptr;
//
//      }
//
//      string strMessage;
//
//      if (!bInApp)
//      {
//
//         string strLibrary = ::future::app_id_to_app_name(strAppId);
//
//         m_plibrary = __new(::acme::library);
//
//         m_plibrary->initialize(psystem);
//
//         m_plibrary->m_strCa2Name = strAppId;
//
//         if (!m_plibrary->open(strLibrary, false, true))
//         {
//
//            output_error_message("failed to open application initialization library (1)");
//
//            return;
//
//         }
//
//         if (!m_plibrary->open_ca2_library(strLibrary))
//         {
//
//            output_error_message("failed to open application initialization library (2)");
//
//            return;
//
//         }
//
//      }
//
//      //PFN_DEFER_INIT pfnDeferInit = nullptr;
//
//      //PFN_DEFER_TERM pfnDeferTerm = nullptr;
//
//      //if (m_plibrary != nullptr || hmodule != nullptr || bInApp)
//      //{
//
//      //   if ((hmodule = __node_library_touch("apex", strMessage)) != nullptr)
//      //   {
//
//      //      pfnDeferInit = (PFN_DEFER_INIT) __node_library_raw_get(hmodule, "defer_apex_init");
//
//      //      pfnDeferTerm = (PFN_DEFER_TERM) __node_library_raw_get(hmodule, "defer_apex_term");
//
//      //   }
//      //   //else if ((hmodule = __node_library_touch("base", strMessage)) != nullptr)
//      //   //{
//
//      //   //   pfnDeferInit = (PFN_DEFER_INIT) __node_library_raw_get(hmodule, "defer_base_init");
//
//      //   //   pfnDeferTerm = (PFN_DEFER_TERM) __node_library_raw_get(hmodule, "defer_base_term");
//
//      //   //}
//      //   //else if ((hmodule = __node_library_touch("axis", strMessage)) != nullptr)
//      //   //{
//
//      //   //   pfnDeferInit = (PFN_DEFER_INIT) __node_library_raw_get(hmodule, "defer_axis_init");
//
//      //   //   pfnDeferTerm = (PFN_DEFER_TERM) __node_library_raw_get(hmodule, "defer_axis_term");
//
//      //   //}
//      //   else if ((hmodule = __node_library_touch("apex", strMessage)) != nullptr)
//      //   {
//
//      //      pfnDeferInit = (PFN_DEFER_INIT) __node_library_raw_get(hmodule, "defer_apex_init");
//
//      //      pfnDeferTerm = (PFN_DEFER_TERM) __node_library_raw_get(hmodule, "defer_apex_term");
//
//      //   }
//
//      //}
//
//      //if (pfnDeferInit != nullptr)
//      //{
//
//      //   if (pfnDeferTerm == nullptr)
//      //   {
//
//      //      output_error_message("Missing corresponding defer_*_term for the defer_*_init backbone library." + e_message_box_icon_error);
//
//      //      on_result(error_failed);
//
//      //   }
//      //   else
//      //   {
//
//      //      m_pfnDeferTerm = pfnDeferTerm;
//
//      //   }
//
//      //}
//
//      //if(!::apex_level::defer_init(pfnDeferInit))
//      //{
//
//      //   on_result(error_failed);
//
//      //}
//
//   }
//
//}
//
//
//void app_core::defer_unload_backbone_libraries()
//{
//
//   if (m_pfnDeferTerm != nullptr)
//   {
//
//      (*m_pfnDeferTerm)();
//
//   }
//
//}


void main::system_end()
{

   //os_term_application();

   //os_term_windowing();

   //os_term_imaging();

//   if (m_bShowApplicationInformation)
//   {
//
//      char szEllapsed[MAX_PATH * 2];
//
//      ansi_count_copy(szEllapsed, ::file::path(APP_CORE_BASE_DIR) / "show_elapsed.txt", sizeof(szEllapsed));
//
//      auto tickEnd = ::duration::now();
//
//      char szTimeMessage[2108];
//
//      ::time_t timet = ::time(nullptr);
//
//      tm t;
//
//#ifdef WINDOWS
//
//      errno_t err = _localtime64_s(&t, &timet);
//
//#else
//
//      localtime_r(&timet, &t);
//
//#endif
//
//      if (is_verbose())
//      {
//
//         char szTime[2048];
//
//         sprintf(szTime, "%04d-%02d-%02d %02d:%02d:%02d", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
//
//         sprintf(szTimeMessage, "\n\n\n---------------------------------------------------------------------------------------------\n|\n|\n|  Just After First papp Request Completion %"  PRId64 " ms", (m_durationAfterApplicationFirstRequest - m_durationStart).m_i);
//         ::output_debug_string(szTimeMessage);
//         printf("%s", szTimeMessage);
//
//         ::duration i::durationsTotal = tickEnd - m_durationStart;
//
//         sprintf(szTimeMessage, "\n|  Total Elapsed Time %" PRId64 " ms", i::durationsTotal.m_i);
//         ::output_debug_string(szTimeMessage);
//         printf("%s", szTimeMessage);
//
//         int i::durations = i::durationsTotal.m_i % 1000;
//         int iSecondsTotal = (int)(i::durationsTotal.m_i / 1000);
//         int iSeconds = iSecondsTotal % 60;
//         int iMinutesTotal = iSecondsTotal / 60;
//         int iMinutes = iMinutesTotal % 60;
//         int iHoursTotal = iMinutesTotal / 60;
//         int iHours = iHoursTotal % 24;
//         int iDays = iHoursTotal / 24;
//
//         if (iDays > 0)
//         {
//
//            sprintf(szTimeMessage, "\n|  Total Elapsed Time %d days %02d:%02d:%02d %03d ms", iDays, iHours, iMinutes, iSeconds, i::durations);
//
//         }
//         else if (iHours > 0)
//         {
//
//            sprintf(szTimeMessage, "\n|  Total Elapsed Time %02d:%02d:%02d %03d ms", iHours, iMinutes, iSeconds, i::durations);
//
//         }
//         else if (iMinutes > 0)
//         {
//
//            sprintf(szTimeMessage, "\n|  Total Elapsed Time %02d:%02d %03d ms", iMinutes, iSeconds, i::durations);
//
//         }
//         else
//         {
//
//            sprintf(szTimeMessage, "\n|  Total Elapsed Time %02ds %03d ms", iSeconds, i::durations);
//
//         }
//
//         ::output_debug_string(szTimeMessage);
//         printf("%s", szTimeMessage);
//
//         sprintf(szTimeMessage, "\n|");
//         ::output_debug_string(szTimeMessage);
//         printf("%s", szTimeMessage);
//
//         sprintf(szTimeMessage, "\n|  %s", szTime);
//         ::output_debug_string(szTimeMessage);
//         printf("%s", szTimeMessage);
//
//         sprintf(szTimeMessage, "\n|");
//         ::output_debug_string(szTimeMessage);
//         printf("%s", szTimeMessage);
//
//         sprintf(szTimeMessage, "\n|");
//         ::output_debug_string(szTimeMessage);
//         printf("%s", szTimeMessage);
//
//         sprintf(szTimeMessage, "\n-------------------------------------------------------------------------------------------- - ");
//         ::output_debug_string(szTimeMessage);
//         printf("%s", szTimeMessage);
//
//         sprintf(szTimeMessage, "\n");
//         ::output_debug_string(szTimeMessage);
//         printf("%s", szTimeMessage);
//
//         sprintf(szTimeMessage, "\n");
//         ::output_debug_string(szTimeMessage);
//         printf("%s", szTimeMessage);
//
//         sprintf(szTimeMessage, "\n");
//         ::output_debug_string(szTimeMessage);
//         printf("%s", szTimeMessage);
//
//         sprintf(szTimeMessage, "\n");
//         ::output_debug_string(szTimeMessage);
//         printf("%s", szTimeMessage);
//
//         if (file_exists_raw(szEllapsed))
//         {
//
//            char szUTCTime[2048];
//
//            time_t rawtime;
//
//            struct tm* g;
//
//            time(&rawtime);
//
//            g = gmtime(&rawtime);
//
//            sprintf(szUTCTime, "%04d-%02d-%02d %02d:%02d:%02d UTC", g->tm_year + 1900, g->tm_mon, g->tm_mday, g->tm_hour, g->tm_min, g->tm_sec);
//
//            char szTimeMessage1[2048];
//
//            sprintf(szTimeMessage1, " Just After First papp Request Completion %" PRId64 " ms", (m_durationAfterApplicationFirstRequest - m_durationStart).m_i);
//
//            if (file_length_raw(szEllapsed) > 0)
//            {
//
//               file_add_contents_raw(szEllapsed, "\n");
//
//            }
//
//            file_add_contents_raw(szEllapsed, szUTCTime);
//
//            file_add_contents_raw(szEllapsed, szTimeMessage1);
//
//            file_add_contents_raw(szEllapsed, "\n");
//
//            char szTimeMessage2[2048];
//
//            sprintf(szTimeMessage2, " Total Elapsed Time " __prtick, (tickEnd - m_durationStart).m_i);
//
//            file_add_contents_raw(szEllapsed, szUTCTime);
//
//            file_add_contents_raw(szEllapsed, szTimeMessage2);
//
//         }
//
//      }
//
//   }

   //defer_unload_backbone_libraries();

#ifdef __MCRTDBG

   _CrtDumpMemoryLeaks();

#endif

}


//typedef int_bool DEFER_INIT();


//typedef DEFER_INIT * PFN_DEFER_INIT;



//CLASS_DECL_APEX long apex_prefix(::apex::system * psystem)
//{
//
//   //pmaindata->m_pappcore = __new(app_core(pmaindata));
//
//   if (!psystem->system_prep())
//   {
//
//      return psystem->m_iTotalStatusCount;
//
//   }
//
//   if (psystem->system_proc())
//   {
//
//      psystem->system_pre_run();
//
//   }
//
//   return 0;
//
//}


//CLASS_DECL_APEX long apex_fork(::apex::system * psystem, PFN_NEW_APEX_APPLICATION pfnNewAuraApplication)
//{
//
//   //pmaindata->m_pappcore = __new(app_core(pmaindata));
//
//   if (!psystem->system_prep())
//   {
//
//      return psystem->m_iTotalStatusCount;
//
//   }
//
//   if (psystem->system_init())
//   {
//
//      psystem->system_pre_run();
//
//      psystem->fork([&]()
//      {
//
//            psystem->run();
//
//      });
//
//   }
//
//   return 0;
//
//}


//CLASS_DECL_APEX long apex_apex(::apex::system * psystem)
//{
//
//   if (!psystem->system_prep())
//   {
//
//      return psystem->m_iTotalStatusCount;
//
//   }
//
//   psystem->system_init();
//
//   return psystem->m_iTotalStatusCount;
//
//}


struct heap_test_struct :
   virtual public object
{

   byte m_ucha[1024];

};

typedef size_t FN_GET_STRING(char * psz, size_t s);


typedef FN_GET_STRING * PFN_GET_STRING;


#if defined(LINUX)


//void app_core::system_main()
//{
//
//   bool bOk = system_ini();
//
//   if(bOk)
//   {
//
//      //bOk = beg();
//
//      //if(bOk)
//      //{
//
//         system_run();
//
//      //}
//
//   }
//
//   system_end();
//
//}
//

#elif !defined(ANDROID)


void main::system_proc()
{

   //return ::error_failed;

   //::e_status estatus = system_proc();

   //if(estatus.succeeded())
   //{

   //   system_main();

   //}

   //system_end();

}


#endif


//void app_core::system_call()
//{
//
//   ::e_status estatus = error_failed;
//
//   try
//   {
//
//      estatus = system_proc();
//
//   }
//   catch (...)
//   {
//
//      output_debug_string("exception:app_core:run");
//
//      estatus = error_exception;
//
//   }
//
//   return estatus;
//
//}


//bool main::has_apex_application_factory() const
//{
//
//   if (m_pfnnewmatterApplication)
//   {
//
//      return true;
//
//   }
//
//   //if (m_pfnNewAuraLibrary)
//   //{
//
//   //   return true;
//
//   //}
//
//   return false;
//
//}
//


#ifdef __APPLE__




#elif defined(_UWP)



#elif defined(LINUX)


//// LOOK AT LINUX_MAIN.Cpp

//// defined at linux_main.cpp


#elif defined(ANDROID)


// LOOK AT ANDROID_MAIN.Cpp

// defined at android_main.cpp


#else


//::u32 app_core::system_main()
//{
//
//   ::e_status estatus = psystem->__thread_procedure();
//
//   return estatus;
//
//}


#endif


//::pointer<::acme::application>main::new_app()
//{
//
//   //if(::acme::application::g_p)
//   //{
//
//   //   return ::acme::application::g_p;
//
//   //}
//
//   if (!m_pfnnewmatterApplication)
//   {
//
//      return nullptr;
//
//   }
//
//   ::pointer<::acme::application>papp;
//
//   papp = m_pfnnewmatterApplication();
//
//   if (papp.is_null())
//   {
//
//      return nullptr;
//
//   }
//
//   return papp;
//
//}




void main::initialize_application(::acme::application *papp, ::object * pobject)
{

   //auto estatus = 
   
   papp->initialize(pobject);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return ::success;

}

//static apex_level * s_plevel = NULL;
//
//
//apex_level::apex_level(enum_level elevel, PFN_DEFER_INIT pfnDeferInit) :
//   m_elevel(elevel),
//   m_pfnDeferInit(pfnDeferInit),
//   m_plevelNext(s_plevel)
//{
//
//   s_plevel = this;
//
//}
//
//
//apex_level * apex_level::get_maximum_level()
//{
//
//#ifdef LINUX
//
//return nullptr;
//
//#endif
//
//try
//{
//   if(s_plevel == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   apex_level * plevel = s_plevel;
//
//   apex_level * plevelMax = plevel;
//
//   while(true)
//   {
//
//      plevel = plevel->m_plevelNext;
//
//      if(plevel == nullptr)
//      {
//
//         break;
//
//      }
//
//      if(plevel->m_elevel > plevelMax->m_elevel)
//      {
//
//         plevelMax = plevel;
//
//      }
//
//   }
//
//   return plevelMax;
//
//   }
//   catch(...)
//   {
//
//   }
//
//   return nullptr;
//}
//
//
//apex_level * apex_level::find_level(PFN_DEFER_INIT pfnDeferInit)
//{
//
//   if(s_plevel == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   apex_level * plevel = s_plevel;
//
//   while(plevel != nullptr)
//   {
//
//      if(plevel->m_pfnDeferInit > pfnDeferInit)
//      {
//
//         return plevel;
//
//      }
//
//      plevel = plevel->m_plevelNext;
//
//   }
//
//   return nullptr;
//
//}
//
//
//bool apex_level::defer_init()
//{
//
//   auto plevel = get_maximum_level();
//
//   if(plevel == nullptr)
//   {
//
//      return false;
//
//   }
//
//   return plevel->m_pfnDeferInit();
//
//}
//
//
//bool apex_level::defer_init(PFN_DEFER_INIT pfnDeferInit)
//{
//
//   auto plevel = get_maximum_level();
//
//   if(plevel == nullptr)
//   {
//
//      if(pfnDeferInit != nullptr)
//      {
//
//         return pfnDeferInit();
//
//      }
//      else
//      {
//
//         return true;
//
//      }
//
//   }
//   else if(pfnDeferInit == nullptr)
//   {
//
//      if(plevel->m_pfnDeferInit != nullptr)
//      {
//
//         return plevel->m_pfnDeferInit();
//
//      }
//      else
//      {
//
//         return true;
//
//      }
//
//   }
//   else
//   {
//
//      auto plevelFind = find_level(pfnDeferInit);
//
//      if(plevelFind == nullptr)
//      {
//
//         bool bOk1 = false;
//
//         bOk1 = pfnDeferInit();
//
//         bool bOk2 = true;
//
//         if(plevel->m_pfnDeferInit != nullptr)
//         {
//
//            bOk2 = plevel->m_pfnDeferInit();
//
//         }
//
//         return bOk1 && bOk2;
//
//      }
//      else if(plevelFind->m_elevel > plevel->m_elevel)
//      {
//
//         return plevelFind->m_pfnDeferInit();
//
//      }
//      else
//      {
//
//         return plevel->m_pfnDeferInit();
//
//      }
//
//   }
//
//   return true;
//
//}


//
//
//static const char * g_pszCubeAppId = nullptr;
//
//
//const char * get_cube_app_id()
//{
//
//   return g_pszCubeAppId;
//
//}
//
//
//void cube_set_app_id(const char * pszAppId)
//{
//
//   g_pszCubeAppId = pszAppId;
//
//}
//
////
////apex_apex::apex_apex()
////{
////
////   if (!defer_apex_init())
////   {
////
////      throw raw_fail();
////
////   }
////
////}
//
////
////apex_apex::~apex_apex()
////{
////
////   defer_apex_term();
////
////}
////
//
//


#if !defined(WINDOWS)


::string quote_if_has_space(const char *psz)
{

   if(strchr(psz, ' ') != nullptr)
   {

      return "\"" + string(psz) + "\"";

   }
   else
   {

      return psz;

   }

}


::string get_command_line()
{

   ::string str;

   for(int i = 0; i < g_argc; i++)
   {

      if (str.has_char())
      {

         str += " ";

      }

      str += quote_if_has_space(g_argv[i]);

   }

   return str;

}


#endif



