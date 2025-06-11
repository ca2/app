#include "framework.h"
#include "context.h"
#include "frame_buffer.h"
#include "renderer.h"
#include "swap_chain.h"
#include "aura/graphics/gpu/device.h"
#include "aura/user/user/interaction.h"
#include "aura/windowing/window.h"


namespace gpu_opengl
{


   swap_chain::swap_chain()
   {

      m_VAOFullScreenQuad = 0;
      m_VBOFullScreenQuad = 0;

   }

   //swap_chain::swap_chain(renderer* pgpurenderer, VkExtent2D extent)
   //	: render_pass(pgpurenderer, extent)
   //{
   //	//m_bNeedRebuild = false;
   //   //init();
   //}

   //swap_chain::swap_chain(renderer* pgpurenderer, VkExtent2D extent, ::pointer<render_pass> previous)
   //	: render_pass(pgpurenderer, extent, previous)
   //{
   //	//m_bNeedRebuild = false;
   //   //init();
   //   // Cleans up old swap chain since it's no longer needed after resizing
   //   //oldSwapChain = nullptr;
   //}


   //void swap_chain::initialize_render_pass(renderer* pgpurenderer, VkExtent2D extent, ::pointer<render_pass> previous)
   //{

   //	render_pass::initialize_render_pass(pgpurenderer, extent, previous);
   //	//m_bNeedRebuild = false;
   //	//init();
   //	// Cleans up old swap chain since it's no longer needed after resizing
   //	//oldSwapChain = nullptr;
   //}


   //void swap_chain::init()
   //{

   //	m_pgpurenderer->restart_frame_counter();

   //	createRenderPassImpl();
   //	createImageViews();
   //	createRenderPass();
   //	createDepthResources();
   //	createFramebuffers();
   //	createSyncObjects();

   //}


   swap_chain::~swap_chain()
   {
      //for (auto imageView : m_imageviews) {
      //	vkDestroyImageView(m_pgpucontext->logicalDevice(), imageView, nullptr);
      //}
      //m_imageviews.clear();

      //if (m_vkswapchain != nullptr) {
      //	vkDestroySwapchainKHR(m_pgpucontext->logicalDevice(), m_vkswapchain, nullptr);
      //	m_vkswapchain = nullptr;
      //}

      ////for (int i = 0; i < depthImages.size(); i++) {
      ////   vkDestroyImageView(m_pgpucontext->logicalDevice(), depthImageViews[i], nullptr);
      ////   vkDestroyImage(m_pgpucontext->logicalDevice(), depthImages[i], nullptr);
      ////   vkFreeMemory(m_pgpucontext->logicalDevice(), depthImageMemorys[i], nullptr);
      ////}

      ////for (auto framebuffer : m_vkswapchainFramebuffers) {
      ////   vkDestroyFramebuffer(m_pgpucontext->logicalDevice(), framebuffer, nullptr);
      ////}

      ////vkDestroyRenderPass(m_pgpucontext->logicalDevice(), m_vkrenderpass, nullptr);

      ////// cleanup synchronization objects
      ////for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
      ////   vkDestroySemaphore(m_pgpucontext->logicalDevice(), renderFinishedSemaphores[i], nullptr);
      ////   vkDestroySemaphore(m_pgpucontext->logicalDevice(), imageAvailableSemaphores[i], nullptr);
      ////   vkDestroyFence(m_pgpucontext->logicalDevice(), inFlightFences[i], nullptr);
      ////}
      //for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
      //{
      //	vkDestroyFence(m_pgpucontext->logicalDevice(), inFlightFences[i], nullptr);
      //}


   }


   //VkResult swap_chain::acquireNextImage()
   //{

   //	uint32_t* imageIndex = &currentImageIndex;

   //	auto currentFrame = m_pgpurenderer->get_frame_index();

   //	// Wait for the fence of the current frame first (prevents CPU running too fast)
   //	vkWaitForFences(m_pgpucontext->logicalDevice(), 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

   //	VkResult result = vkAcquireNextImageKHR(
   //		m_pgpucontext->logicalDevice(),
   //		m_vkswapchain,
   //		UINT64_MAX,
   //		imageAvailableSemaphores[currentFrame],  // signal semaphore
   //		VK_NULL_HANDLE,
   //		imageIndex);

