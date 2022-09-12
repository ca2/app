#pragma once


#if defined(__MM)


#include "_c_bridge.h"
#include "objc.h"
#include "objcpp.h"


#elif defined(__cplusplus)


#include "_.h"


#elif defined(__M)


#include "_c.h"
#include "objc.h"


#elif defined(__cplusplus_winrt)


#include "_.h"
#include "winrt.h"


#else


#include "_c_bridge.h"


#endif



