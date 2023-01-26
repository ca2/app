#pragma once


#include "apex/_.h"


#ifdef _API_YOUTUBE_LIBRARY
#define CLASS_DECL_API_YOUTUBE  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_API_YOUTUBE  CLASS_DECL_IMPORT
#endif

