#include "framework.h"
// Co-creating with V0idsEmbrace@Twitch with
// camilo on 2025-05-19 04:59 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "shader.h"
#include "context.h"
#include "descriptors.h"
//#include "engine.h"
#include "pipeline.h"
#include "renderer.h"
//#include "app-cube/cube/impact.h"


namespace gpu_vulkan
{


   shader::shader()
   {



   }


   shader::~shader()
   {

      ::cast < context > pcontext = m_pcontext;

      vkDestroyPipelineLayout(pcontext->logicalDevice(), m_vkpipelinelayout, nullptr);

   }


   void shader::_create_pipeline_layout(int iSize)
   {

      ::cast < context > pcontext = m_pcontext;

      ::cast < engine > pengine = pcontext->m_pimpact->m_pengine;

      VkPushConstantRange pushConstantRange{};
      pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
      pushConstantRange.offset = 0;
      //pushConstantRange.size = sizeof(PointLightPushConstants);
      pushConstantRange.size = iSize;

      auto globalSetLayout = pengine->m_psetdescriptorlayoutGlobal->getDescriptorSetLayout();

      ::array<VkDescriptorSetLayout> descriptorSetLayouts{ globalSetLayout };

      VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
      pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
      pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
      pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
      pipelineLayoutInfo.pushConstantRangeCount = 1;
      pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
      //pipelineLayoutInfo.pPushConstantRanges = nullptr;
      if (vkCreatePipelineLayout(
         pcontext->logicalDevice(),
         &pipelineLayoutInfo,
         nullptr,
         &m_vkpipelinelayout) !=
         VK_SUCCESS)
      {
         throw ::exception(error_failed, "failed to create pipeline layout!");
      }

   }


   void shader::on_initialize_shader()
   {

      _create_pipeline_layout(m_properties.m_memory.size());

      __construct_new(m_ppipeline);

      ::cast <engine> pengine = m_pcontext->m_pimpact->m_pengine;

      PipelineConfigInfo pipelineConfig{};
      pipeline::defaultPipelineConfigInfo(pipelineConfig);
      if (m_eflag & e_flag_clear_default_bindings_and_attributes_descriptions)
      {
         pipelineConfig.attributeDescriptions.clear();
         pipelineConfig.bindingDescriptions.clear();
      }
      pipelineConfig.renderPass = pengine->m_prenderer->m_pvkcrenderpass->m_vkrenderpass;
      pipelineConfig.pipelineLayout = m_vkpipelinelayout;


      m_ppipeline->initialize_pipeline(m_pcontext,
         pengine->_translate_shader_path(m_pathVert),
         pengine->_translate_shader_path(m_pathFrag),
         pipelineConfig);


   }


   void shader::bind() const
   {

      ::cast <engine> pengine = m_pcontext->m_pimpact->m_pengine;

      auto commandBuffer = pengine->m_prenderer->getCurrentCommandBuffer();

      m_ppipeline->bind(commandBuffer);

      auto globalDescriptorSet = pengine->getcurrentDescriptorSet();

      vkCmdBindDescriptorSets(
         commandBuffer,
         VK_PIPELINE_BIND_POINT_GRAPHICS,
         m_vkpipelinelayout,
         0,
         1,
         &globalDescriptorSet,
         0,
         nullptr);

   }


   void shader::push_properties()
   {

      ::cast <engine> pengine = m_pcontext->m_pimpact->m_pengine;

      auto commandBuffer = pengine->m_prenderer->getCurrentCommandBuffer();

      vkCmdPushConstants(
         commandBuffer,
         m_vkpipelinelayout,
         VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
         0,
         m_properties.size(),
         m_properties.data());

   }


   void shader::draw()
   {

      ::cast <engine> pengine = m_pcontext->m_pimpact->m_pengine;

      auto commandBuffer = pengine->m_prenderer->getCurrentCommandBuffer();

      vkCmdDraw(commandBuffer, 6, 1, 0, 0);

   }


} // namespace gpu_vulkan



