// graphics3d/include/IRenderSystem.h
#pragma once

namespace graphics3d
{

  

   class CLASS_DECL_BRED render_system :
      virtual public ::particle
   {
   public:


      ::graphics3d::enum_render_system m_erendersystem;

      ::pointer<::graphics3d::engine> m_pengine;


      ::pointer<::gpu::shader> m_pshader;


      render_system();


      ~render_system() override;

      virtual void initialize_render_system(::graphics3d::engine* pengine);


      

      // virtual void on_prepare();
      //
      //
      // virtual void on_update();
      //
      //
      // virtual void on_render();


      virtual void prepare(::gpu::context* pgpucontext);
      virtual void on_prepare(::gpu::context* pgpucontext);


      virtual void update(::gpu::context* pgpucontext, ::graphics3d::scene_base* pscene);
      virtual void on_update(::gpu::context* pgpucontext, ::graphics3d::scene_base* pscene);

      //void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
      //void createPipeline(VkRenderPass renderPass);

      virtual void render(::gpu::context* pgpucontext, ::graphics3d::scene_base* pscene);
      virtual void on_render(::gpu::context* pgpucontext, ::graphics3d::scene_base* pscene);

      //VkPipelineLayout pipelineLayout;

   };


} // namespace graphics3d
