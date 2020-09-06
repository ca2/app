#ifndef __GNUC__
#pragma once
#endif


#ifdef __cplusplus

#ifdef __OBJC__

#include "aura/include/objcpp.h"

#else

#include "core/_.h"

#ifndef BROAD_PRECOMPILED_HEADER
#define BROAD_PRECOMPILED_HEADER 1
#endif // BROAD_PRECOMPILED_HEADER

#if BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#include "core/user/rich_text/_rich_text.h"
#include "core/filesystem/filemanager/_filemanager.h"
#include "core/filesystem/filehandler/_filehandler.h"
#include "core/user/userex/_userex.h"
#include "core/user/simple_ui/_simple_ui.h"
#include "core/user/account/_account.h"
#include "core/user/databaseuser/_databaseuser.h"
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



