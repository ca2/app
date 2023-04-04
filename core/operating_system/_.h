#pragma once


#ifdef WINDOWS_DESKTOP

#include "windows/_.h"

#elif defined(UNIVERSAL_WINDOWS)

#include "universal_windows/_.h"

#elif defined(MACOS)

#include "macos/_.h"

#elif defined(APPLE_IOS)

#include "ios/_.h"

#elif defined(LINUX)

#include "linux/_.h"

#elif defined(ANDROID)

//#include "android/_.h"

//#include "apex/os/posix/file_os_watcher.h"

#endif






