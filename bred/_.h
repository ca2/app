///TBS__<3tbs
#pragma once

//#pragma pack(show)


#include "base/_.h"


#if defined(_BRED_LIBRARY)
#define CLASS_DECL_BRED  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_BRED  CLASS_DECL_IMPORT
#endif


#undef __spin_namespace


#include "bred/include/_.h"



