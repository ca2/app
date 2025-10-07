#pragma once


#if defined(__OBJECTIVE_CPP__)


#include "berg/include/_c_bridge.h"
#include "berg/include/objc.h"
#include "berg/include/objcpp.h"


#elif defined(__cplusplus)


#include "berg/include/_.h"


#elif defined(__OBJECTIVE_C__)


#include "berg/include/_c.h"
#include "berg/include/objc.h"


#elif defined(__cplusplus_winrt)


//#include "_c.h"
#include "berg/include/_.h"
#include "berg/include/winrt.h"


#else


#include "berg/include/_c_bridge.h"


#endif



