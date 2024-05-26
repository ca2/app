// Created by camilo on 2022-11-08 21:46 <3ThomasBorregaardSorensen!!
// From acme by camilo on 2024-05-22 11:15 <3ThomasBorregaardSorensen!!
#pragma once


// Sorensen oe


#include "ace/platform/release_time_for_project.h"


#define __RELEASE_TIME(library)  library ## _release_time
#define __DECLARE_RELEASE_TIME(library) extern "C" release_time_for_project __RELEASE_TIME(library)()
#define __DECLARE_APPLICATION_RELEASE_TIME() release_time_for_project release_time() override
#define __IMPLEMENT_APPLICATION_RELEASE_TIME(library) \
extern "C" release_time_for_project __RELEASE_TIME(library)(); \
namespace library { \
release_time_for_project  application::release_time() { return __RELEASE_TIME(library)(); } \
} // namespace library


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

#if defined(WINDOWS_DESKTOP) || defined(LINUX) || defined(MACOS) || defined(FREEBSD) || defined(OPENBSD)
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




#define __CONCAT3(xxx, yyy, zzz) xxx ## yyy ## zzz



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


#if defined(MACOS) || defined(WINDOWS_DESKTOP) || defined(LINUX) || defined(__BSD__)
#define IS_DESKTOP_SYSTEM() (true)
#else
#define IS_DESKTOP_SYSTEM() (false)
#endif



