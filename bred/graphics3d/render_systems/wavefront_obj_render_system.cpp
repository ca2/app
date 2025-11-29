#include "framework.h"
#include "wavefront_obj_render_system.h"
#include "bred/graphics3d/engine.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/shader.h"
#include "bred/graphics3d/model.h"
#include "bred/graphics3d/scene_renderable.h"
#include "bred/graphics3d/frame.h"
#include "graphics3d/immersion_layer.h"
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


	void wavefront_obj_render_system::on_prepare(::gpu::context* pgpucontext)
	{

		auto prenderer = pgpucontext->m_pgpurenderer;

      m_pshader = øcreate<::gpu::shader>();
      m_pshader->m_propertiesPushShared.set_properties(simple_render_properties());
      pgpucontext->layout_push_constants(
         m_pshader->m_propertiesPushShared, false);
      m_pshader->initialize_shader(
         pgpucontext->m_pgpurenderer,
         "matter://shaders/wavefront.vert",
			"matter://shaders/wavefront.frag",
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
         ::gpu::current_command_buffer(), pgpucontext->current_target_texture(::gpu::current_frame()));

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

			if (prenderable && prenderable->m_erenderabletype ==
            ::gpu::e_renderable_type_wavefront_obj)
			{

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

		m_pshader->unbind(::gpu::current_command_buffer());

	}

} // namespace graphics3d
