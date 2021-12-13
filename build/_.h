#pragma once


#include "apex/_.h"


#ifdef _APP_BUILD_LIBRARY
#define CLASS_DECL_APP_BUILD  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_BUILD  CLASS_DECL_IMPORT
#endif




