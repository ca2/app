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
      virtual ~image();


      virtual bool _map(bool bApplyAlphaTransform = true) override;
      virtual bool _unmap() override;


      virtual ::draw2d::graphics * _get_graphics() const override;
      virtual ::draw2d::bitmap_pointer get_bitmap() const override;
      virtual ::draw2d::bitmap_pointer detach_bitmap() override;

      virtual bool stretch(::image * pimage_impl) override;

      bool dc_select(bool bSelect = true) override;

      virtual ::estatus create(const ::size & size, ::eobject eobjectCreate = OK, int iGoodStride = -1, bool bPreserve = false) override;
      virtual ::estatus create(::draw2d::graphics * pgraphics) override;
      virtual bool destroy() override;


      virtual bool on_host_read_pixels(const ::pixmap * ppixmap) override;
      bool from(::draw2d::graphics * pgraphics) override;

      bool to(::draw2d::graphics * pgraphics, const ::point & point, const ::size & size, const ::point & pointSrc) override;
      virtual ::estatus SetIconMask(::draw2d::icon * picon, i32 cx, i32 cy) override;


      virtual ::stream & write(::stream & stream) const override;
      virtual ::stream & read(::stream & stream) override;


      virtual bool blend(const ::point & ptDst, ::image * pimageAlf, const ::point & pointAlf, const ::size & size, byte bA) override;


   };


} // namespace draw2d_cairo



