#include "framework.h"
#include "acme/exception/exception.h"
#include "acme/platform/constraint.h"
// #include "acme/primitive/string/string.h"
//#ifdef WINDOWS
#include "acme/_operating_system.h"
//#endif


CLASS_DECL_ACME enum_trace_level trace_level_constraint(enum_trace_level elevel)
{

   return minimum_maximum(elevel, e_trace_level_none, e_trace_level_count);

}


extern const char * g_pszTraceLevelName[];


CLASS_DECL_ACME const char * trace_level_name(enum_trace_level elevel)
{

   return g_pszTraceLevelName[trace_level_constraint(elevel)];

}


extern char g_chaTraceLevel[];;;


CLASS_DECL_ACME char trace_level_char(enum_trace_level elevel)
{

   return g_chaTraceLevel[trace_level_constraint(elevel)];

}


#ifndef ANDROID



void os_trace(enum_trace_level elevel, const ::scoped_string & scopedstrTag, const ::scoped_string & scopedstr)
{

   string strMessage;

   string strTag;

   strTag = strTag.left(23);

   strTag = string(' ', maximum(0, 23 - strTag.length()));

   strMessage.format("-%c- %s %s\n", trace_level_char(elevel), strTag.c_str(), ::string(scopedstr).c_str());

   output_debug_string(strMessage);

}





void simple_debug_print(const ::scoped_string & scopedstr)
{

   os_trace(e_trace_level_information, "simple_debug_string", scopedstr);

}


#endif



#ifndef ANDROID
//
//void os_trace(enum_trace_level elevel, const ::scoped_string & scopedstrTag, const ::scoped_string & scopedstr)
//{
//
//   string strMessage;
//
//   string strTag;
//
//   strTag = strTag.left(23);
//
//   strTag = string(' ', maximum(0, 23 - strTag.length()));
//
//   strMessage.format("-%c- %s %s\n", e_trace_level_char(elevel), strTag.c_str(), psz);
//
//   output_debug_string(strMessage);
//
//}
//



//
//void simple_debug_print(const ::scoped_string & scopedstr)
//{
//
////   os_trace(e_trace_level_information, "simple_debug_string", psz);
//   output_debug_string(psz);
//
//}


#endif

//
//thread_local void t_estatusLast = ::success;
//
//
//CLASS_DECL_ACME void get_last_status()
//{
//
//    return t_estatusLast;
//
//}
//
//
//CLASS_DECL_ACME void set_last_error(::e_status estatus)
//{
//
//    t_estatusLast = estatus;
//
//}


//CLASS_DECL_ACME void output_debug_string(const ::scoped_string & scopedstr)
//{
//
//
//}


CLASS_DECL_ACME void output_error_message(const ::scoped_string & strMessageParam, const ::scoped_string & strTitleParam, int iMessageBox)
{

   string strMessage(strMessageParam);

   string strTitle(strTitleParam);

   if (strTitle.is_empty())
   {

      output_debug_string("ERRORMSG: " + strMessage + "\n");

   }
   else
   {

      strTitle.make_upper();

      output_debug_string("\nERROR: \"" + strTitle + "\"\nMSG: " + strMessage + "\n\n");

   }

}


void throw_last_error_exception(const ::scoped_string & scopedstrErrorMessage, DWORD dwLastError)
{

   if (dwLastError == 0)
   {

      dwLastError = ::GetLastError();

   }

   auto estatus = ::windows::last_error_status(dwLastError);

   auto errorcode = ::windows::last_error_error_code(dwLastError);

   throw ::exception(estatus, { errorcode }, scopedstrErrorMessage);

}



