// Created by camilo on 2025-05-23 <3ThomasBorregaardSorensen!!
#pragma once



#include "aura/graphics/gpu/properties.h"
#include <glm/glm.hpp>


namespace graphics3d
{


   class CLASS_DECL_AURA scene_system :
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


      //void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
      //void createPipeline(VkRenderPass renderPass);

      virtual void prepare(::gpu::context* pgpucontext);

      //VkPipelineLayout pipelineLayout;

   };


}  // namespace graphics3d



