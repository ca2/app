#include "framework.h"
// obj_render_system.cpp
#include "object_render_system.h"
//#include "pipeline.h"
//#include "port/graphics/freetype/include/freetype/internal/fttrace.h"
#include "bred/gpu/shader.h"
#include "bred/graphics3d/model.h"
#include "bred/graphics3d/scene_object.h"
#include "bred/graphics3d/frame.h"
// // External
// 
// 
// 
//

// STD
//////#include <stdexcept>
//#include <array>
//#include <cassert>
//#include <stdexcept>

// TODO: Add wireframe pipeline that player input will toggle 
namespace graphics3d
{
	struct PushConstantData {
		floating_matrix4 modelMatrix{ 1.f };
		floating_matrix4 normalMatrix{ 1.f };
		//int textureIndex;
	};

	// object_render_system::object_render_system(graphics3d::device *pdevice, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout)
	// 	: m_pgpudevice(pdevice)//, m_globalSetLayout(globalSetLayout)
	// {
	//
	// }
	object_render_system::object_render_system()
//		: m_pgpudevice(pdevice)//, m_globalSetLayout(globalSetLayout)
	{

	}

	// void object_render_system::init(
	// 	graphics3d::device * pdevice,
	// 	VkRenderPass renderPass,
	// 	VkDescriptorSetLayout globalSetLayout,
	// 	graphics3d::sandbox_descriptor_pool& descriptorPool,
	// 	size_t frameCount)
	// {
	// 	ASSERT(pdevice == m_pgpudevice);
	//
	// 	createPipelineLayout(globalSetLayout);
	// 	createPipeline(renderPass);
	// }

	object_render_system::~object_render_system()
	{
		//vkDestroyPipelineLayout(m_pgpudevice->device(), m_pipelineLayout, nullptr);
	}


	void object_render_system::on_render(::gpu::frame * pframe)
	{
		//m_ppipeline->bind(frame.m_pcommandbuffer);
		//m_pshader->bind(pframe->getCommandBuffer());
		m_pshader->bind();
		//::preallocated_array_base< ::array_base <VkDescriptorSet>, 1 > descriptorSets;

		//descriptorSets = { frame.globalDescriptorSet };

		// vkCmdBindDescriptorSets(
		// 	frame.m_pcommandbuffer,
		// 	VK_PIPELINE_BIND_POINT_GRAPHICS,
		// 	m_pipelineLayout,
		// 	0,
		// 	static_cast<uint32_t>(descriptorSets.size()),
		// 	descriptorSets.data(),
		// 	0,
		// 	nullptr
		// );

		auto psceneobjects = pframe->scene_objects();

		auto & sceneobjects = *psceneobjects;

		for (auto& [id, psceneobject] : sceneobjects)
		{

			//auto& obj = kv.element2();

			auto & transformcomponent = psceneobject->transform();
			PushConstantData push{};
			push.modelMatrix = transformcomponent.floating_matrix4();
			push.normalMatrix = transformcomponent.normalMatrix();
			//
			// vkCmdPushConstants(
			// 	frame.m_pcommandbuffer,
			// 	m_pipelineLayout,
			// 	VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
			// 	0,
			// 	sizeof(PushConstantData),
			// 	&push);

			m_pshader->set_push_properties(::as_memory_block(push));

			if (auto pmodel = psceneobject->model())
			   {
				//model->bind(frame.m_pcommandbuffer);
				//model->draw(frame.m_pcommandbuffer);
				pmodel->bind(pframe->getCommandBuffer());
				pmodel->draw(pframe->getCommandBuffer());
			}

		}

	}


	// void object_render_system::createPipelineLayout(VkDescriptorSetLayout globalSetLayout) {
	//
	// 	VkPushConstantRange pushConstantRange{};
	// 	pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
	// 	pushConstantRange.offset = 0;
	// 	pushConstantRange.size = sizeof(PushConstantData);
	//
	// 	::array_base<VkDescriptorSetLayout> descriptorSetLayouts = {
	// 		globalSetLayout
	// 	};
	//
	// 	VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
	// 	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	// 	pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
	// 	pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
	// 	pipelineLayoutInfo.pushConstantRangeCount = 1;
	// 	pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
	//
	//
	//
	// 	if (vkCreatePipelineLayout(m_pgpudevice->device(), &pipelineLayoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS) {
	// 		throw std::runtime_error("Failed to create pipeline layout");
	// 	}
	// }

	// void object_render_system::createPipeline(VkRenderPass renderPass)
	// {
	// 	ASSERT(m_pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");
	//
	// 	//graphics3d::pipeline_configuration_information pipelineconfiguration{};
	// 	//graphics3d::pipeline::default_pipeline_configuration(pipelineconfiguration);
	//
	// 	//pipelineconfiguration.renderPass = renderPass;
	// 	//pipelineconfiguration.pipelineLayout = m_pipelineLayout;
	//
	// 	::string vertShaderPath = "matter://shaders/spirV/vert.vert.spv";
	// 	::string fragShaderPath = "matter://shaders/spirV/frag.frag.spv";
	//
	// 	//m_ppipeline = øallocate graphics3d::pipeline(
	// 	//	m_pgpudevice,
	// 	//	vertShaderPath.c_str(),
	// 	//	fragShaderPath.c_str(),
	// 	//	pipelineconfiguration
	// 	//);
	// }
} // namespace graphics3d
