#pragma once


namespace draw2d_quartz2d
{


   class CLASS_DECL_DRAW2D_QUARTZ2D image :
      virtual public ::image
   {
   public:


//      ::draw2d::bitmap_pointer        m_pbitmap;
//      ::draw2d::graphics_pointer      m_spgraphics;


      image();
      virtual ~image();

      virtual bool map(bool bApplyAlphaTransform = true) override;
      virtual bool _unmap() override;

      
      //virtual bool detach(::image * pimage) override;
      

      virtual ::draw2d::graphics * _get_graphics() const override;
      virtual ::draw2d::bitmap_pointer get_bitmap() const override;
      virtual ::draw2d::bitmap_pointer detach_bitmap() override;


      //virtual const color32_t * get_data() const override;

      virtual bool stretch_image(::image * pimage) override;

      bool dc_select(bool bSelect = true) override;


      ::e_status create(const ::size_i32 & size, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1, bool bPreserve = false) override;
      //::e_status create(i32 iWidth, i32 iHeight, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1, bool bPreserve = false) override;
      ::e_status create(::draw2d::graphics * pgraphics) override;
      virtual bool destroy() override;



      bool from(const ::point_i32 & pointDest, ::draw2d::graphics * pgraphics, const ::point_i32 & point, const ::size_i32 & sz) override;
      bool to(::draw2d::graphics * pgraphics, const ::point_i32 & point, const ::size_i32 & size, const ::point_i32 & pointSrc) override;

      ::e_status SetIconMask(::draw2d::icon * picon, i32 cx, i32 cy) override;

      virtual bool set_mapped() override;

      virtual bool blend(const ::point_i32 & pointDst, ::image * pimplSrc, const ::point_i32 & pointSrc, const ::size_i32 & size, byte bA) override;


   };
      

} // namespace draw2d_quartz2d



