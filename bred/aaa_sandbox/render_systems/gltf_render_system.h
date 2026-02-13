#pragma once
//#include "SceneFoundry/graphics3d/render_system.h"
#include "bred/graphics3d/render_system.h"

//#include "SceneFoundry/graphics3d/asset_provider_i.h"
//#include "SceneFoundry/graphics3d/game_object_i.h"

//#include "device.h"
//#include "pipeline.h"
//#include "SceneFoundry/graphics3d/descriptor.h"

//#include "gltf.h"
//#include "SceneFoundry/graphics3d/renderer.h"

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


		//s::pointer <::graphics3d::device > m_pgpudevice;

		// aaaVkDescriptorSetLayout m_globalSetLayout;
		// aaaVkDescriptorSetLayout m_iblSetLayout;
		// VkDescriptorSet m_iblDescriptorSet;

		//::pointer<::graphics3d::pipeline> m_opaquePipeline;
		//::pointer<::graphics3d::pipeline> m_maskPipeline;
		//::pointer<::graphics3d::pipeline> m_blendPipeline;
		///VkPipelineLayout m_pipelineLayout;
		::pointer < ::gpu::shader > m_pshaderOpaque;
		::pointer < ::gpu::shader > m_pshaderMask;
		::pointer < ::gpu::shader > m_pshaderBlend;
		///

		::pointer <::graphics3d::IAssetProvider > m_passetmanager;

		//::pointer<::graphics3d::sandbox_descriptor_set_layout> m_iblLayout;
		//::array_base<VkDescriptorSet>				  m_iblDescriptorSets;


		//gltf_render_system(::graphics3d::device * pdevice, VkRenderPass renderPass, aaaVkDescriptorSetLayout globalSetLayout, IAssetProvider& assets);
		gltf_render_system();
		~gltf_render_system();

		// gltf_render_system(const gltf_render_system&) = delete;
		// gltf_render_system& operator=(const gltf_render_system&) = delete;

		// void init(
		// 	graphics3d::device * pdevice,
		// 	VkRenderPass            renderPass,
		// 	aaaVkDescriptorSetLayout   globalSetLayout,
		// 	graphics3d::sandbox_descriptor_pool& descriptorPool,
		// 	size_t frameCount)override;

		void render(::gpu::frame * pframe) override;
	//private:
		//void createPipelineLayout(aaaVkDescriptorSetLayout globalSetLayout);
		//void createPipeline(VkRenderPass renderPass);


	};


} // namespace graphics3d


