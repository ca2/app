//
// Created by camilo on 2025-08-22 09:37 <3ThomasBorregaardSorensen!!
//
#include "platform.h"
#include "device.h"
#include "queue.h"


namespace gpu
{


   queue::queue()
   {


   }


   queue::~queue()
   {


   }


   void queue::initialize_gpu_queue(::gpu::device * pgpudevice)
   {

      m_pgpudevice = pgpudevice;

   }


   void queue::execute_command_buffer(::gpu::command_buffer * pgpucommandbuffer)
   {


   }


} // namespace gpu



