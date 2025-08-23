#include "framework.h"
//#include "pipeline.h"
#include "skybox_ibl_render_system.h"
#include "bred/gpu/device.h"
#include "bred/gpu/frame.h"
#include "bred/gpu/shader.h"
#include "bred/graphics3d/model.h"
#include "bred/graphics3d/game_object.h"
#include "bred/graphics3d/engine.h"
#include "bred/graphics3d/frame.h"
#include "bred/graphics3d/scene.h"
#include "bred/graphics3d/shape_factory.h"
#include "bred/graphics3d/skybox.h"


namespace graphics3d
{
	//skybox_ibl_render_system::skybox_ibl_render_system(::graphics3d::device * pdevice, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout)
	//	: m_pgpudevice{ pdevice }, m_pipelineLayout{ VK_NULL_HANDLE }, m_skyboxDescriptorSet(VK_NULL_HANDLE), m_bHasCubemap(false)
//	{
//	}

	skybox_ibl_render_system::skybox_ibl_render_system()
	{
	}


	skybox_ibl_render_system::~skybox_ibl_render_system()
	{
		// destroy the pipeline layout you created
		//vkDestroyPipelineLayout(m_pgpudevice->device(), m_pipelineLayout, nullptr);
		// (the pipeline unique_ptr will destroy the VkPipeline)
	}
	//
	//
	// void skybox_ibl_render_system::init(
	// 	graphics3d::device * pdevice,
	// 	VkRenderPass renderPass,
	// 	VkDescriptorSetLayout globalSetLayout,
	// 	graphics3d::sandbox_descriptor_pool& descriptorPool,
	// 	size_t frameCount)
	// {
	// 	ASSERT(pdevice == m_pgpudevice);
	// 	m_descriptorPool = &descriptorPool;
	//
	// 	createSkyboxDescriptorSetLayout();
	//
	// 	if (m_bHasCubemap) {
	// 		allocateAndWriteSkyboxDescriptorSet();
	// 	}
	//
	// 	createPipelineLayout(globalSetLayout);
	// 	createPipeline(renderPass);
	// }

	void skybox_ibl_render_system::createSkyboxDescriptorSetLayout() {
		// m_skyboxSetLayout = graphics3d::sandbox_descriptor_set_layout::Builder(m_pgpudevice)
		// 	.addBinding(
		// 		0,
		// 		VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
		// 		VK_SHADER_STAGE_FRAGMENT_BIT,
		// 		1,
		// 		0) // no binding flags needed here
		// 	.build();
	}


	void skybox_ibl_render_system::allocateAndWriteSkyboxDescriptorSet() {
		// ASSERT(m_descriptorPool && "Descriptor pool must be set before allocating descriptors");
		// ASSERT(m_skyboxSetLayout && "Descriptor set layout must be created before allocating");
		//
		// graphics3d::sandbox_descriptor_writer writer(*m_skyboxSetLayout, *m_descriptorPool);
		// writer.writeImage(0, &m_skyboxImageInfo);
		// bool success = writer.build(m_skyboxDescriptorSet);
		// ASSERT(success && "Failed to build skybox descriptor set");
	}

	// void skybox_ibl_render_system::createPipelineLayout(VkDescriptorSetLayout globalSetLayout) {
	//
	// 	VkDescriptorSetLayout skyboxLayoutHandle =
	// 		m_skyboxSetLayout->getDescriptorSetLayout();
	//
	// 	::preallocated_array_base< ::array_base <VkDescriptorSetLayout>, 2 > layouts;
	//
	// 	layouts = {
	// 		globalSetLayout,
	// 		skyboxLayoutHandle // from createSkyboxDescriptorSetLayout()
	// 	};
	//
	// 	VkPipelineLayoutCreateInfo layoutInfo{ VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO };
	// 	layoutInfo.setLayoutCount = (uint32_t)layouts.size();
	// 	layoutInfo.pSetLayouts = layouts.data();
	// 	layoutInfo.pushConstantRangeCount = 0;
	// 	layoutInfo.pPushConstantRanges = nullptr;
	//
	// 	if (vkCreatePipelineLayout(m_pgpudevice->device(), &layoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS) {
	// 		throw std::runtime_error("Failed to create skybox pipeline layout");
	// 	}
	// }

   void skybox_ibl_render_system::on_prepare(gpu::context *pgpucontext)
   {

	   // Initialize skybox shader
	   ødefer_construct(m_pshader);

	   m_pshader->m_bDisableDepthTest = false;
	   m_pshader->m_bDepthTestButNoDepthWrite = true;
	   m_pshader->m_bLequalDepth = true;
	   m_pshader->m_bEnableBlend = true;
	   m_pshader->m_ecullmode = ::gpu::e_cull_mode_none;
	   m_pshader->m_bindingCubeSampler.set();

	   m_pshader->initialize_shader(pgpucontext->m_pgpurenderer,
         "matter://shaders/skybox.vert",
         "matter://shaders/skybox.frag",
         {::gpu::shader::e_descriptor_set_slot_global},
         nullptr,
         nullptr,
         pgpucontext->input_layout<::graphics3d::shape_factory::Vertex>()
      );



   }


