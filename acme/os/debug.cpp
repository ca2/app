#include "framework.h"


//CLASS_DECL_ACME void __simple_tracev(e_trace_category ecategory, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list args);
//CLASS_DECL_ACME void __simple_tracea(e_trace_category ecategory, e_trace_level elevel, const char * pszFunction, const char *pszFileName, i32 iLine, const char * psz);
//CLASS_DECL_ACME void __simple_tracev(generic * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list args);
//CLASS_DECL_ACME void __simple_tracea(generic * pobject, e_trace_level elevel, const char * pszFunction, const char *pszFileName, i32 iLine, const char * psz);




//char os_trace_level_char(e_trace_level elevel)
//{
//
//   switch (elevel)
//   {
//   case level_info:
//      return 'I';
//   case level_warning:
//      return 'W';
//   case level_error:
//      return 'E';
//   default:
//      return 'D';
//   }
//
//}

#ifndef ANDROID




CLASS_DECL_ACME e_trace_level trace_level_constraint(e_trace_level elevel)
{

   return ::papaya::constraint(elevel, trace_level_none, trace_level_count);

}


extern const char * g_pszTraceLevelName[];


CLASS_DECL_ACME const char * trace_level_name(e_trace_level elevel)
{

   return g_pszTraceLevelName[trace_level_constraint(elevel)];

}


extern char g_chaTraceLevel[];;;


CLASS_DECL_ACME char trace_level_char(e_trace_level elevel)
{

   return g_chaTraceLevel[trace_level_constraint(elevel)];

}

void os_trace(e_trace_level elevel, const char* pszTag, const char* psz)
{

   string strMessage;

   string strTag;

   strTag = strTag.Left(23);

   strTag = string(' ', max(0, 23 - strTag.get_length()));

   strMessage.Format("-%c- %s %s\n", trace_level_char(elevel), strTag.c_str(), psz);

   output_debug_string(strMessage);

}





void simple_debug_print(const char* psz)
{

   os_trace(trace_level_information, "simple_debug_string", psz);

}


#endif



#ifndef ANDROID
//
//void os_trace(e_trace_level elevel, const char * pszTag, const char * psz)
//{
//
//   string strMessage;
//
//   string strTag;
//
//   strTag = strTag.Left(23);
//
//   strTag = string(' ', MAX(0, 23 - strTag.get_length()));
//
//   strMessage.Format("-%c- %s %s\n", trace_level_char(elevel), strTag.c_str(), psz);
//
//   output_debug_string(strMessage);
//
//}
//



//
//void simple_debug_print(const char * psz)
//{
//
////   os_trace(trace_level_information, "simple_debug_string", psz);
//   output_debug_string(psz);
//
//}


#endif


