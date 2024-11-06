// print formatted.cpp

// based on:
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001

// 08/12/06 (mv)

#include "framework.h"
#include <wchar.h>
#include <stdio.h>
#include <stdarg.h>
#include "acme/parallelization/synchronous_lock.h"


int printf_dup(const char *format, ...)
{
   va_list args;
   va_start(args, format);
   int ret = vprintf(format, args);
   va_end(args);

   return ret;
}


int wprintf_dup(const ::wide_character *format, ...)
{
   va_list args;
   va_start(args, format);
   int ret = vwprintf(format, args);
   va_end(args);

   return ret;
}



int vprintf_dup(const char *format, va_list args)
{

   return vprintf(format, args);

}


int vwprintf_dup(const ::wide_character *format, va_list args)
{

   return vwprintf(format, args);

}

//
//#ifdef __APPLE__
//
//::pointer< ::mutex > g_pmutexCvt = nullptr;
//
//int ecvt_r(double d, int i, int *__restrict pi1, int *__restrict pi2, char * sz, size_t size) /* LEGACY */
//{
//
//   synchronous_lock ml(g_pmutexCvt);
//
//   char * psz = ecvt(d, i, pi1, pi2);
//
//   if(psz == nullptr)
//      return -1;
//
//   if(strlen(psz) > (size - 1))
//      return -1;
//
//   strcpy(sz, psz);
//
//   return 0;
//
//}
//
//int fcvt_r(double d, int i, int *__restrict pi1, int *__restrict pi2, char * sz, size_t size) /* LEGACY */
//{
//
//   synchronous_lock ml(g_pmutexCvt);
//
//   char * psz = fcvt(d, i, pi1, pi2);
//
//   if(psz == nullptr)
//      return -1;
//
//   if(strlen(psz) > (size - 1))
//      return -1;
//
//   strcpy(sz, psz);
//
//   return 0;
//
//}
//
//#endif
