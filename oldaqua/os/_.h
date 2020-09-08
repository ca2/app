//  Created by Camilo Sasuke Tsumanuma on 05/01/18.
#pragma once

CLASS_DECL_AQUA string get_command_line_dup();

#if defined(MACOS)

#include "aqua/os/ansios/_.h"
#include "aqua/os/apple/_.h"
#include "aqua/os/macos/_.h"

#elif defined(APPLE_IOS)

#include "aqua/os/ansios/_.h"
#include "aqua/os/apple/_.h"
#include "aqua/os/ios/_.h"

#elif defined(LINUX)

#include "aqua/os/cairo/_.h"
#include "aqua/os/ansios/_.h"
#include "aqua/os/linux/_.h"

#elif defined(_UWP)

#include "aqua/os/ansios/_.h"
#include "aqua/os/windows_common/_.h"
#include "aqua/os/uwp/_.h"

#elif defined(WINDOWS_DESKTOP)

#include "aqua/os/ansios/_.h"
#include "aqua/os/windows_common/_.h"
#include "aqua/os/windows/_.h"

#elif defined(ANDROID)

#include "aqua/os/ansios/_.h"
#include "aqua/os/android/_.h"

#elif defined(SOLARIS)

#include "aqua/os/ansios/_.h"
#include "aqua/os/solaris/_.h"

#else

#error "The operating system wasn't expected."

#endif

template < typename PRED >
inline bool pred_Sleep(int iTime, PRED pred);


//void adapt_font_name(string & str);


namespace str
{

   string CLASS_DECL_AQUA get_window_text_timeout(oswindow oswindow, tick tickTimeout = 1000);

} // namespace str


CLASS_DECL_AQUA void defer_dock_application(int_bool bDock);


CLASS_DECL_AQUA string get_current_login_name();


#if defined(WINDOWS)


CLASS_DECL_AQUA _locale_t get_c_locale();


#else


CLASS_DECL_AQUA locale_t get_c_locale();

#endif



