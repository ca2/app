// Created by camilo on 2022-11-08 21:46 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/object_reference_count_debug.h"


#define ALOG_CONTEXT context_trace_object()

#define _S_ALOG_CONTEXT ::context_trace_object()


#ifdef WINDOWS_DESKTOP


#if defined _M_IX86
#define _ACME_LINKER_SYMBOL_PREFIX "_"
#elif defined _M_X64 || defined _M_ARM || defined _M_ARM64
#define _ACME_LINKER_SYMBOL_PREFIX ""
#else
#error Unsupported architecture
#endif


#endif



#if defined(APPLE_IOS) || defined(ANDROID) || defined(_UWP)

#define MOBILE_PLATFORM 1

#else

#define MOBILE_PLATFORM 0

#endif

#if defined(WINDOWS_DESKTOP) || defined(LINUX) || defined(MACOS) || defined(FREEBSD)
#define DESKTOP_PLATFORM
#endif


#if defined(ANDROID) || defined(APPLE_IOS) || defined(_UWP)
#define SANDBOXED_PLATFORM
#endif


#define _STRINGFY(identifier) #identifier
#define STRINGFY(identifier) _STRINGFY(identifier)
#define STRING_PREFIX_LAYER_NAMESPACE(str) STRINGFY(LAYER_NAMESPACE) str

#define PLATFORM_INCLUDE(include) STRINGFY(__IDENTIFIER(OPERATING_SYSTEM_NAMESPACE)/include)

#ifndef  __STRING
#  define   __STRING(x) "x"
#endif


#define __EVALUATE(xxx) xxx
#define __CONCAT(xxx, yyy) xxx ## yyy

#define __CONCAT3(xxx, yyy, zzz) xxx ## yyy ## zzz





#define ___PREFIX_UNDERSCORE(prefix,name) prefix##_##name
#define __PREFIX_UNDERSCORE(prefix,name) ___PREFIX_UNDERSCORE(prefix,name)
#define __EVALUATE_MACRO(name) name


#define low_byte(w)              ((byte)((w) & 0xff))






#define colorref_get_r_value(rgb)    (low_byte(rgb))
#define colorref_get_g_value(rgb)    (low_byte((rgb)>>8))
#define colorref_get_b_value(rgb)    (low_byte((rgb)>>16))
#define colorref_get_a_value(rgb)    (low_byte((rgb)>>24))



#define __CONCAT3(xxx, yyy, zzz) xxx ## yyy ## zzz


#define __u16(a, b)                                   ((::u16)(((::u8)(((::uptr)(a)) & 0xff)) | ((::u16)((::u8)(((::uptr)(b)) & 0xff))) << 8))
#define __u32(a, b)                                   ((::u32)(((::u16)(((::uptr)(a)) & 0xffff)) | ((::u32)((::u16)(((::uptr)(b)) & 0xffff))) << 16))


#ifdef __cplusplus


#define __u64(a, b)                                   (((::u64)(((::u32)(((::u64)(a)) & 0xffffffff)) | ((::u64)((::u32)(((::u64)(b)) & 0xffffffff))) << 32)))


#else

#define __MAKE_LONG64(a, b)                              (((u64)(((u32)(((u64)(a)) & 0xffffffff)) | ((u64)((u32)(((u64)(b)) & 0xffffffff))) << 32)))
#define __u64(a, b)                                   (((u64)(((u32)(((u64)(a)) & 0xffffffff)) | ((u64)((u32)(((u64)(b)) & 0xffffffff))) << 32)))

#endif

#define __lo16(u)                                     ((::u16)(((::uptr)(u)) & 0xffff))
#define __hi16(u)                                     ((::u16)((((::uptr)(u)) >> 16) & 0xffff))
#define __lo32(u)                                     ((::u32)(u))
#define __hi32(u)                                     ((::u32)(((u) >> 32) & 0xffffffff))

#define __u32x(u)                                     ((::i16)__lo16(u))
#define __u32y(u)                                     ((::i16)__hi16(u))

#define __u32xy(u)                                    __u32x(u), __u32y(u)

#define __u64x(u)                                     ((::i32)__lo32(u))
#define __u64y(u)                                     ((::i32)__hi32(u))

#define __u64xy(u)                                    __u64x(u), __u64y(u)


#define GET_X_LPARAM64(lparam)                        ((i32)(i16)LODWORD(lparam))
#define GET_Y_LPARAM64(lparam)                        ((i32)(i16)HIDWORD(lparam))




#define __UNREFERENCED_PARAMETER(u)	(void)(u)



