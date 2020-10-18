#include "framework.h"
#include "app_core.h"
#include "static_setup.h"
#include "apex/os/_os.h"
#include "apex/node/_node.h"
#include "apex/platform/static_start.h"
#include <stdio.h>
#include <time.h>

CLASS_DECL_ACME bool is_verbose();

CLASS_DECL_APEX int_bool os_init_windowing();
CLASS_DECL_APEX void os_term_windowing();


//extern string_map < __pointer(::apex::library) >* g_pmapLibrary ;
//extern string_map < PFN_NEW_APEX_LIBRARY >* g_pmapNewAuraLibrary;
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

//
//#ifdef DEBUG
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


extern ::app_core * g_pappcore;


//extern bool g_bOutputDebugString;


typedef int_bool DEFER_INIT();


typedef DEFER_INIT * PFN_DEFER_INIT;


void debug_context_object(::layered * pobjectContext);


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



//app_core::app_core(apex_main_data* pdata)
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

//#ifdef

  // os_init_windowing();

   return true;

}


extern "C"
::apex::system * apex_create_apex_system();


CLASS_DECL_ACME void set_path_install_folder(const char * pszPath);

CLASS_DECL_APEX void set_debug_pointer(void * p);


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

      set_path_install_folder(pathModule.folder(4));

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

      os_message_box("going to seteuid to: " + __str(uid), "going to seteuid", MB_OK);

      if (seteuid(uid) == 0)
      {

         os_message_box("uid=" + __str(uid), "seteuid success", MB_OK);

      }
      else
      {

         int iErr = errno;

         string strError;

         strError.Format("errno=%d uid=%d", iErr);

         os_message_box(strError, "seteuid failed", MB_ICONEXCLAMATION);

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

   // get_context_system() = __move_transfer(g_pfn_create_system());

   //get_context_system() = __move_transfer(apex_create_apex_system());

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

   //::apex::g_bOutputDebugString = file_exists(pathOutputDebugString)||  file_exists(pathGlobalOutputDebugString);

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

      file_put_contents(path, get_command_line());

      ::file::path pathExecutable = consume_param(psz, nullptr);

      string strAppTitle = executable_title_from_appid(strAppId);

      path = pathFolder / "last_executable.txt";

      if (file_is_equal_path(pathExecutable.title(), strAppTitle))
      {

         file_put_contents(path, pathExecutable);

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
//         bInApp = m_pfnNewAuraApplication != nullptr;
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
//         m_plibrary = __new(::apex::library);
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


void app_core::system_end()
{

   os_term_application();

   //os_term_windowing();

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


//CLASS_DECL_APEX int apex_entry_point(int argc, char * argv[], const char * pszMainAppId)
//{
//
//   int iResult = 0;
//
//   {
//
//      apex_main_struct apex_main_struct = {};
//
//      apex_main_struct.m_bConsole = false;
//      apex_main_struct.m_bDraw2d = true;
//      apex_main_struct.m_bUser = true;
//      apex_main_struct.m_bUserEx = true;
//
//      auto psystem = __new(::apex::system());
//
//      psystem->system_construct(argc, argv);
//
//      psystem->m_strAppId = pszMainAppId;
//
//      iResult = (int) ::apex_apex(psystem);
//
//   }
//
//   return iResult;
//
//}


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
   virtual public context_object
{

   byte m_ucha[1024];

};


//#define new ACME_NEW
//
//
//string_array get_c_args_from_string(const char * psz)
//{
//
//   string_array stra;
//
//   if (psz == nullptr)
//   {
//
//      return stra;
//
//   }
//
//   string_array straBeforeColon;
//
//   string_array straAfterColon;
//
//   const char * pszEnd = psz + strlen(psz);
//
//   string str;
//
//   int i = 0;
//
//   bool bColon = false;
//
//   while (psz < pszEnd)
//   {
//
//      ::str::consume_spaces(psz, 0, pszEnd);
//
//      if (psz >= pszEnd)
//      {
//
//         break;
//
//      }
//      if (*psz == '\"')
//      {
//
//         str = ::str::consume_quoted_value(psz, pszEnd);
//
//      }
//      else if (*psz == '\'')
//      {
//
//         str = ::str::consume_quoted_value(psz, pszEnd);
//
//      }
//      else
//      {
//
//         const char * pszValueStart = psz;
//
//         while (!::str::ch::is_whitespace(psz))
//         {
//
//            psz = str::utf8_inc(psz);
//
//            if (psz >= pszEnd)
//            {
//
//               break;
//
//            }
//
//            if (*psz == '\"')
//            {
//
//               ::str::consume_quoted_value_ex(psz, pszEnd);
//
//            }
//            else if (*psz == '\'')
//            {
//
//               ::str::consume_quoted_value_ex(psz, pszEnd);
//
//            }
//
//         }
//
//         str = string(pszValueStart, psz - pszValueStart);
//
//      }
//
//      if (str == ":")
//      {
//
//         bColon = true;
//
//      }
//      else if (!bColon && (i == 0 || str[0] != '-'))
//      {
//
//         straBeforeColon.add(str);
//
//      }
//      else
//      {
//
//         straAfterColon.add(str);
//
//      }
//
//      i++;
//
//   }
//
//   stra = straBeforeColon;
//
//   if (straAfterColon.has_elements())
//   {
//
//      stra.add(":");
//
//      stra += straAfterColon;
//
//   }
//
//   return stra;
//
//}
//
//
//string_array get_c_args_from_c(const char * psz)
//{
//
//   string_array stra;
//
//   if(psz == nullptr)
//   {
//
//      return stra;
//
//   }
//
//   string_array straBeforeColon;
//
//   string_array straAfterColon;
//
//   const char * pszEnd = psz + strlen(psz);
//
//   string str;
//
//   int i = 0;
//
//   bool bColon = false;
//
//   while(psz < pszEnd)
//   {
//
//      ::str::consume_spaces(psz, 0, pszEnd);
//
//      if(psz >= pszEnd)
//      {
//
//         break;
//
//      }
//      if(*psz == '\"')
//      {
//
//         str = ::str::consume_c_quoted_value(psz, pszEnd);
//
//      }
//      else if(*psz == '\'')
//      {
//
//         str = ::str::consume_c_quoted_value(psz, pszEnd);
//
//      }
//      else
//      {
//
//         const char * pszValueStart = psz;
//
//         while (!::str::ch::is_whitespace(psz))
//         {
//
//            psz = str::utf8_inc(psz);
//
//            if (psz >= pszEnd)
//            {
//
//               break;
//
//            }
//
//            if (*psz == '\"')
//            {
//
//               ::str::consume_quoted_value_ex(psz, pszEnd);
//
//            }
//            else if (*psz == '\'')
//            {
//
//               ::str::consume_quoted_value_ex(psz, pszEnd);
//
//            }
//
//         }
//
//         str = string(pszValueStart, psz - pszValueStart);
//
//      }
//
//      if (str == ":")
//      {
//
//         bColon = true;
//
//      }
//      else if (!bColon && (i == 0 || str[0] != '-'))
//      {
//
//         straBeforeColon.add(str);
//
//      }
//      else
//      {
//
//         straAfterColon.add(str);
//
//      }
//
//      i++;
//
//   }
//
//   stra = straBeforeColon;
//
//   if (straAfterColon.has_elements())
//   {
//
//      stra.add(":");
//
//      stra += straAfterColon;
//
//   }
//
//   return stra;
//
//}
//
//
//string_array get_c_args_for_c(const char * psz)
//{
//
//   string_array stra;
//
//   if(psz == nullptr)
//   {
//
//      return stra;
//
//   }
//
//   const char * pszEnd = psz + strlen(psz);
//
//   string str;
//
//   while(psz < pszEnd)
//   {
//
//      ::str::consume_spaces(psz, 0, pszEnd);
//
//      if(psz >= pszEnd)
//      {
//
//         break;
//
//      }
//
//      if(*psz == '\"')
//      {
//
//         str = ::str::consume_c_quoted_value(psz, pszEnd);
//
//      }
//      else if(*psz == '\'')
//      {
//
//         str = ::str::consume_c_quoted_value(psz, pszEnd);
//
//      }
//      else
//      {
//
//         const char * pszValueStart = psz;
//
//         while(!::str::ch::is_whitespace(psz))
//         {
//
//            psz = str::utf8_inc(psz);
//
//            if(psz >= pszEnd)
//            {
//
//               break;
//
//            }
//
//            if(*psz == '\"')
//            {
//
//               ::str::consume_quoted_value_ex(psz, pszEnd);
//
//            }
//            else if(*psz == '\'')
//            {
//
//               ::str::consume_quoted_value_ex(psz, pszEnd);
//
//            }
//
//         }
//
//         str = string(pszValueStart, psz - pszValueStart);
//
//      }
//
//      stra.add(str);
//
//   }
//
//   return stra;
//
//}
//
//
//string_array get_c_args(int argc, char ** argv)
//{
//
//   string_array straBeforeColon;
//
//   string_array straAfterColon;
//
//   if(argc > 0)
//   {
//
//      straBeforeColon.add(argv[0]);
//
//   }
//
//   bool bColon = false;
//
//   for(int i = 1; i < argc; i++)
//   {
//
//      if(strcmp(argv[i], ":") == 0)
//      {
//         bColon = true;
//      }
//#ifdef WINDOWS
//      else if(bColon || straAfterColon.has_elements() || argv[i][0] == '-' || (argv[i][0] == '/' && strlen(argv[i]) == 2))
//#else
//      else if(bColon || straAfterColon.has_elements() || argv[i][0] == '-')
//#endif
//      {
//
//         straAfterColon.add(argv[i]);
//
//      }
//      else
//      {
//
//         straBeforeColon.add(argv[i]);
//
//      }
//
//   }
//
//   string_array stra;
//
//   stra = straBeforeColon;
//
//   if (straAfterColon.has_elements())
//   {
//
//      stra.add(":");
//
//      stra += straAfterColon;
//
//   }
//
//   return stra;
//
//}
//

typedef size_t FN_GET_STRING(char * psz, size_t s);


typedef FN_GET_STRING * PFN_GET_STRING;


#ifdef __APPLE__


string apple_get_bundle_identifier()
{

   return ::str::from_strdup(ns_get_bundle_identifier());

}


#endif


//string transform_to_c_arg(const char * psz)
//{
//
//   bool bNeedQuote = false;
//
//   const char * pszParse = psz;
//
//   char chQuote = '\0';
//
//   while(*pszParse)
//   {
//
//      if(chQuote != '\0')
//      {
//
//         if(*pszParse == '\\')
//         {
//
//            pszParse = ::str::utf8_inc(pszParse);
//
//         }
//         else if(*pszParse == chQuote)
//         {
//
//            chQuote = '\0';
//
//         }
//
//      }
//      else if (*pszParse == '\'')
//      {
//
//         chQuote = '\'';
//
//      }
//      else if (*pszParse == '\"')
//      {
//
//         chQuote = '\"';
//
//      }
//      else if(::str::ch::is_whitespace(pszParse)
//         || isspace((unsigned char) *pszParse)
//              || *pszParse == ':')
//      {
//
//         bNeedQuote = true;
//
//         break;
//
//      }
//
//      pszParse = ::str::utf8_inc(pszParse);
//
//   }
//
//   if (bNeedQuote)
//   {
//
//      return string("\"") + ::str::replace("\"", "\\\"", psz) + "\"";
//
//   }
//   else
//   {
//
//      return psz;
//
//   }
//
//}
//
//
//string merge_colon_args(const array < string_array > & str2a)
//{
//
//   string_array straBeforeColon;
//
//   string_array straAfterColon;
//
//   string strCommandLine;
//
//   for (auto & stra : str2a)
//   {
//
//      index iFindColon = stra.find_first(":");
//
//      if (stra.get_size() > 0 && iFindColon != 0)
//      {
//
//         if (strCommandLine.is_empty())
//         {
//
//            strCommandLine = transform_to_c_arg(stra[0]);
//
//         }
//
//      }
//
//      if (iFindColon < 0)
//      {
//
//         iFindColon = stra.get_size();
//
//      }
//
//      for (index i = 1; i < stra.get_count(); i++)
//      {
//
//         string str = stra[i];
//
//         if (i < iFindColon)
//         {
//
//            straBeforeColon.add(str);
//
//         }
//         else if (i > iFindColon)
//         {
//
//            if (str.begins_eat_ci("app="))
//            {
//
//               if (straAfterColon.find_first_begins("app=") >= 0) // fixed case when added below :D..O
//               {
//
//                  straAfterColon.add("fallback_app=" + str);
//
//               }
//               else
//               {
//
//                  straAfterColon.add("app=" + str); // fixed case :) (excuses, excuses...)
//
//               }
//
//            }
//            else
//            {
//
//               straAfterColon.add(str);
//
//            }
//
//         }
//
//      }
//
//   }
//
//   strCommandLine += ::str::has_char(straBeforeColon.pred_implode(&transform_to_c_arg, " "), " ");
//
//   strCommandLine += " : ";
//
//   strCommandLine += straAfterColon.pred_implode(&transform_to_c_arg, " ");
//
//   return strCommandLine;
//
//}


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


bool app_core::has_apex_application_factory() const
{

   if (m_pfnNewAuraApplication)
   {

      return true;

   }

   //if (m_pfnNewAuraLibrary)
   //{

   //   return true;

   //}

   return false;

}



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


__result(::apex::application) app_core::get_new_application(::object* pobjectContext)
{

   if (!m_pfnNewAuraApplication)
   {

      return nullptr;

   }

   __pointer(::apex::application) papp;

   papp = m_pfnNewAuraApplication();

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


__result(::apex::application) app_core::get_new_application(::object* pobjectContext, const char* pszAppId)
{

   __pointer(::apex::application) papp;

   string strAppId = pszAppId;

   sync_lock sl(&::get_context_system()->m_mutexLibrary);

   __pointer(::apex::library)& plibrary = ::get_context_system()->m_mapLibrary[strAppId];

   if (papp)
   {

      if (!plibrary)
      {

         plibrary = new ::apex::library();

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

               papp = get_context_system()->__create < ::apex::application > ();

               *((::apex_main_struct*)papp) = *((::apex_main_struct*)this);

            }

         }

      }

      if (!papp)
      {

         if (plibrary)
         {

            plibrary->initialize_apex_library(pobjectContext, 0, nullptr);

         }
         else
         {

            //plibrary = __new(::apex::library);

            //plibrary->initialize_apex_library(pobjectContext, 0, nullptr);

            string strLibrary = strAppId;

            strLibrary.replace("/", "_");

            strLibrary.replace("-", "_");

            if (is_verbose())
            {

               ::output_debug_string("\n\n::apex::session::get_new_application assembled library path " + strLibrary + "\n\n");

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

               ::output_debug_string("\n\n::apex::session::get_new_application Found library : " + strLibrary + "\n\n");

            }

            // error anticipation is not perfect prediction and may affect results
            // so anticipation may be counter-self-healing
            // specially if what it would avoid on error is exactly we want if successful
            // who doesn't try it, won't taste it neither possibly enjoy it
//          if (!plibrary->is_opened())
//          {
//
//             ::output_debug_string("\n\n::apex::session::get_new_application Failed to load library : " + strLibrary + "\n\n");
//
//             return nullptr;
//
//          }

            if (is_verbose())
            {

               ::output_debug_string("\n\n::apex::session::get_new_application Opened library : " + strLibrary + "\n\n");

            }

            //if (!plibrary->open_ca2_library())
            //{

            //::output_debug_string("\n\n::apex::session::get_new_application open_ca2_library failed(2) : " + strLibrary + "\n\n");

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

      ::apex::library& library = *plibrary;

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

   return papp;

}


static apex_level * s_plevel = NULL;


apex_level::apex_level(e_level elevel, PFN_DEFER_INIT pfnDeferInit) :
   m_elevel(elevel),
   m_pfnDeferInit(pfnDeferInit),
   m_plevelNext(s_plevel)
{

   s_plevel = this;

}


apex_level * apex_level::get_maximum_level()
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

   apex_level * plevel = s_plevel;

   apex_level * plevelMax = plevel;

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


apex_level * apex_level::find_level(PFN_DEFER_INIT pfnDeferInit)
{

   if(s_plevel == nullptr)
   {

      return nullptr;

   }

   apex_level * plevel = s_plevel;

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


bool apex_level::defer_init()
{

   auto plevel = get_maximum_level();

   if(plevel == nullptr)
   {

      return false;

   }

   return plevel->m_pfnDeferInit();

}


bool apex_level::defer_init(PFN_DEFER_INIT pfnDeferInit)
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



//void set_apex_system_as_thread()
//{
//
//   ::set_thread(::get_context_system());
//
//}


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
//apex_apex::apex_apex()
//{
//
//   if (!defer_apex_init())
//   {
//
//      throw raw_fail();
//
//   }
//
//}

//
//apex_apex::~apex_apex()
//{
//
//   defer_apex_term();
//
//}
//


