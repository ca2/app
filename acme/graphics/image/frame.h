#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"
////#include "acme/prototype/prototype/object.h"
#include "acme/prototype/geometry2d/rectangle.h"

namespace image
{


   class CLASS_DECL_ACME image_frame :
      virtual public particle
   {
   public:


      ::pixmap_pointer              m_ppixmap;
      ::i32_rectangle               m_rectangle;
      class ::time                  m_time;
      ::collection::index           m_iFrame;
      ::draw2d::enum_disposal       m_edisposal;
      ::color::color                m_colorTransparent;
      bool                          m_bTransparent;
      bool                          m_bLocalPalette;
      ::particle_pointer            m_pparticleImage;


      image_frame();
      ~image_frame() override;


      virtual void gif_set_disposal(::i32 iDisposal);


      virtual void _001Process(::pixmap *ppixmapCompose, ::pixmap *ppixmapFrame, ::image::image_frame_array * pframea);
      //virtual void create(::image::image_frame * pframeSource, const ::image::image_drawing & imagedrawing, ::image::image_frame_array * pframea);
      virtual void create_frame(::image::image_frame * pframeSource, const ::pixmap * ppixmap, ::image::image_frame_array * pframea);


   };


} // namespace image



