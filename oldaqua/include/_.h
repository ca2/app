/////////////////////////////////////////////////////////////////////////////////////////
//
//  ca2
//
//  ca2 is an all-purpose multi-platform framework and set of libraries written in 
//  C++ language with the aim to help developers create awesome apps for users.
//
//  ca2/C++/C/Assembly/Huffman Machine/Hardware/Universe/Multiverse stack
//
//


#pragma once


#include "aqua/primitive/primitive/estatus.h"


#include <tuple>


CLASS_DECL_AQUA void aura_ref();


#ifdef WINDOWS_DESKTOP

typedef i32 WINAPI __MAIN_DEFERRED_RUN(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR pCmdLine, i32 nCmdShow);

#else

typedef i32 __MAIN_DEFERRED_RUN(int argc, char ** argv);

#endif


typedef __MAIN_DEFERRED_RUN * __LPFN_MAIN_DEFERRED_RUN;
extern CLASS_DECL_AQUA __LPFN_MAIN_DEFERRED_RUN __main_deferred_run;


#ifdef __DEBUG

#define INLINE

#else

#define INLINE inline

#endif


//#include "aqua/platform/cpu_architecture.h"


#include "aqua/message/global.h"


#include "aqua/exception/_c.h"


#ifdef WINDOWS_DESKTOP


#if defined _M_IX86
#define _AURA_LINKER_SYMBOL_PREFIX "_"
#elif defined _M_X64 || defined _M_ARM || defined _M_ARM64
#define _AURA_LINKER_SYMBOL_PREFIX ""
#else
#error Unsupported architecture
#endif


#endif


#if defined(APPLE_IOS) || defined(ANDROID) || defined(_UWP)

#define MOBILE_PLATFORM 1

#else

#define MOBILE_PLATFORM 0

#endif


#ifndef WINDOWS


#define _CRT_ASSERT 0


#endif




#include "aqua/platform/obj_ref_dbg.h"


namespace opengl
{

   class opengl;


} // namespace opengl


struct INT_STRING
{

   int            m_i;
   const char* m_psz;

};



CLASS_DECL_AQUA void throw_todo(void);


CLASS_DECL_AQUA void set_last_status(const ::estatus & estatus);
CLASS_DECL_AQUA void windowing_output_debug_string(const char * pszDebugString);
CLASS_DECL_AQUA void c_function_call(void * p);
extern CLASS_DECL_AQUA int g_bAura;
CLASS_DECL_AQUA int __assert_failed_line(const char * pszFileName,int iLineNumber);
CLASS_DECL_AQUA int is_debugger_attached(void);
CLASS_DECL_AQUA void debug_print(const char * psz,...);


CLASS_DECL_AQUA int throw_assert_exception(const char * pszFileName,int iLineNumber);
CLASS_DECL_AQUA void throw_what_exclamation_exclamation(const char * psz);



#ifndef __cplusplus


#define ASSERT assert


#else


#ifdef __DEBUG


#define ASSERT(f)          ((void) ((f) || (is_debugger_attached() && !::__assert_failed_line(__FILE__, __LINE__) && (::debug_break(), 0)) || (!is_debugger_attached() && (throw_assert_exception(__FILE__, __LINE__), 0))))
#define _ASSUME(cond)       do { bool _gen__condVal=!!(cond); ASSERT(_gen__condVal); __analysis_assume(_gen__condVal); } while(0)
#define ASSERT_VALID(pOb)  ::__assert_valid_object(pOb, __FILE__, __LINE__)


#else


#define ASSERT(f)
#define _ASSUME(cond)
#if defined(ANDROID)
#define ASSERT_VALID(cond)
#elif defined(APPLEOS)
#define ASSERT_VALID(cond)
#elif defined(LINUX)
#define ASSERT_VALID(cond)
#else
#define ASSERT_VALID(cond) __noop;
#endif
#endif


#endif


#define low_byte(w)              ((byte)((w) & 0xff))


#if defined(WINDOWS) || defined(LINUX) || defined(__i386__)


#define IMAGE_A_BYTE_INDEX 3
#define IMAGE_R_BYTE_INDEX 2
#define IMAGE_G_BYTE_INDEX 1
#define IMAGE_B_BYTE_INDEX 0


#define IMAGE_ARGB(a, r, g, b)         ((COLORREF)((low_byte(b)|((WORD)(low_byte(g))<<8))|(((u32)low_byte(r))<<16)|(((u32)low_byte(a))<<24)))


#define image_r_value(rgb)    (low_byte((rgb)>>16))
#define image_g_value(rgb)    (low_byte((rgb)>>8))
#define image_b_value(rgb)    (low_byte((rgb)))
#define image_a_value(rgb)    (low_byte((rgb)>>24))


#else


#define IMAGE_A_BYTE_INDEX 3
#define IMAGE_R_BYTE_INDEX 0
#define IMAGE_G_BYTE_INDEX 1
#define IMAGE_B_BYTE_INDEX 2


#define IMAGE_ARGB(a, r, g, b)         ((COLORREF)((low_byte(r)|((WORD)(low_byte(g))<<8))|(((u32)low_byte(b))<<16)|(((u32)low_byte(a))<<24)))


#define image_r_value(rgb)    (low_byte((rgb)))
#define image_g_value(rgb)    (low_byte((rgb)>>8))
#define image_b_value(rgb)    (low_byte((rgb)>>16))
#define image_a_value(rgb)    (low_byte((rgb)>>24))


#endif


#define __CONCAT3(xxx, yyy, zzz) xxx ## yyy ## zzz


#define colorref_get_r_value(rgb)    (low_byte(rgb))
#define colorref_get_g_value(rgb)    (low_byte((rgb)>>8))
#define colorref_get_b_value(rgb)    (low_byte((rgb)>>16))
#define colorref_get_a_value(rgb)    (low_byte((rgb)>>24))
#define RGBA(r, g, b, a)         ((COLORREF)((low_byte(r)|((WORD)(low_byte(g))<<8))|(((u32)low_byte(b))<<16)|(((u32)low_byte(a))<<24)))
#define ARGB(a, r, g, b)      RGBA(r, g, b, a)


#define __acolor(a, r, g, b)      ::color(r, g, b, a)


inline int trailingBytesForUTF8(char ch);


extern CLASS_DECL_AQUA const char g_trailingBytesForUTF8[256];


inline int trailingBytesForUTF8(char ch)
{

   return ::g_trailingBytesForUTF8[(byte)ch];

}


CLASS_DECL_AQUA int is_ptr_null(const void * p, size_t s);


inline CLASS_DECL_AQUA int c_is_null(const void * p)
{
   return ((uptr)p) < 65536;

}



#define void_ptr_is_null(p) (((uptr)(void *) p) < 4096)

namespace dynamic_source
{


   class script_interface;


} // namespace dynamic_source


#include "aqua/primitive/math/mkint_c.h"

// C-includes
#include "aqua/os/_c.h"
#include "aqua/memory/heap_c.h"



#undef MIN
#undef MAX


#define INTABS(i) (((i) >= 0) ? (i) : (-i))
#define FLOATABS(f) (((f) >= 0.f) ? (f) : (-f))
#define DOUBLEABS(d) (((d) >= 0.0) ? (d) : (-d))


#ifdef __cplusplus
#define MAX(a, b) (((b) < (a)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#include "aqua/primitive/comparison/_c.h"
#else
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif


#define LIM(a, min, max) MIN(max, MAX(min, a))
#define SORT_LIM(x,minmax,maxmin) ((minmax) < (maxmin) ? LIM(x,minmax,maxmin) : LIM(x,maxmin,minmax))
#define CLIP_USHRT(x) LIM(x,0,USHRT_MAX)




#ifdef WINDOWS
#include <intsafe.h>
#else

#ifndef LODWORD
#define LODWORD(l)                                    ((::u32)(((::u64)(l)) & 0xffffffff))
#endif
#ifndef HIDWORD
#define HIDWORD(l)                                    ((::u32)((((::u64)(l)) >> 32) & 0xffffffff))
#endif

#endif




#define __u16(a, b)                                   ((::u16)(((::u8)(((::uptr)(a)) & 0xff)) | ((::u16)((::u8)(((::uptr)(b)) & 0xff))) << 8))
#define __u32(a, b)                                   ((::u32)(((::u16)(((::uptr)(a)) & 0xffff)) | ((::u32)((::u16)(((::uptr)(b)) & 0xffff))) << 16))


#ifdef __cplusplus

#define MAKELONG64(a, b)                              (((::u64)(((::u32)(((::u64)(a)) & 0xffffffff)) | ((::u64)((::u32)(((::u64)(b)) & 0xffffffff))) << 32)))
#define __u64(a, b)                                   (((::u64)(((::u32)(((::u64)(a)) & 0xffffffff)) | ((::u64)((::u32)(((::u64)(b)) & 0xffffffff))) << 32)))

#else

#define MAKELONG64(a, b)                              (((u64)(((u32)(((u64)(a)) & 0xffffffff)) | ((u64)((u32)(((u64)(b)) & 0xffffffff))) << 32)))
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


#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lparam)                          ((i32)(i16)LOWORD(lparam))
#endif


#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lparam)                          ((i32)(i16)HIWORD(lparam))
#endif

#define GET_X_LPARAM64(lparam)                        ((i32)(i16)LODWORD(lparam))
#define GET_Y_LPARAM64(lparam)                        ((i32)(i16)HIDWORD(lparam))


//CLASS_DECL_AQUA int get_aura_init();

//extern "C"
//CLASS_DECL_AQUA int_bool defer_aura_init();

//extern "C"
//CLASS_DECL_AQUA int_bool defer_aura_term();




typedef struct rdp_freerdp freerdp;


