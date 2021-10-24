/*
 * Win32 definitions for Windows NT
 *
 * Copyright 1996 Alexandre Julliard
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

#pragma once

#ifndef CROSS_WINDOWS_NT_H
#define CROSS_WINDOWS_NT_H





#include "windows_base_tsd.h"
#include "windows_guid_def.h"

#ifndef RC_INVOKED
#include <ctype.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

#ifdef _NTSYSTEM_
#define NTSYSAPI
#else
#define NTSYSAPI DECLSPEC_IMPORT
#endif

//#define NTAPI __stdcall
#define NTAPI

#ifndef MIDL_PASS
# if defined(_MSC_VER)
#  define DECLSPEC_IMPORT __declspec(dllimport)
# elif defined(__MINGW32__) || defined(__CYGWIN__)
#  define DECLSPEC_IMPORT __attribute__((dllimport))
# else
#  define DECLSPEC_IMPORT DECLSPEC_HIDDEN
# endif
#else
# define DECLSPEC_IMPORT
#endif

#ifndef DECLSPEC_NORETURN
# if defined(_MSC_VER) && (_MSC_VER >= 1200) && !defined(MIDL_PASS)
#  define DECLSPEC_NORETURN __declspec(noreturn)
# elif defined(__GNUC__)
#  define DECLSPEC_NORETURN __attribute__((noreturn))
# else
#  define DECLSPEC_NORETURN
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

#ifndef DECLSPEC_CACHEALIGN
# define DECLSPEC_CACHEALIGN DECLSPEC_ALIGN(128)
#endif

#ifndef DECLSPEC_UUID
# if defined(_MSC_VER) && (_MSC_VER >= 1100) && defined (__cplusplus)
#  define DECLSPEC_UUID(x) __declspec(uuid(x))
# else
#  define DECLSPEC_UUID(x)
# endif
#endif

#ifndef DECLSPEC_NOVTABLE
# if defined(_MSC_VER) && (_MSC_VER >= 1100) && defined(__cplusplus)
#  define DECLSPEC_NOVTABLE __declspec(novtable)
# else
#  define DECLSPEC_NOVTABLE
# endif
#endif

#ifndef DECLSPEC_SELECTANY
#if defined(_MSC_VER) && (_MSC_VER >= 1100)
#define DECLSPEC_SELECTANY __declspec(selectany)
#else
#define DECLSPEC_SELECTANY
#endif
#endif

#ifndef NOP_FUNCTION
# if defined(_MSC_VER) && (_MSC_VER >= 1210)
#  define NOP_FUNCTION __noop
# else
#  define NOP_FUNCTION (void)0
# endif
#endif

#ifndef DECLSPEC_ADDRSAFE
# if defined(_MSC_VER) && (_MSC_VER >= 1200) && (defined(_M_ALPHA) || defined(_M_AXP64))
#  define DECLSPEC_ADDRSAFE __declspec(address_safe)
# else
#  define DECLSPEC_ADDRSAFE
# endif
#endif

#ifndef FORCEINLINE
# if defined(_MSC_VER) && (_MSC_VER >= 1200)
#  define FORCEINLINE __forceinline
# elif defined(__GNUC__) && ((__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 2)))
#  define FORCEINLINE inline __attribute__((always_inline))
# else
#  define FORCEINLINE inline
# endif
#endif

#ifndef DECLSPEC_DEPRECATED
# if defined(_MSC_VER) && (_MSC_VER >= 1300) && !defined(MIDL_PASS)
#  define DECLSPEC_DEPRECATED __declspec(deprecated)
#  define DEPRECATE_SUPPORTED
# elif defined(__GNUC__) && ((__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 2)))
#  define DECLSPEC_DEPRECATED __attribute__((deprecated))
#  define DEPRECATE_SUPPORTED
# else
#  define DECLSPEC_DEPRECATED
#  undef  DEPRECATE_SUPPORTED
# endif
#endif

/* a couple of useful Wine extensions */

#ifdef _MSC_VER
# define DECLSPEC_EXPORT __declspec(dllexport)
#elif defined(__MINGW32__)
# define DECLSPEC_EXPORT __attribute__((dllexport))
#elif defined(__GNUC__) && ((__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 3)))
# define DECLSPEC_EXPORT __attribute__((visibility ("default")))
#else
# define DECLSPEC_EXPORT
#endif

#if defined(__MSC_VER) || defined(__MINGW32__) || defined(__CYGWIN__)
# define DECLSPEC_HIDDEN
#elif defined(__GNUC__) && ((__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 3)))
# define DECLSPEC_HIDDEN __attribute__((visibility ("hidden")))
#else
# define DECLSPEC_HIDDEN
#endif

#if defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3)))
#define __WINE_ALLOC_SIZE(x) __attribute__((__alloc_size__(x)))
#else
#define __WINE_ALLOC_SIZE(x)
#endif

/* Anonymous union/struct handling */

#ifndef NONAMELESSSTRUCT
# ifdef __GNUC__
   /* Anonymous struct support starts with gcc 2.96 or gcc/g++ 3.x */
#  if (__GNUC__ < 2) || ((__GNUC__ == 2) && (defined(__cplusplus) || (__GNUC_MINOR__ < 96)))
#   define NONAMELESSSTRUCT
#  endif
# elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#  define NONAMELESSSTRUCT
# endif
#endif  /* NONAMELESSSTRUCT */

#ifndef NONAMELESSUNION
# ifdef __GNUC__
   /* Anonymous unions support starts with gcc 2.96/g++ 2.95 */
#  if (__GNUC__ < 2) || ((__GNUC__ == 2) && ((__GNUC_MINOR__ < 95) || ((__GNUC_MINOR__ == 95) && !defined(__cplusplus))))
#   define NONAMELESSUNION
#  endif
# elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#  define NONAMELESSUNION
# endif
#endif  /* NONAMELESSUNION */

#ifndef NONAMELESSSTRUCT
#define DUMMYSTRUCTNAME
#define DUMMYSTRUCTNAME1
#define DUMMYSTRUCTNAME2
#define DUMMYSTRUCTNAME3
#define DUMMYSTRUCTNAME4
#define DUMMYSTRUCTNAME5
#else /* !defined(NONAMELESSSTRUCT) */
#define DUMMYSTRUCTNAME   s
#define DUMMYSTRUCTNAME1  s1
#define DUMMYSTRUCTNAME2  s2
#define DUMMYSTRUCTNAME3  s3
#define DUMMYSTRUCTNAME4  s4
#define DUMMYSTRUCTNAME5  s5
#endif /* !defined(NONAMELESSSTRUCT) */

#ifndef NONAMELESSUNION
#define DUMMYUNIONNAME
#define DUMMYUNIONNAME1
#define DUMMYUNIONNAME2
#define DUMMYUNIONNAME3
#define DUMMYUNIONNAME4
#define DUMMYUNIONNAME5
#define DUMMYUNIONNAME6
#define DUMMYUNIONNAME7
#define DUMMYUNIONNAME8
#else /* !defined(NONAMELESSUNION) */
#define DUMMYUNIONNAME   u
#define DUMMYUNIONNAME1  u1
#define DUMMYUNIONNAME2  u2
#define DUMMYUNIONNAME3  u3
#define DUMMYUNIONNAME4  u4
#define DUMMYUNIONNAME5  u5
#define DUMMYUNIONNAME6  u6
#define DUMMYUNIONNAME7  u7
#define DUMMYUNIONNAME8  u8
#endif /* !defined(NONAMELESSUNION) */

#ifndef __C89_NAMELESS
# if !defined(__WINESRC__) && !defined(WINE_NO_NAMELESS_EXTENSION)
#  ifdef __GNUC__
    /* Anonymous structs support starts with gcc 2.96/g++ 2.95 */
#   if (__GNUC__ > 2) || ((__GNUC__ == 2) && ((__GNUC_MINOR__ > 95) || ((__GNUC_MINOR__ == 95) && defined(__cplusplus))))
#    define __C89_NAMELESS __extension__
#   endif
#  elif defined(_MSC_VER)
#   define __C89_NAMELESS
#  endif
# endif
#endif

#ifdef __C89_NAMELESS
#  define __C89_NAMELESSSTRUCTNAME
#  define __C89_NAMELESSUNIONNAME
#else
#  define __C89_NAMELESS
#  define __C89_NAMELESSSTRUCTNAME DUMMYSTRUCTNAME
#  define __C89_NAMELESSUNIONNAME DUMMYUNIONNAME
#endif

/* C99 restrict support */

#if defined(ENABLE_RESTRICTED) && !defined(MIDL_PASS) && !defined(RC_INVOKED)
# if defined(_MSC_VER) && defined(_M_MRX000)
#  define RESTRICTED_POINTER __restrict
# elif defined(__GNUC__) && ((__GNUC__ > 2) || ((__GNUC__ == 2) && (__GNUC_MINOR__ >= 95)))
#  define RESTRICTED_POINTER __restrict
# else
#  define RESTRICTED_POINTER
# endif
#else
# define RESTRICTED_POINTER
#endif

/* C99 unaligned support */

#ifndef UNALIGNED
#if defined(_MSC_VER) && (defined(_M_MRX000) || defined(_M_ALPHA) || defined(_M_PPC) || defined(_M_IA64) || defined(_M_AMD64))
# define UNALIGNED __unaligned
# ifdef OS64BIT
#  define UNALIGNED64 __unaligned
# else
#  define UNALIGNED64
# endif
#else
# define UNALIGNED
# define UNALIGNED64
#endif
#endif

/* Alignment macros */

#if defined(OS64BIT) || (defined(_MSC_VER) && defined(_M_ALPHA)) || defined(__alpha__)
#define MAX_NATURAL_ALIGNMENT sizeof(ULONGLONG)
#define MEMORY_ALLOCATION_ALIGNMENT 16
#else
#define MAX_NATURAL_ALIGNMENT sizeof(::u32)
#define MEMORY_ALLOCATION_ALIGNMENT 8
#endif

#if defined(_MSC_VER) && (_MSC_VER >= 1300) && defined(__cplusplus)
# define TYPE_ALIGNMENT(t) __alignof(t)
#elif defined(__GNUC__)
# define TYPE_ALIGNMENT(t) __alignof__(t)
#else
# define TYPE_ALIGNMENT(t) FIELD_OFFSET(struct { char x; t test; }, test)
#endif

#ifdef OS64BIT
# define PROBE_ALIGNMENT(_s) \
    (TYPE_ALIGNMENT(_s) > TYPE_ALIGNMENT(::u32) ? \
    TYPE_ALIGNMENT(_s) : TYPE_ALIGNMENT(::u32))
# define PROBE_ALIGNMENT32(_s) TYPE_ALIGNMENT(::u32)
#else
# define PROBE_ALIGNMENT(_s) TYPE_ALIGNMENT(::u32)
#endif

/* Compile time assertion */

#if defined(_MSC_VER)
# define C_ASSERT(e) typedef char __C_ASSERT__[(e)?1:-1]
#else
# define C_ASSERT(e) extern void __C_ASSERT__(i32 [(e)?1:-1])
#endif

/* Eliminate Microsoft C/C++ compiler warning 4715 */
#if defined(_MSC_VER) && (_MSC_VER > 1200)
# define DEFAULT_UNREACHABLE default: __assume(0)
#else
# define DEFAULT_UNREACHABLE
#endif

/* Error Masks */
#define APPLICATION_ERROR_MASK       0x20000000
#define ERROR_SEVERITY_SUCCESS       0x00000000
#define ERROR_SEVERITY_INFORMATIONAL 0x40000000
#define ERROR_SEVERITY_WARNING       0x80000000
#define ERROR_SEVERITY_ERROR         0xC0000000

#ifdef __cplusplus
#define DEFINE_ENUM_FLAG_OPERATORS(ENUMTYPE) \
extern "C++" { \
    inline ENUMTYPE operator | (ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((i32)a)|((i32)b)); } \
    inline ENUMTYPE operator |= (ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((i32 &)a) |= ((i32)b)); } \
    inline ENUMTYPE operator & (ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((i32)a)&((i32)b)); } \
    inline ENUMTYPE operator &= (ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((i32 &)a) &= ((i32)b)); } \
    inline ENUMTYPE operator ~ (ENUMTYPE a) { return (ENUMTYPE)(~((i32)a)); } \
    inline ENUMTYPE operator ^ (ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((i32)a)^((i32)b)); } \
    inline ENUMTYPE operator ^= (ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((i32 &)a) ^= ((i32)b)); } \
}
#else
#define DEFINE_ENUM_FLAG_OPERATORS(ENUMTYPE) /* */
#endif

/* Microsoft's macros for declaring functions */

#ifdef __cplusplus
# define EXTERN_C    extern "C"
#else
# define EXTERN_C    extern
#endif

#define STDMETHODCALLTYPE       __stdcall
#define STDMETHODVCALLTYPE      __cdecl
#define STDAPICALLTYPE          __stdcall
#define STDAPIVCALLTYPE         __cdecl

#define STDAPI                  EXTERN_C HRESULT STDAPICALLTYPE
#define STDAPI_(type)           EXTERN_C type STDAPICALLTYPE
#define STDMETHODIMP            HRESULT STDMETHODCALLTYPE
#define STDMETHODIMP_(type)     type STDMETHODCALLTYPE
#define STDAPIV                 EXTERN_C HRESULT STDAPIVCALLTYPE
#define STDAPIV_(type)          EXTERN_C type STDAPIVCALLTYPE
#define STDMETHODIMPV           HRESULT STDMETHODVCALLTYPE
#define STDMETHODIMPV_(type)    type STDMETHODVCALLTYPE

/* Define the basic types */
#ifndef VOID
#define VOID void
#endif
//typedef VOID           *PVOID;
typedef VOID           *PVOID64;
typedef byte            WINBOOLEAN,    *PBOOLEAN;
typedef char            char,       *PCHAR;
typedef short           SHORT,      *PSHORT;
#ifdef _MSC_VER
typedef long            ::i32,       *PLONG;
#else
typedef i32             ::i32,       *PLONG;
#endif

/* Some systems might have unichar, but we really need 16 bit characters */
#ifdef WINE_UNICODE_NATIVE
typedef wd16char        WCHAR,      *PWCHAR;
#else
typedef unsigned short  WCHAR,      *PWCHAR;
#endif

/* 'Extended/Wide' numerical types */
#ifndef _ULONGLONG_
# define _ULONGLONG_
# ifdef _MSC_VER
typedef signed ::i64   ::i64,  *PLONGLONG;
typedef ::u64 ULONGLONG, *PULONGLONG;
# else
typedef signed ::i64   DECLSPEC_ALIGN(8) ::i64,   *PLONGLONG;
typedef ::u64 DECLSPEC_ALIGN(8) ULONGLONG,  *PULONGLONG;
# endif
#endif

#ifndef _DWORDLONG_
# define _DWORDLONG_
# ifdef _MSC_VER
typedef ULONGLONG DWORDLONG, *PDWORDLONG;
# else
typedef ULONGLONG   DECLSPEC_ALIGN(8) DWORDLONG,   *PDWORDLONG;
# endif
#endif

/* ANSI string types */
typedef char           *PCH,        *LPCH;
typedef const char     *PCCH,       *LPCCH;
typedef char           *PSTR,       *char *,     *NPSTR;
typedef const char     *PCSTR,      *const char *;

/* Unicode string types */
typedef WCHAR          *PWCH,       *LPWCH;
typedef const WCHAR    *PCWCH,      *LPCWCH;
typedef WCHAR          *PWSTR,      *LPWSTR,    *NWPSTR;
typedef const WCHAR    *PCWSTR,     *const widechar *;

/* Neutral character and string types */
/* These are only defined for Winelib, i.e. _not_ defined for
 * the emulator. The reason is they depend on the UNICODE
 * macro which only exists in the user's code.
 */
#ifndef WINE_NO_UNICODE_MACROS
# ifdef UNICODE
# ifndef _TCHAR_DEFINED
typedef WCHAR           TCHAR,      *PTCHAR;
# define _TCHAR_DEFINED
#endif
typedef LPWSTR          PTSTR,       char *;
typedef const widechar *         PCTSTR,      LPCTSTR;
#  define __TEXT(string) L##string
# else  /* UNICODE */
# ifndef _TCHAR_DEFINED
typedef char            TCHAR,      *PTCHAR;
# define _TCHAR_DEFINED
# endif
typedef char *           PTSTR,       char *;
typedef const char *          PCTSTR,      LPCTSTR;
#  define __TEXT(string) string
# endif /* UNICODE */
# define TEXT(quote) __TEXT(quote)
#endif   /* WINE_NO_UNICODE_MACROS */

/* Misc common WIN32 types */
typedef char            CCHAR;
typedef ::u32           LCID,       *PLCID;
typedef ::u16            LANGID;
typedef ::u32		EXECUTION_STATE;
#ifndef _HRESULT_DEFINED
#define _HRESULT_DEFINED
typedef ::i32            HRESULT;
#endif

/* Handle type */

//typedef void *HANDLE;
//typedef HANDLE *PHANDLE, *LPHANDLE;

#ifdef STRICT
#define DECLARE_HANDLE(a) typedef struct a##__ { i32 unused; } *a
#else /*STRICT*/
#define DECLARE_HANDLE(a) typedef HANDLE a
#endif /*STRICT*/

typedef byte  FCHAR;
typedef ::u16  FSHORT;
typedef ::u32 FLONG;

/* Defines */

#ifndef WIN32_NO_STATUS

#define STATUS_WAIT_0                    ((int) 0x00000000)
#define STATUS_ABANDONED_WAIT_0          ((int) 0x00000080)
#define STATUS_USER_APC                  ((int) 0x000000C0)
#define STATUS_TIMEOUT                   ((int) 0x00000102)
#define STATUS_PENDING                   ((int) 0x00000103)
#define STATUS_SEGMENT_NOTIFICATION      ((int) 0x40000005)
#define STATUS_GUARD_PAGE_VIOLATION      ((int) 0x80000001)
#define STATUS_DATATYPE_MISALIGNMENT     ((int) 0x80000002)
#define STATUS_BREAKPOINT                ((int) 0x80000003)
#define STATUS_SINGLE_STEP               ((int) 0x80000004)
#define STATUS_ACCESS_VIOLATION          ((int) 0xC0000005)
#define STATUS_IN_PAGE_ERROR             ((int) 0xC0000006)
#define STATUS_INVALID_HANDLE            ((int) 0xC0000008)
#define STATUS_NO_MEMORY                 ((int) 0xC0000017)
#define STATUS_ILLEGAL_INSTRUCTION       ((int) 0xC000001D)
#define STATUS_NONCONTINUABLE_EXCEPTION  ((int) 0xC0000025)
#define STATUS_INVALID_DISPOSITION       ((int) 0xC0000026)
#define STATUS_ARRAY_BOUNDS_EXCEEDED     ((int) 0xC000008C)
#define STATUS_FLOAT_DENORMAL_OPERAND    ((int) 0xC000008D)
#define STATUS_FLOAT_DIVIDE_BY_ZERO      ((int) 0xC000008E)
#define STATUS_FLOAT_INEXACT_RESULT      ((int) 0xC000008F)
#define STATUS_FLOAT_INVALID_OPERATION   ((int) 0xC0000090)
#define STATUS_FLOAT_OVERFLOW            ((int) 0xC0000091)
#define STATUS_FLOAT_STACK_CHECK         ((int) 0xC0000092)
#define STATUS_FLOAT_UNDERFLOW           ((int) 0xC0000093)
#define STATUS_INTEGER_DIVIDE_BY_ZERO    ((int) 0xC0000094)
#define STATUS_INTEGER_OVERFLOW          ((int) 0xC0000095)
#define STATUS_PRIVILEGED_INSTRUCTION    ((int) 0xC0000096)
#define STATUS_STACK_OVERFLOW            ((int) 0xC00000FD)
#define STATUS_CONTROL_C_EXIT            ((int) 0xC000013A)
#define STATUS_FLOAT_MULTIPLE_FAULTS     ((int) 0xC00002B4)
#define STATUS_FLOAT_MULTIPLE_TRAPS      ((int) 0xC00002B5)
#define STATUS_REG_NAT_CONSUMPTION       ((int) 0xC00002C9)
#define STATUS_SXS_EARLY_DEACTIVATION    ((int) 0xC015000F)
#define STATUS_SXS_INVALID_DEACTIVATION  ((int) 0xC0150010)

/* status values for ContinueDebugEvent */
#define DBG_EXCEPTION_HANDLED       ((int) 0x00010001)
#define DBG_CONTINUE                ((int) 0x00010002)
#define DBG_TERMINATE_THREAD        ((int) 0x40010003)
#define DBG_TERMINATE_PROCESS       ((int) 0x40010004)
#define DBG_CONTROL_C               ((int) 0x40010005)
#define DBG_CONTROL_BREAK           ((int) 0x40010008)
#define DBG_COMMAND_EXCEPTION       ((int) 0x40010009)
#define DBG_EXCEPTION_NOT_HANDLED   ((int) 0x80010001)

#endif /* WIN32_NO_STATUS */

/* Argument 1 passed to the DllEntryProc. */
#define	DLL_PROCESS_DETACH	0	/* detach process (unload library) */
#define	DLL_PROCESS_ATTACH	1	/* attach process (load library) */
#define	DLL_THREAD_ATTACH	2	/* attach new thread */
#define	DLL_THREAD_DETACH	3	/* detach thread */
#ifdef __WINESRC__
#define DLL_WINE_PREATTACH      8       /* called before process attach for Wine builtins */
#endif

/* u.x.wProcessorArchitecture (NT) */
#define PROCESSOR_ARCHITECTURE_INTEL	0
#define PROCESSOR_ARCHITECTURE_MIPS	1
#define PROCESSOR_ARCHITECTURE_ALPHA	2
#define PROCESSOR_ARCHITECTURE_PPC	3
#define PROCESSOR_ARCHITECTURE_SHX	4
#define PROCESSOR_ARCHITECTURE_ARM	5
#define PROCESSOR_ARCHITECTURE_IA64     6
#define PROCESSOR_ARCHITECTURE_ALPHA64  7
#define PROCESSOR_ARCHITECTURE_MSIL     8
#define PROCESSOR_ARCHITECTURE_AMD64    9
#define PROCESSOR_ARCHITECTURE_IA32_ON_WIN64    10
#define PROCESSOR_ARCHITECTURE_UNKNOWN	0xFFFF

/* Wine extension */
#define PROCESSOR_ARCHITECTURE_SPARC    20

/* dwProcessorType */
#define PROCESSOR_INTEL_386      386
#define PROCESSOR_INTEL_486      486
#define PROCESSOR_INTEL_PENTIUM  586
#define PROCESSOR_INTEL_860      860
#define PROCESSOR_INTEL_IA64     2200
#define PROCESSOR_AMD_X8664      8664
#define PROCESSOR_MIPS_R2000     2000
#define PROCESSOR_MIPS_R3000     3000
#define PROCESSOR_MIPS_R4000     4000
#define PROCESSOR_ALPHA_21064    21064
#define PROCESSOR_PPC_601        601
#define PROCESSOR_PPC_603        603
#define PROCESSOR_PPC_604        604
#define PROCESSOR_PPC_620        620
#define PROCESSOR_HITACHI_SH3    10003
#define PROCESSOR_HITACHI_SH3E   10004
#define PROCESSOR_HITACHI_SH4    10005
#define PROCESSOR_MOTOROLA_821   821
#define PROCESSOR_SHx_SH3        103
#define PROCESSOR_SHx_SH4        104
#define PROCESSOR_STRONGARM      2577
#define PROCESSOR_ARM720         1824    /* 0x720 */
#define PROCESSOR_ARM820         2080    /* 0x820 */
#define PROCESSOR_ARM920         2336    /* 0x920 */
#define PROCESSOR_ARM_7TDMI      70001
#define PROCESSOR_OPTIL          18767

#ifdef OS64BIT
#define MAXIMUM_PROCESSORS       64
#else
#define MAXIMUM_PROCESSORS       32
#endif

typedef struct _MEMORY_BASIC_INFORMATION
{
    LPVOID   BaseAddress;
    LPVOID   AllocationBase;
    ::u32    AllocationProtect;
    SIZE_T   RegionSize;
    ::u32    State;
    ::u32    Protect;
    ::u32    Type;
} MEMORY_BASIC_INFORMATION, *PMEMORY_BASIC_INFORMATION;

#define	PAGE_NOACCESS		0x01
#define	PAGE_READONLY		0x02
#define	PAGE_READWRITE		0x04
#define	PAGE_WRITECOPY		0x08
#define	PAGE_EXECUTE		0x10
#define	PAGE_EXECUTE_READ	0x20
#define	PAGE_EXECUTE_READWRITE	0x40
#define	PAGE_EXECUTE_WRITECOPY	0x80
#define	PAGE_GUARD		0x100
#define	PAGE_NOCACHE		0x200
#define	PAGE_WRITECOMBINE	0x400

#define MEM_COMMIT              0x00001000
#define MEM_RESERVE             0x00002000
#define MEM_DECOMMIT            0x00004000
#define MEM_RELEASE             0x00008000
#define MEM_FREE                0x00010000
#define MEM_PRIVATE             0x00020000
#define MEM_MAPPED              0x00040000
#define MEM_RESET               0x00080000
#define MEM_TOP_DOWN            0x00100000
#define MEM_WRITE_WATCH         0x00200000
#define MEM_PHYSICAL            0x00400000
#define MEM_LARGE_PAGES         0x20000000
#define MEM_4MB_PAGES           0x80000000

#define SEC_FILE                0x00800000
#define SEC_IMAGE               0x01000000
#define SEC_RESERVE             0x04000000
#define SEC_COMMIT              0x08000000
#define SEC_NOCACHE             0x10000000
#define SEC_LARGE_PAGES         0x80000000
#define MEM_IMAGE               SEC_IMAGE

#define WRITE_WATCH_FLAG_RESET  0x00000001


#define MINCHAR       0x80
#define MAXCHAR       0x7f
#define MINSHORT      0x8000
#define MAXSHORT      0x7fff
#define MINLONG       0x80000000
#define MAXLONG       0x7fffffff
#define MAXBYTE       0xff
#define MAXWORD       0xffff
#define MAXDWORD      0xffffffff

#define UNICODE_STRING_MAX_CHARS 32767

#define FIELD_OFFSET(type, field) \
  ((::i32)(INT_PTR)&(((type *)0)->field))

#define CONTAINING_RECORD(address, type, field) \
  ((type *)((PCHAR)(address) - (PCHAR)(&((type *)0)->field)))

/* Types */

typedef struct _LIST_ENTRY {
  struct _LIST_ENTRY *Flink;
  struct _LIST_ENTRY *Blink;
} LIST_ENTRY, *PLIST_ENTRY, * RESTRICTED_POINTER PRLIST_ENTRY;

typedef struct _SINGLE_LIST_ENTRY {
  struct _SINGLE_LIST_ENTRY *Next;
} SINGLE_LIST_ENTRY, *PSINGLE_LIST_ENTRY;

#ifdef OS64BIT

//typedef struct DECLSPEC_ALIGN(16) _SLIST_ENTRY *PSLIST_ENTRY;
typedef struct _SLIST_ENTRY *PSLIST_ENTRY;
typedef struct DECLSPEC_ALIGN(16) _SLIST_ENTRY {
    PSLIST_ENTRY Next;
} SLIST_ENTRY;

typedef union DECLSPEC_ALIGN(16) _SLIST_HEADER {
    struct {
        ULONGLONG Alignment;
        ULONGLONG Region;
    } DUMMYSTRUCTNAME;
    struct {
        ULONGLONG Depth:16;
        ULONGLONG Sequence:9;
        ULONGLONG NextEntry:39;
        ULONGLONG HeaderType:1;
        ULONGLONG Init:1;
        ULONGLONG Reserved:59;
        ULONGLONG Region:3;
    } Header8;
    struct {
        ULONGLONG Depth:16;
        ULONGLONG Sequence:48;
        ULONGLONG HeaderType:1;
        ULONGLONG Init:1;
        ULONGLONG Reserved:2;
        ULONGLONG NextEntry:60;
    } Header16;
} SLIST_HEADER, *PSLIST_HEADER;

#else

#undef SLIST_ENTRY /* for Mac OS */
#define SLIST_ENTRY SINGLE_LIST_ENTRY
#define _SLIST_ENTRY _SINGLE_LIST_ENTRY
#define PSLIST_ENTRY PSINGLE_LIST_ENTRY

typedef union _SLIST_HEADER {
    ULONGLONG Alignment;
    struct {
        SLIST_ENTRY Next;
        ::u16 Depth;
        ::u16 Sequence;
    } DUMMYSTRUCTNAME;
} SLIST_HEADER, *PSLIST_HEADER;

#endif

NTSYSAPI PSLIST_ENTRY WINAPI RtlFirstEntrySList(const SLIST_HEADER*);
NTSYSAPI VOID         WINAPI RtlInitializeSListHead(PSLIST_HEADER);
NTSYSAPI PSLIST_ENTRY WINAPI RtlInterlockedFlushSList(PSLIST_HEADER);
NTSYSAPI PSLIST_ENTRY WINAPI RtlInterlockedPopEntrySList(PSLIST_HEADER);
NTSYSAPI PSLIST_ENTRY WINAPI RtlInterlockedPushEntrySList(PSLIST_HEADER, PSLIST_ENTRY);
NTSYSAPI ::u16         WINAPI RtlQueryDepthSList(PSLIST_HEADER);


/* Heap flags */

#define HEAP_NO_SERIALIZE               0x00000001
#define HEAP_GROWABLE                   0x00000002
#define HEAP_GENERATE_EXCEPTIONS        0x00000004
#define HEAP_ZERO_MEMORY                0x00000008
#define HEAP_REALLOC_IN_PLACE_ONLY      0x00000010
#define HEAP_TAIL_CHECKING_ENABLED      0x00000020
#define HEAP_FREE_CHECKING_ENABLED      0x00000040
#define HEAP_DISABLE_COALESCE_ON_FREE   0x00000080
#define HEAP_CREATE_ALIGN_16            0x00010000
#define HEAP_CREATE_ENABLE_TRACING      0x00020000
#define HEAP_CREATE_ENABLE_EXECUTE      0x00040000

/* This flag allows it to create heaps shared by all processes under win95,
   FIXME: correct name */
#define HEAP_SHARED                     0x04000000

typedef enum _HEAP_INFORMATION_CLASS {
    HeapCompatibilityInformation,
} HEAP_INFORMATION_CLASS;

/* Processor feature flags.  */
#define PF_FLOATING_POINT_PRECISION_ERRATA	0
#define PF_FLOATING_POINT_EMULATED		1
#define PF_COMPARE_EXCHANGE_DOUBLE		2
#define PF_MMX_INSTRUCTIONS_AVAILABLE		3
#define PF_PPC_MOVEMEM_64BIT_OK			4
#define PF_ALPHA_BYTE_INSTRUCTIONS		5
#define PF_XMMI_INSTRUCTIONS_AVAILABLE		6
#define PF_3DNOW_INSTRUCTIONS_AVAILABLE		7
#define PF_RDTSC_INSTRUCTION_AVAILABLE		8
#define PF_PAE_ENABLED				9
#define PF_XMMI64_INSTRUCTIONS_AVAILABLE	10
#define PF_SSE_DAZ_MODE_AVAILABLE		11
#define PF_NX_ENABLED				12
#define PF_SSE3_INSTRUCTIONS_AVAILABLE		13
#define PF_COMPARE_EXCHANGE128			14
#define PF_COMPARE64_EXCHANGE128		15
#define PF_CHANNELS_ENABLED			16


