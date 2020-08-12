#pragma once


#include "cross.h"



#if defined(LINUX)

#include "ansios/ansios.h"
#include "linux/linux.h"

#elif defined(_UWP)

#include "uwp/_UWP.h"
//#include "uwp/_UWP_user_impl.h"

#elif defined(MACOS)

#include "ansios/ansios.h"
#include "macos/macos.h"
//#include "macos/macos_windowing.h"

#elif defined(ANDROID)

#include "ansios/ansios.h"
#include "android/android.h"

#elif defined(WINDOWS)

#include "windows/_.h"

#elif defined(APPLE_IOS)

#include "ansios/ansios.h"
#include "ios/ios.h"

#elif defined(SOLARIS)

#include "ansios/ansios.h"
#include "solaris/solaris_user_impl.h"

#else


#error "not implemented!!"

#endif





