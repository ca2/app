//
// Created by camilo on 2026-01-06 23:41 <3ThomasBorregaardSørensen!!
//
#pragma once


//#include "bred/gpu/device.h"


namespace gpu
{


   class CLASS_DECL_BRED fence :
      virtual public ::particle
   {

   public:


      ::u64                            m_uFence;
      ::pointer < ::gpu::device >      m_pgpudevice;


      fence();
      ~fence() override;


      virtual void initialize_gpu_fence(::gpu::device * pgpudevice, bool bCreateSignaled);
      
      virtual void signal_gpu_fence(::gpu::queue * pgpuqueue);
      
      virtual void reset_gpu_fence();

      virtual void wait_gpu_fence();

      virtual bool has_finished();

   };


} // gpu

