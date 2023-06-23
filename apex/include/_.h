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


#undef LAYER_NAMESPACE
#define LAYER_NAMESPACE apex
#define SYSTEM_NAMESPACE LAYER_NAMESPACE


#define __spin_namespace apex // back bone / four-letter "spin*" namespace name


namespace apex
{


   class system;
   class node;
   class session;
   

   class application;


   //class apex;


   //inline system * acmesystem() { return (system *) acmesystem()->layer(LAYERED_APEX); }


} // namespace apex



CLASS_DECL_APEX void apex_ref();


#include "_forward_declaration.h"



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


#if defined(APPLE_IOS) || defined(ANDROID) || defined(UNIVERSAL_WINDOWS)

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



class api;


class api_client;


extern CLASS_DECL_APEX int g_bApex;


// C-includes
//#include "apex/os/_c.h"


#undef minimum
#undef maximum


//#define INTABS(i) (((i) >= 0) ? (i) : (-(i)))
//#define FLOATABS(f) (((f) >= 0.f) ? (f) : (-(f)))
//#define DOUBLEABS(d) (((d) >= 0.0) ? (d) : (-(d)))
//
#undef APPLICATION_INCLUDE
#define APPLICATION_INCLUDE "apex/platform/application.h"
#undef APPLICATION_CLASS
#define APPLICATION_CLASS ::apex::application





//
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
//
//#define __u64(a, b)                                   (((::u64)(((::u32)(((::u64)(a)) & 0xffffffff)) | ((::u64)((::u32)(((::u64)(b)) & 0xffffffff))) << 32)))
//
//
//#else
//
//#define __MAKE_LONG64(a, b)                              (((u64)(((u32)(((u64)(a)) & 0xffffffff)) | ((u64)((u32)(((u64)(b)) & 0xffffffff))) << 32)))
//#define __u64(a, b)                                   (((u64)(((u32)(((u64)(a)) & 0xffffffff)) | ((u64)((u32)(((u64)(b)) & 0xffffffff))) << 32)))
//
//#endif
//
//#define lower_u16(u)                                     ((::u16)(((::uptr)(u)) & 0xffff))
//#define upper_u16(u)                                     ((::u16)((((::uptr)(u)) >> 16) & 0xffff))
//#define lower_u32(u)                                     ((::u32)(u))
//#define upper_u32(u)                                     ((::u32)(((u) >> 32) & 0xffffffff))
//
//#define u32_x(u)                                     ((::i16)lower_u16(u))
//#define u32_y(u)                                     ((::i16)upper_u16(u))
//
//#define __u32xy(u)                                    u32_x(u), u32_y(u)
//
//#define u64_x(u)                                     ((::i32)lower_u32(u))
//#define u64_y(u)                                     ((::i32)upper_u32(u))
//
//#define __u64xy(u)                                    u64_x(u), u64_y(u)
//
//
//#ifndef i32_x
//#define i32_x(lparam)                          ((i32)(i16)LOWORD(lparam))
//#endif
//
//
//#ifndef i32_y
//#define i32_y(lparam)                          ((i32)(i16)HIWORD(lparam))
//#endif
//
//#define GET_X_LPARAM64(lparam)                        ((i32)(i16)lower_u32(lparam))
//#define GET_Y_LPARAM64(lparam)                        ((i32)(i16)upper_u32(lparam))
//
//
//
//#if !defined(O_BINARY) && !defined(WINDOWS)
//# define O_BINARY 0
//#endif


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



#include "apex/handler/_.h"


#include "apex/platform/_critical_section.h"


//#include "acme/platform/library.h"


#include "apex/filesystem/_.h"


#include "apex/interprocess/_.h"


//#include "apex/platform/apex_main_struct.h"






//class eimpact;
//
//enum e_simple_command : ::i64;
//enum e_message : ::i64;
//enum enum_impact : ::i64;
//enum ::enum_id : ::u64;
//enum enum_check: ::i32;


//template < typename CHAR_TYPE >
//class string_base;