/* Execution state flags */
#define ES_SYSTEM_REQUIRED    0x00000001
#define ES_DISPLAY_REQUIRED   0x00000002
#define ES_USER_PRESENT       0x00000004
#define ES_CONTINUOUS         0x80000000

/* The Win32 register action_context */

/* i386 action_context definitions */
#ifdef __i386__

#define SIZE_OF_80387_REGISTERS      80

typedef struct _FLOATING_SAVE_AREA
{
    ::u32   ControlWord;
    ::u32   StatusWord;
    ::u32   TagWord;
    ::u32   ErrorOffset;
    ::u32   ErrorSelector;
    ::u32   DataOffset;
    ::u32   DataSelector;
    byte    RegisterArea[SIZE_OF_80387_REGISTERS];
    ::u32   Cr0NpxState;
} FLOATING_SAVE_AREA, *PFLOATING_SAVE_AREA;

#define MAXIMUM_SUPPORTED_EXTENSION     512

typedef struct _CONTEXT
{
    ::u32   ContextFlags;

    /* These are selected by CONTEXT_DEBUG_REGISTERS */
    ::u32   Dr0;
    ::u32   Dr1;
    ::u32   Dr2;
    ::u32   Dr3;
    ::u32   Dr6;
    ::u32   Dr7;

    /* These are selected by CONTEXT_FLOATING_POINT */
    FLOATING_SAVE_AREA FloatSave;

    /* These are selected by CONTEXT_SEGMENTS */
    ::u32   SegGs;
    ::u32   SegFs;
    ::u32   SegEs;
    ::u32   SegDs;

    /* These are selected by CONTEXT_INTEGER */
    ::u32   Edi;
    ::u32   Esi;
    ::u32   Ebx;
    ::u32   Edx;
    ::u32   Ecx;
    ::u32   Eax;

    /* These are selected by CONTEXT_CONTROL */
    ::u32   Ebp;
    ::u32   Eip;
    ::u32   SegCs;
    ::u32   EFlags;
    ::u32   Esp;
    ::u32   SegSs;

    byte    ExtendedRegisters[MAXIMUM_SUPPORTED_EXTENSION];
} CONTEXT;

#define CONTEXT_X86       0x00010000
#define CONTEXT_i386      CONTEXT_X86
#define CONTEXT_i486      CONTEXT_X86

#define CONTEXT_CONTROL   (CONTEXT_i386 | 0x0001) /* SS:SP, CS:IP, FLAGS, BP */
#define CONTEXT_INTEGER   (CONTEXT_i386 | 0x0002) /* AX, BX, CX, DX, SI, DI */
#define CONTEXT_SEGMENTS  (CONTEXT_i386 | 0x0004) /* DS, ES, FS, GS */
#define CONTEXT_FLOATING_POINT  (CONTEXT_i386 | 0x0008L) /* 387 state */
#define CONTEXT_DEBUG_REGISTERS (CONTEXT_i386 | 0x0010L) /* DB 0-3,6,7 */
#define CONTEXT_EXTENDED_REGISTERS (CONTEXT_i386 | 0x0020L)
#define CONTEXT_FULL (CONTEXT_CONTROL | CONTEXT_INTEGER | CONTEXT_SEGMENTS)
#define CONTEXT_ALL (CONTEXT_CONTROL | CONTEXT_INTEGER | CONTEXT_SEGMENTS | \
        CONTEXT_FLOATING_POINT | CONTEXT_DEBUG_REGISTERS | CONTEXT_EXTENDED_REGISTERS)

#define EXCEPTION_READ_FAULT    0
#define EXCEPTION_WRITE_FAULT   1
#define EXCEPTION_EXECUTE_FAULT 8

#endif  /* __i386__ */

typedef struct _LDT_ENTRY {
    ::u16	LimitLow;
    ::u16	BaseLow;
    union {
        struct {
            byte    BaseMid;
            byte    Flags1;
            byte    Flags2;
            byte    BaseHi;
        } Bytes;
        struct {
            unsigned    BaseMid: 8;
            unsigned    Type : 5;
            unsigned    Dpl : 2;
            unsigned    Pres : 1;
            unsigned    LimitHi : 4;
            unsigned    Sys : 1;
            unsigned    Reserved_0 : 1;
            unsigned    Default_Big : 1;
            unsigned    Granularity : 1;
            unsigned    BaseHi : 8;
        } Bits;
    } HighWord;
} LDT_ENTRY, *PLDT_ENTRY;

/* x86-64 action_context definitions */
#if defined(__x86_64__)

#define CONTEXT_AMD64   0x00100000

#define CONTEXT_CONTROL   (CONTEXT_AMD64 | 0x0001)
#define CONTEXT_INTEGER   (CONTEXT_AMD64 | 0x0002)
#define CONTEXT_SEGMENTS  (CONTEXT_AMD64 | 0x0004)
#define CONTEXT_FLOATING_POINT  (CONTEXT_AMD64 | 0x0008L)
#define CONTEXT_DEBUG_REGISTERS (CONTEXT_AMD64 | 0x0010L)
#define CONTEXT_FULL (CONTEXT_CONTROL | CONTEXT_INTEGER | CONTEXT_FLOATING_POINT)
#define CONTEXT_ALL (CONTEXT_CONTROL | CONTEXT_INTEGER | CONTEXT_SEGMENTS | CONTEXT_FLOATING_POINT | CONTEXT_DEBUG_REGISTERS)

#define EXCEPTION_READ_FAULT    0
#define EXCEPTION_WRITE_FAULT   1
#define EXCEPTION_EXECUTE_FAULT 8

typedef struct DECLSPEC_ALIGN(16) _M128A {
    ULONGLONG Low;
    ::i64 High;
} M128A, *PM128A;

typedef struct _XMM_SAVE_AREA32 {
    ::u16 ControlWord;        /* 000 */
    ::u16 StatusWord;         /* 002 */
    byte TagWord;            /* 004 */
    byte Reserved1;          /* 005 */
    ::u16 ErrorOpcode;        /* 006 */
    ::u32 ErrorOffset;       /* 008 */
    ::u16 ErrorSelector;      /* 00c */
    ::u16 Reserved2;          /* 00e */
    ::u32 DataOffset;        /* 010 */
    ::u16 DataSelector;       /* 014 */
    ::u16 Reserved3;          /* 016 */
    ::u32 MxCsr;             /* 018 */
    ::u32 MxCsr_Mask;        /* 01c */
    M128A FloatRegisters[8]; /* 020 */
    M128A XmmRegisters[16];  /* 0a0 */
    byte Reserved4[96];      /* 1a0 */
} XMM_SAVE_AREA32, *PXMM_SAVE_AREA32;



