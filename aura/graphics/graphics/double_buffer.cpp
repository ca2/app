#include "framework.h"
#include "double_buffer.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/application.h"
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

      construct_newø(m_bufferitema[0]);
      constructø(m_bufferitema[0]->m_pimageBufferItem);
      constructø(m_bufferitema[0]->m_pmutex);
      m_bufferitema[0]->m_pimageBufferItem->id() = 0;

      construct_newø(m_bufferitema[1]);
      constructø(m_bufferitema[1]->m_pimageBufferItem);
      constructø(m_bufferitema[1]->m_pmutex);
      m_bufferitema[1]->m_pimageBufferItem->id() = 1;

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


   void double_buffer::_on_configure_window(buffer_item * pbufferitem)
   {


   }


   bool double_buffer::_on_begin(buffer_item * pbufferitem)
   {

      //auto pbufferitem = get_buffer_item();

      //buffer_size_and_position(pbufferitem);

      //if (pbufferitem->m_size.is_empty())
      //{

      //   if (egraphics & e_graphics_layout)
      //   {

      //      pbufferitem->m_size = { 512, 256 };

      //   }
      //   else
      //   {

      //      information() << "window size is zero in begin draw!!";

      //      return nullptr;

      //   }

      //}

      if (!m_bDibIsHostingBuffer)
      {

         auto & pimageBufferItem = pbufferitem->m_pimageBufferItem;

         auto sizeImage = pimageBufferItem->is_ok() ? pimageBufferItem->get_size() : ::i32_size(0, 0);

         auto sizeReserved = ::i32_size(1920, 1080);

         if (pbufferitem->m_sizeBufferItem.cx > sizeImage.cx)
         {

            sizeImage.cx = pbufferitem->m_sizeBufferItem.cx;

         }

         if (pbufferitem->m_sizeBufferItem.cy > sizeImage.cy)
         {

            sizeImage.cy = pbufferitem->m_sizeBufferItem.cy;

         }

         if (sizeReserved.cx > sizeImage.cx)
         {

            sizeImage.cx = sizeReserved.cx;

         }

         if (sizeReserved.cy > sizeImage.cy)
         {

            sizeImage.cy = sizeReserved.cy;

         }

         debug() << "double_buffer::_on_begin_draw Going to create image : " << sizeImage;

         pimageBufferItem->create(sizeImage);

         if (pimageBufferItem.nok())
         {

            information() << "double_buffer::_on_begin_draw Image Nok : " << sizeImage;

            return false;

         }

         debug() << "double_buffer::_on_begin_draw Deferred image Creation/Update : " << sizeImage;

         auto pgraphicsBufferItem = pimageBufferItem->acquire_graphics();
         
         if (pgraphicsBufferItem)
         {

            //pbufferitem->m_pgraphics = pgraphics;
            
            pgraphicsBufferItem->resize(pbufferitem->m_sizeBufferItem);

         }
         
      }

      //return pbufferitem;

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



   bool double_buffer::buffer_lock_round_swap_key_buffers(::draw2d::graphics_pointer &pgraphics)
   {

      if (is_single_buffer_mode())
      {

         auto pbufferitem = get_buffer_item();

         if (pbufferitem)
         {

            if (pbufferitem->m_pimageBufferItem)
            {

               //auto pgraphics = pbufferitem->acquire_graphics();

               if (pgraphics)
               {

                  pgraphics->on_end_draw(m_pwindow);

               }

               pbufferitem->m_pointBufferItemWindow = pbufferitem->m_pointBufferItem;

               pbufferitem->m_sizeBufferItemWindow = pbufferitem->m_sizeBufferItem;

            }

         }

         m_iCurrentBuffer = 0;

         return true;

      }

      _synchronous_lock sl(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      _synchronous_lock slBuffer(get_buffer_item()->m_pmutex, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      _synchronous_lock slScreen(get_screen_item()->m_pmutex, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

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

         auto pimageNewScreen = pscreenitem->m_pimageBufferItem;

         auto pimageNewBuffer = get_buffer_item()->m_pimageBufferItem;

         if (pimageNewBuffer->size() == pimageNewScreen->size())
         {

            pimageNewBuffer->copy_from_no_create(pimageNewScreen);

         }

         pscreenitem->m_pointBufferItemWindow = pscreenitem->m_pointBufferItem;

         pscreenitem->m_sizeBufferItemWindow = pscreenitem->m_sizeBufferItem;

      }

      //      m_pimpl->m_puserinteraction->payload("bQueuedPostRedraw") = false;

            //if (get_buffer_image()->is_ok())
            //{

            //   get_buffer_image()->fill(0);

            //}

      //      ::i32 debug = 1;
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
      //         ::u8 * p = (::u8 *)pdata;
      //
      //         ::u8 r = p[0];
      //
      //         ::u8 g = p[1];
      //
      //         ::u8 b = p[2];
      //
      //         ::u8 a = p[3];
      //
      //         //informationf("argb " +as_string(r) + "," + as_string(g) + "," +as_string(b) + "," + as_string(a));
      //
      //      }

      return true;

   }


   void double_buffer::update_screen()
   {

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto pitemScreen = get_screen_item();

      _synchronous_lock synchronouslockScreen(pitemScreen->m_pmutex, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      synchronouslock.unlock();

      if (!pitemScreen->m_pimageBufferItem.ok())
      {

         if (!m_papplication->m_gpu.m_bUseSwapChainWindow)
         {

            warning() << "pitemScreen->m_pimage2 not ok!";

         }

         _on_configure_window(pitemScreen);

         return;

      }

      on_update_screen(pitemScreen);

   }


   void double_buffer::destroy_buffer()
   {

      graphics::graphics::destroy_buffer();
      //m_bufferitema[0].defer_destroy();
      //m_bufferitema[1].defer_destroy();

   }


} // namespace graphics



