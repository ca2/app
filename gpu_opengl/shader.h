#pragma once


namespace opengl
{


   class CLASS_DECL_GPU_OPENGL shader :
      virtual public ::gpu::shader
   {
   public:
      
      
      shader();
      virtual ~shader();

      
      virtual ::e_status create_shader(const char * pszVertex, const char * pszFragment, const char * pszGeometry = nullptr) override;

      virtual void use() override;

      virtual void setBool(const char * pszName, bool value) override;

      virtual void setInt(const char * pszName, int value) override;

      virtual void setFloat(const char * pszName, float value) override;

      //virtual void setVec2(const char * pszName, const glm::vec2& value) override;
      virtual void setVec2(const char * pszName, float x, float y) override;

      //virtual void setVec3(const char * pszName, const glm::vec3& value) override;
      virtual void setVec3(const char * pszName, float x, float y, float z) override;

      //virtual void setVec4(const char * pszName, const glm::vec4& value) override;
      virtual void setVec4(const char * pszName, float x, float y, float z, float w) override;

      //virtual void setMat2(const char * pszName, const glm::mat2& mat) override;
      //virtual void setMat3(const char * pszName, const glm::mat3& mat) override;
      //virtual void setMat4(const char * pszName, const glm::mat4& mat) override;
      virtual void setMat2(const char * pszName, const float p[2*2]) override;
      virtual void setMat3(const char * pszName, const float p[3*3]) override;
      virtual void setMat4(const char * pszName, const float p[4*4]) override;



      unsigned int create_shader(const char* pszVertex, GLenum type);

      virtual ::e_status shader_compile_errors(GLuint shader, GLenum type, string & strSummary);

      virtual ::e_status program_compile_errors(GLuint program, string & strSummary);


   };


} // namespace opengl



