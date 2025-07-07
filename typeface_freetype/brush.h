#pragma once


#include "aura/graphics/draw2d/brush.h"


namespace typeface_freetype
{


   class CLASS_DECL_TYPEFACE_FREETYPE brush : 
      virtual public ::draw2d::brush
   {
   public:


      brush();
      virtual ~brush();


      // void dump(dump_context & dumpcontext) const override;


   };


} // namespace typeface_freetype


