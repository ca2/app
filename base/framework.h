#ifndef __GNUC__
#pragma once
#endif


#include "acme/_start.h"


#ifdef __cplusplus

#ifdef __OBJC__

#include "aura/include/objcpp.h"

#else

#include "base/_.h"
#include "base/platform/_platform.h"
#if !defined(BROAD_PRECOMPILED_HEADER)
#define BROAD_PRECOMPILED_HEADER 1
#endif
//#if BROAD_PRECOMPILED_HEADER
//#include "base/user/user/_user.h"
//#include "base/user/experience/_experience.h"
//#include "base/user/simple/_simple.h"
//#include "base/user/menu/_menu.h"
//#endif

#include "aura/_defer.h"

#endif

#else

#ifdef __OBJC__

#include "aura/include/objc.h"

#else

#include "aura/_.h"

#endif

#endif



