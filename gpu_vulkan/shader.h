// Co-creating with V0idsEmbrace@Twitch with
// camilo on 2025-05-19 04:59 <3ThomasBorregaardSorensen!!
#pragma once



#include "aura/graphics/gpu/shader.h"


namespace gpu_vulkan
{


   class CLASS_DECL_GPU_VULKAN shader :
      virtual public ::gpu::shader
   {
   public:


      ::pointer < pipeline > m_ppipeline;


      shader();
      ~shader();


      //void bind(VkCommandBuffer commandBuffer);

      ///static void defaultPipelineConfigInfo(PipelineConfigInfo& configInfo);
   ///private:
///		static ::array<char> readFile(const std::string& filepath);

      /*void createGraphicsPipeline(
         const std::string& vertFilepath,
         const std::string& fragFilepath,
         const PipelineConfigInfo& configInfo);

      void createShaderModule(const ::block& block, VkShaderModule* shaderModule);*/

      /*
      VkPipeline graphicsPipeline;
      VkShaderModule vertShaderModule;
      VkShaderModule fragShaderModule;*/
      VkPipelineLayout		m_vkpipelinelayout;


      void _create_pipeline_layout(int iSize);

      void draw() override;

      //void initialize_shader(
      //	::graphics3d::context* pcontext,
      //	const ::file::path& pathVert,
      //	const ::file::path& pathFrag,
      //	const ::graphics3d::property* pproperties) override;

      void on_initialize_shader() override;


      void bind() override;


      void push_properties() override;


   };


} // namespace gpu_vulkan 




//#pragma once
//
//
//#include "aura/graphics/gpu/shader.h"
//
//
//namespace gpu_vulkan
//{
//   //enum enum_type
//   //{
//   //   e_type_int,
//   //   e_type_float,
//
//   //};
//
//   class CLASS_DECL_GPU_VULKAN shader :
//      virtual public ::gpu::shader
//   {
//   public:
//
//      //struct payload
//      //{
//
//      //   int m_iOffset;
//      //   enum_type m_etype;
//
//      //};
//
//      memory   m_memoryPushConstants;
//      //__creatable_from_base(shader, ::gpu::shader);
//      
//      shader();
//      ~shader() override;
//
//      
//      virtual void create_shader(const ::string & pszVertex, const ::string & pszFragment, const ::string & pszGeometry = nullptr) override;
//
//      virtual void use() override;
//
//      virtual void setBool(const ::scoped_string & scopedstrName, bool value) override;
//
//      virtual void setInt(const ::scoped_string & scopedstrName, int value) override;
//
//      virtual void setFloat(const ::scoped_string & scopedstrName, float value) override;
//
//      //virtual void setVec2(const ::scoped_string & scopedstrName, const glm::vec2& value) override;
//      virtual void setVec2(const ::scoped_string & scopedstrName, float x, float y) override;
//
//      //virtual void setVec3(const ::scoped_string & scopedstrName, const glm::vec3& value) override;
//      virtual void setVec3(const ::scoped_string & scopedstrName, float x, float y, float z) override;
//
//      //virtual void setVec4(const ::scoped_string & scopedstrName, const glm::vec4& value) override;
//      virtual void setVec4(const ::scoped_string & scopedstrName, float x, float y, float z, float w) override;
//
//      //virtual void setMat2(const ::scoped_string & scopedstrName, const glm::mat2& mat) override;
//      //virtual void setMat3(const ::scoped_string & scopedstrName, const glm::mat3& mat) override;
//      //virtual void setMat4(const ::scoped_string & scopedstrName, const glm::mat4& mat) override;
//      virtual void setMat2(const ::scoped_string & scopedstrName, const float p[2*2]) override;
//      virtual void setMat3(const ::scoped_string & scopedstrName, const float p[3*3]) override;
//      virtual void setMat4(const ::scoped_string & scopedstrName, const float p[4*4]) override;
//
//
//
//      unsigned int create_shader(const ::string & pszVertex, VkShaderStageFlagBits type);
//
//      virtual void shader_compile_errors(int shader, VkShaderStageFlagBits type, string & strSummary);
//
//      virtual void program_compile_errors(int program, string & strSummary);
//      //::gpu::uniform get_uniform(const ::string & strUniform) override;
//
//   };
//
//
//} // namespace gpu_vulkan
//
//
//
