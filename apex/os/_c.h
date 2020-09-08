//
//  os.h
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 05/01/18.
//

// 

// CLASS_DECL_APEX int_bool os_is_alias(const char * psz);

// 


// C-includes


#if defined(ANDROID)
#include "apex/os/ansios/_c.h"
#include "apex/os/android/_c.h"
#elif defined(MACOS)
#include "apex/os/ansios/_c.h"
#include "apex/os/macos/_c.h"
#elif defined(LINUX)
#include "apex/os/ansios/_c.h"
#include "apex/os/linux/_c.h"
#elif defined(_UWP)
#include "apex/os/windows_common/_c.h"
#include "apex/os/uwp/_.h"
#elif defined(WINDOWS_DESKTOP)
#include "apex/os/windows_common/_c.h"
#include "apex/os/windows/_c.h"
#elif defined(SOLARIS)
#include "apex/os/solaris/solaris.h"
#elif defined(APPLE_IOS)
#include "apex/os/ansios/_c.h"
#include "apex/os/ios/_c.h"
#else
#error Not Supported Operational System
#endif

