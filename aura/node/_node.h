#pragma once


#ifdef WINDOWS_DESKTOP

//#include "windows/_windows.h"

#elif defined(_UWP)

//#include "universal_windows/_uwp.h"

#elif defined(MACOS)

#include "macos/_macos.h"

#elif defined(APPLE_IOS)

#include "ios/_ios.h"

#elif defined(LINUX)

#include "posix/_posix.h"
#include "linux/_linux.h"

#elif defined(ANDROID)

#include "android/_android.h"

#endif


//CLASS_DECL_AURA void ([a-z0-9_]+)_factory(::factory::factory * pfactory);



