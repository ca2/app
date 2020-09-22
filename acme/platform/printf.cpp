// print formatted.cpp

// based on:
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001

// 08/12/06 (mv)

#include "framework.h"
//#include <wchar.h>
#include <stdio.h>
#include <stdarg.h>



i32 printf_dup(const char *format, ...)
{
   va_list args;
   va_start(args, format);
   i32 ret = vprintf(format, args);
   va_end(args);

   return ret;
}

i32 wprintf_dup(const widechar *format, ...)
{
   va_list args;
   va_start(args, format);
   i32 ret = vwprintf(format, args);
   va_end(args);

   return ret;
}



i32 vprintf_dup(const char *format, va_list args)
{

   return vprintf(format, args);

}


i32 vwprintf_dup(const widechar *format, va_list args)
{

   return vwprintf(format, args);

}


#ifdef __APPLE__

::mutex * g_pmutexCvt = nullptr;

i32 ecvt_r(double d, int i, int *__restrict pi1, int *__restrict pi2, char * sz, size_t size) /* LEGACY */
{

   sync_lock ml(g_pmutexCvt);

   char * psz = ecvt(d, i, pi1, pi2);

   if(psz == nullptr)
      return -1;

   if(strlen(psz) > (size - 1))
      return -1;

   strcpy(sz, psz);

   return 0;

}

i32 fcvt_r(double d, int i, int *__restrict pi1, int *__restrict pi2, char * sz, size_t size) /* LEGACY */
{

   sync_lock ml(g_pmutexCvt);

   char * psz = fcvt(d, i, pi1, pi2);

   if(psz == nullptr)
      return -1;

   if(strlen(psz) > (size - 1))
      return -1;

   strcpy(sz, psz);

   return 0;

}

#endif
