// Created by camilo on 2022-11-08 21:46 <3ThomasBorregaardSorensen!!
#pragma once

// Sorensen oe


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



#if defined(APPLE_IOS) || defined(ANDROID) || defined(UNIVERSAL_WINDOWS)

#define MOBILE_PLATFORM 1

#else

#define MOBILE_PLATFORM 0

#endif

#if defined(WINDOWS_DESKTOP) || defined(LINUX) || defined(MACOS) || defined(FREEBSD)
#define DESKTOP_PLATFORM
#endif


#if defined(ANDROID) || defined(APPLE_IOS) || defined(UNIVERSAL_WINDOWS)
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
#ifndef __CONCAT
#define __CONCAT(xxx, yyy) xxx ## yyy
#endif

#define __CONCAT3(xxx, yyy, zzz) xxx ## yyy ## zzz


#define TOKEN_CONCATENATE_PHASE1(x, y) x ## y

#define TOKEN_CONCATENATE(x, y) TOKEN_CONCATENATE_PHASE1(x, y)



#define ___PREFIX_UNDERSCORE(prefix,name) prefix##_##name
#define __PREFIX_UNDERSCORE(prefix,name) ___PREFIX_UNDERSCORE(prefix,name)
#define __EVALUATE_MACRO(name) name


///#define lower_u8(w)              ((::u8)((w) & 0xff))









#define __CONCAT3(xxx, yyy, zzz) xxx ## yyy ## zzz


// #define __u16(a, b)                                   ((::u16)(((::u8)(((::uptr)(a)) & 0xff)) | ((::u16)((::u8)(((::uptr)(b)) & 0xff))) << 8))
// #define __u32(a, b)                                   ((::u32)(((::u16)(((::uptr)(a)) & 0xffff)) | ((::u32)((::u16)(((::uptr)(b)) & 0xffff))) << 16))


// #ifdef __cplusplus


// #define __u64(a, b)                                   (((::u64)(((::u32)(((::u64)(a)) & 0xffffffff)) | ((::u64)((::u32)(((::u64)(b)) & 0xffffffff))) << 32)))


// #else

// #define __MAKE_LONG64(a, b)                              (((u64)(((u32)(((u64)(a)) & 0xffffffff)) | ((u64)((u32)(((u64)(b)) & 0xffffffff))) << 32)))
// #define __u64(a, b)                                   (((u64)(((u32)(((u64)(a)) & 0xffffffff)) | ((u64)((u32)(((u64)(b)) & 0xffffffff))) << 32)))

// #endif

// #define lower_u16(u)                                     ((::u16)(((::uptr)(u)) & 0xffff))
// #define upper_u16(u)                                     ((::u16)((((::uptr)(u)) >> 16) & 0xffff))
// #define lower_u32(u)                                     ((::u32)(u))
// #define upper_u32(u)                                     ((::u32)(((u) >> 32) & 0xffffffff))

// #define u32_x(u)                                     ((::i16)lower_u16(u))
// #define u32_y(u)                                     ((::i16)upper_u16(u))

// #define __u32xy(u)                                    u32_x(u), u32_y(u)

// #define u64_x(u)                                     ((::i32)lower_u32(u))
// #define u64_y(u)                                     ((::i32)upper_u32(u))

// #define __u64xy(u)                                    u64_x(u), u64_y(u)


//#define GET_X_LPARAM64(lparam)                        ((i32)(i16)lower_u32(lparam))
//#define GET_Y_LPARAM64(lparam)                        ((i32)(i16)upper_u32(lparam))



#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(u)	(void)(u)
#endif



// #define make_i32(a, b)           ((::i32)(((::u16)(((::uptr)(a)) & 0xffff)) | ((::u32)((::u16)(((::uptr)(b)) & 0xffff))) << 16))

// #define __MAKE_LONG64(a, b)         ((::i64)(((::u32)(((::u64)(a)) & 0xffffffff)) | ((::u64)((::u32)(((::u64)(b)) & 0xffffffff))) << 32))

// #define make_u32(l, h)         ((::uptr)(::u32)make_i32(l, h))

//#define lower_u8(w)                 ((::u8)(((dword_ptr)(w)) & 0xff))



//
//
//#if !defined(O_BINARY) && !defined(WINDOWS)
//# define O_BINARY 0
//#endif
//



// #undef _

// #define _(str) (__get_text(str))


#define DECLARE_NEW_ACME_LIBRARY(X) extern "C" \
::acme::library* X##_new_acme_library()


#define REGISTER_GET_NEW_ACME_LIBRARY(X) register_get_new_acme_library(#X, &X##_get_new_library)




//#define gp(TYPE) ::guard_pointer < TYPE >
//