#define __MAKE_LONG(a, b)           ((::i32)(((::u16)(((::uptr)(a)) & 0xffff)) | ((::u32)((::u16)(((::uptr)(b)) & 0xffff))) << 16))

#define __MAKE_LONG64(a, b)         ((::i64)(((::u32)(((::u64)(a)) & 0xffffffff)) | ((::u64)((::u32)(((::u64)(b)) & 0xffffffff))) << 32))

#define __MAKE_LPARAM(l, h)         ((::uptr)(::u32)__MAKE_LONG(l, h))

#define __LOBYTE(w)                 ((byte)(((dword_ptr)(w)) & 0xff))



//
//
//#if !defined(O_BINARY) && !defined(WINDOWS)
//# define O_BINARY 0
//#endif
//



#undef _

#define _(str) (__get_text(str))


#define DECLARE_NEW_ACME_LIBRARY(X) extern "C" \
::acme::library* X##_new_acme_library()


#define REGISTER_GET_NEW_ACME_LIBRARY(X) register_get_new_acme_library(#X, &X##_get_new_library)




//#define gp(TYPE) ::guard_pointer < TYPE >
//

#ifdef __APPLE__
#undef err_none
#endif

#define BAD_WCHAR ((widechar)(-1))


#define ARRAY_SIZE(a) (sizeof(a)/sizeof(*(a)))



// return - result - if not ok
#ifndef RINOK
#define RINOK(x) { i32 __result__ = (x); if (__result__ != 0) return __result__; }
#endif

// throw ::exception( - exception - result exception - if not ok
#ifndef TINOK
#define TINOK(e, x) { i32 __result__ = (x); if (__result__ != 0) throw ::exception(e(get_app(), __result__)); }
#endif


#define SECOND_NANOS 1'000'000'000






#define _FORMATTED_CATEGORY_INFORMATION(p, etracecategory, ...)   p->trace_log_information   (e_trace_category_ ## etracecategory, __VA_ARGS__)
#define _FORMATTED_CATEGORY_WARNING(p, etracecategory, ...)   p->trace_log_warning       (e_trace_category_ ## etracecategory, __VA_ARGS__)
#define _FORMATTED_CATEGORY_ERROR(p, etracecategory, ...)   p->trace_log_error         (e_trace_category_ ## etracecategory, __VA_ARGS__)
#define _FORMATTED_CATEGORY_FATAL(p, etracecategory, ...)   p->trace_log_fatal         (e_trace_category_ ## etracecategory, __VA_ARGS__)


#define _CATEGORY_INFORMATION(p, etracecategory, ...)   p->trace_log_information   (e_trace_category_ ## etracecategory) << __VA_ARGS__
#define _CATEGORY_WARNING(p, etracecategory, ...)   p->trace_log_warning       (e_trace_category_ ## etracecategory) << __VA_ARGS__
#define _CATEGORY_ERROR(p, etracecategory, ...)   p->trace_log_error         (e_trace_category_ ## etracecategory) << __VA_ARGS__
#define _CATEGORY_FATAL(p, etracecategory, ...)   p->trace_log_fatal         (e_trace_category_ ## etracecategory) << __VA_ARGS__


#define FORMATTED_CATEGORY_INFORMATION(etracecategory, ...)      trace_log_information            (e_trace_category_ ## etracecategory, __VA_ARGS__)
#define FORMATTED_CATEGORY_WARNING(etracecategory, ...)      trace_log_warning                (e_trace_category_ ## etracecategory, __VA_ARGS__)
#define FORMATTED_CATEGORY_ERROR(etracecategory, ...)      trace_log_error                  (e_trace_category_ ## etracecategory, __VA_ARGS__)
#define FORMATTED_CATEGORY_FATAL(etracecategory, ...)      trace_log_fatal                  (e_trace_category_ ## etracecategory, __VA_ARGS__)


#define CATEGORY_INFORMATION(etracecategory, ...)      trace_log_information            (e_trace_category_ ## etracecategory) << __VA_ARGS__
#define CATEGORY_WARNING(etracecategory, ...)      trace_log_warning                (e_trace_category_ ## etracecategory) << __VA_ARGS__
#define CATEGORY_ERROR(etracecategory, ...)      trace_log_error                  (e_trace_category_ ## etracecategory) << __VA_ARGS__
#define CATEGORY_FATAL(etracecategory, ...)      trace_log_fatal                  (e_trace_category_ ## etracecategory) << __VA_ARGS__


