#pragma once





#ifdef WINDOWS_DESKTOP

#include "windows_common/_.h"
#include "windows/_.h"

#elif defined(UNIVERSAL_WINDOWS)

#include "windows_common/_.h"
#include "universal_windows/_.h"

#elif defined(MACOS)


#include "posix/_.h"
#include "apple/_.h"
#include "macos/_.h"


#elif defined(APPLE_IOS)


#include "posix/_.h"
#include "apple/_.h"
#include "ios/_.h"


#elif defined(LINUX)


#include "posix/_.h"
#include "linux/_.h"


#elif defined(ANDROID)


#include "posix/_.h"
#include "android/_.h"

//#include "posix/file_os_watcher.h"

#endif


CLASS_DECL_ACME void flush_stdin();


namespace operating_system
{


   class summary;


} // namespace operating_system



