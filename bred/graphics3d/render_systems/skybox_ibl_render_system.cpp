#include "framework.h"
//#include "pipeline.h"
#include "skybox_ibl_render_system.h"
#include "bred/gltf/vertex.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/device.h"
#include "bred/gpu/frame.h"
#include "bred/gpu/shader.h"
#include "bred/gpu/texture.h"
#include "bred/graphics3d/model.h"
#include "bred/graphics3d/game_object.h"
#include "bred/graphics3d/engine.h"
#include "bred/graphics3d/frame.h"
#include "bred/graphics3d/scene_base.h"
#include "bred/graphics3d/shape_factory.h"
#include "bred/graphics3d/skybox.h"
#include "bred/graphics3d/skybox.h"

//
//   namespace gltf
//{
//   /*
//      gltf default vertex layout with easy Vulkan mapping functions
//   */
//   enum class CubeVertexComponent
//   {
//      Position,
//      Normal,
//      UV,
//      Color,
//      //Joint0,
//      //Weight0,
//      Tangent,
//   };
//
//   struct CubeVertex
//   {
//      floating_sequence3 pos;
//      floating_sequence3 normal;
//      floating_sequence2 uv;
//      floating_sequence4 color;
//      //floating_sequence4 joint0;
//      //floating_sequence4 weight0;
//      floating_sequence4 tangent;
//    
//   };
//
//} // namespace gltf

