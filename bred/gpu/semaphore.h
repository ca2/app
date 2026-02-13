//
// Created by camilo on 2026-01-28 22:50 <3ThomasBorregaardSørensen!!
//
#pragma once



#include "bred/gpu/context_object.h"


namespace gpu
{


   class CLASS_DECL_BRED semaphore :
      virtual public ::gpu::context_object
   {
   public:


      semaphore();
      ~semaphore() override;


      virtual void initialize_gpu_semaphore(::gpu::context * pgpucontext);


   };


} // namespace gpu



