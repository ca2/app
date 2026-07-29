// created by Camilo on 2025-05-31 22:51 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "image.h"
#include "context.h"
#include "drawing.h"
#include "aaa_target.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "aura/graphics/draw2d/graphics_pointer.h"


namespace image
{


   aaa_target::aaa_target()
   {

   }


   aaa_target::~aaa_target()
   {

   }


   void aaa_target::on_initialize_particle()
   {

      m_pparticleSynchronization = node()->create_mutex();

      constructø(m_pimage);

   }


   void aaa_target::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (::is_ok(m_pimage))
      {

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         _synchronous_lock synchronouslock(m_pparticleSynchronization, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         ::image::image_source imagesource(m_pimage, m_pimage->rectangle());

         ::image::image_drawing_options imagedrawingoptions(m_pimage->rectangle());

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->draw(imagedrawing);

      }

   }


   void aaa_target::set_size(const ::i32_size& size)
   {

      _synchronous_lock synchronouslock(m_pparticleSynchronization, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      m_pimage->create_as_descriptor(size);

   }


   void aaa_target::set_image_pixels(const ::image32_t* pimage32, ::i32 w, ::i32 h, ::i32 stride, bool bYSwap)
   {

      ::i32_size s(w, h);

      {

         _synchronous_lock synchronouslock(m_pparticleSynchronization, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         m_pimage->create_as_descriptor(s);

         if (bYSwap)
         {

            m_pimage->image32()->vertical_swap_copy(s, m_pimage->m_iScan, pimage32, stride);
            //m_pimage->fill_rectangle({100, 100, 200, 200}, argb(0.5, 0.5, 0.75, 0.95));
         }
         else
         {

            m_pimage->image32()->copy(s, m_pimage->m_iScan, pimage32, stride);

         }


         //}

         ////   for (::i32 y = 0; y < h; y++)
         ////   {

         ////      auto p = (::u8*)(m_pimage->image32() + (y * m_pimage->m_iScan) / 4);

         ////      for (::i32 x = 0; x < w; x++)
         ////      {

         ////         //p[0] = p[0] * p[3] / 255;
         ////         //p[1] = p[1] * p[3] / 255;
         ////         //p[2] = p[2] * p[3] / 255;

         ////         auto r = p[0];
         ////         auto g = p[1];
         ////         auto b = p[2];
         ////         auto a = p[3];
         ////         //p[0] = b;
         ////         //p[2] = r;
         ////         //p[3] = 255;

         ////         /*         if (r > a)
         ////                  {

         ////                     information("What a red!!"_ansi);

         ////                  }

         ////                  if (g > a)
         ////                  {

         ////                     information("What a green!!"_ansi);

         ////                  }

         ////                  if (b > a)
         ////                  {

         ////                     information("What a blue!!"_ansi);

         ////                  }*/

         ////         p += 4;

         ////      }

         ////   }

         ////}

         //m_pimpact->set_need_redraw();

         //m_pimpact->post_redraw();

      }

      on_image_pixels();

   }


   void aaa_target::do_target()
   {

      m_imagebuffer.unlock();

      set_image_pixels(
         m_imagebuffer.data(),
         m_imagebuffer.width(),
         m_imagebuffer.height(),
         m_imagebuffer.scan_size(),
         (m_imagebuffer.m_ecopydisposition & e_copy_disposition_y_swap) != 0);

   }


   void aaa_target::on_image_pixels()
   {

      if (m_callbackOnImagePixels)
      {

         m_callbackOnImagePixels();

      }

   }


   ::image::aaa_lock aaa_target::no_padded_lock(::image::enum_copy_disposition ecopydisposition)
   {

      return m_imagebuffer.no_padding_lock(ecopydisposition, m_pimage);

   }


   ::image::aaa_lock aaa_target::source_scan_lock(::image::enum_copy_disposition ecopydisposition)
   {

      return m_imagebuffer.source_lock(ecopydisposition, m_pimage);

   }


   ::image::aaa_targeting aaa_target::no_padded_targeting(::image::enum_copy_disposition ecopydisposition)
   {

      m_imagebuffer.no_padding_lock(ecopydisposition, m_pimage);

      return this;

   }


   ::image::aaa_targeting aaa_target::source_scan_targeting(::image::enum_copy_disposition ecopydisposition)
   {

      m_imagebuffer.source_lock(ecopydisposition, m_pimage);

      return this;

   }


   //void aaa_target::unlock(const ::pixmap* ppixmap)
   //{

   //   m_imagebuffer.unlock(ppixmap);

   //}


   aaa_targeting::aaa_targeting(::image::aaa_target* pimagetarget)
   {

      m_pimagetarget = pimagetarget;

   }


   aaa_targeting::~aaa_targeting()
   {

      m_pimagetarget->do_target();

   }


   ::i32 aaa_targeting::width() const
   {

      return m_pimagetarget->m_imagebuffer.width();

   }


   ::i32 aaa_targeting::height() const
   {

      return m_pimagetarget->m_imagebuffer.height();

   }


   ::i32 aaa_targeting::scan() const
   {

      return m_pimagetarget->m_imagebuffer.scan_size();

   }


   image32_t* aaa_targeting::data()
   {

      return m_pimagetarget->m_imagebuffer.data();

   }




} // namespace image



