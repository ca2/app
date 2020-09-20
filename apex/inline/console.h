#include "console_common.h"


#ifdef LINUX

#include "console/linux.h"

#elif defined(_UWP)

#include "console/uwp.h"

#elif defined(WINDOWS)

#include "console/windows.h"

#elif defined(MACOS)

#include "console/macos.h"

#elif defined(ANDROID)

#include "console/android.h"

#else

#error "console/---->platform_name<---- not implemented"

#endif


#if !defined(CUBE)


#include "_new_impl.h"


#if defined(WINDOWS)


#include "apex/library.h"


#endif


#endif


#include "apex/_defer.h"



