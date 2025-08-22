#include "framework.h"
// obj_render_system.cpp
#include "object_render_system.h"
//#include "pipeline.h"
#include "bred/graphics3d/engine.h"
//#include "port/graphics/freetype/include/freetype/internal/fttrace.h"
#include "bred/gpu/shader.h"
#include "bred/graphics3d/model.h"
#include "bred/graphics3d/scene_object.h"
#include "bred/graphics3d/frame.h"
#include "graphics3d/game_layer.h"
#include "graphics3d/scene.h"
// // External
// #define GLM_FORCE_RADIANS
// #define GLM_FORCE_DEPTH_ZERO_TO_ONE
// #include <glm/glm.hpp>
//#include <glm/gtc/constants.hpp>

// STD
//////#include <stdexcept>
//#include <array>
//#include <cassert>
//#include <stdexcept>

// TODO: Add wireframe pipeline that player input will toggle 
namespace graphics3d
{
	struct PushConstantData {
		glm::mat4 modelMatrix{ 1.f };
		glm::mat4 normalMatrix{ 1.f };
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


	// void object_render_system::on_render()
	// {
	// 	//m_ppipeline->bind(frame.m_pcommandbuffer);
	// 	//m_pshader->bind(pframe->getCommandBuffer());
	// 	m_pshader->bind();
	// 	//::preallocated_array_base< ::array_base <VkDescriptorSet>, 1 > descriptorSets;
	//
	// 	//descriptorSets = { frame.globalDescriptorSet };
	//
	// 	// vkCmdBindDescriptorSets(
	// 	// 	frame.m_pcommandbuffer,
	// 	// 	VK_PIPELINE_BIND_POINT_GRAPHICS,
	// 	// 	m_pipelineLayout,
	// 	// 	0,
	// 	// 	static_cast<uint32_t>(descriptorSets.size()),
	// 	// 	descriptorSets.data(),
	// 	// 	0,
	// 	// 	nullptr
	// 	// );
	//
	//    auto pframe = ::gpu::current_frame();
	//
	//    auto pscene = m_pengine->current_scene();
	//
	// 	auto psceneobjects = pframe->scene_objects();
	//
	// 	auto & sceneobjects = *psceneobjects;
	//
	// 	for (auto& [id, psceneobject] : sceneobjects)
	// 	{
	//
	// 		//auto& obj = kv.element2();
	//
	// 		auto & transformcomponent = psceneobject->transform();
	// 		PushConstantData push{};
	// 		push.modelMatrix = transformcomponent.mat4();
	// 		push.normalMatrix = transformcomponent.normalMatrix();
	// 		//
	// 		// vkCmdPushConstants(
	// 		// 	frame.m_pcommandbuffer,
	// 		// 	m_pipelineLayout,
	// 		// 	VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
	// 		// 	0,
	// 		// 	sizeof(PushConstantData),
	// 		// 	&push);
	//
	// 		m_pshader->set_push_properties(::as_memory_block(push));
	//
	// 		if (auto pmodel = psceneobject->model())
	// 		   {
	// 			//model->bind(frame.m_pcommandbuffer);
	// 			//model->draw(frame.m_pcommandbuffer);
	// 			pmodel->bind(pframe->getCommandBuffer());
	// 			pmodel->draw(pframe->getCommandBuffer());
	// 		}
	//
	// 	}
	//
	// }
	//

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
	// 	//graphics3d::pipeline_configuration_information pipelineConfig{};
	// 	//graphics3d::pipeline::defaultPipelineConfigInfo(pipelineConfig);
	//
	// 	//pipelineConfig.renderPass = renderPass;
	// 	//pipelineConfig.pipelineLayout = m_pipelineLayout;
	//
	// 	::string vertShaderPath = "matter://shaders/spirV/vert.vert.spv";
	// 	::string fragShaderPath = "matter://shaders/spirV/frag.frag.spv";
	//
	// 	//m_ppipeline = øallocate graphics3d::pipeline(
	// 	//	m_pgpudevice,
	// 	//	vertShaderPath.c_str(),
	// 	//	fragShaderPath.c_str(),
	// 	//	pipelineConfig
	// 	//);
	// }



	void object_render_system::initialize_render_system(::graphics3d::engine* pengine)
	{

		initialize_render_system(pengine);

	}


	void object_render_system::on_prepare(::gpu::context* pgpucontext)
	{

		auto prenderer = pgpucontext->m_pgpurenderer;

		m_pshader = prenderer->create_shader(
			"matter://shaders/vert.vert",
			"matter://shaders/frag.frag",
			{ ::gpu::shader::e_descriptor_set_slot_global,
			::gpu::shader::e_descriptor_set_slot_local }, {},
			simple_render_properties(),
			pgpucontext->input_layout<::graphics3d::Vertex>()

		);

		//m_pshader->m_bClearColor = true;
      //m_pshader->m_colorClear = argb(0.8f, 0.1f, 0.5f, 0.1f);

	}


	void object_render_system::on_update(::gpu::context* pgpucontext, ::graphics3d::scene* pscene)
	{


	}


	void object_render_system::on_render(::gpu::context * pgpucontext, ::graphics3d::scene* pscene)
	{

		m_pshader->bind(pgpucontext->current_target_texture(::gpu::current_frame()));

	   auto pgamelayer = m_pengine->m_pgamelayer;

		for (auto& kv : pscene->scene_objects())
		{

			auto& obj = kv.element2();

			//SimplePushConstantData push{};
			//push.modelMatrix = obj->m_transform.mat4();
			//push.normalMatrix = obj->m_transform.normalMatrix();

			//vkCmdPushConstants(
			//	frameInfo.commandBuffer,
			//	pipelineLayout,
			//	VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
			//	0,
			//	sizeof(SimplePushConstantData),
			//	&push);

		   auto prenderable = obj->renderable();

			if (prenderable)
			{

				//auto pszPath = obj->m_strPath.c_str();

				auto modelMatrix = m_pengine->model_matrix(obj->m_transform);

				m_pshader->m_propertiesPush["modelMatrix"] = modelMatrix;

				auto normalMatrix = m_pengine->normal_matrix(obj->m_transform);

				m_pshader->m_propertiesPush["normalMatrix"] = normalMatrix;

				m_pshader->push_properties();

				auto pcommandbuffer = pgpucontext->m_pgpurenderer->getCurrentCommandBuffer2(::gpu::current_frame());

				prenderable->bind(pcommandbuffer);

				prenderable->draw(pcommandbuffer);

				prenderable->unbind(pcommandbuffer);

			}

		}

		m_pshader->unbind();

	}

} // namespace graphics3d
