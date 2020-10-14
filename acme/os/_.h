//  Created by Camilo Sasuke Tsumanuma on 05/01/18.
#pragma once

//CLASS_DECL_ACME string get_command_line();
CLASS_DECL_ACME bool is_verbose();


#if defined(MACOS)

#include "acme/os/ansios/_.h"
#include "acme/os/apple/_.h"
#include "acme/os/macos/_.h"

#elif defined(APPLE_IOS)

#include "acme/os/ansios/_.h"
#include "acme/os/apple/_.h"
#include "acme/os/ios/_.h"

#elif defined(LINUX)

//#include "acme/os/cairo/_.h"
#include "acme/os/ansios/_.h"
#include "acme/os/linux/_.h"

#elif defined(_UWP)

#include "acme/os/ansios/_.h"
#include "acme/os/windows_common/_.h"
#include "acme/os/uwp/_.h"

#elif defined(WINDOWS_DESKTOP)

#include "acme/os/ansios/_.h"
#include "acme/os/windows_common/_.h"
#include "acme/os/windows/_.h"

#elif defined(ANDROID)

#include "acme/os/ansios/_.h"
#include "acme/os/android/_.h"

#elif defined(SOLARIS)

#include "acme/os/ansios/_.h"
#include "acme/os/solaris/_.h"

#else

#error "The operating system wasn't expected."

#endif

template < typename PRED >
inline bool pred_Sleep(int iTime, PRED pred);

CLASS_DECL_ACME void press_any_key_to_exit(const char* psz = nullptr);

//void adapt_font_name(string & str);


namespace str
{

   string CLASS_DECL_ACME get_window_text_timeout(oswindow oswindow, tick tickTimeout = 1000);

} // namespace str


//CLASS_DECL_ACME void defer_dock_application(int_bool bDock);


CLASS_DECL_ACME string executable_get_app_id(HINSTANCE hinstance);


CLASS_DECL_ACME string executable_get_app_id();


CLASS_DECL_ACME string get_current_login_name();


#if defined(WINDOWS)


CLASS_DECL_ACME _locale_t get_c_locale();


#else


CLASS_DECL_ACME locale_t get_c_locale();

#endif


#include "time.h"


#include "thread.h"


//#ifdef
//
//CLASS_DECL_ACME iptr get_window_long_ptr(oswindow oswindow, int iIndex);
//CLASS_DECL_ACME iptr set_window_long_ptr(oswindow oswindow, int iIndex, iptr i);


#include "user.h"


#include "file.h"


CLASS_DECL_ACME void output_debug_string(const char * psz);
CLASS_DECL_ACME void output_debug_string(const wchar_t * psz);


int process_get_status();

void process_set_status(int iStatus);

void process_set_args(int argc, TCHAR ** argv);

int * process_get_pargc();

TCHAR *** process_get_pargv();

int process_get_argc();

TCHAR ** process_get_argv();


struct update_notification_task;
update_notification_task * os_dark_mode_change();

void os_register_dark_mode_change(::element * pelement, bool * pbChanged);
void os_unregister_dark_mode_change(::element * pelement);

void os_destroy_dark_mode_change();



