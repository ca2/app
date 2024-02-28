#pragma once


//#include "acme/primitive/primitive/matter.h"


namespace gpu
{

   enum enum_shader
   {

      shader_fragment,
      shader_projection,

   };

   class CLASS_DECL_AURA shader :
      virtual public ::matter
   {
   public:
      
      
      unsigned int m_uId;

      string      m_strError;

      shader();
      virtual ~shader();

      
      virtual void create_shader(const ::string & pszVertex, const ::string & pszFragment, const ::string & pszGeometry = nullptr);

      virtual void use();

      virtual void setBool(const ::string & pszName, bool value);

      virtual void setInt(const ::string & pszName, int value);

      virtual void setFloat(const ::string & pszName, float value);

      //virtual void setVec2(const ::string & pszName, const glm::vec2& value);
      virtual void setVec2(const ::string & pszName, float x, float y);

      //virtual void setVec3(const ::string & pszName, const glm::vec3& value);
      virtual void setVec3(const ::string & pszName, float x, float y, float z);

      //virtual void setVec4(const ::string & pszName, const glm::vec4& value);
      virtual void setVec4(const ::string & pszName, float x, float y, float z, float w);

      virtual void setMat2(const ::string & pszName, const float p[2*2]);
      virtual void setMat3(const ::string & pszName, const float p[3*3]);
      virtual void setMat4(const ::string & pszName, const float p[4*4]);

      //virtual shader * create_shader(const ::string & pszVertex, enum_shader eshader);

      //static void shader_compile_errors(GLuint shader, enum_shader eshader, string & strSummary);

      //static void program_compile_errors(GLuint program, string & strSummary);


      virtual uniform get_uniform(const ::string & strName);


   };


} // namespace gpu




