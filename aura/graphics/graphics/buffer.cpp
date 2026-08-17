#include "platform.h"
#include "buffer.h"
#include "buffer_item.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "aura/graphics/image/image.h"
//#include "aura/user/user/interaction_impl.h"
#include "aura/user/user/interaction.h"


namespace graphics
{


   buffer_graphics::buffer_graphics()
   {

   }


   buffer_graphics::~buffer_graphics()
   {

      destroy_buffer();

      //destroy_os_buffer();

   }


   void buffer_graphics::update_screen()
   {

      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      //auto bOk =
         
      on_update_screen(get_screen_item());

      // 
      // 
      // 
  //    bool bOk = false;
//

      auto ppixmapImageBuffer = m_pimageBuffer->map();
      ipc_copy(ppixmapImageBuffer);

      //return bOk;

   }


   //bool buffer_graphics::update_screen(buffer_item * pitem)
   //{

   //   __UNREFERENCED_PARAMETER(pitem);

   //   return false;

   //}


   ::image::image_pointer & buffer_graphics::get_buffer()
   {

      return m_pimageBuffer;

   }


   bool buffer_graphics::is_buffer_ok()
   {

      return m_pimageBuffer->is_set();

   }


   void buffer_graphics::destroy_buffer()
   {

      m_pimageBuffer->destroy();

   }


   ::i32_size buffer_graphics::buffer_size()
   {

      return m_pimageBuffer->get_size();

   }


   bool buffer_graphics::update_buffer(buffer_item * pitem)
   {

      //auto pitem = get_buffer_item();

      try
      {

         information() << "::graphics::buffer_graphics::update_buffer going to create image : " << pitem->m_sizeBufferItem;

         m_pimageBuffer->create_as_descriptor(pitem->m_sizeBufferItem);

         information() << "::graphics::buffer_graphics::update_buffer going after create image : " << pitem->m_sizeBufferItem;

      }
      catch (...)
      {

         return false;

      }

      return true;

      //if (!m_pimageBuffer->create_as_descriptor(size))
      //{

      //   return false;

      //}

      //return true;

   }


   //::image::image_pointer & buffer_graphics::get_screen_image()
   //{

   //   return m_pimageBuffer;

   //}


   //::particle * buffer_graphics::get_screen_sync()
   //{

   //   return synchronization();

   //}


   //::particle * buffer_graphics::get_draw_lock()
   //{

   //   return synchronization();

   //}


   bool buffer_graphics::_on_begin(::graphics::buffer_item * pitem)
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

      if (!update_buffer(pitem))
      {

         return false;

      }

      //return pitem;

      return true;

   }


   bool buffer_graphics::buffer_lock_round_swap_key_buffers()
   {

      return true;

   }


} // namespace graphics



