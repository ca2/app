#pragma once
//#include "SceneFoundry/graphics3d/render_system.h"
#include "bred/graphics3d/render_system.h"

//#include "SceneFoundry/graphics3d/asset_provider_i.h"
//#include "SceneFoundry/graphics3d/game_object_i.h"

//#include "device.h"
//#include "pipeline.h"
//#include "SceneFoundry/sandbox_renderer/descriptor.h"

//#include "gltf.h"
//#include "SceneFoundry/sandbox_renderer/renderer.h"

// STD
//#include <memory>
//#include <vector>

//#include <vulkan/vulkan.h>


namespace graphics3d
{


	class CLASS_DECL_BRED gltf_render_system :
		virtual public ::graphics3d::render_system
	{
	public:


		//s::pointer <::sandbox_renderer::device > m_pgpudevice;

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

		::pointer <::graphics3d::IAssetProvider > m_passetprovider;

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

		void render(::graphics3d::IFrame * pframe) override;
	//private:
		//void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
		//void createPipeline(VkRenderPass renderPass);


	};


} // namespace graphics3d


