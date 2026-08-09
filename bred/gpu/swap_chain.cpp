// Created by camilo on 2025-06-10 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "command_buffer.h"
#include "context.h"
#include "device.h"
#include "window_attachment.h"
#include "fence.h"
#include "renderer.h"
#include "semaphore.h"
#include "swap_chain.h"
#include "texture.h"
#include "texture_synchronization.h"
#include "aura/windowing/window.h"


namespace gpu
{


   swap_chain::swap_chain()
   {

      m_iCurrentSwapChainFrame = 0;

      m_bWindowInitialized = false;

      m_bSwapChainInitialized = false;

   }
      
   
   swap_chain::~swap_chain()
   {

   }


   void swap_chain::on_new_frame()
   {



   }



   void swap_chain::do_output(::gpu::texture * pgputexture)
   {

      //if (eoutput == ::gpu::e_output_swap_chain)
      {

         //auto pgpuwindowattachment = ::gpu::window_attachment::get(m_pgpucontext);

         //auto pgpuswapchain = pgpuwindowattachment->m_pgpucontextWindow->get_swap_chain();

         //if (pgpuswapchain)
         {

            auto pgpucontextSwapChain = m_pgpucontext;

            if (!m_bSwapChainInitialized)
            {

               initialize_gpu_swap_chain(pgpucontextSwapChain->m_pgpurenderer);

            }

            //::cast<gpu::render_target> pgpurendertarget = pgpuswapchain;

            ////if (pgpurendertarget)
            //{

            //  // if (!pgpurendertarget->m_pgpurenderer)
            //   if (!m_pgpurenderer)
            //   {

            //      initialize_render_target(m, m_pgpucontext->size(), nullptr);

            //   }

            //}

            //::cast<renderer> pgpurendererSwapChain = pgpucontextSwapChain->m_pgpurenderer;
            ::cast<renderer> pgpurendererSwapChain = m_pgpurenderer;

            // pgpucontextSwapChain->start_frame();

            // pgpucontextSwapChain->start_layer();

            //::cast<command_buffer> pcommandbufferSwapChain =
            // pgpurendererSwapChain->getCurrentCommandBuffer2(::gpu::current_layer());
            ::pointer<command_buffer> pcommandbufferSwapChain =
               pgpucontextSwapChain->beginSingleTimeCommands(pgpucontextSwapChain->m_pgpudevice->graphics_queue());

            auto pgpuwindowattachment = ::gpu::window_attachment::get(pgpucontextSwapChain);

            pcommandbufferSwapChain->m_iCommandBufferFrameIndex2 = pgpuwindowattachment->m_iCurrentFrame3;

            // pcommandbuffer->begin_command_buffer(false);
            auto iSwapChainFrameIndex = swap_chain_frame_index();

            // if (defer_constructø(pgpucontextSwapChain->m_gpusemaphoreaPresentReady.atø(iSwapChainFrameIndex)))
            //{

            //   pgpucontextSwapChain->m_gpusemaphoreaPresentReady[iSwapChainFrameIndex]->initialize_gpu_semaphore(
            //      m_pgpucontext);
            //}

            auto & framesync = frame(iSwapChainFrameIndex);

            if (::is_set(framesync.m_pgpusemaphoreImageAvailable))
            {

               if (pcommandbufferSwapChain->m_semaphoreaWait.add_unique(framesync.m_pgpusemaphoreImageAvailable))
               {

                  pcommandbufferSwapChain->m_epipelinestageaWait.add(
                     e_pipeline_stage_color_attachment_output_bit);

               }

            }

            pcommandbufferSwapChain->m_pgpufence = framesync.m_pgpufenceInFlight;

            if (framesync.m_pgpusemaphoreRenderFinished)
            {

               pcommandbufferSwapChain->m_semaphoreaSignal.add_unique(framesync.m_pgpusemaphoreRenderFinished);

               m_gpusemaphoreaWait.add_unique(framesync.m_pgpusemaphoreRenderFinished);

            }

            //for (::collection::index i = 0; i < semaphoreaReady.get_count(); i++)
            //{

            if (pgputexture->synchronization())
            {

               auto pgpusemaphoreRenderFinished = pgputexture->synchronization()->m_pgpusemaphoreRenderFinished;

               if (pgpusemaphoreRenderFinished)
               {

                  if (pcommandbufferSwapChain->m_semaphoreaWait.add_unique(pgpusemaphoreRenderFinished))
                  {

                     pcommandbufferSwapChain->m_epipelinestageaWait.add(::gpu::e_pipeline_stage_fragment_shader_bit);

                  }

                  //if (semaphoreaReady.add_unique(pgpusemaphoreRenderFinished))
                  //{
                  //
                  //   epipelinestageaReady.add(::gpu::e_pipeline_stage_fragment_shader_bit);
                  //
                  //}

               }

            }


            //   if (pcommandbufferSwapChain->m_semaphoreaWait.add_unique(semaphoreaReady[i]))
            //   {

            //      pcommandbufferSwapChain->m_epipelinestageaWait.add(epipelinestageaReady[i]);

            //   }

            //}
            // pcommandbufferSwapChain->m_semaphoreaSignal.add_unique(
            //  pgpucontextSwapChain->m_gpusemaphoreaPresentReady.atø(iSwapChainFrameIndex));

            // pswapchain->m_pwindowSwapChain->_main_send([pswapchain, ptextureBackBuffer]()
            //  system()->acme_windowing()
            //  ->_main_send([pswapchain, ptextureBackBuffer]()
            //{


            present(pgputexture, pcommandbufferSwapChain);


            set_present_state(pcommandbufferSwapChain);
            // pgpucontextSwapChain->end_layer();

            // pgpucontextSwapChain->end_frame();
            //}

            // pcommandbuffer->m_semaphoreaWait.add_unique(pswapchain->m_fr->m_semaphoreaSignal);
            //}

            //});

            // prendererBackBuffer->frame_suffix();


            // #endif
            //          pcommandbuffer->submit_command_buffer(nullptr);

            pgpucontextSwapChain->endSingleTimeCommands(pcommandbufferSwapChain);

            swap_buffers();

            framesync.m_pcommandbufferLastSwapChainPresentation = pcommandbufferSwapChain;

            // pswapchain->swap_buffers();

         }

      }

   }