struct pixmap;


#define CONSIDER_AS(as, use) using use = as

//
//using ansi_string = string_base < ::ansi_character >;
//using wd16_string = string_base < ::wd16_character >;
//using wd32_string = string_base < ::wd32_character >;
//using wide_string = string_base < ::wide_character >;
//
//
//using string = string_base < ::ansi_character >;
//using wstring = string_base < ::wide_character >;


class machine_event_central;


#include "apex/crypto/_.h"


extern "C"
CLASS_DECL_APEX void register_library(const ::scoped_string & scopedstr, ::acme::library * plibrary);


extern "C"
CLASS_DECL_APEX void register_get_new_library(const ::scoped_string & scopedstr, PFN_NEW_LIBRARY pfnnewlibrary);


#define DECLARE_NEW_APEX_LIBRARY(X) extern "C" \
::acme::library * X##_new_apex_library()

#define REGISTER_GET_NEW_APEX_LIBRARY(X) register_get_new_apex_library(#X, &X##_get_new_library)


namespace install
{


   class installer;


} // namespace install


namespace message
{


   class mouse;


} // namespace message



class form_property_set;


namespace apex
{


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

//class dump_context;

class atom_space;
class ptra;
class factory_item_base;
class fixed_alloc_no_sync;
class critical_section;
class payload_array;
class thread;
class channel;
class critical_section;
class mutex;
class atom;

namespace colorertake5
{

   class ParserFactory;


} // namespace colorertake5


class memory;




namespace datetime
{


   class department;


} // namespace datetime



namespace earth
{


   class time;
   class time_span;
   class zonetime;


} // namespace datetime


//namespace trace
//{

   class trace;

//}


namespace apex
{


   class file;


   class session;

} // namespace apex


CLASS_DECL_APEX bool enable_trace_category(enum_trace_category ecategory, bool bEnable = true);


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


using thread_pointer = ::task_pointer;
using thread_array = pointer_array < thread >;


namespace html
{

   class html; // defined and set by html library/component

}


//#define SCAST_PTR(TYPE, ptarget, psource) ::pointer<TYPE>ptarget(psource);
//#define SCAST_REF(TYPE, rtarget, psource) TYPE & rtarget = *(dynamic_cast < TYPE * > (psource))


//#define get_session() (Sess(get_session()))

//#define papp (App(this))
//#define ThisApp (*::app_consumer < application >::get_app())
//#define m_pacmeapplication->


//#undef Ctx
//#define Ctx(pparticle) (*(::get_context(pparticle)))
//#define Context (Ctx(this))




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

typedef void * HDWP;

#endif


typedef void(*PFN_factory)(::factory::factory * pfactory);


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


//extern "C" CLASS_DECL_APEX PFN_NEW_APEX_LIBRARY get_get_new_apex_library(const ::scoped_string & scopedstr);
//extern "C" CLASS_DECL_APEX void register_get_new_apex_library(const ::scoped_string & scopedstr, PFN_NEW_APEX_LIBRARY pfnNewAuraLibrary);


//CLASS_DECL_APEX ::acme::library & get_library(const ::scoped_string & scopedstr);
//CLASS_DECL_APEX void register_apex_library(const ::scoped_string & scopedstr, ::acme::library* plibrary);

//CLASS_DECL_APEX ::context * get_context();
//CLASS_DECL_APEX ::context * get_context(::particle * pparticle);
//CLASS_DECL_APEX inline ::context * get_context(::context * pcontext);


//inline ::object * this;


//CLASS_DECL_APEX void set_global_application(::apex::application * papp);
//CLASS_DECL_APEX ::application * get_global_application();


//CLASS_DECL_APEX ::application * get_app();
//CLASS_DECL_APEX ::application * get_app(::particle * pparticle);
//CLASS_DECL_APEX inline ::application * get_app(::apex::application * papp);
//CLASS_DECL_APEX inline ::application * get_app() { return get_app(); }


//CLASS_DECL_APEX ::apex::session * get_session();
//CLASS_DECL_APEX ::apex::session * get_session(::particle * pparticle);
//CLASS_DECL_APEX inline ::apex::session * get_session(::apex::session * psession);


//CLASS_DECL_APEX ::apex::system * ::apex::get_system(::particle * pparticle);


#define BAD_WCHAR ((::wide_character)(-1))


#define ARRAY_COUNT_OF(a) (sizeof(a)/sizeof(*(a)))


class payload;
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

#endif

class type;


//#include "apex/platform/definition.h"


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



typedef void THREAD_ROUTINE(thread_parameter parameter);

class sticker;

template < typename POINTER_TYPE >
class ptr_array;

using object_ptra = pointer_array < ::matter >; // Please use just for keeping non-member-based references.

///using object_addra = __address_array(::matter); // Please use just for keeping non-member-based references.

class object_meta;


//#define __composite_array(TYPE) ::array < ::pointer<TYPE >>
//#define __reference_array(TYPE) ::array < ::pointer<TYPE >>

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

