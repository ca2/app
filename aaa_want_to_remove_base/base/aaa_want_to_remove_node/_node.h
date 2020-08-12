#pragma once


//void __node_base_factory_exchange();


#if defined(APPLE_IOS)

#include "ios/ios.h"

#elif defined(MACOS)

#include "macos/_.h"

#elif defined(WINDOWS_DESKTOP)

#include "windows/_windows.h"

#elif defined(_UWP)

#include "uwp/_uwp.h"

#endif

