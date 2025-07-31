#include "framework.h"
#include "app_core.h"
#include "system_setup.h"
#include "aura/os/_os.h"
#include "aura/node/_node.h"
#include "aura/platform/static_start.h"
#include <stdio.h>
#include <time.h>


//extern string_map < ::pointer<::acme::library >> g_pmapLibrary ;
//extern string_map < PFN_NEW_AURA_LIBRARY >* g_pmapNewAuraLibrary;
//extern ::pointer < ::mutex >* ::auraacmesystem()->m_pmutexLibrary;


#ifdef RASPBERRYPIOS


#include <sys/types.h>
#include <unistd.h>


#endif


#ifdef LINUX


   #ifndef RASPBERRYPIOS


   void sn_start_context();


   #endif


#endif


bool is_verbose()
{

   return ::auraacmesystem()->m_bVerbose;

}


void set_verbose(bool bVerbose)
{

   ::auraacmesystem()->m_bVerbose = bVerbose;

}


//extern ::app_core * g_pappcore;


//extern bool g_bOutputDebugString;


typedef int_bool DEFER_INIT();


typedef DEFER_INIT * PFN_DEFER_INIT;


void debug_context_object(::particle * pparticle);


#ifdef __APPLE__


char * ns_get_bundle_identifier();


string apple_get_bundle_identifier();


string ca2_command_line2();


#endif


#ifdef WINDOWS


#define APP_CORE_BASE_DIR "C:\\ca2\\config\\system"


#else


#undef USE_MISC


#define APP_CORE_BASE_DIR "/::payload/tmp/ca2/config/system"


#endif



