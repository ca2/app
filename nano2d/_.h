#pragma once


#include "aura/_.h"


#ifdef _nano2d_project
#define CLASS_DECL_NANO2D  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_NANO2D CLASS_DECL_IMPORT
#endif


namespace nano2d
{


   class context;

   struct glyphPosition;

   class text_box;

} // namespace nano2d


CLASS_DECL_NANO2D::object * get_nano2d_object(::nano2d::context * pcontext);


