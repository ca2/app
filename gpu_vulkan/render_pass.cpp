// From vk_swapchain by camilo on 2025-05-09 02:01 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "physical_device.h"
#include "render_pass.h"

// std
#include <array>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <set>
#include <stdexcept>
#undef min
#undef max


namespace gpu_vulkan
{


   render_pass::render_pass(context* pvkcdeviceRef, VkExtent2D extent)
      : m_pcontext(pvkcdeviceRef), windowExtent(extent)
   {
      //init();
      //m_pvkcrenderpassOld = nullptr;
   }

   
   render_pass::render_pass(context* pvkcdeviceRef, VkExtent2D extent, ::pointer<render_pass> previous)
      : m_pcontext{ pvkcdeviceRef }, windowExtent{ extent }, m_pvkcrenderpassOld{ previous } 
   {
      //init();
      // Cleans up old swap chain since it's no longer needed after resizing
      //m_pvkcrenderpassOld = nullptr;
   }

   
   void render_pass::init() 
   {

      createRenderPassImpl();
      createImageViews();
      createRenderPass();
      createDepthResources();
      createFramebuffers();
      createSyncObjects();
      // Cleans up old swap chain since it's no longer needed after resizing
      m_pvkcrenderpassOld = nullptr;

   }


   render_pass::~render_pass()
   {
      for (auto imageView : m_imageviews) 
      {
         vkDestroyImageView(m_pcontext->device(), imageView, nullptr);
      }
      m_imageviews.clear();

      //if (swapChain != nullptr) {
      //   vkDestroySwapchainKHR(m_pcontext->device(), swapChain, nullptr);
      //   swapChain = nullptr;
      //}

      for (int i = 0; i < depthImages.size(); i++) 
      {
         vkDestroyImageView(m_pcontext->device(), depthImageViews[i], nullptr);
         vkDestroyImage(m_pcontext->device(), depthImages[i], nullptr);
         vkFreeMemory(m_pcontext->device(), depthImageMemorys[i], nullptr);
      }

      for (auto framebuffer : m_framebuffers)
      {
         vkDestroyFramebuffer(m_pcontext->device(), framebuffer, nullptr);
      }

      vkDestroyRenderPass(m_pcontext->device(), m_vkrenderpass, nullptr);

      // cleanup synchronization objects
      for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
      {
         vkDestroySemaphore(m_pcontext->device(), renderFinishedSemaphores[i], nullptr);
         vkDestroySemaphore(m_pcontext->device(), imageAvailableSemaphores[i], nullptr);
         vkDestroyFence(m_pcontext->device(), inFlightFences[i], nullptr);
      }
   }

   
   VkResult render_pass::acquireNextImage(uint32_t* imageIndex) 
   {

      //vkWaitForFences(
      //   m_pcontext->device(),
      //   1,
      //   &inFlightFences[currentFrame],
      //   VK_TRUE,
      //   std::numeric_limits<uint64_t>::max());

      //VkResult result = vkAcquireNextImageKHR(
      //   m_pcontext->device(),
      //   swapChain,
      //   std::numeric_limits<uint64_t>::max(),
      //   imageAvailableSemaphores[currentFrame],  // must be a not signaled semaphore
      //   VK_NULL_HANDLE,
      //   imageIndex);

      return VK_ERROR_FEATURE_NOT_PRESENT;

   }


