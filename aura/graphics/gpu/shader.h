#pragma once


//#include "acme/prototype/prototype/matter.h"


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
      
      
      unsigned int               m_uId;

      string                     m_strError;

      string_map < payload >     m_mapLayout;

      ::file::path               m_pathVertex;
      ::file::path               m_pathFragment;
      ::file::path               m_pathGeometry;

      memory                     m_memoryVertex;
      memory                     m_memoryFragment;
      memory                     m_memoryGeometry;


      shader();
      ~shader() override;

      
      virtual void create_shader(const ::file::path & pathVertex, const ::file::path & pathFragment, const ::file::path & pathGeometry = {});
      virtual void create_shader_with_block(const ::block & blockVertex, const ::block & blockFragment, const ::block & blockGeometry = {});


      virtual void use();

      virtual void setBool(const ::scoped_string & scopedstrName, bool value);

      virtual void setInt(const ::scoped_string & scopedstrName, int value);

      virtual void setFloat(const ::scoped_string & scopedstrName, float value);

      //virtual void setVec2(const ::scoped_string & scopedstrName, const glm::vec2& value);
      virtual void setVec2(const ::scoped_string & scopedstrName, float x, float y);

      //virtual void setVec3(const ::scoped_string & scopedstrName, const glm::vec3& value);
      virtual void setVec3(const ::scoped_string & scopedstrName, float x, float y, float z);

      //virtual void setVec4(const ::scoped_string & scopedstrName, const glm::vec4& value);
      virtual void setVec4(const ::scoped_string & scopedstrName, float x, float y, float z, float w);

      virtual void setMat2(const ::scoped_string & scopedstrName, const float p[2*2]);
      virtual void setMat3(const ::scoped_string & scopedstrName, const float p[3*3]);
      virtual void setMat4(const ::scoped_string & scopedstrName, const float p[4*4]);

      //virtual shader * create_shader(const ::string & pszVertex, enum_shader eshader);

      //static void shader_compile_errors(GLuint shader, enum_shader eshader, string & strSummary);

      //static void program_compile_errors(GLuint program, string & strSummary);


      //virtual payload * get_uniform(const ::string & strName);

      virtual ::gpu::payload * get_payload(const ::scoped_string & scopedstrName);
      virtual void draw();

      virtual void on_initialize_shader();


      virtual void bind();


      virtual void push_properties();



   };


} // namespace gpu




