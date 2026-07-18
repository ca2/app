// Created by camilo on 2025-05-19 22:08 <3ThomasBorregaardSorensen!!
#include "framework.h"
//#include "command_buffer.h"
//#include "context.h"
#include "frame.h"
//#include "render_target.h"
//#include "renderer.h"
//
//
namespace gpu
{


   frame::frame()
   {

   }


   frame::~frame()
   {


   }


   void frame::initialize_gpu_frame()
   {


      m_egpuframestate = e_gpu_frame_state_initial;

   }


   void frame::on_before_start_frame()
   {

            if (m_procedureaOnJustBeforeFrameNextStart.has_element())
            {
      
               try
               {
      
                  for (auto & procedure : m_procedureaOnJustBeforeFrameNextStart)
                  {
      
                     try
                     {
      
                        procedure();
      
                     }
                     catch (...)
                     {
      
      
                     }
      
                  }
      
               }
               catch (...)
               {
      
      
               }
      
               m_procedureaOnJustBeforeFrameNextStart.clear();
      
            }

   }

   void frame::start_frame()
   {

      on_before_start_frame();


      {

         if (!(m_egpuframestate == e_gpu_frame_state_initial || m_egpuframestate == e_gpu_frame_state_ended_frame))
         {

            information() << "Wrong state when e_happening_begin_frame";
         }
         m_egpuframestate = e_gpu_frame_state_began_frame;
      }

   }


   void frame::end_frame()
   {

      {

         ASSERT(m_egpuframestate == e_gpu_frame_state_began_frame);
         m_egpuframestate = e_gpu_frame_state_ended_frame;
      }

      on_after_end_frame();

   }


   void frame::on_after_end_frame()
   {


            if (m_procedureaOnAfterEndFrame.has_element())
            {
      
               try
               {
      
                  for (auto &procedure: m_procedureaOnAfterEndFrame)
                  {
                     try
                     {
      
                        procedure();
      
                     }
                     catch (...)
                     {
      
      
                     }
                  }
      
               }
               catch (...)
               {
      
      
               }
               m_procedureaOnAfterEndFrame.clear();
      
            }
      
      

   }


   
   void frame::post_on_after_end_frame(const ::procedure &procedure)
   {

      //_synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      m_procedureaOnAfterEndFrame.add(procedure);
   }


   void frame::post_on_just_before_frame_next_start(const ::procedure &procedure)
   {

      m_procedureaOnJustBeforeFrameNextStart.add(procedure);
   }

   //::gpu::context* frame::gpu_context()
   //{

   //   return m_pgpucommandbuffer->m_pgpurendertarget->m_pgpurenderer->m_pgpucontext;

   //}


   //thread_local ::gpu::frame* t_pgpuframe;


   //void set_current_frame(::gpu::layer* pgpulayer)
   //{

   //   t_pgpuframe = pgpulayer;


   //}
   //::gpu::frame* current_frame()
   //{

   //   return t_pgpuframe;

   //}


}  // namespace gpu


