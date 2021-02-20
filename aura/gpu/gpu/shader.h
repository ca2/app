#pragma once


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

      shader();
      virtual ~shader();

      
      virtual ::e_status create_shader(const char * pszVertex, const char * pszFragment, const char * pszGeometry = nullptr);

      virtual void use();

      virtual void setBool(const char * pszName, bool value);

      virtual void setInt(const char * pszName, int value);

      virtual void setFloat(const char * pszName, float value);

      //virtual void setVec2(const char * pszName, const glm::vec2& value);
      virtual void setVec2(const char * pszName, float x, float y);

      //virtual void setVec3(const char * pszName, const glm::vec3& value);
      virtual void setVec3(const char * pszName, float x, float y, float z);

      //virtual void setVec4(const char * pszName, const glm::vec4& value);
      virtual void setVec4(const char * pszName, float x, float y, float z, float w);

      virtual void setMat2(const char * pszName, const float p[2*2]);
      virtual void setMat3(const char * pszName, const float p[3*3]);
      virtual void setMat4(const char * pszName, const float p[4*4]);

      //virtual shader * create_shader(const char* pszVertex, enum_shader eshader);

      //static ::e_status shader_compile_errors(GL::u32 shader, enum_shader eshader, string & strSummary);

      //static ::e_status program_compile_errors(GL::u32 program, string & strSummary);


   };


} // namespace gpu




