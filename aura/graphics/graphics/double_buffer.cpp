#include "framework.h"
#include "double_buffer.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "aura/graphics/image/image.h"
#include "aura/windowing/window.h"


namespace graphics
{


   double_buffer::double_buffer()
   {

      m_iCurrentBuffer = 0;
      //m_bSingleBufferMode = true;
      //m_bSingleBufferMode = false;

   }


   double_buffer::~double_buffer()
   {

   }


   void double_buffer::initialize_graphics_graphics(::windowing::window * pwindow)
   {

      //auto estatus = 

      graphics::initialize_graphics_graphics(pwindow);

      //if (!estatus)
      //{

      //   return estatus;

      //}
      m_bufferitema.set_size(2);

      __construct_new(m_bufferitema[0]);
      __øconstruct(m_bufferitema[0]->m_pimage2);
      __øconstruct(m_bufferitema[0]->m_pmutex);
      m_bufferitema[0]->m_pimage2->id() = 0;

      __construct_new(m_bufferitema[1]);
      __øconstruct(m_bufferitema[1]->m_pimage2);
      __øconstruct(m_bufferitema[1]->m_pmutex);
      m_bufferitema[1]->m_pimage2->id() = 1;

      //return estatus;

   }


   bool double_buffer::is_single_buffer_mode() const
   {

      return true;

   }


   //::particle * double_buffer::get_draw_lock()
   //{

   //   return get_buffer_item()->m_pmutex;

   //}


   bool double_buffer::_on_begin_draw(buffer_item * pitem)
   {

      //auto pitem = get_buffer_item();

      //buffer_size_and_position(pitem);

      //if (pitem->m_size.is_empty())
      //{

      //   if (egraphics & e_graphics_layout)
      //   {

      //      pitem->m_size = { 512, 256 };

      //   }
      //   else
      //   {

      //      information() << "window size is zero in begin draw!!";

      //      return nullptr;

      //   }

      //}

      if (!m_bDibIsHostingBuffer)
      {

         auto & pimage = pitem->m_pimage2;

         auto sizeImage = pimage->is_ok() ? pimage->get_size() : ::int_size(0, 0);

         auto sizeReserved = ::int_size(1920, 1080);

         if (pitem->m_sizeBufferItemDraw.cx() > sizeImage.cx())
         {

            sizeImage.cx() = pitem->m_sizeBufferItemDraw.cx();

         }

         if (pitem->m_sizeBufferItemDraw.cy() > sizeImage.cy())
         {

            sizeImage.cy() = pitem->m_sizeBufferItemDraw.cy();

         }

         if (sizeReserved.cx() > sizeImage.cx())
         {

            sizeImage.cx() = sizeReserved.cx();

         }

         if (sizeReserved.cy() > sizeImage.cy())
         {

            sizeImage.cy() = sizeReserved.cy();

         }

         debug() << "double_buffer::_on_begin_draw Going to create image : " << sizeImage;

         pimage->create(sizeImage);

         if (pimage.nok())
         {

            information() << "double_buffer::_on_begin_draw Image Nok : " << sizeImage;

            return false;

         }

         debug() << "double_buffer::_on_begin_draw Deferred image Creation/Update : " << sizeImage;

         auto pgraphics = pimage->g();

         if (pgraphics)
         {

            pgraphics->resize(pitem->m_sizeBufferItemDraw);

         }

      }

      //return pitem;

      return true;

   }


   buffer_item * double_buffer::get_buffer_item()
   {

      return m_bufferitema[get_buffer_index()];

   }


   //::image::image_pointer & double_buffer::get_buffer_image()
   //{

   //   return get_buffer_item()->m_pimage;

   //}


   //::particle * double_buffer::get_buffer_sync()
   //{

   //   return get_buffer_item()->m_pparticleSynchronization;

   //}


   buffer_item * double_buffer::get_screen_item()
   {

      return m_bufferitema[get_screen_index()];

   }


   //::image::image_pointer & double_buffer::get_screen_image()
   //{

