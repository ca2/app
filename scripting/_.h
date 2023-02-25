#pragma once


#include "acme/_.h"



#if defined(_scripting_project)
#define CLASS_DECL_APP_SCRIPTING  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_SCRIPTING  CLASS_DECL_IMPORT
#endif


#include "javascript/_.h"