CLASS_DECL_AQUA int_bool freerdp_authenticate(void * instance, char** username,char** password,char** domain, const char * pszServerName, int bInteractive);


#if !defined(O_BINARY) && !defined(WINDOWS)
# define O_BINARY 0
#endif


CLASS_DECL_AQUA i32     ansi_open(const char * psz,i32 i);
CLASS_DECL_AQUA FILE *  ansi_fopen(const char * psz,const char * pszMode);
CLASS_DECL_AQUA int     ansi_file_flag(int iFlag);
CLASS_DECL_AQUA void    ansi_get_errno(i32 * perrno);
CLASS_DECL_AQUA void    ansi_unlink(const char * psz);


CLASS_DECL_AQUA DWORD get_last_error();
CLASS_DECL_AQUA void set_last_error(DWORD dw);

typedef char ansichar;

i32 CLASS_DECL_AQUA MultiByteToWideChar2(UINT CodePage, DWORD dwFlags, const ansichar * pMultByteStr, i32 cbMultiByte, widechar * pWideCharStr, i32 cchWideChar);
i32 CLASS_DECL_AQUA WideCharToMultiByte2(UINT CodePage, DWORD dwFlags, const widechar * pWideCharStr, i32 cchWideChar, ansichar * pMultByteStr, i32 cbMultiByte, LPCSTR pDefaultChar, LPBOOL pUsedDefaultChar);


enum e_image_type
{

   image_type_complex,
   image_type_plain_color

};





#include "aqua/primitive/primitive/_c_memory.h"

#include "aqua/primitive/string/_c.h"

#include "aqua/primitive/datetime/_c.h"

#include "aqua/filesystem/file/_c.h"

#include "aqua/const/thread.h"





#if !defined(APPLEOS) && !defined(LINUX) && !defined(ANDROID)

int ftruncate(int file, filesize len);

#endif


CLASS_DECL_AQUA i32 get_os_thread_priority(::e_priority epriority);
CLASS_DECL_AQUA i32 get_os_priority_class(::e_priority epriority);
CLASS_DECL_AQUA ::e_priority get_os_thread_scheduling_priority(i32 iCa2Priority);
CLASS_DECL_AQUA ::e_priority get_os_class_scheduling_priority(i32 iCa2Priority);



//#include "aqua/primitive/datetime/mktime.h"
#include "aqua/primitive/api/api.h"


#include "aqua/multimedia/_c.h"


class generic_object;


template < typename T >
void __finalize_and_release(T& p)
{

   if (p)
   {

      p->finalize();

      p.release();

   }

}


CLASS_DECL_AQUA extern u32 g_tickStartTime;

#define ALOG_CONTEXT context_trace_object()

#define _S_ALOG_CONTEXT ::context_trace_object()



CLASS_DECL_AQUA ::generic_object * general_trace_object();

CLASS_DECL_AQUA int_bool c_enable_trace_category(e_trace_category ecategory, int_bool iEnable);

inline ::generic_object * context_trace_object() { return general_trace_object(); }


CLASS_DECL_AQUA void __tracea(::generic_object * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz);
CLASS_DECL_AQUA void __tracef(::generic_object * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz, ...);
CLASS_DECL_AQUA void __tracev(::generic_object * pobject, e_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz, va_list vargs);
CLASS_DECL_AQUA const char * trace_category_name(e_trace_category ecategory);


CLASS_DECL_AQUA ::generic_object * trace_object(e_trace_category ecategory);

const char * topic_text(::generic_object * pcontextobject);

e_trace_category object_trace_category(::generic_object * pcontextobject);



#define __alog(...) __tracef(__VA_ARGS__)

#define INFO(...) __alog(trace_object(ALOG_CONTEXT), trace_level_information, ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)
#define WARN(...) __alog(trace_object(ALOG_CONTEXT), trace_level_warning, ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)
#define ERR(...) __alog(trace_object(ALOG_CONTEXT), trace_level_error, ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)
#define FATAL(...) __alog(trace_object(ALOG_CONTEXT), trace_level_fatal, ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)

#define TRACE(...) INFO(__VA_ARGS__)


namespace aqua
{


   class theme;


} // namespace aqua


namespace axis
{


   class application;
   class session;
   class system;


} // namespace axis


namespace base
{


   class application;
   class session;
   class system;
   class user;


} // namespace base


namespace core
{


   class application;
   class session;
   class system;


} // namespace core



#include "aqua/primitive/string/_c_impl.h"


#include "aqua/platform/aura_main_struct.h"


//#ifdef WINDOWS
//#pragma warning(disable: 4251)
//#endif

//#include "platform/platform/_.h"

class eimpact;

enum e_simple_command : ::i64;
enum e_message : ::i64;
enum e_impact : ::i64;
enum e_id : ::u64;
enum enum_check: ::i32;

template <typename TYPE>
struct remove_const_struct { // remove top-level const qualifier
   using NON_CONST_TYPE = TYPE;
};

template <typename TYPE>
struct remove_const_struct< TYPE &> {
   using NON_CONST_TYPE = TYPE &;
};


template <typename TYPE>
struct remove_const_struct<const TYPE> {
   using NON_CONST_TYPE = TYPE;
};

template <typename TYPE>
struct remove_const_struct<const TYPE &> {
   using NON_CONST_TYPE = TYPE &;
};

template <class TYPE>
using non_const = typename remove_const_struct<TYPE>::NON_CONST_TYPE;

struct true_type { };
struct false_type { };
template < typename POINTER >
class raw_pointer
{
public:

   using RAW_POINTER = POINTER;

};

template < typename TYPE >
class raw_type
{
public:

   using RAW_TYPE = TYPE;

};

template < typename TYPE >
class raw_type < TYPE * >
{
public:

   using RAW_TYPE = TYPE;

};

template < typename TYPE >
class raw_type < TYPE * & >
{
public:

   using RAW_TYPE = TYPE;

};

template < typename TYPE >
class raw_type < const TYPE * >
{
public:

   using RAW_TYPE = TYPE;

};

template < typename TYPE >
class raw_type < const TYPE * & >
{
public:

   using RAW_TYPE = TYPE;

};


template < typename LEFT, typename RIGHT >
inline void assign(LEFT & l, const RIGHT & r) { l = r; }


//template < typename, typename >
//inline constexpr auto is_strictly_same_type = false_type();
//template < typename TYPE >
//inline constexpr auto is_strictly_same_type < TYPE, TYPE> = true_type();
//
//template < typename TYPE >
//inline constexpr auto is_void = is_strictly_same_type< TYPE, void>;

#ifdef CPP17

template <typename PRED, typename ... Args >
inline bool _returns_true(PRED pred, const true_type & pred_returns_void, bool bOnVoid, Args... args)
{
   pred(args...);
   return bOnVoid;
}

template <typename PRED, typename ... Args >
inline bool _returns_true(PRED pred, const false_type & pred_returns_void, bool, Args... args)
{
   return (bool)pred(args...);
}

template <typename PRED, typename ... Args >
inline bool returns_true(PRED pred, bool bOnVoid, Args... args)
{

   return _returns_true(pred, is_void<decltype(pred(args...))>, bOnVoid, args...);

}

template <typename PRED, typename ... Args >
inline bool _returns_false(PRED pred, const true_type & pred_returns_void, bool bOnVoid, Args... args)
{
   pred(args...);
   return bOnVoid;
}

template <typename PRED, typename ... Args >
inline bool _returns_false(PRED pred, const false_type & pred_returns_void, bool, Args... args)
{
   return !(bool)pred(args...);
}

template <typename PRED, typename ... Args >
inline bool returns_false(PRED pred, bool bOnVoid, Args... args)
{

   return _returns_false(pred, is_void < decltype(pred(args...)) >, bOnVoid, args...);

}

#endif

template < typename CHAR_TYPE >
class string_base;


struct pixmap;


#define CONSIDER_AS(as, use) using use = as


using ansistring = string_base < ansichar >;
using wd16string = string_base < wd16char >;
using wd32string = string_base < wd32char >;
using widestring = string_base < widechar >;


using string = string_base < ansichar >;
using wstring = string_base < widechar >;


inline const ansichar* __c_str(const string& str);

class machine_event_central;


template < typename ARG_KEY >
inline uptr uptr_hash(ARG_KEY key) { return (uptr)((uptr)key); }

//#if OSBIT == 64

template < typename ARG_KEY >
inline u32 u32_hash(ARG_KEY key) { return (u32)(uptr_hash<ARG_KEY>(key)); }

//#endif


#define __base(TYPE, ptarget, psource) for(__pointer(TYPE) ptarget = psource; ptarget.is_set(); ptarget.release())
#define __base_reference(TYPE, ptarget, source) for(__pointer(TYPE) ptarget = &source; ptarget.is_set(); ptarget.release())
#define __exception(TYPE) __base(TYPE, pe, e)


#undef _

#define _(str) (__get_text(str))

CLASS_DECL_AQUA string __get_text(string str);




//class critical_section;


//namespace command
//{
//
//   class command;
//
//} // namespace command


class trait;
class create;
class sync;


//CLASS_DECL_AQUA i32 aura_run_system(::aqua::system* psystem);


//CLASS_DECL_AQUA ::estatus aura_run_system_init(::aqua::system * psystem);
//CLASS_DECL_AQUA ::estatus aura_run_system_proc(::aqua::system * psystem);
//CLASS_DECL_AQUA ::estatus aura_run_system_term(::aqua::system * psystem);


template < typename VAR >
class var_type
{
public:

   using VAR_TYPE = VAR;

   VAR_TYPE * this_var() { return (VAR_TYPE *)this; }
   const VAR_TYPE * this_var() const { return (const VAR_TYPE *)this; }

};

