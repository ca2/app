// From vk_swapchain by camilo on 2025-05-09 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "offscreen_render_pass.h"
#include "initializers.h"
#include "physical_device.h"

using namespace vulkan;

//#include "tools.h"

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


#define VK_CHECK(x) do { VkResult err = x; if (err) { std::cerr << "Detected Vulkan error: " << err << std::endl; abort(); } } while (0)


namespace gpu_vulkan
{


   offscreen_render_pass::offscreen_render_pass(context* pvkcdeviceRef, VkExtent2D extent)
      : render_pass(pvkcdeviceRef, extent)
   {

   }


   offscreen_render_pass::offscreen_render_pass(context* pvkcdeviceRef, VkExtent2D extent, ::pointer<render_pass> previous)
      : render_pass(pvkcdeviceRef, extent, previous)
   {

   }


   void offscreen_render_pass::init()
   {

      createRenderPassImpl();
      createImageViews();
      createRenderPass();
      createDepthResources();
      createFramebuffers();
      createSyncObjects();

   }


   offscreen_render_pass::~offscreen_render_pass() 
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

      //for (auto framebuffer : m_framebuffers) {
      //   vkDestroyFramebuffer(m_pcontext->device(), framebuffer, nullptr);
      //}

      //vkDestroyRenderPass(m_pcontext->device(), renderPass, nullptr);