typedef struct DECLSPEC_ALIGN(16) _CONTEXT {
    DWORD64 P1Home;          /* 000 */
    DWORD64 P2Home;          /* 008 */
    DWORD64 P3Home;          /* 010 */
    DWORD64 P4Home;          /* 018 */
    DWORD64 P5Home;          /* 020 */
    DWORD64 P6Home;          /* 028 */

    /* Control flags */
    ::u32 ContextFlags;      /* 030 */
    ::u32 MxCsr;             /* 034 */

    /* Segment */
    ::u16 SegCs;              /* 038 */
    ::u16 SegDs;              /* 03a */
    ::u16 SegEs;              /* 03c */
    ::u16 SegFs;              /* 03e */
    ::u16 SegGs;              /* 040 */
    ::u16 SegSs;              /* 042 */
    ::u32 EFlags;            /* 044 */

    /* Debug */
    DWORD64 Dr0;             /* 048 */
    DWORD64 Dr1;             /* 050 */
    DWORD64 Dr2;             /* 058 */
    DWORD64 Dr3;             /* 060 */
    DWORD64 Dr6;             /* 068 */
    DWORD64 Dr7;             /* 070 */

    /* Integer */
    DWORD64 Rax;             /* 078 */
    DWORD64 Rcx;             /* 080 */
    DWORD64 Rdx;             /* 088 */
    DWORD64 Rbx;             /* 090 */
    DWORD64 Rsp;             /* 098 */
    DWORD64 Rbp;             /* 0a0 */
    DWORD64 Rsi;             /* 0a8 */
    DWORD64 Rdi;             /* 0b0 */
    DWORD64 R8;              /* 0b8 */
    DWORD64 R9;              /* 0c0 */
    DWORD64 R10;             /* 0c8 */
    DWORD64 R11;             /* 0d0 */
    DWORD64 R12;             /* 0d8 */
    DWORD64 R13;             /* 0e0 */
    DWORD64 R14;             /* 0e8 */
    DWORD64 R15;             /* 0f0 */

    /* Counter */
    DWORD64 Rip;             /* 0f8 */

    /* Floating point */
    union {
        XMM_SAVE_AREA32 FltSave;  /* 100 */
        struct {
            M128A Header[2];      /* 100 */
            M128A Legacy[8];      /* 120 */
            M128A Xmm0;           /* 1a0 */
            M128A Xmm1;           /* 1b0 */
            M128A Xmm2;           /* 1c0 */
            M128A Xmm3;           /* 1d0 */
            M128A Xmm4;           /* 1e0 */
            M128A Xmm5;           /* 1f0 */
            M128A Xmm6;           /* 200 */
            M128A Xmm7;           /* 210 */
            M128A Xmm8;           /* 220 */
            M128A Xmm9;           /* 230 */
            M128A Xmm10;          /* 240 */
            M128A Xmm11;          /* 250 */
            M128A Xmm12;          /* 260 */
            M128A Xmm13;          /* 270 */
            M128A Xmm14;          /* 280 */
            M128A Xmm15;          /* 290 */
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;

    /* Vector */
    M128A VectorRegister[26];     /* 300 */
    DWORD64 VectorControl;        /* 4a0 */

    /* Debug control */
    DWORD64 DebugControl;         /* 4a8 */
    DWORD64 LastBranchToRip;      /* 4b0 */
    DWORD64 LastBranchFromRip;    /* 4b8 */
    DWORD64 LastExceptionToRip;   /* 4c0 */
    DWORD64 LastExceptionFromRip; /* 4c8 */
} CONTEXT;

typedef struct _RUNTIME_FUNCTION
{
    ::u32 BeginAddress;
    ::u32 EndAddress;
    ::u32 UnwindData;
} RUNTIME_FUNCTION, *PRUNTIME_FUNCTION;

#define UNWIND_HISTORY_TABLE_SIZE 12

typedef struct _UNWIND_HISTORY_TABLE_ENTRY
{
    ULONG64 ImageBase;
    PRUNTIME_FUNCTION FunctionEntry;
} UNWIND_HISTORY_TABLE_ENTRY, *PUNWIND_HISTORY_TABLE_ENTRY;

#define UNWIND_HISTORY_TABLE_NONE 0
#define UNWIND_HISTORY_TABLE_GLOBAL 1
#define UNWIND_HISTORY_TABLE_LOCAL 2

typedef struct _UNWIND_HISTORY_TABLE
{
    WINULONG Count;
    WINUCHAR Search;
    ULONG64 LowAddress;
    ULONG64 HighAddress;
    UNWIND_HISTORY_TABLE_ENTRY Entry[UNWIND_HISTORY_TABLE_SIZE];
} UNWIND_HISTORY_TABLE, *PUNWIND_HISTORY_TABLE;

typedef struct _KNONVOLATILE_CONTEXT_POINTERS
{
    union
    {
        PM128A FloatingContext[16];
        struct
        {
            PM128A Xmm0;
            PM128A Xmm1;
            PM128A Xmm2;
            PM128A Xmm3;
            PM128A Xmm4;
            PM128A Xmm5;
            PM128A Xmm6;
            PM128A Xmm7;
            PM128A Xmm8;
            PM128A Xmm9;
            PM128A Xmm10;
            PM128A Xmm11;
            PM128A Xmm12;
            PM128A Xmm13;
            PM128A Xmm14;
            PM128A Xmm15;
        } DUMMYSTRUCTNAME1;
    } DUMMYUNIONNAME1;

    union
    {
        PULONG64 IntegerContext[16];
        struct
        {
            PULONG64 Rax;
            PULONG64 Rcx;
            PULONG64 Rdx;
            PULONG64 Rbx;
            PULONG64 Rsp;
            PULONG64 Rbp;
            PULONG64 Rsi;
            PULONG64 Rdi;
            PULONG64 R8;
            PULONG64 R9;
            PULONG64 R10;
            PULONG64 R11;
            PULONG64 R12;
            PULONG64 R13;
            PULONG64 R14;
            PULONG64 R15;
        } DUMMYSTRUCTNAME2;
    } DUMMYUNIONNAME2;
} KNONVOLATILE_CONTEXT_POINTERS, *PKNONVOLATILE_CONTEXT_POINTERS;

WINBOOLEAN CDECL            RtlAddFunctionTable(RUNTIME_FUNCTION*,::u32,DWORD64);
WINBOOLEAN CDECL            RtlDeleteFunctionTable(RUNTIME_FUNCTION*);
PRUNTIME_FUNCTION WINAPI RtlLookupFunctionEntry(DWORD64,DWORD64*,UNWIND_HISTORY_TABLE*);
PVOID WINAPI             RtlVirtualUnwind(WINULONG,ULONG64,ULONG64,RUNTIME_FUNCTION*,CONTEXT*,PVOID*,ULONG64*,KNONVOLATILE_CONTEXT_POINTERS*);

#define UNW_FLAG_NHANDLER  0
#define UNW_FLAG_EHANDLER  1
#define UNW_FLAG_UHANDLER  2
#define UNW_FLAG_CHAININFO 4

#endif /* __x86_64__ */

/* IA64 action_context definitions */
#ifdef __ia64__

#define CONTEXT_IA64                  0x00080000
#define CONTEXT_CONTROL               (CONTEXT_IA64 | 0x00000001)
#define CONTEXT_LOWER_FLOATING_POINT  (CONTEXT_IA64 | 0x00000002)
#define CONTEXT_HIGHER_FLOATING_POINT (CONTEXT_IA64 | 0x00000004)
#define CONTEXT_INTEGER               (CONTEXT_IA64 | 0x00000008)
#define CONTEXT_DEBUG                 (CONTEXT_IA64 | 0x00000010)
#define CONTEXT_IA32_CONTROL          (CONTEXT_IA64 | 0x00000020)
#define CONTEXT_FLOATING_POINT        (CONTEXT_LOWER_FLOATING_POINT | CONTEXT_HIGHER_FLOATING_POINT)
#define CONTEXT_FULL                  (CONTEXT_CONTROL | CONTEXT_FLOATING_POINT | CONTEXT_INTEGER | CONTEXT_IA32_CONTROL)
#define CONTEXT_ALL                   (CONTEXT_CONTROL | CONTEXT_FLOATING_POINT | CONTEXT_INTEGER | CONTEXT_DEBUG | CONTEXT_IA32_CONTROL)

#define CONTEXT_EXCEPTION_ACTIVE      0x8000000
#define CONTEXT_SERVICE_ACTIVE        0x10000000
#define CONTEXT_EXCEPTION_REQUEST     0x40000000
#define CONTEXT_EXCEPTION_REPORTING   0x80000000

typedef struct _CONTEXT
{
    ::u32 ContextFlags;
    ::u32 Fill1[3];
    ULONGLONG DbI0;
    ULONGLONG DbI1;
    ULONGLONG DbI2;
    ULONGLONG DbI3;
    ULONGLONG DbI4;
    ULONGLONG DbI5;
    ULONGLONG DbI6;
    ULONGLONG DbI7;
    ULONGLONG DbD0;
    ULONGLONG DbD1;
    ULONGLONG DbD2;
    ULONGLONG DbD3;
    ULONGLONG DbD4;
    ULONGLONG DbD5;
    ULONGLONG DbD6;
    ULONGLONG DbD7;
    FLOAT128 FltS0;
    FLOAT128 FltS1;
    FLOAT128 FltS2;
    FLOAT128 FltS3;
    FLOAT128 FltT0;
    FLOAT128 FltT1;
    FLOAT128 FltT2;
    FLOAT128 FltT3;
    FLOAT128 FltT4;
    FLOAT128 FltT5;
    FLOAT128 FltT6;
    FLOAT128 FltT7;
    FLOAT128 FltT8;
    FLOAT128 FltT9;
    FLOAT128 FltS4;
    FLOAT128 FltS5;
    FLOAT128 FltS6;
    FLOAT128 FltS7;
    FLOAT128 FltS8;
    FLOAT128 FltS9;
    FLOAT128 FltS10;
    FLOAT128 FltS11;
    FLOAT128 FltS12;
    FLOAT128 FltS13;
    FLOAT128 FltS14;
    FLOAT128 FltS15;
    FLOAT128 FltS16;
    FLOAT128 FltS17;
    FLOAT128 FltS18;
    FLOAT128 FltS19;
    FLOAT128 FltF32;
    FLOAT128 FltF33;
    FLOAT128 FltF34;
    FLOAT128 FltF35;
    FLOAT128 FltF36;
    FLOAT128 FltF37;
    FLOAT128 FltF38;
    FLOAT128 FltF39;
    FLOAT128 FltF40;
    FLOAT128 FltF41;
    FLOAT128 FltF42;
    FLOAT128 FltF43;
    FLOAT128 FltF44;
    FLOAT128 FltF45;
    FLOAT128 FltF46;
    FLOAT128 FltF47;
    FLOAT128 FltF48;
    FLOAT128 FltF49;
    FLOAT128 FltF50;
    FLOAT128 FltF51;
    FLOAT128 FltF52;
    FLOAT128 FltF53;
    FLOAT128 FltF54;
    FLOAT128 FltF55;
    FLOAT128 FltF56;
    FLOAT128 FltF57;
    FLOAT128 FltF58;
    FLOAT128 FltF59;
    FLOAT128 FltF60;
    FLOAT128 FltF61;
    FLOAT128 FltF62;
    FLOAT128 FltF63;
    FLOAT128 FltF64;
    FLOAT128 FltF65;
    FLOAT128 FltF66;
    FLOAT128 FltF67;
    FLOAT128 FltF68;
    FLOAT128 FltF69;
    FLOAT128 FltF70;
    FLOAT128 FltF71;
    FLOAT128 FltF72;
    FLOAT128 FltF73;
    FLOAT128 FltF74;
    FLOAT128 FltF75;
    FLOAT128 FltF76;
    FLOAT128 FltF77;
    FLOAT128 FltF78;
    FLOAT128 FltF79;
    FLOAT128 FltF80;
    FLOAT128 FltF81;
    FLOAT128 FltF82;
    FLOAT128 FltF83;
    FLOAT128 FltF84;
    FLOAT128 FltF85;
    FLOAT128 FltF86;
    FLOAT128 FltF87;
    FLOAT128 FltF88;
    FLOAT128 FltF89;
    FLOAT128 FltF90;
    FLOAT128 FltF91;
    FLOAT128 FltF92;
    FLOAT128 FltF93;
    FLOAT128 FltF94;
    FLOAT128 FltF95;
    FLOAT128 FltF96;
    FLOAT128 FltF97;
    FLOAT128 FltF98;
    FLOAT128 FltF99;
    FLOAT128 FltF100;
    FLOAT128 FltF101;
    FLOAT128 FltF102;
    FLOAT128 FltF103;
    FLOAT128 FltF104;
    FLOAT128 FltF105;
    FLOAT128 FltF106;
    FLOAT128 FltF107;
    FLOAT128 FltF108;
    FLOAT128 FltF109;
    FLOAT128 FltF110;
    FLOAT128 FltF111;
    FLOAT128 FltF112;
    FLOAT128 FltF113;
    FLOAT128 FltF114;
    FLOAT128 FltF115;
    FLOAT128 FltF116;
    FLOAT128 FltF117;
    FLOAT128 FltF118;
    FLOAT128 FltF119;
    FLOAT128 FltF120;
    FLOAT128 FltF121;
    FLOAT128 FltF122;
    FLOAT128 FltF123;
    FLOAT128 FltF124;
    FLOAT128 FltF125;
    FLOAT128 FltF126;
    FLOAT128 FltF127;
    ULONGLONG StFPSR;
    ULONGLONG IntGp;
    ULONGLONG IntT0;
    ULONGLONG IntT1;
    ULONGLONG IntS0;
    ULONGLONG IntS1;
    ULONGLONG IntS2;
    ULONGLONG IntS3;
    ULONGLONG IntV0;
    ULONGLONG IntT2;
    ULONGLONG IntT3;
    ULONGLONG IntT4;
    ULONGLONG IntSp;
    ULONGLONG IntTeb;
    ULONGLONG IntT5;
    ULONGLONG IntT6;
    ULONGLONG IntT7;
    ULONGLONG IntT8;
    ULONGLONG IntT9;
    ULONGLONG IntT10;
    ULONGLONG IntT11;
    ULONGLONG IntT12;
    ULONGLONG IntT13;
    ULONGLONG IntT14;
    ULONGLONG IntT15;
    ULONGLONG IntT16;
    ULONGLONG IntT17;
    ULONGLONG IntT18;
    ULONGLONG IntT19;
    ULONGLONG IntT20;
    ULONGLONG IntT21;
    ULONGLONG IntT22;
    ULONGLONG IntNats;
    ULONGLONG Preds;
    ULONGLONG BrRp;
    ULONGLONG BrS0;
    ULONGLONG BrS1;
    ULONGLONG BrS2;
    ULONGLONG BrS3;
    ULONGLONG BrS4;
    ULONGLONG BrT0;
    ULONGLONG BrT1;
    ULONGLONG ApUNAT;
    ULONGLONG ApLC;
    ULONGLONG ApEC;
    ULONGLONG ApCCV;
    ULONGLONG ApDCR;
    ULONGLONG RsPFS;
    ULONGLONG RsBSP;
    ULONGLONG RsBSPSTORE;
    ULONGLONG RsRSC;
    ULONGLONG RsRNAT;
    ULONGLONG StIPSR;
    ULONGLONG StIIP;
    ULONGLONG StIFS;
    ULONGLONG StFCR;
    ULONGLONG Eflag;
    ULONGLONG SegCSD;
    ULONGLONG SegSSD;
    ULONGLONG Cflag;
    ULONGLONG StFSR;
    ULONGLONG StFIR;
    ULONGLONG StFDR;
    ULONGLONG UNUSEDPACK;
} CONTEXT, *PCONTEXT;

typedef struct _RUNTIME_FUNCTION
{
    WINULONG BeginAddress;
    WINULONG EndAddress;
    WINULONG UnwindInfoAddress;
} RUNTIME_FUNCTION, *PRUNTIME_FUNCTION;

typedef struct _FRAME_POINTERS {
  ULONGLONG MemoryStackFp;
  ULONGLONG BackingStoreFp;
} FRAME_POINTERS, *PFRAME_POINTERS;

#define UNWIND_HISTORY_TABLE_SIZE 12

typedef struct _UNWIND_HISTORY_TABLE_ENTRY {
  ULONG64 ImageBase;
  ULONG64 Gp;
  PRUNTIME_FUNCTION FunctionEntry;
} UNWIND_HISTORY_TABLE_ENTRY, *PUNWIND_HISTORY_TABLE_ENTRY;

typedef struct _UNWIND_HISTORY_TABLE {
  WINULONG Count;
  WINUCHAR Search;
  ULONG64 LowAddress;
  ULONG64 HighAddress;
  UNWIND_HISTORY_TABLE_ENTRY Entry[UNWIND_HISTORY_TABLE_SIZE];
} UNWIND_HISTORY_TABLE, *PUNWIND_HISTORY_TABLE;

typedef struct _KNONVOLATILE_CONTEXT_POINTERS
{
    PFLOAT128  FltS0;
    PFLOAT128  FltS1;
    PFLOAT128  FltS2;
    PFLOAT128  FltS3;
    PFLOAT128  HighFloatingContext[10];
    PFLOAT128  FltS4;
    PFLOAT128  FltS5;
    PFLOAT128  FltS6;
    PFLOAT128  FltS7;
    PFLOAT128  FltS8;
    PFLOAT128  FltS9;
    PFLOAT128  FltS10;
    PFLOAT128  FltS11;
    PFLOAT128  FltS12;
    PFLOAT128  FltS13;
    PFLOAT128  FltS14;
    PFLOAT128  FltS15;
    PFLOAT128  FltS16;
    PFLOAT128  FltS17;
    PFLOAT128  FltS18;
    PFLOAT128  FltS19;
    PULONGLONG IntS0;
    PULONGLONG IntS1;
    PULONGLONG IntS2;
    PULONGLONG IntS3;
    PULONGLONG IntSp;
    PULONGLONG IntS0Nat;
    PULONGLONG IntS1Nat;
    PULONGLONG IntS2Nat;
    PULONGLONG IntS3Nat;
    PULONGLONG IntSpNat;
    PULONGLONG Preds;
    PULONGLONG BrRp;
    PULONGLONG BrS0;
    PULONGLONG BrS1;
    PULONGLONG BrS2;
    PULONGLONG BrS3;
    PULONGLONG BrS4;
    PULONGLONG ApUNAT;
    PULONGLONG ApLC;
    PULONGLONG ApEC;
    PULONGLONG RsPFS;
    PULONGLONG StFSR;
    PULONGLONG StFIR;
    PULONGLONG StFDR;
    PULONGLONG Cflag;
} KNONVOLATILE_CONTEXT_POINTERS, *PKNONVOLATILE_CONTEXT_POINTERS;

ULONGLONG WINAPI RtlVirtualUnwind(ULONGLONG,ULONGLONG,RUNTIME_FUNCTION*,CONTEXT*,WINBOOLEAN*,FRAME_POINTERS*,KNONVOLATILE_CONTEXT_POINTERS*);

#endif /* __ia64__ */

/* Alpha action_context definitions */
#if defined(_ALPHA_) || defined(__ALPHA__) || defined(__alpha__)

#define CONTEXT_ALPHA   0x00020000

#define CONTEXT_CONTROL		(CONTEXT_ALPHA | 0x00000001L)
#define CONTEXT_FLOATING_POINT	(CONTEXT_ALPHA | 0x00000002L)
#define CONTEXT_INTEGER		(CONTEXT_ALPHA | 0x00000004L)
#define CONTEXT_FULL  (CONTEXT_CONTROL | CONTEXT_FLOATING_POINT | CONTEXT_INTEGER)

#define EXCEPTION_READ_FAULT    0
#define EXCEPTION_WRITE_FAULT   1
#define EXCEPTION_EXECUTE_FAULT 8

typedef struct _CONTEXT
{
    /* selected by CONTEXT_FLOATING_POINT */
    ULONGLONG FltF0;
    ULONGLONG FltF1;
    ULONGLONG FltF2;
    ULONGLONG FltF3;
    ULONGLONG FltF4;
    ULONGLONG FltF5;
    ULONGLONG FltF6;
    ULONGLONG FltF7;
    ULONGLONG FltF8;
    ULONGLONG FltF9;
    ULONGLONG FltF10;
    ULONGLONG FltF11;
    ULONGLONG FltF12;
    ULONGLONG FltF13;
    ULONGLONG FltF14;
    ULONGLONG FltF15;
    ULONGLONG FltF16;
    ULONGLONG FltF17;
    ULONGLONG FltF18;
    ULONGLONG FltF19;
    ULONGLONG FltF20;
    ULONGLONG FltF21;
    ULONGLONG FltF22;
    ULONGLONG FltF23;
    ULONGLONG FltF24;
    ULONGLONG FltF25;
    ULONGLONG FltF26;
    ULONGLONG FltF27;
    ULONGLONG FltF28;
    ULONGLONG FltF29;
    ULONGLONG FltF30;
    ULONGLONG FltF31;

    /* selected by CONTEXT_INTEGER */
    ULONGLONG IntV0;
    ULONGLONG IntT0;
    ULONGLONG IntT1;
    ULONGLONG IntT2;
    ULONGLONG IntT3;
    ULONGLONG IntT4;
    ULONGLONG IntT5;
    ULONGLONG IntT6;
    ULONGLONG IntT7;
    ULONGLONG IntS0;
    ULONGLONG IntS1;
    ULONGLONG IntS2;
    ULONGLONG IntS3;
    ULONGLONG IntS4;
    ULONGLONG IntS5;
    ULONGLONG IntFp;
    ULONGLONG IntA0;
    ULONGLONG IntA1;
    ULONGLONG IntA2;
    ULONGLONG IntA3;
    ULONGLONG IntA4;
    ULONGLONG IntA5;
    ULONGLONG IntT8;
    ULONGLONG IntT9;
    ULONGLONG IntT10;
    ULONGLONG IntT11;
    ULONGLONG IntRa;
    ULONGLONG IntT12;
    ULONGLONG IntAt;
    ULONGLONG IntGp;
    ULONGLONG IntSp;
    ULONGLONG IntZero;

    /* selected by CONTEXT_FLOATING_POINT */
    ULONGLONG Fpcr;
    ULONGLONG SoftFpcr;

    /* selected by CONTEXT_CONTROL */
    ULONGLONG Fir;
    ::u32 Psr;
    ::u32 ContextFlags;
    ::u32 Fill[4];
} CONTEXT;

#define _QUAD_PSR_OFFSET   HighSoftFpcr
#define _QUAD_FLAGS_OFFSET HighFir

#endif  /* _ALPHA_ */

#ifdef __arm__

/* The following flags control the contents of the CONTEXT structure. */

#define CONTEXT_ARM    0x0000040
#define CONTEXT_CONTROL         (CONTEXT_ARM | 0x00000001L)
#define CONTEXT_INTEGER         (CONTEXT_ARM | 0x00000002L)

#define CONTEXT_FULL (CONTEXT_CONTROL | CONTEXT_INTEGER)

#define EXCEPTION_READ_FAULT    0
#define EXCEPTION_WRITE_FAULT   1
#define EXCEPTION_EXECUTE_FAULT 8

typedef struct _CONTEXT {
	/* The flags values within this flag control the contents of
	   a CONTEXT record.

	   If the action_context record is used as an input parameter, then
	   for each portion of the action_context record controlled by a flag
	   whose value is set, it is assumed that that portion of the
	   action_context record contains valid action_context. If the action_context record
	   is being used to modify a thread's action_context, then only that
	   portion of the threads action_context will be modified.

	   If the action_context record is used as an IN OUT parameter to capture
	   the action_context of a thread, then only those portions of the thread's
	   action_context corresponding to set flags will be returned.

	   The action_context record is never used as an OUT only parameter. */

	WINULONG ContextFlags;

	/* This section is specified/returned if the ContextFlags word contains
	   the flag CONTEXT_INTEGER. */
	WINULONG R0;
	WINULONG R1;
	WINULONG R2;
	WINULONG R3;
	WINULONG R4;
	WINULONG R5;
	WINULONG R6;
	WINULONG R7;
	WINULONG R8;
	WINULONG R9;
	WINULONG R10;
	WINULONG Fp;
	WINULONG Ip;

	/* These are selected by CONTEXT_CONTROL */
	WINULONG Sp;
	WINULONG Lr;
	WINULONG Pc;
	WINULONG Cpsr;
} CONTEXT;

#endif /* defined APPLE_IOS && !defined __arm__ */


   /* Mips action_context definitions */
#if defined(_MIPS_) || defined(__MIPS__) || defined(__mips__)

#define CONTEXT_R4000   0x00010000

#define CONTEXT_CONTROL         (CONTEXT_R4000 | 0x00000001)
#define CONTEXT_FLOATING_POINT  (CONTEXT_R4000 | 0x00000002)
#define CONTEXT_INTEGER         (CONTEXT_R4000 | 0x00000004)

#define CONTEXT_FULL (CONTEXT_CONTROL | CONTEXT_FLOATING_POINT | CONTEXT_INTEGER)

#define EXCEPTION_READ_FAULT    0
#define EXCEPTION_WRITE_FAULT   1
#define EXCEPTION_EXECUTE_FAULT 8

typedef struct _CONTEXT
{
    ::u32 Argument[4];
    /* These are selected by CONTEXT_FLOATING_POINT */
    ::u32 FltF0;
    ::u32 FltF1;
    ::u32 FltF2;
    ::u32 FltF3;
    ::u32 FltF4;
    ::u32 FltF5;
    ::u32 FltF6;
    ::u32 FltF7;
    ::u32 FltF8;
    ::u32 FltF9;
    ::u32 FltF10;
    ::u32 FltF11;
    ::u32 FltF12;
    ::u32 FltF13;
    ::u32 FltF14;
    ::u32 FltF15;
    ::u32 FltF16;
    ::u32 FltF17;
    ::u32 FltF18;
    ::u32 FltF19;
    ::u32 FltF20;
    ::u32 FltF21;
    ::u32 FltF22;
    ::u32 FltF23;
    ::u32 FltF24;
    ::u32 FltF25;
    ::u32 FltF26;
    ::u32 FltF27;
    ::u32 FltF28;
    ::u32 FltF29;
    ::u32 FltF30;
    ::u32 FltF31;

    /* These are selected by CONTEXT_INTEGER */
    ::u32 IntZero;
    ::u32 IntAt;
    ::u32 IntV0;
    ::u32 IntV1;
    ::u32 IntA0;
    ::u32 IntA1;
    ::u32 IntA2;
    ::u32 IntA3;
    ::u32 IntT0;
    ::u32 IntT1;
    ::u32 IntT2;
    ::u32 IntT3;
    ::u32 IntT4;
    ::u32 IntT5;
    ::u32 IntT6;
    ::u32 IntT7;
    ::u32 IntS0;
    ::u32 IntS1;
    ::u32 IntS2;
    ::u32 IntS3;
    ::u32 IntS4;
    ::u32 IntS5;
    ::u32 IntS6;
    ::u32 IntS7;
    ::u32 IntT8;
    ::u32 IntT9;
    ::u32 IntK0;
    ::u32 IntK1;
    ::u32 IntGp;
    ::u32 IntSp;
    ::u32 IntS8;
    ::u32 IntRa;
    ::u32 IntLo;
    ::u32 IntHi;

    /* These are selected by CONTEXT_FLOATING_POINT */
    ::u32 Fsr;

    /* These are selected by CONTEXT_CONTROL */
    ::u32 Fir;
    ::u32 Psr;

    ::u32 ContextFlags;
    ::u32 Fill[2];
} CONTEXT;

#endif  /* _MIPS_ */

/* PowerPC action_context definitions */
#ifdef __powerpc__

#define CONTEXT_CONTROL         0x0001
#define CONTEXT_FLOATING_POINT  0x0002
#define CONTEXT_INTEGER         0x0004
#define CONTEXT_DEBUG_REGISTERS 0x0008
#define CONTEXT_FULL (CONTEXT_CONTROL | CONTEXT_FLOATING_POINT | CONTEXT_INTEGER)

#define EXCEPTION_READ_FAULT    0
#define EXCEPTION_WRITE_FAULT   1
#define EXCEPTION_EXECUTE_FAULT 8

typedef struct
{
    /* These are selected by CONTEXT_FLOATING_POINT */
    double Fpr0;
    double Fpr1;
    double Fpr2;
    double Fpr3;
    double Fpr4;
    double Fpr5;
    double Fpr6;
    double Fpr7;
    double Fpr8;
    double Fpr9;
    double Fpr10;
    double Fpr11;
    double Fpr12;
    double Fpr13;
    double Fpr14;
    double Fpr15;
    double Fpr16;
    double Fpr17;
    double Fpr18;
    double Fpr19;
    double Fpr20;
    double Fpr21;
    double Fpr22;
    double Fpr23;
    double Fpr24;
    double Fpr25;
    double Fpr26;
    double Fpr27;
    double Fpr28;
    double Fpr29;
    double Fpr30;
    double Fpr31;
    double Fpscr;

    /* These are selected by CONTEXT_INTEGER */
    ::u32 Gpr0;
    ::u32 Gpr1;
    ::u32 Gpr2;
    ::u32 Gpr3;
    ::u32 Gpr4;
    ::u32 Gpr5;
    ::u32 Gpr6;
    ::u32 Gpr7;
    ::u32 Gpr8;
    ::u32 Gpr9;
    ::u32 Gpr10;
    ::u32 Gpr11;
    ::u32 Gpr12;
    ::u32 Gpr13;
    ::u32 Gpr14;
    ::u32 Gpr15;
    ::u32 Gpr16;
    ::u32 Gpr17;
    ::u32 Gpr18;
    ::u32 Gpr19;
    ::u32 Gpr20;
    ::u32 Gpr21;
    ::u32 Gpr22;
    ::u32 Gpr23;
    ::u32 Gpr24;
    ::u32 Gpr25;
    ::u32 Gpr26;
    ::u32 Gpr27;
    ::u32 Gpr28;
    ::u32 Gpr29;
    ::u32 Gpr30;
    ::u32 Gpr31;

    ::u32 Cr;
    ::u32 Xer;

    /* These are selected by CONTEXT_CONTROL */
    ::u32 Msr;
    ::u32 Iar; /* Instruction Address Register , aka PC ... */
    ::u32 Lr;
    ::u32 Ctr;

    ::u32 ContextFlags;

    ::u32 Dar;   /* Fault registers for coredump */
    ::u32 Dsisr;
    ::u32 Trap;  /* number of powerpc exception taken */

    /* These are selected by CONTEXT_DEBUG_REGISTERS */
    ::u32 Dr0;
    ::u32 Dr1;
    ::u32 Dr2;
    ::u32 Dr3;
    ::u32 Dr4;
    ::u32 Dr5;
    ::u32 Dr6;
    ::u32 Dr7;
} CONTEXT;

typedef struct _STACK_FRAME_HEADER
{
    ::u32 BackChain;
    ::u32 GlueSaved1;
    ::u32 GlueSaved2;
    ::u32 Reserved1;
    ::u32 Spare1;
    ::u32 Spare2;

    ::u32 Parameter0;
    ::u32 Parameter1;
    ::u32 Parameter2;
    ::u32 Parameter3;
    ::u32 Parameter4;
    ::u32 Parameter5;
    ::u32 Parameter6;
    ::u32 Parameter7;
} STACK_FRAME_HEADER,*PSTACK_FRAME_HEADER;

#endif  /* __powerpc__ */

#ifdef __sparc__

/*
 * FIXME:
 *
 * There is no official CONTEXT structure defined for the SPARC
 * architecture, so I just made one up.
 *
 * This structure is valid only for 32-bit SPARC architectures,
 * not for 64-bit SPARC.
 *
 * Note that this structure contains only the 'top-level' registers;
 * the rest of the register window chain is not visible.
 *
 * The on_layout follows the Solaris 'prgregset_t' structure.
 *
 */

#define CONTEXT_SPARC            0x10000000

#define CONTEXT_CONTROL         (CONTEXT_SPARC | 0x00000001)
#define CONTEXT_FLOATING_POINT  (CONTEXT_SPARC | 0x00000002)
#define CONTEXT_INTEGER         (CONTEXT_SPARC | 0x00000004)

#define CONTEXT_FULL (CONTEXT_CONTROL | CONTEXT_FLOATING_POINT | CONTEXT_INTEGER)

#define EXCEPTION_READ_FAULT    0
#define EXCEPTION_WRITE_FAULT   1
#define EXCEPTION_EXECUTE_FAULT 8

typedef struct _CONTEXT
{
    ::u32 ContextFlags;

    /* These are selected by CONTEXT_INTEGER */
    ::u32 g0;
    ::u32 g1;
    ::u32 g2;
    ::u32 g3;
    ::u32 g4;
    ::u32 g5;
    ::u32 g6;
    ::u32 g7;
    ::u32 o0;
    ::u32 o1;
    ::u32 o2;
    ::u32 o3;
    ::u32 o4;
    ::u32 o5;
    ::u32 o6;
    ::u32 o7;
    ::u32 l0;
    ::u32 l1;
    ::u32 l2;
    ::u32 l3;
    ::u32 l4;
    ::u32 l5;
    ::u32 l6;
    ::u32 l7;
    ::u32 i0;
    ::u32 i1;
    ::u32 i2;
    ::u32 i3;
    ::u32 i4;
    ::u32 i5;
    ::u32 i6;
    ::u32 i7;

    /* These are selected by CONTEXT_CONTROL */
    ::u32 psr;
    ::u32 pc;
    ::u32 npc;
    ::u32 y;
    ::u32 wim;
    ::u32 tbr;

    /* FIXME: floating point registers missing */

} CONTEXT;

#endif  /* __sparc__ */

#if !defined(CONTEXT_FULL) && !defined(RC_INVOKED)
#error You need to define a CONTEXT for your CPU
#endif

typedef CONTEXT *PCONTEXT;

NTSYSAPI void WINAPI RtlCaptureContext(CONTEXT*);

/*
 * Product types
 */
#define PRODUCT_UNLICENSED                              0xABCDABCD
#define PRODUCT_BUSINESS                                0x00000006
#define PRODUCT_BUSINESS_N                              0x00000010
#define PRODUCT_CLUSTER_SERVER                          0x00000012
#define PRODUCT_DATACENTER_SERVER                       0x00000008
#define PRODUCT_DATACENTER_SERVER_CORE                  0x0000000C
#define PRODUCT_DATACENTER_SERVER_CORE_V                0x00000027
#define PRODUCT_SERVER_V                                0x00000025
#define PRODUCT_ENTERPRISE                              0x00000004
#define PRODUCT_ENTERPRISE_N                            0x0000001B
#define PRODUCT_ENTERPRISE_SERVER                       0x0000000A
#define PRODUCT_ENTERPRISE_SERVER_CORE                  0x0000000E
#define PRODUCT_ENTERPRISE_SERVER_CORE_V                0x00000029
#define PRODUCT_ENTERPRISE_SERVER_IA64                  0x0000000F
#define PRODUCT_ENTERPRISE_SERVER_V                     0x00000026
#define PRODUCT_HOME_BASIC                              0x00000002
#define PRODUCT_HOME_BASIC_N                            0x00000005
#define PRODUCT_HOME_PREMIUM                            0x00000003
#define PRODUCT_HOME_PREMIUM_N                          0x0000001A
#define PRODUCT_HYPERV                                  0x0000002A
#define PRODUCT_MEDIUMBUSINESS_SERVER_MANAGEMENT        0x0000001E
#define PRODUCT_MEDIUMBUSINESS_SERVER_MESSAGING         0x00000020
#define PRODUCT_MEDIUMBUSINESS_SERVER_SECURITY          0x0000001F
#define PRODUCT_SERVER_FOR_SMALLBUSINESS                0x00000018
#define PRODUCT_SERVER_FOR_SMALLBUSINESS_V              0x00000023
#define PRODUCT_SMALLBUSINESS_SERVER                    0x00000009
#define PRODUCT_STANDARD_SERVER                         0x00000007
#define PRODUCT_STANDARD_SERVER_CORE                    0x0000000D
#define PRODUCT_STANDARD_SERVER_CORE_V                  0x00000028
#define PRODUCT_STANDARD_SERVER_V                       0x00000024
#define PRODUCT_STARTER                                 0x0000000B
#define PRODUCT_STORAGE_ENTERPRISE_SERVER               0x00000017
#define PRODUCT_STORAGE_EXPRESS_SERVER                  0x00000014
#define PRODUCT_STORAGE_STANDARD_SERVER                 0x00000015
#define PRODUCT_STORAGE_WORKGROUP_SERVER                0x00000016
#define PRODUCT_UNDEFINED                               0x00000000
#define PRODUCT_ULTIMATE                                0x00000001
#define PRODUCT_ULTIMATE_N                              0x0000001C
#define PRODUCT_WEB_SERVER                              0x00000011
#define PRODUCT_WEB_SERVER_CORE                         0x0000001D


/*
 * Language IDs
 */

#define MAKELCID(l, s)		(MAKELONG(l, s))

#define MAKELANGID(p, s)        ((((::u16)(s))<<10) | (::u16)(p))
#define PRIMARYLANGID(l)        ((::u16)(l) & 0x3ff)
#define SUBLANGID(l)            ((::u16)(l) >> 10)

#define LANGIDFROMLCID(lcid)	((::u16)(lcid))
#define SORTIDFROMLCID(lcid)	((::u16)((((::u32)(lcid)) >> 16) & 0x0f))

#define LANG_SYSTEM_DEFAULT	(MAKELANGID(LANG_NEUTRAL, SUBLANG_SYS_DEFAULT))
#define LANG_USER_DEFAULT	(MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT))
#define LOCALE_SYSTEM_DEFAULT	(MAKELCID(LANG_SYSTEM_DEFAULT, SORT_DEFAULT))
#define LOCALE_USER_DEFAULT	(MAKELCID(LANG_USER_DEFAULT, SORT_DEFAULT))
#define LOCALE_NEUTRAL		(MAKELCID(MAKELANGID(LANG_NEUTRAL,SUBLANG_NEUTRAL),SORT_DEFAULT))
#define LOCALE_INVARIANT	(MAKELCID(MAKELANGID(LANG_INVARIANT,SUBLANG_NEUTRAL),SORT_DEFAULT))

#define __UNREFERENCED_PARAMETER(u)	(void)(u)
#define DBG___UNREFERENCED_PARAMETER(u)	(void)(u)
#define DBG_UNREFERENCED_LOCAL_VARIABLE(u) (void)(u)

#define LANG_NEUTRAL        0x00
#define LANG_INVARIANT      0x7f

#define LANG_AFRIKAANS      0x36
#define LANG_ALBANIAN       0x1c
#define LANG_ALSATIAN       0x84
#define LANG_AMHARIC        0x5e
#define LANG_ARABIC         0x01
#define LANG_ARMENIAN       0x2b
#define LANG_ASSAMESE       0x4d
#define LANG_AZERI          0x2c
#define LANG_BASHKIR        0x6d
#define LANG_BASQUE         0x2d
#define LANG_BELARUSIAN     0x23
#define LANG_BENGALI        0x45
#define LANG_BOSNIAN        0x1a
#define LANG_BOSNIAN_NEUTRAL      0x781a
#define LANG_BRETON         0x7e
#define LANG_BULGARIAN      0x02
#define LANG_CATALAN        0x03
#define LANG_CHINESE        0x04
#define LANG_CHINESE_SIMPLIFIED   0x0004
#define LANG_CHINESE_TRADITIONAL  0x7c04
#define LANG_CORSICAN       0x83
#define LANG_CROATIAN       0x1a
#define LANG_CZECH          0x05
#define LANG_DANISH         0x06
#define LANG_DARI           0x8c
#define LANG_DIVEHI         0x65
#define LANG_DUTCH          0x13
#define LANG_ENGLISH        0x09
#define LANG_ESTONIAN       0x25
#define LANG_FAEROESE       0x38
#define LANG_FARSI          LANG_PERSIAN
#define LANG_FILIPINO       0x64
#define LANG_FINNISH        0x0b
#define LANG_FRENCH         0x0c
#define LANG_FRISIAN        0x62
#define LANG_GALICIAN       0x56
#define LANG_GEORGIAN       0x37
#define LANG_GERMAN         0x07
#define LANG_GREEK          0x08
#define LANG_GREENLANDIC    0x6f
#define LANG_GUJARATI       0x47
#define LANG_HAUSA          0x68
#define LANG_HEBREW         0x0d
#define LANG_HINDI          0x39
#define LANG_HUNGARIAN      0x0e
#define LANG_ICELANDIC      0x0f
#define LANG_IGBO           0x70
#define LANG_INDONESIAN     0x21
#define LANG_INUKTITUT      0x5d
#define LANG_IRISH          0x3c
#define LANG_ITALIAN        0x10
#define LANG_JAPANESE       0x11
#define LANG_KANNADA        0x4b
#define LANG_KASHMIRI       0x60
#define LANG_KAZAK          0x3f
#define LANG_KHMER          0x53
#define LANG_KICHE          0x86
#define LANG_KINYARWANDA    0x87
#define LANG_KONKANI        0x57
#define LANG_KOREAN         0x12
#define LANG_KYRGYZ         0x40
#define LANG_LAO            0x54
#define LANG_LATVIAN        0x26
#define LANG_LITHUANIAN     0x27
#define LANG_LOWER_SORBIAN  0x2e
#define LANG_LUXEMBOURGISH  0x6e
#define LANG_MACEDONIAN     0x2f
#define LANG_MALAY          0x3e
#define LANG_MALAYALAM      0x4c
#define LANG_MALTESE        0x3a
#define LANG_MANIPURI       0x58
#define LANG_MAORI          0x81
#define LANG_MAPUDUNGUN     0x7a
#define LANG_MARATHI        0x4e
#define LANG_MOHAWK         0x7c
#define LANG_MONGOLIAN      0x50
#define LANG_NEPALI         0x61
#define LANG_NORWEGIAN      0x14
#define LANG_OCCITAN        0x82
#define LANG_ORIYA          0x48
#define LANG_PASHTO         0x63
#define LANG_PERSIAN        0x29
#define LANG_POLISH         0x15
#define LANG_PORTUGUESE     0x16
#define LANG_PUNJABI        0x46
#define LANG_QUECHUA        0x6b
#define LANG_ROMANIAN       0x18
#define LANG_ROMANSH        0x17
#define LANG_RUSSIAN        0x19
#define LANG_SAMI           0x3b
#define LANG_SANSKRIT       0x4f
#define LANG_SERBIAN        0x1a
#define LANG_SERBIAN_NEUTRAL      0x7c1a
#define LANG_SINDHI         0x59
#define LANG_SINHALESE      0x5b
#define LANG_SLOVAK         0x1b
#define LANG_SLOVENIAN      0x24
#define LANG_SOTHO          0x6c
#define LANG_SPANISH        0x0a
#define LANG_SWAHILI        0x41
#define LANG_SWEDISH        0x1d
#define LANG_SYRIAC         0x5a
#define LANG_TAJIK          0x28
#define LANG_TAMAZIGHT      0x5f
#define LANG_TAMIL          0x49
#define LANG_TATAR          0x44
#define LANG_TELUGU         0x4a
#define LANG_THAI           0x1e
#define LANG_TIBETAN        0x51
#define LANG_TIGRIGNA       0x73
#define LANG_TSWANA         0x32
#define LANG_TURKISH        0x1f
#define LANG_TURKMEN        0x42
#define LANG_UIGHUR         0x80
#define LANG_UKRAINIAN      0x22
#define LANG_UPPER_SORBIAN  0x2e
#define LANG_URDU           0x20
#define LANG_UZBEK          0x43
#define LANG_VIETNAMESE     0x2a
#define LANG_WELSH          0x52
#define LANG_WOLOF          0x88
#define LANG_XHOSA          0x34
#define LANG_YAKUT          0x85
#define LANG_YI             0x78
#define LANG_YORUBA         0x6a
#define LANG_ZULU           0x35

/* These are documented by the MSDN but are missing from the Windows header */
#define LANG_MALAGASY       0x8d

/* FIXME: these are not defined anywhere */
#define LANG_SUTU           0x30
#define LANG_TSONGA         0x31
#define LANG_VENDA          0x33

/* non standard; keep the number high enough (but < 0xff) */
#define LANG_ESPERANTO			 0x8f
#define LANG_WALON			 0x90
#define LANG_CORNISH                     0x91
#define LANG_GAELIC                      0x94

/* Sublanguage definitions */
#define SUBLANG_NEUTRAL                  0x00    /* language neutral */
#define SUBLANG_DEFAULT                  0x01    /* user default */
#define SUBLANG_SYS_DEFAULT              0x02    /* system default */
#define SUBLANG_CUSTOM_DEFAULT           0x03
#define SUBLANG_CUSTOM_UNSPECIFIED       0x04
#define SUBLANG_UI_CUSTOM_DEFAULT        0x05

#define SUBLANG_AFRIKAANS_SOUTH_AFRICA     0x01
#define SUBLANG_ALBANIAN_ALBANIA           0x01
#define SUBLANG_ALSATIAN_FRANCE            0x01
#define SUBLANG_AMHARIC_ETHIOPIA           0x01
#define SUBLANG_ARABIC_SAUDI_ARABIA        0x01
#define SUBLANG_ARABIC_IRAQ                0x02
#define SUBLANG_ARABIC_EGYPT               0x03
#define SUBLANG_ARABIC_LIBYA               0x04
#define SUBLANG_ARABIC_ALGERIA             0x05
#define SUBLANG_ARABIC_MOROCCO             0x06
#define SUBLANG_ARABIC_TUNISIA             0x07
#define SUBLANG_ARABIC_OMAN                0x08
#define SUBLANG_ARABIC_YEMEN               0x09
#define SUBLANG_ARABIC_SYRIA               0x0a
#define SUBLANG_ARABIC_JORDAN              0x0b
#define SUBLANG_ARABIC_LEBANON             0x0c
#define SUBLANG_ARABIC_KUWAIT              0x0d
#define SUBLANG_ARABIC_UAE                 0x0e
#define SUBLANG_ARABIC_BAHRAIN             0x0f
#define SUBLANG_ARABIC_QATAR               0x10
#define SUBLANG_ARMENIAN_ARMENIA           0x01
#define SUBLANG_ASSAMESE_INDIA             0x01
#define SUBLANG_AZERI_LATIN                0x01
#define SUBLANG_AZERI_CYRILLIC             0x02
#define SUBLANG_BASHKIR_RUSSIA             0x01
#define SUBLANG_BASQUE_BASQUE              0x01
#define SUBLANG_BELARUSIAN_BELARUS         0x01
#define SUBLANG_BENGALI_INDIA              0x01
#define SUBLANG_BENGALI_BANGLADESH         0x02
#define SUBLANG_BOSNIAN_BOSNIA_HERZEGOVINA_LATIN 0x05
#define SUBLANG_BOSNIAN_BOSNIA_HERZEGOVINA_CYRILLIC 0x08
#define SUBLANG_BRETON_FRANCE              0x01
#define SUBLANG_BULGARIAN_BULGARIA         0x01
#define SUBLANG_CATALAN_CATALAN            0x01
#define SUBLANG_CHINESE_TRADITIONAL        0x01
#define SUBLANG_CHINESE_SIMPLIFIED         0x02
#define SUBLANG_CHINESE_HONGKONG           0x03
#define SUBLANG_CHINESE_SINGAPORE          0x04
#define SUBLANG_CHINESE_MACAU              0x05
#define SUBLANG_CORSICAN_FRANCE            0x01
#define SUBLANG_CROATIAN_CROATIA           0x01
#define SUBLANG_CROATIAN_BOSNIA_HERZEGOVINA_LATIN 0x04
#define SUBLANG_CZECH_CZECH_REPUBLIC       0x01
#define SUBLANG_DANISH_DENMARK             0x01
#define SUBLANG_DARI_AFGHANISTAN           0x01
#define SUBLANG_DIVEHI_MALDIVES            0x01
#define SUBLANG_DUTCH                      0x01
#define SUBLANG_DUTCH_BELGIAN              0x02
#define SUBLANG_ENGLISH_US                 0x01
#define SUBLANG_ENGLISH_UK                 0x02
#define SUBLANG_ENGLISH_AUS                0x03
#define SUBLANG_ENGLISH_CAN                0x04
#define SUBLANG_ENGLISH_NZ                 0x05
#define SUBLANG_ENGLISH_EIRE               0x06
#define SUBLANG_ENGLISH_SOUTH_AFRICA       0x07
#define SUBLANG_ENGLISH_JAMAICA            0x08
#define SUBLANG_ENGLISH_CARIBBEAN          0x09
#define SUBLANG_ENGLISH_BELIZE             0x0a
#define SUBLANG_ENGLISH_TRINIDAD           0x0b
#define SUBLANG_ENGLISH_ZIMBABWE           0x0c
#define SUBLANG_ENGLISH_PHILIPPINES        0x0d
#define SUBLANG_ENGLISH_INDIA              0x10
#define SUBLANG_ENGLISH_MALAYSIA           0x11
#define SUBLANG_ENGLISH_SINGAPORE          0x12
#define SUBLANG_ESTONIAN_ESTONIA           0x01
#define SUBLANG_FAEROESE_FAROE_ISLANDS     0x01
#define SUBLANG_FILIPINO_PHILIPPINES       0x01
#define SUBLANG_FINNISH_FINLAND            0x01
#define SUBLANG_FRENCH                     0x01
#define SUBLANG_FRENCH_BELGIAN             0x02
#define SUBLANG_FRENCH_CANADIAN            0x03
#define SUBLANG_FRENCH_SWISS               0x04
#define SUBLANG_FRENCH_LUXEMBOURG          0x05
#define SUBLANG_FRENCH_MONACO              0x06
#define SUBLANG_FRISIAN_NETHERLANDS        0x01
#define SUBLANG_GALICIAN_GALICIAN          0x01
#define SUBLANG_GEORGIAN_GEORGIA           0x01
#define SUBLANG_GERMAN                     0x01
#define SUBLANG_GERMAN_SWISS               0x02
#define SUBLANG_GERMAN_AUSTRIAN            0x03
#define SUBLANG_GERMAN_LUXEMBOURG          0x04
#define SUBLANG_GERMAN_LIECHTENSTEIN       0x05
#define SUBLANG_GREEK_GREECE               0x01
#define SUBLANG_GREENLANDIC_GREENLAND      0x01
#define SUBLANG_GUJARATI_INDIA             0x01
#define SUBLANG_HAUSA_NIGERIA_LATIN        0x01
#define SUBLANG_HEBREW_ISRAEL              0x01
#define SUBLANG_HINDI_INDIA                0x01
#define SUBLANG_HUNGARIAN_HUNGARY          0x01
#define SUBLANG_ICELANDIC_ICELAND          0x01
#define SUBLANG_IGBO_NIGERIA               0x01
#define SUBLANG_INDONESIAN_INDONESIA       0x01
#define SUBLANG_INUKTITUT_CANADA           0x01
#define SUBLANG_INUKTITUT_CANADA_LATIN     0x02
#define SUBLANG_IRISH_IRELAND              0x02
#define SUBLANG_ITALIAN                    0x01
#define SUBLANG_ITALIAN_SWISS              0x02
#define SUBLANG_JAPANESE_JAPAN             0x01
#define SUBLANG_KANNADA_INDIA              0x01
#define SUBLANG_KASHMIRI_SASIA             0x02
#define SUBLANG_KASHMIRI_INDIA             0x02
#define SUBLANG_KAZAK_KAZAKHSTAN           0x01
#define SUBLANG_KHMER_CAMBODIA             0x01
#define SUBLANG_KICHE_GUATEMALA            0x01
#define SUBLANG_KINYARWANDA_RWANDA         0X01
#define SUBLANG_KONKANI_INDIA              0x01
#define SUBLANG_KOREAN                     0x01
#define SUBLANG_KYRGYZ_KYRGYZSTAN          0x01
#define SUBLANG_LAO_LAO                    0x01
#define SUBLANG_LATVIAN_LATVIA             0x01
#define SUBLANG_LITHUANIAN_LITHUANIA       0x01
#define SUBLANG_LOWER_SORBIAN_GERMANY      0x02
#define SUBLANG_LUXEMBOURGISH_LUXEMBOURG   0x01
#define SUBLANG_MACEDONIAN_MACEDONIA       0x01
#define SUBLANG_MALAY_MALAYSIA             0x01
#define SUBLANG_MALAY_BRUNEI_DARUSSALAM    0x02
#define SUBLANG_MALAYALAM_INDIA            0x01
#define SUBLANG_MALTESE_MALTA              0x01
#define SUBLANG_MAORI_NEW_ZEALAND          0x01
#define SUBLANG_MAPUDUNGUN_CHILE           0x01
#define SUBLANG_MARATHI_INDIA              0x01
#define SUBLANG_MOHAWK_MOHAWK              0x01
#define SUBLANG_MONGOLIAN_CYRILLIC_MONGOLIA 0x01
#define SUBLANG_MONGOLIAN_PRC              0x02
#define SUBLANG_NEPALI_INDIA               0x02
#define SUBLANG_NEPALI_NEPAL               0x01
#define SUBLANG_NORWEGIAN_BOKMAL           0x01
#define SUBLANG_NORWEGIAN_NYNORSK          0x02
#define SUBLANG_OCCITAN_FRANCE             0x01
#define SUBLANG_ORIYA_INDIA                0x01
#define SUBLANG_PASHTO_AFGHANISTAN         0x01
#define SUBLANG_PERSIAN_IRAN               0x01
#define SUBLANG_POLISH_POLAND              0x01
#define SUBLANG_PORTUGUESE                 0x02
#define SUBLANG_PORTUGUESE_BRAZILIAN       0x01
#define SUBLANG_PUNJABI_INDIA              0x01
#define SUBLANG_QUECHUA_BOLIVIA            0x01
#define SUBLANG_QUECHUA_ECUADOR            0x02
#define SUBLANG_QUECHUA_PERU               0x03
#define SUBLANG_ROMANIAN_ROMANIA           0x01
#define SUBLANG_ROMANSH_SWITZERLAND        0x01
#define SUBLANG_RUSSIAN_RUSSIA             0x01
#define SUBLANG_SAMI_NORTHERN_NORWAY       0x01
#define SUBLANG_SAMI_NORTHERN_SWEDEN       0x02
#define SUBLANG_SAMI_NORTHERN_FINLAND      0x03
#define SUBLANG_SAMI_LULE_NORWAY           0x04
#define SUBLANG_SAMI_LULE_SWEDEN           0x05
#define SUBLANG_SAMI_SOUTHERN_NORWAY       0x06
#define SUBLANG_SAMI_SOUTHERN_SWEDEN       0x07
#define SUBLANG_SAMI_SKOLT_FINLAND         0x08
#define SUBLANG_SAMI_INARI_FINLAND         0x09
#define SUBLANG_SANSKRIT_INDIA             0x01
#define SUBLANG_SERBIAN_BOSNIA_HERZEGOVINA_LATIN 0x06
#define SUBLANG_SERBIAN_BOSNIA_HERZEGOVINA_CYRILLIC 0x07
#define SUBLANG_SERBIAN_CROATIA            0x01
#define SUBLANG_SERBIAN_LATIN              0x02
#define SUBLANG_SERBIAN_CYRILLIC           0x03
#define SUBLANG_SINDHI_AFGHANISTAN         0x02
#define SUBLANG_SINHALESE_SRI_LANKA        0x01
#define SUBLANG_SLOVAK_SLOVAKIA            0x01
#define SUBLANG_SLOVENIAN_SLOVENIA         0x01
#define SUBLANG_SOTHO_NORTHERN_SOUTH_AFRICA 0x01
#define SUBLANG_SPANISH                    0x01
#define SUBLANG_SPANISH_MEXICAN            0x02
#define SUBLANG_SPANISH_MODERN             0x03
#define SUBLANG_SPANISH_GUATEMALA          0x04
#define SUBLANG_SPANISH_COSTA_RICA         0x05
#define SUBLANG_SPANISH_PANAMA             0x06
#define SUBLANG_SPANISH_DOMINICAN_REPUBLIC 0x07
#define SUBLANG_SPANISH_VENEZUELA          0x08
#define SUBLANG_SPANISH_COLOMBIA           0x09
#define SUBLANG_SPANISH_PERU               0x0a
#define SUBLANG_SPANISH_ARGENTINA          0x0b
#define SUBLANG_SPANISH_ECUADOR            0x0c
#define SUBLANG_SPANISH_CHILE              0x0d
#define SUBLANG_SPANISH_URUGUAY            0x0e
#define SUBLANG_SPANISH_PARAGUAY           0x0f
#define SUBLANG_SPANISH_BOLIVIA            0x10
#define SUBLANG_SPANISH_EL_SALVADOR        0x11
#define SUBLANG_SPANISH_HONDURAS           0x12
#define SUBLANG_SPANISH_NICARAGUA          0x13
#define SUBLANG_SPANISH_PUERTO_RICO        0x14
#define SUBLANG_SPANISH_US                 0x15
#define SUBLANG_SWAHILI_KENYA              0x01
#define SUBLANG_SWEDISH                    0x01
#define SUBLANG_SWEDISH_FINLAND            0x02
#define SUBLANG_SYRIAC_SYRIA               0x01
#define SUBLANG_TAJIK_TAJIKISTAN           0x01
#define SUBLANG_TAMAZIGHT_ALGERIA_LATIN    0x02
#define SUBLANG_TAMIL_INDIA                0x01
#define SUBLANG_TATAR_RUSSIA               0x01
#define SUBLANG_TELUGU_INDIA               0x01
#define SUBLANG_THAI_THAILAND              0x01
#define SUBLANG_TIBETAN_PRC                0x01
#define SUBLANG_TIBETAN_BHUTAN             0x02
#define SUBLANG_TIGRIGNA_ERITREA           0x02
#define SUBLANG_TSWANA_SOUTH_AFRICA        0x01
#define SUBLANG_TURKISH_TURKEY             0x01
#define SUBLANG_TURKMEN_TURKMENISTAN       0x01
#define SUBLANG_UIGHUR_PRC                 0x01
#define SUBLANG_UKRAINIAN_UKRAINE          0x01
#define SUBLANG_UPPER_SORBIAN_GERMANY      0x01
#define SUBLANG_URDU_PAKISTAN              0x01
#define SUBLANG_URDU_INDIA                 0x02
#define SUBLANG_UZBEK_LATIN                0x01
#define SUBLANG_UZBEK_CYRILLIC             0x02
#define SUBLANG_VIETNAMESE_VIETNAM         0x01
#define SUBLANG_WELSH_UNITED_KINGDOM       0x01
#define SUBLANG_WOLOF_SENEGAL              0x01
#define SUBLANG_XHOSA_SOUTH_AFRICA         0x01
#define SUBLANG_YAKUT_RUSSIA               0x01
#define SUBLANG_YI_PRC                     0x01
#define SUBLANG_YORUBA_NIGERIA             0x01
#define SUBLANG_ZULU_SOUTH_AFRICA          0x01

/* These are documented by the MSDN but are missing from the Windows header */
#define SUBLANG_ENGLISH_IRELAND            SUBLANG_ENGLISH_EIRE
#define SUBLANG_HAUSA_NIGERIA              SUBLANG_HAUSA_NIGERIA_LATIN
#define SUBLANG_LAO_LAO_PDR                SUBLANG_LAO_LAO
#define SUBLANG_LITHUANIAN                 SUBLANG_LITHUANIAN_LITHUANIA
#define SUBLANG_PORTUGUESE_PORTUGAL        SUBLANG_PORTUGUESE
#define SUBLANG_SWAHILI                    SUBLANG_SWAHILI_KENYA
#define SUBLANG_SWEDISH_SWEDEN             SUBLANG_SWEDISH
#define SUBLANG_SYRIAC                     SUBLANG_SYRIAC_SYRIA

/* FIXME: these are not defined anywhere */
#define SUBLANG_DUTCH_SURINAM              0x03
#define SUBLANG_ROMANIAN                   SUBLANG_ROMANIAN_ROMANIA
#define SUBLANG_ROMANIAN_MOLDAVIA          0x02
#define SUBLANG_RUSSIAN                    SUBLANG_RUSSIAN_RUSSIA
#define SUBLANG_RUSSIAN_MOLDAVIA           0x02
#define SUBLANG_CROATIAN                   SUBLANG_CROATIAN_CROATIA
#define SUBLANG_LITHUANIAN_CLASSIC         0x02
#define SUBLANG_GAELIC                     0x01
#define SUBLANG_GAELIC_SCOTTISH            0x02
#define SUBLANG_GAELIC_MANX                0x03


/*
 * Sort definitions
 */

#define SORT_DEFAULT                     0x0
#define SORT_JAPANESE_XJIS               0x0
#define SORT_JAPANESE_UNICODE            0x1
#define SORT_CHINESE_BIG5                0x0
#define SORT_CHINESE_UNICODE             0x1
#define SORT_KOREAN_KSC                  0x0
#define SORT_KOREAN_UNICODE              0x1



/*
 * Definitions for IsTextUnicode()
 */

#define IS_TEXT_UNICODE_ASCII16		   0x0001
#define IS_TEXT_UNICODE_STATISTICS         0x0002
#define IS_TEXT_UNICODE_CONTROLS           0x0004
#define IS_TEXT_UNICODE_SIGNATURE	   0x0008
#define IS_TEXT_UNICODE_UNICODE_MASK       0x000F
#define IS_TEXT_UNICODE_REVERSE_ASCII16	   0x0010
#define IS_TEXT_UNICODE_REVERSE_STATISTICS 0x0020
#define IS_TEXT_UNICODE_REVERSE_CONTROLS   0x0040
#define IS_TEXT_UNICODE_REVERSE_SIGNATURE  0x0080
#define IS_TEXT_UNICODE_REVERSE_MASK       0x00F0
#define IS_TEXT_UNICODE_ILLEGAL_CHARS	   0x0100
#define IS_TEXT_UNICODE_ODD_LENGTH	   0x0200
#define IS_TEXT_UNICODE_DBCS_LEADBYTE      0x0400
#define IS_TEXT_UNICODE_NOT_UNICODE_MASK   0x0F00
#define IS_TEXT_UNICODE_NULL_BYTES         0x1000
#define IS_TEXT_UNICODE_NOT_ASCII_MASK     0xF000

#define MAXIMUM_WAIT_OBJECTS 64
#define MAXIMUM_SUSPEND_COUNT 127

#define WT_EXECUTEDEFAULT              0x00
#define WT_EXECUTEINIOTHREAD           0x01
#define WT_EXECUTEINUITHREAD           0x02
#define WT_EXECUTEINWAITTHREAD         0x04
#define WT_EXECUTEONLYONCE             0x08
#define WT_EXECUTELONGFUNCTION         0x10
#define WT_EXECUTEINTIMERTHREAD        0x20
#define WT_EXECUTEINPERSISTENTIOTHREAD 0x40
#define WT_EXECUTEINPERSISTENTTHREAD   0x80
#define WT_EXECUTEINLONGTHREAD         0x10
#define WT_EXECUTEDELETEWAIT           0x08
#define WT_TRANSFER_IMPERSONATION      0x0100


#define EXCEPTION_CONTINUABLE        0
#define EXCEPTION_NONCONTINUABLE     0x01

/*
 * The exception record used by Win32 to give additional information
 * about exception to exception handlers.
 */

#define EXCEPTION_MAXIMUM_PARAMETERS 15

typedef struct _EXCEPTION_RECORD
{
    ::u32    ExceptionCode;
    ::u32    ExceptionFlags;
    struct  _EXCEPTION_RECORD *ExceptionRecord;

    PVOID    ExceptionAddress;
    ::u32    NumberParameters;
    ULONG_PTR ExceptionInformation[EXCEPTION_MAXIMUM_PARAMETERS];
} EXCEPTION_RECORD, *PEXCEPTION_RECORD;

/*
 * The exception pointers structure passed to exception filters
 * in except() and the UnhandledExceptionFilter().
 */

typedef struct _EXCEPTION_POINTERS
{
  PEXCEPTION_RECORD  ExceptionRecord;
  PCONTEXT           ContextRecord;
} EXCEPTION_POINTERS, *PEXCEPTION_POINTERS;


/*
 * The exception frame, used for registering exception handlers
 * Win32 cares only about this, but compilers generally emit
 * larger exception frames for their own use.
 */

struct _EXCEPTION_REGISTRATION_RECORD;

typedef ::u32 (*PEXCEPTION_HANDLER)(PEXCEPTION_RECORD,struct _EXCEPTION_REGISTRATION_RECORD*,
                                    PCONTEXT,struct _EXCEPTION_REGISTRATION_RECORD **);

typedef struct _EXCEPTION_REGISTRATION_RECORD
{
  struct _EXCEPTION_REGISTRATION_RECORD *Prev;
  PEXCEPTION_HANDLER       Handler;
} EXCEPTION_REGISTRATION_RECORD;

/*
 * function pointer to an exception filter
 */

typedef ::i32 (CALLBACK *PVECTORED_EXCEPTION_HANDLER)(PEXCEPTION_POINTERS ExceptionInfo);

typedef struct _NT_TIB
{
	struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList;
	PVOID StackBase;
	PVOID StackLimit;
	PVOID SubSystemTib;
	union {
          PVOID FiberData;
          ::u32 Version;
	} DUMMYUNIONNAME;
	PVOID ArbitraryUserPointer;
	struct _NT_TIB *Self;
} NT_TIB, *PNT_TIB;

struct _TEB;

#if defined(__i386__) && defined(__GNUC__) && ((__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 2)))
static inline struct _TEB * WINAPI NtCurrentTeb(void)
{
    struct _TEB *teb;
    __asm__(".byte 0x64\n\tmovl (0x18),%0" : "=r" (teb));
    return teb;
}
#elif defined(__i386__) && defined(_MSC_VER)
static inline struct _TEB * WINAPI NtCurrentTeb(void)
{
  struct _TEB *teb;
  __asm mov eax, fs:[0x18];
  __asm mov teb, eax;
  return teb;
}
#elif defined(__x86_64__) && defined(__GNUC__)
static inline struct _TEB * WINAPI NtCurrentTeb(void)
{
    struct _TEB *teb;
    __asm__(".byte 0x65\n\tmovq (0x30),%0" : "=r" (teb));
    return teb;
}
#elif defined(__x86_64__) && defined (_MSC_VER)
static inline struct _TEB * WINAPI NtCurrentTeb(void)
{
  struct _TEB *teb;
  __asm mov rax, gs:[0x30];
  __asm mov teb, rax;
  return teb;
}
#elif defined(LINUX) && !defined(RASPBIAN)
#if defined(__x86_64__)
static inline struct _TEB * WINAPI NtCurrentTeb(void)
{
    struct _TEB *teb;
    __asm__(".byte 0x65\n\tmovq (0x30),%0" : "=r" (teb));
    return teb;
}
#else
static inline struct _TEB * WINAPI NtCurrentTeb(void)
{
    struct _TEB *teb;
    __asm__(".byte 0x64\n\tmovl (0x18),%0" : "=r" (teb));
    return teb;
}
#endif
#else
extern struct _TEB * WINAPI NtCurrentTeb(void);
#endif

#ifdef NONAMELESSUNION
#define GetCurrentFiber()  (((NT_TIB *)NtCurrentTeb())->u.FiberData)
#else
#define GetCurrentFiber()  (((NT_TIB *)NtCurrentTeb())->FiberData)
#endif
#define GetFiberData()     (*(void **)GetCurrentFiber())

#define TLS_MINIMUM_AVAILABLE 64

/*
 * File formats definitions
 */

//#include "windows_pshpack2.h"
//typedef struct _IMAGE_DOS_HEADER {
//    ::u16  e_magic;      /* 00: MZ Header signature */
//    ::u16  e_cblp;       /* 02: Bytes on last page of file */
//    ::u16  e_cp;         /* 04: Pages in file */
//    ::u16  e_crlc;       /* 06: Relocations */
//    ::u16  e_cparhdr;    /* 08: Size of header in paragraphs */
//    ::u16  e_minalloc;   /* 0a: Minimum extra paragraphs needed */
//    ::u16  e_maxalloc;   /* 0c: Maximum extra paragraphs needed */
//    ::u16  e_ss;         /* 0e: Initial (relative) SS value */
//    ::u16  e_pointer;         /* 10: Initial SP value */
//    ::u16  e_csum;       /* 12: Checksum */
//    ::u16  e_ip;         /* 14: Initial IP value */
//    ::u16  e_cs;         /* 16: Initial (relative) CS value */
//    ::u16  e_lfarlc;     /* 18: File address of relocation table */
//    ::u16  e_ovno;       /* 1a: Overlay number */
//    ::u16  e_res[4];     /* 1c: Reserved words */
//    ::u16  e_oemid;      /* 24: OEM identifier (for e_oeminfo) */
//    ::u16  e_oeminfo;    /* 26: OEM information; e_oemid specific */
//    ::u16  e_res2[10];   /* 28: Reserved words */
//    ::u32 e_lfanew;     /* 3c: Offset to extended header */
//} IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;
//#include "windows_poppack.h"

#define IMAGE_DOS_SIGNATURE    0x5A4D     /* MZ   */
#define IMAGE_OS2_SIGNATURE    0x454E     /* NE   */
#define IMAGE_OS2_SIGNATURE_LE 0x454C     /* LE   */
#define IMAGE_OS2_SIGNATURE_LX 0x584C     /* LX */
#define IMAGE_VXD_SIGNATURE    0x454C     /* LE   */
#define IMAGE_NT_SIGNATURE     0x00004550 /* PE00 */

/*
 * This is the Windows executable (NE) header.
 * the name IMAGE_OS2_HEADER is misleading, but in the SDK this way.
 */
//#include "windows_pshpack2.h"
//typedef struct
//{
//    ::u16  ne_magic;             /* 00 NE signature 'NE' */
//    byte  ne_ver;               /* 02 Linker version number */
//    byte  ne_rev;               /* 03 Linker revision number */
//    ::u16  ne_enttab;            /* 04 Offset to entry table relative to NE */
//    ::u16  ne_cbenttab;          /* 06 Length of entry table in bytes */
//    ::i32  ne_crc;               /* 08 Checksum */
//    ::u16  ne_flags;             /* 0c Flags about segments in this file */
//    ::u16  ne_autodata;          /* 0e Automatic data segment number */
//    ::u16  ne_heap;              /* 10 Initial size of local heap */
//    ::u16  ne_stack;             /* 12 Initial size of stack */
//    ::u32 ne_csip;              /* 14 Initial CS:IP */
//    ::u32 ne_sssp;              /* 18 Initial SS:SP */
//    ::u16  ne_cseg;              /* 1c # of entries in segment table */
//    ::u16  ne_cmod;              /* 1e # of entries in module object tab. */
//    ::u16  ne_cbnrestab;         /* 20 Length of nonresident-name table     */
//    ::u16  ne_segtab;            /* 22 Offset to segment table */
//    ::u16  ne_rsrctab;           /* 24 Offset to resource table */
//    ::u16  ne_restab;            /* 26 Offset to resident-name table */
//    ::u16  ne_modtab;            /* 28 Offset to module object table */
//    ::u16  ne_imptab;            /* 2a Offset to imported name table */
//    ::u32 ne_nrestab;           /* 2c Offset to nonresident-name table */
//    ::u16  ne_cmovent;           /* 30 # of movable entry points */
//    ::u16  ne_align;             /* 32 Logical sector alignment shift count */
//    ::u16  ne_cres;              /* 34 # of resource segments */
//    byte  ne_exetyp;            /* 36 Flags indicating target OS */
//    byte  ne_flagsothers;       /* 37 Additional information flags */
//    ::u16  ne_pretthunks;        /* 38 Offset to return thunks */
//    ::u16  ne_psegrefbytes;      /* 3a Offset to segment ref. bytes */
//    ::u16  ne_swaparea;          /* 3c Reserved by Microsoft */
//    ::u16  ne_expver;            /* 3e Expected Windows version number */
//} IMAGE_OS2_HEADER, *PIMAGE_OS2_HEADER;
//#include "windows_poppack.h"

//#include "windows_pshpack2.h"
//typedef struct _IMAGE_VXD_HEADER {
//  ::u16  e32_magic;
//  byte  e32_border;
//  byte  e32_worder;
//  ::u32 e32_level;
//  ::u16  e32_cpu;
//  ::u16  e32_os;
//  ::u32 e32_ver;
//  ::u32 e32_mflags;
//  ::u32 e32_mpages;
//  ::u32 e32_startobj;
//  ::u32 e32_eip;
//  ::u32 e32_stackobj;
//  ::u32 e32_esp;
//  ::u32 e32_pagesize;
//  ::u32 e32_lastpagesize;
//  ::u32 e32_fixupsize;
//  ::u32 e32_fixupsum;
//  ::u32 e32_ldrsize;
//  ::u32 e32_ldrsum;
//  ::u32 e32_objtab;
//  ::u32 e32_objcnt;
//  ::u32 e32_objmap;
//  ::u32 e32_itermap;
//  ::u32 e32_rsrctab;
//  ::u32 e32_rsrccnt;
//  ::u32 e32_restab;
//  ::u32 e32_enttab;
//  ::u32 e32_dirtab;
//  ::u32 e32_dircnt;
//  ::u32 e32_fpagetab;
//  ::u32 e32_frectab;
//  ::u32 e32_impmod;
//  ::u32 e32_impmodcnt;
//  ::u32 e32_impproc;
//  ::u32 e32_pagesum;
//  ::u32 e32_datapage;
//  ::u32 e32_preload;
//  ::u32 e32_nrestab;
//  ::u32 e32_cbnrestab;
//  ::u32 e32_nressum;
//  ::u32 e32_autodata;
//  ::u32 e32_debuginfo;
//  ::u32 e32_debuglen;
//  ::u32 e32_instpreload;
//  ::u32 e32_instdemand;
//  ::u32 e32_heapsize;
//  byte  e32_res3[12];
//  ::u32 e32_winresoff;
//  ::u32 e32_winreslen;
//  ::u16  e32_devid;
//  ::u16  e32_ddkver;
//} IMAGE_VXD_HEADER, *PIMAGE_VXD_HEADER;
//#include "windows_poppack.h"

/* These defines describe the meanings of the bits in the Characteristics
   field */

#define IMAGE_FILE_RELOCS_STRIPPED	0x0001 /* No relocation info */
#define IMAGE_FILE_EXECUTABLE_IMAGE	0x0002
#define IMAGE_FILE_LINE_NUMS_STRIPPED   0x0004
#define IMAGE_FILE_LOCAL_SYMS_STRIPPED  0x0008
#define IMAGE_FILE_AGGRESIVE_WS_TRIM	0x0010
#define IMAGE_FILE_LARGE_ADDRESS_AWARE	0x0020
#define IMAGE_FILE_16BIT_MACHINE	0x0040
#define IMAGE_FILE_BYTES_REVERSED_LO	0x0080
#define IMAGE_FILE_32BIT_MACHINE	0x0100
#define IMAGE_FILE_DEBUG_STRIPPED	0x0200
#define IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP	0x0400
#define IMAGE_FILE_NET_RUN_FROM_SWAP	0x0800
#define IMAGE_FILE_SYSTEM		0x1000
#define IMAGE_FILE_DLL			0x2000
#define IMAGE_FILE_UP_SYSTEM_ONLY	0x4000
#define IMAGE_FILE_BYTES_REVERSED_HI	0x8000

/* These are the settings of the Machine field. */
#define	IMAGE_FILE_MACHINE_UNKNOWN	0
#define	IMAGE_FILE_MACHINE_I860		0x014d
#define	IMAGE_FILE_MACHINE_I386		0x014c
#define	IMAGE_FILE_MACHINE_R3000	0x0162
#define	IMAGE_FILE_MACHINE_R4000	0x0166
#define	IMAGE_FILE_MACHINE_R10000	0x0168
#define	IMAGE_FILE_MACHINE_WCEMIPSV2	0x0169
#define	IMAGE_FILE_MACHINE_ALPHA	0x0184
#define	IMAGE_FILE_MACHINE_SH3		0x01a2
#define	IMAGE_FILE_MACHINE_SH3DSP	0x01a3
#define	IMAGE_FILE_MACHINE_SH3E		0x01a4
#define	IMAGE_FILE_MACHINE_SH4		0x01a6
#define	IMAGE_FILE_MACHINE_SH5		0x01a8
#define	IMAGE_FILE_MACHINE_ARM		0x01c0
#define	IMAGE_FILE_MACHINE_THUMB	0x01c2
#define	IMAGE_FILE_MACHINE_AM33		0x01d3
#define	IMAGE_FILE_MACHINE_POWERPC	0x01f0
#define	IMAGE_FILE_MACHINE_POWERPCFP	0x01f1
#define	IMAGE_FILE_MACHINE_IA64		0x0200
#define	IMAGE_FILE_MACHINE_MIPS16	0x0266
#define	IMAGE_FILE_MACHINE_ALPHA64	0x0284
#define	IMAGE_FILE_MACHINE_MIPSFPU	0x0366
#define	IMAGE_FILE_MACHINE_MIPSFPU16	0x0466
#define	IMAGE_FILE_MACHINE_AXP64	IMAGE_FILE_MACHINE_ALPHA64
#define	IMAGE_FILE_MACHINE_TRICORE	0x0520
#define	IMAGE_FILE_MACHINE_CEF		0x0cef
#define	IMAGE_FILE_MACHINE_EBC		0x0ebc
#define	IMAGE_FILE_MACHINE_AMD64	0x8664
#define	IMAGE_FILE_MACHINE_M32R		0x9041
#define	IMAGE_FILE_MACHINE_CEE		0xc0ee

/* Wine extension */
#define	IMAGE_FILE_MACHINE_SPARC	0x2000

#define	IMAGE_SIZEOF_FILE_HEADER		20
#define IMAGE_SIZEOF_ROM_OPTIONAL_HEADER	56
#define IMAGE_SIZEOF_STD_OPTIONAL_HEADER	28
#define IMAGE_SIZEOF_NT_OPTIONAL32_HEADER 	224
#define IMAGE_SIZEOF_NT_OPTIONAL64_HEADER 	240
#define IMAGE_SIZEOF_SHORT_NAME 		8
#define IMAGE_SIZEOF_SECTION_HEADER 		40
#define IMAGE_SIZEOF_SYMBOL 			18
#define IMAGE_SIZEOF_AUX_SYMBOL 		18
#define IMAGE_SIZEOF_RELOCATION 		10
#define IMAGE_SIZEOF_BASE_RELOCATION 		8
#define IMAGE_SIZEOF_LINENUMBER 		6
#define IMAGE_SIZEOF_ARCHIVE_MEMBER_HDR 	60

/* Possible Magic values */
#define IMAGE_NT_OPTIONAL_HDR32_MAGIC      0x10b
#define IMAGE_NT_OPTIONAL_HDR64_MAGIC      0x20b
#define IMAGE_ROM_OPTIONAL_HDR_MAGIC       0x107

#ifdef OS64BIT
#define IMAGE_SIZEOF_NT_OPTIONAL_HEADER IMAGE_SIZEOF_NT_OPTIONAL64_HEADER
#define IMAGE_NT_OPTIONAL_HDR_MAGIC     IMAGE_NT_OPTIONAL_HDR64_MAGIC
#else
#define IMAGE_SIZEOF_NT_OPTIONAL_HEADER IMAGE_SIZEOF_NT_OPTIONAL32_HEADER
#define IMAGE_NT_OPTIONAL_HDR_MAGIC     IMAGE_NT_OPTIONAL_HDR32_MAGIC
#endif

/* These are indexes into the DataDirectory array */
#define IMAGE_FILE_EXPORT_DIRECTORY		0
#define IMAGE_FILE_IMPORT_DIRECTORY		1
#define IMAGE_FILE_RESOURCE_DIRECTORY		2
#define IMAGE_FILE_EXCEPTION_DIRECTORY		3
#define IMAGE_FILE_SECURITY_DIRECTORY		4
#define IMAGE_FILE_BASE_RELOCATION_TABLE	5
#define IMAGE_FILE_DEBUG_DIRECTORY		6
#define IMAGE_FILE_DESCRIPTION_STRING		7
#define IMAGE_FILE_MACHINE_VALUE		8  /* Mips */
#define IMAGE_FILE_THREAD_LOCAL_STORAGE		9
#define IMAGE_FILE_CALLBACK_DIRECTORY		10

/* Directory Entries, indices into the DataDirectory array */

#define	IMAGE_DIRECTORY_ENTRY_EXPORT		0
#define	IMAGE_DIRECTORY_ENTRY_IMPORT		1
#define	IMAGE_DIRECTORY_ENTRY_RESOURCE		2
#define	IMAGE_DIRECTORY_ENTRY_EXCEPTION		3
#define	IMAGE_DIRECTORY_ENTRY_SECURITY		4
#define	IMAGE_DIRECTORY_ENTRY_BASERELOC		5
#define	IMAGE_DIRECTORY_ENTRY_DEBUG		6
#define	IMAGE_DIRECTORY_ENTRY_COPYRIGHT		7
#define	IMAGE_DIRECTORY_ENTRY_GLOBALPTR		8   /* (MIPS GP) */
#define	IMAGE_DIRECTORY_ENTRY_TLS		9
#define	IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG	10
#define	IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT	11
#define	IMAGE_DIRECTORY_ENTRY_IAT		12  /* Import Address Table */
#define	IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT	13
#define	IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR	14

/* Subsystem Values */

#define	IMAGE_SUBSYSTEM_UNKNOWN			0
#define	IMAGE_SUBSYSTEM_NATIVE			1
#define	IMAGE_SUBSYSTEM_WINDOWS_GUI		2	/* Windows GUI subsystem */
#define	IMAGE_SUBSYSTEM_WINDOWS_CUI		3	/* Windows character subsystem */
#define	IMAGE_SUBSYSTEM_OS2_CUI			5
#define	IMAGE_SUBSYSTEM_POSIX_CUI		7
#define	IMAGE_SUBSYSTEM_NATIVE_WINDOWS		8	/* native Win9x driver */
#define	IMAGE_SUBSYSTEM_WINDOWS_CE_GUI		9	/* Windows CE subsystem */
#define	IMAGE_SUBSYSTEM_EFI_APPLICATION		10
#define	IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER	11
#define	IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER	12
#define	IMAGE_SUBSYSTEM_EFI_ROM			13
#define	IMAGE_SUBSYSTEM_XBOX			14
#define	IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION	16

/* DLL Characteristics */
#define IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE          0x0040
#define IMAGE_DLLCHARACTERISTICS_FORCE_INTEGRITY       0x0080
#define IMAGE_DLLCHARACTERISTICS_NX_COMPAT             0x0100
#define IMAGE_DLLCHARACTERISTICS_NO_ISOLATION          0x0200
#define IMAGE_DLLCHARACTERISTICS_NO_SEH                0x0400
#define IMAGE_DLLCHARACTERISTICS_NO_BIND               0x0800
#define IMAGE_DLLCHARACTERISTICS_WDM_DRIVER            0x2000
#define IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE 0x8000

typedef struct _IMAGE_FILE_HEADER {
  ::u16  Machine;
  ::u16  NumberOfSections;
  ::u32 TimeDateStamp;
  ::u32 PointerToSymbolTable;
  ::u32 NumberOfSymbols;
  ::u16  SizeOfOptionalHeader;
  ::u16  Characteristics;
} IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;

typedef struct _IMAGE_DATA_DIRECTORY {
  ::u32 VirtualAddress;
  ::u32 Size;
} IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;

#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES 16

typedef struct _IMAGE_OPTIONAL_HEADER64 {
  ::u16  Magic; /* 0x20b */
  byte MajorLinkerVersion;
  byte MinorLinkerVersion;
  ::u32 SizeOfCode;
  ::u32 SizeOfInitializedData;
  ::u32 SizeOfUninitializedData;
  ::u32 AddressOfEntryPoint;
  ::u32 BaseOfCode;
  ULONGLONG ImageBase;
  ::u32 SectionAlignment;
  ::u32 FileAlignment;
  ::u16 MajorOperatingSystemVersion;
  ::u16 MinorOperatingSystemVersion;
  ::u16 MajorImageVersion;
  ::u16 MinorImageVersion;
  ::u16 MajorSubsystemVersion;
  ::u16 MinorSubsystemVersion;
  ::u32 Win32VersionValue;
  ::u32 SizeOfImage;
  ::u32 SizeOfHeaders;
  ::u32 CheckSum;
  ::u16 Subsystem;
  ::u16 DllCharacteristics;
  ULONGLONG SizeOfStackReserve;
  ULONGLONG SizeOfStackCommit;
  ULONGLONG SizeOfHeapReserve;
  ULONGLONG SizeOfHeapCommit;
  ::u32 LoaderFlags;
  ::u32 NumberOfRvaAndSizes;
  IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
} IMAGE_OPTIONAL_HEADER64, *PIMAGE_OPTIONAL_HEADER64;

typedef struct _IMAGE_NT_HEADERS64 {
  ::u32 Signature;
  IMAGE_FILE_HEADER FileHeader;
  IMAGE_OPTIONAL_HEADER64 OptionalHeader;
} IMAGE_NT_HEADERS64, *PIMAGE_NT_HEADERS64;

typedef struct _IMAGE_OPTIONAL_HEADER {

  /* Standard fields */

  ::u16  Magic; /* 0x10b or 0x107 */	/* 0x00 */
  byte  MajorLinkerVersion;
  byte  MinorLinkerVersion;
  ::u32 SizeOfCode;
  ::u32 SizeOfInitializedData;
  ::u32 SizeOfUninitializedData;
  ::u32 AddressOfEntryPoint;		/* 0x10 */
  ::u32 BaseOfCode;
  ::u32 BaseOfData;

  /* NT additional fields */

  ::u32 ImageBase;
  ::u32 SectionAlignment;		/* 0x20 */
  ::u32 FileAlignment;
  ::u16  MajorOperatingSystemVersion;
  ::u16  MinorOperatingSystemVersion;
  ::u16  MajorImageVersion;
  ::u16  MinorImageVersion;
  ::u16  MajorSubsystemVersion;		/* 0x30 */
  ::u16  MinorSubsystemVersion;
  ::u32 Win32VersionValue;
  ::u32 SizeOfImage;
  ::u32 SizeOfHeaders;
  ::u32 CheckSum;			/* 0x40 */
  ::u16  Subsystem;
  ::u16  DllCharacteristics;
  ::u32 SizeOfStackReserve;
  ::u32 SizeOfStackCommit;
  ::u32 SizeOfHeapReserve;		/* 0x50 */
  ::u32 SizeOfHeapCommit;
  ::u32 LoaderFlags;
  ::u32 NumberOfRvaAndSizes;
  IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES]; /* 0x60 */
  /* 0xE0 */
} IMAGE_OPTIONAL_HEADER32, *PIMAGE_OPTIONAL_HEADER32;

typedef struct _IMAGE_NT_HEADERS {
  ::u32 Signature; /* "PE"\0\0 */	/* 0x00 */
  IMAGE_FILE_HEADER FileHeader;		/* 0x04 */
  IMAGE_OPTIONAL_HEADER32 OptionalHeader;	/* 0x18 */
} IMAGE_NT_HEADERS32, *PIMAGE_NT_HEADERS32;

#ifdef OS64BIT
typedef IMAGE_NT_HEADERS64  IMAGE_NT_HEADERS;
typedef PIMAGE_NT_HEADERS64 PIMAGE_NT_HEADERS;
typedef IMAGE_OPTIONAL_HEADER64 IMAGE_OPTIONAL_HEADER;
typedef PIMAGE_OPTIONAL_HEADER64 PIMAGE_OPTIONAL_HEADER;
#else
typedef IMAGE_NT_HEADERS32  IMAGE_NT_HEADERS;
typedef PIMAGE_NT_HEADERS32 PIMAGE_NT_HEADERS;
typedef IMAGE_OPTIONAL_HEADER32 IMAGE_OPTIONAL_HEADER;
typedef PIMAGE_OPTIONAL_HEADER32 PIMAGE_OPTIONAL_HEADER;
#endif

#define IMAGE_SIZEOF_SHORT_NAME 8

typedef struct _IMAGE_SECTION_HEADER {
  byte  Name[IMAGE_SIZEOF_SHORT_NAME];
  union {
    ::u32 PhysicalAddress;
    ::u32 VirtualSize;
  } Misc;
  ::u32 VirtualAddress;
  ::u32 SizeOfRawData;
  ::u32 PointerToRawData;
  ::u32 PointerToRelocations;
  ::u32 PointerToLinenumbers;
  ::u16  NumberOfRelocations;
  ::u16  NumberOfLinenumbers;
  ::u32 Characteristics;
} IMAGE_SECTION_HEADER, *PIMAGE_SECTION_HEADER;

#define	IMAGE_SIZEOF_SECTION_HEADER 40

#define IMAGE_FIRST_SECTION(ntheader) \
  ((PIMAGE_SECTION_HEADER)(ULONG_PTR)((const byte *)&((const IMAGE_NT_HEADERS *)(ntheader))->OptionalHeader + \
                           ((const IMAGE_NT_HEADERS *)(ntheader))->FileHeader.SizeOfOptionalHeader))

/* These defines are for the Characteristics bitfield. */
/* #define IMAGE_SCN_TYPE_REG			0x00000000 - Reserved */
/* #define IMAGE_SCN_TYPE_DSECT			0x00000001 - Reserved */
/* #define IMAGE_SCN_TYPE_NOLOAD		0x00000002 - Reserved */
/* #define IMAGE_SCN_TYPE_GROUP			0x00000004 - Reserved */
#define IMAGE_SCN_TYPE_NO_PAD			0x00000008 /* Reserved */
/* #define IMAGE_SCN_TYPE_COPY			0x00000010 - Reserved */

#define IMAGE_SCN_CNT_CODE			0x00000020
#define IMAGE_SCN_CNT_INITIALIZED_DATA		0x00000040
#define IMAGE_SCN_CNT_UNINITIALIZED_DATA	0x00000080

#define	IMAGE_SCN_LNK_OTHER			0x00000100
#define	IMAGE_SCN_LNK_INFO			0x00000200
/* #define	IMAGE_SCN_TYPE_OVER		0x00000400 - Reserved */
#define	IMAGE_SCN_LNK_REMOVE			0x00000800
#define	IMAGE_SCN_LNK_COMDAT			0x00001000

/* 						0x00002000 - Reserved */
/* #define IMAGE_SCN_MEM_PROTECTED 		0x00004000 - Obsolete */
#define	IMAGE_SCN_MEM_FARDATA			0x00008000

/* #define IMAGE_SCN_MEM_SYSHEAP		0x00010000 - Obsolete */
#define	IMAGE_SCN_MEM_PURGEABLE			0x00020000
#define	IMAGE_SCN_MEM_16BIT			0x00020000
#define	IMAGE_SCN_MEM_LOCKED			0x00040000
#define	IMAGE_SCN_MEM_PRELOAD			0x00080000

#define	IMAGE_SCN_ALIGN_1BYTES			0x00100000
#define	IMAGE_SCN_ALIGN_2BYTES			0x00200000
#define	IMAGE_SCN_ALIGN_4BYTES			0x00300000
#define	IMAGE_SCN_ALIGN_8BYTES			0x00400000
#define	IMAGE_SCN_ALIGN_16BYTES			0x00500000  /* Default */
#define	IMAGE_SCN_ALIGN_32BYTES			0x00600000
#define	IMAGE_SCN_ALIGN_64BYTES			0x00700000
#define	IMAGE_SCN_ALIGN_128BYTES		0x00800000
#define	IMAGE_SCN_ALIGN_256BYTES		0x00900000
#define	IMAGE_SCN_ALIGN_512BYTES		0x00A00000
#define	IMAGE_SCN_ALIGN_1024BYTES		0x00B00000
#define	IMAGE_SCN_ALIGN_2048BYTES		0x00C00000
#define	IMAGE_SCN_ALIGN_4096BYTES		0x00D00000
#define	IMAGE_SCN_ALIGN_8192BYTES		0x00E00000
/* 						0x00F00000 - Unused */
#define	IMAGE_SCN_ALIGN_MASK			0x00F00000

#define IMAGE_SCN_LNK_NRELOC_OVFL		0x01000000


#define IMAGE_SCN_MEM_DISCARDABLE		0x02000000
#define IMAGE_SCN_MEM_NOT_CACHED		0x04000000
#define IMAGE_SCN_MEM_NOT_PAGED			0x08000000
#define IMAGE_SCN_MEM_SHARED			0x10000000
#define IMAGE_SCN_MEM_EXECUTE			0x20000000
#define IMAGE_SCN_MEM_READ			0x40000000
#define IMAGE_SCN_MEM_WRITE			0x80000000

//#include "windows_pshpack2.h"
//
//typedef struct _IMAGE_SYMBOL {
//    union {
//        byte    ShortName[8];
//        struct {
//            ::u32   Short;
//            ::u32   Long;
//        } Name;
//        ::u32   LongName[2];
//    } N;
//    ::u32   Value;
//    SHORT   SectionNumber;
//    ::u16    Type;
//    byte    StorageClass;
//    byte    NumberOfAuxSymbols;
//} IMAGE_SYMBOL;
//typedef IMAGE_SYMBOL *PIMAGE_SYMBOL;
//
//#define IMAGE_SIZEOF_SYMBOL 18
//
//typedef struct _IMAGE_LINENUMBER {
//    union {
//        ::u32   SymbolTableIndex;
//        ::u32   VirtualAddress;
//    } Type;
//    ::u16    Linenumber;
//} IMAGE_LINENUMBER;
//typedef IMAGE_LINENUMBER *PIMAGE_LINENUMBER;
//
//#define IMAGE_SIZEOF_LINENUMBER  6
//
//typedef union _IMAGE_AUX_SYMBOL {
//    struct {
//        ::u32    TagIndex;
//        union {
//            struct {
//                ::u16    Linenumber;
//                ::u16    Size;
//            } LnSz;
//           ::u32    TotalSize;
//        } Misc;
//        union {
//            struct {
//                ::u32    PointerToLinenumber;
//                ::u32    PointerToNextFunction;
//            } Function;
//            struct {
//                ::u16     Dimension[4];
//            } Array;
//        } FcnAry;
//        ::u16    TvIndex;
//    } Sym;
//    struct {
//        byte    Name[IMAGE_SIZEOF_SYMBOL];
//    } File;
//    struct {
//        ::u32   Length;
//        ::u16    NumberOfRelocations;
//        ::u16    NumberOfLinenumbers;
//        ::u32   CheckSum;
//        SHORT   Number;
//        byte    Selection;
//    } Section;
//} IMAGE_AUX_SYMBOL;
//typedef IMAGE_AUX_SYMBOL *PIMAGE_AUX_SYMBOL;
//
//#define IMAGE_SIZEOF_AUX_SYMBOL 18
//
//#include "windows_poppack.h"

#define IMAGE_SYM_UNDEFINED           (SHORT)0
#define IMAGE_SYM_ABSOLUTE            (SHORT)-1
#define IMAGE_SYM_DEBUG               (SHORT)-2

#define IMAGE_SYM_TYPE_NULL                 0x0000
#define IMAGE_SYM_TYPE_VOID                 0x0001
#define IMAGE_SYM_TYPE_CHAR                 0x0002
#define IMAGE_SYM_TYPE_SHORT                0x0003
#define IMAGE_SYM_TYPE_INT                  0x0004
#define IMAGE_SYM_TYPE_LONG                 0x0005
#define IMAGE_SYM_TYPE_FLOAT                0x0006
#define IMAGE_SYM_TYPE_DOUBLE               0x0007
#define IMAGE_SYM_TYPE_STRUCT               0x0008
#define IMAGE_SYM_TYPE_UNION                0x0009
#define IMAGE_SYM_TYPE_ENUM                 0x000A
#define IMAGE_SYM_TYPE_MOE                  0x000B
#define IMAGE_SYM_TYPE_BYTE                 0x000C
#define IMAGE_SYM_TYPE_WORD                 0x000D
#define IMAGE_SYM_TYPE_::u32                 0x000E
#define IMAGE_SYM_TYPE_DWORD                0x000F
#define IMAGE_SYM_TYPE_PCODE                0x8000

#define IMAGE_SYM_DTYPE_NULL                0
#define IMAGE_SYM_DTYPE_POINTER             1
#define IMAGE_SYM_DTYPE_FUNCTION            2
#define IMAGE_SYM_DTYPE_ARRAY               3

#define IMAGE_SYM_CLASS_END_OF_FUNCTION     (byte )-1
#define IMAGE_SYM_CLASS_NULL                0x0000
#define IMAGE_SYM_CLASS_AUTOMATIC           0x0001
#define IMAGE_SYM_CLASS_EXTERNAL            0x0002
#define IMAGE_SYM_CLASS_STATIC              0x0003
#define IMAGE_SYM_CLASS_REGISTER            0x0004
#define IMAGE_SYM_CLASS_EXTERNAL_DEF        0x0005
#define IMAGE_SYM_CLASS_LABEL               0x0006
#define IMAGE_SYM_CLASS_UNDEFINED_LABEL     0x0007
#define IMAGE_SYM_CLASS_MEMBER_OF_STRUCT    0x0008
#define IMAGE_SYM_CLASS_ARGUMENT            0x0009
#define IMAGE_SYM_CLASS_STRUCT_TAG          0x000A
#define IMAGE_SYM_CLASS_MEMBER_OF_UNION     0x000B
#define IMAGE_SYM_CLASS_UNION_TAG           0x000C
#define IMAGE_SYM_CLASS_TYPE_DEFINITION     0x000D
#define IMAGE_SYM_CLASS_UNDEFINED_STATIC    0x000E
#define IMAGE_SYM_CLASS_ENUM_TAG            0x000F
#define IMAGE_SYM_CLASS_MEMBER_OF_ENUM      0x0010
#define IMAGE_SYM_CLASS_REGISTER_PARAM      0x0011
#define IMAGE_SYM_CLASS_BIT_FIELD           0x0012

#define IMAGE_SYM_CLASS_FAR_EXTERNAL        0x0044
#define IMAGE_SYM_CLASS_BLOCK               0x0064
#define IMAGE_SYM_CLASS_FUNCTION            0x0065
#define IMAGE_SYM_CLASS_END_OF_STRUCT       0x0066
#define IMAGE_SYM_CLASS_FILE                0x0067
#define IMAGE_SYM_CLASS_SECTION             0x0068
#define IMAGE_SYM_CLASS_WEAK_EXTERNAL       0x0069

#define N_BTMASK                            0x000F
#define N_TMASK                             0x0030
#define N_TMASK1                            0x00C0
#define N_TMASK2                            0x00F0
#define N_BTSHFT                            4
#define N_TSHIFT                            2

#define BTYPE(x) ((x) & N_BTMASK)

#ifndef ISPTR
#define ISPTR(x) (((x) & N_TMASK) == (IMAGE_SYM_DTYPE_POINTER << N_BTSHFT))
#endif

#ifndef ISFCN
#define ISFCN(x) (((x) & N_TMASK) == (IMAGE_SYM_DTYPE_FUNCTION << N_BTSHFT))
#endif

#ifndef ISARY
#define ISARY(x) (((x) & N_TMASK) == (IMAGE_SYM_DTYPE_ARRAY << N_BTSHFT))
#endif

#ifndef ISTAG
#define ISTAG(x) ((x)==IMAGE_SYM_CLASS_STRUCT_TAG || (x)==IMAGE_SYM_CLASS_UNION_TAG || (x)==IMAGE_SYM_CLASS_ENUM_TAG)
#endif

#ifndef INCREF
#define INCREF(x) ((((x)&~N_BTMASK)<<N_TSHIFT)|(IMAGE_SYM_DTYPE_POINTER<<N_BTSHFT)|((x)&N_BTMASK))
#endif
#ifndef DECREF
#define DECREF(x) ((((x)>>N_TSHIFT)&~N_BTMASK)|((x)&N_BTMASK))
#endif

#define IMAGE_COMDAT_SELECT_NODUPLICATES    1
#define IMAGE_COMDAT_SELECT_ANY             2
#define IMAGE_COMDAT_SELECT_SAME_SIZE       3
#define IMAGE_COMDAT_SELECT_EXACT_MATCH     4
#define IMAGE_COMDAT_SELECT_ASSOCIATIVE     5
#define IMAGE_COMDAT_SELECT_LARGEST         6
#define IMAGE_COMDAT_SELECT_NEWEST          7

#define IMAGE_WEAK_EXTERN_SEARCH_NOLIBRARY  1
#define IMAGE_WEAK_EXTERN_SEARCH_LIBRARY    2
#define IMAGE_WEAK_EXTERN_SEARCH_ALIAS      3

/* Export module directory */

typedef struct _IMAGE_EXPORT_DIRECTORY {
	::u32	Characteristics;
	::u32	TimeDateStamp;
	::u16	MajorVersion;
	::u16	MinorVersion;
	::u32	Name;
	::u32	Base;
	::u32	NumberOfFunctions;
	::u32	NumberOfNames;
	::u32	AddressOfFunctions;
	::u32	AddressOfNames;
	::u32	AddressOfNameOrdinals;
} IMAGE_EXPORT_DIRECTORY,*PIMAGE_EXPORT_DIRECTORY;

/* Import name entry */
typedef struct _IMAGE_IMPORT_BY_NAME {
	::u16	Hint;
	byte	Name[1];
} IMAGE_IMPORT_BY_NAME,*PIMAGE_IMPORT_BY_NAME;

//#include "windows_pshpack8.h"
///* Import thunk */
//typedef struct _IMAGE_THUNK_DATA64 {
//   union {
//      ULONGLONG ForwarderString;
//      ULONGLONG Function;
//      ULONGLONG Ordinal;
//      ULONGLONG AddressOfData;
//   } u1;
//} IMAGE_THUNK_DATA64,*PIMAGE_THUNK_DATA64;
//#include "windows_poppack.h"

typedef struct _IMAGE_THUNK_DATA32 {
	union {
		::u32 ForwarderString;
		::u32 Function;
		::u32 Ordinal;
		::u32 AddressOfData;
	} u1;
} IMAGE_THUNK_DATA32,*PIMAGE_THUNK_DATA32;

/* Import module directory */

typedef struct _IMAGE_IMPORT_DESCRIPTOR {
	union {
		::u32	Characteristics; /* 0 for terminating null import descriptor  */
		::u32	OriginalFirstThunk;	/* RVA to original unbound IAT */
	} DUMMYUNIONNAME;
	::u32	TimeDateStamp;	/* 0 if not bound,
				 * -1 if bound, and real date\time stamp
				 *    in IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT
				 * (new BIND)
				 * otherwise date/time stamp of DLL bound to
				 * (Old BIND)
				 */
	::u32	ForwarderChain;	/* -1 if no forwarders */
	::u32	Name;
	/* RVA to IAT (if bound this IAT has actual addresses) */
	::u32	FirstThunk;
} IMAGE_IMPORT_DESCRIPTOR,*PIMAGE_IMPORT_DESCRIPTOR;

#define IMAGE_ORDINAL_FLAG64             (((ULONGLONG)0x80000000 << 32) | 0x00000000)
#define IMAGE_ORDINAL_FLAG32             0x80000000
#define IMAGE_SNAP_BY_ORDINAL64(ordinal) (((ordinal) & IMAGE_ORDINAL_FLAG64) != 0)
#define IMAGE_SNAP_BY_ORDINAL32(ordinal) (((ordinal) & IMAGE_ORDINAL_FLAG32) != 0)
#define IMAGE_ORDINAL64(ordinal)         ((ordinal) & 0xffff)
#define IMAGE_ORDINAL32(ordinal)         ((ordinal) & 0xffff)

#ifdef OS64BIT
#define IMAGE_ORDINAL_FLAG              IMAGE_ORDINAL_FLAG64
#define IMAGE_SNAP_BY_ORDINAL(Ordinal)  IMAGE_SNAP_BY_ORDINAL64(Ordinal)
#define IMAGE_ORDINAL(Ordinal)          IMAGE_ORDINAL64(Ordinal)
//typedef IMAGE_THUNK_DATA64              IMAGE_THUNK_DATA;
//typedef PIMAGE_THUNK_DATA64             PIMAGE_THUNK_DATA;
#else
#define IMAGE_ORDINAL_FLAG              IMAGE_ORDINAL_FLAG32
#define IMAGE_SNAP_BY_ORDINAL(Ordinal)  IMAGE_SNAP_BY_ORDINAL32(Ordinal)
#define IMAGE_ORDINAL(Ordinal)          IMAGE_ORDINAL32(Ordinal)
//typedef IMAGE_THUNK_DATA32              IMAGE_THUNK_DATA;
//typedef PIMAGE_THUNK_DATA32             PIMAGE_THUNK_DATA;
#endif

typedef struct _IMAGE_BOUND_IMPORT_DESCRIPTOR
{
    ::u32   TimeDateStamp;
    ::u16    OffsetModuleName;
    ::u16    NumberOfModuleForwarderRefs;
/* Array of zero or more IMAGE_BOUND_FORWARDER_REF follows */
} IMAGE_BOUND_IMPORT_DESCRIPTOR,  *PIMAGE_BOUND_IMPORT_DESCRIPTOR;

typedef struct _IMAGE_BOUND_FORWARDER_REF
{
    ::u32   TimeDateStamp;
    ::u16    OffsetModuleName;
    ::u16    Reserved;
} IMAGE_BOUND_FORWARDER_REF, *PIMAGE_BOUND_FORWARDER_REF;

typedef struct _IMAGE_BASE_RELOCATION
{
	::u32	VirtualAddress;
	::u32	SizeOfBlock;
	/* ::u16	TypeOffset[1]; */
} IMAGE_BASE_RELOCATION,*PIMAGE_BASE_RELOCATION;

//#include "windows_pshpack2.h"
//
//typedef struct _IMAGE_RELOCATION
//{
//    union {
//        ::u32   VirtualAddress;
//        ::u32   RelocCount;
//    } DUMMYUNIONNAME;
//    ::u32   SymbolTableIndex;
//    ::u16    Type;
//} IMAGE_RELOCATION, *PIMAGE_RELOCATION;
//
//#include "windows_poppack.h"

#define IMAGE_SIZEOF_RELOCATION 10

/* matter relocation types */
#define IMAGE_REL_BASED_ABSOLUTE 		0
#define IMAGE_REL_BASED_HIGH			1
#define IMAGE_REL_BASED_LOW			2
#define IMAGE_REL_BASED_HIGHLOW			3
#define IMAGE_REL_BASED_HIGHADJ			4
#define IMAGE_REL_BASED_MIPS_JMPADDR		5
#define IMAGE_REL_BASED_SECTION			6
#define	IMAGE_REL_BASED_REL			7
#define IMAGE_REL_BASED_MIPS_JMPADDR16		9
#define IMAGE_REL_BASED_IA64_IMM64		9 /* yes, 9 too */
#define IMAGE_REL_BASED_DIR64			10
#define IMAGE_REL_BASED_HIGH3ADJ		11

/* I386 relocation types */
#define	IMAGE_REL_I386_ABSOLUTE			0
#define	IMAGE_REL_I386_DIR16			1
#define	IMAGE_REL_I386_REL16			2
#define	IMAGE_REL_I386_DIR32			6
#define	IMAGE_REL_I386_DIR32NB			7
#define	IMAGE_REL_I386_SEG12			9
#define	IMAGE_REL_I386_SECTION			10
#define	IMAGE_REL_I386_SECREL			11
#define	IMAGE_REL_I386_TOKEN			12
#define	IMAGE_REL_I386_SECREL7			13
#define	IMAGE_REL_I386_REL32			20

/* MIPS relocation types */
#define IMAGE_REL_MIPS_ABSOLUTE		0x0000
#define IMAGE_REL_MIPS_REFHALF		0x0001
#define IMAGE_REL_MIPS_REFWORD		0x0002
#define IMAGE_REL_MIPS_JMPADDR		0x0003
#define IMAGE_REL_MIPS_REFHI		0x0004
#define IMAGE_REL_MIPS_REFLO		0x0005
#define IMAGE_REL_MIPS_GPREL		0x0006
#define IMAGE_REL_MIPS_LITERAL		0x0007
#define IMAGE_REL_MIPS_SECTION		0x000A
#define IMAGE_REL_MIPS_SECREL		0x000B
#define IMAGE_REL_MIPS_SECRELLO		0x000C
#define IMAGE_REL_MIPS_SECRELHI		0x000D
#define IMAGE_REL_MIPS_TOKEN		0x000E
#define IMAGE_REL_MIPS_JMPADDR16	0x0010
#define IMAGE_REL_MIPS_REFWORDNB	0x0022
#define IMAGE_REL_MIPS_PAIR		0x0025

/* ALPHA relocation types */
#define IMAGE_REL_ALPHA_ABSOLUTE	0x0000
#define IMAGE_REL_ALPHA_REFLONG		0x0001
#define IMAGE_REL_ALPHA_REFQUAD		0x0002
#define IMAGE_REL_ALPHA_GPREL		0x0003
#define IMAGE_REL_ALPHA_LITERAL		0x0004
#define IMAGE_REL_ALPHA_LITUSE		0x0005
#define IMAGE_REL_ALPHA_GPDISP		0x0006
#define IMAGE_REL_ALPHA_BRADDR		0x0007
#define IMAGE_REL_ALPHA_HINT		0x0008
#define IMAGE_REL_ALPHA_INLINE_REFLONG	0x0009
#define IMAGE_REL_ALPHA_REFHI		0x000A
#define IMAGE_REL_ALPHA_REFLO		0x000B
#define IMAGE_REL_ALPHA_PAIR		0x000C
#define IMAGE_REL_ALPHA_MATCH		0x000D
#define IMAGE_REL_ALPHA_SECTION		0x000E
#define IMAGE_REL_ALPHA_SECREL		0x000F
#define IMAGE_REL_ALPHA_REFLONGNB	0x0010
#define IMAGE_REL_ALPHA_SECRELLO	0x0011
#define IMAGE_REL_ALPHA_SECRELHI	0x0012
#define IMAGE_REL_ALPHA_REFQ3		0x0013
#define IMAGE_REL_ALPHA_REFQ2		0x0014
#define IMAGE_REL_ALPHA_REFQ1		0x0015
#define IMAGE_REL_ALPHA_GPRELLO		0x0016
#define IMAGE_REL_ALPHA_GPRELHI		0x0017

/* PowerPC relocation types */
#define IMAGE_REL_PPC_ABSOLUTE          0x0000
#define IMAGE_REL_PPC_ADDR64            0x0001
#define IMAGE_REL_PPC_ADDR            0x0002
#define IMAGE_REL_PPC_ADDR24            0x0003
#define IMAGE_REL_PPC_ADDR16            0x0004
#define IMAGE_REL_PPC_ADDR14            0x0005
#define IMAGE_REL_PPC_REL24             0x0006
#define IMAGE_REL_PPC_REL14             0x0007
#define IMAGE_REL_PPC_TOCREL16          0x0008
#define IMAGE_REL_PPC_TOCREL14          0x0009
#define IMAGE_REL_PPC_ADDR32NB          0x000A
#define IMAGE_REL_PPC_SECREL            0x000B
#define IMAGE_REL_PPC_SECTION           0x000C
#define IMAGE_REL_PPC_IFGLUE            0x000D
#define IMAGE_REL_PPC_IMGLUE            0x000E
#define IMAGE_REL_PPC_SECREL16          0x000F
#define IMAGE_REL_PPC_REFHI             0x0010
#define IMAGE_REL_PPC_REFLO             0x0011
#define IMAGE_REL_PPC_PAIR              0x0012
#define IMAGE_REL_PPC_SECRELLO          0x0013
#define IMAGE_REL_PPC_SECRELHI          0x0014
#define IMAGE_REL_PPC_GPREL		0x0015
#define IMAGE_REL_PPC_TOKEN             0x0016
#define IMAGE_REL_PPC_TYPEMASK          0x00FF
/* modifier bits */
#define IMAGE_REL_PPC_NEG               0x0100
#define IMAGE_REL_PPC_BRTAKEN           0x0200
#define IMAGE_REL_PPC_BRNTAKEN          0x0400
#define IMAGE_REL_PPC_TOCDEFN           0x0800

/* SH3 ? relocation type */
#define IMAGE_REL_SH3_ABSOLUTE          0x0000
#define IMAGE_REL_SH3_DIRECT16          0x0001
#define IMAGE_REL_SH3_DIRECT          0x0002
#define IMAGE_REL_SH3_DIRECT8           0x0003
#define IMAGE_REL_SH3_DIRECT8_WORD      0x0004
#define IMAGE_REL_SH3_DIRECT8_LONG      0x0005
#define IMAGE_REL_SH3_DIRECT4           0x0006
#define IMAGE_REL_SH3_DIRECT4_WORD      0x0007
#define IMAGE_REL_SH3_DIRECT4_LONG      0x0008
#define IMAGE_REL_SH3_PCREL8_WORD       0x0009
#define IMAGE_REL_SH3_PCREL8_LONG       0x000A
#define IMAGE_REL_SH3_PCREL12_WORD      0x000B
#define IMAGE_REL_SH3_STARTOF_SECTION   0x000C
#define IMAGE_REL_SH3_SIZEOF_SECTION    0x000D
#define IMAGE_REL_SH3_SECTION           0x000E
#define IMAGE_REL_SH3_SECREL            0x000F
#define IMAGE_REL_SH3_DIRECT32_NB       0x0010
#define IMAGE_REL_SH3_GPREL4_LONG       0x0011
#define IMAGE_REL_SH3_TOKEN             0x0012

/* ARM (Archimedes?) relocation types */
#define IMAGE_REL_ARM_ABSOLUTE		0x0000
#define IMAGE_REL_ARM_ADDR		0x0001
#define IMAGE_REL_ARM_ADDR32NB		0x0002
#define IMAGE_REL_ARM_BRANCH24		0x0003
#define IMAGE_REL_ARM_BRANCH11		0x0004
#define IMAGE_REL_ARM_TOKEN		0x0005
#define IMAGE_REL_ARM_GPREL12		0x0006
#define IMAGE_REL_ARM_GPREL7		0x0007
#define IMAGE_REL_ARM_BLX24		0x0008
#define IMAGE_REL_ARM_BLX11		0x0009
#define IMAGE_REL_ARM_SECTION		0x000E
#define IMAGE_REL_ARM_SECREL		0x000F

/* IA64 relocation types */
#define IMAGE_REL_IA64_ABSOLUTE		0x0000
#define IMAGE_REL_IA64_IMM14		0x0001
#define IMAGE_REL_IA64_IMM22		0x0002
#define IMAGE_REL_IA64_IMM64		0x0003
#define IMAGE_REL_IA64_DIR		0x0004
#define IMAGE_REL_IA64_DIR64		0x0005
#define IMAGE_REL_IA64_PCREL21B		0x0006
#define IMAGE_REL_IA64_PCREL21M		0x0007
#define IMAGE_REL_IA64_PCREL21F		0x0008
#define IMAGE_REL_IA64_GPREL22		0x0009
#define IMAGE_REL_IA64_LTOFF22		0x000A
#define IMAGE_REL_IA64_SECTION		0x000B
#define IMAGE_REL_IA64_SECREL22		0x000C
#define IMAGE_REL_IA64_SECREL64I	0x000D
#define IMAGE_REL_IA64_SECREL		0x000E
#define IMAGE_REL_IA64_LTOFF64		0x000F
#define IMAGE_REL_IA64_DIR32NB		0x0010
#define IMAGE_REL_IA64_SREL14		0x0011
#define IMAGE_REL_IA64_SREL22		0x0012
#define IMAGE_REL_IA64_SREL32		0x0013
#define IMAGE_REL_IA64_UREL32		0x0014
#define IMAGE_REL_IA64_PCREL60X	0x0015
#define IMAGE_REL_IA64_PCREL60B	0x0016
#define IMAGE_REL_IA64_PCREL60F	0x0017
#define IMAGE_REL_IA64_PCREL60I	0x0018
#define IMAGE_REL_IA64_PCREL60M	0x0019
#define IMAGE_REL_IA64_IMMGPREL64	0x001A
#define IMAGE_REL_IA64_TOKEN		0x001B
#define IMAGE_REL_IA64_GPREL32		0x001C
#define IMAGE_REL_IA64_ADDEND		0x001F

/* AMD64 relocation types */
#define IMAGE_REL_AMD64_ABSOLUTE        0x0000
#define IMAGE_REL_AMD64_ADDR64          0x0001
#define IMAGE_REL_AMD64_ADDR32          0x0002
#define IMAGE_REL_AMD64_ADDR32NB        0x0003
#define IMAGE_REL_AMD64_REL32           0x0004
#define IMAGE_REL_AMD64_REL32_1         0x0005
#define IMAGE_REL_AMD64_REL32_2         0x0006
#define IMAGE_REL_AMD64_REL32_3         0x0007
#define IMAGE_REL_AMD64_REL32_4         0x0008
#define IMAGE_REL_AMD64_REL32_5         0x0009
#define IMAGE_REL_AMD64_SECTION         0x000A
#define IMAGE_REL_AMD64_SECREL          0x000B
#define IMAGE_REL_AMD64_SECREL7         0x000C
#define IMAGE_REL_AMD64_TOKEN           0x000D
#define IMAGE_REL_AMD64_SREL32          0x000E
#define IMAGE_REL_AMD64_PAIR            0x000F
#define IMAGE_REL_AMD64_SSPAN32         0x0010

/* archive format */

#define IMAGE_ARCHIVE_START_SIZE             8
#define IMAGE_ARCHIVE_START                  "!<arch>\n"
#define IMAGE_ARCHIVE_END                    "`\n"
#define IMAGE_ARCHIVE_PAD                    "\n"
#define IMAGE_ARCHIVE_LINKER_MEMBER          "/               "
#define IMAGE_ARCHIVE_LONGNAMES_MEMBER       "//              "

typedef struct _IMAGE_ARCHIVE_MEMBER_HEADER
{
    byte     Name[16];
    byte     Date[12];
    byte     UserID[6];
    byte     GroupID[6];
    byte     Mode[8];
    byte     Size[10];
    byte     EndHeader[2];
} IMAGE_ARCHIVE_MEMBER_HEADER, *PIMAGE_ARCHIVE_MEMBER_HEADER;

#define IMAGE_SIZEOF_ARCHIVE_MEMBER_HDR 60

typedef struct _IMPORT_OBJECT_HEADER
{
    ::u16     Sig1;
    ::u16     Sig2;
    ::u16     Version;
    ::u16     Machine;
    ::u32    TimeDateStamp;
    ::u32    SizeOfData;
    union
    {
        ::u16 Ordinal;
        ::u16 Hint;
    } DUMMYUNIONNAME;
    ::u16     Type : 2;
    ::u16     NameType : 3;
    ::u16     Reserved : 11;
} IMPORT_OBJECT_HEADER;

#define IMPORT_OBJECT_HDR_SIG2  0xffff

typedef enum IMPORT_OBJECT_TYPE
{
    IMPORT_OBJECT_CODE = 0,
    IMPORT_OBJECT_DATA = 1,
    IMPORT_OBJECT_CONST = 2
} IMPORT_OBJECT_TYPE;

typedef enum IMPORT_OBJECT_NAME_TYPE
{
    IMPORT_OBJECT_ORDINAL = 0,
    IMPORT_OBJECT_NAME = 1,
    IMPORT_OBJECT_NAME_NO_PREFIX = 2,
    IMPORT_OBJECT_NAME_UNDECORATE = 3
} IMPORT_OBJECT_NAME_TYPE;

typedef struct _ANON_OBJECT_HEADER
{
    ::u16     Sig1;
    ::u16     Sig2;
    ::u16     Version;
    ::u16     Machine;
    ::u32    TimeDateStamp;
    CLSID    ClassID;
    ::u32    SizeOfData;
} ANON_OBJECT_HEADER;

/*
 * Resource directory stuff
 */
typedef struct _IMAGE_RESOURCE_DIRECTORY {
	::u32	Characteristics;
	::u32	TimeDateStamp;
	::u16	MajorVersion;
	::u16	MinorVersion;
	::u16	NumberOfNamedEntries;
	::u16	NumberOfIdEntries;
	/*  IMAGE_RESOURCE_DIRECTORY_ENTRY DirectoryEntries[]; */
} IMAGE_RESOURCE_DIRECTORY,*PIMAGE_RESOURCE_DIRECTORY;

#define	IMAGE_RESOURCE_NAME_IS_STRING		0x80000000
#define	IMAGE_RESOURCE_DATA_IS_DIRECTORY	0x80000000

typedef struct _IMAGE_RESOURCE_DIRECTORY_ENTRY {
	union {
		struct {
#ifdef BITFIELDS_BIGENDIAN
			unsigned NameIsString:1;
			unsigned NameOffset:31;
#else
			unsigned NameOffset:31;
			unsigned NameIsString:1;
#endif
		} DUMMYSTRUCTNAME1;
		::u32   Name;
                struct {
#ifdef WORDS_BIGENDIAN
			::u16    __pad;
			::u16    Id;
#else
			::u16    Id;
			::u16    __pad;
#endif
		} DUMMYSTRUCTNAME2;
	} DUMMYUNIONNAME1;
	union {
		::u32   OffsetToData;
		struct {
#ifdef BITFIELDS_BIGENDIAN
			unsigned DataIsDirectory:1;
			unsigned OffsetToDirectory:31;
#else
			unsigned OffsetToDirectory:31;
			unsigned DataIsDirectory:1;
#endif
		} DUMMYSTRUCTNAME3;
	} DUMMYUNIONNAME2;
} IMAGE_RESOURCE_DIRECTORY_ENTRY,*PIMAGE_RESOURCE_DIRECTORY_ENTRY;


typedef struct _IMAGE_RESOURCE_DIRECTORY_STRING {
	::u16	Length;
	char	NameString[ 1 ];
} IMAGE_RESOURCE_DIRECTORY_STRING,*PIMAGE_RESOURCE_DIRECTORY_STRING;

typedef struct _IMAGE_RESOURCE_DIR_STRING_U {
	::u16	Length;
	WCHAR	NameString[ 1 ];
} IMAGE_RESOURCE_DIR_STRING_U,*PIMAGE_RESOURCE_DIR_STRING_U;

typedef struct _IMAGE_RESOURCE_DATA_ENTRY {
	::u32	OffsetToData;
	::u32	Size;
	::u32	CodePage;
	::u32	Reserved;
} IMAGE_RESOURCE_DATA_ENTRY,*PIMAGE_RESOURCE_DATA_ENTRY;


typedef VOID (CALLBACK *PIMAGE_TLS_CALLBACK)(
	LPVOID DllHandle,::u32 Reason,LPVOID Reserved
);

typedef struct _IMAGE_TLS_DIRECTORY64 {
    ULONGLONG   StartAddressOfRawData;
    ULONGLONG   EndAddressOfRawData;
    ULONGLONG   AddressOfIndex;
    ULONGLONG   AddressOfCallBacks;
    ::u32       SizeOfZeroFill;
    ::u32       Characteristics;
} IMAGE_TLS_DIRECTORY64, *PIMAGE_TLS_DIRECTORY64;

typedef struct _IMAGE_TLS_DIRECTORY32 {
    ::u32   StartAddressOfRawData;
    ::u32   EndAddressOfRawData;
    ::u32   AddressOfIndex;
    ::u32   AddressOfCallBacks;
    ::u32   SizeOfZeroFill;
    ::u32   Characteristics;
} IMAGE_TLS_DIRECTORY32, *PIMAGE_TLS_DIRECTORY32;

#ifdef OS64BIT
typedef IMAGE_TLS_DIRECTORY64           IMAGE_TLS_DIRECTORY;
typedef PIMAGE_TLS_DIRECTORY64          PIMAGE_TLS_DIRECTORY;
#else
typedef IMAGE_TLS_DIRECTORY32           IMAGE_TLS_DIRECTORY;
typedef PIMAGE_TLS_DIRECTORY32          PIMAGE_TLS_DIRECTORY;
#endif

typedef struct _IMAGE_DEBUG_DIRECTORY {
  ::u32 Characteristics;
  ::u32 TimeDateStamp;
  ::u16  MajorVersion;
  ::u16  MinorVersion;
  ::u32 Type;
  ::u32 SizeOfData;
  ::u32 AddressOfRawData;
  ::u32 PointerToRawData;
} IMAGE_DEBUG_DIRECTORY, *PIMAGE_DEBUG_DIRECTORY;

#define IMAGE_DEBUG_TYPE_UNKNOWN        0
#define IMAGE_DEBUG_TYPE_COFF           1
#define IMAGE_DEBUG_TYPE_CODEVIEW       2
#define IMAGE_DEBUG_TYPE_FPO            3
#define IMAGE_DEBUG_TYPE_MISC           4
#define IMAGE_DEBUG_TYPE_EXCEPTION      5
#define IMAGE_DEBUG_TYPE_FIXUP          6
#define IMAGE_DEBUG_TYPE_OMAP_TO_SRC    7
#define IMAGE_DEBUG_TYPE_OMAP_FROM_SRC  8
#define IMAGE_DEBUG_TYPE_BORLAND        9
#define IMAGE_DEBUG_TYPE_RESERVED10    10

typedef enum ReplacesCorHdrNumericDefines
{
    COMIMAGE_FLAGS_ILONLY           = 0x00000001,
    COMIMAGE_FLAGS_32BITREQUIRED    = 0x00000002,
    COMIMAGE_FLAGS_IL_LIBRARY       = 0x00000004,
    COMIMAGE_FLAGS_STRONGNAMESIGNED = 0x00000008,
    COMIMAGE_FLAGS_TRACKDEBUGDATA   = 0x00010000,

    COR_VERSION_MAJOR_V2       = 2,
    COR_VERSION_MAJOR          = COR_VERSION_MAJOR_V2,
    COR_VERSION_MINOR          = 0,
    COR_DELETED_NAME_LENGTH    = 8,
    COR_VTABLEGAP_NAME_LENGTH  = 8,

    NATIVE_TYPE_MAX_CB = 1,
    COR_ILMETHOD_SECT_SMALL_MAX_DATASIZE = 0xff,

    IMAGE_COR_MIH_METHODRVA  = 0x01,
    IMAGE_COR_MIH_EHRVA      = 0x02,
    IMAGE_COR_MIH_BASICBLOCK = 0x08,

    COR_VTABLE_32BIT             = 0x01,
    COR_VTABLE_64BIT             = 0x02,
    COR_VTABLE_FROM_UNMANAGED    = 0x04,
    COR_VTABLE_CALL_MOST_DERIVED = 0x10,

    IMAGE_COR_EATJ_THUNK_SIZE = 32,

    MAX_CLASS_NAME   = 1024,
    MAX_PACKAGE_NAME = 1024,
} ReplacesCorHdrNumericDefines;

typedef struct IMAGE_COR20_HEADER
{
    ::u32 cb;
    ::u16  MajorRuntimeVersion;
    ::u16  MinorRuntimeVersion;

    IMAGE_DATA_DIRECTORY MetaData;
    ::u32 Flags;
    ::u32 EntryPointToken;

    IMAGE_DATA_DIRECTORY Resources;
    IMAGE_DATA_DIRECTORY StrongNameSignature;
    IMAGE_DATA_DIRECTORY CodeManagerTable;
    IMAGE_DATA_DIRECTORY VTableFixups;
    IMAGE_DATA_DIRECTORY ExportAddressTableJumps;
    IMAGE_DATA_DIRECTORY ManagedNativeHeader;

} IMAGE_COR20_HEADER, *PIMAGE_COR20_HEADER;

typedef struct _IMAGE_COFF_SYMBOLS_HEADER {
  ::u32 NumberOfSymbols;
  ::u32 LvaToFirstSymbol;
  ::u32 NumberOfLinenumbers;
  ::u32 LvaToFirstLinenumber;
  ::u32 RvaToFirstByteOfCode;
  ::u32 RvaToLastByteOfCode;
  ::u32 RvaToFirstByteOfData;
  ::u32 RvaToLastByteOfData;
} IMAGE_COFF_SYMBOLS_HEADER, *PIMAGE_COFF_SYMBOLS_HEADER;

#define FRAME_FPO       0
#define FRAME_TRAP      1
#define FRAME_TSS       2
#define FRAME_NONFPO    3

typedef struct _FPO_DATA {
  ::u32 ulOffStart;
  ::u32 cbProcSize;
  ::u32 cdwLocals;
  ::u16  cdwParams;
  ::u16  cbProlog : 8;
  ::u16  cbRegs   : 3;
  ::u16  fHasSEH  : 1;
  ::u16  fUseBP   : 1;
  ::u16  reserved : 1;
  ::u16  cbFrame  : 2;
} FPO_DATA, *PFPO_DATA;

typedef struct _IMAGE_LOAD_CONFIG_DIRECTORY {
  ::u32 Size;
  ::u32 TimeDateStamp;
  ::u16  MajorVersion;
  ::u16  MinorVersion;
  ::u32 GlobalFlagsClear;
  ::u32 GlobalFlagsSet;
  ::u32 CriticalSectionDefaultTimeout;
  ::u32 DeCommitFreeBlockThreshold;
  ::u32 DeCommitTotalFreeThreshold;
  PVOID LockPrefixTable;
  ::u32 MaximumAllocationSize;
  ::u32 VirtualMemoryThreshold;
  ::u32 ProcessHeapFlags;
  ::u32 ProcessAffinityMask;
  ::u16  CSDVersion;
  ::u16  Reserved1;
  PVOID EditList;
  ::u32 SecurityCookie;
  ::u32 SEHandlerTable;
  ::u32 SEHandlerCount;
} IMAGE_LOAD_CONFIG_DIRECTORY, *PIMAGE_LOAD_CONFIG_DIRECTORY;

typedef struct _IMAGE_FUNCTION_ENTRY {
  ::u32 StartingAddress;
  ::u32 EndingAddress;
  ::u32 EndOfPrologue;
} IMAGE_FUNCTION_ENTRY, *PIMAGE_FUNCTION_ENTRY;

#define IMAGE_DEBUG_MISC_EXENAME    1

typedef struct _IMAGE_DEBUG_MISC {
    ::u32       DataType;
    ::u32       Length;
    byte        Unicode;
    byte        Reserved[ 3 ];
    byte        Data[ 1 ];
} IMAGE_DEBUG_MISC, *PIMAGE_DEBUG_MISC;

/* This is the structure that appears at the very start of a .DBG file. */

typedef struct _IMAGE_SEPARATE_DEBUG_HEADER {
	::u16	Signature;
	::u16	Flags;
	::u16	Machine;
	::u16	Characteristics;
	::u32	TimeDateStamp;
	::u32	CheckSum;
	::u32	ImageBase;
	::u32	SizeOfImage;
	::u32	NumberOfSections;
	::u32	ExportedNamesSize;
	::u32	DebugDirectorySize;
	::u32	SectionAlignment;
	::u32	Reserved[ 2 ];
} IMAGE_SEPARATE_DEBUG_HEADER,*PIMAGE_SEPARATE_DEBUG_HEADER;

#define IMAGE_SEPARATE_DEBUG_SIGNATURE 0x4944


typedef struct tagMESSAGE_RESOURCE_ENTRY {
	::u16	Length;
	::u16	Flags;
	byte	Text[1];
} MESSAGE_RESOURCE_ENTRY,*PMESSAGE_RESOURCE_ENTRY;
#define	MESSAGE_RESOURCE_UNICODE	0x0001

typedef struct tagMESSAGE_RESOURCE_BLOCK {
	::u32	LowId;
	::u32	HighId;
	::u32	OffsetToEntries;
} MESSAGE_RESOURCE_BLOCK,*PMESSAGE_RESOURCE_BLOCK;

typedef struct tagMESSAGE_RESOURCE_DATA {
	::u32			NumberOfBlocks;
	MESSAGE_RESOURCE_BLOCK	Blocks[ 1 ];
} MESSAGE_RESOURCE_DATA,*PMESSAGE_RESOURCE_DATA;

/*
 * Here follows typedefs for security and tokens.
 */

/*
 * First a constant for the following typedefs.
 */

#define ANYSIZE_ARRAY   1

/* FIXME:  Orphan.  What does it point to? */
typedef PVOID PACCESS_TOKEN;
typedef PVOID PSECURITY_DESCRIPTOR;
typedef PVOID PSID;

typedef enum _TOKEN_ELEVATION_TYPE {
  TokenElevationTypeDefault = 1,
  TokenElevationTypeFull,
  TokenElevationTypeLimited
} TOKEN_ELEVATION_TYPE, *PTOKEN_ELEVATION_TYPE;

/*
 * TOKEN_INFORMATION_CLASS
 */

typedef enum _TOKEN_INFORMATION_CLASS {
  TokenUser = 1,
  TokenGroups,
  TokenPrivileges,
  TokenOwner,
  TokenPrimaryGroup,
  TokenDefaultDacl,
  TokenSource,
  TokenType,
  TokenImpersonationLevel,
  TokenStatistics,
  TokenRestrictedSids,
  TokenSessionId,
  TokenGroupsAndPrivileges,
  TokenSessionReference,
  TokenSandBoxInert,
  TokenAuditPolicy,
  TokenOrigin,
  TokenElevationType,
  TokenLinkedToken,
  TokenElevation,
  TokenHasRestrictions,
  TokenAccessInformation,
  TokenVirtualizationAllowed,
  TokenVirtualizationEnabled,
  TokenIntegrityLevel,
  TokenUIAccess,
  TokenMandatoryPolicy,
  TokenLogonSid,
  MaxTokenInfoClass
} TOKEN_INFORMATION_CLASS;

#define TOKEN_TOKEN_ADJUST_DEFAULT   0x0080
#define TOKEN_ADJUST_GROUPS          0x0040
#define TOKEN_ADJUST_PRIVILEGES      0x0020
#define TOKEN_ADJUST_SESSIONID       0x0100
#define TOKEN_ASSIGN_PRIMARY         0x0001
#define TOKEN_DUPLICATE              0x0002
#define TOKEN_EXECUTE                STANDARD_RIGHTS_EXECUTE
#define TOKEN_IMPERSONATE            0x0004
#define TOKEN_QUERY                  0x0008
#define TOKEN_QUERY_SOURCE           0x0010
#define TOKEN_ADJUST_DEFAULT         0x0080
#define TOKEN_READ                   (STANDARD_RIGHTS_READ|TOKEN_QUERY)
#define TOKEN_WRITE                  (STANDARD_RIGHTS_WRITE     | \
					TOKEN_ADJUST_PRIVILEGES | \
					TOKEN_ADJUST_GROUPS | \
					TOKEN_ADJUST_DEFAULT )
