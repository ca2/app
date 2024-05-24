#pragma once


#ifdef WINDOWS_DESKTOP

//#include "windows_common/_windows_common.h"
//#include "windows/_windows.h"

#elif defined(UNIVERSAL_WINDOWS)

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


//CLASS_DECL_ACID void ([a-z0-9_]+)_factory(::factory::factory * pfactory);



