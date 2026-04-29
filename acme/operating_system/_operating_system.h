#pragma once


#ifdef WINDOWS_DESKTOP

#include "windows_common/_windows_common.h"
#include "windows/_windows.h"

#elif defined(UNIVERSAL_WINDOWS)

#include "windows_common/_windows_common.h"
#include "universal_windows/_universal_windows.h"

#elif defined(MACOS)


#include "posix/_posix.h"
#include "apple/_apple.h"
#include "macos/_macos.h"


#elif defined(APPLE_IOS)


#include "posix/_posix.h"
#include "apple/_apple.h"
#include "ios/_ios.h"


#elif defined(LINUX)


#include "posix/_posix.h"
#include "linux/_linux.h"


#elif defined(FREEBSD)


#include "posix/_posix.h"
#include "freebsd/_freebsd.h"


#elif defined(OPENBSD)


#include "posix/_posix.h"
#include "openbsd/_openbsd.h"


#elif defined(__ANDROID__)


#include "posix/_posix.h"
#include "android/_android.h"

//#include "posix/file_os_watcher.h"

#endif



