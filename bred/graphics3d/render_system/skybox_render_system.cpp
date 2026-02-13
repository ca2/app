#include "framework.h"
#include "skybox_render_system.h"
#include "bred/gltf/vertex.h"
#include "bred/gpu/binding.h"
#include "bred/gpu/block.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/device.h"
#include "bred/gpu/frame.h"
#include "bred/gpu/renderer.h"
#include "bred/gpu/render_target.h"
#include "bred/gpu/shader.h"
#include "bred/gpu/texture.h"
#include "bred/graphics3d/engine.h"
#include "bred/graphics3d/scene_base.h"
#include "bred/graphics3d/shape_factory.h"
#include "bred/graphics3d/skybox.h"



namespace graphics3d
{


	skybox_render_system::skybox_render_system()
	{
	}


	skybox_render_system::~skybox_render_system()
	{

   
   }

	void skybox_render_system::createSkyboxDescriptorSetLayout()
   {
		// m_skyboxSetLayout = graphics3d::sandbox_descriptor_set_layout::Builder(m_pgpudevice)
		// 	.addBinding(
		// 		0,
		// 		VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
		// 		VK_SHADER_STAGE_FRAGMENT_BIT,
		// 		1,
		// 		0) // no binding flags needed here
		// 	.build();
	}


   ::memory skybox_render_system::vertex_shader_memory()
   {

      ::memory memory;

      m_pengine->gpu_context()->m_pgpudevice->defer_shader_memory(memory, "matter://shaders/skybox_ibl.vert");

      return memory;

   }


   
   ::memory skybox_render_system::fragment_shader_memory()
   {

      ::memory memory;

      m_pengine->gpu_context()->m_pgpudevice->defer_shader_memory(memory, "matter://shaders/skybox_ibl.frag");

      return memory;

   }


   ::memory skybox_render_system::hdr_fragment_shader_memory()
   {

      ::memory memory;

      m_pengine->gpu_context()->m_pgpudevice->defer_shader_memory(memory, "matter://shaders/hdr_skybox_ibl.frag");

      return memory;

   }


