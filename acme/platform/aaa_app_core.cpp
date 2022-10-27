// Offloading apex(TBS) from deep stack stuff 2022-02-22 by camilo at 07:18 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/operating_system.h"
#include "app_core.h"
#include "acme/platform/system_setup.h"
//#include "apex/platform/static_start.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include <stdio.h>
#include <time.h>



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


//void debug_context_object(::particle * pparticle);


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



//app_core::app_core(apex_main_data* pdata)
app_core::app_core()
{


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

   if (acmefile()->exists(::file::path(APP_CORE_BASE_DIR) / "wait_on_beg.txt"))
   {

      sleep(10_s);

   }

   if (acmefile()->exists(::file::path(APP_CORE_BASE_DIR) / "beg_debug_box.txt"))
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


void app_core::system_init()
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

   //   acmedirectory()->set_path_install_folder(pathModule.folder(4));

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
  // ::file::path pathOutputDebugString = acmedirectory()->system() / strAppId / "output_debug_string.txt" ;

   //::file::path pathGlobalOutputDebugString = acmedirectory()->config() / "output_debug_string.txt" ;

   //::apex::g_bOutputDebugString = acmefile()->exists(pathOutputDebugString)||  acmefile()->exists(pathGlobalOutputDebugString);

   //return true;

}




string app_core::get_command_line()
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


void app_core::system_end()
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


void app_core::system_proc()
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


bool app_core::has_apex_application_factory() const
{

   if (m_pfnnewmatterApplication)
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
//   ::e_status estatus = psystem->__thread_procedure();
//
//   return estatus;
//
//}


#endif


::pointer<::acme::application>app_core::new_app()
{

   //if(::acme::application::g_p)
   //{

   //   return ::acme::application::g_p;

   //}

   if (!m_pfnnewmatterApplication)
   {

      return nullptr;

   }

   ::pointer<::acme::application>papp;

   papp = m_pfnnewmatterApplication();

   if (papp.is_null())
   {

      return nullptr;

   }

   return papp;

}




void app_core::initialize_application(::acme::application *papp, ::particle * pparticle)
{

   //auto estatus = 
   
   papp->initialize(pparticle);

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
