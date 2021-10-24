#pragma once


#ifdef WINDOWS_DESKTOP

//#include "windows_common/_windows_common.h"
//#include "windows/_windows.h"

#elif defined(_UWP)

#include "universal_windows/_uwp.h"

#elif defined(MACOS)

//aaa_#include "macos/_macos.h"

#elif defined(APPLE_IOS)

#include "ios/_ios.h"

#elif defined(LINUX)

#include "posix/_posix.h"
#include "linux/_linux.h"

#elif defined(ANDROID)

#include "android/_android.h"

#endif


//CLASS_DECL_ACME void __node_aura_factory_exchange(::factory_map * pfactorymap);