#define TOKEN_ALL_ACCESS             (STANDARD_RIGHTS_REQUIRED | \
					TOKEN_ASSIGN_PRIMARY | \
					TOKEN_DUPLICATE | \
					TOKEN_IMPERSONATE | \
					TOKEN_QUERY | \
					TOKEN_QUERY_SOURCE | \
					TOKEN_ADJUST_PRIVILEGES | \
					TOKEN_ADJUST_GROUPS | \
					TOKEN_ADJUST_SESSIONID | \
					TOKEN_ADJUST_DEFAULT )

#ifndef _SECURITY_DEFINED
#define _SECURITY_DEFINED


typedef ::u32 ACCESS_MASK, *PACCESS_MASK;

typedef struct _GENERIC_MAPPING {
    ACCESS_MASK GenericRead;
    ACCESS_MASK GenericWrite;
    ACCESS_MASK GenericExecute;
    ACCESS_MASK Genericall;
} GENERIC_MAPPING, *PGENERIC_MAPPING;

#ifndef SID_IDENTIFIER_AUTHORITY_DEFINED
#define SID_IDENTIFIER_AUTHORITY_DEFINED
typedef struct {
    byte Value[6];
} SID_IDENTIFIER_AUTHORITY, *PSID_IDENTIFIER_AUTHORITY;
#endif /* !defined(SID_IDENTIFIER_AUTHORITY_DEFINED) */

