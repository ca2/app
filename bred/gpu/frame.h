// Created by camilo on 2025-05-19 21:58 <3ThomasBorregaardSorensen!!
#pragma once


namespace gpu
{


   class CLASS_DECL_BRED frame :
      virtual public ::particle
   {
   public:


      enum_gpu_frame_state m_egpuframestate = e_gpu_frame_state_initial;

      ::procedure_array m_procedureaOnAfterEndFrame;

      ::procedure_array m_procedureaOnJustBeforeFrameNextStart;

      //::pointer < ::gpu::layer > m_pgpulayer;

      //::pointer < ::gpu::command_buffer > m_pgpucommandbuffer;

      frame();
      ~frame();

      virtual void initialize_gpu_frame();

      virtual void on_before_start_frame();

      virtual void start_frame();

      virtual void end_frame();

      virtual void on_after_end_frame();

      //virtual ::gpu::context* gpu_context();

      virtual void post_on_after_end_frame(const ::procedure &procedure);


      virtual void post_on_just_before_frame_next_start(const ::procedure &procedure);


   };

   //CLASS_DECL_BRED void set_current_frame(::gpu::layer* pgpulayer);
   //CLASS_DECL_BRED ::gpu::frame* current_frame();

}  // namespace gpu


