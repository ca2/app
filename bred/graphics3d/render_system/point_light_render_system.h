#pragma once
// #include "bred/graphics3d/render_system.h"
//
// //#include "SceneFoundry/graphics3d/device.h"
// //#include "SceneFoundry/graphics3d/pipeline.h"
//
// //#include <vulkan/vulkan.h>
//
// // STD
// //#include <memory>
// //#include <vector>
// 
// 

#include "bred/graphics3d/render_system.h"


namespace graphics3d
{


   //
   // class point_light_scene_object :
   // virtual public sandbox_game::game_object
   // {
   // public:
   //
   // 	float m_fLightIntensity = 1.0f;
   //
   // };

   //struct point_light_component;

   class CLASS_DECL_BRED point_light_render_system :
      public ::graphics3d::render_system
   {
   public:


      //::pointer<::graphics3d::device> m_pgpudevice;

      //VkDescriptorSetLayout m_pdescriptorsetlayoutUbo;
      //::pointer<::gpu::shader> m_pshader;
      //::pointer<graphics3d::pipeline> m_ppipeline;
      //VkPipelineLayout m_pipelineLayout;
      ::pointer<::gpu::shader> m_pshader;
      ::pointer < ::gpu::model_buffer > m_pmodelDummy;

      float m_rotationSpeed = 0.2f;
      // point_light_render_system(const point_light_render_system&) = delete;
      // point_light_render_system& operator=(const point_light_render_system&) = delete;

      //point_light_render_system(graphics3d::device * pdevice, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);
      point_light_render_system();


      ~point_light_render_system();


      // void init(
      // 	::graphics3d::device * pdevice,
      // 	VkRenderPass            renderPass,
      // 	VkDescriptorSetLayout   globalSetLayout,
      // 	graphics3d::sandbox_descriptor_pool& descriptorPool,
      // 	size_t frameCount)override;
      //
      // void on_prepare() override;
      //
      //
      // void on_update(::gpu::frame *pframe) override;
      //
      //
      // void on_render(::gpu::frame *pframe) override;

      void initialize_render_system(::graphics3d::engine * pengine) override;

      void on_prepare(::gpu::context* pgpucontext) override;
      void on_update(::gpu::context* pgpucontext, ::graphics3d::scene_base * pscene) override;
      void on_render(::gpu::context* pgpucontext, ::graphics3d::scene_base * pscene) override;


      //private:
      //void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
      //void createPipeline(VkRenderPass renderPass);


   };


} // namespace graphics3d
