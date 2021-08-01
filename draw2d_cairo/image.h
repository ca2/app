#pragma once


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


      virtual bool map(bool bApplyAlphaTransform = true) override;
      virtual bool _unmap() override;



      virtual ::draw2d::graphics * _get_graphics() const override;
      virtual ::draw2d::bitmap_pointer get_bitmap() const override;
      virtual ::draw2d::bitmap_pointer detach_bitmap() override;

      //virtual bool stretch(const ::image * pimage) override;

      bool dc_select(bool bSelect = true) override;

      virtual ::e_status create(const ::size_i32 & size, ::eobject eobjectCreate = OK, int iGoodStride = -1, bool bPreserve = false) override;
      virtual ::e_status create(::draw2d::graphics * pgraphics) override;
      virtual ::e_status destroy() override;


      virtual bool on_host_read_pixels(const ::pixmap * ppixmap) override;
      //virtual bool stretch(const ::image * pimage) override;
      virtual bool _draw_raw(const ::rectangle_i32 & rectangle, ::image * pimage, const ::point_i32 & point = ::point_i32()) override;

      //bool to(::draw2d::graphics * pgraphics, const ::point_i32 & point, const ::size_i32 & size, const ::point_i32 & pointSrc) override;
      virtual ::e_status SetIconMask(::draw2d::icon * picon, i32 cx, i32 cy) override;


      virtual ::stream & write(::stream & stream) const override;
      virtual ::stream & read(::stream & stream) override;


      virtual bool blend(const ::point_i32 & ptDst, ::image * pimageAlf, const ::point_i32 & pointAlf, const ::size_i32 & size, byte bA) override;


   };


} // namespace draw2d_cairo