      //// cleanup synchronization objects
      //for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
      //   vkDestroySemaphore(m_pcontext->device(), renderFinishedSemaphores[i], nullptr);
      //   vkDestroySemaphore(m_pcontext->device(), imageAvailableSemaphores[i], nullptr);
      //   vkDestroyFence(m_pcontext->device(), inFlightFences[i], nullptr);
      //}
   }


   VkResult offscreen_render_pass::acquireNextImage(uint32_t* imageIndex) 
   {

      vkWaitForFences(
         m_pcontext->device(),
         1,
         &inFlightFences[currentFrame],
         VK_TRUE,
         std::numeric_limits<uint64_t>::max());

      *imageIndex = (*imageIndex + 1) % m_images.size();

      //VkResult result = vkAcquireNextImageKHR(
      //   m_pcontext->device(),
      //   swapChain,
      //   std::numeric_limits<uint64_t>::max(),
      //   imageAvailableSemaphores[currentFrame],  // must be a not signaled semaphore
      //   VK_NULL_HANDLE,
      //   imageIndex);

      return VK_SUCCESS;

   }


   VkResult offscreen_render_pass::submitCommandBuffers(const VkCommandBuffer* buffers, uint32_t* imageIndex)
   {

      if (imagesInFlight[*imageIndex] != VK_NULL_HANDLE)
      {

         vkWaitForFences(m_pcontext->device(), 1, &imagesInFlight[*imageIndex], VK_TRUE, UINT64_MAX);

      }

      imagesInFlight[*imageIndex] = inFlightFences[currentFrame];

      VkSubmitInfo submitInfo = {};
      submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

      VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
      VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
      if (imageAvailable[currentFrame] > 0)
      {
         submitInfo.waitSemaphoreCount = 1;
         submitInfo.pWaitSemaphores = waitSemaphores;
         submitInfo.pWaitDstStageMask = waitStages;
      }

      submitInfo.commandBufferCount = 1;
      submitInfo.pCommandBuffers = buffers;

      VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };
      submitInfo.signalSemaphoreCount = 1;
      submitInfo.pSignalSemaphores = signalSemaphores;

      vkResetFences(m_pcontext->device(), 1, &inFlightFences[currentFrame]);

      auto queueGraphics = m_pcontext->graphicsQueue();

      if (vkQueueSubmit(queueGraphics, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) 
      {

         throw ::exception(error_failed,"failed to submit draw command buffer!");
         
      }

      VK_CHECK(vkWaitForFences(m_pcontext->device(), 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX));

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

      return VK_SUCCESS;

   }



   VkResult offscreen_render_pass::submitSamplingWork(const VkCommandBuffer buffer, uint32_t* imageIndex)
   {

      if (imagesInFlight[*imageIndex] != VK_NULL_HANDLE)
      {

         vkWaitForFences(m_pcontext->device(), 1, &imagesInFlight[*imageIndex], VK_TRUE, UINT64_MAX);

      }

      imagesInFlight[*imageIndex] = inFlightFences[currentFrame];

      VkSubmitInfo submitInfo = {};
      submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

      VkSemaphore waitSemaphores[] = { renderFinishedSemaphores[currentFrame] };
      VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
      submitInfo.waitSemaphoreCount = 1;
      submitInfo.pWaitSemaphores = waitSemaphores;
      submitInfo.pWaitDstStageMask = waitStages;

      submitInfo.commandBufferCount = 1;
      submitInfo.pCommandBuffers = &buffer;

      VkSemaphore signalSemaphores[] = { imageAvailableSemaphores[currentFrame] };
      submitInfo.signalSemaphoreCount = 1;
      submitInfo.pSignalSemaphores = signalSemaphores;
      imageAvailable[currentFrame]++;
      if (imageAvailable[currentFrame] <= 0)
      {
         imageAvailable[currentFrame]=1;
      }

      vkResetFences(m_pcontext->device(), 1, &inFlightFences[currentFrame]);

      if (vkQueueSubmit(m_pcontext->graphicsQueue(), 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS)
      {

         throw ::exception(error_failed,"failed to submit draw command buffer!");

      }

      VK_CHECK(vkWaitForFences(m_pcontext->device(), 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX));

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

      return VK_SUCCESS;

   }


   void offscreen_render_pass::createRenderPassImpl()
   {

      ////SwapChainSupportDetails swapChainSupport = m_pcontext->getSwapChainSupport();

      ////VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
      ////VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
      ////VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

      ////uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
      ////if (swapChainSupport.capabilities.maxImageCount > 0 &&
      ////   imageCount > swapChainSupport.capabilities.maxImageCount) {
      ////   imageCount = swapChainSupport.capabilities.maxImageCount;
      ////}

      ////VkSwapchainCreateInfoKHR createInfo = {};
      ////createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
      ////createInfo.surface = m_pcontext->surface();

      ////createInfo.minImageCount = imageCount;
      ////createInfo.imageFormat = surfaceFormat.format;
      ////createInfo.imageColorSpace = surfaceFormat.colorSpace;
      ////createInfo.imageExtent = extent;
      ////createInfo.imageArrayLayers = 1;
      ////createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

      ////QueueFamilyIndices indices = m_pcontext->findPhysicalQueueFamilies();
      ////uint32_t queueFamilyIndices[] = { indices.graphicsFamily, indices.presentFamily };

      ////if (indices.graphicsFamily != indices.presentFamily) {
      ////   createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
      ////   createInfo.queueFamilyIndexCount = 2;
      ////   createInfo.pQueueFamilyIndices = queueFamilyIndices;
      ////}
      ////else {
      ////   createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
      ////   createInfo.queueFamilyIndexCount = 0;      // Optional
      ////   createInfo.pQueueFamilyIndices = nullptr;  // Optional
      ////}

      ////createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
      ////createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

      ////createInfo.presentMode = presentMode;
      ////createInfo.clipped = VK_TRUE;

      ////createInfo.oldSwapchain = oldSwapChain == nullptr ? VK_NULL_HANDLE : oldSwapChain->swapChain;

      ////if (vkCreateSwapchainKHR(m_pcontext->device(), &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
      ////   throw ::exception(error_failed,"failed to create swap chain!");
      ////}

      ////// we only specified a minimum number of images in the swap chain, so the implementation is
      ////// allowed to create a swap chain with more. That's why we'll first query the final number of
      ////// images with vkGetSwapchainImagesKHR, then resize the container and finally call it again to
      ////// retrieve the handles.
      ////vkGetSwapchainImagesKHR(m_pcontext->device(), swapChain, &imageCount, nullptr);
      ////swapChainImages.resize(imageCount);
      ////vkGetSwapchainImagesKHR(m_pcontext->device(), swapChain, &imageCount, swapChainImages.data());

      ////swapChainImageFormat = surfaceFormat.format;
      ////swapChainExtent = extent;


      ////offscreenPass.width = FB_DIM;
      ////offscreenPass.height = FB_DIM;

      m_extent.width = windowExtent.width;
      m_extent.height = windowExtent.height;

#ifdef WINDOWS_DESKTOP
      m_formatImage = VK_FORMAT_B8G8R8A8_UNORM;
#else
      m_formatImage = VK_FORMAT_R8G8B8A8_UNORM;
#endif

      ::cast < context > pcontext = m_pcontext;

      //// Find a suitable depth format
      VkFormat fbDepthFormat;
      VkBool32 validDepthFormat = getSupportedDepthFormat(
         pcontext->m_pphysicaldevice->m_physicaldevice, &fbDepthFormat);
      ASSERT(validDepthFormat);

      //// Color attachment
      VkImageCreateInfo image = initializers::imageCreateInfo();
      image.imageType = VK_IMAGE_TYPE_2D;
      image.format = m_formatImage;
      image.extent.width = m_extent.width;
      image.extent.height = m_extent.height;
      image.extent.depth = 1;
      image.mipLevels = 1;
      image.arrayLayers = 1;
      image.samples = VK_SAMPLE_COUNT_1_BIT;
      image.tiling = VK_IMAGE_TILING_OPTIMAL;
      //// We will sample directly from the color attachment
      image.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT |
         VK_IMAGE_USAGE_TRANSFER_SRC_BIT;

      //VkMemoryAllocateInfo memAlloc = initializers::memory_allocate_info();
      //VkMemoryRequirements memReqs;

      m_images.resize(MAX_FRAMES_IN_FLIGHT);
      m_imagememories.resize(MAX_FRAMES_IN_FLIGHT);

      for (int i = 0; i < m_images.size(); i++)
      {

         m_pcontext->createImageWithInfo(
            image,
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
            m_images[i],
            m_imagememories[i]
         );
         //VK_CHECK_RESULT(vkCreateImage(m_pcontext->device(), &image, nullptr, &m_images[i]));
         //vkGetImageMemoryRequirements(m_pcontext->device(), m_images[i], &memReqs);
         //memAlloc.allocationSize = memReqs.size;
         //memAlloc.memoryTypeIndex = m_pcontext->findMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
         //VK_CHECK_RESULT(vkAllocateMemory(m_pcontext->device(), &memAlloc, nullptr, &m_imagememories[i]));
         //VK_CHECK_RESULT(vkBindImageMemory(m_pcontext->device(), m_images[i], m_imagememories[i], 0));

      }

      //VkImageViewCreateInfo colorImageView = initializers::imageViewCreateInfo();
      //colorImageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
      //colorImageView.format = m_formatImage;
      //colorImageView.subresourceRange = {};
      //colorImageView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
      //colorImageView.subresourceRange.baseMipLevel = 0;
      //colorImageView.subresourceRange.levelCount = 1;
      //colorImageView.subresourceRange.baseArrayLayer = 0;
      //colorImageView.subresourceRange.layerCount = 1;
      //colorImageView.image = offscreenPass.color.image;
      //VK_CHECK_RESULT(vkCreateImageView(context, &colorImageView, nullptr, &offscreenPass.color.view));

      // Create sampler to sample from the attachment in the fragment shader
      VkSamplerCreateInfo samplerInfo = initializers::samplerCreateInfo();
      samplerInfo.magFilter = VK_FILTER_LINEAR;
      samplerInfo.minFilter = VK_FILTER_LINEAR;
      samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
      samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
      samplerInfo.addressModeV = samplerInfo.addressModeU;
      samplerInfo.addressModeW = samplerInfo.addressModeU;
      samplerInfo.mipLodBias = 0.0f;
      samplerInfo.maxAnisotropy = 1.0f;
      samplerInfo.minLod = 0.0f;
      samplerInfo.maxLod = 1.0f;
      samplerInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
      VK_CHECK_RESULT(vkCreateSampler(m_pcontext->device(), &samplerInfo, nullptr, &m_vksampler));

      //// Depth stencil attachment
      //image.format = fbDepthFormat;
      //image.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;

      //depthImages.resize(MAX_FRAMES_IN_FLIGHT);
      //depthImageMemorys.resize(MAX_FRAMES_IN_FLIGHT);

      //for (int i = 0; i < depthImages.size(); i++)
      //{
      //   VK_CHECK_RESULT(vkCreateImage(m_pcontext->device(), &image, nullptr, &depthImages[i]));
      //   vkGetImageMemoryRequirements(m_pcontext->device(), depthImages[i], &memReqs);
      //   memAlloc.allocationSize = memReqs.size;
      //   memAlloc.memoryTypeIndex = m_pcontext->findMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
      //   VK_CHECK_RESULT(vkAllocateMemory(m_pcontext->device(), &memAlloc, nullptr, &depthImageMemorys[i]));
      //   VK_CHECK_RESULT(vkBindImageMemory(m_pcontext->device(), depthImages[i], depthImageMemorys[i], 0));

      //}

      //VkImageViewCreateInfo depthStencilView = initializers::imageViewCreateInfo();
      //depthStencilView.viewType = VK_IMAGE_VIEW_TYPE_2D;
      //depthStencilView.format = fbDepthFormat;
      //depthStencilView.flags = 0;
      //depthStencilView.subresourceRange = {};
      //depthStencilView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
      //if (fbDepthFormat >= VK_FORMAT_D16_UNORM_S8_UINT) {
      //   depthStencilView.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
      //}
      //depthStencilView.subresourceRange.baseMipLevel = 0;
      //depthStencilView.subresourceRange.levelCount = 1;
      //depthStencilView.subresourceRange.baseArrayLayer = 0;
      //depthStencilView.subresourceRange.layerCount = 1;
      //depthStencilView.image = offscreenPass.depth.image;
      //VK_CHECK_RESULT(vkCreateImageView(context, &depthStencilView, nullptr, &offscreenPass.depth.view));

      //// Create a separate render pass for the offscreen rendering as it may differ from the one used for scene rendering

      //std::array<VkAttachmentDescription, 2> attchmentDescriptions = {};
      //// Color attachment
      //attchmentDescriptions[0].format = FB_COLOR_FORMAT;
      //attchmentDescriptions[0].samples = VK_SAMPLE_COUNT_1_BIT;
      //attchmentDescriptions[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
      //attchmentDescriptions[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
      //attchmentDescriptions[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
      //attchmentDescriptions[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
      //attchmentDescriptions[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
      //attchmentDescriptions[0].finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
      //// Depth attachment
      //attchmentDescriptions[1].format = fbDepthFormat;
      //attchmentDescriptions[1].samples = VK_SAMPLE_COUNT_1_BIT;
      //attchmentDescriptions[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
      //attchmentDescriptions[1].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
      //attchmentDescriptions[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
      //attchmentDescriptions[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
      //attchmentDescriptions[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
      //attchmentDescriptions[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

      //VkAttachmentReference colorReference = { 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };
      //VkAttachmentReference depthReference = { 1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL };

      //VkSubpassDescription subpassDescription = {};
      //subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
      //subpassDescription.colorAttachmentCount = 1;
      //subpassDescription.pColorAttachments = &colorReference;
      //subpassDescription.pDepthStencilAttachment = &depthReference;

      //// Use subpass dependencies for layout transitions
      //std::array<VkSubpassDependency, 2> dependencies;

      //dependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
      //dependencies[0].dstSubpass = 0;
      //dependencies[0].srcStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
      //dependencies[0].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
      //dependencies[0].srcAccessMask = VK_ACCESS_NONE_KHR;
      //dependencies[0].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
      //dependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

      //dependencies[1].srcSubpass = 0;
      //dependencies[1].dstSubpass = VK_SUBPASS_EXTERNAL;
      //dependencies[1].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
      //dependencies[1].dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
      //dependencies[1].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
      //dependencies[1].dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
      //dependencies[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

      //// Create the actual renderpass
      //VkRenderPassCreateInfo renderPassInfo = {};
      //renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
      //renderPassInfo.attachmentCount = static_cast<uint32_t>(attchmentDescriptions.size());
      //renderPassInfo.pAttachments = attchmentDescriptions.data();
      //renderPassInfo.subpassCount = 1;
      //renderPassInfo.pSubpasses = &subpassDescription;
      //renderPassInfo.dependencyCount = static_cast<uint32_t>(dependencies.size());
      //renderPassInfo.pDependencies = dependencies.data();

      //VK_CHECK_RESULT(vkCreateRenderPass(context, &renderPassInfo, nullptr, &offscreenPass.renderPass));

      //VkImageView attachments[2];
      //attachments[0] = offscreenPass.color.view;
      //attachments[1] = offscreenPass.depth.view;

      //VkFramebufferCreateInfo fbufCreateInfo = initializers::framebufferCreateInfo();
      //fbufCreateInfo.renderPass = offscreenPass.renderPass;
      //fbufCreateInfo.attachmentCount = 2;
      //fbufCreateInfo.pAttachments = attachments;
      //fbufCreateInfo.width = offscreenPass.width;
      //fbufCreateInfo.height = offscreenPass.height;
      //fbufCreateInfo.layers = 1;

      //VK_CHECK_RESULT(vkCreateFramebuffer(context, &fbufCreateInfo, nullptr, &offscreenPass.frameBuffer));

      //// Fill a descriptor for later use in a descriptor set
      //offscreenPass.descriptor.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
      //offscreenPass.descriptor.imageView = offscreenPass.color.view;
      //offscreenPass.descriptor.sampler = offscreenPass.sampler;

      m_extent = windowExtent;

   }



   void offscreen_render_pass::createImageViews()
   {

      render_pass::createImageViews();

      //m_imageviews.resize(m_images.size());
      //for (size_t i = 0; i < m_images.size(); i++) {
      //   VkImageViewCreateInfo viewInfo{};
      //   viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
      //   viewInfo.image = m_images[i];
      //   viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
      //   viewInfo.format = m_formatImage;
      //   viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
      //   viewInfo.subresourceRange.baseMipLevel = 0;
      //   viewInfo.subresourceRange.levelCount = 1;
      //   viewInfo.subresourceRange.baseArrayLayer = 0;
      //   viewInfo.subresourceRange.layerCount = 1;

      //   if (vkCreateImageView(m_pcontext->device(), &viewInfo, nullptr, &m_imageviews[i]) !=
      //      VK_SUCCESS) {
      //      throw ::exception(error_failed,"failed to create texture image view!");
      //   }
      //}

   }


   void offscreen_render_pass::createRenderPass()
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
      //colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
      colorAttachment.finalLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;

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

   void offscreen_render_pass::createFramebuffers()
   {
      render_pass::createFramebuffers();
      //m_framebuffers.resize(imageCount());
      //for (size_t i = 0; i < imageCount(); i++) {
      //   std::array<VkImageView, 2> attachments = { m_imageviews[i], depthImageViews[i] };

      //   VkExtent2D swapChainExtent = getExtent();
      //   VkFramebufferCreateInfo framebufferInfo = {};
      //   framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
      //   framebufferInfo.renderPass = m_vkrenderpass;
      //   framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
      //   framebufferInfo.pAttachments = attachments.data();
      //   framebufferInfo.width = swapChainExtent.width;
      //   framebufferInfo.height = swapChainExtent.height;
      //   framebufferInfo.layers = 1;

      //   if (vkCreateFramebuffer(
      //      m_pcontext->device(),
      //      &framebufferInfo,
      //      nullptr,
      //      &m_framebuffers[i]) != VK_SUCCESS) {
      //      throw ::exception(error_failed,"failed to create framebuffer!");
      //   }
      //}
   }

   void offscreen_render_pass::createDepthResources()
   {
      render_pass::createDepthResources();
      //VkFormat depthFormat = findDepthFormat();
      //m_formatDepth = depthFormat;
      //VkExtent2D extent = getExtent();

      //depthImages.resize(imageCount());
      //depthImageMemorys.resize(imageCount());
      //depthImageViews.resize(imageCount());

      //for (int i = 0; i < depthImages.size(); i++) {
      //   VkImageCreateInfo imageInfo{};
      //   imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
      //   imageInfo.imageType = VK_IMAGE_TYPE_2D;
      //   imageInfo.extent.width = extent.width;
      //   imageInfo.extent.height = extent.height;
      //   imageInfo.extent.depth = 1;
      //   imageInfo.mipLevels = 1;
      //   imageInfo.arrayLayers = 1;
      //   imageInfo.format = depthFormat;
      //   imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
      //   imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
      //   imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
      //   imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
      //   imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
      //   imageInfo.flags = 0;

      //   m_pcontext->createImageWithInfo(
      //      imageInfo,
      //      VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
      //      depthImages[i],
      //      depthImageMemorys[i]);

      //   VkImageViewCreateInfo viewInfo{};
      //   viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
      //   viewInfo.image = depthImages[i];
      //   viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
      //   viewInfo.format = depthFormat;
      //   viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
      //   viewInfo.subresourceRange.baseMipLevel = 0;
      //   viewInfo.subresourceRange.levelCount = 1;
      //   viewInfo.subresourceRange.baseArrayLayer = 0;
      //   viewInfo.subresourceRange.layerCount = 1;

      //   if (vkCreateImageView(m_pcontext->device(), &viewInfo, nullptr, &depthImageViews[i]) != VK_SUCCESS) {
      //      throw ::exception(error_failed,"failed to create texture image view!");
      //   }
      //}
   }


   void offscreen_render_pass::createSyncObjects()
   {

      render_pass::createSyncObjects();

      //imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
      //renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
      //inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
      //imagesInFlight.resize(imageCount(), VK_NULL_HANDLE);

      //VkSemaphoreCreateInfo semaphoreInfo = {};
      //semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

      //VkFenceCreateInfo fenceInfo = {};
      //fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
      //fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

      //for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
      //   if (vkCreateSemaphore(m_pcontext->device(), &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) !=
      //      VK_SUCCESS ||
      //      vkCreateSemaphore(m_pcontext->device(), &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) !=
      //      VK_SUCCESS ||
      //      vkCreateFence(m_pcontext->device(), &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
      //      throw ::exception(error_failed,"failed to create synchronization objects for a frame!");
      //   }
      //}
   }

   //VkSurfaceFormatKHR offscreen_render_pass::chooseSwapSurfaceFormat(
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

   //VkPresentModeKHR offscreen_render_pass::chooseSwapPresentMode(
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

   //VkExtent2D offscreen_render_pass::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
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

   VkFormat offscreen_render_pass::findDepthFormat()
   {
      return render_pass::findDepthFormat();

      //return m_pcontext->findSupportedFormat(
      //   { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
      //   VK_IMAGE_TILING_OPTIMAL,
      //   VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
   }


} // namespace gpu_vulkan


