#pragma once


#include "aura/graphics/gpu/shader.h"


namespace opengl
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

      virtual void setBool(const ::string & pszName, bool value) override;

      virtual void setInt(const ::string & pszName, int value) override;

      virtual void setFloat(const ::string & pszName, float value) override;

      //virtual void setVec2(const ::string & pszName, const glm::vec2& value) override;
      virtual void setVec2(const ::string & pszName, float x, float y) override;

      //virtual void setVec3(const ::string & pszName, const glm::vec3& value) override;
      virtual void setVec3(const ::string & pszName, float x, float y, float z) override;

      //virtual void setVec4(const ::string & pszName, const glm::vec4& value) override;
      virtual void setVec4(const ::string & pszName, float x, float y, float z, float w) override;

      //virtual void setMat2(const ::string & pszName, const glm::mat2& mat) override;
      //virtual void setMat3(const ::string & pszName, const glm::mat3& mat) override;
      //virtual void setMat4(const ::string & pszName, const glm::mat4& mat) override;
      virtual void setMat2(const ::string & pszName, const float p[2*2]) override;
      virtual void setMat3(const ::string & pszName, const float p[3*3]) override;
      virtual void setMat4(const ::string & pszName, const float p[4*4]) override;



      unsigned int create_shader(const ::string & pszVertex, GLenum type);

      virtual void shader_compile_errors(GLuint shader, GLenum type, string & strSummary);

      virtual void program_compile_errors(GLuint program, string & strSummary);
      ::gpu::uniform get_uniform(const ::string & strUniform) override;

   };


} // namespace opengl



