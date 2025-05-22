#pragma once
//#include <string>
//#include <vector>


#include "context.h"


namespace gpu_vulkan
{


   struct PipelineConfigInfo
   {


      PipelineConfigInfo() = default;
      PipelineConfigInfo(const PipelineConfigInfo &) = delete;
      PipelineConfigInfo & operator=(const PipelineConfigInfo &) = delete;


      ::array<VkVertexInputBindingDescription> bindingDescriptions{};
      ::array<VkVertexInputAttributeDescription> attributeDescriptions{};
      VkPipelineViewportStateCreateInfo viewportInfo;
      VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
      VkPipelineRasterizationStateCreateInfo rasterizationInfo;
      VkPipelineMultisampleStateCreateInfo multisampleInfo;
      VkPipelineColorBlendAttachmentState colorBlendAttachment;
      VkPipelineColorBlendStateCreateInfo colorBlendInfo;
      VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
      ::array<VkDynamicState> dynamicStateEnables;
      VkPipelineDynamicStateCreateInfo dynamicStateInfo;
      VkPipelineLayout pipelineLayout = nullptr;
      VkRenderPass renderPass = nullptr;
      uint32_t subpass = 0;
   };

   class CLASS_DECL_GPU_VULKAN pipeline :
      virtual public ::particle
   {
   public:


      pipeline();
      virtual void initialize_pipeline(
         ::gpu::context * pcontext,
         const ::file::path & pathVert,
         const ::file::path & pathFrag,
         const PipelineConfigInfo & configInfo);
      virtual void initialize_pipeline_with_block(
         ::gpu::context * pcontext,
         const ::block & blockVert,
         const ::block & blockFrag,
         const PipelineConfigInfo & configInfo);
      ~pipeline();

      pipeline(const pipeline &) = delete;
      void operator=(const pipeline &) = delete;

      void bind(VkCommandBuffer commandBuffer);

      static void defaultPipelineConfigInfo(PipelineConfigInfo & configInfo);
   private:
      static ::array<char> readFile(const std::string & filepath);

      void createGraphicsPipeline(
         const ::file::path & pathVert,
         const ::file::path & pathFrag,
         const PipelineConfigInfo & configInfo);

      void createShaderModule(const ::block & block, VkShaderModule * shaderModule);

      ::pointer < context > m_pcontext;
      VkPipeline graphicsPipeline;
      VkShaderModule vertShaderModule;
      VkShaderModule fragShaderModule;
   };


} // namespace gpu_vulkan 



