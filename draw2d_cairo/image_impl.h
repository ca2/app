#pragma once


namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO image :
      virtual public ::image
   {
   public:


      //::draw2d::bitmap_pointer      m_pbitmap;
      //::draw2d::graphics_pointer    m_spgraphics;
      //bool                          m_bTrans;


//      class size64            m_sizeWnd;
#ifdef WINDOWS
      HBITMAP                 m_hbitmap;
//      BITMAPINFO              m_bitmapinfo;
      //    BITMAPINFO              m_info;
#endif


      image();
      //virtual void construct(i32 cx, i32 cy);
      virtual ~image();


      virtual bool _map(bool bApplyAlphaTransform = true) override;
      virtual bool _unmap() override;


      virtual ::draw2d::graphics * _get_graphics() const override;
      virtual ::draw2d::bitmap_pointer get_bitmap() const override;
      virtual ::draw2d::bitmap_pointer detach_bitmap() override;


      //virtual COLORREF * get_data();

      virtual bool stretch_image(::image * pimage_impl) override;

      bool dc_select(bool bSelect = true) override;





      virtual ::estatus create(const ::size & size, ::eobject eobjectCreate = OK, int iGoodStride = -1, bool bPreserve = false) override;
      //virtual bool create(i32 iWidth, i32 iHeight, const ::uid & uidCreateImage = OK, int iGoodStride = -1) override;
      virtual ::estatus create(::draw2d::graphics * pgraphics) override;
      virtual bool destroy() override;


virtual bool on_host_read_pixels(const ::pixmap * ppixmap) override;
      bool from(::draw2d::graphics * pgraphics) override;
      //bool from(const ::point & ptDest, ::draw2d::graphics * pgraphics, const ::point & point, const ::size & size) override;

      bool to(::draw2d::graphics * pgraphics, const ::point & point, const ::size & size, const ::point & pointSrc) override;
//#if defined(WINDOWS) || defined(LINUX) || defined(ANDROID)
  //    virtual bool update_window(::aura::draw_interface * pwnd,::message::message * pmessage, bool bTransferBuffer);
    //  virtual bool print_window(::aura::draw_interface * pwnd,::message::message * pmessage);
//#endif
      virtual ::estatus SetIconMask(::draw2d::icon * picon, i32 cx, i32 cy) override;


      //virtual void io(stream & stream) override;


      virtual ::stream & write(::stream & stream) const override;
      virtual ::stream & read(::stream & stream) override;


      //virtual bool blend(point ptDst, ::image * pimage, point ptSrc, ::size size, byte bA) override;
      virtual bool blend(const ::point & ptDst, ::image * pimageAlf, const ::point & pointAlf, const ::size & size, byte bA) override;


   };


} // namespace draw2d_cairo



