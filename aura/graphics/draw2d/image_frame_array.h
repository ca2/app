#pragma once


class CLASS_DECL_AURA image_frame_array :
   virtual public __pointer_array(::image_frame)
{
public:


   ::image_pointer      m_pimage;
   ::duration           m_durationTotal;
   ::count              m_countLoop; // 0 - infinite loop
   ::index              m_iLoop;
   int                  m_iTransparentIndex;
   bool                 m_bTransparent;
   ::color::color       m_colorTransparent;
   ::color::color       m_colorBack;
   byte                 m_backgroundIndex;
   ::size_i32           m_sizeLogical;
   ::size_i32           m_size;
   ::image_pointer      m_pimageCompose;
   colorref_array       m_colorrefa;


   image_frame_array();
   ~image_frame_array() override;


   const ::size_i32 size() { return m_size; }
   const ::size_i32 & size() const { return m_size; }

   ::rectangle_i32 rectangle(const ::point_i32 & point = nullptr) { return ::rectangle_i32(point, m_size); }
   const ::rectangle_i32 rectangle(const ::point_i32 & point = nullptr) const { return ::rectangle_i32(point, m_size); }

   virtual ::image_pointer calc_current_frame(image_dynamic & dynamic);


   inline image_extension * extension() { return m_pimage->extension(); }

};
