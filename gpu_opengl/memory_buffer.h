// Created by camilo on 2025-06-11 00:50 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/gpu/memory_buffer.h"


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL memory_buffer :
      virtual public ::gpu::memory_buffer
   {
   public:



      GLuint m_gluVbo;
      GLsizei m_iType;
      //::gpu_vulkan::context * m_pcontext;
      //VkDeviceMemory m_vkdevicememory;
      //VkBuffer m_vkbuffer;
      //memsize m_size;
      //void* m_pMap;


      memory_buffer();
      ~memory_buffer();


      //void initialize_memory_buffer_with_context(::gpu::context* pcontext, memsize size, memory_buffer::enum_type etype) override;
      //void initialize_memory_buffer_with_model_buffer(::gpu::model_buffer* pmodelbuffer, memsize size, memory_buffer::enum_type etype) override;

      void on_initialize_memory_buffer(const void * dataStatic = nullptr, memsize size = 0) override;

      void on_set_memory_buffer(const void* data = nullptr, memsize size = 0) override;

      void _on_set_memory_buffer(const void* data = nullptr, memsize size = 0) override;


      bool is_initialized() const override;


      void _assign(const void* data, memsize size) override;


      void * _map(memsize start, memsize count) override;
      void _unmap() override;


      void bind() override;
      void unbind() override;


   };




} // namespace gpu_opengl