#ifdef __APPLE__
#undef err_none
#endif

#define BAD_WCHAR ((::wide_character)(-1))


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





//
//#define TRACE_FORMATTED_CATEGORY_INFORMATION(p, etracecategory, ...)    p->log_statement()(p)(e_trace_level_information )()  (e_trace_category_ ## etracecategory, __VA_ARGS__)
//#define TRACE_FORMATTED_CATEGORY_WARNING(p, etracecategory, ...)        p->log_statement()(p)(e_trace_level_warning     )()  (e_trace_category_ ## etracecategory, __VA_ARGS__)
//#define TRACE_FORMATTED_CATEGORY_ERROR(p, etracecategory, ...)          p->log_statement()(p)(e_trace_level_error       )()  (e_trace_category_ ## etracecategory, __VA_ARGS__)
//#define TRACE_FORMATTED_CATEGORY_FATAL(p, etracecategory, ...)          p->log_statement()(p)(e_trace_level_fatal       )()  (e_trace_category_ ## etracecategory, __VA_ARGS__)
//
//
//#define TRACE_CATEGORY_INFORMATION(p, etracecategory, ...)              p->log_statement()(p)(e_trace_level_information )()  (e_trace_category_ ## etracecategory) << __VA_ARGS__
//#define TRACE_CATEGORY_WARNING(p, etracecategory, ...)                  p->log_statement()(p)(e_trace_level_warning     )()  (e_trace_category_ ## etracecategory) << __VA_ARGS__
//#define TRACE_CATEGORY_ERROR(p, etracecategory, ...)                    p->log_statement()(p)(e_trace_level_error       )()  (e_trace_category_ ## etracecategory) << __VA_ARGS__
//#define TRACE_CATEGORY_FATAL(p, etracecategory, ...)                    p->log_statement()(p)(e_trace_level_fatal       )()  (e_trace_category_ ## etracecategory) << __VA_ARGS__
//
//
//#define TRACE_FORMATTED_INFORMATION(p, ...)                             p->log_statement()(p)(e_trace_level_information )()  (__VA_ARGS__)
//#define TRACE_FORMATTED_WARNING(p, ...)                                 p->log_statement()(p)(e_trace_level_warning     )()  (__VA_ARGS__)
//#define TRACE_FORMATTED_ERROR(p, ...)                                   p->log_statement()(p)(e_trace_level_error       )()  (__VA_ARGS__)
//#define TRACE_FORMATTED_FATAL(p, ...)                                   p->log_statement()(p)(e_trace_level_fatal       )()  (__VA_ARGS__)
//
//
//#define TRACE_INFORMATION(p, ...)                                       p->log_statement()(p)(e_trace_level_information )()  << __VA_ARGS__
//#define TRACE_WARNING(p, ...)                                           p->log_statement()(p)(e_trace_level_warning     )()  << __VA_ARGS__
//#define TRACE_ERROR(p, ...)                                             p->log_statement()(p)(e_trace_level_error       )()  << __VA_ARGS__
//#define TRACE_FATAL(p, ...)                                             p->log_statement()(p)(e_trace_level_fatal       )()  << __VA_ARGS__
//
//
//#define FORMATTED_CATEGORY_INFORMATION(etracecategory, ...)             log_statement()(trace_this())(e_trace_level_information )()   (e_trace_category_ ## etracecategory, __VA_ARGS__)
//#define FORMATTED_CATEGORY_WARNING(etracecategory, ...)                 log_statement()(trace_this())(e_trace_level_warning     )()   (e_trace_category_ ## etracecategory, __VA_ARGS__)
//#define FORMATTED_CATEGORY_ERROR(etracecategory, ...)                   log_statement()(trace_this())(e_trace_level_error       )()   (e_trace_category_ ## etracecategory, __VA_ARGS__)
//#define FORMATTED_CATEGORY_FATAL(etracecategory, ...)                   log_statement()(trace_this())(e_trace_level_fatal       )()   (e_trace_category_ ## etracecategory, __VA_ARGS__)
//
//
//#define CATEGORY_INFORMATION(etracecategory, ...)                       log_statement()(trace_this())(e_trace_level_information )()  (e_trace_category_ ## etracecategory) << __VA_ARGS__
//#define CATEGORY_WARNING(etracecategory, ...)                           log_statement()(trace_this())(e_trace_level_warning     )()  (e_trace_category_ ## etracecategory) << __VA_ARGS__
//#define CATEGORY_ERROR(etracecategory, ...)                             log_statement()(trace_this())(e_trace_level_error       )()  (e_trace_category_ ## etracecategory) << __VA_ARGS__
//#define CATEGORY_FATAL(etracecategory, ...)                             log_statement()(trace_this())(e_trace_level_fatal       )()  (e_trace_category_ ## etracecategory) << __VA_ARGS__
//
//
//#define LOG_FORMATTED_INFORMATION(...)                                  log_statement()(trace_this())(e_trace_level_information )() (__VA_ARGS__)
//#define LOG_FORMATTED_WARNING(...)                                      log_statement()(trace_this())(e_trace_level_warning     )() (__VA_ARGS__)
//#define LOG_FORMATTED_ERROR(...)                                        log_statement()(trace_this())(e_trace_level_error       )() (__VA_ARGS__)
//#define LOG_FORMATTED_FATAL(...)                                        log_statement()(trace_this())(e_trace_level_fatal       )() (__VA_ARGS__)
//
//
//#define LOG_INFORMATION(...)                                            log_statement()(trace_this())(e_trace_level_information )() << e_start_reference << __VA_ARGS__
//#define LOG_WARNING(...)                                                log_statement()(trace_this())(e_trace_level_warning     )() << e_start_reference << __VA_ARGS__
//#define LOG_ERROR(...)                                                  log_statement()(trace_this())(e_trace_level_error       )() << e_start_reference << __VA_ARGS__
//#define LOG_FATAL(...)                                                  log_statement()(trace_this())(e_trace_level_fatal       )() << e_start_reference << __VA_ARGS__
//
//
//#define information(...)                                      LOG_FORMATTED_INFORMATION(__VA_ARGS__)
//#define warning(...)                                          LOG_FORMATTED_WARNING(__VA_ARGS__)
//#define error(...)                                            LOG_FORMATTED_ERROR(__VA_ARGS__)
//#define fatal(...)                                            LOG_FORMATTED_FATAL(__VA_ARGS__)
//
//
//#define log_information((...)                                                LOG_INFORMATION(__VA_ARGS__)
//#define log_warning(...)                                                    LOG_WARNING(__VA_ARGS__)
//#define log_error(...)                                                      LOG_ERROR(__VA_ARGS__)
//#define log_fatal(...)                                                      LOG_FATAL(__VA_ARGS__)
//
//
////#define log_information((...) trace_object(ALOG_CONTEXT)->__alog(e_trace_level_information   , ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)
////#define WARN(...) trace_object(ALOG_CONTEXT)->__alog(e_trace_level_warning       , ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)
////#define ERR(...) trace_object(ALOG_CONTEXT)->__alog(e_trace_level_error         , ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)
////#define log_fatal(...) trace_object(ALOG_CONTEXT)->__alog(e_trace_level_fatal         , ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)
//
//
//#define information(...)                                            information(__VA_ARGS__)
//#define information(...)                                                      log_information((__VA_ARGS__)
//

