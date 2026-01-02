// Created by camilo on 2025-05-23 <3ThomasBorregaardSorensen!!
#pragma once



#include "bred/gpu/properties.h"



namespace graphics3d
{


   class CLASS_DECL_BRED scene_system :
      virtual public ::particle
   {
   public:


      ::pointer < ::graphics3d::engine >     m_pengine;

      ::pointer < ::gpu::shader >            m_pshader;


      scene_system();
      ~scene_system();


      void initialize_scene_system(::graphics3d::engine* pengine);


      virtual void update(::gpu::context* pgpucontext, ::graphics3d::scene* pscene);
      virtual void render(::gpu::context* pgpucontext, ::graphics3d::scene* pscene);

      virtual void on_update(::gpu::context* pgpucontext, ::graphics3d::scene* pscene);
      virtual void on_render(::gpu::context* pgpucontext, ::graphics3d::scene* pscene);

      //void createPipelineLayout(aaaVkDescriptorSetLayout globalSetLayout);
      //void createPipeline(VkRenderPass renderPass);

      virtual void prepare(::gpu::context* pgpucontext);
      virtual void on_prepare(::gpu::context* pgpucontext);

      //VkPipelineLayout pipelineLayout;

   };


}  // namespace graphics3d



