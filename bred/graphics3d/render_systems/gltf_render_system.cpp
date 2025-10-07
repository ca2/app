#include "framework.h"
//#include "bred/gpu/gltf_model.h"
#include "gltf_render_system.h"
#include "bred/gpu/context.h"
#include "bred/gpu/frame.h"
#include "bred/gpu/renderer.h"
#include "bred/graphics3d/scene_base.h"
#include "bred/graphics3d/types.h"
//#include "graphics3d/_.h"
//#include <stdexcept>


namespace graphics3d
{


   // gltf_render_system::gltf_render_system(
   //     graphics3d::device * pdevice,
   //     VkRenderPass renderPass,
   //     VkDescriptorSetLayout globalSetLayout,
   //     IAssetProvider& assets
   // ) :
   //     m_pgpudevice(pdevice),
   //     m_pdescriptorsetlayoutUbo(globalSetLayout),
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
   //    graphics3d::device * pdevice,
   //     VkRenderPass renderPass,
   //     VkDescriptorSetLayout globalSetLayout,
   //    graphics3d::sandbox_descriptor_pool& descriptorPool,
   //     size_t frameCount
   // ) {
   //     m_pdescriptorsetlayoutUbo = globalSetLayout;
   //
   //     m_pdescriptorsetlayoutIbl = graphics3d::sandbox_descriptor_set_layout::Builder{ pdevice }
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
   //     m_vkdescriptorsetaIbl.resize(frameCount);
   //     for (uint32_t i = 0; i < frameCount; i++) {
   //         VkDescriptorSet set;
   //         descriptorPool.allocateDescriptor(
   //             m_pdescriptorsetlayoutIbl->getDescriptorSetLayout(),
   //             set,
   //             /*setIndex=*/0
   //         );
   //         // grab descriptors straight from the provider:
   //         auto brdfInfo = m_assets.getBRDFLUTDescriptor();
   //         auto irradianceInfo = m_assets.getIrradianceDescriptor();
   //         // auto prefilterInfo = m_assets.getPrefilteredDescriptor();
   //
   //         graphics3d::sandbox_descriptor_writer(*m_pdescriptorsetlayoutIbl, descriptorPool)
   //             .writeImage(0, &brdfInfo)
   //             .writeImage(1, &irradianceInfo)
   //           //  .writeImage(2, &prefilterInfo)
   //             .build(set);
   //
   //         m_vkdescriptorsetaIbl[i] = set;
   //     }
   //
   //
   // }

   void gltf_render_system::on_prepare(::gpu::context *pgpucontext)
   {

      auto prenderer = pgpucontext->m_pgpurenderer;

      m_pshader = prenderer->create_shader(
         "matter://shaders/vert.vert",
         "matter://shaders/frag.frag",
         {::gpu::shader::e_descriptor_set_slot_global, ::gpu::shader::e_descriptor_set_slot_local}, {},
         {}  ,
         pgpucontext->input_layout<::graphics3d::Vertex>()

      );

      // m_pshader->m_bClearColor = true;
      // m_pshader->m_colorClear = argb(0.8f, 0.1f, 0.5f, 0.1f);
   }


