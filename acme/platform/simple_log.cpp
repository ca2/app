#include "framework.h"
#include "simple_log.h"
#include "trace.h"
#include "acme/platform/acme.h"
#include "acme/platform/application.h"
#include "acme/platform/debug.h"
#include "acme/platform/system.h"
#include "acme/prototype/datetime/datetime.h"
#ifdef WINDOWS
#include <process.h>
#elif defined(LINUX)
#include <sys/types.h>
#include <unistd.h>
#elif defined(__BSD__) || defined(__APPLE__)
#include <stdio.h>
#endif

static bool g_bPrintfIfDebuggerIsNotAttached = false;

string get_status_message(const ::e_status & estatus);


CLASS_DECL_ACME void __simple_tracea(enum_trace_level elevel, const_char_pointer pszFunction, const_char_pointer pszFile, int iLine, const ::scoped_string & scopedstr);
CLASS_DECL_ACME void __simple_tracev(enum_trace_level elevel, const_char_pointer pszFunction, const_char_pointer pszFile, int iLine, const ::scoped_string & scopedstrFormat, va_list args);


//CLASS_DECL_ACME void FUNCTION_DEBUGBOX(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox, ::callback callback)
//{
//
//   ::auto pmessagebox = __initialize_new ::message_box(nullptr, pszMessage, pszTitle, iFlags, function);

//pmessagebox->sync();
//
//}


//CLASS_DECL_ACME void FUNCTION_DEBUGBOXW(const WCHAR * pszMessage, const WCHAR * pszTitle, int iFlags, const ::function_arg& function)
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

   informationf(scopedstr);

}


CLASS_DECL_ACME void __trace(enum_trace_level elevel, const ::scoped_string & scopedstrTag, const ::scoped_string & scopedstrText, const ::scoped_string & scopedstrFile, int iLine)
{

   character_count iLen;

   iLen = scopedstrText.size();

   if (scopedstrFile.has_character())
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

   if (scopedstrFile.has_character())
   {

      ansi_concatenate(psz, ", \"");

      ansi_concatenate(psz, scopedstrText.begin(), scopedstrText.size());

      if (iLine >= 1)
      {

         char pszNum[30];

         ansi_from_long_long(pszNum, iLine, 10, e_digit_case_upper);

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
//      g_iMemoryCounters = file_system()->exists(         auto psystem = system();

//         auto pdirectorysystem = psystem->m_pdirectorysystem;
//
//pdirectorysystem->config() / "system/memory_counters.txt") ? 1 : 0;
//
//      if (g_iMemoryCounters)
//      {
//
//         g_pmutexMemoryCounters = ___new ::pointer < ::mutex > (e_create_new, nullptr, false, "Global\\ca2_memory_counters");
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
//      g_pMemoryCounters = ___new ::file::path ();
//
//#if defined(UNIVERSAL_WINDOWS)
//
//      string strBasePath =          auto psystem = system();

//         auto pdirectorysystem = psystem->m_pdirectorysystem;
//
//pdirectorysystem->system() / "memory_counters";
//
//#else
//
//      ::file::path strModule = module_path_from_pid(getpid());
//
//      string strBasePath =          auto psystem = system();

//         auto pdirectorysystem = psystem->m_pdirectorysystem;
//
//pdirectorysystem->system() / "memory_counters" / strModule.title() / as_string(getpid());
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

#if REFERENCING_DEBUGGING

   disable_referencing_debugging();

#endif

   increment_reference_count();

   m_bReallySimple = true;
   m_bWithTimePrefix = true;
   m_bDisplayRelativeTime = true;

   ::file::path pathTrace;

   auto pathHome = home_folder_path();

   pathTrace = pathHome / "trace_using_printf.txt";

   if (file_exists(pathTrace))
   {

      g_bPrintfIfDebuggerIsNotAttached = true;

   }

#ifdef _DEBUG

   //information() << "Starting Simple Alog";

#endif

}


simple_log::~simple_log()
{

   //information() << "Ending Simple Alog";

}


void simple_log::print(::trace_statement & tracestatement, bool bFlush)
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

         auto s = tracestatement.as_string();

         if (s.begins_eat("\r"))
         {
            
            str += "\r";

            str += strTaskName + "> ";

            str += s;

         }
         else
         {

            str += strTaskName + "> ";

            str += s;

            str += "\n";

         }

      }
      else
      {

         str.formatf("%s> %c %s %d %s\n", strTaskName.c_str(), trace_level_char(tracestatement.m_etracelevel), tracestatement.m_pszFunction, tracestatement.m_iLine, tracestatement.as_string().c_str());

      }

      if(m_bWithTimePrefix)
      {

         ::string strTime;

         class ::time timeNow;

         timeNow.Now();

         if(m_bDisplayRelativeTime)
         {

            auto Δtime = timeNow - ::acme::get()->m_timeStart;

            ::earth::time_span earthtimepan(Δtime);

            if(earthtimepan.days() <= 0)
            {

               strTime.formatf("%02d:%02d:%02d %03d ",
                              earthtimepan.hours(),
                              earthtimepan.minute(),
                              earthtimepan.second(),
                              Δtime.millisecond());

            }
            else
            {

               strTime.formatf("%3d %02d:%02d:%02d %03d ",
                              earthtimepan.days(),
                              earthtimepan.hour(),
                              earthtimepan.minute(),
                              earthtimepan.second(),
                              Δtime.millisecond());

            }

         }
         else
         {

            ::earth::time earthtime(timeNow);

            strTime.formatf("%04d-%02d-%02d %02d:%02d:%02d %03d ",
                           earthtime.year(),
                           earthtime.month(),
                           earthtime.day(),
                           earthtime.hour(),
                           earthtime.minute(),
                           earthtime.second(),
                           timeNow.millisecond());

         }

         if (str.begins_eat("\r"))
         {


            str = "\r"+strTime + str;

         }
         else
         {

            if (str.is_empty())
            {

               output_debug_string("WHAT?!?!(2)");

            }
            else if (str.begins("\n"))
            {

               output_debug_string("WHAT?!?!");

            }

            str = strTime + str;
         }

      }

      auto pplatform = ::platform::get();

      if ((pplatform && pplatform->is_console()) || (!::is_debugger_attached() && g_bPrintfIfDebuggerIsNotAttached))
      {

         if (tracestatement.m_etracelevel <= e_trace_level_information)
         {

            fwrite(str.c_str(), 1, str.size(), stdout);

            if(bFlush)
            {

               fflush(stdout);

            }

         }
         else
         {

            fprintf(stderr, "%s", str.c_str());

            if(bFlush)
            {

               fflush(stderr);

            }

         }

      }
      else
      {

         ::output_debug_string(str);

         ::output_debug_string_flush();

      }

   }

}




