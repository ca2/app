/////////////////////////////////////////////////////////////////////////////////////////
//
//  ca2
//
//  ca2 is an all-purpose multi-platform framework and set of libraries written in
//  C++ language with the aim to help developers create awesome apps for users.
//
//  ca2/./aura/C++/C/Assembly/Huffman Machine/Hardware/Universe/Multiverse stack
//
//
//
//
//  c(s)t(s)<tb(s)!!
//




#pragma once



#define __spin_namespace aura // back bone / four-letter "spin*" namespace name



#undef Sys
#undef Sess
#undef App


#define Sys(playered) (*::get_context_system(playered)->m_paurasystem)
#define Sess(playered) (*::get_context_session(playered)->m_paurasession)
#define App(playered) (*::get_context_application(playered)->m_pauraapplication)


#define Au(playered) (*(::get_context_audio(playered)))
#define Audio (Au(get_context()))

#define Mm(playered) (*(::get_context_multimedia(playered)))
#define Multimedia (Mm(get_context()))



//#include "aura/primitive/primitive/estatus.h"
//
//
//#include <tuple>
//
//
CLASS_DECL_AURA void aura_ref();
//
//
//#ifdef WINDOWS_DESKTOP
//
//typedef i32 WINAPI __MAIN_DEFERRED_RUN(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR pCmdLine, i32 nCmdShow);
//
//#else
//
//typedef i32 __MAIN_DEFERRED_RUN(int argc, char ** argv);
//
//#endif
//
//
//typedef __MAIN_DEFERRED_RUN * __LPFN_MAIN_DEFERRED_RUN;
//extern CLASS_DECL_AURA __LPFN_MAIN_DEFERRED_RUN __main_deferred_run;
//
//
//#ifdef __DEBUG
//
//#define INLINE
//
//#else
//
//#define INLINE inline
//
//#endif
//
//
////#include "aura/platform/cpu_architecture.h"
//
//
////#include "aura/message/global.h"
//
//
////#include "aura/exception/_c.h"
//
//
//#ifdef WINDOWS_DESKTOP
//
//
//#if defined _M_IX86
//#define _AURA_LINKER_SYMBOL_PREFIX "_"
//#elif defined _M_X64 || defined _M_ARM || defined _M_ARM64
//#define _AURA_LINKER_SYMBOL_PREFIX ""
//#else
//#error Unsupported architecture
//#endif
//
//
//#endif
//
//
//#if defined(APPLE_IOS) || defined(ANDROID) || defined(_UWP)
//
//#define MOBILE_PLATFORM 1
//
//#else
//
//#define MOBILE_PLATFORM 0
//
//#endif
//
//
//#ifndef WINDOWS
//
//
//#define _CRT_ASSERT 0
//
//
//#endif
//
//
//#if defined(DEBUG) && !defined(NO_AURA_MEMORY_MANAGEMENT)
//#define ACME_NEW new(__FILE__, __LINE__)
//#else
//#define ACME_NEW new
//#endif
//
//#define new ACME_NEW
//
//
//#include "aura/platform/obj_ref_dbg.h"
//
//
//namespace opengl
//{
//
//
//   class opengl;
//
//
//} // namespace opengl
//
//
//struct INT_STRING
//{
//
//   int            m_i;
//   const char* m_psz;
//
//};
//
//
//
//CLASS_DECL_AURA void throw_todo(void);
//
//
////CLASS_DECL_AURA void set_last_status(const ::estatus & estatus);
////CLASS_DECL_AURA void windowing_output_debug_string(const char * pszDebugString);
////CLASS_DECL_AURA void c_function_call(void * p);
////extern CLASS_DECL_AURA int g_bAura;
////CLASS_DECL_AURA int __assert_failed_line(const char * pszFileName,int iLineNumber);
////CLASS_DECL_AURA int is_debugger_attached(void);
////CLASS_DECL_AURA void debug_print(const char * psz,...);
////
////
////CLASS_DECL_AURA int throw_assert_exception(const char * pszFileName,int iLineNumber);
////CLASS_DECL_AURA void throw_what_exclamation_exclamation(const char * psz);
////
//
//
//#ifndef __cplusplus
//
//
//#define ASSERT assert
//
//
//#else
//
//
//#ifdef __DEBUG
//
//
//#define ASSERT(f)          ((void) ((f) || (is_debugger_attached() && !::__assert_failed_line(__FILE__, __LINE__) && (::debug_break(), 0)) || (!is_debugger_attached() && (throw_assert_exception(__FILE__, __LINE__), 0))))
//#define _ASSUME(cond)       do { bool _gen__condVal=!!(cond); ASSERT(_gen__condVal); __analysis_assume(_gen__condVal); } while(0)
//#define ASSERT_VALID(pOb)  ::__assert_valid_object(pOb, __FILE__, __LINE__)
//
//
//#else
//
//
//#define ASSERT(f)
//#define _ASSUME(cond)
//#if defined(ANDROID)
//#define ASSERT_VALID(cond)
//#elif defined(APPLEOS)
//#define ASSERT_VALID(cond)
//#elif defined(LINUX)
//#define ASSERT_VALID(cond)
//#else
//#define ASSERT_VALID(cond) __noop;
//#endif
//#endif
//
//
//#endif
//
//
//#define low_byte(w)              ((byte)((w) & 0xff))
//
//
//#if defined(WINDOWS) || defined(LINUX) || defined(__i386__)
//
//
//#define IMAGE_A_BYTE_INDEX 3
//#define IMAGE_R_BYTE_INDEX 2
//#define IMAGE_G_BYTE_INDEX 1
//#define IMAGE_B_BYTE_INDEX 0
//
//
//#define IMAGE_ARGB(a, r, g, b)         ((COLORREF)((low_byte(b)|((WORD)(low_byte(g))<<8))|(((u32)low_byte(r))<<16)|(((u32)low_byte(a))<<24)))
//
//
//#define image_r_value(rgb)    (low_byte((rgb)>>16))
//#define image_g_value(rgb)    (low_byte((rgb)>>8))
//#define image_b_value(rgb)    (low_byte((rgb)))
//#define image_a_value(rgb)    (low_byte((rgb)>>24))
//
//
//#else
//
//
//#define IMAGE_A_BYTE_INDEX 3
//#define IMAGE_R_BYTE_INDEX 0
//#define IMAGE_G_BYTE_INDEX 1
//#define IMAGE_B_BYTE_INDEX 2
//
//
//#define IMAGE_ARGB(a, r, g, b)         ((COLORREF)((low_byte(r)|((WORD)(low_byte(g))<<8))|(((u32)low_byte(b))<<16)|(((u32)low_byte(a))<<24)))
//
//
//#define image_r_value(rgb)    (low_byte((rgb)))
//#define image_g_value(rgb)    (low_byte((rgb)>>8))
//#define image_b_value(rgb)    (low_byte((rgb)>>16))
//#define image_a_value(rgb)    (low_byte((rgb)>>24))
//
//
//#endif
//
//
//#define __CONCAT3(xxx, yyy, zzz) xxx ## yyy ## zzz
//
//
//#define colorref_get_r_value(rgb)    (low_byte(rgb))
//#define colorref_get_g_value(rgb)    (low_byte((rgb)>>8))
//#define colorref_get_b_value(rgb)    (low_byte((rgb)>>16))
//#define colorref_get_a_value(rgb)    (low_byte((rgb)>>24))
//#define RGBA(r, g, b, a)         ((COLORREF)((low_byte(r)|((WORD)(low_byte(g))<<8))|(((u32)low_byte(b))<<16)|(((u32)low_byte(a))<<24)))
//#define ARGB(a, r, g, b)      RGBA(r, g, b, a)
//
//
//#define __acolor(a, r, g, b)      ::color(r, g, b, a)
//
//
//inline int trailingBytesForUTF8(char ch);
//
//
//extern CLASS_DECL_AURA const char g_trailingBytesForUTF8[256];
//
//
//inline int trailingBytesForUTF8(char ch)
//{
//
//   return ::g_trailingBytesForUTF8[(byte)ch];
//
//}
//
//
//CLASS_DECL_AURA int is_ptr_null(const void * p, size_t s);
//
//
//inline CLASS_DECL_AURA int c_is_null(const void * p)
//{
//   return ((uptr)p) < 65536;
//
//}
//
//
//
//#define void_ptr_is_null(p) (((uptr)(void *) p) < 4096)
//
//namespace dynamic_source
//{
//
//
//   class script_interface;
//
//
//} // namespace dynamic_source
//
//
////#include "aura/primitive/math/mkint_c.h"
//
//// C-includes
//#include "aura/os/_c.h"
////#include "aura/memory/heap_c.h"
//
//
//
//#undef min
//#undef max
//
//
//#define INTABS(i) (((i) >= 0) ? (i) : (-i))
//#define FLOATABS(f) (((f) >= 0.f) ? (f) : (-f))
//#define DOUBLEABS(d) (((d) >= 0.0) ? (d) : (-d))
//
//
////#ifdef __cplusplus
////#define max(a, b) (((b) < (a)) ? (a) : (b))
////#define min(a, b) (((a) < (b)) ? (a) : (b))
////#include "aura/primitive/comparison/_c.h"
////#else
////#define max(a, b) (((a) > (b)) ? (a) : (b))
////#define min(a, b) (((a) < (b)) ? (a) : (b))
////#endif
//
//
//#define LIM(a, min, max) min(max, max(min, a))
//#define SORT_LIM(x,minmax,maxmin) ((minmax) < (maxmin) ? LIM(x,minmax,maxmin) : LIM(x,maxmin,minmax))
//#define CLIP_USHRT(x) LIM(x,0,USHRT_MAX)
//
//
//
//
//#ifdef WINDOWS
//#include <intsafe.h>
//#else
//
//#ifndef LODWORD
//#define LODWORD(l)                                    ((::u32)(((::u64)(l)) & 0xffffffff))
//#endif
//#ifndef HIDWORD
//#define HIDWORD(l)                                    ((::u32)((((::u64)(l)) >> 32) & 0xffffffff))
//#endif
//
//#endif
//
//
//
//
//#define __u16(a, b)                                   ((::u16)(((::u8)(((::uptr)(a)) & 0xff)) | ((::u16)((::u8)(((::uptr)(b)) & 0xff))) << 8))
//#define __u32(a, b)                                   ((::u32)(((::u16)(((::uptr)(a)) & 0xffff)) | ((::u32)((::u16)(((::uptr)(b)) & 0xffff))) << 16))
//
//
//#ifdef __cplusplus
//
//#define MAKELONG64(a, b)                              (((::u64)(((::u32)(((::u64)(a)) & 0xffffffff)) | ((::u64)((::u32)(((::u64)(b)) & 0xffffffff))) << 32)))
//#define __u64(a, b)                                   (((::u64)(((::u32)(((::u64)(a)) & 0xffffffff)) | ((::u64)((::u32)(((::u64)(b)) & 0xffffffff))) << 32)))
//
//#else
//
//#define MAKELONG64(a, b)                              (((u64)(((u32)(((u64)(a)) & 0xffffffff)) | ((u64)((u32)(((u64)(b)) & 0xffffffff))) << 32)))
//#define __u64(a, b)                                   (((u64)(((u32)(((u64)(a)) & 0xffffffff)) | ((u64)((u32)(((u64)(b)) & 0xffffffff))) << 32)))
//
//#endif
//
//#define __lo16(u)                                     ((::u16)(((::uptr)(u)) & 0xffff))
//#define __hi16(u)                                     ((::u16)((((::uptr)(u)) >> 16) & 0xffff))
//#define __lo32(u)                                     ((::u32)(u))
//#define __hi32(u)                                     ((::u32)(((u) >> 32) & 0xffffffff))
//
//#define __u32x(u)                                     ((::i16)__lo16(u))
//#define __u32y(u)                                     ((::i16)__hi16(u))
//
//#define __u32xy(u)                                    __u32x(u), __u32y(u)
//
//#define __u64x(u)                                     ((::i32)__lo32(u))
//#define __u64y(u)                                     ((::i32)__hi32(u))
//
//#define __u64xy(u)                                    __u64x(u), __u64y(u)
//
//
//#ifndef GET_X_LPARAM
//#define GET_X_LPARAM(lparam)                          ((i32)(i16)LOWORD(lparam))
//#endif
//
//
//#ifndef GET_Y_LPARAM
//#define GET_Y_LPARAM(lparam)                          ((i32)(i16)HIWORD(lparam))
//#endif
//
//#define GET_X_LPARAM64(lparam)                        ((i32)(i16)LODWORD(lparam))
//#define GET_Y_LPARAM64(lparam)                        ((i32)(i16)HIDWORD(lparam))
//
//
////CLASS_DECL_AURA int get_aura_init();
//
////extern "C"
////CLASS_DECL_AURA int_bool defer_aura_init();
//
////extern "C"
////CLASS_DECL_AURA int_bool defer_aura_term();
//
//
//
//
//typedef struct rdp_freerdp freerdp;
//
//
//CLASS_DECL_AURA int_bool freerdp_authenticate(void * instance, char** username,char** password,char** domain, const char * pszServerName, int bInteractive);
//
//
//#if !defined(O_BINARY) && !defined(WINDOWS)
//# define O_BINARY 0
//#endif
//
//
//CLASS_DECL_AURA i32     ansi_open(const char * psz,i32 i);
//CLASS_DECL_AURA FILE *  ansi_fopen(const char * psz,const char * pszMode);
//CLASS_DECL_AURA int     ansi_file_flag(int iFlag);
//CLASS_DECL_AURA void    ansi_get_errno(i32 * perrno);
//CLASS_DECL_AURA void    ansi_unlink(const char * psz);
//
//
//CLASS_DECL_AURA DWORD get_last_error();
//CLASS_DECL_AURA void set_last_error(DWORD dw);
//
//typedef char ansichar;
//
//i32 CLASS_DECL_AURA MultiByteToWideChar2(UINT CodePage, DWORD dwFlags, const ansichar * pMultByteStr, i32 cbMultiByte, widechar * pWideCharStr, i32 cchWideChar);
//i32 CLASS_DECL_AURA WideCharToMultiByte2(UINT CodePage, DWORD dwFlags, const widechar * pWideCharStr, i32 cchWideChar, ansichar * pMultByteStr, i32 cbMultiByte, LPCSTR pDefaultChar, LPBOOL pUsedDefaultChar);
//
//
//enum e_image_type
//{
//
//   image_type_complex,
//   image_type_plain_color
//
//};
//
//
//
//
//
////#include "aura/primitive/primitive/_c_memory.h"
//
////#include "aura/primitive/string/_c.h"
//
////#include "aura/primitive/datetime/_c.h"
//
////#include "aura/filesystem/file/_c.h"
//
//#include "aura/const/thread.h"
//
//
//
//
//
//#if !defined(APPLEOS) && !defined(LINUX) && !defined(ANDROID)
//
//int ftruncate(int file, filesize len);
//
//#endif
//
//
//CLASS_DECL_AURA i32 get_os_thread_priority(::e_priority epriority);
//CLASS_DECL_AURA i32 get_os_priority_class(::e_priority epriority);
//CLASS_DECL_AURA ::e_priority get_os_thread_scheduling_priority(i32 iCa2Priority);
//CLASS_DECL_AURA ::e_priority get_os_class_scheduling_priority(i32 iCa2Priority);
//
//
//
////#include "aura/primitive/datetime/mktime.h"
////#include "aura/primitive/api/api.h"
//
//
#include "aura/multimedia/_c.h"
//
//
//class generic;
//
//
//template < typename T >
//void __finalize_and_release(T& p)
//{
//
//   if (p)
//   {
//
//      p->finalize();
//
//      p.release();
//
//   }
//
//}
//
//
//CLASS_DECL_AURA extern u32 g_tickStartTime;
//
//#define ALOG_CONTEXT context_trace_object()
//
//#define _S_ALOG_CONTEXT ::context_trace_object()
//
//
//
//CLASS_DECL_AURA ::generic * general_trace_object();
//
//CLASS_DECL_AURA int_bool c_enable_trace_category(e_trace_category ecategory, int_bool iEnable);
//
//inline ::generic * context_trace_object() { return general_trace_object(); }
//
//
//CLASS_DECL_AURA void __tracea(::generic * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz);
//CLASS_DECL_AURA void __tracef(::generic * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz, ...);
//CLASS_DECL_AURA void __tracev(::generic * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz, va_list vargs);
//CLASS_DECL_AURA const char * trace_category_name(e_trace_category ecategory);
//
//
//CLASS_DECL_AURA ::generic * trace_object(e_trace_category ecategory);
//
//const char * topic_text(::generic * pcontextobject);
//
//e_trace_category object_trace_category(::generic * pcontextobject);
//
//
//
//#define __alog(...) __tracef(__VA_ARGS__)
//
//#define INFO(...) __alog(trace_object(ALOG_CONTEXT), trace_level_information, ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)
//#define WARN(...) __alog(trace_object(ALOG_CONTEXT), trace_level_warning, ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)
//#define ERR(...) __alog(trace_object(ALOG_CONTEXT), trace_level_error, ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)
//#define FATAL(...) __alog(trace_object(ALOG_CONTEXT), trace_level_fatal, ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)
//
//#define TRACE(...) INFO(__VA_ARGS__)
//
//
//namespace aura
//{
//
//
//   class theme;
//
//
//} // namespace aura
//
//
//namespace axis
//{
//
//
//   class application;
//   class session;
//   class system;
//
//
//} // namespace axis
//
//
//namespace base
//{
//
//
//   class application;
//   class session;
//   class system;
//   class user;
//
//
//} // namespace base
//
//
//namespace core
//{
//
//
//   class application;
//   class session;
//   class system;
//
//
//} // namespace core
//
//
//
////#include "aura/primitive/string/_c_impl.h"
//
//
////#include "aura/platform/aura_main_struct.h"
//
//
////#ifdef WINDOWS
////#pragma warning(disable: 4251)
////#endif
//
////#include "platform/platform/_.h"
//
//class eimpact;
//
//enum e_simple_command : ::i64;
//enum e_message : ::i64;
//enum e_impact : ::i64;
//enum e_id : ::u64;
//enum enum_check: ::i32;
//
//template <typename TYPE>
//struct remove_const_struct { // remove top-level const qualifier
//   using NON_CONST_TYPE = TYPE;
//};
//
//template <typename TYPE>
//struct remove_const_struct< TYPE &> {
//   using NON_CONST_TYPE = TYPE &;
//};
//
//
//template <typename TYPE>
//struct remove_const_struct<const TYPE> {
//   using NON_CONST_TYPE = TYPE;
//};
//
//template <typename TYPE>
//struct remove_const_struct<const TYPE &> {
//   using NON_CONST_TYPE = TYPE &;
//};
//
//template <class TYPE>
//using non_const = typename remove_const_struct<TYPE>::NON_CONST_TYPE;
//
//struct true_type { };
//struct false_type { };
//template < typename POINTER >
//class raw_pointer
//{
//public:
//
//   using RAW_POINTER = POINTER;
//
//};
//
//template < typename TYPE >
//class raw_type
//{
//public:
//
//   using RAW_TYPE = TYPE;
//
//};
//
//template < typename TYPE >
//class raw_type < TYPE * >
//{
//public:
//
//   using RAW_TYPE = TYPE;
//
//};
//
//template < typename TYPE >
//class raw_type < TYPE * & >
//{
//public:
//
//   using RAW_TYPE = TYPE;
//
//};
//
//template < typename TYPE >
//class raw_type < const TYPE * >
//{
//public:
//
//   using RAW_TYPE = TYPE;
//
//};
//
//template < typename TYPE >
//class raw_type < const TYPE * & >
//{
//public:
//
//   using RAW_TYPE = TYPE;
//
//};
//
//
//template < typename LEFT, typename RIGHT >
//inline void assign(LEFT & l, const RIGHT & r) { l = r; }
//
//
////template < typename, typename >
////inline constexpr auto is_strictly_same_type = false_type();
////template < typename TYPE >
////inline constexpr auto is_strictly_same_type < TYPE, TYPE> = true_type();
////
////template < typename TYPE >
////inline constexpr auto is_void = is_strictly_same_type< TYPE, void>;
//
//#ifdef CPP17
//
//template <typename PRED, typename ... Args >
//inline bool _returns_true(PRED pred, const true_type & pred_returns_void, bool bOnVoid, Args... args)
//{
//   pred(args...);
//   return bOnVoid;
//}
//
//template <typename PRED, typename ... Args >
//inline bool _returns_true(PRED pred, const false_type & pred_returns_void, bool, Args... args)
//{
//   return (bool)pred(args...);
//}
//
//template <typename PRED, typename ... Args >
//inline bool returns_true(PRED pred, bool bOnVoid, Args... args)
//{
//
//   return _returns_true(pred, is_void<decltype(pred(args...))>, bOnVoid, args...);
//
//}
//
//template <typename PRED, typename ... Args >
//inline bool _returns_false(PRED pred, const true_type & pred_returns_void, bool bOnVoid, Args... args)
//{
//   pred(args...);
//   return bOnVoid;
//}
//
//template <typename PRED, typename ... Args >
//inline bool _returns_false(PRED pred, const false_type & pred_returns_void, bool, Args... args)
//{
//   return !(bool)pred(args...);
//}
//
//template <typename PRED, typename ... Args >
//inline bool returns_false(PRED pred, bool bOnVoid, Args... args)
//{
//
//   return _returns_false(pred, is_void < decltype(pred(args...)) >, bOnVoid, args...);
//
//}
//
//#endif
//
//template < typename CHAR_TYPE >
//class string_base;
//
//
//struct pixmap;
//
//
//#define CONSIDER_AS(as, use) using use = as
//
//
//using ansistring = string_base < ansichar >;
//using wd16string = string_base < wd16char >;
//using wd32string = string_base < wd32char >;
//using widestring = string_base < widechar >;
//
//
//using string = string_base < ansichar >;
//using wstring = string_base < widechar >;
//
//
//inline const ansichar* __c_str(const string& str);
//
//class machine_event_central;
//
//
//template < typename ARG_KEY >
//inline uptr uptr_hash(ARG_KEY key) { return (uptr)((uptr)key); }
//
////#if OSBIT == 64
//
//template < typename ARG_KEY >
//inline u32 u32_hash(ARG_KEY key) { return (u32)(uptr_hash<ARG_KEY>(key)); }
//
////#endif
//
//
//#define __base(TYPE, ptarget, psource) for(__pointer(TYPE) ptarget = psource; ptarget.is_set(); ptarget.release())
//#define __base_reference(TYPE, ptarget, source) for(__pointer(TYPE) ptarget = &source; ptarget.is_set(); ptarget.release())
//#define __exception(TYPE) __base(TYPE, pe, e)
//
//
//#undef _
//
//#define _(str) (__get_text(str))
//
//CLASS_DECL_AURA string __get_text(string str);
//
//
//
//
////class critical_section;
//
//
////namespace command
////{
////
////   class command;
////
////} // namespace command
//
//
//class trait;
//class create;
//class sync;
//
//
////CLASS_DECL_AURA i32 aura_run_system(::aura::system* psystem);
//
//
////CLASS_DECL_AURA ::estatus aura_run_system_init(::aura::system * psystem);
////CLASS_DECL_AURA ::estatus aura_run_system_proc(::aura::system * psystem);
////CLASS_DECL_AURA ::estatus aura_run_system_term(::aura::system * psystem);
//
//
//template < typename VAR >
//class var_type
//{
//public:
//
//   using VAR_TYPE = VAR;
//
//   VAR_TYPE * this_var() { return (VAR_TYPE *)this; }
//   const VAR_TYPE * this_var() const { return (const VAR_TYPE *)this; }
//
//};
//
////// very short name ([{c}])ontext (switchers, as it as action_context) enums
////enum nullptr_t
////{
////   nullptr
////};
//
//// very short name ([{c}])ontext (switchers, as it as action_context) enums
//enum e_context_switcher_empty
//{
//   cempty
//};
//
//
//enum enum_create_new
//{
//
//   e_create_new
//
//};
//
//
//enum enum_create
//{
//
//   e_create
//
//};
//
//enum enum_defer_new // new - for factoryless_allocation FACTORYLESS_ALLOCATION_ID
//{
//
//   e_defer_new
//
//};
//
//enum enum_move_transfer
//{
//
//   e_move_transfer
//
//};
//
//
//enum enum_copy_clone
//{
//
//   e_copy_clone
//
//};
//
//#define IMPL_OPERATOR_PLUS(type) \
//template < typename TYPE > \
//type operator + (const TYPE & t) const { auto copy = *this; copy.add(t); return copy; }
//
////#include "aura/primitive/math/_.h"
//
////#include "aura/memory/_heap.h"
//
////#include "aura/exception/_const.h"
//
#include "aura/user/_const.h"
//
////#include "aura/user/_experience_const.h"
//
////#include "aura/filesystem/file/_const.h"
//


