#include "framework.h"
#include "renderer.h"
#include "bred/graphics3d/render_system.h"
#include "aura/user/user/interaction.h"
//#include <stdexcept>
//#include <array>
//#include <cassert>
//#include <spdlog/spdlog.h>

namespace sandbox_renderer
{


   // renderer::renderer(device * pdevice, ::user::interaction * puserinteraction)
   //    : m_pgpudevice(pdevice),
   //    m_puserinteraction(puserinteraction)
   // {
   //    recreateSwapchain();
   //
   //    createGlobalDescriptorObjects();
   //    allocateGlobalDescriptors();
   // }
   renderer::renderer()
   {
      // recreateSwapchain();
      //
      // createGlobalDescriptorObjects();
      // allocateGlobalDescriptors();
   }
   renderer::~renderer() {
      //freeCommandBuffers();
   }
   // void renderer::createGlobalDescriptorObjects() {
   //    // === build pool exactly like old buildLayouts() ===
   //    m_pool = ::renderer::sandbox_descriptor_pool::Builder{ m_pgpudevice }
   //       .setMaxSets(FrameCount + 3 /*texture+sky+ibl*/)
   //       .addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, FrameCount)
   //       .addPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 10)
   //       .setPoolFlags(VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT)
   //       .build();
   //
   //    // === global UBO layout (set=0) ===
   //    m_globalLayout = sandbox_descriptor_set_layout::Builder{ m_pgpudevice }
   //       .addBinding(0,
   //          VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
   //          VK_SHADER_STAGE_ALL_GRAPHICS)
   //       .build();
   // }
   //
   // void renderer::allocateGlobalDescriptors() {
   //
   //    m_uboBuffers.resize(FrameCount);
   //    for (uint32_t i = 0; i < FrameCount; i++) {
   //       m_uboBuffers[i] = øcreate_pointer<sandbox_buffer>(
   //          m_pgpudevice,
   //          sizeof(GlobalUbo),
   //          1,
   //          VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
   //          VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
   //       );
   //       m_uboBuffers[i]->map();
   //    }
   //
   //    m_globalDescriptorSets.resize(FrameCount);
   //    for (uint32_t i = 0; i < FrameCount; i++) {
   //       auto bufInfo = m_uboBuffers[i]->descriptorInfo();
   //       VkDescriptorSet set;
   //       // allocate
   //       if (!m_pool->allocateDescriptor(
   //          m_globalLayout->getDescriptorSetLayout(),
   //          set, 0)) {
   //          throw std::runtime_error("Failed to allocate global descriptor set");
   //       }
   //       // write
   //       sandbox_descriptor_writer(*m_globalLayout, *m_pool)
   //          .writeBuffer(0, &bufInfo)
   //          .build(set);
   //
   //       m_globalDescriptorSets[i] = set;
   //    }
   //
   // }

   void renderer::initializeSystems(::graphics3d::IAssetProvider * passetprovider)
{
      // // grab the things every system will need
      // VkRenderPass rp = m_swapchain->getRenderPass();
      // VkDescriptorSetLayout globalLayout = m_globalLayout->getDescriptorSetLayout();
      // ::renderer::sandbox_descriptor_pool& pool = *m_pool;
      //
      // // Create skybox system (note: only construct, do not init yet)
      // //auto skyboxSystem = øcreate_pointer<skybox_ibl_render_system>(m_pgpudevice, rp, globalLayout);
      //
      // // Ask provider for the assets we need
      // // model
      // auto skyModel = provider.getGLTFmodel("cube"); // or the name you set in assets.json
      // if (skyModel) {
      //    //skyboxSystem->setSkyboxModel(skyModel);
      // }
      // else {
      //    warning("No skybox model found in provider for 'cube'");
      // }
      //
      // // cubemap descriptor (VkDescriptorImageInfo)
      // // choose the name you used in default_scene_assets.json (e.g. "skybox_hdr")
      // try {
      //    VkDescriptorImageInfo cubemapDesc = provider.getCubemapDescriptor("skybox_hdr");
      //    //skyboxSystem->setSkyboxCubemap(cubemapDesc);
      // }
      // catch (const ::exception& e) {
      //    warning("Skybox: cubemap not found: {}", e.get_message());
      // }
      //
      // // push it into systems list, before we init them
      // //m_systems.add(std::move(skyboxSystem));
      //
      // m_systems.add(øcreate_pointer<object_render_system>(
      //    m_pgpudevice,
      //    rp,
      //    globalLayout
      // ));
      //
      // m_systems.add(øcreate_pointer<gltf_render_system>(
      //    m_pgpudevice,
      //    rp,
      //    globalLayout,
      //    provider
      // ));
      //
      // m_systems.add(øcreate_pointer<point_light_render_system>(
      //    m_pgpudevice,
      //    rp,
      //    globalLayout
      // ));
      //
      //
      // // Now call init() hooks
      // for (auto& sys : m_systems) {
      //    sys->init(
      //       m_pgpudevice,
      //       rp,
      //       globalLayout,
      //       pool,
      //       FrameCount
      //    );
      // }
   }
   void renderer::updateSystems(::graphics3d::IFrame * pframe, ::gpu::properties * ppropertiesGlobalUbo, float deltaTime)
   {
      for (auto& prendersystem : m_rendersystema) {
         //prendersystem->update(pframe, ppropertiesGlobalUbo);
         prendersystem->on_update(pframe);
      }
   }

