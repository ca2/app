#include "framework.h"
#include "acme/id.h"
//#if !BROAD_PRECOMPILED_HEADER
//#include "acme/user/_user.h"
CLASS_DECL_ACME void __simple_tracev(e_trace_category ecategory, enum_trace_level elevel, const char* pszFunction, const char* pszFile, i32 iLine, const char* pszFormat, va_list args);
CLASS_DECL_ACME void __simple_tracea(e_trace_category ecategory, enum_trace_level elevel, const char* pszFunction, const char* pszFileName, i32 iLine, const char* psz);
CLASS_DECL_ACME void __simple_tracev(::matter* pmatter, enum_trace_level elevel, const char* pszFunction, const char* pszFile, i32 iLine, const char* pszFormat, va_list args);
CLASS_DECL_ACME void __simple_tracea(::matter* pmatter, enum_trace_level elevel, const char* pszFunction, const char* pszFileName, i32 iLine, const char* psz);

CLASS_DECL_ACME void __tracev(::matter * pmatter, enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list args);

//#endif
#include "acme/update.h"
#ifdef WINDOWS
#include <process.h>
#elif defined(LINUX)
#include <sys/types.h>
#include <unistd.h>
#endif
#include "trace_category.h"





void debug_object_event_promisse_predicate()
{

   //::matter o;

   //::matter * po = new matter();

   //// 2 arguments
   //o.treat(ok, po, [&](auto & result) { output_debug_string("o += ok..."); return success; } };

   //// 3 arguments
   //o += { ok, id_text, [&](auto & result) { output_debug_string("o += ok, id_text ..."); return ::success; } };


   //__pointer(::matter) pobject;

   //__keep(pobject, nullptr);
   ////   // 4 arguments
   ////   o += { ok, id_text, [&](auto pobject) { ASSERT(pobject == &o); output_debug_string("o += ok, id_text, &o ...");  } };


}


//void system_call_update_wallpaper_changed()
//{
//
//   System.call_subject(id_wallpaper_changed);
//
//}
//
//
//void system_call_update_app_activated()
//{
//
//   System.call_subject(id_app_activated);
//
//}
//
//
void system_call_update_app_activated()
{
   System.process_subject(id_app_activated);
}
//void system_call_update_app_changed_occlusion_state()
//{
//
//   System.call_subject(id_app_changed_occlusion_state);
//
//}







//void debug_id_eid()
//{
//
//   auto pupdate = new_update();
//
//   psubject->payload(id_filter) = "*.jpg";
//
//}








#ifdef DEBUG


static bool g_bVerbose = true;


#else


static bool g_bVerbose = false;


#endif


CLASS_DECL_ACME bool is_verbose()
{

   return g_bVerbose;

}


void set_verbose(bool bVerbose)
{

   g_bVerbose = bVerbose;

}



//extern "C"
CLASS_DECL_ACME void debug_print(const char* pszFormat, ...)
{

   if (is_ptr_null(pszFormat, 1024))
   {

      return;

   }

   va_list argList;

   va_start(argList, pszFormat);

   char sz[4096];

   vsnprintf(sz, sizeof(sz), pszFormat, argList);

   ::output_debug_string(sz);

   va_end(argList);

}




int g_iMemoryCounters = -1;

CLASS_DECL_ACME::mutex * g_pmutexMemoryCounters = nullptr;

int g_iMemoryCountersStartable = 0;

CLASS_DECL_ACME bool memcnts()
{

   if (g_iMemoryCountersStartable && g_iMemoryCounters < 0)
   {

      g_iMemoryCounters = file_exists(::dir::config() / "system/memory_counters.txt") ? 1 : 0;

      if (g_iMemoryCounters)
      {

         g_pmutexMemoryCounters = new ::mutex(e_create_new, false, "Global\\ca2_memory_counters");

      }

   }

   return g_iMemoryCountersStartable && g_iMemoryCounters;

}


::file::path* g_pMemoryCounters = nullptr;


CLASS_DECL_ACME::file::path memcnts_base_path()
{

   if (g_iMemoryCountersStartable && g_pMemoryCounters == nullptr)
   {

      g_pMemoryCounters = new ::file::path();

#if defined(_UWP)

      string strBasePath = ::dir::system() / "memory_counters";

#else

      ::file::path strModule = module_path_from_pid(getpid());

      string strBasePath = ::dir::system() / "memory_counters" / strModule.title() / __str(getpid());

#endif

      * g_pMemoryCounters = strBasePath;

   }

   return *g_pMemoryCounters;

}









CLASS_DECL_ACME void __tracea(::matter * pobject, enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * psz)
{

   if (::is_null(::get_context_system()))
   {

      __simple_tracea(pobject, elevel, pszFunction, pszFile, iLine, psz);

      return;

   }

   System.__tracea(pobject, elevel, pszFunction, pszFile, iLine, psz);

}


CLASS_DECL_ACME void __tracef(::matter * pobject, enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, ...)
{

   va_list list;

   va_start(list, pszFormat);

   try
   {

      __tracev(pobject, elevel, pszFunction, pszFile, iLine, pszFormat, list);

   }
   catch (...)
   {

   }

   va_end(list);

}


CLASS_DECL_ACME void __tracev(::matter * pobject, enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list args)
{

   if (::is_null(::get_context_system()))
   {

      __simple_tracev(pobject, elevel, pszFunction, pszFile, iLine, pszFormat, args);

      return;

   }

   System.__tracev(pobject, elevel, pszFunction, pszFile, iLine, pszFormat, args);

}

//
//
//
//
//
