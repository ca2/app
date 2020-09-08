#pragma once


#ifndef __cplusplus

//#include <assert.h>

#define ASSERT assert

#endif



#include "acme/primitive/math/mkint_c.h"

//#if defined(ANDROID)
//#include "acme/acme/os/android/android.h"
//#elif defined(MACOS)
//#include "acme/acme/os/macos/macos.h"
//#elif defined(LINUX)
//#include "acme/acme/os/linux/linux.h"
//#elif defined(_UWP)
//#include "acme/acme/os/_UWP/_UWP.h"
//#elif defined(WINDOWS)
//#include "acme/acme/os/windows/windows.h"
//#elif defined(SOLARIS)
//#include "acme/acme/os/solaris/solaris.h"
//#elif defined(APPLE_IOS)
//#include "acme/acme/os/ios/ios.h"
//#else
//#error Not Supported Operational System
//#endif


//#include "acme/net/idn/idna.h"



CLASS_DECL_ACME int get_axis_init();
extern "C"
CLASS_DECL_ACME int_bool defer_axis_init();
extern "C"
CLASS_DECL_ACME int_bool defer_axis_term();






