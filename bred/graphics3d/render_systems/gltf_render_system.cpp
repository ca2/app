#include "framework.h"
#include "gltf_render_system.h"
#include "bred/gltf/vertex.h"
#include "bred/gpu/binding.h"
#include "bred/gpu/context.h"
#include "bred/gpu/frame.h"
#include "bred/gpu/renderer.h"
#include "bred/graphics3d/engine.h"
#include "bred/graphics3d/global_ubo1.h"
#include "bred/graphics3d/scene_base.h"
#include "bred/graphics3d/types.h"


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

      m_pshader = øcreate<::gpu::shader>();

      m_pshader->set_global_ubo();
      //auto & bindingUbo = m_pshader->binding();
      //bindingUbo.m_strUniform = "ubo";
      //bindingUbo.m_ebinding = ::gpu::e_binding_global_ubo;
      
         
      //m_pshader->initialize_shader(
      //      pgpucontext->m_pgpurenderer,
      //   "matter://shaders/vert.vert",
      //   "matter://shaders/frag.frag",
      //   {::gpu::shader::e_descriptor_set_slot_local}, {},
      //   pgpucontext->input_layout<::graphics3d::Vertex>()

      //);

      // m_pshader->m_bClearColor = true;
      // m_pshader->m_colorClear = argb(0.8f, 0.1f, 0.5f, 0.1f);

            auto pcontext = m_pengine->gpu_context();

       øconstruct(m_pshaderOpaque);
       øconstruct(m_pshaderMask);
       øconstruct(m_pshaderBlend);


       auto ppropertiesUbo = ::gpu_properties<::graphics3d::global_ubo1>();
       auto ppropertiesPush = ::gpu_properties<push_constants>();
       auto pinputlayout = pgpucontext->input_layout < ::gpu::gltf::vertex >();


       
      

       //m_pdescriptorsetlayoutIbl =
       //   ::gpu_vulkan::descriptor_set_layout::Builder(pcontext)
       //      .addBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT)
       //      .addBinding(1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT)
       //      .addBinding(2, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT)
       //      .build();

       //m_pdescriptorsetlayoutPbr =
       //   ::gpu_vulkan::descriptor_set_layout::Builder(pcontext)
       //      .addBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT) // albedo
       //      .addBinding(1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT) // normal
       //      .addBinding(2, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT) //
       //      metallicRoughness .addBinding(3, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT)
       //      // ao .addBinding(4, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT) // emissive
       //      .build();




      //::cast<::gpu_vulkan::shader> pshaderOpaque = m_pshaderOpaque;
       m_pshaderOpaque->binding_set(0, pgpucontext->global_ubo1_binding_set());
       m_pshaderOpaque->binding_set(1, pgpucontext->ibl1_binding_set());
       m_pshaderOpaque->binding_set(2, pgpucontext->gltf_pbr_binding_set());
       //pshaderOpaque->m_mapDescriptorSetLayout[1] = m_pdescriptorsetlayoutIbl;
       //pshaderOpaque->m_mapDescriptorSetLayout[2] = m_pdescriptorsetlayoutPbr;
       m_pshaderOpaque->m_propertiesPushShared.set_properties(ppropertiesPush);
       pgpucontext->layout_push_constants(m_pshaderOpaque->m_propertiesPushShared, false);
      //m_pshaderOpaque->m_propertiesPushVertex.set_properties(ppropertiesPushVertex);
      //m_pshaderOpaque->m_propertiesPushFragment.set_properties(ppropertiesPushFragment);
      //pgpucontext->layout_push_constants(m_pshaderOpaque->m_propertiesPushVertex);
      //pgpucontext->layout_push_constants(m_pshaderOpaque->m_propertiesPushFragment);
       m_pshaderOpaque->set_global_ubo();
       m_pshaderOpaque->initialize_shader_with_block(
          pgpucontext->m_pgpurenderer,
          gltf_vert_memory(),
          gltf_frag_memory(),
          {},
          {},
          pinputlayout);


      auto pshaderMask = m_pshaderMask;

       //pshaderMask->m_mapDescriptorSetLayout[1] = m_pdescriptorsetlayoutIbl;
       //pshaderMask->m_mapDescriptorSetLayout[2] = m_pdescriptorsetlayoutPbr;

      m_pshaderMask->binding_set(0, pgpucontext->global_ubo1_binding_set());
      m_pshaderMask->binding_set(1, pgpucontext->ibl1_binding_set());
      m_pshaderMask->binding_set(2, pgpucontext->gltf_pbr_binding_set());


       m_pshaderMask->m_propertiesPushShared.set_properties(ppropertiesPush);
       m_pshaderMask->set_global_ubo();
       pgpucontext->layout_push_constants(m_pshaderMask->m_propertiesPushShared, false);
      //m_pshaderMask->m_propertiesPushVertex.set_properties(ppropertiesPushVertex);
      //m_pshaderMask->m_propertiesPushFragment.set_properties(ppropertiesPushFragment);
      //pgpucontext->layout_push_constants(m_pshaderMask->m_propertiesPushVertex);
      //pgpucontext->layout_push_constants(m_pshaderMask->m_propertiesPushFragment);
       m_pshaderMask->initialize_shader_with_block(
          pgpucontext->m_pgpurenderer, gltf_vert_memory(), gltf_frag_memory(),
                                                   {},
          {},
          pinputlayout);

      auto pshaderBlend = m_pshaderBlend;

       //pshaderBlend->m_mapDescriptorSetLayout[1] = m_pdescriptorsetlayoutIbl;
       //pshaderBlend->m_mapDescriptorSetLayout[2] = m_pdescriptorsetlayoutPbr;

      m_pshaderBlend->binding_set(0, pgpucontext->global_ubo1_binding_set());
      m_pshaderBlend->binding_set(1, pgpucontext->ibl1_binding_set());
      m_pshaderBlend->binding_set(2, pgpucontext->gltf_pbr_binding_set());



       m_pshaderBlend->m_propertiesPushShared.set_properties(ppropertiesPush);
       m_pshaderBlend->set_global_ubo();
       pgpucontext->layout_push_constants(m_pshaderBlend->m_propertiesPushShared, false);
      //m_pshaderBlend->m_propertiesPushVertex.set_properties(ppropertiesPushVertex);
      //m_pshaderBlend->m_propertiesPushFragment.set_properties(ppropertiesPushFragment);
      //pgpucontext->layout_push_constants(m_pshaderBlend->m_propertiesPushVertex);
      //pgpucontext->layout_push_constants(m_pshaderBlend->m_propertiesPushFragment);
       m_pshaderBlend->initialize_shader_with_block(
          pgpucontext->m_pgpurenderer, gltf_vert_memory(), gltf_frag_memory(),
                                                    {},
          {},
          pinputlayout);


      //createPipelineLayout(pcontext->m_psetdescriptorlayoutGlobal->getDescriptorSetLayout());

      //auto prenderpass = render_pass2();

      //createPipeline(prenderpass->m_vkrenderpass);

      //::cast<::gpu_vulkan::renderer> prenderer = pcontext->m_pgpurenderer;

      //::cast<::gpu_vulkan::render_target> prendertarget = prenderer->m_pgpurendertarget;

      //auto frameCount = prendertarget->get_frame_count();

      //m_vkdescriptorsetaIbl.resize(frameCount);

      //auto pdescriptorpoolbuilder = øallocate::gpu_vulkan::descriptor_pool::Builder();

      //pdescriptorpoolbuilder->initialize_builder(pcontext);
      //pdescriptorpoolbuilder->setMaxSets(frameCount * 10);
      //pdescriptorpoolbuilder->addPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, frameCount * 100);

      //m_pdescriptorpool = pdescriptorpoolbuilder->build();


      //auto passetmanager = m_pengine->m_pimmersionlayer->m_passetmanager;

      //::cast<::graphics3d::scene> pscene = m_pengine->m_pimmersionlayer->m_pscene;

      //for (uint32_t i = 0; i < frameCount; i++)
      //{

      //   VkDescriptorSet set;

      //   // m_pdescriptorpool->allocateDescriptor(m_pdescriptorsetlayoutIbl->getDescriptorSetLayout(), set,
      //   //                                 /*setIndex=*/0);
      //   m_pdescriptorpool->allocateDescriptor(
      //      m_pdescriptorsetlayoutIbl->getDescriptorSetLayout(), set, 0);

      //   ::cast<::gpu_vulkan::texture> ptextureIrrad = pscene->m_ptextureIrradianceCube;
      //   ::cast<::gpu_vulkan::texture> ptexturePrefltr = pscene->m_ptexturePrefilteredCube;
      //   ::cast<::gpu_vulkan::texture> ptextureBrdf = pscene->m_ptextureLuBrdf;
      //   // auto irradianceInfo = m_assets.getIrradianceDescriptor();
      //   // auto prefilterInfo = m_assets.getPrefilteredDescriptor();

      //   auto irradianceInfo = ptextureIrrad->m_descriptor3;
      //   auto prefilterInfo = ptexturePrefltr->m_descriptor3;
      //   auto brdfInfo = ptextureBrdf->m_descriptor3;


      //   ::gpu_vulkan::descriptor_writer(*m_pdescriptorsetlayoutIbl, *m_pdescriptorpool)
      //      .writeImage(0, &irradianceInfo)
      //      .writeImage(1, &prefilterInfo)
      //      .writeImage(2, &brdfInfo)
      //      .build(set);

      //   m_vkdescriptorsetaIbl[i] = set;
      //}

      //for (uint32_t uFrameIndex = 0; uFrameIndex < frameCount; uFrameIndex++)
      //{
      //   VkDescriptorSet set;
      //   // m_pdescriptorpool->allocateDescriptor(m_pdescriptorsetlayoutPbr->getDescriptorSetLayout(), set,
      //*setIndex=*/0); /   //
      
       
       //m_pdescriptorpool->allocateDescriptor(m_pdescriptorsetlayoutPbr->getDescriptorSetLayout(), set);

      //   // auto logDescriptor = [&](const char *name, const VkDescriptorImageInfo &info)
      //   //{
      //   //    information("{} - sampler: {}, imageView: {}, layout: {}", name, (uint64_t)info.sampler,
      //   //                 (uint64_t)info.imageView, (int)info.imageLayout);
      //   // };

      //   if (1)
      //   {

      //      auto &scenerenderables = pscene->scene_renderables();

      //      //   //// xxxxxxxxxxxxxxxxx
      //      ::cast<::gpu_vulkan::context> pcontext = m_pengine->gpu_context();
      //      ::cast<::gpu_vulkan::renderer> prenderer = pcontext->m_pgpurenderer;

      //      ////// xxxxxxxxxxxxxxxxx
      //      // auto globalSetLayout = pcontext->m_psetdescriptorlayoutGlobal->getDescriptorSetLayout();
      //      auto vkdescriptorsetGlobal = pcontext->getGlobalDescriptorSet(prenderer, uFrameIndex);


      //      for (auto &[id, pscenerenderable]: scenerenderables)
      //      {

      //         if (!pscenerenderable)
      //         {

      //            continue;
      //         }

      //         if (pscenerenderable->m_erendersystem != ::graphics3d::e_render_system_gltf_ibl)
      //         {

      //            continue;
      //         }


      //         auto prenderable = pscenerenderable->renderable();
      //         if (!prenderable)
      //            continue;

      //         auto erenderabletype = prenderable->m_erenderabletype;

      //         if (erenderabletype != ::gpu::e_renderable_type_gltf)
      //         {
      //            continue; // not mine, skip
      //         }
      //         ::cast<::gpu_vulkan::gltf::Model> pgltfmodel = prenderable;

      //         if (!pgltfmodel)
      //            continue;

      //         //for (auto &material: pgltfmodel->m_materiala)
      //         //{
      //         //   if (material.baseColorTexture != nullptr)
      //         //   {
      //         //      material.addDescriptorSet(
      //         //         m_pdescriptorpool->m_vkdescriptorpool,
      //         //         m_pdescriptorsetlayoutPbr->m_vkdescriptorsetlayout,
      //         //         ::gpu_vulkan::gltf::DescriptorBindingFlags::ImageBaseColor |
      //         //         ::gpu_vulkan::gltf::DescriptorBindingFlags::ImageMetallicMap |
      //         //         ::gpu_vulkan::gltf::DescriptorBindingFlags::ImageNormalMap |
      //         //         ::gpu_vulkan::gltf::DescriptorBindingFlags::ImageAOMap |
      //         //         ::gpu_vulkan::gltf::DescriptorBindingFlags::ImageEmissiveMap,
      //         //         pgltfmodel->emptyTexture);
      //         //   }
      //         //}


      //         //pgltfmodel->m_vkdescriptorsetaPbr.resize(frameCount);


      //         // pgltfmodel->bind(pgpucommandbuffer);

      //         // for (auto *pnode: pgltfmodel->m_pgltfmodel->m_nodeaLinear)
      //         //{
      //         //    if (!pnode->m_pmesh)
      //         //       continue;


      //         //::cast<::gpu_vulkan::texture> ptextureAlbedo = pgltfmodel->y;
      //         //::cast<::gpu_vulkan::texture> ptextureNormal = passetmanager->getTexture("cerberus_normal");
      //         //::cast<::gpu_vulkan::texture> ptextureMetallic = passetmanager->getTexture("cerberus_metallic");
      //         //::cast<::gpu_vulkan::texture> ptextureRoughness = passetmanager->getTexture("cerberus_roughness");
      //         //::cast<::gpu_vulkan::texture> ptextureAo = passetmanager->getTexture("cerberus_ao");*/


      //         // VkDescriptorImageInfo albedoInfo = m_assets.getTextureDescriptor("cerberus_albedo");
      //         // VkDescriptorImageInfo normalInfo = m_assets.getTextureDescriptor("cerberus_normal");
      //         // VkDescriptorImageInfo metallicInfo = m_assets.getTextureDescriptor("cerberus_metallic");
      //         // VkDescriptorImageInfo roughnessInfo = m_assets.getTextureDescriptor("cerberus_roughness");
      //         // VkDescriptorImageInfo aoInfo = m_assets.getTextureDescriptor("cerberus_ao");

      //         //VkDescriptorImageInfo albedoInfo = ptextureAlbedo->m_descriptor3;
      //         //VkDescriptorImageInfo normalInfo = ptextureNormal->m_descriptor3;
      //         //VkDescriptorImageInfo metallicInfo = ptextureMetallic->m_descriptor3;
      //         //VkDescriptorImageInfo roughnessInfo = ptextureRoughness->m_descriptor3;
      //         //VkDescriptorImageInfo aoInfo = ptextureAo->m_descriptor3;

      //         // logDescriptor("albedo", albedoInfo);
      //         // logDescriptor("normal", normalInfo);
      //         // logDescriptor("metallic", metallicInfo);
      //         // logDescriptor("roughness", roughnessInfo);
      //         // logDescriptor("ao", aoInfo);

      //         //::gpu_vulkan::descriptor_writer(*m_pdescriptorsetlayoutPbr, *m_pdescriptorpool)
      //         //   .writeImage(0, &albedoInfo)
      //         //   .writeImage(1, &normalInfo)
      //         //   .writeImage(2, &metallicInfo)
      //         //   .writeImage(3, &roughnessInfo)
      //         //   .writeImage(4, &aoInfo)
      //         //   .build(set);

      //         //pgltfmodel->m_vkdescriptorsetaPbr[uFrameIndex] = set;
      //      }
      //   }
      //}

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


