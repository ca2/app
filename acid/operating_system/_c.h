//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 05/01/18.
#pragma once



//CLASS_DECL_ACID string get_command_line();
//CLASS_DECL_ACID bool is_verbose();


#if defined(MACOS)

#include "acid/operating_system/ansi/_c.h"
#include "acid/operating_system/apple/_c.h"
#include "acid/operating_system/macos/_c.h"

#elif defined(APPLE_IOS)

#include "acid/operating_system/ansi/_c.h"
#include "acid/operating_system/apple/_c.h"
#include "acid/operating_system/ios/_c.h"

#elif defined(LINUX)

//#include "acid/operating_system/cairo/_c.h"
//#include "acid/operating_system/ansi/_c.h"
//#include "acid/operating_system/linux/_c.h"

#elif defined(FREEBSD)

//#include "acid/operating_system/cairo/_c.h"
//#include "acid/operating_system/ansi/_c.h"
//#include "acid/operating_system/linux/_c.h"

#elif defined(OPENBSD)

//#include "acid/operating_system/cairo/_c.h"
//#include "acid/operating_system/ansi/_c.h"
//#include "acid/operating_system/linux/_c.h"

#elif defined(UNIVERSAL_WINDOWS)

#include "acid/operating_system/ansi/_c.h"
#include "acid/operating_system/windows_common/_c.h"
#include "acid/operating_system/universal_windows/_c.h"

#elif defined(WINDOWS_DESKTOP)

#include "acid/operating_system/ansi/_c.h"
#include "acid/operating_system/windows_common/_c.h"
#include "acid/operating_system/windows/_c.h"

#elif defined(ANDROID)

#include "acid/operating_system/ansi/_c.h"
#include "acid/operating_system/android/_c.h"

#elif defined(SOLARIS)

#include "acid/operating_system/ansi/_c.h"
#include "acid/operating_system/solaris/_c.h"

#else

#error "The operating system wasn't expected."

#endif

//template < typename PRED >
//inline bool predicate_Sleep(int iTime, PRED pred);

//CLASS_DECL_ACID void press_any_key_to_exit(const ::scoped_string & scopedstr);

//void adapt_font_name(string & str);





//CLASS_DECL_ACID void defer_dock_application(int_bool bDock);



//CLASS_DECL_ACID string get_current_login_name();


#if defined(WINDOWS)


CLASS_DECL_ACID _locale_t get_c_locale();


#else


CLASS_DECL_ACID locale_t get_c_locale();

#endif


