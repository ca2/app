#include "framework.h"
#include "global_ubo.h"
//#include "pipeline.h"
#include "aura/platform/application.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/properties.h"
#include "SceneFoundry/sandbox_renderer/render_systems/point_light_render_system.h"
#include "bred/sandbox/camera.h"
#include "bred/sandbox/frame.h"
#include "bred/sandbox/game_object.h"
//#include "SceneFoundry/sandbox/game_object.h"
// // libs
// #define GLM_FORCE_RADIANS
// #define GLM_FORCE_DEPTH_ZERO_TO_ONE
// #include <glm/glm.hpp>
// #include <glm/gtc/constants.hpp>
// #include <glm/gtx/transform.hpp>
// // std
// //#include <array>
// //#include <cassert>
// //#include <map>
// //#include <stdexcept>
// //#include <cassert>


namespace sandbox_renderer
{
    // Define light constants
    struct PointLightPushConstants {
        glm::vec4 position{};
        glm::vec4 color{};
        float radius;
    };

    // point_light_render_system::point_light_render_system(sandbox_renderer::device * pdevice, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout)
    //     : m_pgpudevice(pdevice), m_globalSetLayout(globalSetLayout)
    // {
    //
    // }
    point_light_render_system::point_light_render_system()
    {

    }
    // void point_light_render_system::init(
    //    sandbox_renderer::device * pgpudevice,
    //     VkRenderPass renderPass,
    //     VkDescriptorSetLayout globalSetLayout,
    //    sandbox_renderer::sandbox_descriptor_pool& descriptorPool,
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
    //     //sandbox_renderer::pipeline_configuration_information pipelineConfig{};
    //     //sandbox_renderer::pipeline::defaultPipelineConfigInfo(pipelineConfig);
    //     //pipelineConfig.bindingDescriptions.clear();
    //     //pipelineConfig.attributeDescriptions.clear();
    //     //pipelineConfig.renderPass = renderPass;
    //     //pipelineConfig.pipelineLayout = m_pipelineLayout;
    //
    //     ::string vertShaderPath = "matter://shaders/spirV/point_light.vert.spv";
    //     ::string fragShaderPath = "matter://shaders/spirV/point_light.frag.spv";
    //
    //     //m_ppipeline = øallocate sandbox_renderer::pipeline(
    //     //    m_pgpudevice,
    //     //    vertShaderPath.c_str(),
    //     //    fragShaderPath.c_str(),
    //     //    pipelineConfig
    //     //);
    //     m_ppipeline = m_pgpudevice->create_pipeline_from_file(
    //        vertShaderPath.c_str(),
    //        fragShaderPath.c_str()
    //     );
    // }

    void point_light_render_system::render(::sandbox::IFrame * pframe) {
        ::map<float, uint32_t> sorted;

auto pgameobjects = pframe->game_objects();

        for (auto& [id, pobject] : *pgameobjects) {
            ::cast < point_light_scene_object > ppointlightsceneobject = pobject;
            if (!ppointlightsceneobject) continue;
            glm::vec3 offset = pframe->camera()->getPosition() - pobject->getTransform().translation;// need to implement getPosition because ICamera has no defintion
            float distanceSquared = glm::dot(offset, offset);
            sorted[distanceSquared] = pobject->getId();
        }
        m_ppipeline->bind(pframe->getCommandBuffer());

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

        for (auto it = sorted.begin(); it != sorted.end(); ++it) {
            auto pobject = (*pframe->scene_objects())[it ->element2()];
            ::cast < point_light_scene_object > ppointlightsceneobject = pobject;
            PointLightPushConstants push{};
            push.position = glm::vec4(ppointlightsceneobject->getTransform().translation, 1.0f);
            push.color = glm::vec4(ppointlightsceneobject->getColor(), ppointlightsceneobject->m_fLightIntensity);
            push.radius = ppointlightsceneobject->getTransform().scale.x;

            m_ppipeline->set_push_properties(::as_memory_block(push));

            // vkCmdPushConstants(
            //     frame.m_pcommandbuffer,
            //     m_pipelineLayout,
            //     VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
            //     0,
            //     sizeof(PointLightPushConstants),
            //     &push
            // );
            pframe->getCommandBuffer()->draw_vertexes(6);
            //vkCmdDraw(frame.m_pcommandbuffer, 6, 1, 0, 0);
        }

    }void point_light_render_system::update(::sandbox::IFrame * pframe, ::gpu::properties * ppropertiesGlobalUbo) {
        auto rotateLight = glm::rotate(glm::mat4(1.f), m_rotationSpeed * pframe->frameTime(), { 0.f, -1.f, 0.f });
        auto & ubo  =(*ppropertiesGlobalUbo);
        int lightIndex = 0;
        auto & sceneobjects = (*pframe->scene_objects());
        for (auto& [id, pobject] : sceneobjects) {
            ::cast < point_light_scene_object > ppointlightsceneobject = pobject;
            if (!ppointlightsceneobject)
                continue;

            ASSERT(lightIndex < point_light::MAX_LIGHTS && "Point lights exceed maximum supported.");

            auto& transform = ppointlightsceneobject->getTransform();
            transform.translation = glm::vec3(rotateLight * glm::vec4(transform.translation, 1.f));

            auto pointLights=ubo["pointLights"];
            pointLights[lightIndex]["position"] = glm::vec4(transform.translation, 1.f);
            pointLights[lightIndex]["color"] = glm::vec4(ppointlightsceneobject->getColor(), ppointlightsceneobject->m_fLightIntensity);

            ++lightIndex;
        }

        ubo["numLights"] = lightIndex;
    }
} //  namespace sandbox_renderer