//// very short name ([{c}])ontext (switchers, as it as action_context) enums
//enum nullptr_t
//{
//   nullptr
//};

// very short name ([{c}])ontext (switchers, as it as action_context) enums
enum e_context_switcher_empty
{
   cempty
};


enum enum_create_new
{

   e_create_new

};


enum enum_create
{

   e_create

};

enum enum_defer_new // new - for factoryless_allocation FACTORYLESS_ALLOCATION_ID
{

   e_defer_new

};

enum enum_move_transfer
{

   e_move_transfer

};


enum enum_copy_clone
{

   e_copy_clone

};

#define IMPL_OPERATOR_PLUS(type) \
template < typename TYPE > \
type operator + (const TYPE & t) const { auto copy = *this; copy.add(t); return copy; }

#include "aqua/primitive/math/_.h"

#include "aqua/memory/_heap.h"

#include "aqua/exception/_const.h"

//#include "aqua/user/_const.h"

//#include "aqua/user/_experience_const.h"

#include "aqua/filesystem/file/_const.h"

//#include "aqua/graphics/draw2d/_const.h"


#define Usr(pobject) (*Sess(pobject).user())
#define User (Usr(get_context()))



enum enum_command
{

   command_none,
   command_default,
   command_on_agree_exit,
   command_france_exit,
   command_check_exit,
   command_protocol

};


class composite_base;
class context_object;
class object;


//namespace aqua
//{
//
//
//   class printer;
//
//
//
//} // namespace aqua


extern "C"
CLASS_DECL_AQUA void register_aura_library(const char * psz, ::aqua::library * plibrary);


extern "C"
CLASS_DECL_AQUA void register_get_new_aura_library(const char* psz, PFN_NEW_AURA_LIBRARY pfnNewAuraLibrary);


#define DECLARE_NEW_AURA_LIBRARY(X) extern "C" \
::aqua::library * X##_new_aura_library()


#define REGISTER_GET_NEW_AURA_LIBRARY(X) register_get_new_aura_library(#X, &X##_get_new_library)


namespace install
{


   class installer;


} // namespace install


template<class T>
struct remove_reference
{
   typedef T TYPE;
};

template<class T>
struct remove_reference<T&>
{
   typedef T TYPE;
};

template<class T>
struct remove_reference<T&&>
{
   typedef T TYPE;
};

template<class T> inline
typename remove_reference<T>::TYPE&& move(T && t)
{

   return (static_cast<typename remove_reference<T>::TYPE&&>(t));

}




template < class T >
class pointer;

template < class T >
class pointer_array;


//#define __composite(TYPE) ::reference < TYPE >

#define __pointer(TYPE) ::pointer < TYPE >
#define __pointer_array(TYPE) ::pointer_array < TYPE >
#define __address_array(TYPE) ::comparable_array < TYPE * >

namespace draw2d
{

   class font_enum_item;

   using font_enum_item_array = __pointer_array(font_enum_item);

} // namespace draw2d

template < typename T >
class result_pointer;

#define __result(T) ::result_pointer < T >

template < class TYPE >
inline auto & __typed(TYPE & t) { return t; }

template < class POINTER_TYPE >
inline auto & __typed(POINTER_TYPE * p) { return *p; }

template < class POINTER_POINTER_TYPE >
inline auto & __typed(POINTER_POINTER_TYPE ** p) { return **p; }


template < class TYPE >
inline auto & __typed_defer_new(TYPE & t) { return t; }

template < class POINTER_TYPE >
inline auto & __typed_defer_new(POINTER_TYPE *& p) { if (!p) p = new POINTER_TYPE; return *p; }

template < class POINTER_POINTER_TYPE >
inline auto & __typed_defer_new(POINTER_POINTER_TYPE ** p) { if (!*p) *p = new POINTER_POINTER_TYPE;  return **p; }

template < class T >
inline auto & __typed_defer_new(__pointer(T) & p) { if (!p) p = new T; return *p; }

template < class T >
inline auto & __typed_defer_create(__pointer(T) & p) { if (!p) __construct(p); return *p; }

template < typename T >
inline __pointer(T) move_transfer(T * p);

#define __new(...) move_transfer( new __VA_ARGS__ )


template < typename TYPE1, typename TYPE2 >
inline void __dynamic_cast(TYPE1*& ptype1, const TYPE2* ptype2)
{

   ptype1 = dynamic_cast <TYPE2*> (ptype2);

}


template < typename TYPE1, typename TYPE2 >
inline void __dynamic_cast(__pointer(TYPE1)& ptype1, const TYPE2* ptype2)
{

   ptype1 = ptype2;

}


template < typename TYPE1, typename TYPE2 >
inline void __dynamic_cast(__pointer(TYPE1)& ptype1, const __pointer(TYPE2)& ptype2)
{

   ptype1 = ptype2;

}


template < typename TYPE1, typename TYPE2 >
inline void __dynamic_cast(TYPE1*& ptype1, const __pointer(TYPE2)& ptype2);


template < typename T >
inline bool __found(const __pointer(T) & p);


template < typename T >
inline bool __not_found(const __pointer(T) & p);


template < typename TDST, typename TSRC >
inline __pointer(TDST) & clone(__pointer(TDST) & dst, const __pointer(TSRC) & src);

template < typename T >
inline __pointer(T) clone(const __pointer(T) & t);


template < class T >
class guard_pointer;


#define gp(TYPE) ::guard_pointer < TYPE >


#define clone_impl(name) inline name * clone() { return __new(name(*this)); }


#define DOUBLE_PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844


template < typename TYPE > inline TYPE* __random_bytes(TYPE* p, memsize s);
template < typename TYPE > inline TYPE& __random(TYPE& t);
template < typename TYPE > inline TYPE __random();
inline float __random(float f1, float f2);
inline double __random(double d1, double d2);
template < typename INT > inline INT __random_int(INT i1, INT i2);
inline i64 __random(i64 i1, i64 i2);
inline i32 __random(i32 i1, i32 i2);

template < typename TYPE >
inline void swap(TYPE& a, TYPE& b)
{
   auto t = a;
   a = b;
   b = t;

}

inline bool is_null(const void * p, size_t s)
{

   const auto max = (size_t)(-1);

   return ((size_t)p) <= s || ((size_t)p) >= (max - s);

}



template < typename TYPE >
inline bool is_null(const TYPE * p)
{

   const auto max = (size_t)(-1) - 65536;

   return ((size_t) p <= 65536) || ((size_t)p) >= (max);

}


template < >
inline bool is_null(const void * p)
{

   return is_null(p, 65536);

}


template < typename TYPE >
inline bool is_set(const TYPE * p)
{

   return !is_null(p);

}


template < typename TYPE >
inline bool is_ref_set(const TYPE & t)
{

   return is_set(&t);

}


template < typename TYPE >
inline bool is_ok(const TYPE* p)
{

   return ::is_set(p);

}
template < typename TYPE >
inline bool is_ok(const __pointer(TYPE) & p)
{

   return ::is_ok(p.m_p);

}


template < typename TYPE >
inline bool nok(const TYPE* p)
{

   return !::is_ok(p);

}



class istring;
class var;
class property_set;
class object;
//class base_edit;
class var_array;
class property;


class timer_callback;


//namespace handle
//{
//
//   class ini;
//
//} // namespace handle

namespace aqua
{

   class Timer;

};

class timer;

typedef bool FN_TIMER(timer * ptimer);
typedef FN_TIMER * PFN_TIMER;

#define NOK_IMAGE_OBJECT (NONE_ID)
#define IMAGE_OBJECT_OK (SUCCESS)
#define DEFAULT_CREATE_IMAGE_OBJECT_FLAG (IMAGE_OBJECT_OK)

#include "aqua/const/_const.h"


#include "aqua/primitive/primitive/_memory.h"


inline bool is_impact_group(::u64 u, ::u64 uGroup) { return u >= uGroup && u < uGroup + 1000; }
inline bool is_impact_subgroup(::u64 u, ::u64 uGroup) { return u >= uGroup && u < uGroup + 100; }


class image;
namespace draw2d{class icon;}

using image_pointer = __pointer(::image);
using icon_pointer = __pointer(::draw2d::icon);


using image_result = __result(::image);
using icon_result=__result(::draw2d::icon);


class command_line;


using command_line_pointer = __pointer(command_line);


namespace message
{


   class mouse;


} // namespace message


//#include "aqua/user/_const.h"
//#include "aqua/user/_const_key.h"

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




template < typename T1, typename T2, typename ARG_T1 = const T1 &, typename ARG_T2 = const T2 & >
class pair;

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE = const VALUE &, class PAIR = pair < KEY, VALUE, ARG_KEY, ARG_VALUE > >
class map;

template < class ENUM >
class flags;

template < class EENUM, EENUM edefault = (EENUM)0 >
class base_enum;

class form_property_set;


//namespace user
//{
//
//
//   class create;
//   class control_event;
//   class item;
//   class check;
//   class create_struct;
//   class command;
//   class interaction_impl;
//   class primitive;
//   class frame;
////   class menu;
//   //class controller;
//   //class document;
//
//   //class impact_system;
//   //class impact_data;
//   class printer;
////   class impact;
//   class primitive;
//   class interaction;
//   class layout;
//   //class place_holder;
//   //class menu_item;
//   //class form;
//   class style;
//   class menu_interaction;
//   //class tab;
//   class tab_pane;
//   class check_box;
//   class toolbar;
//   class split_layout;
//   class style_rect;
//   class scroll_bar;
//   class scroll_data;
//
//
//   //using color_map = map < e_color, e_color, COLORREF, COLORREF >;
//   //using font_map = map < e_font, e_font, ::draw2d::font_pointer >;
//   using eflag = flags < enum_flag >;
//   //using flag_map = map < e_flag, e_flag, bool, bool >;
//   //using rect_map = ::map < e_rect, e_rect, style_rect >;
//   //using int_map = ::map < e_int, e_int, int, int >;
//   //using double_map = ::map < e_double, e_double, double, double >;
//   //using color_map = map < e_color, e_color, COLORREF, COLORREF >;
//   //using eelement = base_enum < e_element >;
//   //using translucency_map = ::map < e_element, e_element, e_translucency, e_translucency >;
//
//
//
//#if defined(_UWP) || defined(APPLE_IOS) || defined(ANDROID)
//
//   class native_window_initialize;
//
//#endif
//
//
//} // namespace user


