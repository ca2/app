#include "framework.h"
#include "_.h"
#include "_graphics.h"
#include "aura/graphics/draw2d/image.h"


namespace graphics
{


   double_buffer::double_buffer()
   {

      m_iCurrentBuffer = 0;

   }


   double_buffer::~double_buffer()
   {

   }


   void double_buffer::initialize_graphics_graphics(::user::interaction_impl * pimpl)
   {

      auto estatus = graphics::initialize_graphics_graphics(pimpl);

      if (!estatus)
      {

         return estatus;

      }

      __construct(m_imageaBuffer[0]);
      //m_imageaBuffer[0]->defer_create_mutex();
      m_imageaBuffer[0]->m_id = 0;

      __construct(m_imageaBuffer[1]);
      //m_imageaBuffer[1]->defer_create_mutex();
      m_imageaBuffer[1]->m_id = 1;

      return estatus;

   }


   synchronization_object * double_buffer::get_draw_lock()
   {

      return get_buffer_sync();

   }


   ::draw2d::graphics * double_buffer::on_begin_draw()
   {

      auto & pimage = get_buffer_image();

      auto sizeWindow = window_size();

      //if (pimage->size() != sizeWindow)
      {
         
//         if(pimage->size().area() < sizeWindow.area())
//         {
//
//            ::size_i32 sizeImage(1920, 1080);
//
//            if(sizeWindow.area() > sizeImage.area())
//            {
//
//               sizeImage = sizeWindow;
//
//            }
//
            if (!pimage->create(sizeWindow))
            {

               return nullptr;

            }
            
//         }
//
//         if(pimage->size().area() > sizeWindow.area())
//         {
//
//            pimage->map();
//
//            pimage->m_iScan = sizeWindow.width() * sizeof(::color32_t);
//
//            pimage->m_size = sizeWindow;
//
//         }
//
      }

      if (!pimage)
      {

         return nullptr;

      }

      return pimage->g();

   }


   ::image_pointer & double_buffer::get_buffer_image()
   {

      return m_imageaBuffer[get_buffer_index()];

   }


   synchronization_object * double_buffer::get_buffer_sync()
   {

      return &m_mutexa[get_buffer_index()];

   }


   ::image_pointer & double_buffer::get_screen_image()
   {

      return m_imageaBuffer[get_screen_index()];

   }


   synchronization_object * double_buffer::get_screen_sync()
   {

      return &m_mutexa[get_screen_index()];

   }

   
   ::index double_buffer::get_buffer_index() const
   {

      if (m_iCurrentBuffer == 0)
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

      if (m_iCurrentBuffer == 0)
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

      synchronous_lock slScreen(get_screen_sync());

      if (m_iCurrentBuffer == 0)
      {

         m_iCurrentBuffer = 1;

      }
      else
      {

         m_iCurrentBuffer = 0;

      }

      //if (get_buffer_image()->is_ok())
      //{

      //   get_buffer_image()->fill(0);

      //}

      int debug = 1;

      if (debug)
      {

         auto pimageScreen = get_screen_image();

         if(::is_null(pimageScreen))
         {

            return false;

         }

         pimageScreen->map();

         auto pdata = pimageScreen->get_data();

         byte * p = (byte *)pdata;

         byte r = p[0];

         byte g = p[1];

         byte b = p[2];

         byte a = p[3];

         //::output_debug_string("argb " +__string(r) + "," + __string(g) + "," +__string(b) + "," + __string(a));

      }

      return true;

   }



   bool double_buffer::update_window()
   {

      synchronous_lock synchronouslock(mutex());

      synchronous_lock slScreen(get_screen_sync());

      auto pimage = get_screen_image();

      synchronouslock.unlock();

      if (!::is_ok(pimage))
      {

         return false;

      }

      return update_window(pimage);

   }


   void double_buffer::destroy_buffer()
   {
      
      m_imageaBuffer[0].release();
      m_imageaBuffer[1].release();

   }


} // namespace graphics



