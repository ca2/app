#include "../framework.h"
//#include "bred/gpu/gltf_model.h"
#include "gltf_render_system.h"
#include "SceneFoundry/graphics3d/frame.h"
#include "sandbox_engine/_.h"
//#include <stdexcept>


namespace graphics3d
{


    // gltf_render_system::gltf_render_system(
    //     sandbox_renderer::device * pdevice,
    //     VkRenderPass renderPass,
    //     VkDescriptorSetLayout globalSetLayout,
    //     IAssetProvider& assets
    // ) :
    //     m_pgpudevice(pdevice),
    //     m_globalSetLayout(globalSetLayout),
    //     m_assets(assets)
    // {
    //
    // }

    gltf_render_system::gltf_render_system()
    {


    }

    gltf_render_system::~gltf_render_system() {
        //vkDestroyPipelineLayout(m_pgpudevice->device(), m_pipelineLayout, nullptr);
    }


    // void gltf_render_system::init(
    //    sandbox_renderer::device * pdevice,
    //     VkRenderPass renderPass,
    //     VkDescriptorSetLayout globalSetLayout,
    //    sandbox_renderer::sandbox_descriptor_pool& descriptorPool,
    //     size_t frameCount
    // ) {
    //     m_globalSetLayout = globalSetLayout;
    //
    //     m_iblLayout = sandbox_renderer::sandbox_descriptor_set_layout::Builder{ pdevice }
    //     .addBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT)
    //     .addBinding(1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT)
    //     //.addBinding(2, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT)
    //     .build();
    //
    //
    //
    //     createPipelineLayout(globalSetLayout);
    //     createPipeline(renderPass);
    //
    //     // --- 2) Allocate & write per‐frame IBL descriptor sets ---
    //     m_iblDescriptorSets.resize(frameCount);
    //     for (uint32_t i = 0; i < frameCount; i++) {
    //         VkDescriptorSet set;
    //         descriptorPool.allocateDescriptor(
    //             m_iblLayout->getDescriptorSetLayout(),
    //             set,
    //             /*setIndex=*/0
    //         );
    //         // grab descriptors straight from the provider:
    //         auto brdfInfo = m_assets.getBRDFLUTDescriptor();
    //         auto irradianceInfo = m_assets.getIrradianceDescriptor();
    //         // auto prefilterInfo = m_assets.getPrefilteredDescriptor();
    //
    //         sandbox_renderer::sandbox_descriptor_writer(*m_iblLayout, descriptorPool)
    //             .writeImage(0, &brdfInfo)
    //             .writeImage(1, &irradianceInfo)
    //           //  .writeImage(2, &prefilterInfo)
    //             .build(set);
    //
    //         m_iblDescriptorSets[i] = set;
    //     }
    //
    //
    // }

    // void gltf_render_system::createPipelineLayout(VkDescriptorSetLayout globalSetLayout) {
    //     const ::array_base<VkDescriptorSetLayout> layouts = {
    //         globalSetLayout,
    //         sandbox_renderer::gltf::descriptorSetLayoutUbo,
    //         sandbox_renderer::gltf::descriptorSetLayoutImage,
    //         m_iblLayout->getDescriptorSetLayout()
    //     };
    //
    //     VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    //     pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    //     pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(layouts.size());
    //     pipelineLayoutInfo.pSetLayouts = layouts.data();
    //
    //     if (vkCreatePipelineLayout(m_pgpudevice->device(), &pipelineLayoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS) {
    //         throw std::runtime_error("Failed to create GLTF pipeline layout");
    //     }
    // }

