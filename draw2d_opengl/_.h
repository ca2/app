#pragma once


#include "aura/_.h"


#ifdef _DRAW2D_OPENGL_STATIC
#define CLASS_DECL_DRAW2D_OPENGL
#elif defined(_draw2d_opengl_project)
#define CLASS_DECL_DRAW2D_OPENGL  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_DRAW2D_OPENGL  CLASS_DECL_IMPORT
#endif


