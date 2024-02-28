#pragma once


#include "image.h"
#include "frame.h"
#include "acme/graphics/draw2d/color_array.h"


class CLASS_DECL_AURA image_frame_array :
   virtual public pointer_array < ::image_frame >
{
public:


   ::image_pointer      m_pimage;
   class ::time         m_timeTotal;
   ::count              m_countLoop; // 0 - infinite loop
   ::index              m_iLoop;
   int                  m_iTransparentIndex;
   bool                 m_bTransparent;
   ::color::color       m_colorTransparent;
   ::color::color       m_colorBack;
   ::u8                 m_backgroundIndex;
   ::size_i32           m_sizeLogical;
   ::size_i32           m_size;
   ::image_pointer      m_pimageCompose;
   color_array          m_colora;


   image_frame_array();
   ~image_frame_array() override;


   const ::size_i32 size() { return m_size; }
   const ::size_i32 & size() const { return m_size; }

   ::rectangle_i32 rectangle(const ::point_i32 & point = {}) { return ::rectangle_i32(point, m_size); }
   const ::rectangle_i32 rectangle(const ::point_i32 & point = {}) const { return ::rectangle_i32(point, m_size); }

   virtual ::image_pointer calc_current_frame(image_dynamic & dynamic);
   virtual void update(::image * pimageHost, const ::image_drawing & imagedrawing);

   inline image_extension * extension() { return m_pimage->extension(); }

};
