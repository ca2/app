#pragma once


#undef __spin_namespace


#if defined(__MM)


#include "apex/include/_c_bridge.h"
#include "acme/include/objc.h"
#include "acme/include/objcpp.h"


#elif defined(__cplusplus)


#include "apex/include/_.h"


#elif defined(__M)


#include "apex/include/_c.h"
#include "acme/include/objc.h"


#elif defined(__cplusplus_winrt)


//#include "_c.h"
#include "apex/include/_.h"
#include "apex/include/winrt.h"


#else


#include "apex/include/_c_bridge.h"


#endif