   VkResult render_pass::submitCommandBuffers(
      const VkCommandBuffer* buffers, uint32_t* imageIndex)
   {

      //if (imagesInFlight[*imageIndex] != VK_NULL_HANDLE) {
      //   vkWaitForFences(m_pcontext->device(), 1, &imagesInFlight[*imageIndex], VK_TRUE, UINT64_MAX);
      //}
      //imagesInFlight[*imageIndex] = inFlightFences[currentFrame];

      //VkSubmitInfo submitInfo = {};
      //submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

      //VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
      //VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
      //submitInfo.waitSemaphoreCount = 1;
      //submitInfo.pWaitSemaphores = waitSemaphores;
      //submitInfo.pWaitDstStageMask = waitStages;

      //submitInfo.commandBufferCount = 1;
      //submitInfo.pCommandBuffers = buffers;

      //VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };
      //submitInfo.signalSemaphoreCount = 1;
      //submitInfo.pSignalSemaphores = signalSemaphores;

      //vkResetFences(m_pcontext->device(), 1, &inFlightFences[currentFrame]);
      //if (vkQueueSubmit(m_pcontext->graphicsQueue(), 1, &submitInfo, inFlightFences[currentFrame]) !=
      //   VK_SUCCESS) {
      //   throw ::exception(error_failed,"failed to submit draw command buffer!");
      //}

      //VkPresentInfoKHR presentInfo = {};
      //presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

      //presentInfo.waitSemaphoreCount = 1;
      //presentInfo.pWaitSemaphores = signalSemaphores;

      //VkSwapchainKHR swapChains[] = { swapChain };
      //presentInfo.swapchainCount = 1;
      //presentInfo.pSwapchains = swapChains;

      //presentInfo.pImageIndices = imageIndex;

      //auto result = vkQueuePresentKHR(m_pcontext->presentQueue(), &presentInfo);

      //currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;

      //return result;

      return VK_SUCCESS;

   }


   void render_pass::createRenderPassImpl() 
   {

      //SwapChainSupportDetails swapChainSupport = m_pcontext->getSwapChainSupport();

      //VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
      //VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
      //VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

      //uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
      //if (swapChainSupport.capabilities.maxImageCount > 0 &&
      //   imageCount > swapChainSupport.capabilities.maxImageCount) {
      //   imageCount = swapChainSupport.capabilities.maxImageCount;
      //}

      //VkSwapchainCreateInfoKHR createInfo = {};
      //createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
      //createInfo.surface = m_pcontext->surface();

      //createInfo.minImageCount = imageCount;
      //createInfo.imageFormat = surfaceFormat.format;
      //createInfo.imageColorSpace = surfaceFormat.colorSpace;
      //createInfo.imageExtent = extent;
      //createInfo.imageArrayLayers = 1;
      //createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

      //QueueFamilyIndices indices = m_pcontext->findPhysicalQueueFamilies();
      //uint32_t queueFamilyIndices[] = { indices.graphicsFamily, indices.presentFamily };

      //if (indices.graphicsFamily != indices.presentFamily) {
      //   createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
      //   createInfo.queueFamilyIndexCount = 2;
      //   createInfo.pQueueFamilyIndices = queueFamilyIndices;
      //}
      //else {
      //   createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
      //   createInfo.queueFamilyIndexCount = 0;      // Optional
      //   createInfo.pQueueFamilyIndices = nullptr;  // Optional
      //}

      //createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
      //createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

      //createInfo.presentMode = presentMode;
      //createInfo.clipped = VK_TRUE;

      //createInfo.oldSwapchain = oldSwapChain == nullptr ? VK_NULL_HANDLE : oldSwapChain->swapChain;

      //if (vkCreateSwapchainKHR(m_pcontext->device(), &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
      //   throw ::exception(error_failed,"failed to create swap chain!");
      //}

      //// we only specified a minimum number of images in the swap chain, so the implementation is
      //// allowed to create a swap chain with more. That's why we'll first query the final number of
      //// images with vkGetSwapchainImagesKHR, then resize the container and finally call it again to
      //// retrieve the handles.
      //vkGetSwapchainImagesKHR(m_pcontext->device(), swapChain, &imageCount, nullptr);
      //swapChainImages.resize(imageCount);
      //vkGetSwapchainImagesKHR(m_pcontext->device(), swapChain, &imageCount, swapChainImages.data());

      //swapChainImageFormat = surfaceFormat.format;
      //extent = extent;

   }

   
   void render_pass::createImageViews() 
   {

      m_imageviews.resize(m_images.size());

      for (size_t i = 0; i < m_images.size(); i++) 
      {

         VkImageViewCreateInfo viewInfo{};
         viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
         viewInfo.image = m_images[i];
         viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
         viewInfo.format = m_formatImage;
         viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
         viewInfo.subresourceRange.baseMipLevel = 0;
         viewInfo.subresourceRange.levelCount = 1;
         viewInfo.subresourceRange.baseArrayLayer = 0;
         viewInfo.subresourceRange.layerCount = 1;

         if (vkCreateImageView(m_pcontext->device(), &viewInfo, nullptr, &m_imageviews[i]) !=
            VK_SUCCESS) 
         {
            throw ::exception(error_failed,"failed to create texture image view!");
         }

      }

   }


