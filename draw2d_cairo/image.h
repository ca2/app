#pragma once


#include "aura/graphics/image/image.h"


namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO image :
      virtual public ::image::image
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

      //virtual bool stretch(const ::image::image *pimage) override;

      void dc_select(bool bSelect = true) override;

      void create(const ::int_size & size, ::enum_flag eflagCreate = OK_IMAGE, int iGoodStride = -1, bool bPreserve = false) override;
      void create(::draw2d::graphics * pgraphics) override;
      void destroy() override;

      bool on_host_read_pixels(::pixmap * ppixmap) const override;
      //virtual bool stretch(const ::image::image *pimage) override;
      void _draw_raw(const ::int_rectangle & rectangle, ::image::image *pimage, const ::int_point & point = ::int_point()) override;

      //bool to(::draw2d::graphics * pgraphics, const ::int_point & point, const ::int_size & size, const ::int_point & pointSrc) override;
      void SetIconMask(::image::icon * picon, int cx, int cy) override;


      //void write(::binary_stream & stream) const override;
      //void read(::binary_stream & stream) override;


      void blend(const ::int_point & ptDst, ::image::image *pimageAlf, const ::int_point & pointAlf, const ::int_size & size, unsigned char bA) override;
      //void blend2(const ::int_point & ptDst, ::image::image *pimageAlf, const ::int_point & pointAlf, const ::int_size & size, unsigned char bA) override;


   };


} // namespace draw2d_cairo