   using graphics_pointer = ::pointer<graphics>;
      using pen_pointer = ::pointer<pen>;


} // namespace draw2d


using generic_pointer = ::pointer<::matter>;


namespace core
{


   class user;


} // namespace core


//#include "apex/primitive/primitive/object.h"

//#include "apex/handler/_.h"

//#include "apex/primitive/primitive/object.h"

//#include "acme/primitive/primitive/object_meta.h"

//#include "app/acme/platform/trace.h"

#include "apex/platform/display.h"


//#include "apex/platform/library_object_allocator.h"


//#include "apex/platform/library.h"


#include "apex/filesystem/filesystem.h"


//#include "apex/progress/_.h"


#include "apex/parallelization/_.h"


#if defined(LINUX)

//#include "apex/operating_system/ansi/_.h"

#elif defined(UNIVERSAL_WINDOWS)
//
//#include "apex/os/UNIVERSAL_WINDOWS/UNIVERSAL_WINDOWS.h"
//#include "apex/os/UNIVERSAL_WINDOWS/_UWP_user_impl.h"
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




//#include "apex/message/_message.h"


//#include "apex/message/message.h"


//#include "apex/platform/thread_set.h"


//#include "apex/platform/simple_log.h"


//#include "apex/platform/department.h"


//#include "apex/parallelization/threading.h"


class message_queue;


namespace windowing
{


   class cursor;


} // namespace windowing


//#include "apex/user/check.h"
//#include "apex/user/text.h"
//#include "apex/user/primitive.h"


//s#include "apex/parallelization/thread.h"


class handler_manager;


class service;
class service_handler;

//#include "apex/parallelization/service.h"

//#include "apex/parallelization/handler_manager.h"
//#include "apex/parallelization/service_status.h"
//#include "apex/parallelization/service.h"
//#include "apex/parallelization/service_handler.h"
//#include "apex/parallelization/service/plain_service.h"
//#include "apex/parallelization/service/plain_service.h"
//#include "apex/parallelization/fork.h"
//#include "apex/parallelization/delay_thread.h"
//#include "apex/parallelization/tools.h"


//#include "apex/parallelization/thread_impl.h"


//#include "apex/platform/log.h"


namespace user
{


   class style;

   using style_pointer = ::pointer<style>;


} // namespace user


//#include "apex/user.h"

//#include "apex/platform/savings.h"

#include "apex/networking/_.h"

class launcher;
//#include "apex/platform/launcher.h"

//#include "apex/interprocess/channel.h"

//#include "apex/platform/app_launcher.h"


class zip_context;


namespace file
{

   class watcher;

} // namespace file


//#include "apex/filesystem/filesystem/file_system.h"

//#include "apex/filesystem/filesystem/dir_system.h"

//#include "apex/filesystem/filesystem/file_context.h"

//#include "apex/filesystem/filesystem/dir_context.h"

//#include "apex/filesystem/file/set.h"

//#include "apex/platform/net.h"

