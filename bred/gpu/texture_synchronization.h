// Created by camilo on 2026-07-28 01:08 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


namespace gpu
{


   //class binding_slot_set;

   class CLASS_DECL_BRED texture_synchronization : 
      virtual public ::particle
   {
   public:

      //::gpu_vulkan::render_pass *   m_prenderpass = nullptr;
      //::gpu_vulkan::render_target * m_prendertarget = nullptr;
      ::gpu::texture *m_ptexture = nullptr;


      // bool                          m_bAdvancedPipelineSynchronization = false;
      int m_iImageAvailable = -1;
      int m_iRendering = -1;
      // VkSemaphore                   m_vksemaphoreAvailable = VK_NULL_HANDLE;
      // VkSemaphore                   m_vksemaphoreRenderFinished = VK_NULL_HANDLE;
      // VkFence                       m_vkfenceInFlight2 = VK_NULL_HANDLE;
      // VkFence                       m_vkfenceImageInFlight = VK_NULL_HANDLE;
      ::pointer<::gpu::semaphore> m_pgpusemaphoreAvailable;
      ::pointer<::gpu::semaphore> m_pgpusemaphoreRenderFinished;
      ::pointer<::gpu::fence> m_pgpufenceInFlight;
      ::pointer<::gpu::fence> m_pgpufenceImageInFlight;

      texture_synchronization();
      ~texture_synchronization();

      //VkFramebuffer get_frame_buffer(::gpu_vulkan::render_pass *prenderpass);
      //VkFramebuffer _get_frame_buffer(::gpu_vulkan::render_pass *prenderpass);

      // VkFence in_flight_fence();

      ::gpu::fence *in_flight_fence();

      // virtual texture_synchronization& synchronization(::gpu::render_target * prendertarget);
   };


} // namespace gpu
   


