#include "framework.h"


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

   strMessage.Format("-%c- %s %s\n", trace_level_char(elevel), strTag.c_str(), psz);

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
//   strMessage.Format("-%c- %s %s\n", e_trace_level_char(elevel), strTag.c_str(), psz);
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
//thread_local ::e_status t_estatusLast = ::success;
//
//
//CLASS_DECL_ACME ::e_status get_last_status()
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



