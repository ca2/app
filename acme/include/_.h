//        acme / camilo made by thomas
// 
//   
//    
//        ------------------ - --/ ------------------------ - ----/ -------------------------------------- - --
//        DOMAS_16-09-0.1989 > ThomasBS_ / ------ - ---/ aura.dll Release(Win32) / aura.lib Static Release(Win32)   oe      helloaura.exe     Static     Release(Win32)   ----   -    -- <3Thomas Boregaard SoerensenCamilo SasukeThomas Boregaard Soerensen!!
//        2020 - 08 - 18 01:38 / 17, 180kb---- - ---/ 189, 893kb-------- - ---/ 12, 187kb------------------ - --
//        2020 - 08 - 20 07:41 / 13, 915kb / 137, 668kb / 9, 715kb------------------ - --
//        rebuild mark / ---------------- - ------------------------- - -------------------------------- - --
//        ------------------ - --
//
//
//
//
//        ------------------------------------------------------------------------------
//        |                                                                            |
//        |                                                                            |
//        |                                                                            |
//        |                                                                            |
//        |                                                                            |
//        |                                                                            |
//        |                                                                            |
//        |                                                                            |
//        |                                                                            |
//        |                                                                            |
//        |                                                                            |
//        |                                                                            |
//        |                                                                            |
//        |                                                                            |
//        |    |-----------------|    |-----------------| |    |-----------------|     |
//        |    | |---------------|    |-----------------| |    |---------------| |     |
//        |    | |                                      | |                    | |     |
//        |    | |                    |------| |-| |----| |    |---------------| |     |
//        |    | |                    | |----| |-| |----| |    | |---------------|     |
//        |    | |                    | |               | |    | |                     |
//        |    | |---------------|    | |---------------| |    | |---------------|     |
//        |    |-----------------|    |-----------------| |    |-----------------|     |
//        |                                                                            |
//        ------------------------------------------------------------------------------
//
//
//        <3 ThomasBS - 400th follower
//
//
//        ca2 is an all-purpose multi-platform framework
//        and set of libraries written in C++ language with
//        the aim to help developers create awesome apps for users.
//
//
//        ca2/./acme/C++/C/Assembly/Huffman Machine/...
//        ...Hardware/Universe/Multiverse stack
//
//
//
//
//        c(s)t(s)<tb(s)!!
//
//01234567-?8888?+? ??? ??? ????? ??????????? ????? ?????????? ??????? ???????????????????????
//
//
//
//---------------------------------------------------------------------------------------
#pragma once


#define CPP20 1


#define __spin_namespace acme // back bone / four-letter "spin*" namespace name


#pragma once


#define LAYER_NAMESPACE acme

#define _STRINGFY(identifier) #identifier
#define STRINGFY(identifier) _STRINGFY(identifier)
#define STRING_PREFIX_LAYER_NAMESPACE(str) STRINGFY(LAYER_NAMESPACE) str


//#undef Sys


//#define get_system() (::get_context_system())


//#define Node (psystem->node())


#include "acme/primitive/primitive/estatus.h"


#include "_c.h"


#include <tuple>


class object;
class thread;
//class object;


CLASS_DECL_ACME void acme_ref();
//
//
//#ifdef WINDOWS_DESKTOP
//
//typedef i32 WINAPI __MAIN_DEFERRED_RUN(HINSTANCE hinstance, HINSTANCE hPrevInstance, char * pCmdLine, i32 nCmdShow);
//
//#else
//
//typedef i32 __MAIN_DEFERRED_RUN(int argc, char **argv);
//
//#endif
//
//
//typedef __MAIN_DEFERRED_RUN *__LPFN_MAIN_DEFERRED_RUN;
//extern CLASS_DECL_ACME __LPFN_MAIN_DEFERRED_RUN __main_deferred_run;

#ifdef __DEBUG

#define INLINE

#else

#define INLINE inline

#endif


class system; // acme - cam
class app; // apex(::application) - tbs offloading his deep stack in ::app(::acme):cstbs


CLASS_DECL_ACME class system * get_system();


namespace acme
{


   CLASS_DECL_ACME void increment_reference_count();
   CLASS_DECL_ACME void decrement_reference_count();


   class reference
   {
   public:


      reference() { increment_reference_count(); }
      ~reference() { decrement_reference_count(); }


   };


   class node;
   class library;


} // namespace acme


namespace acme_posix
{


   class node;


} // namespace acme_posix


namespace IDENTIFIER_SUFFIX_OPERATING_SYSTEM(aura_)
{


   class node;
   class buffer;


} // namespace IDENTIFIER_SUFFIX_OPERATING_SYSTEM(aura_)




//class ____start
//{
//public:
//
//   ____start() {::acme::initialize();}
//    ~____start() {::acme::finalize();}
//
//};
//


namespace acme_posix { class node; }
namespace apex_posix { class node; }
namespace aura_posix { class node; }


namespace IDENTIFIER_SUFFIX_OPERATING_SYSTEM(acme_) { class node; }
namespace IDENTIFIER_SUFFIX_OPERATING_SYSTEM(apex_) { class node; }
namespace IDENTIFIER_SUFFIX_OPERATING_SYSTEM(aura_) { class node; }


//class IDENTIFIER_SUFFIX_OPERATING_SYSTEM(node_) { class node; }


namespace acme
{


   class system;


   class node;


} // namespace acme


namespace apex
{


   class system;


   class node;


} // namespace apex


namespace aura
{


   class system;


   class node;


} // namespace aura


namespace windowing_win32
{


   class node;


} // namespace windowing_win32


namespace windowing_universal_windows
{

   
   class node;


} // namespace windowing_universal_windows




#define APPLICATION_CLASS app


namespace windowing_x11
{


   class node;


} // namespace windowing_x11


namespace windowing_xcb
{


   class node;


} // namespace windowing_xcb


namespace node_gtk
{


   class node;


} // namespace node_gtk


namespace node_gnome
{


   class node;


} // namespace node_gnome


namespace node_kde
{


   class node;


} // namespace node_kde


namespace node_xfce
{


   class node;


} // namespace node_xfce


namespace desktop_environment_gnome
{


   class node;


} // namespace desktop_environment_gnome


namespace desktop_environment_kde
{


   class node;


} // namespace desktop_environment_kde


namespace desktop_environment_xfce
{


   class node;


} // namespace desktop_environment_xfce


#define ___STR(s) #s
#define __STR(s) ___STR(s)
//#define __IDENTIFIER(identifier) identifier
#define PLATFORM_INCLUDE(include) __STR(__IDENTIFIER(OPERATING_SYSTEM_NAMESPACE)/include)

#ifndef  __STRING
#  define   __STRING(x) "x"
#endif


#include "acme/exception/_c.h"


#include "acme/constant/_.h"


#include "acme/constant/exception.h"


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


#ifndef WINDOWS


#define _CRT_ASSERT 0


#endif


#if defined(DEBUG) && !defined(NO_ACME_MEMORY_MANAGEMENT)
#define ACME_NEW new(__FILE__, __LINE__)
#else
#define ACME_NEW new
#endif

#define new ACME_NEW


#include "acme/platform/object_reference_count_debug.h"

