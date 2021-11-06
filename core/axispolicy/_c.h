#pragma once


#ifndef __cplusplus

//#include <assert.h>

#define ASSERT assert

#endif



#include "aura/primitive/math/mkint_c.h"

//#if defined(ANDROID)
//#include "axis/axis/os/android/android.h"
//#elif defined(MACOS)
//#include "axis/axis/os/macos/macos.h"
//#elif defined(LINUX)
//#include "axis/axis/os/linux/linux.h"
//#elif defined(_UWP)
//#include "axis/axis/os/_UWP/_UWP.h"
//#elif defined(WINDOWS)
//#include "axis/axis/os/windows/windows.h"
//#elif defined(SOLARIS)
//#include "axis/axis/os/solaris/solaris.h"
//#elif defined(APPLE_IOS)
//#include "axis/axis/os/ios/ios.h"
//#else
//#error Not Supported Operational System
//#endif


//#include "axis/net/idn/idna.h"



CLASS_DECL_CORE int get_axis_init();
extern "C"
CLASS_DECL_CORE int_bool defer_axis_init();
extern "C"
CLASS_DECL_CORE int_bool defer_axis_term();






