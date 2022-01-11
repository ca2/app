#include "framework.h"
#include "aura/user/_user.h"
#include "_.h"
#include "_graphics.h"


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

      synchronous_lock synchronouslock(mutex());

      auto bOk = update_window(m_pimageBuffer);

      ipc_copy(m_pimageBuffer);

      return bOk;

   }


   bool buffer::update_window(::image * pimage)
   {

      __UNREFERENCED_PARAMETER(pimage);

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


   ::size_i32 buffer::buffer_size()
   {

      return m_pimageBuffer->get_size();

   }


   bool buffer::update_buffer(const ::size_i32 & size, int iScan)
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


   synchronization_object * buffer::get_screen_sync()
   {

      return mutex();

   }


   ::synchronization_object * buffer::get_draw_lock()
   {

      return mutex();

   }


   ::draw2d::graphics * buffer::on_begin_draw()
   {

      auto sizeWindow = window_size();

      ///if (buffer_size() != sizeWindow)
      {

         string strType = __type_name(m_pimpl->m_puserinteraction);

         if (strType.contains("list_box"))
         {

            output_debug_string("list_box");

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



