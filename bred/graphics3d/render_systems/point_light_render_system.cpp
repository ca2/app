#include "framework.h"
#include "point_light_render_system.h"
//#include "global_ubo.h"
//#include "pipeline.h"
#include "aura/platform/application.h"
#include "bred/graphics3d/engine.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/model_buffer.h"
#include "bred/gpu/properties.h"
#include "bred/gpu/renderer.h"
#include "bred/gpu/shader.h"
#include "bred/graphics3d/camera.h"
#include "bred/graphics3d/frame.h"
#include "bred/graphics3d/scene_base.h"
#include "bred/graphics3d/game_object.h"
#include "bred/graphics3d/point_light.h"
//#include "SceneFoundry/graphics3d/game_object.h"
// // libs
// 
// 
// 
// 
// 
// // std
// //#include <array>
// //#include <cassert>
// //#include <map>
// //#include <stdexcept>
// //#include <cassert>


namespace graphics3d
{
   // Define light constants
   struct PointLightPushConstants
   {
      floating_sequence4 position{};
      floating_sequence4 color{};
      float radius;
   };


   // point_light_render_system::point_light_render_system(graphics3d::device * pdevice, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout)
   //     : m_pgpudevice(pdevice), m_pdescriptorsetlayoutUbo(globalSetLayout)
   // {
   //
   // }
   point_light_render_system::point_light_render_system()
   {

   }


   // void point_light_render_system::init(
   //    graphics3d::device * pgpudevice,
   //     VkRenderPass renderPass,
   //     VkDescriptorSetLayout globalSetLayout,
   //    graphics3d::sandbox_descriptor_pool& descriptorPool,
   //     size_t frameCount)
   // {
   //     // Optional: ASSERT pdevice consistency
   //     ASSERT(pgpudevice == m_pgpudevice);
   //
   //     createPipelineLayout(globalSetLayout);
   //     createPipeline(renderPass);
   // }

   point_light_render_system::~point_light_render_system()
   {
      //vkDestroyPipelineLayout(m_pgpudevice->device(), m_pipelineLayout, nullptr);
   }


   void point_light_render_system::initialize_render_system(graphics3d::engine *pengine)
   {

      ::graphics3d::render_system::initialize_render_system(pengine);


      ødefer_construct_new(m_pmodelDummy);

      // ::graphics3d::model::Builder builderDummy;

      m_pmodelDummy->initialize_dummy_model(
         pengine->m_pgpucontextCompositor2->m_pgpurenderer,
         6);


   }


   void point_light_render_system::on_prepare(::gpu::context * pgpucontext)
   {

      auto prenderer = pgpucontext->m_pgpurenderer;

      m_pshader = øcreate<::gpu::shader>();

      m_pshader->m_propertiesPushShared.set_properties(::gpu_properties<::gpu::point_light_push_constants>());
      
      pgpucontext->layout_push_constants(m_pshader->m_propertiesPushShared, false);

      m_pshader->initialize_shader(
         pgpucontext->m_pgpurenderer,
         "matter://shaders/point_light.vert",
         "matter://shaders/point_light.frag",
         { ::gpu::shader::e_descriptor_set_slot_global,
         ::gpu::shader::e_descriptor_set_slot_local },
         nullptr,
         pgpucontext->input_layout<::graphics3d::Vertex>(),
         ::gpu::shader::e_flag_clear_default_bindings_and_attributes_descriptions
      );

   }


   // void point_light_render_system::createPipelineLayout(VkDescriptorSetLayout globalSetLayout) {
   //     // VkPushConstantRange pushConstantRange{};
   //     // pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
   //     // pushConstantRange.offset = 0;
   //     // pushConstantRange.size = sizeof(PointLightPushConstants);
   //     //
   //     // ::array_base<VkDescriptorSetLayout> setLayouts = { globalSetLayout };
   //     //
   //     // VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
   //     // pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
   //     // pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(setLayouts.size());
   //     // pipelineLayoutInfo.pSetLayouts = setLayouts.data();
   //     // pipelineLayoutInfo.pushConstantRangeCount = 1;
   //     // pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
   //     //
   //     // if (vkCreatePipelineLayout(m_pgpudevice->device(), &pipelineLayoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS) {
   //     //     throw std::runtime_error("failed to create point_light_render_system pipeline layout!");
   //     // }
   // }

   // void point_light_render_system::createPipeline(VkRenderPass renderPass) {
   //     ASSERT(m_pipelineLayout != VK_NULL_HANDLE && "Cannot create pipeline before pipeline layout");
   //
   //     //graphics3d::pipeline_configuration_information pipelineconfiguration{};
   //     //graphics3d::pipeline::default_pipeline_configuration(pipelineconfiguration);
   //     //pipelineconfiguration.bindingDescriptions.clear();
   //     //pipelineconfiguration.attributeDescriptions.clear();
   //     //pipelineconfiguration.renderPass = renderPass;
   //     //pipelineconfiguration.pipelineLayout = m_pipelineLayout;
   //
   //     ::string vertShaderPath = "matter://shaders/spirV/point_light.vert.spv";
   //     ::string fragShaderPath = "matter://shaders/spirV/point_light.frag.spv";
   //
   //     //m_ppipeline = øallocate graphics3d::pipeline(
   //     //    m_pgpudevice,
   //     //    vertShaderPath.c_str(),
   //     //    fragShaderPath.c_str(),
   //     //    pipelineconfiguration
   //     //);
   //     m_ppipeline = m_pgpudevice->create_pipeline_from_file(
   //        vertShaderPath.c_str(),
   //        fragShaderPath.c_str()
   //     );
   // }

