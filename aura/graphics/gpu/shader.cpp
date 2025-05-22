#include "framework.h"
#include "shader.h"
//#include "_.h"
//#include "_gpu.h"


namespace gpu
{


   //const char* shader_type_c_str(GLenum etype)
   //{

   //   switch (etype)
   //   {
   //   case GL_VERTEX_SHADER:
   //      return "VERTEX";
   //   case GL_FRAGMENT_SHADER:
   //      return "FRAGMENT";
   //   case GL_GEOMETRY_SHADER:
   //      return "GEOMETRY";
   //   default:
   //      return "(Unknown Shader Type)";
   //   }

   //}


   shader::shader()
   {


   }


   shader::~shader()
   {


   }



   void shader::create_shader(const ::string & pszVertex, const ::string & pszFragment, const ::string & pszGeometry)
   {


      //return ::success;

   }


   void shader::create_shader_with_block(const ::block & blockVertex, const ::block & blockFragment, const ::block & blockGeometry)
   {


   }

   // activate the shader
   // ------------------------------------------------------------------------
   void shader::use()
   {
   }


   void shader::setBool(const ::scoped_string & scopedstrName, bool value)
   {


   }


   void shader::setInt(const ::scoped_string & scopedstrName, int value)
   {


   }


   void shader::setFloat(const ::scoped_string & scopedstrName, float value)
   {


   }


//   void shader::setVec2(const ::scoped_string & scopedstrName, const glm::vec2& value)
//   {
//
//   }


   void shader::setVec2(const ::scoped_string & scopedstrName, float x, float y)
   {

   }


//   void shader::setVec3(const ::scoped_string & scopedstrName, const glm::vec3& value)
//   {
//
//
//   }


   void shader::setVec3(const ::scoped_string & scopedstrName, float x, float y, float z)
   {

   }


//   void shader::setVec4(const ::scoped_string & scopedstrName, const glm::vec4& value)
//   {
//
//   }


   void shader::setVec4(const ::scoped_string & scopedstrName, float x, float y, float z, float w)
   {

   }


   void shader::setMat2(const ::scoped_string & scopedstrName, const float p[2*2])
   {

   }


   void shader::setMat3(const ::scoped_string & scopedstrName, const float p[3*3])
   {

   }


   void shader::setMat4(const ::scoped_string & scopedstrName, const float p[4*4])
   {

   }


   //void shader::shader_compile_errors(GLuint shader, GLenum type, string & strSummary)
   //{

   //   ::e_status estatus = ::success;

   //   return estatus;

   //}


   //void shader::program_compile_errors(GLuint program, string & strSummary)
   //{

   //   ::e_status estatus = ::success;


   //   return estatus;

   //}

   
   void shader::draw()
   {


   }

   
   void shader::on_initialize_shader()
   {


   }


   void shader::bind()
   {


   }


   void shader::push_properties()
   {


   }



   ::gpu::payload * shader::get_payload(const ::scoped_string & scopedstrPayload)
   {

      auto p = m_mapLayout.plookup(scopedstrPayload);

      if (!p)
      {

         return nullptr;

      }

      return &p->element2();

      //m_iMatrixUniform = glGetUniformLocation(
      //   m_pprogram->m_pshader->m_uId,
      //   m_strMatrixUniform
      //return -1;
   }


} // namespace gpu



