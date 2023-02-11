#pragma once


#include "aura/_.h"


#ifdef _nanoui_project
#define CLASS_DECL_NANOUI  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_NANOUI CLASS_DECL_IMPORT
#endif


#define NANOUI_EXPORT CLASS_DECL_NANOUI
#define NANO2D_EXPORT CLASS_DECL_NANOUI


#include "nano2d/_.h"


namespace nanoui
{


   class Screen;


} // namespace nanoui


#include "_constant.h"


#include "_function.h"



