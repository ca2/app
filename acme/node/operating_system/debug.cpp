#include "framework.h"
#ifdef WINDOWS
#include "acme/operating_system.h"
#endif


CLASS_DECL_ACME enum_trace_level trace_level_constraint(enum_trace_level elevel)
{

   return ::papaya::constraint(elevel, e_trace_level_none, e_trace_level_count);

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



void os_trace(enum_trace_level elevel, const char* pszTag, const char* psz)
{

   string strMessage;

   string strTag;

   strTag = strTag.Left(23);

   strTag = string(' ', maximum(0, 23 - strTag.get_length()));

   strMessage.format("-%c- %s %s\n", trace_level_char(elevel), strTag.c_str(), psz);

   output_debug_string(strMessage);

}





void simple_debug_print(const char* psz)
{

   os_trace(e_trace_level_information, "simple_debug_string", psz);

}


#endif



#ifndef ANDROID
//
//void os_trace(enum_trace_level elevel, const char * pszTag, const char * psz)
//{
//
//   string strMessage;
//
//   string strTag;
//
//   strTag = strTag.Left(23);
//
//   strTag = string(' ', maximum(0, 23 - strTag.get_length()));
//
//   strMessage.format("-%c- %s %s\n", e_trace_level_char(elevel), strTag.c_str(), psz);
//
//   output_debug_string(strMessage);
//
//}
//



//
//void simple_debug_print(const char * psz)
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
//CLASS_DECL_ACME void set_last_error(::e_status3 estatus)
//{
//
//    t_estatusLast = estatus;
//
//}


//CLASS_DECL_ACME void output_debug_string(const char * psz)
//{
//
//
//}


CLASS_DECL_ACME void output_error_message(const ansichar * pszMessage, const ansichar * pszTitle, int iMessageBox)
{

   string strMessage(pszMessage);

   string strTitle(pszTitle);

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



