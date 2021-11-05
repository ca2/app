///TBS__<3tbs
#pragma once

//#pragma pack(show)


#include "apex/_.h"


#if defined(_AQUA_LIBRARY)
#define CLASS_DECL_AQUA  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_AQUA  CLASS_DECL_IMPORT
#endif


#undef __spin_namespace


#include "aqua/include/_.h"



