#pragma once


namespace draw2d_direct2d
{


   class CLASS_DECL_DRAW2D_DIRECT2D image :
      virtual public ::image
   {
   public:


      HRESULT                             m_hrEndDraw;
      BITMAPINFO                          m_info;
      bool                                m_bTrans;

      //::draw2d::bitmap_pointer            m_pbitmap;
      //::draw2d::graphics_pointer          m_pgraphics;

      ::draw2d::bitmap_pointer            m_pbitmapMap;
      ::draw2d::graphics_pointer          m_pgraphicsMap;


      image();
      virtual ~image();


      virtual bool _map(bool bApplyAlphaTransform = true) override;
      virtual bool _unmap() override;


      virtual ::draw2d::graphics * _get_graphics() const override;
      virtual ::draw2d::bitmap_pointer get_bitmap() const;
      virtual ::draw2d::bitmap_pointer detach_bitmap();


      virtual bool stretch(const ::image * pimage) override;

      bool dc_select(bool bSelect = true);





      //bool _create(::size size);
      using ::image::create;
      virtual ::e_status create(const ::size & size, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iStride = -1, bool bPreserver = false) override;
      bool _create(::draw2d::graphics * pgraphics);
      bool destroy();


      using ::image::draw;
      //virtual bool draw(::draw2d::graphics * pgraphics) override;
      virtual bool draw(const ::rect & rectDst, ::image * pimage, const ::point & pointSrc) override;

      //using ::image::to;
      //bool to(::draw2d::graphics * pgraphics, const ::point & point, const ::size & size, const ::point & pointSrc) override;

      virtual ::e_status SetIconMask(::draw2d::icon * picon, i32 cx, i32 cy) override;


      virtual bool defer_realize(::draw2d::graphics * pgraphics) const;
      virtual bool realize(::draw2d::graphics * pgraphics) const;
      virtual bool unrealize() const;
      virtual bool is_realized() const;

      using ::image::blend;
      virtual bool blend(const ::point & pointDst, ::image * pimageSrc, const ::point & pointSrc, const ::size & size, byte bA) override;

      using ::image::tint;
      virtual bool tint(::image * pimage, const rgb & rgb) override;

      


   };


} // namespace draw2d_direct2d



