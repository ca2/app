//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 05/01/18.
#pragma once




#ifndef WINDOWS


#ifndef HIBYTE
#define HIBYTE(x) (((x) >> 8) & 0x00ff)
#endif


#ifndef HIWORD
#define HIWORD(x) (((x) >> 16) & 0x0000ffff)
#endif


#ifndef LOWORD
#define LOWORD(x) ((x) & 0x0000ffff)
#endif


#ifndef MAKEWORD
#define MAKEWORD(lo, hi) (((lo) & 0xff) | (((hi) << 8) & 0xff00))
#endif


#define SWAPWORD(x)		MAKEWORD(HIBYTE(x), lower_u8(x))
#define SWAPLONG(x)		make_i32(SWAPWORD(HIWORD(x)), SWAPWORD(LOWORD(x)))


#endif


//CLASS_DECL_ACME string get_command_line();
CLASS_DECL_ACME bool is_verbose();


#if defined(MACOS)

#include "acme/operating_system/ansi/_.h"
#include "acme/operating_system/apple/_.h"
#include "acme/operating_system/macos/_.h"

#elif defined(APPLE_IOS)

#include "acme/operating_system/ansi/_.h"
#include "acme/operating_system/apple/_.h"
#include "acme/operating_system/ios/_.h"

#elif defined(LINUX)

//#include "acme/operating_system/cairo/_.h"
//#include "acme/operating_system/ansi/_.h"
//#include "acme/operating_system/linux/_.h"

#elif defined(FREEBSD)

//#include "acme/operating_system/cairo/_.h"
//#include "acme/operating_system/ansi/_.h"
//#include "acme/operating_system/linux/_.h"

#elif defined(UNIVERSAL_WINDOWS)

#include "acme/operating_system/ansi/_.h"
#include "acme/operating_system/windows_common/_.h"
#include "acme/operating_system/universal_windows/_.h"

#elif defined(WINDOWS_DESKTOP)

#include "acme/operating_system/ansi/_.h"
#include "acme/operating_system/windows_common/_.h"
#include "acme/operating_system/windows/_.h"

#elif defined(ANDROID)

#include "acme/operating_system/ansi/_.h"
#include "acme/operating_system/android/_.h"

#elif defined(SOLARIS)

#include "acme/operating_system/ansi/_.h"
#include "acme/operating_system/solaris/_.h"

#else

#error "The operating system wasn't expected."

#endif

template < typename PRED >
inline bool predicate_Sleep(int iTime, PRED pred);

CLASS_DECL_ACME void press_any_key_to_exit(const ::scoped_string & scopedstr = nullptr);

//void adapt_font_name(string & str);





//CLASS_DECL_ACME void defer_dock_application(int_bool bDock);



CLASS_DECL_ACME string get_current_login_name();


#if defined(WINDOWS)


CLASS_DECL_ACME _locale_t get_c_locale();


#else


CLASS_DECL_ACME locale_t get_c_locale();

#endif


#include "time.h"




#include "parallelization.h"


//#ifdef
//
//CLASS_DECL_ACME iptr get_window_long_ptr(::windowing::window * pwindow, int iIndex);
//CLASS_DECL_ACME iptr set_window_long_ptr(::windowing::window * pwindow, int iIndex, iptr i);


#include "user.h"


#include "file.h"


CLASS_DECL_ACME enum_dialog_result message_box_for_console(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrTitle, const ::enum_message_box& emessagebox);

//CLASS_DECL_ACME void is_directory(const ::file::path & path);

//CLASS_DECL_ACME void file_exists(const ::file::path & path);

//CLASS_DECL_ACME void create_directory_path(const ::file::path & path);

//CLASS_DECL_ACME void create_directory(const ::file::path & path);

//CLASS_DECL_ACME void file_delete(const ::file::path & path);


enum enum_command_system
{

   e_command_system_none = 0,
   e_command_system_inline_log = 1,

};


#include "acme/prototype/duration/_.h"


CLASS_DECL_ACME void command_system(string & strOutput, string & strError, int & iExitCode, const ::scoped_string & scopedstr, enum_command_system ecommandsystem = e_command_system_none, const ::duration & durationTimeout = ::duration::infinite());

CLASS_DECL_ACME ::atom message_box_synchronous(::particle * pparticle, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, enum_message_box emessagebox = e_message_box_ok);

#include "_c.h"



