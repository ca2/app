#ifndef __GNUC__
#pragma once
#endif


#ifdef __cplusplus

#ifdef __OBJC__

#include "aqua/include/objcpp.h"

#else

#include "aqua/_.h"
#include "aqua/platform/_platform.h"
#if !defined(BROAD_PRECOMPILED_HEADER)
#define BROAD_PRECOMPILED_HEADER 1
#endif
#include "aqua/user/_user.h"
#if BROAD_PRECOMPILED_HEADER
//#include "core/user/simple/_simple.h"
//#include "aqua/user/rich_text/_rich_text.h"
//#include "aqua/filesystem/filemanager/_filemanager.h"
//#include "aqua/filesystem/filehandler/_filehandler.h"
//#include "core/user/userex/_userex.h"
//#include "core/user/experience/_experience.h"
//#include "aqua/user/databaseuser/_databaseuser.h"
#endif
#include "aqua/crypto/crypto_openssl.h"
#include "aqua/_defer.h"



#endif

#else

#ifdef __OBJC__

#include "aqua/include/objc.h"

#else

#include "aqua/_.h"

#endif

#endif



