#pragma once


#include "core/core/core/core.h"
#include "core/math/math_math.h"


#if defined(_CA2_TIME_DLL)
   #define CLASS_DECL_CA2_TIME  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_CA2_TIME  CLASS_DECL_IMPORT
#endif


#include "time/calculator/calculator.h"

#include "time/datetime/datetime.h"

#include "time/graphics/graphics.h"
