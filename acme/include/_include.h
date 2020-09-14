#pragma once


#undef __spin_namespace


#ifdef __cplusplus


#include "acme/include/_.h"


#elif defined(__MM)


#include "acme/include/_c_bridge.h"
#include "acme/include/objc.h"
#include "acme/include/objcpp.h"


#elif defined(__M)


#include "acme/include/_c.h"
#include "acme/include/objc.h"


#elif defined(__cplusplus_winrt)


//#include "_c.h"
#include "acme/include/_.h"
#include "acme/include/winrt.h"


#else


#include "acme/include/_c_bridge.h"


#endif



