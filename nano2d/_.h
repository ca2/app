#pragma once


#include "aura/_.h"


#ifdef _nano2d_project
#define CLASS_DECL_NANO2D  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_NANO2D CLASS_DECL_IMPORT
#endif


//#define NANOUI_EXPORT CLASS_DECL_NANOUI
//#define NANO2D_EXPORT CLASS_DECL_NANOUI


//#include "nano2d/_.h"
//
//
namespace nano2d
{
//
//
   class context;



   struct glyphPosition;

//
//
} // namespace nano2d
//
//
//#include "_constant.h"
//
//
//#include "_function.h"
//
//
//

CLASS_DECL_NANO2D::object * get_nano2d_object(::nano2d::context * pcontext);