   // void gltf_render_system::createPipelineLayout(VkDescriptorSetLayout globalSetLayout) {
   //     const ::array_base<VkDescriptorSetLayout> layouts = {
   //         globalSetLayout,
   //         graphics3d::gltf::descriptorSetLayoutUbo,
   //         graphics3d::gltf::descriptorSetLayoutImage,
   //         m_pdescriptorsetlayoutIbl->getDescriptorSetLayout()
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
   //         vkinit::vertexInputBindingDescription(0, sizeof(graphics3d::gltf::Vertex), VK_VERTEX_INPUT_RATE_VERTEX)
   //     };
   //
   //     ::array_base<VkVertexInputAttributeDescription> attributes = {
   //         vkinit::vertexInputAttributeDescription(0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(graphics3d::gltf::Vertex, pos)),
   //         vkinit::vertexInputAttributeDescription(0, 1, VK_FORMAT_R32G32B32_SFLOAT, offsetof(graphics3d::gltf::Vertex, normal)),
   //         vkinit::vertexInputAttributeDescription(0, 2, VK_FORMAT_R32G32_SFLOAT, offsetof(graphics3d::gltf::Vertex, uv)),
   //         vkinit::vertexInputAttributeDescription(0, 3, VK_FORMAT_R32G32B32A32_SFLOAT, offsetof(graphics3d::gltf::Vertex, color)),
   //         vkinit::vertexInputAttributeDescription(0, 4, VK_FORMAT_R32G32B32A32_SFLOAT, offsetof(graphics3d::gltf::Vertex, tangent))
   //     };
   //
   //     // OPAQUE
   //     // graphics3d::pipeline_configuration_information opaqueConfig{};
   //     // graphics3d::pipeline::default_pipeline_configuration(opaqueConfig);
   //     // opaqueConfig.pipelineLayout = m_pipelineLayout;
   //     // opaqueConfig.renderPass = renderPass;
   //     // opaqueConfig.bindingDescriptions = bindings;
   //     // opaqueConfig.attributeDescriptions = attributes;
   //
   //     m_opaquePipeline = øcreate_pointer<graphics3d::pipeline>(
   //         //m_pgpudevice, vertSpv, fragSpv, opaqueConfig);
   //         m_pgpudevice, vertSpv, fragSpv);
   //
   //     // MASK
   //     // graphics3d::pipeline_configuration_information maskConfig{};
   //     // graphics3d::pipeline::default_pipeline_configuration(maskConfig);
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
   //     m_maskPipeline = øcreate_pointer<graphics3d::pipeline>(
   //         //m_pgpudevice, vertSpv, fragSpv, maskConfig);
   //         m_pgpudevice, vertSpv, fragSpv);
   //
   //     // // BLEND
   //     // graphics3d::pipeline_configuration_information blendConfig{};
   //     // graphics3d::pipeline::default_pipeline_configuration(blendConfig);
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
   //     m_blendPipeline = øcreate_pointer<graphics3d::pipeline>(
   //     m_pgpudevice, vertSpv, fragSpv);
   //     //m_pgpudevice, vertSpv, fragSpv, blendConfig);
   // }


   void gltf_render_system::on_render(::gpu::context* pgpucontext, ::graphics3d::scene_base* pscene)
   {

      // vkCmdBindDescriptorSets(
      //     frame.m_pcommandbuffer,
      //     VK_PIPELINE_BIND_POINT_GRAPHICS,
      //     m_pipelineLayout,
      //     0, 1,
      //     &frame.globalDescriptorSet,
      //     0, nullptr);

//      auto pframe = ::gpu::current_frame();
//
//      auto& sceneobjects = pscene->scene_objects();
//
//      for (auto& [id, pgameobject] : sceneobjects)
//      {
//
//         auto prenderable = pgameobject->renderable();
//
//         if (!prenderable
// || 			 prenderable->m_erenderabletype !=
//            ::gpu::e_renderabled_type_gltf)
//) continue;
//            
//         ::cast<::gpu::gltf::Model> model =  baseModel;
//
//         if (!prenderable) continue;
//
//         prenderable->bind(pframe->m_pgpucommandbuffer);
//
//         for (auto* node : prenderable->m_linearNodes)
//         {
//
//            if (!node->mesh) continue;
//
//            glm::mat4 world = pgameobject->getTransform().mat4() * node->getMatrix();
//            glm::mat4 normalMat = glm::transpose(glm::inverse(world));
//            memcpy(node->mesh->uniformBuffer.mapped, &world, sizeof(world));
//            memcpy((char*)node->mesh->uniformBuffer.mapped + sizeof(world), &normalMat, sizeof(normalMat));
//
//             vkCmdBindDescriptorSets(
//                 frame.m_pcommandbuffer,
//                 VK_PIPELINE_BIND_POINT_GRAPHICS,
//                 m_pipelineLayout,
//                 1, 1,
//                 &node->mesh->uniformBuffer.descriptorSet,
//                 0, nullptr);
//
//            const auto& mat = node->mesh->primitives[0]->material;
//            switch (mat.alphaMode) {
//            case ::graphics3d::gltf::Material::ALPHAMODE_OPAQUE:
//               m_opaquePipeline->bind(frame.m_pcommandbuffer);
//               break;
//            case ::graphics3d::gltf::Material::ALPHAMODE_MASK:
//               m_maskPipeline->bind(frame.m_pcommandbuffer);
//               break;
//            case ::graphics3d::gltf::Material::ALPHAMODE_BLEND:
//            default:
//               m_blendPipeline->bind(frame.m_pcommandbuffer);
//               break;
//            }
//
//
//            model->drawNode(
//               node,
//               frame.m_pcommandbuffer,
//               ::graphics3d::gltf::RenderFlags::BindImages,
//               m_pipelineLayout,
//               2 // bindImageSet
//            );
//         }
//      }
   }
} // namespace graphics3d