CLASS_DECL_ACME const_char_pointer e_trace_level_name(enum_trace_level elevel);

#undef DEFINE_MESSAGE

#define SIMPLE_TRACE_FUNCTION_NAME 0
#define SIMPLE_TRACE_FILE_NAME 0

CLASS_DECL_ACME void __simple_tracea(::particle * pparticle, enum_trace_level elevel, const_char_pointer pszFunction, const_char_pointer pszFileName, int iLine, const ::scoped_string & scopedstr)
{

#ifndef _DEBUG

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

      strMessage.formatf("%c:%s> %s", trace_level_char(elevel), strTopic.c_str(), scopedstr.c_str());

   }
   else
   {

      strMessage.formatf("%c> %s", trace_level_char(elevel), scopedstr.c_str());

   }

#if SIMPLE_TRACE_FUNCTION_NAME

   if (::is_set(scopedstrFunction))
   {

      strMessage += "\nFunction: ";

      strMessage += pszFunction;

   }

#endif

#if SIMPLE_TRACE_FILE_NAME

   if (::is_set(scopedstrFileName))
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

   informationf(strMessage);

}


CLASS_DECL_ACME void __simple_tracev(::particle * pparticle, enum_trace_level elevel, const_char_pointer pszFunction, const_char_pointer pszFileName, int iLine, const_char_pointer pszFormat, va_list args)
{

   //if (s_pstringmanager == nullptr)
   //{

   //   vprintf(scopedstrFormat, args);

   //   return;

   //}

   string strMessage;

   strMessage.formatf_arguments(pszFormat, args);

   __simple_tracea(pparticle, elevel, pszFunction, pszFileName, iLine, strMessage);

}

