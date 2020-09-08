#include "framework.h"
#include "app_core.h"
#include "static_setup.h"
#include "acme/os/_os.h"
#include "acme/node/_node.h"
#include "acme/platform/static_start.h"
#include <stdio.h>
#include <time.h>


//extern string_map < __pointer(::acme::library) >* g_pmapLibrary ;
//extern string_map < PFN_NEW_ace_LIBRARY >* g_pmapNewaceLibrary;
//extern ::mutex* &::get_context_system()->m_mutexLibrary;


#ifdef RASPBIAN


#include <sys/types.h>
#include <unistd.h>


#endif


#ifdef LINUX


   #ifndef RASPBIAN


   void sn_start_context();


   #endif


#endif


#ifdef DEBUG


   static bool g_bVerbose = true;


#else


   static bool g_bVerbose = false;


#endif


bool is_verbose()
{

   return g_bVerbose;

}


void set_verbose(bool bVerbose)
{

   g_bVerbose = bVerbose;

}


extern ::app_core * g_pappcore;


//extern bool g_bOutputDebugString;


typedef int_bool DEFER_INIT();


typedef DEFER_INIT * PFN_DEFER_INIT;


void debug_context_object(::generic * pobject);


#ifdef __APPLE__


char * ns_get_bundle_identifier();


string apple_get_bundle_identifier();


string ca2_command_line2();


#endif


#ifdef WINDOWS


#define APP_CORE_BASE_DIR "C:\\ca2\\config\\system"


#else


#undef USE_MISC


#define APP_CORE_BASE_DIR "/var/tmp/ca2/config/system"


#endif



//app_core::app_core(ace_main_data* pdata)
app_core::app_core()
{

   //m_pmaindata = pdata;

   //m_pappcore = this;

   if(!g_pappcore)
   {

      g_pappcore = this;

   }

   #ifndef WINDOWS

   ::unsetenv("LD_LIBRARY_PATH");

   #endif

   m_pfnDeferTerm = nullptr;

   m_iStatusCount = 0;

   m_iTotalStatusCount = 0;



}


app_core::~app_core()
{

}


bool app_core::on_result(const ::estatus & estatus)
{

   if (estatus == ::success)
   {

      return true;

   }

   if (m_iStatusCount >= APP_CORE_MAXIMUM_STATUS_COUNT)
   {

      m_iTotalStatusCount++;

      return false;

   }

   m_estatusa[m_iStatusCount] = estatus;

   m_iStatusCount++;

   m_iTotalStatusCount = m_iStatusCount;

   return false;

}


::estatus app_core::system_prep()
{

// prelude::defer_call_construct(this);

//#ifdef __APPLE__
//
// if(m_lpCmdLine == nullptr)
// {
//
//    string str = apple_get_bundle_identifier();
//
//    ::str::begins_eat_ci(str, "com.ca2.");
//
//    str.replace(".", "/");
//
//    m_lpCmdLine = ::str::dup("app : app=" + str);
//
// }
//
//#endif

   m_tickStart = ::first_tick();

   m_tickAfterApplicationFirstRequest = m_tickStart;

   if (file_exists(::file::path(APP_CORE_BASE_DIR) / "wait_on_beg.txt"))
   {

      Sleep(10000);

   }

   if (file_exists(::file::path(APP_CORE_BASE_DIR) / "beg_debug_box.txt"))
   {

      //debug_box("zzzAPPzzz app", "zzzAPPzzz app", MB_ICONINFORMATION);

   }

   //os_init_imaging();

   os_init_windowing();

   return true;

}


extern "C"
::acme::system * ace_create_ace_system();


extern ::file::path * g_ppathInstallFolder;


CLASS_DECL_ACME void set_debug_pointer(void * p);