   //	if (result == VK_ERROR_OUT_OF_DATE_KHR) {
   //		// Swapchain needs to be recreated - handle outside
   //		return result;
   //	}
   //	else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
   //		throw ::exception(error_failed, "failed to acquire swap chain image!");
   //	}

   //	// If the image we acquired is already being used (fence not signaled), wait for it
   //	if (imagesInFlight[*imageIndex] != VK_NULL_HANDLE) {
   //		vkWaitForFences(m_pgpucontext->logicalDevice(), 1, &imagesInFlight[*imageIndex], VK_TRUE, UINT64_MAX);
   //	}

   //	// Mark this image as now being in use by current frame
   //	imagesInFlight[*imageIndex] = inFlightFences[currentFrame];

   //	return result;
   //	//vkWaitForFences(
   //	//   m_pgpucontext->logicalDevice(),
   //	//   1,
   //	//   &inFlightFences[m_pgpurenderer->get_frame_index()],
   //	//   VK_TRUE,
   //	//   std::numeric_limits<uint64_t>::max());

   //	//VkResult result = vkAcquireNextImageKHR(
   //	//   m_pgpucontext->logicalDevice(),
   //	//   m_vkswapchain,
   //	//   std::numeric_limits<uint64_t>::max(),
   //	//   imageAvailableSemaphores[m_pgpurenderer->get_frame_index()],  // must be a not signaled semaphore
   //	//   VK_NULL_HANDLE,
   //	//   imageIndex);
   //	//if (result == VK_ERROR_OUT_OF_DATE_KHR) {
   //	//   // Swapchain needs to be recreated - handle outside
   //	//   return result;
   //	//}
   //	//else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
   //	//   throw ::exception(error_failed, "failed to acquire swap chain image!");
   //	//}

   //	//// If the image we acquired is already being used (fence not signaled), wait for it
   //	//if (imagesInFlight[*imageIndex] != VK_NULL_HANDLE) {
   //	//   vkWaitForFences(m_pgpucontext->logicalDevice(), 1, &imagesInFlight[*imageIndex], VK_TRUE, UINT64_MAX);
   //	//}

   //	//// Mark this image as now being in use by current frame
   //	//imagesInFlight[*imageIndex] = inFlightFences[m_pgpurenderer->get_frame_index()];
   //	//return result;
   //}


   //VkResult swap_chain::submitCommandBuffers(const VkCommandBuffer* buffers)
   //{

   //	uint32_t* imageIndex = &currentImageIndex;

   //	auto currentFrame = m_pgpurenderer->get_frame_index();

   //	// Use currentFrame to access per-frame sync objects
   //	vkWaitForFences(m_pgpucontext->logicalDevice(), 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);
   //	vkResetFences(m_pgpucontext->logicalDevice(), 1, &inFlightFences[currentFrame]);

   //	VkSubmitInfo submitInfo{};
   //	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

   //	VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
   //	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
   //	submitInfo.waitSemaphoreCount = 1;
   //	submitInfo.pWaitSemaphores = waitSemaphores;
   //	submitInfo.pWaitDstStageMask = waitStages;

   //	submitInfo.commandBufferCount = 1;
   //	submitInfo.pCommandBuffers = buffers;

   //	VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };
   //	submitInfo.signalSemaphoreCount = 1;
   //	submitInfo.pSignalSemaphores = signalSemaphores;

   //	VkResult vkresult = vkQueueSubmit(m_pgpucontext->graphicsQueue(), 1, &submitInfo, inFlightFences[currentFrame]);
   //	if (vkresult != VK_SUCCESS) {
   //		throw ::exception(error_failed, "failed to submit draw command buffer!");
   //	}

   //	VkPresentInfoKHR presentInfo{};
   //	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
   //	presentInfo.waitSemaphoreCount = 1;
   //	presentInfo.pWaitSemaphores = signalSemaphores;
   //	presentInfo.swapchainCount = 1;
   //	presentInfo.pSwapchains = &m_vkswapchain;
   //	presentInfo.pImageIndices = imageIndex;

   //	VkResult result = vkQueuePresentKHR(m_pgpucontext->presentQueue(), &presentInfo);

   //	//currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;

   //	return result;

   //	////if (imagesInFlight[*imageIndex] != VK_NULL_HANDLE) {
   //	//  // vkWaitForFences(m_pgpucontext->logicalDevice(), 1, &imagesInFlight[*imageIndex], VK_TRUE, UINT64_MAX);
   //	////}
   //	////imagesInFlight[*imageIndex] = inFlightFences[currentFrame];

