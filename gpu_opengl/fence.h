//
//  fence.h
//  gpu_opengl
//
//  Created by camilo on 2026-02-08 22:17 <3ThomasBorregaardSørensen!!
//
#pragma once


#include "bred/gpu/fence.h"
#include "gpu_opengl/_gpu_opengl.h"


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL fence :
      virtual public ::gpu::fence
   {
   public:
   
      
      GLsync m_glsyncFence;
      
      fence();
      ~fence() override;
      
      
      
      void initialize_gpu_fence(::gpu::context * pgpucontext) override;
      
      
      void reset() override;

      void wait_gpu_fence() override;

   
   };


} // namespace gpu_opengl




