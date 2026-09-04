//
// Created by camilo on 2026-01-06 23:41 <3ThomasBorregaardSørensen!!
//
#pragma once


#include "bred/gpu/context_pointer.h"


namespace gpu
{


   class CLASS_DECL_BRED fence :
      virtual public ::particle
   {

   public:


      ::u64                            m_uFence;
      ::gpu::context_pointer           m_pgpucontextGpuFence;


      fence();
      ~fence() override;


      virtual void initialize_gpu_fence(::gpu::context * pgpucontext, bool bCreateSignaled);
      
      virtual void signal_gpu_fence(::gpu::queue * pgpuqueue);
      
      virtual void reset_gpu_fence();

      virtual void wait_gpu_fence();

      virtual bool has_finished();

   };


} // gpu

