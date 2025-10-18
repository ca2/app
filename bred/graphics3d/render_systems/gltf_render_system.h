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

      ::graphics3d::scene_renderable *m_pscenerenderableCurrent;
      bool m_bDisableAlbedo = false;
      bool m_bDisableMetallicRoughness = false;
      bool m_bDisableNormal = false;
      bool m_bDisableAmbientOcclusion = false;
      bool m_bDisableEmissive = false;
      bool m_bForceDefaultMetallicFactor = false;
      bool m_bForceDefaultRoughnessFactor = false;
      bool m_bForceDefaultAmbientOcclusionFactor = false;
      bool m_bForceDefaultAlbedo = false;
      bool m_bForceDefaultEmission = false;
      float m_fDefaultMetallicFactor = 0.0f;
      float m_fDefaultRoughnessFactor = 0.0f;
      float m_fDefaultAmbientOcclusionFactor = 0.0f;
      glm::vec3 m_seq3DefaultAlbedo={};
      glm::vec3 m_seq3DefaultEmission = {};

      //VkDescriptorSetLayout m_pdescriptorsetlayoutUbo;
      //VkDescriptorSetLayout m_iblSetLayout;
      //VkDescriptorSet m_iblDescriptorSet;

		//s::pointer <::graphics3d::device > m_pgpudevice;

		// VkDescriptorSetLayout m_pdescriptorsetlayoutUbo;
		// VkDescriptorSetLayout m_iblSetLayout;
		// VkDescriptorSet m_iblDescriptorSet;

		//::pointer<::graphics3d::pipeline> m_opaquePipeline;
		//::pointer<::graphics3d::pipeline> m_maskPipeline;
		//::pointer<::graphics3d::pipeline> m_blendPipeline;
		///VkPipelineLayout m_pipelineLayout;
		::pointer < ::gpu::shader > m_pshaderOpaque;
		::pointer < ::gpu::shader > m_pshaderMask;
		::pointer < ::gpu::shader > m_pshaderBlend;
		///

		::pointer <::graphics3d::asset_manager > m_passetmanager;

		//::pointer<::graphics3d::sandbox_descriptor_set_layout> m_pdescriptorsetlayoutIbl;
		//::array_base<VkDescriptorSet>				  m_vkdescriptorsetaIbl;


		//gltf_render_system(::graphics3d::device * pdevice, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout, IAssetProvider& assets);
		gltf_render_system();
		~gltf_render_system();

      void on_prepare(::gpu::context *pgpucontext) override;

		// gltf_render_system(const gltf_render_system&) = delete;
		// gltf_render_system& operator=(const gltf_render_system&) = delete;

		// void init(
		// 	graphics3d::device * pdevice,
		// 	VkRenderPass            renderPass,
		// 	VkDescriptorSetLayout   globalSetLayout,
		// 	graphics3d::sandbox_descriptor_pool& descriptorPool,
		// 	size_t frameCount)override;

		//void render(::gpu::frame * pframe) override;
		void on_render(::gpu::context* pgpucontext, ::graphics3d::scene_base* pscene) override;
	//private:
		//void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
		//void createPipeline(VkRenderPass renderPass);


	};


} // namespace graphics3d


