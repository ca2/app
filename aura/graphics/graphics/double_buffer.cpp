#include "framework.h"
#include "double_buffer.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/graphics/image/image.h"


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


   void double_buffer::initialize_graphics_graphics(::user::interaction_impl * pimpl)
   {

      //auto estatus = 

      graphics::initialize_graphics_graphics(pimpl);

      //if (!estatus)
      //{

      //   return estatus;

      //}
      m_bufferitema.set_size(2);

      __construct_new(m_bufferitema[0]);
      __construct(m_bufferitema[0]->m_pimage);
      __construct(m_bufferitema[0]->m_pmutex);
      m_bufferitema[0]->m_pimage->m_atom = 0;

      __construct_new(m_bufferitema[1]);
      __construct(m_bufferitema[1]->m_pimage);
      __construct(m_bufferitema[1]->m_pmutex);
      m_bufferitema[1]->m_pimage->m_atom = 1;

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


   buffer_item * double_buffer::on_begin_draw()
   {

      auto pitem = get_buffer_item();

      buffer_size_and_position(pitem);

      if (!m_bDibIsHostingBuffer)
      {

         auto & pimage = pitem->m_pimage;

         auto sizeImage = pimage->is_ok() ? pimage->get_size() : ::size_i32(0, 0);

         auto sizeReserved = ::size_i32(1920, 1080);

         if (pitem->m_size.cx() > sizeImage.cx())
         {

            sizeImage.cx() = pitem->m_size.cx();

         }

         if (pitem->m_size.cy() > sizeImage.cy())
         {

            sizeImage.cy() = pitem->m_size.cy();

         }

         if (sizeReserved.cx() > sizeImage.cx())
         {

            sizeImage.cx() = sizeReserved.cx();

         }

         if (sizeReserved.cy() > sizeImage.cy())
         {

            sizeImage.cy() = sizeReserved.cy();

         }

         pimage->create(sizeImage);

         if (pimage.nok())
         {

            return nullptr;

         }

         auto pgraphics = pimage->g();

         if (pgraphics)
         {

            pgraphics->resize(pitem->m_size);

         }

      }

      return pitem;

   }


   buffer_item * double_buffer::get_buffer_item()
   {

      return m_bufferitema[get_buffer_index()];

   }


   //::image_pointer & double_buffer::get_buffer_image()
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


   //::image_pointer & double_buffer::get_screen_image()
   //{

   //   return get_screen_item()->m_pimage;

   //}


   //::particle * double_buffer::get_screen_sync()
   //{

   //   return get_screen_item()->m_pmutex;

   //}


   ::index double_buffer::get_buffer_index() const
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


   ::index double_buffer::get_screen_index() const
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

         m_iCurrentBuffer = 0;

         return true;

      }

      _synchronous_lock sl(this->synchronization());

      _synchronous_lock slBuffer(get_buffer_item()->m_pmutex);

      _synchronous_lock slScreen(get_screen_item()->m_pmutex);

      if (m_iCurrentBuffer == 0)
      {

         m_iCurrentBuffer = 1;

         //output_debug_string("buffer_lock_round_swap_key_buffers (1)\n");

      }
      else
      {

         m_iCurrentBuffer = 0;

         //output_debug_string("buffer_lock_round_swap_key_buffers (0)\n");

      }

      if(!is_single_buffer_mode())
      {

         auto pimageNewScreen = get_screen_item()->m_pimage;

         auto pimageNewBuffer = get_buffer_item()->m_pimage;

         if (pimageNewBuffer->size() == pimageNewScreen->size())
         {

            pimageNewBuffer->copy_from_no_create(pimageNewScreen);

         }

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
      //         //::output_debug_string("argb " +as_string(r) + "," + as_string(g) + "," +as_string(b) + "," + as_string(a));
      //
      //      }

      return true;

   }



   bool double_buffer::update_screen()
   {

      synchronous_lock synchronouslock(this->synchronization());

      auto pitemScreen = get_screen_item();

      synchronous_lock synchronouslockScreen(pitemScreen->m_pmutex);

      synchronouslock.unlock();

      return on_update_screen(pitemScreen);

   }


   void double_buffer::destroy_buffer()
   {

      m_bufferitema[0]->m_pimage.release();
      m_bufferitema[1]->m_pimage.release();

   }


} // namespace graphics