   void render_pass::createRenderPass() 
   {

      VkAttachmentDescription depthAttachment{};
      depthAttachment.format = findDepthFormat();
      depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
      depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
      depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
      depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
      depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
      depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
      depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

      VkAttachmentReference depthAttachmentRef{};
      depthAttachmentRef.attachment = 1;
      depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

      VkAttachmentDescription colorAttachment = {};
      colorAttachment.format = getImageFormat();
      colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
      colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
      colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
      colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
      colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
      colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
      colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

      VkAttachmentReference colorAttachmentRef = {};
      colorAttachmentRef.attachment = 0;
      colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

      VkSubpassDescription subpass = {};
      subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
      subpass.colorAttachmentCount = 1;
      subpass.pColorAttachments = &colorAttachmentRef;
      subpass.pDepthStencilAttachment = &depthAttachmentRef;

      VkSubpassDependency dependency = {};
      dependency.dstSubpass = 0;
      dependency.dstAccessMask =
         VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
      dependency.dstStageMask =
         VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
      dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
      dependency.srcAccessMask = 0;
      dependency.srcStageMask =
         VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;


      std::array<VkAttachmentDescription, 2> attachments = { colorAttachment, depthAttachment };
      VkRenderPassCreateInfo renderPassInfo = {};
      renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
      renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
      renderPassInfo.pAttachments = attachments.data();
      renderPassInfo.subpassCount = 1;
      renderPassInfo.pSubpasses = &subpass;
      renderPassInfo.dependencyCount = 1;
      renderPassInfo.pDependencies = &dependency;

      if (vkCreateRenderPass(m_pcontext->device(), &renderPassInfo, nullptr, &m_vkrenderpass) != VK_SUCCESS) 
      {

         throw ::exception(error_failed,"failed to create render pass!");

      }

   }


   void render_pass::createFramebuffers() 
   {

      m_framebuffers.resize(imageCount());

      for (size_t i = 0; i < imageCount(); i++) 
      {

         std::array<VkImageView, 2> attachments = { m_imageviews[i], depthImageViews[i] };

         VkExtent2D extent = getExtent();
         VkFramebufferCreateInfo framebufferInfo = {};
         framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
         framebufferInfo.renderPass = m_vkrenderpass;
         framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
         framebufferInfo.pAttachments = attachments.data();
         framebufferInfo.width = extent.width;
         framebufferInfo.height = extent.height;
         framebufferInfo.layers = 1;

         if (vkCreateFramebuffer(
            m_pcontext->device(),
            &framebufferInfo,
            nullptr,
            &m_framebuffers[i]) != VK_SUCCESS) 
         {

            throw ::exception(error_failed,"failed to create framebuffer!");

         }

      }

   }


