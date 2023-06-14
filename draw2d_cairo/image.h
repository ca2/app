#pragma once


#include "aura/graphics/image/image.h"


namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO image :
      virtual public ::image
   {
   public:


#ifdef WINDOWS
      HBITMAP                 m_hbitmap;
//      BITMAPINFO              m_bitmapinfo;
      //    BITMAPINFO              m_info;
#endif


      image();
      ~image() override;


      void _map(bool bApplyAlphaTransform = true) override;
      void _unmap() override;


      ::draw2d::graphics * _get_graphics() const override;
      ::draw2d::bitmap_pointer get_bitmap() const override;
      ::draw2d::bitmap_pointer detach_bitmap() override;

      //virtual bool stretch(const ::image * pimage) override;

      void dc_select(bool bSelect = true) override;

      void create(const ::size_i32 & size, ::enum_flag eflagCreate = OK_IMAGE, int iGoodStride = -1, bool bPreserve = false) override;
      void create(::draw2d::graphics * pgraphics) override;
      void destroy() override;


      bool on_host_read_pixels(::pixmap * ppixmap) const override;
      //virtual bool stretch(const ::image * pimage) override;
      void _draw_raw(const ::rectangle_i32 & rectangle, ::image * pimage, const ::point_i32 & point = ::point_i32()) override;

      //bool to(::draw2d::graphics * pgraphics, const ::point_i32 & point, const ::size_i32 & size, const ::point_i32 & pointSrc) override;
      void SetIconMask(::draw2d::icon * picon, i32 cx, i32 cy) override;


      //void write(::binary_stream < FILE > & stream) const override;
      //void read(::binary_stream < FILE > & stream) override;


      void blend(const ::point_i32 & ptDst, ::image * pimageAlf, const ::point_i32 & pointAlf, const ::size_i32 & size, ::u8 bA) override;
      //void blend2(const ::point_i32 & ptDst, ::image * pimageAlf, const ::point_i32 & pointAlf, const ::size_i32 & size, ::u8 bA) override;


   };


} // namespace draw2d_cairo