   //	//vkWaitForFences(m_pgpucontext->logicalDevice(), 1, &inFlightFences[m_pgpurenderer->get_frame_index()], VK_TRUE, UINT64_MAX);
   //	//vkResetFences(m_pgpucontext->logicalDevice(), 1, &inFlightFences[m_pgpurenderer->get_frame_index()]);

   //	//VkSubmitInfo submitInfo = {};
   //	//submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

   //	//VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[m_pgpurenderer->get_frame_index()] };
   //	//VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
   //	//submitInfo.waitSemaphoreCount = 1;
   //	//submitInfo.pWaitSemaphores = waitSemaphores;
   //	//submitInfo.pWaitDstStageMask = waitStages;

   //	//submitInfo.commandBufferCount = 1;
   //	//submitInfo.pCommandBuffers = buffers;

   //	//VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[m_pgpurenderer->get_frame_index()] };
   //	//submitInfo.signalSemaphoreCount = 1;
   //	//submitInfo.pSignalSemaphores = signalSemaphores;

   //	////vkResetFences(m_pgpucontext->logicalDevice(), 1, &inFlightFences[currentFrame]);
   //	//if (vkQueueSubmit(m_pgpucontext->graphicsQueue(), 1, &submitInfo, inFlightFences[m_pgpurenderer->get_frame_index()]) !=
   //	//   VK_SUCCESS) {
   //	//   throw ::exception(error_failed,"failed to submit draw command buffer!");
   //	//}

   //	//VkPresentInfoKHR presentInfo = {};
   //	//presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

   //	//presentInfo.waitSemaphoreCount = 1;
   //	//presentInfo.pWaitSemaphores = signalSemaphores;

   //	//VkSwapchainKHR m_vkswapchains[] = { m_vkswapchain };
   //	//presentInfo.swapchainCount = 1;
   //	//presentInfo.pSwapchains = m_vkswapchains;

   //	//presentInfo.pImageIndices = imageIndex;

   //	//auto result = vkQueuePresentKHR(m_pgpucontext->presentQueue(), &presentInfo);

   //	//return result;

   //}


   //int swap_chain::get_image_index() const
   //{

   //	return currentImageIndex;

   //}


   //void swap_chain::createRenderPassImpl()
   //{

   //	auto pgpucontext = m_pgpucontext;

   //	auto pgpudevice = pgpucontext->m_pgpudevice;

   //	auto pphysicaldevice = pgpudevice->m_pphysicaldevice;

   //	auto swapchainSupport = pphysicaldevice->querySwapChainSupport();

   //	VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapchainSupport.formats);
   //	VkPresentModeKHR presentMode = chooseSwapPresentMode(swapchainSupport.presentModes);
   //	VkExtent2D extent = chooseSwapExtent(swapchainSupport.capabilities);
   //	uint32_t imageCount = swapchainSupport.capabilities.minImageCount + 1;
   //	if (swapchainSupport.capabilities.maxImageCount > 0 &&
   //		imageCount > swapchainSupport.capabilities.maxImageCount) {
   //		imageCount = swapchainSupport.capabilities.maxImageCount;
   //	}

   //	VkSwapchainCreateInfoKHR createInfo = {};
   //	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
   //	createInfo.surface = m_pgpucontext->m_pgpudevice->m_pphysicaldevice->surface();

   //	//createInfo.minImageCount = imageCount;
   //	createInfo.minImageCount = 3;
   //	createInfo.imageFormat = surfaceFormat.format;
   //	createInfo.imageColorSpace = surfaceFormat.colorSpace;
   //	createInfo.imageExtent = extent;
   //	createInfo.imageArrayLayers = 1;
   //	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

   //	vulkan::QueueFamilyIndices indices = m_pgpucontext->m_pgpudevice->m_pphysicaldevice->findQueueFamilies();
   //	uint32_t queueFamilyIndices[] = 
   //	{ 
   //		(uint32_t)indices.graphicsFamily,
   //		(uint32_t)indices.presentFamily 
   //	};

