#pragma once


#include "bred/_.h"
#if defined(WINDOWS_DESKTOP)
#include "windowing_win32/_.h"
#include "acme/_operating_system.h"
#endif
#include "gpu_opengl/_.h"


#ifdef _DRAW2D_OPENGL_STATIC
#define CLASS_DECL_DRAW2D_OPENGL
#elif defined(_draw2d_opengl_project)
#define CLASS_DECL_DRAW2D_OPENGL  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_DRAW2D_OPENGL  CLASS_DECL_IMPORT
#endif


namespace draw2d_opengl
{

   class face;
   class face_freetype;
   class face_gdiplus;

} // namespace draw2d_opengl