namespace aqua
{


   class application;
   class system;
   class application_message;

   class command;

   class str;
   class str_context;


} // namespace aqua

namespace gpu
{

   class approach;

} // namespace gpu


namespace data
{


   class listener;
   class data;
   class simple_data;
   class data_container_base;


} // namespace data

namespace sockets // only usable from base.dll and dependants
{

   class sockets; // only usable from base.dll and dependants


} // namespace sockets // only usable from base.dll and dependants


namespace url
{

   class department; // only usable from base.dll and dependants


} // namespace url


class compress_department; // only usable from axis.dll and dependants

class channel;

class dump_context;

class id_space;
class ptra;
class factory_item_base;
class fixed_alloc_no_sync;
class critical_section;
class var_array;
class thread;
class channel;
class critical_section;
class mutex;
class id;

namespace colorertake5
{

   class ParserFactory;


} // namespace colorertake5


//class pixmap;


class memory;


CLASS_DECL_AQUA ::aqua::system* platform_create_system(HINSTANCE hinstance);
CLASS_DECL_AQUA ::aqua::session* platform_create_session();


//namespace plane
//{
//
//   class session;
//   class system;
//   //class cube;
//
//
//} // namespace plane




#define SECOND_NANOS 1000000000


namespace datetime
{


   class department;
   class time;
   class time_span;


} // namespace datetime



template < typename Type,typename RawType = Type >
class string_array_base;


typedef string_array_base < string > string_array;


namespace file
{

   class listing;
   class path;
   typedef CLASS_DECL_AQUA ::string_array_base < ::file::path,string > patha;
   class file;

   enum e_type
   {

      type_none,
      type_folder,
      type_file,
      type_element,

   };

} // namespace file


class machine_event_data;

namespace hotplugin
{

   class host;
   class plugin;

}



namespace html
{


   class html;


} // namespace html


namespace audio
{


   class plugin;


} // namespace audio


#include "aqua/primitive/collection/forward.h"

enum e_optional
{

   optional,

};

enum e_no_init
{

   no_init,

};

class CLASS_DECL_AQUA set
{
public:

   e_set    m_eset;

   inline set(e_optional) { m_eset = set_none; }
   inline set() { m_eset = set_none; }
   inline set(int i) { operator = (i); }
   inline set(bool b) { operator = (b); }

   inline bool isFalse() const { return is_false(); }

   inline bool is_false() const { return m_eset < set_empty; }

   inline bool undefined() const { return is_empty(); }

   inline bool is_empty() const { return m_eset == set_empty; }

   inline bool is_none() const { return is_empty(); }

   inline bool is_true() const { return m_eset > set_empty; }

   inline bool is_true(bool bDefault) const { return m_eset ? isTrue() : bDefault; }

   inline bool isTrue() const { return is_true(); }

   inline bool is_optional() const { return !m_eset; }

   inline bool isOptional() const { return is_optional(); }

   inline operator bool() const { return isTrue(); }

   inline bool operator !() const { return isFalse(); }

   inline bool operator < (int i) const { return (int)m_eset < i; }

   inline bool operator <= (int i) const { return (int)m_eset <= i; }

   inline bool operator > (int i) const { return (int)m_eset > i; }

   inline bool operator >= (int i) const { return (int)m_eset >= i; }

   inline bool operator == (int i) const { return (int)m_eset == i; }

   inline bool operator != (int i) const { return !operator ==(i); }

   inline set & operator = (int i) { m_eset = (e_set)i; return *this; }

   inline set & operator = (bool b) { m_eset = (b ? set_true : set_false); return *this; }

   inline void defer(int i) { if(is_empty()) operator =(i); }

   inline set deferred(int i) const { if(is_empty()) return i; else return m_eset; }

   inline set operator()(int i) const { return deferred(i); }

};

inline bool __is_true(bool b) { return b; }
inline bool __is_true(const ::set& set) { return set; }

inline bool __is_false(bool b) { return !b; }
inline bool __is_false(const ::set& set) { return !set; }

inline bool __is_optional(bool b) { return false; }
inline bool __is_optional(const ::set& set) { return set.isOptional(); }


#define __optional_is_true(flag, option) ((bool)(flag) || (__is_optional(flag) && (option)))


#include "aqua/platform/auto.h"
#include "aqua/primitive/comparison/compare.h"
#include "aqua/primitive/primitive/papaya.h"






template <class t>
inline void delptr(t *& p)
{
   if(p != nullptr)
   {
      delete p;
      p = nullptr;
   }
}

template < typename T >
inline int type_is_null(const T * p)
{
   return (((UINT_PTR)(void *)p) < MAX(4096, sizeof(T)));
}


#include "aqua/primitive/string/_uhash.h"


class allocer;





namespace aqua
{

   template < typename T >
   inline void del(T * & p)
   {

      //Thank you Fiora a Eterna!!

      //Fiora Aeterna☄ ‏@FioraAeterna 20m20 minutes ago

      //   maybe it's cynical but I'm starting to think the real reason so many newer games have constant autosaves is because they crash all the time
      //   Details

      // BRT 2015-02-18 19:08
      // catch all (...) here in aqua::del ... but should remove try catch from all underlying calls (frees, memory_frees, memory_dbg_frees).

      try
      {

         //Thank you Dunno_Aye for the is_null!!

         if(!is_null(p))
         {

            T * pdel = p;

            p = nullptr;

            delete pdel;

         }

      }
      catch(...)
      {

      }

   }


   template < typename T >
   inline void delobj(T * & p);

   template < typename T >
   inline void adel(T * & p)
   {

      //Thank you Fiora a Eterna!!

      //Fiora Aeterna☄ ‏@FioraAeterna 20m20 minutes ago

      //   maybe it's cynical but I'm starting to think the real reason so many newer games have constant autosaves is because they crash all the time
      //   Details

      // BRT 2015-02-18 19:08
      // catch all (...) here in aqua::del ... but should remove try catch from all underlying calls (frees, memory_frees, memory_dbg_frees).

      try
      {

         if(p != nullptr)
         {

            delete[] p;

            p = nullptr;

         }

      }
      catch(...)
      {

      }

   }


   template < typename T >
   inline void free(T * & p)
   {

      //Thank you Mummi!!

      //Nice late afternoon coffee of ever!!

      //Thank you Fiora a Eterna!!

      //Fiora Aeterna☄ ‏@FioraAeterna some minutes ago

      //   maybe it's cynical but I'm starting to think the real reason so many newer games have constant autosaves is because they crash all the time
      //   Details

      // BRT 2016-11-23 19:08
      // catch all (...) here in aqua::del ... but should remove try catch from all underlying calls (frees, memory_frees, memory_dbg_frees).

      try
      {

         if (p != nullptr)
         {

            void * pdel = (void *) p;

            p = nullptr;

            ::free(pdel);

         }

      }
      catch (...)
      {

      }

   }


   template < typename T >
   inline void memory_free(T * & p)
   {

      //Thank you Mummi!!

      //Nice late afternoon coffee of ever!!

      //Thank you Fiora a Eterna!!

      //Fiora Aeterna☄ ‏@FioraAeterna some minutes ago

      //   maybe it's cynical but I'm starting to think the real reason so many newer games have constant autosaves is because they crash all the time
      //   Details

      // BRT 2016-11-23 19:08
      // catch all (...) here in aqua::del ... but should remove try catch from all underlying calls (frees, memory_frees, memory_dbg_frees).

      try
      {

         if (p != nullptr)
         {

            void * pdel = (void *)p;

            p = nullptr;

            ::memory_free(pdel);

         }

      }
      catch (...)
      {

      }

   }


   template < typename T >
   inline T * reset(T * & p, T * pNew)
   {

      ::aqua::del(p);

      return p = pNew;

   }

   template < typename T >
   inline T * reset(T * & p)
   {

      ::aqua::del(p);

      return p = new T;

   }

} // namespace aqua





#include "aqua/memory/malloc.h"

class image_list;




struct SIZEPARENTPARAMS
{

   RECT  rect;       // parent client rectangle (trim as appropriate)
   SIZE  sizeTotal;  // total size on each side as on_layout proceeds
   bool  bStretch;   // should stretch to fill all space

};


typedef struct RECTD RECTD;


namespace aqua
{


//#if defined _UWP && defined(__cplusplus_winrt)
//
//   interface class system_window
//   {
//
//      virtual Windows::Foundation::Rect get_window_rect() = 0;
//      virtual Windows::Foundation::Point get_cursor_pos() = 0;
//
//
//
//   };
//
//   CLASS_DECL_AQUA bool get_window_rect(system_window ^ pwindow,RECTD * prect);

//   CLASS_DECL_AQUA bool get_window_rect(system_window ^ pwindow,RECT * prect);

//
//#endif


   class file;


   namespace trace
   {

      class trace;

   }

   class session;

} // namespace aqua

CLASS_DECL_AQUA bool enable_trace_category(e_trace_category ecategory, bool bEnable = true);

// only usable from axis and axis dependants
namespace aqua
{

   class application;
   class session;
   class system;

}


