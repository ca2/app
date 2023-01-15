#pragma once


#include "base/_.h"


#ifdef _APP_SIMPLE_DRAWING_LIBRARY
#define CLASS_DECL_APP_SIMPLE_DRAWING  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_APP_SIMPLE_DRAWING  CLASS_DECL_IMPORT
#endif


namespace app_simple_drawing
{


   class application;
   class tab_impact;
   class document;
   class impact;
   class render;


} // namespace flag

