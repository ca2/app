#ifndef __GNUC__
#pragma once
#endif


#include "acme/_start.h"


#ifdef __cplusplus

#ifdef __OBJC__

#include "aura/include/objcpp.h"

#else

#include "berg/_.h"
#include "berg/platform/_platform.h"
//#if BROAD_PRECOMPILED_HEADER
////#include "berg/user/user/_component.h"
//#include "berg/user/experience/_experience.h"
////#include "berg/user/simple/_component.h"
//#include "berg/user/menu/_menu.h"
//#endif

//#include "aura/_defer.h"

#endif

#else

#ifdef __OBJC__

#include "aura/include/objc.h"

#else

#include "aura/_.h"

#endif

#endif



