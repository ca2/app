//
// Created by camilo on 2026-01-06 23:41 <3ThomasBorregaardSørensen!!
//
#pragma once


#include "bred/gpu/context_object.h"


namespace gpu
{

   class fence :
   virtual public ::gpu::context_object
   {

   public:


      fence();
      ~fence() override;


      virtual void initialize_gpu_fence(::gpu::context * pgpucontext);

      virtual void wait_gpu_fence();


   };


} // gpu

