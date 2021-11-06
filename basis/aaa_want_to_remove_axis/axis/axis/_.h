#pragma once


#include "aura/_.h"



#ifdef _AXIS_STATIC
   #define CLASS_DECL_AXIS
#elif defined(_AXIS_LIBRARY)
   #define CLASS_DECL_AXIS  CLASS_DECL_EXPORT
   #define LIBIDN_BUILDING
#else
   #define CLASS_DECL_AXIS  CLASS_DECL_IMPORT
#endif











#include "axis/axis/os/_.h"

//#include "axis_number.h"


#ifdef AURA_LANGUAGE


#ifdef cplusplus


#include "axis/policy/_c.h"
#include "axis/policy/_.h"


#else





#include "_c.h"





#endif


#else


#if defined(__M)


#include "axis/policy/_c.h"
#include "axis/policy/policy_objc.h"


#elif defined(__MM)


#include "axis/policy/_c.h"
#include "axis/policy/policy_objc.h"
#include "axis/policy/policy_objcpp.h"


#elif defined(__cplusplus_winrt)


#include "axis/policy/_c.h"
#include "axis/policy/_.h"
#include "axis/policy/policy_winrt.h"


#else


#error "This is a not supported, hope, yet, non converging babylon language."


#endif


#endif




#define new ACME_NEW