   void point_light_render_system::on_render(::gpu::context* pgpucontext, ::graphics3d::scene_base * pscene)
   {
      //::map<float, uint32_t> sorted;

      auto & pointlighta = pscene->m_pointlighta;

      // for (auto ppointlight: pointlighta)
      // {
      //    floating_sequence3 offset = pframe->camera()->getPosition() - pobject->transform().translation;
      //    // need to implement getPosition because ICamera has no defintion
      //    float distanceSquared = glm::dot(offset, offset);
      //    sorted[distanceSquared] = pobject->getId();
      // }
      //
      //
      pgpucontext->defer_bind(m_pshader);

      auto pframe = ::gpu::current_frame();

      // vkCmdBindDescriptorSets(
      //     frame.m_pcommandbuffer,
      //     VK_PIPELINE_BIND_POINT_GRAPHICS,
      //     m_pipelineLayout,
      //     0,
      //     1,
      //     &frame.globalDescriptorSet,
      //     0,
      //     nullptr
      // );

      for (auto ppointlight : pointlighta)
      {
         //auto pobject = (*pframe->scene_objects())[it->element2()];
         //::cast<point_light> ppointlight = pobject;
         ::gpu::point_light_push_constants pushconstants{};
         pushconstants.position = floating_sequence4(
            ppointlight->transform().m_sequence3Position, 1.0f);
         pushconstants.color = floating_sequence4(
            ppointlight->color().f32_red(),
            ppointlight->color().f32_green(),
            ppointlight->color().f32_blue(),
            ppointlight->m_fLightIntensity);
         pushconstants.radius = ppointlight->transform().m_sequence3Scale.x;

         m_pshader->set_push_properties(pframe->m_pgpucommandbuffer, ::as_memory_block(pushconstants));

         // vkCmdPushConstants(
         //     frame.m_pcommandbuffer,
         //     m_pipelineLayout,
         //     VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
         //     0,
         //     sizeof(PointLightPushConstants),
         //     &push
         // );
         //pframe->m_pgpucommandbuffer->draw_vertexes(6);
         //vkCmdDraw(frame.m_pcommandbuffer, 6, 1, 0, 0);
         m_pmodelDummy->bind(pframe->m_pgpucommandbuffer);
         m_pmodelDummy->draw(pframe->m_pgpucommandbuffer);
      }

      pgpucontext->defer_unbind(m_pshader);

   }


   void point_light_render_system::on_update(::gpu::context* pgpucontext, ::graphics3d::scene_base * pscene)
   {

      auto dt = m_pengine->dt();

      //auto pscene = m_pengine->m_pscene;

      auto& globalubo = pscene->global_ubo();

      //auto rotateLight = floating_matrix4(1.f);
      //rotateLight.rotate(0.5f * dt, { 0.f, -1.f, 0.f });

      int lightIndex = 0;

      auto & pointlighta = pscene->m_pointlighta;

      for (auto ppointlight : pointlighta)
      {
         auto rotateLight = floating_matrix4(1.f);
         
         rotateLight.rotate(radians(0.5f * dt), {0.f, -1.f, 0.f});

         // update light position
         ppointlight->m_transform.m_sequence3Position =
            floating_sequence3(rotateLight * floating_sequence4(ppointlight->m_transform.m_sequence3Position, 1.f));

         // copy light to ubo
         globalubo["pointLights"][lightIndex]["position"] =
            floating_sequence4(ppointlight->m_transform.m_sequence3Position, 1.f);
         globalubo["pointLights"][lightIndex]["color"] =
            floating_sequence4(ppointlight->m_color.f32_red(),
            ppointlight->m_color.f32_green(),
            ppointlight->m_color.f32_blue(),
                ppointlight->m_fLightIntensity);

         lightIndex += 1;

      }

      globalubo["numLights"] = lightIndex;

      // auto rotateLight = glm::rotate(floating_matrix4(1.f), m_rotationSpeed * pframe->frameTime(), {0.f, -1.f, 0.f});
      // auto &ubo = (*ppropertiesGlobalUbo);
      // int lightIndex = 0;
      // auto &sceneobjects = (*pframe->scene_objects());
      // for (auto &[id, pobject]: sceneobjects)
      // {
      //    ::cast<point_light_scene_object> ppointlight = pobject;
      //    if (!ppointlight)
      //       continue;
      //
      //    ASSERT(lightIndex < point_light::MAX_LIGHTS && "Point lights exceed maximum supported.");
      //
      //    auto &transform = ppointlight->getTransform();
      //    transform.translation = floating_sequence3(rotateLight * floating_sequence4(transform.translation, 1.f));
      //
      //    auto pointLights = ubo["pointLights"];
      //    pointLights[lightIndex]["position"] = floating_sequence4(transform.translation, 1.f);
      //    pointLights[lightIndex]["color"] = floating_sequence4(ppointlight->getColor(),
      //                                                 ppointlight->m_fLightIntensity);
      //
      //    ++lightIndex;
      // }
      //
      // ubo["numLights"] = lightIndex;
   }



} //  namespace graphics3d