#ifndef SID_DEFINED
#define SID_DEFINED
typedef struct _SID {
    byte Revision;
    byte SubAuthorityCount;
    SID_IDENTIFIER_AUTHORITY IdentifierAuthority;
    ::u32 SubAuthority[1];
} SID,*PISID;
#endif /* !defined(SID_DEFINED) */

#define	SID_REVISION			(1)	/* Current revision */
#define	SID_MAX_SUB_AUTHORITIES		(15)	/* current maximum subauths */
#define	SID_RECOMMENDED_SUB_AUTHORITIES	(1)	/* recommended subauths */

#define SECURITY_MAX_SID_SIZE (sizeof(SID) - sizeof(::u32) + (SID_MAX_SUB_AUTHORITIES * sizeof(::u32)))

/*
 * ACL
 */

#define ACL_REVISION1 1
#define ACL_REVISION2 2
#define ACL_REVISION3 3
#define ACL_REVISION4 4

#define MIN_ACL_REVISION ACL_REVISION2
#define MAX_ACL_REVISION ACL_REVISION4

#define ACL_REVISION 2

typedef struct _ACL {
    byte AclRevision;
    byte Sbz1;
    ::u16 AclSize;
    ::u16 AceCount;
    ::u16 Sbz2;
} ACL, *PACL;

