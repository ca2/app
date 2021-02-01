#include "framework.h"
#include "acme/update.h"
#ifdef WINDOWS
#include <process.h>
#elif defined(LINUX)
#include <sys/types.h>
#include <unistd.h>
#endif
#include "simple_trace.h"
#include "trace.h"


CLASS_DECL_ACME void __simple_tracea(::matter * pobjectContext, enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * psz);
CLASS_DECL_ACME void __simple_tracev(::matter * pobjectContext, enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list args);


//CLASS_DECL_APEX void FUNCTION_DEBUGBOX(const char * pszMessage, const char * pszTitle, const ::e_message_box & emessagebox, ::callback callback)
//{
//
//   ::os_message_box(nullptr, pszMessage, pszTitle, iFlags, function);
//
//}


//CLASS_DECL_APEX void FUNCTION_DEBUGBOXW(const WCHAR * pszMessage, const WCHAR * pszTitle, i32 iFlags, const ::function_arg& function)
//{
//
//   ::os_message_box_w(nullptr, pszMessage, pszTitle, iFlags, function);
//
//}


void TRACELASTSTATUS()
{

   auto estatus = ::get_last_status();

   if (!estatus)
   {

      return;

   }

   string strStatusMessage = ::get_system_error_message(estatus);

   TRACE("Status Message :\n%s\n", strStatusMessage.c_str());

}



extern "C"
void o_debug_string(const char * psz)
{
   output_debug_string(psz);
}


CLASS_DECL_ACME void __trace(enum_trace_level elevel, const char * pszTag, const char * pszText, const char * pszFile, int iLine)
{

   strsize iLen;

   iLen = strlen(pszText);

   if (pszFile != nullptr)
   {

      iLen += strlen(pszFile);

      iLen += 30;

      if (iLine >= 1)
      {

         iLen += 30;

      }

   }

   string str;

   char * psz = str.get_string_buffer(iLen + 8);

   strcpy(psz, pszText);

   if (pszFile != nullptr)
   {

      ansi_concatenate(psz, ", \"");

      ansi_concatenate(psz, pszFile);

      if (iLine >= 1)
      {

         char pszNum[30];

         ansi_from_i64(pszNum, iLine, 10);

         ansi_concatenate(psz, "(");

         ansi_concatenate(psz, pszNum);

         ansi_concatenate(psz, ")");

      }

      ansi_concatenate(psz, "\"");

   }

   str.release_string_buffer();

   os_trace(elevel, pszTag, str);

}



//int g_iMemoryCounters = -1;
//
//CLASS_DECL_APEX::mutex * g_pmutexMemoryCounters = nullptr;
//
//int g_iMemoryCountersStartable = 0;
//
//CLASS_DECL_APEX bool memcnts()
//{
//
//   if (g_iMemoryCountersStartable && g_iMemoryCounters < 0)
//   {
//
//      g_iMemoryCounters = file_exists(::dir::config() / "system/memory_counters.txt") ? 1 : 0;
//
//      if (g_iMemoryCounters)
//      {
//
//         g_pmutexMemoryCounters = new ::mutex(e_create_new, nullptr, false, "Global\\ca2_memory_counters");
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
//CLASS_DECL_APEX::file::path memcnts_base_path()
//{
//
//   if (g_iMemoryCountersStartable && g_pMemoryCounters == nullptr)
//   {
//
//      g_pMemoryCounters = new ::file::path();
//
//#if defined(_UWP)
//
//      string strBasePath = ::dir::system() / "memory_counters";
//
//#else
//
//      ::file::path strModule = module_path_from_pid(getpid());
//
//      string strBasePath = ::dir::system() / "memory_counters" / strModule.title() / __str(getpid());
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



simple_trace::simple_trace()
{

#ifdef DEBUG

   INFO("Starting Simple Alog");

#endif

}


simple_trace::~simple_trace()
{

   //INFO("Ending Simple Alog");

}


void simple_trace::__tracea(::matter * pobjectContext, enum_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz)
{

   __simple_tracea(pobjectContext, elevel, pszFunction, pszFile, iLine, psz);
   //printf("%d %c %s %d %s", (i32)ecategory, e_trace_level_char(elevel), pszFunction, iLine, psz);

}




CLASS_DECL_ACME const char * e_trace_level_name(enum_trace_level elevel);

#undef DEFINE_MESSAGE

#define SIMPLE_TRACE_FUNCTION_NAME 0
#define SIMPLE_TRACE_FILE_NAME 0

CLASS_DECL_ACME void __simple_tracea(::matter * pobjectContext, enum_trace_level elevel, const char * pszFunction, const char * pszFileName, i32 iLine, const char * psz)
{

#ifndef DEBUG

   if (elevel < e_trace_level_error)
   {

      return;

   }

#endif

   string strMessage;

   auto pszTopicText = topic_text(pobjectContext);

   if (::is_set(pszTopicText) && *pszTopicText != '\0')
   {

      string strTopic(pszTopicText);

      ::str::begins_eat_ci(strTopic, "class ");

      ::str::begins_eat_ci(strTopic, "struct ");

      strMessage.Format("%c:%s> %s", trace_level_char(elevel), strTopic.c_str(), psz);

   }
   else
   {

      strMessage.Format("%c> %s", trace_level_char(elevel), psz);

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

         strMessage += "(" + __str(iLine) + ")";

      }

   }

#endif

   strMessage += "\n";

   output_debug_string(strMessage);

}


CLASS_DECL_ACME void __simple_tracev(::matter * pobjectContext, enum_trace_level elevel, const char * pszFunction, const char * pszFileName, i32 iLine, const char * pszFormat, va_list args)
{

   //if (s_pstringmanager == nullptr)
   //{

   //   vprintf(pszFormat, args);

   //   return;

   //}

   string strMessage;

   strMessage.FormatV(pszFormat, args);

   __simple_tracea(pobjectContext, elevel, pszFunction, pszFileName, iLine, strMessage);

}




