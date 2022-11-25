#include "acme/parallelization/synchronous_lock.h"

#include <android/log.h>


//static string * m_pstrOutputDebugStringA = nullptr;
::pointer< ::particle > g_pmutexOutputDebugStringA;

void output_debug_string(const char * lpOutputString)
{

   synchronous_lock synchronouslock(g_pmutexOutputDebugStringA);

   //if (m_pstrOutputDebugStringA == nullptr)
   //{

   //   m_pstrOutputDebugStringA = memory_new string();

   //}

   //m_pstrOutputDebugStringA->operator +=(lpOutputString);

   //// very lazy implementation

   //string_array stra;

   //stra.add_lines(*m_pstrOutputDebugStringA);

   //if (stra.get_count() > 0)
   //{

   //   *m_pstrOutputDebugStringA = stra.pop();

   //   if (stra.get_count() > 0)
   //   {

   //      for (auto str : stra)
   //      {

   //__android_log_print(ANDROID_LOG_INFO, "output_debug_string", str);

   __android_log_print(ANDROID_LOG_INFO,"output_debug_string", "%s", lpOutputString);

   //      }

   //   }

   //}


}


CLASS_DECL_ACME void simple_debug_print(const char * psz)
{

   __android_log_print(ANDROID_LOG_INFO, "simple_debug_string", "%s", psz);

}


void output_debug_string(const widechar * lpOutputString)
{


   output_debug_string(string(lpOutputString));


}


CLASS_DECL_ACME int os_trace_level(enum_trace_level elevel)
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


CLASS_DECL_ACME void os_trace(enum_trace_level elevel, const char * pszTag, const char * pszMessage)
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


//void debug_break()
//{
//
//#ifdef __arm__
//
//   __asm__("BKPT");
//
//#else
//
//   asm("int $3");
//
//#endif
//
//}