//app_core::app_core(aura_main_data* pdata)
app_core::app_core()
{

   //m_pmaindata = pdata;

   //m_pappcore = this;

   //if(!g_pappcore)
   //{

   //   g_pappcore = this;

   //}

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


bool app_core::on_result(const ::e_status & estatus)
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


void app_core::system_prep()
{

// prelude::defer_call_construct(this);

//#ifdef __APPLE__
//
// if(m_lpCmdLine == nullptr)
// {
//
//    string str = apple_get_bundle_identifier();
//
//    str.case_insensitive_begins_eat("com.ca2.");
//
//    str.replace(".", "/");
//
//    m_lpCmdLine = ::str::dup("app : app=" + str);
//
// }
//
//#endif

   m_durationStart = ::first_millis();

   m_durationAfterApplicationFirstRequest = m_durationStart;

   if (file_system()->exists(::file::path(APP_CORE_BASE_DIR) / "wait_on_beg.txt"))
   {

      sleep(10000_ms);

   }

   if (file_system()->exists(::file::path(APP_CORE_BASE_DIR) / "beg_debug_box.txt"))
   {

      //debug_box("zzzAPPzzz app", "zzzAPPzzz app", e_message_box_icon_information);

   }

   //os_init_imaging();

   os_init_windowing();

   return true;

}


extern "C"
::aura::system * aura_create_aura_system();


extern ::file::path * g_ppathInstallFolder;


CLASS_DECL_AURA void set_debug_pointer(void * p);


void app_core::system_init()
{

   /// string test (NEW STRING 2019-11-26)
   {

      //string str1 = "\"teste\\\"teste2\"";

      //const ::scoped_string & scopedstr = str1;

      //string str = ::str::consume_quoted_value(scopedstr);

      //information(str);

   }

   if (m_iPathInstallFolderExeArg >= 0 && m_iPathInstallFolderExeArg < m_argc)
   {

      ::file::path pathModule = get_arg(m_iPathInstallFolderExeArg);

      g_ppathInstallFolder = aaa_primitive_new ::file::path(pathModule.folder(4));

   }

   string strAppId;

   string_array stra1;

#ifdef WINDOWS

   {

      auto pwsz = ::GetCommandLineW();

      string strCommandLine(pwsz);

      stra1 = get_c_args_from_string(strCommandLine);

   }

#elif defined(__ANDROID__)

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

   get_command_line_parameter(strUid, strCommandLine, "uid");

   if (strUid.has_character())
   {

      uid_t uid = atoi(strUid);

      auto pmessagebox = __initialize_new ::message_box(nullptr, "going to seteuid to: " + as_string(uid), "going to seteuid", e_message_box_ok);

pmessagebox->sync();

      if (seteuid(uid) == 0)
      {

         auto pmessagebox = __initialize_new ::message_box(nullptr, "uid=" + as_string(uid), "seteuid success", e_message_box_ok);

pmessagebox->sync();

      }
      else
      {

         int iErr = errno;

         string strError;

         strError.formatf("errno=%d uid=%d", iErr);

         auto pmessagebox = __initialize_new ::message_box(nullptr, strError, "seteuid failed", e_message_box_icon_exclamation);

pmessagebox->sync();

      }

   }

#endif

   if (!m_bShowApplicationInformation)
   {

      string strShowApplicationInformation;

      if (is_command_line_parameter_true(strShowApplicationInformation, strCommandLine, "show_application_information"))
      {

         m_bShowApplicationInformation = true;

      }

   }

   string strNoDock;

   get_command_line_parameter(strAppId, strCommandLine, "app");

   if (strAppId.has_character())
   {

      m_strAppId = strAppId;

   }
   else if(m_strAppId.has_character())
   {

      strCommandLine += " app=" +m_strAppId;

   }


   {

      string strPrgName = m_strAppId;

      strPrgName.replace("/", ".");

      strPrgName.replace("_", "-");

      m_strProgName = "com." + strPrgName;

   }

   string strDerivedApplication;

   get_command_line_parameter(strDerivedApplication, strCommandLine, "derived_application");

   //g_iDerivedApplication = atoi(strDerivedApplication);

//#ifndef CUBE
//
//   defer_load_backbone_libraries(strAppId);
//
//#endif

   os_init_application();

//   {
//
//   const ::scoped_string & scopedstr = nullptr;
//   const ::scoped_string & scopedstr2 = nullptr;
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

   //get_context_system() = __move_transfer(aura_create_aura_system());

   if (!get_context_system())
   {

      on_result(error_failed);

      return false;

   }

//   ::auraacmesystem()->common_construct();

   ::set_thread(get_context_system());

   debug_context_object(get_context_system());

   ::auraacmesystem()->initialize(get_context_system());

   //set_object(get_context_system());

   auto pcreate = __allocate ::create(get_context_system());

   pcreate->m_strAppId = strAppId;

   pcreate->m_pcommandline = __allocate command_line(get_context_system(), strCommandLine);

   //::auraacmesystem()->get_command()->add_create(pcreate);

   ::auraacmesystem()->add_create(pcreate);

   // what could influence time before Main?
   // cold start (never previously called program and its Dlls...)?
   ::auraacmesystem()->m_durationMainStart = m_durationStart;

   //xxdebug_box("box1", "box1", e_message_box_icon_information);

   ::file::path pathOutputDebugString =          auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / strAppId / "information.txt" ;

   ::file::path pathGlobalOutputDebugString =          auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->config() / "information.txt" ;

   ::aura::g_bOutputDebugString = file_system()->exists(pathOutputDebugString)||  file_system()->exists(pathGlobalOutputDebugString);

   return true;

}


string app_core::get_command_line()
{

   return m_strCommandLine;

}


void app_core::set_command_line(const ::scoped_string & scopedstr)
{

   m_strCommandLine = psz;

   ::file::path pathFolder =          auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->ca2roaming() / "program";

   string strAppId = get_command_line_parameter(scopedstr, "app");

   if (strAppId.has_character())
   {

      pathFolder /= strAppId;

      ::file::path path = pathFolder / "last_command_line.txt";

      file_system()->put_contents(path, get_command_line());

      ::file::path pathExecutable = consume_command_line_parameter(scopedstr, nullptr);

      string strAppTitle = executable_title_from_appid(strAppId);

      path = pathFolder / "last_executable.txt";

      if (file_is_equal_path_dup(pathExecutable.title(), strAppTitle))
      {

         file_system()->put_contents(path, pathExecutable);

      }

   }

}


//void app_core::defer_load_backbone_libraries(string strAppId)
//{
//
//   if (strAppId.has_character())
//   {
//
//      void * hmodule = nullptr;
//
//      bool bInApp = strAppId.case_insensitive_order("acid") == 0;
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
//         m_plibrary = __allocate ::acme::library();
//
//         m_plibrary->initialize(get_context_system());
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
//      //   if ((hmodule = __node_library_touch("aura", strMessage)) != nullptr)
//      //   {
//
//      //      pfnDeferInit = (PFN_DEFER_INIT) __node_library_raw_get(hmodule, "defer_aura_init");
//
//      //      pfnDeferTerm = (PFN_DEFER_TERM) __node_library_raw_get(hmodule, "defer_aura_term");
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
//      //   else if ((hmodule = __node_library_touch("aura", strMessage)) != nullptr)
//      //   {
//
//      //      pfnDeferInit = (PFN_DEFER_INIT) __node_library_raw_get(hmodule, "defer_aura_init");
//
//      //      pfnDeferTerm = (PFN_DEFER_TERM) __node_library_raw_get(hmodule, "defer_aura_term");
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
//      //if(!::aura_level::defer_init(pfnDeferInit))
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

   //os_term_application();

   os_term_windowing();

   //os_term_imaging();

   if (m_bShowApplicationInformation)
   {

      char szEllapsed[MAX_PATH * 2];

      ansi_count_copy(szEllapsed, ::file::path(APP_CORE_BASE_DIR) / "show_elapsed.txt", sizeof(szEllapsed));

      auto tickEnd = ::duration::now();

      char szTimeMessage[2108];

      ::posix_time timet = ::time(nullptr);

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

         sprintf(szTimeMessage, "\n\n\n---------------------------------------------------------------------------------------------\n|\n|\n|  Just After First papp Request Completion %"  PRId64 " ms", (m_durationAfterApplicationFirstRequest - m_durationStart).m_i);
         ::information(szTimeMessage);
         printf("%s", szTimeMessage);

         ::duration i::durationsTotal = tickEnd - m_durationStart;

         sprintf(szTimeMessage, "\n|  Total Elapsed Time %" PRId64 " ms", i::durationsTotal.m_i);
         ::information(szTimeMessage);
         printf("%s", szTimeMessage);

         int i::durations = i::durationsTotal.m_i % 1000;
         int iSecondsTotal = (int)(i::durationsTotal.m_i / 1000);
         int iSeconds = iSecondsTotal % 60;
         int iMinutesTotal = iSecondsTotal / 60;
         int iMinutes = iMinutesTotal % 60;
         int iHoursTotal = iMinutesTotal / 60;
         int iHours = iHoursTotal % 24;
         int iDays = iHoursTotal / 24;

         if (iDays > 0)
         {

            sprintf(szTimeMessage, "\n|  Total Elapsed Time %d days %02d:%02d:%02d %03d ms", iDays, iHours, iMinutes, iSeconds, i::durations);

         }
         else if (iHours > 0)
         {

            sprintf(szTimeMessage, "\n|  Total Elapsed Time %02d:%02d:%02d %03d ms", iHours, iMinutes, iSeconds, i::durations);

         }
         else if (iMinutes > 0)
         {

            sprintf(szTimeMessage, "\n|  Total Elapsed Time %02d:%02d %03d ms", iMinutes, iSeconds, i::durations);

         }
         else
         {

            sprintf(szTimeMessage, "\n|  Total Elapsed Time %02ds %03d ms", iSeconds, i::durations);

         }

         ::information(szTimeMessage);
         printf("%s", szTimeMessage);

         sprintf(szTimeMessage, "\n|");
         ::information(szTimeMessage);
         printf("%s", szTimeMessage);

         sprintf(szTimeMessage, "\n|  %s", szTime);
         ::information(szTimeMessage);
         printf("%s", szTimeMessage);

         sprintf(szTimeMessage, "\n|");
         ::information(szTimeMessage);
         printf("%s", szTimeMessage);

         sprintf(szTimeMessage, "\n|");
         ::information(szTimeMessage);
         printf("%s", szTimeMessage);

         sprintf(szTimeMessage, "\n-------------------------------------------------------------------------------------------- - ");
         ::information(szTimeMessage);
         printf("%s", szTimeMessage);

         sprintf(szTimeMessage, "\n");
         ::information(szTimeMessage);
         printf("%s", szTimeMessage);

         sprintf(szTimeMessage, "\n");
         ::information(szTimeMessage);
         printf("%s", szTimeMessage);

         sprintf(szTimeMessage, "\n");
         ::information(szTimeMessage);
         printf("%s", szTimeMessage);

         sprintf(szTimeMessage, "\n");
         ::information(szTimeMessage);
         printf("%s", szTimeMessage);

         if (file_exists_raw(szEllapsed))
         {

            char szUTCTime[2048];

            posix_time rawtime;

            struct tm* g;

            time(&rawtime);

            g = gmtime(&rawtime);

            sprintf(szUTCTime, "%04d-%02d-%02d %02d:%02d:%02d UTC", g->tm_year + 1900, g->tm_mon, g->tm_mday, g->tm_hour, g->tm_min, g->tm_sec);

            char szTimeMessage1[2048];

            sprintf(szTimeMessage1, " Just After First papp Request Completion %" PRId64 " ms", (m_durationAfterApplicationFirstRequest - m_durationStart).m_i);

            if (file_length_raw(szEllapsed) > 0)
            {

               file_add_contents_raw(szEllapsed, "\n");

            }

            file_add_contents_raw(szEllapsed, szUTCTime);

            file_add_contents_raw(szEllapsed, szTimeMessage1);

            file_add_contents_raw(szEllapsed, "\n");

            char szTimeMessage2[2048];

            sprintf(szTimeMessage2, " Total Elapsed Time " __prtick, (tickEnd - m_durationStart).m_i);

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


//CLASS_DECL_AURA int aura_entry_point(int argc, char * argv[], const ::scoped_string & scopedstrMainAppId)
//{
//
//   int iResult = 0;
//
//   {
//
//      aura_main_struct aura_main_struct = {};
//
//      aura_main_struct.m_bConsole = false;
//      aura_main_struct.m_bDraw2d = true;
//      aura_main_struct.m_bUser = true;
//      aura_main_struct.m_bUserEx = true;
//
//      auto psystem = __allocate ::aura::system();
//
//      psystem->system_construct(argc, argv);
//
//      psystem->m_XstrAppId = pszMainAppId;
//
//      iResult = (int) ::aura_aura(psystem);
//
//   }
//
//   return iResult;
//
//}


//CLASS_DECL_AURA long aura_prefix(::aura::system * psystem)
//{
//
//   //pmaindata->m_pappcore = __allocate app_core(pmaindata);
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


//CLASS_DECL_AURA long aura_fork(::aura::system * psystem, PFN_NEW_AURA_APPLICATION pfnNewAuraApplication)
//{
//
//   //pmaindata->m_pappcore = __allocate app_core(pmaindata);
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


//CLASS_DECL_AURA long aura_aura(::aura::system * psystem)
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

   unsigned char m_ucha[1024];

};





string_array get_c_args_from_string(const ::scoped_string & scopedstr)
{

   string_array stra;

   if (scopedstr == nullptr)
   {

      return stra;

   }

   string_array straBeforeColon;

   string_array straAfterColon;

   const ::ansi_character * pszEnd = psz + strlen(scopedstr);

   string str;

   int i = 0;

   bool bColon = false;

   while (scopedstr < pszEnd)
   {

      ::str::consume_spaces(scopedstr, 0, pszEnd);

      if (scopedstr >= pszEnd)
      {

         break;

      }
      if (*psz == '\"')
      {

         str = ::str::consume_quoted_value(scopedstr, pszEnd);

      }
      else if (*psz == '\'')
      {

         str = ::str::consume_quoted_value(scopedstr, pszEnd);

      }
      else
      {

         const ::scoped_string & scopedstrValueStart = psz;

         while (!unicode_is_whitespace(scopedstr))
         {

            unicode_increment(scopedstr);

            if (scopedstr >= pszEnd)
            {

               break;

            }

            if (*psz == '\"')
            {

               ::str::consume_quoted_value_ex(scopedstr, pszEnd);

            }
            else if (*psz == '\'')
            {

               ::str::consume_quoted_value_ex(scopedstr, pszEnd);

            }

         }

         str = string(scopedstrValueStart, psz - pszValueStart);

      }

      if (str == ":")
      {

         bColon = true;

      }
      else if (!bColon && (i == 0 || str[0] != '-'))
      {

         straBeforeColon.add(str);

      }
      else
      {

         straAfterColon.add(str);

      }

      i++;

   }

   stra = straBeforeColon;

   if (straAfterColon.has_elements())
   {

      stra.add(":");

      stra += straAfterColon;

   }

   return stra;

}


string_array get_c_args_from_c(const ::scoped_string & scopedstr)
{

   string_array stra;

   if(scopedstr == nullptr)
   {

      return stra;

   }

   string_array straBeforeColon;

   string_array straAfterColon;

   const ::ansi_character * pszEnd = psz + strlen(scopedstr);

   string str;

   int i = 0;

   bool bColon = false;

   while(scopedstr < pszEnd)
   {

      ::str::consume_spaces(scopedstr, 0, pszEnd);

      if(scopedstr >= pszEnd)
      {

         break;

      }
      if(*psz == '\"')
      {

         str = ::str::consume_c_quoted_value(scopedstr, pszEnd);

      }
      else if(*psz == '\'')
      {

         str = ::str::consume_c_quoted_value(scopedstr, pszEnd);

      }
      else
      {

         const ::scoped_string & scopedstrValueStart = psz;

         while (!unicode_is_whitespace(scopedstr))
         {

            unicode_increment(scopedstr);

            if (scopedstr >= pszEnd)
            {

               break;

            }

            if (*psz == '\"')
            {

               ::str::consume_quoted_value_ex(scopedstr, pszEnd);

            }
            else if (*psz == '\'')
            {

               ::str::consume_quoted_value_ex(scopedstr, pszEnd);

            }

         }

         str = string(scopedstrValueStart, psz - pszValueStart);

      }

      if (str == ":")
      {

         bColon = true;

      }
      else if (!bColon && (i == 0 || str[0] != '-'))
      {

         straBeforeColon.add(str);

      }
      else
      {

         straAfterColon.add(str);

      }

      i++;

   }

   stra = straBeforeColon;

   if (straAfterColon.has_elements())
   {

      stra.add(":");

      stra += straAfterColon;

   }

   return stra;

}


string_array get_c_args_for_c(const ::scoped_string & scopedstr)
{

   string_array stra;

   if(scopedstr == nullptr)
   {

      return stra;

   }

   const ::ansi_character * pszEnd = psz + strlen(scopedstr);

   string str;

   while(scopedstr < pszEnd)
   {

      ::str::consume_spaces(scopedstr, 0, pszEnd);

      if(scopedstr >= pszEnd)
      {

         break;

      }

      if(*psz == '\"')
      {

         str = ::str::consume_c_quoted_value(scopedstr, pszEnd);

      }
      else if(*psz == '\'')
      {

         str = ::str::consume_c_quoted_value(scopedstr, pszEnd);

      }
      else
      {

         const ::scoped_string & scopedstrValueStart = psz;

         while(!unicode_is_whitespace(scopedstr))
         {

            unicode_increment(scopedstr);

            if(scopedstr >= pszEnd)
            {

               break;

            }

            if(*psz == '\"')
            {

               ::str::consume_quoted_value_ex(scopedstr, pszEnd);

            }
            else if(*psz == '\'')
            {

               ::str::consume_quoted_value_ex(scopedstr, pszEnd);

            }

         }

         str = string(scopedstrValueStart, psz - pszValueStart);

      }

      stra.add(str);

   }

   return stra;

}


string_array get_c_args(int argc, char ** argv)
{

   string_array straBeforeColon;

   string_array straAfterColon;

   if(argc > 0)
   {

      straBeforeColon.add(argv[0]);

   }

   bool bColon = false;

   for(int i = 1; i < argc; i++)
   {

      if(strcmp(argv[i], ":") == 0)
      {
         bColon = true;
      }
#ifdef WINDOWS
      else if(bColon || straAfterColon.has_elements() || argv[i][0] == '-' || (argv[i][0] == '/' && strlen(argv[i]) == 2))
#else
      else if(bColon || straAfterColon.has_elements() || argv[i][0] == '-')
#endif
      {

         straAfterColon.add(argv[i]);

      }
      else
      {

         straBeforeColon.add(argv[i]);

      }

   }

   string_array stra;

   stra = straBeforeColon;

   if (straAfterColon.has_elements())
   {

      stra.add(":");

      stra += straAfterColon;

   }

   return stra;

}


typedef size_t FN_GET_STRING(char * psz, size_t s);


typedef FN_GET_STRING * PFN_GET_STRING;


#ifdef __APPLE__


string apple_get_bundle_identifier()
{

   return ::string_from_strdup(ns_get_bundle_identifier());

}


#endif


string transform_to_c_arg(const ::scoped_string & scopedstr)
{

   bool bNeedQuote = false;

   const ::scoped_string & scopedstrParse = psz;

   char chQuote = '\0';

   while(*pszParse)
   {

      if(chQuote != '\0')
      {

         if(*pszParse == '\\')
         {

            unicode_increment(scopedstrParse);

         }
         else if(*pszParse == chQuote)
         {

            chQuote = '\0';

         }

      }
      else if (*pszParse == '\'')
      {

         chQuote = '\'';

      }
      else if (*pszParse == '\"')
      {

         chQuote = '\"';

      }
      else if(unicode_is_whitespace(scopedstrParse)
         || character_isspace((unsigned char) *pszParse)
              || *pszParse == ':')
      {

         bNeedQuote = true;

         break;

      }

      unicode_increment(scopedstrParse);

   }

   if (bNeedQuote)
   {

      return string("\"") + ::str::replace("\"", "\\\"", psz) + "\"";

   }
   else
   {

      return psz;

   }

}


string merge_colon_args(const array < string_array > & straa)
{

   string_array straBeforeColon;

   string_array straAfterColon;

   string strCommandLine;

   for (auto & stra : straa)
   {

      ::collection::index iFindColon = stra.find_first(":");

      if (stra.get_size() > 0 && iFindColon != 0)
      {

         if (strCommandLine.is_empty())
         {

            strCommandLine = transform_to_c_arg(stra[0]);

         }

      }

      if (iFindColon < 0)
      {

         iFindColon = stra.get_size();

      }

      for (::collection::index i = 1; i < stra.get_count(); i++)
      {

         string str = stra[i];

         if (i < iFindColon)
         {

            straBeforeColon.add(str);

         }
         else if (i > iFindColon)
         {

            if (str.case_insensitive_begins_eat("app="))
            {

               if (straAfterColon.find_first_begins("app=") >= 0) // fixed case when added below :D..O
               {

                  straAfterColon.add("fallback_app=" + str);

               }
               else
               {

                  straAfterColon.add("app=" + str); // fixed case :) (excuses, excuses...)

               }

            }
            else
            {

               straAfterColon.add(str);

            }

         }

      }

   }

   strCommandLine += ::str::has_character(straBeforeColon.predicate_implode(&transform_to_c_arg, " "), " ");

   strCommandLine += " : ";

   strCommandLine += straAfterColon.predicate_implode(&transform_to_c_arg, " ");

   return strCommandLine;

}


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

#elif !defined(__ANDROID__)


void app_core::system_proc()
{

   return ::error_failed;

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
//      informationf("exception:app_core:run");
//
//      estatus = error_exception;
//
//   }
//
//   return estatus;
//
//}


bool app_core::has_aura_application_factory() const
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


//void app_core::system_pre_run()
//{
//
//   if (m_pmainstruct && m_pmainstruct->m_bConsole)
//   {
//
//      return ::auraacmesystem()->inline_init();
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
//void app_core::system_start()
//{
//
//   ::e_status estatus = system_pre_run();
//
//   if (!estatus)
//   {
//
//      return estatus;
//
//   }
//
//   ::auraacmesystem()->increment_reference_count();
//
//   if (m_pmainstruct && m_pmainstruct->m_bConsole)
//   {
//
//      ::auraacmesystem()->get_session()->set_context_app(::auraacmesystem()->application());
//
//      ::auraacmesystem()->set_context_app(::auraacmesystem()->application());
//
//      ::auraacmesystem()->get_session()->set_context(::auraacmesystem()->application());
//
//      ::auraacmesystem()->set_context(::auraacmesystem()->application());
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




#elif defined(UNIVERSAL_WINDOWS)



#elif defined(LINUX)


//// LOOK AT LINUX_MAIN.Cpp

//// defined at linux_main.cpp


#elif defined(__ANDROID__)


// LOOK AT ANDROID_MAIN.Cpp

// defined at android_main.cpp


#else


//unsigned int app_core::system_main()
//{
//
//   ::e_status estatus = ::auraacmesystem()->__thread_procedure();
//
//   return estatus;
//
//}


#endif


::pointer<::aura::application>app_core::get_new_application(::object* pparticle)
{

   if (!m_pfnNewAuraApplication)
   {

      return nullptr;

   }

   ::pointer<::aura::application>papp;

   papp = m_pfnNewAuraApplication();

   if (papp.is_null())
   {

      return nullptr;

   }

   auto estatus = papp->initialize(pparticle);

   if (!estatus)
   {

      return estatus;

   }

   return papp;

}


::pointer<::aura::application>app_core::get_new_application(::object* pparticle, const ::scoped_string & scopedstrAppId)
{

   ::pointer<::aura::application>papp;

   string strAppId = pszAppId;

   synchronous_lock synchronouslock(::auraacmesystem()->m_pmutexLibrary);

   ::pointer<::acme::library> plibrary = ::auraacmesystem()->m_mapLibrary[strAppId];

   if (papp)
   {

      if (!plibrary)
      {

         plibrary = aaa_primitive_new ::acme::library();

         plibrary->m_strName = "";

      }

   }
   else
   {

      auto psetup = system_setup::get_first(::system_setup::flag_application, strAppId);

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

               papp = ::auraacmesystem()->__øcreate < ::aura::application > ();

               *((::aura_main_struct*)papp) = *((::aura_main_struct*)this);

            }

         }

      }

      if (!papp)
      {

         if (plibrary)
         {

            plibrary->initialize_aura_library(pparticle, 0, nullptr);

         }
         else
         {

            //plibrary = __allocate ::acme::library();

            //plibrary->initialize_aura_library(pparticle, 0, nullptr);

            string strLibrary = strAppId;

            strLibrary.replace("/", "_");

            strLibrary.replace("-", "_");

            if (is_verbose())
            {

               informationf("\n\n::aura::session::get_new_application assembled library path " + strLibrary + "\n\n");

            }

            plibrary = ::auraacmesystem()->get_library(strLibrary);

            if (!plibrary)
            {

#ifndef UNIVERSAL_WINDOWS

               output_error_message("papp \"" + strAppId + "\" cannot be created.\n\nThe library \"" + strLibrary + "\" could not be loaded. " + plibrary->m_strMessage, "ca2", e_message_box_icon_error);

#endif

               return nullptr;

            }

            if (is_verbose())
            {

               informationf("\n\n::aura::session::get_new_application Found library : " + strLibrary + "\n\n");

            }

            // error anticipation is not perfect prediction and may affect results
            // so anticipation may be counter-self-healing
            // specially if what it would avoid on error is exactly we want if successful
            // who doesn't try it, won't taste it neither possibly enjoy it
//          if (!plibrary->is_opened())
//          {
//
//             informationf("\n\n::aura::session::get_new_application Failed to load library : " + strLibrary + "\n\n");
//
//             return nullptr;
//
//          }

            if (is_verbose())
            {

               informationf("\n\n::aura::session::get_new_application Opened library : " + strLibrary + "\n\n");

            }

            //if (!plibrary->open_ca2_library())
            //{

            //informationf("\n\n::aura::session::get_new_application open_ca2_library failed(2) : " + strLibrary + "\n\n");

            //return nullptr;

            //}

            //if (is_verbose())
            //{

            //   informationf("\n\n\n|(5)----");
            //   informationf("| app : " + strAppId + "\n");
            //   informationf("|\n");
            //   informationf("|\n");
            //   informationf("|----");

            //}

         }

      }

   }

   if (!papp)
   {

      ::acme::library& library = *plibrary;

      papp = library.get_new_application(::auraacmesystem()->get_session(), strAppId);

      informationf("\n\n\n|(4)----");
      informationf("| app : " + strAppId + "(papp=0x" + ::hex::upper_from((uptr)papp.m_p) + ")\n");
      informationf("|\n");
      informationf("|\n");
      informationf("|----");

   }

   if (!papp)
   {

      return nullptr;

   }

#ifdef WINDOWS_DESKTOP

   WCHAR wsz[1024];

   unsigned int dwSize = sizeof(wsz) / sizeof(WCHAR);

   GetUserNameW(wsz, &dwSize);

   string strUserName = wsz;

#endif // WINDOWS_DESKTOP

   if (is_verbose())
   {

      informationf("\n\n\n|(3)----");
      informationf("| app : " + strAppId + "\n");
      informationf("|\n");
      informationf("|\n");
      informationf("|----");

   }

   if (is_verbose())
   {

      informationf("\n\n\n|(2)----");
      informationf("| app : " + strAppId + "\n");
      informationf("|\n");
      informationf("|\n");
      informationf("|----");

   }

   //if (m_pmaindata)
   //{

   //   m_pmainstruct = papp;

   //}

#if !defined(__ANDROID__)

   if (!papp->is_serviceable() || papp->is_user_service())
   {

      ::auraacmesystem()->m_spmutexUserAppData = __allocate ::pointer < ::mutex > (e_create_new, false, "Local\\ca2.UserAppData");
      ::auraacmesystem()->m_spmutexSystemAppData = __allocate ::pointer < ::mutex > (e_create_new, false, "Local\\ca2.SystemAppData");

   }

#endif

   if (is_verbose())
   {

      informationf("\n\n\n|(1)----");
      informationf("| app : " + strAppId + "\n");
      informationf("|\n");
      informationf("|\n");
      informationf("|----");

   }

   papp->m_strAppId = strAppId;

   //papp->set_object(::auraacmesystem()->get_session());

   //papp->set_context_system(get_context_system());

   //papp->set_context_session(::auraacmesystem()->get_session());

   //papp->set_context_app(papp);

   //papp->set_context_thread(::auraacmesystem()->get_session());

   //papp->set_context(papp);

   return papp;

}


