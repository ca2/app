#pragma once


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


      void Prepare(const ::rectangle_i32 & rectangle);


   };


} // namespace vis





