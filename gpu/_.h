///TBS__<3tbs
#pragma once

//#pragma pack(show)


#include "bred/_.h"
//#ifdef	_STDIO_H_
//#error "already included?!?! WHAT?!?! (At aqua:a)"
//#endif

//#undef PLATFORM_LAYER_NAME
//#define PLATFORM_LAYER_NAME gpu

#if defined(_gpu_project)
#define CLASS_DECL_GPU  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_GPU  CLASS_DECL_IMPORT
#endif


namespace gpu
{


   //class cube;

   class full_screen_quad;

   class Timer;

   //class hdr_texture;


} // namespace gpu


#include "aqua/include/_include.h"


#include "gpu/gltf/_.h"
#include "gpu/ibl/_.h"



