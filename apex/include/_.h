//        apex / thomas thomas thomas my pray my life my GOD
// 
//   
//    
//        ------------------ - --/ ------------------------ - ----/ -------------------------------------- - --
//        DOMAS_16-1109-0.1989 > ThomasBS_ / ------ - ---/ aura.dll Release(Win32) / aura.lib Static Release(Win32)   oe      helloaura.exe     Static     Release(Win32)   ----   -    -- <3Thomas Boregaard SoerensenCamilo SasukeThomas Boregaard Soerensen!!
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




#define __spin_namespace apex // back bone / four-letter "spin*" namespace name


namespace apex
{


   class system;
   class node;
   class session;
   class application;
   
   //class apex;


   //inline system * get_system() { return (system *) get_system()->layer(LAYERED_APEX); }


} // namespace apex



CLASS_DECL_APEX void apex_ref();





#include "apex/message/global.h"


#ifdef WINDOWS_DESKTOP


#if defined _M_IX86
#define _APEX_LINKER_SYMBOL_PREFIX "_"
#elif defined _M_X64 || defined _M_ARM || defined _M_ARM64
#define _APEX_LINKER_SYMBOL_PREFIX ""
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


namespace opengl
{

   class opengl;


} // namespace opengl



extern CLASS_DECL_APEX int g_bApex;


// C-includes
//#include "apex/os/_c.h"


#undef minimum
#undef maximum


#define INTABS(i) (((i) >= 0) ? (i) : (-i))
#define FLOATABS(f) (((f) >= 0.f) ? (f) : (-f))
#define DOUBLEABS(d) (((d) >= 0.0) ? (d) : (-d))








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



#if !defined(O_BINARY) && !defined(WINDOWS)
# define O_BINARY 0
#endif


namespace aqua
{


   class application;
   class session;
   class system;


} // namespace aqua


namespace aura
{


   class application;
   class session;
   class system;


} // namespace aura


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


namespace bred
{


   class application;
   class session;
   class system;
   class user;


} // namespace bred

namespace core
{


   class application;
   class session;
   class system;


} // namespace core


#include "apex/platform/apex_main_struct.h"





//class eimpact;
//
//enum e_simple_command : ::i64;
//enum e_message : ::i64;
//enum e_impact : ::i64;
//enum e_id : ::u64;
//enum enum_check: ::i32;


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


//#include "apex/primitive/math/_.h"


#include "apex/crypto/_.h"


extern "C"
CLASS_DECL_APEX void register_library(const char * psz, ::acme::library * plibrary);


extern "C"
CLASS_DECL_APEX void register_get_new_library(const char* psz, PFN_NEW_LIBRARY pfnnewlibrary);


#define DECLARE_NEW_APEX_LIBRARY(X) extern "C" \
::acme::library * X##_new_apex_library()

#define REGISTER_GET_NEW_APEX_LIBRARY(X) register_get_new_apex_library(#X, &X##_get_new_library)


namespace install
{


   class installer;


} // namespace install


class command_line;


using command_line_pointer = __pointer(command_line);


namespace message
{


   class mouse;


} // namespace message



class form_property_set;


namespace apex
{


   class application;
   class system;
   //class application_message;

   class command;

} // namespace apex


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


class memory;


CLASS_DECL_APEX ::apex::system* platform_create_system(const char * pszAppId);
CLASS_DECL_APEX ::apex::session* platform_create_session();


#define SECOND_NANOS 1000000000


namespace datetime
{


   class department;
   class time;
   class time_span;


} // namespace datetime


namespace trace
{

   class trace;

}


namespace apex
{


   class file;


   class session;

} // namespace apex

CLASS_DECL_APEX bool enable_trace_category(e_trace_category ecategory, bool bEnable = true);

// only usable from axis and axis dependants
namespace apex
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

// only usable from apex and apex dependants
namespace apex
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



namespace draw2d
{


   class graphics;


} // namespace draw2d


class event;


class thread;


class thread;


using thread_pointer = __pointer(::thread);
using thread_array = __pointer_array(thread);