   void swap_chain::create_images()
   {


   }


   void swap_chain::defer_check_swap_chain()
   {

      if (::is_set(m_ptextureaSwapChain) && m_iSwapSeed == m_iCurrentSwapSerial)
      {

         return;

      }

      m_iCurrentSwapSerial = m_iSwapSeed;

      on_new_swap_chain();

   }


   void swap_chain::on_new_swap_chain()
   {

      create_images();

   }


   void swap_chain::initialize_swap_chain_window(::gpu::context * pgpucontext, ::acme::windowing::window* pwindow)
   {

      ASSERT(pgpucontext && pgpucontext->m_etype == ::gpu::context::e_type_window);

      m_pgpucontext = pgpucontext;

      m_pwindowSwapChain = pwindow;

      m_bWindowInitialized = true;

      ::string strType = ::type(pwindow->m_pacmeuserinteraction).name();

      const_char_pointer pszType = strType.c_str();

      information("initialize_swap_chain_window {}", pszType);

   }


   void swap_chain::initialize_gpu_swap_chain(::gpu::renderer * pgpurenderer)
   {

      if (!m_bWindowInitialized || !m_pwindowSwapChain)
      {

         throw ::exception(error_wrong_state);

      }

      if (pgpurenderer->m_pgpucontext != m_pgpucontext
      || m_pgpucontext->m_etype != ::gpu::context::e_type_window)
      {

         throw ::exception(error_wrong_state);

      }

      m_pgpurenderer = pgpurenderer;

      m_bSwapChainInitialized = true;

   }


   void swap_chain::present(::gpu::texture * pgputexture, ::gpu::command_buffer * pgpucommandbuffer)
   {


   }


