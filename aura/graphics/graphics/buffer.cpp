#include "framework.h"
#include "buffer.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/graphics/image/image.h"
#include "aura/user/user/interaction_impl.h"
#include "aura/user/user/interaction.h"


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


   bool buffer::update_screen()
   {

      synchronous_lock synchronouslock(this->synchronization());

      auto bOk = on_update_screen(get_screen_item());
      // 
      // 
      // 
  //    bool bOk = false;
//
      ipc_copy(m_pimageBuffer);

      return bOk;

   }


   //bool buffer::update_screen(buffer_item * pitem)
   //{

   //   UNREFERENCED_PARAMETER(pitem);

   //   return false;

   //}


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


   bool buffer::update_buffer(buffer_item * pitem)
   {

      //auto pitem = get_buffer_item();

      try
      {

         m_pimageBuffer->create(pitem->m_size);

      }
      catch (...)
      {

         return false;

      }

      return true;

      //if (!m_pimageBuffer->create(size))
      //{

      //   return false;

      //}

      //return true;

   }


   //::image_pointer & buffer::get_screen_image()
   //{

   //   return m_pimageBuffer;

   //}


   //::particle * buffer::get_screen_sync()
   //{

   //   return synchronization();

   //}


   //::particle * buffer::get_draw_lock()
   //{

   //   return synchronization();

   //}


   ::graphics::buffer_item * buffer::on_begin_draw()
   {

      auto pitem = get_buffer_item();

      buffer_size_and_position(pitem);

      update_buffer(pitem);

      return pitem;

   }


   bool buffer::buffer_lock_round_swap_key_buffers()
   {

      return true;

   }


} // namespace graphics



