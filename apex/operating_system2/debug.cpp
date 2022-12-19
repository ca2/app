#include "framework.h"


//CLASS_DECL_APEX void __simple_tracev(e_trace_category ecategory, enum_trace_level elevel, const scoped_string & strFunction, const scoped_string & strFile, i32 iLine, const scoped_string & strFormat, va_list args);
//CLASS_DECL_APEX void __simple_tracea(e_trace_category ecategory, enum_trace_level elevel, const scoped_string & strFunction, const char *pszFileName, i32 iLine, const scoped_string & str);
//CLASS_DECL_APEX void __simple_tracev(::particle * pparticle, enum_trace_level elevel, const scoped_string & strFunction, const scoped_string & strFile, i32 iLine, const scoped_string & strFormat, va_list args);
//CLASS_DECL_APEX void __simple_tracea(::particle * pparticle, enum_trace_level elevel, const scoped_string & strFunction, const char *pszFileName, i32 iLine, const scoped_string & str);




//char os_trace_level_char(enum_trace_level elevel)
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



//CLASS_DECL_APEX void __tracea(::particle * pparticle, enum_trace_level elevel, const scoped_string & strFunction, const scoped_string & strFile, i32 iLine, const scoped_string & str)
//{
//
//   if (::is_null(::psystem))
//   {
//
//      __simple_tracea(pparticle, elevel, pszFunction, pszFile, iLine, psz);
//
//      return;
//
//   }
//
//   psystem->__tracea(pparticle, elevel, pszFunction, pszFile, iLine, psz);
//
//}
//
//CLASS_DECL_APEX void __tracef(::particle * pparticle, enum_trace_level elevel, const scoped_string & strFunction, const scoped_string & strFile, i32 iLine, const scoped_string & strFormat, ...)
//{
//
//   va_list list;
//
//   va_start(list, pszFormat);
//
//   try
//   {
//
//      __tracev(pparticle, elevel, pszFunction, pszFile, iLine, pszFormat, list);
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
//
//
//CLASS_DECL_APEX void __tracev(::particle * pparticle, enum_trace_level elevel, const scoped_string & strFunction, const scoped_string & strFile, i32 iLine, const scoped_string & strFormat, va_list args)
//{
//
//   if (::is_null(::psystem))
//   {
//
//      __simple_tracev(pparticle, elevel, pszFunction, pszFile, iLine, pszFormat, args);
//
//      return;
//
//   }
//
//   psystem->__tracev(pparticle, elevel, pszFunction, pszFile, iLine, pszFormat, args);
//
//}
//
//
//
//
//
//
