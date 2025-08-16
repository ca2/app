// Created by camilo on 2025-08-16 01:20 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "device.h"
#include "frame_storage.h"


namespace gpu
{


   frame_storage::frame_storage()
   {


   }


   frame_storage::~frame_storage()
   {


   }


   void frame_storage::initialize_gpu_frame_storage(::gpu::device* pgpudevice)
   {

      m_pgpudevice = pgpudevice;

   }


   void frame_storage::map_allocate(::gpu::memory_buffer* pbuffer, int size)
   {



   }


   //void* frame_storage::allocate(int size)
   //{

   //   return nullptr;

   //}


} // namespace gpu



