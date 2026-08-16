// Created by camilo on 2026-08-07 11:02 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
#include "platform.h"
#include "window_attachment.h"
#include "acme/windowing/window.h"


namespace apex
{


   namespace gpu
   {


      window_attachment::window_attachment()
      {

         m_iCurrentFrame3 = 0;
         m_iCurrentImage = -1;
         m_iFrameSerial2 = -1;
         m_iFrameCount = 3;

      }


      window_attachment::~window_attachment()
      {


      }


      void window_attachment::initialize_gpu_window_attachment(::acme::windowing::window * pacmewindowingwindow)
      {

         m_pacmewindowingwindow = pacmewindowingwindow;
             
      }



      ::i32 window_attachment::get_frame_index3()
      {

         auto iFrameCount = this->get_frame_count();

         if (iFrameCount > 1)
         {

            return (::i32)(m_iCurrentFrame3 % iFrameCount);

         }
         else
         {

            return 0;

         }

      }


      ::i32 window_attachment::get_image_index()
      {

         if (this->get_frame_count() > 1)
         {

            return (::i32)m_iCurrentImage;
         }
         else
         {

            return 0;
         }

      }


      ::i32 window_attachment::get_frame_count()
      {

         return (::i32)m_iFrameCount;

      }


      bool window_attachment::is_starting_frame()const
      {

         return m_iFrameSerial2 == m_iCurrentFrame3;

      }


      void window_attachment::restart_frame_counter()
      {

         if (this->get_frame_count() > 1)
         {

            m_iCurrentFrame3 = 0;
            m_iFrameSerial2 = -1;

            //m_pgpurenderer->m_prenderstate->on_happening(e_happening_reset_frame_counter);

         }

      }



   } // namespace gpu


} // namespace apex