// only usable from base and base dependants
namespace base
{

   class application;
   class session;
   class system;

}

// only usable from aqua and aqua dependants
namespace aqua
{

   class application;
   class session;
   class system;

}


class app_core;


//extern "C"
//typedef ::aqua::system *  CREATE_SYSTEM(app_core * pappcore);
//typedef ::aqua::system * CREATE_SYSTEM();

//typedef CREATE_SYSTEM * LPFN_CREATE_SYSTEM;

//CLASS_DECL_AQUA extern LPFN_CREATE_SYSTEM g_pfn_create_system;
//CLASS_DECL_AQUA extern const char * g_pszCooperativeLevel;
//CLASS_DECL_AQUA extern int g_iDerivedApplication; // one-based-index of derived application, zero if Main application


namespace data
{


   class item;


} // namespace data


namespace xml
{

   
   class node;
   class document;


} // namespace xml






enum e_extract
{

   extract_none,
   extract_first,
   extract_all

};


namespace str
{


   namespace international
   {


      class locale_schema;


   } // namespace international


} // namespace str




namespace draw2d
{


   class graphics;


} // namespace draw2d


//class random_access_iterator
//{
//public:
//};





class event;


class thread;




class thread;


typedef pointer < thread > thread_pointer;
typedef pointer_array < thread > thread_spa;


//class thread_impl;


//typedef pointer < thread_impl > thread_impl_pointer;


namespace html
{

   class html; // defined and set by html library/component

}


#define SCAST_PTR(TYPE, ptarget, psource) TYPE * ptarget = dynamic_cast < TYPE * > (psource);
#define SCAST_REF(TYPE, rtarget, psource) TYPE & rtarget = *(dynamic_cast < TYPE * > (psource))

#define Au(pobject) (*(::get_context_audio(pobject)))
#define Audio (Au(get_context()))

#define Mm(pobject) (*(::get_context_multimedia(pobject)))
#define Multimedia (Mm(get_context()))

#define System (*get_context_system())

#define Session (*get_context_session())

#define Application (*get_app())
#define ThisApp (*::application_consumer < application >::get_app())

#undef Ctx
#define Ctx(pobject) (*(::get_context(pobject)))
#define Context (Ctx(get_context()))


// return - result - if not ok
#ifndef RINOK
#define RINOK(x) { i32 __result__ = (x); if (__result__ != 0) return __result__; }
#endif

// __throw( - exception - result exception - if not ok
#ifndef TINOK
#define TINOK(e, x) { i32 __result__ = (x); if (__result__ != 0) __throw(e(get_context_application(), __result__)); }
#endif


#ifdef WINDOWS
#pragma warning(disable: 4251)  // using non-exported as public in exported
#endif


#ifndef WINDOWS_DESKTOP

typedef void * HDWP;

#endif

#ifdef APPLE_IOS

struct plane_system;

#endif

typedef  void(*PFN_factory_exchange)();

#ifdef WINDOWS
CLASS_DECL_AQUA bool defer_co_initialize_ex(bool bMultiThread, bool bDisableOleDDE = false);
#endif

class generic_object;

class var;

using argument = var;

class var_array;

using arguments = var_array;

class context;




//CLASS_DECL_AQUA bool aura_init();
//CLASS_DECL_AQUA bool aura_term();

CLASS_DECL_AQUA bool __node_aura_pre_init();
CLASS_DECL_AQUA bool __node_aura_pos_init();

CLASS_DECL_AQUA bool __node_aura_pre_term();
CLASS_DECL_AQUA bool __node_aura_pos_term();


extern "C" CLASS_DECL_AQUA PFN_NEW_AURA_LIBRARY get_get_new_aura_library(const char * psz);
extern "C" CLASS_DECL_AQUA void register_get_new_aura_library(const char* psz, PFN_NEW_AURA_LIBRARY pfnNewAuraLibrary);


CLASS_DECL_AQUA ::aqua::library & get_library(const char* psz);
CLASS_DECL_AQUA void register_aura_library(const char* psz, ::aqua::library* plibrary);

CLASS_DECL_AQUA ::context * get_context();
CLASS_DECL_AQUA inline ::context * get_context(::object * pobject);
CLASS_DECL_AQUA inline ::context * get_context(::context * pcontext);


CLASS_DECL_AQUA void set_global_application(::aqua::application * papp);
CLASS_DECL_AQUA ::aqua::application * get_global_application();


CLASS_DECL_AQUA ::aqua::application * get_context_application();
CLASS_DECL_AQUA inline ::aqua::application * get_context_application(::object * pobject);
CLASS_DECL_AQUA inline ::aqua::application * get_context_application(::aqua::application * papp);
CLASS_DECL_AQUA inline ::aqua::application * get_app() { return get_context_application(); }


CLASS_DECL_AQUA::aqua::session * get_context_session();
CLASS_DECL_AQUA inline ::aqua::session * get_context_session(::object * pobject);
CLASS_DECL_AQUA inline ::aqua::session * get_context_session(::aqua::session * psession);

CLASS_DECL_AQUA::aqua::system * get_context_system();
CLASS_DECL_AQUA inline ::aqua::system * get_context_system(::object * pobject);
CLASS_DECL_AQUA inline ::aqua::system * get_context_system(::aqua::system * psystem);


#define BAD_WCHAR ((widechar)(-1))


#define ARRAY_SIZE(a) (sizeof(a)/sizeof(*(a)))


class var;
class id;


namespace calculator
{


   class value;


} // namespace calculator






#ifdef APPLEOS
#undef err_none
#endif

#ifdef WINDOWS

template < typename POINTER_TYPE >
class cotaskptr;

#endif

class type;


#include "aqua/primitive/string/_.h"


#include "aqua/platform/definition.h"

#include "aqua/memory/new.h"

#include "aqua/platform/lparam.h"
#include "aqua/platform/muldiv64.h"




#include "aqua/platform/auto_pointer.h"


// C-includes
//#include "aqua/os/os.h"

class thread_parameter;

#include "aqua/primitive/primitive/enum.h"


#include "aqua/primitive/primitive/interlocked_long.h"
#include "aqua/primitive/primitive/interlocked_long_pulse.h"
#include "aqua/primitive/primitive/type.h"
#include "aqua/primitive/primitive/id.h"
#include "aqua/primitive/primitive/uid.h"


namespace primitive
{


   template < typename TYPE >
   class member;


   template < typename TYPE >
   class composite;


   template < typename TYPE >
   class reference;


} // namespace primitive


#define __member(TYPE) ::primitive::member < TYPE >
#define __composite(TYPE) ::primitive::composite < TYPE >
#define __reference(TYPE) ::primitive::reference < TYPE >




template < typename TYPE >
inline bool is_null(const __pointer(TYPE) & p)
{

   return ::is_null(p.m_p);

}

template < typename TYPE >
inline bool is_null(const __composite(TYPE) & p)
{

   return p.is_null();

}

template < typename TYPE >
inline bool is_null(const __reference(TYPE) & p)
{

   return p.is_null();

}


template < typename TYPE >
inline bool is_set(const __pointer(TYPE) & p)
{

   return p.is_set();

}

template < typename TYPE >
inline bool is_set(const __composite(TYPE) & p)
{

   return p.is_set();

}

template < typename TYPE >
inline bool is_set(const __reference(TYPE) & p)
{

   return p.is_set();

}

template < typename TYPE >
inline bool is_null_ref(const TYPE & t)
{

   return is_null(&t);

}


template < typename TYPE >
inline bool is_set_ref(const TYPE & t)
{
   return !is_null_ref(t);
}




#include "aqua/primitive/primitive/pointer.h"
#include "aqua/primitive/primitive/pointer2.h"


template < class POINTER_TYPE >
inline auto & __typed(__pointer(POINTER_TYPE) & p) { return *p; }


#include "aqua/multithreading/thread_parameter.h"

#include "aqua/platform/keep_true.h"

using file_pointer = __pointer(::file::file);

using file_result = __result(::file::file);

class stream;
class binary_stream;

template < typename BASE_TYPE >
inline stream & __save_object(stream & stream, BASE_TYPE * p);

template < typename BASE_TYPE >
inline stream & __save_object(stream & stream, const __pointer(BASE_TYPE) & p)
{
   return __save_object(stream, (BASE_TYPE *) p.m_p);
}

#include "aqua/primitive/primitive/logic.h"



#include "aqua/primitive/math/static_numeric_info.h"
#include "aqua/primitive/math/numeric_info.h"




#include "aqua/primitive/math/c_number.h"

using wparam = c_number < WPARAM >;




#include "aqua/primitive/math/math_clip.h"


#include "aqua/platform/tick.h"


#include "aqua/primitive/datetime/duration.h"

#include "aqua/platform/common.h"


//#include "aqua/primitive/string/_.h"


#include "aqua/primitive/datetime/date_span.h"
#include "aqua/primitive/datetime/time_span.h"
#include "aqua/primitive/datetime/time.h"
#include "aqua/primitive/datetime/zonetime.h"
#include "aqua/primitive/datetime/file_time_span.h"
#include "aqua/primitive/datetime/file_time.h"






//#include "aqua/os/_.h"


class update;

namespace status
{

   class result;

} // namespace status

namespace message
{
   class message;

} // namespace status

class parents;

class children;


namespace exception
{

   class exception;
   using exception_pointer = __pointer(exception);

} // namespace exception


using exception_pointer = ::exception::exception_pointer;


class event_map;
class thread_ptra;
//class traits;


namespace papaya
{

   class topic;

} // namespace papaya


class memory_base;



template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename RECT_BASE_TYPE >
class size_type;

using size = size_type < SIZE, POINT, RECT >;


#include "aqua/primitive/math/cast.h"


