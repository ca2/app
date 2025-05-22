#pragma once


#include "render_pass.h"


namespace gpu_vulkan
{


   class swap_chain_render_pass :
      virtual public render_pass
   {
   public:
      static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

      swap_chain_render_pass(context* pvkcdeviceRef, VkExtent2D windowExtent);
      swap_chain_render_pass(context* pvkcdeviceRef, VkExtent2D windowExtent, ::pointer <render_pass>previous);
      ~swap_chain_render_pass();

      swap_chain_render_pass(const swap_chain_render_pass&) = delete;
      swap_chain_render_pass& operator=(const swap_chain_render_pass&) = delete;

      //VkFramebuffer getFrameBuffer(int index) { return swapChainFramebuffers[index]; }
      //VkRenderPass getRenderPass() { return m_vkrenderpass; }
      //VkImageView getImageView(int index) { return swapChainImageViews[index]; }
      //size_t imageCount() { return swapChainImages.size(); }
      //VkFormat getSwapChainImageFormat() { return swapChainImageFormat; }
      //VkExtent2D getSwapChainExtent() { return m_extent; }
      //uint32_t width() { return m_extent.width; }
      //uint32_t height() { return m_extent.height; }

      //float extentAspectRatio() {
      //   return static_cast<float>(m_extent.width) / static_cast<float>(m_extent.height);
      //}
      VkFormat findDepthFormat();

      VkResult acquireNextImage(uint32_t* imageIndex);
      VkResult submitCommandBuffers(const VkCommandBuffer* buffers, uint32_t* imageIndex);

      //bool compareSwapFormats(const swap_chain_render_pass& m_swapchain) const {
      //   return m_swapchain.swapChainDepthFormat == swapChainDepthFormat &&
      //      m_swapchain.swapChainImageFormat == swapChainImageFormat;
      //}

   public:
      void init();
      void createRenderPassImpl();
      void createImageViews();
      void createDepthResources();
      void createRenderPass();
      void createFramebuffers();
      void createSyncObjects();

      // Helper functions
      VkSurfaceFormatKHR chooseSwapSurfaceFormat(
         const ::array<VkSurfaceFormatKHR>& availableFormats);
      VkPresentModeKHR chooseSwapPresentMode(
         const ::array<VkPresentModeKHR>& availablePresentModes);
      VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

      /*VkFormat swapChainImageFormat;
      VkFormat swapChainDepthFormat;
      VkExtent2D m_extent;

      ::array<VkFramebuffer> swapChainFramebuffers;
      VkRenderPass m_vkrenderpass;

      ::array<VkImage> depthImages;
      ::array<VkDeviceMemory> depthImageMemorys;
      ::array<VkImageView> depthImageViews;
      ::array<VkImage> swapChainImages;
      ::array<VkImageView> swapChainImageViews;

      ::pointer < context > m_pcontext;
      VkExtent2D windowExtent;*/

      VkSwapchainKHR m_vkswapchain;
      //::pointer<swap_chain_render_pass> oldSwapChain;

      //::array<VkSemaphore> imageAvailableSemaphores;
      //::array<VkSemaphore> renderFinishedSemaphores;
      //::array<VkFence> inFlightFences;
      //::array<VkFence> imagesInFlight;
      //size_t currentFrame = 0;

   };


}  // namespace gpu_vulkan