namespace html
{

   class html; // defined and set by html library/component

}


//#define SCAST_PTR(TYPE, ptarget, psource) __pointer(TYPE) ptarget(psource);
//#define SCAST_REF(TYPE, rtarget, psource) TYPE & rtarget = *(dynamic_cast < TYPE * > (psource))


//#define get_session() (Sess(get_session()))

//#define papplication (App(this))
//#define ThisApp (*::application_consumer < application >::get_app())
//#define m_papplication->


//#undef Ctx
//#define Ctx(pobject) (*(::get_context(pobject)))
//#define Context (Ctx(this))




// return - result - if not ok
#ifndef RINOK
#define RINOK(x) { i32 __result__ = (x); if (__result__ != 0) return __result__; }
#endif

// __throw( - exception - result exception - if not ok
#ifndef TINOK
#define TINOK(e, x) { i32 __result__ = (x); if (__result__ != 0) __throw(e(get_application(), __result__)); }
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


class factory_map;


typedef void(*PFN_factory_exchange)(::factory_map * pfactorymap);


class object;

namespace apex
{

   class context;

}


namespace aura
{

   class context;

}


//CLASS_DECL_APEX bool __node_apex_pre_init();
//CLASS_DECL_APEX bool __node_apex_pos_init();

//CLASS_DECL_APEX bool __node_apex_pre_term();
//CLASS_DECL_APEX bool __node_apex_pos_term();


//extern "C" CLASS_DECL_APEX PFN_NEW_APEX_LIBRARY get_get_new_apex_library(const char * psz);
//extern "C" CLASS_DECL_APEX void register_get_new_apex_library(const char* psz, PFN_NEW_APEX_LIBRARY pfnNewAuraLibrary);


//CLASS_DECL_APEX ::acme::library & get_library(const char* psz);
//CLASS_DECL_APEX void register_apex_library(const char* psz, ::acme::library* plibrary);

//CLASS_DECL_APEX ::context * get_context();
//CLASS_DECL_APEX ::context * get_context(::object * pobject);
//CLASS_DECL_APEX inline ::context * get_context(::context * pcontext);


//inline ::object * this;


//CLASS_DECL_APEX void set_global_application(::apex::application * papp);
//CLASS_DECL_APEX ::apex::application * get_global_application();


//CLASS_DECL_APEX ::apex::application * get_application();
//CLASS_DECL_APEX ::apex::application * get_application(::object * pobject);
//CLASS_DECL_APEX inline ::apex::application * get_application(::apex::application * papp);
//CLASS_DECL_APEX inline ::apex::application * get_app() { return get_application(); }


//CLASS_DECL_APEX ::apex::session * get_session();
//CLASS_DECL_APEX ::apex::session * get_session(::object * pobject);
//CLASS_DECL_APEX inline ::apex::session * get_session(::apex::session * psession);


//CLASS_DECL_APEX ::apex::system * ::apex::get_system(::object * pobject);


#define BAD_WCHAR ((widechar)(-1))


#define ARRAY_SIZE(a) (sizeof(a)/sizeof(*(a)))


class payload;
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


#include "apex/platform/definition.h"


class thread_parameter;


namespace primitive
{


   template < typename TYPE >
   class member;


   template < typename TYPE >
   class composite;


   template < typename TYPE >
   class reference;


} // namespace primitive



typedef ::e_status THREAD_ROUTINE(thread_parameter parameter);

class sticker;

template < typename POINTER_TYPE >
class ptr_array;

using object_ptra = __pointer_array(::matter); // Please use just for keeping non-member-based references.

using object_addra = __address_array(::matter); // Please use just for keeping non-member-based references.

class object_meta;


#define __composite_array(TYPE) ::array < __composite(TYPE) >
#define __reference_array(TYPE) ::array < __reference(TYPE) >

namespace http
{

   class context;

} // namespace http


namespace apex
{

   
   class context;


} // namespace apex


namespace draw2d
{

   class graphics;
   class pen;

