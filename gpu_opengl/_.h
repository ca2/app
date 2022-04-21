// Changed by camilo on 2021-12-10 19:36 PM <3ThomasBorregaardSørensen!!
#pragma once


#include "aura/_.h"
#include "aura/gpu/gpu/_.h"


#ifdef _GPU_OPENGL_STATIC
#define CLASS_DECL_GPU_OPENGL
#elif defined(_GPU_OPENGL_LIBRARY)
#define CLASS_DECL_GPU_OPENGL  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_GPU_OPENGL  CLASS_DECL_IMPORT
#endif
