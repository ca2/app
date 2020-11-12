#include "framework.h"


namespace graphics
{


   double_buffer::double_buffer()
   {

      m_iCurrentBuffer = 0;

   }


   double_buffer::~double_buffer()
   {

   }


   ::estatus double_buffer::initialize_graphics_graphics(::user::interaction_impl * pimpl)
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


   sync * double_buffer::get_draw_lock()
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
//            ::size sizeImage(1920, 1080);
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
//            pimage->m_iScan = sizeWindow.width() * sizeof(color32_t);
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

      return m_imageaBuffer[m_iCurrentBuffer];

   }


   sync * double_buffer::get_buffer_sync()
   {

      return &m_mutexa[m_iCurrentBuffer];

   }


   ::image_pointer & double_buffer::get_screen_image()
   {

      return m_imageaBuffer[!m_iCurrentBuffer];

   }


   sync * double_buffer::get_screen_sync()
   {

      return &m_mutexa[!m_iCurrentBuffer];

   }


   bool double_buffer::round_swap_key_buffers()
   {

      sync_lock slBuffer(get_buffer_sync());

      sync_lock slScreen(get_screen_sync());

      get_buffer_image()->map();

      m_iCurrentBuffer = !m_iCurrentBuffer;

      if (get_buffer_image()->is_ok())
      {

         get_buffer_image()->fill(0);

      }

      return true;

   }



   bool double_buffer::update_window()
   {

      sync_lock sl(mutex());

      sync_lock slScreen(get_screen_sync());

      auto pimage = get_screen_image();

      sl.unlock();

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



