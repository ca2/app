#pragma once
// #include "bred/graphics3d/render_system.h"
//
// //#include "SceneFoundry/sandbox_renderer/device.h"
// //#include "SceneFoundry/sandbox_renderer/pipeline.h"
//
// //#include <vulkan/vulkan.h>
//
// // STD
// //#include <memory>
// //#include <vector>
// #define GLM_ENABLE_EXPERIMENTAL
// #include <glm/glm.hpp>

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


      //::pointer<::sandbox_renderer::device> m_pgpudevice;

      //VkDescriptorSetLayout m_globalSetLayout;
      //::pointer<::gpu::shader> m_pshader;
      //::pointer<sandbox_renderer::pipeline> m_ppipeline;
      //VkPipelineLayout m_pipelineLayout;

      float m_rotationSpeed = 0.2f;
      // point_light_render_system(const point_light_render_system&) = delete;
      // point_light_render_system& operator=(const point_light_render_system&) = delete;

      //point_light_render_system(sandbox_renderer::device * pdevice, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);
      point_light_render_system();


      ~point_light_render_system();


      // void init(
      // 	::sandbox_renderer::device * pdevice,
      // 	VkRenderPass            renderPass,
      // 	VkDescriptorSetLayout   globalSetLayout,
      // 	sandbox_renderer::sandbox_descriptor_pool& descriptorPool,
      // 	size_t frameCount)override;

      void on_prepare() override;


      void on_update(::graphics3d::IFrame *pframe) override;


      void on_render(::graphics3d::IFrame *pframe) override;


      //private:
      //void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
      //void createPipeline(VkRenderPass renderPass);


   };


} // namespace graphics3d
