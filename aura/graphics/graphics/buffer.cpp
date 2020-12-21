#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif
#include "aura/graphics/graphics/buffer.h"


namespace graphics
{


   buffer::buffer()
   {

   }


   buffer::~buffer()
   {

      destroy_buffer();

      //destroy_os_buffer();

   }


   bool buffer::update_window()
   {

      sync_lock sl(mutex());

      return update_window(m_pimageBuffer);

   }


   bool buffer::update_window(::image * pimage)
   {

      UNREFERENCED_PARAMETER(pimage);

      return false;

   }


   ::image_pointer & buffer::get_buffer()
   {

      return m_pimageBuffer;

   }


   bool buffer::is_buffer_ok()
   {

      return m_pimageBuffer->is_set();

   }


   void buffer::destroy_buffer()
   {

      m_pimageBuffer->destroy();

   }



   bool buffer::update_buffer(const ::size & size, int iScan)
   {

      if (!m_pimageBuffer->create(size))
      {

         return false;

      }

      return true;

   }


   ::image_pointer & buffer::get_screen_image()
   {

      return m_pimageBuffer;

   }


   sync * buffer::get_screen_sync()
   {

      return mutex();

   }


   ::sync * buffer::get_draw_lock()
   {

      return mutex();

   }


   ::draw2d::graphics * buffer::on_begin_draw()
   {

      auto sizeWindow = window_size();

      ///if (buffer_size() != sizeWindow)
      {

         string strType = m_pimpl->m_puserinteraction->type_name();

         if (strType.contains("combo_list"))
         {

            output_debug_string("combo_list");

         }


         if (!update_buffer(sizeWindow))
         {

            return nullptr;

         }

         if (!m_pimpl->m_puserinteraction)
         {

            return nullptr;

         }

         //ASSERT(buffer_size() == sizeWindow);

         //if (m_pimpl->m_puserinteraction->m_ewindowflag & window_flag_ipc_copy)
         //{

         //   defer_initialize_ipc_copy();

         //}

      }

      return m_pimageBuffer->g();

   }


   bool buffer::buffer_lock_round_swap_key_buffers()
   {

      return true;

   }


} // namespace graphics