   //	if (indices.graphicsFamily != indices.presentFamily) {
   //		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
   //		createInfo.queueFamilyIndexCount = 2;
   //		createInfo.pQueueFamilyIndices = queueFamilyIndices;
   //	}
   //	else {
   //		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
   //		createInfo.queueFamilyIndexCount = 0;      // Optional
   //		createInfo.pQueueFamilyIndices = nullptr;  // Optional
   //	}

   //	createInfo.preTransform = swapchainSupport.capabilities.currentTransform;
   //	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
   //	//createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR;

   //	createInfo.presentMode = presentMode;
   //	createInfo.clipped = VK_TRUE;

   //	::pointer < swap_chain> pswapchainOld = m_pvkcrenderpassOld;

   //	createInfo.oldSwapchain = pswapchainOld == nullptr ? VK_NULL_HANDLE : pswapchainOld->m_vkswapchain;

   //	auto logicalDevice = m_pgpucontext->logicalDevice();

   //	if (vkCreateSwapchainKHR(logicalDevice, &createInfo, nullptr, &m_vkswapchain) != VK_SUCCESS) {
   //		//throw ::exception(error_failed,"failed to create swap chain!");
   //		m_bNeedRebuild = true;
   //		return;
   //	}

   //	// we only specified a minimum number of images in the swap chain, so the implementation is
   //	// allowed to create a swap chain with more. That's why we'll first query the final number of
   //	// images with vkGetSwapchainImagesKHR, then resize the container and finally call it again to
   //	// retrieve the handles.
   //	vkGetSwapchainImagesKHR(m_pgpucontext->logicalDevice(), m_vkswapchain, &imageCount, nullptr);
   //	m_images.resize(imageCount);
   //	vkGetSwapchainImagesKHR(m_pgpucontext->logicalDevice(), m_vkswapchain, &imageCount, m_images.data());

   //	m_formatImage = surfaceFormat.format;
   //	m_extent = extent;
   //	m_pgpucontext->m_rectangle.set_size({ (int)extent.width, (int)extent.height });

   //}


   //void swap_chain::createImageViews() 
   //{

   //	m_imageviews.resize(m_images.size());
   //	for (::collection::index i = 0; i < m_images.size(); i++) {
   //		VkImageViewCreateInfo viewInfo{};
   //		viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
   //		viewInfo.image = m_images[i];
   //		viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
   //		viewInfo.format = m_formatImage;
   //		viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
   //		viewInfo.subresourceRange.baseMipLevel = 0;
   //		viewInfo.subresourceRange.levelCount = 1;
   //		viewInfo.subresourceRange.baseArrayLayer = 0;
   //		viewInfo.subresourceRange.layerCount = 1;

   //		if (vkCreateImageView(m_pgpucontext->logicalDevice(), &viewInfo, nullptr, &m_imageviews[i]) !=
   //			VK_SUCCESS) {
   //			throw ::exception(error_failed, "failed to create texture image view!");
   //		}
   //	}
   //}


   //void swap_chain::createRenderPass() 
   //{

   //	VkAttachmentDescription depthAttachment{};
   //	depthAttachment.format = findDepthFormat();
   //	depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
   //	depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
   //	depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
   //	depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
   //	depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
   //	depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
   //	depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

   //	VkAttachmentReference depthAttachmentRef{};
   //	depthAttachmentRef.attachment = 1;
   //	depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

   //	VkAttachmentDescription colorAttachment = {};
   //	colorAttachment.format = getImageFormat();
   //	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
   //	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
   //	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
   //	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
   //	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
   //	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
   //	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

   //	VkAttachmentReference colorAttachmentRef = {};
   //	colorAttachmentRef.attachment = 0;
   //	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

   //	VkSubpassDescription subpass = {};
   //	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
   //	subpass.colorAttachmentCount = 1;
   //	subpass.pColorAttachments = &colorAttachmentRef;
   //	subpass.pDepthStencilAttachment = &depthAttachmentRef;

   //	VkSubpassDependency dependency[2]{};
   //	dependency[0].dstSubpass = 0;
   //	dependency[0].dstAccessMask =
   //		VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
   //	dependency[0].dstStageMask =
   //		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
   //	dependency[0].srcSubpass = VK_SUBPASS_EXTERNAL;
   //	dependency[0].srcAccessMask = 0;
   //	dependency[0].srcStageMask =
   //		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;



