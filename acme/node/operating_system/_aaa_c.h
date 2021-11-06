//
//  os.h
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 05/01/18.
//

// 

// CLASS_DECL_ACME int_bool os_is_alias(const char * psz);

// 


// C-includes
#pragma once


#include "acme/node/operating_system/cross/_.h"




#if defined(ANDROID)
#include "acme/node/operating_system/ansi/_c.h"
#include "acme/node/operating_system/android/_c.h"
#elif defined(MACOS)
#include "acme/node/operating_system/ansi/_c.h"
#include "acme/node/operating_system/macos/_c.h"
#elif defined(LINUX)
#include "acme/node/operating_system/ansi/_c.h"
#include "acme/node/operating_system/linux/_c.h"
#elif defined(_UWP)
#include "acme/node/operating_system/windows_common/_c.h"
#include "acme/node/operating_system/universal_windows/_.h"
#elif defined(WINDOWS_DESKTOP)
#include "acme/node/operating_system/windows_common/_c.h"
#include "acme/node/operating_system/windows/_c.h"
#elif defined(SOLARIS)
#include "acme/node/operating_system/solaris/solaris.h"
#elif defined(APPLE_IOS)
#include "acme/node/operating_system/ansi/_c.h"
#include "acme/node/operating_system/ios/_c.h"
#else
#error Not Supported Operational ::acme::get_system()
#endif

