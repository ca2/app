#pragma once
#include "SceneFoundry/sandbox/render_system.h"

//#include "SceneFoundry/sandbox/asset_provider_i.h"
//#include "SceneFoundry/sandbox/game_object_i.h"

//#include "device.h"
//#include "pipeline.h"
//#include "SceneFoundry/sandbox_renderer/descriptor.h"

//#include "gltf.h"
//#include "SceneFoundry/sandbox_renderer/renderer.h"

// STD
//#include <memory>
//#include <vector>

//#include <vulkan/vulkan.h>


namespace sandbox_renderer
{


	class CLASS_DECL_SANDBOX_RENDERER gltf_render_system :
		virtual public ::sandbox::IRenderSystem
	{
	public:


		::pointer <::sandbox_renderer::device > m_pgpudevice;

		// VkDescriptorSetLayout m_globalSetLayout;
		// VkDescriptorSetLayout m_iblSetLayout;
		// VkDescriptorSet m_iblDescriptorSet;

		//::pointer<::sandbox_renderer::pipeline> m_opaquePipeline;
		//::pointer<::sandbox_renderer::pipeline> m_maskPipeline;
		//::pointer<::sandbox_renderer::pipeline> m_blendPipeline;
		///VkPipelineLayout m_pipelineLayout;
		::pointer < ::gpu::shader > m_pshaderOpaque;
		::pointer < ::gpu::shader > m_pshaderMask;
		::pointer < ::gpu::shader > m_pshaderBlend;
		///

		::pointer <::sandbox::IAssetProvider > m_passetprovider;

		//::pointer<::sandbox_renderer::sandbox_descriptor_set_layout> m_iblLayout;
		//::array_base<VkDescriptorSet>				  m_iblDescriptorSets;


		//gltf_render_system(::sandbox_renderer::device * pdevice, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout, IAssetProvider& assets);
		gltf_render_system();
		~gltf_render_system();

		// gltf_render_system(const gltf_render_system&) = delete;
		// gltf_render_system& operator=(const gltf_render_system&) = delete;

		// void init(
		// 	sandbox_renderer::device * pdevice,
		// 	VkRenderPass            renderPass,
		// 	VkDescriptorSetLayout   globalSetLayout,
		// 	sandbox_renderer::sandbox_descriptor_pool& descriptorPool,
		// 	size_t frameCount)override;

		void render(::sandbox::IFrame * pframe) override;
	//private:
		//void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
		//void createPipeline(VkRenderPass renderPass);


	};


} // namespace sandbox_renderer