   void render_pass::createDepthResources()
   {

      VkFormat depthFormat = findDepthFormat();

      m_formatDepth = depthFormat;

      VkExtent2D extent = getExtent();

      depthImages.resize(imageCount());
      depthImageMemorys.resize(imageCount());
      depthImageViews.resize(imageCount());

      for (int i = 0; i < depthImages.size(); i++) 
      {

         VkImageCreateInfo imageInfo{};
         imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
         imageInfo.imageType = VK_IMAGE_TYPE_2D;
         imageInfo.extent.width = extent.width;
         imageInfo.extent.height = extent.height;
         imageInfo.extent.depth = 1;
         imageInfo.mipLevels = 1;
         imageInfo.arrayLayers = 1;
         imageInfo.format = depthFormat;
         imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
         imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
         imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
         imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
         imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
         imageInfo.flags = 0;

         m_pcontext->createImageWithInfo(
            imageInfo,
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
            depthImages[i],
            depthImageMemorys[i]);

         VkImageViewCreateInfo viewInfo{};
         viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
         viewInfo.image = depthImages[i];
         viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
         viewInfo.format = depthFormat;
         viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
         viewInfo.subresourceRange.baseMipLevel = 0;
         viewInfo.subresourceRange.levelCount = 1;
         viewInfo.subresourceRange.baseArrayLayer = 0;
         viewInfo.subresourceRange.layerCount = 1;

         if (vkCreateImageView(m_pcontext->device(), &viewInfo, nullptr, &depthImageViews[i]) != VK_SUCCESS) 
         {
            throw ::exception(error_failed,"failed to create texture image view!");
         }

      }

   }


   void render_pass::createSyncObjects() 
   {

      imageAvailable.resize(MAX_FRAMES_IN_FLIGHT);
      imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
      renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
      inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
      imagesInFlight.resize(imageCount(), VK_NULL_HANDLE);

      VkSemaphoreCreateInfo semaphoreInfo = {};
      semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

      VkFenceCreateInfo fenceInfo = {};
      fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
      fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

      for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) 
      {
         imageAvailable[i] = 0;
         if (vkCreateSemaphore(m_pcontext->device(), &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) !=
            VK_SUCCESS ||
            vkCreateSemaphore(m_pcontext->device(), &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) !=
            VK_SUCCESS ||
            vkCreateFence(m_pcontext->device(), &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) 
         {
            throw ::exception(error_failed,"failed to create synchronization objects for a frame!");
         }
      }
   }

   //VkSurfaceFormatKHR render_pass::chooseSwapSurfaceFormat(
   //   const ::array<VkSurfaceFormatKHR>& availableFormats) {
   //   for (const auto& availableFormat : availableFormats) {
   //      // SRGB can be changed to "UNORM" instead
   //      if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
   //         availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
   //         return availableFormat;
   //      }
   //   }

   //   return availableFormats[0];
   //}

   //VkPresentModeKHR render_pass::chooseSwapPresentMode(
   //   const ::array<VkPresentModeKHR>& availablePresentModes) {
   //   for (const auto& availablePresentMode : availablePresentModes) {
   //      if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
   //         std::cout << "Present mode: Mailbox" << std::endl;
   //         return availablePresentMode;
   //      }
   //   }

   //   // for (const auto &availablePresentMode : availablePresentModes) {
   //   //   if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
   //   //     std::cout << "Present mode: Immediate" << std::endl;
   //   //     return availablePresentMode;
   //   //   }
   //   // }

   //   std::cout << "Present mode: V-Sync" << std::endl;
   //   return VK_PRESENT_MODE_FIFO_KHR;
   //}

   //VkExtent2D render_pass::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
   //   if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
   //      return capabilities.currentExtent;
   //   }
   //   else {
   //      VkExtent2D actualExtent = windowExtent;
   //      actualExtent.width = std::max(
   //         capabilities.minImageExtent.width,
   //         std::min(capabilities.maxImageExtent.width, actualExtent.width));
   //      actualExtent.height = std::max(
   //         capabilities.minImageExtent.height,
   //         std::min(capabilities.maxImageExtent.height, actualExtent.height));

   //      return actualExtent;
   //   }
   //}

   VkFormat render_pass::findDepthFormat() 
   {

      return m_pcontext->m_pphysicaldevice->findSupportedFormat(
         { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
         VK_IMAGE_TILING_OPTIMAL,
         VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);

   }

} // namespace gpu_vulkan



