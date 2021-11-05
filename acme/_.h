///<3TBS_!!
#pragma once




#if defined(__cplusplus) && !defined(_ACID_LIBRARY)
#include "acme/memory/allocation.h"
#endif


#ifdef __cplusplus


#undef SYSTEM_TYPE
#define SYSTEM_TYPE class ::system

#undef SESSION_TYPE
#define SESSION_TYPE ::acme::session

#undef APP_TYPE
#define APP_TYPE ::acme::application


#endif


#if !defined(_UWP) && !defined(APPLE_IOS) && !defined(ANDROID) && !defined(SMALLCODE) && !defined(RASPBIAN)

#define HOTPLUGIN_SUBSYSTEM

#endif

#include "acme/platform/object_reference_count_debug.h"

#include "acme/platform/object_type_counter.h"

#include "acme/constant/_constant.h"

#include "acme/memory/memory_allocate.h"

#include "acme/memory/heap_c.h"

#include "acme/memory/allocate_processor_cache_oriented.h"

#include "acme/platform/number.h"

#include "acme/include/_include.h"



