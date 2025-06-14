#pragma once

//
//#include "render_target.h"
//
//
//namespace gpu_directx11
//{
//
//
//   class swap_chain_render_target :
//      virtual public render_target
//   {
//   public:
//
//      ::comptr<IDXGISwapChain> m_pdxgiswapchain;
//
//      ::comptr<ID3D11Texture2D> m_ptextureShared;
//      //VkSwapchainKHR       m_vkswapchain;
//      uint32_t             currentImageIndex;
//      //::int_size m_size;
//
//      ::comptr<ID3D11VertexShader> m_pvertexshaderFullscreen;
//      ::comptr<ID3D11PixelShader> m_ppixelshaderFullscreen;
//      ::comptr<ID3D11SamplerState> m_psamplerstateLinear;
//      ::comptr<ID3D11ShaderResourceView> m_pshaderresourceviewShader;
//
//
//      static constexpr int MAX_FRAMES_IN_FLIGHT = 2;
//
//      //swap_chain_render_target();
//      swap_chain_render_target(renderer* pgpurenderer, const ::int_size & size);
//      swap_chain_render_target(renderer * pgpurenderer, const ::int_size& size, ::pointer <render_target>previous);
//      ~swap_chain_render_target();
//
//      //swap_chain_render_target(const swap_chain_render_target&) = delete;
//      //swap_chain_render_target& operator=(const swap_chain_render_target&) = delete;
//
//      //VkFramebuffer getFrameBuffer(int index) { return swapChainFramebuffers[index]; }
//      //VkRenderPass getRenderPass() { return m_vkrendertargetview; }
//      //VkImageView getImageView(int index) { return swapChainImageViews[index]; }
//      //size_t imageCount() { return swapChainImages.size(); }
//      //VkFormat getSwapChainImageFormat() { return swapChainImageFormat; }
//      //VkExtent2D getSwapChainExtent() { return m_extent; }
//      //uint32_t width() { return m_extent.width; }
//      //uint32_t height() { return m_extent.height; }
//
//      //float extentAspectRatio() {
//      //   return static_cast<float>(m_extent.width) / static_cast<float>(m_extent.height);
//      //}
//  //    VkFormat findDepthFormat();
//
//      HRESULT acquireNextImage() override;
////      HRESULT submitCommandBuffers(const VkCommandBuffer* buffers) override;
//      int get_image_index() const override;
//      //bool compareSwapFormats(const swap_chain_render_target& m_swapchain) const {
//      //   return m_swapchain.swapChainDepthFormat == swapChainDepthFormat &&
//      //      m_swapchain.swapChainImageFormat == swapChainImageFormat;
//      //}
//
//   //public:
//      void init();
//      void createRenderPassImpl();
//      void createImageViews();
//      void createDepthResources();
//      void createRenderPass();
//      void createFramebuffers();
//      void createSyncObjects();
//
//      //// Helper functions
//      //VkSurfaceFormatKHR chooseSwapSurfaceFormat(
//      //   const ::array<VkSurfaceFormatKHR>& availableFormats);
//      //VkPresentModeKHR chooseSwapPresentMode(
//      //   const ::array<VkPresentModeKHR>& availablePresentModes);
//      //VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
//
//      /*VkFormat swapChainImageFormat;
//      VkFormat swapChainDepthFormat;
//      VkExtent2D m_extent;
//
//      ::array<VkFramebuffer> swapChainFramebuffers;
//      VkRenderPass m_vkrendertargetview;
//
//      ::array<VkImage> depthImages;
//      ::array<VkDeviceMemory> depthImageMemorys;
//      ::array<VkImageView> depthImageViews;
//      ::array<VkImage> swapChainImages;
//      ::array<VkImageView> swapChainImageViews;
//
//      ::pointer < context > m_pgpucontext;
//      VkExtent2D windowExtent;*/
//
//      //::pointer<swap_chain_render_target> oldSwapChain;
//
//      //::array<VkSemaphore> imageAvailableSemaphores;
//      //::array<VkSemaphore> renderFinishedSemaphores;
//      //::array<VkFence> inFlightFences;
//      //::array<VkFence> imagesInFlight;
//      //size_t currentFrame = 0;
//
//      virtual void endDraw();
//
//   };
//
//
//}  // namespace gpu_directx11
//
//
