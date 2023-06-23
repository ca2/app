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

   // activate the shader
   // ------------------------------------------------------------------------
   void shader::use()
   {
   }


   void shader::setBool(const ::string & pszName, bool value)
   {


   }


   void shader::setInt(const ::string & pszName, int value)
   {


   }


   void shader::setFloat(const ::string & pszName, float value)
   {


   }


//   void shader::setVec2(const ::string & pszName, const glm::vec2& value)
//   {
//
//   }


   void shader::setVec2(const ::string & pszName, float x, float y)
   {

   }


//   void shader::setVec3(const ::string & pszName, const glm::vec3& value)
//   {
//
//
//   }


   void shader::setVec3(const ::string & pszName, float x, float y, float z)
   {

   }


//   void shader::setVec4(const ::string & pszName, const glm::vec4& value)
//   {
//
//   }


   void shader::setVec4(const ::string & pszName, float x, float y, float z, float w)
   {

   }


   void shader::setMat2(const ::string & pszName, const float p[2*2])
   {

   }


   void shader::setMat3(const ::string & pszName, const float p[3*3])
   {

   }


   void shader::setMat4(const ::string & pszName, const float p[4*4])
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

   uniform shader::get_uniform(const ::string & strUniform)
   {


      //m_iMatrixUniform = glGetUniformLocation(
      //   m_pprogram->m_pshader->m_uId,
      //   m_strMatrixUniform
      return -1;
   }


} // namespace gpu



