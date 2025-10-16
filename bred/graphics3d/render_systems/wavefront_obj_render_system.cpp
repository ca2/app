#include "framework.h"
// obj_render_system.cpp
#include "wavefront_obj_render_system.h"
//#include "pipeline.h"
#include "bred/graphics3d/engine.h"
//#include "port/graphics/freetype/include/freetype/internal/fttrace.h"
#include "bred/gpu/shader.h"
#include "bred/graphics3d/model.h"
#include "bred/graphics3d/scene_renderable.h"
#include "bred/graphics3d/frame.h"
#include "graphics3d/immersion_layer.h"
#include "graphics3d/scene_base.h"
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

	// wavefront_obj_render_system::wavefront_obj_render_system(graphics3d::device *pdevice, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout)
	// 	: m_pgpudevice(pdevice)//, m_pdescriptorsetlayoutUbo(globalSetLayout)
	// {
	//
	// }
	wavefront_obj_render_system::wavefront_obj_render_system()
//		: m_pgpudevice(pdevice)//, m_pdescriptorsetlayoutUbo(globalSetLayout)
	{

	}

	// void wavefront_obj_render_system::init(
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

	wavefront_obj_render_system::~wavefront_obj_render_system()
	{
		//vkDestroyPipelineLayout(m_pgpudevice->device(), m_pipelineLayout, nullptr);
	}


	// void wavefront_obj_render_system::on_render()
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

	// void wavefront_obj_render_system::createPipelineLayout(VkDescriptorSetLayout globalSetLayout) {
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

	// void wavefront_obj_render_system::createPipeline(VkRenderPass renderPass)
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



	void wavefront_obj_render_system::initialize_render_system(::graphics3d::engine* pengine)
	{

		::graphics3d::render_system::initialize_render_system(pengine);

	}


	void wavefront_obj_render_system::on_prepare(::gpu::context* pgpucontext)
	{

		auto prenderer = pgpucontext->m_pgpurenderer;

      m_pshader = øcreate<::gpu::shader>();
      m_pshader->m_propertiesPushShared.set_properties(simple_render_properties());
      pgpucontext->layout_push_constants(
         m_pshader->m_propertiesPushShared);
      m_pshader->initialize_shader(
         pgpucontext->m_pgpurenderer, "matter://shaders/vert.vert",
			"matter://shaders/frag.frag",
			{ ::gpu::shader::e_descriptor_set_slot_global,
			::gpu::shader::e_descriptor_set_slot_local }, {},
			pgpucontext->input_layout<::graphics3d::Vertex>()

		);

		//m_pshader->m_bClearColor = true;
      //m_pshader->m_colorClear = argb(0.8f, 0.1f, 0.5f, 0.1f);

	}


	void wavefront_obj_render_system::on_update(::gpu::context* pgpucontext, ::graphics3d::scene_base* pscene)
	{


	}


	void wavefront_obj_render_system::on_render(::gpu::context * pgpucontext, ::graphics3d::scene_base* pscene)
	{


		m_pshader->bind(
         ::gpu::current_frame()->m_pgpucommandbuffer, pgpucontext->current_target_texture(::gpu::current_frame()));

	   auto pgamelayer = m_pengine->m_pimmersionlayer;

		for (auto &[strName, pscenerenderable]: pscene->scene_renderables())
		{

         if (!pscenerenderable)
         {

            continue;

         }

         if (pscenerenderable->m_erendersystem != ::graphics3d::e_render_system_wavefront_obj)
         {

            continue;
         }

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

		   auto prenderable = pscenerenderable->renderable();

			if (prenderable && prenderable->m_erenderabletype ==
            ::gpu::e_renderable_type_wavefront_obj)
			{

				//auto pszPath = obj->m_strPath.c_str();

				auto modelMatrix = m_pengine->model_matrix(pscenerenderable->m_transform);

				m_pshader->m_propertiesPushShared["modelMatrix"] = modelMatrix;

				auto normalMatrix = m_pengine->normal_matrix(pscenerenderable->m_transform);

				m_pshader->m_propertiesPushShared["normalMatrix"] = normalMatrix;

				auto pcommandbuffer = pgpucontext->m_pgpurenderer->getCurrentCommandBuffer2(::gpu::current_frame());

				m_pshader->push_properties(pcommandbuffer);

            prenderable->bind(pcommandbuffer);

				prenderable->draw(pcommandbuffer);

				prenderable->unbind(pcommandbuffer);

			}

		}

		m_pshader->unbind(::gpu::current_frame()->m_pgpucommandbuffer);

	}

} // namespace graphics3d
