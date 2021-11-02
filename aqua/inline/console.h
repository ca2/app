#include "console_common.h"
#include "aqua/platform/layer.h"


static ::aqua::layer g_layer;


//#ifdef LINUX
//
//#include "apex/inline/console/linux.h"
//
//#elif defined(_UWP)
//
//#include "apex/inline/console/universal_windows.h"
//
//#elif defined(WINDOWS)
//
//#include "apex/inline/console/windows.h"
//
//#elif defined(MACOS)
//
//#include "apex/inline/console/macos.h"
//
//#elif defined(ANDROID)
//
//#include "apex/inline/console/android.h"
//
//#else
//
//#include "apex/inline/console/---->platform_name<---- not implemented"
//
//#endif


#if !defined(CUBE)


#include "_new_impl.h"


#if defined(WINDOWS)


#include "acme/asset/new.cpp"


#endif


#endif




#include "aura/_defer.h"



