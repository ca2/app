#include "application_common.h"
#include "__apps.inl"


#include "acme/platform/static_setup.h"


#include "_main_hold.h"


#ifdef LINUX


#include "application/linux.h"


#elif defined(FREEBSD)


#include "application/freebsd.h"


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


#include "acme/library.h"


#endif


#include "acme/_defer.h"



