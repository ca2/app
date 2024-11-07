///TBS__<3tbs
#pragma once


#include "bred/_.h"


#undef PLATFORM_LAYER_NAME
#define PLATFORM_LAYER_NAME core


#if defined(_core_project)
#define CLASS_DECL_CORE  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_CORE  CLASS_DECL_IMPORT
#endif


#include "core/include/_include.h"