#include "aqua/primitive/primitive/block.h"
#include "aqua/memory/memory.h"

#include "aqua/primitive/primitive/cflag.h"

//namespace user
//{
//
//   using estate = cflag < enum_state >;
//   using eelement = cflag < e_element >;
//
//} // namespace user







//using eobject = cflag < ::enum_object >;
class action_context;

#include "aqua/primitive/primitive/eobject.h"

using emessagebox = cflag < enum_message_box >;

#include "aqua/primitive/primitive/function_base.h"





#include "aqua/primitive/primitive/generic_object.h"
#include "aqua/primitive/primitive/task.h"
#include "aqua/primitive/primitive/compare_pred.h"


#include "aqua/platform/status.h"
#include "aqua/primitive/primitive/enum_type.h"

using efileopen = cflag < ::file::e_open >;

using eiostate = ::cflag < ::file::e_iostate >;

using ecommand = ::enum_type < enum_command >;

using echeck = ::enum_type < enum_check >;


typedef ::estatus THREAD_PROCEDURE(thread_parameter parameter);


inline bool succeeded(const ::var & var);
inline bool succeeded(const ::property & set);

inline bool failed(const ::var & var) { return !::succeeded(var); }
inline bool failed(const ::property & set) { return !::succeeded(set); }


#define __inner_release(outer, inner) ::release(outer, outer->inner)


#include "aqua/primitive/primitive/function_base.h"


#include "aqua/primitive/primitive/member.h"


#include "aqua/primitive/primitive/context_object.h"


#include "aqua/primitive/primitive/trait.h"







#include "aqua/primitive/primitive/_papaya.h"








#include "aqua/primitive/geometry2d/_.h"


//#include "aqua/primitive/primitive/context_object.h"


#include "aqua/primitive/primitive/_factory_prefix.h"


#include "aqua/primitive/collection/decl.h"

#include "aqua/primitive/collection/raw_array_decl.h"


#include "aqua/primitive/collection/comparable_eq_array.h"
#include "aqua/primitive/collection/comparable_array.h"
#include "aqua/primitive/collection/comparable_raw_array.h"


#include "aqua/primitive/collection/pointer_array_process.h"

#include "aqua/primitive/collection/pointer_array.h"



//#include "aqua/primitive/collection/_papaya_array_decl.h"
#include "aqua/primitive/collection/_papaya_heap.h"


#include "aqua/primitive/collection/address_array.h"


#include "aqua/primitive/collection/_papaya.h"


//#include "aqua/primitive/collection/pointer2_array.h"

class sticker;


inline ::generic_object * trace_object(::generic_object * pobjectContext) { return pobjectContext; }

template < typename POINTER_TYPE >
class ptr_array;

//using composite_ptra = __pointer_array(::generic_object); // Please use just for composition (ownership).

//using reference_ptra = __pointer_array(::generic_object); // Please use just for reference (member-based).

//using object_ptra = __pointer_array(::context_object); // Please use just for keeping non-member-based references.

using object_ptra = __pointer_array(::generic_object); // Please use just for keeping non-member-based references.

using object_addra = __address_array(::generic_object); // Please use just for keeping non-member-based references.

class object_meta;


#define __composite_array(TYPE) ::array < __composite(TYPE) >
#define __reference_array(TYPE) ::array < __reference(TYPE) >

namespace http
{

   class context;

} // namespace http

template < typename PRED > inline auto __task_procedure(PRED pred, ::generic_object * pobjectHold = nullptr);

template < typename PRED > inline auto __task_callback(PRED pred, ::generic_object* pobjectHold = nullptr);

class context;

namespace draw2d
{

   class graphics;
   class pen;

   using graphics_pointer = __pointer(graphics);
   using pen_pointer = __pointer(pen);




} // namespace draw2d


//class create_thread;

using generic_pointer = __pointer(::generic_object);


#ifdef WINDOWS_DESKTOP


#include "aqua/os/windows/itemidlist.h"


#endif

class procedure;
class callback;


namespace core
{

   
   class user;


} // namespace core


#include "aqua/exception/_.h"

#include "aqua/primitive/comparison/var_strict.h"

#include "aqua/filesystem/filesystem/path.h"

#include "aqua/filesystem/filesystem/path_object.h"

#include "aqua/primitive/collection/_.h"

#include "aqua/primitive/primitive/procedure.h"

#include "aqua/primitive/primitive/callback.h"

#include "aqua/primitive/geometry2d/collection.h"

#include "aqua/primitive/geometry3d/_.h"

class message_box;

#include "aqua/primitive/primitive/object.h"

#include "aqua/primitive/primitive/object_meta.h"

#include "aqua/platform/trace.h"

#include "aqua/platform/pred_procedure.h"

#include "aqua/platform/debug.h"

#include "aqua/platform/class.h"

#include "aqua/primitive/comparison/md5.h"

//#include "aqua/platform/conv.h"

#include "aqua/primitive/primitive/request_interface.h"

#include "aqua/multithreading/sync_result.h"

//#include "aqua/multithreading/sync.h"

//#include "aqua/xml/exportable.h"

//#include "aqua/xml/importable.h"

#include "aqua/primitive/comparison/_.h"

#include "aqua/primitive/primitive/traits.h"

//#include "aqua/static_setup.h"

CLASS_DECL_AQUA string merge_colon_args(const array < string_array > & str2a);

class callstack;

CLASS_DECL_AQUA __pointer(callstack) get_callstack(const char* pszFormat = "%f(%l) %s\n", iptr iSkip = -1000, void* caller_address = nullptr, iptr iCount = -1);

CLASS_DECL_AQUA __pointer(callstack) get_callstack(e_callstack ecallstack, int iCallStackAddUp = 0);

CLASS_DECL_AQUA void set_callstack_mask(cflag < e_callstack > ecallstack);

CLASS_DECL_AQUA e_callstack get_callstack_mask();

inline bool is_callstack_enabled(e_callstack ecallstack) { return (i64) get_callstack_mask()& (i64) ecallstack; }


#include "aqua/platform/fixed_alloc.h"



#include "aqua/memory/allocate.h"
#include "aqua/memory/plex.h"


#include "aqua/primitive/primitive/id.h"


inline bool is_filemanager(::id id) { return is_impact_group(id.i64(), FILEMANAGER_IMPACT); }
inline bool is_filemanager_group(::id id, ::i64 iGroup) { return is_impact_subgroup(id.i64(), FILEMANAGER_IMPACT + iGroup); }
inline bool is_color_sel(::id id) { return is_impact_group(id.i64(), COLORSEL_IMPACT); }
inline bool is_font_sel(::id id) { return is_impact_group(id.i64(), FONTSEL_IMPACT); }


#include "aqua/primitive/string/composite.h"
#include "aqua/primitive/string/base64.h"

#include "aqua/primitive/collection/composite_array.h"



template < class POINTER_TYPE >
inline auto & __typed(__composite(POINTER_TYPE) * pp) { return *pp->operator POINTER_TYPE * (); }






#include "aqua/platform/display.h"





#include "aqua/filesystem/file/file.h"
#include "aqua/filesystem/file/stream.h"
#include "aqua/filesystem/file/binary_stream.h"
#include "aqua/filesystem/file/var_stream.h"
#include "aqua/filesystem/file/string_file.h"
#include "aqua/filesystem/file/text_stream.h"


#include "aqua/exception/_dump_context.h"

inline int read_char(u8 * & pdata, memsize & s, char * pch)
{

   if (s < 1)
   {

      return 0;

   }

   *pch = (char)*pdata;

   pdata++;

   s--;

   return 1;

}

template<class TYPE>
inline void dump_elements(dump_context & dumpcontext, const TYPE* pElements, ::count nCount);


//#include "aqua/common.h"


#include "aqua/filesystem/file/cpp.h"

#include "aqua/platform/library_object_allocator.h"

#include "aqua/platform/library.h"


#include "aqua/filesystem/filesystem.h"




//#include "aqua/primitive/collection/base_enum.h"

#include "aqua/const/source.h"
#include "aqua/const/context.h"
#include "aqua/primitive/primitive/action_context.h"



#include "aqua/platform/cmp.h"


#include "aqua/filesystem/file/string_file.h"


#include "aqua/filesystem/file/var_stream.h"


//#include "aqua/primitive/str/str_format.h"


#include "aqua/primitive/primitive/var2.h"


#include "aqua/primitive/primitive/id_space.h"


#include "aqua/primitive/math/scalar_enum.h"


#include "aqua/primitive/math/scalar.h"


#include "aqua/platform/progress.h"


#include "aqua/platform/enum.h"


#include "aqua/multithreading/_.h"


namespace aqua
{

#if defined _UWP && defined(__cplusplus_winrt)

   interface class system_window
      {

         virtual Windows::Foundation::Rect get_window_rect() = 0;
         virtual Windows::Foundation::Point get_cursor_pos() = 0;



      };

   CLASS_DECL_AQUA bool get_window_rect(system_window ^ pwindow, RECTD * prect);

   CLASS_DECL_AQUA bool get_window_rect(system_window ^ pwindow, RECT * prect);


#endif


   class session;

} // namespace aqua



#if defined _UWP


namespace uwp
{


   ref class directx_application;


} // namespace uwp


#endif

//namespace account
//{
//
//
//   //class interactive;
//   //class credentials;
//   //class department;
//   //class user;
//   //class product;
//   //class storage;
//
//
//} // namespace account



//#include "aqua/account/_.h"



#if defined(LINUX)

#include "aqua/os/ansios/_.h"

