#pragma once


#undef __spin_namespace


#ifdef __cplusplus


#include "aura/include/_.h"


#elif defined(__MM)


#include "aura/include/_c_bridge.h"
#include "aura/include/objc.h"
#include "aura/include/objcpp.h"


#elif defined(__M)


#include "aura/include/_c.h"
#include "aura/include/objc.h"


#elif defined(__cplusplus_winrt)


//#include "_c.h"
#include "aura/include/_.h"
#include "aura/include/winrt.h"


#else


#include "aura/include/_c_bridge.h"


#endif



