// created by Camilo on 2025-05-31 22:51 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "image.h"
#include "context.h"
#include "drawing.h"
#include "target.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"


namespace image
{


   target::target()
   {

   }


   target::~target()
   {

   }


   void target::on_initialize_particle()
   {

      m_pparticleSynchronization = node()->create_mutex();

      __øconstruct(m_pimage);

   }


   void target::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (::is_ok(m_pimage))
      {

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         _synchronous_lock synchronouslock(m_pparticleSynchronization);

         ::image::image_source imagesource(m_pimage, m_pimage->rectangle());

         ::image::image_drawing_options imagedrawingoptions(m_pimage->rectangle());

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->draw(imagedrawing);

      }

   }


   void target::set_size(const ::int_size& size)
   {

      _synchronous_lock synchronouslock(m_pparticleSynchronization);

      m_pimage->create(size);

   }


   void target::set_image_pixels(const ::image32_t* pimage32, int w, int h, int stride)
   {

      ::int_size s(w, h);

      _synchronous_lock synchronouslock(m_pparticleSynchronization);

      m_pimage->create(s);

      m_pimage->image32()->vertical_swap_copy(s, m_pimage->m_iScan, pimage32, stride);

      //}

      ////   for (int y = 0; y < h; y++)
      ////   {

      ////      auto p = (unsigned char*)(m_pimage->image32() + (y * m_pimage->m_iScan) / 4);

      ////      for (int x = 0; x < w; x++)
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

      on_image_pixels();

   }


   void target::on_image_pixels()
   {

      if (m_callback)
      {

         m_callback();

      }

   }


   ::image::lock target::no_padded_lock()
   {

      return m_imagebuffer.no_padding_lock(m_pimage);

   }


   //void target::unlock(const ::pixmap* ppixmap)
   //{

   //   m_imagebuffer.unlock(ppixmap);

   //}


} // namespace image