//#include "aura/graphics/draw2d/_const.h"


//
//
//
//
//
//enum enum_command
//{
//
//   command_none,
//   command_default,
//   command_on_agree_exit,
//   command_france_exit,
//   command_check_exit,
//   command_protocol
//
//};
//
//
//class composite_base;
//class context_object;
//class object;
//
//
////namespace aura
////{
////
////
////   class printer;
////
////
////
////} // namespace aura
//
////
////extern "C"
////CLASS_DECL_AURA void register_aura_library(const char * psz, ::apex::library * plibrary);
////
////
////extern "C"
////CLASS_DECL_AURA void register_get_new_aura_library(const char* psz, PFN_NEW_AURA_LIBRARY pfnNewAuraLibrary);
//
//
//#define DECLARE_NEW_AURA_LIBRARY(X) extern "C" \
//::apex::library * X##_new_aura_library()
//
//
//#define REGISTER_GET_NEW_AURA_LIBRARY(X) register_get_new_aura_library(#X, &X##_get_new_library)
//
//
//namespace install
//{
//
//
//   class installer;
//
//
//} // namespace install
//
//
//template<class T>
//struct remove_reference
//{
//   typedef T TYPE;
//};
//
//template<class T>
//struct remove_reference<T&>
//{
//   typedef T TYPE;
//};
//
//template<class T>
//struct remove_reference<T&&>
//{
//   typedef T TYPE;
//};
//
//template<class T> inline
//typename remove_reference<T>::TYPE&& move(T && t)
//{
//
//   return (static_cast<typename remove_reference<T>::TYPE&&>(t));
//
//}
//
//
//
//
//template < class T >
//class pointer;
//
//template < class T >
//class pointer_array;
//
//
////#define __composite(TYPE) ::reference < TYPE >
//
//#define __pointer(TYPE) ::pointer < TYPE >
//#define __pointer_array(TYPE) ::pointer_array < TYPE >
//#define __address_array(TYPE) ::comparable_array < TYPE * >
//
//namespace draw2d
//{
//
//   class font_enum_item;
//
//   using font_enum_item_array = __pointer_array(font_enum_item);
//
//} // namespace draw2d
//
//template < typename T >
//class result_pointer;
//
//#define __result(T) ::result_pointer < T >
//
//template < class TYPE >
//inline auto & __typed(TYPE & t) { return t; }
//
//template < class POINTER_TYPE >
//inline auto & __typed(POINTER_TYPE * p) { return *p; }
//
//template < class POINTER_POINTER_TYPE >
//inline auto & __typed(POINTER_POINTER_TYPE ** p) { return **p; }
//
//
//template < class TYPE >
//inline auto & __typed_defer_new(TYPE & t) { return t; }
//
//template < class POINTER_TYPE >
//inline auto & __typed_defer_new(POINTER_TYPE *& p) { if (!p) p = new POINTER_TYPE; return *p; }
//
//template < class POINTER_POINTER_TYPE >
//inline auto & __typed_defer_new(POINTER_POINTER_TYPE ** p) { if (!*p) *p = new POINTER_POINTER_TYPE;  return **p; }
//
//template < class T >
//inline auto & __typed_defer_new(__pointer(T) & p) { if (!p) p = new T; return *p; }
//
//template < class T >
//inline auto & __typed_defer_create(__pointer(T) & p) { if (!p) __construct(p); return *p; }
//
//template < typename T >
//inline __pointer(T) move_transfer(T * p);
//
//#define __new(...) move_transfer( new __VA_ARGS__ )
//
//
//template < typename TYPE1, typename TYPE2 >
//inline void __dynamic_cast(TYPE1*& ptype1, const TYPE2* ptype2)
//{
//
//   ptype1 = dynamic_cast <TYPE2*> (ptype2);
//
//}
//
//
//template < typename TYPE1, typename TYPE2 >
//inline void __dynamic_cast(__pointer(TYPE1)& ptype1, const TYPE2* ptype2)
//{
//
//   ptype1 = ptype2;
//
//}
//
//
//template < typename TYPE1, typename TYPE2 >
//inline void __dynamic_cast(__pointer(TYPE1)& ptype1, const __pointer(TYPE2)& ptype2)
//{
//
//   ptype1 = ptype2;
//
//}
//
//
//template < typename TYPE1, typename TYPE2 >
//inline void __dynamic_cast(TYPE1*& ptype1, const __pointer(TYPE2)& ptype2);
//
//
//template < typename T >
//inline bool __found(const __pointer(T) & p);
//
//
//template < typename T >
//inline bool __not_found(const __pointer(T) & p);
//
//
//template < typename TDST, typename TSRC >
//inline __pointer(TDST) & clone(__pointer(TDST) & dst, const __pointer(TSRC) & src);
//
//template < typename T >
//inline __pointer(T) clone(const __pointer(T) & t);
//
//
//template < class T >
//class guard_pointer;
//
//
//#define gp(TYPE) ::guard_pointer < TYPE >
//
//
//#define clone_impl(name) inline name * clone() { return __new(name(*this)); }
//
//
//#define DOUBLE_PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844
//
//
//template < typename TYPE > inline TYPE* __random_bytes(TYPE* p, memsize s);
//template < typename TYPE > inline TYPE& __random(TYPE& t);
//template < typename TYPE > inline TYPE __random();
//inline float __random(float f1, float f2);
//inline double __random(double d1, double d2);
//template < typename INT > inline INT __random_int(INT i1, INT i2);
//inline i64 __random(i64 i1, i64 i2);
//inline i32 __random(i32 i1, i32 i2);
//
//template < typename TYPE >
//inline void swap(TYPE& a, TYPE& b)
//{
//   auto t = a;
//   a = b;
//   b = t;
//
//}
//
//inline bool is_null(const void * p, size_t s)
//{
//
//   const auto max = (size_t)(-1);
//
//   return ((size_t)p) <= s || ((size_t)p) >= (max - s);
//
//}
//
//
//
//template < typename TYPE >
//inline bool is_null(const TYPE * p)
//{
//
//   const auto max = (size_t)(-1) - 65536;
//
//   return ((size_t) p <= 65536) || ((size_t)p) >= (max);
//
//}
//
//
//template < >
//inline bool is_null(const void * p)
//{
//
//   return is_null(p, 65536);
//
//}
//
//
//template < typename TYPE >
//inline bool is_set(const TYPE * p)
//{
//
//   return !is_null(p);
//
//}
//
//
//template < typename TYPE >
//inline bool is_ref_set(const TYPE & t)
//{
//
//   return is_set(&t);
//
//}
//
//
//template < typename TYPE >
//inline bool is_ok(const TYPE* p)
//{
//
//   return ::is_set(p);
//
//}
//template < typename TYPE >
//inline bool is_ok(const __pointer(TYPE) & p)
//{
//
//   return ::is_ok(p.m_p);
//
//}
//
//
//template < typename TYPE >
//inline bool nok(const TYPE* p)
//{
//
//   return !::is_ok(p);
//
//}
//
//
//
//class istring;
//class var;
//class property_set;
//class object;
////class base_edit;
//class var_array;
//class property;
//
//
//class timer_callback;
//
//
////namespace handle
////{
////
////   class ini;
////
////} // namespace handle
//
//namespace aura
//{
//
//   class Timer;
//
//};
//
//class timer;
//
//typedef bool FN_TIMER(timer * ptimer);
//typedef FN_TIMER * PFN_TIMER;
//
//#define NOK_IMAGE_OBJECT (NONE_ID)
//#define IMAGE_OBJECT_OK (SUCCESS)
//#define DEFAULT_CREATE_IMAGE_OBJECT_FLAG (IMAGE_OBJECT_OK)
//
//#include "aura/const/_const.h"
//
//
////#include "aura/primitive/primitive/_memory.h"
//
//
//inline bool is_impact_group(::u64 u, ::u64 uGroup) { return u >= uGroup && u < uGroup + 1000; }
//inline bool is_impact_subgroup(::u64 u, ::u64 uGroup) { return u >= uGroup && u < uGroup + 100; }
//
//
class image;
namespace draw2d{class icon;}
//
using image_pointer = __pointer(::image);
using icon_pointer = __pointer(::draw2d::icon);
//
//
using image_result = __result(::image);
using icon_result=__result(::draw2d::icon);
//
//
//class command_line;
//
//
//using command_line_pointer = __pointer(command_line);
//
//
//namespace message
//{
//
//
//   class mouse;
//
//
//} // namespace message
//
//
//#include "aura/user/_const.h"
#include "acme/user/_const_key.h"