   //	dependency[1].srcSubpass = 0;
   //	dependency[1].dstSubpass = 0;
   //	//dependency[1].srcStageMask = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;
   //	//dependency[1].dstStageMask = VK_PIPELINE_STAGE_2_FRAGMENT_SHADER_BIT;
   //	//dependency[1].srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
   //	//dependency[1].dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
   //	dependency[1].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
   //	dependency[1].dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
   //	dependency[1].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
   //	dependency[1].dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
   //	dependency[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;// if needed


   //	VkAttachmentDescription attachments[2] = {colorAttachment, depthAttachment};
   //	VkRenderPassCreateInfo renderPassInfo = {};
   //	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
   //	renderPassInfo.attachmentCount = 2;
   //	renderPassInfo.pAttachments = attachments;
   //	renderPassInfo.subpassCount = 1;
   //	renderPassInfo.pSubpasses = &subpass;
   //	renderPassInfo.dependencyCount = 1;
   //	renderPassInfo.pDependencies = dependency;

   //	if (vkCreateRenderPass(m_pgpucontext->logicalDevice(), &renderPassInfo, nullptr, &m_vkrenderpass) != VK_SUCCESS) {
   //		throw ::exception(error_failed, "failed to create render pass!");
   //	}

   //}


   //void swap_chain::createFramebuffers()
   //{
   //	render_pass::createFramebuffers();
   //	//swapChainFramebuffers.resize(imageCount());
   //	//for (size_t i = 0; i < imageCount(); i++) {
   //	//   std::array<VkImageView, 2> attachments = { m_imageviews[i], depthImageViews[i] };

   //	//   VkExtent2D m_vkswapchainExtent = getExtent();
   //	//   VkFramebufferCreateInfo framebufferInfo = {};
   //	//   framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
   //	//   framebufferInfo.renderPass = m_vkrenderpass;
   //	//   framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
   //	//   framebufferInfo.pAttachments = attachments.data();
   //	//   framebufferInfo.width = m_vkswapchainExtent.width;
   //	//   framebufferInfo.height = m_vkswapchainExtent.height;
   //	//   framebufferInfo.layers = 1;

   //	//   if (vkCreateFramebuffer(
   //	//      m_pgpucontext->logicalDevice(),
   //	//      &framebufferInfo,
   //	//      nullptr,
   //	//      &swapChainFramebuffers[i]) != VK_SUCCESS) {
   //	//      throw ::exception(error_failed,"failed to create framebuffer!");
   //	//   }
   //	//}
   //}


   //void swap_chain::createDepthResources()
   //{
   //	render_pass::createDepthResources();

   //	//VkFormat depthFormat = findDepthFormat();
   //	//m_formatDepth = depthFormat;
   //	//VkExtent2D m_vkswapchainExtent = getExtent();

   //	//depthImages.resize(imageCount());
   //	//depthImageMemorys.resize(imageCount());
   //	//depthImageViews.resize(imageCount());

   //	//for (int i = 0; i < depthImages.size(); i++) {
   //	//   VkImageCreateInfo imageInfo{};
   //	//   imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
   //	//   imageInfo.imageType = VK_IMAGE_TYPE_2D;
   //	//   imageInfo.extent.width = m_vkswapchainExtent.width;
   //	//   imageInfo.extent.height = m_vkswapchainExtent.height;
   //	//   imageInfo.extent.depth = 1;
   //	//   imageInfo.mipLevels = 1;
   //	//   imageInfo.arrayLayers = 1;
   //	//   imageInfo.format = depthFormat;
   //	//   imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
   //	//   imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
   //	//   imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
   //	//   imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
   //	//   imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
   //	//   imageInfo.flags = 0;

   //	//   m_pgpucontext->createImageWithInfo(
   //	//      imageInfo,
   //	//      VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
   //	//      depthImages[i],
   //	//      depthImageMemorys[i]);

   //	//   VkImageViewCreateInfo viewInfo{};
   //	//   viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
   //	//   viewInfo.image = depthImages[i];
   //	//   viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
   //	//   viewInfo.format = depthFormat;
   //	//   viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
   //	//   viewInfo.subresourceRange.baseMipLevel = 0;
   //	//   viewInfo.subresourceRange.levelCount = 1;
   //	//   viewInfo.subresourceRange.baseArrayLayer = 0;
   //	//   viewInfo.subresourceRange.layerCount = 1;