//#include "shader.h"
//
//
//namespace gpu_vulkan
//{
//
//
//   const char* shader_type_c_str(VkShaderStageFlagBits etype)
//   {
//
//      switch (etype)
//      {
//      case VK_SHADER_STAGE_VERTEX_BIT:
//         return "VERTEX";
//      case VK_SHADER_STAGE_FRAGMENT_BIT:
//         return "FRAGMENT";
//#if !defined(__APPLE__) && !defined(__ANDROID__)
//      case VK_SHADER_STAGE_GEOMETRY_BIT:
//         return "GEOMETRY";
//#endif
//      default:
//         return "(Unknown Shader Type)";
//      }
//
//   }
//
//
//   shader::shader()
//   {
//
//
//   }
//
//
//   shader::~shader()
//   {
//
//
//   }
//
//
//   unsigned int shader::create_shader(const ::string & strSource, VkShaderStageFlagBits type)
//   {
//
//      //unsigned int uShader;
//
//      //uShader = glCreateShader(type);
//
//      //if(!uShader)
//      //{
//
//      //   GLenum eerror = glGetError();
//      //   
//      //   auto errString = vulkan_error_string(eerror);
//
//      //   informationf("error %d \"%s\"", eerror, errString);
//
//      //   return ::error_failed;
//
//      //}
//
//      //const char * sza[1];
//
//      //sza[0] = strSource;
//
//      //glShaderSource(uShader, 1, sza, NULL);
//
//      //glCompileShader(uShader);
//
//      //information() << "compiling shader : " << sza[0];
//
//      ////string strSummary;
//
//      ////::e_status estatus =
//      //
//      //shader_compile_errors(uShader, type, m_strError);
//
//      ////if (!estatus)
//      ////{
//
//      ////   return 0;
//
//      ////}
//      //m_strError.empty();
//
//      //return uShader;
//
//      return 0;
//
//
//   }
//
//
//   void shader::create_shader(const ::string & pszVertex, const ::string & pszFragment, const ::string & pszGeometry)
//   {
//
//      unsigned int uVertex = create_shader(pszVertex, VK_SHADER_STAGE_VERTEX_BIT);
//
//      unsigned int uFragment = create_shader(pszFragment, VK_SHADER_STAGE_FRAGMENT_BIT);
//      
//#if !defined(__APPLE__) && !defined(__ANDROID__)
//
//      unsigned int uGeometry = 0;
//
//      bool bGeometry = pszGeometry.trimmed().has_character();
//
//      if (bGeometry)
//      {
//
//         uGeometry = create_shader(pszGeometry, VK_SHADER_STAGE_GEOMETRY_BIT);
//
//      }
//      
//#endif
//
////      m_uId = glCreateProgram();
////
////      glAttachShader(m_uId, uVertex);
////
////      glAttachShader(m_uId, uFragment);
////      
////#if !defined(__APPLE__) && !defined(__ANDROID__)
////
////      if (bGeometry)
////      {
////
////         glAttachShader(m_uId, uGeometry);
////
////      }
////      
////#endif
////
////      glLinkProgram(m_uId);
////      
////      // Validate program
//////      glValidateProgram(m_uId);
////
////      string strSummary;
////
////      ///::e_status estatus =
////      
////      program_compile_errors(m_uId, strSummary);
////
////      //if(estatus.succeeded())
////      //{
////
////      //   return estatus;
////
////      //}
////
////      // delete the shaders
////      // they're linked into our program
////
////      glDeleteShader(uVertex);
////
////      glDeleteShader(uFragment);
////
////#if !defined(__APPLE__) && !defined(__ANDROID__)
////
////      if (bGeometry)
////      {
////
////         glDeleteShader(uGeometry);
////
////      }
////      
////#endif
////
//      //return ::success;
//
//   }
//
//
//   // activate the shader
//   // ------------------------------------------------------------------------
//   void shader::use()
//   {
//      
//      //glUseProgram(m_uId);
//      
//   }
//
//
//   void shader::setBool(const ::scoped_string & scopedstrName, bool b)
//   {
//
//      setInt(scopedstrName, b != false);
//
//      //GLint i = glGetUniformLocation(m_uId, pszName);
//
//      //glUniform1i(i, (int)value);
//
//   }
//
//
//   void shader::setInt(const ::scoped_string & scopedstrName, int i)
//   {
//
//      auto p = get_payload(scopedstrName);
//
//      if(!p)
//      {
//
//         throw ::exception(error_not_found, "not known property");
//
//      }
//
//      m_memoryPushConstants.set_at(p->m_iOffset, &i, sizeof(int));
//
//      //GLint i = glGetUniformLocation(m_uId, pszName);
//
//      //glUniform1i(i, value);
//
//      //int i = value != 0;
//      //m_memoryPushConstants.append(&i, sizeof(int));
//
//
//   }
//
//
//   void shader::setFloat(const ::scoped_string & scopedstrName, float f)
//   {
//
//      //GLint i = glGetUniformLocation(m_uId, pszName);
//
//      //glUniform1f(i, value);
//      //int i = value != 0;
//      auto p = get_payload(scopedstrName);
//
//      if (!p)
//      {
//
//         throw ::exception(error_not_found, "not known property");
//
//      }
//
//      m_memoryPushConstants.set_at(p->m_iOffset, &f, sizeof(float));
//
//   }
//
//
////   void shader::setVec2(const ::scoped_string & scopedstrName, const glm::vec2& value)
////   {
////
////      GLint i = glGetUniformLocation(m_uId, pszName);
////
////      glUniform2fv(i, 1, &value[0]);
////
////   }
//
//
//   void shader::setVec2(const ::scoped_string & scopedstrName, float x, float y)
//   {
//
//      auto p = get_payload(scopedstrName);
//
//      if (!p)
//      {
//
//         throw ::exception(error_not_found, "not known property");
//
//      }
//
//      m_memoryPushConstants.set_at(p->m_iOffset, &x, sizeof(float));
//      m_memoryPushConstants.set_at(p->m_iOffset + sizeof(float), &y, sizeof(float));
//
//   }
//
//
////   void shader::setVec3(const ::scoped_string & scopedstrName, const glm::vec3& value)
////   {
////
////      GLint i = glGetUniformLocation(m_uId, pszName);
////
////      glUniform3fv(i, 1, &value[0]);
////
////   }
//
//
//   void shader::setVec3(const ::scoped_string & scopedstrName, float x, float y, float z)
//   {
//      
//      auto p = get_payload(scopedstrName);
//
//      if (!p)
//      {
//
//         throw ::exception(error_not_found, "not known property");
//
//      }
//
//      m_memoryPushConstants.set_at(p->m_iOffset, &x, sizeof(float));
//      m_memoryPushConstants.set_at(p->m_iOffset + sizeof(float), &y, sizeof(float));
//      m_memoryPushConstants.set_at(p->m_iOffset + 2*sizeof(float), &z, sizeof(float));
//      
//   }
//
//
////   void shader::setVec4(const ::scoped_string & scopedstrName, const glm::vec4& value)
////   {
////
////      GLint i = glGetUniformLocation(m_uId, pszName);
////
////      glUniform4fv(i, 1, &value[0]);
////
////   }
//
//
//   void shader::setVec4(const ::scoped_string & scopedstrName, float x, float y, float z, float w)
//   {
//
//      auto p = get_payload(scopedstrName);
//
//      if (!p)
//      {
//
//         throw ::exception(error_not_found, "not known property");
//
//      }
//
//      m_memoryPushConstants.set_at(p->m_iOffset, &x, sizeof(float));
//      m_memoryPushConstants.set_at(p->m_iOffset + sizeof(float), &y, sizeof(float));
//      m_memoryPushConstants.set_at(p->m_iOffset + 2 * sizeof(float), &z, sizeof(float));
//      m_memoryPushConstants.set_at(p->m_iOffset + 3 * sizeof(float), &w, sizeof(float));
//
//   }
//
//
//   void shader::setMat2(const ::scoped_string & scopedstrName, const float a[2*2])
//   {
//
//      auto p = get_payload(scopedstrName);
//
//      if (!p)
//      {
//
//         throw ::exception(error_not_found, "not known property");
//
//      }
//
//      m_memoryPushConstants.set_at(p->m_iOffset, (void *) a, 2*2*sizeof(float));
//
//   }
//
//
//   void shader::setMat3(const ::scoped_string & scopedstrName, const float a[3*3])
//   {
//
//      auto p = get_payload(scopedstrName);
//
//      if (!p)
//      {
//
//         throw ::exception(error_not_found, "not known property");
//
//      }
//
//      m_memoryPushConstants.set_at(p->m_iOffset, a, 3 * 3 * sizeof(float));
//
//   }
//
//
//   void shader::setMat4(const ::scoped_string & scopedstrName, const float a[4*4])
//   {
//
//      auto p = get_payload(scopedstrName);
//
//      if (!p)
//      {
//
//         throw ::exception(error_not_found, "not known property");
//
//      }
//
//      m_memoryPushConstants.set_at(p->m_iOffset, a, 4 * 4 * sizeof(float));
//
//   }
//
//
//   void shader::shader_compile_errors(int shader, VkShaderStageFlagBits type, string & strSummary)
//   {
//
//      //::e_status estatus = ::success;
//
//      //GLint success = 0;
//
//      //GLchar infoLog[1024];
//
//      //glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//
//      //if (success)
//      //{
//
//      //   strSummary.formatf("SUCCESS::SHADER_COMPILATION (%s) \n -- --------------------------------------------------- -- \n", shader_type_c_str(type));
//
//      //}
//      //else
//      //{
//
//      //   glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
//
//      //   const char * psz = shader_type_c_str(type);
//
//      //   const char * pszLog = infoLog;
//
//      //   strSummary.formatf("error::SHADER_COMPILATION_ERROR of type: %s \n %s \n -- --------------------------------------------------- -- \n", psz, pszLog);
//
//      //   warning() << strSummary;
//
//      //   throw ::exception(error_failed, "Shader Compilation Error", strSummary);
//
//      //}
//
//      //information() << strSummary;
//
//      ////return estatus;
//
//   }
//
//
//   void shader::program_compile_errors(int program, string & strSummary)
//   {
//
//      ////::e_status estatus = ::success;
//
//      //GLint success;
//
//      //GLchar infoLog[1024];
//      //
//      //glGetProgramiv(program, GL_LINK_STATUS, &success);
//
//      //if (success)
//      //{
//
//      //   strSummary.formatf("SUCCESS::PROGRAM_LINKING \n -- --------------------------------------------------- -- \n");
//
//      //}
//      //else
//      //{
//
//      //   glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
//
//      //   strSummary.formatf("error::PROGRAM_LINKING_ERROR : \n %s \n -- --------------------------------------------------- -- \n", infoLog);
//
//      //   throw ::exception(error_failed);
//
//      //}
//
//      //information() << strSummary;
//
//      ////return estatus;
//
//   }
//
//
//   //::gpu::payload * shader::get_payload(const ::scoped_string & scopedstrPayload)
//   //{
//   //   
//   //   auto uniform = glGetUniformLocation(m_uId, strUniform);
//
//   //   return uniform;
//
//   //}
//
//
//} // namespace gpu_vulkan
//
//
//
