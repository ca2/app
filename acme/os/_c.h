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


#include "acme/os/cross/_.h"


inline CLASS_DECL_ACME int c_is_null(const void * p) { return ((uptr)p) < 65536; }


#if defined(ANDROID)
#include "acme/os/ansios/_c.h"
#include "acme/os/android/_c.h"
#elif defined(MACOS)
#include "acme/os/ansios/_c.h"
#include "acme/os/macos/_c.h"
#elif defined(LINUX)
#include "acme/os/ansios/_c.h"
#include "acme/os/linux/_c.h"
#elif defined(_UWP)
#include "acme/os/windows_common/_c.h"
#include "acme/os/uwp/_.h"
#elif defined(WINDOWS_DESKTOP)
#include "acme/os/windows_common/_c.h"
#include "acme/os/windows/_c.h"
#elif defined(SOLARIS)
#include "acme/os/solaris/solaris.h"
#elif defined(APPLE_IOS)
#include "acme/os/ansios/_c.h"
#include "acme/os/ios/_c.h"
#else
#error Not Supported Operational System
#endif