::estatus app_core::system_init()
{

   /// string test (NEW STRING 2019-11-26)
   {

      //string str1 = "\"teste\\\"teste2\"";

      //const char * psz = str1;

      //string str = str::consume_quoted_value(psz);

      //output_debug_string(str);

   }

   if (m_iPathInstallFolderExeArg >= 0 && m_iPathInstallFolderExeArg < m_argc)
   {

      ::file::path pathModule = get_arg(m_iPathInstallFolderExeArg);

      g_ppathInstallFolder = new ::file::path(pathModule.folder(4));

   }

   string strAppId;

   string_array stra1;

#ifdef WINDOWS

   {

      auto pwsz = ::GetCommandLineW();

      string strCommandLine(pwsz);

      stra1 = get_c_args_from_string(strCommandLine);

   }

#elif defined(ANDROID)

   {

      string strCommandLine(m_strCommandLine);

      stra1 = get_c_args_from_string(strCommandLine);

   }

#else


   stra1 = get_c_args(m_argc, m_argv);

#endif

   string_array stra2;

   stra2 = get_c_args_from_string(m_strCommandLine);

   string_array stra3;

#ifdef WINDOWS_DESKTOP

   stra3 = get_c_args_from_string(ca2_command_line(m_hinstance));

#elif defined(__APPLE__)

   stra3 =  get_c_args_for_c(ca2_command_line2());

#else

   stra3 = get_c_args_from_c(ca2_command_line());

#endif

   string_array stra5;

   if(m_pszMain)
   {

      stra5 = get_c_args_from_string(m_pszMain);

   }

   string_array stra4;

   string strCommandLine = merge_colon_args(
      {

         stra1, stra2, stra3, stra5


      });

   set_command_line(strCommandLine);

#if !defined(WINDOWS)

   string strUid;

   get_command_line_param(strUid, strCommandLine, "uid");

   if (strUid.has_char())
   {

      uid_t uid = atoi(strUid);

      os_message_box(nullptr, "going to seteuid to: " + __str(uid), "going to seteuid", MB_OK);

      if (seteuid(uid) == 0)
      {

         os_message_box(nullptr, "uid=" + __str(uid), "seteuid success", MB_OK);

      }
      else
      {

         int iErr = errno;

         string strError;

         strError.Format("errno=%d uid=%d", iErr);

         os_message_box(nullptr, strError, "seteuid failed", MB_ICONEXCLAMATION);

      }

   }

#endif

   if (!m_bShowApplicationInformation)
   {

      string strShowApplicationInformation;

      if (is_command_line_param_true(strShowApplicationInformation, strCommandLine, "show_application_information"))
      {

         m_bShowApplicationInformation = true;

      }

   }

   string strNoDock;

   get_command_line_param(strAppId, strCommandLine, "app");

   if (strAppId.has_char())
   {

      m_strAppId = strAppId;

   }
   else if(m_strAppId.has_char())
   {

      strCommandLine += " app=" +m_strAppId;

   }


   {

      string strPrgName = m_strAppId;

      strPrgName.replace("/", ".");

      strPrgName.replace("_", "-");

      m_strProgName = "cc.ca2." + strPrgName;

   }

   string strDerivedApplication;

   get_command_line_param(strDerivedApplication, strCommandLine, "derived_application");

   //g_iDerivedApplication = atoi(strDerivedApplication);

//#ifndef CUBE
//
//   defer_load_backbone_libraries(strAppId);
//
//#endif

   os_init_application();

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

   // get_context_system() = __move_transfer(g_pfn_create_system());

   //get_context_system() = __move_transfer(ace_create_ace_system());

   if (!get_context_system())
   {

      on_result(error_failed);

      return false;

   }

//   get_context_system()->common_construct();

   ::set_thread(get_context_system());

   debug_context_object(get_context_system());

   get_context_system()->initialize(get_context_system());

   //set_context_object(get_context_system());

   auto pcreate = __new(::create(get_context_system()));

   pcreate->m_strAppId = strAppId;

   pcreate->m_pcommandline = __new(command_line(get_context_system(), strCommandLine));

   //get_context_system()->get_command()->add_create(pcreate);

   get_context_system()->add_create(pcreate);

   // what could influence time before Main?
   // cold start (never previously called program and its Dlls...)?
   get_context_system()->m_tickMainStart = m_tickStart;

   //xxdebug_box("box1", "box1", MB_ICONINFORMATION);

   ::file::path pathOutputDebugString = ::dir::system() / strAppId / "output_debug_string.txt" ;

   ::file::path pathGlobalOutputDebugString = ::dir::config() / "output_debug_string.txt" ;

   ::acme::g_bOutputDebugString = file_exists(pathOutputDebugString)||  file_exists(pathGlobalOutputDebugString);

   return true;

}


