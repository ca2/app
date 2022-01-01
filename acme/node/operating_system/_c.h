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

#include "acme/node/operating_system/ansi/_c.h"
#include "acme/node/operating_system/apple/_c.h"
#include "acme/node/operating_system/macos/_c.h"

#elif defined(APPLE_IOS)

#include "acme/node/operating_system/ansi/_c.h"
#include "acme/node/operating_system/apple/_c.h"
#include "acme/node/operating_system/ios/_c.h"

#elif defined(LINUX)

//#include "acme/node/operating_system/cairo/_c.h"
//#include "acme/node/operating_system/ansi/_c.h"
//#include "acme/node/operating_system/linux/_c.h"

#elif defined(FREEBSD)

//#include "acme/node/operating_system/cairo/_c.h"
//#include "acme/node/operating_system/ansi/_c.h"
//#include "acme/node/operating_system/linux/_c.h"

#elif defined(_UWP)

#include "acme/node/operating_system/ansi/_c.h"
#include "acme/node/operating_system/windows_common/_c.h"
#include "acme/node/operating_system/universal_windows/_c.h"

#elif defined(WINDOWS_DESKTOP)

#include "acme/node/operating_system/ansi/_c.h"
#include "acme/node/operating_system/windows_common/_c.h"
#include "acme/node/operating_system/windows/_c.h"

#elif defined(ANDROID)

#include "acme/node/operating_system/ansi/_c.h"
#include "acme/node/operating_system/android/_c.h"

#elif defined(SOLARIS)

#include "acme/node/operating_system/ansi/_c.h"
#include "acme/node/operating_system/solaris/_c.h"

#else

#error "The operating system wasn't expected."

#endif

//template < typename PRED >
//inline bool predicate_Sleep(int iTime, PRED pred);

CLASS_DECL_ACME void press_any_key_to_exit(const char* psz);

//void adapt_font_name(string & str);





//CLASS_DECL_ACME void defer_dock_application(int_bool bDock);



//CLASS_DECL_ACME string get_current_login_name();


#if defined(WINDOWS)


CLASS_DECL_ACME _locale_t get_c_locale();


#else


CLASS_DECL_ACME locale_t get_c_locale();

#endif


