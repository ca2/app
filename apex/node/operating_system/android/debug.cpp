#include "framework.h"

#include <android/log.h>


CLASS_DECL_APEX void simple_debug_print(const char * psz)
{

   __android_log_print(ANDROID_LOG_INFO, "simple_debug_string", "%s", psz);

}




CLASS_DECL_APEX int os_trace_level(enum_trace_level elevel)
{

   switch(elevel)
   {
   case e_trace_level_error:
      return ANDROID_LOG_ERROR;
   case e_trace_level_warning:
      return ANDROID_LOG_WARN;
   case e_trace_level_information:
      return ANDROID_LOG_INFO;
   default:
      return ANDROID_LOG_DEBUG;
   }

}


CLASS_DECL_APEX void os_trace(enum_trace_level elevel, const char * pszTag, const char * pszMessage)
{

   int iLevel = os_trace_level(elevel);

   __android_log_print(iLevel, pszTag, "%s", pszMessage);

}




::u32
WINAPI
FormatMessage(
::u32 dwFlags,
const void * lpSource,
::u32 dwMessageId,
::u32 dwLanguageId,
char * lpBuffer,
::u32 nSize,
va_list *Arguments
)
{


   return 0;


}
