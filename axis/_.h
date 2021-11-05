///TBS__<3tbs
#pragma once


#include "aura/_.h"


#if defined(_AXIS_LIBRARY)
#define CLASS_DECL_AXIS  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_AXIS  CLASS_DECL_IMPORT
#endif


#include "axis/include/_.h"



