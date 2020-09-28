#pragma once


namespace gpu
{

   enum enum_shader
   {

      shader_fragment,
      shader_projection,

   };

   class CLASS_DECL_AURA shader :
      virtual public ::elemental
   {
   public:
      
      
      unsigned int m_uId;

      shader();
      virtual ~shader();

      
      virtual ::estatus create_shader(const char * pszVertex, const char * pszFragment, const char * pszGeometry = nullptr);

      virtual void use();

      virtual void setBool(const char * pszName, bool value);

      virtual void setInt(const char * pszName, int value);

      virtual void setFloat(const char * pszName, float value);

      virtual void setVec2(const char * pszName, const glm::vec2& value);
      virtual void setVec2(const char * pszName, float x, float y);

      virtual void setVec3(const char * pszName, const glm::vec3& value);
      virtual void setVec3(const char * pszName, float x, float y, float z);

      virtual void setVec4(const char * pszName, const glm::vec4& value);
      virtual void setVec4(const char * pszName, float x, float y, float z, float w);

      virtual void setMat2(const char * pszName, const glm::mat2& mat);
      virtual void setMat3(const char * pszName, const glm::mat3& mat);
      virtual void setMat4(const char * pszName, const glm::mat4& mat);

      //virtual shader * create_shader(const char* pszVertex, enum_shader eshader);

      //static ::estatus shader_compile_errors(GLuint shader, enum_shader eshader, string & strSummary);

      //static ::estatus program_compile_errors(GLuint program, string & strSummary);


   };


} // namespace gpu



