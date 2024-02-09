#pragma once


#if defined(__OBJECTIVE_CPP__)


#include "_c_bridge.h"
#include "objc.h"
#include "objcpp.h"


#elif defined(__cplusplus)


#include "_.h"


#elif defined(__OBJECTIVE_C__)


#include "_c.h"
#include "objc.h"


#elif defined(__cplusplus_winrt)


#include "_.h"
#include "winrt.h"


#else


#include "_c_bridge.h"


#endif



