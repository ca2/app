//  Created by Camilo Sasuke Tsumanuma on 05/01/18.
#pragma once

//CLASS_DECL_AURA string get_command_line();


#if defined(MACOS)

#include "aura/os/ansios/_.h"
#include "aura/os/apple/_.h"
#include "aura/os/macos/_.h"

#elif defined(APPLE_IOS)

#include "aura/os/ansios/_.h"
#include "aura/os/apple/_.h"
#include "aura/os/ios/_.h"

#elif defined(LINUX)

#include "aura/os/cairo/_.h"
#include "aura/os/ansios/_.h"
#include "aura/os/linux/_.h"

#elif defined(_UWP)

#include "aura/os/ansios/_.h"
#include "aura/os/windows_common/_.h"
#include "aura/os/uwp/_.h"

#elif defined(WINDOWS_DESKTOP)

#include "aura/os/ansios/_.h"
#include "aura/os/windows_common/_.h"
#include "aura/os/windows/_.h"

#elif defined(ANDROID)

#include "aura/os/ansios/_.h"
#include "aura/os/android/_.h"

#elif defined(SOLARIS)

#include "aura/os/ansios/_.h"
#include "aura/os/solaris/_.h"

#else

#error "The operating system wasn't expected."

#endif


//CLASS_DECL_AURA iptr get_window_long_ptr(oswindow oswindow, int iIndex);
//CLASS_DECL_AURA iptr set_window_long_ptr(oswindow oswindow, int iIndex, iptr i);



//template < typename PRED >
//inline bool pred_Sleep(int iTime, PRED pred);

//CLASS_DECL_AURA void press_any_key_to_exit(const char* psz = nullptr);

//void adapt_font_name(string & str);

//
//namespace str
//{
//
//   string CLASS_DECL_AURA get_window_text_timeout(oswindow oswindow, millis tickTimeout = 1000);
//
//} // namespace str
//

//CLASS_DECL_AURA void defer_dock_application(int_bool bDock);


//CLASS_DECL_AURA string get_current_login_name();


//#if defined(WINDOWS)
//
//
//CLASS_DECL_AURA _locale_t get_c_locale();
//
//
//#else
//
//
//CLASS_DECL_AURA locale_t get_c_locale();
//
//#endif