namespace draw2d
{


   class graphics;


   class icon;
   class cursor;
   class region;
   class brush;
   class font;
   using brush_pointer = __pointer(brush);
   using font_pointer = __pointer(font);


} // namespace draw2d



//
//template < typename T1, typename T2, typename ARG_T1 = const T1 &, typename ARG_T2 = const T2 & >
//class pair;
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE = const VALUE &, class PAIR = pair < KEY, VALUE, ARG_KEY, ARG_VALUE > >
//class map;
//
//template < class ENUM >
//class flags;
//
//template < class EENUM, EENUM edefault = (EENUM)0 >
//class base_enum;
//
//class form_property_set;
//
//
////namespace user
////{
////
////
////   class create;
////   class control_event;
////   class item;
////   class check;
////   class create_struct;
////   class command;
////   class interaction_impl;
////   class primitive;
////   class frame;
//////   class menu;
////   //class controller;
////   //class document;
////
////   //class impact_system;
////   //class impact_data;
////   class printer;
//////   class impact;
////   class primitive;
////   class interaction;
////   class layout;
////   //class place_holder;
////   //class menu_item;
////   //class form;
////   class style;
////   class menu_interaction;
////   //class tab;
////   class tab_pane;
////   class check_box;
////   class toolbar;
////   class split_layout;
////   class style_rect;
////   class scroll_bar;
////   class scroll_data;
////
////
////   //using color_map = map < e_color, e_color, COLORREF, COLORREF >;
////   //using font_map = map < e_font, e_font, ::draw2d::font_pointer >;
////   using eflag = flags < enum_flag >;
////   //using flag_map = map < e_flag, e_flag, bool, bool >;
////   //using rect_map = ::map < e_rect, e_rect, style_rect >;
////   //using int_map = ::map < e_int, e_int, int, int >;
////   //using double_map = ::map < e_double, e_double, double, double >;
////   //using color_map = map < e_color, e_color, COLORREF, COLORREF >;
////   //using eelement = base_enum < e_element >;
////   //using translucency_map = ::map < e_element, e_element, e_translucency, e_translucency >;
////
////
////
////#if defined(_UWP) || defined(APPLE_IOS) || defined(ANDROID)
////
////   class native_window_initialize;
////
////#endif
////
////
////} // namespace user
////=======
namespace user
{


