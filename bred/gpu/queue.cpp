//
// Created by camilo on 2025-08-22 09:37 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "context.h"
#include "queue.h"


namespace gpu
{


   queue::queue()
   {


   }


   queue::~queue()
   {


   }


   void queue::initialize_gpu_queue(::gpu::context * pgpucontext)
   {

      m_pgpucontext = pgpucontext;

   }


} // namespace gpu



