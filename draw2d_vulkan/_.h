#pragma once


#include "aura/_.h"
#if defined(WINDOWS_DESKTOP)
#include "windowing_win32/_.h"
#include "acme/_operating_system.h"
#endif
#include "gpu_vulkan/_.h"


#ifdef _DRAW2D_VULKAN_STATIC
#define CLASS_DECL_DRAW2D_VULKAN
#elif defined(_draw2d_vulkan_project)
#define CLASS_DECL_DRAW2D_VULKAN  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_DRAW2D_VULKAN  CLASS_DECL_IMPORT
#endif