//#define LOG_INFORMATION    log_information()()
//#define LOG_WARNING        log_warning()()
//#define LOG_ERROR          log_error()()
//#define LOG_FATAL          log_fatal()()
//
//
//#define INFORMATION        LOG_INFORMATION
//#define WARNING            LOG_WARNING
//#define ERROR              LOG_ERROR
//#define FATAL              LOG_FATAL

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


//#define TOKENPASTE_PROCESS(x, y) x ## y
//#define TOKEN_CONCATENATE(x, y) TOKENPASTE_PROCESS(x, y)
#define COUNTER_TOKEN(token) TOKEN_CONCATENATE(token, __COUNTER__)


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



// #ifndef i32_x
// #define i32_x(lparam)                          ((i32)(i16)LOWORD(lparam))
// #endif


// #ifndef i32_y
// #define i32_y(lparam)                          ((i32)(i16)HIWORD(lparam))
// #endif


// #ifndef lower_u32
// #define lower_u32(l)                                    ((::u32)(((::u64)(l)) & 0xffffffffu))
// #endif
// #ifndef upper_u32
// #define upper_u32(l)                                    ((::u32)((((::u64)(l)) >> 32) & 0xffffffffu))
// #endif


////https://www.artima.com/articles/the-safe-bool-idiom BEGIN
//#define SAFE_BOOL_OPERATOR(type) \
//typedef void (type:: * bool_type)() const; \
//constexpr void this_type_does_not_support_comparisons() const {} \
//constexpr operator bool_type() const { return this->is_set() ? &type::this_type_does_not_support_comparisons : 0; }
////https://www.artima.com/articles/the-safe-bool-idiom END


#define DECLARE_FACTORY(name) \
__FACTORY_IMPORT void TOKEN_CONCATENATE(name, _factory)(::factory::factory * pfactory)


#define IMPLEMENT_FACTORY(name) \
__FACTORY_EXPORT void TOKEN_CONCATENATE(name, _factory)(::factory::factory * pfactory)



