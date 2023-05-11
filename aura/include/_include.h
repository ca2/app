#pragma once


#undef __spin_namespace


#if defined(__MM)


#include "acme/_.h"
//#include "aura/include/_c_bridge.h"
//#include "acme/include/objc.h"
//#include "acme/include/objcpp.h"



#elif defined(__cplusplus)


#include "aura/include/_.h"


#elif defined(__M)


#include "aura/include/_c.h"
#include "acme/include/objc.h"


#elif defined(__cplusplus_winrt)


//#include "_c.h"
#include "aura/include/_.h"
#include "aura/include/winrt.h"


#else


#include "aura/include/_c_bridge.h"


#endif



