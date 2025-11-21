// Created by camilo on 2025-08-16 01:17 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{

   enum enum_resource
   {

      e_resource_upload_buffer,

   };


   class CLASS_DECL_BRED frame_storage :
      virtual public ::particle
   {
   public:


      class CLASS_DECL_BRED object :
         virtual public ::particle
      {
      public:


         virtual void on_end_frame();


      };

      ::pointer < ::gpu::device > m_pgpudevice;

      map < particle*, map < enum_resource, ::pointer < object > > > m_mapObject;

      int m_iBuffer;
      int m_iBufferSize = (int) 1_MiB;
      int m_iBufferOffset;

      
      pointer_array < memory_buffer > m_buffera;
      pointer_array<memory> m_memorya;


      frame_storage();
      ~frame_storage() override;


      virtual void initialize_gpu_frame_storage(::gpu::device* pgpudevice);

      virtual void map_allocate(::gpu::memory_buffer * pbuffer, int size);

      virtual void on_end_frame();


   };


} // namespace gpu