   using graphics_pointer = __pointer(graphics);
   using pen_pointer = __pointer(pen);


} // namespace draw2d


using generic_pointer = __pointer(::matter);


namespace core
{


   class user;


} // namespace core


//#include "apex/primitive/primitive/object.h"

#include "apex/primitive/subject/_.h"

//#include "apex/primitive/primitive/object.h"

//#include "acme/primitive/primitive/object_meta.h"

#include "app/acme/platform/trace.h"

#include "apex/platform/display.h"


#include "apex/platform/library_object_allocator.h"


#include "apex/platform/library.h"


#include "apex/filesystem/filesystem.h"


#include "apex/platform/progress.h"

#include "apex/parallelization/_.h"


#if defined(LINUX)

#include "apex/os/ansios/_.h"

#elif defined(_UWP)
//
//#include "apex/os/_UWP/_UWP.h"
//#include "apex/os/_UWP/_UWP_user_impl.h"
//
#elif defined(MACOS)
//
//#include "apex/os/ansios/ansios.h"
//#include "apex/os/macos/macos.h"
//
#elif defined(ANDROID)
//
//#include "apex/os/ansios/ansios.h"
//#include "apex/os/android/android.h"
//
#elif defined(WINDOWS_DESKTOP)
//
//#include "apex/os/windows/windows.h"
//
#elif defined(APPLE_IOS)
//
//#include "apex/os/ansios/ansios.h"
//#include "apex/os/ios/ios.h"
////#include "apex/os/ios/ios_windowing.h"
//
#elif defined(SOLARIS)
//
//#include "apex/os/ansios/ansios.h"
//#include "apex/os/solaris/solaris_user_impl.h"
//
#else
//
//#error "not implemented!!"
//
#endif




#include "apex/message/_message.h"


#include "apex/message/message.h"


#include "apex/platform/thread_set.h"


#include "apex/platform/simple_log.h"


//#include "apex/platform/department.h"


#include "apex/parallelization/threading.h"


class message_queue;


namespace windowing
{


   class cursor;


} // namespace windowing


#include "apex/user/check.h"
#include "apex/user/text.h"
#include "apex/user/primitive.h"


#include "apex/parallelization/thread.h"
#include "apex/parallelization/handler.h"
//#include "apex/parallelization/service_status.h"
#include "apex/parallelization/service.h"
#include "apex/parallelization/service_handler.h"
//#include "apex/parallelization/service/plain_service.h"
//#include "apex/parallelization/service/plain_service.h"
//#include "apex/parallelization/fork.h"
#include "apex/parallelization/delay_thread.h"
//#include "apex/parallelization/tools.h"


#include "apex/parallelization/thread_impl.h"


#include "apex/platform/log.h"


namespace user
{


   class style;

   using style_pointer = __pointer(style);


} // namespace user


#include "apex/user.h"

#include "apex/platform/savings.h"

#include "apex/net/_.h"

class launcher;
//#include "apex/platform/launcher.h"

#include "apex/platform/interprocess_communication.h"

//#include "apex/platform/app_launcher.h"


class zip_context;


namespace file
{

   class watcher;

} // namespace file


#include "apex/filesystem/filesystem/file_system.h"

#include "apex/filesystem/filesystem/dir_system.h"

#include "apex/filesystem/filesystem/file_context.h"

#include "apex/filesystem/filesystem/dir_context.h"

#include "apex/filesystem/file/set.h"

#include "apex/platform/net.h"

#include "apex/platform/command_line.h"

#include "apex/platform/create.h"


namespace zip
{


   class util;


} // namespace zip


#include "apex/os/text.h"

#include "apex/process/process.h"

#include "apex/filesystem/filesystem/file_watcher.h"

#include "apex/platform/os_context.h"

#include "apex/crypto/crypto.h"

#include "apex/database/_.h"

#include "apex/user/_.h"


#include "apex/platform/application_menu.h"
#include "apex/platform/application_array.h"
#include "apex/platform/application_container.h"


class interprocess_task;

class interprocess_intercommunication;

using interprocess_task_map = id_map < __pointer(interprocess_task) >;


