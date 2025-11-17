#include "framework.h"
//#include "bred/graphics3d/context.h"
#include "bred/graphics3d/scene.h"
#include "bred/gpu/shader.h"
#include "bred/user/user/graphics3d.h"
#include "simple_render_system.h"
// libs
	





#include <string>
#include <array>
#include <cassert>
#include <stdexcept>


namespace graphics3d 
{
	//struct SimplePushConstantData {
	//	floating_matrix4 modelMatrix{ 1.f };
	//	floating_matrix4 normalMatrix{ 1.f };
	//};

	///::graphics3d::property * simple_

	//simple_render_system::simple_render_system(context * pdevice, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout)
	simple_render_system::simple_render_system()
	{

	}
		

	void simple_render_system::initialize_simple_render_system(::graphics3d::context * pcontext)
	{
		
		m_pcontext = pcontext;

		m_pshader = m_pcontext->m_pimpact->m_pengine->create_shader(
			pcontext,
			"matter://Shaders/vert.vert",
			"matter://Shaders/frag.frag",
			simple_render_properties()
			);

		//std::string vertShaderPath = 
		//std::string fragShaderPath = "matter://Shaders/SpirV/frag.frag.spv";


		//createPipelineLayout(globalSetLayout);
		//createPipeline(renderPass);

	}

	simple_render_system::~simple_render_system() {
		/*vkDestroyPipelineLayout(m_pcontext->logicalDevice(), pipelineLayout, nullptr);*/
	}



	//void simple_render_system::createPipelineLayout(VkDescriptorSetLayout globalSetLayout) {

	//	VkPushConstantRange pushConstantRange{};
	//	pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
	//	pushConstantRange.offset = 0;
	//	pushConstantRange.size = sizeof(SimplePushConstantData);

	//	std::vector<VkDescriptorSetLayout> descriptorSetLayouts{ globalSetLayout };

	//	VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
	//	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	//	pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
	//	pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
	//	pipelineLayoutInfo.pushConstantRangeCount = 1;
	//	pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
	//	if (vkCreatePipelineLayout(m_pcontext->logicalDevice(), &pipelineLayoutInfo, nullptr, &pipelineLayout) !=
	//		VK_SUCCESS) {
	//		throw std::runtime_error("Failed to create pipeline layout");
	//	}

	//}


	//void simple_render_system::createPipeline(VkRenderPass renderPass) 
	//{

	//	assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

	//	pipeline_configuration pipelineconfiguration{};
	//	pipeline::default_pipeline_configuration(pipelineconfiguration);

	//	pipelineconfiguration.renderPass = renderPass;
	//	pipelineconfiguration.pipelineLayout = pipelineLayout;

	//	// Construct paths using PROJECT_ROOT_DIR
	//	std::string vertShaderPath = "matter://Shaders/SpirV/vert.vert.spv";
	//	std::string fragShaderPath = "matter://Shaders/SpirV/frag.frag.spv";

	//	m_ppipeline = øallocate pipeline();
	//	
	//	m_ppipeline->initialize_pipeline(
	//		m_pcontext,
	//		vertShaderPath.c_str(),
	//		fragShaderPath.c_str(),
	//		pipelineconfiguration
	//	);
	//}


	void simple_render_system::renderGameObjects(::graphics3d::scene* pscene)
	{

		m_pshader->bind();

	////	vkCmdBindDescriptorSets(
	////		frameInfo.commandBuffer,
	////		VK_PIPELINE_BIND_POINT_GRAPHICS,
	////		pipelineLayout,
	////		0, 1,
	////		&frameInfo.globalDescriptorSet,
	////		0, nullptr
	////	);

		for (auto& kv : pscene->m_mapObjects) {
			auto& obj = kv.element2();
			//SimplePushConstantData push{};
			//push.modelMatrix = obj->m_transform.floating_matrix4();
			//push.normalMatrix = obj->m_transform.normalMatrix();

			m_pshader->setMat4("modelMatrix",obj->m_transform.floating_matrix4());
			m_pshader->setMat4("normalMatrix", obj->m_transform.normalMatrix());

			m_pshader->push_properties();
			//vkCmdPushConstants(
			//	frameInfo.commandBuffer,
			//	pipelineLayout,
			//	VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
			//	0,
			//	sizeof(SimplePushConstantData),
			//	&push);

			if (obj->m_pmodel)
			{
				obj->m_pmodel->bind(m_pcontext);
				obj->m_pmodel->draw(m_pcontext);
			}
		}
	}

} // namespace graphics3d 



