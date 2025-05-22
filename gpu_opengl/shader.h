#pragma once


#include "aura/graphics/gpu/shader.h"


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL shader :
      virtual public ::gpu::shader
   {
   public:


      //__creatable_from_base(shader, ::gpu::shader);
      
      
      shader();
      ~shader() override;

      
      virtual void create_shader(const ::string & pszVertex, const ::string & pszFragment, const ::string & pszGeometry = nullptr) override;

      virtual void use() override;

      virtual void setBool(const ::scoped_string & scopedstrName, bool value) override;

      virtual void setInt(const ::scoped_string & scopedstrName, int value) override;

      virtual void setFloat(const ::scoped_string & scopedstrName, float value) override;

      //virtual void setVec2(const ::scoped_string & scopedstrName, const glm::vec2& value) override;
      virtual void setVec2(const ::scoped_string & scopedstrName, float x, float y) override;

      //virtual void setVec3(const ::scoped_string & scopedstrName, const glm::vec3& value) override;
      virtual void setVec3(const ::scoped_string & scopedstrName, float x, float y, float z) override;

      //virtual void setVec4(const ::scoped_string & scopedstrName, const glm::vec4& value) override;
      virtual void setVec4(const ::scoped_string & scopedstrName, float x, float y, float z, float w) override;

      //virtual void setMat2(const ::scoped_string & scopedstrName, const glm::mat2& mat) override;
      //virtual void setMat3(const ::scoped_string & scopedstrName, const glm::mat3& mat) override;
      //virtual void setMat4(const ::scoped_string & scopedstrName, const glm::mat4& mat) override;
      virtual void setMat2(const ::scoped_string & scopedstrName, const float p[2*2]) override;
      virtual void setMat3(const ::scoped_string & scopedstrName, const float p[3*3]) override;
      virtual void setMat4(const ::scoped_string & scopedstrName, const float p[4*4]) override;



      unsigned int create_shader(const ::string & pszVertex, GLenum type);

      virtual void shader_compile_errors(GLuint shader, GLenum type, string & strSummary);

      virtual void program_compile_errors(GLuint program, string & strSummary);
      ::gpu::payload * get_payload(const ::scoped_string & scopedestrUniform) override;

   };


} // namespace gpu_opengl



