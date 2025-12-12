// From gpu_vulkan/block.cpp by camilo on 2025-12-11 18:11 <3ThomasBorregaardSørensen!!
#include "framework.h"
#define STB_USE_HUNTER
#include "_gpu_opengl.h"
#include "block.h"
#include "command_buffer.h"
#include "context.h"
#include "render_target.h"
#include "renderer.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/binding.h"


namespace gpu_opengl
{


   block::block() {}


   block::~block() {}


   void block::initialize_gpu_block(::gpu::context *pgpucontext)
   {

      ::gpu::block::initialize_gpu_block(pgpucontext);

   }


   void block::create_gpu_block(::gpu::context *pgpucontext)
   {

      ::gpu::context_lock contextlock(pgpucontext);

      int iUboSize = this->size(false);

      // Create the UBO
      glGenBuffers(1, &m_iUBO);
      GLCheckError("");
      glBindBuffer(GL_UNIFORM_BUFFER, m_iUBO);
      GLCheckError("");
      glBufferData(GL_UNIFORM_BUFFER, iUboSize, NULL, GL_STATIC_DRAW); // For 2 mat4s = 2 * sizeof(float) * 16
      GLCheckError("");
      unsigned int uUboBindingPoint = 0;
      glBindBufferBase(GL_UNIFORM_BUFFER, uUboBindingPoint, m_iUBO);
      GLCheckError("");
      glBindBuffer(GL_UNIFORM_BUFFER, 0);
      GLCheckError("");

   }

//
//    VkDescriptorSet block::descriptor_set(::gpu::binding_set_pointer pgpubindingset,
//                                          ::gpu::command_buffer *pgpucommandbuffer)
//    {
//
//       if (m_vkdescriptorset)
//       {
//
//          return m_vkdescriptorset;
//
//       }
//
// //      VkDescriptorBufferInfo bufferinfo;
//
//       ::cast<::gpu_vulkan::context> pcontext = m_pgpucontext;
//
//       //bufferinfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
//       //bufferinfo.imageView = get_image_view();
//       //bufferinfo.sampler = pcontext->_001VkSampler();
//
//       unsigned int uSamplerBinding = 0;
//
//       //auto pgpubindingset = pshader->get_first_image_sampler_binding_set();
//
//       ::cast<::gpu_vulkan::binding_set> pbindingset = pgpubindingset.m_pbindingset;
//
//       auto playout = pbindingset->descriptor_set_layout(pgpucommandbuffer);
//
//       auto ppool = pbindingset->m_pdescriptorpool;
//
//       auto iFrameIndex = pgpucommandbuffer->m_pgpurendertarget->get_frame_index();
//
//       auto bufferInfo = m_uboBuffers[iFrameIndex]->descriptorInfo();
//
//       //   descriptor_writer(*globalSetLayout, *m_pglobalpool)
//       //      .writeBuffer(0, &bufferInfo)
//       //      .build(globalDescriptorSets[i]);
//       ::gpu_vulkan::descriptor_writer(*playout, *ppool)
//          .writeBuffer(uSamplerBinding, &bufferInfo)
//          .build(m_vkdescriptorset);
//
//       return m_vkdescriptorset;
//
//    }
//

   void block::update_frame(gpu::renderer* pgpurenderer)
   {

      ::gpu::context_lock contextlock(m_pgpucontext);

      ASSERT(m_iUBO != 0);

      glBindBuffer(GL_UNIFORM_BUFFER, m_iUBO);
      GLCheckError("");

      int iSize = this->size(false);

      // Map the entire buffer for writing
      void *p = glMapBufferRange(
         GL_UNIFORM_BUFFER,
         0, iSize,
         GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
      GLCheckError("");

      if (p)
      {

         memcpy(p, this->data(false), this->size(false));

         glUnmapBuffer(GL_UNIFORM_BUFFER);
         GLCheckError("");

      }
      else
      {

         warning() << "Failed to map_base UBO";

      }

      glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_iUBO);
      GLCheckError("");

   }


} // namespace gpu_vulkan


