#ifndef __GNUC__
#pragma once
#endif


#include "acme/_start.h"


#ifdef __cplusplus

#ifdef __OBJC__

#include "apex/include/objcpp.h"

#else

#include "apex/_.h"
#include "apex/platform/_platform.h"
#if BROAD_PRECOMPILED_HEADER
////#include "core/user/simple/_component.h"
//#include "apex/user/rich_text/_rich_text.h"
//#include "apex/filesystem/filemanager/_filemanager.h"
//#include "apex/filesystem/filehandler/_filehandler.h"
//#include "core/user/userex/_userex.h"
//#include "core/user/experience/_experience.h"
//#include "apex/user/databaseuser/_databaseuser.h"
#endif


#include "apex/_defer.h"



#endif

#else

#ifdef __OBJC__

#include "apex/include/objc.h"

#else

#include "apex/_.h"

#endif

#endif



