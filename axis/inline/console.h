#include "console_common.h"


// Implement this function
//void main();


#ifdef LINUX

#include "console/linux.h"

#elif defined(UNIVERSAL_WINDOWS)

#include "console/universal_windows.h"

#elif defined(WINDOWS)

#include "console/windows.h"

#elif defined(MACOS)

#include "console/macos.h"

#elif defined(__ANDROID__)

#include "console/android.h"

#else

#error "console/---->platform_name<---- not implemented" 

#endif


#if !defined(CUBE)


#include "_new_impl.h"

#if defined(WINDOWS)


#include "acme/_library.h"


#endif


#endif





//#include "aura/_defer.h"