   void renderer::renderSystems(::graphics3d::IFrame * pframe) {
      // upload camera UBO into m_uboBuffers[frame.frameIndex]...
      // loop all your render systems:
      for (auto& prendersystem : m_rendersystema)
      {
         prendersystem->on_render(pframe);
      }
   }

   // void renderer::recreateSwapchain() {
   //
   //    auto extent = m_window.getExtent();
   //    while (extent.width == 0 || extent.width == 0)
   //    {
   //       //glfwWaitEvents();
   //       extent = m_window.getExtent();
   //    }
   //
   //    vkDeviceWaitIdle(m_pgpudevice->device());
   //
   //    if (m_swapchain == nullptr)
   //    {
   //
   //       m_swapchain = øcreate_pointer<sandbox_swap_chain>(
   //          m_pgpudevice,
   //          extent
   //       );
   //
   //    }
   //    else {
   //       ::pointer oldSwapchain = std::move(m_swapchain);
   //       m_swapchain = øcreate_pointer<sandbox_swap_chain>(m_pgpudevice, extent, oldSwapchain);
   //       if (!oldSwapchain->compareSwapFormats(*m_swapchain.get())) {
   //          throw std::runtime_error("Swap chain image(or depth) format has changed");
   //       }
   //    }
   //    createCommandBuffers();
   // }
   // ISandboxRenderer::FrameContext renderer::beginFrame() {
   //    // 1) AcquireNextImage does the fence‐wait for the current in‐flight frame internally
   //    VkResult result = m_swapchain->acquireNextImage(&m_currentImageIndex);
   //    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
   //       recreateSwapchain();
   //       return {}; // invalid context
   //    }
   //    if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
   //       throw std::runtime_error("Failed to acquire swap chain image");
   //    }
   //
   //    // 2) Map imageIndex → frameIndex (in‐flight slot)
   //    //    Typically they’re the same because swapchain was created with MAX_FRAMES_IN_FLIGHT images.
   //    m_currentFrameIndex = m_currentImageIndex % FrameCount;
   //
   //    // 3) Begin recording
   //    VkCommandBuffer cmd = m_commandBuffers[m_currentImageIndex];
   //    vkResetCommandBuffer(cmd, 0);
   //    VkCommandBufferBeginInfo bi{ VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
   //    if (vkBeginCommandBuffer(cmd, &bi) != VK_SUCCESS) {
   //       throw std::runtime_error("Failed to begin recording command buffer");
   //    }
   //
   //    m_bIsFrameStarted = true;
   //
   //    // 4) Build the FrameContext
   //    ISandboxRenderer::FrameContext ctx{};
   //    ctx.graphicsCommandBuffers = m_commandBuffers;
   //    ctx.primaryGraphicsCommandBuffer = cmd;
   //    ctx.frameIndex = m_currentFrameIndex;
   //    // let the game know which fence is in flight if it wants to wait on it:
   //    ctx.frameFence = m_swapchain->getFence(m_currentFrameIndex);
   //    return ctx;
   // }
   // void renderer::endFrame(FrameContext& frame) {
   //    ASSERT(m_bIsFrameStarted && "endFrame() called when no frame in progress");
   //
   //    // // 1) finish command buffer
   //    // if (vkEndCommandBuffer(frame.primaryGraphicsCommandBuffer) != VK_SUCCESS) {
   //    //    throw std::runtime_error("Failed to end command buffer");
   //    // }
   //
   //    // 2) hand off to swapchain (which will queue submit & signal its fence)
   //    VkResult result = m_swapchain->submitCommandBuffers(
   //       &frame.primaryGraphicsCommandBuffer,
   //       &m_currentImageIndex  // you could also store this in frame
   //    );
   //
   //    // 3) handle resize/out‑of‑date
   //    if (result == VK_ERROR_OUT_OF_DATE_KHR
   //       || result == VK_SUBOPTIMAL_KHR
   //       || m_window.wasWindowResized())
   //    {
   //       m_window.resetWindowResizedFlag();
   //       recreateSwapchain();
   //    }
   //    else if (result != VK_SUCCESS) {
   //       throw std::runtime_error("Failed to present swap chain image!");
   //    }
   //
   //
   //    m_bIsFrameStarted = false;
   //    m_currentFrameIndex = (m_currentFrameIndex + 1) % FrameCount;
   // }
   // void renderer::beginSwapChainRenderPass(FrameContext& frame)
   // {
   //    ASSERT(m_bIsFrameStarted && "Can't call beginSwapChainRenderPass if frame is not in progress");
   //
   //    //
   //    // VkRenderPassBeginInfo renderPassInfo{};
   //    // renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
   //    // renderPassInfo.renderPass = m_swapchain->getRenderPass();
   //    // renderPassInfo.framebuffer = m_swapchain->getFrameBuffer(m_currentImageIndex);
   //    //
   //    // renderPassInfo.renderArea.offset = { 0, 0 };
   //    // renderPassInfo.renderArea.extent = m_swapchain->getSwapChainExtent();
   //    //
   //    // ::preallocated_array_base< ::array_base <VkClearValue>,2 > clearValues{};
   //    // clearValues[0].color = { 0.5f, 0.5f, 0.5f, 1.0f };
   //    // clearValues[1].depthStencil = { 1.0f, 0 };
   //    // renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
   //    // renderPassInfo.pClearValues = clearValues.data();
   //    //
   //    // vkCmdBeginRenderPass(frame.primaryGraphicsCommandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
   //    // VkViewport viewport{};
   //    // viewport.x = 0.0f;
   //    // viewport.y = 0.0f;
   //    // viewport.width = static_cast<float>(m_swapchain->getSwapChainExtent().width);
   //    // viewport.height = static_cast<float>(m_swapchain->getSwapChainExtent().height);
   //    // viewport.minDepth = 0.0f;
   //    // viewport.maxDepth = 1.0f;
   //    // VkRect2D scissor{ {0, 0}, m_swapchain->getSwapChainExtent() };
   //    // vkCmdSetViewport(frame.primaryGraphicsCommandBuffer, 0, 1, &viewport);
   //    // vkCmdSetScissor(frame.primaryGraphicsCommandBuffer, 0, 1, &scissor);
   // }
   //
   // void renderer::endSwapChainRenderPass(FrameContext& frame)
   // {
   //
   //    ASSERT(m_bIsFrameStarted && "Can't call endSwapChainRenderPass if frame is not in progress");
   //
   //    //vkCmdEndRenderPass(frame.primaryGraphicsCommandBuffer);
   // }
   // void renderer::createCommandBuffers() {
   //    size_t imageCount = m_swapchain->imageCount();
   //    m_commandBuffers.resize(imageCount);
   //    //m_commandBuffers.resize(sandbox_swap_chain::MAX_FRAMES_IN_FLIGHT);
   //    //
   //    // VkCommandBufferAllocateInfo allocInfo{};
   //    // allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
   //    // allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
   //    // allocInfo.commandPool = m_pgpudevice->getCommandPool();
   //    // allocInfo.commandBufferCount = static_cast<uint32_t>(m_commandBuffers.size());
   //    //
   //    // if (vkAllocateCommandBuffers(
   //    //    m_pgpudevice->device(),
   //    //    &allocInfo,
   //    //    m_commandBuffers.data()
   //    // ) != VK_SUCCESS) {
   //    //    throw std::runtime_error("failed to allocate command buffers!");
   //    // }
   // }
   //
   // void renderer::freeCommandBuffers() {
   //    if (m_commandBuffers.empty()) {
   //       return;
   //    }
   //
   //    // vkFreeCommandBuffers(
   //    //    m_pgpudevice->device(),
   //    //    m_pgpudevice->getCommandPool(),
   //    //    static_cast<uint32_t>(m_commandBuffers.size()),
   //    //    m_commandBuffers.data()
   //    // );
   //
   //    m_commandBuffers.clear();
   // }
   //
   // void renderer::waitDeviceIdle() {
   //    //vkDeviceWaitIdle(m_pgpudevice->device());
   // }

   float renderer::getAspectRatio() const
   {

      //return m_swapchain->extentAspectRatio();

      return 1920.0f / 1080.f;

   }


   bool renderer::isFrameInProgress() const
   {

      return m_bIsFrameStarted;

   }


} // namespace renderer



