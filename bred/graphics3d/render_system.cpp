// create by camilo on 2025-08-21 18:38 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "engine.h"
#include "render_system.h"
#include "bred/graphics3d/scene_renderable.h"


namespace graphics3d
{
   render_system::render_system()
   {

      m_erendersystem = ::graphics3d::e_render_system_none;

   }


   render_system::~render_system()
   {
   }

   //
   // void render_system::on_prepare()
   // {
   // }
   //
   //
   // void render_system::on_update()
   // {
   //
   //
   // }
   //
   //
   // void render_system::on_render()
   // {
   //
   //
   // }



   void render_system::initialize_render_system(::graphics3d::engine* pengine)
   {

      m_pengine = pengine;

   }


   ::graphics3d::scene_renderable * render_system::current_scene_renderable()
   {

      return nullptr;

   }


   void render_system::update(::gpu::context* pgpucontext, ::graphics3d::scene_base* pscene)
   {

      on_update(pgpucontext, pscene);

   }


   void render_system::on_update(::gpu::context* pgpucontext, ::graphics3d::scene_base* pscene)
   {


   }


   void render_system::render(::gpu::context* pgpucontext, ::graphics3d::scene_base* pscene)
   {

      //testall pgpucontext->current_target_texture()->bind_render_target();

      if (!m_bPrepared)
      {

         return;

      }

      on_render(pgpucontext, pscene);

   }


   void render_system::on_render(::gpu::context* pgpucontext, ::graphics3d::scene_base* pscene)
   {


   }


   //void createPipelineLayout(aaaVkDescriptorSetLayout globalSetLayout);
   //void createPipeline(VkRenderPass renderPass);

   void render_system::prepare(::gpu::context* pgpucontext)
   {

      on_prepare(pgpucontext);

      m_bPrepared = true;

   }


   void render_system::on_prepare(::gpu::context* pgpucontext)
   {

   }

   //VkPipelineLayout pipelineLayout;

   //};

   CLASS_DECL_BRED enum_render_system as_render_system(const ::scoped_string & scopedstr)
   {

      if (scopedstr.case_insensitive_equals("scene"))
      {

         return e_render_system_gltf_scene;

      }
      else if (scopedstr.case_insensitive_equals("gltf"))
      {

         return e_render_system_gltf_ibl;
      }
      else if (scopedstr.case_insensitive_begins("wavefront"))
      {

         return e_render_system_wavefront_obj;
      }
      else if (scopedstr.case_insensitive_equals("skybox_ibl"))
      {

         return e_render_system_skybox_ibl;
      }
      else if (scopedstr.case_insensitive_equals("skybox"))
      {

         return e_render_system_skybox;
      }
      else
      {

         return e_render_system_none;

      }


   }


}// namespace graphics3d