//// Setup the offscreen framebuffer for rendering the mirrored scene
//	// The color attachment of this framebuffer will then be used to sample from in the fragment shader of the final pass
//void prepareOffscreen()
//{
//	offscreenPass.width = FB_DIM;
//	offscreenPass.height = FB_DIM;
//
//	// Find a suitable depth format
//	VkFormat fbDepthFormat;
//	VkBool32 validDepthFormat = ::graphics3d_vulkan::tools::getSupportedDepthFormat(physicalDevice, &fbDepthFormat);
//	assert(validDepthFormat);
//
//	// Color attachment
//	VkImageCreateInfo image = initializers::imageCreateInfo();
//	image.imageType = VK_IMAGE_TYPE_2D;
//	image.format = m_formatImage;
//	image.extent.width = windowExtent.width;
//	image.extent.height = windowExtent.height;
//	image.extent.depth = 1;
//	image.mipLevels = 1;
//	image.arrayLayers = 1;
//	image.samples = VK_SAMPLE_COUNT_1_BIT;
//	image.tiling = VK_IMAGE_TILING_OPTIMAL;
//	// We will sample directly from the color attachment
//	image.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
//
//	////VkMemoryAllocateInfo memAlloc = initializers::memory_allocate_info();
//	////VkMemoryRequirements memReqs;
//
//	////VK_CHECK_RESULT(vkCreateImage(context, &image, nullptr, &offscreenPass.color.image));
//	////vkGetImageMemoryRequirements(context, offscreenPass.color.image, &memReqs);
//	////memAlloc.allocationSize = memReqs.size;
//	////memAlloc.memoryTypeIndex = vulkanDevice->getMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
//	////VK_CHECK_RESULT(vkAllocateMemory(context, &memAlloc, nullptr, &offscreenPass.color.mem));
//	////VK_CHECK_RESULT(vkBindImageMemory(context, offscreenPass.color.image, offscreenPass.color.mem, 0));
//
//	////VkImageViewCreateInfo colorImageView = initializers::imageViewCreateInfo();
//	////colorImageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
//	////colorImageView.format = FB_COLOR_FORMAT;
//	////colorImageView.subresourceRange = {};
//	////colorImageView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
//	////colorImageView.subresourceRange.baseMipLevel = 0;
//	////colorImageView.subresourceRange.levelCount = 1;
//	////colorImageView.subresourceRange.baseArrayLayer = 0;
//	////colorImageView.subresourceRange.layerCount = 1;
//	////colorImageView.image = offscreenPass.color.image;
//	////VK_CHECK_RESULT(vkCreateImageView(context, &colorImageView, nullptr, &offscreenPass.color.view));
//
//	//// Create sampler to sample from the attachment in the fragment shader
//	//VkSamplerCreateInfo samplerInfo = initializers::samplerCreateInfo();
//	//samplerInfo.magFilter = VK_FILTER_LINEAR;
//	//samplerInfo.minFilter = VK_FILTER_LINEAR;
//	//samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
//	//samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
//	//samplerInfo.addressModeV = samplerInfo.addressModeU;
//	//samplerInfo.addressModeW = samplerInfo.addressModeU;
//	//samplerInfo.mipLodBias = 0.0f;
//	//samplerInfo.maxAnisotropy = 1.0f;
//	//samplerInfo.minLod = 0.0f;
//	//samplerInfo.maxLod = 1.0f;
//	//samplerInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
//	//VK_CHECK_RESULT(vkCreateSampler(context, &samplerInfo, nullptr, &offscreenPass.sampler));
//
//	//// Depth stencil attachment
//	//image.format = fbDepthFormat;
//	//image.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
//
//	//VK_CHECK_RESULT(vkCreateImage(context, &image, nullptr, &offscreenPass.depth.image));
//	//vkGetImageMemoryRequirements(context, offscreenPass.depth.image, &memReqs);
//	//memAlloc.allocationSize = memReqs.size;
//	//memAlloc.memoryTypeIndex = vulkanDevice->getMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
//	//VK_CHECK_RESULT(vkAllocateMemory(context, &memAlloc, nullptr, &offscreenPass.depth.mem));
//	//VK_CHECK_RESULT(vkBindImageMemory(context, offscreenPass.depth.image, offscreenPass.depth.mem, 0));
//
//	//VkImageViewCreateInfo depthStencilView = initializers::imageViewCreateInfo();
//	//depthStencilView.viewType = VK_IMAGE_VIEW_TYPE_2D;
//	//depthStencilView.format = fbDepthFormat;
//	//depthStencilView.flags = 0;
//	//depthStencilView.subresourceRange = {};
//	//depthStencilView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
//	//if (fbDepthFormat >= VK_FORMAT_D16_UNORM_S8_UINT) {
//	//	depthStencilView.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
//	//}
//	//depthStencilView.subresourceRange.baseMipLevel = 0;
//	//depthStencilView.subresourceRange.levelCount = 1;
//	//depthStencilView.subresourceRange.baseArrayLayer = 0;
//	//depthStencilView.subresourceRange.layerCount = 1;
//	//depthStencilView.image = offscreenPass.depth.image;
//	//VK_CHECK_RESULT(vkCreateImageView(context, &depthStencilView, nullptr, &offscreenPass.depth.view));
//
//	//// Create a separate render pass for the offscreen rendering as it may differ from the one used for scene rendering
//
//	//std::array<VkAttachmentDescription, 2> attchmentDescriptions = {};
//	//// Color attachment
//	//attchmentDescriptions[0].format = FB_COLOR_FORMAT;
//	//attchmentDescriptions[0].samples = VK_SAMPLE_COUNT_1_BIT;
//	//attchmentDescriptions[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
//	//attchmentDescriptions[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
//	//attchmentDescriptions[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
//	//attchmentDescriptions[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
//	//attchmentDescriptions[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
//	//attchmentDescriptions[0].finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
//	//// Depth attachment
//	//attchmentDescriptions[1].format = fbDepthFormat;
//	//attchmentDescriptions[1].samples = VK_SAMPLE_COUNT_1_BIT;
//	//attchmentDescriptions[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
//	//attchmentDescriptions[1].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
//	//attchmentDescriptions[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
//	//attchmentDescriptions[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
//	//attchmentDescriptions[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
//	//attchmentDescriptions[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
//
//	//VkAttachmentReference colorReference = { 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };
//	//VkAttachmentReference depthReference = { 1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL };
//
//	//VkSubpassDescription subpassDescription = {};
//	//subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
//	//subpassDescription.colorAttachmentCount = 1;
//	//subpassDescription.pColorAttachments = &colorReference;
//	//subpassDescription.pDepthStencilAttachment = &depthReference;
//
//	//// Use subpass dependencies for layout transitions
//	//std::array<VkSubpassDependency, 2> dependencies;
//
//	//dependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
//	//dependencies[0].dstSubpass = 0;
//	//dependencies[0].srcStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
//	//dependencies[0].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
//	//dependencies[0].srcAccessMask = VK_ACCESS_NONE_KHR;
//	//dependencies[0].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
//	//dependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;
//
//	//dependencies[1].srcSubpass = 0;
//	//dependencies[1].dstSubpass = VK_SUBPASS_EXTERNAL;
//	//dependencies[1].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
//	//dependencies[1].dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
//	//dependencies[1].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
//	//dependencies[1].dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
//	//dependencies[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;
//
//	//// Create the actual renderpass
//	//VkRenderPassCreateInfo renderPassInfo = {};
//	//renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
//	//renderPassInfo.attachmentCount = static_cast<uint32_t>(attchmentDescriptions.size());
//	//renderPassInfo.pAttachments = attchmentDescriptions.data();
//	//renderPassInfo.subpassCount = 1;
//	//renderPassInfo.pSubpasses = &subpassDescription;
//	//renderPassInfo.dependencyCount = static_cast<uint32_t>(dependencies.size());
//	//renderPassInfo.pDependencies = dependencies.data();
//
//	//VK_CHECK_RESULT(vkCreateRenderPass(context, &renderPassInfo, nullptr, &offscreenPass.renderPass));
//
//	//VkImageView attachments[2];
//	//attachments[0] = offscreenPass.color.view;
//	//attachments[1] = offscreenPass.depth.view;
//
//	//VkFramebufferCreateInfo fbufCreateInfo = initializers::framebufferCreateInfo();
//	//fbufCreateInfo.renderPass = offscreenPass.renderPass;
//	//fbufCreateInfo.attachmentCount = 2;
//	//fbufCreateInfo.pAttachments = attachments;
//	//fbufCreateInfo.width = offscreenPass.width;
//	//fbufCreateInfo.height = offscreenPass.height;
//	//fbufCreateInfo.layers = 1;
//
//	//VK_CHECK_RESULT(vkCreateFramebuffer(context, &fbufCreateInfo, nullptr, &offscreenPass.frameBuffer));
//
//	//// Fill a descriptor for later use in a descriptor set
//	//offscreenPass.descriptor.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
//	//offscreenPass.descriptor.imageView = offscreenPass.color.view;
//	//offscreenPass.descriptor.sampler = offscreenPass.sampler;
//}

