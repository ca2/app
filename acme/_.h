///<3TBS_!!
#pragma once


#include "acme/include/_include.h"


#define PLATFORM_LAYER_NAME platform


#if __OBJC__


#if __cplusplus


#include "acme/include/objcpp.h"


#else


#include "acme/include/objc.h"


#endif


#else


#include "acme/platform/system.h"


#endif