   class create;
   class control_event;
   class item;
   class check;
   class create_struct;
   class command;
   class interaction_impl;
   class primitive;
   class frame;
   class printer;
   class primitive;
   class interaction;
   class interaction_layout;
   class form;
   class form_callback;
   class menu_interaction;
   class toolbar;
   class split_layout;
   class style_rect;
   class scroll_bar;
   class scroll_data;
   class style;
   class box;
   class interaction_pointer_array;

   using style_pointer = __pointer(style);

   using eflag = flags < enum_flag >;


#if defined(_UWP) || defined(APPLE_IOS) || defined(ANDROID)

   class native_window_initialize;

#endif


} // namespace user


class form_document;


//
//
//
//namespace aura
//{
//
//
//   class application;
//   class system;
//   class application_message;
//
//   class command;
//
//   class str;
//   class str_context;
//
//
//} // namespace aura
//
//namespace gpu
//{
//
//   class approach;
//
//} // namespace gpu
//
//
//namespace data
//{
//
//
//   class listener;
//   class data;
//   class simple_data;
//   class data_container_base;
//
//
//} // namespace data
//
//namespace sockets // only usable from base.dll and dependants
//{
//
//   class sockets; // only usable from base.dll and dependants
//
//
//} // namespace sockets // only usable from base.dll and dependants
//
//
//namespace url
//{
//
//   class department; // only usable from base.dll and dependants
//
//
//} // namespace url
//
//
//class compress_department; // only usable from axis.dll and dependants
//
//class channel;
//
//class dump_context;
//
//class id_space;
//class ptra;
//class factory_item_base;
//class fixed_alloc_no_sync;
//class critical_section;
//class var_array;
//class thread;
//class channel;
//class critical_section;
//class mutex;
//class id;
//
//namespace colorertake5
//{
//
//   class ParserFactory;
//
//
//} // namespace colorertake5
//
//
////class pixmap;
//
//
//class memory;
//
//
//CLASS_DECL_AURA ::aura::system* platform_create_system(HINSTANCE hinstance);
//CLASS_DECL_AURA ::aura::session* platform_create_session();
//
//
////namespace plane
////{
////
////   class session;
////   class system;
////   //class cube;
////
////
////} // namespace plane
//
//
//
//
//#define SECOND_NANOS 1000000000
//
//
//namespace datetime
//{
//
//
//   class department;
//   class time;
//   class time_span;
//
//
//} // namespace datetime
//
//
//
//template < typename Type,typename RawType = Type >
//class string_array_base;
//
//
//typedef string_array_base < string > string_array;
//
//
//namespace file
//{
//
//   class listing;
//   class path;
//   typedef CLASS_DECL_AURA ::string_array_base < ::file::path,string > patha;
//   class file;
//
//   enum e_type
//   {
//
//      type_none,
//      type_folder,
//      type_file,
//      type_element,
//
//   };
//
//} // namespace file
//
//
//class machine_event_data;
//
//namespace hotplugin
//{
//
//   class host;
//   class plugin;
//
//}
//
//
//
//namespace html
//{
//
//
//   class html;
//
//
//} // namespace html
//
//
namespace audio
{


   class plugin;


} // namespace audio
//
//
////#include "aura/primitive/collection/forward.h"
//
//enum e_optional
//{
//
//   optional,
//
//};
//
//enum e_no_init
//{
//
//   no_init,
//
//};
//
//class CLASS_DECL_AURA set
//{
//public:
//
//   e_set    m_eset;
//
//   inline set(e_optional) { m_eset = set_none; }
//   inline set() { m_eset = set_none; }
//   inline set(int i) { operator = (i); }
//   inline set(bool b) { operator = (b); }
//
//   inline bool isFalse() const { return is_false(); }
//
//   inline bool is_false() const { return m_eset < set_empty; }
//
//   inline bool undefined() const { return is_empty(); }
//
//   inline bool is_empty() const { return m_eset == set_empty; }
//
//   inline bool is_none() const { return is_empty(); }
//
//   inline bool is_true() const { return m_eset > set_empty; }
//
//   inline bool is_true(bool bDefault) const { return m_eset ? isTrue() : bDefault; }
//
//   inline bool isTrue() const { return is_true(); }
//
//   inline bool is_optional() const { return !m_eset; }
//
//   inline bool isOptional() const { return is_optional(); }
//
//   inline operator bool() const { return isTrue(); }
//
//   inline bool operator !() const { return isFalse(); }
//
//   inline bool operator < (int i) const { return (int)m_eset < i; }
//
//   inline bool operator <= (int i) const { return (int)m_eset <= i; }
//
//   inline bool operator > (int i) const { return (int)m_eset > i; }
//
//   inline bool operator >= (int i) const { return (int)m_eset >= i; }
//
//   inline bool operator == (int i) const { return (int)m_eset == i; }
//
//   inline bool operator != (int i) const { return !operator ==(i); }
//
//   inline set & operator = (int i) { m_eset = (e_set)i; return *this; }
//
//   inline set & operator = (bool b) { m_eset = (b ? set_true : set_false); return *this; }
//
//   inline void defer(int i) { if(is_empty()) operator =(i); }
//
//   inline set deferred(int i) const { if(is_empty()) return i; else return m_eset; }
//
//   inline set operator()(int i) const { return deferred(i); }
//
//};
//
//inline bool __is_true(bool b) { return b; }
//inline bool __is_true(const ::set& set) { return set; }
//
//inline bool __is_false(bool b) { return !b; }
//inline bool __is_false(const ::set& set) { return !set; }
//
//inline bool __is_optional(bool b) { return false; }
//inline bool __is_optional(const ::set& set) { return set.isOptional(); }
//
//
//#define __optional_is_true(flag, option) ((bool)(flag) || (__is_optional(flag) && (option)))
//
//
//#include "aura/platform/auto.h"
////#include "aura/primitive/comparison/compare.h"
////#include "aura/primitive/primitive/papaya.h"
//
//
//
//
//
//
//template <class t>
//inline void delptr(t *& p)
//{
//   if(p != nullptr)
//   {
//      delete p;
//      p = nullptr;
//   }
//}
//
//template < typename T >
//inline int type_is_null(const T * p)
//{
//   return (((UINT_PTR)(void *)p) < max(4096, sizeof(T)));
//}
//
//
////#include "aura/primitive/string/_uhash.h"
//
//
//class allocer;
//
//
//
//
//
//namespace aura
//{
//
//   template < typename T >
//   inline void del(T * & p)
//   {
//
//      //Thank you Fiora a Eterna!!
//
//      //Fiora Aeterna☄ ‏@FioraAeterna 20m20 minutes ago
//
//      //   maybe it's cynical but I'm starting to think the real reason so many newer games have constant autosaves is because they crash all the time
//      //   Details
//
//      // BRT 2015-02-18 19:08
//      // catch all (...) here in acme::del ... but should remove try catch from all underlying calls (frees, memory_frees, memory_dbg_frees).
//
//      try
//      {
//
//         //Thank you Dunno_Aye for the is_null!!
//
//         if(!is_null(p))
//         {
//
//            T * pdel = p;
//
//            p = nullptr;
//
//            delete pdel;
//
//         }
//
//      }
//      catch(...)
//      {
//
//      }
//
//   }
//
//
//   template < typename T >
//   inline void delobj(T * & p);
//
//   template < typename T >
//   inline void adel(T * & p)
//   {
//
//      //Thank you Fiora a Eterna!!
//
//      //Fiora Aeterna☄ ‏@FioraAeterna 20m20 minutes ago
//
//      //   maybe it's cynical but I'm starting to think the real reason so many newer games have constant autosaves is because they crash all the time
//      //   Details
//
//      // BRT 2015-02-18 19:08
//      // catch all (...) here in acme::del ... but should remove try catch from all underlying calls (frees, memory_frees, memory_dbg_frees).
//
//      try
//      {
//
//         if(p != nullptr)
//         {
//
//            delete[] p;
//
//            p = nullptr;
//
//         }
//
//      }
//      catch(...)
//      {
//
//      }
//
//   }
//
//
//   template < typename T >
//   inline void free(T * & p)
//   {
//
//      //Thank you Mummi!!
//
//      //Nice late afternoon coffee of ever!!
//
//      //Thank you Fiora a Eterna!!
//
//      //Fiora Aeterna☄ ‏@FioraAeterna some minutes ago
//
//      //   maybe it's cynical but I'm starting to think the real reason so many newer games have constant autosaves is because they crash all the time
//      //   Details
//
//      // BRT 2016-11-23 19:08
//      // catch all (...) here in acme::del ... but should remove try catch from all underlying calls (frees, memory_frees, memory_dbg_frees).
//
//      try
//      {
//
//         if (p != nullptr)
//         {
//
//            void * pdel = (void *) p;
//
//            p = nullptr;
//
//            ::free(pdel);
//
//         }
//
//      }
//      catch (...)
//      {
//
//      }
//
//   }
//
//
//   template < typename T >
//   inline void memory_free(T * & p)
//   {
//
//      //Thank you Mummi!!
//
//      //Nice late afternoon coffee of ever!!
//
//      //Thank you Fiora a Eterna!!
//
//      //Fiora Aeterna☄ ‏@FioraAeterna some minutes ago
//
//      //   maybe it's cynical but I'm starting to think the real reason so many newer games have constant autosaves is because they crash all the time
//      //   Details
//
//      // BRT 2016-11-23 19:08
//      // catch all (...) here in acme::del ... but should remove try catch from all underlying calls (frees, memory_frees, memory_dbg_frees).
//
//      try
//      {
//
//         if (p != nullptr)
//         {
//
//            void * pdel = (void *)p;
//
//            p = nullptr;
//
//            ::memory_free(pdel);
//
//         }
//
//      }
//      catch (...)
//      {
//
//      }
//
//   }
//
//
//   template < typename T >
//   inline T * reset(T * & p, T * pNew)
//   {
//
//      ::acme::del(p);
//
//      return p = pNew;
//
//   }
//
//   template < typename T >
//   inline T * reset(T * & p)
//   {
//
//      ::acme::del(p);
//
//      return p = new T;
//
//   }
//
//} // namespace aura
//
//
//
//
//
////#include "aura/memory/malloc.h"
//
//class image_list;
//
//
//
//
//struct SIZEPARENTPARAMS
//{
//
//   RECT  rect;       // parent client rectangle (trim as appropriate)
//   SIZE  sizeTotal;  // total size on each side as on_layout proceeds
//   bool  bStretch;   // should stretch to fill all space
//
//};
//
//
//typedef struct RECTD RECTD;
//
//
//namespace aura
//{
//
//
////#if defined _UWP && defined(__cplusplus_winrt)
////
////   interface class system_window
////   {
////
////      virtual Windows::Foundation::Rect get_window_rect() = 0;
////      virtual Windows::Foundation::Point get_cursor_pos() = 0;
////
////
////
////   };
////
////   CLASS_DECL_AURA bool get_window_rect(system_window ^ pwindow,RECTD * prect);
//
////   CLASS_DECL_AURA bool get_window_rect(system_window ^ pwindow,RECT * prect);
//
////
////#endif
//
//
//   class file;
//
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
//CLASS_DECL_AURA bool enable_trace_category(e_trace_category ecategory, bool bEnable = true);
//
//// only usable from axis and axis dependants
//namespace aura
//{
//
//   class application;
//   class session;
//   class system;
//
//}
//
//
//// only usable from base and base dependants
//namespace base
//{
//
//   class application;
//   class session;
//   class system;
//
//}
//
//// only usable from aura and aura dependants
//namespace aura
//{
//
//   class application;
//   class session;
//   class system;
//
//}
//
//
//class app_core;
//
//
////extern "C"
////typedef ::aura::system *  CREATE_SYSTEM(app_core * pappcore);
////typedef ::aura::system * CREATE_SYSTEM();
//
////typedef CREATE_SYSTEM * LPFN_CREATE_SYSTEM;
//
////CLASS_DECL_AURA extern LPFN_CREATE_SYSTEM g_pfn_create_system;
////CLASS_DECL_AURA extern const char * g_pszCooperativeLevel;
////CLASS_DECL_AURA extern int g_iDerivedApplication; // one-based-index of derived application, zero if Main application
//
//
//namespace data
//{
//
//
//   class item;
//
//
//} // namespace data
//
//
//namespace xml
//{
//
//
//   class node;
//   class document;
//
//
//} // namespace xml
//
//
//
//
//
//
//enum e_extract
//{
//
//   extract_none,
//   extract_first,
//   extract_all
//
//};
//
//
//namespace str
//{
//
//
//   namespace international
//   {
//
//
//      class locale_schema;
//
//
//   } // namespace international
//
//
//} // namespace str
//
//
//