#elif defined(_UWP)
//
//#include "aqua/os/_UWP/_UWP.h"
//#include "aqua/os/_UWP/_UWP_user_impl.h"
//
#elif defined(MACOS)
//
//#include "aqua/os/ansios/ansios.h"
//#include "aqua/os/macos/macos.h"
//
#elif defined(ANDROID)
//
//#include "aqua/os/ansios/ansios.h"
//#include "aqua/os/android/android.h"
//
#elif defined(WINDOWS_DESKTOP)
//
//#include "aqua/os/windows/windows.h"
//
#elif defined(APPLE_IOS)
//
//#include "aqua/os/ansios/ansios.h"
//#include "aqua/os/ios/ios.h"
////#include "aqua/os/ios/ios_windowing.h"
//
#elif defined(SOLARIS)
//
//#include "aqua/os/ansios/ansios.h"
//#include "aqua/os/solaris/solaris_user_impl.h"
//
#else
//
//#error "not implemented!!"
//
#endif





CLASS_DECL_AQUA string get_system_error_message(u32 dwError);


#include "aqua/platform/flags.h"
#include "aqua/const/check.h"


#include "aqua/message/_message.h"




//#include "aqua/user/command.h"


#include "aqua/message/message.h"


#include "aqua/platform/keep.h"
#include "aqua/platform/restore.h"


#include "aqua/primitive/data/_.h"


#include "aqua/primitive/math/objects.h"


#include "aqua/platform/simple_log.h"


#include "aqua/primitive/collection/file_path_map.h"

#include "aqua/primitive/primitive/edit.h"
#include "aqua/platform/department.h"
//#include "aqua/platform/department_container.h"

#include "aqua/multithreading/threading.h"

class mq;

//#include "aqua/platform/live_signal.h"
#include "aqua/multithreading/pred_holder.h"
//#include "aqua/primitive/primitive/command.h"
#include "aqua/multithreading/thread.h"
#include "aqua/multithreading/handler.h"
#include "aqua/multithreading/service_base.h"
#include "aqua/multithreading/service/plain_service.h"
#include "aqua/multithreading/service/plain_service.h"
#include "aqua/multithreading/fork.h"
#include "aqua/multithreading/delay_thread.h"
#include "aqua/multithreading/tools.h"
#include "aqua/platform/timer_callback.h"
#include "aqua/platform/timer_item.h"
#include "aqua/platform/timer_array.h"
#include "aqua/platform/timer.h"
#include "aqua/platform/timer_event.h"

#include "aqua/multithreading/thread_impl.h"
//#include "aqua/multithreading/simple_thread.h"
//#include "aqua/multithreading/go_thread.h"
//#include "aqua/multithreading/signal_thread.h"
#include "aqua/multithreading/procedure_array.h"


///#include "aqua/primitive/primitive/job.h"

//#include "aqua/user/simple/message_box.h"


//#include "aqua/user/impact_data.h"

#include "aqua/platform/log.h"


#include "aqua/primitive/primitive/memory_base.h"
#include "aqua/primitive/primitive/memory.h"
#include "aqua/primitive/primitive/shared_memory.h"
#include "aqua/primitive/primitive/virtual_memory.h"
#include "aqua/primitive/primitive/memory_container.h"







#include "aqua/filesystem/file/memory_file.h"
#include "aqua/filesystem/file/circular_file.h"



//#include "aqua/filesystem/file/timeout_buffer.h"
//#include "aqua/filesystem/file/transfer_buffer.h"

#include "aqua/filesystem/file/memory_map.h"

#include "aqua/primitive/string/international2.h"



//#if defined(_UWP)
//
//#include "app/aqua/os/_UWP/_UWP_sockets.h"
//
//#endif


#include "aqua/primitive/primitive/factory.h"


namespace user
{


   using style_pointer = __pointer(style);


} // namespace user



#include "aqua/graphics/_.h"

#include "aqua/user.h"



#include "aqua/primitive/math/random_number_generator.h"
#include "aqua/primitive/math/department.h"
#include "aqua/primitive/geometry2d/geometry.h"


CLASS_DECL_AQUA string get_exe_path();


#include "aqua/platform/savings.h"

#include "aqua/net/_.h"

#include "aqua/platform/launcher.h"

#include "aqua/platform/ipc.h"

#include "aqua/platform/app_launcher.h"


class zip_context;
//namespace zip
//{
//
//   class util;
//
//} // namespace zip


namespace file
{

   class watcher;

} // namespace file

#include "aqua/filesystem/filesystem/file_system.h"

#include "aqua/filesystem/filesystem/dir_system.h"

#include "aqua/filesystem/filesystem/file_context.h"

#include "aqua/filesystem/filesystem/dir_context.h"

#include "aqua/filesystem/filesystem/listing.h"

#include "aqua/filesystem/file/set.h"

//#include "aqua/primitive/primitive/application_bias.h"

//#include "aqua/primitive/primitive/command.h"


#include "aqua/exception/engine.h"


#include "aqua/platform/fixed_alloc_impl.h"
#include "aqua/primitive/primitive/command_line.h"
//#include "aqua/user/create.h"
//#include "aqua/primitive/primitive/create.h"
#include "aqua/primitive/primitive/request_signal.h"


#include "aqua/platform/net.h"


#include "aqua/filesystem/file/buffered_file.h"


#include "aqua/primitive/datetime/_.h"


#include "aqua/primitive/string/international_locale_schema.h"


//#include "aqua/platform/cregexp.h"
//#include "aqua/platform/cregexp_util.h"


class CLASS_DECL_AQUA ptra :
   virtual public __pointer_array(object)
{
public:


};


typedef ::map < __pointer(object), __pointer(object), __pointer(object), __pointer(object) > element_map;
typedef ::map < __pointer(object), __pointer(object), ptra, ptra > map_many;


namespace zip
{


   class util;


} // namespace zip


#include "aqua/os/text.h"

#ifdef ANDROID

#include "aqua/os/android/_os_local.h"

#endif

#include "aqua/platform/regex.h"

#include "aqua/process/process.h"

#include "aqua/filesystem/filesystem/file_watcher.h"

#include "aqua/platform/os_context.h"

#include "aqua/crypto/crypto.h"

#include "aqua/database/_.h"

//#include "aqua/database/simpledb/_.h"

#include "aqua/user/_.h"




#include "aqua/multimedia/_.h"




//#include "aqua/user/style_coord.h"
//#include "aqua/user/style_rect.h"
#include "aqua/user/item.h"


#include "aqua/platform/exclusive.h"


#include "aqua/platform/application_menu.h"
#include "aqua/platform/application_array.h"
#include "aqua/platform/application_container.h"


#include "aqua/os/process.h"

#include "aqua/platform/ipi.h"

#include "aqua/platform/hyperlink.h"

#include "aqua/platform/context.h"

//#include "aqua/geoip/geoip.h"

class ftpfs;

namespace fs
{

   class remote_native;
   class fs;
   class data;

}

class ifs;

//#include "axis/programming/javascript/javascript.h"

#include "aqua/filesystem/fs/_fs.h"

//#include "aqua/user/userpresence/_.h"

//#include "aqua/html/html_lite/_.h"

//#include "core/user/experience/_.h"

//#include "aqua/filesystem/userfs/_.h"

//#include "aqua/filesystem/filehandler/_.h"

#include "aqua/game/_.h"

#include "aqua/_.h"

#include "aqua/message/_.h"

#include "aqua/platform/context_thread.h"

#include "aqua/filesystem/filemanager/callback.h"

#include "aqua/platform/application.h"

//#include "aqua/platform/app.h"

#include "aqua/platform/application_message.h"

//#include "aqua/account/_account.h"

#include "aqua/filesystem/filemanager/item_action.h"

//#include "aqua/filesystem/filemanager/component.h"

//#include "core/user/userex/userex.h"

#include "aqua/platform/session.h"

#include "aqua/multithreading/retry.h"


CLASS_DECL_AQUA::file::path application_installer_folder(const ::file::path & pathExe, string strAppId, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema);
CLASS_DECL_AQUA bool is_application_installed(const ::file::path & pathExe, string strAppId, string & strBuild, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema);
CLASS_DECL_AQUA bool set_application_installed(const ::file::path & pathExe, string strAppId, const char * pszBuild, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema);
CLASS_DECL_AQUA::file::path get_application_path(string strAppId, const char * pszPlatform, const char * pszConfiguration);
CLASS_DECL_AQUA::file::path get_last_run_application_path_file(string strAppId);
CLASS_DECL_AQUA::file::path get_last_run_application_path(string strAppId);
CLASS_DECL_AQUA bool set_last_run_application_path(string strAppId);

CLASS_DECL_AQUA ::estatus load_factory_library(string strLibrary);


class node_data_exchange;

namespace xml
{

   
   class department;


} // namespace xml


#include "aqua/multimedia/audio/speaker.h"


#include "aqua/multimedia/audio.h"

#include "aqua/multimedia/multimedia.h"

#include "aqua/platform/app_core.h"

//#include "aqua/primitive/collection/map.h"

//#include "aqua/primitive/collection/strid_map.h"

#include "aqua/platform/system.h"

//#include "aqua/platform/system_str.h"




#define new ACME_NEW




/*namespace numeric_info
{


template < typename T >
inline T get_maximum_value()
{
__throw(not_implemented(get_object()));
}

template < typename T >
inline T get_minimum_value()
{
__throw(not_implemented(get_object()));
}
template < typename T >
inline T get_null_value()
{
return 0;
}
template < typename T >
inline T get_unitary_value()
{
return 1;
}

template < typename T >
inline T get_allset_value()
{
T t;
__memset(&t,0xff,sizeof(T));
return t;
}

template < typename T >
inline bool is_signed()
{
return ((T)-1) < 0;
}

template < typename T >
inline bool is_integer()
{
// guess, as float and double is implemented
return true;
}


template < typename T >
inline string json(const T & value)
{
return __str(value);
}

} // namespace numeric_info

*/