 //   void skybox_ibl_render_system::on_bind(::gpu:)
	// {
 // // Make sure to bind the shader first
	// }
 //

   void skybox_ibl_render_system::on_render(::gpu::context* pgpucontext, ::graphics3d::scene* pscene)
	{

		if (!m_bHasCubemap) return;

	   auto pengine = m_pengine;

	   //auto pscene = pengine->current_scene();

		//if (!m_skyboxModel) return;
		auto pskyboxCurrent = pscene->current_sky_box();
		if (!pskyboxCurrent) {
			return; // nothing to draw
		}


	   auto pgpudevice = pgpucontext->m_pgpudevice;

	   auto pgpurenderer = pgpucontext->m_pgpurenderer;

	   auto iFrameSerial = pgpudevice->m_iFrameSerial2;

	   auto ptextureDst = pgpurenderer->current_render_target_texture(::gpu::current_frame());

	   m_pshader->m_bindingCubeSampler.m_strUniform = "skybox";

	   //auto pskybox = pscene->m_psceneobjectSkybox;

	   auto ptextureCubeMap = pskyboxCurrent->m_ptextureCubeMap;

	   m_pshader->bind(ptextureDst, ptextureCubeMap);
		//IGameObject * skyObj = skyOpt->get();

		//sASSERT(m_skyboxDescriptorSet != VK_NULL_HANDLE && "Skybox descriptor set is not allocated!");

		//m_pshader->bind(pframe->getCommandBuffer());
		//m_pshader->bind();
		// Bind two descriptor sets: 0=global UBO, 1=skybox cubemap
//		::preallocated_array_base< ::array_base <VkDescriptorSet>, 2 > sets;

		// sets= {
		// 	frameInfo.globalDescriptorSet,
		// 	m_skyboxDescriptorSet
		// };
		// vkCmdBindDescriptorSets(
		// 	frameInfo.m_pcommandbuffer,
		// 	VK_PIPELINE_BIND_POINT_GRAPHICS,
		// 	m_pipelineLayout,
		// 	0, // firstSet = 0 (binds set 0 and 1 in this call)
		// 	static_cast<uint32_t>(sets.size()),
		// 	sets.data(),
		// 	0,
		// 	nullptr
		// );

      auto pframe = ::gpu::current_frame();

		auto prenderable = pskyboxCurrent->renderable();

	   if (prenderable)
		{

			prenderable->bind(pframe->m_pgpucommandbuffer);

			prenderable->draw(pframe->m_pgpucommandbuffer);

		}


	}


	// void skybox_ibl_render_system::createPipeline(VkRenderPass renderPass) {
	// 	ASSERT(m_pipelineLayout != VK_NULL_HANDLE && "Pipeline layout must be created before pipeline");
	//
	// 	// graphics3d::pipeline_configuration_information config{};
	// 	// graphics3d::pipeline::default_pipeline_configuration(config);
	// 	//
	// 	// ::array_base<VkVertexInputBindingDescription>   bindings = {
	// 	// 	vkinit::vertexInputBindingDescription(
	// 	// 		0,
	// 	// 		sizeof(graphics3d::gltf::Vertex),
	// 	// 		VK_VERTEX_INPUT_RATE_VERTEX)
	// 	// };
	// 	// ::array_base<VkVertexInputAttributeDescription> attributes = {
	// 	// 	vkinit::vertexInputAttributeDescription(
	// 	// 		/*binding=*/0,
	// 	// 		/*location=*/0,
	// 	// 		/*format=*/VK_FORMAT_R32G32B32_SFLOAT,
	// 	// 		/*offset=*/offsetof(graphics3d::gltf::Vertex, pos))
	// 	// };
	// 	//
	// 	// config.bindingDescriptions = bindings;
	// 	// config.attributeDescriptions = attributes;
	// 	// config.renderPass = renderPass;
	// 	// config.pipelineLayout = m_pipelineLayout;
	// 	// config.depthStencilInfo.depthTestEnable = VK_TRUE;
	// 	// config.depthStencilInfo.depthWriteEnable = VK_FALSE;
	// 	// config.depthStencilInfo.depthWriteEnable = VK_COMPARE_OP_LESS_OR_EQUAL;
	//
	//
	// 	::string vertPath = "matter://shaders/spirV/skybox_ibl.vert.spv";
	// 	::string fragPath = "matter://shaders/spirV/skybox_ibl.frag.spv";
	//
	// 	m_ppipeline = øcreate_pointer<graphics3d::pipeline>(
	// 		m_pgpudevice,
	// 		vertPath.c_str(),
	// 		fragPath.c_str()
	// 		//,		config
	// 	);
	// }
} // namespace graphics3d