namespace draw2d
{


   class graphics;


} // namespace draw2d

//
////class random_access_iterator
////{
////public:
////};
//
//
//
//
//
//class event;
//
//
//class thread;
//
//
//
//
//class thread;
//
//
//typedef pointer < thread > thread_pointer;
//typedef pointer_array < thread > thread_spa;
//
//
////class thread_impl;
//
//
////typedef pointer < thread_impl > thread_impl_pointer;
//
//
//namespace html
//{
//
//   class html; // defined and set by html library/component
//
//}
//
//
//#define SCAST_PTR(TYPE, ptarget, psource) TYPE * ptarget = dynamic_cast < TYPE * > (psource);
//#define SCAST_REF(TYPE, rtarget, psource) TYPE & rtarget = *(dynamic_cast < TYPE * > (psource))
//
//
//
//#undef Sys
//#define Sys(pobject) (*::get_context_system(pobject))
//
//#undef Sess
//#define Sess(pobject) (*::get_context_session(pobject))
//
//#undef App
//#define App(pobject) (*::get_context_application(pobject))
//
//
//#define System Sys(get_context())
//#define Session Sess(get_context())
//#define Application App(get_context())
//#define ThisApp (*::application_consumer < application >::get_app())
//#define NamespaceApp(namespace) (*::application_consumer < ::namespace::application >::get_app())
//
//
//#undef Ctx
//#define Ctx(pobject) (*(::get_context(pobject)))
//#define Context (Ctx(get_context()))
//
//
//// return - result - if not ok
//#ifndef RINOK
//#define RINOK(x) { i32 __result__ = (x); if (__result__ != 0) return __result__; }
//#endif
//
//// __throw( - exception - result exception - if not ok
//#ifndef TINOK
//#define TINOK(e, x) { i32 __result__ = (x); if (__result__ != 0) __throw(e(get_context_application(), __result__)); }
//#endif
//
//
//#ifdef WINDOWS
//#pragma warning(disable: 4251)  // using non-exported as public in exported
//#endif
//
//
//#ifndef WINDOWS_DESKTOP
//
//typedef void * HDWP;
//
//#endif
//
//#ifdef APPLE_IOS
//
//struct plane_system;
//
//#endif
//
//typedef  void(*PFN_factory_exchange)();
//
//// #ifdef WINDOWS
//// CLASS_DECL_AURA bool defer_co_initialize_ex(bool bMultiThread, bool bDisableOleDDE = false);
//// #endif
//
//class generic;
//
//class var;
//
//using argument = var;
//
//class var_array;
//
//using arguments = var_array;
//
//class context;
//
//
//
//
CLASS_DECL_AURA bool aura_init();
CLASS_DECL_AURA bool aura_term();
//
CLASS_DECL_AURA bool __node_aura_pre_init();
CLASS_DECL_AURA bool __node_aura_pos_init();
//
CLASS_DECL_AURA bool __node_aura_pre_term();
CLASS_DECL_AURA bool __node_aura_pos_term();
//
//
////extern "C" CLASS_DECL_AURA PFN_NEW_AURA_LIBRARY get_get_new_aura_library(const char * psz);
////extern "C" CLASS_DECL_AURA void register_get_new_aura_library(const char* psz, PFN_NEW_AURA_LIBRARY pfnNewAuraLibrary);
//
//
////CLASS_DECL_AURA ::apex::library & get_library(const char* psz);
////CLASS_DECL_AURA void register_aura_library(const char* psz, ::apex::library* plibrary);
////
////CLASS_DECL_AURA ::context * get_context();
////CLASS_DECL_AURA inline ::context * get_context(::layered * pobjectContext);
////CLASS_DECL_AURA inline ::context * get_context(::context * pcontext);
//
//
//CLASS_DECL_AURA void set_global_application(::aura::application * papp);
//CLASS_DECL_AURA ::aura::application * get_global_application();
//
//
//CLASS_DECL_AURA ::aura::application * get_context_application();
//CLASS_DECL_AURA inline ::aura::application * get_context_application(::layered * pobjectContext);
//CLASS_DECL_AURA inline ::aura::application * get_context_application(::aura::application * papp);
//CLASS_DECL_AURA inline ::aura::application * get_app() { return get_context_application(); }
//
//
//CLASS_DECL_AURA::aura::session * get_context_session();
//CLASS_DECL_AURA inline ::aura::session * get_context_session(::layered * pobjectContext);
//CLASS_DECL_AURA inline ::aura::session * get_context_session(::aura::session * psession);
//
//CLASS_DECL_AURA::aura::system * get_context_system();
//CLASS_DECL_AURA inline ::aura::system * get_context_system(::layered * pobjectContext);
//CLASS_DECL_AURA inline ::aura::system * get_context_system(::aura::system * psystem);
//
//
//#define BAD_WCHAR ((widechar)(-1))
//
//
//#define ARRAY_SIZE(a) (sizeof(a)/sizeof(*(a)))
//
//
//class var;
//class id;
//
//
//namespace calculator
//{
//
//
//   class value;
//
//
//} // namespace calculator
//
//
//
//
//
//
//#ifdef APPLEOS
//#undef err_none
//#endif
//
//#ifdef WINDOWS
//
//template < typename POINTER_TYPE >
//class cotaskptr;
//
//#endif
//
//class type;
//
//
//#include "aura/primitive/string/_.h"
//
//
//#include "aura/platform/definition.h"
//
//#include "aura/memory/new.h"
//
//#include "aura/platform/lparam.h"
//#include "aura/platform/muldiv64.h"
//
//
//
//
//#include "aura/platform/auto_pointer.h"
//
//
//// C-includes
////#include "aura/os/os.h"
//
//class thread_parameter;
//
//#include "aura/primitive/primitive/enum.h"
//
//
//#include "aura/primitive/primitive/interlocked_long.h"
//#include "aura/primitive/primitive/interlocked_long_pulse.h"
//#include "aura/primitive/primitive/type.h"
//#include "aura/primitive/primitive/id.h"
//#include "aura/primitive/primitive/uid.h"
//
//
//namespace primitive
//{
//
//
//   template < typename TYPE >
//   class member;
//
//
//   template < typename TYPE >
//   class composite;
//
//
//   template < typename TYPE >
//   class reference;
//
//
//} // namespace primitive
//
//
//#define __member(TYPE) ::primitive::member < TYPE >
//#define __composite(TYPE) ::primitive::composite < TYPE >
//#define __reference(TYPE) ::primitive::reference < TYPE >
//
//
//
//
//template < typename TYPE >
//inline bool is_null(const __pointer(TYPE) & p)
//{
//
//   return ::is_null(p.m_p);
//
//}
//
//template < typename TYPE >
//inline bool is_null(const __composite(TYPE) & p)
//{
//
//   return p.is_null();
//
//}
//
//template < typename TYPE >
//inline bool is_null(const __reference(TYPE) & p)
//{
//
//   return p.is_null();
//
//}
//
//
//template < typename TYPE >
//inline bool is_set(const __pointer(TYPE) & p)
//{
//
//   return p.is_set();
//
//}
//
//template < typename TYPE >
//inline bool is_set(const __composite(TYPE) & p)
//{
//
//   return p.is_set();
//
//}
//
//template < typename TYPE >
//inline bool is_set(const __reference(TYPE) & p)
//{
//
//   return p.is_set();
//
//}
//
//template < typename TYPE >
//inline bool is_null_ref(const TYPE & t)
//{
//
//   return is_null(&t);
//
//}
//
//
//template < typename TYPE >
//inline bool is_set_ref(const TYPE & t)
//{
//   return !is_null_ref(t);
//}
//
//
//
//
//#include "aura/primitive/primitive/pointer.h"
//#include "aura/primitive/primitive/pointer2.h"
//
//
//template < class POINTER_TYPE >
//inline auto & __typed(__pointer(POINTER_TYPE) & p) { return *p; }
//
//
//#include "aura/multithreading/thread_parameter.h"
//
//#include "aura/platform/keep_true.h"
//
//using file_pointer = __pointer(::file::file);
//
//using file_result = __result(::file::file);
//
//class stream;
//class binary_stream;
//
//template < typename BASE_TYPE >
//inline stream & __save_object(stream & stream, BASE_TYPE * p);
//
//template < typename BASE_TYPE >
//inline stream & __save_object(stream & stream, const __pointer(BASE_TYPE) & p)
//{
//   return __save_object(stream, (BASE_TYPE *) p.m_p);
//}
//
//#include "aura/primitive/primitive/logic.h"
//
//
//
//#include "aura/primitive/math/static_numeric_info.h"
//#include "aura/primitive/math/numeric_info.h"
//
//
//
//
//#include "aura/primitive/math/c_number.h"
//
//using wparam = c_number < WPARAM >;
//
//
//
//
//#include "aura/primitive/math/math_clip.h"
//
//
//#include "aura/platform/tick.h"
//
//
//#include "aura/primitive/datetime/duration.h"
//
//#include "aura/platform/common.h"
//
//
////#include "aura/primitive/string/_.h"
//
//
//#include "aura/primitive/datetime/date_span.h"
//#include "aura/primitive/datetime/time_span.h"
//#include "aura/primitive/datetime/time.h"
//#include "aura/primitive/datetime/zonetime.h"
//#include "aura/primitive/datetime/file_time_span.h"
//#include "aura/primitive/datetime/file_time.h"
//
//
//
//
//
//
#include "aura/os/_.h"
//
//
//class update;
//
//namespace status
//{
//
//   class result;
//
//} // namespace status
//
//namespace message
//{
//   class message;
//
//} // namespace status
//
//class parents;
//
//class children;
//
//
//namespace exception
//{
//
//   class exception;
//   using exception_pointer = __pointer(exception);
//
//} // namespace exception
//
//
//using exception_pointer = ::exception::exception_pointer;
//
//
//class event_map;
//class thread_ptra;
////class traits;
//
//
//namespace papaya
//{
//
//   class topic;
//
//} // namespace papaya
//
//
//class memory_base;
//
//
//
//template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename RECT_BASE_TYPE >
//class size_type;
//
//using size = size_type < SIZE, POINT, RECT >;
//
//
//#include "aura/primitive/math/cast.h"
//
//
//#include "aura/primitive/primitive/block.h"
//#include "aura/memory/memory.h"
//
//#include "aura/primitive/primitive/cflag.h"

