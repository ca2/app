//
//  fence.h
//  gpu_opengl
//
//  Created by camilo on 2026-02-08 22:33 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "semaphore.h"


namespace gpu_opengl
{


      
   semaphore::semaphore()
   {
      
   }


   semaphore::~semaphore()
   {
      
     
   }


   void semaphore::initialize_gpu_semaphore(::gpu::context * pgpucontext)
   {
      
      ::gpu::semaphore::initialize_gpu_semaphore(pgpucontext);
   
   }

        
   
} // namespace gpu_opengl