   void skybox_render_system::on_prepare(gpu::context *pgpucontext)
   {

      //auto modeldataCube = m_pengine->shape_factory()->create_cube(pgpucontext, 32.0f);

      ::pointer<::graphics3d::renderable> pmodelCube;

      //if (pgpucontext->m_eapi == ::gpu::e_api_opengl)
      {

        pmodelCube = m_pengine->shape_factory()->create_cube_002(pgpucontext, 32.0f);

      }
      //else
      {

        // pmodelCube = m_pengine->shape_factory()->create_cube_001(pgpucontext, 32.0f);

      }

      // øconstruct(m_pmodelCube);

      /*auto pmodelCube = øcreate<::gpu::model_buffer>();

      pmodelCube->initialize_model(pgpucontext, modeldataCube);*/

      // m_pmodelCube = pmodelCube;

      m_prenderableCube = pmodelCube;

      m_prenderableCube->m_ecoordinatesystem = ::gpu::e_coordinate_system_opengl;

      auto ppropertiesPush = ::gpu_properties<push_constants>();

      {

             /*  auto ppropertiesPush = ::gpu_properties<push_constants>();*/


	   // Initialize skybox shader
	   ødefer_construct(m_pshaderHdr);

	   m_pshaderHdr->m_bDisableDepthTest = false;
      m_pshaderHdr->m_bDepthTestButNoDepthWrite = true;
      m_pshaderHdr->m_bLequalDepth = true;
      m_pshaderHdr->m_bEnableBlend = true;
      //m_pshader->m_bDisableDepthTest = true;
      m_pshaderHdr->m_ecullmode = ::gpu::e_cull_mode_none;

      //auto &bindingUbo = m_pshaderHdr->binding(0, 0);
      //bindingUbo.m_strUniform = "ubo";
      //bindingUbo.m_ebinding = ::gpu::e_binding_global_ubo;
      m_pshaderHdr->set_global_ubo();

      auto pbindingCubeSampler = m_pshaderHdr->binding(1, 0);
      pbindingCubeSampler->m_strUniform = "skybox";
      pbindingCubeSampler->m_ebinding = ::gpu::e_binding_cube_sampler;
      pbindingCubeSampler->m_iTextureUnit = 0;
         
      //m_pshader->m_bindingCubeSampler.m_uSet = 1;

	   //m_pshaderHdr->m_bindingCubeSampler.set();
      m_pshaderHdr->m_propertiesPushShared.set_properties(ppropertiesPush);
      pgpucontext->layout_push_constants(m_pshaderHdr->m_propertiesPushShared, false);
      auto iSize = sizeof(::gpu::gltf::vertex);

      //if (false)
      //if(m_bHdr)
      //{

         m_pshaderHdr->initialize_shader_with_block(
            pgpucontext->m_pgpurenderer, vertex_shader_memory(), hdr_fragment_shader_memory(), 
            //{}, nullptr, 
            pgpucontext->input_layout<::graphics3d::shape_factory::Vertex>());
      }
      //else
      {


            

         	   // Initialize skybox shader
         ødefer_construct(m_pshaderNormal);

         m_pshaderNormal->m_bDisableDepthTest = false;
         m_pshaderNormal->m_bDepthTestButNoDepthWrite = true;
         m_pshaderNormal->m_bLequalDepth = true;
         m_pshaderNormal->m_bEnableBlend = true;
         // m_pshader->m_bDisableDepthTest = true;
         m_pshaderNormal->m_ecullmode = ::gpu::e_cull_mode_none;

         //auto &bindingUbo = m_pshaderNormal->binding(0, 0);
         //bindingUbo.m_strUniform = "ubo";
         //bindingUbo.m_ebinding = ::gpu::e_binding_global_ubo;
         m_pshaderNormal->set_global_ubo();

         auto pbindingCubeSampler = m_pshaderNormal->binding(1, 0);
         pbindingCubeSampler->m_strUniform = "skybox";
         pbindingCubeSampler->m_ebinding = ::gpu::e_binding_cube_sampler;
         pbindingCubeSampler->m_iTextureUnit = 0;
         //m_pshaderNormal->m_bindingCubeSampler.m_strUniform = "skybox";
         // m_pshader->m_bindingCubeSampler.m_uSet = 1;

         //m_pshaderNormal->m_bindingCubeSampler.set();
         m_pshaderNormal->m_propertiesPushShared.set_properties(ppropertiesPush);
         pgpucontext->layout_push_constants(m_pshaderNormal->m_propertiesPushShared, false);
         auto iSize = sizeof(::graphics3d::shape_factory::Vertex);

         // if (false)
         // if(m_bHdr)
         //{


         m_pshaderNormal->initialize_shader_with_block(
            pgpucontext->m_pgpurenderer, vertex_shader_memory(), fragment_shader_memory(),
            //{}, nullptr,
            pgpucontext->input_layout<::graphics3d::shape_factory::Vertex>());

      }



   }


   void skybox_render_system::on_render(::gpu::context* pgpucontext, ::graphics3d::scene_base* pscene)
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

      //auto prenderableSkyboxModel = pskybox->m_prenderable;

      auto prenderableSkyboxModel = m_prenderableCube;

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

      auto prendertarget = pgpurenderer->render_target();

	   auto ptextureDst = prendertarget->current_texture(::gpu::current_frame());

      pgpucontext->start_debug_happening(::gpu::current_command_buffer(), "skybox_render_system on_render");

	   //auto pskybox = pscene->m_psceneobjectSkybox;
      //auto ptextureCubeMap = prenderableSkyboxModel->get_target_texture();
      //auto ptextureCubeMap = pscene->current_sky_box_texture();

      ::gpu::shader *pgpushader = nullptr;

      if (pskybox->m_ptexture->m_bHdr)
      {
         
         pgpushader = m_pshaderHdr;

      }
      else
      {
         
         pgpushader = m_pshaderNormal;

      }