namespace user
{

   using estate = cflag < enum_state >;
   using eelement = cflag < e_element >;

} // namespace user


//
//
//
//
//
////using eobject = cflag < ::enum_object >;
//class action_context;
//
//#include "aura/primitive/primitive/eobject.h"
//
//using emessagebox = cflag < enum_message_box >;
//
//#include "aura/primitive/primitive/function_base.h"
//
//
//
//
//
//#include "aura/primitive/primitive/generic.h"
//#include "aura/primitive/primitive/task.h"
//#include "aura/primitive/primitive/compare_pred.h"
//
//
//#include "aura/platform/status.h"
//#include "aura/primitive/primitive/enum_type.h"
//
//using efileopen = cflag < ::file::e_open >;
//
//using eiostate = ::cflag < ::file::e_iostate >;
//
//using ecommand = ::enum_type < enum_command >;
//
//using echeck = ::enum_type < enum_check >;
//
//
//typedef ::estatus THREAD_PROCEDURE(thread_parameter parameter);
//
//
//inline bool succeeded(const ::var & var);
//inline bool succeeded(const ::property & set);
//
//inline bool failed(const ::var & var) { return !::succeeded(var); }
//inline bool failed(const ::property & set) { return !::succeeded(set); }
//
//
//#define __inner_release(outer, inner) ::release(outer, outer->inner)
//
//
//#include "aura/primitive/primitive/function_base.h"
//
//
//#include "aura/primitive/primitive/member.h"
//
//
//#include "aura/primitive/primitive/context_object.h"
//
//
//#include "aura/primitive/primitive/trait.h"
//
//
//
//
//
//
//
//#include "aura/primitive/primitive/_papaya.h"
//
//
//
//
//
//
//
//
//#include "aura/primitive/geometry2d/_.h"
//
//
////#include "aura/primitive/primitive/context_object.h"
//
//
//#include "aura/primitive/primitive/_factory_prefix.h"
//
//
//#include "aura/primitive/collection/decl.h"
//
//#include "aura/primitive/collection/raw_array_decl.h"
//
//
//#include "aura/primitive/collection/comparable_eq_array.h"
//#include "aura/primitive/collection/comparable_array.h"
//#include "aura/primitive/collection/comparable_raw_array.h"
//
//
//#include "aura/primitive/collection/pointer_array_process.h"
//
//#include "aura/primitive/collection/pointer_array.h"
//
//
//
////#include "aura/primitive/collection/_papaya_array_decl.h"
//#include "aura/primitive/collection/_papaya_heap.h"
//
//
//#include "aura/primitive/collection/address_array.h"
//
//
//#include "aura/primitive/collection/_papaya.h"
//
//
////#include "aura/primitive/collection/pointer2_array.h"
//
//class sticker;
//
//
//inline ::generic * trace_object(::generic * pobjectContext) { return pobjectContext; }
//
//template < typename POINTER_TYPE >
//class ptr_array;
//
////using composite_ptra = __pointer_array(::generic); // Please use just for composition (ownership).
//
////using reference_ptra = __pointer_array(::generic); // Please use just for reference (member-based).
//
////using object_ptra = __pointer_array(::context_object); // Please use just for keeping non-member-based references.
//
//using object_ptra = __pointer_array(::generic); // Please use just for keeping non-member-based references.
//
//using object_addra = __address_array(::generic); // Please use just for keeping non-member-based references.
//
//class object_meta;
//
//
//#define __composite_array(TYPE) ::array < __composite(TYPE) >
//#define __reference_array(TYPE) ::array < __reference(TYPE) >
//
//namespace http
//{
//
//   class context;
//
//} // namespace http
//
//template < typename PRED > inline auto __task_procedure(PRED pred, ::generic * pobjectHold = nullptr);
//
//template < typename PRED > inline auto __task_callback(PRED pred, ::generic* pobjectHold = nullptr);
//
//class context;

namespace draw2d
{

   class graphics;
   class pen;

   using graphics_pointer = __pointer(graphics);
   using pen_pointer = __pointer(pen);




} // namespace draw2d


////class create_thread;
//
//using generic_pointer = __pointer(::generic);
//
//
//#ifdef WINDOWS_DESKTOP
//
//
//#include "aura/os/windows/itemidlist.h"
//
//
//#endif
//
//class procedure;
//class callback;
//
//
//namespace core
//{
//
//
//   class user;
//
//
//} // namespace core
//
//
//#include "aura/exception/_.h"
//
//#include "aura/primitive/comparison/var_strict.h"
//
//#include "aura/filesystem/filesystem/path.h"
//
//#include "aura/filesystem/filesystem/path_object.h"
//
//#include "aura/primitive/collection/_.h"
//
//#include "aura/primitive/primitive/procedure.h"
//
//#include "aura/primitive/primitive/callback.h"
//
//#include "aura/primitive/geometry2d/collection.h"
//
//#include "aura/primitive/geometry3d/_.h"
//
//class message_box;
//
//#include "aura/primitive/primitive/object.h"
//
//#include "aura/primitive/primitive/object_meta.h"
//
//#include "aura/platform/trace.h"
//
//#include "aura/platform/pred_procedure.h"
//
//#include "aura/platform/debug.h"
//
//#include "aura/platform/class.h"
//
//#include "aura/primitive/comparison/md5.h"
//
////#include "aura/platform/conv.h"
//
//#include "aura/primitive/primitive/request_interface.h"
//
//#include "aura/multithreading/sync_result.h"
//
////#include "aura/multithreading/sync.h"
//
////#include "aura/xml/exportable.h"
//
////#include "aura/xml/importable.h"
//
//#include "aura/primitive/comparison/_.h"
//
//#include "aura/primitive/primitive/traits.h"
//
////#include "aura/static_setup.h"
//
//CLASS_DECL_AURA string merge_colon_args(const array < string_array > & str2a);
//
//class callstack;
//
//CLASS_DECL_AURA __pointer(callstack) get_callstack(const char* pszFormat = "%f(%l) %s\n", iptr iSkip = -1000, void* caller_address = nullptr, iptr iCount = -1);
//
//CLASS_DECL_AURA __pointer(callstack) get_callstack(e_callstack ecallstack, int iCallStackAddUp = 0);
//
//CLASS_DECL_AURA void set_callstack_mask(cflag < e_callstack > ecallstack);
//
//CLASS_DECL_AURA e_callstack get_callstack_mask();
//
//inline bool is_callstack_enabled(e_callstack ecallstack) { return (i64) get_callstack_mask()& (i64) ecallstack; }
//
//
//#include "aura/platform/fixed_alloc.h"
//
//
//
//#include "aura/memory/allocate.h"
//#include "aura/memory/plex.h"
//
//
//#include "aura/primitive/primitive/id.h"
//
//
//inline bool is_filemanager(::id id) { return is_impact_group(id.i64(), FILEMANAGER_IMPACT); }
//inline bool is_filemanager_group(::id id, ::i64 iGroup) { return is_impact_subgroup(id.i64(), FILEMANAGER_IMPACT + iGroup); }
//inline bool is_color_sel(::id id) { return is_impact_group(id.i64(), COLORSEL_IMPACT); }
//inline bool is_font_sel(::id id) { return is_impact_group(id.i64(), FONTSEL_IMPACT); }
//
//
//#include "aura/primitive/string/composite.h"
//#include "aura/primitive/string/base64.h"
//
//#include "aura/primitive/collection/composite_array.h"
//
//
//
//template < class POINTER_TYPE >
//inline auto & __typed(__composite(POINTER_TYPE) * pp) { return *pp->operator POINTER_TYPE * (); }
//
//
//
//
//
//
//#include "aura/platform/display.h"
//
//
//
//
//
//#include "aura/filesystem/file/file.h"
//#include "aura/filesystem/file/stream.h"
//#include "aura/filesystem/file/binary_stream.h"
//#include "aura/filesystem/file/var_stream.h"
//#include "aura/filesystem/file/string_file.h"
//#include "aura/filesystem/file/text_stream.h"
//
//
//#include "aura/exception/_dump_context.h"
//
//inline int read_char(u8 * & pdata, memsize & s, char * pch)
//{
//
//   if (s < 1)
//   {
//
//      return 0;
//
//   }
//
//   *pch = (char)*pdata;
//
//   pdata++;
//
//   s--;
//
//   return 1;
//
//}
//
//template<class TYPE>
//inline void dump_elements(dump_context & dumpcontext, const TYPE* pElements, ::count nCount);
//
//
////#include "aura/common.h"
//
//
//#include "aura/filesystem/file/cpp.h"
//
//#include "aura/platform/library_object_allocator.h"
//
//#include "aura/platform/library.h"
//
//
//#include "aura/filesystem/filesystem.h"
//
//
//
//
////#include "aura/primitive/collection/base_enum.h"
//
//#include "aura/const/source.h"
//#include "aura/const/context.h"
//#include "aura/primitive/primitive/action_context.h"
//
//
//
//#include "aura/platform/cmp.h"
//
//
//#include "aura/filesystem/file/string_file.h"
//
//
//#include "aura/filesystem/file/var_stream.h"
//
//
////#include "aura/primitive/str/str_format.h"
//
//
//#include "aura/primitive/primitive/var2.h"
//
//
//#include "aura/primitive/primitive/id_space.h"
//
//
//#include "aura/primitive/math/scalar_enum.h"
//
//
//#include "aura/primitive/math/scalar.h"
//
//
//#include "aura/platform/progress.h"
//
//
//#include "aura/platform/enum.h"
//
//
//#include "aura/multithreading/_.h"
//
//
//namespace aura
//{
//
//#if defined _UWP && defined(__cplusplus_winrt)
//
//   interface class system_window
//      {
//
//         virtual Windows::Foundation::Rect get_window_rect() = 0;
//         virtual Windows::Foundation::Point get_cursor_pos() = 0;
//
//
//
//      };
//
//   CLASS_DECL_AURA bool get_window_rect(system_window ^ pwindow, RECTD * prect);
//
//   CLASS_DECL_AURA bool get_window_rect(system_window ^ pwindow, RECT * prect);
//
//
//#endif
//
//
//   class session;
//
//} // namespace aura
//
//
//
//#if defined _UWP
//
//
//namespace uwp
//{
//
//
//   ref class directx_application;
//
//
//} // namespace uwp
//
//
//#endif
//
////namespace account
////{
////
////
////   //class interactive;
////   //class credentials;
////   //class department;
////   //class user;
////   //class product;
////   //class storage;
////
////
////} // namespace account
//
//
//
////#include "aura/account/_.h"
//
//
//
//#if defined(LINUX)
//
//#include "aura/os/ansios/_.h"
//
//#elif defined(_UWP)
////
////#include "aura/os/_UWP/_UWP.h"
////#include "aura/os/_UWP/_UWP_user_impl.h"
////
//#elif defined(MACOS)
////
////#include "aura/os/ansios/ansios.h"
////#include "aura/os/macos/macos.h"
////
//#elif defined(ANDROID)
////
////#include "aura/os/ansios/ansios.h"
////#include "aura/os/android/android.h"
////
//#elif defined(WINDOWS_DESKTOP)
////
////#include "aura/os/windows/windows.h"
////
//#elif defined(APPLE_IOS)
////
////#include "aura/os/ansios/ansios.h"
////#include "aura/os/ios/ios.h"
//////#include "aura/os/ios/ios_windowing.h"
////
//#elif defined(SOLARIS)
////
////#include "aura/os/ansios/ansios.h"
////#include "aura/os/solaris/solaris_user_impl.h"
////
//#else
////
////#error "not implemented!!"
////
//#endif
//
//
//
//
//
//CLASS_DECL_AURA string get_system_error_message(u32 dwError);
//
//
//#include "aura/platform/flags.h"
//#include "aura/const/check.h"
//
//
//#include "aura/message/_message.h"
//
//
//
//
//#include "aura/user/command.h"
//
//
//#include "aura/message/message.h"
//
//
//#include "aura/platform/keep.h"
//#include "aura/platform/restore.h"
//
//
//#include "aura/primitive/data/_.h"
//
//
//#include "aura/primitive/math/objects.h"
//
//
//#include "aura/platform/simple_log.h"
//
//
//#include "aura/primitive/collection/file_path_map.h"
//
//#include "aura/primitive/primitive/edit.h"
//#include "aura/platform/department.h"
////#include "aura/platform/department_container.h"
//
//#include "aura/multithreading/threading.h"
//
//class mq;
//
////#include "aura/platform/live_signal.h"
//#include "aura/multithreading/pred_holder.h"
////#include "aura/primitive/primitive/command.h"
//#include "aura/multithreading/thread.h"
//#include "aura/multithreading/handler.h"
//#include "aura/multithreading/service_base.h"
//#include "aura/multithreading/service/plain_service.h"
//#include "aura/multithreading/service/plain_service.h"
//#include "aura/multithreading/fork.h"
//#include "aura/multithreading/delay_thread.h"
//#include "aura/multithreading/tools.h"
//#include "aura/platform/timer_callback.h"
//#include "aura/platform/timer_item.h"
//#include "aura/platform/timer_array.h"
//#include "aura/platform/timer.h"
//#include "aura/platform/timer_event.h"
//
//#include "aura/multithreading/thread_impl.h"
////#include "aura/multithreading/simple_thread.h"
////#include "aura/multithreading/go_thread.h"
////#include "aura/multithreading/signal_thread.h"
//#include "aura/multithreading/procedure_array.h"
//
//
/////#include "aura/primitive/primitive/job.h"
//
//#include "aura/user/simple/message_box.h"
//
//
//#include "aura/user/impact_data.h"
//
//#include "aura/platform/log.h"
//
//
//#include "aura/primitive/primitive/memory_base.h"
//#include "aura/primitive/primitive/memory.h"
//#include "aura/primitive/primitive/shared_memory.h"
//#include "aura/primitive/primitive/virtual_memory.h"
//#include "aura/primitive/primitive/memory_container.h"
//
//
//
//
//
//
//
//#include "aura/filesystem/file/memory_file.h"
//#include "aura/filesystem/file/circular_file.h"
//
//
//
////#include "aura/filesystem/file/timeout_buffer.h"
////#include "aura/filesystem/file/transfer_buffer.h"
//
//#include "aura/filesystem/file/memory_map.h"
//
//#include "aura/primitive/string/international2.h"
//
//
//
////#if defined(_UWP)
////
////#include "app/aura/os/_UWP/_UWP_sockets.h"
////
////#endif
//
//
//#include "aura/primitive/primitive/factory.h"
//
//


