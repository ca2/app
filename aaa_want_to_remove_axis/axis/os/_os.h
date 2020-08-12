#pragma once


#include "cross/cross.h"


#if defined(LINUX)


#include "ansios/ansios.h"
#include "linux/linux.h"


#elif defined(ANDROID)


#include "ansios/ansios.h"
#include "android/android.h"


#elif defined(MACOS)


#include "ansios/ansios.h"
#include "macos/macos.h"

#elif defined(_UWP)
#include "uwp/_UWP.h"
#elif defined(WINDOWS)
#include "windows/windows.h"
#elif defined(SOLARIS)
#include "solaris/solaris.h"
#elif defined(APPLE_IOS)
#include "ios/ios.h"
#else
#error Not Supported Operational System
#endif




