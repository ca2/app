//  Created by Camilo Sasuke Tsumanuma on 05/01/18.
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


#define SWAPWORD(x)		MAKEWORD(HIBYTE(x), __LOBYTE(x))
#define SWAPLONG(x)		__MAKE_LONG(SWAPWORD(HIWORD(x)), SWAPWORD(LOWORD(x)))


#endif


//CLASS_DECL_ACME string get_command_line();
CLASS_DECL_ACME bool is_verbose();


#if defined(MACOS)

#include "acme/node/operating_system/ansi/_.h"
#include "acme/node/operating_system/apple/_.h"
#include "acme/node/operating_system/macos/_.h"

#elif defined(APPLE_IOS)

#include "acme/node/operating_system/ansi/_.h"
#include "acme/node/operating_system/apple/_.h"
#include "acme/node/operating_system/ios/_.h"

#elif defined(LINUX)

//#include "acme/node/operating_system/cairo/_.h"
//#include "acme/node/operating_system/ansi/_.h"
//#include "acme/node/operating_system/linux/_.h"

#elif defined(FREEBSD)

//#include "acme/node/operating_system/cairo/_.h"
//#include "acme/node/operating_system/ansi/_.h"
//#include "acme/node/operating_system/linux/_.h"

#elif defined(_UWP)

#include "acme/node/operating_system/ansi/_.h"
#include "acme/node/operating_system/windows_common/_.h"
#include "acme/node/operating_system/universal_windows/_.h"

#elif defined(WINDOWS_DESKTOP)

#include "acme/node/operating_system/ansi/_.h"
#include "acme/node/operating_system/windows_common/_.h"
#include "acme/node/operating_system/windows/_.h"

#elif defined(ANDROID)

#include "acme/node/operating_system/ansi/_.h"
#include "acme/node/operating_system/android/_.h"

#elif defined(SOLARIS)

#include "acme/node/operating_system/ansi/_.h"
#include "acme/node/operating_system/solaris/_.h"

#else

#error "The operating system wasn't expected."

#endif

template < typename PRED >
inline bool predicate_Sleep(int iTime, PRED pred);

CLASS_DECL_ACME void press_any_key_to_exit(const char* psz = nullptr);

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


CLASS_DECL_ACME enum_dialog_result message_box_for_console(const char* psz, const char* pszTitle, const ::enum_message_box& emessagebox);

//CLASS_DECL_ACME ::e_status is_directory(const char * path);

//CLASS_DECL_ACME ::e_status file_exists(const char * path);

//CLASS_DECL_ACME ::e_status create_directory_path(const char * path);

//CLASS_DECL_ACME ::e_status create_directory(const char * path);

//CLASS_DECL_ACME ::e_status file_delete(const char * path);


enum enum_command_system
{

   e_command_system_none = 0,
   e_command_system_inline_log = 1,

};


#include "acme/primitive/duration/_.h"


CLASS_DECL_ACME ::e_status command_system(string & strOutput, string & strError, int & iExitCode, const char* psz, enum_command_system ecommandsystem = e_command_system_none, const ::duration & durationTimeout = ::duration::infinite());



#include "_c.h"



