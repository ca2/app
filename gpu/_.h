///TBS__<3tbs
#pragma once

//#pragma pack(show)


#include "bred/_.h"
//#ifdef	_STDIO_H_
//#error "already included?!?! WHAT?!?! (At aqua:a)"
//#endif

#undef PLATFORM_LAYER_NAME
#define PLATFORM_LAYER_NAME gpu

#if defined(_gpu_project)
#define CLASS_DECL_GPU  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_GPU  CLASS_DECL_IMPORT
#endif


#undef __spin_namespace


namespace gpu
{


   class Cube;

   class FullscreenQuad;

   class HDRTexture;


} // namespace gpu


#include "aqua/include/_include.h"

#include "gpu/gltf/_.h"
#include "gpu/ibl/_.h"



