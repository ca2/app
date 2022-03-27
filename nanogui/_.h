#pragma once


#include "aura/_.h"


#ifdef _NANOGUI_LIBRARY
#define CLASS_DECL_NANOGUI  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_NANOGUI CLASS_DECL_IMPORT
#endif


#define NANOGUI_EXPORT CLASS_DECL_NANOGUI
#define NANO2D_EXPORT CLASS_DECL_NANOGUI


namespace nanogui
{



} // namespace nanogui