   void swap_chain::set_present_state(::gpu::command_buffer *pgpucommandbuffer)
   {


   }


   void swap_chain::swap_buffers()
   {


   }


   ::i32 swap_chain::swap_chain_frame_index()
   {

      return m_iCurrentSwapChainFrame;

   }


      ::i32 swap_chain::swap_chain_image_index() { return m_iCurrentSwapChainImage; }


   ::i32 swap_chain::swap_chain_frame_count()
   {

      return -1;

   }


   ::gpu::texture* swap_chain::current_swap_chain_texture()
   {

      defer_check_swap_chain();

      return m_ptextureaSwapChain->element_at(m_iCurrentSwapChainImage);

   }



void swap_chain::on_gpu_context_render_frame(::i32 w, ::i32 h)
{
   
   
}


   bool swap_chain::create_frame_sync(frame_sync &frame)
{

   auto pcontext = m_pgpucontext;
   //;
   //;
   //auto vkdevice = pcontext->logicalDevice();
   // ----------------------------------------------------
   // Fence (CPU → GPU)
   // ----------------------------------------------------

   defer_constructø(frame.m_pgpufenceInFlight);

   frame.m_pgpufenceInFlight->initialize_gpu_fence(m_pgpucontext, true);

   // VkFenceCreateInfo fenceInfo{};
   // fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;

   //// Start signaled so first frame doesn't stall
   // fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

   // if (vkCreateFence(
   //         vkdevice,
   //         &fenceInfo,
   //         nullptr,
   //         &frame.m_vkfenceInFlight) != VK_SUCCESS)
   //{
   //    return false;
   // }

   // ----------------------------------------------------
   // Semaphores (GPU → GPU)
   // ----------------------------------------------------

   defer_constructø(frame.m_pgpusemaphoreImageAvailable);

   frame.m_pgpusemaphoreImageAvailable->initialize_gpu_semaphore(m_pgpucontext);

   defer_constructø(frame.m_pgpusemaphoreRenderFinished);

   frame.m_pgpusemaphoreRenderFinished->initialize_gpu_semaphore(m_pgpucontext);

   // VkSemaphoreCreateInfo semaphoreInfo{};
   // semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

   // if (vkCreateSemaphore(
   //         vkdevice,
   //         &semaphoreInfo,
   //         nullptr,
   //         &frame.m_vksemaphoreImageAvailable) != VK_SUCCESS)
   //{
   //    return false;
   // }

   // if (vkCreateSemaphore(
   //         vkdevice,
   //         &semaphoreInfo,
   //         nullptr,
   //         &frame.m_vksemaphoreRenderFinished) != VK_SUCCESS)
   //{
   //    return false;
   // }

   return true;
}

void swap_chain::destroy_frame_sync(frame_sync &frame)
{

   //::cast<::gpu_vulkan::context> pcontext = m_pgpucontextSwapChain;
   //auto vkdevice = pcontext->logicalDevice();

   // if (frame.m_vkfenceInFlight != VK_NULL_HANDLE)
   //    vkDestroyFence(vkdevice, frame.m_vkfenceInFlight, nullptr);

   // if (frame.m_vksemaphoreImageAvailable != VK_NULL_HANDLE)
   //    vkDestroySemaphore(vkdevice, frame.m_vksemaphoreImageAvailable, nullptr);

   // if (frame.m_vksemaphoreRenderFinished != VK_NULL_HANDLE)
   //    vkDestroySemaphore(vkdevice, frame.m_vksemaphoreRenderFinished, nullptr);

   frame = {};
}


swap_chain::frame_sync &swap_chain::frame(::collection::index iFrameIndex)
{

   if (iFrameIndex < 0 || iFrameIndex > 16)
   {

      throw ::exception(error_failed, "invalid frame index!");
   }

   auto &framesync = m_framesynca.atø(iFrameIndex);

   if (!framesync.m_pgpufenceInFlight)
   {

      create_frame_sync(framesync);
   }

   return framesync;
}

} // namespace direct2d



