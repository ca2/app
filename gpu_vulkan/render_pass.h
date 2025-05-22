// From vk_swapchain by camilo on 2025-05-09 01:40 <3ThomasBorregaardSorensen!!
#pragma once


#include "context.h"

// vulkan headers
#include "_gpu_vulkan.h"

// std lib headers
#include <string>
#include <vector>
#include <memory>


namespace gpu_vulkan
{


   class CLASS_DECL_GPU_VULKAN render_pass :
      virtual public ::particle
   {
   public:


      static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

      render_pass(context* pvkcdeviceRef, VkExtent2D windowExtent);
      render_pass(context* pvkcdeviceRef, VkExtent2D windowExtent, ::pointer <render_pass>previous);
      ~render_pass();

      render_pass(const render_pass&) = delete;
      render_pass& operator=(const render_pass&) = delete;

      VkFramebuffer getFrameBuffer(int index) { return m_framebuffers[index]; }
      VkRenderPass getRenderPass() { return m_vkrenderpass; }
      VkImageView getImageView(int index) { return m_imageviews[index]; }
      size_t imageCount() { return m_images.size(); }
      VkFormat getImageFormat() { return m_formatImage; }
      VkExtent2D getExtent() { return m_extent; }
      uint32_t width() { return m_extent.width; }
      uint32_t height() { return m_extent.height; }

      float extentAspectRatio() {
         return static_cast<float>(m_extent.width) / static_cast<float>(m_extent.height);
      }
      virtual VkFormat findDepthFormat();

      virtual VkResult acquireNextImage(uint32_t* imageIndex);
      virtual VkResult submitCommandBuffers(const VkCommandBuffer* buffers, uint32_t* imageIndex);

      bool compareFormats(const render_pass& renderpass) const {
         return renderpass.m_formatDepth == m_formatDepth &&
            renderpass.m_formatImage == m_formatImage;
      }

      virtual void init();
      virtual void createRenderPassImpl();
      virtual void createImageViews();
      virtual void createDepthResources();
      virtual void createRenderPass();
      virtual void createFramebuffers();
      virtual void createSyncObjects();
      //virtual void defer_layout();
      //// Helper functions
      //VkSurfaceFormatKHR chooseSwapSurfaceFormat(
      //   const ::array<VkSurfaceFormatKHR>& availableFormats);
      //VkPresentModeKHR chooseSwapPresentMode(
      //   const ::array<VkPresentModeKHR>& availablePresentModes);
      //VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

      VkFormat m_formatImage;
      VkFormat m_formatDepth;
      VkExtent2D m_extent;

      ::array<VkFramebuffer> m_framebuffers;
      VkRenderPass m_vkrenderpass;

      ::array<VkImage> depthImages;
      ::array<VkDeviceMemory> depthImageMemorys;
      ::array<VkImageView> depthImageViews;
      ::array<VkImage> m_images;
      ::array<VkImageView> m_imageviews;

      context* m_pcontext;
      VkExtent2D windowExtent;

      //VkSwapchainKHR swapChain;
      ::pointer<render_pass> m_pvkcrenderpassOld;

      ::int_array imageAvailable;
      ::array<VkSemaphore> imageAvailableSemaphores;
      ::array<VkSemaphore> renderFinishedSemaphores;
      ::array<VkFence> inFlightFences;
      ::array<VkFence> imagesInFlight;
      size_t currentFrame = 0;
   };


}  // namespace gpu_vulkan



