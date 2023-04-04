#include "application_common.h"


#ifdef LINUX

#include "apex/inline/application/linux.h"

#elif defined(UNIVERSAL_WINDOWS)

#include "apex/inline/application/universal_windows.h"

#elif defined(WINDOWS)

#include "apex/inline/application/windows.h"

#elif defined(MACOS)

#include "apex/inline/application/macos.h"

#elif defined(ANDROID)

#include "apex/inline/application/android.h"

#elif defined(APPLE_IOS)

#include "apex/inline/application/ios.h"

#else

#error "apex/inline/application/---->platform_name<---- not implemented"

#endif


#if !defined(CUBE)


#include "_new_impl.h"


#include "acme/_library.h"


#endif


//#include "aura/_defer.h"



