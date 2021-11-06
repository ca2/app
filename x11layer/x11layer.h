#pragma once


#ifdef _WIN32
#ifdef CUBE
#define CLASS_DECL_AQUA
#else
#if defined(_APP_AQUA_LIBRARY)
#define CLASS_DECL_AQUA CLASS_DECL_EXPORT
#else
#define CLASS_DECL_AQUA CLASS_DECL_IMPORT
#endif
#endif
#else
#define CLASS_DECL_AQUA 
#endif


#include "aqua_graphics_alpha.h"



