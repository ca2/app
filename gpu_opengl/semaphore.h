//
//  semaphore.h
//  gpu_opengl
//
//  Created by camilo on 2026-02-08 22:31 <3ThomasBorregaardSørensen!!
//
#pragma once


#include "bred/gpu/semaphore.h"


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL semaphore :
      virtual public ::gpu::semaphore
   {
   public:
   
      
      semaphore();
      ~semaphore() override;
      
      
      
      void initialize_gpu_semaphore(::gpu::context * pgpucontext) override;

   
   };


} // namespace gpu_opengl




