#include "framework.h"
#include "simple_log.h"
#include "trace.h"
#include "acme/platform/debug.h"
#include "acme/platform/system.h"
#ifdef WINDOWS
#include <process.h>
#elif defined(LINUX)
#include <sys/types.h>
#include <unistd.h>
#endif

string get_status_message(const ::e_status & estatus);


CLASS_DECL_ACME void __simple_tracea(enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const ::scoped_string & scopedstr);
CLASS_DECL_ACME void __simple_tracev(enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const ::scoped_string & scopedstrFormat, va_list args);


//CLASS_DECL_ACME void FUNCTION_DEBUGBOX(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, ::callback callback)
//{
//
//   ::message_box_synchronous(nullptr, pszMessage, pszTitle, iFlags, function);
//
//}


//CLASS_DECL_ACME void FUNCTION_DEBUGBOXW(const WCHAR * pszMessage, const WCHAR * pszTitle, i32 iFlags, const ::function_arg& function)
//{
//
//   ::os_message_box_w(nullptr, pszMessage, pszTitle, iFlags, function);
//
//}


void matter::trace_last_status()
{

   auto estatus = ::get_last_status();

   if (!estatus)
   {

      return;

   }

   string strStatusMessage = ::get_status_message(estatus);

   warning() <<"Status Message :\n" << strStatusMessage << "\n";

}


extern "C"
void o_debug_string(const ::scoped_string & scopedstr)
{
   information(scopedstr);
}


CLASS_DECL_ACME void __trace(enum_trace_level elevel, const ::scoped_string & scopedstrTag, const ::scoped_string & scopedstrText, const ::scoped_string & scopedstrFile, int iLine)
{

   strsize iLen;

   iLen = scopedstrText.size();

   if (scopedstrFile.has_char())
   {

      iLen += scopedstrFile.size();

      iLen += 30;

      if (iLine >= 1)
      {

         iLen += 30;

      }

   }

   string str;

   char * psz = str.get_buffer(iLen + 8);

   ansi_ncpy(psz, scopedstrText, scopedstrText.size());

   if (scopedstrFile.has_char())
   {

      ansi_concatenate(psz, ", \"");

      ansi_concatenate(psz, scopedstrText.begin(), scopedstrText.size());

      if (iLine >= 1)
      {

         char pszNum[30];

         ansi_from_i64(pszNum, iLine, 10, e_digit_case_upper);

         ansi_concatenate(psz, "(");

         ansi_concatenate(psz, pszNum);

         ansi_concatenate(psz, ")");

      }

      ansi_concatenate(psz, "\"");

   }

   str.release_buffer();

   os_trace(elevel, scopedstrTag, str);

}



//int g_iMemoryCounters = -1;
//
//CLASS_DECL_ACME::pointer< ::mutex > g_pmutexMemoryCounters = nullptr;
//
//int g_iMemoryCountersStartable = 0;
//
//CLASS_DECL_ACME bool memory_counter_on()
//{
//
//   if (g_iMemoryCountersStartable && g_iMemoryCounters < 0)
//   {
//
//      g_iMemoryCounters = acmefile()->exists(         auto psystem = acmesystem();

//         auto pacmedirectory = psystem->m_pacmedirectory;
//
//pacmedirectory->config() / "system/memory_counters.txt") ? 1 : 0;
//
//      if (g_iMemoryCounters)
//      {
//
//         g_pmutexMemoryCounters = memory_new ::pointer < ::mutex >(e_create_new, nullptr, false, "Global\\ca2_memory_counters");
//
//      }
//
//   }
//
//   return g_iMemoryCountersStartable && g_iMemoryCounters;
//
//}
//
//
//::file::path * g_pMemoryCounters = nullptr;
//
//
//CLASS_DECL_ACME::file::path memory_counter_base_path()
//{
//
//   if (g_iMemoryCountersStartable && g_pMemoryCounters == nullptr)
//   {
//
//      g_pMemoryCounters = memory_new ::file::path();
//
//#if defined(UNIVERSAL_WINDOWS)
//
//      string strBasePath =          auto psystem = acmesystem();

