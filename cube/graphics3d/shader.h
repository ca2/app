//// Co-creating with V0idsEmbrace@Twitch with
//// camilo on 2025-05-18 23:14 <3ThomasBorregaardSorensen!!
//#pragma once
//
//
//#include "cube/gpu/properties.h"
//
//
//namespace graphics3d
//{
//
//
//   class CLASS_DECL_CUBE shader :
//      virtual public ::particle
//   {
//   public:
//
//      enum enum_flag
//      {
//         e_flag_none = 0,
//         e_flag_clear_default_bindings_and_attributes_descriptions = 1,
//
//      };
//
//
//      ::pointer < context >   m_pgpucontext;
//      ::file::path            m_pathVert;
//      ::file::path            m_pathFrag;
//      properties              m_properties;
//      enum_flag               m_eflag = e_flag_none;
//
//
//      shader();
//      ~shader() override;
//
//
//      virtual void initialize_shader(
//         ::gpu::context* pgpucontext,
//         const ::file::path& pathVert,
//         const ::file::path & pathFrag, 
//         const ::gpu::property * pproperties, 
//         enum_flag eflag = e_flag_none);
//
//
//      virtual void on_initialize_shader();
//
//      virtual void bind() const;
//
//      virtual void unbind() const;
//
//      virtual void push_properties();
//
//      virtual void draw();
//
//
//      virtual void setBool(const ::scoped_string& scopedstrName, bool value);
//
//      virtual void setInt(const ::scoped_string& scopedstrName, int value);
//
//      virtual void setFloat(const ::scoped_string& scopedstrName, float value);
//
//      //virtual void setVec2(const ::scoped_string & scopedstrName, const glm::vec2& value) override;
//      virtual void setVec2(const ::scoped_string& scopedstrName, float x, float y);
//      virtual void setVec2(const ::scoped_string& scopedstrName, const ::glm::vec2& a);
//      //virtual void setVec3(const ::scoped_string & scopedstrName, const glm::vec3& value) override;
//      virtual void setVec3(const ::scoped_string& scopedstrName, float x, float y, float z);
//      virtual void setVec3(const ::scoped_string& scopedstrName, const ::glm::vec3& a);
//      //virtual void setVec4(const ::scoped_string & scopedstrName, const glm::vec4& value) override;
//      virtual void setVec4(const ::scoped_string& scopedstrName, float x, float y, float z, float w);
//
//      virtual void setVec4(const ::scoped_string& scopedstrName, const ::glm::vec4& a);
//
//      //virtual void setMat2(const ::scoped_string & scopedstrName, const glm::mat2& mat) override;
//      //virtual void setMat3(const ::scoped_string & scopedstrName, const glm::mat3& mat) override;
//      //virtual void setMat4(const ::scoped_string & scopedstrName, const glm::mat4& mat) override;
//      virtual void setMat2(const ::scoped_string& scopedstrName, const ::glm::mat2 & a);
//      virtual void setMat3(const ::scoped_string& scopedstrName, const ::glm::mat3& a);
//      virtual void setMat4(const ::scoped_string& scopedstrName, const ::glm::mat4& a);
//
//
//   };
//
//
//} // namespace graphics3d
//
//