#include "aura/graphics/_.h"


//#include "aura/graphics/draw2d/context_image.h"


//
//#include "aura/primitive/math/random_number_generator.h"
//#include "aura/primitive/math/department.h"
//#include "aura/primitive/geometry2d/geometry.h"
//
//
//CLASS_DECL_AURA string get_exe_path();
//
//
//#include "aura/platform/savings.h"
//
//#include "aura/net/_.h"
//
//#include "aura/platform/launcher.h"
//
//#include "aura/platform/interprocess_communication.h"
//
//#include "aura/platform/app_launcher.h"
//
//
//class zip_context;
////namespace zip
////{
////
////   class util;
////
////} // namespace zip
//
//
//namespace file
//{
//
//   class watcher;
//
//} // namespace file
//
//#include "aura/filesystem/filesystem/file_system.h"
//
//#include "aura/filesystem/filesystem/dir_system.h"
//
//#include "aura/filesystem/filesystem/file_context.h"
//
//#include "aura/filesystem/filesystem/dir_context.h"
//
//#include "aura/filesystem/filesystem/listing.h"
//
//#include "aura/filesystem/file/set.h"
//
////#include "aura/primitive/primitive/application_bias.h"
//
////#include "aura/primitive/primitive/command.h"
//
//
//#include "aura/exception/engine.h"
//
//
//#include "aura/platform/fixed_alloc_impl.h"
//#include "aura/primitive/primitive/command_line.h"
#include "aura/user/create.h"
////#include "aura/primitive/primitive/create.h"
//#include "aura/primitive/primitive/request_signal.h"
//
//
//#include "aura/platform/net.h"
//
//
//#include "aura/filesystem/file/buffered_file.h"
//
//
//#include "aura/primitive/datetime/_.h"
//
//
//#include "aura/primitive/string/international_locale_schema.h"
//
//
////#include "aura/platform/cregexp.h"
////#include "aura/platform/cregexp_util.h"
//
//
//class CLASS_DECL_AURA ptra :
//   virtual public __pointer_array(object)
//{
//public:
//
//
//};
//
//
//typedef ::map < __pointer(object), __pointer(object), __pointer(object), __pointer(object) > element_map;
//typedef ::map < __pointer(object), __pointer(object), ptra, ptra > map_many;
//
//
//namespace zip
//{
//
//
//   class util;
//
//
//} // namespace zip
//
//
//#include "aura/os/text.h"
//
//#ifdef ANDROID
//
//#include "aura/os/android/_os_local.h"
//
//#endif
//
//#include "aura/platform/regex.h"
//
//#include "aura/process/process.h"
//
//#include "aura/filesystem/filesystem/file_watcher.h"
//
//#include "aura/platform/os_context.h"
//
//#include "aura/crypto/crypto.h"
//
//#include "aura/database/_.h"
//
////#include "aura/database/simpledb/_.h"
//
#include "aura/user/_.h"
//
//
//
//
#include "aura/multimedia/_.h"
//
//
//
//
////#include "aura/user/style_coord.h"
////#include "aura/user/style_rect.h"
#include "aura/user/item.h"
//
//
//#include "aura/platform/exclusive.h"
//
//
//#include "aura/platform/application_menu.h"
//#include "aura/platform/application_array.h"
//#include "aura/platform/application_container.h"
//
//
//#include "aura/os/process.h"
//
//#include "aura/platform/interprocess_intercommunication.h"
//
//#include "aura/platform/hyperlink.h"
//
//#include "aura/platform/context.h"
//
////#include "aura/geoip/geoip.h"
//
//class ftpfs;
//
//namespace fs
//{
//
//   class remote_native;
//   class fs;
//   class data;
//
//}
//
//class ifs;
//
////#include "axis/programming/javascript/javascript.h"
//
//#include "aura/filesystem/fs/_fs.h"
//
////#include "aura/user/userpresence/_.h"
//
////#include "aura/html/html_lite/_.h"
//
////#include "core/user/experience/_.h"
//
////#include "aura/filesystem/userfs/_.h"
//
////#include "aura/filesystem/filehandler/_.h"


#include "aura/platform/drawable.h"

//
#include "aura/game/_.h"
//
//#include "aura/_.h"
//
//#include "aura/message/_.h"
//
//#include "aura/platform/context_thread.h"
//
//#include "aura/filesystem/filemanager/callback.h"
//


#include "aura/platform/theme.h"


#include "aura/user/callback.h"

#include "aura/filesystem/filemanager/callback.h"

