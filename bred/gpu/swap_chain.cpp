// Created by camilo on 2025-06-10 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "context.h"
#include "device.h"
#include "fence.h"
#include "renderer.h"
#include "semaphore.h"
#include "swap_chain.h"
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

      const char *pszType = strType.c_str();

      information("initialize_swap_chain_window {}", pszType);

   }


   void swap_chain::initialize_gpu_swap_chain(::gpu::renderer * pgpurenderer)
   {

      ASSERT(m_bWindowInitialized && m_pwindowSwapChain);

      ASSERT(pgpurenderer->m_pgpucontext == m_pgpucontext
      && m_pgpucontext->m_etype == ::gpu::context::e_type_window);

      m_pgpurenderer = pgpurenderer;

      m_bSwapChainInitialized = true;

   }


   void swap_chain::present(::gpu::texture * pgputexture)
   {


   }


   void swap_chain::set_present_state()
   {


   }


   void swap_chain::swap_buffers()
   {


   }


   int swap_chain::swap_chain_frame_index()
   {

      return m_iCurrentSwapChainFrame;

   }


      int swap_chain::swap_chain_image_index() { return m_iCurrentSwapChainImage; }


   int swap_chain::swap_chain_frame_count()
   {

      return -1;

   }


   ::gpu::texture* swap_chain::current_swap_chain_texture()
   {

      defer_check_swap_chain();

      return m_ptextureaSwapChain->element_at(m_iCurrentSwapChainFrame);

   }



void swap_chain::on_gpu_context_render_frame(int w, int h)
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



