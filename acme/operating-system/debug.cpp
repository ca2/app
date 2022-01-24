#include "framework.h"
#include "acme/id.h"
//#if !BROAD_PRECOMPILED_HEADER
//#include "acme/user/_user.h"
//CLASS_DECL_ACME void __simple_tracev(e_trace_category ecategory, enum_trace_level elevel, const char* pszFunction, const char* pszFile, i32 iLine, const char* pszFormat, va_list args);
//CLASS_DECL_ACME void __simple_tracea(e_trace_category ecategory, enum_trace_level elevel, const char* pszFunction, const char* pszFileName, i32 iLine, const char* psz);

//CLASS_DECL_ACME void __tracev(const ::matter * pmatter, enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list args);

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
//   get_system()->call_subject(id_wallpaper_changed);
//
//}
//
//
//void system_call_update_app_activated()
//{
//
//   get_system()->call_subject(id_app_activated);
//
//}
//
//
//void system_call_update_app_activated()
//{
//
//   get_system()->process_subject(id_app_activated);
//
//}
//void system_call_update_app_changed_occlusion_state()
//{
//
//   get_system()->call_subject(id_app_changed_occlusion_state);
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








#ifdef _DEBUG


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




//int g_iMemoryCounters = -1;

//CLASS_DECL_ACME::mutex * g_pmutexMemoryCounters = nullptr;

//
//
//
//CLASS_DECL_ACME void __tracea(::matter * pmatter, enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * psz)
//{
//
//   //if (::is_null(::get_context_system()))
//   if (::is_null(pmatter->m_psystem))
//   {
//
//      pmatter->__simple_tracea(elevel, pszFunction, pszFile, iLine, psz);
//
//      return;
//
//   }
//
//   pmatter->m_psystem->__tracea(elevel, pszFunction, pszFile, iLine, psz);
//
//}
//

//CLASS_DECL_ACME void __tracef(const ::matter * pmatter, enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, ...)
//{
//
//   va_list list;
//
//   va_start(list, pszFormat);
//
//   try
//   {
//
//      __tracev(pmatter, elevel, pszFunction, pszFile, iLine, pszFormat, list);
//
//   }
//   catch (...)
//   {
//
//   }
//
//   va_end(list);
//
//}


//CLASS_DECL_ACME void __tracev(::matter * pmatter, enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list args)
//{
//
//   if (::is_null(pmatter->m_psystem))
//   {
//
//      pmatter->__simple_tracev(elevel, pszFunction, pszFile, iLine, pszFormat, args);
//
//      return;
//
//   }
//
//   pmatter->m_psystem->__tracev(elevel, pszFunction, pszFile, iLine, pszFormat, args);
//
//}

//
//
//
//
//


::e_status _003CountStatus(::count countSuccess, ::count countFailed)
{

   ::count countTotal = countFailed + countSuccess;

   if (countTotal <= 0)
   {

      return error_failed;

   }
   else if (countSuccess <= 0)
   {

      return error_all_failed;

   }
   else if (countSuccess == countTotal)
   {

      return success;

   }
   else if (countFailed <= countTotal / 3)
   {

      return partial_one_third_or_less_has_failed;

   }
   else if (countFailed >= 2 * countTotal / 3)
   {

      return partial_two_thirds_or_more_but_not_all_has_failed;

   }
   else
   {

      return partial_sorf_of_half_has_failed;

   }

}


string get_status_message(::e_status estatus)
{
   
   if(estatus == ::success)
   {
      
      return "success";
      
   }
   else if(estatus == ::error_failed)
   {
    
      return "error_failed";
      
   }
      
   string str;
      
   if(estatus)
   {
    
      str.format("success status (%" PRId64 ")", (::i64) estatus.m_estatus);
      
   }
   else
   {
         
      str.format("failure status (%" PRId64 ")", (::i64) estatus.m_estatus);
         
   }

   return str;
  
}


template < >
string __string(const ::enum_status & estatus)
{

   string str = "estatus=";

   if(estatus == error_not_implemented)
   {

      str += "error_not_implemented";

   }
   else if(estatus == error_no_factory)
   {

      str += "error_no_factory";

   }
   else if (estatus == error_file_not_found)
   {

      str += "error_file_not_found";

   }
   else if (estatus == error_bad_path)
   {

      str += "error_bad_path";

   }
   else if (estatus == error_library_not_found)
   {

      str += "error_library_not_found";

   }
   else if(failed(estatus))
   {

      str += "\"failed...\"";

   }
   else if(estatus == success)
   {

      str += "success";

   }
   else if(estatus == success)
   {

      str += "\"succeeded\"";

   }

   return str;

}