   //   return get_screen_item()->m_pimage;

   //}


   //::particle * double_buffer::get_screen_sync()
   //{

   //   return get_screen_item()->m_pmutex;

   //}


   ::collection::index double_buffer::get_buffer_index() const
   {

      if (is_single_buffer_mode())
      {

         return 0;

      }
      else if (m_iCurrentBuffer == 0)
      {

         return 0;

      }
      else
      {

         return 1;

      }

   }


   ::collection::index double_buffer::get_screen_index() const
   {

      if (is_single_buffer_mode())
      {

         return 0;

      }
      else if (m_iCurrentBuffer == 0)
      {

         return 1;

      }
      else
      {

         return 0;

      }

   }



   bool double_buffer::buffer_lock_round_swap_key_buffers()
   {

      if (is_single_buffer_mode())
      {

         auto pbufferitem = get_buffer_item();

         if (pbufferitem)
         {

            if (pbufferitem->m_pimage2)
            {

               if (pbufferitem->m_pimage2->m_pgraphics)
               {

                  pbufferitem->m_pimage2->m_pgraphics->on_end_draw(m_pwindow->oswindow());

               }

               pbufferitem->m_pointBufferItemWindow = pbufferitem->m_pointBufferItemDraw;

               pbufferitem->m_sizeBufferItemWindow = pbufferitem->m_sizeBufferItemDraw;

            }

         }

         m_iCurrentBuffer = 0;

         return true;

      }

      _synchronous_lock sl(this->synchronization());

      _synchronous_lock slBuffer(get_buffer_item()->m_pmutex);

      _synchronous_lock slScreen(get_screen_item()->m_pmutex);

      if (m_iCurrentBuffer == 0)
      {

         m_iCurrentBuffer = 1;

         //informationf("buffer_lock_round_swap_key_buffers (1)\n");

      }
      else
      {

         m_iCurrentBuffer = 0;

         //informationf("buffer_lock_round_swap_key_buffers (0)\n");

      }

      if(!is_single_buffer_mode())
      {

         auto pscreenitem = get_screen_item();

         auto pimageNewScreen = pscreenitem->m_pimage2;

         auto pimageNewBuffer = get_buffer_item()->m_pimage2;

         if (pimageNewBuffer->size() == pimageNewScreen->size())
         {

            pimageNewBuffer->copy_from_no_create(pimageNewScreen);

         }

         pscreenitem->m_pointBufferItemWindow = pscreenitem->m_pointBufferItemDraw;

         pscreenitem->m_sizeBufferItemWindow = pscreenitem->m_sizeBufferItemDraw;

      }

      //      m_pimpl->m_puserinteraction->payload("bQueuedPostRedraw") = false;

            //if (get_buffer_image()->is_ok())
            //{

            //   get_buffer_image()->fill(0);

            //}

      //      int debug = 1;
      //
      //      if (debug)
      //      {
      //
      //         auto pimageScreen = get_screen_image();
      //
      //         if(::is_null(pimageScreen))
      //         {
      //
      //            return false;
      //
      //         }
      //
      //         pimageScreen->map();
      //
      //         auto pdata = pimageScreen->get_data();
      //
      //         unsigned char * p = (unsigned char *)pdata;
      //
      //         unsigned char r = p[0];
      //
      //         unsigned char g = p[1];
      //
      //         unsigned char b = p[2];
      //
      //         unsigned char a = p[3];
      //
      //         //informationf("argb " +as_string(r) + "," + as_string(g) + "," +as_string(b) + "," + as_string(a));
      //
      //      }

      return true;

   }


   void double_buffer::update_screen()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto pitemScreen = get_screen_item();

      _synchronous_lock synchronouslockScreen(pitemScreen->m_pmutex);

      synchronouslock.unlock();

      on_update_screen(pitemScreen);

   }


   void double_buffer::destroy_buffer()
   {

      graphics::graphics::destroy_buffer();
      //m_bufferitema[0].defer_destroy();
      //m_bufferitema[1].defer_destroy();

   }


} // namespace graphics



