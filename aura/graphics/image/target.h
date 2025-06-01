// created by Camilo on 2025-05-31 22:46 <3ThomasBorregaardSorensen!!
#pragma once


#include "aura/graphics/image/buffer.h"
#include "aura/graphics/image/lock.h"


namespace image
{


   class CLASS_DECL_AURA target :
      virtual public ::particle
   {
   public:


      ::image::image_pointer							m_pimage;
      ::particle_pointer                        m_pparticleSynchronization;
      ::procedure                               m_callback;
      ::image::buffer                           m_imagebuffer;


      target();
      ~target() override;


      void on_initialize_particle() override;


      virtual void _001OnDraw(::draw2d::graphics_pointer& pgraphics);

      virtual void set_size(const ::int_size & size);
      
      virtual void set_image_pixels(const ::image32_t* pimage32, int w, int h, int stride);

      virtual void on_image_pixels();

      virtual ::image::lock no_padded_lock(::image::enum_copy_disposition ecopydisposition);
      virtual ::image::lock source_scan_lock(::image::enum_copy_disposition ecopydisposition);


   };


} // namespace image



