// Created by camilo on 2025-06-12 21:08 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "command_buffer.h"
#include "context.h"
#include "device.h"
#include "layer.h"
#include "renderer.h"
#include "render_target.h"
#include "texture.h"


namespace gpu
{


   layer::layer()
   {


   }


   layer::~layer()
   {


   }


   ::gpu::command_buffer* layer::getCurrentCommandBuffer4()
   {

      if (m_commandbufferaLayer.is_empty())
      {

         create_command_buffers();

      }

      auto pgpurenderer = m_pgpurenderer;

      auto pgpurendertarget = pgpurenderer->m_pgpurendertarget;

      auto iFrameIndex = pgpurenderer->m_pgpucontext->m_pgpudevice->get_frame_index2();

      auto pcommandbufferLayer = m_commandbufferaLayer[iFrameIndex];

      pcommandbufferLayer->m_iFrameIndex = iFrameIndex;

      pcommandbufferLayer->m_strAnnotation = "layer";

      if (pgpurenderer->m_pgpucontext->m_etype == ::gpu::context::e_type_draw2d)
      {

         pcommandbufferLayer->m_strAnnotation += ".draw2d";

      }
      else if (pgpurenderer->m_pgpucontext->m_etype == ::gpu::context::e_type_graphics3d)
      {

         pcommandbufferLayer->m_strAnnotation += ".graphics3d";

      }

      return pcommandbufferLayer;

   }


   void layer::initialize_gpu_layer(::gpu::renderer * pgpurenderer, int iFrameIndex, int iLayerIndex)
   {

      m_pgpurenderer = pgpurenderer;

      m_iFrameIndex = iFrameIndex;

      m_iLayerIndex = iLayerIndex;

      m_pgpurenderer->defer_update_renderer();

   }


   //void layer::set_target_texture(texture* ptextureTarget)
   //{

   //   target_texture() = ptextureTarget;

   //}


   void layer::layer_start()
   {

      m_bRenderTargetFramebufferInitialized = false;

      m_pgpurenderer->on_start_layer(this);

   }


   void layer::create_command_buffers()
   {

      m_commandbufferaLayer.set_size(m_pgpurenderer->m_iDefaultFrameCount);

      for (auto& pcommandbufferLayer : m_commandbufferaLayer)
      {

         ødefer_construct(pcommandbufferLayer);

         pcommandbufferLayer->initialize_command_buffer(
            m_pgpurenderer->m_pgpurendertarget,
            m_pgpurenderer->m_pgpucontext->m_pgpudevice->graphics_queue(),
            ::gpu::e_command_buffer_graphics);

      }

      //commandBuffers.resize(render_target_view::MAX_FRAMES_IN_FLIGHT);

      //VkCommandBufferAllocateInfo allocInfo{};
      //allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
      //allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
      //allocInfo.commandPool = m_pgpucontext->m_pgpudevice->getCommandPool();
      //allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

      //if (vkAllocateCommandBuffers(m_pgpucontext->logicalDevice(), &allocInfo, commandBuffers.data()) !=
      //   VK_SUCCESS) {
      //   throw ::exception(error_failed, "failed to allocate command buffers!");
      //}


   }




   void layer::layer_end()
   {

      m_pgpurenderer->on_end_layer(this);

   }


   ::pointer < texture >& layer::texture()
   {

      int iFrameIndex = m_pgpurenderer->m_pgpucontext->m_pgpudevice->get_frame_index2();

      auto & ptexture = m_texturea.element_at_grow(iFrameIndex);

      m_pgpurenderer->ødefer_construct(ptexture);

      ptexture->m_bRenderTarget = true;

      auto rectangle = m_pgpurenderer->m_pgpucontext->rectangle();

      ptexture->m_bTransferDst = true;

      ptexture->initialize_texture(m_pgpurenderer, rectangle, false);

      return ptexture;

   }


   ::pointer < texture >& layer::source_texture()
   {

      int iFrameIndex = m_pgpurenderer->m_pgpucontext->m_pgpudevice->get_frame_index2();

      auto& ptextureSource = m_textureaSource.element_at_grow(iFrameIndex);

      m_pgpurenderer->ødefer_construct(ptextureSource);

      ptextureSource->m_bRenderTarget = true;

      ptextureSource->m_bTransferSrc = true;

      auto rectangle = m_pgpurenderer->m_pgpucontext->rectangle();

      auto escene = m_pgpurenderer->m_pgpucontext->m_escene;

      bool bWithDepth = escene == ::gpu::e_scene_3d;

      ptextureSource->initialize_texture(m_pgpurenderer, rectangle, bWithDepth);

      return ptextureSource;

   }


   //::pointer < texture >& layer::target_texture()
   //{
   //   
   //   int iTargetFrameIndex = m_pgpurendererTarget->_get_frame_index();
   //   
   //   auto & ptextureTarget = m_gputextureaTarget[iTargetFrameIndex];

   //   m_pgpurendererTarget->ødefer_construct(ptextureTarget);

   //   auto rectangleTarget = m_pgpurendererTarget->m_pgpucontext->rectangle();

   //   ptextureTarget->initialize_gpu_texture(m_pgpurendererTarget, rectangleTarget);

   //   return ptextureTarget;

   //}


} // namespace gpu


