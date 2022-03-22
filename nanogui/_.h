#pragma once


#include "base/_.h"


#ifdef _NANOGUI_LIBRARY
#define CLASS_DECL_NANOGUI  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_NANOGUI CLASS_DECL_IMPORT
#endif


#define NANOGUI_EXPORT CLASS_DECL_NANOGUI


namespace nanogui
{



} // namespace nanogui


