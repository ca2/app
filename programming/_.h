#pragma once


#include "axis/_.h"


#if defined(_programming_project)
#define CLASS_DECL_APP_PROGRAMMING  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_PROGRAMMING  CLASS_DECL_IMPORT
#endif


#include "programming/_.h"

#include "dynamic_source/_.h"

#include "introjection/_.h"



