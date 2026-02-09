//
// Created by camilo on 2026-01-06 23:41 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "fence.h"


namespace gpu
{


   fence::fence()
   {



   }


   fence::~fence()
   {



   }


   void fence::initialize_gpu_fence(::gpu::context * pgpucontext)
   {


      ::gpu::fence::initialize_gpu_context_object(pgpucontext);


   }


   void fence::reset()
   {
      
      
   }

   void fence::wait_gpu_fence()
   {


   }


} // gpu
