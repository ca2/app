#pragma once


#include "axis/_.h"
#include "nano2d/_.h"


#ifdef _nanoui_project
#define CLASS_DECL_NANOUI  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_NANOUI CLASS_DECL_IMPORT
#endif


namespace nanoui
{


   class Screen;


   template < typename NUMBER >
   class IntBox;


} // namespace nanoui


//#include "nanoui/_constant.h"


//#include "nanoui/_function.h"



