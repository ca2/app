#include "framework.h"
#include "acme/constant/id.h"
#include "acme/exception/extended_status.h"
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

   //::matter * po = __new matter();

   //// 2 arguments
   //o.treat(ok, po, [&](auto & result) { informationf("o += ok..."); return success; } };

   //// 3 arguments
   //o += { ok, id_text, [&](auto & result) { informationf("o += ok, id_text ..."); return ::success; } };


   //::pointer<::matter>pparticle;

   //KEEP(pparticle, nullptr);
   ////   // 4 arguments
   ////   o += { ok, id_text, [&](auto pparticle) { ASSERT(pparticle == &o); informationf("o += ok, id_text, &o ...");  } };


}


//void system_call_update_wallpaper_changed()
//{
//
//   system()->call_subject(id_wallpaper_changed);
//
//}
//
//
//void system_call_update_app_activated()
//{
//
//   system()->call_subject(id_app_activated);
//
//}


//
//#ifdef _DEBUG
//
//
//static bool g_bVerbose = true;
//
//
//#else
//
//
//static bool g_bVerbose = false;
//
//
//#endif
//
//
//CLASS_DECL_ACME bool is_verbose()
//{
//
//   return g_bVerbose;
//
//}
//
//
//void set_verbose(bool bVerbose)
//{
//
//   g_bVerbose = bVerbose;
//
//}


CLASS_DECL_ACME void debug_print(const char * pszFormat, ...)
{

   if (is_null(pszFormat, 1024))
   {

      return;

   }

   va_list args;

   va_start(args, pszFormat);

   string str;

   str.formatf_arguments(pszFormat, args);

   ::acme::get()->platform()->informationf(str);

   va_end(args);

}



::e_status _003CountStatus(::collection::count countSuccess, ::collection::count countFailed)
{

   ::collection::count countTotal = countFailed + countSuccess;

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


string get_status_message(const ::e_status & estatus)
{
   
   // if(estatus == ::success)
   // {
      
   //    return "success";
      
   // }
   // else if(estatus == ::error_failed)
   // {
    
   //    return "error_failed";
      
   // }
      
   // string str;
      
   // if(estatus)
   // {
    
   //    str.formatf("success status (%" PRId64 ")", (::i64) estatus.m_estatus);
      
   // }
   // else
   // {
         
   //    str.formatf("failure status (%" PRId64 ")", (::i64) estatus.m_estatus);
         
   // }

   string strMessage;

   strMessage += as_string(estatus) + " ";

   strMessage += status_short_description(estatus);

   return strMessage;
  
}


// CLASS_DECL_ACME ::string as_string(const ::e_status & estatus)
// {

//    string str = "estatus=";

//    if(estatus == success)
//    {

//       str += "success";

//    }
//    else if(::succeeded(estatus))
//    {

//       str += "\"succeeded status=" + ::hex::lower_from(estatus) + "...\"";

//    }
//    else if(estatus == error_not_implemented)
//    {

//       str += "error_not_implemented";

//    }
//    else if(estatus == error_no_factory)
//    {

//       str += "error_no_factory";

//    }
//    else if (estatus == error_file_not_found)
//    {

//       str += "error_file_not_found";

//    }
//    else if (estatus == error_bad_path)
//    {

//       str += "error_bad_path";

//    }
//    else if (estatus == error_library_not_found)
//    {

//       str += "error_library_not_found";

//    }
//    else if(estatus == error_failed)
//    {

//       str += "error_failed";

//    }
//    else if (estatus == error_already_exists)
//    {

//       str += "error_already_exists";

//    }
//    else if (estatus == error_wrong_state)
//    {

//       str += "error_wrong_state";

//    }
//    else if(failed(estatus))
//    {

//       str += "\"failed status=" + ::hex::lower_from(estatus) + "...\"";

//    }

//    return str;

// }



