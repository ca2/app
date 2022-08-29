#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/user/_component.h"
#endif
#include "aura/graphics/graphics/multiple_buffer.h"
#include "_.h"
#include "_graphics.h"
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

      __construct_new(m_pimageaBuffer);

#ifdef MACOS

      m_pimageaBuffer->set_size(3);

#else

      m_pimageaBuffer->set_size(5);

#endif

      for (auto & pimage : *m_pimageaBuffer)
      {

         __construct(pimage);

         //pimage->defer_create_mutex();

      }

      m_mutexa.set_size(m_pimageaBuffer->get_size());

      //return estatus;

   }


   ::synchronization_object * multiple_buffer::get_draw_lock()
   {

      return m_mutexa[m_iBuffer];

   }


   ::draw2d::graphics * multiple_buffer::on_begin_draw()
   {

      auto sizeBuffer = window_size();

      //if (m_imageaBuffer[m_iBuffer]->size() != sizeBuffer)
      {

         m_pimageaBuffer->element_at(m_iBuffer)->create(sizeBuffer);

         //if (!m_imageaBuffer[m_iBuffer]->create(sizeBuffer))
         //{

         //   return nullptr;

         //}

      }

      ::image_pointer & pimage = m_pimageaBuffer->element_at(m_iBuffer);

      if (!pimage)
      {

         return nullptr;

      }

      return pimage->g();

   }


   index multiple_buffer::find_best_buffer(const ::size_i32 & size)
   {

      synchronous_lock synchronouslock(mutex());

      bool bFoundExact = false;

      index iGot = -1;

      index iFound = -1;

      index iFound2 = -1;

      bool bBigger = false;

      if (m_pimageaBuffer->get_size() == 1)
      {

         return 0;

      }

      if (m_pimageaBuffer->element_at(m_iDone))
      {

         iFound = m_iDone;

         ::size_i32 sizeBuffer = m_pimageaBuffer->element_at(iFound)->get_size();

         bBigger = sizeBuffer.cx > size.cx || sizeBuffer.cy > size.cy;

      }

      for (index i = m_iDone; i >= 0; i--)
      {

         if(i == m_iBuffer)
         {

            continue;

         }

         if (!m_pimageaBuffer->element_at(i))
         {

            break;

         }

         ::size_i32 sizeBuffer = m_pimageaBuffer->element_at(i)->get_size();

         if (size == sizeBuffer)
         {

            iFound = i;

            bFoundExact = true;

            break;

         }

         if (iFound2 < 0)
         {

            if ((bBigger && sizeBuffer.cx > size.cx && sizeBuffer.cy > size.cy)
               || (!bBigger && sizeBuffer.cx < size.cx && sizeBuffer.cy < size.cy))
            {

               iFound2 = i;

            }

         }

      }

      if (!bFoundExact)
      {

         for (index i = m_pimageaBuffer->get_upper_bound(); i > m_iDone; i--)
         {

            if(i == m_iBuffer)
            {

               continue;

            }

            if (!m_pimageaBuffer->element_at(i))
            {

               break;

            }

            ::size_i32 sizeBuffer = m_pimageaBuffer->element_at(i)->get_size();

            if (sizeBuffer == size)
            {

               iFound = i;

               bFoundExact = true;

               break;

            }

            if (iFound2 < 0)
            {

               if ((bBigger && sizeBuffer.cx > size.cx && sizeBuffer.cy > size.cy)
                  || (!bBigger && sizeBuffer.cx < size.cx && sizeBuffer.cy < size.cy))
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

      int iAge;

      if (iGot < 0)
      {

         iAge = -1;

      }
      else if (iGot <= m_iDone)
      {

         iAge = (int)(m_iDone - iGot);

      }
      else
      {

         iAge = (int)(m_pimageaBuffer->get_count() - iGot + m_iDone);

      }

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

         output_debug_string("NOT DRAWING? <<---- search and bp here !imageBuffer2 ");

      }

      return iGot;

   }


   bool multiple_buffer::buffer_lock_round_swap_key_buffers()
   {

      synchronous_lock synchronouslock(mutex());

      m_iDone = m_iBuffer;

      m_iBuffer++;

      m_iBuffer %= m_pimageaBuffer->get_count();

      return true;

   }


   synchronization_object * multiple_buffer::get_screen_sync()
   {

      auto size = m_pimpl->m_puserinteraction->const_layout().design().size();

      m_iScreen = find_best_buffer(size);

      if (m_iScreen < 0)
      {

         return nullptr;

      }

      return m_mutexa[m_iScreen];

   }


   ::image_pointer & multiple_buffer::get_screen_image()
   {

      return m_pimageaBuffer->element_at(m_iScreen);

   }



   bool multiple_buffer::update_screen()
   {

      synchronous_lock synchronouslock(mutex());

      auto size = m_pimpl->m_puserinteraction->const_layout().design().size();

      auto iImage = find_best_buffer(size);

      if (iImage < 0)
      {

         return false;

      }

      synchronous_lock slBuffer(get_screen_sync());

      auto bOk = update_screen(get_screen_image());

      ipc_copy(get_screen_image());

      return bOk;



   }


} // namespace graphics