    // void gltf_render_system::createPipeline(VkRenderPass renderPass) {
    //     ASSERT(m_pipelineLayout != VK_NULL_HANDLE);
    //
    //     auto vertSpv = "matter://shaders/spirV/gltf_vert.vert.spv";
    //     auto fragSpv = "matter://shaders/spirV/gltf_frag.frag.spv";
    //
    //     ::array_base<VkVertexInputBindingDescription> bindings = {
    //         vkinit::vertexInputBindingDescription(0, sizeof(sandbox_renderer::gltf::Vertex), VK_VERTEX_INPUT_RATE_VERTEX)
    //     };
    //
    //     ::array_base<VkVertexInputAttributeDescription> attributes = {
    //         vkinit::vertexInputAttributeDescription(0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(sandbox_renderer::gltf::Vertex, pos)),
    //         vkinit::vertexInputAttributeDescription(0, 1, VK_FORMAT_R32G32B32_SFLOAT, offsetof(sandbox_renderer::gltf::Vertex, normal)),
    //         vkinit::vertexInputAttributeDescription(0, 2, VK_FORMAT_R32G32_SFLOAT, offsetof(sandbox_renderer::gltf::Vertex, uv)),
    //         vkinit::vertexInputAttributeDescription(0, 3, VK_FORMAT_R32G32B32A32_SFLOAT, offsetof(sandbox_renderer::gltf::Vertex, color)),
    //         vkinit::vertexInputAttributeDescription(0, 4, VK_FORMAT_R32G32B32A32_SFLOAT, offsetof(sandbox_renderer::gltf::Vertex, tangent))
    //     };
    //
    //     // OPAQUE
    //     // sandbox_renderer::pipeline_configuration_information opaqueConfig{};
    //     // sandbox_renderer::pipeline::defaultPipelineConfigInfo(opaqueConfig);
    //     // opaqueConfig.pipelineLayout = m_pipelineLayout;
    //     // opaqueConfig.renderPass = renderPass;
    //     // opaqueConfig.bindingDescriptions = bindings;
    //     // opaqueConfig.attributeDescriptions = attributes;
    //
    //     m_opaquePipeline = øcreate_pointer<sandbox_renderer::pipeline>(
    //         //m_pgpudevice, vertSpv, fragSpv, opaqueConfig);
    //         m_pgpudevice, vertSpv, fragSpv);
    //
    //     // MASK
    //     // sandbox_renderer::pipeline_configuration_information maskConfig{};
    //     // sandbox_renderer::pipeline::defaultPipelineConfigInfo(maskConfig);
    //     // maskConfig.pipelineLayout = m_pipelineLayout;
    //     // maskConfig.renderPass = renderPass;
    //     // maskConfig.bindingDescriptions = bindings;
    //     // maskConfig.attributeDescriptions = attributes;
    //     // maskConfig.colorBlendAttachment.blendEnable = VK_FALSE;
    //
    //     // struct SpecData { VkBool32 alphaMask; float cutoff; };
    //     // static SpecData specData{ VK_TRUE, 0.5f };
    //     // static VkSpecializationMapEntry mapEntries[2] = {
    //     //     { 0, offsetof(SpecData, alphaMask), sizeof(VkBool32) },
    //     //     { 1, offsetof(SpecData, cutoff),    sizeof(float) }
    //     // };
    //     // static VkSpecializationInfo specInfo{};
    //     // specInfo.mapEntryCount = 2;
    //     // specInfo.pMapEntries = mapEntries;
    //     // specInfo.dataSize = sizeof(specData);
    //     // specInfo.pData = &specData;
    //     //
    //     // maskConfig.fragSpecInfo = &specInfo;
    //
    //     m_maskPipeline = øcreate_pointer<sandbox_renderer::pipeline>(
    //         //m_pgpudevice, vertSpv, fragSpv, maskConfig);
    //         m_pgpudevice, vertSpv, fragSpv);
    //
    //     // // BLEND
    //     // sandbox_renderer::pipeline_configuration_information blendConfig{};
    //     // sandbox_renderer::pipeline::defaultPipelineConfigInfo(blendConfig);
    //     // blendConfig.pipelineLayout = m_pipelineLayout;
    //     // blendConfig.renderPass = renderPass;
    //     // blendConfig.bindingDescriptions = bindings;
    //     // blendConfig.attributeDescriptions = attributes;
    //     //
    //     // blendConfig.colorBlendAttachment.blendEnable = VK_TRUE;
    //     // blendConfig.colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    //     // blendConfig.colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    //     // blendConfig.colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
    //     // blendConfig.colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    //     // blendConfig.colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    //     // blendConfig.colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
    //     //
    //     // blendConfig.colorBlendAttachment.colorWriteMask =
    //     //     VK_COLOR_COMPONENT_R_BIT |
    //     //     VK_COLOR_COMPONENT_G_BIT |
    //     //     VK_COLOR_COMPONENT_B_BIT |
    //     //     VK_COLOR_COMPONENT_A_BIT;
    //
    //     m_blendPipeline = øcreate_pointer<sandbox_renderer::pipeline>(
    //     m_pgpudevice, vertSpv, fragSpv);
    //     //m_pgpudevice, vertSpv, fragSpv, blendConfig);
    // }



    void gltf_render_system::render(::graphics3d::IFrame * pframe)
    {
        // vkCmdBindDescriptorSets(
        //     frame.m_pcommandbuffer,
        //     VK_PIPELINE_BIND_POINT_GRAPHICS,
        //     m_pipelineLayout,
        //     0, 1,
        //     &frame.globalDescriptorSet,
        //     0, nullptr);

        auto pgameobjects = pframe->game_objects();

        for (auto& [id, pgameobject] : *pgameobjects) {
            auto pmodel = pgameobject->getModel();
            if (!pmodel) continue;

            //::cast<::gpu::gltf::Model> model =  baseModel;
            if (!pmodel) continue;

            pmodel->bind(pframe->getCommandBuffer());

            for (auto* node : model->m_linearNodes) {
                if (!node->mesh) continue;

                glm::mat4 world = pgameobject->getTransform().mat4() * node->getMatrix();
                glm::mat4 normalMat = glm::transpose(glm::inverse(world));
                memcpy(node->mesh->uniformBuffer.mapped, &world, sizeof(world));
                memcpy((char*)node->mesh->uniformBuffer.mapped + sizeof(world), &normalMat, sizeof(normalMat));

                // vkCmdBindDescriptorSets(
                //     frame.m_pcommandbuffer,
                //     VK_PIPELINE_BIND_POINT_GRAPHICS,
                //     m_pipelineLayout,
                //     1, 1,
                //     &node->mesh->uniformBuffer.descriptorSet,
                //     0, nullptr);

                const auto& mat = node->mesh->primitives[0]->material;
                switch (mat.alphaMode) {
                case ::sandbox_renderer::gltf::Material::ALPHAMODE_OPAQUE:
                    m_opaquePipeline->bind(frame.m_pcommandbuffer);
                    break;
                case ::sandbox_renderer::gltf::Material::ALPHAMODE_MASK:
                    m_maskPipeline->bind(frame.m_pcommandbuffer);
                    break;
                case ::sandbox_renderer::gltf::Material::ALPHAMODE_BLEND:
                default:
                    m_blendPipeline->bind(frame.m_pcommandbuffer);
                    break;
                }


                model->drawNode(
                    node,
                    frame.m_pcommandbuffer,
                   ::sandbox_renderer::gltf::RenderFlags::BindImages,
                    m_pipelineLayout,
                    2 // bindImageSet
                );
            }
        }
    }
} // namespace graphics3d