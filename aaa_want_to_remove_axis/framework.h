#ifndef __GNUC__
#pragma once
#endif


#ifdef __cplusplus

#ifdef __OBJC__

#include "axis/policy/policy_objcpp.h"

#else

#include "axis/axis/axis/_.h"

#include "_defer.h"

#endif

#else

#ifdef __OBJC__

#include "axis/policy/policy_objc.h"

#else

#include "axis/axis/axis/_.h"

#endif

#endif