string app_core::get_command_line()
{

   return m_strCommandLine;

}


void app_core::set_command_line(const char * psz)
{

   m_strCommandLine = psz;

   ::file::path pathFolder = ::dir::ca2roaming() / "program";

   string strAppId = get_command_line_param(psz, "app");

   if (strAppId.has_char())
   {

      pathFolder /= strAppId;

      ::file::path path = pathFolder / "last_command_line.txt";

      file_put_contents_dup(path, get_command_line());

      ::file::path pathExecutable = consume_param(psz, nullptr);

      string strAppTitle = executable_title_from_appid(strAppId);

      path = pathFolder / "last_executable.txt";

      if (file_is_equal_path_dup(pathExecutable.title(), strAppTitle))
      {

         file_put_contents_dup(path, pathExecutable);

      }

   }

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
//         bInApp = m_pfnNewaceApplication != nullptr;
//
//      }
//
//      string strMessage;
//
//      if (!bInApp)
//      {
//
//         string strLibrary = ::process::app_id_to_app_name(strAppId);
//
//         m_plibrary = __new(::acme::library);
//
//         m_plibrary->initialize(get_context_system());
//
//         m_plibrary->m_strCa2Name = strAppId;
//
//         if (!m_plibrary->open(strLibrary, false, true))
//         {
//
//            message_box("failed to open application initialization library (1)");
//
//            return;
//
//         }
//
//         if (!m_plibrary->open_ca2_library(strLibrary))
//         {
//
//            message_box("failed to open application initialization library (2)");
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
//      //   if ((hmodule = __node_library_touch("acme", strMessage)) != nullptr)
//      //   {
//
//      //      pfnDeferInit = (PFN_DEFER_INIT) __node_library_raw_get(hmodule, "defer_ace_init");
//
//      //      pfnDeferTerm = (PFN_DEFER_TERM) __node_library_raw_get(hmodule, "defer_ace_term");
//
//      //   }
//      //   //else if ((hmodule = __node_library_touch("acme", strMessage)) != nullptr)
//      //   //{
//
//      //   //   pfnDeferInit = (PFN_DEFER_INIT) __node_library_raw_get(hmodule, "defer_base_init");
//
//      //   //   pfnDeferTerm = (PFN_DEFER_TERM) __node_library_raw_get(hmodule, "defer_base_term");
//
//      //   //}
//      //   //else if ((hmodule = __node_library_touch("acme", strMessage)) != nullptr)
//      //   //{
//
//      //   //   pfnDeferInit = (PFN_DEFER_INIT) __node_library_raw_get(hmodule, "defer_axis_init");
//
//      //   //   pfnDeferTerm = (PFN_DEFER_TERM) __node_library_raw_get(hmodule, "defer_axis_term");
//
//      //   //}
//      //   else if ((hmodule = __node_library_touch("acme", strMessage)) != nullptr)
//      //   {
//
//      //      pfnDeferInit = (PFN_DEFER_INIT) __node_library_raw_get(hmodule, "defer_ace_init");
//
//      //      pfnDeferTerm = (PFN_DEFER_TERM) __node_library_raw_get(hmodule, "defer_ace_term");
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
//      //      message_box("Missing corresponding defer_*_term for the defer_*_init backbone library." + message_box_icon_error);
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
//      //if(!::ace_level::defer_init(pfnDeferInit))
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


void app_core::system_end()
{

   os_term_application();

   os_term_windowing();

   //os_term_imaging();

   if (m_bShowApplicationInformation)
   {

      char szEllapsed[MAX_PATH * 2];

      ansi_count_copy(szEllapsed, ::file::path(APP_CORE_BASE_DIR) / "show_elapsed.txt", sizeof(szEllapsed));

      auto tickEnd = ::tick::now();

      char szTimeMessage[2108];

      ::time_t timet = ::time(nullptr);

      tm t;

#ifdef WINDOWS

      errno_t err = _localtime64_s(&t, &timet);

#else

      localtime_r(&timet, &t);

#endif

      if (is_verbose())
      {

         char szTime[2048];

         sprintf(szTime, "%04d-%02d-%02d %02d:%02d:%02d", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

         sprintf(szTimeMessage, "\n\n\n---------------------------------------------------------------------------------------------\n|\n|\n|  Just After First Application Request Completion %"  PRId64 " ms", (m_tickAfterApplicationFirstRequest - m_tickStart).m_i);
         ::output_debug_string(szTimeMessage);
         printf("%s", szTimeMessage);

         tick iMillisecondsTotal = tickEnd - m_tickStart;

         sprintf(szTimeMessage, "\n|  Total Elapsed Time %" PRId64 " ms", iMillisecondsTotal.m_i);
         ::output_debug_string(szTimeMessage);
         printf("%s", szTimeMessage);

         int iMilliseconds = iMillisecondsTotal.m_i % 1000;
         int iSecondsTotal = (int)(iMillisecondsTotal.m_i / 1000);
         int iSeconds = iSecondsTotal % 60;
         int iMinutesTotal = iSecondsTotal / 60;
         int iMinutes = iMinutesTotal % 60;
         int iHoursTotal = iMinutesTotal / 60;
         int iHours = iHoursTotal % 24;
         int iDays = iHoursTotal / 24;

         if (iDays > 0)
         {

            sprintf(szTimeMessage, "\n|  Total Elapsed Time %d days %02d:%02d:%02d %03d ms", iDays, iHours, iMinutes, iSeconds, iMilliseconds);

         }
         else if (iHours > 0)
         {

            sprintf(szTimeMessage, "\n|  Total Elapsed Time %02d:%02d:%02d %03d ms", iHours, iMinutes, iSeconds, iMilliseconds);

         }
         else if (iMinutes > 0)
         {

            sprintf(szTimeMessage, "\n|  Total Elapsed Time %02d:%02d %03d ms", iMinutes, iSeconds, iMilliseconds);

         }
         else
         {

            sprintf(szTimeMessage, "\n|  Total Elapsed Time %02ds %03d ms", iSeconds, iMilliseconds);

         }

         ::output_debug_string(szTimeMessage);
         printf("%s", szTimeMessage);

         sprintf(szTimeMessage, "\n|");
         ::output_debug_string(szTimeMessage);
         printf("%s", szTimeMessage);

         sprintf(szTimeMessage, "\n|  %s", szTime);
         ::output_debug_string(szTimeMessage);
         printf("%s", szTimeMessage);

         sprintf(szTimeMessage, "\n|");
         ::output_debug_string(szTimeMessage);
         printf("%s", szTimeMessage);

         sprintf(szTimeMessage, "\n|");
         ::output_debug_string(szTimeMessage);
         printf("%s", szTimeMessage);

         sprintf(szTimeMessage, "\n-------------------------------------------------------------------------------------------- - ");
         ::output_debug_string(szTimeMessage);
         printf("%s", szTimeMessage);

         sprintf(szTimeMessage, "\n");
         ::output_debug_string(szTimeMessage);
         printf("%s", szTimeMessage);

         sprintf(szTimeMessage, "\n");
         ::output_debug_string(szTimeMessage);
         printf("%s", szTimeMessage);

         sprintf(szTimeMessage, "\n");
         ::output_debug_string(szTimeMessage);
         printf("%s", szTimeMessage);

         sprintf(szTimeMessage, "\n");
         ::output_debug_string(szTimeMessage);
         printf("%s", szTimeMessage);

         if (file_exists_raw(szEllapsed))
         {

            char szUTCTime[2048];

            time_t rawtime;

            struct tm* g;

            time(&rawtime);

            g = gmtime(&rawtime);

            sprintf(szUTCTime, "%04d-%02d-%02d %02d:%02d:%02d UTC", g->tm_year + 1900, g->tm_mon, g->tm_mday, g->tm_hour, g->tm_min, g->tm_sec);

            char szTimeMessage1[2048];

            sprintf(szTimeMessage1, " Just After First Application Request Completion %" PRId64 " ms", (m_tickAfterApplicationFirstRequest - m_tickStart).m_i);

            if (file_length_raw(szEllapsed) > 0)
            {

               file_add_contents_raw(szEllapsed, "\n");

            }

            file_add_contents_raw(szEllapsed, szUTCTime);

            file_add_contents_raw(szEllapsed, szTimeMessage1);

            file_add_contents_raw(szEllapsed, "\n");

            char szTimeMessage2[2048];

            sprintf(szTimeMessage2, " Total Elapsed Time " __prtick, (tickEnd - m_tickStart).m_i);

            file_add_contents_raw(szEllapsed, szUTCTime);

            file_add_contents_raw(szEllapsed, szTimeMessage2);

         }

      }

   }

   //defer_unload_backbone_libraries();

#ifdef __MCRTDBG

   _CrtDumpMemoryLeaks();

#endif

}


typedef int_bool DEFER_INIT();


typedef DEFER_INIT * PFN_DEFER_INIT;


//CLASS_DECL_ACME int ace_entry_point(int argc, char * argv[], const char * pszMainAppId)
//{
//
//   int iResult = 0;
//
//   {
//
//      ace_main_struct ace_main_struct = {};
//
//      ace_main_struct.m_bConsole = false;
//      ace_main_struct.m_bDraw2d = true;
//      ace_main_struct.m_bUser = true;
//      ace_main_struct.m_bUserEx = true;
//
//      auto psystem = __new(::acme::system());
//
//      psystem->system_construct(argc, argv);
//
//      psystem->m_strAppId = pszMainAppId;
//
//      iResult = (int) ::ace_ace(psystem);
//
//   }
//
//   return iResult;
//
//}


//CLASS_DECL_ACME long ace_prefix(::acme::system * psystem)
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


//CLASS_DECL_ACME long ace_fork(::acme::system * psystem, PFN_NEW_ace_APPLICATION pfnNewaceApplication)
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


//CLASS_DECL_ACME long ace_ace(::acme::system * psystem)
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
   virtual public generic
{

   byte m_ucha[1024];

};



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


::estatus app_core::system_proc()
{

   return ::error_failed;

   //::estatus estatus = system_proc();

   //if(estatus)
   //{

   //   system_main();

   //}

   //system_end();

}


#endif


//::estatus app_core::system_call()
//{
//
//   ::estatus estatus = error_failed;
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


bool app_core::has_ace_application_factory() const
{

   if (m_pfnNewaceApplication)
   {

      return true;

   }

   //if (m_pfnNewaceLibrary)
   //{

   //   return true;

   //}

   return false;

}


//::estatus app_core::system_pre_run()
//{
//
//   if (m_pmainstruct && m_pmainstruct->m_bConsole)
//   {
//
//      return get_context_system()->inline_init();
//
//   }
//
//   return ::success;
//
//}
//


//#if !defined(LINUX)
//
//
//::estatus app_core::system_start()
//{
//
//   ::estatus estatus = system_pre_run();
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   get_context_system()->add_ref(OBJ_REF_DBG_THIS);
//
//   if (m_pmainstruct && m_pmainstruct->m_bConsole)
//   {
//
//      get_context_system()->get_context_session()->set_context_app(get_context_system()->m_papplicationStartup);
//
//      get_context_system()->set_context_app(get_context_system()->m_papplicationStartup);
//
//      get_context_system()->get_context_session()->set_context(get_context_system()->m_papplicationStartup);
//
//      get_context_system()->set_context(get_context_system()->m_papplicationStartup);
//
//   }
//
//   return estatus;
//
//}
//
//
//#endif



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
//   ::estatus estatus = get_context_system()->__thread_proc();
//
//   return estatus;
//
//}


#endif


__result(::acme::application) app_core::get_new_application(::generic* pobjectContext)
{

   if (!m_pfnNewaceApplication)
   {

      return nullptr;

   }

   __pointer(::acme::application) papp;

   papp = m_pfnNewaceApplication();

   if (papp.is_null())
   {

      return nullptr;

   }

   auto estatus = papp->initialize(pobjectContext);

   if (!estatus)
   {

      return estatus;

   }

   return papp;

}


__result(::acme::application) app_core::get_new_application(::generic* pobjectContext, const char* pszAppId)
{

   __pointer(::acme::application) papp;

   string strAppId = pszAppId;

   sync_lock sl(&::get_context_system()->m_mutexLibrary);

   __pointer(::acme::library)& plibrary = ::get_context_system()->m_mapLibrary[strAppId];

   if (papp)
   {

      if (!plibrary)
      {

         plibrary = new ::acme::library();

         plibrary->m_strName = "";

      }

   }
   else
   {

      auto psetup = static_setup::get_first(::static_setup::flag_application, strAppId);

      if (psetup)
      {

         papp = psetup->create_new_application();

         if (papp)
         {

            papp->initialize(get_context_system());

            strAppId = papp->m_strAppId;

         }

      }

      if (!papp)
      {

         if (!plibrary)
         {

            if (strAppId.is_empty())
            {

               papp = get_context_system()->__create < ::acme::application > ();

               *((::ace_main_struct*)papp) = *((::ace_main_struct*)this);

            }

         }

      }

      if (!papp)
      {

         if (plibrary)
         {

            plibrary->initialize_ace_library(pobjectContext, 0, nullptr);

         }
         else
         {

            //plibrary = __new(::acme::library);

            //plibrary->initialize_ace_library(pobjectContext, 0, nullptr);

            string strLibrary = strAppId;

            strLibrary.replace("/", "_");

            strLibrary.replace("-", "_");

            if (is_verbose())
            {

               ::output_debug_string("\n\n::acme::session::get_new_application assembled library path " + strLibrary + "\n\n");

            }

            plibrary = get_context_system()->get_library(strLibrary);

            if (!plibrary)
            {

#ifndef _UWP

               message_box("Application \"" + strAppId + "\" cannot be created.\n\nThe library \"" + strLibrary + "\" could not be loaded. " + plibrary->m_strMessage, "ca2", message_box_icon_error);

#endif

               return nullptr;

            }

            if (is_verbose())
            {

               ::output_debug_string("\n\n::acme::session::get_new_application Found library : " + strLibrary + "\n\n");

            }

            // error anticipation is not perfect prediction and may affect results
            // so anticipation may be counter-self-healing
            // specially if what it would avoid on error is exactly we want if successful
            // who doesn't try it, won't taste it neither possibly enjoy it
//          if (!plibrary->is_opened())
//          {
//
//             ::output_debug_string("\n\n::acme::session::get_new_application Failed to load library : " + strLibrary + "\n\n");
//
//             return nullptr;
//
//          }

            if (is_verbose())
            {

               ::output_debug_string("\n\n::acme::session::get_new_application Opened library : " + strLibrary + "\n\n");

            }

            //if (!plibrary->open_ca2_library())
            //{

            //::output_debug_string("\n\n::acme::session::get_new_application open_ca2_library failed(2) : " + strLibrary + "\n\n");

            //return nullptr;

            //}

            //if (is_verbose())
            //{

            //   ::output_debug_string("\n\n\n|(5)----");
            //   ::output_debug_string("| app : " + strAppId + "\n");
            //   ::output_debug_string("|\n");
            //   ::output_debug_string("|\n");
            //   ::output_debug_string("|----");

            //}

         }

      }

   }

   if (!papp)
   {

      ::acme::library& library = *plibrary;

      papp = library.get_new_application(get_context_system()->get_context_session(), strAppId);

      ::output_debug_string("\n\n\n|(4)----");
      ::output_debug_string("| app : " + strAppId + "(papp=0x" + ::hex::upper_from((uptr)papp.m_p) + ")\n");
      ::output_debug_string("|\n");
      ::output_debug_string("|\n");
      ::output_debug_string("|----");

   }

   if (!papp)
   {

      return nullptr;

   }

#ifdef WINDOWS_DESKTOP

   WCHAR wsz[1024];

   DWORD dwSize = sizeof(wsz) / sizeof(WCHAR);

   GetUserNameW(wsz, &dwSize);

   string strUserName = wsz;

#endif // WINDOWS_DESKTOP

   if (is_verbose())
   {

      ::output_debug_string("\n\n\n|(3)----");
      ::output_debug_string("| app : " + strAppId + "\n");
      ::output_debug_string("|\n");
      ::output_debug_string("|\n");
      ::output_debug_string("|----");

   }

   if (is_verbose())
   {

      ::output_debug_string("\n\n\n|(2)----");
      ::output_debug_string("| app : " + strAppId + "\n");
      ::output_debug_string("|\n");
      ::output_debug_string("|\n");
      ::output_debug_string("|----");

   }

   //if (m_pmaindata)
   //{

   //   m_pmainstruct = papp;

   //}

#if !defined(ANDROID)

   if (!papp->is_serviceable() || papp->is_user_service())
   {

      get_context_system()->m_spmutexUserAppData = __new(::mutex(e_create_new, false, "Local\\ca2.UserAppData"));
      get_context_system()->m_spmutexSystemAppData = __new(::mutex(e_create_new, false, "Local\\ca2.SystemAppData"));

   }

#endif

   if (is_verbose())
   {

      ::output_debug_string("\n\n\n|(1)----");
      ::output_debug_string("| app : " + strAppId + "\n");
      ::output_debug_string("|\n");
      ::output_debug_string("|\n");
      ::output_debug_string("|----");

   }

   papp->m_strAppId = strAppId;

   //papp->set_context_object(get_context_system()->get_context_session());

   //papp->set_context_system(get_context_system());

   //papp->set_context_session(get_context_system()->get_context_session());

   //papp->set_context_app(papp);

   //papp->set_context_thread(get_context_system()->get_context_session());

   //papp->set_context(papp);

   return papp;

}


static ace_level * s_plevel = NULL;


ace_level::ace_level(e_level elevel, PFN_DEFER_INIT pfnDeferInit) :
   m_elevel(elevel),
   m_pfnDeferInit(pfnDeferInit),
   m_plevelNext(s_plevel)
{

   s_plevel = this;

}


ace_level * ace_level::get_maximum_level()
{

#ifdef LINUX

return nullptr;

#endif

try
{
   if(s_plevel == nullptr)
   {

      return nullptr;

   }

   ace_level * plevel = s_plevel;

   ace_level * plevelMax = plevel;

   while(true)
   {

      plevel = plevel->m_plevelNext;

      if(plevel == nullptr)
      {

         break;

      }

      if(plevel->m_elevel > plevelMax->m_elevel)
      {

         plevelMax = plevel;

      }

   }

   return plevelMax;

   }
   catch(...)
   {

   }

   return nullptr;
}


ace_level * ace_level::find_level(PFN_DEFER_INIT pfnDeferInit)
{

   if(s_plevel == nullptr)
   {

      return nullptr;

   }

   ace_level * plevel = s_plevel;

   while(plevel != nullptr)
   {

      if(plevel->m_pfnDeferInit > pfnDeferInit)
      {

         return plevel;

      }

      plevel = plevel->m_plevelNext;

   }

   return nullptr;

}


bool ace_level::defer_init()
{

   auto plevel = get_maximum_level();

   if(plevel == nullptr)
   {

      return false;

   }

   return plevel->m_pfnDeferInit();

}


bool ace_level::defer_init(PFN_DEFER_INIT pfnDeferInit)
{

   auto plevel = get_maximum_level();

   if(plevel == nullptr)
   {

      if(pfnDeferInit != nullptr)
      {

         return pfnDeferInit();

      }
      else
      {

         return true;

      }

   }
   else if(pfnDeferInit == nullptr)
   {

      if(plevel->m_pfnDeferInit != nullptr)
      {

         return plevel->m_pfnDeferInit();

      }
      else
      {

         return true;

      }

   }
   else
   {

      auto plevelFind = find_level(pfnDeferInit);

      if(plevelFind == nullptr)
      {

         bool bOk1 = false;

         bOk1 = pfnDeferInit();

         bool bOk2 = true;

         if(plevel->m_pfnDeferInit != nullptr)
         {

            bOk2 = plevel->m_pfnDeferInit();

         }

         return bOk1 && bOk2;

      }
      else if(plevelFind->m_elevel > plevel->m_elevel)
      {

         return plevelFind->m_pfnDeferInit();

      }
      else
      {

         return plevel->m_pfnDeferInit();

      }

   }

   return true;

}



void set_ace_system_as_thread()
{

   ::set_thread(::get_context_system());

}


::app_core * g_pappcore = nullptr;


static const char * g_pszCubeAppId = nullptr;


const char * get_cube_app_id()
{

   return g_pszCubeAppId;

}


void cube_set_app_id(const char * pszAppId)
{

   g_pszCubeAppId = pszAppId;

}

//
//ace_ace::ace_ace()
//{
//
//   if (!defer_ace_init())
//   {
//
//      throw raw_fail();
//
//   }
//
//}

//
//ace_ace::~ace_ace()
//{
//
//   defer_ace_term();
//
//}
//


