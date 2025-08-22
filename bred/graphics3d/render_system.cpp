// create by camilo on 2025-08-21 18:38 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "engine.h"
#include "render_system.h"


namespace graphics3d
{
   render_system::render_system()
   {

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


   void render_system::update(::gpu::context* pgpucontext, ::graphics3d::scene* pscene)
   {

      on_update(pgpucontext, pscene);

   }


   void render_system::on_update(::gpu::context* pgpucontext, ::graphics3d::scene* pscene)
   {


   }


   void render_system::render(::gpu::context* pgpucontext, ::graphics3d::scene* pscene)
   {

      //testall pgpucontext->current_target_texture()->bind_render_target();

      on_render(pgpucontext, pscene);

   }


   void render_system::on_render(::gpu::context* pgpucontext, ::graphics3d::scene* pscene)
   {


   }


   //void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
   //void createPipeline(VkRenderPass renderPass);

   void render_system::prepare(::gpu::context* pgpucontext)
   {

      on_prepare(pgpucontext);

   }


   void render_system::on_prepare(::gpu::context* pgpucontext)
   {

   }

   //VkPipelineLayout pipelineLayout;

   //};




}// namespace graphics3d



