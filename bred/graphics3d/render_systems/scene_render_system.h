#pragma once

#include "bred/graphics3d/render_system.h"

//#include "interfaces/asset_provider_i.h"
//#include "interfaces/game_object_i.h"
//#include "interfaces/model_i.h"
//#include "interfaces/render_system_i.h"
//
//#include "vulkan_wrapper/vulkan_descriptor.h"
//#include "vulkan_wrapper/vulkan_device.h"
//#include "vulkan_wrapper/vulkan_pipeline.h"
//
//#include "vulkan_wrapper/render_systems/gltf_render_system.h"
//#include "vulkan_wrapper/vulkan_gltf.h"
//#include "vulkan_wrapper/vulkan_renderer.h"
//
//// STD
//#include <memory>
//#include <vector>
//
//#include <vulkan/vulkan.h>


namespace graphics3d
{


   class CLASS_DECL_BRED scene_render_system : virtual public ::graphics3d::render_system
   {
   public:


      // scene_render_system(VkSandboxDevice &device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout,
      //                 IAssetProvider & assets);
      scene_render_system();
      ~scene_render_system();


      // void init(VkSandboxDevice & device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout,
      //           VkSandboxDescriptorPool & descriptorPool, size_t frameCount) override;

      // void render(FrameInfo & frame) override;

      void on_prepare(::gpu::context *pgpucontext) override;

      void on_render(::gpu::context *pgpucontext, ::graphics3d::scene_base *pscene) override;
      // private:
      // void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
      // void createPipeline(VkRenderPass renderPass);

      // VkSandboxDevice & m_device;

      // VkDescriptorSetLayout m_globalSetLayout;
      /*VkDescriptorSetLayout m_iblSetLayout;
      VkDescriptorSet m_iblDescriptorSet;*/

      // std::unique_ptr<VkSandboxPipeline> m_opaquePipeline;
      // std::unique_ptr<VkSandboxPipeline> m_maskPipeline;
      // std::unique_ptr<VkSandboxPipeline> m_blendPipeline;
      // VkPipelineLayout m_pipelineLayout;

      // IAssetProvider & m_assets;

      // std::unique_ptr<VkSandboxDescriptorSetLayout> m_iblLayout;
      // std::vector<VkDescriptorSet>				  m_iblDescriptorSets;

      // std::unique_ptr<VkSandboxDescriptorSetLayout> m_pbrLayout;
      // std::vector<VkDescriptorSet>				  m_pbrDescriptorSets;
      //};
   };

} // namespace graphics3d
