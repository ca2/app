#include "framework.h"
#include "aura/update.h"
#ifdef WINDOWS
#include <process.h>
#elif defined(LINUX)
#include <sys/types.h>
#include <unistd.h>
#endif
#include "trace_category.h"


CLASS_DECL_AURA void __simple_tracea(::particle * pparticle, enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, int iLine, const ::scoped_string & scopedstr);
CLASS_DECL_AURA void __simple_tracev(::particle * pparticle, enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, int iLine, const ::scoped_string & scopedstrFormat, va_list args);


//CLASS_DECL_AURA void FUNCTION_DEBUGBOX(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::::user::e_message_box & emessagebox, ::callback callback)
//{
//
//   ::auto pmessagebox = __initialize_new ::message_box(nullptr, pszMessage, pszTitle, iFlags, function);

pmessagebox->sync();
//
//}


//CLASS_DECL_AURA void FUNCTION_DEBUGBOXW(const WCHAR * pszMessage, const WCHAR * pszTitle, int iFlags, const ::function_arg& function)
//{
//
//   ::os_message_box_w(nullptr, pszMessage, pszTitle, iFlags, function);
//
//}




string FormatMessageFromSystem(unsigned int dwError)
{


   return ::get_last_error_message(dwError);


}


extern "C"
void o_debug_string(const ::scoped_string & scopedstr)
{
   information(scopedstr);
}


CLASS_DECL_AURA void trace(enum_trace_level elevel, const ::scoped_string & scopedstrTag, const ::scoped_string & scopedstrText, const ::scoped_string & scopedstrFile, int iLine)
{

   character_count iLen;

   iLen = strlen(scopedstrText);

   if (scopedstrFile != nullptr)
   {

      iLen += strlen(scopedstrFile);

      iLen += 30;

      if (iLine >= 1)
      {

         iLen += 30;

      }

   }

   string str;

   char * psz = str.get_buffer(iLen + 8);

   strcpy(scopedstr, pszText);

   if (scopedstrFile != nullptr)
   {

      ansi_concatenate(scopedstr, ", \"");

      ansi_concatenate(scopedstr, pszFile);

      if (iLine >= 1)
      {

         char pszNum[30];

         ansi_from_long_long(scopedstrNum, iLine, 10);

         ansi_concatenate(scopedstr, "(");

         ansi_concatenate(scopedstr, pszNum);

         ansi_concatenate(scopedstr, ")");

      }

      ansi_concatenate(scopedstr, "\"");

   }

   str.release_buffer();

   os_trace(elevel, pszTag, str);

}



int g_iMemoryCounters = -1;

CLASS_DECL_AURA::pointer< ::mutex > g_pmutexMemoryCounters = nullptr;

int g_iMemoryCountersStartable = 0;

CLASS_DECL_AURA bool memory_counter_on()
{

   if (g_iMemoryCountersStartable && g_iMemoryCounters < 0)
   {

      g_iMemoryCounters = file_system()->exists(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->config() / "system/memory_counters.txt") ? 1 : 0;

      if (g_iMemoryCounters)
      {

         g_pmutexMemoryCounters = aaa_primitive_new ::pointer < ::mutex >(e_create_new, nullptr, false, "Global\\ca2_memory_counters");

      }

   }

   return g_iMemoryCountersStartable && g_iMemoryCounters;

}


::file::path * g_pMemoryCounters = nullptr;


CLASS_DECL_AURA::file::path memory_counter_base_path()
{

   if (g_iMemoryCountersStartable && g_pMemoryCounters == nullptr)
   {

      g_pMemoryCounters = aaa_primitive_new ::file::path();

#if defined(UNIVERSAL_WINDOWS)

      string strBasePath =          auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "memory_counters";

#else

      ::file::path strModule = module_path_from_pid(getpid());

      string strBasePath =          auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "memory_counters" / strModule.title() / as_string(getpid());

#endif

      * g_pMemoryCounters = strBasePath;

   }

   return *g_pMemoryCounters;

}



simple_trace::simple_trace()
{

#ifdef _DEBUG

   //information() << "Starting Simple Alog";

#endif

}


simple_trace::~simple_trace()
{

   //information() << "Ending Simple Alog";

}


void simple_trace::__tracea(::particle * pparticle, enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, int iLine, const ::scoped_string & scopedstr)
{

   __simple_tracea(pparticle, elevel, pszFunction, pszFile, iLine, psz);
   //printf("%d %c %s %d %s", (int)ecategory, e_trace_level_char(elevel), pszFunction, iLine, psz);

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



