#ifndef __GNUC__
#pragma once
#endif


#include "acme/_start.h"


#ifdef __cplusplus



#include "_.h"
#include "aqua/xml.h"
#if !defined(BROAD_PRECOMPILED_HEADER)
#define BROAD_PRECOMPILED_HEADER 1
#endif
#if BROAD_PRECOMPILED_HEADER
//#include "aura/user/_user.h"
//#include "core/user/simple/_simple.h"
//#include "aura/user/rich_text/_rich_text.h"
//#include "aura/filesystem/filemanager/_filemanager.h"
//#include "aura/filesystem/filehandler/_filehandler.h"
//#include "core/user/userex/_userex.h"
//#include "core/user/experience/_experience.h"
//#include "aura/user/databaseuser/_databaseuser.h"
#endif
//#include "aura/crypto/crypto_openssl.h"
#include "apex/_defer.h"



#else

#ifdef __OBJC__

#include "aqua/include/objc.h"

#else

#include "aqua/_.h"

#endif

#endif