typedef enum _ACL_INFORMATION_CLASS
{
  AclRevisionInformation = 1,
  AclSizeInformation
} ACL_INFORMATION_CLASS;

typedef struct _ACL_REVISION_INFORMATION
{
    ::u32 AclRevision;
} ACL_REVISION_INFORMATION, *PACL_REVISION_INFORMATION;

typedef struct _ACL_SIZE_INFORMATION
{
    ::u32 AceCount;
    ::u32 AclBytesInUse;
    ::u32 AclBytesFree;
} ACL_SIZE_INFORMATION, *PACL_SIZE_INFORMATION;

/* SECURITY_DESCRIPTOR */
#define	SECURITY_DESCRIPTOR_REVISION	1
#define	SECURITY_DESCRIPTOR_REVISION1	1


/*
 * Privilege Names
 */
#define SE_CREATE_TOKEN_NAME		TEXT("SeCreateTokenPrivilege")
#define SE_ASSIGNPRIMARYTOKEN_NAME	TEXT("SeAssignPrimaryTokenPrivilege")
#define SE_LOCK_MEMORY_NAME		TEXT("SeLockMemoryPrivilege")
#define SE_INCREASE_QUOTA_NAME		TEXT("SeIncreaseQuotaPrivilege")
#define SE_UNSOLICITED_INPUT_NAME	TEXT("SeUnsolicitedInputPrivilege")
#define SE_MACHINE_ACCOUNT_NAME 	TEXT("SeMachineAccountPrivilege")
#define SE_TCB_NAME			TEXT("SeTcbPrivilege")
#define SE_SECURITY_NAME		TEXT("SeSecurityPrivilege")
#define SE_TAKE_OWNERSHIP_NAME		TEXT("SeTakeOwnershipPrivilege")
#define SE_LOAD_DRIVER_NAME		TEXT("SeLoadDriverPrivilege")
#define SE_SYSTEM_PROFILE_NAME		TEXT("SeSystemProfilePrivilege")
#define SE_SYSTEMTIME_NAME		TEXT("SeSystemtimePrivilege")
#define SE_PROF_SINGLE_PROCESS_NAME	TEXT("SeProfileSingleProcessPrivilege")
#define SE_INC_BASE_PRIORITY_NAME	TEXT("SeIncreaseBasePriorityPrivilege")
#define SE_CREATE_PAGEFILE_NAME 	TEXT("SeCreatePagefilePrivilege")
#define SE_CREATE_PERMANENT_NAME	TEXT("SeCreatePermanentPrivilege")
#define SE_BACKUP_NAME 			TEXT("SeBackupPrivilege")
#define SE_RESTORE_NAME			TEXT("SeRestorePrivilege")
#define SE_SHUTDOWN_NAME		TEXT("SeShutdownPrivilege")
#define SE_DEBUG_NAME			TEXT("SeDebugPrivilege")
#define SE_AUDIT_NAME			TEXT("SeAuditPrivilege")
#define SE_SYSTEM_ENVIRONMENT_NAME	TEXT("SeSystemEnvironmentPrivilege")
#define SE_CHANGE_NOTIFY_NAME		TEXT("SeChangeNotifyPrivilege")
#define SE_REMOTE_SHUTDOWN_NAME		TEXT("SeRemoteShutdownPrivilege")
#define SE_UNDOCK_NAME                  TEXT("SeUndockPrivilege")
#define SE_ENABLE_DELEGATION_NAME       TEXT("SeEnableDelegationPrivilege")
#define SE_MANAGE_VOLUME_NAME           TEXT("SeManageVolumePrivilege")
#define SE_IMPERSONATE_NAME             TEXT("SeImpersonatePrivilege")
#define SE_CREATE_GLOBAL_NAME           TEXT("SeCreateGlobalPrivilege")

#define SE_GROUP_MANDATORY 		0x00000001
#define SE_GROUP_ENABLED_BY_DEFAULT 	0x00000002
#define SE_GROUP_ENABLED 		0x00000004
#define SE_GROUP_OWNER 			0x00000008
#define SE_GROUP_USE_FOR_DENY_ONLY 	0x00000010
#define SE_GROUP_LOGON_ID 		0xC0000000
#define SE_GROUP_RESOURCE 		0x20000000

#define SE_PRIVILEGE_ENABLED_BY_DEFAULT 0x00000001
#define SE_PRIVILEGE_ENABLED 		0x00000002
#define SE_PRIVILEGE_REMOVE		0x00000004
#define SE_PRIVILEGE_USED_FOR_ACCESS 	0x80000000

#define PRIVILEGE_SET_ALL_NECESSARY     1

#define SE_OWNER_DEFAULTED		0x00000001
#define SE_GROUP_DEFAULTED		0x00000002
#define SE_DACL_PRESENT			0x00000004
#define SE_DACL_DEFAULTED		0x00000008
#define SE_SACL_PRESENT			0x00000010
#define SE_SACL_DEFAULTED		0x00000020
#define SE_DACL_AUTO_INHERIT_REQ	0x00000100
#define SE_SACL_AUTO_INHERIT_REQ	0x00000200
#define SE_DACL_AUTO_INHERITED		0x00000400
#define SE_SACL_AUTO_INHERITED		0x00000800
#define SE_DACL_PROTECTED 		0x00001000
#define SE_SACL_PROTECTED 		0x00002000
#define SE_RM_CONTROL_VALID		0x00004000
#define SE_SELF_RELATIVE		0x00008000

typedef ::u32 SECURITY_INFORMATION, *PSECURITY_INFORMATION;
typedef ::u16 SECURITY_DESCRIPTOR_CONTROL, *PSECURITY_DESCRIPTOR_CONTROL;

/* The security descriptor structure */
typedef struct {
    byte Revision;
    byte Sbz1;
    SECURITY_DESCRIPTOR_CONTROL Control;
    ::u32 Owner;
    ::u32 Group;
    ::u32 Sacl;
    ::u32 Dacl;
} SECURITY_DESCRIPTOR_RELATIVE, *PISECURITY_DESCRIPTOR_RELATIVE;

typedef struct {
    byte Revision;
    byte Sbz1;
    SECURITY_DESCRIPTOR_CONTROL Control;
    PSID Owner;
    PSID Group;
    PACL Sacl;
    PACL Dacl;
} SECURITY_DESCRIPTOR, *PISECURITY_DESCRIPTOR;

#define SECURITY_DESCRIPTOR_MIN_LENGTH   (sizeof(SECURITY_DESCRIPTOR))

#endif /* _SECURITY_DEFINED */

/*
 * SID_AND_ATTRIBUTES
 */

typedef struct _SID_AND_ATTRIBUTES {
  PSID  Sid;
  ::u32 Attributes;
} SID_AND_ATTRIBUTES, *PSID_AND_ATTRIBUTES;

/* security entities */
#define SECURITY_NULL_RID			(0x00000000L)
#define SECURITY_WORLD_RID			(0x00000000L)
#define SECURITY_LOCAL_RID			(0X00000000L)

#define SECURITY_NULL_SID_AUTHORITY		{0,0,0,0,0,0}

/* S-1-1 */
#define SECURITY_WORLD_SID_AUTHORITY		{0,0,0,0,0,1}

/* S-1-2 */
#define SECURITY_LOCAL_SID_AUTHORITY		{0,0,0,0,0,2}

/* S-1-3 */
#define SECURITY_CREATOR_SID_AUTHORITY		{0,0,0,0,0,3}
#define SECURITY_CREATOR_OWNER_RID		(0x00000000L)
#define SECURITY_CREATOR_GROUP_RID		(0x00000001L)
#define SECURITY_CREATOR_OWNER_SERVER_RID	(0x00000002L)
#define SECURITY_CREATOR_GROUP_SERVER_RID	(0x00000003L)

/* S-1-4 */
#define SECURITY_NON_UNIQUE_AUTHORITY		{0,0,0,0,0,4}

/* S-1-5 */
#define SECURITY_NT_AUTHORITY			{0,0,0,0,0,5}
#define SECURITY_DIALUP_RID                     0x00000001L
#define SECURITY_NETWORK_RID                    0x00000002L
#define SECURITY_BATCH_RID                      0x00000003L
#define SECURITY_INTERACTIVE_RID                0x00000004L
#define SECURITY_LOGON_IDS_RID                  0x00000005L
#define SECURITY_SERVICE_RID                    0x00000006L
#define SECURITY_ANONYMOUS_LOGON_RID            0x00000007L
#define SECURITY_PROXY_RID                      0x00000008L
#define SECURITY_ENTERPRISE_CONTROLLERS_RID     0x00000009L
#define SECURITY_SERVER_LOGON_RID               SECURITY_ENTERPRISE_CONTROLLERS_RID
#define SECURITY_PRINCIPAL_SELF_RID             0x0000000AL
#define SECURITY_AUTHENTICATED_USER_RID         0x0000000BL
#define SECURITY_RESTRICTED_CODE_RID            0x0000000CL
#define SECURITY_TERMINAL_SERVER_RID            0x0000000DL
#define SECURITY_REMOTE_LOGON_RID               0x0000000EL
#define SECURITY_THIS_ORGANIZATION_RID          0x0000000FL
#define SECURITY_LOCAL_SYSTEM_RID               0x00000012L
#define SECURITY_LOCAL_SERVICE_RID              0x00000013L
#define SECURITY_NETWORK_SERVICE_RID            0x00000014L
#define SECURITY_NT_NON_UNIQUE                  0x00000015L
#define SECURITY_BUILTIN_DOMAIN_RID             0x00000020L

#define SECURITY_PACKAGE_BASE_RID               0x00000040L
#define SECURITY_PACKAGE_NTLM_RID               0x0000000AL
#define SECURITY_PACKAGE_SCHANNEL_RID           0x0000000EL
#define SECURITY_PACKAGE_DIGEST_RID             0x00000015L
#define SECURITY_MAX_ALWAYS_FILTERED            0x000003E7L
#define SECURITY_MIN_NEVER_FILTERED             0x000003E8L
#define SECURITY_OTHER_ORGANIZATION_RID         0x000003E8L

#define FOREST_USER_RID_MAX                     0x000001F3L
#define DOMAIN_USER_RID_ADMIN                   0x000001F4L
#define DOMAIN_USER_RID_GUEST                   0x000001F5L
#define DOMAIN_USER_RID_KRBTGT                  0x000001F6L
#define DOMAIN_USER_RID_MAX                     0x000003E7L

#define DOMAIN_GROUP_RID_ADMINS                 0x00000200L
#define DOMAIN_GROUP_RID_USERS                  0x00000201L
#define DOMAIN_GROUP_RID_GUESTS                 0x00000202L
#define DOMAIN_GROUP_RID_COMPUTERS              0x00000203L
#define DOMAIN_GROUP_RID_CONTROLLERS            0x00000204L
#define DOMAIN_GROUP_RID_CERT_ADMINS            0x00000205L
#define DOMAIN_GROUP_RID_SCHEMA_ADMINS          0x00000206L
#define DOMAIN_GROUP_RID_ENTERPRISE_ADMINS      0x00000207L
#define DOMAIN_GROUP_RID_POLICY_ADMINS          0x00000208L

#define SECURITY_MANDATORY_LABEL_AUTHORITY {0,0,0,0,0,16}
#define SECURITY_MANDATORY_UNTRUSTED_RID        0x00000000L
#define SECURITY_MANDATORY_LOW_RID              0x00001000L
#define SECURITY_MANDATORY_MEDIUM_RID           0x00002000L
#define SECURITY_MANDATORY_HIGH_RID             0x00003000L
#define SECURITY_MANDATORY_SYSTEM_RID           0x00004000L
#define SECURITY_MANDATORY_PROTECTED_PROCESS_RID 0x00005000L

#define DOMAIN_ALIAS_RID_ADMINS                 0x00000220L
#define DOMAIN_ALIAS_RID_USERS                  0x00000221L
#define DOMAIN_ALIAS_RID_GUESTS                 0x00000222L
#define DOMAIN_ALIAS_RID_POWER_USERS            0x00000223L

#define DOMAIN_ALIAS_RID_ACCOUNT_OPS            0x00000224L
#define DOMAIN_ALIAS_RID_SYSTEM_OPS             0x00000225L
#define DOMAIN_ALIAS_RID_PRINT_OPS              0x00000226L
#define DOMAIN_ALIAS_RID_BACKUP_OPS             0x00000227L

#define DOMAIN_ALIAS_RID_REPLICATOR             0x00000228L
#define DOMAIN_ALIAS_RID_RAS_SERVERS            0x00000229L
#define DOMAIN_ALIAS_RID_PREW2KCOMPACCESS       0x0000022AL
#define DOMAIN_ALIAS_RID_REMOTE_DESKTOP_USERS   0x0000022BL
#define DOMAIN_ALIAS_RID_NETWORK_CONFIGURATION_OPS 0x0000022CL
#define DOMAIN_ALIAS_RID_INCOMING_FOREST_TRUST_BUILDERS 0x0000022DL

#define DOMAIN_ALIAS_RID_MONITORING_USERS       0x0000022EL
#define DOMAIN_ALIAS_RID_LOGGING_USERS          0x0000022FL
#define DOMAIN_ALIAS_RID_AUTHORIZATIONACCESS    0x00000230L
#define DOMAIN_ALIAS_RID_TS_LICENSE_SERVERS     0x00000231L
#define DOMAIN_ALIAS_RID_DCOM_USERS             0x00000232L

#define SECURITY_SERVER_LOGON_RID		SECURITY_ENTERPRISE_CONTROLLERS_RID

#define SECURITY_PACKAGE_RID_COUNT              2L
#define SECURITY_LOGON_IDS_RID_COUNT		3L