//#ifdef VARIADIC_TEMPLATE_FORMAT2
//
//template<typename T,typename... Args>
//inline void string_format::format(const char * & s,const T & value,Args... args)
//{
//
//   while(*s)
//   {
//
//      if(*s == '%' && *(++s) != '%')
//      {
//
//         defer_get_additional_argument(s,value,args...);
//
//         return;
//
//      }
//
//      append(*s++);
//
//   }
//
//   __throw(::exception::exception("extra arguments provided to format"));
//
//
//}
//
//
//
//
//#endif



//#include "aqua/core_os.h"


#include "aqua/os/chronometer.h"


#include "aqua/platform/assert_running_task.h"


#include "aqua/platform/number.h"


#include "aqua/platform/debug.h"


#include "aqua/platform/printf.h"
#include "aqua/platform/sprintf.h"


//#include "aqua/math/_math.h"


// C++ Includes
#include "aqua/os/_.h"
#include "aqua/node/_.h"


#include "aqua/multithreading/data.h"


#include "aqua/platform/shell_launcher.h"


#include "aqua/platform/async.h"


//#include "aqua/platform/mq.h"


#include "aqua/platform/international.h"


//#include "aqua/platform/static_start.h"



#define return_(y, x) {y = x; return;}


extern "C"
{


   i32 _c_lock_is_active(const char * lpszName);
   i32 _c_lock(const char * lpszName,void ** pdata);
   i32 _c_unlock(void ** pdata);


}


CLASS_DECL_AQUA string _ca_get_file_name(const char * psz,bool bCreate = false,i32 * pfd = nullptr);

CLASS_DECL_AQUA string get_system_error_message(u32 dwError);


#include "aqua/platform/simple_app.h"







//#include "app/aqua/node/node.h"


namespace math
{

   template < typename T >
   class complex;


} // namespace math

namespace _std
{


   template <class T> void __swap(T& a, T& b)
   {
      T c(a);
      a = b;
      b = c;
   }


}


//namespace file
//{
//
//
//   class text_stream_string_file;
//
//} // namespace file

//using text_stream = ::text_stream_string_file;



/*
namespace std
{

   using string = ::string;
   using wstring = ::wstring;

   template < class KEY,class VALUE >
   using map = ::map < KEY,const KEY &,VALUE,const VALUE & >;

   template < class TYPE >
   using list = ::list< TYPE >;

   template < class TYPE >
   using vector = ::array< TYPE >;

   template < class TYPE >
   using set = ::set< TYPE >;

   using ostream = stream;
   using ofstream = ::file::file_stream;

   using istream = stream;
   using ifstream = ::file::file_stream;

   using stream = stream;
   using fstream = ::file::file_stream;

   using iostream = stream;
   using iofstream = ::file::file_stream;

   using stringstream = ::text_stream_string_file;
   using ostringstream = ::text_stream_string_file;

   template < typename T >
   using numeric_limits = ::numeric_info < T >;

   //      template <class T> void sort(T & t1,T & t2)
   //    {
   //     __sort < T >(t1,t2);
   //}

   template < class iterator >
   void sort(iterator & a, iterator & b)
   {
      ::sort::quick_sort_iter(a, b);
   }


   template < typename T >
   using stack = ::stack < T >;


   using filebuf = ::file::stdio_file;

   //using ios_base = stream_base;

   // replace ::file:: => ::file::


   using runtime_error = ::runtime_error;

   using stdio_file = ::file::file;


   template < typename T >
   T abs(T t)
   {
      if(t < ::numeric_info< T >::null())
         return -t;
      else
         return t;
   }


   using streamsize = filesize;
   using streampos = filesize;
   using streamoff = filesize;

   using setw = ::file::set_width;

#if !defined(WINDOWS_DESKTOP) && !defined(APPLEOS) && !defined(_UWP)

   using bad_alloc = ::memory_exception;

#endif

   template < typename T >
   using complex = ::math::complex < T >;


   template <class T> const T& min(const T& a,const T& b)
   {
      return !(a > b) ? a : b;
   }
   template <class T> const T& max(const T& a,const T& b)
   {
      return !(a < b) ? a : b;
   }

   template <class RandomAccessIterator>
   void make_heap(RandomAccessIterator first,RandomAccessIterator last)
   {
      ::papaya::make_heap(first,last);
   }

   template <class RandomAccessIterator,class Compare>
   void make_heap(RandomAccessIterator first,RandomAccessIterator last,Compare comp)
   {
      ::papaya::make_heap(first,last,comp);
   }

   template <class RandomAccessIterator,class Compare>
   void pop_heap(RandomAccessIterator first,RandomAccessIterator last)
   {
      ::papaya::pop_heap(first,last);
   }

   template <class RandomAccessIterator,class Compare>
   void pop_heap(RandomAccessIterator first,RandomAccessIterator last,Compare comp)
   {
      ::papaya::pop_heap(first,last,comp);
   }

   template <class RandomAccessIterator,class Compare>
   void push_heap(RandomAccessIterator first,RandomAccessIterator last)
   {
      ::papaya::push_heap(first,last);
   }

   template <class RandomAccessIterator,class Compare>
   void push_heap(RandomAccessIterator first,RandomAccessIterator last,Compare comp)
   {
      ::papaya::push_heap(first,last,comp);
   }

   template <class RandomAccessIterator>
   void sort_heap(RandomAccessIterator first,RandomAccessIterator last)
   {
      ::papaya::sort_heap(first,last);
   }

   template <class RandomAccessIterator,class Compare>
   void sort_heap(RandomAccessIterator first,RandomAccessIterator last,Compare comp)
   {
      ::papaya::sort_heap(first,last,comp);
   }



#if !defined(__APPLE__)

   template <class T> void __swap(T& a, T& b)
   {
      _std::__swap(a, b);
   }

#endif


}*/


template < typename T >
inline string & to_json(string & str, const T & value, bool bNewLine)
{

   return str = __str(value);

}


CLASS_DECL_AQUA int trace_hr(const char * psz,HRESULT hr);

CLASS_DECL_AQUA string get_last_error_string();

CLASS_DECL_AQUA string get_error_string(u64 uiError);

CLASS_DECL_AQUA void set_aura(void * p,::aqua::application * papp);

CLASS_DECL_AQUA ::aqua::application * get_aura(void * p);


#include "aqua/platform/error.h"


#include "aqua/primitive/primitive/_.h"


//#include "aqua/scripting/javascript/javascript.h"


#include "aqua/compress/compress.h"


#include "aqua/graphics/graphics/graphics.h"


#include "aqua/platform/application_consumer.h"


#if !defined(_UWP)


#include "aqua/platform/serial.h"


#endif


#include "aqua/platform/async.h"




#include "aqua/const/idpool.h"


#include "aqua/user/_.h"


#include "aqua/platform/message_box.h"


#include "aqua/platform/console_application.h"


#include "aqua/platform/application.h"


#include "aqua/primitive/primitive/_defer.h"


#include "aqua/multithreading/_impl.h"


#include "aqua/platform/_impl.h"


#include "aqua/primitive/collection/_collection_impl.h"


#ifndef WINDOWS_DESKTOP

#include "aqua/os/cross/windows/windows_thread_impl.h"

#endif


#include "aqua/primitive/collection/_papaya_impl.h"


#include "aqua/primitive/collection/_array_base_impl.h"
#include "aqua/primitive/collection/_array_impl.h"
#include "aqua/primitive/collection/_raw_array_impl.h"
#include "aqua/primitive/collection/_sort_array_impl.h"
#include "aqua/primitive/collection/_papaya_array_impl.h"

#include "aqua/primitive/collection/_list_impl.h"
#include "aqua/primitive/collection/_map_impl.h"

#include "aqua/primitive/collection/_sort_map_impl.h"

#include "aqua/primitive/collection/_fifo_map_impl.h"

#include "aqua/primitive/collection/_papaya_array2d_impl.h"



#include "aqua/platform/_system_smart_pointer_impl.h"
#include "aqua/platform/_system_object_impl.h"
#include "aqua/platform/_system_id_impl.h"
#include "aqua/platform/_system_var_impl.h"




#include "aqua/primitive/string/_impl.h"


#include "aqua/primitive/string/_base_impl.h"


#include "aqua/primitive/primitive/_factory_impl.h"


#include "aqua/primitive/math/_impl.h"


#include "aqua/primitive/collection/_string_array_impl.h"


#include "aqua/primitive/primitive/_impl.h"


#include "aqua/primitive/primitive/_papaya_impl.h"


#include "aqua/primitive/datetime/_impl.h"


#include "aqua/primitive/geometry2d/_impl.h"


#include "aqua/filesystem/_impl.h"


#include "aqua/filesystem/file/_impl.h"


#include "aqua/filesystem/file/_var_stream_impl.h"


#include "aqua/filesystem/file/_text_stream_impl.h"


#include "aqua/net/_impl.h"


#include "aqua/graphics/draw2d/_impl.h"


#include "aqua/exception/_.inl"


#include "aqua/graphics/draw2d/_image_impl.h"


#include "aqua/primitive/string/_str_impl.h"


#include "aqua/graphics/_impl.h"


#include "aqua/filesystem/file/_serializable_impl.h"


#include "aqua/filesystem/file/_.h"


#include "aqua/filesystem/file/_papaya_impl.h"


#include "aqua/filesystem/file/_stream_process_impl.h"


#include "aqua/filesystem/file/_text_stream_impl.h"


#include "aqua/net/_impl.h"


#include "aqua/filesystem/filesystem/_impl.h"


#include "aqua/database/_impl.h"


#include "aqua/os/_impl.h"


