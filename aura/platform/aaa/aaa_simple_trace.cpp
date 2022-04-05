#include "framework.h"
#include "aura/update.h"
#ifdef WINDOWS
#include <process.h>
#elif defined(LINUX)
#include <sys/types.h>
#include <unistd.h>
#endif
#include "trace_category.h"


CLASS_DECL_AURA void __simple_tracea(::matter * pobject, enum_trace_level elevel, const ::string & pszFunction, const ::string & pszFile, i32 iLine, const ::string & psz);
CLASS_DECL_AURA void __simple_tracev(::matter * pobject, enum_trace_level elevel, const ::string & pszFunction, const ::string & pszFile, i32 iLine, const ::string & pszFormat, va_list args);


//CLASS_DECL_AURA void FUNCTION_DEBUGBOX(const ::string & pszMessage, const ::string & pszTitle, const ::e_message_box & emessagebox, ::callback callback)
//{
//
//   ::message_box_synchronous(nullptr, pszMessage, pszTitle, iFlags, function);
//
//}


//CLASS_DECL_AURA void FUNCTION_DEBUGBOXW(const WCHAR * pszMessage, const WCHAR * pszTitle, i32 iFlags, const ::function_arg& function)
//{
//
//   ::os_message_box_w(nullptr, pszMessage, pszTitle, iFlags, function);
//
//}




string FormatMessageFromSystem(u32 dwError)
{


   return ::get_last_error_message(dwError);


}


extern "C"
void o_debug_string(const ::string & psz)
{
   output_debug_string(psz);
}


CLASS_DECL_AURA void trace(enum_trace_level elevel, const ::string & pszTag, const ::string & pszText, const ::string & pszFile, int iLine)
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



int g_iMemoryCounters = -1;

CLASS_DECL_AURA::mutex * g_pmutexMemoryCounters = nullptr;

int g_iMemoryCountersStartable = 0;

CLASS_DECL_AURA bool memory_counter_on()
{

   if (g_iMemoryCountersStartable && g_iMemoryCounters < 0)
   {

      g_iMemoryCounters = m_psystem->m_pacmefile->exists(         auto psystem = m_psystem;

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->config() / "system/memory_counters.txt") ? 1 : 0;

      if (g_iMemoryCounters)
      {

         g_pmutexMemoryCounters = new ::mutex(e_create_new, nullptr, false, "Global\\ca2_memory_counters");

      }

   }

   return g_iMemoryCountersStartable && g_iMemoryCounters;

}


::file::path * g_pMemoryCounters = nullptr;


CLASS_DECL_AURA::file::path memory_counter_base_path()
{

   if (g_iMemoryCountersStartable && g_pMemoryCounters == nullptr)
   {

      g_pMemoryCounters = new ::file::path();

#if defined(_UWP)

      string strBasePath =          auto psystem = m_psystem;

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "memory_counters";

#else

      ::file::path strModule = module_path_from_pid(getpid());

      string strBasePath =          auto psystem = m_psystem;

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "memory_counters" / strModule.title() / __string(getpid());

#endif

      * g_pMemoryCounters = strBasePath;

   }

   return *g_pMemoryCounters;

}



simple_trace::simple_trace()
{

#ifdef _DEBUG

   //INFORMATION("Starting Simple Alog");

#endif

}


simple_trace::~simple_trace()
{

   //INFORMATION("Ending Simple Alog");

}


void simple_trace::__tracea(::matter * pobject, enum_trace_level elevel, const ::string & pszFunction, const ::string & pszFile, int iLine, const ::string & psz)
{

   __simple_tracea(pobject, elevel, pszFunction, pszFile, iLine, psz);
   //printf("%d %c %s %d %s", (i32)ecategory, e_trace_level_char(elevel), pszFunction, iLine, psz);

}


CLASS_DECL_AURA const char * trace_category_name(e_trace_category ecategory)
{

   if (ecategory < trace_category_first && ecategory < trace_category_count)
   {

      return nullptr;

   }

   return trace_category::s_ptracecategorya->element_at((iptr)ecategory)->m_strTopicText;

}


CLASS_DECL_AURA bool enable_trace_category(e_trace_category ecategory, bool bEnable)
{

   trace_category::s_ptracecategorya->element_at((iptr)ecategory)->m_bEnable = bEnable;

   return true;

}


CLASS_DECL_AURA int_bool c_enable_trace_category(e_trace_category ecategory, int_bool iEnable)
{

   if (!enable_trace_category(ecategory, iEnable != false))
   {

      return false;

   }

   return true;

}


CLASS_DECL_AURA::matter * general_trace_object()
{

   return trace_category::s_ptracecategorya->element_at(0);

}


CLASS_DECL_AURA::matter * trace_object(e_trace_category ecategory)
{

   return trace_category::s_ptracecategorya->element_at((iptr)ecategory);

}


const char * g_pszTraceLevelName[] =
{

   "none",
   "info",
   "warning",
   "error",
   "fatal",
   "undefined log level"

};


char g_chaTraceLevel[] =
{

   ' ',
   'I',
   'W',
   'E',
   'F',
   'U'

};