typedef enum {
    WinNullSid                                  = 0,
    WinWorldSid                                 = 1,
    WinLocalSid                                 = 2,
    WinCreatorOwnerSid                          = 3,
    WinCreatorGroupSid                          = 4,
    WinCreatorOwnerServerSid                    = 5,
    WinCreatorGroupServerSid                    = 6,
    WinNtAuthoritySid                           = 7,
    WinDialupSid                                = 8,
    WinNetworkSid                               = 9,
    WinBatchSid                                 = 10,
    WinInteractiveSid                           = 11,
    WinServiceSid                               = 12,
    WinAnonymousSid                             = 13,
    WinProxySid                                 = 14,
    WinEnterpriseControllersSid                 = 15,
    WinSelfSid                                  = 16,
    WinAuthenticatedUserSid                     = 17,
    WinRestrictedCodeSid                        = 18,
    WinTerminalServerSid                        = 19,
    WinRemoteLogonIdSid                         = 20,
    WinLogonIdsSid                              = 21,
    WinLocalSystemSid                           = 22,
    WinLocalServiceSid                          = 23,
    WinNetworkServiceSid                        = 24,
    WinBuiltinDomainSid                         = 25,
    WinBuiltinAdministratorsSid                 = 26,
    WinBuiltinUsersSid                          = 27,
    WinBuiltinGuestsSid                         = 28,
    WinBuiltinPowerUsersSid                     = 29,
    WinBuiltinAccountOperatorsSid               = 30,
    WinBuiltinSystemOperatorsSid                = 31,
    WinBuiltinPrintOperatorsSid                 = 32,
    WinBuiltinBackupOperatorsSid                = 33,
    WinBuiltinReplicatorSid                     = 34,
    WinBuiltinPreWindows2000CompatibleAccessSid = 35,
    WinBuiltinRemoteDesktopUsersSid             = 36,
    WinBuiltinNetworkConfigurationOperatorsSid  = 37,
    WinAccountAdministratorSid                  = 38,
    WinAccountGuestSid                          = 39,
    WinAccountKrbtgtSid                         = 40,
    WinAccountDomainAdminsSid                   = 41,
    WinAccountDomainUsersSid                    = 42,
    WinAccountDomainGuestsSid                   = 43,
    WinAccountComputersSid                      = 44,
    WinAccountControllersSid                    = 45,
    WinAccountCertAdminsSid                     = 46,
    WinAccountSchemaAdminsSid                   = 47,
    WinAccountEnterpriseAdminsSid               = 48,
    WinAccountPolicyAdminsSid                   = 49,
    WinAccountRasAndIasServersSid               = 50,
    WinNTLMAuthenticationSid                    = 51,
    WinDigestAuthenticationSid                  = 52,
    WinSChannelAuthenticationSid                = 53,
    WinThisOrganizationSid                      = 54,
    WinOtherOrganizationSid                     = 55,
    WinBuiltinIncomingForestTrustBuildersSid    = 56,
    WinBuiltinPerfMonitoringUsersSid            = 57,
    WinBuiltinPerfLoggingUsersSid               = 58,
    WinBuiltinAuthorizationAccessSid            = 59,
    WinBuiltinTerminalServerLicenseServersSid   = 60,
    WinBuiltinDCOMUsersSid                      = 61,
    WinBuiltinIUsersSid                         = 62,
    WinIUserSid                                 = 63,
    WinBuiltinCryptoOperatorsSid                = 64,
    WinUntrustedLabelSid                        = 65,
    WinLowLabelSid                              = 66,
    WinMediumLabelSid                           = 67,
    WinHighLabelSid                             = 68,
    WinSystemLabelSid                           = 69,
    WinWriteRestrictedCodeSid                   = 70,
    WinCreatorOwnerRightsSid                    = 71,
    WinCacheablePrincipalsGroupSid              = 72,
    WinNonCacheablePrincipalsGroupSid           = 73,
    WinEnterpriseReadonlyControllersSid         = 74,
    WinAccountReadonlyControllersSid            = 75,
    WinBuiltinEventLogReadersGroup              = 76,
    WinNewEnterpriseReadonlyControllersSid      = 77,
    WinBuiltinCertSvcDComAccessGroup            = 78,
    WinMediumPlusLabelSid                       = 79,
    WinLocalLogonSid                            = 80,
    WinConsoleLogonSid                          = 81,
    WinThisOrganizationCertificateSid           = 82,
} WELL_KNOWN_SID_TYPE;

/*
 * TOKEN_USER
 */

typedef struct _TOKEN_USER {
    SID_AND_ATTRIBUTES User;
} TOKEN_USER, *PTOKEN_USER;

/*
 * TOKEN_GROUPS
 */

typedef struct _TOKEN_GROUPS {
    ::u32 GroupCount;
    SID_AND_ATTRIBUTES Groups[ANYSIZE_ARRAY];
} TOKEN_GROUPS, *PTOKEN_GROUPS;

/*
 * LUID_AND_ATTRIBUTES
 */

typedef union _LARGE_INTEGER {
    struct {
#ifdef WORDS_BIGENDIAN
        ::i32     HighPart;
        ::u32    LowPart;
#else
        ::u32    LowPart;
        ::i32     HighPart;
#endif
    } u;
#ifndef NONAMELESSSTRUCT
    struct {
#ifdef WORDS_BIGENDIAN
        ::i32     HighPart;
        ::u32    LowPart;
#else
        ::u32    LowPart;
        ::i32     HighPart;
#endif
    };
#endif
    ::i64 QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;

typedef union _ULARGE_INTEGER {
    struct {
#ifdef WORDS_BIGENDIAN
        ::u32    HighPart;
        ::u32    LowPart;
#else
        ::u32    LowPart;
        ::u32    HighPart;
#endif
    } u;
#ifndef NONAMELESSSTRUCT
    struct {
#ifdef WORDS_BIGENDIAN
        ::u32    HighPart;
        ::u32    LowPart;
#else
        ::u32    LowPart;
        ::u32    HighPart;
#endif
    };
#endif
    ULONGLONG QuadPart;
} ULARGE_INTEGER, *PULARGE_INTEGER;

/*
 * Locally Unique Identifier
 */

typedef struct _LUID {
    ::u32 LowPart;
    ::i32 HighPart;
} LUID, *PLUID;

//#include "windows_pshpack4.h"
//typedef struct _LUID_AND_ATTRIBUTES {
//  LUID   Luid;
//  ::u32  Attributes;
//} LUID_AND_ATTRIBUTES, *PLUID_AND_ATTRIBUTES;
//#include "windows_poppack.h"

/*
 * PRIVILEGE_SET
 */

//typedef struct _PRIVILEGE_SET {
//    ::u32 PrivilegeCount;
//    ::u32 Control;
//    LUID_AND_ATTRIBUTES Privilege[ANYSIZE_ARRAY];
//} PRIVILEGE_SET, *PPRIVILEGE_SET;

/*
 * TOKEN_PRIVILEGES
 */

//typedef struct _TOKEN_PRIVILEGES {
//  ::u32 PrivilegeCount;
//  LUID_AND_ATTRIBUTES Privileges[ANYSIZE_ARRAY];
//} TOKEN_PRIVILEGES, *PTOKEN_PRIVILEGES;

/*
 * TOKEN_OWNER
 */

typedef struct _TOKEN_OWNER {
  PSID Owner;
} TOKEN_OWNER, *PTOKEN_OWNER;

/*
 * TOKEN_PRIMARY_GROUP
 */

typedef struct _TOKEN_PRIMARY_GROUP {
  PSID PrimaryGroup;
} TOKEN_PRIMARY_GROUP, *PTOKEN_PRIMARY_GROUP;


/*
 * TOKEN_DEFAULT_DACL
 */

typedef struct _TOKEN_DEFAULT_DACL {
  PACL DefaultDacl;
} TOKEN_DEFAULT_DACL, *PTOKEN_DEFAULT_DACL;

/*
 * TOKEN_SOURCE
 */

#define TOKEN_SOURCE_LENGTH 8

typedef struct _TOKEN_SOURCE {
  char SourceName[TOKEN_SOURCE_LENGTH];
  LUID SourceIdentifier;
} TOKEN_SOURCE, *PTOKEN_SOURCE;

/*
 * TOKEN_TYPE
 */

typedef enum tagTOKEN_TYPE {
  TokenPrimary = 1,
  TokenImpersonation
} TOKEN_TYPE;

/*
 * SECURITY_IMPERSONATION_LEVEL
 */

typedef enum _SECURITY_IMPERSONATION_LEVEL {
  SecurityAnonymous,
  SecurityIdentification,
  SecurityImpersonation,
  SecurityDelegation
} SECURITY_IMPERSONATION_LEVEL, *PSECURITY_IMPERSONATION_LEVEL;

#define SECURITY_DYNAMIC_TRACKING   (true)
#define SECURITY_STATIC_TRACKING    (false)

typedef WINBOOLEAN SECURITY_CONTEXT_TRACKING_MODE,
	* PSECURITY_CONTEXT_TRACKING_MODE;
/*
 *	Quality of Service
 */

typedef struct _SECURITY_QUALITY_OF_SERVICE {
  ::u32				Length;
  SECURITY_IMPERSONATION_LEVEL	ImpersonationLevel;
  SECURITY_CONTEXT_TRACKING_MODE ContextTrackingMode;
  WINBOOLEAN			EffectiveOnly;
} SECURITY_QUALITY_OF_SERVICE, *PSECURITY_QUALITY_OF_SERVICE;

/*
 * TOKEN_STATISTICS
 */

//#include "windows_pshpack4.h"
//typedef struct _TOKEN_STATISTICS {
//  LUID  TokenId;
//  LUID  AuthenticationId;
//  LARGE_INTEGER ExpirationTime;
//  TOKEN_TYPE    TokenType;
//  SECURITY_IMPERSONATION_LEVEL ImpersonationLevel;
//  ::u32 DynamicCharged;
//  ::u32 Dynamicavailable;
//  ::u32 GroupCount;
//  ::u32 PrivilegeCount;
//  LUID  ModifiedId;
//} TOKEN_STATISTICS;
//#include "windows_poppack.h"

//typedef struct _TOKEN_GROUPS_AND_PRIVILEGES {
//  ::u32                 SidCount;
//  ::u32                 SidLength;
//  PSID_AND_ATTRIBUTES   Sids;
//  ::u32                 RestrictedSidCount;
//  ::u32                 RestrictedSidLength;
//  PSID_AND_ATTRIBUTES   RestrictedSids;
//  ::u32                 PrivilegeCount;
//  ::u32                 PrivilegeLength;
//  PLUID_AND_ATTRIBUTES  Privileges;
//  LUID                  AuthenticationId;
//} TOKEN_GROUPS_AND_PRIVILEGES, * PTOKEN_GROUPS_AND_PRIVILEGES;

typedef struct _TOKEN_ORIGIN {
  LUID  OriginatingLogonSession;
} TOKEN_ORIGIN, * PTOKEN_ORIGIN;

typedef struct _TOKEN_LINKED_TOKEN {
  HANDLE LinkedToken;
} TOKEN_LINKED_TOKEN, * PTOKEN_LINKED_TOKEN;

typedef struct _TOKEN_ELEVATION {
  ::u32 TokenIsElevated;
} TOKEN_ELEVATION, * PTOKEN_ELEVATION;


/*
 *	ACLs of NT
 */

/* ACEs, directly starting after an ACL */
typedef struct _ACE_HEADER {
	byte	AceType;
	byte	AceFlags;
	::u16	AceSize;
} ACE_HEADER,*PACE_HEADER;

/* AceType */
#define	ACCESS_ALLOWED_ACE_TYPE		0
#define	ACCESS_DENIED_ACE_TYPE		1
#define	SYSTEM_AUDIT_ACE_TYPE		2
#define	SYSTEM_ALARM_ACE_TYPE		3

/* inherit AceFlags */
#define	OBJECT_INHERIT_ACE		0x01
#define	CONTAINER_INHERIT_ACE		0x02
#define	NO_PROPAGATE_INHERIT_ACE	0x04
#define	INHERIT_ONLY_ACE		0x08
#define	INHERITED_ACE		        0x10
#define	VALID_INHERIT_FLAGS		0x1F

/* AceFlags mask for what events we (should) audit */
#define	SUCCESSFUL_ACCESS_ACE_FLAG	0x40
#define	FAILED_ACCESS_ACE_FLAG		0x80

/* different ACEs depending on AceType
 * SidStart marks the begin of a SID
 * so the thing finally looks like this:
 * 0: ACE_HEADER
 * 4: ACCESS_MASK
 * 8... : SID
 */
typedef struct _ACCESS_ALLOWED_ACE {
	ACE_HEADER	Header;
	::u32		Mask;
	::u32		SidStart;
} ACCESS_ALLOWED_ACE,*PACCESS_ALLOWED_ACE;

typedef struct _ACCESS_DENIED_ACE {
	ACE_HEADER	Header;
	::u32		Mask;
	::u32		SidStart;
} ACCESS_DENIED_ACE,*PACCESS_DENIED_ACE;

typedef struct _SYSTEM_AUDIT_ACE {
	ACE_HEADER	Header;
	::u32		Mask;
	::u32		SidStart;
} SYSTEM_AUDIT_ACE,*PSYSTEM_AUDIT_ACE;

typedef struct _SYSTEM_ALARM_ACE {
	ACE_HEADER	Header;
	::u32		Mask;
	::u32		SidStart;
} SYSTEM_ALARM_ACE,*PSYSTEM_ALARM_ACE;

typedef enum tagSID_NAME_USE {
	SidTypeUser = 1,
	SidTypeGroup,
	SidTypeDomain,
	SidTypeAlias,
	SidTypeWellKnownGroup,
	SidTypeDeletedAccount,
	SidTypeInvalid,
	SidTypeUnknown
} SID_NAME_USE,*PSID_NAME_USE;

#define ACE_OBJECT_TYPE_PRESENT 0x1
#define ACE_INHERITED_OBJECT_TYPE_PRESENT   0x2

/* Access rights */

/* DELETE may be already defined via /usr/include/arpa/nameser_compat.h */
#undef  DELETE
#define DELETE                     0x00010000
#define READ_CONTROL               0x00020000
#define WRITE_DAC                  0x00040000
#define WRITE_OWNER                0x00080000
#define SYNCHRONIZE                0x00100000
#define STANDARD_RIGHTS_REQUIRED   0x000f0000

#define STANDARD_RIGHTS_READ       READ_CONTROL
#define STANDARD_RIGHTS_WRITE      READ_CONTROL
#define STANDARD_RIGHTS_EXECUTE    READ_CONTROL

#define STANDARD_RIGHTS_ALL        0x001f0000

#define SPECIFIC_RIGHTS_ALL        0x0000ffff

#define GENERIC_READ               0x80000000
#define GENERIC_WRITE              0x40000000
#define GENERIC_EXECUTE            0x20000000
#define GENERIC_ALL                0x10000000

#define MAXIMUM_ALLOWED            0x02000000
#define ACCESS_SYSTEM_SECURITY     0x01000000

#define EVENT_QUERY_STATE          0x0001
#define EVENT_MODIFY_STATE         0x0002
#define EVENT_ALL_ACCESS           (STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|0x3)

#define SEMAPHORE_MODIFY_STATE     0x0002
#define SEMAPHORE_ALL_ACCESS       (STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|0x3)

#define MUTEX_MODIFY_STATE         0x0001
#define MUTEX_ALL_ACCESS           (STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|0x1)

#define JOB_OBJECT_ASSIGN_PROCESS           0x0001
#define JOB_OBJECT_SET_ATTRIBUTES           0x0002
#define JOB_OBJECT_QUERY                    0x0004
#define JOB_OBJECT_TERMINATE                0x0008
#define JOB_OBJECT_SET_SECURITY_ATTRIBUTES  0x0010
#define JOB_OBJECT_ALL_ACCESS               (STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|0x1f)

#define TIMER_QUERY_STATE          0x0001
#define TIMER_MODIFY_STATE         0x0002
#define TIMER_ALL_ACCESS           (STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|0x3)

#define PROCESS_TERMINATE          0x0001
#define PROCESS_CREATE_THREAD      0x0002
#define PROCESS_VM_OPERATION       0x0008
#define PROCESS_VM_READ            0x0010
#define PROCESS_VM_WRITE           0x0020
#define PROCESS_DUP_HANDLE         0x0040
#define PROCESS_CREATE_PROCESS     0x0080
#define PROCESS_SET_QUOTA          0x0100
#define PROCESS_SET_INFORMATION    0x0200
#define PROCESS_QUERY_INFORMATION  0x0400
#define PROCESS_SUSPEND_RESUME     0x0800
#define PROCESS_QUERY_LIMITED_INFORMATION 0x1000
#define PROCESS_ALL_ACCESS         (STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|0xfff)

#define THREAD_TERMINATE           0x0001
#define THREAD_SUSPEND_RESUME      0x0002
#define THREAD_GET_CONTEXT         0x0008
#define THREAD_SET_CONTEXT         0x0010
#define THREAD_SET_INFORMATION     0x0020
#define THREAD_QUERY_INFORMATION   0x0040
#define THREAD_SET_THREAD_TOKEN    0x0080
#define THREAD_IMPERSONATE         0x0100
#define THREAD_DIRECT_IMPERSONATION 0x0200
#define THREAD_ALL_ACCESS          (STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|0x3ff)

#define THREAD_BASE_PRIORITY_LOWRT  15
#define THREAD_BASE_PRIORITY_MAX    2
#define THREAD_BASE_PRIORITY_MIN   -2
#define THREAD_BASE_PRIORITY_IDLE  -15

typedef struct _QUOTA_LIMITS {
    SIZE_T PagedPoolLimit;
    SIZE_T NonPagedPoolLimit;
    SIZE_T MinimumWorkingSetSize;
    SIZE_T MaximumWorkingSetSize;
    SIZE_T PagefileLimit;
    LARGE_INTEGER TimeLimit;
} QUOTA_LIMITS, *PQUOTA_LIMITS;

#define QUOTA_LIMITS_HARDWS_MIN_ENABLE  0x00000001
#define QUOTA_LIMITS_HARDWS_MIN_DISABLE 0x00000002
#define QUOTA_LIMITS_HARDWS_MAX_ENABLE  0x00000004
#define QUOTA_LIMITS_HARDWS_MAX_DISABLE 0x00000008

typedef struct _QUOTA_LIMITS_EX {
    SIZE_T PagedPoolLimit;
    SIZE_T NonPagedPoolLimit;
    SIZE_T MinimumWorkingSetSize;
    SIZE_T MaximumWorkingSetSize;
    SIZE_T PagefileLimit;
    LARGE_INTEGER TimeLimit;
    SIZE_T Reserved1;
    SIZE_T Reserved2;
    SIZE_T Reserved3;
    SIZE_T Reserved4;
    ::u32 Flags;
    ::u32 Reserved5;
} QUOTA_LIMITS_EX, *PQUOTA_LIMITS_EX;

#define SECTION_QUERY              0x0001
#define SECTION_MAP_WRITE          0x0002
#define SECTION_MAP_READ           0x0004
#define SECTION_MAP_EXECUTE        0x0008
#define SECTION_EXTEND_SIZE        0x0010
#define SECTION_MAP_EXECUTE_EXPLICIT 0x0020
#define SECTION_ALL_ACCESS         (STANDARD_RIGHTS_REQUIRED|0x01f)

#define FILE_READ_DATA            0x0001    /* file & pipe */
#define FILE_LIST_DIRECTORY       0x0001    /* directory */
#define FILE_WRITE_DATA           0x0002    /* file & pipe */
#define FILE_ADD_FILE             0x0002    /* directory */
#define FILE_APPEND_DATA          0x0004    /* file */
#define FILE_ADD_SUBDIRECTORY     0x0004    /* directory */
#define FILE_CREATE_PIPE_INSTANCE 0x0004    /* named pipe */
#define FILE_READ_EA              0x0008    /* file & directory */
#define FILE_READ_PROPERTIES      FILE_READ_EA
#define FILE_WRITE_EA             0x0010    /* file & directory */
#define FILE_WRITE_PROPERTIES     FILE_WRITE_EA
#define FILE_EXECUTE              0x0020    /* file */
#define FILE_TRAVERSE             0x0020    /* directory */
#define FILE_DELETE_CHILD         0x0040    /* directory */
#define FILE_READ_ATTRIBUTES      0x0080    /* all */
#define FILE_WRITE_ATTRIBUTES     0x0100    /* all */
#define FILE_ALL_ACCESS           (STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|0x1ff)

#define FILE_GENERIC_READ         (STANDARD_RIGHTS_READ | FILE_READ_DATA | \
                                   FILE_READ_ATTRIBUTES | FILE_READ_EA | \
                                   SYNCHRONIZE)
#define FILE_GENERIC_WRITE        (STANDARD_RIGHTS_WRITE | FILE_WRITE_DATA | \
                                   FILE_WRITE_ATTRIBUTES | FILE_WRITE_EA | \
                                   FILE_APPEND_DATA | SYNCHRONIZE)
#define FILE_GENERIC_EXECUTE      (STANDARD_RIGHTS_EXECUTE | FILE_EXECUTE | \
                                   FILE_READ_ATTRIBUTES | SYNCHRONIZE)

#define DUPLICATE_CLOSE_SOURCE     0x00000001
#define DUPLICATE_SAME_ACCESS      0x00000002

/* File attribute flags */
#define FILE_SHARE_READ			0x00000001L
#define FILE_SHARE_WRITE		0x00000002L
#define FILE_SHARE_DELETE		0x00000004L

#define FILE_ATTRIBUTE_READONLY            0x00000001
#define FILE_ATTRIBUTE_HIDDEN              0x00000002
#define FILE_ATTRIBUTE_SYSTEM              0x00000004
#define FILE_ATTRIBUTE_DIRECTORY           0x00000010
#define FILE_ATTRIBUTE_ARCHIVE             0x00000020
#define FILE_ATTRIBUTE_DEVICE              0x00000040
#define FILE_ATTRIBUTE_NORMAL              0x00000080
#define FILE_ATTRIBUTE_TEMPORARY           0x00000100
#define FILE_ATTRIBUTE_SPARSE_FILE         0x00000200
#define FILE_ATTRIBUTE_REPARSE_POINT       0x00000400
#define FILE_ATTRIBUTE_COMPRESSED          0x00000800
#define FILE_ATTRIBUTE_OFFLINE             0x00001000
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED 0x00002000
#define FILE_ATTRIBUTE_ENCRYPTED           0x00004000

/* File notification flags */
#define FILE_NOTIFY_CHANGE_FILE_NAME    0x00000001
#define FILE_NOTIFY_CHANGE_DIR_NAME     0x00000002
#define FILE_NOTIFY_CHANGE_ATTRIBUTES   0x00000004
#define FILE_NOTIFY_CHANGE_SIZE         0x00000008
#define FILE_NOTIFY_CHANGE_LAST_WRITE   0x00000010
#define FILE_NOTIFY_CHANGE_LAST_ACCESS  0x00000020
#define FILE_NOTIFY_CHANGE_CREATION     0x00000040
#define FILE_NOTIFY_CHANGE_EA           0x00000080
#define FILE_NOTIFY_CHANGE_SECURITY     0x00000100
#define FILE_NOTIFY_CHANGE_STREAM_NAME  0x00000200
#define FILE_NOTIFY_CHANGE_STREAM_SIZE  0x00000400
#define FILE_NOTIFY_CHANGE_STREAM_WRITE 0x00000800

#define FILE_ACTION_ADDED               0x00000001
#define FILE_ACTION_REMOVED             0x00000002
#define FILE_ACTION_MODIFIED            0x00000003
#define FILE_ACTION_RENAMED_OLD_NAME    0x00000004
#define FILE_ACTION_RENAMED_NEW_NAME    0x00000005
#define FILE_ACTION_ADDED_STREAM        0x00000006
#define FILE_ACTION_REMOVED_STREAM      0x00000007
#define FILE_ACTION_MODIFIED_STREAM     0x00000008

#define FILE_CASE_SENSITIVE_SEARCH      0x00000001
#define FILE_CASE_PRESERVED_NAMES       0x00000002
#define FILE_UNICODE_ON_DISK            0x00000004
#define FILE_PERSISTENT_ACLS            0x00000008
#define FILE_FILE_COMPRESSION           0x00000010
#define FILE_VOLUME_IS_COMPRESSED       0x00008000
#define FILE_SUPPORTS_OBJECT_IDS        0x00010000
#define FILE_SUPPORTS_ENCRYPTION        0x00020000
#define FILE_NAMED_STREAMS              0x00040000
#define FILE_READ_ONLY_VOLUME           0x00080000

/* File alignments (NT) */
#define	FILE_BYTE_ALIGNMENT		0x00000000
#define	FILE_WORD_ALIGNMENT		0x00000001
#define	FILE_LONG_ALIGNMENT		0x00000003
#define	FILE_QUAD_ALIGNMENT		0x00000007
#define	FILE_OCTA_ALIGNMENT		0x0000000f
#define	FILE_32_BYTE_ALIGNMENT		0x0000001f
#define	FILE_64_BYTE_ALIGNMENT		0x0000003f
#define	FILE_128_BYTE_ALIGNMENT		0x0000007f
#define	FILE_256_BYTE_ALIGNMENT		0x000000ff
#define	FILE_512_BYTE_ALIGNMENT		0x000001ff

#define MAILSLOT_NO_MESSAGE             ((::u32)-1)
#define MAILSLOT_WAIT_FOREVER           ((::u32)-1)

#define REG_NONE		0	/* no type */
#define REG_SZ			1	/* string type (ASCII) */
#define REG_EXPAND_SZ		2	/* string, includes %ENVVAR% (expanded by caller) (ASCII) */
#define REG_BINARY		3	/* binary format, callerspecific */
/* YES, REG_DWORD == REG_DWORD_LITTLE_ENDIAN */
#define REG_DWORD		4	/* ::u32 in little endian format */
#define REG_DWORD_LITTLE_ENDIAN	4	/* ::u32 in little endian format */
#define REG_DWORD_BIG_ENDIAN	5	/* ::u32 in big endian format  */
#define REG_LINK		6	/* symbolic link (UNICODE) */
#define REG_MULTI_SZ		7	/* multiple strings, delimited by \0, terminated by \0\0 (ASCII) */
#define REG_RESOURCE_LIST	8	/* resource list? huh? */
#define REG_FULL_RESOURCE_DESCRIPTOR	9	/* full resource descriptor? huh? */
#define REG_RESOURCE_REQUIREMENTS_LIST	10
#define REG_QWORD		11	/* QWORD in little endian format */
#define REG_QWORD_LITTLE_ENDIAN	11	/* QWORD in little endian format */

/* ----------------------------- begin power management --------------------- */

typedef enum _LATENCY_TIME {
	LT_DONT_CARE,
	LT_LOWEST_LATENCY
} LATENCY_TIME, *PLATENCY_TIME;

#define DISCHARGE_POLICY_CRITICAL 	0
#define DISCHARGE_POLICY_LOW		1
#define NUM_DISCHARGE_POLICIES		4

#define PO_THROTTLE_NONE		0
#define PO_THROTTLE_CONSTANT		1
#define PO_THROTTLE_DEGRADE		2
#define PO_THROTTLE_ADAPTIVE		3

typedef enum _POWER_ACTION {
	PowerActionNone = 0,
	PowerActionReserved,
	PowerActionSleep,
	PowerActionHibernate,
	PowerActionShutdown,
	PowerActionShutdownReset,
	PowerActionShutdownOff,
	PowerActionWarmEject
} POWER_ACTION,
*PPOWER_ACTION;

typedef enum _SYSTEM_POWER_STATE {
	PowerSystemUnspecified = 0,
	PowerSystemWorking = 1,
	PowerSystemSleeping1 = 2,
	PowerSystemSleeping2 = 3,
	PowerSystemSleeping3 = 4,
	PowerSystemHibernate = 5,
	PowerSystemShutdown = 6,
	PowerSystemMaximum = 7
} SYSTEM_POWER_STATE,
*PSYSTEM_POWER_STATE;

typedef enum _DEVICE_POWER_STATE {
    PowerDeviceUnspecified,
    PowerDeviceD0,
    PowerDeviceD1,
    PowerDeviceD2,
    PowerDeviceD3,
    PowerDeviceMaximum
} DEVICE_POWER_STATE, *PDEVICE_POWER_STATE;

typedef enum _POWER_INFORMATION_LEVEL {
        SystemPowerPolicyAc,
        SystemPowerPolicyDc,
        VerifySystemPolicyAc,
        VerifySystemPolicyDc,
        SystemPowerCapabilities,
        SystemBatteryState,
        SystemPowerStateHandler,
        ProcessorStateHandler,
        SystemPowerPolicyCurrent,
        AdministratorPowerPolicy,
        SystemReserveHiberFile,
        ProcessorInformation,
        SystemPowerInformation,
        ProcessorStateHandler2,
        LastWakeTime,
        LastSleepTime,
        SystemExecutionState,
        SystemPowerStateNotifyHandler,
        ProcessorPowerPolicyAc,
        ProcessorPowerPolicyDc,
        VerifyProcessorPowerPolicyAc,
        VerifyProcessorPowerPolicyDc,
        ProcessorPowerPolicyCurrent
} POWER_INFORMATION_LEVEL;

typedef struct _ADMINISTRATOR_POWER_POLICY {
	SYSTEM_POWER_STATE MinSleep;
	SYSTEM_POWER_STATE MaxSleep;
	WINULONG MinVideoTimeout;
	WINULONG MaxVideoTimeout;
	WINULONG MinSpindownTimeout;
	WINULONG MaxSpindownTimeout;
} ADMINISTRATOR_POWER_POLICY, *PADMINISTRATOR_POWER_POLICY;

typedef struct {
	WINULONG Granularity;
	WINULONG Capacity;
} BATTERY_REPORTING_SCALE,
*PBATTERY_REPORTING_SCALE;

typedef struct {
	POWER_ACTION Action;
	WINULONG Flags;
	WINULONG EventCode;
} POWER_ACTION_POLICY,
*PPOWER_ACTION_POLICY;

typedef struct _PROCESSOR_POWER_INFORMATION {
	WINULONG Number;
	WINULONG MaxMhz;
	WINULONG CurrentMhz;
	WINULONG MhzLimit;
	WINULONG MaxIdleState;
	WINULONG CurrentIdleState;
} PROCESSOR_POWER_INFORMATION,
*PPROCESSOR_POWER_INFORMATION;

typedef struct _PROCESSOR_POWER_POLICY_INFO {
	WINULONG TimeCheck;
	WINULONG DemoteLimit;
	WINULONG PromoteLimit;
	WINUCHAR DemotePercent;
	WINUCHAR PromotePercent;
	WINUCHAR Spare[2];
	WINULONG AllowDemotion:1;
	WINULONG AllowPromotion:1;
	WINULONG Reserved:30;
} PROCESSOR_POWER_POLICY_INFO,
*PPROCESSOR_POWER_POLICY_INFO;

typedef struct _PROCESSOR_POWER_POLICY {
	::u32 Revision;
	byte DynamicThrottle;
	byte Spare[3];
	::u32 DisableCStates:1;
	::u32 Reserved:31;
	::u32 PolicyCount;
	PROCESSOR_POWER_POLICY_INFO Policy[3];
} PROCESSOR_POWER_POLICY,
*PPROCESSOR_POWER_POLICY;

typedef struct {
	WINBOOLEAN AcOnLine;
	WINBOOLEAN BatteryPresent;
	WINBOOLEAN Charging;
	WINBOOLEAN Discharging;
	WINBOOLEAN Spare1[4];
	WINULONG MaxCapacity;
	WINULONG RemainingCapacity;
	WINULONG Rate;
	WINULONG EstimatedTime;
	WINULONG DefaultAlert1;
	WINULONG DefaultAlert2;
} SYSTEM_BATTERY_STATE,
*PSYSTEM_BATTERY_STATE;