template < class root_derived >
inline i64 increment_reference_count(root_derived * pca OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

template < class root_derived >
inline i64 release(root_derived *& pca OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);


namespace opengl
{

   class opengl;


} // namespace opengl

//
//enum enum_normalize
//{
//
//   e_normalize
//
//};
//

namespace message
{

 
   class command;


} // namespace message

//
//enum enum_null
//{
//
//   e_null
//
//};


template < typename TYPE > inline TYPE *& __defer_new(TYPE *& p) { if (!p) p = new TYPE; return p; }


struct INT_STRING
{

   int m_i;
   const char *m_psz;

};


#include "acme/operating_system/windows_common/arg_sec_attrs.h"


template < typename CONCRETE >
class concrete :
   public CONCRETE
{
public:


   using CONCRETE::CONCRETE;


};


template<class T>
   class ___pointer;


template<class T>
   class pointer_array;


//#define __FACTORY(xxx) __CONCAT(xxx, _factory)
//
//#define DECLARE_FACTORY(decl, xxx) extern "C" decl void __FACTORY(xxx)(::factory::factory * pfactory)
//
//#define BEGIN_FACTORY(xxx) extern "C" CLASS_DECL_EXPORT void __FACTORY(xxx)(::factory::factory * pfactory) { 
//
//#define FACTORY_DEPENDENCY(aaa) __FACTORY(aaa)(pfactory);
//
//#define FACTORY_ITEM(iii) iii::_add_to_factory(pfactory);
//
//#define END_FACTORY() }
//
//
//#define _creatable(expr) static void _add_to_factory(::factory::factory * pfactory) { pfactory->expr; }
//#define _creatable2(expr1, expr2) static void _add_to_factory(::factory::factory * pfactory) { pfactory->expr1; pfactory->expr2; }
//
//
//#define ____creatable(type) add_factory_item < type >()
//
//
//#define ____creatable_from_base(type, base) add_factory_item < type, base >()
//
//
//#define ____creatable_from_id(type, id) add_factory_item < type >(id)
//
//
////#define ____creatable_from_library(type, base, source) ::factory::_add_factory_item_from < type, base >(source)
//
//
////#define __creatable_from_library(type, base, source) _creatable(____creatable_from_library(type, base, source))
//
//
//#define __creatable_from_id(type, id) _creatable(____creatable_from_id(type, id))
//
//
//#define __creatable_from_base(type, base) _creatable(____creatable_from_base(type, base))
//
//
//#define __creatable_and_from_base(type, base) _creatable(____creatable(type), ____creatable_from_base(type, base))
//
//
////#define __creatable_from_library(type, base, source) _creatable(____creatable_from_library(type, base, source))
//
//
//#define __creatable(type) _creatable(____creatable(type))


#include <type_traits>


class matter;
class element;
class stream;
class payload_stream;



template < typename T >
concept a_pointer = std::is_pointer < T >::value;

template < typename T >
concept non_pointer = !std::is_pointer < T >::value;

template < typename T >
concept a_enum = std::is_enum < T >::value;

template < typename T >
concept primitive_integral = std::is_integral < T >::value || std::is_enum < T >::value || std::same_as < T, ::e_status >;

template < typename T >
concept primitive_integer = std::is_integral < T >::value;

template < typename T >
concept primitive_natural = std::is_integral < T >::value && !std::is_signed < T >::value;

template < typename T >
concept primitive_signed = (std::is_integral < T >::value || std::is_enum < T >::value) && std::is_signed < T >::value;

template < typename T >
concept primitive_unsigned = (std::is_integral < T >::value || std::is_enum < T >::value) && !std::is_signed < T >::value;


template < typename T >
concept primitive_floating = std::is_floating_point < T >::value;

template < typename T >
concept primitive_number = std::is_integral < T >::value || std::is_enum < T >::value || std::is_floating_point < T >::value;

template < typename T >
concept primitive_character = 
   std::same_as < T, ::ansichar > || 
   std::same_as < T, ::wd16char > ||
   std::same_as < T, ::wd32char >;


template < typename T >
concept const_c_string =
std::is_convertible < T, const ::ansichar * >::value ||
std::is_convertible < T, const ::wd16char * >::value ||
std::is_convertible < T, const ::wd32char * >::value;




template < bool B, class TRUE_TYPE = void, class ELSE_TYPE = void >
struct if_else {};

template < class TRUE_TYPE, class ELSE_TYPE >
struct if_else < true, TRUE_TYPE, ELSE_TYPE > { using type = TRUE_TYPE; };

template < class TRUE_TYPE, class ELSE_TYPE >
struct if_else < false, TRUE_TYPE, ELSE_TYPE > { using type = ELSE_TYPE; };

template < typename T >
struct base_const_c_string
{

   using type =
      typename if_else <
      std::is_convertible < T, const ansichar * >::value,
      const ansichar *,
      typename if_else <
      std::is_convertible < T, const wd16char * >::value,
      const wd16char *,
      typename if_else <
      std::is_convertible < T, const wd32char * >::value,
      const wd32char *,
      void *
      >::type
      >::type
      >::type;

};

template < typename FROM, typename TO_POINTER >
concept raw_pointer_castable =
   ::std::is_convertible < FROM, TO_POINTER * >::value ||
   ::std::is_convertible < FROM, const TO_POINTER * >::value;


template < typename T >
concept non_const_c_string =
std::is_convertible < T, ::ansichar * >::value ||
std::is_convertible < T, ::wd16char * >::value ||
std::is_convertible < T, ::wd32char * >::value;

template < typename T >
concept c_string =
const_c_string < T > ||
non_const_c_string < T >;

template < typename DERIVED, typename BASE >
concept is_derived_from =
::std::is_base_of < BASE, DERIVED >::value;

template < bool, typename T1, typename T2 >
struct boolean_type_selection { using type = T1; };

template < typename T1, typename T2 >
struct boolean_type_selection<false, T1, T2> { using type = T2; };


template < typename T1, typename T2 >
struct largest_type {
   using type = typename ::boolean_type_selection< (sizeof(T1) > sizeof(T2)), T1, T2>::type;
};


template < typename T1, typename T2 >
struct smaller_type {
   using type = typename ::boolean_type_selection< (sizeof(T1) < sizeof(T2)), T1, T2>::type;
};


template < typename T1, typename T2, typename T3 >
struct largest_type_of_3 {
   using largest_type_of_1_and_2 = typename largest_type < T1, T2 >::type;
   using type = typename ::boolean_type_selection < (sizeof(largest_type_of_1_and_2) > sizeof(T3)), largest_type_of_1_and_2, T3>::type;
};


template < typename TYPE, std::size_t SIZE >
using array_reference = TYPE ( & ) [ SIZE ];





template < typename TYPE, std::size_t SIZE >
inline std::size_t item_count(array_reference < TYPE, SIZE > &) { return SIZE; }


template < typename T >
inline byte byte_clip(const T & t) { return ((byte)(((t) < (byte)0) ? (byte)0 : (((t) > (byte)255) ? (byte)255 : (byte)t))); }





template < typename TYPE, std::size_t SIZE >
inline array_reference < TYPE, SIZE > & __zero(TYPE(&)[SIZE]);




template < a_pointer POINTER>
inline typename std::remove_pointer<POINTER>::type & __zero(POINTER p);

template < non_pointer NON_POINTER>
inline NON_POINTER & __zero(NON_POINTER & t);



template < typename TYPE, std::size_t Size >
inline bool __is_zero(TYPE(&array)[Size]);



template < a_pointer POINTER >
inline bool __is_zero(const POINTER p);

template < non_pointer NON_POINTER >
inline bool __is_zero(const NON_POINTER & t);



#define ___PREFIX_UNDERSCORE(prefix,name) prefix##_##name
#define __PREFIX_UNDERSCORE(prefix,name) ___PREFIX_UNDERSCORE(prefix,name)
#define __EVALUATE_MACRO(name) name






CLASS_DECL_ACME void set_last_status(const ::e_status &estatus);

CLASS_DECL_ACME void windowing_output_debug_string(const char *pszDebugString);


namespace windowing
{

   class window;

} // namespace windowing

//using oswindow = void *;
using windows_handle = void *;
using hinstance = void *;
#ifdef UNICODE
using tchar = wchar_t;
#else
using tchar = char;
#endif



namespace acme
{


   class static_start;


   extern CLASS_DECL_ACME bool g_bAcme;


} // namespace acme


class acme_directory;

class acme_file;

class acme_path;


namespace IDENTIFIER_SUFFIX_OPERATING_SYSTEM(acme_)
{


   class acme_directory;

   class acme_file;

   class acme_path;


} // namespace IDENTIFIER_SUFFIX_OPERATING_SYSTEM(acme_)


// returns true if it should continue...
CLASS_DECL_ACME bool __assert_failed_line(const char *pszFileName, int iLineNumber);

CLASS_DECL_ACME int is_debugger_attached(void);

CLASS_DECL_ACME void debug_print(const char * pszFormat, ...);

CLASS_DECL_ACME void throw_todo();

CLASS_DECL_ACME int throw_assert_exception(const char *pszFileName, int iLineNumber);

//CLASS_DECL_ACME void throw_what_exclamation_exclamation(const char* psz);

#define __pass_array(A) A, sizeof(A)

#ifndef __cplusplus


#define ASSERT assert


#else


#ifdef _DEBUG




#define ASSERT(f)                                              \
{                                                              \
                                                               \
   if(!(f))                                                    \
   {                                                           \
                                                               \
     if(is_debugger_attached())                                \
     {                                                         \
                                                               \
        if(!__assert_failed_line(__FILE__, __LINE__))          \
        {                                                      \
                                                               \
            debug_break();                                     \
                                                               \
        }                                                      \
                                                               \
     }                                                         \
     else                                                      \
     {                                                         \
                                                               \
         throw_assert_exception(__FILE__, __LINE__);           \
                                                               \
     }                                                         \
                                                               \
   }                                                           \
                                                               \
} 


#define _ASSUME(cond)      do { bool _gen__condVal=!!(cond); ASSERT(_gen__condVal); __analysis_assume(_gen__condVal); } while(0)
#define ASSERT_VALID(pOb)  ::__assert_object_ok(pOb, __FILE__, __LINE__)


#else


#define ASSERT(f)
#define _ASSUME(cond)
#if defined(ANDROID)
#define ASSERT_VALID(cond)
#elif defined(__APPLE__)
#define ASSERT_VALID(cond)
#elif defined(LINUX)
#define ASSERT_VALID(cond)
#else
#define ASSERT_VALID(cond) __noop;
#endif
#endif


#endif

#include "acme/primitive/primitive/enumeration.h"





#include "acme/parallelization/_types.h"
#include "acme/constant/_enumeration.h"


#define low_byte(w)              ((byte)((w) & 0xff))


#ifdef __APPLE__


#define IMAGE_Y(y, h) ((h) - (y) - 1)


#else


#define IMAGE_Y(y, h) (y)


#endif


#if defined(WINDOWS) || defined(LINUX) || defined(__i386__) || defined(FREEBSD)


#define IMAGE_A_BYTE_INDEX 3
#define IMAGE_R_BYTE_INDEX 2
#define IMAGE_G_BYTE_INDEX 1
#define IMAGE_B_BYTE_INDEX 0


#define IMAGE_ARGB(a, r, g, b)         ((::color::color)((low_byte(b)|((::u16)(low_byte(g))<<8))|(((u32)low_byte(r))<<16)|(((u32)low_byte(a))<<24)))


#define image_r_value(rgb)    (low_byte((rgb)>>16))
#define image_g_value(rgb)    (low_byte((rgb)>>8))
#define image_b_value(rgb)    (low_byte((rgb)))
#define image_a_value(rgb)    (low_byte((rgb)>>24))


#else


#define IMAGE_A_BYTE_INDEX 3
#define IMAGE_R_BYTE_INDEX 0
#define IMAGE_G_BYTE_INDEX 1
#define IMAGE_B_BYTE_INDEX 2


#define IMAGE_ARGB(a, r, g, b)         ((::color::color)((low_byte(r)|((::u16)(low_byte(g))<<8))|(((u32)low_byte(b))<<16)|(((u32)low_byte(a))<<24)))


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
//#define RGBA(r, g, b, a)         ((::color::color)((low_byte(r)|((::u16)(low_byte(g))<<8))|(((u32)low_byte(b))<<16)|(((u32)low_byte(a))<<24)))
//#define argb(a, r, g, b)      RGBA(r, g, b, a)


#define __acolor(a, r, g, b)      ::color::color(r, g, b, a)


CLASS_DECL_ACME int trailingBytesForUTF8(char ch);


class signal;
class backing;
class manager;
class topic;
class context;
class handler;
template < typename RESULT > class process;
class extended_topic;


CLASS_DECL_ACME int trailingBytesForUTF8(char ch);


CLASS_DECL_ACME int is_ptr_null(const void *p, size_t s);


#define void_ptr_is_null(p) (((uptr)(void *) p) < 4096)

namespace dynamic_source
{


   class script_interface;


} // namespace dynamic_source


#include "acme/primitive/mathematics/mkint_c.h"

// C-includes
#include "acme/_c.h"
#include "acme/memory/memory_allocate.h"
#include "acme/memory/secondary_memory_allocate.h"
#include "acme/memory/heap_c.h"


enum enum_platform_level
{

   e_platform_level_acme,
   e_platform_level_apex,

   e_platform_level_aura,
   e_platform_level_axis,
   e_platform_level_base,
   e_platform_level_core,

};


CLASS_DECL_ACME void set_platform_level(enum_platform_level eplatformlevel);

CLASS_DECL_ACME enum_platform_level get_platform_level();




#ifdef __cplusplus

#include "acme/primitive/comparison/_c.h"


#endif


#define LIM(a, minimum, maximum) minimum(maximum, maximum(minimum, a))
#define SORT_LIM(x, minmax, maxmin) ((minmax) < (maxmin) ? LIM(x,minmax,maxmin) : LIM(x,maxmin,minmax))
#define CLIP_USHRT(x) LIM(x,0,USHRT_MAX)

enum enum_optional
{

   e_optional,

};

#ifdef WINDOWS
#include <intsafe.h>
#else

//#include "acme/operating_system/cross/windows/_include.h"

#endif



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


//typedef struct rdp_freerdp freerdp;


//CLASS_DECL_ACME int_bool
//freerdp_authenticate(void *instance, char **username, char **password, char **domain, const char *pszServerName,
  //                   int bInteractive);


#if !defined(O_BINARY) && !defined(WINDOWS)
# define O_BINARY 0
#endif



CLASS_DECL_ACME i32 ansi_open(const char *psz, i32 i);

CLASS_DECL_ACME FILE *ansi_fopen(const char *psz, const char *pszMode);

CLASS_DECL_ACME int ansi_file_flag(int iFlag);

CLASS_DECL_ACME void ansi_get_errno(i32 *perrno);

CLASS_DECL_ACME void ansi_unlink(const char *psz);


CLASS_DECL_ACME ::e_status get_last_status();




enum e_image_type
{

   image_type_complex,
   image_type_plain_color

};

#include "acme/platform/text.h"

#include "acme/primitive/primitive/_c_memory.h"

#include "acme/primitive/string/_c.h"

#include "acme/primitive/datetime/_c.h"

#include "acme/filesystem/file/_c.h"

#include "acme/constant/thread.h"

#if !defined(__APPLE__) && !defined(LINUX) && !defined(ANDROID)

int ftruncate(int file, filesize len);

#endif


CLASS_DECL_ACME i32 get_os_thread_priority(::enum_priority epriority);

CLASS_DECL_ACME i32 get_os_priority_class(::enum_priority epriority);

CLASS_DECL_ACME ::enum_priority get_os_thread_scheduling_priority(i32 iCa2Priority);

CLASS_DECL_ACME ::enum_priority get_os_class_scheduling_priority(i32 iCa2Priority);


#include "acme/platform/this_type.h"


#include "acme/operating_system/argcargv.h"



CLASS_DECL_ACME void release_on_end(::matter *pmatter);


template<typename TYPE>
TYPE *__release_on_end(TYPE *pmatter)
{

   release_on_end(pmatter);

   return pmatter;

}


CLASS_DECL_ACME extern u32 g_tickStartTime;
//
//#define ALOG_CONTEXT context_trace_object()
//
//#define _S_ALOG_CONTEXT ::context_trace_object()


//
//CLASS_DECL_ACME ::matter * general_trace_object();
//
//CLASS_DECL_ACME int_bool c_enable_trace_category(e_trace_category ecategory, int_bool iEnable);
//
//inline ::matter * context_trace_object() { return general_trace_object(); }


//CLASS_DECL_ACME void __tracea(::matter * pobject, enum_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz);
//CLASS_DECL_ACME void __tracef(::matter * pobject, enum_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz, ...);
//CLASS_DECL_ACME void __tracev(::matter * pobject, enum_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz, va_list vargs);





#define ALOG_CONTEXT context_trace_object()

#define _S_ALOG_CONTEXT ::context_trace_object()



CLASS_DECL_ACME const ::matter * general_trace_object();

CLASS_DECL_ACME int_bool c_enable_trace_category(enum_trace_category ecategory, int_bool iEnable);

inline const ::matter * context_trace_object() { return general_trace_object(); }


//#ifdef WINDOWS
//#include "windows_common.h"
//#endif

//CLASS_DECL_ACME void __tracea(const ::matter * pobject, enum_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz);
//CLASS_DECL_ACME void __tracef(const ::matter * pobject, enum_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz, ...);
//CLASS_DECL_ACME void __tracev(const ::matter * pobject, enum_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz, va_list vargs);


//#define __alog(...) __tracef(__VA_ARGS__)


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


#define INFORMATION(...)                      TRACE_LOG_INFORMATION(__VA_ARGS__)
#define WARNING(...)                      TRACE_LOG_WARNING(__VA_ARGS__)
#define ERROR(...)                                                   TRACE_LOG_ERROR(__VA_ARGS__)
#define FATAL(...)                      TRACE_LOG_FATAL(__VA_ARGS__)


//#define INFORMATION(...) trace_object(ALOG_CONTEXT)->__alog(e_trace_level_information   , ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)
//#define WARN(...) trace_object(ALOG_CONTEXT)->__alog(e_trace_level_warning       , ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)
//#define ERR(...) trace_object(ALOG_CONTEXT)->__alog(e_trace_level_error         , ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)
//#define FATAL(...) trace_object(ALOG_CONTEXT)->__alog(e_trace_level_fatal         , ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)


#define FORMATTED_TRACE(...)              FORMATTED_INFORMATION(__VA_ARGS__)
#define TRACE(...)                        INFORMATION(__VA_ARGS__)




CLASS_DECL_ACME const char *trace_category_name(enum_trace_category ecategory);

CLASS_DECL_ACME const ::matter *trace_object(enum_trace_category ecategory);

CLASS_DECL_ACME const char *topic_text(::matter *pobject);

CLASS_DECL_ACME enum_trace_category object_trace_category(::matter *pobject);


//
//#define __alog(...) __tracef(__VA_ARGS__)
//
//#define INFORMATION(...) __alog(trace_object(ALOG_CONTEXT), e_trace_level_information, ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)
//#define WARN(...) __alog(trace_object(ALOG_CONTEXT), e_trace_level_warning, ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)
//#define ERR(...) __alog(trace_object(ALOG_CONTEXT), e_trace_level_error, ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)
//#define FATAL(...) __alog(trace_object(ALOG_CONTEXT), e_trace_level_fatal, ALOG_FUNCTION, ALOG_FILE, ALOG_LINE, __VA_ARGS__)
//
//#define TRACE(...) INFORMATION(__VA_ARGS__)
//


namespace apex
{


   class theme;


   class idpool;


   class system;


   class session;


   class node;


//   class application;


} // namespace apex


namespace aqua
{


   class system;


   class session;


   class application;


} // namespace aqua


namespace aura
{


   class theme;


   class idpool;


   class application;


   class session;


   class node;


   class system;


} // namespace aura


namespace axis
{


   class idpool;


   class application;


   class session;


   class system;


   class user;


} // namespace axis


namespace base
{


   class idpool;


   class application;


   class session;


   class system;


   class user;


} // namespace base


namespace bred
{

   class system;


   class session;


   class application;

} // namespace bred


namespace core
{


   class idpool;


   class application;


   class session;


   class system;


} // namespace core






//#include "acme/platform/acme_main_struct.h"


//#ifdef WINDOWS
//#pragma warning(disable: 4251)
//#endif

//#include "platform/platform/_.h"

class eimpact;


enum enum_simple_command : ::i64;
enum enum_message : ::i64;
enum enum_impact : ::i64;
enum enum_id : ::u64;
enum enum_check : ::i32;

template<typename TYPE>
struct erase_const_struct
{ // erase top-level const qualifier
   using NON_CONST_TYPE = TYPE;
};

template<typename TYPE>
struct erase_const_struct<TYPE &>
{
   using NON_CONST_TYPE = TYPE &;
};


template<typename TYPE>
struct erase_const_struct<const TYPE>
{
   using NON_CONST_TYPE = TYPE;
};

template<typename TYPE>
struct erase_const_struct<const TYPE &>
{
   using NON_CONST_TYPE = TYPE &;
};

template<class TYPE>
using non_const = typename erase_const_struct<TYPE>::NON_CONST_TYPE;

struct true_type
{
};
struct false_type
{
};


template<typename POINTER>
class raw_pointer
{
public:

   using RAW_POINTER = POINTER;

};


template<typename TYPE>
class raw_type
{
public:

   using RAW_TYPE = TYPE;

};


template<typename TYPE>
class raw_type<TYPE *>
{
public:

   using RAW_TYPE = TYPE;

};


template<typename TYPE>
class raw_type<TYPE *&>
{
public:

   using RAW_TYPE = TYPE;

};


template<typename TYPE>
class raw_type<const TYPE *>
{
public:

   using RAW_TYPE = TYPE;

};


template<typename TYPE>
class raw_type<const TYPE *&>
{
public:

   using RAW_TYPE = TYPE;

};


template<typename LEFT, typename RIGHT>
inline void assign(LEFT &l, const RIGHT &r) { l = r; }


class payload;
struct block;

inline void assign(::block & block, const ::payload & r);

inline void assign(long & l, const ::payload & r);
inline void assign(unsigned long & l, const ::payload & r);


inline void assign(bool & l, const ::payload & r);
inline void assign(::i8 & i8, const ::payload & r);
inline void assign(::u8 & u8, const ::payload & r);
inline void assign(::i16 & i16, const ::payload & r);
inline void assign(::u16 & u16, const ::payload & r);
inline void assign(::i32 & i32, const ::payload & r);
inline void assign(::u32 & u32, const ::payload & r);
inline void assign(::i64 & i64, const ::payload & r);
inline void assign(::u64 & u64, const ::payload & r);


//template < typename, typename >
//inline constexpr auto is_strictly_same_type = false_type();
//template < typename TYPE >
//inline constexpr auto is_strictly_same_type < TYPE, TYPE> = true_type();
//
//template < typename TYPE >
//inline constexpr auto is_void = is_strictly_same_type< TYPE, void>;

#ifdef CPP17

template <typename PRED, typename ... Args >
inline bool _returns_true(PRED pred, const true_type & predicate_returns_void, bool bOnVoid, Args... args)
{
   pred(args...);
   return bOnVoid;
}

template <typename PRED, typename ... Args >
inline bool _returns_true(PRED pred, const false_type & predicate_returns_void, bool, Args... args)
{
   return (bool)pred(args...);
}

template <typename PRED, typename ... Args >
inline bool returns_true(PRED pred, bool bOnVoid, Args... args)
{

   return _returns_true(pred, is_void<decltype(pred(args...))>, bOnVoid, args...);

}

template <typename PRED, typename ... Args >
inline bool _returns_false(PRED pred, const true_type & predicate_returns_void, bool bOnVoid, Args... args)
{
   pred(args...);
   return bOnVoid;
}

template <typename PRED, typename ... Args >
inline bool _returns_false(PRED pred, const false_type & predicate_returns_void, bool, Args... args)
{
   return !(bool)pred(args...);
}

template <typename PRED, typename ... Args >
inline bool returns_false(PRED pred, bool bOnVoid, Args... args)
{

   return _returns_false(pred, is_void < decltype(pred(args...)) >, bOnVoid, args...);

}

#endif


struct block;


template<typename CHAR_TYPE>
class string_base;


struct pixmap;


#define CONSIDER_AS(as, use) using use = as


using ansistring = string_base<ansichar>;
using wd16string = string_base<wd16char>;
using wd32string = string_base<wd32char>;
using widestring = string_base<widechar>;


using string = string_base < ansichar >;
using wstring = string_base < widechar >;


#define __c_str(x) __string((x)).c_str()


template < typename T >
concept has_to_string = requires(T t)
{

   { t.to_string() } -> std::same_as < ::string >;

};

template < typename T >
concept has_get_string = requires(T t)
{

   { t.get_string() } -> std::same_as < ::string >;

};


class machine_event_central;


template<typename ARG_KEY>
inline uptr uptr_hash(ARG_KEY key) { return (uptr) ((uptr) key); }


//#if OSBIT == 64

template<typename ARG_KEY>
inline u32 u32_hash(ARG_KEY key) { return (u32) (uptr_hash<ARG_KEY>(key)); }

//#endif


// #define __base(TYPE, ptarget, psource) for(__pointer(TYPE) ptarget = psource; ptarget.is_set(); ptarget.release())
// #define __base_reference(TYPE, ptarget, source) for(__pointer(TYPE) ptarget = &source; ptarget.is_set(); ptarget.release())
// #define __exception(TYPE) __base(TYPE, pe, e)

#define __rethrow(pe) throw pe;
#define __throw_exit(estatus) throw ::exception(exit_exception(estatus))


#undef _

#define _(str) (__get_text(str))

//typedef string __GET_TEXT(string str);

//using __PFN_GET_TEXT = __GET_TEXT *;



//CLASS_DECL_ACME void __set_get_text(__PFN_GET_TEXT pgettext);

CLASS_DECL_ACME string __get_text(const ::string & str);




//class critical_section;


//namespace command
//{
//
//   class command;
//
//} // namespace command


class trait;


class create;


class synchronization_object;


//CLASS_DECL_ACME i32 acme_run_system(class ::system* psystem);


//CLASS_DECL_ACME ::e_status2 acme_run_system_init(class ::system * psystem);
//CLASS_DECL_ACME ::e_status2 acme_run_system_proc(class ::system * psystem);
//CLASS_DECL_ACME ::e_status2 acme_run_system_term(class ::system * psystem);


#include "acme/primitive/primitive/payload_type.h"


#include "acme/memory/_heap.h"


//#include "acme/exception/_const.h"


//#include "acme/primitive/primitive/bits.h"

#include "acme/primitive/mathematics/_.h"

//#include "acme/user/user/_const.h"

//#include "acme/user/user/_experience_const.h"

#include "acme/filesystem/file/_constant.h"

//#include "acme/graphics/draw2d/_const.h"





enum enum_command
{

   e_command_file_nothing = -1,
   e_command_none = 0,
   e_command_default,
   e_command_application_start,
   e_command_file_new,
   e_command_file_open,
   e_command_file_print,
   e_command_file_print_to,
   e_command_file_dde,
   e_command_app_unregister,
   e_command_request_exit,
   e_command_protocol

};


class composite_base;




#define DECLARE_NEW_ACME_LIBRARY(X) extern "C" \
::acme::library * X##_new_acme_library()


#define REGISTER_GET_NEW_ACME_LIBRARY(X) register_get_new_acme_library(#X, &X##_get_new_library)


namespace install
{


   class installer;


} // namespace install

#include "acme/primitive/primitive/move.h"

class task;


#include "_forward_declaration.h"


using handler_pointer = __pointer(handler);
using manager_pointer = __pointer(manager);
using context_pointer = __pointer(context);


using topic_pointer = __pointer(topic);
using extended_topic_pointer = __pointer(extended_topic);


template<typename THREAD_POINTER>
class ___task_pool;


using task_pointer = __pointer(::task);


class task_pool;


namespace write_text
{

   
   class font_enumeration_item;


   using font_enumeration_item_array = __pointer_array(font_enumeration_item);


} // namespace write_text

//
//namespace extended
//{
//
//
//   template < typename OBJECT >
//   class transport;
//
//
//} // namespace extended
//

//#define __pointer(T) ::extended::transport < T >


// From apex by camilo 2021-11-01 13:41 BRT <3ThomasBorregaardSørensen!!
CLASS_DECL_ACME __pointer(class ::system) platform_create_system(const char * pszAppId);



template<class TYPE>
inline auto &__typed(TYPE &t) { return t; }


template<class POINTER_TYPE>
inline auto &__typed(POINTER_TYPE *p) { return *p; }


template<class POINTER_POINTER_TYPE>
inline auto &__typed(POINTER_POINTER_TYPE **p) { return **p; }


template<class TYPE>
inline auto &__typed_defer_new(TYPE &t) { return t; }


template<class POINTER_TYPE>
inline auto &__typed_defer_new(POINTER_TYPE *&p)
{
   if (!p) { p = new POINTER_TYPE; }
   return *p;
}


template<class POINTER_POINTER_TYPE>
inline auto &__typed_defer_new(POINTER_POINTER_TYPE **p)
{
   if (!*p) { *p = new POINTER_POINTER_TYPE; }
   return **p;
}


template<class T>
inline auto &__typed_defer_new(__pointer(T) &p)
{
   if (!p) { p = new T; }
   return *p;
}

//
//template<class T>
//inline auto &__typed_defer_create(__pointer(T) &p)
//{
//   if (!p) { __construct(p); }
//   return *p;
//}


template < typename TYPE >
inline void __dynamic_cast(TYPE*& ptarget, const TYPE* psource)
{

   ptarget = (TYPE *) psource;

}


template<typename TARGET, typename SOURCE>
inline void __dynamic_cast(TARGET*& ptarget, const SOURCE* psource)
{

   ptarget = dynamic_cast <TARGET*> ((SOURCE *) psource);

}


template<typename T>
inline bool __found(const __pointer(T) &p);


template<typename T>
inline bool __not_found(const __pointer(T) &p);


template<typename TDST, typename TSRC>
inline __pointer(TDST) &clone(__pointer(TDST) &dst, const __pointer(TSRC) &src);

template<typename T>
inline __pointer(T) clone(const __pointer(T) &t);


template<class T>
class guard_pointer;


#define gp(TYPE) ::guard_pointer < TYPE >


//#define clone_impl(name) inline name * clone() { return __new(name(*this)); }


#define DOUBLE_PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844


template<typename TYPE>
inline TYPE *__random_bytes(TYPE *p, memsize s);

template<typename TYPE>
inline TYPE &__random(TYPE &t);

template<typename TYPE>
inline TYPE __random();



template < primitive_floating FLOATING1, primitive_floating FLOATING2, primitive_floating FLOATING_RESULT = typename ::largest_type < FLOATING1, FLOATING2 >::type >
inline FLOATING_RESULT __random(FLOATING1 i1, FLOATING2 i2);


template < primitive_integral INTEGRAL1, primitive_integral INTEGRAL2, primitive_integral INTEGRAL_RESULT = typename ::largest_type < INTEGRAL1, INTEGRAL2 >::type >
inline INTEGRAL_RESULT __random(INTEGRAL1 i1, INTEGRAL2 i2);


//inline i64 __random(i64 i1, i64 i2);

//inline i32 __random(i32 i1, i32 i2);


namespace sort
{


   template<typename TYPE>
   inline void swap(TYPE & a, TYPE & b)
   {
      auto t = a;
      a = b;
      b = t;

   }


} // namespace sort


inline bool is_null(const void * p, size_t s)
{

   return ((size_t) p <= s);

}


template < a_pointer POINTER >
inline bool is_null(POINTER p)
{

   return ((size_t) p <= 65536);

}


template < typename CHAR_STRING >
inline bool is_string_empty(CHAR_STRING p) { return ::is_null(p) || *p == '\0'; }

inline bool is_empty(const ansichar * p) { return is_string_empty(p); }
inline bool is_empty(const wd16char * p) { return is_string_empty(p); }
inline bool is_empty(const wd32char * p) { return is_string_empty(p); }


inline bool has_char(const ansichar * p) { return !is_empty(p); }
inline bool has_char(const wd16char * p) { return !is_empty(p); }
inline bool has_char(const wd32char * p) { return !is_empty(p); }


template < a_pointer POINTER >
inline bool is_set(POINTER p)
{

   return !is_null(p);

}



template<typename TYPE>
inline bool is_ref_set(const TYPE &t)
{

   return is_set(&t);

}


template<typename TYPE>
inline bool is_ok(const TYPE *p)
{

   return ::is_set(p) && p->is_ok();

}


template<typename TYPE>
inline bool is_ok(const __pointer(TYPE) &p)
{

   return ::is_ok(p.m_p);

}


template<typename TYPE>
inline bool nok(TYPE & t)
{

   return !::is_ok(t);

}


class istring;


class property_set;


class payload_array;


class property;


class timer_future;


namespace acme
{

   class Timer;

};


class timer;
class timer_task;


typedef bool FN_TIMER(timer *ptimer);

typedef FN_TIMER *PFN_TIMER;

#define NOK_IMAGE (::e_flag_none)
#define OK_IMAGE (::e_flag_success)
#define DEFAULT_CREATE_IMAGE_FLAG (::e_flag_success)

//#include "acme/constant/_constant.h"

#include "acme/primitive/primitive/tuple.h"


#include "acme/primitive/primitive/_memory.h"


inline bool is_impact_group(::u64 u, ::u64 uGroup) { return u >= uGroup && u < uGroup + 1000; }


inline bool is_impact_subgroup(::u64 u, ::u64 uGroup) { return u >= uGroup && u < uGroup + 100; }


//class command_line;


//using command_line_pointer = __pointer(command_line);


namespace message
{


   class mouse;


} // namespace message




template < typename ARGUMENT >
class argument_of
{
public:

   using type = typename smaller_type < ARGUMENT, const ARGUMENT & >::type;

};


template < >
class argument_of < ::string >
{
public:

   using type = ::block;

};


template < typename T, typename ARG_T = typename argument_of < T >::type >
class single;


template < class KEY, class ARG_KEY = typename argument_of < KEY >::type, class PAYLOAD = single < KEY, ARG_KEY > >
class set;


template < typename T1, typename T2, typename ARG_T1 = typename argument_of < T1 >::type, typename ARG_T2 = typename argument_of < T2 >::type >
class pair;


template < class KEY, class VALUE, class ARG_KEY = typename argument_of < KEY >::type, class ARG_VALUE = typename argument_of < VALUE >::type, class PAIR = pair < KEY, VALUE, ARG_KEY, ARG_VALUE > >
class map;


template<class ENUM>
class flags;


template<class EENUM, EENUM edefault = (EENUM) 0>
class base_enum;


class form_property_set;


namespace acme
{


   //class application;
   //class system;
   //class application_message;

   class command;


} // namespace acme


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


class atom_space;


class ptra;


class factory_item_base;


class fixed_alloc_no_sync;


class critical_section;


class channel;


class critical_section;


class mutex;


class atom;

namespace colorertake5
{

   class ParserFactory;


} // namespace colorertake5


//class pixmap;


class memory;


#define SECOND_NANOS 1000000000


namespace datetime
{


   class department;


   class time;


   class time_span;


} // namespace datetime


template<typename Type, typename RawType = Type, enum_type t_etypePayload = e_type_element >
class string_array_base;


typedef string_array_base < string, string, e_type_string_array > string_array;


namespace file
{

   class listing;


   class path;


   class file;


   enum enum_type
   {

      e_type_unknown = 0,
      e_type_exists = 1 << 0,
      e_type_folder = e_type_exists | (1 << 1),
      e_type_file = e_type_exists | (1 << 2),
      e_type_file_or_folder = e_type_folder | e_type_file,
      e_type_element = e_type_exists | (1 << 3),
      e_type_doesnt_exist = 0x80000000,

   };


} // namespace file


inline bool is_file_or_folder(const ::file::enum_type & etype)
{

   return (etype & ::file::e_type_file_or_folder) > ::file::e_type_exists;

}


inline bool exists(const ::file::enum_type & etype)
{

   return etype & ::file::e_type_exists;

}


class machine_event_data;

namespace hotplugin
{

   class host;


   class plugin;

}


namespace html
{


   class html;


   class element;


} // namespace html


namespace audio
{


   class plugin;


} // namespace audio


#include "acme/primitive/collection/forward.h"



#include "acme/primitive/logic/boolean.h"


#include "acme/platform/auto.h"
#include "acme/primitive/comparison/compare.h"


#include "acme/primitive/primitive/papaya.h"


#include "acme/primitive/primitive/logic.h"


#include "acme/primitive/mathematics/static_numeric_info.h"
#include "acme/primitive/mathematics/numeric_info.h"


#include "acme/primitive/mathematics/c_number.h"


#include "acme/primitive/duration/time.h"


#include "acme/parallelization/wait.h"


#include "acme/primitive/duration/_.h"


#include "acme/primitive/duration/_unit.h"


#include "acme/primitive/duration/time_operator.h"


template<class t>
inline void delptr(t *&p)
{

   if (p != nullptr)
   {

      delete p;

      p = nullptr;

   }

}


template<typename T>
inline int type_is_null(const T *p)
{

   return (((uptr) (void *) p) < maximum(4096, sizeof(T)));

}


#include "acme/primitive/string/_uhash.h"


//class allocer;


namespace acme
{

   template<typename T>
   inline void del(T *&p)
   {

      try
      {

         if (!is_null(p))
         {

            T *pdel = p;

            p = nullptr;

            delete pdel;

         }

      }
      catch (...)
      {

      }

   }


   template<typename T>
   inline void delobj(T *&p);


   template<typename T>
   inline void adel(T *&p)
   {


      try
      {

         if (p != nullptr)
         {

            delete[] p;

            p = nullptr;

         }

      }
      catch (...)
      {

      }

   }


   template<typename T>
   inline void free(T *&p)
   {

      //Thank you Mummi!!


      try
      {

         if (p != nullptr)
         {

            void *pdel = (void *) p;

            p = nullptr;

            ::free(pdel);

         }

      }
      catch (...)
      {

      }

   }


   template<typename T>
   inline void memory_free(T *&p)
   {

      //Thank you Mummi!!

      try
      {

         if (p != nullptr)
         {

            void *pdel = (void *) p;

            p = nullptr;

            ::memory_free(pdel);

         }

      }
      catch (...)
      {

      }

   }


   template<typename T>
   inline T *reset(T *&p, T *pNew)
   {

      ::acme::del(p);

      return p = pNew;

   }


   template<typename T>
   inline T *reset(T *&p)
   {

      ::acme::del(p);

      return p = new T;

   }


} // namespace acme



class image_list;


namespace acme
{


   class file;


   mutex * get_global_mutex();


   namespace trace
   {

      class trace;

   }

   class session;

} // namespace acme


// only usable from base and base dependants
namespace base
{

   class application;

   class session;


   class system;

}


class app_core;


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




class event;


namespace html
{

   class html; // defined and set by html library/component

}


#define SCAST_PTR(TYPE, ptarget, psource) TYPE * ptarget = dynamic_cast < TYPE * > (psource);
#define SCAST_REF(TYPE, rtarget, psource) TYPE & rtarget = *(dynamic_cast < TYPE * > (psource))


// return - result - if not ok
#ifndef RINOK
#define RINOK(x) { i32 __result__ = (x); if (__result__ != 0) return __result__; }
#endif

// throw ::exception( - exception - result exception - if not ok
#ifndef TINOK
#define TINOK(e, x) { i32 __result__ = (x); if (__result__ != 0) throw ::exception(e(get_app(), __result__)); }
#endif


#ifdef WINDOWS
#pragma warning(disable: 4251)  // using non-exported as public in exported
#endif


#ifndef WINDOWS_DESKTOP

typedef void *HDWP;

#endif


namespace factory
{


   class factory;


} // namespace factory


typedef void(*PFN_factory)(::factory::factory * pfactory);


using argument = payload;


using arguments = payload_array;


CLASS_DECL_ACME void __node_acme_pre_init();

CLASS_DECL_ACME void __node_acme_pos_init();

CLASS_DECL_ACME void __node_acme_pre_term();

CLASS_DECL_ACME void __node_acme_pos_term();


#define BAD_WCHAR ((widechar)(-1))


#define ARRAY_SIZE(a) (sizeof(a)/sizeof(*(a)))


class atom;


namespace calculator
{


   class value;


} // namespace calculator






#ifdef __APPLE__
#undef err_none
#endif

#ifdef WINDOWS

template < typename POINTER_TYPE >
class cotaskptr;

template < typename POINTER_TYPE >
class cotaskptr_array;

#endif


class type;


#include "acme/primitive/string/_.h"

namespace text
{
 
   class text;
   class data;
   class translator;


   class table;
   class context;


   namespace international
   {

      class locale_schema;

   }


} // namespace text


//#include "acme/primitive/text/data.h"


#include "acme/primitive/text/text.h"


#include "acme/platform/definition.h"

#include "acme/memory/new.h"


//#include "acme/platform/muldiv64.h"


#include "acme/platform/auto_pointer.h"


#define __m_own(owner, member_reference, ...) (owner)->__compose(member_reference, __VA_ARGS__ )
#define __own(owner, member, ...) __m_own(owner, (owner)->member, __VA_ARGS__ )
#define __unbind(holder, ...) (holder)->__release((holder)-> __VA_ARGS__ )


//CLASS_DECL_ACME ::e_status2 __realize(::matter * pmatter, const ::future & process);


// C-includes
//#include "acme/operating_system/os.h"


class thread_parameter;


#include "acme/primitive/primitive/interlocked.h"
#include "acme/primitive/primitive/interlocked_long_pulse.h"
#include "acme/primitive/primitive/type.h"
#include "acme/primitive/primitive/atom.h"
#include "acme/primitive/primitive/uid.h"


namespace primitive
{


   template<typename TYPE>
   class member;


   template<typename TYPE>
   class composite;


   template<typename TYPE>
   class reference;


} // namespace primitive
#include "acme/primitive/primitive/ptr.h"


#include "acme/primitive/primitive/member.h"


template < typename T >
concept not_pointer = !std::is_pointer < T >::value;

template < typename T >
concept an_object = !std::is_pointer < T >::value 
&& !std::is_integral < T >::value
&& !std::is_enum < T >::value
&& !std::is_floating_point < T >::value;


template<typename TYPE>
inline bool is_null(const __pointer(TYPE)& p);


template<typename TYPE>
inline bool is_set(const __pointer(TYPE)& p);


template < non_pointer NOT_A_POINTER >
inline bool is_null(const NOT_A_POINTER & t)
{

   return is_null(&t);

}


template < not_pointer TYPE >
inline bool is_set(const TYPE & t)
{

   return is_set(&t);

}


//#include "acme/user/user/primitive.h"






template < typename TYPE >
inline ::i64 release(__pointer(TYPE) & pointer OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);


template < typename TYPE >
inline ::i64 __finalize(__pointer(TYPE) & pointer OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);


template < class REFERENCE >
inline ::i64 release(__reference(REFERENCE) & preference OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);


template<typename T>
inline ptr < T > move_transfer(T * p);


template < typename T >
inline T * set_heap_allocated(T * p) { p->set_heap_allocated();  return p; }


#define ___new(...) ::set_heap_allocated( new __VA_ARGS__ )


#define __new(...) ::move_transfer( ___new(__VA_ARGS__ ) )


#include "acme/primitive/primitive/pointer.h"

#include "acme/primitive/primitive/holder.h"


template < typename FROM, typename TO_POINTER >
concept pointer_castable =
   ::std::is_convertible < FROM, TO_POINTER * >::value ||
   ::std::is_convertible < FROM, const TO_POINTER * >::value ||
   ::std::is_convertible < FROM, __pointer(TO_POINTER) >::value;


template < typename FROM >
concept matter_pointer_castable = pointer_castable < FROM, ::matter >;


template < typename FROM >
concept non_matter_pointer_castable = !pointer_castable < FROM, ::matter >;


using element_pointer = __pointer(::element);


using matter_pointer = __pointer(::matter);


namespace message
{


    class message;


} // namespace message


#include "acme/platform/predicate_function_pointer.h"


template<class POINTER_TYPE>
inline auto &__typed(__pointer(POINTER_TYPE) &p) { return *p; }


class duration;


class folder;

class memory_file;

using file_pointer = __pointer(::file::file);

using file_pointer = __pointer(::file::file);

using memory_file_pointer = __pointer(::memory_file);

using folder_pointer = __pointer(::folder);

using folder_pointer = __pointer(::folder);


class binary_stream;


template<typename BASE_TYPE>
inline stream &__save_object(stream &stream, BASE_TYPE *p);


template<typename BASE_TYPE>
inline stream &__save_object(stream &stream, const __pointer(BASE_TYPE) &p)
{

   return __save_object(stream, (BASE_TYPE *) p.m_p);

}



using wparam = c_number<iptr>;


#include "acme/primitive/mathematics/math_clip.h"


#include "acme/primitive/duration/_unit_operator.h"


#include "acme/primitive/duration/_string_format.h"


#include "acme/primitive/duration/_.h"


#include "acme/primitive/datetime/_.h"


#include "acme/primitive/datetime/_string.h"


#include "acme/platform/common.h"



//namespace status
//{
//
//   class result;
//
//} // namespace status

template<typename T>
void __destroy_and_release(__pointer(T) & p)
{

   if (::is_null(p))
   {

      return;

   }

   try
   {

      p->destroy();

   }
   catch (...)
   {

   }

   p.release();

}



namespace message
{

   
   class message;


} // namespace status


class parents;


class children;


//namespace exception
//{


   class exception;

   //using exception_pointer = __pointer(exception);


//} // namespace exception


class event_map;


class thread_ptra;


namespace papaya
{

   class topic;

} // namespace papaya


class memory_base;


//template<typename BASE_TYPE, typename POINT_BASE_TYPE, typename RECTANGLE_BASE_TYPE>
//class size_type;


//using size = size_type<SIZE_I32, POINT_I32, RECTANGLE_I32>;


#include "acme/primitive/mathematics/cast.h"


#include "acme/primitive/primitive/block.h"


#include "acme/memory/chunk.h"


#include "acme/memory/_memory.h"


#include "acme/memory/memory.h"


#include "acme/memory/malloc.h"


//#include "acme/constant/user.h"




#include "acme/exception/status.h"


//inline void throw ::exception(const ::e_status& estatus, const char * pszMessage = nullptr);
//inline void throw ::exception(const ::enum_status& estatus, const char* pszMessage = nullptr);



//CLASS_DECL_ACME ::e_status _003CountStatus(::count countSuccess, ::count countFailed);

#include "acme/constant/filesystem.h"




namespace file
{

   DECLARE_ENUMERATION(e_open, enum_open);
   DECLARE_ENUMERATION(e_state, enum_state);


} // namespace file
class thread;


namespace user
{

   class primitive;

   //class create;


} // namespace user


class action_context;



#include "acme/primitive/primitive/eobject.h"


DECLARE_ENUMERATION(e_message_box, enum_message_box);


namespace user
{

   
   class interaction;

   class form;


} // namespace user


template < typename POINT >
concept primitive_point = requires(POINT point)
{
   point.x;
   point.y;
};


template < typename POINT >
concept XY_point = requires(POINT point)
{
   point.X;
   point.Y;
};


template < typename SIZE >
concept primitive_size = requires(SIZE size)
{
   size.cx;
   size.cy;
};


template < typename SIZE >
concept Dim_size = requires(SIZE size)
{
   size.Width;
   size.Height;
};


template < typename RECTANGLE >
concept primitive_rectangle = requires(RECTANGLE rectangle)
{
   rectangle.left;
   rectangle.top;
   rectangle.right;
   rectangle.bottom;
};


template < typename RECTANGLE >
concept XYDim_rectangle = requires(RECTANGLE rectangle)
{
   rectangle.X;
   rectangle.Y;
   rectangle.Width;
   rectangle.Height;
};


template < typename RECTANGLE >
concept xydim_rectangle = requires(RECTANGLE rectangle)
{
   rectangle.x;
   rectangle.y;
   rectangle.width;
   rectangle.height;
};


#include "acme/platform/lparam.h"


#include "acme/primitive/geometry2d/_.h"


#include "acme/platform/_global.h"


#include "acme/platform/keep.h"


namespace factory
{


   class factory_item_interface;


} // namespace factory


class CLASS_DECL_ACME integral_byte { public: integral_byte(memsize memsize = 1) : m_memsize(memsize) {} memsize m_memsize; operator memsize() const { return m_memsize; } };


#include "acme/constant/parallelization.h"


#include "acme/parallelization/synchronization_result.h"


template < typename TYPE > class sequence;



#include "acme/primitive/primitive/particle.h"
#include "acme/handler/handler.h"
#include "acme/primitive/primitive/e_flag.h"
#include "acme/primitive/primitive/element.h"
#include "acme/primitive/primitive/function.h"
#include "acme/platform/procedure.h"
#include "acme/user/user/conversation.h"
#include "acme/primitive/primitive/tracer.h"
#include "acme/primitive/primitive/matter.h"
//#include "acme/primitive/primitive/linked_property.h"



#include "acme/constant/idpool.h"


//#include "acme/primitive/geometry2d/_geometry2d.h"




class manual_reset_event;


#include "acme/platform/sequence.h"


#include "acme/primitive/primitive/work.h"


#include "acme/primitive/primitive/compare_predicate.h"


#include "acme/platform/status.h"
//#include "acme/primitive/primitive/enumeration.h"





using eiostate = ::enumeration<::file::e_iostate>;

using ecommand = ::enumeration<enum_command>;

using echeck = ::enumeration<enum_check>;


typedef void THREAD_ROUTINE(thread_parameter parameter);


inline bool succeeded(const ::payload & payload);

inline bool succeeded(const ::property &set);


inline bool failed(const ::payload & payload) { return !::succeeded(payload); }


inline bool failed(const ::property &set) { return !::succeeded(set); }


#define __inner_release(outer, inner) ::release(outer, outer->inner)


//#include "acme/primitive/primitive/function.h"


//#include "acme/primitive/primitive/member.h"


#include "acme/primitive/primitive/trait.h"


#include "acme/primitive/primitive/_papaya.h"



#include "acme/primitive/primitive/_factory_prefix.h"


#include "acme/primitive/collection/decl.h"

#include "acme/primitive/collection/raw_array_decl.h"


#include "acme/primitive/collection/comparable_eq_array.h"
#include "acme/primitive/collection/comparable_array.h"
#include "acme/primitive/collection/comparable_raw_array.h"


#include "acme/primitive/collection/pointer_array_process.h"

#include "acme/primitive/collection/pointer_array.h"

#include "acme/primitive/primitive/id_array.h"

#include "acme/primitive/primitive/element_array.h"





//#include "acme/primitive/collection/_papaya_array_decl.h"
#include "acme/primitive/collection/_papaya_heap.h"


#include "acme/primitive/collection/address_array.h"


using element_address_array = ::address_array<matter *>;


#include "acme/primitive/collection/_papaya.h"

class sticker;

inline const ::matter *trace_object(const ::matter *pobject) { return pobject; }

template<typename POINTER_TYPE>
class ptr_array;

using object_ptra = __pointer_array(::matter); // Please use just for keeping non-member-based references.

using matter_array = __pointer_array(::matter); // Please use just for keeping non-member-based references.

using task_array = __pointer_array(::task); // Please use just for keeping non-member-based references.

//using object_addra = __address_array(::matter); // Please use just for keeping non-member-based references.

class object_meta;


#define __composite_array(TYPE) ::array < __composite(TYPE) >
#define __reference_array(TYPE) ::array < __reference(TYPE) >


namespace http
{

   class context;

} // namespace http



#ifdef WINDOWS_DESKTOP

struct hwnd { }; // as pointer is a HWND

using oswindow_t = hwnd;

#else

using oswindow_t = ::windowing::window;

#endif


using oswindow = oswindow_t *;


struct MESSAGE
{

   ::oswindow              oswindow;
   ::atom                    m_atom;
   wparam                  wParam;
   lparam                  lParam;
   point_i32               pt;
   ::u64                   time;

};


using generic_pointer = __pointer(::matter);



namespace core
{


   class user;


} // namespace core


class task;

template < class TYPE, class ARG_TYPE = const TYPE & >
class list;


template < typename TYPE, typename ARG_TYPE = typename argument_of < TYPE >::type, typename PAIR = pair < ::atom, TYPE, typename argument_of < ::atom >::type, ARG_TYPE > >
using id_map = ::map < atom, TYPE, typename argument_of < ::atom >::type, ARG_TYPE, PAIR >;


//using procedure_function = ::function < void() >;


//class CLASS_DECL_ACME procedure :
//   public procedure_function
//{
//public:
//
//
//   using procedure_function::procedure_function;
//   procedure(const ::procedure & procedure) : procedure_function(procedure) { }
//   procedure(::procedure && procedure) : procedure_function(::move(procedure)) { }
//   procedure(::element * pelement) { m_ppredicate = pelement; }
//
//
//};


using procedure = ::function < void() >;

using procedure_array = ::array < ::procedure >;
using procedure_list = ::list < ::procedure >;
using procedure_map = ::id_map < ::procedure_array >;


//using process_array = ::array < process >;

template<typename PRED>
void add_procedure(::procedure_array& array, PRED pred);


//template<typename PRED>
//void add_process(process_array &array, PRED pred);


//} // namespace topic


using exception_array = ::array < ::exception >;


#include "acme/primitive/primitive/linked_property.h"


#include "acme/primitive/primitive/property_object.h"


#include "acme/exception/extended_status.h"



#include "acme/primitive/primitive/material_object.h"


#include "acme/primitive/primitive/enum_bitset.h"


#include "acme/parallelization/task_flag.h"


#include "acme/exception/_.h"


#include "acme/primitive/primitive/pointer2.h"


#include "acme/user/user/conversation.h"


namespace file
{


   class path;
   class path_object;
   class path_array;


} // namespace file


#include "acme/primitive/comparison/var_strict.h"

#include "acme/constant/filesystem.h"

#include "acme/filesystem/filesystem/file_path.h"

#include "acme/primitive/datetime/file_time_span.h"

#include "acme/primitive/datetime/file_time.h"

#include "acme/filesystem/filesystem/path.h"


#include "acme/filesystem/filesystem/path_object.h"


#include "acme/primitive/collection/_collection.h"


#include "acme/graphics/draw2d/_const.h"


#include "acme/graphics/draw2d/opacity.h"


#include "acme/graphics/draw2d/color.h"


#include "acme/primitive/primitive/payload.h"


#include "acme/primitive/collection/payload_array.h"


#include "acme/primitive/primitive/property.h"


#include "acme/primitive/primitive/property_set.h"


#include "acme/primitive/primitive/property_set_papaya.h"


#include "acme/filesystem/filesystem/path_array.h"


#include "acme/filesystem/filesystem/enumerator.h"

#include "acme/platform/predicate_procedure.h"

#include "acme/platform/predicate_process.h"


#include "acme/parallelization/_preamble.h"


#include "acme/parallelization/critical_section.h"


#include "acme/primitive/primitive/factory.h"


CLASS_DECL_ACME void add_release_on_end(::matter * pmatter);


#include "acme/primitive/primitive/object.h"





DECLARE_ENUMERATION(e_dock, enum_dock);
DECLARE_ENUMERATION(e_border, enum_border);
DECLARE_ENUMERATION(e_grip, enum_grip);


namespace draw2d
{


   class graphics;

   using graphics_pointer = __pointer(graphics);


} // namespace draw2d




#define OPTIONAL_BASE_BODY                                                          \
public:                                                                             \
   void on_initialize_object() override {}         \
   void assert_ok() const override {}                                    \
   void dump(dump_context&) const override {}                               \
   void handle(::topic*,::context*) override {}    \
   //void on_subject(::topic::topic*, ::context*) override {} \


#define OPTIONAL_INTERACTION_BODY                                                   \
   OPTIONAL_BASE_BODY                                                               \
   void install_message_routing(::channel*) override {}                     \
   void on_layout(::draw2d::graphics_pointer&) {}


class optional_base1 : virtual public ::object { OPTIONAL_BASE_BODY };
class optional_base2 : virtual public ::object { OPTIONAL_BASE_BODY };
class optional_base3 : virtual public ::object { OPTIONAL_BASE_BODY };
class optional_base4 : virtual public ::object { OPTIONAL_BASE_BODY };

class optional_interaction1 : virtual public ::object { OPTIONAL_INTERACTION_BODY };
class optional_interaction2 : virtual public ::object { OPTIONAL_INTERACTION_BODY };
class optional_interaction3 : virtual public ::object { OPTIONAL_INTERACTION_BODY };
class optional_interaction4 : virtual public ::object { OPTIONAL_INTERACTION_BODY };


class context_image;


#include "acme/parallelization/_parallelization.h"


#include "acme/primitive/data/_.h"


#include "acme/primitive/text/_.h"


#include "acme/primitive/string/_string.h"


#include "acme/platform/context.h"




//#include "acme/parallelization/pool.h"

//#include "acme/primitive/geometry2d/_collection.h"

//#include "acme/primitive/geometry3d/_.h"

//class message_box;

CLASS_DECL_ACME ::atom message_box_synchronous(::object * pobject, const char * pszMessage, const char * pszTitle = nullptr, enum_message_box emessagebox = e_message_box_ok, const char * pszDetails = nullptr);

CLASS_DECL_ACME void message_box_asynchronous(::function < void(const ::atom & atom) > function, ::object * pobject, const char * pszMessage, const char * pszTitle = nullptr, enum_message_box emessagebox = e_message_box_ok, const char * pszDetails = nullptr);


#include "acme/memory/counter.h"

#include "acme/platform/debug.h"

#include "acme/platform/class.h"

//#include "acme/primitive/comparison/md5.h"

#include "acme/primitive/primitive/request_interface.h"



//#include "acme/parallelization/synchronization_object.h"

//#include "acme/xml/exportable.h"

//#include "acme/xml/importable.h"

#include "acme/primitive/comparison/_.h"

#include "acme/primitive/primitive/traits.h"

//#include "acme/system_setup.h"

#include "acme/platform/string_exchange.h"


CLASS_DECL_ACME string merge_colon_args(const array<string_array> &str2a);


//class callstack;


//CLASS_DECL_ACME __pointer(callstack) get_callstack(const char *pszFormat = "%f(%l) %s\n", iptr iSkip = -1000,
                                                   //void *caller_address = nullptr, iptr iCount = -1);

//CLASS_DECL_ACME __pointer(callstack) get_callstack(e_callstack ecallstack, int iCallStackAddUp = 0);

//CLASS_DECL_ACME void set_callstack_mask(enumeration<e_callstack> ecallstack);

//CLASS_DECL_ACME e_callstack get_callstack_mask();

//inline bool is_callstack_enabled(e_callstack ecallstack) { return (i64) get_callstack_mask() & (i64) ecallstack; }


#include "acme/platform/fixed_alloc.h"


#include "acme/memory/allocate.h"
//#include "acme/memory/plex.h"


#include "acme/primitive/primitive/atom.h"


inline bool is_filemanager(const ::atom & atom)
{

   if(atom.is_text())
   {

      return ::str().begins(atom.m_psz, "file_manager_");

   }

   return is_impact_group(atom.i64(), FILEMANAGER_IMPACT);

}


inline bool is_filemanager_group(const ::atom & atom, const char * pszGroup)
{

   if(!atom.is_text())
   {

      return false;

   }

   string strFileManagerGroup;

   strFileManagerGroup.format("file_manager_%s", pszGroup);

   if(atom == strFileManagerGroup)
   {

      return true;

   }

   strFileManagerGroup += "_";

   if(::str().begins(atom.m_psz, strFileManagerGroup))
   {


      return true;

   }

   return false;

}


inline bool is_filemanager_group(const ::atom & atom, int iGroup)
{

   if(atom.is_text())
   {

      return false;

   }

   return is_impact_subgroup(atom.i64(), FILEMANAGER_IMPACT + iGroup);

}


inline bool is_color_sel(const ::atom & atom) { return is_impact_group(atom.i64(), COLORSEL_IMPACT); }


inline bool is_font_sel(const ::atom & atom) { return is_impact_group(atom.i64(), FONTSEL_IMPACT); }


#include "acme/primitive/string/composite.h"


#include "acme/primitive/collection/composite_array.h"


namespace acme
{

   inline ::atom atom(const class ::payload & payload);

   inline ::atom atom(const property &prop);

   inline ::atom atom(const ::std::type_info &info);

   inline ::atom atom(const char *psz);

   inline ::atom atom(const string &str);

   inline ::atom atom(i64 i);

   inline atom_space &atom();


} //namespace acme


template<class POINTER_TYPE>
inline auto &__typed(__composite(POINTER_TYPE) *pp) { return *pp->operator POINTER_TYPE *(); }





#include "acme/platform/display.h"





#include "acme/filesystem/file/status.h"
#include "acme/filesystem/file/translatable.h"
#include "acme/filesystem/file/streamable.h"
#include "acme/filesystem/file/streamable_composite.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/file/stream.h"
#include "acme/filesystem/file/binary_stream.h"
#include "acme/filesystem/file/payload_stream.h"
#include "acme/filesystem/file/string_file.h"
#include "acme/filesystem/file/text_stream.h"


//#include "acme/filesystem/filesystem/acme_directory.h"
//#include "acme/filesystem/filesystem/acme_file.h"
//#include "acme/filesystem/filesystem/acme_path.h"


#include "acme/exception/_dump_context.h"


inline int read_char(u8 *&pdata, memsize &s, char *pch)
{

   if (s < 1)
   {

      return 0;

   }

   *pch = (char) *pdata;

   pdata++;

   s--;

   return 1;

}


template<class TYPE>
inline void dump_elements(dump_context &dumpcontext, const TYPE *pElements, ::count nCount);


//#include "acme/common.h"


#include "acme/filesystem/file/cpp.h"

//#include "acme/platform/library_object_allocator.h"

//#include "acme/platform/library.h"


#include "acme/filesystem/filesystem.h"


#include "acme/constant/source.h"


DECLARE_ENUMERATION(e_source, enum_source);




using lresult = iptr;


#include "acme/constant/context.h"
#include "acme/platform/message.h"
#include "acme/primitive/primitive/action_context.h"


#include "acme/platform/cmp.h"


#include "acme/filesystem/file/string_file.h"


#include "acme/filesystem/file/payload_stream.h"


#include "acme/primitive/primitive/payload2.h"


#include "acme/primitive/primitive/atom_space.h"


namespace mathematics
{

   class mathematics;

} // namespace mathematics


#include "acme/primitive/mathematics/scalar_enum.h"


#include "acme/primitive/mathematics/scalar.h"


//#include "acme/platform/progress.h"


#include "acme/platform/enum.h"










#include "acme/operating_system/_.h"



CLASS_DECL_ACME string get_status_message(const ::e_status & estatus);


#include "acme/platform/flags.h"
#include "acme/constant/check.h"


#include "acme/platform/keep.h"
#include "acme/platform/restore.h"


#include "acme/primitive/mathematics/objects.h"


//#include "acme/primitive/collection/file_path_map.h"


//#include "acme/primitive/primitive/edit.h"


class mq_base;


namespace acme
{


   class timer_array;


} // namespace acme



#include "acme/platform/timer_callback.h"


#include "acme/platform/procedure_array.h"


#include "acme/primitive/primitive/memory_base.h"
#include "acme/primitive/primitive/memory.h"
//#include "acme/primitive/primitive/shared_memory.h"
//#include "acme/primitive/primitive/virtual_memory.h"
#include "acme/primitive/primitive/memory_container.h"


#include "acme/filesystem/file/memory_file.h"
//#include "acme/filesystem/file/circular_file.h"



//#include "acme/filesystem/file/timeout_buffer.h"
//#include "acme/filesystem/file/transfer_buffer.h"

#include "acme/filesystem/file/memory_map.h"

#include "acme/primitive/string/international2.h"




CLASS_DECL_ACME string get_exe_path();



namespace file
{

   class watcher;

} // namespace file


#include "acme/filesystem/filesystem/listing.h"


#include "acme/platform/fixed_alloc_impl.h"


#include "acme/platform/net.h"


//#include "acme/filesystem/file/buffered_file.h"


#include "acme/platform/department.h"


#include "acme/primitive/datetime/_datetime.h"


struct lib_main_int
{

   int               m_iAny = 0;
   ::duration        m_durationProcessAttach;
   ::duration        m_durationProcessDetach;
   ::duration        m_durationThreadAttach;
   ::duration        m_durationThreadDetach;

};


#include "acme/networking/_.h"


//#include "acme/primitive/text/context.h"


//#include "acme/primitive/datetime/_.h"


//#include "acme/primitive/text/international_locale_schema.h"


//#include "acme/platform/cregexp.h"
//#include "acme/platform/cregexp_util.h"


//class CLASS_DECL_ACME ptra :
//        virtual public __pointer_array(matter)
//{
//public:
//
//
//};

//
//template < typename KEY, typename VALUE, typename ARG_VALUE = typename argument_of < VALUE >::type, class PAIR = pair<__pointer(KEY), VALUE, __pointer(KEY), ARG_VALUE> >
//using pointer_map = map < __pointer(KEY), __pointer(KEY), VALUE, ARG_VALUE, PAIR >;
//
//template < typename KEY, typename VALUE, class PAIR = pair<__pointer(KEY), __pointer(VALUE), __pointer(KEY), __pointer(VALUE)> >
//using pointer_to_pointer = pointer_map < KEY, __pointer(VALUE), __pointer(VALUE), PAIR >;
//
//template < typename KEY, typename VALUE, class PAIR = pair< KEY, __pointer(VALUE), KEY, __pointer(VALUE)> >
//using map_to_pointer = map < KEY, KEY, __pointer(VALUE), __pointer(VALUE), PAIR >;

//using matter_to_matter = map < __pointer(matter), __pointer(matter) >;
//using matter_to_ptra = map < __pointer(matter), ptra > ;


//namespace zip
//{
//
//
//   class util;
//
//
//} // namespace zip
//

#include "acme/operating_system/text.h"


//#ifdef ANDROID

//#include "acme/operating_system/android/_os_local.h"

//class android_driver;
//class android_direct;

//android_driver * __android_proxy();
//android_direct * __android_direct();

//void set_oslocal(android_driver * poslocal);
//void set_osremote(android_direct * posremote);

//#endif

//#include "acme/platform/regex.h"

#include "acme/process/_.h"

#include "acme/operating_system/process.h"






//#include "acme/platform/exclusive.h"


#include "acme/process/_.h"


//#include "acme/platform/hyperlink.h"


class ftpfs;


namespace fs
{

   class remote_native;


   class fs;


   class data;

}

class ifs;

#include "acme/_.h"

class node_data_exchange;

namespace xml
{


   class xml;


} // namespace xml


#define new ACME_NEW


//#include "acme/operating_system/chronometer.h"


#include "acme/platform/number.h"



i32 CLASS_DECL_ACME MultiByteToWideChar2(::u32 CodePage, ::u32 dwFlags, const ansichar *pMultByteStr, i32 cbMultiByte,
                                         widechar *pWideCharStr, i32 cchWideChar);

i32 CLASS_DECL_ACME WideCharToMultiByte2(::u32 CodePage, ::u32 dwFlags, const widechar *pWideCharStr, i32 cchWideChar,
                                         ansichar *pMultByteStr, i32 cbMultiByte, const char *pDefaultChar,
                                         int_bool *pUsedDefaultChar);


#include "acme/primitive/text/international.h"




#define return_(y, x) {y = x; return;}



#include "acme/primitive/primitive/osdata_array.h"


namespace mathematics
{

   template<typename T>
   class complex;


} // namespace mathematics

namespace _std
{


   template<class T>
   void __swap(T &a, T &b)
   {
      T c(a);
      a = b;
      b = c;
   }


}



template<typename T>
inline string &to_network_payload(string &str, const T &value, bool bNewLine)
{

   return str = __string(value);

}



CLASS_DECL_ACME string get_last_error_string();




#include "acme/platform/error.h"


#include "acme/primitive/primitive/_.h"



#if !defined(_UWP)


#include "acme/platform/serial_shared.h"


#endif




namespace draw2d
{


   class graphics;
   class path;


} // namespace draw2d


class wcsdup_array;


DECLARE_ENUMERATION(e_element, enum_element);


#include "acme/graphics/draw2d/_.h"


#include "acme/user/user/_.h"


#include "acme/user/user/ewindowflag.h"


#include "acme/constant/application_capability.h"


using enum_application_capability_array = ::comparable_array < enum_application_capability >;


#include "acme/platform/node.h"


#include "acme/platform/predicate_holder.h"


#include "acme/parallelization/fork.h"


//#include "acme/parallelization/tools.h"


#include "acme/platform/main.h"


#include "acme/platform/acme_main_struct.h"


CLASS_DECL_ACME string implementation_name(const ::string& strComponent, const ::string& strImplementation);


CLASS_DECL_ACME string library_name(const ::string & strComponent, const ::string & strImplementation);


CLASS_DECL_ACME string factory_name(const ::string& strLibrary);


CLASS_DECL_ACME string library_filter(const ::string& str);


#include "acme/regular_expression/_regular_expression.h"


#include "acme/platform/log.h"


namespace user
{


   class primitive;
   class element;
   class primitive_impl;


   DECLARE_ENUMERATION(e_flag, enum_flag);


} // namespace user




#include "acme/handler/item.h"
#include "acme/handler/topic.h"
#include "acme/handler/extended_topic.h"



namespace geometry
{

   class geometry;

} // namespace geometry

class compress;
class uncompress;

//class system_impl;


//namespace str
//{
//
 class base64;
//
//} // namespace str


namespace acme
{

   class library;


   using library_map = string_map < __pointer(::acme::library) >;

} // namespace acme

class task_group;
class task_tool;



#include "acme/platform/app_core.h"



#include "acme/platform/app.h"



#include "acme/platform/plane_system.h"



#include "acme/platform/system.h"



#include "acme/primitive/duration/_duration.h"



#include "acme/primitive/primitive/_defer.h"



#include "acme/parallelization/_impl.h"


#include "acme/platform/_impl.h"




#include "acme/primitive/collection/_papaya_impl.h"


#include "acme/primitive/collection/_array_base_impl.h"
#include "acme/primitive/collection/_array_impl.h"
#include "acme/primitive/collection/_array_impl2.h"
#include "acme/primitive/collection/_raw_array_impl.h"
#include "acme/primitive/collection/_sort_array_impl.h"
#include "acme/primitive/collection/_papaya_array_impl.h"
#include "acme/primitive/collection/_tiny_array_impl.h"

#include "acme/primitive/collection/_list_impl.h"
#include "acme/primitive/collection/_map_impl.h"
#include "acme/primitive/collection/_set_impl.h"

#include "acme/primitive/collection/_sort_map_impl.h"

#include "acme/primitive/collection/_fifo_map_impl.h"

#include "acme/primitive/collection/_papaya_array2d_impl.h"


#include "acme/primitive/string/_c_impl.h"


#include "acme/primitive/string/_impl.h"


#include "acme/primitive/string/_base_impl.h"


#include "acme/primitive/primitive/_factory_impl.h"


#include "acme/primitive/mathematics/_impl.h"


#include "acme/primitive/collection/_string_array_impl.h"


#include "acme/primitive/primitive/_impl.h"


#include "acme/primitive/primitive/_papaya_impl.h"


#include "acme/primitive/duration/integral/_impl.h"


#include "acme/primitive/duration/duration/_impl.h"


#include "acme/primitive/datetime/_impl.h"


//#include "acme/primitive/geometry2d/_impl.h"


#include "acme/filesystem/_impl.h"


#include "acme/filesystem/file/_impl.h"


#include "acme/filesystem/file/_payload_stream_impl.h"


#include "acme/filesystem/file/_text_stream_impl.h"




#include "acme/primitive/string/_str_impl.h"


#include "acme/filesystem/file/_serializable_impl.h"


#include "acme/filesystem/file/_.h"


#include "acme/filesystem/file/_papaya_impl.h"


#include "acme/filesystem/file/_stream_process_impl.h"


#include "acme/filesystem/file/_text_stream_impl.h"


#include "acme/filesystem/filesystem/_impl.h"


#include "acme/primitive/primitive/_atom_impl.h"


#include "acme/primitive/primitive/_payload_impl.h"


#include "acme/primitive/primitive/_property_object_impl.h"


#include "acme/primitive/primitive/_interlocked_count_impl.h"


#include "acme/memory/_impl.h"


#include "acme/exception/_impl.h"


