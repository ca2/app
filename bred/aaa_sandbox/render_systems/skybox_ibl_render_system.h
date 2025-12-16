#pragma once

#include "bred/graphics3d/render_system.h"
//#include "SceneFoundry/graphics3d/asset_provider.h"
//#include "device.h"
//#include "SceneFoundry/graphics3d/pipeline.h"
//#include "SceneFoundry/graphics3d/descriptor.h"
//#include "gltf.h"
//#include <vulkan/vulkan.h>

// STD
//#include <memory>
//#include <vector>
//#include <array>

namespace graphics3d
{


    class CLASS_DECL_BRED skybox_ibl_render_system :
        virtual public ::graphics3d::render_system
    {
    public:


        //aaaVkDescriptorSetLayout m_skyboxLayout;


        //::pointer<::gpu_vulkan::pipeline> m_ppipeline;
        //VkPipelineLayout m_pipelineLayout;
        //VkDescriptorImageInfo m_skyboxImageInfo{};
        //::pointer<graphics3d::sandbox_descriptor_set_layout> m_skyboxSetLayout;
        //VkDescriptorSet m_skyboxDescriptorSet;

        //graphics3d::sandbox_descriptor_pool* m_descriptorPool = nullptr;
        bool m_bHasCubemap = false;


        //skybox_ibl_render_system(graphics3d::device * pdevice, VkRenderPass renderPass, aaaVkDescriptorSetLayout globalSetLayout);
        skybox_ibl_render_system();
        ~skybox_ibl_render_system();

        // skybox_ibl_render_system(const skybox_ibl_render_system&) = delete;
        // skybox_ibl_render_system& operator=(const skybox_ibl_render_system&) = delete;

        // void init(
        //    graphics3d::device * pdevice,
        //     VkRenderPass            renderPass,
        //     aaaVkDescriptorSetLayout   globalSetLayout,
        //    graphics3d::sandbox_descriptor_pool& descriptorPool,
        //     size_t frameCount)override;

        // Call this inside your scene render loop, after global descriptors are bound
        void on_render(::gpu::frame * pframe) override;

        //
        // inline void setCubemapTexture(const VkDescriptorImageInfo& info) {
        //     m_skyboxImageInfo = info;
        //     m_bHasCubemap = true;
        //     allocateAndWriteSkyboxDescriptorSet();
        // }
        //
        // inline void setCubemapByName(const ::scoped_string & name, const IAssetProvider& provider) {
        //     VkDescriptorImageInfo desc = provider.getCubemapDescriptor(name);
        //     setCubemapTexture(desc); // <--- this is where we can handle descriptor set allocation
        // }

        void createSkyboxDescriptorSetLayout();
        void allocateAndWriteSkyboxDescriptorSet();
    //private:
        //void createPipelineLayout(aaaVkDescriptorSetLayout globalSetLayout);
        //void createPipeline(VkRenderPass renderPass);




    };


} // namespace graphics3d




