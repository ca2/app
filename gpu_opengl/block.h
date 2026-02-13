// From gpu_vulkan/block.h by camilo on 2025-12-11 18:11 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/gpu/block.h"
#include "bred/gpu/context.h"


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL block :
      virtual public ::gpu::block
   {
   public:


      //::pointer_array<::gpu_vulkan::memory_buffer> m_uboBuffers;

      //VkDescriptorSet m_vkdescriptorset;

      GLuint m_iUBO;

      block();
      ~block() override;


      //void initialize_gpu_block(::gpu::context *pgpucontext) override;


      void create_gpu_block(::gpu::context *pgpucontext) override;
      //virtual VkDescriptorSet descriptor_set(::gpu::binding_set_pointer pgpubindingset, ::gpu::command_buffer *pgpucommandbuffer);


      void update_frame(gpu::renderer* pgpurenderer) override;


   };


} // namespace gpu_opengl