   //	//   if (vkCreateImageView(m_pgpucontext->logicalDevice(), &viewInfo, nullptr, &depthImageViews[i]) != VK_SUCCESS) {
   //	//      throw ::exception(error_failed,"failed to create texture image view!");
   //	//   }
   //	//}
   //}


   //void swap_chain::createSyncObjects() 
   //{
   //	//imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
   //	//renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);

   //	render_pass::createSyncObjects();


   //	//inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
   //	//imagesInFlight.resize(imageCount(), VK_NULL_HANDLE);

   //	////VkSemaphoreCreateInfo semaphoreInfo = {};
   //	////semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

   //	//VkFenceCreateInfo fenceInfo = {};
   //	//fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
   //	//fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

   //	//for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
   //	//   if (vkCreateFence(m_pgpucontext->logicalDevice(), &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS)
   //	//   {
   //	//      throw ::exception(error_failed,"failed to create synchronization objects for a frame!");
   //	//   }
   //	//}
   //}


   //VkSurfaceFormatKHR swap_chain::chooseSwapSurfaceFormat(const ::array<VkSurfaceFormatKHR>& availableFormats) 
   //{

   //	for (const auto& availableFormat : availableFormats) {
   //		// SRGB can be changed to "UNORM" instead
   //		//if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
   //		if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM &&
   //			availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
   //			return availableFormat;
   //		}
   //	}

   //	return availableFormats[0];
   //}

   //VkPresentModeKHR swap_chain::chooseSwapPresentMode(const ::array<VkPresentModeKHR>& availablePresentModes)
   //{
   //	for (const auto& availablePresentMode : availablePresentModes)
   //	{

   //		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
   //		{
   //			debug() << "Present mode: Mailbox";
   //			return availablePresentMode;
   //		}
   //	}

   //	for (const auto& availablePresentMode : availablePresentModes) {
   //		if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
   //			debug() << "Present mode: Immediate";
   //			return availablePresentMode;
   //		}
   //	}

   //	debug() << "Present mode: V-Sync";
   //	return VK_PRESENT_MODE_FIFO_KHR;
   //}

   //VkExtent2D swap_chain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
   //	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
   //		return capabilities.currentExtent;
   //	}
   //	else {
   //		VkExtent2D actualExtent = windowExtent;
   //		actualExtent.width = std::max(
   //			capabilities.minImageExtent.width,
   //			std::min(capabilities.maxImageExtent.width, actualExtent.width));
   //		actualExtent.height = std::max(
   //			capabilities.minImageExtent.height,
   //			std::min(capabilities.maxImageExtent.height, actualExtent.height));

   //		return actualExtent;
   //	}
   //}

   //VkFormat swap_chain::findDepthFormat()
   //{

   //	return m_pgpucontext->m_pgpudevice->m_pphysicaldevice->findSupportedFormat(
   //		{ VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
   //		VK_IMAGE_TILING_OPTIMAL,
   //		VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
   //}
GLuint createFullscreenQuad(GLuint& quadVBO);

