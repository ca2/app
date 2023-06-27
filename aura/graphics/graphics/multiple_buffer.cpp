#include "framework.h"
#include "multiple_buffer.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/graphics/graphics/multiple_buffer.h"
#include "aura/graphics/image/image.h"
#include "aura/user/user/interaction.h"
#include "aura/user/user/interaction_impl.h"
#include "aura/graphics/image/array.h"


namespace graphics
{


   multiple_buffer::multiple_buffer()
   {

      m_iBuffer = 0;

      m_iDone = -1;

      m_iScreen = -1;


   }


   multiple_buffer::~multiple_buffer()
   {

   }


   void multiple_buffer::initialize_graphics_graphics(::user::interaction_impl * pimpl)
   {

      //auto estatus = 
      
      graphics::initialize_graphics_graphics(pimpl);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //__construct_new(m_pim);

#ifdef MACOS

      m_bufferitema.set_size(3);

#else

      m_bufferitema.set_size(5);

#endif

      for (auto & pbufferitem : m_bufferitema)
      {

         __construct_new(pbufferitem);

         //pimage->defer_create_synchronization();

      }

      //m_mutexa.set_size(m_pimageaBuffer->image_count());

      //return estatus;

   }


   //::particle * multiple_buffer::get_draw_lock()
   //{

   //   return get_buffer_item()->m_pmutex;

   //}


   ::graphics::buffer_item * multiple_buffer::on_begin_draw()
   {

      auto pitem = get_buffer_item();

      //auto sizeBuffer = window_size();
      buffer_size_and_position(pitem);

      //if (m_imageaBuffer[m_iBuffer]->size() != sizeBuffer)
      {

         pitem->m_pimage2->create(pitem->m_size);

         //if (!m_imageaBuffer[m_iBuffer]->create(sizeBuffer))
         //{

         //   return nullptr;

         //}

      }

      ::image_pointer & pimage = m_bufferitema[m_iBuffer]->m_pimage2;

      if (!pimage)
      {

         return nullptr;

      }

      return pitem;

   }


   index multiple_buffer::find_best_buffer(const ::size_i32 & size)
   {

      synchronous_lock synchronouslock(this->synchronization());

      bool bFoundExact = false;

      index iGot = -1;

      index iFound = -1;

      index iFound2 = -1;

      bool bBigger = false;

      if (m_bufferitema.size() == 1)
      {

         return 0;

      }

      if (m_bufferitema[m_iDone]->m_pimage2)
      {

         iFound = m_iDone;

         ::size_i32 sizeBuffer = m_bufferitema[iFound]->m_pimage2->size();

         bBigger = sizeBuffer.cx() > size.cx() || sizeBuffer.cy() > size.cy();

      }

      for (index i = m_iDone; i >= 0; i--)
      {

         if(i == m_iBuffer)
         {

            continue;

         }

         if (!m_bufferitema[i]->m_pimage2)
         {

            break;

         }

         ::size_i32 sizeBuffer = m_bufferitema[i]->m_pimage2->size();

         if (size == sizeBuffer)
         {

            iFound = i;

            bFoundExact = true;

            break;

         }

         if (iFound2 < 0)
         {

            if ((bBigger && sizeBuffer.cx() > size.cx() && sizeBuffer.cy() > size.cy())
               || (!bBigger && sizeBuffer.cx() < size.cx() && sizeBuffer.cy() < size.cy()))
            {

               iFound2 = i;

            }

         }

      }

      if (!bFoundExact)
      {

         for (index i = m_bufferitema.get_upper_bound(); i > m_iDone; i--)
         {

            if(i == m_iBuffer)
            {

               continue;

            }

            if (!m_bufferitema[i]->m_pimage2)
            {

               break;

            }

            ::size_i32 sizeBuffer = m_bufferitema[i]->m_pimage2->get_size();

            if (sizeBuffer == size)
            {

               iFound = i;

               bFoundExact = true;

               break;

            }

            if (iFound2 < 0)
            {

               if ((bBigger && sizeBuffer.cx() > size.cx() && sizeBuffer.cy() > size.cy())
                  || (!bBigger && sizeBuffer.cx() < size.cx() && sizeBuffer.cy() < size.cy()))
               {

                  iFound2 = i;

               }

            }

         }

      }

      iGot = iFound;

      if (!bFoundExact && iFound2 >= 0)
      {

         iGot = iFound2;

      }

      //int iAge;

      //if (iGot < 0)
      //{

      //   //iAge = -1;

      //}
      //else if (iGot <= m_iDone)
      //{

      //   //iAge = (int)(m_iDone - iGot);

      //}
      //else
      //{

      //   //iAge = (int)(m_bufferitema.size() - iGot + m_iDone);

      //}

#ifdef EXTRALOG

      strFormat.format(" age %d", iAge);

      str += strFormat;

      if (!bFoundExact)
      {

         strFormat.format(" buffer size_i32 %d, %d", pimageBuffer2->width(), pimageBuffer2->height());

         s_iLastExact = -1;

      }
      else
      {

         strFormat.format("!!");

         s_iLastExact++;

      }

      str += strFormat;

#endif

      if (iGot < 0)
      {

         information("NOT DRAWING? <<---- search and bp here !imageBuffer2 ");

      }

      return iGot;

   }


   bool multiple_buffer::buffer_lock_round_swap_key_buffers()
   {

      synchronous_lock synchronouslock(this->synchronization());

      m_iDone = m_iBuffer;

      m_iBuffer++;

      m_iBuffer %= m_bufferitema.size();

      return true;

   }


   buffer_item * multiple_buffer::get_screen_item()
   {

      auto size = m_pimpl->m_puserinteraction->const_layout().design().size();

      m_iScreen = find_best_buffer(size);

      if (m_iScreen < 0)
      {

         return nullptr;

      }

      return m_bufferitema[m_iScreen];

   }


   //::image_pointer & multiple_buffer::get_screen_image()
   //{

   //   return m_bufferitema[m_iScreen].m_pimage;

   //}



   bool multiple_buffer::update_screen()
   {

      synchronous_lock synchronouslock(this->synchronization());

      auto size = m_pimpl->m_puserinteraction->const_layout().design().size();

      auto iImage = find_best_buffer(size);

      if (iImage < 0)
      {

         return false;

      }

      auto pitem = get_screen_item();

      synchronous_lock slScreen(pitem->m_pmutex);

      //auto bOk = update_screen(get_screen_item());

      bool bOk = false;

      ipc_copy(pitem->m_pimage2);

      return bOk;



   }


} // namespace graphics


