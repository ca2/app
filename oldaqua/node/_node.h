#pragma once


#ifdef WINDOWS_DESKTOP

#include "windows/_windows.h"

#elif defined(_UWP)

#include "uwp/_uwp.h"

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


CLASS_DECL_AQUA void __node_aura_factory_exchange();



