// Created by camilo on 2025-12-11 16:03 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "binding.h"
#include "block.h"
#include "command_buffer.h"
#include "context.h"
#include "render_target.h"
#include "renderer.h"


namespace gpu_vulkan
{


   block::block() {}


   block::~block() {}


   void block::initialize_gpu_block(::gpu::context *pgpucontext)
   {

      ::gpu::block::initialize_gpu_block(pgpucontext);

   }


   void block::create_gpu_block(::gpu::context *pgpucontext)
   {

      // ::gpu::context_lock contextlock(this);
      //
      // // Create the UBO
      // glGenBuffers(1, &m_globalUBO);
      // GLCheckError("");
      // glBindBuffer(GL_UNIFORM_BUFFER, m_globalUBO);
      // GLCheckError("");
      // glBufferData(GL_UNIFORM_BUFFER, iGlobalUboSize, NULL, GL_STATIC_DRAW); // For 2 mat4s = 2 * sizeof(float) * 16
      // GLCheckError("");
      // unsigned int uUboBindingPoint = 0;
      // glBindBufferBase(GL_UNIFORM_BUFFER, uUboBindingPoint, m_globalUBO);
      // GLCheckError("");
      // glBindBuffer(GL_UNIFORM_BUFFER, 0);
      // GLCheckError("");

   }


   VkDescriptorSet block::descriptor_set(::gpu::binding_set_pointer pgpubindingset,
                                         ::gpu::command_buffer *pgpucommandbuffer)
   {

      if (m_vkdescriptorset)
      {

         return m_vkdescriptorset;

      }

//      VkDescriptorBufferInfo bufferinfo;

      ::cast<::gpu_vulkan::context> pcontext = m_pgpucontext;

      //bufferinfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
      //bufferinfo.imageView = get_image_view();
      //bufferinfo.sampler = pcontext->_001VkSampler();

      unsigned int uSamplerBinding = 0;

      //auto pgpubindingset = pshader->get_first_image_sampler_binding_set();

      ::cast<::gpu_vulkan::binding_set> pbindingset = pgpubindingset.m_pbindingset;

      auto playout = pbindingset->descriptor_set_layout(pgpucommandbuffer);

      auto ppool = pbindingset->m_pdescriptorpool;

      auto iFrameIndex = pgpucommandbuffer->m_pgpurendertarget->get_frame_index();

      auto bufferInfo = m_uboBuffers[iFrameIndex]->descriptorInfo();

      //   descriptor_writer(*globalSetLayout, *m_pglobalpool)
      //      .writeBuffer(0, &bufferInfo)
      //      .build(globalDescriptorSets[i]);
      ::gpu_vulkan::descriptor_writer(*playout, *ppool)
         .writeBuffer(uSamplerBinding, &bufferInfo)
         .build(m_vkdescriptorset);

      return m_vkdescriptorset;

   }


   void block::update_frame(gpu::renderer* pgpurenderer)
   {

      auto iFrameIndex = pgpurenderer->m_pgpurendertarget->get_frame_index();

      if (iFrameIndex < 0 || iFrameIndex >= m_uboBuffers.size())
      {

         return;
      }

      if (!m_uboBuffers[iFrameIndex])
      {

         return;
      }

      m_uboBuffers[iFrameIndex]->map();

      m_uboBuffers[iFrameIndex]->writeToBuffer(block.data());

      m_uboBuffers[iFrameIndex]->flush();

      m_uboBuffers[iFrameIndex]->unmap();

   }


} // namespace gpu_vulkan


