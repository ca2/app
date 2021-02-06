//  Created by Camilo Sasuke Tsumanuma on 05/01/18.
#pragma once


#include "acme/os/_2.h"


//CLASS_DECL_APEX string get_command_line();

#if defined(MACOS)

#include "apex/os/ansios/_.h"
#include "apex/os/apple/_.h"
#include "apex/os/macos/_.h"

#elif defined(APPLE_IOS)

#include "apex/os/ansios/_.h"
#include "apex/os/apple/_.h"
#include "apex/os/ios/_.h"

#elif defined(LINUX)

//#include "apex/os/cairo/_.h"
#include "apex/os/ansios/_.h"
#include "apex/os/linux/_.h"

#elif defined(_UWP)

#include "apex/os/ansios/_.h"
#include "apex/os/windows_common/_.h"
#include "apex/os/uwp/_.h"

#elif defined(WINDOWS_DESKTOP)

#include "apex/os/ansios/_.h"
#include "apex/os/windows_common/_.h"
#include "apex/os/windows/_.h"

#elif defined(ANDROID)

#include "apex/os/ansios/_.h"
#include "apex/os/android/_.h"

#elif defined(SOLARIS)

#include "apex/os/ansios/_.h"
#include "apex/os/solaris/_.h"

#else

#error "The operating system wasn't expected."

#endif

template < typename PRED >
inline bool pred_Sleep(int iTime, PRED pred);


//void adapt_font_name(string & str);


//namespace str
//{
//
//   string CLASS_DECL_APEX get_window_text_timeout(::windowing::window * pwindow, millis tickTimeout = 1000);
//
//} // namespace str


CLASS_DECL_APEX void defer_dock_application(int_bool bDock);


//CLASS_DECL_APEX string get_current_login_name();


//#if defined(WINDOWS)
//
//
//CLASS_DECL_APEX _locale_t get_c_locale();
//
//
//#else
//
//
//CLASS_DECL_APEX locale_t get_c_locale();
//
//#endif



