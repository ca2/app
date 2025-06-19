// From vk_swapchain by camilo on 2025-05-09 <3ThomasBorregaardSorensen!!
#pragma once


#include "render_target.h"



namespace gpu_opengl
{


	class CLASS_DECL_GPU_OPENGL offscreen_render_target :
		virtual public render_target
	{
	public:


		


		//comptr<ID3D11Texture2D> m_ptextureOffscreen;
		//comptr< ID3D11SamplerState> m_psamplerstate;
		//comptr<ID3D11ShaderResourceView>m_pshaderresourceview;
		//static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

		offscreen_render_target();
		//offscreen_render_target(renderer* pgpurenderer, const ::int_size & size);
		//offscreen_render_target(renderer * pgpurenderer, const ::int_size& size, ::pointer <render_target>previous);
		~offscreen_render_target();



		void initialize_render_target(::gpu::renderer* pgpurenderer, const ::int_size& size, ::pointer <::gpu::render_target>previous) override;


		//VkFramebuffer getFrameBuffer(int index) { return swapChainFramebuffers[index]; }
		//VkRenderPass getRenderPass() { return m_vkrendertargetview; }
		//VkImageView getImageView(int index) { return m_imageview[index]; }
		//size_t imageCount() { return m_images.size(); }
		//VkFormat getImageFormat() { return imageFormat; }
		//VkExtent2D getExtent() { return m_extent; }
		//uint32_t width() { return m_extent.width; }
		//uint32_t height() { return m_extent.height; }

		//float extentAspectRatio() {
		//	return static_cast<float>(m_extent.width) / static_cast<float>(m_extent.height);
		//}
//		VkFormat findDepthFormat();

		//HRESULT acquireNextImage() override;
		//HRESULT submitCommandBuffers(const VkCommandBuffer* buffers);

		//bool compareSwapFormats(const offscreen_render_target& swapChain) const {
		//	return swapChain.depthFormat == depthFormat &&
		//		swapChain.imageFormat == imageFormat;
		//}

	//public:
		void on_init() override;
		void createRenderPassImpl();
		void createImageViews();
		void createDepthResources();
		void createRenderPass();
		void createFramebuffers();
		void createSyncObjects();

		//HRESULT submitSamplingWork(const VkCommandBuffer buffer, uint32_t* imageIndex);
		//HRESULT submitSamplingWork(const VkCommandBuffer buffer);


		virtual void defer_resize(const ::int_size& size);

		//// Helper functions
		//VkSurfaceFormatKHR chooseSwapSurfaceFormat(
		//	const ::array<VkSurfaceFormatKHR>& availableFormats);
		//VkPresentModeKHR chooseSwapPresentMode(
		//	const ::array<VkPresentModeKHR>& availablePresentModes);
		//VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		//VkFormat imageFormat;
		//VkFormat depthFormat;
		//VkExtent2D m_extent;

		//::array<VkFramebuffer> swapChainFramebuffers;
		//VkRenderPass m_vkrendertargetview;

		////::array<VkImage> depthImages;
		////::array<VkDeviceMemory> depthImageMemorys;
		////::array<VkImageView> depthImageViews;
		//VkSampler m_vksampler;
		// ::array<VkDeviceMemory> m_imagememories;
		////::array<VkImage> swapChainImages;
		////::array<VkImageView> swapChainImageViews;

		//context* m_pgpucontext;
		//VkExtent2D windowExtent;

		////VkSwapchainKHR swapChain;
		//::pointer<offscreen_render_target> oldOffScreen;

		//::array<VkSemaphore> imageAvailableSemaphores;
		//::array<VkSemaphore> renderFinishedSemaphores;
		//::array<VkFence> inFlightFences;
		//::array<VkFence> imagesInFlight;
		//size_t currentFrame = 0;
	};


}  // namespace gpu_opengl



