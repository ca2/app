#pragma once
#include "bred/sandbox/render_system.h"

//#include "SceneFoundry/sandbox_renderer/device.h"
//#include "SceneFoundry/sandbox_renderer/pipeline.h"
//#include <vulkan/vulkan.h>

// STD
//#include <memory>
//#include <vector>

namespace sandbox_renderer
{


	class CLASS_DECL_SANDBOX_RENDERER object_render_system :
		virtual public ::sandbox::IRenderSystem
	{
	public:


		::pointer < ::sandbox_renderer::device > m_pgpudevice;

		//VkDescriptorSetLayout m_globalSetLayout;

		//::pointer<::gpu::pipeline> m_ppipeline;
		::pointer < ::gpu::shader > m_pshader;
		///	VkPipelineLayout m_pipelineLayout;

		//object_render_system(::sandbox_renderer::device *pdevice, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);
		object_render_system();
		~object_render_system();

		//object_render_system(const object_render_system&) = delete;
		//object_render_system& operator=(const object_render_system&) = delete;

		// void init(
		// 	::sandbox_renderer::device * pdevice,
		// 	VkRenderPass            renderPass,
		// 	VkDescriptorSetLayout   globalSetLayout,
		// 	::sandbox_renderer::sandbox_descriptor_pool& descriptorPool,
		// 	size_t frameCount)override;

		void on_render(::sandbox::IFrame * pframe) override;
		//private:
		//void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
		//void createPipeline(VkRenderPass renderPass);

	};


} // namespace sandbox_renderer