   void swap_chain::endDraw(::draw2d_gpu::graphics* pgraphics, ::user::interaction* puserinteraction, ::gpu::renderer* pgpurendererSrc)
   {

      ::gpu::swap_chain::endDraw(pgraphics, puserinteraction, pgpurendererSrc);

      auto pwindow = puserinteraction->window();

      if (!m_pgpucontextSwapChain)
      {

         m_pgpucontextSwapChain = pgpurendererSrc->m_pgpucontext->m_pgpudevice->start_swap_chain_context(this, pwindow);

      }

      auto rectanglePlacement = pwindow->get_window_rectangle();

      m_pgpucontextSwapChain->set_placement(rectanglePlacement);

      auto prendererOutput = m_pgpucontextSwapChain->get_renderer(::gpu::e_scene_2d);

      prendererOutput->defer_update_renderer();


      ::cast<renderer>prendererSrc = pgpurendererSrc;


      m_pgpucontextSwapChain->send_on_context([this, prendererSrc]()
         {

            m_pgpucontextSwapChain->m_pgpurenderer->do_on_frame([this, prendererSrc]()
               {

                  m_pgpucontextSwapChain->clear(::argb(127, 140 / 2, 220 / 2, 240 / 2));
                  //m_pgpucontext->clear(::color::transparent);


                  if (1)
                  {


                     //if (m_pimpact->global_ubo_block().size() > 0)
                     //{

                       // update_global_ubo(m_pgpucontext);

                     //}

                     //m_pscene->on_render(m_pgpucontext);

                     //_blend_image(image, m_rectangle);

            //         glDisable(GL_BLEND);
            //         //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


                     if (!m_pshaderCopyTextureOnEndDraw)
                     {

                        auto pvertexshader = R"vert(#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main() {
   gl_Position = vec4(aPos.xy, 0.0, 1.0);
   TexCoord = aTexCoord;
}
)vert";


                        auto pfragmentshader = R"frag(#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D uTexture;

void main() {
   FragColor = texture(uTexture, TexCoord);
}
)frag";

                        m_pshaderCopyTextureOnEndDraw = __create_new < ::gpu_opengl::shader >();

                        m_pshaderCopyTextureOnEndDraw->initialize_shader_with_block(
                           m_pgpucontextSwapChain->m_pgpurenderer,
                           pvertexshader, pfragmentshader);


                     }

                     m_pshaderCopyTextureOnEndDraw->bind();

                     if (1)
                     {

                        glActiveTexture(GL_TEXTURE0);

                        int iGlError1 = glGetError();

                        ::cast < context > pcontext = prendererSrc->m_pgpucontext;

                        GLuint tex = pcontext->m_pframebuffer->m_tex;

                        glBindTexture(GL_TEXTURE_2D, tex);

                        int iGlError2 = glGetError();

                        ::cast < ::gpu_opengl::shader > pshaderOnEndDraw = m_pshaderCopyTextureOnEndDraw;

                        pshaderOnEndDraw->_set_int("uTexture", 0);

                        if (!m_VAOFullScreenQuad)
                        {

                           m_VAOFullScreenQuad = createFullscreenQuad(m_VBOFullScreenQuad);

                        }

                        glBindVertexArray(m_VAOFullScreenQuad);

                        int iGlError00 = glGetError();

                        glDrawArrays(GL_TRIANGLES, 0, 6); // assuming 2 triangles (quad)

                        int iGlError01 = glGetError();

                        glBindVertexArray(0);

                        int iGlErrorA = glGetError();

                        glBindTexture(GL_TEXTURE_2D, 0);

                        int iGlErrorB = glGetError();

                        debug() << "gl error";

                     }

                     m_pshaderCopyTextureOnEndDraw->unbind();

                  }

               });


         });

      //return prendererOutput;


//		if (!m_pgpucontextSwapChain)
//		{
//
//			m_pgpucontextSwapChain = pgpurendererSrc->m_pgpucontext->m_pgpudevice->start_swap_chain_context(this, puserinteraction->window());
//
//		}
//
//		m_pgpucontextSwapChain->send_on_context([this, puserinteraction]()
//			{
//
//				auto rectanglePlacement = puserinteraction->window()->get_window_rectangle();
//
//				m_pgpucontextSwapChain->set_placement(rectanglePlacement);
//
//				auto prendererOutput = m_pgpucontextSwapChain->get_renderer(::gpu::e_scene_2d);
//
//				prendererOutput->defer_update_renderer();
//
//				ASSERT(m_pgpucontextSwapChain == m_pgpucontext);
//
//				::cast < renderer > prendererThis = m_pgpucontextSwapChain->m_pgpurenderer;
//
//				ASSERT(prendererThis->m_pvkcrenderpass == this);
//
//			});
//
//		::cast < renderer > prendererSrc = pgpurendererSrc;
//
//		VkImage vkimage = prendererSrc->m_pvkcrenderpass->m_images[prendererSrc->get_frame_index()];
//
//		::int_rectangle rectangle = prendererSrc->m_pgpucontext->rectangle();
//
//		m_pgpucontext->send_on_context([this, vkimage, rectangle]()
//			{
//
//				m_pgpucontext->m_pgpurenderer->do_on_frame([this, vkimage, rectangle]()
//					{
//
//						::cast < renderer > prenderer = m_pgpucontext->m_pgpurenderer;
//
//						prenderer->_copy_image(vkimage, rectangle, false);
//
//					});
//
//			});
////		m_pgpucontextOutput
//
//		//vkQueueWaitIdle(m_pgpucontext->graphicsQueue());
//
//		//vkQueueWaitIdle(m_pgpucontext->presentQueue());

   }


} // namespace gpu_opengl


