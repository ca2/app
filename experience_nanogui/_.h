#pragma once


#include "base/_.h"


#ifdef _APP_EXPERIENCE_CORE_LIBRARY
    #define CLASS_DECL_APP_EXPERIENCE_CORE  CLASS_DECL_EXPORT
#else
    #define CLASS_DECL_APP_EXPERIENCE_CORE  CLASS_DECL_IMPORT
#endif



