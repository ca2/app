//
//  os.h
//  acid
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 05/01/18.
//

// 

// CLASS_DECL_ACID int_bool os_is_alias(const ::scoped_string & scopedstr);

// 


// C-includes
#pragma once


//#include "acid/operating_system/cross/_2.h"



#if defined(ANDROID)
#include "acid/operating_system/ansi/_c.h"
#include "acid/operating_system/android/_c.h"
#elif defined(MACOS)
#include "acid/operating_system/ansi/_c.h"
#include "acid/operating_system/macos/_c.h"
#elif defined(LINUX)
#include "acid/operating_system/ansi/_c.h"
#include "acid/operating_system/linux/_c.h"
#elif defined(UNIVERSAL_WINDOWS)
#include "acid/operating_system/windows_common/_c.h"
#include "acid/operating_system/universal_windows/_.h"
#include "universal_windows.h"
#include "windows_common.h"
#elif defined(WINDOWS_DESKTOP)
#include "acid/operating_system/windows/_windows.h"
#include "acid/operating_system/windows_common/_windows_common.h"
#elif defined(SOLARIS)
#include "acid/operating_system/solaris/solaris.h"
#elif defined(APPLE_IOS)
#include "acid/operating_system/ansi/_c.h"
#include "acid/operating_system/ios/_c.h"
#else
#error Not Supported Operational system()
#endif

