#pragma once


#ifdef AURA_LANGUAGE


#ifdef cplusplus



#include "_.h"


#else





#include "_c.h"





#endif


#else


#if defined(__M)


//#include "_c.h"
#include "policy_objc.h"


#elif defined(__MM)


#include "base_c.h"
#include "base_policy_objc.h"
#include "base_policy_objcpp.h"


#elif defined(__cplusplus_winrt)


//#include "base_c.h"
#include "_.h"
#include "policy_winrt.h"


#else


#error "This is a not supported, hope, yet, non converging babylon language."


#endif


#endif
