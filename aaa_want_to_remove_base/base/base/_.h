#pragma once


#include "aura/_.h"


#ifdef _BASE_STATIC
#define CLASS_DECL_BASE
#elif defined(_BASE_LIBRARY)
#define CLASS_DECL_BASE  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_BASE  CLASS_DECL_IMPORT
#endif

//#include "base/base/os/_.h"

#include "base/policy/policy.h"

#define new AURA_NEW












