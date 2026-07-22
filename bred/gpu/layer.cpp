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

      m_bFirstLayer = false;
      m_bClosingLayer = false;
      //m_bFinished = false;

   }


   layer::~layer()
   {


   }


   

   void layer::initialize_layer_state() { m_egpulayerstate = e_gpu_layer_state_initial; }

   void layer::start_layer_render() { m_egpulayerstate = e_gpu_layer_state_began_render; }

   void layer::end_layer_render() { m_egpulayerstate = e_gpu_layer_state_ended_render; }




   ::manual_reset_happening * layer::finished_manual_reset_happening()
   {

      if (!m_pmanualresethappeningFinished)
      {

         construct_newø(m_pmanualresethappeningFinished);

      }

      return m_pmanualresethappeningFinished;

   }


   ::gpu::command_buffer* layer::getCurrentCommandBuffer4()
   {

      if (m_pcommandbufferScoped)
      {

         return m_pcommandbufferScoped;

      }

      if (m_commandbufferaLayer.is_empty())
      {

         create_command_buffers();

      }

      auto pgpurenderer = m_pgpurenderer;

      //auto pgpurendertarget = pgpurenderer->render_target();

      auto iImageIndex = pgpurenderer->m_pgpucontext->m_pgpudevice->get_image_index();
      const auto iFrameIndex = pgpurenderer->m_pgpucontext->m_pgpudevice->get_frame_index3();

      if (iImageIndex < 0)
      {

         ::warning("iImageIndex < 0 (1) as gpu::layer");

      }

      auto pcommandbufferLayer = m_commandbufferaLayer[iImageIndex];

      pcommandbufferLayer->m_iCommandBufferFrameIndex2 = iFrameIndex;
      pcommandbufferLayer->m_iCommandBufferImageIndex = iImageIndex;

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


   void layer::initialize_gpu_layer(::gpu::renderer * pgpurenderer, ::i32 iFrameIndex, ::i32 iLayerIndex)
   {

      m_pgpurenderer = pgpurenderer;

      m_iFrameIndex = iFrameIndex;

      m_iLayerIndex = iLayerIndex;

      m_bIncludeInFrameComposition = true;

      if (iLayerIndex >= 3)
      {

         information("iLayerIndex >= 3");

      }

      m_pgpurenderer->defer_update_renderer();

   }


   //void layer::set_target_texture(texture* ptextureTarget)
   //{

   //   target_texture() = ptextureTarget;

   //}


   void layer::layer_start()
   {

      m_timeStart.Now();

      m_bRenderTargetFramebufferInitialized = false;

      ::gpu::set_current_layer(this);

      //m_bFinished = false;
      finished_manual_reset_happening()->reset_happening();

      m_pgpurenderer->on_start_layer(this);

   }


   void layer::create_command_buffers()
   {

      m_commandbufferaLayer.set_size(m_pgpurenderer->m_iDefaultFrameCount);

      ::i32 iImageIndex = -1;

      for (auto& pcommandbufferLayer : m_commandbufferaLayer)
      {

         iImageIndex++;

         defer_constructø(pcommandbufferLayer);

         pcommandbufferLayer->initialize_command_buffer(m_pgpurenderer->render_target(),
            m_pgpurenderer->m_pgpucontext->m_pgpudevice->graphics_queue(),
            ::gpu::e_command_buffer_graphics);

         pcommandbufferLayer->m_iCommandBufferImageIndex = iImageIndex;

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

      // auto pgpufence = m_pgpufence;
      //
      // if (::is_set(pgpufence))
      // {
      //
      //    pgpufence->wait_gpu_fence();
      //
      // }
      //
      // m_timeEnd.Now();
      //
      // m_timeDuration = m_timeEnd - m_timeStart;
      //
      // information("Layer {} duration : {} ms", m_iLayerIndex, m_timeDuration.floating_millisecond());
      //
      // finished_manual_reset_happening()->set_happening();

   }


   void layer::layer_on_after_submit()
   {

//      m_pgpurenderer->on_end_layer(this);

      auto pgpufence = m_pgpufence;

      if (::is_set(pgpufence))
      {

         pgpufence->wait_gpu_fence();

      }

      m_timeEnd.Now();

      m_timeDuration = m_timeEnd - m_timeStart;

      information("Layer {} duration : {} ms", m_iLayerIndex, m_timeDuration.floating_millisecond());

      finished_manual_reset_happening()->set_happening();

   }


   ::pointer < texture >& layer::texture()
   {

      ::i32 iFrameIndex = m_pgpurenderer->m_pgpucontext->m_pgpudevice->get_frame_index3();

      auto & ptexture = m_texturea.element_at_grow(iFrameIndex);

      m_pgpurenderer->defer_constructø(ptexture);

      auto rectangle = m_pgpurenderer->m_pgpucontext->rectangle();

      ::gpu::texture_attributes textureattributes(rectangle);

      ::gpu::texture_flags textureflags;

      textureflags.m_bRenderTarget = true;
      textureflags.m_bTransferTarget = true;
      textureflags.m_bShaderResource = true;

      ptexture->initialize_texture(m_pgpurenderer->m_pgpucontext, textureattributes, textureflags);

      return ptexture;

   }


   ::pointer < texture >& layer::source_texture()
   {

      ::i32 iFrameIndex = m_pgpurenderer->m_pgpucontext->m_pgpudevice->get_frame_index3();

      auto& ptextureSource = m_textureaSource.element_at_grow(iFrameIndex);

      if (m_pgpurenderer->defer_constructø(ptextureSource))
      {

         m_pgpurenderer->m_pgpurendertarget2->initialize_render_target_image(ptextureSource);

      }

      return ptextureSource;

   }


   //::pointer < texture >& layer::target_texture()
   //{
   //   
   //   ::i32 iTargetFrameIndex = m_pgpurendererTarget->_get_frame_index();
   //   
   //   auto & ptextureTarget = m_gputextureaTarget[iTargetFrameIndex];

   //   m_pgpurendererTarget->defer_constructø(ptextureTarget);

   //   auto rectangleTarget = m_pgpurendererTarget->m_pgpucontext->rectangle();

   //   ptextureTarget->initialize_gpu_texture(m_pgpurendererTarget, rectangleTarget);

   //   return ptextureTarget;

   //}

   
   thread_local ::gpu::layer *t_pgpulayer;


   void set_current_layer(::gpu::layer *pgpulayer) { t_pgpulayer = pgpulayer; }
   ::gpu::layer *current_layer() { return t_pgpulayer; }


} // namespace gpu


