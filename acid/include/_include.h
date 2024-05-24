#pragma once


#undef __spin_namespace


#ifdef cplusplus

#include "acid/_.h"

#include "acid/include/_.h"
#ifdef	_STDIO_H_
#error "already included?!?! WHAT?!?! (At acid:_)"
#endif


#elif defined(__OBJECTIVE_CPP__)


#include "acid/include/_c.h"
#if defined(_STDIO_H_)
#error "already included?!?! WHAT?!?! (After including <acid/include/_c.h>)"
#endif

#include "acid/include/_c_bridge.h"
#if defined(_STDIO_H_)
#error "already included?!?! WHAT?!?! (After including <acid/include/_c_bridge.h>)"
#endif

#include "acid/include/objc.h"
#if defined(_STDIO_H_)
#error "already included?!?! WHAT?!?! (After including <acid/include/objc.h>)"
#endif


#include "acid/include/objcpp.h"
#if defined(_STDIO_H_)
#error "already included?!?! WHAT?!?! (After including <acid/include/objcpp.h>)"
#endif



#elif defined(__OBJECTIVE_C__)


#include "acid/include/_c.h"
#include "acid/include/objc.h"


#elif defined(__cplusplus_winrt)


//#include "_c.h"
#include "acid/include/_.h"
#include "acid/include/winrt.h"


#else


#include "acid/include/_c_bridge.h"


#endif