typedef struct {
	WINBOOLEAN PowerButtonPresent;
	WINBOOLEAN SleepButtonPresent;
	WINBOOLEAN LidPresent;
	WINBOOLEAN SystemS1;
	WINBOOLEAN SystemS2;
	WINBOOLEAN SystemS3;
	WINBOOLEAN SystemS4;
	WINBOOLEAN SystemS5;
	WINBOOLEAN HiberFilePresent;
	WINBOOLEAN FullWake;
	WINBOOLEAN VideoDimPresent;
	WINBOOLEAN ApmPresent;
	WINBOOLEAN UpsPresent;
	WINBOOLEAN ThermalControl;
	WINBOOLEAN ProcessorThrottle;
	WINUCHAR ProcessorMinThrottle;
	WINUCHAR ProcessorMaxThrottle;
	WINUCHAR spare2[4];
	WINBOOLEAN DiskSpinDown;
	WINUCHAR spare3[8];
	WINBOOLEAN SystemBatteriesPresent;
	WINBOOLEAN BatteriesAreShortTerm;
	BATTERY_REPORTING_SCALE BatteryScale[3];
	SYSTEM_POWER_STATE AcOnLineWake;
	SYSTEM_POWER_STATE SoftLidWake;
	SYSTEM_POWER_STATE RtcWake;
	SYSTEM_POWER_STATE MinDeviceWakeState;
	SYSTEM_POWER_STATE DefaultLowLatencyWake;
} SYSTEM_POWER_CAPABILITIES,
*PSYSTEM_POWER_CAPABILITIES;

typedef struct _SYSTEM_POWER_INFORMATION {
	WINULONG MaxIdlenessAllowed;
	WINULONG Idleness;
	WINULONG TimeRemaining;
	WINUCHAR CoolingMode;
} SYSTEM_POWER_INFORMATION,
*PSYSTEM_POWER_INFORMATION;

typedef struct _SYSTEM_POWER_LEVEL {
	WINBOOLEAN Enable;
	WINUCHAR Spare[3];
	WINULONG BatteryLevel;
	POWER_ACTION_POLICY PowerPolicy;
	SYSTEM_POWER_STATE MinSystemState;
} SYSTEM_POWER_LEVEL,
*PSYSTEM_POWER_LEVEL;

typedef struct _SYSTEM_POWER_POLICY {
	WINULONG Revision;
	POWER_ACTION_POLICY PowerButton;
	POWER_ACTION_POLICY SleepButton;
	POWER_ACTION_POLICY LidClose;
	SYSTEM_POWER_STATE LidOpenWake;
	WINULONG Reserved;
	POWER_ACTION_POLICY Idle;
	WINULONG IdleTimeout;
	WINUCHAR IdleSensitivity;
	WINUCHAR DynamicThrottle;
	WINUCHAR Spare2[2];
	SYSTEM_POWER_STATE MinSleep;
	SYSTEM_POWER_STATE MaxSleep;
	SYSTEM_POWER_STATE ReducedLatencySleep;
	WINULONG WinLogonFlags;
	WINULONG Spare3;
	WINULONG DozeS4Timeout;
	WINULONG BroadcastCapacityResolution;
	SYSTEM_POWER_LEVEL DischargePolicy[NUM_DISCHARGE_POLICIES];
	WINULONG VideoTimeout;
	WINBOOLEAN VideoDimDisplay;
	WINULONG VideoReserved[3];
	WINULONG SpindownTimeout;
	WINBOOLEAN OptimizeForPower;
	WINUCHAR FanThrottleTolerance;
	WINUCHAR ForcedThrottle;
	WINUCHAR MinThrottle;
	POWER_ACTION_POLICY OverThrottled;
} SYSTEM_POWER_POLICY,
*PSYSTEM_POWER_POLICY;

typedef union _FILE_SEGMENT_ELEMENT {
	PVOID64 Buffer;
	ULONGLONG Alignment;
} FILE_SEGMENT_ELEMENT, *PFILE_SEGMENT_ELEMENT;

typedef struct _FILE_NOTIFY_INFORMATION {
	::u32 NextEntryOffset;
	::u32 Action;
	::u32 FileNameLength;
	WCHAR FileName[1];
} FILE_NOTIFY_INFORMATION, *PFILE_NOTIFY_INFORMATION;

/* ----------------------------- begin tape storage --------------------- */

#define TAPE_FIXED_PARTITIONS     0
#define TAPE_SELECT_PARTITIONS    1
#define TAPE_INITIATOR_PARTITIONS 2
#define TAPE_ERASE_SHORT 0
#define TAPE_ERASE_LONG  1
#define TAPE_LOAD    0
#define TAPE_UNLOAD  1
#define TAPE_TENSION 2
#define TAPE_LOCK    3
#define TAPE_UNLOCK  4
#define TAPE_FORMAT  5
#define TAPE_SETMARKS  0
#define TAPE_FILEMARKS 1
#define TAPE_SHORT_FILEMARKS 2
#define TAPE_LONG_FILEMARKS  3
#define TAPE_REWIND                0
#define TAPE_ABSOLUTE_BLOCK        1
#define TAPE_LOGICAL_BLOCK         2
#define TAPE_PSEUDO_LOGICAL_BLOCK  3
#define TAPE_SPACE_END_OF_DATA     4
#define TAPE_SPACE_RELATIVE_BLOCKS 5
#define TAPE_SPACE_FILEMARKS       6
#define TAPE_SPACE_SEQUENTIAL_FMKS 7
#define TAPE_SPACE_SETMARKS        8
#define TAPE_SPACE_SEQUENTIAL_SMKS 9

typedef struct _TAPE_CREATE_PARTITION {
    ::u32 Method;
    ::u32 Count;
    ::u32 Size;
} TAPE_CREATE_PARTITION, *PTAPE_CREATE_PARTITION;

typedef struct _TAPE_ERASE {
    ::u32 Type;
    WINBOOLEAN Immediate;
} TAPE_ERASE, *PTAPE_ERASE;

typedef struct _TAPE_PREPARE {
    ::u32 Operation;
    WINBOOLEAN Immediate;
} TAPE_PREPARE, *PTAPE_PREPARE;

typedef struct _TAPE_SET_DRIVE_PARAMETERS {
    WINBOOLEAN ECC;
    WINBOOLEAN Compression;
    WINBOOLEAN DataPadding;
    WINBOOLEAN ReportSetmarks;
    WINULONG EOTWarningZoneSize;
} TAPE_SET_DRIVE_PARAMETERS, *PTAPE_SET_DRIVE_PARAMETERS;

typedef struct _TAPE_SET_MEDIA_PARAMETERS {
    WINULONG BlockSize;
} TAPE_SET_MEDIA_PARAMETERS, *PTAPE_SET_MEDIA_PARAMETERS;

typedef struct _TAPE_WRITE_MARKS {
    ::u32 Type;
    ::u32 Count;
    WINBOOLEAN Immediate;
} TAPE_WRITE_MARKS, *PTAPE_WRITE_MARKS;

typedef struct _TAPE_GET_POSITION {
    WINULONG Type;
    WINULONG Partition;
    WINULONG OffsetLow;
    WINULONG OffsetHigh;
} TAPE_GET_POSITION, *PTAPE_GET_POSITION;

typedef struct _TAPE_SET_POSITION {
    WINULONG Method;
    WINULONG Partition;
    LARGE_INTEGER Offset;
    WINBOOLEAN Immediate;
} TAPE_SET_POSITION, *PTAPE_SET_POSITION;

typedef struct _TAPE_GET_DRIVE_PARAMETERS {
    WINBOOLEAN ECC;
    WINBOOLEAN Compression;
    WINBOOLEAN DataPadding;
    WINBOOLEAN ReportSetmarks;
    ::u32 DefaultBlockSize;
    ::u32 MaximumBlockSize;
    ::u32 MinimumBlockSize;
    ::u32 MaximumPartitionCount;
    ::u32 FeaturesLow;
    ::u32 FeaturesHigh;
    ::u32 EOTWarningZoneSize;
} TAPE_GET_DRIVE_PARAMETERS, *PTAPE_GET_DRIVE_PARAMETERS;

typedef struct _TAPE_GET_MEDIA_PARAMETERS {
    LARGE_INTEGER Capacity;
    LARGE_INTEGER Remaining;
    ::u32 BlockSize;
    ::u32 PartitionCount;
    WINBOOLEAN WriteProtected;
} TAPE_GET_MEDIA_PARAMETERS, *PTAPE_GET_MEDIA_PARAMETERS;

/* ----------------------------- begin registry ----------------------------- */

/* Registry security values */
#define OWNER_SECURITY_INFORMATION	0x00000001
#define GROUP_SECURITY_INFORMATION	0x00000002
#define DACL_SECURITY_INFORMATION	0x00000004
#define SACL_SECURITY_INFORMATION	0x00000008

#define REG_OPTION_RESERVED		0x00000000
#define REG_OPTION_NON_VOLATILE		0x00000000
#define REG_OPTION_VOLATILE		0x00000001
#define REG_OPTION_CREATE_LINK		0x00000002
#define REG_OPTION_BACKUP_RESTORE	0x00000004 /* FIXME */
#define REG_OPTION_OPEN_LINK		0x00000008
#define REG_LEGAL_OPTION	       (REG_OPTION_RESERVED|  \
					REG_OPTION_NON_VOLATILE|  \
					REG_OPTION_VOLATILE|  \
					REG_OPTION_CREATE_LINK|  \
					REG_OPTION_BACKUP_RESTORE|  \
					REG_OPTION_OPEN_LINK)


#define REG_CREATED_NEW_KEY	0x00000001
#define REG_OPENED_EXISTING_KEY	0x00000002

/* For RegNotifyChangeKeyValue */
#define REG_NOTIFY_CHANGE_NAME       0x01
#define REG_NOTIFY_CHANGE_ATTRIBUTES 0x02
#define REG_NOTIFY_CHANGE_LAST_SET   0x04
#define REG_NOTIFY_CHANGE_SECURITY   0x08

#define KEY_QUERY_VALUE		0x00000001
#define KEY_SET_VALUE		0x00000002
#define KEY_CREATE_SUB_KEY	0x00000004
#define KEY_ENUMERATE_SUB_KEYS	0x00000008
#define KEY_NOTIFY		0x00000010
#define KEY_CREATE_LINK		0x00000020
#define KEY_WOW64_64KEY         0x00000100
#define KEY_WOW64_32KEY         0x00000200
#define KEY_WOW64_RES           0x00000300

/* for RegKeyRestore flags */
#define REG_WHOLE_HIVE_VOLATILE 0x00000001
#define REG_REFRESH_HIVE        0x00000002
#define REG_NO_LAZY_FLUSH       0x00000004
#define REG_FORCE_RESTORE       0x00000008

#define KEY_READ	      ((STANDARD_RIGHTS_READ|  \
				KEY_QUERY_VALUE|  \
				KEY_ENUMERATE_SUB_KEYS|  \
				KEY_NOTIFY)  \
				& (~SYNCHRONIZE)  \
			      )
#define KEY_WRITE	      ((STANDARD_RIGHTS_WRITE|  \
				KEY_SET_VALUE|  \
				KEY_CREATE_SUB_KEY)  \
				& (~SYNCHRONIZE)  \
			      )
#define KEY_EXECUTE           ((KEY_READ) & (~SYNCHRONIZE))
#define KEY_ALL_ACCESS        ((STANDARD_RIGHTS_ALL|  \
				KEY_QUERY_VALUE|  \
				KEY_SET_VALUE|  \
				KEY_CREATE_SUB_KEY|  \
				KEY_ENUMERATE_SUB_KEYS|  \
				KEY_NOTIFY|  \
				KEY_CREATE_LINK)  \
				& (~SYNCHRONIZE)  \
			      )
/* ------------------------------ end registry ------------------------------ */


#define EVENTLOG_SUCCESS                0x0000
#define EVENTLOG_ERROR_TYPE             0x0001
#define EVENTLOG_WARNING_TYPE           0x0002
#define EVENTLOG_INFORMATION_TYPE       0x0004
#define EVENTLOG_AUDIT_SUCCESS          0x0008
#define EVENTLOG_AUDIT_FAILURE          0x0010

#define EVENTLOG_SEQUENTIAL_READ        0x0001
#define EVENTLOG_SEEK_READ              0x0002
#define EVENTLOG_FORWARDS_READ          0x0004
#define EVENTLOG_BACKWARDS_READ         0x0008

typedef struct _EVENTLOGRECORD {
    ::u32  Length;
    ::u32  Reserved;
    ::u32  RecordNumber;
    ::u32  TimeGenerated;
    ::u32  TimeWritten;
    ::u32  EventID;
    ::u16   EventType;
    ::u16   NumStrings;
    ::u16   EventCategory;
    ::u16   ReservedFlags;
    ::u32  ClosingRecordNumber;
    ::u32  StringOffset;
    ::u32  UserSidLength;
    ::u32  UserSidOffset;
    ::u32  DataLength;
    ::u32  DataOffset;
} EVENTLOGRECORD, *PEVENTLOGRECORD;

#define SERVICE_BOOT_START   0x00000000
#define SERVICE_SYSTEM_START 0x00000001
#define SERVICE_AUTO_START   0x00000002
#define SERVICE_DEMAND_START 0x00000003
#define SERVICE_DISABLED     0x00000004

#define SERVICE_ERROR_IGNORE   0x00000000
#define SERVICE_ERROR_NORMAL   0x00000001
#define SERVICE_ERROR_SEVERE   0x00000002
#define SERVICE_ERROR_CRITICAL 0x00000003

/* Service types */
#define SERVICE_KERNEL_DRIVER      0x00000001
#define SERVICE_FILE_SYSTEM_DRIVER 0x00000002
#define SERVICE_ADAPTER            0x00000004
#define SERVICE_RECOGNIZER_DRIVER  0x00000008

#define SERVICE_DRIVER ( SERVICE_KERNEL_DRIVER | SERVICE_FILE_SYSTEM_DRIVER | \
                         SERVICE_RECOGNIZER_DRIVER )

#define SERVICE_WIN32_OWN_PROCESS   0x00000010
#define SERVICE_WIN32_SHARE_PROCESS 0x00000020
#define SERVICE_WIN32  (SERVICE_WIN32_OWN_PROCESS | SERVICE_WIN32_SHARE_PROCESS)

#define SERVICE_INTERACTIVE_PROCESS 0x00000100

#define SERVICE_TYPE_ALL ( SERVICE_WIN32 | SERVICE_ADAPTER | \
                           SERVICE_DRIVER | SERVICE_INTERACTIVE_PROCESS )


typedef enum _CM_SERVICE_NODE_TYPE
{
  DriverType               = SERVICE_KERNEL_DRIVER,
  FileSystemType           = SERVICE_FILE_SYSTEM_DRIVER,
  Win32ServiceOwnProcess   = SERVICE_WIN32_OWN_PROCESS,
  Win32ServiceShareProcess = SERVICE_WIN32_SHARE_PROCESS,
  AdapterType              = SERVICE_ADAPTER,
  RecognizerType           = SERVICE_RECOGNIZER_DRIVER
} SERVICE_NODE_TYPE;

typedef enum _CM_SERVICE_LOAD_TYPE
{
  BootLoad    = SERVICE_BOOT_START,
  SystemLoad  = SERVICE_SYSTEM_START,
  AutoLoad    = SERVICE_AUTO_START,
  DemandLoad  = SERVICE_DEMAND_START,
  DisableLoad = SERVICE_DISABLED
} SERVICE_LOAD_TYPE;

typedef enum _CM_ERROR_CONTROL_TYPE
{
  IgnoreError   = SERVICE_ERROR_IGNORE,
  NormalError   = SERVICE_ERROR_NORMAL,
  SevereError   = SERVICE_ERROR_SEVERE,
  CriticalError = SERVICE_ERROR_CRITICAL
} SERVICE_ERROR_TYPE;



#define RtlEqualMemory(Destination, Source, Length) (!__memcmp((Destination),(Source),(Length)))
#define RtlMoveMemory(Destination, Source, Length) __memmov((Destination),(Source),(Length))
#define RtlCopyMemory(Destination, Source, Length) ::memcpy_dup((Destination),(Source),(Length))
#define RtlFillMemory(Destination, Length, Fill) __memset((Destination),(Fill),(Length))
#define RtlZeroMemory(Destination, Length) __memset((Destination),0,(Length))

#include "windows_guid_def.h"

typedef struct _OBJECT_TYPE_LIST {
    ::u16   Level;
    ::u16   Sbz;
    GUID *ObjectType;
} OBJECT_TYPE_LIST, *POBJECT_TYPE_LIST;

typedef struct _RTL_CRITICAL_SECTION_DEBUG
{
  ::u16   Type;
  ::u16   CreatorBackTraceIndex;
  struct _RTL_CRITICAL_SECTION *CriticalSection;
  LIST_ENTRY ProcessLocksList;
  ::u32 EntryCount;
  ::u32 ContentionCount;
#ifdef __WINESRC__  /* in Wine we store the name here */
  DWORD_PTR Spare[8/sizeof(DWORD_PTR)];
#else
  ::u32 Spare[ 2 ];
#endif
} RTL_CRITICAL_SECTION_DEBUG, *PRTL_CRITICAL_SECTION_DEBUG, RTL_RESOURCE_DEBUG, *PRTL_RESOURCE_DEBUG;

typedef struct _RTL_CRITICAL_SECTION {
    PRTL_CRITICAL_SECTION_DEBUG DebugInfo;
    ::i32 LockCount;
    ::i32 RecursionCount;
    HANDLE OwningThread;
    HANDLE LockSemaphore;
    ULONG_PTR SpinCount;
}  RTL_CRITICAL_SECTION, *PRTL_CRITICAL_SECTION;

#define RTL_CRITICAL_SECTION_FLAG_NO_DEBUG_INFO 0x1000000
#define RTL_CRITICAL_SECTION_FLAG_DYNAMIC_SPIN  0x2000000
#define RTL_CRITICAL_SECTION_FLAG_STATIC_INIT   0x4000000
#define RTL_CRITICAL_SECTION_ALL_FLAG_BITS      0xFF000000
#define RTL_CRITICAL_SECTION_FLAG_RESERVED      (RTL_CRITICAL_SECTION_ALL_FLAG_BITS & ~0x7000000)

typedef VOID (NTAPI * WAITORTIMERCALLBACKFUNC) (PVOID, WINBOOLEAN );
typedef VOID (NTAPI * PFLS_CALLBACK_FUNCTION) ( PVOID );

//#include "windows_pshpack8.h"
//typedef struct _IO_COUNTERS {
//    ULONGLONG DECLSPEC_ALIGN(8) ReadOperationCount;
//    ULONGLONG DECLSPEC_ALIGN(8) WriteOperationCount;
//    ULONGLONG DECLSPEC_ALIGN(8) OtherOperationCount;
//    ULONGLONG DECLSPEC_ALIGN(8) ReadTransferCount;
//    ULONGLONG DECLSPEC_ALIGN(8) WriteTransferCount;
//    ULONGLONG DECLSPEC_ALIGN(8) OtherTransferCount;
//} IO_COUNTERS, *PIO_COUNTERS;
//#include "windows_poppack.h"

//typedef struct {
//	::u32 dwOSVersionInfoSize;
//	::u32 dwMajorVersion;
//	::u32 dwMinorVersion;
//	::u32 dwBuildNumber;
//	::u32 dwPlatformId;
//	char szCSDVersion[128];
//} OSVERSIONINFOA, *POSVERSIONINFOA, *LPOSVERSIONINFOA;

typedef struct {
	::u32 dwOSVersionInfoSize;
	::u32 dwMajorVersion;
	::u32 dwMinorVersion;
	::u32 dwBuildNumber;
	::u32 dwPlatformId;
	WCHAR szCSDVersion[128];
} OSVERSIONINFOW, *POSVERSIONINFOW, *LPOSVERSIONINFOW, RTL_OSVERSIONINFOW, *PRTL_OSVERSIONINFOW;

DECL_WINELIB_TYPE_AW(OSVERSIONINFO)
DECL_WINELIB_TYPE_AW(POSVERSIONINFO)
DECL_WINELIB_TYPE_AW(LPOSVERSIONINFO)



typedef struct {
	::u32 dwOSVersionInfoSize;
	::u32 dwMajorVersion;
	::u32 dwMinorVersion;
	::u32 dwBuildNumber;
	::u32 dwPlatformId;
	WCHAR szCSDVersion[128];
	::u16 wServicePackMajor;
	::u16 wServicePackMinor;
	::u16 wSuiteMask;
	byte wProductType;
	byte wReserved;
} OSVERSIONINFOEXW, *POSVERSIONINFOEXW, *LPOSVERSIONINFOEXW, RTL_OSVERSIONINFOEXW, *PRTL_OSVERSIONINFOEXW;

DECL_WINELIB_TYPE_AW(OSVERSIONINFOEX)
DECL_WINELIB_TYPE_AW(POSVERSIONINFOEX)
DECL_WINELIB_TYPE_AW(LPOSVERSIONINFOEX)

NTSYSAPI ULONGLONG WINAPI VerSetConditionMask(ULONGLONG,::u32,byte);

#define VER_SET_CONDITION(_m_,_t_,_c_) ((_m_)=VerSetConditionMask((_m_),(_t_),(_c_)))


#define	VER_MINORVERSION			0x00000001
#define	VER_MAJORVERSION			0x00000002
#define	VER_BUILDNUMBER				0x00000004
#define	VER_PLATFORMID				0x00000008
#define	VER_SERVICEPACKMINOR			0x00000010
#define	VER_SERVICEPACKMAJOR			0x00000020
#define	VER_SUITENAME				0x00000040
#define	VER_PRODUCT_TYPE			0x00000080


#define	VER_SUITE_SMALLBUSINESS			0x00000001
#define	VER_SUITE_ENTERPRISE			0x00000002
#define	VER_SUITE_BACKOFFICE			0x00000004
#define	VER_SUITE_COMMUNICATIONS		0x00000008
#define	VER_SUITE_TERMINAL			0x00000010
#define	VER_SUITE_SMALLBUSINESS_RESTRICTED	0x00000020
#define	VER_SUITE_EMBEDDEDNT			0x00000040
#define	VER_SUITE_DATACENTER			0x00000080
#define	VER_SUITE_SINGLEUSERTS			0x00000100
#define	VER_SUITE_PERSONAL			0x00000200
#define	VER_SUITE_BLADE				0x00000400
#define	VER_SUITE_EMBEDDED_RESTRICTED		0x00000800
#define	VER_SUITE_SECURITY_APPLIANCE		0x00001000
#define VER_SUITE_STORAGE_SERVER                0x00002000
#define VER_SUITE_COMPUTE_SERVER                0x00004000
#define VER_SUITE_WH_SERVER                     0x00008000

#define	VER_EQUAL				1
#define	VER_GREATER				2
#define	VER_GREATER_EQUAL			3
#define	VER_LESS				4
#define	VER_LESS_EQUAL				5
#define	VER_AND					6
#define	VER_OR					7

typedef struct _ACTIVATION_CONTEXT_DETAILED_INFORMATION {
    ::u32 dwFlags;
    ::u32 ulFormatVersion;
    ::u32 ulAssemblyCount;
    ::u32 ulRootManifestPathType;
    ::u32 ulRootManifestPathChars;
    ::u32 ulRootConfigurationPathType;
    ::u32 ulRootConfigurationPathChars;
    ::u32 ulAppDirPathType;
    ::u32 ulAppDirPathChars;
    PCWSTR lpRootManifestPath;
    PCWSTR lpRootConfigurationPath;
    PCWSTR lpAppDirPath;
} ACTIVATION_CONTEXT_DETAILED_INFORMATION, *PACTIVATION_CONTEXT_DETAILED_INFORMATION;

typedef struct _ACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION {
    ::u32 ulFlags;
    ::u32 ulEncodedAssemblyIdentityLength;
    ::u32 ulManifestPathType;
    ::u32 ulManifestPathLength;
    LARGE_INTEGER liManifestLastWriteTime;
    ::u32 ulPolicyPathType;
    ::u32 ulPolicyPathLength;
    LARGE_INTEGER liPolicyLastWriteTime;
    ::u32 ulMetadataSatelliteRosterIndex;
    ::u32 ulManifestVersionMajor;
    ::u32 ulManifestVersionMinor;
    ::u32 ulPolicyVersionMajor;
    ::u32 ulPolicyVersionMinor;
    ::u32 ulAssemblyDirectoryNameLength;
    PCWSTR lpAssemblyEncodedAssemblyIdentity;
    PCWSTR lpAssemblyManifestPath;
    PCWSTR lpAssemblyPolicyPath;
    PCWSTR lpAssemblyDirectoryName;
    ::u32  ulFileCount;
} ACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION, *PACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION;

typedef struct _ACTIVATION_CONTEXT_QUERY_INDEX {
    ::u32 ulAssemblyIndex;
    ::u32 ulFileIndexInAssembly;
} ACTIVATION_CONTEXT_QUERY_INDEX, *PACTIVATION_CONTEXT_QUERY_INDEX;

typedef const struct _ACTIVATION_CONTEXT_QUERY_INDEX *PCACTIVATION_CONTEXT_QUERY_INDEX;

typedef struct _ASSEMBLY_FILE_DETAILED_INFORMATION {
    ::u32 ulFlags;
    ::u32 ulFilenameLength;
    ::u32 ulPathLength;
    PCWSTR lpFileName;
    PCWSTR lpFilePath;
} ASSEMBLY_FILE_DETAILED_INFORMATION, *PASSEMBLY_FILE_DETAILED_INFORMATION;

typedef const ASSEMBLY_FILE_DETAILED_INFORMATION *PCASSEMBLY_FILE_DETAILED_INFORMATION;

typedef enum _ACTIVATION_CONTEXT_INFO_CLASS {
    ActivationContextBasicInformation                       = 1,
    ActivationContextDetailedInformation                    = 2,
    AssemblyDetailedInformationInActivationContext          = 3,
    FileInformationInAssemblyOfAssemblyInActivationContext  = 4,
    MaxActivationContextInfoClass,

    AssemblyDetailedInformationInActivationContxt          = 3,
    FileInformationInAssemblyOfAssemblyInActivationContxt  = 4
} ACTIVATION_CONTEXT_INFO_CLASS;

#define ACTIVATION_CONTEXT_PATH_TYPE_NONE         1
#define ACTIVATION_CONTEXT_PATH_TYPE_WIN32_FILE   2
#define ACTIVATION_CONTEXT_PATH_TYPE_URL          3
#define ACTIVATION_CONTEXT_PATH_TYPE_ASSEMBLYREF  4

#define ACTIVATION_CONTEXT_SECTION_ASSEMBLY_INFORMATION          1
#define ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION               2
#define ACTIVATION_CONTEXT_SECTION_WINDOW_CLASS_REDIRECTION      3
#define ACTIVATION_CONTEXT_SECTION_COM_SERVER_REDIRECTION        4
#define ACTIVATION_CONTEXT_SECTION_COM_INTERFACE_REDIRECTION     5
#define ACTIVATION_CONTEXT_SECTION_COM_TYPE_LIBRARY_REDIRECTION  6
#define ACTIVATION_CONTEXT_SECTION_COM_PROGID_REDIRECTION        7
#define ACTIVATION_CONTEXT_SECTION_GLOBAL_OBJECT_RENAME_TABLE    8
#define ACTIVATION_CONTEXT_SECTION_CLR_SURROGATES                9

typedef enum _JOBOBJECTINFOCLASS
{
    JobObjectBasicaccountingInformation = 1,
    JobObjectBasicLimitInformation,
    JobObjectBasicProcessIdList,
    JobObjectBasicUIRestrictions,
    JobObjectSecurityLimitInformation,
    JobObjectEndOfJobTimeInformation,
    JobObjectAssociateCompletionPortInformation,
    JobObjectBasicandIoAccountingInformation,
    JobObjectExtendedLimitInformation,
    JobObjectJobSetInformation,
    MaxJobObjectInfoClass
} JOBOBJECTINFOCLASS;

typedef enum _LOGICAL_PROCESSOR_RELATIONSHIP
{
    RelationProcessorCore    = 0,
    RelationNumaNode         = 1,
    RelationCache            = 2,
    RelationProcessorPackage = 3,
    RelationGroup            = 4,
    RelationAll              = 0xffff
} LOGICAL_PROCESSOR_RELATIONSHIP;

typedef enum _PROCESSOR_CACHE_TYPE
{
    CacheUnified,
    CacheInstruction,
    CacheData,
    CacheTrace
} PROCESSOR_CACHE_TYPE;

typedef struct _PROCESSOR_GROUP_INFO
{
    byte MaximumProcessorCount;
    byte ActiveProcessorCount;
    byte Reserved[38];
    KAFFINITY ActiveProcessorMask;
} PROCESSOR_GROUP_INFO, *PPROCESSOR_GROUP_INFO;

typedef struct _CACHE_DESCRIPTOR
{
    byte Level;
    byte Associativity;
    ::u16 LineSize;
    ::u32 Size;
    PROCESSOR_CACHE_TYPE Type;
} CACHE_DESCRIPTOR, *PCACHE_DESCRIPTOR;

typedef struct _GROUP_AFFINITY
{
    KAFFINITY Mask;
    ::u16 Group;
    ::u16 Reserved[3];
} GROUP_AFFINITY, *PGROUP_AFFINITY;

typedef struct _PROCESSOR_RELATIONSHIP
{
    byte Flags;
    byte Reserved[21];
    ::u16 GroupCount;
    GROUP_AFFINITY GroupMask[ANYSIZE_ARRAY];
} PROCESSOR_RELATIONSHIP, *PPROCESSOR_RELATIONSHIP;


typedef struct _NUMA_NODE_RELATIONSHIP
{
    ::u32 NodeNumber;
    byte Reserved[20];
    GROUP_AFFINITY GroupMask;
} NUMA_NODE_RELATIONSHIP, *PNUMA_NODE_RELATIONSHIP;

typedef struct _CACHE_RELATIONSHIP
{
    byte Level;
    byte Associativity;
    ::u16 LineSize;
    PROCESSOR_CACHE_TYPE Type;
    byte Reserved[20];
    GROUP_AFFINITY GroupMask;
} CACHE_RELATIONSHIP, *PCACHE_RELATIONSHIP;

typedef struct _GROUP_RELATIONSHIP
{
    ::u16 MaximumGroupCount;
    ::u16 ActiveGroupCount;
    byte Reserved[20];
    PROCESSOR_GROUP_INFO GroupInfo[ANYSIZE_ARRAY];
} GROUP_RELATIONSHIP, *PGROUP_RELATIONSHIP;

typedef struct _SYSTEM_LOGICAL_PROCESSOR_INFORMATION
{
    ULONG_PTR ProcessorMask;
    LOGICAL_PROCESSOR_RELATIONSHIP Relationship;
    union
    {
        struct
        {
            byte Flags;
        } ProcessorCore;
        struct
        {
            ::u32 NodeNumber;
        } NumaNode;
        CACHE_DESCRIPTOR cache;
        ULONGLONG Reserved[2];
    } DUMMYUNIONNAME;
} SYSTEM_LOGICAL_PROCESSOR_INFORMATION, *PSYSTEM_LOGICAL_PROCESSOR_INFORMATION;

typedef struct _SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX
{
    LOGICAL_PROCESSOR_RELATIONSHIP Relationship;
    ::u32 Size;
    union
    {
        PROCESSOR_RELATIONSHIP Processor;
        NUMA_NODE_RELATIONSHIP NumaNode;
        CACHE_RELATIONSHIP Cache;
        GROUP_RELATIONSHIP Group;
    } DUMMYUNIONNAME;
} SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX, *PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX;

NTSYSAPI WINBOOLEAN NTAPI RtlGetProductInfo(::u32,::u32,::u32,::u32,PDWORD);

#ifdef __cplusplus
}
#endif

#endif // CROSS_WINDOWS_NT_H
