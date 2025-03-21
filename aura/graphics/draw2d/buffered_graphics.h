#pragma once


#include "aura/graphics/draw2d/bitmap.h"


namespace draw2d
{


   class buffered_graphics :
      public ::draw2d::graphics_pointer
   {
   public:


      ::draw2d::bitmap_pointer   m_pbitmap;
      ::draw2d::bitmap_pointer   m_pbitmapBlend;


      buffered_graphics();
      virtual ~buffered_graphics();


      void Prepare(const ::int_rectangle & rectangle);


   };


} // namespace vis