#include "apex/platform/interprocess_call.h"

#include "apex/platform/interprocess_task.h"

#include "apex/platform/interprocess_communication.h"

#include "apex/platform/interprocess_intercommunication.h"

#include "apex/platform/hyperlink.h"

#include "apex/platform/context.h"


class ftpfs;


namespace fs
{

   class remote_native;
   class fs;
   class data;

}


class ifs;


namespace apex
{


   enum enum_end
   {

      e_end_close,
      e_end_app,
      e_end_session,
      e_end_system,

   };


} // namespace apex


namespace user
{

   
   class menu;


} // namespace user


#include "apex/filesystem/fs/_fs.h"

#include "apex/_.h"

#include "apex/user/text.h"

#include "apex/user/check.h"

#include "apex/user/menu_shared_command.h"

#include "apex/message/command.h"

#include "apex/message/_.h"

#include "apex/platform/context_thread.h"

#include "apex/platform/application.h"

#include "apex/user/_const_key.h"

#include "apex/platform/session.h"

#include "apex/parallelization/retry.h"


//CLASS_DECL_APEX::file::path application_installer_folder(const ::file::path & pathExe, string strAppId, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema);
//CLASS_DECL_APEX bool is_application_installed(const ::file::path & pathExe, string strAppId, string & strBuild, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema);
//CLASS_DECL_APEX bool set_application_installed(const ::file::path & pathExe, string strAppId, const char * pszBuild, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema);
//CLASS_DECL_APEX::file::path get_application_path(string strAppId, const char * pszPlatform, const char * pszConfiguration);
//CLASS_DECL_APEX::file::path get_last_run_application_path_file(string strAppId);
//CLASS_DECL_APEX::file::path get_last_run_application_path(string strAppId);
//CLASS_DECL_APEX bool set_last_run_application_path(string strAppId);


//CLASS_DECL_APEX ::e_status load_factory_library(string strLibrary);


class node_data_exchange;


namespace xml
{


   class xml;


} // namespace xml


#include "apex/platform/app_core.h"


#include "apex/process/_.h"


//#include "apex/primitive/math/department.h"


#include "apex/platform/node.h"


#include "apex/platform/system.h"


#define new ACME_NEW


//#include "apex/os/chronometer.h"


#include "apex/platform/assert_running_task.h"


//#include "apex/platform/debug.h"


// C++ Includes
//#include "apex/os/_.h"
//#include "apex/node/_.h"


#include "apex/parallelization/data.h"


#include "apex/platform/shell_launcher.h"


#include "apex/platform/async.h"


#include "apex/platform/international.h"


#define return_(y, x) {y = x; return;}


extern "C"
{


   i32 _c_lock_is_active(const char * lpszName);
   i32 _c_lock(const char * lpszName,void ** pdata);
   i32 _c_unlock(void ** pdata);


}


#include "apex/platform/simple_app.h"


namespace mathematics
{

   template < typename T >
   class complex;


} // namespace mathematics


#include "apex/platform/error.h"


#include "apex/compress/_.h"


#include "apex/platform/application_consumer.h"


#include "apex/platform/async.h"


#include "apex/const/idpool.h"


#include "apex/user/_.h"


#include "apex/platform/message_box.h"


#include "apex/platform/console_application.h"


#include "apex/platform/application.h"


#include "apex/parallelization/_impl.h"


#include "apex/platform/_impl.h"


#ifndef WINDOWS_DESKTOP


#include "apex/os/cross/windows/windows_thread_impl.h"


#endif


#include "apex/platform/_system_smart_pointer_impl.h"
#include "apex/platform/_system_object_impl.h"
#include "apex/platform/_system_id_impl.h"
#include "apex/platform/_system_var_impl.h"


#include "apex/filesystem/_impl.h"


#include "apex/filesystem/file/_.h"


//#include "apex/net/_impl.h"


#include "apex/filesystem/filesystem/_impl.h"


#include "apex/database/_impl.h"


#include "apex/os/_impl.h"



