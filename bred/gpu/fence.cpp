//
// Created by camilo on 2026-01-06 23:41 <3ThomasBorregaardSørensen!!
//
#include "platform.h"
#include "device.h"
#include "fence.h"


namespace gpu
{


   fence::fence()
   {

      m_uFence = 0;

   }


   fence::~fence()
   {



   }


   void fence::initialize_gpu_fence(::gpu::device * pgpudevice, bool bCreateSignaled)
   {

      m_pgpudevice = pgpudevice;
      //::gpu::fence::initialize_gpu_context_object(pgpucontext);


   }


   void fence::signal_gpu_fence(::gpu::queue * pgpuqueue)
   {



   }


   void fence::reset_gpu_fence()
   {
      
      
   }


   void fence::wait_gpu_fence()
   {


   }


   bool fence::has_finished()
   {

      return true;

   }

} // gpu
