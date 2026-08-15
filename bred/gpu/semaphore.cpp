//
// Created by camilo on 2026-01-28 22:52 <3ThomasBorregaardSørensen!!
//
#include "platform.h"
#include "semaphore.h"


namespace gpu
{


   semaphore::semaphore()
   {



   }


   semaphore::~semaphore()
   {



   }


   void semaphore::initialize_gpu_semaphore(::gpu::context * pgpucontext)
   {

      initialize_gpu_context_object(pgpucontext);

   }


   void semaphore::wait(::gpu::queue * pgpuqueue)
   {


   }


   void semaphore::signal(::gpu::queue * pgpuqueue)
   {



   }


} // namespace gpu



