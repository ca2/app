//
//  os.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 05/01/18.
//

// 

// CLASS_DECL_ACME int_bool os_is_alias(const char * psz);

// 


// C-includes
#pragma once


#include "acme/operating_system/cross/_.h"




#if defined(ANDROID)
#include "acme/operating_system/ansi/_c.h"
#include "acme/operating_system/android/_c.h"
#elif defined(MACOS)
#include "acme/operating_system/ansi/_c.h"
#include "acme/operating_system/macos/_c.h"
#elif defined(LINUX)
#include "acme/operating_system/ansi/_c.h"
#include "acme/operating_system/linux/_c.h"
#elif defined(_UWP)
#include "acme/operating_system/windows_common/_c.h"
#include "acme/operating_system/universal_windows/_.h"
#elif defined(WINDOWS_DESKTOP)
#include "acme/operating_system/windows_common/_c.h"
#include "acme/operating_system/windows/_c.h"
#elif defined(SOLARIS)
#include "acme/operating_system/solaris/solaris.h"
#elif defined(APPLE_IOS)
#include "acme/operating_system/ansi/_c.h"
#include "acme/operating_system/ios/_c.h"
#else
#error Not Supported Operational ::acme::get_system()
#endif

