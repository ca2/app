#include "framework.h"


CLASS_DECL_AURA void __simple_tracev(e_trace_category ecategory, enum_trace_level elevel, const scoped_string & strFunction, const scoped_string & strFile, i32 iLine, const scoped_string & strFormat, va_list args);
CLASS_DECL_AURA void __simple_tracea(e_trace_category ecategory, enum_trace_level elevel, const scoped_string & strFunction, const char *pszFileName, i32 iLine, const scoped_string & str);
CLASS_DECL_AURA void __simple_tracev(::particle * pparticle, enum_trace_level elevel, const scoped_string & strFunction, const scoped_string & strFile, i32 iLine, const scoped_string & strFormat, va_list args);
CLASS_DECL_AURA void __simple_tracea(::particle * pparticle, enum_trace_level elevel, const scoped_string & strFunction, const char *pszFileName, i32 iLine, const scoped_string & str);




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

#ifndef ANDROID

void os_trace(enum_trace_level elevel, const scoped_string & strTag, const scoped_string & str)
{

   string strMessage;

   string strTag;

   strTag = strTag.Left(23);

   strTag = string(' ', maximum(0, 23 - strTag.get_length()));

   strMessage.format("-%c- %s %s\n", e_trace_level_char(elevel), strTag.c_str(), psz);

   output_debug_string(strMessage);

}





void simple_debug_print(const scoped_string & str)
{

   os_trace(e_trace_level_information, "simple_debug_string", psz);

}


#endif



CLASS_DECL_AURA void __tracea(::particle * pparticle, enum_trace_level elevel, const scoped_string & strFunction, const scoped_string & strFile, i32 iLine, const scoped_string & str)
{

   if (::is_null(::get_context_system()))
   {

      __simple_tracea(pparticle, elevel, pszFunction, pszFile, iLine, psz);

      return;

   }

   ::auraacmesystem()->__tracea(pparticle, elevel, pszFunction, pszFile, iLine, psz);

}

CLASS_DECL_AURA void __tracef(::particle * pparticle, enum_trace_level elevel, const scoped_string & strFunction, const scoped_string & strFile, i32 iLine, const scoped_string & strFormat, ...)
{

   va_list list;

   va_start(list, pszFormat);

   try
   {

      __tracev(pparticle, elevel, pszFunction, pszFile, iLine, pszFormat, list);

   }
   catch (...)
   {

   }

   va_end(list);

}


CLASS_DECL_AURA void __tracev(::particle * pparticle, enum_trace_level elevel, const scoped_string & strFunction, const scoped_string & strFile, i32 iLine, const scoped_string & strFormat, va_list args)
{

   if (::is_null(::get_context_system()))
   {

      __simple_tracev(pparticle, elevel, pszFunction, pszFile, iLine, pszFormat, args);

      return;

   }

   ::auraacmesystem()->__tracev(pparticle, elevel, pszFunction, pszFile, iLine, pszFormat, args);

}