::memory gltf_render_system::gltf_vert_memory()
{

   throw ::interface_only();

   return {};

      }


   ::memory gltf_render_system::gltf_frag_memory()

   {

      throw ::interface_only();

      return {};
   }


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
//            floating_matrix4 world = pgameobject->getTransform().floating_matrix4() * node->getMatrix();
//            floating_matrix4 normalMat = glm::transpose(glm::inverse(world));
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
//            const auto& mat = node->mesh->prototypes[0]->material;
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






BEGIN_GPU_PROPERTIES(::graphics3d::gltf_render_system::push_constants)
GPU_PROPERTY("modelMatrix", ::gpu::e_type_mat4)
GPU_PROPERTY("normalMatrix", ::gpu::e_type_mat4)
GPU_PROPERTY("useTextureAlbedo", ::gpu::e_type_int)
GPU_PROPERTY("useTextureMetallicRoughness", ::gpu::e_type_int)
GPU_PROPERTY("useTextureNormal", ::gpu::e_type_int)
GPU_PROPERTY("useTextureAmbientOcclusion", ::gpu::e_type_int)
GPU_PROPERTY("useTextureEmissive", ::gpu::e_type_int)
GPU_PROPERTY("albedo", ::gpu::e_type_seq3)
GPU_PROPERTY("metallic", ::gpu::e_type_float)
GPU_PROPERTY("roughness", ::gpu::e_type_float)
GPU_PROPERTY("ambientOcclusion", ::gpu::e_type_float)
GPU_PROPERTY("emissive", ::gpu::e_type_seq3)
// GPU_PROPERTY("cameraPosition", ::gpu::e_type_seq3)
GPU_PROPERTY("bloomBrightnessCutoff", ::gpu::e_type_float)
GPU_PROPERTY("multiplier", ::gpu::e_type_seq3)
END_GPU_PROPERTIES()
