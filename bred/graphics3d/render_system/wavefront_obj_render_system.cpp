#include "framework.h"
#include "wavefront_obj_render_system.h"
#include "bred/graphics3d/engine.h"
#include "bred/gpu/binding.h"
#include "bred/gpu/block.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/context.h"
#include "bred/gpu/device.h"
#include "bred/gpu/frame.h"
#include "bred/gpu/renderer.h"
#include "bred/gpu/shader.h"
#include "bred/graphics3d/scene_renderable.h"
#include "graphics3d/scene_base.h"


namespace graphics3d
{


   wavefront_obj_render_system::wavefront_obj_render_system()
	{


	}


	wavefront_obj_render_system::~wavefront_obj_render_system()
	{

   
   }


	void wavefront_obj_render_system::initialize_render_system(::graphics3d::engine* pengine)
	{

		::graphics3d::render_system::initialize_render_system(pengine);

	}

   ::memory wavefront_obj_render_system::vert_shader_memory() 
   {
      
      ::memory memory;

      m_pengine->gpu_context()->m_pgpudevice->defer_shader_memory(
         memory, "matter://shaders/wavefront.vert");

      return memory;

   }

   ::memory wavefront_obj_render_system::frag_shader_memory()
   {

      ::memory memory;

      m_pengine->gpu_context()->m_pgpudevice->defer_shader_memory(
         memory, "matter://shaders/wavefront.frag");

      return memory;

   }


	void wavefront_obj_render_system::on_prepare(::gpu::context* pgpucontext)
	{

		auto prenderer = pgpucontext->m_pgpurenderer;

      m_pshader = øcreate<::gpu::shader>();
      m_pshader->m_propertiesPushShared.set_properties(simple_render_properties());
      pgpucontext->layout_push_constants(
         m_pshader->m_propertiesPushShared, false);

      m_pshader->set_global_ubo();
      //auto &bindingUbo = m_pshader->binding();
      //bindingUbo.m_strUniform = "ubo";
      //bindingUbo.m_ebinding = ::gpu::e_binding_global_ubo;

      m_pshader->initialize_shader_with_block(
         pgpucontext->m_pgpurenderer,
         this->vert_shader_memory(), 
         this->frag_shader_memory(),
			//{
			//::gpu::shader::e_descriptor_set_slot_local }, {},
			pgpucontext->input_layout<::graphics3d::Vertex>()

		);

		//m_pshader->m_bClearColor = true;
      //m_pshader->m_colorClear = argb(0.8f, 0.1f, 0.5f, 0.1f);

	}


	void wavefront_obj_render_system::on_update(::gpu::context* pgpucontext, ::graphics3d::scene_base* pscene)
	{


	}


   ::floating_matrix4 wavefront_obj_render_system::model_matrix2(::graphics3d::scene_renderable *pscenerenderable)
   {

      floating_matrix4 matrixModel;

      floating_matrix4 matrixNormal;

      model_and_normal_matrices(matrixModel, matrixNormal, pscenerenderable);

      return matrixModel;

   }



   void wavefront_obj_render_system::model_and_normal_matrices(::floating_matrix4 & matrixModel,
                                                               ::floating_matrix4 & matrixNormal,
                                    ::graphics3d::scene_renderable * pscenerenderable)
   {

      matrixModel = model_matrix2(pscenerenderable);

      matrixNormal = floating_matrix3(matrixModel).inversed().transposed();

   }


	void wavefront_obj_render_system::on_render(::gpu::context * pgpucontext, ::graphics3d::scene_base* pscene)
	{

      auto pgpucommandbuffer = ::gpu::current_command_buffer();

      pgpucommandbuffer->set_shader(m_pshader);

            auto pblockGlobalUbo1 = pscene->global_ubo1(pgpucontext);

      // auto pbindingsetGlobalUbo =

      // pgpucommandbuffer->set_block(pblockGlobalUbo);

      auto pbindingslotsetGlobalUbo1 =
         pblockGlobalUbo1->binding_slot_set(pgpucommandbuffer, pgpucontext->global_ubo1_binding_set());

      pgpucommandbuffer->bind_slot_set(0, pbindingslotsetGlobalUbo1);

		//m_pshader->bind(
  //       ::gpu::current_command_buffer(), pgpucontext->current_target_texture(::gpu::current_frame()));

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

		   auto prenderable = pscenerenderable->renderable();

			if (prenderable && prenderable->m_egpumodel ==
            ::gpu::e_model_wavefront)
			{

            //auto T = ::floating_matrix4::translation(pscenerenderable->m_sequence3Translation);

            //auto R = pscenerenderable->m_matrixRotation;

            //auto S = ::floating_matrix4::scaling(pscenerenderable->m_sequence3Scaling);

            ::floating_matrix4 matrixModel;

            ::floating_matrix4 matrixNormal;

				model_and_normal_matrices(matrixModel, matrixNormal, pscenerenderable);

				m_pshader->m_propertiesPushShared["modelMatrix"] = matrixModel;

				//auto normalMatrix = m_pengine->normal_matrix(pscenerenderable->m_transform);

            //floating_matrix4 normalMatrix = floating_matrix3(modelMatrix).inversed().transposed();

				m_pshader->m_propertiesPushShared["normalMatrix"] = matrixNormal;

				///auto pcommandbuffer = pgpucontext->m_pgpurenderer->getCurrentCommandBuffer2(::gpu::current_frame());

				m_pshader->push_properties(pgpucommandbuffer);

            //prenderable->bind(pcommandbuffer);

            on_before_draw_renderable(pgpucontext, pscene, pscenerenderable);

            pgpucommandbuffer->draw(prenderable);

				prenderable->unbind(pgpucommandbuffer);

			}

		}

		//m_pshader->unbind(::gpu::current_command_buffer());

	}


   void wavefront_obj_render_system::on_before_draw_renderable(::gpu::context * pgpucontext,
                                                               ::graphics3d::scene_base * pscene,
                                    ::graphics3d::scene_renderable * pscenerenderable)
   {

   }


} // namespace graphics3d
