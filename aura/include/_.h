/////////////////////////////////////////////////////////////////////////////////////////
//
//  ca2
//
//  ca2 is an all-purpose multi-platform framework and set of libraries written in
//  C++ language with the aim to help developers create awesome apps for users.
//
//  ca2/./aura/C++/C/Assembly/Hardware/Universe/Multiverse stack
//
//
//
//
//  c(s)t(s)<tb(s)!!
//
#pragma once

#undef LAYER_NAMESPACE
#define LAYER_NAMESPACE aura


//#undef ::auraacmesystem()
//#undef Node
//#undef Sess
//#undef App
//
//
//#define ::auraacmesystem() (psystem->m_paurasystem)
//#define Node (psystem->m_pnode ? psystem->m_pnode->m_pauranode : nullptr)
//#define Sess(pcontextsession) (pcontextsession->m_paurasession)
//#define App(playered) (*::get_app(playered)->m_pauraapplication)


namespace acme_posix { class node; }
namespace apex_posix { class node; }
namespace aura_posix { class node; }


#define __spin_namespace aura // back bone / four-letter "spin*" namespace name


namespace aura
{


   class system;
   class session;
   class application;
   class node;


//   inline system * acmesystem() { return acmesystem()->layer(LAYERED_AURA); }


} // namespace aura


#if defined UNIVERSAL_WINDOWS


namespace aura_universal_windows
{


   //ref class directx_framework_impact;
   //ref class directx_application_source;
   class interaction_impl;


} // namespace universal_windows


#endif


namespace IDENTIFIER_SUFFIX_OPERATING_SYSTEM(aura_)
{


   class interaction_impl;


} // namespace IDENTIFIER_SUFFIX_OPERATING_SYSTEM(aura_)



#include "aura/hardware/_.h"


#include "aura/graphics/_.h"


#include "aura/game/_.h"


#include "aura/gpu/_.h"


#include "aura/user/_.h"


#include "aura/message/_.h"


#include "aura/windowing/_.h"


#include "aura/filesystem/_.h"


#include "aura/platform/_.h"