static aura_level * s_plevel = NULL;


aura_level::aura_level(e_level elevel, PFN_DEFER_INIT pfnDeferInit) :
   m_elevel(elevel),
   m_pfnDeferInit(pfnDeferInit),
   m_plevelNext(s_plevel)
{

   s_plevel = this;

}


aura_level * aura_level::get_maximum_level()
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

   aura_level * plevel = s_plevel;

   aura_level * plevelMax = plevel;

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


aura_level * aura_level::find_level(PFN_DEFER_INIT pfnDeferInit)
{

   if(s_plevel == nullptr)
   {

      return nullptr;

   }

   aura_level * plevel = s_plevel;

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


bool aura_level::defer_init()
{

   auto plevel = get_maximum_level();

   if(plevel == nullptr)
   {

      return false;

   }

   return plevel->m_pfnDeferInit();

}


bool aura_level::defer_init(PFN_DEFER_INIT pfnDeferInit)
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


void set_apex_system_as_thread()
{

   ::set_thread(::get_context_system());

}


::app_core * g_pappcore = nullptr;


static const char * g_pszCubeAppId = nullptr;


const char * get_cube_app_id()
{

   return g_pszCubeAppId;

}


void cube_set_app_id(const ::scoped_string & scopedstrAppId)
{

   g_pszCubeAppId = pszAppId;

}

//
//aura_aura::aura_aura()
//{
//
//   if (!defer_aura_init())
//   {
//
//      throw raw_fail();
//
//   }
//
//}

//
//aura_aura::~aura_aura()
//{
//
//   defer_aura_term();
//
//}
//


