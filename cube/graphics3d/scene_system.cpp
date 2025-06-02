// Created by camilo on 2025-05-23 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "application.h"
#include "engine.h"
#include "scene_system.h"


namespace graphics3d
{


   scene_system::scene_system()
   {

   }


   scene_system::~scene_system()
   {

   }


   void scene_system::initialize_scene_system(::graphics3d::engine* pengine)
   {

      m_pengine = pengine;

   }

   
   void scene_system::update(::gpu::context* pgpucontext, ::graphics3d::scene* pscene)
   {


   }


   void scene_system::render(::gpu::context* pgpucontext, ::graphics3d::scene* pscene)
   {


   }


      //void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
      //void createPipeline(VkRenderPass renderPass);

   void scene_system::prepare(::gpu::context* pgpucontext)
   {

   }

      //VkPipelineLayout pipelineLayout;

   //};


}  // namespace graphics3d



