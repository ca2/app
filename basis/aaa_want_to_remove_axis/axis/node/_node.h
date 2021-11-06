#pragma once


#ifdef WINDOWS_DESKTOP

#include "windows/windows.h"

#elif defined(APPLE_IOS)

#include "apple/apple.h"
#include "ios/ios.h"

#elif defined(MACOS)

#include "apple/apple.h"
#include "macos/macos.h"

#elif defined(ANDROID)

#include "android/android.h"

#endif

