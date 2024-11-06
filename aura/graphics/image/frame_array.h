#pragma once


#include "image.h"
#include "frame.h"
#include "acme/graphics/draw2d/color_array.h"


namespace image
{



   class CLASS_DECL_AURA image_frame_array :
      virtual public pointer_array < ::image::image_frame >
   {
   public:


      ::image::image_pointer      m_pimage;
      class ::time         m_timeTotal;
      ::collection::count              m_countLoop; // 0 - infinite loop
      ::collection::index              m_iLoop;
      int                  m_iTransparentIndex;
      bool                 m_bTransparent;
      ::color::color       m_colorTransparent;
      ::color::color       m_colorBack;
      unsigned char                 m_backgroundIndex;
      ::int_size           m_sizeLogical;
      ::int_size           m_size;
      ::image::image_pointer      m_pimageCompose;
      color_array          m_colora;


      image_frame_array();
      ~image_frame_array() override;


      const ::int_size size() { return m_size; }
      const ::int_size & size() const { return m_size; }

      ::int_rectangle rectangle(const ::int_point & point = {}) { return ::int_rectangle(point, m_size); }
      const ::int_rectangle rectangle(const ::int_point & point = {}) const { return ::int_rectangle(point, m_size); }

      virtual ::image::image_pointer calc_current_frame(image_dynamic & dynamic);
      virtual void update(::image::image *pimageHost, const ::image::image_drawing & imagedrawing);

      inline image_extension * extension() { return m_pimage->extension(); }

   };


} // namespace image



