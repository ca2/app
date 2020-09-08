#pragma once


#ifdef __cplusplus


#include "aqua/include/_.h"


#elif defined(__MM)


#include "aqua/include/_c_bridge.h"
#include "aqua/include/objc.h"
#include "aqua/include/objcpp.h"


#elif defined(__M)


#include "aqua/include/_c.h"
#include "aqua/include/objc.h"


#elif defined(__cplusplus_winrt)


//#include "_c.h"
#include "aqua/include/_.h"
#include "aqua/include/winrt.h"


#else


#include "aqua/include/_c_bridge.h"


#endif



