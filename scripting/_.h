#pragma once


#include "acme/_.h"



#ifdef _APP_SCRIPTING_LIBRARY
#define CLASS_DECL_APP_SCRIPTING  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_SCRIPTING  CLASS_DECL_IMPORT
#endif


#include "javascript/_.h"