//
//
////#include "aura/primitive/primitive/estatus.h"
////
////
////#include <tuple>
////
////
//CLASS_DECL_AURA void aura_ref();
////
////
////#ifdef WINDOWS_DESKTOP
////
////typedef i32 WINAPI __MAIN_DEFERRED_RUN(HINSTANCE hinstance, HINSTANCE hPrevInstance, char * pCmdLine, i32 nCmdShow);
////
////#else
////
////typedef i32 __MAIN_DEFERRED_RUN(int argc, char ** argv);
////
////#endif
////
////
////typedef __MAIN_DEFERRED_RUN * __LPFN_MAIN_DEFERRED_RUN;
////extern CLASS_DECL_AURA __LPFN_MAIN_DEFERRED_RUN __main_deferred_run;
////
////
////#ifdef __DEBUG
////
////#define INLINE
////
////#else
////
////#define INLINE inline
////
////#endif
////
////
//////#include "aura/platform/cpu_architecture.h"
////
////
//////#include "aura/message/global.h"
////
////
//////#include "aura/exception/_c.h"
////
////
////#ifdef WINDOWS_DESKTOP
////
////
////#if defined _M_IX86
////#define _AURA_LINKER_SYMBOL_PREFIX "_"
////#elif defined _M_X64 || defined _M_ARM || defined _M_ARM64
////#define _AURA_LINKER_SYMBOL_PREFIX ""
////#else
////#error Unsupported architecture
////#endif
////
////
////#endif
////
////
////#if defined(APPLE_IOS) || defined(ANDROID) || defined(UNIVERSAL_WINDOWS)
////
////#define MOBILE_PLATFORM 1
////
////#else
////
////#define MOBILE_PLATFORM 0
////
////#endif
////
////
////#ifndef WINDOWS
////
////
////#define _CRT_ASSERT 0
////
////
////#endif
////
////
////#if defined(DEBUG) && !defined(NO_AURA_MEMORY_MANAGEMENT)
////#define ACME_NEW memory_new(__FILE__, __LINE__)
////#else
////#define ACME_NEW memory_new
////#endif
////
//////#define memory_new ACME_NEW
////
////
////#include "aura/platform/object_reference_count_debug.h"
////
////
////namespace opengl
////{
////
////
////   class opengl;
////
////
////} // namespace opengl
////
////
////struct ::i32_sz
////{
////
////   int            m_i;
////   const char* m_psz;
////
////};
////
////
////
////CLASS_DECL_AURA void throw_todo(void);
////
////
//////CLASS_DECL_AURA void set_last_status(const ::e_status & estatus);
//////CLASS_DECL_AURA void windowing_output_debug_string(const ::string & pszDebugString);
//////CLASS_DECL_AURA void c_function_call(void * p);
//////extern CLASS_DECL_AURA int g_bAura;
//////CLASS_DECL_AURA int __assert_failed_line(const ::string & pszFileName,int iLineNumber);
//////CLASS_DECL_AURA int is_debugger_attached(void);
//////CLASS_DECL_AURA void debug_print(const ::string & psz,...);
//////
//////
//////CLASS_DECL_AURA int throw_assert_exception(const ::string & pszFileName,int iLineNumber);
//////CLASS_DECL_AURA void throw_what_exclamation_exclamation(const ::string & psz);
//////
////
////
////#ifndef __cplusplus
////
////
////#define ASSERT assert
////
////
////#else
////
////
////#ifdef __DEBUG
////
////
////#define ASSERT(f)          ((void) ((f) || (is_debugger_attached() && !::__assert_failed_line(__FILE__, __LINE__) && (::debug_break(), 0)) || (!is_debugger_attached() && (throw_assert_exception(__FILE__, __LINE__), 0))))
////#define _ASSUME(cond)       do { bool _gen__condVal=!!(cond); ASSERT(_gen__condVal); __analysis_assume(_gen__condVal); } while(0)
////#define ASSERT_VALID(pOb)  ::__assert_particle_ok(pOb, __FILE__, __LINE__)
////
////
////#else
////
////
////#define ASSERT(f)
////#define _ASSUME(cond)
////#if defined(ANDROID)
////#define ASSERT_VALID(cond)
////#elif defined(__APPLE__)
////#define ASSERT_VALID(cond)
////#elif defined(LINUX)
////#define ASSERT_VALID(cond)
////#else
////#define ASSERT_VALID(cond) __noop;
////#endif
////#endif
////
////
////#endif
////
////
////#define low_byte(w)              ((byte)((w) & 0xff))
////
////
////#if defined(WINDOWS) || defined(LINUX) || defined(__i386__)
////
////
////#define IMAGE_A_BYTE_INDEX 3
////#define IMAGE_R_BYTE_INDEX 2
////#define IMAGE_G_BYTE_INDEX 1
////#define IMAGE_B_BYTE_INDEX 0
////
////
////#define IMAGE_ARGB(a, r, g, b)         ((::color::color)((low_byte(b)|((::u16)(low_byte(g))<<8))|(((u32)low_byte(r))<<16)|(((u32)low_byte(a))<<24)))
////
////
////#define image_r_value(rgb)    (low_byte((rgb)>>16))
////#define image_g_value(rgb)    (low_byte((rgb)>>8))
////#define image_b_value(rgb)    (low_byte((rgb)))
////#define image_a_value(rgb)    (low_byte((rgb)>>24))
////
////
////#else
////
////
////#define IMAGE_A_BYTE_INDEX 3
////#define IMAGE_R_BYTE_INDEX 0
////#define IMAGE_G_BYTE_INDEX 1
////#define IMAGE_B_BYTE_INDEX 2
////
////
////#define IMAGE_ARGB(a, r, g, b)         ((::color::color)((low_byte(r)|((::u16)(low_byte(g))<<8))|(((u32)low_byte(b))<<16)|(((u32)low_byte(a))<<24)))
////
////
////#define image_r_value(rgb)    (low_byte((rgb)))
////#define image_g_value(rgb)    (low_byte((rgb)>>8))
////#define image_b_value(rgb)    (low_byte((rgb)>>16))
////#define image_a_value(rgb)    (low_byte((rgb)>>24))
////
////
////#endif
////
////
////#define __CONCAT3(xxx, yyy, zzz) xxx ## yyy ## zzz
////
////
////#define colorref_get_r_value(rgb)    (low_byte(rgb))
////#define colorref_get_g_value(rgb)    (low_byte((rgb)>>8))
////#define colorref_get_b_value(rgb)    (low_byte((rgb)>>16))
////#define colorref_get_a_value(rgb)    (low_byte((rgb)>>24))
////#define RGBA(r, g, b, a)         ((::color::color)((low_byte(r)|((::u16)(low_byte(g))<<8))|(((u32)low_byte(b))<<16)|(((u32)low_byte(a))<<24)))
////#define argb(a, r, g, b)      RGBA(r, g, b, a)
////
////
////#define ::color::color(a, r, g, b)      ::color::color(r, g, b, a)
////
////
////inline int trailingBytesForUTF8(char ch);
////
////
////extern CLASS_DECL_AURA const char g_trailingBytesForUTF8[256];
////
////
////inline int trailingBytesForUTF8(char ch)
////{
////
////   return ::g_trailingBytesForUTF8[(byte)ch];
////
////}
////
////
////CLASS_DECL_AURA int is_ptr_null(const void * p, size_t s);
////
////
////inline CLASS_DECL_AURA int c_is_null(const void * p)
////{
////   return ((uptr)p) < 65536;
////
////}
////
////
////
////#define void_ptr_is_null(p) (((uptr)(void *) p) < 4096)
////
////namespace dynamic_source
////{
////
////
////   class script_interface;
////
////
////} // namespace dynamic_source
////
////
//////#include "aura/primitive/math/mkint_c.h"
////
////// C-includes
////#include "aura/os/_c.h"
//////#include "aura/memory/heap_c.h"
////
////
////
////#undef minimum
////#undef maximum
////
////
////#define INTABS(i) (((i) >= 0) ? (i) : (-i))
////#define FLOATABS(f) (((f) >= 0.f) ? (f) : (-f))
////#define DOUBLEABS(d) (((d) >= 0.0) ? (d) : (-d))
////
////
//////#ifdef __cplusplus
//////#define maximum(a, b) (((b) < (a)) ? (a) : (b))
//////#define minimum(a, b) (((a) < (b)) ? (a) : (b))
//////#include "aura/primitive/comparison/_c.h"
//////#else
//////#define maximum(a, b) (((a) > (b)) ? (a) : (b))
//////#define minimum(a, b) (((a) < (b)) ? (a) : (b))
//////#endif
////
////
////#define LIM(a, minimum, maximum) minimum(maximum, maximum(minimum, a))
////#define SORT_LIM(x,minmax,maxmin) ((minmax) < (maxmin) ? LIM(x,minmax,maxmin) : LIM(x,maxmin,minmax))
////#define CLIP_USHRT(x) LIM(x,0,USHRT_MAX)
////
////
////
////
////#ifdef WINDOWS
////#include <intsafe.h>
////#else
////
////#ifndef LODWORD
////#define LODWORD(l)                                    ((::u32)(((::u64)(l)) & 0xffffffff))
////#endif
////#ifndef HIDWORD
////#define HIDWORD(l)                                    ((::u32)((((::u64)(l)) >> 32) & 0xffffffff))
////#endif
////
////#endif
////
////
////
////
////#define __u16(a, b)                                   ((::u16)(((::u8)(((::uptr)(a)) & 0xff)) | ((::u16)((::u8)(((::uptr)(b)) & 0xff))) << 8))
////#define __u32(a, b)                                   ((::u32)(((::u16)(((::uptr)(a)) & 0xffff)) | ((::u32)((::u16)(((::uptr)(b)) & 0xffff))) << 16))
////
////
////#ifdef __cplusplus
////
////#define __MAKE_LONG64(a, b)                              (((::u64)(((::u32)(((::u64)(a)) & 0xffffffff)) | ((::u64)((::u32)(((::u64)(b)) & 0xffffffff))) << 32)))
////#define __u64(a, b)                                   (((::u64)(((::u32)(((::u64)(a)) & 0xffffffff)) | ((::u64)((::u32)(((::u64)(b)) & 0xffffffff))) << 32)))
////
////#else
////
////#define __MAKE_LONG64(a, b)                              (((u64)(((u32)(((u64)(a)) & 0xffffffff)) | ((u64)((u32)(((u64)(b)) & 0xffffffff))) << 32)))
////#define __u64(a, b)                                   (((u64)(((u32)(((u64)(a)) & 0xffffffff)) | ((u64)((u32)(((u64)(b)) & 0xffffffff))) << 32)))
////
////#endif
////
////#define __lo16(u)                                     ((::u16)(((::uptr)(u)) & 0xffff))
////#define __hi16(u)                                     ((::u16)((((::uptr)(u)) >> 16) & 0xffff))
////#define __lo32(u)                                     ((::u32)(u))
////#define __hi32(u)                                     ((::u32)(((u) >> 32) & 0xffffffff))
////
////#define __u32x(u)                                     ((::i16)__lo16(u))
////#define __u32y(u)                                     ((::i16)__hi16(u))
////
////#define __u32xy(u)                                    __u32x(u), __u32y(u)
////
////#define __u64x(u)                                     ((::i32)__lo32(u))
////#define __u64y(u)                                     ((::i32)__hi32(u))
////
////#define __u64xy(u)                                    __u64x(u), __u64y(u)
////
////
////#ifndef GET_X_LPARAM
////#define GET_X_LPARAM(lparam)                          ((i32)(i16)LOWORD(lparam))
////#endif
////
////
////#ifndef GET_Y_LPARAM
////#define GET_Y_LPARAM(lparam)                          ((i32)(i16)HIWORD(lparam))
////#endif
////
////#define GET_X_LPARAM64(lparam)                        ((i32)(i16)LODWORD(lparam))
////#define GET_Y_LPARAM64(lparam)                        ((i32)(i16)HIDWORD(lparam))
////
////
//////CLASS_DECL_AURA int get_aura_init();
////
//////extern "C"
//////CLASS_DECL_AURA int_bool defer_aura_init();
////
//////extern "C"
//////CLASS_DECL_AURA int_bool defer_aura_term();
////
////
////
////
////typedef struct rdp_freerdp freerdp;
////
////
////CLASS_DECL_AURA int_bool freerdp_authenticate(void * instance, char** username,char** password,char** domain, const ::string & pszServerName, int bInteractive);
////
////
////#if !defined(O_BINARY) && !defined(WINDOWS)
////# define O_BINARY 0
////#endif
////
////
////CLASS_DECL_AURA i32     ansi_open(const ::string & psz,i32 i);
////CLASS_DECL_AURA FILE *  ansi_fopen(const ::string & psz, const ::string & pszMode);
////CLASS_DECL_AURA int     ansi_file_flag(int iFlag);
////CLASS_DECL_AURA void    ansi_get_errno(i32 * perrno);
////CLASS_DECL_AURA void    ansi_unlink(const ::string & psz);
////
////
////CLASS_DECL_AURA ::u32 get_last_error();
////CLASS_DECL_AURA void set_last_error(::u32 dw);
////
////typedef char ::ansi_character;
////
////i32 CLASS_DECL_AURA MultiByteToWideChar2(::u32 CodePage, ::u32 dwFlags, const ::ansi_character * pMultByteStr, i32 cbMultiByte, ::wide_character * pWideCharStr, i32 cchWideChar);
////i32 CLASS_DECL_AURA WideCharToMultiByte2(::u32 CodePage, ::u32 dwFlags, const ::wide_character * pWideCharStr, i32 cchWideChar, ::ansi_character * pMultByteStr, i32 cbMultiByte, const ::string & pDefaultChar, int_bool * pUsedDefaultChar);
////
////
////enum e_image_type
////{
////
////   image_type_complex,
////   image_type_plain_color
////
////};
////
////
////
////
////
//////#include "aura/primitive/primitive/_c_memory.h"
////
//////#include "aura/primitive/string/_c.h"
////
//////#include "aura/primitive/datetime/_c.h"
////
//////#include "aura/filesystem/file/_c.h"
////
////#include "aura/const/thread.h"
////
////
////
////
////
////#if !defined(__APPLE__) && !defined(LINUX) && !defined(ANDROID)
////
////int ftruncate(int file, filesize len);
////
////#endif
////
////
////CLASS_DECL_AURA i32 get_os_thread_priority(::enum_priority epriority);
////CLASS_DECL_AURA i32 get_os_priority_class(::enum_priority epriority);
////CLASS_DECL_AURA ::enum_priority get_os_thread_scheduling_priority(i32 iCa2Priority);
////CLASS_DECL_AURA ::enum_priority get_os_class_scheduling_priority(i32 iCa2Priority);
////
////
////
//////#include "aura/primitive/datetime/mktime.h"
//////#include "aura/primitive/api/api.h"
////
////
////#include "aura/multimedia/_c.h"
////
////
////class matter;
////
////
////template < typename T >
////void __finalize_and_release(T& p)
////{
////
////   if (p)
////   {
////
////      p->destroy();
////
////      p.release();
////
////   }
////
////}
////
////
////CLASS_DECL_AURA extern u32 g_tickStartTime;
////
////#define ALOG_CONTEXT context_trace_object()
////
////#define _S_ALOG_CONTEXT ::context_trace_object()
////
////
////
////CLASS_DECL_AURA ::matter * general_trace_object();
////
////CLASS_DECL_AURA int_bool c_enable_trace_category(e_trace_category ecategory, int_bool iEnable);
////
////inline ::matter * context_trace_object() { return general_trace_object(); }
////
////
////CLASS_DECL_AURA void __tracea(::particle * pparticle, enum_trace_level elevel, const ::string & pszFunction, const ::string & pszFile, int iLine, const ::string & psz);
////CLASS_DECL_AURA void __tracef(::particle * pparticle, enum_trace_level elevel, const ::string & pszFunction, const ::string & pszFile, int iLine, const ::string & psz, ...);
////CLASS_DECL_AURA void __tracev(::particle * pparticle, enum_trace_level elevel, const ::string & pszFunction, const ::string & pszFile, int iLine, const ::string & psz, va_list vargs);
////CLASS_DECL_AURA const char * trace_category_name(e_trace_category ecategory);
////
////
////CLASS_DECL_AURA ::matter * trace_object(e_trace_category ecategory);
////
////const char * topic_text(::particle * pparticle);
////
////e_trace_category object_trace_category(::particle * pparticle);
////
////
////
////#define __alog(...) __tracef(__VA_ARGS__)
////
////#define INFORMATION(...) __alog(trace_object(ALOG_CONTEXT), e_trace_level_information, ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)
////#define WARN(...) __alog(trace_object(ALOG_CONTEXT), e_trace_level_warning, ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)
////#define ERR(...) __alog(trace_object(ALOG_CONTEXT), e_trace_level_error, ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)
////#define FATAL(...) __alog(trace_object(ALOG_CONTEXT), e_trace_level_fatal, ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)
////
////#define TRACE(...) INFORMATION(__VA_ARGS__)
////
////
////namespace aura
////{
////
////
////   class theme;
////
////
////} // namespace aura
////
////
////namespace axis
////{
////
////
////   class application;
////   class session;
////   class system;
////
////
////} // namespace axis
////
////
////namespace base
////{
////
////
////   class application;
////   class session;
////   class system;
////   class user;
////
////
////} // namespace base
////
////
////namespace core
////{
////
////
////   class application;
////   class session;
////   class system;
////
////
////} // namespace core
////
////
////
//////#include "aura/primitive/string/_c_impl.h"
////
////
//////#include "aura/platform/aura_main_struct.h"
////
////
//////#ifdef WINDOWS
//////#pragma warning(disable: 4251)
//////#endif
////
//////#include "platform/platform/_.h"
////
////class eimpact;
////
////enum e_simple_command : ::i64;
////enum e_message : ::i64;
////enum enum_impact : ::i64;
////enum ::enum_id : ::u64;
////enum enum_check: ::i32;
////
////template <typename TYPE>
////struct erase_const_struct { // erase top-level const qualifier
////   using NON_CONST_TYPE = TYPE;
////};
////
////template <typename TYPE>
////struct erase_const_struct< TYPE &> {
////   using NON_CONST_TYPE = TYPE &;
////};
////
////
////template <typename TYPE>
////struct erase_const_struct<const TYPE> {
////   using NON_CONST_TYPE = TYPE;
////};
////
////template <typename TYPE>
////struct erase_const_struct<const TYPE &> {
////   using NON_CONST_TYPE = TYPE &;
////};
////
////template <class TYPE>
////using non_const = typename erase_const_struct<TYPE>::NON_CONST_TYPE;
////
////struct true_type { };
////struct false_type { };
////template < typename POINTER >
////class raw_pointer
////{
////public:
////
////   using RAW_POINTER = POINTER;
////
////};
////
////template < typename TYPE >
////class raw_type
////{
////public:
////
////   using RAW_TYPE = TYPE;
////
////};
////
////template < typename TYPE >
////class raw_type < TYPE * >
////{
////public:
////
////   using RAW_TYPE = TYPE;
////
////};
////
////template < typename TYPE >
////class raw_type < TYPE * & >
////{
////public:
////
////   using RAW_TYPE = TYPE;
////
////};
////
////template < typename TYPE >
////class raw_type < const TYPE * >
////{
////public:
////
////   using RAW_TYPE = TYPE;
////
////};
////
////template < typename TYPE >
////class raw_type < const TYPE * & >
////{
////public:
////
////   using RAW_TYPE = TYPE;
////
////};
////
////
////template < typename LEFT, typename RIGHT >
////inline void assign(LEFT & l, const RIGHT & r) { l = r; }
////
////
//////template < typename, typename >
//////inline constexpr auto is_strictly_same_type = false_type();
//////template < typename TYPE >
//////inline constexpr auto is_strictly_same_type < TYPE, TYPE> = true_type();
//////
//////template < typename TYPE >
//////inline constexpr auto is_void = is_strictly_same_type< TYPE, void>;
////
////#ifdef CPP17
////
////template <typename PRED, typename ... Args >
////inline bool _returns_true(PRED pred, const true_type & predicate_returns_void, bool bOnVoid, Args... args)
////{
////   pred(args...);
////   return bOnVoid;
////}
////
////template <typename PRED, typename ... Args >
////inline bool _returns_true(PRED pred, const false_type & predicate_returns_void, bool, Args... args)
////{
////   return (bool)pred(args...);
////}
////
////template <typename PRED, typename ... Args >
////inline bool returns_true(PRED pred, bool bOnVoid, Args... args)
////{
////
////   return _returns_true(pred, is_void<decltype(pred(args...))>, bOnVoid, args...);
////
////}
////
////template <typename PRED, typename ... Args >
////inline bool _returns_false(PRED pred, const true_type & predicate_returns_void, bool bOnVoid, Args... args)
////{
////   pred(args...);
////   return bOnVoid;
////}
////
////template <typename PRED, typename ... Args >
////inline bool _returns_false(PRED pred, const false_type & predicate_returns_void, bool, Args... args)
////{
////   return !(bool)pred(args...);
////}
////
////template <typename PRED, typename ... Args >
////inline bool returns_false(PRED pred, bool bOnVoid, Args... args)
////{
////
////   return _returns_false(pred, is_void < decltype(pred(args...)) >, bOnVoid, args...);
////
////}
////
////#endif
////
////template < typename CHAR_TYPE >
////class string_base;
////
////
////struct pixmap;
////
////
////#define CONSIDER_AS(as, use) using use = as
////
////
////using ansi_string = string_base < ::ansi_character >;
////using wd16_string = string_base < ::wd16_character >;
////using wd32_string = string_base < ::wd32_character >;
////using wide_string = string_base < ::wide_character >;
////
////
////using string = string_base < ::ansi_character >;
////using wstring = string_base < ::wide_character >;
////
////
////class machine_event_central;

