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


::i32 printf_dup(const_char_pointer format, ...)
{
   va_list args;
   va_start(args, format);
   ::i32 ret = vprintf(format, args);
   va_end(args);

   return ret;
}


::i32 wprintf_dup(const ::wide_character *format, ...)
{
   va_list args;
   va_start(args, format);
   ::i32 ret = vwprintf(format, args);
   va_end(args);

   return ret;
}



::i32 vprintf_dup(const_char_pointer format, va_list args)
{

   return vprintf(format, args);

}


::i32 vwprintf_dup(const ::wide_character *format, va_list args)
{

   return vwprintf(format, args);

}

//
//#ifdef __APPLE__
//
//::pointer< ::mutex > g_pmutexCvt = nullptr;
//
//::i32 ecvt_r(::f64 d, ::i32 i, ::i32 *__restrict pi1, ::i32 *__restrict pi2, char_pointer sz, size_t size) /* LEGACY */
//{
//
//   synchronous_lock ml(g_pmutexCvt, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//   char_pointer psz = ecvt(d, i, pi1, pi2);
//
//   if(scopedstr == nullptr)
//      return -1;
//
//   if(strlen(scopedstr) > (size - 1))
//      return -1;
//
//   strcpy(sz, psz);
//
//   return 0;
//
//}
//
//::i32 fcvt_r(::f64 d, ::i32 i, ::i32 *__restrict pi1, ::i32 *__restrict pi2, char_pointer sz, size_t size) /* LEGACY */
//{
//
//   synchronous_lock ml(g_pmutexCvt, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//   char_pointer psz = fcvt(d, i, pi1, pi2);
//
//   if(scopedstr == nullptr)
//      return -1;
//
//   if(strlen(scopedstr) > (size - 1))
//      return -1;
//
//   strcpy(sz, psz);
//
//   return 0;
//
//}
//
//#endif