#include "aura/platform/application.h"
//
////#include "aura/platform/app.h"
//
//#include "aura/platform/application_message.h"
//
////#include "aura/account/_account.h"
//
#include "aura/filesystem/filemanager/item_action.h"
//
////#include "core/user/userex/userex.h"
//
#include "aura/platform/session.h"
//
//#include "aura/multithreading/retry.h"
//
//
//CLASS_DECL_AURA::file::path application_installer_folder(const ::file::path & pathExe, string strAppId, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema);
//CLASS_DECL_AURA bool is_application_installed(const ::file::path & pathExe, string strAppId, string & strBuild, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema);
//CLASS_DECL_AURA bool set_application_installed(const ::file::path & pathExe, string strAppId, const char * pszBuild, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema);
//CLASS_DECL_AURA::file::path get_application_path(string strAppId, const char * pszPlatform, const char * pszConfiguration);
//CLASS_DECL_AURA::file::path get_last_run_application_path_file(string strAppId);
//CLASS_DECL_AURA::file::path get_last_run_application_path(string strAppId);
//CLASS_DECL_AURA bool set_last_run_application_path(string strAppId);
//
//CLASS_DECL_AURA ::estatus load_factory_library(string strLibrary);
//
//
//class node_data_exchange;
//
//namespace xml
//{
//
//
//   class department;
//
//
//} // namespace xml
//
//
#include "aura/multimedia/audio/speaker.h"
//
//
#include "aura/multimedia/audio.h"
//
#include "aura/multimedia/multimedia.h"
//
//#include "aura/platform/app_core.h"
//
////#include "aura/primitive/collection/map.h"
//
////#include "aura/primitive/collection/strid_map.h"
//
#include "aura/platform/system.h"
//
////#include "aura/platform/system_str.h"
//
//
//
//
//#define new ACME_NEW
//
//
//
//
///*namespace numeric_info
//{
//
//
//template < typename T >
//inline T get_maximum_value()
//{
//__throw(not_implemented(get_object()));
//}
//
//template < typename T >
//inline T get_minimum_value()
//{
//__throw(not_implemented(get_object()));
//}
//template < typename T >
//inline T get_null_value()
//{
//return 0;
//}
//template < typename T >
//inline T get_unitary_value()
//{
//return 1;
//}
//
//template < typename T >
//inline T get_allset_value()
//{
//T t;
//__memset(&t,0xff,sizeof(T));
//return t;
//}
//
//template < typename T >
//inline bool is_signed()
//{
//return ((T)-1) < 0;
//}
//
//template < typename T >
//inline bool is_integer()
//{
//// guess, as float and double is implemented
//return true;
//}
//
//
//template < typename T >
//inline string json(const T & value)
//{
//return __str(value);
//}
//
//} // namespace numeric_info
//
//*/
//
//
////#ifdef VARIADIC_TEMPLATE_FORMAT2
////
////template<typename T,typename... Args>
////inline void string_format::format(const char * & s,const T & value,Args... args)
////{
////
////   while(*s)
////   {
////
////      if(*s == '%' && *(++s) != '%')
////      {
////
////         defer_get_additional_argument(s,value,args...);
////
////         return;
////
////      }
////
////      append(*s++);
////
////   }
////
////   __throw(::exception::exception("extra arguments provided to format"));
////
////
////}
////
////
////
////
////#endif
//
//
//
////#include "aura/core_os.h"
//
//
//#include "aura/os/chronometer.h"
//
//
//#include "aura/platform/assert_running_task.h"
//
//
//#include "aura/platform/number.h"
//
//
//#include "aura/platform/debug.h"
//
//
////#include "aura/platform/printf.h"
////#include "aura/platform/sprintf.h"
//
//
////#include "aura/math/_math.h"
//
//
//// C++ Includes
//#include "aura/os/_.h"
//#include "aura/node/_.h"
//
//
//#include "aura/multithreading/data.h"
//
//
//#include "aura/platform/shell_launcher.h"
//
//
//#include "aura/platform/async.h"
//
//
#include "aura/platform/mq.h"
//
//
//#include "aura/platform/international.h"
//
//
////#include "aura/platform/static_start.h"
//
//
//
//#define return_(y, x) {y = x; return;}
//
//
//extern "C"
//{
//
//
//   i32 _c_lock_is_active(const char * lpszName);
//   i32 _c_lock(const char * lpszName,void ** pdata);
//   i32 _c_unlock(void ** pdata);
//
//
//}
//
//
//CLASS_DECL_AURA string _ca_get_file_name(const char * psz,bool bCreate = false,i32 * pfd = nullptr);
//
//CLASS_DECL_AURA string get_system_error_message(u32 dwError);
//
//
//#include "aura/platform/simple_app.h"
//
//
//
//
//
//
//
////#include "app/aura/node/node.h"
//
//
//namespace math
//{
//
//   template < typename T >
//   class complex;
//
//
//} // namespace math
//
//namespace _std
//{
//
//
//   template <class T> void __swap(T& a, T& b)
//   {
//      T c(a);
//      a = b;
//      b = c;
//   }
//
//
//}
//
//
////namespace file
////{
////
////
////   class text_stream_string_file;
////
////} // namespace file
//
////using text_stream = ::text_stream_string_file;
//
//
//
///*
//namespace std
//{
//
//   using string = ::string;
//   using wstring = ::wstring;
//
//   template < class KEY,class VALUE >
//   using map = ::map < KEY,const KEY &,VALUE,const VALUE & >;
//
//   template < class TYPE >
//   using list = ::list< TYPE >;
//
//   template < class TYPE >
//   using vector = ::array< TYPE >;
//
//   template < class TYPE >
//   using set = ::set< TYPE >;
//
//   using ostream = stream;
//   using ofstream = ::file::file_stream;
//
//   using istream = stream;
//   using ifstream = ::file::file_stream;
//
//   using stream = stream;
//   using fstream = ::file::file_stream;
//
//   using iostream = stream;
//   using iofstream = ::file::file_stream;
//
//   using stringstream = ::text_stream_string_file;
//   using ostringstream = ::text_stream_string_file;
//
//   template < typename T >
//   using numeric_limits = ::numeric_info < T >;
//
//   //      template <class T> void sort(T & t1,T & t2)
//   //    {
//   //     __sort < T >(t1,t2);
//   //}
//
//   template < class iterator >
//   void sort(iterator & a, iterator & b)
//   {
//      ::sort::quick_sort_iter(a, b);
//   }
//
//
//   template < typename T >
//   using stack = ::stack < T >;
//
//
//   using filebuf = ::file::stdio_file;
//
//   //using ios_base = stream_base;
//
//   // replace ::file:: => ::file::
//
//
//   using runtime_error = ::runtime_error;
//
//   using stdio_file = ::file::file;
//
//
//   template < typename T >
//   T abs(T t)
//   {
//      if(t < ::numeric_info< T >::null())
//         return -t;
//      else
//         return t;
//   }
//
//
//   using streamsize = filesize;
//   using streampos = filesize;
//   using streamoff = filesize;
//
//   using setw = ::file::set_width;
//
//#if !defined(WINDOWS_DESKTOP) && !defined(APPLEOS) && !defined(_UWP)
//
//   using bad_alloc = ::memory_exception;
//
//#endif
//
//   template < typename T >
//   using complex = ::math::complex < T >;
//
//
//   template <class T> const T& min(const T& a,const T& b)
//   {
//      return !(a > b) ? a : b;
//   }
//   template <class T> const T& max(const T& a,const T& b)
//   {
//      return !(a < b) ? a : b;
//   }
//
//   template <class RandomAccessIterator>
//   void make_heap(RandomAccessIterator first,RandomAccessIterator last)
//   {
//      ::papaya::make_heap(first,last);
//   }
//
//   template <class RandomAccessIterator,class Compare>
//   void make_heap(RandomAccessIterator first,RandomAccessIterator last,Compare comp)
//   {
//      ::papaya::make_heap(first,last,comp);
//   }
//
//   template <class RandomAccessIterator,class Compare>
//   void pop_heap(RandomAccessIterator first,RandomAccessIterator last)
//   {
//      ::papaya::pop_heap(first,last);
//   }
//
//   template <class RandomAccessIterator,class Compare>
//   void pop_heap(RandomAccessIterator first,RandomAccessIterator last,Compare comp)
//   {
//      ::papaya::pop_heap(first,last,comp);
//   }
//
//   template <class RandomAccessIterator,class Compare>
//   void push_heap(RandomAccessIterator first,RandomAccessIterator last)
//   {
//      ::papaya::push_heap(first,last);
//   }
//
//   template <class RandomAccessIterator,class Compare>
//   void push_heap(RandomAccessIterator first,RandomAccessIterator last,Compare comp)
//   {
//      ::papaya::push_heap(first,last,comp);
//   }
//
//   template <class RandomAccessIterator>
//   void sort_heap(RandomAccessIterator first,RandomAccessIterator last)
//   {
//      ::papaya::sort_heap(first,last);
//   }
//
//   template <class RandomAccessIterator,class Compare>
//   void sort_heap(RandomAccessIterator first,RandomAccessIterator last,Compare comp)
//   {
//      ::papaya::sort_heap(first,last,comp);
//   }
//
//
//
//#if !defined(__APPLE__)
//
//   template <class T> void __swap(T& a, T& b)
//   {
//      _std::__swap(a, b);
//   }
//
//#endif
//
//
//}*/
//
//
//template < typename T >
//inline string & to_json(string & str, const T & value, bool bNewLine)
//{
//
//   return str = __str(value);
//
//}
//
//
//CLASS_DECL_AURA int trace_hr(const char * psz,HRESULT hr);
//
//CLASS_DECL_AURA string get_last_error_string();
//
//CLASS_DECL_AURA string get_error_string(u64 uiError);
//
//CLASS_DECL_AURA void set_aura(void * p,::aura::application * papp);
//
//CLASS_DECL_AURA ::aura::application * get_aura(void * p);
//
//
//#include "aura/platform/error.h"
//
//
//#include "aura/primitive/primitive/_.h"
//
//
////#include "aura/scripting/javascript/javascript.h"
//
//
//#include "aura/compress/compress.h"
//
//
#include "aura/graphics/graphics/graphics.h"
//
//
//#include "aura/platform/application_consumer.h"
//
//
//#if !defined(_UWP)
//
//
//#include "aura/platform/serial.h"
//
//
//#endif
//
//
//#include "aura/platform/async.h"
//
//
//
//
//#include "aura/const/idpool.h"
//
//
//#include "aura/user/_.h"
//
//
//#include "aura/platform/message_box.h"
//
//
//#include "aura/platform/console_application.h"
//
//
//#include "aura/platform/application.h"
//
//
//#include "aura/primitive/primitive/_defer.h"
//
//
//#include "aura/multithreading/_impl.h"
//
//
//#include "aura/platform/_impl.h"
//
//
////#include "aura/primitive/collection/_collection_impl.h"
//
//
//#ifndef WINDOWS_DESKTOP
//
//#include "aura/os/cross/windows/windows_thread_impl.h"
//
//#endif
//
//
//#include "aura/primitive/collection/_papaya_impl.h"
//
//
//#include "aura/primitive/collection/_array_base_impl.h"
//#include "aura/primitive/collection/_array_impl.h"
//#include "aura/primitive/collection/_raw_array_impl.h"
//#include "aura/primitive/collection/_sort_array_impl.h"
//#include "aura/primitive/collection/_papaya_array_impl.h"
//
//#include "aura/primitive/collection/_list_impl.h"
//#include "aura/primitive/collection/_map_impl.h"
//
//#include "aura/primitive/collection/_sort_map_impl.h"
//
//#include "aura/primitive/collection/_fifo_map_impl.h"
//
//#include "aura/primitive/collection/_papaya_array2d_impl.h"
//
//
//
//#include "aura/platform/_system_smart_pointer_impl.h"
//#include "aura/platform/_system_object_impl.h"
//#include "aura/platform/_system_id_impl.h"
//#include "aura/platform/_system_var_impl.h"
//
//
//
//
//#include "aura/primitive/string/_impl.h"
//
//
//#include "aura/primitive/string/_base_impl.h"
//
//
//#include "aura/primitive/primitive/_factory_impl.h"
//
//
//#include "aura/primitive/math/_impl.h"
//
//
//#include "aura/primitive/collection/_string_array_impl.h"
//
//
//#include "aura/primitive/primitive/_impl.h"
//
//
//#include "aura/primitive/primitive/_papaya_impl.h"
//
//
//#include "aura/primitive/datetime/_impl.h"
//
//
//#include "aura/primitive/geometry2d/_impl.h"
//
//
//#include "aura/filesystem/_impl.h"
//
//
//#include "aura/filesystem/file/_impl.h"
//
//
//#include "aura/filesystem/file/_var_stream_impl.h"
//
//
//#include "aura/filesystem/file/_text_stream_impl.h"
//
//
//#include "aura/net/_impl.h"
//
//
#include "aura/graphics/draw2d/_impl.h"
//
//
//#include "aura/exception/_.inl"
//
//
#include "aura/graphics/draw2d/_image_impl.h"
//
//
//#include "aura/primitive/string/_str_impl.h"
//
//
#include "aura/graphics/_impl.h"
//
//
//#include "aura/filesystem/file/_serializable_impl.h"
//
//
//#include "aura/filesystem/file/_.h"
//
//
//#include "aura/filesystem/file/_papaya_impl.h"
//
//
//#include "aura/filesystem/file/_stream_process_impl.h"
//
//
//#include "aura/filesystem/file/_text_stream_impl.h"
//
//
//#include "aura/net/_impl.h"
//
//
//#include "aura/filesystem/filesystem/_impl.h"
//
//
//#include "aura/database/_impl.h"







#include "aura/os/_impl.h"