//
////
////#undef _
////
////#define _(str) (__get_text(str))
////
////CLASS_DECL_AURA string __get_text(string str);
////
////
////
////
//////class critical_section;
////
////
//////namespace command
//////{
//////
//////   class command;
//////
//////} // namespace command
////
////
////class trait;
////class create;
////class synchronization;
////
////
//////CLASS_DECL_AURA i32 aura_run_system(::aura::system* psystem);
////
////
//////CLASS_DECL_AURA void aura_run_system_init(::aura::system * psystem);
//////CLASS_DECL_AURA void aura_run_system_proc(::aura::system * psystem);
//////CLASS_DECL_AURA void aura_run_system_term(::aura::system * psystem);
////
////
////template < typename VAR >
////class var_type
////{
////public:
////
////   using VAR_TYPE = VAR;
////
////   VAR_TYPE * this_var() { return (VAR_TYPE *)this; }
////   const VAR_TYPE * this_var() const { return (const VAR_TYPE *)this; }
////
////};
////
//////// very short name ([{c}])ontext (switchers, as it as action_context) enums
//////enum nullptr_t
//////{
//////   nullptr
//////};
////
////// very short name ([{c}])ontext (switchers, as it as action_context) enums
////enum e_context_switcher_empty
////{
////   cempty
////};
////
////
////enum enum_create_new
////{
////
////   e_create_new
////
////};
////
////
////enum enum_create
////{
////
////   e_create
////
////};
////
////enum enum_defer_new // memory_new - for factoryless_allocation FACTORYLESS_ALLOCATION_ID
////{
////
////   e_defer_new
////
////};
////
////enum enum_move_transfer
////{
////
////   e_pointer_transfer
////
////};
////
////
////enum enum_copy_clone
////{
////
////   e_copy_clone
////
////};
////
////#define IMPL_OPERATOR_PLUS(type) \
////template < typename TYPE > \
////type operator + (const TYPE & t) const { auto copy = *this; copy.add(t); return copy; }
////
//////#include "aura/primitive/math/_.h"
////
//////#include "aura/memory/_heap.h"
////
//////#include "aura/exception/_const.h"
////
////#include "aura/user/user/_constant.h"
////
//////#include "aura/user/_experience_const.h"
////
//////#include "aura/filesystem/file/_const.h"
////
//
//
////#include "aura/graphics/draw2d/_const.h"
//
//
//namespace OPERATING_SYSTEM_NAMESPACE
//{
//
//   class buffer;
//
//} // namespace OPERATING_SYSTEM_NAMESPACE
//
//
//namespace windowing_universal_windows
//{
//
//   class buffer;
//
//} // namespace windowing_universal_windows
//
//
//namespace windowing_win32
//{
//
//   class buffer;
//
//} // namespace windowing_universal_windows
//
//
//namespace aura
//{
//
//   class draw_context;
//
//} // namespace aura
//
//class color_filter;
//
//
//class image_frame_array;
//class image_drawer;
//class image_drawing;
//class image_drawing_options;
//
//template < typename SHAPE_FACTORY >
//class shape_array;
//
//class imaging;
//
//
//class image;
//
//
//namespace draw2d
//{
//
//   class icon;
//   class graphics;
//   class bitmap;
//   class brush;
//   class pen;
//   class item;
//   class path;
//
//   using path_pointer = ::pointer<path>
//
//} // namespace draw2d
//
//
////#include "acme/user/user/_constant_key.h"
//
//
////#include "aura/graphics/_.h"
//
//
////#include "aura/user/_.h"
//
////
////
////namespace draw2d
////{
////
////
////   class graphics;
////
////
////   class icon;
////   class cursor;
////   class region;
////   class brush;
////   using brush_pointer = ::pointer<brush>
////
////
////} // namespace draw2d
////
//
//namespace write_text
//{
//
//
//   class font;
//   using font_pointer = ::pointer<font>
//
//
//} // namespace write_text
//
//
//
//
//
//
////
////template < typename T1, typename T2, typename ARG_T1 = const T1 &, typename ARG_T2 = const T2 & >
////class pair;
////
////template < class KEY, class ARG_KEY, class PAYLOAD, ARG_VALUE = argument_of < PAYLOAD >, class PAIR = pair < KEY, PAYLOAD, ARG_KEY, ARG_VALUE > >
////class map;
////
////template < class ENUM >
////class flags;
////
////template < class EENUM, EENUM edefault = (EENUM)0 >
////class base_enum;
////
////class form_property_set;
////
////
//////namespace user
//////{
//////
//////
//////   class create;
//////   class control_event;
//////   class item;
//////   class check;
//////   class create_struct;
//////   class command;
//////   class interaction_impl;
//////   class primitive;
//////   class frame;
////////   class menu;
//////   //class controller;
//////   //class document;
//////
//////   //class impact_system;
//////   //class impact_data;
//////   class printer;
////////   class impact;
//////   class primitive;
//////   class interaction;
//////   class layout;
//////   //class place_holder;
//////   //class menu_item;
//////   //class form;
//////   class style;
//////   class menu_interaction;
//////   //class tab;
//////   class tab_pane;
//////   class check_box;
//////   class toolbar;
//////   class split_layout;
//////   class style_rect;
//////   class scroll_bar;
//////   class scroll_data;
//////
//////
//////   //using color_map = map < e_color, e_color, ::color::color, ::color::color >;
//////   //using font_map = map < e_font, e_font, ::write_text::font_pointer >;
//////   using eflag = flags < enum_flag >;
//////   //using flag_map = map < enum_flag, enum_flag, bool, bool >;
//////   //using rect_map = ::map < e_rect, e_rect, style_rect >;
//////   //using i32_map = ::map < e_int, e_int, int, int >;
//////   //using double_map = ::map < e_double, e_double, double, double >;
//////   //using color_map = map < e_color, e_color, ::color::color, ::color::color >;
//////   //using eelement = base_enum < enum_element >;
//////   //using translucency_map = ::map < enum_element, enum_element, enum_translucency, enum_translucency >;
//////
//////
//////
//////#if defined(UNIVERSAL_WINDOWS) || defined(APPLE_IOS) || defined(ANDROID)
//////
//////   class native_window_initialize;
//////
//////#endif
//////
//////
//////} // namespace user
//////=======
//namespace user
//{
//
//
//   //class create;
//   //class control_event;
//   //class item;
//   class check;
////   class system;
//   //class command;
//   class interaction_impl;
//   class primitive;
//   class frame;
//   class printer;
//   class primitive;
//   class interaction;
//   class impact;
//   class interaction_layout;
//   class scroll_base;
//   class form;
//   class form_callback;
//   class menu_interaction;
//   class toolbar;
//   class split_layout;
//   class style_rect;
//   class scroll_bar;
//   class scroll_data;
//   class style;
//   class box;
//   class interaction_array;
//
//   using style_pointer = ::pointer<style>
//
//   using e_flag = enumeration < enum_flag >;
//
//
//#if defined(UNIVERSAL_WINDOWS) || defined(APPLE_IOS) || defined(ANDROID)
//
//   class native_window_initialize;
//
//#endif
//
//
//} // namespace user
//
//
//class form_document;
//
//
//namespace aura
//{
//
//   class file;
//
//   namespace trace
//   {
//
//      class trace;
//
//   }
//
//   class session;
//
//} // namespace aura
//
////CLASS_DECL_AURA bool enable_trace_category(e_trace_category ecategory, bool bEnable = true);
////
////// only usable from axis and axis dependants
////namespace aura
////{
////
////   class application;
////   class session;
////   class system;
////
////}
////
////
////// only usable from base and base dependants
////namespace base
////{
////
////   class application;
////   class session;
////   class system;
////
////}
////
////// only usable from aura and aura dependants
////namespace aura
////{
////
////   class application;
////   class session;
////   class system;
////
////}
////
////
////class app_core;
////
////
//////extern "C"
//////typedef ::aura::system *  CREATE_SYSTEM(app_core * pappcore);
//////typedef ::aura::system * CREATE_SYSTEM();
////
//////typedef CREATE_SYSTEM * LPFN_CREATE_SYSTEM;
////
//////CLASS_DECL_AURA extern LPFN_CREATE_SYSTEM g_pfn_create_system;
//////CLASS_DECL_AURA extern const char * g_pszCooperativeLevel;
//////CLASS_DECL_AURA extern int g_iDerivedApplication; // one-based-index of derived application, zero if Main application
////
////
////namespace data
////{
////
////
////   class item;
////
////
////} // namespace data
////
////
////namespace xml
////{
////
////
////   class node;
////   class document;
////
////
////} // namespace xml
////
////
////
////
////
////
////enum enum_extract
////{
////
////   e_extract_none,
////   e_extract_first,
////   e_extract_all
////
////};
////
////
////namespace str
////{
////
////
////   namespace international
////   {
////
////
////      class locale_schema;
////
////
////   } // namespace international
////
////
////} // namespace str
////
////
////
//
//namespace draw2d
//{
//
//
//   class graphics;
//
//
//} // namespace draw2d
//CLASS_DECL_AURA void aura_init();
//CLASS_DECL_AURA void aura_term();
////
//CLASS_DECL_AURA void __node_aura_pre_init();
//CLASS_DECL_AURA void __node_aura_pos_init();
////
//CLASS_DECL_AURA void __node_aura_pre_term();
//CLASS_DECL_AURA void __node_aura_pos_term();
////
////
//////extern "C" CLASS_DECL_AURA PFN_NEW_AURA_LIBRARY get_get_new_aura_library(const ::string & psz);
//////extern "C" CLASS_DECL_AURA void register_get_new_aura_library(const ::string & psz, PFN_NEW_AURA_LIBRARY pfnNewAuraLibrary);
////
////
//////CLASS_DECL_AURA ::acme::library & get_library(const ::string & psz);
//////CLASS_DECL_AURA void register_aura_library(const ::string & psz, ::acme::library* plibrary);
//////
//////CLASS_DECL_AURA ::context * get_context();
//////CLASS_DECL_AURA inline ::context * get_context(::particle * pparticle);
//////CLASS_DECL_AURA inline ::context * get_context(::context * pcontext);
////
////
////CLASS_DECL_AURA void set_global_application(::aura::application * papp);
////CLASS_DECL_AURA ::aura::application * get_global_application();
////
////
////CLASS_DECL_AURA ::aura::application * get_app();
////CLASS_DECL_AURA inline ::aura::application * get_app(::particle * pparticle);
////CLASS_DECL_AURA inline ::aura::application * get_app(::aura::application * papp);
////CLASS_DECL_AURA inline ::aura::application * get_app() { return get_app(); }
////
////
////CLASS_DECL_AURA::aura::session * get_session();
////CLASS_DECL_AURA inline ::aura::session * get_session(::particle * pparticle);
////CLASS_DECL_AURA inline ::aura::session * get_session(::aura::session * psession);
////
////CLASS_DECL_AURA::aura::system * get_context_system();
////CLASS_DECL_AURA inline ::aura::system * get_context_system(::particle * pparticle);
////CLASS_DECL_AURA inline ::aura::system * get_context_system(::aura::system * psystem);
////
////
////#define BAD_WCHAR ((::wide_character)(-1))
////
////
////#define ARRAY_SIZE(a) (sizeof(a)/sizeof(*(a)))
////
////
////class ::payload;
////class atom;
////
////
////namespace calculator
////{
////
////
////   class value;
////
////
////} // namespace calculator
////
////
////
////
////
////
////#ifdef __APPLE__
////#undef err_none
////#endif
////
////#ifdef WINDOWS
////
////template < typename POINTER_TYPE >
////class cotaskptr;
////
////#endif
////
////class type;
////
////
////#include "aura/primitive/string/_.h"
////
////
////#include "aura/platform/definition.h"
////
////#include "aura/memory/memory_new.h"
////
////#include "aura/platform/lparam.h"
////#include "aura/platform/muldiv64.h"
////
////
////
////
////#include "aura/platform/auto_pointer.h"
////
////
////// C-includes
//////#include "aura/os/os.h"
////
////class thread_parameter;
////
////#include "aura/primitive/primitive/enum.h"
////
////
////#include "aura/primitive/primitive/interlocked_long.h"
////#include "aura/primitive/primitive/interlocked_long_pulse.h"
////#include "aura/primitive/primitive/type.h"
////#include "aura/primitive/primitive/atom.h"
////#include "aura/primitive/primitive/uid.h"
////
////
////namespace primitive
////{
////
////
////   template < typename TYPE >
////   class member;
////
////
////   template < typename TYPE >
////   class composite;
////
////
////   template < typename TYPE >
////   class reference;
////
////
////} // namespace primitive
////
////
////#define __member(TYPE) ::primitive::member < TYPE >
////#define ::pointer<TYPE>::primitive::composite < TYPE >
////#define ::pointer<TYPE>::primitive::reference < TYPE >
////
////
////
////
////template < typename TYPE >
////inline bool is_null(const ::pointer<TYPE>& p)
////{
////
////   return ::is_null(p.m_p);
////
////}
////
////template < typename TYPE >
////inline bool is_null(const ::pointer<TYPE>& p)
////{
////
////   return p.is_null();
////
////}
////
////template < typename TYPE >
////inline bool is_null(const ::pointer<TYPE>& p)
////{
////
////   return p.is_null();
////
////}
////
////
////template < typename TYPE >
////inline bool is_set(const ::pointer<TYPE>& p)
////{
////
////   return p.is_set();
////
////}
////
////template < typename TYPE >
////inline bool is_set(const ::pointer<TYPE>& p)
////{
////
////   return p.is_set();
////
////}
////
////template < typename TYPE >
////inline bool is_set(const ::pointer<TYPE>& p)
////{
////
////   return p.is_set();
////
////}
////
////template < typename TYPE >
////inline bool is_null(const TYPE & t)
////{
////
////   return is_null(&t);
////
////}
////
////
////template < typename TYPE >
////inline bool is_set(const TYPE & t)
////{
////   return !is_null(t);
////}
////
////
////
////
////#include "aura/primitive/primitive/pointer.h"
////#include "aura/primitive/primitive/pointer2.h"
////
////
////template < class POINTER_TYPE >
////inline auto & __typed(::pointer<POINTER_TYPE>& p) { return *p; }
////
////
////#include "aura/parallelization/thread_parameter.h"
////
////#include "aura/platform/keep_true.h"
////
////using file_pointer = ::pointer<::file::file>
////
////using file_pointer = ::pointer<::file::file>
////
////class stream;
////class binary_stream < FILE >;
////
////template < typename BASE_TYPE >
////inline stream & __save_object(stream & stream, BASE_TYPE * p);
////
////template < typename BASE_TYPE >
////inline stream & __save_object(stream & stream, const ::pointer<BASE_TYPE>& p)
////{
////   return __save_object(stream, (BASE_TYPE *) p.m_p);
////}
////
////#include "aura/primitive/primitive/logic.h"
////
////
////
////#include "aura/primitive/math/static_numeric_info.h"
////#include "aura/primitive/math/numeric_info.h"
////
////
////
////
////#include "aura/primitive/math/c_number.h"
////
////using wparam = c_number < wparam >;
////
////
////
////
////#include "aura/primitive/math/math_clip.h"
////
////
////#include "aura/platform/class ::time.h"
////
////
////#include "aura/primitive/datetime/time.h"
////
////#include "aura/platform/common.h"
////
////
//////#include "aura/primitive/string/_.h"
////
////
////#include "aura/primitive/datetime/date_span.h"
////#include "aura/primitive/datetime/time_span.h"
////#include "aura/primitive/datetime/time.h"
////#include "aura/primitive/datetime/zonetime.h"
////#include "aura/primitive/datetime/file_time_span.h"
////#include "aura/primitive/datetime/file_time.h"
////
////
////
////
////
////
////#include "aura/operating_system/_.h"
////
////
////class update;
////
////namespace status
////{
////
////   class result;
////
////} // namespace status
////
////namespace message
////{
////   class message;
////
////} // namespace status
////
////class parents;
////
////class children;
////
////
////namespace exception
////{
////
////   class exception;
////   using exception_pointer = ::pointer<exception>
////
////} // namespace exception
////
////
////using exception_pointer = ::exception::exception_pointer;
////
////
////class event_map;
////class thread_ptra;
//////class traits;
////
////
////namespace papaya
////{
////
////   class topic;
////
////} // namespace papaya
////
////
////class memory_base;
////
////
////
////template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename RECTANGLE_BASE_TYPE >
////class size_type;
////
////using size = size_type < SIZE_I32, POINT_I32, RECTANGLE_I32 >;
////
////
////#include "aura/primitive/math/cast.h"
////
////
////#include "aura/primitive/primitive/block.h"
////#include "aura/memory/memory.h"
////
////#include "aura/primitive/primitive/enumeration.h"
//
////
////namespace user
////{
////
////
////   //DECLARE_ENUMERATION(enum_state, enum_state);
////   using eelement = enumeration < enum_element >;
////
////
////} // namespace user
////
//
//
////
////
////
////
////
//////using eobject = enumeration < :: >;
////class action_context;
////
////#include "aura/primitive/primitive/eobject.h"
////
////using emessagebox = enumeration < enum_message_box >;
////
////#include "aura/primitive/primitive/function_base.h"
////
////
////
////
////
////#include "aura/primitive/primitive/matter.h"
////#include "aura/primitive/primitive/task.h"
////#include "aura/primitive/primitive/compare_predicate.h"
////
////
////#include "aura/platform/status.h"
////#include "aura/primitive/primitive/enum_type.h"
////
////using efileopen = enumeration < ::file::e_open >;
////
////using eiostate = ::enumeration < ::file::e_iostate >;
////
////using ecommand = ::enumeration < enum_command >;
////
////using echeck = ::enumeration < enum_check >;
////
////
////typedef void THREAD_PROCEDURE(thread_parameter parameter);
////
////
////inline bool succeeded(const ::payload & payload);
////inline bool succeeded(const ::property & set);
////
////inline bool failed(const ::payload & payload) { return !::succeeded(payload); }
////inline bool failed(const ::property & set) { return !::succeeded(set); }
////
////
////#define __inner_release(outer, inner) ::release(outer, outer->inner)
////
////
////#include "aura/primitive/primitive/function_base.h"
////
////
////#include "aura/primitive/primitive/member.h"
////
////
////#include "aura/primitive/primitive/object.h"
////
////
////#include "aura/primitive/primitive/trait.h"
////
////
////
////
////
////
////
////#include "aura/primitive/primitive/_papaya.h"
////
////
////
////
////
////
////
////
////#include "aura/primitive/geometry2d/_.h"
////
////
//////#include "aura/primitive/primitive/object.h"
////
////
////#include "aura/primitive/primitive/_factory_prefix.h"
////
////
////#include "aura/primitive/collection/decl.h"
////
////#include "aura/primitive/collection/raw_array_decl.h"
////
////
////#include "aura/primitive/collection/comparable_eq_array.h"
////#include "aura/primitive/collection/comparable_array.h"
////#include "aura/primitive/collection/comparable_raw_array.h"
////
////
////#include "aura/primitive/collection/pointer_array_process.h"
////
////#include "aura/primitive/collection/pointer_array.h"
////
////
////
//////#include "aura/primitive/collection/_papaya_array_decl.h"
////#include "aura/primitive/collection/_papaya_heap.h"
////
////
////#include "aura/primitive/collection/address_array.h"
////
////
////#include "aura/primitive/collection/_papaya.h"
////
////
//////#include "aura/primitive/collection/pointer2_array.h"
////
////class sticker;
////
////
////inline ::matter * trace_object(::particle * pparticle) { return pparticle; }
////
////template < typename POINTER_TYPE >
////class ptr_array;
////
//////using composite_ptra = pointer_array < ::matter >; // Please use just for composition (ownership).
////
//////using reference_ptra = pointer_array < ::matter >; // Please use just for reference (member-based).
////
//////using object_ptra = pointer_array < ::object >; // Please use just for keeping non-member-based references.
////
////using object_ptra = pointer_array < ::matter >; // Please use just for keeping non-member-based references.
////
////using object_addra = __address_array(::matter); // Please use just for keeping non-member-based references.
////
////class object_meta;
////
////
////#define __composite_array(TYPE) ::array < ::pointer<TYPE >>
////#define __reference_array(TYPE) ::array < ::pointer<TYPE >>
////
////namespace http
////{
////
////   class context;
////
////} // namespace http
////
////template < typename PRED > inline auto __task_procedure(PRED pred, ::matter * pobjectHold = nullptr);
////
////template < typename PRED > inline auto __task_callback(PRED pred, ::matter* pobjectHold = nullptr);
////
////class context;
//
//
//
////#include "aura/graphics/_.h"
//
////#include "aura/user/user/_.h"
//
////#include "aura/user/item.h"
//
////#include "aura/platform/drawable.h"
//
////#include "aura/game/_.h"
//
////#include "aura/windowing/_.h"
//
//
//
////#include "aura/filesystem/filemanager/callback.h"
////
////#include "aura/platform/shell_open.h"
////
////#include "aura/filesystem/filemanager/item_action.h"
////
////#include "aura/hardware/devices.h"
//
//
//
////#include "aura/platform/_.h"
////
////
////
////#include "aura/operating_system/_impl.h"
////
////#include "aura/platform/_impl.h"
////
//////#include "aura/windowing/_impl.h"
//