      auto pgpucommandbuffer = ::gpu::current_command_buffer();

      pgpucommandbuffer->set_shader(pgpushader);

	   //pgpushader->bind(pgpucommandbuffer, ptextureDst);

      auto pblockGlobalUbo1 = pscene->global_ubo1(pgpucontext);

                             // auto pbindingsetGlobalUbo =

      //pgpucommandbuffer->set_block(pblockGlobalUbo);

      auto pbindingslotsetGlobalUbo1 =
         pblockGlobalUbo1->binding_slot_set(pgpucommandbuffer, pgpucontext->global_ubo1_binding_set());

      pgpucommandbuffer->bind_slot_set(0, pbindingslotsetGlobalUbo1);

      auto pbindingsetSkybox = pgpushader->binding_set(1);

      auto pbindingslotsetSkybox = ptextureSkybox->binding_slot_set(pgpucommandbuffer, pbindingsetSkybox);

      pgpucommandbuffer->bind_slot_set(1, pbindingslotsetSkybox);

      //pgpushader->bind_source(pgpucommandbuffer, ptextureSkybox);

      auto pframe = ::gpu::current_frame();

      auto prenderable = prenderableSkyboxModel;

	   if (prenderable)
		{

         m_erendersystem = ::graphics3d::e_render_system_skybox_ibl;

         pframe->m_pgpucommandbuffer->m_prendersystem = this;

			//prenderable->bind(pframe->m_pgpucommandbuffer);

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

               y_multiplier = -1.f;
               z_multiplier = -1.f;

            }

         }
         else if (prenderable->m_ecoordinatesystem == ::gpu::e_coordinate_system_opengl)
         {

            if (pgpucontext->m_eapi == ::gpu::e_api_opengl)
            {

               y_multiplier = -1.f;
               z_multiplier = -1.f;

            }
            else if (pgpucontext->m_eapi == ::gpu::e_api_vulkan)
            {
               y_multiplier = -1.f;
               //z_multiplier = -1.f;


               // vulkan pbr-renderer was working with this
               // 2-combo: vulkan continuum is also working with this
               //z_multiplier = -1.f;
            }
         }
         //m_pshader->set_float("y_multiplier", y_multiplier);
         //m_pshader->set_float("z_multiplier", z_multiplier);

         floating_sequence3 sequence3Multiplier;

         sequence3Multiplier.x = x_multiplier;
         sequence3Multiplier.y = y_multiplier;
         sequence3Multiplier.z = z_multiplier;

         pgpushader->set_sequence3("multiplier", sequence3Multiplier);

         pgpushader->push_properties(pframe->m_pgpucommandbuffer);

         //int_rectangle r(pgpucontext->m_rectangle.size());

         //pframe->m_pgpucommandbuffer->set_viewport(r);

         //pframe->m_pgpucommandbuffer->set_scissor(r);

         //pframe->m_pgpucommandbuffer->set_model(prenderable);
         //pgpushader->on_before_draw(pframe->m_pgpucommandbuffer);
         //pframe->m_pgpucommandbuffer->draw_model(prenderable);

         pframe->m_pgpucommandbuffer->draw(prenderable);

         //prenderable->unbind(pframe->m_pgpucommandbuffer);

		}

      pgpucontext->end_debug_happening(::gpu::current_command_buffer());


	}


   void skybox_render_system::setCubemapTexture(::gpu::texture *pgputexture)
   {

      m_pgputextureSkybox = pgputexture;

      m_bHasCubemap = ::is_set(m_pgputextureSkybox);

   }

          //}
   //     m_skyboxImageInfo = info;
   //     m_bHasCubemap = true;
   //     allocateAndWriteSkyboxDescriptorSet();
   // }


	// void skybox_render_system::createPipeline(VkRenderPass renderPass) {
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




BEGIN_GPU_PROPERTIES(::graphics3d::skybox_render_system::push_constants)
GPU_PROPERTY("multiplier", ::gpu::e_type_seq3)
END_GPU_PROPERTIES()
