#include "framework.h"
#include "acme/id.h"


CLASS_DECL_APEX void __simple_tracev(e_trace_category ecategory, e_trace_level elevel, const char* pszFunction, const char* pszFile, i32 iLine, const char* pszFormat, va_list args);
CLASS_DECL_APEX void __simple_tracea(e_trace_category ecategory, e_trace_level elevel, const char* pszFunction, const char* pszFileName, i32 iLine, const char* psz);
CLASS_DECL_APEX void __simple_tracev(element* pobject, e_trace_level elevel, const char* pszFunction, const char* pszFile, i32 iLine, const char* pszFormat, va_list args);
CLASS_DECL_APEX void __simple_tracea(element* pobject, e_trace_level elevel, const char* pszFunction, const char* pszFileName, i32 iLine, const char* psz);


//#include "apex/update.h"
//#ifdef WINDOWS
//#include <process.h>
//#elif defined(LINUX)
//#include <sys/types.h>
//#include <unistd.h>
//#endif
//#include "trace_category.h"
//#include "simple_trace.h"
//
//
//
//
//
//void debug_object_event_promisse_pred()
//{
//
//   //::object o;
//
//   //::context_object * po = new context_object();
//
//   //// 2 arguments
//   //o.treat(ok, po, [&](auto & result) { output_debug_string("o += ok..."); return success; } };
//
//   //// 3 arguments
//   //o += { ok, id_text, [&](auto & result) { output_debug_string("o += ok, id_text ..."); return ::success; } };
//
//
//   //__pointer(::object) pobject;
//
//   //__keep(pobject, nullptr);
//   ////   // 4 arguments
//   ////   o += { ok, id_text, [&](auto pobject) { ASSERT(pobject == &o); output_debug_string("o += ok, id_text, &o ...");  } };
//
//
//}
//
//
//void system_call_update_wallpaper_changed()
//{
//
//   ::get_context_system()->call_update(id_wallpaper_changed);
//
//}


void system_call_update_app_activated()
{

   ::get_context_system()->call_update(id_app_activated);

}


//void system_call_update_app_changed_occlusion_state()
//{
//
//   ::get_context_system()->call_update(id_app_changed_occlusion_state);
//
//}
//
//
//
//
//
////
////
////void debug_id_eid()
////{
////
////   auto pupdate = new_update();
////
////   pupdate->value(id_filter) = "*.jpg";
////
////}
//
//
//
//
//
//


CLASS_DECL_APEX void __tracea(::element * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * psz)
{

   if (::is_null(::get_context_system()))
   {

      __simple_tracea(pobject, elevel, pszFunction, pszFile, iLine, psz);

      return;

   }

   ::get_context_system()->__tracea(pobject, elevel, pszFunction, pszFile, iLine, psz);

}


CLASS_DECL_APEX void __tracef(::element * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, ...)
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


CLASS_DECL_APEX void __tracev(::element * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list args)
{

   if (::is_null(::get_context_system()))
   {

      __simple_tracev(pobject, elevel, pszFunction, pszFile, iLine, pszFormat, args);

      return;

   }

   ::get_context_system()->__tracev(pobject, elevel, pszFunction, pszFile, iLine, pszFormat, args);

}

//
//
//
//
//
