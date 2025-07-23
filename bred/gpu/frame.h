// Created by camilo on 2025-05-19 21:58 <3ThomasBorregaardSorensen!!
#pragma once


namespace gpu
{


   class CLASS_DECL_BRED frame :
      virtual public ::particle
   {
   public:


      ::pointer < ::gpu::layer > m_pgpulayer;

      ::pointer < ::gpu::command_buffer > m_pgpucommandbuffer;

      frame();
      ~frame();


      virtual void initialize_frame();

      virtual ::gpu::context* gpu_context();


   };

   CLASS_DECL_BRED void set_current_frame(::gpu::frame* pgpuframe);
   CLASS_DECL_BRED ::gpu::frame* current_frame();

}  // namespace gpu