//         auto pacmedirectory = psystem->m_pacmedirectory;
//
//pacmedirectory->system() / "memory_counters";
//
//#else
//
//      ::file::path strModule = module_path_from_pid(getpid());
//
//      string strBasePath =          auto psystem = acmesystem();

//         auto pacmedirectory = psystem->m_pacmedirectory;
//
//pacmedirectory->system() / "memory_counters" / strModule.title() / as_string(getpid());
//
//#endif
//
//      * g_pMemoryCounters = strBasePath;
//
//   }
//
//   return *g_pMemoryCounters;
//
//}



simple_log::simple_log()
{

   m_bReallySimple = true;

#ifdef _DEBUG

   //information() << "Starting Simple Alog";

#endif

}


simple_log::~simple_log()
{

   //information() << "Ending Simple Alog";

}


void simple_log::print(trace_statement & tracestatement)
{

   if (!m_bLog)
   {

      return;

   }

   if(tracestatement.m_etracelevel >= m_etracelevelMinimum)
   {

      string str;

      ::string strTaskName;

      strTaskName = ::current_task_name();

      if (m_bReallySimple)
      {

         str += strTaskName + "> ";

         str += tracestatement.as_string();

         str += "\n";

      }
      else
      {



         str.format("%s> %c %s %d %s\n", strTaskName.c_str(), trace_level_char(tracestatement.m_etracelevel), tracestatement.m_pszFunction, tracestatement.m_iLine, tracestatement.as_string().c_str());

      }

      ::output_debug_string(str);

   }

}




CLASS_DECL_ACME const char * e_trace_level_name(enum_trace_level elevel);

#undef DEFINE_MESSAGE

#define SIMPLE_TRACE_FUNCTION_NAME 0
#define SIMPLE_TRACE_FILE_NAME 0

CLASS_DECL_ACME void __simple_tracea(::particle * pparticle, enum_trace_level elevel, const char * pszFunction, const char * pszFileName, i32 iLine, const ::scoped_string & scopedstr)
{

#ifndef DEBUG

   if (elevel < e_trace_level_error)
   {

      return;

   }

#endif

   string strMessage;

   auto pszTopicText = topic_text(pparticle);

   if (::is_set(pszTopicText) && *pszTopicText != '\0')
   {

      string strTopic(pszTopicText);

      strTopic.case_insensitive_begins_eat("class ");

      strTopic.case_insensitive_begins_eat("struct ");

      strMessage.format("%c:%s> %s", trace_level_char(elevel), strTopic.c_str(), scopedstr.c_str());

   }
   else
   {

      strMessage.format("%c> %s", trace_level_char(elevel), scopedstr.c_str());

   }

#if SIMPLE_TRACE_FUNCTION_NAME

   if (::is_set(pszFunction))
   {

      strMessage += "\nFunction: ";

      strMessage += pszFunction;

   }

#endif

#if SIMPLE_TRACE_FILE_NAME

   if (::is_set(pszFileName))
   {

      strMessage += "\nFile: ";

      strMessage += pszFileName;

      if (iLine >= 1)
      {

         strMessage += "(" + as_string(iLine) + ")";

      }

   }

#endif

   strMessage += "\n";

   information(strMessage);

}


CLASS_DECL_ACME void __simple_tracev(::particle * pparticle, enum_trace_level elevel, const char * pszFunction, const char * pszFileName, i32 iLine, const ::ansi_character * pszFormat, va_list args)
{

   //if (s_pstringmanager == nullptr)
   //{

   //   vprintf(pszFormat, args);

   //   return;

   //}

   string strMessage;

   strMessage.format_arguments(pszFormat, args);

   __simple_tracea(pparticle, elevel, pszFunction, pszFileName, iLine, strMessage);

}


