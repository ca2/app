#pragma once


#include "axis/_.h"
#include "axis/math/_.h"


#if defined(_CA2_TIME_DLL)
   #define CLASS_DECL_CA2_TIME  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_CA2_TIME  CLASS_DECL_IMPORT
#endif


#include "time/calculator/_.h"

#include "time/datetime/_.h"

#include "time/graphics/_.h"
