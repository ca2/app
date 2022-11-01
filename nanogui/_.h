#pragma once


#include "aura/_.h"


#ifdef _NANOGUI_LIBRARY
#define CLASS_DECL_NANOGUI  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_NANOGUI CLASS_DECL_IMPORT
#endif


#define NANOGUI_EXPORT CLASS_DECL_NANOGUI
#define NANO2D_EXPORT CLASS_DECL_NANOGUI


#include "nano2d/_.h"


namespace nanogui
{


   class Screen;


} // namespace nanogui


#include "_constant.h"


#include "_function.h"



