#include "framework.h"
#include "_.h"
#include "_graphics.h"
#include "aura/graphics/image/image.h"


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

      //auto estatus = 
      
      graphics::initialize_graphics_graphics(pimpl);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      __construct(m_imageaBuffer[0]);
      //m_imageaBuffer[0]->defer_create_mutex();
      m_imageaBuffer[0]->m_atom = 0;

      __construct(m_imageaBuffer[1]);
      //m_imageaBuffer[1]->defer_create_mutex();
      m_imageaBuffer[1]->m_atom = 1;

      //return estatus;

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
//

//         if(sizeWindow.cx == 1)
//         {
//
//            printf("cx=1");
//
//         }
//         else
//         {
//            printf("cx!=1");
//
//         }
          
          auto sizeImage = ::is_ok(pimage)?pimage->get_size() : ::size_i32(0,0);
         auto sizeReserved = ::size_i32(1920, 1080);
          
          if(sizeWindow.cx > sizeImage.cx)
          {
              sizeImage.cx = sizeWindow.cx;
              
          }
          if(sizeWindow.cy > sizeImage.cy)
          {
              sizeImage.cy = sizeWindow.cy;
              
          }
          if(sizeReserved.cx > sizeImage.cx)
          {
              sizeImage.cx = sizeReserved.cx;
              
          }
          if(sizeReserved.cy > sizeImage.cy)
          {
              sizeImage.cy = sizeReserved.cy;
              
          }


          //pimage->create(sizeWindow);
          // 
           pimage->create(sizeImage);
            //if (!pimage->create(sizeWindow))
            //{

            //   return nullptr;

            //}
            
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

      _synchronous_lock slBuffer(get_buffer_sync());
      
      _synchronous_lock slScreen(get_screen_sync());

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
//         byte * p = (byte *)pdata;
//
//         byte r = p[0];
//
//         byte g = p[1];
//
//         byte b = p[2];
//
//         byte a = p[3];
//
//         //::output_debug_string("argb " +__string(r) + "," + __string(g) + "," +__string(b) + "," + __string(a));
//
//      }

      return true;

   }



   bool double_buffer::update_screen()
   {

      synchronous_lock synchronouslock(mutex());

      synchronous_lock slScreen(get_screen_sync());

      auto pimage = get_screen_image();

      synchronouslock.unlock();

      if (!::is_ok(pimage))
      {

         return false;

      }

      return update_screen(pimage);

   }


   void double_buffer::destroy_buffer()
   {
      
      m_imageaBuffer[0].release();
      m_imageaBuffer[1].release();

   }


} // namespace graphics



