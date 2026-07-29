// created by Camilo on 2025-05-31 22:46 <3ThomasBorregaardSorensen!!
#pragma once


#include "aura/graphics/image/aaa_buffer.h"
#include "aura/graphics/image/aaa_lock.h"


namespace image
{


   class CLASS_DECL_AURA aaa_targeting
   {
   public:


      ::image::aaa_target* m_pimagetarget;


      aaa_targeting(::image::aaa_target* pimagetarget);

      ~aaa_targeting();

      ::i32 width() const;

      ::i32 height() const;

      ::i32 scan() const;

      image32_t* data();


   };





   class CLASS_DECL_AURA aaa_target :
      virtual public ::particle
   {
   public:


      ::image::image_pointer							m_pimage;
      ::particle_pointer                        m_pparticleSynchronization;
      ::procedure                               m_callbackOnImagePixels;
      ::image::aaa_buffer                       m_imagebuffer;


      aaa_target();
      ~aaa_target() override;


      void on_initialize_particle() override;


      virtual void _001OnDraw(::draw2d::graphics_pointer& pgraphics);

      virtual void set_size(const ::i32_size & size);
      
      virtual void set_image_pixels(const ::image32_t* pimage32, ::i32 w, ::i32 h, ::i32 stride, bool bYSwap);

      virtual void on_image_pixels();

      virtual void do_target();


      virtual ::image::aaa_lock no_padded_lock(::image::enum_copy_disposition ecopydisposition);
      virtual ::image::aaa_lock source_scan_lock(::image::enum_copy_disposition ecopydisposition);


      virtual ::image::aaa_targeting no_padded_targeting(::image::enum_copy_disposition ecopydisposition);
      virtual ::image::aaa_targeting source_scan_targeting(::image::enum_copy_disposition ecopydisposition);


   };


   //class CLASS_DECL_AURA aaa_targeting
   //{
   //public:


      //::image::aaa_target* m_pimagetarget;


   
} // namespace image



