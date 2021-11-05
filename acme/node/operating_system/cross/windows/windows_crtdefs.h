/*
 * CRT definitions
 *
 * Copyright 2000 Francois Gouget.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef __WINE_CRTDEFS_H
#define __WINE_CRTDEFS_H

#ifndef __WINE_USE_MSVCRT
#define __WINE_USE_MSVCRT
#endif

#ifdef __WINE_WINE_PORT_H
# error You cannot use both wine/port.h and msvcrt headers
#endif

#if defined(__x86_64__) && !defined(OS64BIT)
#define OS64BIT
#endif

//#if !defined(_MSC_VER) && !defined(INT64)
//# if defined(OS64BIT) && !defined(__MINGW64__)
//#   define INT64 long
//# else
//#   define INT64 long long
//# endif
//#endif

#ifndef __stdcall
# ifdef __i386__
#  ifdef __GNUC__
#   ifdef __APPLE__ /* Mac OS X uses a 16-byte aligned stack and not a 4-byte one */
#    define __stdcall __attribute__((__stdcall__)) __attribute__((__force_align_arg_pointer__))
#   else
#    define __stdcall __attribute__((__stdcall__))
#   endif
#  elif defined(_MSC_VER)
    /* Nothing needs to be done. __stdcall already exists */
#  else
#   error You need to define __stdcall for your compiler
#  endif
# elif defined(__x86_64__) && defined (__GNUC__)
#  define __stdcall __attribute__((ms_abi))
# else
#  define __stdcall
# endif
#endif /* __stdcall */

#ifndef __cdecl
# if defined(__i386__) && defined(__GNUC__)
#  ifdef __APPLE__ /* Mac OS X uses 16-byte aligned stack and not a 4-byte one */
#   define __cdecl __attribute__((__cdecl__)) __attribute__((__force_align_arg_pointer__))
#  else
#   define __cdecl __attribute__((__cdecl__))
#  endif
# elif defined(__x86_64__) && defined (__GNUC__)
#  define __cdecl __attribute__((ms_abi))
# elif !defined(_MSC_VER)
#  define __cdecl
# endif
#endif /* __cdecl */

#ifndef __ms_va_list
# if defined(__x86_64__) && defined (__GNUC__)
#  define __ms_va_list __builtin_ms_va_list
#  define __ms_va_start(list,arg) __builtin_ms_va_start(list,arg)
#  define __ms_va_end(list) __builtin_ms_va_end(list)
# else
#  define __ms_va_list va_list
#  define __ms_va_start(list,arg) va_start(list,arg)
#  define __ms_va_end(list) va_end(list)
# endif
#endif

#ifndef DECLSPEC_ALIGN
# if defined(_MSC_VER) && (_MSC_VER >= 1300) && !defined(MIDL_PASS)
#  define DECLSPEC_ALIGN(x) __declspec(align(x))
# elif defined(__GNUC__)
#  define DECLSPEC_ALIGN(x) __attribute__((aligned(x)))
# else
#  define DECLSPEC_ALIGN(x)
# endif
#endif

#ifndef _MSVCRT_LONG_DEFINED
#define _MSVCRT_LONG_DEFINED
/* we need 32-bit longs even on 64-bit */
typedef i32 __msvcrt_long;
typedef u32 __msvcrt_ulong;
#endif

/*
#ifndef _INTPTR_T_DEFINED
#ifdef  OS64BIT
typedef ::i64 intptr_t;
#else
typedef i32 intptr_t;
#endif
#define _INTPTR_T_DEFINED
#endif

#ifndef _::u32PTR_T_DEFINED
#ifdef  OS64BIT
typedef ::u64 ::u32ptr_t;
#else
typedef u32 ::u32ptr_t;
#endif
#define _::u32PTR_T_DEFINED
#endif
 */

//#ifndef _PTRDIFF_T_DEFINED
//#ifdef OS64BIT
//typedef i64 ptrdiff_t;
//#else
//typedef i32 ptrdiff_t;
//#endif
//#define _PTRDIFF_T_DEFINED
//#endif


//#ifndef _SIZE_T_DEFINED
//#ifdef OS64BIT
//typedef ::u64 size_t;
//#else
//typedef u32 size_t;
//#endif
//#define _SIZE_T_DEFINED
//#endif


#ifndef _TIME32_T_DEFINED
typedef __msvcrt_long __time32_t;
#define _TIME32_T_DEFINED
#endif

//#if !defined(_TIME64_T_DEFINED) && !defined(ANDROID)
//typedef ::i64 DECLSPEC_ALIGN(8) time_t;
//#define _TIME64_T_DEFINED
//#endif

#ifdef _USE_32BIT_TIME_T
# ifdef OS64BIT
#  error You cannot use 32-bit time_t in Win64
# endif
#elif !defined(OS64BIT)
# define _USE_32BIT_TIME_T
#endif

/*
#ifndef _TIME_T_DEFINED
#ifdef _USE_32BIT_TIME_T
typedef __time32_t time_t;
#else
typedef time_t time_t;
#endif
#define _TIME_T_DEFINED
#endif

*/

//#if !defined(_WCHAR_T_DEFINED)  && !defined(ANDROID)
//#ifndef __cplusplus
//typedef unsigned short unichar;
//#endif
//#define _WCHAR_T_DEFINED
//#endif

#ifndef _WCTYPE_T_DEFINED
typedef unsigned short  wint_t;
typedef unsigned short  wctype_t;
#define _WCTYPE_T_DEFINED
#endif

#ifndef _ERRNO_T_DEFINED
//typedef i32 errno_t;
#define _ERRNO_T_DEFINED
#endif

struct threadlocaleinfostruct;
struct threadmbcinfostruct;
typedef struct threadlocaleinfostruct *pthreadlocinfo;
typedef struct threadmbcinfostruct *pthreadmbcinfo;

typedef struct localeinfo_struct
{
    pthreadlocinfo locinfo;
    pthreadmbcinfo mbcinfo;
} _locale_tstruct, *_locale_t;

#ifndef _TAGLC_ID_DEFINED
typedef struct tagLC_ID {
    unsigned short wLanguage;
    unsigned short wCountry;
    unsigned short wCodePage;
} LC_ID, *LPLC_ID;
#define _TAGLC_ID_DEFINED
#endif

#undef lconv

//#ifndef _THREADLOCALEINFO
//typedef struct threadlocaleinfostruct {
//    i32 refcount;
//    u32 lc_codepage;
//    u32 lc_collate_cp;
//    unsigned long lc_handle[6];
//    LC_ID lc_id[6];
//    struct {
//        char *locale;
//        unichar *wlocale;
//        i32 *refcount;
//        i32 *wrefcount;
//    } lc_category[6];
//    i32 lc_clike;
//    i32 mb_cur_max;
//    i32 *lconv_intl_refcount;
//    i32 *lconv_num_refcount;
//    i32 *lconv_mon_refcount;
//    struct lconv *lconv;
//    i32 *ctype1_refcount;
//    unsigned short *ctype1;
//    const unsigned short *pctype;
//    const unsigned char *pclmap;
//    const unsigned char *pcumap;
//    struct __lc_time_data *lc_time_curr;
//} threadlocinfo;
//#define _THREADLOCALEINFO
//#define lconv system_lconv
//#endif

#endif /* __WINE_CRTDEFS_H */
