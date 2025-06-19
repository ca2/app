// Changed by camilo on 2021-12-10 19:36 PM <3ThomasBorregaardSorensen!!
#pragma once


#include "bred/_.h"


#if defined(WINDOWS_DESKTOP)
#include "windowing_win32/_.h"
#endif
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"


#if defined(_gpu_opengl_project)
#define CLASS_DECL_GPU_OPENGL  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_GPU_OPENGL  CLASS_DECL_IMPORT
#endif

#include "_gpu_opengl.h"



namespace gpu_opengl
{


   class frame_buffer;

   class device;

   class renderer;

#if defined(WINDOWS_DESKTOP)

   class device_win32;

#endif

   class shader;

} // namespace gpu_opengl


