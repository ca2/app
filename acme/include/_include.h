#pragma once


#undef __spin_namespace


#ifdef cplusplus


#include "acme/include/_c.h"
#ifdef	_STDIO_H_
#error "already included?!?! WHAT?!?! (At acme:_c)"
#endif

#include "acme/include/_.h"
#ifdef	_STDIO_H_
#error "already included?!?! WHAT?!?! (At acme:_)"
#endif


#elif defined(__OBJECTIVE_CPP__)


#include "acme/include/_c.h"
#include "acme/include/_c_bridge.h"
#include "acme/include/objc.h"
#include "acme/include/objcpp.h"


#elif defined(__OBJECTIVE_C__)


#include "acme/include/_c.h"
#include "acme/include/objc.h"


#elif defined(__cplusplus_winrt)


//#include "_c.h"
#include "acme/include/_.h"
#include "acme/include/winrt.h"


#else


#include "acme/include/_c_bridge.h"


#endif



