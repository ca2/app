///TBS__<3tbs
#pragma once

#undef __spin_namespace
#define __spin_namespace axis // back bone / four-letter "spin*" namespace name


#include "aura/_.h"

#undef PLATFORM_LAYER_NAME
#define PLATFORM_LAYER_NAME axis


#if defined(_axis_project)
#define CLASS_DECL_AXIS  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_AXIS  CLASS_DECL_IMPORT
#endif


#include "axis/include/_include.h"



