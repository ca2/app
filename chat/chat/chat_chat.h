#pragma once


#include "aura/_.h"


#if defined(_CA2_MATH_DLL)
   #define CLASS_DECL_CA2_MATH  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_CA2_MATH  CLASS_DECL_IMPORT
#endif


#include "math/kissfft/kissfft.h"
#include "math/calculator/calculator.h"
