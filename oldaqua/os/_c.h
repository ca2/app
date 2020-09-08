//
//  os.h
//  aqua
//
//  Created by Camilo Sasuke Tsumanuma on 05/01/18.
//

// 

// CLASS_DECL_AQUA int_bool os_is_alias(const char * psz);

// 


// C-includes


#if defined(ANDROID)
#include "aqua/os/ansios/_c.h"
#include "aqua/os/android/_c.h"
#elif defined(MACOS)
#include "aqua/os/ansios/_c.h"
#include "aqua/os/macos/_c.h"
#elif defined(LINUX)
#include "aqua/os/ansios/_c.h"
#include "aqua/os/linux/_c.h"
#elif defined(_UWP)
#include "aqua/os/windows_common/_c.h"
#include "aqua/os/uwp/_.h"
#elif defined(WINDOWS_DESKTOP)
#include "aqua/os/windows_common/_c.h"
#include "aqua/os/windows/_c.h"
#elif defined(SOLARIS)
#include "aqua/os/solaris/solaris.h"
#elif defined(APPLE_IOS)
#include "aqua/os/ansios/_c.h"
#include "aqua/os/ios/_c.h"
#else
#error Not Supported Operational System
#endif

