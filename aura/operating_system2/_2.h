//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 05/01/18.
#pragma once


#include "apex/operating_system/_.h"
#include "aura/operating_system/_c.h"


#if defined(MACOS)

#include "aura/operating_system/ansi/_.h"
#include "aura/operating_system/apple/_.h"
#include "aura/operating_system/macos/_.h"

#elif defined(APPLE_IOS)

#include "aura/os/ansios/_.h"
#include "aura/os/apple/_.h"
#include "aura/os/ios/_.h"

#elif defined(LINUX)

#include "aura/operating_system/cairo/_.h"
#include "aura/operating_system/ansi/_.h"
#include "aura/operating_system/linux/_.h"

#elif defined(FREEBSD)

#include "aura/operating_system/cairo/_.h"
#include "aura/operating_system/ansi/_.h"
#include "aura/operating_system/freebsd/_.h"

#elif defined(UNIVERSAL_WINDOWS)

#include "aura/operating_system/ansi/_.h"
#include "aura/operating_system/windows_common/_.h"
#include "aura/operating_system/universal_windows/_.h"

#elif defined(WINDOWS_DESKTOP)

#include "aura/operating_system/ansi/_.h"
#include "aura/operating_system/windows_common/_.h"
#include "aura/operating_system/windows/_.h"

#elif defined(ANDROID)

#include "aura/os/ansios/_.h"
#include "aura/os/android/_.h"

#elif defined(SOLARIS)

#include "aura/os/ansios/_.h"
#include "aura/os/solaris/_.h"

#else

#error "The operating system wasn't expected."

#endif


//CLASS_DECL_AURA iptr get_window_long_ptr(::windowing::window * pwindow, int iIndex);
//CLASS_DECL_AURA iptr set_window_long_ptr(::windowing::window * pwindow, int iIndex, iptr i);



//template < typename PRED >
//inline bool predicate_Sleep(int iTime, PRED pred);

//CLASS_DECL_AURA void press_any_key_to_exit(const ::string & psz = nullptr);

//void adapt_font_name(string & str);

//
//namespace str
//{
//
//   string CLASS_DECL_AURA get_window_text_timeout(::windowing::window * pwindow, class ::time tickTimeout = 1000);
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



