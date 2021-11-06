#include "application_common.h"


#ifdef LINUX

#include "application/linux.h"

#elif defined(_UWP)

#include "application/universal_windows.h"

#elif defined(WINDOWS)

#include "application/windows.h"

#elif defined(MACOS)

#include "application/macos.h"

#elif defined(ANDROID)

#include "application/android.h"

#elif defined(APPLE_IOS)

#include "application/ios.h"

#else

#error "application/---->platform_name<---- not implemented"

#endif


#if !defined(CUBE)


#include "_new_impl.h"


#include "apex/library.h"


#endif


#include "apex/_defer.h"



