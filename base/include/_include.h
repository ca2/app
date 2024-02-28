#pragma once


#if defined(__OBJECTIVE_CPP__)


#include "base/include/_c_bridge.h"
#include "base/include/objc.h"
#include "base/include/objcpp.h"


#elif defined(__cplusplus)


#include "base/include/_.h"


#elif defined(__OBJECTIVE_C__)


#include "base/include/_c.h"
#include "base/include/objc.h"


#elif defined(__cplusplus_winrt)


//#include "_c.h"
#include "base/include/_.h"
#include "base/include/winrt.h"


#else


#include "base/include/_c_bridge.h"


#endif