//BEGIN_GPU_PROPERTIES(::gltf::CubeVertex)
//GPU_PROPERTY("position", ::gpu::e_type_seq3)
//GPU_PROPERTY("normal", ::gpu::e_type_seq3)
//GPU_PROPERTY("uv", ::gpu::e_type_seq2)
//GPU_PROPERTY("color", ::gpu::e_type_seq4)
////GPU_PROPERTY("joint0", ::gpu::e_type_seq4)
////GPU_PROPERTY("weight0", ::gpu::e_type_seq4)
//GPU_PROPERTY("tangent", ::gpu::e_type_seq4)
//END_GPU_PROPERTIES()

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

      auto ppropertiesPush = ::gpu_properties<push_constants>();

	   // Initialize skybox shader
	   ødefer_construct(m_pshader);

	   m_pshader->m_bDisableDepthTest = false;
	   m_pshader->m_bDepthTestButNoDepthWrite = true;
	   m_pshader->m_bLequalDepth = true;
	   m_pshader->m_bEnableBlend = true;
      //m_pshader->m_bDisableDepthTest = true;
	   m_pshader->m_ecullmode = ::gpu::e_cull_mode_none;
      m_pshader->m_bindingCubeSampler.m_strUniform = "skybox";
      //m_pshader->m_bindingCubeSampler.m_uSet = 1;

	   m_pshader->m_bindingCubeSampler.set();
      m_pshader->m_propertiesPushShared.set_properties(ppropertiesPush);
      pgpucontext->layout_push_constants(m_pshader->m_propertiesPushShared, false);
      auto iSize = sizeof(::gpu::gltf::vertex);

      //if (false)
      if(m_bHdr)
      {

         m_pshader->initialize_shader(pgpucontext->m_pgpurenderer, "matter://shaders/skybox_ibl.vert",
                                      "matter://shaders/skybox_ibl_hdr.frag", {::gpu::shader::e_descriptor_set_slot_global}, nullptr, pgpucontext->input_layout<::gpu::gltf::vertex>());
      }
      else
      {

         m_pshader->initialize_shader(pgpucontext->m_pgpurenderer, "matter://shaders/skybox_ibl.vert",
                                      "matter://shaders/skybox_ibl.frag", {::gpu::shader::e_descriptor_set_slot_global},
                                      nullptr, pgpucontext->input_layout<::gpu::gltf::vertex>());

      }



   }


 //   void skybox_ibl_render_system::on_bind(::gpu:)
	// {
 // // Make sure to bind the shader first
	// }
 //

   void skybox_ibl_render_system::on_render(::gpu::context* pgpucontext, ::graphics3d::scene_base* pscene)
	{


		//if (!m_bHasCubemap) return;

	   auto pengine = m_pengine;

	   //auto pscene = pengine->current_scene();

		//if (!m_skyboxModel) return;

      auto pskybox = pscene->current_skybox();

      if (::is_null(pskybox))
      {

         return; // nothing to draw

      }

      auto prenderableSkyboxModel = pskybox->m_prenderable;

      if (!prenderableSkyboxModel)
      {

			throw ::exception(error_wrong_state);

		}

		auto ptextureSkybox = pskybox->m_ptexture;

      if (!ptextureSkybox)
      {

         throw ::exception(error_wrong_state);

      }

	   auto pgpudevice = pgpucontext->m_pgpudevice;

	   auto pgpurenderer = pgpucontext->m_pgpurenderer;

	   auto iFrameSerial = pgpudevice->m_iFrameSerial2;

	   auto ptextureDst = pgpurenderer->current_render_target_texture(::gpu::current_frame());

      pgpucontext->start_debug_happening(::gpu::current_command_buffer()
                                         , "skybox_ibl_render_system on_render");

	   //auto pskybox = pscene->m_psceneobjectSkybox;

      //auto ptextureCubeMap = prenderableSkyboxModel->get_target_texture();
      //auto ptextureCubeMap = pscene->current_sky_box_texture();

	   m_pshader->bind(::gpu::current_command_buffer(), ptextureDst, ptextureSkybox);
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

		//auto prenderable = pskyboxCurrent->renderable();
      auto prenderable = prenderableSkyboxModel;

	   if (prenderable)
		{

         m_erendersystem = ::graphics3d::e_render_system_skybox_ibl;

         pframe->m_pgpucommandbuffer->m_prendersystem = this;

			prenderable->bind(pframe->m_pgpucommandbuffer);

         float x_multiplier = 1.f;
         float y_multiplier = 1.f;
         float z_multiplier = 1.f;

         if (prenderable->m_ecoordinatesystem == ::gpu::e_coordinate_system_vulkan)
         {

            if (pgpucontext->m_eapi == ::gpu::e_api_opengl)
            {

               y_multiplier = -1.f;
               z_multiplier = -1.f;

            }
            else if (pgpucontext->m_eapi == ::gpu::e_api_vulkan)
            {

               y_multiplier = -1.f;
               z_multiplier = -1.f;

            }

         }
         else if (prenderable->m_ecoordinatesystem == ::gpu::e_coordinate_system_y_up)
         {

            if (pgpucontext->m_eapi == ::gpu::e_api_opengl)
            {

               y_multiplier = -1.f;
               z_multiplier = -1.f;

            }
            else if (pgpucontext->m_eapi == ::gpu::e_api_vulkan)
            {

               //y_multiplier = -1.f;
               //z_multiplier = -1.f;

            }

         }

         //m_pshader->set_float("y_multiplier", y_multiplier);
         //m_pshader->set_float("z_multiplier", z_multiplier);

         floating_sequence3 sequence3Multiplier;

         sequence3Multiplier.x = x_multiplier;
         sequence3Multiplier.y = y_multiplier;
         sequence3Multiplier.z = z_multiplier;

         m_pshader->set_sequence3("multiplier", sequence3Multiplier);

         m_pshader->push_properties(pframe->m_pgpucommandbuffer);

         //int_rectangle r(pgpucontext->m_rectangle.size());

         //pframe->m_pgpucommandbuffer->set_viewport(r);

         //pframe->m_pgpucommandbuffer->set_scissor(r);

         prenderable->draw(pframe->m_pgpucommandbuffer);

         prenderable->unbind(pframe->m_pgpucommandbuffer);

		}

      pgpucontext->end_debug_happening(::gpu::current_command_buffer());


	}


   void skybox_ibl_render_system::setCubemapTexture(::gpu::texture *pgputexture)
   {

      m_pgputextureSkybox = pgputexture;

      m_bHasCubemap = ::is_set(m_pgputextureSkybox);

   }

          //}
   //     m_skyboxImageInfo = info;
   //     m_bHasCubemap = true;
   //     allocateAndWriteSkyboxDescriptorSet();
   // }


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




BEGIN_GPU_PROPERTIES(::graphics3d::skybox_ibl_render_system::push_constants)
GPU_PROPERTY("multiplier", ::gpu::e_type_seq3)
END_GPU_PROPERTIES()
