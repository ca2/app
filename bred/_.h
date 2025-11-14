///TBS__<3tbs
#pragma once

//#pragma pack(show)


#include "berg/_.h"
#include "bred/gpu/_types.h"


#undef PLATFORM_LAYER_NAME
#define PLATFORM_LAYER_NAME bred

#if defined(_bred_project)
#define CLASS_DECL_BRED  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_BRED  CLASS_DECL_IMPORT
#endif


#undef __spin_namespace


#include "bred/include/_.h"