//#include "apex/platform/command_line.h"

//#include "acme/handler/request.h"


namespace zip
{


   class util;


} // namespace zip


//#include "apex/operating_system/text.h"

//#include "apex/operating_system/process.h"

//#include "apex/filesystem/file/listener.h"

//#include "apex/platform/os_context.h"

//#include "apex/crypto/crypto.h"

#include "apex/database/_.h"

#include "apex/user/_.h"


//#include "apex/platform/application_menu.h"
//#include "apex/platform/application_array.h"
//#include "apex/platform/application_exit.h"
//#include "apex/platform/app_container.h"


//class ::interprocess::task;

//class interprocess_intercommunication;

//using interprocess_task_map = atom_map < ::pointer<::interprocess::task >>;


//#include "apex/platform/::interprocess::call.h"

//#include "apex/platform/::interprocess::task.h"

//#include "apex/platform/inteprocess_channel.h"

//#include "apex/platform/interprocess_intercommunication.h"

//#include "apex/platform/hyperlink.h"

//#include "apex/platform/context.h"


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


#include "apex/filesystem/fs/_.h"

//#include "apex/_.h"

//#include "apex/user/text.h"

//#include "apex/user/check.h"

//#include "apex/user/menu_shared_command.h"

//#include "apex/message/command.h"

#include "apex/message/_.h"

#include "apex/progress/_.h"
//#include "apex/platform/context_thread.h"


#include "apex/platform/_.h"

//#include "apex/platform/application.h"

//#include "apex/user/_const_key.h"

//#include "apex/platform/session.h"

//#include "apex/parallelization/retry.h"


//CLASS_DECL_APEX::file::path application_installer_folder(const ::file::path & pathExe, string strAppId, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);
//CLASS_DECL_APEX bool is_application_installed(const ::file::path & pathExe, string strAppId, string & strBuild, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);
//CLASS_DECL_APEX bool set_application_installed(const ::file::path & pathExe, string strAppId, const ::scoped_string & scopedstrBuild, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);
//CLASS_DECL_APEX::file::path get_application_path(string strAppId, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration);
//CLASS_DECL_APEX::file::path get_last_run_application_path_file(string strAppId);
//CLASS_DECL_APEX::file::path get_last_run_application_path(string strAppId);
//CLASS_DECL_APEX bool set_last_run_application_path(string strAppId);


//CLASS_DECL_APEX void load_factory_library(string strLibrary);


class node_data_exchange;


namespace xml
{


   class xml;


} // namespace xml


//#include "apex/platform/app_core.h"


//#include "apex/process/_.h"


//#include "apex/primitive/math/department.h"


//#include "apex/user/menu_shared.h"


//#include "apex/platform/node.h"


//#include "apex/platform/system.h"


//#define memory_new ACME_NEW


//#include "apex/os/chronometer.h"


//#include "apex/platform/assert_running_task.h"


//#include "apex/platform/debug.h"


// C++ Includes
//#include "apex/os/_.h"
//#include "apex/operating_system/_.h"


//#include "apex/parallelization/data.h"


//#include "apex/platform/shell_launcher.h"


//#include "apex/platform/async.h"


//#include "apex/platform/international.h"


#define return_(y, x) {y = x; return;}


//#include "apex/platform/simple_app.h"


namespace mathematics
{

   template < typename T >
   class complex;


} // namespace mathematics



#include "apex/compress/_.h"


//#include "apex/platform/app_consumer.h"


//#include "apex/platform/async.h"


//#include "apex/constant/idpool.h"


#include "apex/user/_.h"


#include "apex/parallelization/_impl.h"


#include "apex/platform/_impl.h"


#ifndef WINDOWS_DESKTOP


//#include "apex/operating_system/cross/windows/windows_thread_impl.h"


#endif



#include "apex/filesystem/_impl.h"


#include "apex/filesystem/file/_.h"


#include "apex/filesystem/filesystem/_impl.h"


#include "apex/database/_impl.h"




