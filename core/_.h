///TBS__<3tbs
#pragma once


#include "bred/_.h"


#if defined(_CORE_LIBRARY)
#define CLASS_DECL_CORE  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_CORE  CLASS_DECL_IMPORT
#endif


#include "core/include/_.h"


#include "core/user/user/_.h"
#include "core/user/simple/_.h"



