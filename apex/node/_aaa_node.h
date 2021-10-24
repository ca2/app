#pragma once


#ifdef WINDOWS_DESKTOP

//#include "windows/_windows.h"

#elif defined(_UWP)

#include "universal_windows/_universal_windows.h"

#elif defined(MACOS)

//#include "macos/_macos.h"

#elif defined(APPLE_IOS)

#include "ios/_ios.h"

#elif defined(LINUX)

//#include "posix/_posix.h"
#include "linux/_linux.h"

#elif defined(ANDROID)

#include "android/_android.h"

#endif


CLASS_DECL_ACME void __node_apex_factory_exchange(::factory_map * pfactorymap);



