#pragma once


#include "aura/graphics/draw2d/bitmap.h"
#include "aura/graphics/draw2d/graphics_pointer.h"


namespace draw2d
{


   class CLASS_DECL_AURA buffered_graphics :
      public ::draw2d::graphics_pointer
   {
   public:


      ::draw2d::bitmap_pointer   m_pbitmap;
      ::draw2d::bitmap_pointer   m_pbitmapBlend;


      buffered_graphics();
      ~buffered_graphics();


      void Prepare(const ::i32_rectangle & rectangle);


   };


} // namespace vis





