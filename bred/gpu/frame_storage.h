// Created by camilo on 2025-08-16 01:17 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{


   class CLASS_DECL_BRED frame_storage :
      virtual public ::particle
   {
   public:

      ::pointer < ::gpu::device > m_pgpudevice;

      int m_iBuffer;
      int m_iBufferSize = 1_MiB;
      int m_iBufferOffset;


      frame_storage();
      ~frame_storage() override;


      virtual void initialize_gpu_frame_storage(::gpu::device* pgpudevice);

      virtual void map_allocate(::gpu::memory_buffer * pbuffer, int size);


   };


} // namespace gpu