#define _FORMATTED_INFORMATION(p, ...)                   p->trace_log_information         (__VA_ARGS__)
#define _FORMATTED_WARNING(p, ...)                   p->trace_log_warning             (__VA_ARGS__)
#define _FORMATTED_ERROR(p, ...)                   p->trace_log_error               (__VA_ARGS__)
#define _FORMATTED_FATAL(p, ...)                   p->trace_log_fatal               (__VA_ARGS__)


#define _INFORMATION(p, ...)                   p->trace_log_information         () << __VA_ARGS__
#define _WARNING(p, ...)                   p->trace_log_warning             () << __VA_ARGS__
#define _ERROR(p, ...)                   p->trace_log_error               () << __VA_ARGS__
#define _FATAL(p, ...)                   p->trace_log_fatal               () << __VA_ARGS__


#define TRACE_LOG_FORMATTED_INFORMATION(...)                      trace_log_information            (__VA_ARGS__)
#define TRACE_LOG_FORMATTED_WARNING(...)                      trace_log_warning                (__VA_ARGS__)
#define TRACE_LOG_FORMATTED_ERROR(...)                      trace_log_error                  (__VA_ARGS__)
#define TRACE_LOG_FORMATTED_FATAL(...)                      trace_log_fatal                  (__VA_ARGS__)


#define TRACE_LOG_INFORMATION(...)                      trace_log_information            () << __VA_ARGS__
#define TRACE_LOG_WARNING(...)                      trace_log_warning                () << __VA_ARGS__
#define TRACE_LOG_ERROR(...)                      trace_log_error                  () << __VA_ARGS__
#define TRACE_LOG_FATAL(...)                      trace_log_fatal                  () << __VA_ARGS__


#define FORMATTED_INFORMATION(...)                      TRACE_LOG_FORMATTED_INFORMATION(__VA_ARGS__)
#define FORMATTED_WARNING(...)                      TRACE_LOG_FORMATTED_WARNING(__VA_ARGS__)
#define FORMATTED_ERROR(...)                      TRACE_LOG_FORMATTED_ERROR(__VA_ARGS__)
#define FORMATTED_FATAL(...)                      TRACE_LOG_FORMATTED_FATAL(__VA_ARGS__)


#define INFORMATION(...)               TRACE_LOG_INFORMATION(__VA_ARGS__)
#define WARNING(...)                   TRACE_LOG_WARNING(__VA_ARGS__)
#define ERROR(...)                     TRACE_LOG_ERROR(__VA_ARGS__)
#define FATAL(...)                     TRACE_LOG_FATAL(__VA_ARGS__)


//#define INFORMATION(...) trace_object(ALOG_CONTEXT)->__alog(e_trace_level_information   , ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)
//#define WARN(...) trace_object(ALOG_CONTEXT)->__alog(e_trace_level_warning       , ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)
//#define ERR(...) trace_object(ALOG_CONTEXT)->__alog(e_trace_level_error         , ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)
//#define FATAL(...) trace_object(ALOG_CONTEXT)->__alog(e_trace_level_fatal         , ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)


#define FORMATTED_TRACE(...)              FORMATTED_INFORMATION(__VA_ARGS__)
#define TRACE(...)                        INFORMATION(__VA_ARGS__)






#ifdef _WIN32


#define LONG_IS_32BIT 1
#define LONG_IS_64BIT 0


#else


#if OSBIT == 64


#define LONG_IS_32BIT 0
#define LONG_IS_64BIT 1


#else


#define LONG_IS_32BIT 1
#define LONG_IS_64BIT 0


#endif


#endif


#if OSBIT == 64

#define PRI0xPTR  "016" PRIxPTR

#else

#define PRI0xPTR  "08" PRIxPTR

#endif



#define IMPL_OPERATOR_PLUS(type) \
template < typename TYPE > \
type operator + (const TYPE & t) const { auto copy = *this; copy.add(t); return copy; }


#define TOKENPASTE_PROCESS(x, y) x ## y
#define TOKENPASTE(x, y) TOKENPASTE_PROCESS(x, y)
#define TOKEN_AT_LINE(token) TOKENPASTE(TOKENPASTE(token, _atLine_), __LINE__)


#define __DEBUG_POWER


#if defined(__cplusplus)

#define DECL_EXTERN_C      extern "C"
#define BEGIN_EXTERN_C      extern "C" {
#define END_EXTERN_C         }

#else

#define DECL_EXTERN_C
#define BEGIN_EXTERN_C
#define END_EXTERN_C

#endif



#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lparam)                          ((i32)(i16)LOWORD(lparam))
#endif


#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lparam)                          ((i32)(i16)HIWORD(lparam))
#endif
