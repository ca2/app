#pragma once


#include "axis/_.h"


#ifdef _APP_PROGRAMMING_LIBRARY
#define CLASS_DECL_APP_PROGRAMMING  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_PROGRAMMING  CLASS_DECL_IMPORT
#endif


#include "dynamic_source/_.h"

#include "introjection/_.h"



