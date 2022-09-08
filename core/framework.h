#ifndef __GNUC__
#pragma once
#endif


#include "acme/_start.h"


#ifdef __cplusplus

#ifdef __OBJC__

#include "aura/include/objcpp.h"

#else

#include "core/_.h"


#if BROAD_PRECOMPILED_HEADER
//#include "core/user/userex/_component.h"
//#include "core/user/rich_text/_component.h"
//#include "core/filesystem/filemanager/_component.h"
//#include "core/filesystem/filehandler/_component.h"
//#include "axis/html/graphics/_component.h"
//#include "axis/html/impl/_component.h"
//#include "core/user/account/_component.h"
//#include "core/user/databaseuser/_component.h"
#endif
#include "core/_defer.h"



#endif

#else

#ifdef __OBJC__

#include "aura/include/objc.h"

#else

#include "aura/_.h"

#endif

#endif



