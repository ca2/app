// Changed by camilo on 2021-12-10 19:36 PM <3ThomasBorregaardSorensen!!
#pragma once


#include "aura/_.h"
#include "aura/graphics/gpu/_.h"

#if defined(WINDOWS_DESKTOP)
#include "windowing_win32/_.h"
#endif
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"


#if defined(_gpu_vulkan_project)
#define CLASS_DECL_GPU_VULKAN  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_GPU_VULKAN  CLASS_DECL_IMPORT
#endif


#include "_gpu_vulkan.h"


namespace gpu_vulkan
{

   
   class program;
   class approach;


   class swap_chain;

   class benchmark;

   class physical_device;

   class context;

   class device;

   class pipeline;

   //class camera;


} // namespace gpu_vulkan




 