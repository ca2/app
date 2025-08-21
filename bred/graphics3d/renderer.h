// vulkan_renderer.h
#pragma once
//#include <memory>
#include "bred/gpu/properties.h"
#include "bred/graphics3d/renderer.h"
//#include "SceneFoundry/graphics3d/render_system_i.h"
//#include "SceneFoundry/graphics3d/asset_provider_i.h"
// #include "SceneFoundry/sandbox_renderer/render_systems/object_render_system.h"
// #include "SceneFoundry/sandbox_renderer/render_systems/gltf_render_system.h"
// #include "SceneFoundry/sandbox_renderer/render_systems/skybox_ibl_render_system.h"
// #include "SceneFoundry/sandbox_renderer/render_systems/point_light_render_system.h"
// //#include "SceneFoundry/sandbox_renderer/include/window.h"
// #include "SceneFoundry/sandbox_renderer/device.h"
//#include "SceneFoundry/sandbox_renderer/swapchain.h"
//#include "SceneFoundry/sandbox_renderer/descriptor.h"
//#include "SceneFoundry/sandbox_renderer/buffer.h"
//#include <vector>
//#include <array>


namespace sandbox_renderer
{

	class CLASS_DECL_SANDBOX_RENDERER renderer :
		virtual public ::graphics3d::IRenderer,
		virtual public ::particle
	{
	public:

	//private:

		//::array_base<VkCommandBuffer>					    m_commandBuffers;
		//VkCommandPool										   m_commandPool = VK_NULL_HANDLE;
		uint32_t								         m_currentImageIndex = 0;
		int												 m_currentFrameIndex = 0;
		bool										       m_bIsFrameStarted = false;

		//::pointer<sandbox_descriptor_set_layout>		  m_globalLayout;

		device * m_pgpudevice;
		::user::interaction * m_puserinteraction;
		::pointer_array_base<::graphics3d::render_system>				   m_rendersystema;

		//::pointer<sandbox_swap_chain>					     m_swapchain;
		//::pointer<sandbox_swap_chain>					  m_oldSwapchain;
		//VkInstance												  m_instance = VK_NULL_HANDLE;

		uint32_t								      m_width{ 0 }, m_height{ 0 };
		::gpu::properties							m_propertiesGlobalUbo;
		//::array_base<VkDescriptorSet>				  m_globalDescriptorSets;
		//::array_base<VkFence>							    m_inFlightFences;

		//static constexpr size_t FrameCount =
///			sandbox_swap_chain::MAX_FRAMES_IN_FLIGHT;


		//renderer(::sandbox_renderer::device * pdevice, ::user::interaction * puserinteraction);
		renderer();
		//renderer(const sandbox_renderer&) = delete;
		//renderer& operator=(const sandbox_renderer&) = delete;
		~renderer() override;



		::graphics3d::IFrame * beginFrame() override;

		void endFrame(::graphics3d::IFrame * pframe) override;
		void beginSwapChainRenderPass(::graphics3d::IFrame * pframe)override;
		void endSwapChainRenderPass(::graphics3d::IFrame *pframe)override;

		void initializeSystems(::graphics3d::IAssetProvider * passetprovider);
		void initSkyboxSystem();
		void renderSystems(::graphics3d::IFrame *pframe)override;

		void waitDeviceIdle() override;

		void updateSystems(::graphics3d::IFrame *pframe, ::gpu::properties * ppropertiesGlobalUbo, float deltaTime)override;

		// Inline helpers
		//inline VkRenderPass getSwapChainRenderPass() const { return m_swapchain->getRenderPass(); }
		virtual float getAspectRatio() const;
		virtual inline bool isFrameInProgress() const;

		// inline VkCommandBuffer getCurrentCommandBuffer() const {
		// 	ASSERT(m_bIsFrameStarted && "Cannot get command buffer when frame not in progress");
		// 	return m_commandBuffers[m_currentFrameIndex];
		// }

		inline 	int getFrameIndex() const {
			ASSERT(m_bIsFrameStarted && "Cannot get frame index when frame not in progress");
			return m_currentFrameIndex;
		}

		// inline const ::array_base<VkDescriptorSet>& getGlobalDescriptorSet() const {
		// 	return m_globalDescriptorSets;
		// }
		inline ::gpu::properties & global_ubo() {
			return m_propertiesGlobalUbo;
		}


		//::pointer<::sandbox_renderer::sandbox_descriptor_pool>                      m_pool;

		//void createGlobalDescriptorObjects();
		//void allocateGlobalDescriptors();


		//void createSwapChain();
		//void createCommandBuffers();
		//void freeCommandBuffers();
		//void recreateSwapchain();


	};


} // namespace sandbox_renderer


