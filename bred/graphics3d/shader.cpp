// Co-creating with V0idsEmbrace@Twitch with
// camilo on 2025-05-19 04:30 <3ThomasBorregaardSorensen!!
#include "framework.h"
//#include "shader.h"
//#include "context.h"
//
//
//namespace graphics3d
//{
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
//   void shader::initialize_shader(
//      ::gpu::context* pgpucontext,
//      const ::file::path& pathVert,
//      const ::file::path& pathFrag, 
//      const ::gpu::property * pproperties,
//      ::graphics3d::shader::enum_flag eflag)
//   {
//
//      m_pgpucontext = pgpucontext;
//      m_pathVert = pathVert;
//      m_pathFrag = pathFrag;
//      m_properties.set(pproperties);
//      m_eflag = eflag;
//
//      on_initialize_shader();
//
//   }
//   void shader::on_initialize_shader()
//   {
//
//
//   }
//
//
//   void shader::bind() const
//   {
//
//
//   }
//
//   
//   void shader::unbind() const
//   {
//
//
//   }
//
//
//   void shader::push_properties()
//   {
//
//
//   }
//
//
//   void shader::draw()
//   {
//
//
//   }
//
//   void shader::setBool(const ::scoped_string& scopedstrName, bool value)
//   {
//      setInt(scopedstrName, value != false);
//   }
//   void shader::setInt(const ::scoped_string& scopedstrName, ::i32 value)
//   {
//      ::string strName(scopedstrName);
//      auto& a = m_properties.as_i32(strName);
//      a = value;
//
//   }
//   void shader::setFloat(const ::scoped_string& scopedstrName, ::f32 value)
//   {
//      ::string strName(scopedstrName);
//      auto& a = m_properties.as_f32(strName);
//      a = value;
//
//   }
//   //void shader::setVec2(const ::scoped_string & scopedstrName, const floating_sequence2& value) override;
//   void shader::setVec2(const ::scoped_string& scopedstrName, ::f32 x, ::f32 y)
//   {
//      ::string strName(scopedstrName);
//      auto& a = m_properties.seq2(strName);
//      a.x = x;
//      a.y = y;
//
//   }
//   void shader::setVec2(const ::scoped_string& scopedstrName, const floating_sequence2& a)
//   {
//      ::string strName(scopedstrName);
//      m_properties.seq2(strName) = a;
//
//   }
//   //void shader::setVec3(const ::scoped_string & scopedstrName, const floating_sequence3& value) override;
//   void shader::setVec3(const ::scoped_string& scopedstrName, ::f32 x, ::f32 y, ::f32 z)
//   {
//      ::string strName(scopedstrName);
//      auto& a = m_properties.seq3(strName);
//      a.x = x;
//      a.y = y;
//      a.z = z;
//
//   }
//
//   void shader::setVec3(const ::scoped_string& scopedstrName, const floating_sequence3& a)
//   {
//      ::string strName(scopedstrName);
//      m_properties.seq3(strName) = a;
//
//   }
//   //void shader::setVec4(const ::scoped_string & scopedstrName, const floating_sequence4& value) override;
//   void shader::setVec4(const ::scoped_string& scopedstrName, ::f32 x, ::f32 y, ::f32 z, ::f32 w)
//   {
//      ::string strName(scopedstrName);
//      auto& a = m_properties.seq4(strName);
//      a.x = x;
//      a.y = y;
//      a.z = z;
//      a.w = w;
//
//   }
//
//   void shader::setVec4(const ::scoped_string& scopedstrName, const floating_sequence4& a)
//   {
//      ::string strName(scopedstrName);
//      m_properties.seq4(strName) = a;
//      
//   }
//
//   //void shader::setMat2(const ::scoped_string & scopedstrName, const floating_matrix2& mat) override;
//   //void shader::setMat3(const ::scoped_string & scopedstrName, const floating_matrix3& mat) override;
//   //void shader::setMat4(const ::scoped_string & scopedstrName, const floating_matrix4& mat) override;
//   void shader::setMat2(const ::scoped_string& scopedstrName, const ::floating_matrix2& a)
//   {
//      ::string strName(scopedstrName);
//      m_properties.floating_matrix2(strName.c_str())= a;
//
//   }
//   void shader::setMat3(const ::scoped_string& scopedstrName, const ::floating_matrix3& a)
//   {
//      ::string strName(scopedstrName);
//      m_properties.floating_matrix3(strName.c_str()) =  a;
//
//   }
//   void shader::setMat4(const ::scoped_string& scopedstrName, const ::floating_matrix4& a)
//   {
//      ::string strName(scopedstrName);
//      m_properties.floating_matrix4(strName.c_str()) = a;
//
//   }
//
//
//
//} // namespace graphics3d